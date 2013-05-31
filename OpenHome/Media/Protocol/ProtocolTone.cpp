#include <OpenHome/Media/Protocol/ProtocolTone.h>
#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Arch.h>

#include <cstring>

#include <OpenHome/Private/Printer.h>  // XXX Log::Print()
#include <OpenHome/Media/Msg.h>  // XXX MsgFlush::kIdInvalid
#include <cctype>  // XXX isprint()

#ifndef NDEBUG
    // msg is always string, but val can be any expression (incl. one for which no format specifier exists)
    #define LOG_DBG(msg, val) \
        Log::Print("!!  %s:%d: " msg ": ", __FILE__, __LINE__); Log::Print(val); Log::Print("\n");
#else
    #define LOG_DBG(msg, val) /* NOP */
#endif

//
// declarations
//

namespace OpenHome {
namespace Media {

class ProtocolTone : public Protocol
{
public:
    ProtocolTone(Environment& aEnv);
private: // from Protocol
    ProtocolStreamResult Stream(const Brx& aUri);
private:  // from IStreamHandler
    TUint TryStop(TUint aTrackId, TUint aStreamId);
};

} // namespace Media
} // namespace OpenHome


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
ProtocolTone::ProtocolTone(Environment& aEnv) : Protocol(aEnv)
{
    // XXX
}

// XXX any need to override virtual dtor?
// ProtocolTone::~ProtocolTone() { }

TUint ProtocolTone::TryStop(TUint /* aTrackId */, TUint /* aStreamId */)
{
    return MsgFlush::kIdInvalid;  // XXX
}

// TUint ProtocolTone::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset) { }


EXCEPTION(ToneUriParseError)

ToneUriParser::ToneUriParser() : iParams(), iName(Brn::Empty())
{
    // NOP
} 

