#include <OpenHome/Media/Protocol/ProtocolTone.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Standard.h>

#include <vector>
#include <cstring>

#include <OpenHome/Private/Printer.h>  // XXX Log::Print()
#include <OpenHome/Media/Msg.h>  // XXX MsgFlush::kIdInvalid
#include <cctype>  // XXX isprint()

#undef DEFINE_DEBUG_JOHNH

//
// declarations:  see ProtocolTone.h
//


//
// implementations
//

using namespace OpenHome;
using namespace OpenHome::Media;;

// static function in ProtocolFactory
Protocol* ProtocolFactory::NewTone(Environment& aEnv)
{
    return new ProtocolTone(aEnv);
}

// ProtocolTone
ProtocolTone::ProtocolTone(Environment& aEnv)
    : Protocol(aEnv)
    , iToneGenerators()
{
    iToneGenerators.push_back(new ToneGeneratorSilence);
    iToneGenerators.push_back(new ToneGeneratorSquare);
#ifdef DEFINE_DEBUG
    iToneGenerators.push_back(new ToneGeneratorPattern);
#endif  // DEFINE_DEBUG
}

ProtocolTone::~ProtocolTone()
{
    while (!iToneGenerators.empty()) {
        delete iToneGenerators.back();
        iToneGenerators.pop_back();
    }
}

TUint ProtocolTone::TryStop(TUint /* aTrackId */, TUint /* aStreamId */)
{
    return MsgFlush::kIdInvalid;  // XXX
}

// TUint ProtocolTone::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset) { }

ToneParams::ToneParams()
    : bitsPerSample(0)
    , sampleRate(0)
    , pitch(0)
    , numChannels(0)
    , duration(0)
{
}

ToneParams::ToneParams(TUint16 aBitsPerSample, TUint aSampleRate, TUint aPitch, TUint16 aNumChannels, TUint aDuration)
    : bitsPerSample(aBitsPerSample)
    , sampleRate(aSampleRate)
    , pitch(aPitch)
    , numChannels(aNumChannels)
    , duration(aDuration)
{
}

void ToneParams::Set(TUint16 aBitsPerSample, TUint aSampleRate, TUint aPitch, TUint16 aNumChannels, TUint aDuration)
{
    bitsPerSample = aBitsPerSample;
    sampleRate = aSampleRate;
    pitch = aPitch;
    numChannels = aNumChannels;
    duration = aDuration;
}

ToneUriParser::ToneUriParser()
    : iParams()
    , iName(Brx::Empty())
{
} 

