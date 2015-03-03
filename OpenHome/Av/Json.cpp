#include <OpenHome/Av/Json.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Stream.h>


using namespace OpenHome;
using namespace Av;


// see RFC4627 - http://www.ietf.org/rfc/rfc4627.txt

const Brn Json::kEscapedDoubleQuote("\\\"");
const Brn Json::kEscapedBackslash("\\\\");
const Brn Json::kEscapedForwardSlash("\\/");
const Brn Json::kEscapedBackspace("\\b");
const Brn Json::kEscapedFormfeed("\\f");
const Brn Json::kEscapedNewline("\\n");
const Brn Json::kEscapedLinefeed("\\r");
const Brn Json::kEscapedTab("\\t");

void Json::Escape(IWriter& aWriter, const Brx& aValue)
{
    // FIXME - no support for multi-byte chars
    const TUint bytes = aValue.Bytes();
    for (TUint i=0; i<bytes; i++) {
        TByte ch = aValue[i];
        switch (ch)
        {
        case '\"':
            aWriter.Write(kEscapedDoubleQuote);
            break;
        case '\\':
            aWriter.Write(kEscapedBackslash);
            break;
        case '/':
            aWriter.Write(kEscapedForwardSlash);
            break;
        case '\b':
            aWriter.Write(kEscapedBackspace);
            break;
        case '\f':
            aWriter.Write(kEscapedFormfeed);
            break;
        case '\n':
            aWriter.Write(kEscapedNewline);
            break;
        case '\r':
            aWriter.Write(kEscapedLinefeed);
            break;
        case '\t':
            aWriter.Write(kEscapedTab);
            break;
        default:
            if (ch > 0x1F) {
                aWriter.Write(ch);
            }
            else {
                Bws<6> hexBuf("\\u00");
                Ascii::AppendHex(hexBuf, ch);
                aWriter.Write(hexBuf);
            }
            break;
        }
    }
}

void Json::Unescape(Bwx& aValue)
{
    TUint j = 0;
    const TUint bytes = aValue.Bytes();
    for (TUint i=0; i<bytes; i++) {
        TByte ch = aValue[i];
        if (ch != '\\') {
            aValue[j++] = ch;
        }
        else {
            if (++i == bytes) {
                THROW(JsonInvalid);
            }
            switch (aValue[i])
            {
            case '\"':
                aValue[j++] = '\"';
                break;
            case '\\':
                aValue[j++] = '\\';
                break;
            case '/':
                aValue[j++] = '/';
                break;
            case 'b':
                aValue[j++] = '\b';
                break;
            case 'f':
                aValue[j++] = '\f';
                break;
            case 'n':
                aValue[j++] = '\n';
                break;
            case 'r':
                aValue[j++] = '\r';
                break;
            case 't':
                aValue[j++] = '\t';
                break;
            case 'u':
            {
                if (i+4 >= bytes) {
                    THROW(JsonInvalid);
                }
                Brn hexBuf = aValue.Split(i+1, 4);
                i += 4;
                const TUint hex = Ascii::UintHex(hexBuf);
                if (hex > 0xFF) {
                    THROW(JsonUnsupported);
                }
                aValue[j++] = (TByte)hex;
            }
                break;
            default:
                THROW(JsonInvalid);
            }
        }
    }
    aValue.SetBytes(j);
}
