#include <OpenHome/Private/Ascii.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

using namespace OpenHome;

const Brn kAsciiNewline("\r\n");
const Brn kAsciiHexPrefix("0x");

TBool Ascii::IsHex(TChar aValue)
{
    if (IsDigit(aValue)) {
        return (true);
    }
    if (aValue <= 'F' && aValue >= 'A') {
        return (true);
    }
    if (aValue <= 'f' && aValue >= 'a') {
        return (true);
    }

    return (false);
}

TBool Ascii::IsDigit(TChar aValue)
{
    return (aValue <= '9' && aValue >= '0');
}

TBool Ascii::IsWhitespace(TChar aValue)
{
    bool whitespace = (aValue <= ' ');
#if CHAR_MIN < 0
    if (whitespace) {
        whitespace = (aValue >= 0);
    }
#endif
    return whitespace;
}

TBool Ascii::IsLineEnding(TChar aValue)
{
    return ( (aValue == '\r') || (aValue == '\n') );
}

TBool Ascii::IsAlphabetic(TChar aValue)
{
    return (IsUpperCase(aValue) || IsLowerCase(aValue));
}

TBool Ascii::IsUpperCase(TChar aValue)
{
    return (aValue <= 'Z' && aValue >= 'A');
}

TBool Ascii::IsLowerCase(TChar aValue)
{
    return (aValue <= 'z' && aValue >= 'a');
}

TChar Ascii::ToLowerCase(TChar aValue)
{
    return (IsUpperCase(aValue) ? aValue | 0x20 : aValue);
}

TChar Ascii::ToUpperCase(TChar aValue)
{
    return (IsLowerCase(aValue) ? aValue & ~0x20 : aValue);
}

TBool Ascii::CaseInsensitiveEquals(TChar aValue1, TChar aValue2)
{
    if (IsAlphabetic(aValue1)) {
        return ((aValue1 | 0x20) == (aValue2 | 0x20));
    }
    return (aValue1 == aValue2);
}

TBool Ascii::CaseInsensitiveEquals(const Brx& aBuffer1, const Brx& aBuffer2)
{
    TUint bytes = aBuffer1.Bytes();
    if(aBuffer2.Bytes() != bytes) {
        return (false);
    }
    for (TUint i = 0; i < bytes; i++) {
        if (!CaseInsensitiveEquals(aBuffer1[i], aBuffer2[i])) {
            return (false);
        }
    }
    return (true);
}

/// Return the hex character coresponding to the value passed in.
/// The value passed in should be from 0 to 15.

TChar Ascii::HexChar(TUint aValue)
{
    if (aValue < 10) {
        return (TChar)('0' + aValue);
    }
    if (aValue < 16) {
        return (TChar)('a' + aValue - 10);
    }
    THROW(AsciiError);
}

/// Return value coresponding to the hex character passed in.
/// The value passed in should be from '0' to '9' or 'A' to 'F'
/// or 'a' to 'f'

TUint Ascii::HexValue(TChar aValue)
{
    TChar value = ToUpperCase(aValue);
    if (IsDigit(value)) {
        return (value - '0');
    }
    if (IsHex(value)) {
        return (value - 'A' + 10);
    }
    THROW(AsciiError);
}

/// Return the hex character coresponding to the value passed in.
/// The value passed in should be from 0 to 9.

TChar Ascii::DecChar(TUint aValue)
{
    if (aValue < 10) {
        return (TChar)('0' + aValue);
    }
    THROW(AsciiError);
}

/// Return value coresponding to the hex character passed in.
/// The value passed in should be from '0' to '9'

TUint Ascii::DecValue(TChar aValue)
{
    if (IsDigit(aValue)) {
        return (aValue - '0');
    }
    THROW(AsciiError);
}


TUint Ascii::AppendDec(Bwx& aBuffer, TUint8 aValue)
{
    return AppendDec(aBuffer, (TUint)aValue);
}

TUint Ascii::AppendDec(Bwx& aBuffer, TInt8 aValue)
{
    return AppendDec(aBuffer, (TInt)aValue);
}

TUint Ascii::AppendDec(Bwx& aBuffer, TUint16 aValue)
{
    return AppendDec(aBuffer, (TUint)aValue);
}

TUint Ascii::AppendDec(Bwx& aBuffer, TInt16 aValue)
{
    return AppendDec(aBuffer, (TInt)aValue);
}

TUint Ascii::AppendDec(Bwx& aBuffer, TBool aValue)
{
    return AppendDec(aBuffer, (TInt)(aValue ? 1 : 0));
}

/// Convert the supplied value to an decimal string and append it to
/// the specified buffer.

