#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Codec/AlacBase.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/CodecFactory.h>
#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Av/Debug.h>

namespace OpenHome {
namespace Media {
namespace Codec {

class CodecAlac : public CodecAlacBase
{
public:
    CodecAlac();
    ~CodecAlac();
private: // from CodecBase
    TBool Recognise(const Brx& aData);
    void StreamInitialise();
    void Process();
    TBool TrySeek(TUint aStreamId, TUint64 aSample);
    void StreamCompleted();
private:
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

TBool CodecAlac::Recognise(const Brx& aData)
{
    LOG(kCodec, "CodecAlac::Recognise\n");
    Bws<4> codec;

    try {
        Mpeg4MediaInfo::GetCodec(aData, codec);
    }
    catch (MediaMpeg4FileInvalid) {
        // We couldn't recognise this as an MPEG4/ALAC file.
        return false;
    }

    if (codec == kCodecAlac) {
        LOG(kCodec, "CodecAlac::Recognise alac\n");
        return true;
    }
    return false;
}

void CodecAlac::StreamInitialise()
{
    LOG(kCodec, "CodecAlac::StreamInitialise\n");

    iMp4 = new Mpeg4MediaInfo(*iController);
    iContainer = iMp4;

    CodecAlacBase::Initialise();
}

TBool CodecAlac::TrySeek(TUint aStreamId, TUint64 aSample)
{
    LOG(kCodec, "CodecAlac::TrySeek(%u, %llu)\n", aStreamId, aSample);

    TUint64 startSample = 0;
    TUint64 bytes = iMp4->GetSeekTable().Offset(aSample, startSample);     // find file offset relating to given audio sample
    LOG(kCodec, "CodecAlac::TrySeek to sample: %llu, byte: %lld\n", startSample, bytes);
    TBool canSeek = iController->TrySeek(aStreamId, bytes);
    if (canSeek) {
        iSamplesWrittenTotal = aSample;
        iCurrentSample = startSample;
        iTrackOffset = (aSample * Jiffies::kJiffiesPerSecond) / iMp4->SampleRate();
        iController->OutputDecodedStream(0, iMp4->BitDepth(), iMp4->SampleRate(), iMp4->Channels(), kCodecAlac, iTrackLengthJiffies, aSample, true);
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
            iController->Read(iInBuf, iMp4->GetSampleSizeTable().SampleSize((TUint)iCurrentSample));
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
