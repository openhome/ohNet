#ifndef HEADER_CODEC_OHM
#define HEADER_CODEC_OHM

#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Av/Songcast/Ohm.h>
#include <OpenHome/Av/Songcast/OhmMsg.h>

namespace OpenHome {
namespace Av {

class CodecOhm : public Media::Codec::CodecBase, private IReader
{
public:
    CodecOhm(OhmMsgFactory& aMsgFactory);
    ~CodecOhm();
private: // from CodecBase
    TBool SupportsMimeType(const Brx& aMimeType) override;
    TBool Recognise() override;
    void StreamInitialise() override;
    void Process() override;
    TBool TrySeek(TUint aStreamId, TUint64 aSample) override;
private: // from IReader
    Brn Read(TUint aBytes) override;
    Brn ReadUntil(TByte aSeparator) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    void OutputDelay();
private:
    OhmMsgFactory& iMsgFactory;
    Bws<OhmMsgAudioBlob::kMaxBytes> iBuf;
    TUint iOffset;
    TBool iStreamOutput;
    TBool iSendSession;
    TUint iSampleRate;
    TUint iLatency;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CODEC_OHM