TUint Ascii::AppendDec(Bwx& aBuffer, TInt aValue)
{
    Bws<10> reversed; // Maximum value requires 10 digits

    if (aValue == 0) {
        aBuffer.Append('0');
        return (1);
    }

    TUint extra = 0;

    if (aValue < 0) {
        aBuffer.Append('-');
        extra++;
    }

    while(aValue != 0) {
        reversed.Append((TChar)('0' + abs(aValue % 10)));
        aValue = aValue / 10;
    }

    for (TUint i = reversed.Bytes(); i > 0; i--) {
        aBuffer.Append(reversed[i - 1]);
    }

    return (reversed.Bytes() + extra);
}

/// Convert the supplied value to an decimal string and append it to
/// the specified buffer.

TUint Ascii::AppendDec(Bwx& aBuffer, TUint aValue)
{
    Bws<10> reversed; // Maximum value requires 10 digits

    if (aValue == 0) {
        aBuffer.Append('0');
        return (1);
    }

    while(aValue > 0) {
        reversed.Append((TChar)('0' + aValue % 10));
        aValue = aValue / 10;
    }

    for (TUint i = reversed.Bytes(); i > 0; i--) {
        aBuffer.Append(reversed[i - 1]);
    }

    return (reversed.Bytes());
}

/// Convert the supplied value to an decimal string and append it to
/// the specified buffer.

TUint Ascii::AppendDec(Bwx& aBuffer, TInt64 aValue)
{
    Bws<20> reversed; // Maximum value requires 20 digits

    if (aValue == 0) {
        aBuffer.Append('0');
        return (1);
    }

    TUint extra = 0;

    if (aValue < 0) {
        aBuffer.Append('-');
        extra++;
    }

    while(aValue != 0) {
        reversed.Append((TChar)('0' + abs((TInt)(aValue % 10))));
        aValue = aValue / 10;
    }

    for (TUint i = reversed.Bytes(); i > 0; i--) {
        aBuffer.Append(reversed[i - 1]);
    }

    return (reversed.Bytes() + extra);
}

/// Convert the supplied value to an decimal string and append it to
/// the specified buffer.

TUint Ascii::AppendDec(Bwx& aBuffer, TUint64 aValue)
{
    Bws<20> reversed; // Maximum value requires 20 digits

    if (aValue == 0) {
        aBuffer.Append('0');
        return (1);
    }

    while(aValue > 0) {
        reversed.Append((TChar)('0' + aValue % 10));
        aValue = aValue / 10;
    }

    for (TUint i = reversed.Bytes(); i > 0; i--) {
        aBuffer.Append(reversed[i - 1]);
    }

    return (reversed.Bytes());
}


/// Convert the supplied value to a hex string and append it to
/// the specified buffer.

TUint Ascii::AppendHex(Bwx& aBuffer, TUint aValue)
{
    aBuffer.Append(HexChar((aValue >> 28) & 0xf));
    aBuffer.Append(HexChar((aValue >> 24) & 0xf));
    aBuffer.Append(HexChar((aValue >> 20) & 0xf));
    aBuffer.Append(HexChar((aValue >> 16) & 0xf));
    aBuffer.Append(HexChar((aValue >> 12) & 0xf));
    aBuffer.Append(HexChar((aValue >>  8) & 0xf));
    aBuffer.Append(HexChar((aValue >>  4) & 0xf));
    aBuffer.Append(HexChar((aValue >>  0) & 0xf));
    return(8);
}

/// Convert the supplied value to a hex string and append it to
/// the specified buffer, ignoring leading zeros.

TUint Ascii::AppendHexTrim(Bwx& aBuffer, TUint aValue)
{
    TUint digits;
    TUint value = aValue;

    // remove leading zeros
        
    for (digits = 8; digits > 1; digits--) {
        if (value >> 28 > 0) {
            break;
        }
        value = value << 4;
    }

    TUint count = digits;
        
    while (count--) {
        aBuffer.Append(HexChar(value >> 28));
        value = value << 4;
    }

    return(digits);
}

/// Convert the supplied value to a hex string and append it to
/// the specified buffer.

TUint Ascii::AppendHex(Bwx& aBuffer, TByte aValue)
{
    aBuffer.Append(HexChar((aValue >> 4) & 0xf));
    aBuffer.Append(HexChar((aValue >> 0) & 0xf));
    return(2);
}

TUint Ascii::AppendHex(Bwx& aBuffer, const Brx& aValue)
{
    TUint length = aValue.Bytes();
    TUint i = 0;
    for(i = 0; i < length; ++i)
    {
        AppendHexPrefix(aBuffer);
        AppendHex(aBuffer, aValue[i]);
        if( i != length - 1){ aBuffer.Append(Brn(" "));}
    }
    return ((length * 5) - 1);
}
/// Append the hex prefix to the specified buffer.

TUint Ascii::AppendHexPrefix(Bwx& aBuffer)
{
    aBuffer.Append(kAsciiHexPrefix);
    return(2);
}

