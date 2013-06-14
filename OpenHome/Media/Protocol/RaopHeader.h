#ifndef HEADER_PIPELINE_CODEC_RAOP_HEADER
#define HEADER_PIPELINE_CODEC_RAOP_HEADER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Media/Codec/CodecController.h>

namespace OpenHome {
namespace Media {

class RaopDataHeader
{
public:
    RaopDataHeader(Brx& aRawData, TUint aSenderSkew, TUint aLatency);
    RaopDataHeader(Brx& aBinData);
    TByte Version();
    TByte Payload();
    TUint SenderSkew();
    TUint Latency();
    TUint16 Seqno();
    TUint16 Bytes();
    TUint32 Timestamp();
    TBool Start();
    TBool Mute();
    void SetMute();
private:
    TByte   iVersion;   // always 0x80
    TByte   iPayload;   // 0xe0 at start of stream; 0x60 otherwise
    TUint   iSenderSkew;
    TUint   iLatency;
    TUint16 iSeqno;
    TUint16 iBytes;
    TUint32 iTimestamp;
    TBool iStart;
    TBool iMute;
};

} // namespace Media
} // namespace OpenHome

#endif //HEADER_PIPELINE_CODEC_RAOP_DATA