void ToneUriParser::Parse(const Brx& aUri)
{
    // tone://WAVEFORM.wav?bitdepth=N&samplerate=M&pitch=HZ&channels=K&duration=T
    Uri uri;

    try {
        uri.Replace(aUri);
    } catch (UriError&) {
        // translate exception so as not to expose implementation details
        THROW(ToneUriParseError);
    }

    // BufferOverflow deliberately not caught: programmer error
    iName.ReplaceThrow(uri.Host());

    if (uri.Path() != Brn("/")) {
        THROW(ToneUriParseError);
    }

    if (!uri.Query().BeginsWith(Brn("?"))) {
        THROW(ToneUriParseError);
    }

    // initialise to illegal values to detect missing ones easily below
    iParams = ToneParams();

    Parser parser(uri.Query());
    parser.Forward(1);  // initial "?" already checked

    while (!parser.Finished()) {
        const Brn& keyVal = parser.Next('&');

        Parser kvParser(keyVal);
        const Brn& key = kvParser.Next('=');
        const Brn& val = kvParser.NextToEnd();

        if (key == Brn("bitdepth")) {
            if (iParams.bitsPerSample != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            iParams.bitsPerSample = static_cast<TUint16>(Ascii::Uint(val));
            if ((iParams.bitsPerSample != 8) && (iParams.bitsPerSample != 16) && (iParams.bitsPerSample != 24)) {
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("samplerate")) {
            if (iParams.sampleRate != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            iParams.sampleRate = Ascii::Uint(val);
            switch (iParams.sampleRate) {
                // from OpenHome/Media/Msg.cpp
                case 7350: case 14700: case 29400:
                case 8000: case 16000: case 32000:
                case 11025: case 22050: case 44100: case 88200: case 176400:
                case 12000: case 24000: case 48000: case 96000: case 192000:
                    break;
                default:
                    THROW(ToneUriParseError);
            }
        } else if (key == Brn("pitch")) {  // [Hz]
            if (iParams.pitch != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            iParams.pitch = Ascii::Uint(val);
            // XXX no upper limit, since not necessarily intended for human hearing
            if (0 == iParams.pitch) {
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("channels")) {
            if (iParams.numChannels != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            // 1 ... 8 (in practice no more than 7.1 surround sound)
            iParams.numChannels = static_cast<TUint16>(Ascii::Uint(val));
            if (! ((0 < iParams.numChannels) && (iParams.numChannels <= 8))) {
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("duration")) {  // [s]
            if (iParams.duration != 0) {
                THROW(ToneUriParseError);  // duplicate parameter
            }
            // 1 ... 900 (i.e. 15min): arbitrary limit guaranteed to avoid integer overflow in calculations
            iParams.duration = Ascii::Uint(val);
            if (! ((0 < iParams.duration) && (iParams.duration <= 900))) {
                THROW(ToneUriParseError);
            }
        } else {
            THROW(ToneUriParseError);  // unrecognised key-value pair
        }
    }

    // check for missing parameters (separately, to have unique exception line numbers)
    if (iParams.bitsPerSample == 0) {
        THROW(ToneUriParseError);
    } else if (iParams.sampleRate == 0) {
        THROW(ToneUriParseError);
    } else if (iParams.pitch == 0) {
        THROW(ToneUriParseError);
    } else if (iParams.numChannels == 0) {
        THROW(ToneUriParseError);
    } else if (iParams.duration == 0) {
        THROW(ToneUriParseError);
    }
}

const ToneParams& ToneUriParser::Params() const
{
    return iParams;
}

const Brx& ToneUriParser::Name() const
{
    return iName;
}

// tone generation
ToneGenerator::ToneGenerator(const TChar* aName)
    : iName(aName)
{
}

TBool ToneGenerator::Recognise(const Brx& aName) const
{
    return aName == iName;
}

#ifdef DEFINE_DEBUG
ToneGeneratorPattern::ToneGeneratorPattern()
    : ToneGenerator("pattern.wav")
{
}

TInt32 ToneGeneratorPattern::Generate(TUint /* aOffset */, TUint /* aMaxOffset */)
{
    static TUint cnt = 0;
    cnt = (cnt + 4) & 0xff;
    return (((cnt + 2) << 16) | ((cnt + 1) << 8) | cnt) & 0x00ffffff;
}
#endif  // DEFINE_DEBUG

ToneGeneratorSilence::ToneGeneratorSilence()
    : ToneGenerator("silence.wav")
{
}

// contract: return at most 24-bit value
TInt32 ToneGeneratorSilence::Generate(TUint /* aOffset */, TUint /* aMaxOffset */)
{
    return 0;
}

ToneGeneratorSquare::ToneGeneratorSquare()
    : ToneGenerator("square.wav")
{
}

// contract: return at most 24-bit value
TInt32 ToneGeneratorSquare::Generate(TUint aOffset, TUint aMaxOffset)
{
    // minimum value (two's complement)
    TUint32 val = 1 << 23;
    // full-scale signal with 50% duty cycle
    if (aOffset >= (aMaxOffset / 2)) {
        val -= 1;  // deliberate integer underflow from smallest -ve to largest +ve
    }
    return val;
}

ProtocolStreamResult ProtocolTone::Stream(const Brx& aUri)
{
    if (!aUri.BeginsWith(Brn("tone://"))) {
        // quietly decline offer to handle other URL schemes; leave it to other protocol modules
        return EProtocolErrorNotSupported;
    }

    ToneUriParser uriParser;
    try {
        uriParser.Parse(aUri);
    } catch (ToneUriParseError&) {
        return EProtocolErrorNotSupported;
    } catch (UriError&) {
        return EProtocolErrorNotSupported;
    }

    // XXX unsupported waveforms reported below when trying to find appropriate waveform generator

    const ToneParams& params = uriParser.Params();

#ifdef DEFINE_DEBUG_JOHNH
    Log::Print("@@  bitdepth =   %6u\n", params.bitsPerSample);
    Log::Print("@@  samplerate = %6u\n", params.sampleRate);
    Log::Print("@@  pitch =      %6u\n", params.pitch);
    Log::Print("@@  channels =   %6u\n", params.numChannels);
    Log::Print("@@  duration =   %6u\n", params.duration);
    Log::Print("\n");
#endif  // DEFINE_DEBUG_JOHNH

    //
    // output WAV header:  https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
    //

    const TUint nSamples = params.sampleRate * params.duration;
    // precondition enforced above: bitsPerSample % 8 == 0

    // chunkId: "RIFF" = 0x52494646 (BE)
    // chunkSize: see below
    // format: "WAVE" = 0x57415645 (BE)
    // subchunkOneId: "fmt " = 0x664d7420 (BE)
    const TUint subchunkOneSize = 16;  // for PCM data, no extra parameters in "fmt " subchunnk
    const TUint16 audioFormat = 1;  // PCM (linear quantisation, no compression)
    // TUint16 numChannels: see above (parsing)
    // TUint sampleRate: see above (parsing)
    const TUint byteRate = params.sampleRate * params.numChannels * (params.bitsPerSample / 8);
    const TUint16 blockAlign = params.numChannels * (params.bitsPerSample / 8);
    // TUint16 bitsPerSample: see above (parsing)
    // subchunkTwoId: "data" = 0x64617461 (BE)
    const TUint subchunkTwoSize = nSamples * params.numChannels * (params.bitsPerSample / 8);

    // no integer overflow in worst case: 4 + 8 + 16 + 8 + (192000 * 900 * 8 * 3) < 2^32-1
    const TUint chunkSize = 4 + (8 + subchunkOneSize) + (8 + subchunkTwoSize);

    #define LE2(x) iAudioBuf.Append(static_cast<TByte>((x) & 0x00ff)); iAudioBuf.Append(static_cast<TByte>(((x) & 0xff00) >> 8));
    #define LE4(x) iAudioBuf.Append(static_cast<TByte>((x) & 0x000000ff)); iAudioBuf.Append(static_cast<TByte>(((x) & 0x0000ff00) >> 8)); iAudioBuf.Append(static_cast<TByte>(((x) & 0x00ff0000) >> 16)); iAudioBuf.Append(static_cast<TByte>(((x) & 0xff000000) >> 24));
    iAudioBuf.SetBytes(0);  // reset audio buffer
    iAudioBuf.Append("RIFF");  // != RIFX, i.e. all integer values in little endian format
    LE4(chunkSize)
    iAudioBuf.Append("WAVE");
    iAudioBuf.Append("fmt ");  // trailing space significant
    LE4(subchunkOneSize)
    LE2(audioFormat)
    LE2(params.numChannels)
    LE4(params.sampleRate)
    LE4(byteRate)
    LE2(blockAlign)
    LE2(params.bitsPerSample)
    iAudioBuf.Append("data");
    LE4(subchunkTwoSize)

#ifdef DEFINE_DEBUG_JOHNH
    HexDump(iAudioBuf.Ptr(), iAudioBuf.Bytes());
#endif  // DEFINE_DEBUG_JOHNH

    // dynamically select waveform generator
    ToneGenerator *generator = NULL;
    for (TUint i = 0; i < iToneGenerators.size(); ++i) {
        if (iToneGenerators[i]->Recognise(uriParser.Name())) {
            generator = iToneGenerators[i];
        }
    }
    if (NULL == generator) {
        return EProtocolStreamErrorUnrecoverable;
    }

    //
    // output audio data (data members inherited from Protocol)
    // N.B. assuming only periodic waveforms and identical output on all channels
    //

    // chosen max number of samples that can be Generate()d for any waveform;
    // esp. for LUT-based implementation: trade-off between (on-device) space and audio resolution;
    // pitch more likely to be N x 10[Hz] rather than N x 2^r[Hz]
    // XXX 64000 = 2^6 x 10^3, i.e. plenty of factors from binary and decimal world;
    //     also fits into TUint16;  sizeof(int) x 64000 < 256kB
    const TUint kMaxVirtualSamplesPerPeriod = 64000;  // Nyquist limit: assuming pitch <= 32kHz (beyond audible range)

    // 64000 < 2^16 and (worst case) 32000 < 2^15, so multiplication cannot overflow unsigned 32-bit value
    const TUint virtualSamplesStep = (kMaxVirtualSamplesPerPeriod * params.pitch) / params.sampleRate;

    TUint streamId = iIdProvider->NextStreamId();  // indicate to pipeline that fresh stream is starting
    iSupply->OutputStream(aUri, /*RIFF-WAVE*/ iAudioBuf.Bytes() + nSamples * blockAlign, /*aSeekable*/ false, /*aLive*/ false, /*IStreamHandler*/ *this, streamId);

    for (TUint i = 0; i < nSamples; ++i) {
        // ensure sufficient capacity for another (multi-channel) audio sample
        if (iAudioBuf.Bytes() + blockAlign > iAudioBuf.MaxBytes()) {
#ifdef DEFINE_DEBUG_JOHNH
            Log::Print("flushing audio buffer: %u[B]\n", iAudioBuf.Bytes());
            HexDump(iAudioBuf.Ptr(), iAudioBuf.Bytes());
#endif  // DEFINE_DEBUG_JOHNH
            iSupply->OutputData(iAudioBuf);
            iAudioBuf.SetBytes(0);  // reset audio buffer
        }

        TUint x = (i * virtualSamplesStep) % kMaxVirtualSamplesPerPeriod;
        // contract: generator to produce at most 24-bit values
        TInt32 audioSample = generator->Generate(x, kMaxVirtualSamplesPerPeriod);
        switch (params.bitsPerSample) {
            case 8:
                audioSample >>= 16;
                for (int ch = 0; ch < params.numChannels; ++ch) {
                    iAudioBuf.Append(static_cast<TByte>(audioSample));
                }
                break;
            case 16:
                audioSample >>= 8;  // correct sign extension guaranteed
                for (int ch = 0; ch < params.numChannels; ++ch) {
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0x00ff)));  // LE
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0xff00) >> 8));
                }
                break;
            case 24:
                for (int ch = 0; ch < params.numChannels; ++ch) {
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0x0000ff)));  // LE
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0x00ff00) >> 8));
                    iAudioBuf.Append(static_cast<TByte>((audioSample & 0xff0000) >> 16));
                }
                break;
            default:
                ASSERTS();
        }
    }

    // flush final audio data (if any) from (partially) filled audio buffer