TBool Ascii::Contains(const Brx& aBuffer, TChar aValue)
{
    for (TUint i = 0; i < aBuffer.Bytes(); i++) {
        if (aBuffer[i] == aValue) {
            return (true);
        }
    }
    return (false);
}

TBool Ascii::Contains(const Brx& aBuffer, const Brx& aValue)
{
    TInt bytes = aBuffer.Bytes() - aValue.Bytes();
    for (TInt i=0; i<=bytes; i++) {
        if (strncmp((char*)&aBuffer[i], (char*)&aValue[0], aValue.Bytes()) == 0) {
            return true;
        }
    }
    return false;
}

TBool Ascii::ContainsWhitespace(const Brx& aBuffer)
{
    for (TUint i = 0; i < aBuffer.Bytes(); i++) {
        if (IsWhitespace(aBuffer[i])) {
            return (true);
        }
    }
    return (false);
}

TUint Ascii::IndexOf(const Brx& aBuffer, TChar aValue)
{
    // returns index of aValue (or aBuffer.Bytes() if not in)
    TUint bytes = aBuffer.Bytes();
    const TByte* ptr = aBuffer.Ptr();
    for (TUint i=0 ; i<bytes ; i++) {
        if (ptr[i] == aValue) {
            return i;
        }
    }
    return bytes;
}

void Ascii::Substitute(Bwx& aBuffer, TChar aSearch, TChar aReplace)
{
    // returns index of aValue (or aBuffer.Bytes() if not in)
    TUint bytes = aBuffer.Bytes();
    const TByte* ptr = aBuffer.Ptr();
    for (TUint i=0 ; i<bytes ; i++) {
        if (ptr[i] == aSearch) {
            aBuffer[i] = aReplace;
        }
    }
}

Brn Ascii::Trim(const Brx& aBuffer)
{
    TUint start = 0;
    TUint bytes = aBuffer.Bytes();

    for (TUint i = 0; i < bytes; i++) {
        if (!IsWhitespace(aBuffer[start])) {
            break;
        }
        start++;
    }

    if (start == bytes) {
        return (Brn::Empty());
    }

    TUint end = bytes;

    while (IsWhitespace(aBuffer[end - 1])) {
        end--;
    }

    return (aBuffer.Split(start, end - start));
}

/* |INT32_MIN| and |INT64_MIN| - one larger than the matching MAX, so a negative
   literal has a different limit from a positive one. */
static const TUint   kIntMinMagnitude   = 2147483648u;
static const TUint64 kInt64MinMagnitude = 9223372036854775808ull;

/* Accumulate one digit into aValue, throwing AsciiError instead of overflowing.
   aLimit is the largest magnitude the caller can represent.  Previously these
   parsers accumulated into a signed type with no check at all, which is
   undefined behaviour and silently returned wrapped values for over-long
   input (e.g. an attacker-supplied Content-Length). */
template<typename T>
static void AccumulateDigit(T& aValue, TUint aDigit, T aBase, T aLimit)
{
    if (aValue > (aLimit - aDigit) / aBase) {
        THROW(AsciiError);
    }
    aValue = aValue * aBase + aDigit;
}

TInt Ascii::Int(const Brx& aBuffer)
{
    Brn trim = Trim(aBuffer);
    if (trim.Bytes() == 0) {
        THROW(AsciiError);  // empty string
    }

    TBool negative = false;

    TUint magnitude = 0;

    for (TUint i = 0; i < trim.Bytes(); i++)
    {
        TByte c = trim[i];

        if (c == '-') { // One negative sign allowed at start
            if (i || negative || trim.Bytes() == 1) {
                THROW(AsciiError);
            }
            negative = true;
            continue;
        }

        if (!IsDigit(c)) {
            THROW(AsciiError);
        }

        // the sign is fixed by the first character, so the limit is known here
        AccumulateDigit<TUint>(magnitude, DecValue(c), 10, negative? kIntMinMagnitude : (TUint)INT32_MAX);
    }

    if (negative) {
        return (magnitude == kIntMinMagnitude)? INT32_MIN : -(TInt)magnitude;
    }
    return (TInt)magnitude;
}

TUint Ascii::Uint(const Brx& aBuffer)
{
    Brn trim = Trim(aBuffer);
    if (trim.Bytes() == 0) {
        THROW(AsciiError);  // empty string
    }

    TUint value = 0;

    for (TUint i = 0; i < trim.Bytes(); i++)
    {
        TByte c = trim[i];

        if (!IsDigit(c)) {
            THROW(AsciiError);
        }

        AccumulateDigit<TUint>(value, DecValue(c), 10, UINT32_MAX);
    }

    return (value);
}

