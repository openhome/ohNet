#ifndef HEADER_JSON
#define HEADER_JSON

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>

EXCEPTION(JsonInvalid);
EXCEPTION(JsonUnsupported);

namespace OpenHome {
    class IWriter;
namespace Av{

class Json
{
    static const Brn kEscapedDoubleQuote;
    static const Brn kEscapedBackslash;
    static const Brn kEscapedForwardSlash;
    static const Brn kEscapedBackspace;
    static const Brn kEscapedFormfeed;
    static const Brn kEscapedNewline;
    static const Brn kEscapedLinefeed;
    static const Brn kEscapedTab;
public:
    static void Escape(IWriter& aWriter, const Brx& aValue);
    static void Unescape(Bwx& aValue); // converts in place
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_JSON
