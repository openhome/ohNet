#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Optional.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>
#include <OpenHome/Av/Songcast/OhmSocket.h>
#include <OpenHome/Av/Songcast/OhmTimestamp.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Media/Supply.h>

#include <vector>

EXCEPTION(OhmDiscontinuity);

namespace OpenHome {
    class Environment;
    class Timer;
namespace Av {

class ProtocolOhBase : public Media::Protocol, private IOhmMsgProcessor
{
    static const TUint kMaxRepairBacklogFrames = 200;
    static const TUint kMaxRepairMissedFrames = 20;
    static const TUint kInitialRepairTimeoutMs = 10;
    static const TUint kSubsequentRepairTimeoutMs = 30;
    static const TUint kTimerJoinTimeoutMs = 300;
    static const TUint kTtl = 2;
protected:
    ProtocolOhBase(Environment& aEnv, IOhmMsgFactory& aFactory, Media::TrackFactory& aTrackFactory,
                   Optional<IOhmTimestamper> aTimestamper, const TChar* aSupportedScheme, const Brx& aMode);
    ~ProtocolOhBase();
    void Add(OhmMsg* aMsg);
    void ResendSeen();
    void RequestResend(const Brx& aFrames);
    void SendJoin();
    void SendListen();
    void Send(TUint aType);
    TBool IsCurrentStream(TUint aStreamId) const;
    void WaitForPipelineToEmpty();
    void AddRxTimestamp(OhmMsgAudio& aMsg);
private:
    virtual Media::ProtocolStreamResult Play(TIpAddress aInterface, TUint aTtl, const Endpoint& aEndpoint) = 0;
    virtual void ProcessTimestamps(const OhmMsgAudio& aMsg, TBool& aDiscard) = 0;
protected: // from Media::Protocol
    void Interrupt(TBool aInterrupt) override;
private: // from Media::Protocol
    void Initialise(Media::MsgFactory& aMsgFactory, Media::IPipelineElementDownstream& aDownstream) override;
    Media::ProtocolStreamResult Stream(const Brx& aUri) override;
    Media::ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private: // from IStreamHandler
    Media::EStreamPlay OkToPlay(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private:
    void CurrentSubnetChanged();
    void RepairReset();
    void TimerRepairExpired();
    TBool RepairBegin(OhmMsgAudio& aMsg);
    TBool Repair(OhmMsgAudio& aMsg);
    void OutputAudio(OhmMsgAudio& aMsg);
private: // from IOhmMsgProcessor
    void Process(OhmMsgAudio& aMsg) override;
    void Process(OhmMsgAudioBlob& aMsg) override;
    void Process(OhmMsgTrack& aMsg) override;
    void Process(OhmMsgMetatext& aMsg) override;
protected:
    static const TUint kMaxFrameBytes = 6*1024;
    static const TUint kTimerListenTimeoutMs = 10000;
protected:
    Environment& iEnv;
    IOhmMsgFactory& iMsgFactory;
    Media::Supply* iSupply;
    OhmSocket iSocket;
    Srs<kMaxFrameBytes> iReadBuffer;
    Endpoint iEndpoint;
    Timer* iTimerJoin;
    Timer* iTimerListen;
    Media::BwsMode iMode;
    TUint iStreamId;
    Mutex iMutexTransport;
    IOhmTimestamper* iTimestamper;
    TBool iStarving;
private:
    Media::TrackFactory& iTrackFactory;
    Brn iSupportedScheme;
    TUint iNacnId;
    Uri iUri; // only used inside Stream() but too large to put on the stack
    TUint iFrame;
    TBool iRunning;
    TBool iRepairing;
    TBool iTrackMsgDue;
    TBool iStreamMsgDue;
    TBool iMetatextMsgDue;
    TBool iSeqTrackValid;
    Bws<Media::MsgMetaText::kMaxBytes> iMetatext;
    Bws<Media::MsgMetaText::kMaxBytes> iPendingMetatext;
    TUint iSeqTrack;
    TUint64 iLastSampleStart;
    TUint iBitDepth;
    TUint iSampleRate;
    TUint iNumChannels;
    TUint64 iLatency;
    OhmMsgAudio* iRepairFirst;
    std::vector<OhmMsgAudio*> iRepairFrames;
    Timer* iTimerRepair;
    TUint iAddr; // FIXME - should listen for subnet changes and update this value
    Media::BwsTrackUri iTrackUri;
    Media::BwsTrackMetaData iTrackMetadata;
    Semaphore iPipelineEmpty;
};

} // namespace Av
} // namespace OpenHome

