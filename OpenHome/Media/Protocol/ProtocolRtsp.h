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
    //virtual void Stream();
private: // from Protocol
    ProtocolStreamResult Stream(const Brx& aUri);
private: // from IStreamHandler
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    void StartStream();
    //void OutputAudio();
private:
    Environment& iEnv;
    Uri iUri;
    RtspClient iRtspClient;
    SdpInfo iSdpInfo;
    ReaderBuffer iAudio;
    ReaderBuffer iRtp;
    TUint iKeepAliveTime;
    TUint iKeepAlivePeriod;
};

};  // namespace Media
};  // namespace OpenHome


#endif  // HEADER_PIPELINE_PROTOCOL_RTSP
