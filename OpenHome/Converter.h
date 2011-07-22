#ifndef HEADER_CONVERTER
#define HEADER_CONVERTER

#include <OpenHome/OhNetTypes.h>
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
    static void ToXmlEscaped(IWriter& aWriter, TByte aValue);
    static void ToXmlEscaped(IWriter& aWriter, const Brx& aValue);

    /**
     * Conversion in place
     */
    static void FromBase64(Bwx& aValue);

    /**
     * Conversion in place
     */
    static void FromXmlEscaped(Bwx& aValue);
};

} // namespace OpenHome

#endif // HEADER_CONVERTER
