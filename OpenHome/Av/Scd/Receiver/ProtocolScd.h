#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Av/Scd/ScdMsg.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Av/Scd/Receiver/SupplyScd.h>

#include <memory>

namespace OpenHome {
namespace Scd {

class ProtocolScd : public Media::ProtocolNetwork
                  , private IScdMsgProcessor
{
    static const TUint kVersionMajor;
    static const TUint kVersionMinor;
public:
    ProtocolScd(Environment& aEnv, Media::TrackFactory& aTrackFactory);
    ~ProtocolScd();
private: // from Protocol
    void Initialise(Media::MsgFactory& aMsgFactory, Media::IPipelineElementDownstream& aDownstream) override;
    void Interrupt(TBool aInterrupt) override;
    Media::ProtocolStreamResult Stream(const Brx& aUri) override;
    Media::ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private: // from Media::IStreamHandler
    TUint TryStop(TUint aStreamId) override;
private: // from IScdMsgProcessor
    void Process(ScdMsgReady& aMsg) override;
    void Process(ScdMsgMetadataDidl& aMsg) override;
    void Process(ScdMsgMetadataOh& aMsg) override;
    void Process(ScdMsgFormat& aMsg) override;
    void Process(ScdMsgAudio& aMsg) override;
    void Process(ScdMsgMetatextDidl& aMsg) override;
    void Process(ScdMsgMetatextOh& aMsg) override;
    void Process(ScdMsgHalt& aMsg) override;
    void Process(ScdMsgDisconnect& aMsg) override;
    void Process(ScdMsgSeek& aMsg) override;
    void Process(ScdMsgSkip& aMsg) override;
private:
    void OutputTrack(Media::Track* aTrack);
    void OutputStream();
private:
    Mutex iLock;
    ScdMsgFactory iScdFactory;
    Media::TrackFactory& iTrackFactory;
    std::unique_ptr<SupplyScd> iSupply;
    Uri iUri;
    ScdMsgFormat* iStreamFormat;
    Media::BwsTrackMetaData iMetadata; // only required at function scope but too big for the stack
    TUint iStreamId;
    TUint iNextFlushId;
    TBool iStarted;
    TBool iStopped;
    TBool iUnrecoverableError;
    TBool iFormatReqd;
    TBool iExit;
};

};  // namespace Scd
};  // namespace OpenHome