#ifdef DEFINE_DEBUG_JOHNH
    Log::Print("flushing final audio buffer: %u[B]\n", iAudioBuf.Bytes());
    HexDump(iAudioBuf.Ptr(), iAudioBuf.Bytes());
#endif  // DEFINE_DEBUG_JOHNH
    iSupply->OutputData(iAudioBuf);

    return EProtocolStreamSuccess;
}

#ifdef DEFINE_DEBUG
void ProtocolTone::HexDump(const TByte *aBase, TUint aSize) const
{
    const TByte *p = aBase;
    const int kBytesPerLine = 16;  // 16 x 3 chars + 2 chars + 16 chars < 80
    do {
        int maxBytes = kBytesPerLine;
        if ((p + maxBytes) > (aBase + aSize)) {
            maxBytes = aSize % kBytesPerLine;
        }

        for (int i = 0; i < maxBytes; ++i) {
            Log::Print("%02x ", *(p + i));
        }
        for (int i = 0; i < (kBytesPerLine - maxBytes); ++i) {
            Log::Print("   ");  // optical filler for last line
        }
        Log::Print(" ");
        for (int i = 0; i < maxBytes; ++i) {
            Log::Print("%c", isprint(*(p + i)) ? *(p + i) : '.');
        }
        Log::Print("\n");

        p += kBytesPerLine;
    } while (p < (aBase + aSize));
}
#endif  // DEFINE_DEBUG