void ToneUriParser::Parse(const Brx& aUri)
{
    // tone://WAVEFORM.wav?bitdepth=N&samplerate=M&pitch=HZ&channels=K&duration=T
    Uri uri(aUri);
    iName.Set(uri.Host());

    if (uri.Path() != Brn("/")) {
        LOG_DBG("spurious path", uri.Path())
        THROW(ToneUriParseError);
    }

    if (!uri.Query().BeginsWith(Brn("?"))) {
        LOG_DBG("missing or malformed query", uri.Query())
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
                LOG_DBG("duplicate parameter", "bitdepth")
                THROW(ToneUriParseError);
            }
            iParams.bitsPerSample = static_cast<TUint16>(Ascii::Uint(val));
            if ((iParams.bitsPerSample != 8) && (iParams.bitsPerSample != 16) && (iParams.bitsPerSample != 24)) {
                LOG_DBG("invalid parameter value", keyVal)
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("samplerate")) {
            if (iParams.sampleRate != 0) {
                LOG_DBG("duplicate parameter", "samplerate")
                THROW(ToneUriParseError);
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
                    LOG_DBG("invalid parameter value", keyVal)
                    THROW(ToneUriParseError);
            }
        } else if (key == Brn("pitch")) {  // [Hz]
            if (iParams.pitch != 0) {
                LOG_DBG("duplicate parameter", "pitch")
                THROW(ToneUriParseError);
            }
            iParams.pitch = Ascii::Uint(val);
            // XXX no upper limit, since not necessarily intended for human hearing
            if (0 == iParams.pitch) {
                LOG_DBG("invalid parameter value", keyVal)
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("channels")) {
            if (iParams.numChannels != 0) {
                LOG_DBG("duplicate parameter", "channels")
                THROW(ToneUriParseError);
            }
            // 1 ... 8 (in practice no more than 7.1 surround sound)
            iParams.numChannels = static_cast<TUint16>(Ascii::Uint(val));
            if (! ((0 < iParams.numChannels) && (iParams.numChannels <= 8))) {
                LOG_DBG("invalid parameter value", keyVal)
                THROW(ToneUriParseError);
            }
        } else if (key == Brn("duration")) {  // [s]
            if (iParams.duration != 0) {
                LOG_DBG("duplicate parameter", "duration")
                THROW(ToneUriParseError);
            }
            // 1 ... 900 (i.e. 15min): arbitrary limit guaranteed to avoid integer overflow in calculations
            iParams.duration = Ascii::Uint(val);
            if (! ((0 < iParams.duration) && (iParams.duration <= 900))) {
                LOG_DBG("invalid parameter value", keyVal)
                THROW(ToneUriParseError);
            }
        } else {
            LOG_DBG("unrecognised keyword", key)
            THROW(ToneUriParseError);
        }
    }

    if (iParams.bitsPerSample == 0) {
        LOG_DBG("missing parameter", "bitdepth")
        THROW(ToneUriParseError);
    } else if (iParams.sampleRate == 0) {
        LOG_DBG("missing parameter", "samplerate")
        THROW(ToneUriParseError);
    } else if (iParams.pitch == 0) {
        LOG_DBG("missing parameter", "pitch")
        THROW(ToneUriParseError);
    } else if (iParams.numChannels == 0) {
        LOG_DBG("missing parameter", "channels")
        THROW(ToneUriParseError);
    } else if (iParams.duration == 0) {
        LOG_DBG("missing parameter", "duration")
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

    LOG_DBG("successfully parsed all parameters", "")
    Log::Print("@@  bitdepth =   %6u\n", params.bitsPerSample);
    Log::Print("@@  samplerate = %6u\n", params.sampleRate);
    Log::Print("@@  pitch =      %6u\n", params.pitch);
    Log::Print("@@  channels =   %6u\n", params.numChannels);
    Log::Print("@@  duration =   %6u\n", params.duration);

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

    // serialise RIFF-WAVE structure for output
    TByte riffWav[44] = { 0 };

    strncpy(reinterpret_cast<char *>(riffWav + 0), "RIFF", 4);
    *reinterpret_cast<TUint *>(riffWav + 4) = Arch::LittleEndian4(chunkSize);
    strncpy(reinterpret_cast<char *>(riffWav + 8), "WAVE", 4);
    strncpy(reinterpret_cast<char *>(riffWav + 12), "fmt ", 4);  // trailing space is significant
    *reinterpret_cast<TUint *>(riffWav + 16) = Arch::LittleEndian4(subchunkOneSize);
    *reinterpret_cast<TUint *>(riffWav + 20) = Arch::LittleEndian2(audioFormat);
    *reinterpret_cast<TUint *>(riffWav + 22) = Arch::LittleEndian2(params.numChannels);
    *reinterpret_cast<TUint *>(riffWav + 24) = Arch::LittleEndian4(params.sampleRate);
    *reinterpret_cast<TUint *>(riffWav + 28) = Arch::LittleEndian4(byteRate);
    *reinterpret_cast<TUint *>(riffWav + 32) = Arch::LittleEndian2(blockAlign);
    *reinterpret_cast<TUint *>(riffWav + 34) = Arch::LittleEndian2(params.bitsPerSample);
    strncpy(reinterpret_cast<char *>(riffWav + 36), "data", 4);
    *reinterpret_cast<TUint *>(riffWav + 40) = Arch::LittleEndian4(subchunkTwoSize);

    //
    // output audio data (data members inherited from Protocol)
    //

    // XXX debugging only
    for (TByte *p = riffWav; p < riffWav + sizeof(riffWav); p += 4) {
        Log::Print("%02x  %02x  %02x  %02x    ", *(p + 0), *(p + 1), *(p + 2), *(p + 3));
        for (int i = 0; i < 4; ++i) {
            Log::Print("%c", isprint(*(p + i)) ? *(p + i) : '.');
        }
        Log::Print("\n");
    }

    return EProtocolErrorNotSupported;
}
