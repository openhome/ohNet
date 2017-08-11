#ifndef HEADER_CONVERTER
#define HEADER_CONVERTER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {

/**
 * Utilities for converting to/from base64 and (un)escaping XML
 */
class Converter
{
public:
    static void ToBase64(IWriter& aWriter, const Brx& aValue);
    static void FromBase64(Bwx& aValue); // Converts in place
    static void ToXmlEscaped(IWriter& aWriter, const Brx& aValue);
    static void FromXmlEscaped(Bwx& aValue); // Converts in place
    static TUint64 BeUint64At(const Brx& aBuf, TUint aIndex);
    static TUint32 BeUint32At(const Brx& aBuf, TUint aIndex);
    static TUint16 BeUint16At(const Brx& aBuf, TUint aIndex);
    static TUint32 LeUint32At(const Brx& aBuf, TUint aIndex);
    static TUint16 LeUint16At(const Brx& aBuf, TUint aIndex);
    static void ToUtf8(TUint aCodePoint, IWriter& aWriter);
    static void ToUtf8(TUint aCodePoint, Bwx& aBuf);
private:
    static void ToXmlEscaped(IWriter& aWriter, TByte aValue);
    static TBool IsMultiByteChar(TByte aChar, TUint& aBytes);
};

} // namespace OpenHome

#endif // HEADER_CONVERTER
