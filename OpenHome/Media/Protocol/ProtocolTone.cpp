#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>

#include <OpenHome/Private/Printer.h>  // XXX Log::Print()
#include <OpenHome/Media/Msg.h>  // XXX MsgFlush::kIdInvalid

#ifndef NDEBUG
    #define LOG_DBG(msg, val) \
        Log::Print("!!  ProtocolTone::Stream(): "); Log::Print(msg); Log::Print(": "); Log::Print(val); Log::Print("\n");
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
Protocol*
ProtocolFactory::NewTone(Environment& aEnv)
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

ProtocolStreamResult ProtocolTone::Stream(const Brx& aUri)
{
    // tone://WAVEFORM.wav?bitdepth=N&samplerate=M&pitch=HZ&channels=K&duration=T
    Uri uri(aUri);
    if (uri.Scheme() != Brn("tone")) {
        // quietly decline offer to handle other URL schemes; leave it to other protocol modules
        return EProtocolErrorNotSupported;
    }
    LOG_DBG("scheme", uri.Scheme())

    const Brx& waveForm(uri.Host());
    if ((waveForm != Brn("square.wav")) && (waveForm != Brn("sawtooth.wav"))) {
        LOG_DBG("unsupported waveform", uri.Host())
        return EProtocolErrorNotSupported;
    }

    if (uri.Path() != Brn("/")) {
        LOG_DBG("spurious path", uri.Path())
        return EProtocolStreamErrorUnrecoverable;
    }

    // XXX generalise query parsing into key/value string pairs?
    const Brx& query(uri.Query());
    if (!query.BeginsWith(Brn("?"))) {
        LOG_DBG("missing or malformed query", uri.Query())
        return EProtocolStreamErrorUnrecoverable;
    }

    Parser parser(query);
    parser.Forward(1);  // initial "?" already checked

    // initialising to illegal values to detect missing ones easily below
    TUint bitdepth = 0;
    TUint samplerate = 0;
    TUint pitch = 0;
    TUint channels = 0;
    TUint duration = 0;

    while (!parser.Finished()) {
        const Brn& keyVal = parser.Next('&');

        Parser kvParser(keyVal);
        const Brn& key = kvParser.Next('=');
        const Brn& val = kvParser.NextToEnd();

        if (key == Brn("bitdepth")) {
            if (bitdepth != 0) {
                LOG_DBG("duplicate parameter", "bitdepth")
                return EProtocolStreamErrorUnrecoverable;
            }
            bitdepth = Ascii::Int(val);
            if ((bitdepth != 8) && (bitdepth != 16) && (bitdepth != 24)) {
                LOG_DBG("invalid parameter value", keyVal)
                return EProtocolStreamErrorUnrecoverable;
            }
        } else if (key == Brn("samplerate")) {
            if (samplerate != 0) {
                LOG_DBG("duplicate parameter", "samplerate")
                return EProtocolStreamErrorUnrecoverable;
            }
            samplerate = Ascii::Int(val);
            switch (samplerate) {
                // from OpenHome/Media/Msg.cpp
                case 7350: case 14700: case 29400:
                case 8000: case 16000: case 32000:
                case 11025: case 22050: case 44100: case 88200: case 176400:
                case 12000: case 24000: case 48000: case 96000: case 192000:
                    break;
                default:
                    LOG_DBG("invalid parameter value", keyVal)
                    return EProtocolStreamErrorUnrecoverable;
            }
        } else if (key == Brn("pitch")) {  // [Hz]
            if (pitch != 0) {
                LOG_DBG("duplicate parameter", "pitch")
                return EProtocolStreamErrorUnrecoverable;
            }
            pitch = Ascii::Int(val);
            // XXX no upper limit, since not necessarily intended for human hearing
            if (! (0 < pitch)) {
                LOG_DBG("invalid parameter value", keyVal)
                return EProtocolStreamErrorUnrecoverable;
            }
        } else if (key == Brn("channels")) {
            if (channels != 0) {
                LOG_DBG("duplicate parameter", "channels")
                return EProtocolStreamErrorUnrecoverable;
            }
            // 1 ... 8 (in practice no more than 7.1 surround sound)
            channels = Ascii::Int(val);
            if (! ((0 < channels) && (channels <= 8))) {
                LOG_DBG("invalid parameter value", keyVal)
                return EProtocolStreamErrorUnrecoverable;
            }
        } else if (key == Brn("duration")) {  // [s]
            if (duration != 0) {
                LOG_DBG("duplicate parameter", "duration")
                return EProtocolStreamErrorUnrecoverable;
            }
            // 1 ... 900 (i.e. 15min): arbitrary limit guaranteed to avoid integer overflow in calculations
            duration = Ascii::Int(val);
            if (! ((0 < duration) && (duration <= 900))) {
                LOG_DBG("invalid parameter value", keyVal)
                return EProtocolStreamErrorUnrecoverable;
            }
        } else {
            LOG_DBG("unrecognised keyword", key)
            return EProtocolStreamErrorUnrecoverable;
        }
    }

    if (bitdepth == 0) {
        LOG_DBG("missing parameter", "bitdepth")
        return EProtocolStreamErrorUnrecoverable;
    } else if (samplerate == 0) {
        LOG_DBG("missing parameter", "samplerate")
        return EProtocolStreamErrorUnrecoverable;
    } else if (pitch == 0) {
        LOG_DBG("missing parameter", "pitch")
        return EProtocolStreamErrorUnrecoverable;
    } else if (channels == 0) {
        LOG_DBG("missing parameter", "channels")
        return EProtocolStreamErrorUnrecoverable;
    } else if (duration == 0) {
        LOG_DBG("missing parameter", "duration")
        return EProtocolStreamErrorUnrecoverable;
    }

    LOG_DBG("successfully parsed all parameters", "")
    Log::Print("@@  bitdepth =   %6u\n", bitdepth);
    Log::Print("@@  samplerate = %6u\n", samplerate);
    Log::Print("@@  pitch =      %6u\n", pitch);
    Log::Print("@@  channels =   %6u\n", channels);
    Log::Print("@@  duration =   %6u\n", duration);

    return EProtocolErrorNotSupported;
}
