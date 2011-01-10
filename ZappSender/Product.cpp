#include "OhmSender.h"
#include "DvAvOpenhomeOrgSender1.h"
#include <Ascii.h>
#include <Maths.h>
#include <Arch.h>

#include <stdio.h>

namespace Zapp {

	class ProviderSender : public DvProviderAvOpenhomeOrgSender1
	{
	    static const TUint kMaxMetadataBytes = 4096;
	    static const TUint kTimeoutAudioPresentMs = 1000;
	
	public:
	    ProviderSender(DvDevice& aDevice);
	    
	    void SetMetadata(const Brx& aValue);
	    
	    void SetStatusReady();
	    void SetStatusSending();
	    void SetStatusBlocked();
	    void SetStatusInactive();
	    void SetStatusDisabled();
	    
	    void InformAudioPresent();
	    
	    ~ProviderSender() {}
	    
	private:
	    virtual void PresentationUrl(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
	    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
	    virtual void Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
	    virtual void Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
	    virtual void Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
	
	    void UpdateMetadata();
	    void TimerAudioPresentExpired();
	
	private:
	    Bws<kMaxMetadataBytes> iMetadata;
	    mutable Mutex iMutex;
	    Timer iTimerAudioPresent;
	};

}

using namespace Zapp;

// ProviderSender

ProviderSender::ProviderSender(DvDevice& aDevice)
    : DvProviderAvOpenhomeOrgSender1(aDevice)
    , iMutex("PSND")
    , iTimerAudioPresent(MakeFunctor(*this, &ProviderSender::TimerAudioPresentExpired))
{
    EnableActionPresentationUrl();
    EnableActionMetadata();
    EnableActionAudio();
    EnableActionStatus();
    EnableActionAttributes();
    
    SetPropertyPresentationUrl(Brx::Empty());
    SetPropertyMetadata(Brx::Empty());
    SetPropertyAudio(false);
    SetStatusInactive();
    SetPropertyAttributes(Brx::Empty());
}

void ProviderSender::PresentationUrl(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue)
{
	Brhz value;
    GetPropertyPresentationUrl(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
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
static const Brn kStatusDisabled("Disabled");

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

void ProviderSender::SetStatusDisabled()
{
    SetPropertyStatus(kStatusDisabled);
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

OhmSender::OhmSender(DvDevice& aDevice, TIpAddress aInterface, const Brx& aName, TUint aChannel)
    : iDevice(aDevice)
    , iName(aName)
    , iChannel(aChannel)
    , iEnabled(false)
    , iSocket(kTtl, aInterface)
    , iRxBuffer(iSocket)
    , iMutexStartStop("OHMS")
    , iMutexActive("OHMA")
    , iNetworkAudioDeactivated("OHMD", 0)
    , iTimerAliveJoin(MakeFunctor(*this, &OhmSender::TimerAliveJoinExpired))
    , iTimerAliveAudio(MakeFunctor(*this, &OhmSender::TimerAliveAudioExpired))
    , iStarted(false)
    , iActive(false)
    , iFrame(0)
    , iSendTrack(false)
    , iSendMetatext(false)
    , iSampleStart(0)
    , iSamplesTotal(0)
    , iTimestamp(0)
{
    iProvider = new ProviderSender(iDevice);
    
    UpdateChannel();

    iThreadNetwork = new ThreadFunctor("MPAU", MakeFunctor(*this, &OhmSender::RunNetwork), kThreadPriorityAudio, kThreadStackBytesAudio);
    iThreadNetwork->Start();
}

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

void OhmSender::SetAudioFormat(TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth, TBool aLossless, const Brx& aCodecName)
{
    iMutexActive.Wait();
    iSampleRate = aSampleRate;
    iBitRate = aBitRate;
    iChannels = aChannels;
    iBitDepth = aBitDepth;
    iLossless = aLossless;
    iCodecName.Replace(aCodecName);
    CalculateMclocksPerSample();
    iMutexActive.Signal();
}

void OhmSender::CalculateMclocksPerSample()
{
    iMclocksPerSample = 256 * 44100 / iSampleRate;
}

void OhmSender::StartTrack(TUint64 aSampleStart)
{
    StartTrack(aSampleStart, 0);
}

void OhmSender::StartTrack(TUint64 aSampleStart, TUint64 aSamplesTotal)
{
    StartTrack(aSampleStart, aSamplesTotal, Brx::Empty(), Brx::Empty());
}

void OhmSender::StartTrack(TUint64 aSampleStart, TUint64 aSamplesTotal, const Brx& aUri, const Brx& aMetadata)
{
    iMutexActive.Wait();
    iSampleStart = aSampleStart;
    iSamplesTotal = aSamplesTotal;
    iTrackUri.Replace(aUri);
    iTrackMetadata.Replace(aMetadata);
    iTrackMetatext.Replace(Brx::Empty());
    iSendTrack = true;
    iSendMetatext = true;
    iMutexActive.Signal();
}

void OhmSender::SetMetatext(const Brx& aValue)
{
    iMutexActive.Wait();
    iTrackMetatext.Replace(aValue);
    iSendMetatext = true;
    iMutexActive.Signal();
}
    
void OhmSender::SendAudio(const TByte* aData, TUint aBytes)
{
    iProvider->InformAudioPresent();
    
	iMutexActive.Wait();
	
	/*
	if (!iActive) {
        iMutexActive.Signal();
        return;
	}
	*/
	
    if (iSendTrack) {   
        SendTrack();
    }

    if (iSendMetatext) {   
        SendMetatext();
    }
    
    TUint samples = aBytes * 8 / iChannels / iBitDepth;
    
    OhmHeaderAudio headerAudio(false,  // halt
                               iLossless,
                               false, // sync
                               samples,
                               iFrame,
                               iTimestamp,
                               0, // sync timestamp
                               iSampleStart,
                               iSamplesTotal,
                               iSampleRate,
                               iBitRate,
                               0, // volume offset
                               iBitDepth,
                               iChannels,
                               iCodecName);
    
    OhmHeader header(OhmHeader::kMsgTypeAudio, headerAudio.MsgBytes());

    WriterBuffer writer(iTxBuffer);
    
    writer.Flush();
    header.Externalise(writer);
    headerAudio.Externalise(writer);
    
    writer.Write(Brn(aData, aBytes));
    
    try {
        iSocket.Write(iTxBuffer);
        iSocket.WriteFlush();
    }
    catch (WriterError&) {
	  	printf("Writer Error\n");
    }
    
    iSampleStart += samples;
    iTimestamp += samples * iMclocksPerSample;

    iFrame++;
    
    iMutexActive.Signal();
}

OhmSender::~OhmSender()
{
    iMutexStartStop.Wait();
    Stop();
    iMutexStartStop.Signal();

    delete iThreadNetwork;
}

// Start always called with the start/stop mutex locked

void OhmSender::Start()
{
    if (!iStarted) {
        iFrame = 0;
        try {
	        iSocket.AddMembership(iEndpoint);
	    }
	    catch (NetworkError&) {
	    	printf("Start network error %x:%d\n", iEndpoint.Address(), iEndpoint.Port());
	    	throw;
	    }
        iThreadNetwork->Signal();
        iStarted = true;
    }
}

// Stop always called with the start/stop mutex locked

void OhmSender::Stop()
{
    if (iStarted) {
        iSocket.ReadInterrupt();
        iNetworkAudioDeactivated.Wait();
        iSocket.DropMembership();
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

void OhmSender::RunNetwork()
{
    while (true) {
        iMutexActive.Wait();

        iAliveJoined = false;
        iAliveBlocked = false;
        iSendTrack = false;
        iSendMetatext = false;

        iMutexActive.Signal();
        
        iThreadNetwork->Wait();

        iProvider->SetStatusReady();
        
        try {
            while (true) {
                try {
                    printf("waiting for message\n");

                    OhmHeader header;
                    header.Internalise(iRxBuffer);
                    
                    printf("message received\n");
                    
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
                        
                        TUint delay = Random(kTimerAliveAudioTimeoutMs, kTimerAliveAudioTimeoutMs >> 1);
                        iMutexActive.Wait();
                        iActive = false;
                        iAliveBlocked = true;
                        iTimerAliveAudio.FireIn(delay);
                        iMutexActive.Signal();
                        iProvider->SetStatusBlocked();
                    }
                }
                catch (OhmError)
                {
                }
                
                iRxBuffer.ReadFlush();
            }
        }
        catch (ReaderError) {
            // LOG(kMedia, "OhmSender::RunNetwork reader error\n");
        }

        iRxBuffer.ReadFlush();

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
        
        WriterBuffer writer(iTxBuffer);
        
        writer.Flush();
        header.Externalise(writer);
        headerAudio.Externalise(writer);
        
        TByte* ptr = (TByte*)iTxBuffer.Ptr();
        TUint max = iTxBuffer.MaxBytes();
        TUint bytes = iTxBuffer.Bytes();
        
        Bwn audio(ptr + bytes, max - bytes);
        
        MsgIbAudio::PackBigEndian(audio, *aMsg);
        
        iTxBuffer.SetBytes(bytes + audio.Bytes());
        
        try {
            iSocket.Write(iTxBuffer);
            iSocket.WriteFlush();
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

void OhmSender::UpdateChannel()
{
    TUint address = (iChannel & 0xffff) | 0xeffd0000; // 239.253.x.x
    
    iEndpoint.SetAddress(Arch::BigEndian4(address));
    iEndpoint.SetPort(Ohm::kPort);

    iUri.Replace("ohm://");
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
    iMetadata.Append("<res protocolInfo=\"ohm:*:*:*\">");
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
        Start();
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
    
    WriterBuffer writer(iTxBuffer);
    
    writer.Flush();
    header.Externalise(writer);
    headerTrack.Externalise(writer);
    writer.Write(iTrackUri);
    writer.Write(iTrackMetadata);
    
    iSocket.Write(iTxBuffer);
    iSocket.WriteFlush();
    
    iSendTrack = false;
}

// SendMetatext called with alive mutex locked;

void OhmSender::SendMetatext()
{
    OhmHeaderMetatext headerMetatext(iTrackMetatext);
    OhmHeader header(OhmHeader::kMsgTypeMetatext, headerMetatext.MsgBytes());
    
    WriterBuffer writer(iTxBuffer);
    
    writer.Flush();
    header.Externalise(writer);
    headerMetatext.Externalise(writer);
    writer.Write(iTrackMetatext);
    
    iSocket.Write(iTxBuffer);
    iSocket.WriteFlush();

    iSendMetatext = false;
}
