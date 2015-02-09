#include <OpenHome/Av/Json.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Stream.h>


using namespace OpenHome;
using namespace Av;

// JsonStringSanitiser

JsonStringSanitiser::JsonStringSanitiser(IWriter& aWriter)
    : iWriter(aWriter)
{
}

void JsonStringSanitiser::Write(TByte aValue)
{
    WriteSanitised(aValue);
}

void JsonStringSanitiser::Write(const Brx& aBuffer)
{
    iWriter.Write(Brn("\""));
    for (TUint i=0; i<aBuffer.Bytes(); i++) {
        WriteSanitised(aBuffer[i]);
    }
    iWriter.Write(Brn("\""));
}


void JsonStringSanitiser::WriteFlush()
{
    iWriter.WriteFlush();
}

void JsonStringSanitiser::WriteSanitised(TByte aByte)
{
    // According to RFC4627 (http://www.ietf.org/rfc/rfc4627.txt),
    // quotation mark ("), reverse solidus (/), or any control character
    // (U+0000 through U+001F) must be escaped.
    //
    // The char ranges that aren't required to be escaped are:
    // unescaped = %x20-21 / %x23-5B / %x5D-10FFFF.
    // Therefore, the char ranges that must be escaped are:
    // escaped = %x00-1F / %x22 / %x5C.

    // JSON allows compact escaping for certain chars.
    // Try identify such chars first.
    switch (aByte)
    {
    case '"':
        iWriter.Write(Brn("\\\""));     // %x22
        return;
    case '\\':
        iWriter.Write(Brn("\\\\"));     // %x5C
        return;
    case '/':
        iWriter.Write(Brn("\\/"));
        return;
    case '\b':
        iWriter.Write(Brn("\\b"));
        return;
    case '\f':
        iWriter.Write(Brn("\\f"));
        return;
    case '\n':
        iWriter.Write(Brn("\\n"));
        return;
    case '\r':
        iWriter.Write(Brn("\\r"));
        return;
    case '\t':
        iWriter.Write(Brn("\\t"));
        return;
    default:
        // Break out of switch statement.
        break;
    }

    // Haven't identified a char where a compact escape sequence exists.
    // Remaining chars that must be escaped exist in range %x00-1F.
    // These must be represented as "\uXXXX", where X is a hex digit.
    if (aByte >= 0x00 && aByte <= 0x1F) {
        static const TUint kPrefixBytes = 2; // "\u"
        static const TUint kHexDigitsReq = 4;
        Bws<kPrefixBytes+kHexDigitsReq> hexBuf("\\u");
        if (aByte <= 9) {
            hexBuf.Append("000");
        }
        else {
            hexBuf.Append("00");
        }
        Ascii::AppendDec(hexBuf, aByte);
        iWriter.Write(hexBuf);
        return;
    }

    // Haven't found a char that must be escaped. Safe to output as-is.
    iWriter.Write(aByte);
}
