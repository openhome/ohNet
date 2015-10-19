#pragma once

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/Rtsp.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Media/SupplyAggregator.h>

namespace OpenHome {
namespace Media {

class ProtocolRtsp : public ProtocolNetwork
{
public:
    static const TUint kRtspPort = 554;
public:
    ProtocolRtsp(Environment& aEnv, const Brx& aGuid);
    ~ProtocolRtsp();
private: // from Protocol
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream) override;
    ProtocolStreamResult Stream(const Brx& aUri) override;
    ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private:
    ProtocolStreamResult DoStream();
    void OutputStream();
private: // from IStreamHandler
    TUint TryStop(TUint aStreamId) override;
private:
    Environment& iEnv;
    SupplyAggregatorBytes* iSupply;
    Uri iUri;
    RtspClient iRtspClient;
    SdpInfo iSdpInfo;
    ReaderBuffer iAudio;
    ReaderBuffer iRtp;
    TUint iKeepAliveTime;
    TUint iKeepAlivePeriod;
    TUint iStreamId;
    TUint iNextFlushId;
    TBool iStopped;
};

};  // namespace Media
};  // namespace OpenHome


