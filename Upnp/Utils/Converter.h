#ifndef HEADER_CONVERTER
#define HEADER_CONVERTER

#include <ZappTypes.h>
#include <Buffer.h>
#include <Stream.h>

namespace Zapp {

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

} // namespace Zapp

#endif // HEADER_CONVERTER
