#ifndef HEADER_PIPELINE_PROTOCOL_RTSP
#define HEADER_PIPELINE_PROTOCOL_RTSP

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Protocol/Rtsp.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Uri.h>

namespace OpenHome {
namespace Media {

class ProtocolRtsp : public ProtocolNetwork
{
public:
    static const TUint kRtspPort = 554;
public:
    ProtocolRtsp(Environment& aEnv, const Brx& aGuid);
private: // from Protocol
    ProtocolStreamResult Stream(const Brx& aUri);
    ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes);
    ProtocolStreamResult DoStream();
    void OutputStream();
private: // from IStreamHandler
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    Environment& iEnv;
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


#endif  // HEADER_PIPELINE_PROTOCOL_RTSP
