#include "OhmSender.h"
#include "DvAvOpenhomeOrgSender1.h"
#include <Ascii.h>
#include <Maths.h>
#include <Arch.h>
#include <Debug.h>

#include <stdio.h>

namespace Zapp {

	class ProviderSender : public DvProviderAvOpenhomeOrgSender1
	{
	    static const TUint kMaxMetadataBytes = 4096;
	    static const TUint kTimeoutAudioPresentMs = 1000;
	
	public:
	    ProviderSender(DvDevice& aDevice);
	    
	    void SetMetadata(const Brx& aValue);
	    
	    void SetStatusEnabled();
	    void SetStatusDisabled();
        void SetStatusBlocked();
	    
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
    SetStatusDisabled();
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

static const Brn kStatusEnabled("Enabled");
static const Brn kStatusDisabled("Disabled");
static const Brn kStatusBlocked("Blocked");

void ProviderSender::SetStatusEnabled()
{
    SetPropertyStatus(kStatusEnabled);
}

void ProviderSender::SetStatusDisabled()
{
    SetPropertyStatus(kStatusDisabled);
}

void ProviderSender::SetStatusBlocked()
{
    SetPropertyStatus(kStatusBlocked);
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

OhmSender::OhmSender(DvDevice& aDevice, const Brx& aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled)
    : iDevice(aDevice)
    , iName(aName)
    , iChannel(aChannel)
    , iInterface(aInterface)
    , iTtl(aTtl)
    , iMulticast(aMulticast)
    , iRxBuffer(iSocket)
    , iMutexStartStop("OHMS")
    , iMutexActive("OHMA")
    , iNetworkAudioDeactivated("OHMD", 0)
    , iTimerAliveJoin(MakeFunctor(*this, &OhmSender::TimerAliveJoinExpired))
    , iTimerAliveAudio(MakeFunctor(*this, &OhmSender::TimerAliveAudioExpired))
    , iTimerExpiry(MakeFunctor(*this, &OhmSender::TimerExpiryExpired))
    , iStarted(false)
    , iActive(false)
    , iFrame(0)
    , iSampleStart(0)
    , iSamplesTotal(0)
{
    iProvider = new ProviderSender(iDevice);
    
    UpdateChannel();

    iThreadMulticast = new ThreadFunctor("MTXM", MakeFunctor(*this, &OhmSender::RunMulticast), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadMulticast->Start();
    
    iThreadUnicast = new ThreadFunctor("MTXU", MakeFunctor(*this, &OhmSender::RunUnicast), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadUnicast->Start();
    
    SetEnabled(aEnabled);
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
    
    if (iMulticast) {
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
    }
    
    iMutexStartStop.Signal();
}

void OhmSender::SetInterface(TIpAddress aValue)
{
    iMutexStartStop.Wait();
    
    if (iStarted) {
        Stop();
        iInterface = aValue;
        Start();
    }
    else {
        iInterface = aValue;
    }
    
    iMutexStartStop.Signal();
}

void OhmSender::SetTtl(TUint aValue)
{
    iMutexStartStop.Wait();
    
    if (iStarted) {
        Stop();
        iTtl = aValue;
        Start();
    }
    else {
        iTtl = aValue;
    }
    
    iMutexStartStop.Signal();
}

void OhmSender::SetMulticast(TBool aValue)
{
    iMutexStartStop.Wait();
    
    if (iStarted) {
        Stop();
        iMulticast = aValue;
        Start();
    }
    else {
        iMulticast = aValue;
    }
    
    iMutexStartStop.Signal();
}

void OhmSender::SetEnabled(TBool aValue)
{
    iMutexStartStop.Wait();
    
    iEnabled = aValue;
    
    if (iEnabled) {
        iProvider->SetStatusEnabled();
        Start();
    }
    else {
        Stop();
        iProvider->SetStatusDisabled();
    }

    iMutexStartStop.Signal();
}

// Start always called with the start/stop mutex locked

void OhmSender::Start()
{
    if (!iStarted) {
        iFrame = 0;
        if (iMulticast) {
            iSocket.OpenMulticast(iInterface, iTtl, iMulticastEndpoint);
            iTargetEndpoint.Replace(iMulticastEndpoint);
            iThreadMulticast->Signal();
        }
        else {
            iSocket.OpenUnicast(iInterface, iTtl);
            iThreadUnicast->Signal();
        }
        iStarted = true;
        UpdateMetadata();
    }
}


// Stop always called with the start/stop mutex locked

void OhmSender::Stop()
{
    if (iStarted) {
        iMutexActive.Wait();
        iActive = false;
        iMutexActive.Signal();
        iSocket.ReadInterrupt();
        iNetworkAudioDeactivated.Wait();
        iSocket.Close();
        iStarted = false;
        UpdateMetadata();
    }
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
    iMutexActive.Signal();
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
    iMutexActive.Signal();
}

void OhmSender::SetMetatext(const Brx& aValue)
{
    iMutexActive.Wait();
    iTrackMetatext.Replace(aValue);
    iMutexActive.Signal();
}
    
void OhmSender::SendAudio(const TByte* aData, TUint aBytes)
{
    iProvider->InformAudioPresent();
    
	iMutexActive.Wait();
	
	if (!iActive) {
        iMutexActive.Signal();
        return;
	}
	
    TUint samples = aBytes * 8 / iChannels / iBitDepth;
    
    OhmHeaderAudio headerAudio(false,  // halt
                               iLossless,
                               false, // sync
                               samples,
                               iFrame,
                               0, // timestamp
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

    Send();
        
    iSampleStart += samples;

    iFrame++;
    
    iMutexActive.Signal();
}

OhmSender::~OhmSender()
{
    iMutexStartStop.Wait();
    Stop();
    iMutexStartStop.Signal();

    delete iThreadMulticast;
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

void OhmSender::RunMulticast()
{
    while (true) {
        iMutexActive.Wait();
        iAliveJoined = false;
        iAliveBlocked = false;
        iMutexActive.Signal();
        
        LOG(kMedia, "OhmSender::RunMulticast wait\n");
        
        iThreadMulticast->Wait();

        LOG(kMedia, "OhmSender::RunMulticast go\n");
        
        try {
            while (true) {
                try {
                    OhmHeader header;
                    header.Internalise(iRxBuffer);
                    
                    if (header.MsgType() <= OhmHeader::kMsgTypeListen) {
                        LOG(kMedia, "OhmSender::RunMulticast join/listen received\n");
                        
                        iMutexActive.Wait();
                        
                        iActive = true;
                        iAliveJoined = true;
                        
                        if (header.MsgType() == OhmHeader::kMsgTypeJoin) {
                            SendTrack();
                            SendMetatext();
                        }
                        
                        iTimerAliveJoin.FireIn(kTimerAliveJoinTimeoutMs);

                        iMutexActive.Signal();
                    }
                    else {
                        LOG(kMedia, "OhmSender::RunMulticast audio received\n");

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
                catch (OhmError&)
                {
                }
                
                iRxBuffer.ReadFlush();
            }
        }
        catch (ReaderError&) {
            LOG(kMedia, "OPhmSender::RunMulticast reader error\n");
        }

        iRxBuffer.ReadFlush();

        iTimerAliveJoin.Cancel();
        iTimerAliveAudio.Cancel();
        
        iNetworkAudioDeactivated.Signal();

        LOG(kMedia, "OhmSender::RunMulticast stop\n");
    }
}

void OhmSender::RunUnicast()
{
    while (true) {
        iMutexActive.Wait();
        iAliveJoined = false;
        iAliveBlocked = false;
        iMutexActive.Signal();
        
        LOG(kMedia, "OhmSender::RunUnicast wait\n");
        
        iThreadUnicast->Wait();

        LOG(kMedia, "OhmSender::RunUnicast go\n");
        
        try {
            while (true) {
                // wait for first receiver to join
                // if we receive a listen, it's probably from a temporarily physically disconnected receiver
                // so accept them as well
                            
                while (true) {
                    try {
                        OhmHeader header;
                        header.Internalise(iRxBuffer);
                        
                        if (header.MsgType() <= OhmHeader::kMsgTypeListen) {
                            LOG(kMedia, "OhmSender::RunUnicast ready/join or listen\n");
                            break;                        
                        }
                    }
                    catch (OhmError&)
                    {
                    }
                    
                    iRxBuffer.ReadFlush();  
                }
    
                iRxBuffer.ReadFlush();

                iTargetEndpoint.Replace(iSocket.Sender());

                SendTrack();
                SendMetatext();
            
                iFrame = 0;
                iSlaveCount = 0;
                
                iMutexActive.Wait();
                iActive = true;
                iAliveJoined = true;
                iMutexActive.Signal();
                
                iTimerExpiry.FireIn(kTimerExpiryTimeoutMs);
                
                while (true) {
                    try {
                        OhmHeader header;
                        header.Internalise(iRxBuffer);
                        
                        if (header.MsgType() == OhmHeader::kMsgTypeJoin) {
                            LOG(kMedia, "OhmSender::RunUnicast sending/join\n");
                            
                            Endpoint sender(iSocket.Sender());

                            if (sender.Equals(iTargetEndpoint)) {
                                iTimerExpiry.FireIn(kTimerExpiryTimeoutMs);
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave >= iSlaveCount) {
                                    if (slave < kMaxSlaveCount) {
                                        iSlaveList[slave].Replace(sender);
                                        iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                        iSlaveCount++;
                                        iMutexActive.Wait();
                                        SendListen(sender);
                                        iMutexActive.Signal();
                                    }
                                }
                                else {
                                    iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                }
                            }
                            iMutexActive.Wait();
                            SendSlaveList();
                            SendTrack();
                            SendMetatext();
                            iMutexActive.Signal();
                        }
                        else if (header.MsgType() == OhmHeader::kMsgTypeListen) {
                            LOG(kMedia, "OhmSender::RunUnicast sending/listen\n");
                            
                            Endpoint sender(iSocket.Sender());

                            if (sender.Equals(iTargetEndpoint)) {
                                iTimerExpiry.FireIn(kTimerExpiryTimeoutMs);
                                if (CheckSlaveExpiry()) {
                                    iMutexActive.Wait();
                                    SendSlaveList();
                                    iMutexActive.Signal();
                                }
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave < iSlaveCount) {
                                    iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                }
                                else {
                                    // unknown slave, probably temporarily physically disconnected receiver
                                    if (slave < kMaxSlaveCount) {
                                        iSlaveList[slave].Replace(sender);
                                        iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                        iSlaveCount++;
                                        iMutexActive.Wait();
                                        SendListen(sender);
                                        SendSlaveList();
                                        SendTrack();
                                        SendMetatext();
                                        iMutexActive.Signal();
                                    }
                                }
                            }
                        }
                        else if (header.MsgType() == OhmHeader::kMsgTypeLeave) {
                            LOG(kMedia, "OhmSender::RunUnicast sending/leave\n");
                            
                            Endpoint sender(iSocket.Sender());

                            if (sender.Equals(iTargetEndpoint) || sender.Equals(iSocket.This())) {
                                if (iSlaveCount == 0) {
                                    if (sender.Equals(iTargetEndpoint)) {
                                        iMutexActive.Wait();
                                        SendLeave(sender);
                                        iMutexActive.Signal();
                                    }
                                    break;
                                }
                                else {
                                    iMutexActive.Wait();
                                    SendLeave(sender);
                                    iTargetEndpoint.Replace(iSlaveList[--iSlaveCount]);
                                    iTimerExpiry.FireAt(iSlaveExpiry[iSlaveCount]);
                                    if (iSlaveCount > 0) {
                                        SendSlaveList();
                                    }
                                    iMutexActive.Signal();
                                }
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave < iSlaveCount) {
                                    RemoveSlave(slave);
                                    iMutexActive.Wait();
                                    SendLeave(sender);
                                    SendSlaveList();
                                    iMutexActive.Signal();
                                }
                            }
                        }
                    }
                    catch (OhmError&)
                    {
                    }
                    
                    iRxBuffer.ReadFlush();
                }

                iRxBuffer.ReadFlush();

                iMutexActive.Wait();
                iActive = false;
                iAliveJoined = false;               
                iMutexActive.Signal();
            }
        }
        catch (ReaderError&) {
            LOG(kMedia, "OhmSender::RunUnicast reader error\n");
        }

        iRxBuffer.ReadFlush();

        iTimerExpiry.Cancel();

        iNetworkAudioDeactivated.Signal();
        
        LOG(kMedia, "OhmSender::RunUnicast stop\n");
    }
}

void OhmSender::TimerAliveJoinExpired()
{
    iMutexActive.Wait();
    iActive = false;
    iAliveJoined = false;
    iMutexActive.Signal();
}

void OhmSender::TimerAliveAudioExpired()
{
    iMutexActive.Wait();
    TBool joined = iAliveBlocked;
    iActive = joined;
    iAliveBlocked = false;
    iMutexActive.Signal();
    iProvider->SetStatusEnabled();
}

void OhmSender::TimerExpiryExpired()
{
    // Send a Leave to ourselves, which is interpreted as a Leave from the receiver

    LOG(kMedia, "OhmSender::TimerExpiryExpired TIMEOUT\n");

    Bws<OhmHeader::kHeaderBytes> buffer;
    WriterBuffer writer(buffer);

    OhmHeader leave(OhmHeader::kMsgTypeLeave, 0);
    
    leave.Externalise(writer);

    iMutexActive.Wait();

    try {
        iSocket.Send(buffer, iSocket.This());
    }
    catch (NetworkError&) {
        ASSERTS();
    }

    iMutexActive.Signal();
}

void OhmSender::UpdateChannel()
{
    TUint address = (iChannel & 0xffff) | 0xeffd0000; // 239.253.x.x
    
    iMulticastEndpoint.SetAddress(Arch::BigEndian4(address));
    iMulticastEndpoint.SetPort(Ohm::kPort);
}

void OhmSender::UpdateMetadata()
{
    if (!iStarted) {
        iMetadata.Replace(Brx::Empty());
    }
    else {
        iMetadata.Replace("<DIDL-Lite xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\" xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
        iMetadata.Append("<item id=\"0\" restricted=\"True\">");
        iMetadata.Append("<dc:title>");
        iMetadata.Append(iName);
        iMetadata.Append("</dc:title>");
        if (iMulticast) {
            TUint address = Arch::BigEndian4(iMulticastEndpoint.Address());
            iMetadata.Append("<res protocolInfo=\"ohm:*:*:*\">");
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
        }
        else {
            TUint address = Arch::BigEndian4(iSocket.This().Address());
            iMetadata.Append("<res protocolInfo=\"ohu:*:*:*\">");
            iUri.Replace("ohu://");
            Ascii::AppendDec(iUri, (address >> 24 & 0xff));
            iUri.Append('.');
            Ascii::AppendDec(iUri, (address >> 16 & 0xff));
            iUri.Append('.');
            Ascii::AppendDec(iUri, (address >> 8 & 0xff));
            iUri.Append('.');
            Ascii::AppendDec(iUri, (address & 0xff));
            iUri.Append(':');
            Ascii::AppendDec(iUri, iSocket.This().Port());
        }
        iMetadata.Append(iUri);
        iMetadata.Append("</res>");
        iMetadata.Append("<upnp:class>object.item.audioItem</upnp:class>");
        iMetadata.Append("</item>");
        iMetadata.Append("</DIDL-Lite>");
    }

	iProvider->SetMetadata(iMetadata);
}

void OhmSender::Send()
{
    try {
        iSocket.Send(iTxBuffer, iTargetEndpoint);
    }
    catch (NetworkError&) {
        ASSERTS();
    }
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

    Send();    
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
    
    Send();    
}

// SendSlaveList called with alive mutex locked;

void OhmSender::SendSlaveList()
{
    OhmHeaderSlave headerSlave(iSlaveCount);
    OhmHeader header(OhmHeader::kMsgTypeSlave, headerSlave.MsgBytes());
    
    WriterBuffer writer(iTxBuffer);
    
    writer.Flush();
    header.Externalise(writer);
    headerSlave.Externalise(writer);
    
    WriterBinary binary(writer);
    
    for (TUint i = 0; i < iSlaveCount; i++) {
        binary.WriteUint32Be(Arch::BigEndian4(iSlaveList[i].Address()));
        binary.WriteUint16Be(iSlaveList[i].Port());
    }
    
    Send();    
}


// SendListen called with alive mutex locked;

// Listen message is ignored by slaves, but this is sent to populate my arp tables
// in case the slave needs to be quickly changed to master receiver.

void OhmSender::SendListen(const Endpoint& aEndpoint)
{
    OhmHeader header(OhmHeader::kMsgTypeListen, 0);

    WriterBuffer writer(iTxBuffer);

    writer.Flush();
    header.Externalise(writer);

    Send();    
}

// Leave message is sent to acknowledge a Leave sent from a receiver or slave

void OhmSender::SendLeave(const Endpoint& aEndpoint)
{
    OhmHeader header(OhmHeader::kMsgTypeLeave, 0);

    WriterBuffer writer(iTxBuffer);

    writer.Flush();
    header.Externalise(writer);

    Send();    
}

TBool OhmSender::CheckSlaveExpiry()
{
    TBool changed = false;

    for (TUint i = 0; i < iSlaveCount;) {
        if (Time::IsInPastOrNow(iSlaveExpiry[i])) {
            RemoveSlave(i);
            changed = true;
            continue;
        }
        i++;
    }
    
    return (changed);
}

void OhmSender::RemoveSlave(TUint aIndex)
{
    iSlaveCount--;
    for (TUint i = aIndex; i < iSlaveCount; i++) {
        iSlaveList[i].Replace(iSlaveList[i + 1]);
        iSlaveExpiry[i] = iSlaveExpiry[i + 1];
    }
}

// Returns index of supplied endpoint, or index of empty slot if not found
// distinguish between the two by comparing returned value with iSlaveCount
  
TUint OhmSender::FindSlave(const Endpoint& aEndpoint)
{
    for (TUint i = 0; i < iSlaveCount; i++) {
        if (aEndpoint.Equals(iSlaveList[i])) {
            return (i);
        }
    }
    
    return (iSlaveCount);
}