TInt64 Ascii::Int64(const Brx& aBuffer)
{
    Brn trim = Trim(aBuffer);
    if (trim.Bytes() == 0) {
        THROW(AsciiError);  // empty string
    }

    TBool negative = false;

    TUint64 magnitude = 0;

    for (TUint i = 0; i < trim.Bytes(); i++)
    {
        TByte c = trim[i];

        if (c == '-') { // One negative sign allowed at start
            if (i || negative || trim.Bytes() == 1) {
                THROW(AsciiError);
            }
            negative = true;
            continue;
        }

        if (!IsDigit(c)) {
            THROW(AsciiError);
        }

        AccumulateDigit<TUint64>(magnitude, DecValue(c), 10, negative? kInt64MinMagnitude : (TUint64)INT64_MAX);
    }

    if (negative) {
        return (magnitude == kInt64MinMagnitude)? INT64_MIN : -(TInt64)magnitude;
    }
    return (TInt64)magnitude;
}

TUint64 Ascii::Uint64(const Brx& aBuffer)
{
    Brn trim = Trim(aBuffer);
    if (trim.Bytes() == 0) {
        THROW(AsciiError);  // empty string
    }

    TUint64 value = 0;

    for (TUint i = 0; i < trim.Bytes(); i++)
    {
        TByte c = trim[i];

        if (!IsDigit(c)) {
            THROW(AsciiError);
        }

        AccumulateDigit<TUint64>(value, DecValue(c), 10, UINT64_MAX);
    }

    return (value);
}

TUint Ascii::UintHex(const Brx& aBuffer)
{
    Brn trim = Trim(aBuffer);
    if (trim.Bytes() == 0) {
        THROW(AsciiError);  // empty string
    }

    if (aBuffer.Bytes() > 8) {
        THROW(AsciiError);  // clearly too long
    }

    TUint val = 0;
    for (TUint i=0; i<trim.Bytes(); i++) {
        TByte c = trim[i];
        if (!Ascii::IsHex(c)) {
            THROW(AsciiError);
        }
        AccumulateDigit<TUint>(val, Ascii::HexValue(c), 16, UINT32_MAX);
    }

    return val;
}
// Stream classes (WriterAscii)

WriterAscii::WriterAscii(IWriter& aWriter)
    : iWriter(aWriter)
{
}

void WriterAscii::WriteSpace()
{
    Write(Ascii::kSp);
}

void WriterAscii::WriteNewline()
{
    Write(kAsciiNewline);
}

void WriterAscii::WriteTab()
{
    Write(Ascii::kHt);
}

void WriterAscii::WriteInt(TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> value;
    Ascii::AppendDec(value, aValue);
    Write(value);
}

void WriterAscii::WriteIntPadded(TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> value;
    value.SetBytes(Ascii::kMaxIntStringBytes);
    value.Fill(Ascii::kSp);
    value.SetBytes(0);
    Ascii::AppendDec(value, aValue);
    value.SetBytes(Ascii::kMaxIntStringBytes);
    Write(value);
}

void WriterAscii::WriteUint(TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> value;
    Ascii::AppendDec(value, aValue);
    Write(value);
}

void WriterAscii::WriteUintPadded(TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> value;
    value.SetBytes(Ascii::kMaxUintStringBytes);
    value.Fill(Ascii::kSp);
    value.SetBytes(0);
    Ascii::AppendDec(value, aValue);
    value.SetBytes(Ascii::kMaxUintStringBytes);
    Write(value);
}

void WriterAscii::WriteInt64(TInt64 aValue)
{
    Bws<Ascii::kMaxInt64StringBytes> value;
    Ascii::AppendDec(value, aValue);
    Write(value);
}

void WriterAscii::WriteUint64(TUint64 aValue)
{
    Bws<Ascii::kMaxUint64StringBytes> value;
    Ascii::AppendDec(value, aValue);
    Write(value);
}

void WriterAscii::WriteHex(TUint aValue)
{
    Bws<Ascii::kMaxUintHexStringBytes> value;
    Ascii::AppendHex(value, aValue);
    Write(value);
}

void WriterAscii::WriteHex(TByte aValue)
{
    Bws<Ascii::kMaxByteHexStringBytes> value;
    Ascii::AppendHex(value, aValue);
    Write(value);
}

void WriterAscii::WriteHexPrefix()
{
    Write(kAsciiHexPrefix);
}

void WriterAscii::Write(TByte aValue)
{
    iWriter.Write(aValue);
}

void WriterAscii::Write(const Brx& aBuffer)
{
    iWriter.Write(aBuffer);
}

void WriterAscii::WriteFlush()
{
    iWriter.WriteFlush();
}

// Static functions

void OpenHome::Ascii::StreamWriteUint(IWriter& aStream, TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> value;
    Ascii::AppendDec(value, aValue);
    aStream.Write(value);
}

void OpenHome::Ascii::StreamWriteInt(IWriter& aStream, TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> value;
    Ascii::AppendDec(value, aValue);
    aStream.Write(value);
}
