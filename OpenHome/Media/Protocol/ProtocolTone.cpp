#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Parser.h>

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
    // tone://WAVEFORM.wav?bitdepth=N&samplerate=M&pitch=HZ&channel=K&duration=T
    Uri uri(aUri);
    if (uri.Scheme() != Brn("tone")) {
        return ProtocolStreamResult::EProtocolErrorNotSupported;  // XXX
    }
    Log::Print("@@  ProtocolTone::Stream(): recognised scheme 'tone://'\n");  // XXX

    Log::Print("@@  ProtocolTone::Stream(): host = ");  Log::Print(uri.Host());  Log::Print("\n");  // XXX
    Log::Print("@@  ProtocolTone::Stream(): path = ");  Log::Print(uri.Path());  Log::Print("\n");  // XXX
    Log::Print("@@  ProtocolTone::Stream(): query = ");  Log::Print(uri.Query());  Log::Print("\n");  // XXX

    return ProtocolStreamResult::EProtocolErrorNotSupported;  // XXX
}
