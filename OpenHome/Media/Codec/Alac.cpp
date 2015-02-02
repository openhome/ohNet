#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAlac : public CodecAlacBase
{
public:
    CodecAlac();
    ~CodecAlac();
private: // from CodecBase
    TBool Recognise(const EncodedStreamInfo& aStreamInfo);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
    static const TUint kMaxRecogBytes = 6 * 1024; // copied from previous CodecController behaviour
    Bws<kMaxRecogBytes> iRecogBuf;
    Mpeg4MediaInfo* iMp4;
};

} // namespace Codec
} // namespace Media
} // namespace OpenHome


using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

CodecBase* CodecFactory::NewAlac()
{ // static
    return new CodecAlac();
}


// CodecAlac

CodecAlac::CodecAlac() 
    : iMp4(NULL)
{
    LOG(kCodec, "CodecAlac::CodecAlac\n");
}

CodecAlac::~CodecAlac()
{
    LOG(kCodec, "CodecAlac::~CodecAlac\n");
    if (iMp4) {     // clean up in case not terminating under normal conditions
        delete iMp4;
        iMp4 = NULL;
        iContainer = NULL;
    }
}

TBool CodecAlac::Recognise(const EncodedStreamInfo& aStreamInfo)
{
    LOG(kCodec, "CodecAlac::Recognise\n");

    if (aStreamInfo.RawPcm()) {
        return false;
    }
    iRecogBuf.SetBytes(0);
    iController->Read(iRecogBuf, iRecogBuf.MaxBytes());
    Bws<4> codec;
    try {
        Mpeg4MediaInfo::GetCodec(iRecogBuf, codec);
    }
    catch (MediaMpeg4FileInvalid) {
        // We couldn't recognise this as an MPEG4/ALAC file.
        return false;
    }
    if (codec == Brn("alac")) {
        LOG(kCodec, "CodecAlac::Recognise alac\n");
        return true;
    }
    return false;
}

void CodecAlac::StreamInitialise()
{
    LOG(kCodec, "CodecAlac::StreamInitialise\n");

    iMp4 = new Mpeg4MediaInfo(*iController);
    try {
        iMp4->Process();
    }
    catch (MediaMpeg4EndOfData&) {
        THROW(CodecStreamEnded);
    }
    catch (MediaMpeg4FileInvalid&) {
        THROW(CodecStreamCorrupt);
    }
    iContainer = iMp4;

    CodecAlacBase::Initialise();
}

TBool CodecAlac::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecAlac::TrySeek(%u, %llu)\n", aStreamId, aSample);

    TUint64 startSample = 0;
    TUint64 bytes = iMp4->GetSeekTable().Offset(aSample, startSample);     // find file offset relating to given audio sample
    LOG(kCodec, "CodecAlac::TrySeek to sample: %llu, byte: %lld\n", startSample, bytes);
    TBool canSeek = iController->TrySeekTo(aStreamId, bytes);
    if (canSeek) {
        iSamplesWrittenTotal = aSample;
        iCurrentSample = startSample;
        iTrackOffset = (aSample * Jiffies::kPerSecond) / iMp4->Timescale();
        iController->OutputDecodedStream(0, iMp4->BitDepth(), iMp4->Timescale(), iMp4->Channels(), kCodecAlac, iTrackLengthJiffies, aSample, true);
    }
    return canSeek;
}

void CodecAlac::StreamCompleted()
{
    LOG(kCodec, "CodecAlac::StreamCompleted\n");
    if (iMp4) {
        delete iMp4;
        iMp4 = NULL;
        iContainer = NULL;
    }
    CodecAlacBase::StreamCompleted();
}

void CodecAlac::Process() 
{
    //LOG(kCodec, "CodecAlac::Process\n");

    if (iCurrentSample < iMp4->GetSampleSizeTable().Count()) {
        // read in a single alac sample
        iInBuf.SetBytes(0);

        try {
            //LOG(kCodec, "CodecAlac::Process  sample = %u, size = %u, inBuf max size %u\n", iCurrentSample, iMp4->GetSampleSizeTable().SampleSize((TUint)iCurrentSample), iInBuf.MaxBytes());
            TUint sampleSize = iMp4->GetSampleSizeTable().SampleSize((TUint)iCurrentSample);
            iController->Read(iInBuf, sampleSize);
            if (iInBuf.Bytes() < sampleSize) {
                THROW(CodecStreamEnded);
            }
            iCurrentSample++;
            Decode();
        }
        catch (CodecStreamStart&) {
            iStreamStarted = true;
            LOG(kCodec, "CodecAlac::Process caught CodecStreamStart\n");
        }
        catch (CodecStreamEnded&) {
            iStreamEnded = true;
            LOG(kCodec, "CodecAlac::Process caught CodecStreamEnded\n");
        }
    }
    else {
        iStreamEnded = true;
    }

    OutputFinal();
}
