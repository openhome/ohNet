#include "OhmSender.h"

#include <Maths.h>

using namespace Zapp;

// ProviderSender

ProviderSender::ProviderSender(DvDevice& aDevice, IProviderSenderHandler& aHandler, TUint aChannel, TBool aEnabled)
    : DvServiceLinnCoUkMultipusSender1(aDevice)
    , iHandler(aHandler)
    , iMutex("PSND")
    , iTimerAudioPresent(MakeFunctor(*this, &ProviderSender::TimerAudioPresentExpired))
{
    EnableActionEnabled();
    EnableActionSetEnabled();
    EnableActionChannel();
    EnableActionSetChannel();
    EnableActionMetadata();
    EnableActionAudio();
    EnableActionStatus();
    EnableActionInfoAvailable();
    EnableActionTimeAvailable();
    SetPropertyChannel(aChannel);
    SetPropertyEnabled(aEnabled);
}

void ProviderSender::Channel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aValue)
{
    TUint value;
    GetPropertyChannel(value);
    aResponse.Start();
    aValue.Write(value);
    aResponse.End();
}

void ProviderSender::SetChannel(IInvocationResponse& aResponse, TUint aVersion, TUint aValue)
{
    TBool changed = true;
    SetPropertyChannel(aValue);
    if (changed) {
        iHandler.StoreChannel(aValue);
    }
    aResponse.Start();
    aResponse.End();    
}

void ProviderSender::Enabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue)
{
    TBool value;
    GetPropertyEnabled(value);
    aResponse.Start();
    aValue.Write(value);
    aResponse.End();
}

void ProviderSender::SetEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aValue)
{
    TBool changed = true;
    SetPropertyEnabled(aValue);
    if (changed) {
        iHandler.StoreEnabled(aValue);
    }
    aResponse.Start();
    aResponse.End();    
}

void ProviderSender::Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue)
{
    aResponse.Start();
    aValue.Write(Brn("Metadata"));
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
    Brhz status;
    GetPropertyStatus(status);
    aResponse.Start();
    aValue.Write(status);
    aValue.WriteFlush();
    aResponse.End();
}

void ProviderSender::InfoAvailable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue)
{
    aResponse.Start();
    aValue.Write(false);
    aResponse.End();
}

void ProviderSender::TimeAvailable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue)
{
    aResponse.Start();
    aValue.Write(false);
    aResponse.End();
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

OhmSender::OhmSender(DvDevice& aDevice)
    : iDevice(aDevice)
    , iSocketAudio(kTtl, 0)
    , iReaderAudio(iSocketAudio)
    , iWriterAudio(iSocketAudio)
    , iAudioReceive(iReaderAudio)
    , iMutexStartStop("MPSS")
    , iMutexActive("MPAC")
    , iNetworkAudioDeactivated("MPUS", 0)
    , iTimerAliveJoin(MakeFunctor(*this, &OhmSender::TimerAliveJoinExpired))
    , iTimerAliveAudio(MakeFunctor(*this, &OhmSender::TimerAliveAudioExpired))
    , iActivated(false)
    , iStarted(false)
    , iActive(false)
{
    iProvider = new ProviderSender(iDevice, *this, 0, true);
    
    UpdateEndpoint();

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

void OhmSender::StoreEnabled(TBool aValue)
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

void OhmSender::StoreChannel(TUint aValue)
{
    iMutexStartStop.Wait();
    
    if (iStarted) {
        Stop();
        iChannel = aValue;
        Start();
    }
    else {
        iChannel = aValue;
    }
    
    iMutexStartStop.Signal();
}

/*
void OhmSender::UpdateEndpoint(TUint aChannel)
{
    iProvider->Channel(iEndpoint);
    Bws<kMaxEndpointAddressAndPortStringBytes> endpoint;
    EndpointAddressAndPort(iEndpoint, endpoint);
    Bws<kMaxEndpointAddressAndPortStringBytes + 7> uri;
    uri.Replace("mpus://");
    uri.Append(endpoint);
    iMpusUri.Replace(uri);
}
*/

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
