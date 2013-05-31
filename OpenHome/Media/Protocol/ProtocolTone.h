#ifndef HEADER_PIPELINE_PROTOCOL_TONE
#define HEADER_PIPELINE_PROTOCOL_TONE

#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>

namespace OpenHome {
namespace Media {

// audio parameters specifically for tone generation in RIFF-WAVE format
struct ToneParams
{
    TUint16 bitsPerSample;
    TUint   sampleRate;
    TUint   pitch;
    TUint16 numChannels;
    TUint   duration;
};

class ToneUriParser
{
public:
    ToneUriParser();

    // condition: given URI must live at least as long as parser instance
    // throws ToneUriParseError, UriError
    void Parse(const Brx& aUri);

    const ToneParams& Params() const;
    const Brx& Name() const;
private:
    ToneParams iParams;
    Brn iName;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_TONE
