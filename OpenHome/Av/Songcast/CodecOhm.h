#ifndef HEADER_CODEC_OHM
#define HEADER_CODEC_OHM

#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>
#include <OpenHome/Av/Songcast/OhmTimestamp.h>

namespace OpenHome {
namespace Av {

class CodecOhm : public Media::Codec::CodecBase, private IReader
{
public:
    CodecOhm(OhmMsgFactory& aMsgFactory, IOhmTimestampMapper* aTsMapper);
    ~CodecOhm();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType) override;
    TBool Recognise(const Media::Codec::EncodedStreamInfo& aStreamInfo) override;
    void StreamInitialise() override;
    void Process() override;
    TBool TrySeek(TUint aStreamId, TUint64 aSample) override;
    void StreamCompleted() override;
private: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    void OutputDelay();
    void Reset();
private:
    OhmMsgFactory& iMsgFactory;
    Bws<OhmMsgAudioBlob::kMaxBytes> iBuf;
    TUint iOffset;
    TBool iStreamOutput;
    TBool iSendSession;
    TUint iSampleRate;
    TUint iLatency;
    IOhmTimestampMapper* iTsMapper;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CODEC_OHM
