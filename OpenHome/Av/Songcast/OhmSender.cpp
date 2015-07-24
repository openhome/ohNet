#include "OhmSender.h"
#include <Generated/DvAvOpenhomeOrgSender1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Av/Debug.h>
#include <OpenHome/Av/Songcast/ZoneHandler.h>
#include <OpenHome/Av/Songcast/OhmTimestamp.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <stdio.h>

namespace OpenHome {
class Environment;
namespace Av {

class ProviderSender : public Net::DvProviderAvOpenhomeOrgSender1
{
    static const TUint kMaxMetadataBytes = 4096;
    static const TUint kTimeoutAudioPresentMs = 1000;
    static const Brn kStatusEnabled;
    static const Brn kStatusDisabled;
    static const Brn kStatusBlocked;
public:
    ProviderSender(Net::DvDevice& aDevice);
    void SetMetadata(const Brx& aValue);
    void SetStatusEnabled();
    void SetStatusDisabled();
    void SetStatusBlocked();
    void NotifyAudioPlaying(TBool aPlaying);
private: // from Net::DvProviderAvOpenhomeOrgSender1
    void PresentationUrl(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
    void Metadata(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
    void Audio(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue) override;
    void Status(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
    void Attributes(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue) override;
private:
    void UpdateMetadata();
private:
    mutable Mutex iLock;
    Bws<kMaxMetadataBytes> iMetadata;
    Timer* iTimerAudioPresent;
    Brn iStatus;
};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

// ProviderSender

const Brn ProviderSender::kStatusEnabled("Enabled");
const Brn ProviderSender::kStatusDisabled("Disabled");
const Brn ProviderSender::kStatusBlocked("Blocked");

ProviderSender::ProviderSender(Net::DvDevice& aDevice)
    : DvProviderAvOpenhomeOrgSender1(aDevice)
    , iLock("PSND")
{
    EnablePropertyPresentationUrl();
    EnablePropertyMetadata();
    EnablePropertyAudio();
    EnablePropertyStatus();
    EnablePropertyAttributes();

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

void ProviderSender::PresentationUrl(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue)
{
    Brhz value;
    GetPropertyPresentationUrl(value);
    aInvocation.StartResponse();
    aValue.Write(value);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderSender::Metadata(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue)
{
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        aValue.Write(iMetadata);
    }
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderSender::Audio(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue)
{
    TBool value;
    GetPropertyAudio(value);
    aInvocation.StartResponse();
    aValue.Write(value);
    aInvocation.EndResponse();
}

void ProviderSender::Status(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue)
{
    aInvocation.StartResponse();
    {
        AutoMutex a(iLock);
        aValue.Write(iStatus);
    }
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderSender::Attributes(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue)
{
    // FIXME - can we just copy from Product's attributes?
    Brhz value;
    GetPropertyAttributes(value);
    aInvocation.StartResponse();
    aValue.Write(value);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderSender::SetMetadata(const Brx& aValue)
{
    iLock.Wait();
    iMetadata.Replace(aValue);
    iLock.Signal();
    SetPropertyMetadata(aValue);
}

void ProviderSender::SetStatusEnabled()
{
    AutoMutex a(iLock);
    iStatus.Set(kStatusEnabled);
    SetPropertyStatus(iStatus);
}

void ProviderSender::SetStatusDisabled()
{
    AutoMutex a(iLock);
    iStatus.Set(kStatusDisabled);
    SetPropertyStatus(iStatus);
}

void ProviderSender::SetStatusBlocked()
{
    AutoMutex a(iLock);
    iStatus.Set(kStatusBlocked);
    SetPropertyStatus(iStatus);
}

void ProviderSender::NotifyAudioPlaying(TBool aPlaying)
{
    SetPropertyAudio(aPlaying);
}


// OhmSenderDriver

OhmSenderDriver::OhmSenderDriver(Environment& aEnv, IOhmTimestamper* aTimestamper, IOhmTimestampMapper* aTsMapper)
    : iMutex("OHMD")
    , iEnabled(false)
    , iActive(false)
    , iSend(false)
    , iFrame(0)
    , iSampleRate(0)
    , iBitRate(0)
    , iChannels(0)
    , iBitDepth(0)
    , iLossless(false)
    , iSamplesTotal(0)
    , iSampleStart(0)
    , iLatency(100)
    , iSocket(aEnv)
    , iFactory(100, 10, 10, 10) // FIXME - rationale for msg counts??
    , iTimestamper(aTimestamper)
    , iFirstFrame(true)
    , iTsMapper(aTsMapper)
{
}

void OhmSenderDriver::SetAudioFormat(TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth, TBool aLossless, const Brx& aCodecName)
{
    AutoMutex mutex(iMutex);

    iSampleRate = aSampleRate;
    iBitRate = aBitRate;
    iChannels = aChannels;
    iBitDepth = aBitDepth;
    iLossless = aLossless;
    iCodecName.Replace(aCodecName);
}

void OhmSenderDriver::SendAudio(const TByte* aData, TUint aBytes, TBool aHalt)
{
    AutoMutex mutex(iMutex);

    TUint samples;
    if (iChannels == 0 || iBitDepth == 0) {
        samples = 0;
    }
    else {
        samples = aBytes * 8 / iChannels / iBitDepth;
    }
    if (!iSend) {
        iSampleStart += samples;
        return;
    }
    if (iSampleRate == 0 || (samples == 0 && !aHalt)) {
        // nothing to usefully communicate to receivers
        return;
    }
    TUint multiplier = 48000 * 256;
    if ((iSampleRate % 441) == 0) {
        multiplier = 44100 * 256;
    }
    const TUint latency = iLatency * multiplier / 1000;
    if (iFifoHistory.SlotsUsed() == kMaxHistoryFrames) {
        iFifoHistory.Read()->RemoveRef();
    }

    TBool isTimeStamped = false;
    TUint timeStamp = 0;
    if (iFirstFrame) {
        iFirstFrame = false;
    }
    else if (iTimestamper != nullptr) {
        try {
            timeStamp = iTimestamper->Timestamp(iFrame - 1);
            if (iTsMapper != nullptr) {
                timeStamp = iTsMapper->ToOhmTimestamp(timeStamp, iSampleRate);
            }
            isTimeStamped = true;
        }
        catch (OhmTimestampNotFound&) {}
    }

    OhmMsgAudio* msg = iFactory.CreateAudio(
        aHalt,
        iLossless,
        isTimeStamped,
        false,
        samples,
        iFrame,
        timeStamp, // network timestamp
        latency,
        0,
        iSampleStart,
        iSamplesTotal,
        iSampleRate,
        iBitRate,
        0, // volume offset
        iBitDepth,
        iChannels,
        iCodecName,
        Brn(aData, aBytes)
    );

    WriterBuffer writer(iBuffer);
    writer.Flush();
    msg->Externalise(writer);
    msg->SetResent(true);
    iFifoHistory.Write(msg);
    try {
        iSocket.Send(iBuffer, iEndpoint);
    }
    catch (NetworkError&) {
    }

    iSampleStart += samples;
    iFrame++;
}

void OhmSenderDriver::SetEnabled(TBool aValue)
{
    AutoMutex mutex(iMutex);

    iEnabled = aValue;
    if (iSend) {
        if (!aValue) { // turning off
            ResetLocked();
        }
    }
    else {
        if (aValue && iActive) { // turning on
            iSend = true;
        }
    }
}

void OhmSenderDriver::SetActive(TBool aValue)
{
    AutoMutex mutex(iMutex);

    iActive = aValue;
    if (iSend) {
        if (!aValue) { // turning off
            ResetLocked();
        }
    }
    else {
        if (aValue && iEnabled) { // turning on
            iSend = true;
            if (iTimestamper != nullptr) {
                iTimestamper->Start(iEndpoint);
            }
        }
    }
}

void OhmSenderDriver::SetEndpoint(const Endpoint& aEndpoint, TIpAddress aAdapter)
{
    AutoMutex mutex(iMutex);
    if ((iTimestamper != nullptr) && iActive && !iEndpoint.Equals(aEndpoint)) {
        iTimestamper->Stop();
        iTimestamper->Start(aEndpoint);
    }
    iEndpoint.Replace(aEndpoint);
    iAdapter = aAdapter;
}

void OhmSenderDriver::SetTtl(TUint aValue)
{
    AutoMutex mutex(iMutex);
    iSocket.SetTtl(aValue);
}

void OhmSenderDriver::SetLatency(TUint aValue)
{
    AutoMutex mutex(iMutex);
    iLatency = aValue;
}

void OhmSenderDriver::SetTrackPosition(TUint64 aSamplesTotal, TUint64 aSampleStart)
{
    AutoMutex mutex(iMutex);
    iSamplesTotal = aSamplesTotal;
    iSampleStart = aSampleStart;
}

void OhmSenderDriver::Resend(OhmMsgAudio& aMsg)
{
    WriterBuffer writer(iBuffer);
    writer.Flush();
    aMsg.Externalise(writer);
    try {
        iSocket.Send(iBuffer, iEndpoint);
    }
    catch (NetworkError&) {
    }
}

void OhmSenderDriver::Resend(const Brx& aFrames)
{
    AutoMutex mutex(iMutex);
    LOG(kSongcast, "RESEND");

    ReaderBuffer buffer(aFrames);
    ReaderBinary reader(buffer);
    TUint frames = aFrames.Bytes() / 4;
    TUint frame = reader.ReadUintBe(4);
    frames--;
    LOG(kSongcast, " %lu", (unsigned long)frame);
    TBool found = false;
    TUint count = iFifoHistory.SlotsUsed();
    for (TUint i = 0; i < count; i++) {
        OhmMsgAudio* msg = iFifoHistory.Read();
        if (!found) {
            TInt diff = frame - msg->Frame();
            if (diff == 0) {
                Resend(*msg);
                if (frames-- > 0) {
                    frame = reader.ReadUintBe(4);
                }
                else {
                    found = true;
                }
            }
            else {
                while (diff < 0) {
                    if (frames-- > 0) {
                        frame = reader.ReadUintBe(4);
                    }
                    else {
                        found = true;
                        break;
                    }
                    diff = frame - msg->Frame();
                    if (diff == 0) {
                        Resend(*msg);
                        if (frames-- > 0) {
                            frame = reader.ReadUintBe(4);
                        }
                        else {
                            found = true;
                        }
                        break;
                    }
                }
            }
        }

        iFifoHistory.Write(msg);
    }
    LOG(kSongcast, "\n");
}

void OhmSenderDriver::ResetLocked()
{
    iSend = false;
    iFrame = 0;
    iFirstFrame = true;
    if (iTimestamper != nullptr) {
        iTimestamper->Stop();
    }
    const TUint count = iFifoHistory.SlotsUsed();
    for (TUint i = 0; i < count; i++) {
        iFifoHistory.Read()->RemoveRef();
    }
}


// OhmSender

OhmSender::OhmSender(Environment& aEnv, Net::DvDeviceStandard& aDevice, IOhmSenderDriver& aDriver, ZoneHandler& aZoneHandler, const Brx& aName, TUint aChannel, TUint aLatency, TBool aMulticast, const Brx& aImageFileName)
    : iEnv(aEnv)
    , iDevice(aDevice)
    , iDriver(aDriver)
    , iZoneHandler(&aZoneHandler)
    , iName(aName)
    , iChannel(aChannel)
    , iInterface(0)
    , iLatency(aLatency)
    , iMulticast(aMulticast)
    , iEnabled(false)
    , iImageFileName(aImageFileName)
    , iSocketOhm(aEnv)
    , iRxBuffer(iSocketOhm)
    , iMutexStartStop("OHMS")
    , iMutexActive("OHMA")
    , iNetworkDeactivated("OHDN", 0)
    , iZoneDeactivated("OHDZ", 0)
    , iStarted(false)
    , iActive(false)
    , iAliveJoined(false)
    , iAliveBlocked(false)
    , iSequenceTrack(0)
    , iSequenceMetatext(0)
    , iClientControllingTrackMetadata(false)
{
    iProvider = new ProviderSender(iDevice);
    CurrentSubnetChanged(); // roundabout way of initialising iInterface
 
    iDriver.SetTtl(kTtl);
    iDriver.SetLatency(iLatency);
    LOG(kSongcast, "OHM SENDER DRIVER LATENCY %d\n", iLatency);
       
    iTimerAliveJoin = new Timer(aEnv, MakeFunctor(*this, &OhmSender::TimerAliveJoinExpired), "OhmSenderAliveJoin");
    iTimerAliveAudio = new Timer(aEnv, MakeFunctor(*this, &OhmSender::TimerAliveAudioExpired), "OhmSenderAliveAudio");
    iTimerExpiry = new Timer(aEnv, MakeFunctor(*this, &OhmSender::TimerExpiryExpired), "OhmSenderExpiry");

    iThreadMulticast = new ThreadFunctor("OhmSenderM", MakeFunctor(*this, &OhmSender::RunMulticast), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadMulticast->Start();
    
    iThreadUnicast = new ThreadFunctor("OhmSenderU", MakeFunctor(*this, &OhmSender::RunUnicast), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadUnicast->Start();
    
    UpdateChannel();
    iNacnId = iEnv.NetworkAdapterList().AddCurrentChangeListener(MakeFunctor(*this, &OhmSender::CurrentSubnetChanged), false);
    UpdateMetadata();
}

OhmSender::~OhmSender()
{
    LOG(kSongcast, "OhmSender::~OhmSender\n");
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iNacnId);
    iEnabled = false;
    iDriver.SetEnabled(false);
    LOG(kSongcast, "OhmSender::~OhmSender disabled driver\n");

    {
        AutoMutex mutex(iMutexStartStop);
        Stop();
    }

    LOG(kSongcast, "OhmSender::~OhmSender stopped\n");
    delete iThreadUnicast;
    LOG(kSongcast, "OhmSender::~OhmSender deleted unicast thread\n");
    delete iThreadMulticast;
    LOG(kSongcast, "OhmSender::~OhmSender deleted multicast thread\n");
    delete iTimerAliveJoin;
    delete iTimerAliveAudio;
    delete iTimerExpiry;
    LOG(kSongcast, "OhmSender::~OhmSender deleted timers\n");
    delete iProvider;
    LOG(kSongcast, "OhmSender::~OhmSender deleted provider\n");
}

void OhmSender::SetName(const Brx& aValue)
{
    AutoMutex mutex(iMutexStartStop);
    
    if (iName != aValue) {
        iName.Replace(aValue);
        UpdateMetadata();
    }
}

void OhmSender::SetChannel(TUint aValue)
{
    AutoMutex mutex(iMutexStartStop);

    if (iChannel != aValue) {
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
                UpdateUri();
            }
        }
        else {
            iChannel = aValue;
            UpdateChannel();
        }
    }
}

void OhmSender::SetLatency(TUint aValue)
{
    AutoMutex mutex(iMutexStartStop);
    
    if (iLatency != aValue) {
        if (iStarted) {
            Stop();
            iLatency = aValue;
            iDriver.SetLatency(iLatency);
            LOG(kSongcast, "OHM SENDER DRIVER LATENCY %d\n", iLatency);
            Start();
        }
        else {
            iLatency = aValue;
            iDriver.SetLatency(iLatency);
            LOG(kSongcast, "OHM SENDER DRIVER LATENCY %d\n", iLatency);
        }
    }
}

void OhmSender::SetMulticast(TBool aValue)
{
    AutoMutex mutex(iMutexStartStop);

    if (iMulticast != aValue) {
        if (iStarted) {
            Stop();
            iMulticast = aValue;
            UpdateMetadata();
            Start();
        }
        else {
            iMulticast = aValue;
            UpdateMetadata();
        }
    }
}

void OhmSender::SetEnabled(TBool aValue)
{
    AutoMutex mutex(iMutexStartStop);

    if (iEnabled != aValue) {
        iEnabled = aValue;

        iDriver.SetEnabled(iEnabled);

        LOG(kSongcast, "OHM SENDER DRIVER ENABLED %d\n", aValue);
    
        if (iEnabled) {
            iProvider->SetStatusEnabled();
            Start();
        }
        else {
            Stop();
            iProvider->SetStatusDisabled();
        }
    }
}

void OhmSender::CurrentSubnetChanged()
{
    AutoMutex mutex(iMutexStartStop);

    static const TChar* kNifCookie = "OhmSender";
    NetworkAdapter* current = iEnv.NetworkAdapterList().CurrentAdapter(kNifCookie);
    const TIpAddress addr = (current? current->Address() : 0);
    current->RemoveRef(kNifCookie);
    if (iInterface != addr) {
        if (iStarted) {
            Stop();
            iInterface = addr;
            // recreate server before UpdateMetadata() as that function requires the server port
            UpdateMetadata();
            Start();
        }
        else {
            iInterface = addr;
        }
    }
}

void OhmSender::Start()
{
    // always called with the start/stop mutex locked
    if (!iStarted) {
        if (iMulticast) {
            iSocketOhm.OpenMulticast(iInterface, kTtl, iMulticastEndpoint);
            iTargetEndpoint.Replace(iMulticastEndpoint);
            iTargetInterface = iInterface;
            iThreadMulticast->Signal();
        }
        else {
            iSocketOhm.OpenUnicast(iInterface, kTtl);
            iTargetInterface = iInterface;
            iThreadUnicast->Signal();
        }
        iStarted = true;
        UpdateUri();
    }
}

void OhmSender::Stop()
{
    // always called with the start/stop mutex locked
    if (iStarted) {
        LOG(kSongcast, "STOP INTERRUPT\n");
        iSocketOhm.ReadInterrupt();
        LOG(kSongcast, "STOP WAIT\n");
        iNetworkDeactivated.Wait();
        LOG(kSongcast, "STOP CLOSE\n");
        iSocketOhm.Close();
        iStarted = false;
        LOG(kSongcast, "STOP UPDATE\n");
        UpdateUri();
        LOG(kSongcast, "STOP DONE\n");
    }
}

void OhmSender::SetTrack(const Brx& aUri, const Brx& aMetadata)
{
    AutoMutex mutex(iMutexActive);

    iClientControllingTrackMetadata = true;
    iSequenceTrack++;
    iSequenceMetatext = 0;
    iTrackUri.Replace(aUri);
    iTrackMetadata.Replace(aMetadata);
    iTrackMetatext.Replace(Brx::Empty());
    
    if (iActive) {
        SendTrack();
    }
}

void OhmSender::SetTrackPosition(TUint64 aSamplesTotal, TUint64 aSampleStart)
{
    AutoMutex mutex(iMutexActive);
    iDriver.SetTrackPosition(aSamplesTotal, aSampleStart);
}

void OhmSender::SetMetatext(const Brx& aValue)
{
    AutoMutex mutex(iMutexActive);

    iSequenceMetatext++;
    iTrackMetatext.Replace(aValue);
    
    if (iActive) {
        SendMetatext();
    }
}

void OhmSender::SetPreset(TUint aValue)
{
    iZoneHandler->SetPreset(aValue);
}

void OhmSender::NotifyAudioPlaying(TBool aPlaying)
{
    iProvider->NotifyAudioPlaying(aPlaying);
}

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
    for (;;) {
        LOG(kSongcast, "OhmSender::RunMulticast wait\n");
        iThreadMulticast->Wait();
        LOG(kSongcast, "OhmSender::RunMulticast go\n");
        iDriver.SetEndpoint(iTargetEndpoint, iTargetInterface);
        LOG(kSongcast, "OHM SENDER DRIVER ENDPOINT %x:%d\n", iTargetEndpoint.Address(), iTargetEndpoint.Port());
        try {
            for (;;) {
                try {
                    OhmHeader header;
                    header.Internalise(iRxBuffer);
                    
                    if (header.MsgType() <= OhmHeader::kMsgTypeListen) {
                        LOG(kSongcast, "OhmSender::RunMulticast join/listen received\n");
                        
                        AutoMutex mutex(iMutexActive);
                        
                        if (header.MsgType() == OhmHeader::kMsgTypeJoin) {
                            SendTrack();
                            SendMetatext();
                        }
                        if (!iActive) {
                            iActive = true;
                            iDriver.SetActive(true);
                            LOG(kSongcast, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
                        }
                        iAliveJoined = true;
                        iTimerAliveJoin->FireIn(kTimerAliveJoinTimeoutMs);
                    }
                    else if (header.MsgType() == OhmHeader::kMsgTypeResend) {
                        LOG(kSongcast, "OhmSender::RunMulticast resend received\n");

                        OhmHeaderResend headerResend;
                        headerResend.Internalise(iRxBuffer, header);

                        TUint frames = headerResend.FramesCount();
                        if (frames > 0) {
                            iDriver.Resend(iRxBuffer.Read(frames * 4));
                        }
                    }
                    else if (header.MsgType() == OhmHeader::kMsgTypeAudio) {
                        // Check sender not us
                        Endpoint sender = iSocketOhm.Sender();
                        if (sender.Address() != iInterface) {
                            LOG(kSongcast, "OhmSender::RunMulticast audio received\n");
                            // The following randomisation prevents two senders from both sending,
                            // both seeing each other's audio, both backing off for the same amount of time,
                            // then both sending again, then both seeing each other's audio again,
                            // then both backing off for the same amount of time ...
                            TUint delay = iEnv.Random(kTimerAliveAudioTimeoutMs, kTimerAliveAudioTimeoutMs >> 1);
                            { // scope for AutoMutex
                                AutoMutex mutex(iMutexActive);
                                if (iActive) {
                                    iActive = false;
                                    iDriver.SetActive(false);
                                    LOG(kSongcast, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
                                } 
                                iAliveBlocked = true;
                                iTimerAliveAudio->FireIn(delay);
                            }

                            LOG(kSongcast, "OhmSender::RunMulticast blocked\n");
                            iProvider->SetStatusBlocked();
                        }
                    }
                }
                catch (OhmError&) {
                    LOG2(kSongcast, kError, "OhmSender::RunMulticast OhmError\n");
                }
                
                iRxBuffer.ReadFlush();
            }
        }
        catch (ReaderError&) {
            LOG(kSongcast, "OhmSender::RunMulticast reader error\n");
        }

        iRxBuffer.ReadFlush();
        iTimerAliveJoin->Cancel();
        iTimerAliveAudio->Cancel();
        
        { // scope for AutoMutex
            AutoMutex mutex(iMutexActive);
            if (iActive) {
                iActive = false;
                iDriver.SetActive(false);
                LOG(kSongcast, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
            } 
            iAliveJoined = false;
            iAliveBlocked = false;
        }
        
        iNetworkDeactivated.Signal();
        LOG(kSongcast, "OhmSender::RunMulticast stop\n");
    }
}

void OhmSender::RunUnicast()
{
    for (;;) {
        LOG(kSongcast, "OhmSender::RunUnicast wait\n");
        iThreadUnicast->Wait();
        LOG(kSongcast, "OhmSender::RunUnicast go\n");
        try {
            for (;;) {
                // wait for first receiver to join
                // if we receive a listen, it's probably from a temporarily physically disconnected receiver
                // so accept them as well
                for (;;) {
                    OhmHeader header;
                    try {
                        header.Internalise(iRxBuffer);
                        
                        if (header.MsgType() <= OhmHeader::kMsgTypeListen) {
                            LOG(kSongcast, "OhmSender::RunUnicast ready/join or listen (%u)\n", header.MsgType());
                            break;                        
                        }
                    }
                    catch (OhmError&) {
                        LOG2(kSongcast, kError, "OhmSender: waiting for JOIN, caught OhmError, msgType=%u\n", header.MsgType());
                    }
                    iRxBuffer.ReadFlush();  
                }
    
                iRxBuffer.ReadFlush();
                iTargetEndpoint.Replace(iSocketOhm.Sender());
                iDriver.SetEndpoint(iTargetEndpoint, iTargetInterface);
                LOG(kSongcast, "OHM SENDER DRIVER ENDPOINT %x:%d\n", iTargetEndpoint.Address(), iTargetEndpoint.Port());
                SendTrack();
                SendMetatext();
                iSlaveCount = 0;
                { // scope for AutoMutex
                    AutoMutex mutex(iMutexActive);
                    iActive = true;
                    iAliveJoined = true;
                    iDriver.SetActive(true);
                    LOG(kSongcast, "OHM SENDER DRIVER ACTIVE %d\n", true);
                }
                iTimerExpiry->FireIn(kTimerExpiryTimeoutMs);
                
                for (;;) {
                    try {
                        OhmHeader header;
                        header.Internalise(iRxBuffer);
                        
                        if (header.MsgType() == OhmHeader::kMsgTypeJoin) {
                            LOG(kSongcast, "OhmSender::RunUnicast sending/join\n");
                            Endpoint sender(iSocketOhm.Sender());
                            if (sender.Equals(iTargetEndpoint)) {
                                iTimerExpiry->FireIn(kTimerExpiryTimeoutMs);
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave >= iSlaveCount) {
                                    if (slave < kMaxSlaveCount) {
                                        iSlaveList[slave].Replace(sender);
                                        iSlaveExpiry[slave] = Time::Now(iEnv) + kTimerExpiryTimeoutMs;
                                        iSlaveCount++;

                                        Endpoint::EndpointBuf buf;
                                        sender.AppendEndpoint(buf);
                                        LOG(kSongcast, "OhmSender::RunUnicast new slave: %s (#%u)\n", buf.Ptr(), iSlaveCount);

                                        AutoMutex mutex(iMutexActive);
                                        SendListen(sender);
                                    }
                                }
                                else {
                                    iSlaveExpiry[slave] = Time::Now(iEnv) + kTimerExpiryTimeoutMs;
                                }
                            }

                            AutoMutex mutex(iMutexActive);
                            SendSlaveList();
                            SendTrack();
                            SendMetatext();
                        }
                        else if (header.MsgType() == OhmHeader::kMsgTypeListen) {
                            Endpoint sender(iSocketOhm.Sender());

                            Endpoint::EndpointBuf endptBuf;
                            sender.AppendEndpoint(endptBuf);
                            LOG(kSongcast, "OhmSender::RunUnicast sending/listen from %s\n", endptBuf.Ptr());

                            if (sender.Equals(iTargetEndpoint)) {
                                iTimerExpiry->FireIn(kTimerExpiryTimeoutMs);
                                if (CheckSlaveExpiry()) {
                                    AutoMutex mutex(iMutexActive);
                                    SendSlaveList();
                                }
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave < iSlaveCount) {
                                    iSlaveExpiry[slave] = Time::Now(iEnv) + kTimerExpiryTimeoutMs;
                                }
                                else {
                                    // unknown slave, probably temporarily physically disconnected receiver
                                    if (slave < kMaxSlaveCount) {
                                        iSlaveList[slave].Replace(sender);
                                        iSlaveExpiry[slave] = Time::Now(iEnv) + kTimerExpiryTimeoutMs;
                                        iSlaveCount++;

                                        LOG(kSongcast, "OhmSender::RunUnicast new slave: %s (#%u)\n", endptBuf.Ptr(), iSlaveCount);

                                        AutoMutex mutex(iMutexActive);
                                        SendListen(sender);
                                        SendSlaveList();
                                        SendTrack();
                                        SendMetatext();
                                    }
                                }
                            }
                        }
                        else if (header.MsgType() == OhmHeader::kMsgTypeLeave) {
                            Endpoint sender(iSocketOhm.Sender());
                            Endpoint::EndpointBuf endptBuf;
                            sender.AppendEndpoint(endptBuf);
                            LOG(kSongcast, "OhmSender::RunUnicast LEAVE from %s\n", endptBuf.Ptr());
                            if (sender.Equals(iTargetEndpoint) || sender.Equals(iSocketOhm.This())) {
                                iTimerExpiry->Cancel();
                                if (iSlaveCount == 0) {
                                    break;
                                }
                                else {
                                    AutoMutex mutex(iMutexActive);
                                    iTargetEndpoint.Replace(iSlaveList[--iSlaveCount]);
                                    iTimerExpiry->FireAt(iSlaveExpiry[iSlaveCount]);
                                    if (iSlaveCount > 0) {
                                        SendSlaveList();
                                    }
                                    iDriver.SetEndpoint(iTargetEndpoint, iTargetInterface);
                                    LOG(kSongcast, "OHM SENDER DRIVER ENDPOINT %x:%d\n", iTargetEndpoint.Address(), iTargetEndpoint.Port());
                                }
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave < iSlaveCount) {
                                    RemoveSlave(slave);
                                    AutoMutex mutex(iMutexActive);
                                    SendLeave(sender);
                                    SendSlaveList();
                                }
                            }
                        }
                        else if (header.MsgType() == OhmHeader::kMsgTypeResend) {
                            LOG(kSongcast, "OhmSender::RunUnicast resend received\n");
                            OhmHeaderResend headerResend;
                            headerResend.Internalise(iRxBuffer, header);
                            TUint frames = headerResend.FramesCount();
                            if (frames > 0) {
                                iDriver.Resend(iRxBuffer.Read(frames * 4));
                            }
                        }
                    }
                    catch (OhmError&) {
                        LOG2(kSongcast, kError, "OhmSender::RunUnicast OhmError\n");
                    }
                    
                    iRxBuffer.ReadFlush();
                }

                iRxBuffer.ReadFlush();
                AutoMutex mutex(iMutexActive);
                iActive = false;
                iAliveJoined = false;               
                iDriver.SetActive(false);
                LOG(kSongcast, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
            }
        }
        catch (ReaderError&) {
            LOG(kSongcast, "OhmSender::RunUnicast reader error\n");
        }

        iRxBuffer.ReadFlush();
        iTimerExpiry->Cancel();

        { // scope for AutoMutex
            AutoMutex mutex(iMutexActive);
            if (iActive) {
                iActive = false;
                iDriver.SetActive(false);
                LOG(kSongcast, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
            } 
            iAliveJoined = false;
            iAliveBlocked = false;
        }

        iNetworkDeactivated.Signal();
        LOG(kSongcast, "OhmSender::RunUnicast stop\n");
    }
}

void OhmSender::TimerAliveJoinExpired()
{
    LOG(kSongcast, "AliveJoin timer expired\n");
    AutoMutex mutex(iMutexActive);
    iActive = false;
    iAliveJoined = false;
}

void OhmSender::TimerAliveAudioExpired()
{
    { // scope for AutoMutex
        AutoMutex mutex(iMutexActive);
        TBool joined = iAliveBlocked;
        iActive = joined;
        iAliveBlocked = false;
    }

    iProvider->SetStatusEnabled();
}

void OhmSender::TimerExpiryExpired()
{
    // Send a Leave to ourselves, which is interpreted as a Leave from the receiver
    LOG(kSongcast, "OhmSender::TimerExpiryExpired TIMEOUT\n");
    Bws<OhmHeader::kHeaderBytes> buffer;
    WriterBuffer writer(buffer);
    OhmHeader leave(OhmHeader::kMsgTypeLeave, 0);
    leave.Externalise(writer);
    AutoMutex mutex(iMutexActive);
    try {
        iSocketOhm.Send(buffer, iSocketOhm.This());
    }
    catch (NetworkError&) {
    }
}

void OhmSender::UpdateChannel()
{
    TUint address = (iChannel & 0xffff) | 0xeffd0000; // 239.253.x.x
    iMulticastEndpoint.SetAddress(Arch::BigEndian4(address));
    iMulticastEndpoint.SetPort(Ohm::kPort);
}

void OhmSender::UpdateUri()
{
    // access to iUri is protected by iStartStopMutex which is locked in all callers
    if (iStarted) {
        if (iMulticast) {
            iUri.Replace("ohm://");
            iMulticastEndpoint.AppendEndpoint(iUri);
        }
        else {
            iUri.Replace("ohu://");
            iSocketOhm.This().AppendEndpoint(iUri);
        }
    }
    else {
        iUri.Replace("ohu://0.0.0.0:0");
    }

    iZoneHandler->SetHomeSenderUri(iUri);
}

void OhmSender::UpdateMetadata()
{
    iSenderMetadata.Replace("<DIDL-Lite xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\" xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
    iSenderMetadata.Append("<item id=\"0\" restricted=\"True\">");
    iSenderMetadata.Append("<dc:title>");
    iSenderMetadata.Append(iName);
    iSenderMetadata.Append("</dc:title>");
    
    if (iMulticast) {
        iSenderMetadata.Append("<res protocolInfo=\"ohz:*:*:m\">");
    }
    else {
        iSenderMetadata.Append("<res protocolInfo=\"ohz:*:*:u\">");
    }

    iSenderUri.Replace(Brn("ohz://239.255.255.250:51972/"), iDevice.Udn());
    iSenderMetadata.Append(iSenderUri.AbsoluteUri());
    iSenderMetadata.Append("</res>");
    
    if (iImageFileName.Bytes() > 0)
    {
        AutoNetworkAdapterRef nifRef(iEnv, "OhmSender");
        NetworkAdapter* nif = nifRef.Adapter();
        if (nif != nullptr) {
            Brh imageUriPrefix;
            iDevice.GetResourceManagerUri(*nif, imageUriPrefix);
            if (imageUriPrefix.Bytes() > 0) {
                iSenderMetadata.Append("<upnp:albumArtURI>");
                iSenderMetadata.Append(imageUriPrefix);
                iSenderMetadata.Append(iImageFileName);
                iSenderMetadata.Append("</upnp:albumArtURI>");
            }
        }
    }
        
    iSenderMetadata.Append("<upnp:class>object.item.audioItem</upnp:class>");
    iSenderMetadata.Append("</item>");
    iSenderMetadata.Append("</DIDL-Lite>");

    if (!iClientControllingTrackMetadata) {
        AutoMutex mutex(iMutexActive);
        iTrackMetadata.Replace(iSenderMetadata);
        iSequenceTrack++;
        iSequenceMetatext = 0;
        if (iActive) {
            SendTrack();
        }
    }

    iProvider->SetMetadata(iSenderMetadata);
    iZoneHandler->SetSenderMetadata(iSenderMetadata);
}

void OhmSender::Send()
{
    try {
        iSocketOhm.Send(iTxBuffer, iTargetEndpoint);
    }
    catch (NetworkError&) {
    }
}

void OhmSender::SendTrack()
{
    // called with alive mutex locked;
    OhmHeaderTrack headerTrack(iSequenceTrack, iTrackUri, iTrackMetadata);
    OhmHeader header(OhmHeader::kMsgTypeTrack, headerTrack.MsgBytes());
    WriterBuffer writer(iTxBuffer);
    writer.Flush();
    header.Externalise(writer);
    headerTrack.Externalise(writer);
    writer.Write(iTrackUri);
    writer.Write(iTrackMetadata);

    Send();
}

void OhmSender::SendMetatext()
{
    // called with alive mutex locked;
    OhmHeaderMetatext headerMetatext(iSequenceMetatext, iTrackMetatext);
    OhmHeader header(OhmHeader::kMsgTypeMetatext, headerMetatext.MsgBytes());
    WriterBuffer writer(iTxBuffer);
    writer.Flush();
    header.Externalise(writer);
    headerMetatext.Externalise(writer);
    writer.Write(iTrackMetatext);
    
    Send();
}

void OhmSender::SendSlaveList()
{
    // called with alive mutex locked;
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

void OhmSender::SendListen(const Endpoint& aEndpoint)
{
    // Listen message is ignored by slaves, but this is sent to populate my arp tables
    // in case the slave needs to be quickly changed to master receiver.
    // Called with alive mutex locked;
    OhmHeader header(OhmHeader::kMsgTypeListen, 0);
    WriterBuffer writer(iTxBuffer);
    writer.Flush();
    header.Externalise(writer);
    try {
        iSocketOhm.Send(iTxBuffer, aEndpoint);
    }
    catch (NetworkError&) {
    }
}

void OhmSender::SendLeave(const Endpoint& aEndpoint)
{
    // Leave message is sent to acknowledge a Leave sent from a receiver or slave
    Endpoint::EndpointBuf buf;
    aEndpoint.AppendEndpoint(buf);
    LOG(kSongcast, "OhmSender::SendLeave to %s\n", buf.Ptr());

    OhmHeader header(OhmHeader::kMsgTypeLeave, 0);
    WriterBuffer writer(iTxBuffer);
    writer.Flush();
    header.Externalise(writer);
    try {
        iSocketOhm.Send(iTxBuffer, aEndpoint);
    }
    catch (NetworkError&) {
    }
}

TBool OhmSender::CheckSlaveExpiry()
{
    TBool changed = false;
    for (TUint i = 0; i < iSlaveCount;) {
        if (Time::IsInPastOrNow(iEnv, iSlaveExpiry[i])) {
            RemoveSlave(i);
            changed = true;
            continue;
        }
        i++;
    }
    
    return changed;
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
            return i;
        }
    }
    return iSlaveCount;
}
