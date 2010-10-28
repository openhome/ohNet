#include "OhmSender.h"
#include <Ascii.h>
#include <Maths.h>

using namespace Zapp;

// ProviderSender

ProviderSender::ProviderSender(DvDevice& aDevice)
    : DvServiceMusicOpenhomeOrgSender1(aDevice)
    , iMutex("PSND")
    , iTimerAudioPresent(MakeFunctor(*this, &ProviderSender::TimerAudioPresentExpired))
{
    EnableActionMetadata();
    EnableActionAudio();
    EnableActionStatus();
    EnableActionAttributes();
    
    SetPropertyMetadata(Brx::Empty());
    SetPropertyAudio(false);
    SetStatusInactive();
    SetPropertyAttributes(Brx::Empty());
}

void ProviderSender::Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue)
{
	Brhz value;
    GetPropertyMetadata(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
}

void ProviderSender::Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue)
{
    TBool value;
    GetPropertyAudio(value);
    aResponse.Start();
    aValue.Write(value);
    aResponse.End();
}

void ProviderSender::Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue)
{
    Brhz value;
    GetPropertyStatus(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
}

void ProviderSender::Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue)
{
    Brhz value;
    GetPropertyAttributes(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
}

void ProviderSender::SetMetadata(const Brx& aValue)
{
	SetPropertyMetadata(aValue);
}

static const Brn kStatusReady("Ready");
static const Brn kStatusSending("Sending");
static const Brn kStatusBlocked("Blocked");
static const Brn kStatusInactive("Inactive");

void ProviderSender::SetStatusReady()
{
    SetPropertyStatus(kStatusReady);
}

void ProviderSender::SetStatusSending()
{
    SetPropertyStatus(kStatusSending);
}

void ProviderSender::SetStatusBlocked()
{
    SetPropertyStatus(kStatusBlocked);
}

void ProviderSender::SetStatusInactive()
{
    SetPropertyStatus(kStatusInactive);
}

void ProviderSender::InformAudioPresent()
{
    SetPropertyAudio(true);
    iTimerAudioPresent.FireIn(kTimeoutAudioPresentMs);
}
    
void ProviderSender::TimerAudioPresentExpired()
{
    SetPropertyAudio(false);
}


// OhmSender

OhmSender::OhmSender(DvDevice& aDevice, const Brx& aName, TUint aChannel)
    : iDevice(aDevice)
    , iName(aName)
    , iChannel(aChannel)
    , iEnabled(false)
    , iSocketAudio(kTtl, 0)
    , iReaderAudio(iSocketAudio)
    , iWriterAudio(iSocketAudio)
    , iAudioReceive(iReaderAudio)
    , iMutexStartStop("OHMS")
    , iMutexActive("OHMA")
    , iNetworkAudioDeactivated("OHMD", 0)
    , iTimerAliveJoin(MakeFunctor(*this, &OhmSender::TimerAliveJoinExpired))
    , iTimerAliveAudio(MakeFunctor(*this, &OhmSender::TimerAliveAudioExpired))
    , iActivated(false)
    , iStarted(false)
    , iActive(false)
{
    iProvider = new ProviderSender(iDevice);
    
    UpdateChannel();

    iThreadAudio = new ThreadFunctor("MPAU", MakeFunctor(*this, &OhmSender::RunAudio), kThreadPriorityAudio, kThreadStackBytesAudio);
    iThreadAudio->Start();
}

OhmSender::~OhmSender()
{
    iMutexStartStop.Wait();

    if (iActivated) {    
        iActivated = false;
    
        Stop();
    }
    
    iMutexStartStop.Signal();

    delete iThreadAudio;
}

// Start always called with the start/stop mutex locked

void OhmSender::Start()
{
    if (!iStarted) {
        iFrame = 0;
        iSocketAudio.AddMembership(iEndpoint);
        iSocketAudio.SetSendBufBytes(kUdpSendBufBytes);
        iThreadAudio->Signal();
        iStarted = true;
    }
}

// Stop always called with the start/stop mutex locked

void OhmSender::Stop()
{
    if (iStarted) {
        iReaderAudio.ReadInterrupt();
        iNetworkAudioDeactivated.Wait();
        iSocketAudio.DropMembership();
        iStarted = false;
    }
}

/*
void OhmSender::Play(const Brx& aAudioBuffer)
{
    iFifoAudio.Write(aMsg);
}

void OhmSender::RunPipeline()
{
    while (true) {
        //MsgIb* msg = iFifo.Read();
    }
}
*/

//  This runs a little state machine where the current state is reflected by:
//
//  iAliveJoined: Indicates that someone is listening to us (we received a join recently)
//  iAliveBlocked: Indicates that someone else is sending on our channel (we received audio recently)
//
//  iActive, when true, causes pipeline audio to be sent out over the network
//
//  The state machine ensures that iActive is only true when iAliveJoined is true and iAliveBlocked is false
//

void OhmSender::RunAudio()
{
    while (true) {
        iMutexActive.Wait();

        iAliveJoined = false;
        iAliveBlocked = false;
        iSendTrack = false;
        iSendMetatext = false;

        iMutexActive.Signal();
        
        iThreadAudio->Wait();

        iProvider->SetStatusReady();
        
        try {
            while (true) {
                try {
                    OhmHeader header;
                    header.Internalise(iAudioReceive);
                    
                    if (header.MsgType() <= OhmHeader::kMsgTypeListen) {
                        
                        iMutexActive.Wait();
                        
                        iActive = true;
                        iAliveJoined = true;
                        
                        if (header.MsgType() <= OhmHeader::kMsgTypeJoin) {
                            iSendTrack = true;
                            iSendMetatext = true;
                        }
                        
                        iTimerAliveJoin.FireIn(kTimerAliveJoinTimeoutMs);

                        iMutexActive.Signal();
                        
                        iProvider->SetStatusSending();
                    }
                    else {
                        // LOG(kMedia, "OhmSender::RunNetwork audio received\n");

                        // The following randomisation prevents two senders from both sending,
                        // both seeing each other's audio, both backing off for the same amount of time,
                        // then both sending again, then both seeing each other's audio again,
                        // then both backing off for the same amount of time ...
                        
                        TUint delay = Random(kTimerAliveAudioTimeoutMs < 1, kTimerAliveAudioTimeoutMs);
                        iMutexActive.Wait();
                        iActive = false;
                        iAliveBlocked = true;
                        iTimerAliveAudio.FireIn(delay);
                        iMutexActive.Signal();
                        iProvider->SetStatusBlocked();
                    }
                }
                catch (OhmHeaderInvalid)
                {
                }
                
                iAudioReceive.ReadFlush();
            }
        }
        catch (ReaderError) {
            // LOG(kMedia, "OhmSender::RunNetwork reader error\n");
        }

        iAudioReceive.ReadFlush();

        iMutexActive.Wait();
        iActive = false;
        iMutexActive.Signal();
        
        iNetworkAudioDeactivated.Signal();
        
        iProvider->SetStatusInactive();
    }
}

void OhmSender::TimerAliveJoinExpired()
{
    iMutexActive.Wait();
    iActive = false;
    iAliveJoined = false;
    TBool blocked = iAliveBlocked;
    iMutexActive.Signal();
    
    if (!blocked) {
        iProvider->SetStatusReady();
    }
}

void OhmSender::TimerAliveAudioExpired()
{
    iMutexActive.Wait();
    TBool joined = iAliveBlocked;
    iActive = joined;
    iAliveBlocked = false;
    iMutexActive.Signal();

    if (joined) {
        iProvider->SetStatusSending();
    }
    else {
        iProvider->SetStatusReady();
    }
}

/*
void OhmSender::ProcessOutMsgIbAudio(MsgIbAudio* aMsg)
{
    iProvider->InformAudioPresent();
    
    iMutexActive.Wait();
    
    if (iActive) {
        if (iSendTrack) {   
            SendTrack();
        }

        if (iSendMetatext) {   
            SendMetatext();
        }
        
        TUint txTimestampPrev = 0;

        if (iFrame != 0) {
            txTimestampPrev = 123; // TODO
        }
        
        OhmHeaderAudio headerAudio(aMsg, iFrame, txTimestampPrev);
        OhmHeader header(OhmHeader::kMsgTypeAudio, headerAudio.MsgBytes());
        
        WriterBuffer writer(iAudioTransmit);
        
        writer.Flush();
        header.Externalise(writer);
        headerAudio.Externalise(writer);
        
        TByte* ptr = (TByte*)iAudioTransmit.Ptr();
        TUint max = iAudioTransmit.MaxBytes();
        TUint bytes = iAudioTransmit.Bytes();
        
        Bwn audio(ptr + bytes, max - bytes);
        
        MsgIbAudio::PackBigEndian(audio, *aMsg);
        
        iAudioTransmit.SetBytes(bytes + audio.Bytes());
        
        try {
            iSocketAudio.Write(iAudioTransmit);
            iSocketAudio.WriteFlush();
        }
        catch (WriterError&) {
            LOG(kMedia, "OhmSender::ProcessOutMsgIbAudio WriterError\n");
        }
        
        iFrame++;
    }
    
    iMutexActive.Signal();

    ProcessedOutIb(aMsg);
}
*/

void OhmSender::SetName(const Brx& aValue)
{
    iMutexStartStop.Wait();
    
	iName.Replace(aValue);
	
	UpdateMetadata();

    iMutexStartStop.Signal();
}

void OhmSender::SetChannel(TUint aValue)
{
    iMutexStartStop.Wait();
    
    if (iStarted) {
        Stop();
        iChannel = aValue;
        UpdateChannel();
        Start();
    }
    else {
        iChannel = aValue;
        UpdateChannel();
    }
    
    iMutexStartStop.Signal();
}

void OhmSender::UpdateChannel()
{
    TUint address = (iChannel & 0xffff) | 0xeffd0000; // 239.253.x.x
    iEndpoint.SetAddress(address);
    iEndpoint.SetPort(Ohm::kPort);

    iUri.Replace("mpus://");
    Ascii::AppendDec(iUri, (address >> 24 & 0xff));
    iUri.Append('.');
    Ascii::AppendDec(iUri, (address >> 16 & 0xff));
    iUri.Append('.');
    Ascii::AppendDec(iUri, (address >> 8 & 0xff));
    iUri.Append('.');
    Ascii::AppendDec(iUri, (address & 0xff));
    iUri.Append(':');
    Ascii::AppendDec(iUri, Ohm::kPort);

	UpdateMetadata();    
}

void OhmSender::UpdateMetadata()
{
    iMetadata.Replace("<DIDL-Lite xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\" xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
    iMetadata.Append("<item id=\"0\" restricted=\"True\">");
    iMetadata.Append("<dc:title>");
    iMetadata.Append(iName);
    iMetadata.Append("</dc:title>");
    iMetadata.Append("<res protocolInfo=\"mpus:*:*:*\">");
    iMetadata.Append(iUri);
    iMetadata.Append("</res>");
    iMetadata.Append("<upnp:class>object.item.audioItem</upnp:class>");
    iMetadata.Append("</item>");
    iMetadata.Append("</DIDL-Lite>");

	iProvider->SetMetadata(iMetadata);
}

void OhmSender::SetEnabled(TBool aValue)
{
    iMutexStartStop.Wait();
    
    iEnabled = aValue;
    
    if (iEnabled) {
        if (iActivated) {
            Start();
        }
    }
    else {
        Stop();
    }

    iMutexStartStop.Signal();
}

// SendTrack called with alive mutex locked;

void OhmSender::SendTrack()
{
    OhmHeaderTrack headerTrack(iTrackUri, iTrackMetadata);
    OhmHeader header(OhmHeader::kMsgTypeTrack, headerTrack.MsgBytes());
    
    WriterBuffer writer(iAudioTransmit);
    
    writer.Flush();
    header.Externalise(writer);
    headerTrack.Externalise(writer);
    writer.Write(iTrackUri);
    writer.Write(iTrackMetadata);
    
    iWriterAudio.Write(iAudioTransmit);
    iWriterAudio.WriteFlush();
    
    iSendTrack = false;
}

// SendMetatext called with alive mutex locked;

void OhmSender::SendMetatext()
{
    OhmHeaderMetatext headerMetatext(iTrackMetatext);
    OhmHeader header(OhmHeader::kMsgTypeMetatext, headerMetatext.MsgBytes());
    
    WriterBuffer writer(iAudioTransmit);
    
    writer.Flush();
    header.Externalise(writer);
    headerMetatext.Externalise(writer);
    writer.Write(iTrackMetatext);
    
    iWriterAudio.Write(iAudioTransmit);
    iWriterAudio.WriteFlush();

    iSendMetatext = false;
}
