#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Ascii.h>

#include <OpenHome/Private/Printer.h>  // XXX Log::Print()
#include <OpenHome/Media/Msg.h>  // XXX MsgFlush::kIdInvalid


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

TUint
ProtocolTone::TryStop(TUint aTrackId, TUint aStreamId)
{
    return MsgFlush::kIdInvalid;  // XXX
}

// TUint ProtocolTone::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset) { }

ProtocolStreamResult
ProtocolTone::Stream(const Brx& aUri)
{
    // tone://WAVEFORM.wav?bitdepth=N&samplerate=M&pitch=HZ&channels=K&duration=T
    Uri uri(aUri);
    if (uri.Scheme() != Brn("tone")) {
        return ProtocolStreamResult::EProtocolErrorNotSupported;  // XXX
    }
    Log::Print("@@  ProtocolTone::Stream(): scheme 'tone://'\n");  // XXX

    // Log::Print("@@  ProtocolTone::Stream(): host = ");  Log::Print(uri.Host());  Log::Print("\n");  // XXX
    const Brx& waveForm(uri.Host());
    if ((waveForm != Brn("square.wav")) && (waveForm != Brn("sawtooth.wav"))) {
        Log::Print("!!  ProtocolTone::Stream(): host = ");  Log::Print(uri.Host());  Log::Print("\n");  // XXX
        return ProtocolStreamResult::EProtocolErrorNotSupported;  // XXX
    }

    // Log::Print("@@  ProtocolTone::Stream(): path = ");  Log::Print(uri.Path());  Log::Print("\n");  // XXX
    if (uri.Path() != Brn("/")) {
        Log::Print("!!  ProtocolTone::Stream(): path = ");  Log::Print(uri.Path());  Log::Print("\n");  // XXX
        return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
    }

    // XXX generalise query parsing into key/value string pairs?
    const Brx& query(uri.Query());
    if (!query.BeginsWith(Brn("?"))) {
        Log::Print("!!  ProtocolTone::Stream(): query = ");  Log::Print(uri.Query());  Log::Print("\n");  // XXX
        return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
    }

    // Log::Print("@@  ProtocolTone::Stream(): query = ");  Log::Print(uri.Query());  Log::Print("\n");  // XXX
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
        // Log::Print("@@  key=value: ");  Log::Print(keyVal);  Log::Print("\n");  // XXX

        Parser kvParser(keyVal);
        const Brn& key = kvParser.Next('=');
        const Brn& val = kvParser.NextToEnd();

        if (key == Brn("bitdepth")) {
            if (bitdepth != 0) {
                Log::Print("!!  ProtocolTone::Stream(): duplicate parameter: bitdepth\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
            bitdepth = Ascii::Int(val);
            if ((bitdepth != 8) && (bitdepth != 16) && (bitdepth != 24)) {
                Log::Print("!!  ProtocolTone::Stream(): invalid parameter value: ");  Log::Print(keyVal);  Log::Print("\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
        } else if (key == Brn("samplerate")) {
            if (samplerate != 0) {
                Log::Print("!!  ProtocolTone::Stream(): duplicate parameter: samplerate\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
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
                    Log::Print("!!  ProtocolTone::Stream(): invalid parameter value: ");  Log::Print(keyVal);  Log::Print("\n");  // XXX
                    return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
        } else if (key == Brn("pitch")) {  // [Hz]
            if (pitch != 0) {
                Log::Print("!!  ProtocolTone::Stream(): duplicate parameter: pitch\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
            pitch = Ascii::Int(val);
            // XXX no upper limit, since not necessarily intended for human hearing
            if (! (0 < pitch)) {
                Log::Print("!!  ProtocolTone::Stream(): invalid parameter value: ");  Log::Print(keyVal);  Log::Print("\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
        } else if (key == Brn("channels")) {
            if (channels != 0) {
                Log::Print("!!  ProtocolTone::Stream(): duplicate parameter: channels\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
            // 1 ... 8 (in practice no more than 7.1 surround sound)
            channels = Ascii::Int(val);
            if (! ((0 < channels) && (channels <= 8))) {
                Log::Print("!!  ProtocolTone::Stream(): invalid parameter value: ");  Log::Print(keyVal);  Log::Print("\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
        } else if (key == Brn("duration")) {  // [s]
            if (duration != 0) {
                Log::Print("!!  ProtocolTone::Stream(): duplicate parameter: duration\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
            // 1 ... 900 (i.e. 15min): arbitrary limit guaranteed to avoid integer overflow in calculations
            duration = Ascii::Int(val);
            if (! ((0 < duration) && (duration <= 900))) {
                Log::Print("!!  ProtocolTone::Stream(): invalid parameter value: ");  Log::Print(keyVal);  Log::Print("\n");  // XXX
                return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
            }
        } else {
            Log::Print("!!  ProtocolTone::Stream(): unrecognised keyword: ");  Log::Print(key);  Log::Print("\n");  // XXX
            return ProtocolStreamResult::EProtocolStreamErrorUnrecoverable;  // XXX
        }
    }

    if (bitdepth == 0) {
        Log::Print("!!  ProtocolTone::Stream(): missing parameter or illegal value: bitdepth\n");  // XXX
    } else if (samplerate == 0) {
        Log::Print("!!  ProtocolTone::Stream(): missing parameter or illegal value: samplerate\n");  // XXX
    } else if (pitch == 0) {
        Log::Print("!!  ProtocolTone::Stream(): missing parameter or illegal value: pitch\n");  // XXX
    } else if (channels == 0) {
        Log::Print("!!  ProtocolTone::Stream(): missing parameter or illegal value: channels\n");  // XXX
    } else if (duration == 0) {
        Log::Print("!!  ProtocolTone::Stream(): missing parameter or illegal value: duration\n");  // XXX
    }

    Log::Print("@@  ProtocolTone::Stream(): successfully parsed all parameters\n");  // XXX
    Log::Print("@@  bitdepth =   %6u\n", bitdepth);  // XXX
    Log::Print("@@  samplerate = %6u\n", samplerate);  // XXX
    Log::Print("@@  pitch =      %6u\n", pitch);  // XXX
    Log::Print("@@  channels =   %6u\n", channels);  // XXX
    Log::Print("@@  duration =   %6u\n", duration);  // XXX

    return ProtocolStreamResult::EProtocolErrorNotSupported;  // XXX
}
