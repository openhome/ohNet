#ifndef HEADER_ASCII_ASCII
#define HEADER_ASCII_ASCII

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>

//     0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
// 0  NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI
// 1  DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US
// 2   SP  !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /
// 3   0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?
// 4   @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O
// 5   P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _
// 6   `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o
// 7   p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~ DEL


EXCEPTION(AsciiError)

namespace OpenHome {

class Ascii
{
public:
    static const TByte kNul = 0x00;
    static const TByte kSoh = 0x01;
    static const TByte kStx = 0x02;
    static const TByte kEtx = 0x03;
    static const TByte kEot = 0x04;
    static const TByte kEnq = 0x05;
    static const TByte kAck = 0x06;
    static const TByte kBel = 0x07;
    static const TByte kBs  = 0x08;
    static const TByte kHt =  0x09;
    static const TByte kLf  = 0x0a;
    static const TByte kVt  = 0x0b;
    static const TByte kFf  = 0x0c;
    static const TByte kCr  = 0x0d;
    static const TByte kSo  = 0x0e;
    static const TByte kSi  = 0x0f;

    static const TByte kDle = 0x10;
    static const TByte kDc1 = 0x11;
    static const TByte kDc2 = 0x12;
    static const TByte kDc3 = 0x13;
    static const TByte kDc4 = 0x14;
    static const TByte kNak = 0x15;
    static const TByte kSyn = 0x16;
    static const TByte kEtb = 0x17;
    static const TByte kCan = 0x18;
    static const TByte kEm  = 0x19;
    static const TByte kSub = 0x1a;
    static const TByte kEsc = 0x1b;
    static const TByte kFs  = 0x1c;
    static const TByte kGs  = 0x1d;
    static const TByte kRs  = 0x1e;
    static const TByte kUs  = 0x1f;

    static const TByte kSp  = 0x20;
    static const TByte kDel = 0x7f;

    static const TUint kMaxIntStringBytes = 11;
    static const TUint kMaxUintStringBytes = 10;
    static const TUint kMaxInt64StringBytes = 20;
    static const TUint kMaxUint64StringBytes = 20;
    static const TUint kMaxUintHexStringBytes = 8;
    static const TUint kMaxByteHexStringBytes = 2;
public:
    static TBool IsHex(TChar aValue);
    static TBool IsDigit(TChar aValue);
    static TBool IsWhitespace(TChar aValue);
    static TBool IsLineEnding(TChar aValue);
    static TBool IsAlphabetic(TChar aValue);
    static TBool IsUpperCase(TChar aValue);
    static TBool IsLowerCase(TChar aValue);
    static TChar ToUpperCase(TChar aValue);
    static TChar ToLowerCase(TChar aValue);

    static TChar HexChar(TUint aValue);
    static TUint HexValue(TChar aValue);
    static TChar DecChar(TUint aValue);
    static TUint DecValue(TChar aValue);

    static TBool CaseInsensitiveEquals(TChar aValue1, TChar aValue2);
    static TBool CaseInsensitiveEquals(const Brx& aBuffer1, const Brx& aBuffer2);

    static TUint AppendDec(Bwx& aBuffer, TUint8 aValue);
    static TUint AppendDec(Bwx& aBuffer, TInt8 aValue);
    static TUint AppendDec(Bwx& aBuffer, TUint16 aValue);
    static TUint AppendDec(Bwx& aBuffer, TInt16 aValue);
    static TUint AppendDec(Bwx& aBuffer, TInt aValue);
    static TUint AppendDec(Bwx& aBuffer, TUint aValue);
    static TUint AppendDec(Bwx& aBuffer, TInt64 aValue);
    static TUint AppendDec(Bwx& aBuffer, TUint64 aValue);
    static TUint AppendDec(Bwx& aBuffer, TBool aValue);
    static TUint AppendHex(Bwx& aBuffer, TUint aValue);
    static TUint AppendHex(Bwx& aBuffer, TByte aValue);
    static TUint AppendHex(Bwx& aBuffer, const Brx& aValue); //where aBuf is atleast 5x the size of the aValue to be converted.
    static TUint AppendHexTrim(Bwx& aBuffer, TUint aValue);
    static TUint AppendHexPrefix(Bwx& aBuffer);

    static TBool ContainsWhitespace(const Brx& aBuffer);
    static TBool Contains(const Brx& aBuffer, TChar aValue);
    static TBool Contains(const Brx& aBuffer, const Brx& aValue);
    static TUint IndexOf(const Brx& aBuffer, TChar aValue);    // returns index of aValue (or aBuffer.Bytes() if not in)
    static void  Substitute(Bwx& aBuffer, TChar aSearch, TChar aReplace);

    static Brn Trim(const Brx& aBuffer);

    static TInt Int(const Brx& aBuffer); // Convert buffer to decimal number
    static TUint Uint(const Brx& aBuffer); // Convert buffer to decimal number
    static TInt64 Int64(const Brx& aBuffer); // Convert buffer to decimal number
    static TUint64 Uint64(const Brx& aBuffer); // Convert buffer to decimal number
    static TUint UintHex(const Brx& aBuffer); // Convert buffer to hex number

    static void StreamWriteUint(IWriter& aStream, TUint aValue);
    static void StreamWriteInt(IWriter& aStream, TInt aValue);
};

// Stream classes

class IWriterAscii : public IWriter
{
public:    
    virtual void WriteSpace() = 0;
    virtual void WriteNewline() = 0;
    virtual void WriteTab() = 0;
    virtual void WriteInt(TInt aValue) = 0;
    virtual void WriteUint(TUint aValue) = 0;
    virtual void WriteInt64(TInt64 aValue) = 0;
    virtual void WriteUint64(TUint64 aValue) = 0;
    virtual void WriteHex(TUint aValue) = 0;
    virtual void WriteHex(TByte aValue) = 0;
    virtual void WriteHexPrefix() = 0;
    virtual void WriteUintPadded(TUint aValue) = 0;
    virtual void WriteIntPadded(TInt aValue) = 0;
    virtual ~IWriterAscii() {}
};

class WriterAscii : public IWriterAscii, public INonCopyable
{
public:
    WriterAscii(IWriter& aWriter);
    // IWriter
    virtual void Write(TByte aValue);
    virtual void Write(const Brx& aBuffer);
    virtual void WriteFlush();
    // IWriterAscii
    virtual void WriteSpace();
    virtual void WriteNewline();
    virtual void WriteTab();
    virtual void WriteInt(TInt aValue);
    virtual void WriteUint(TUint aValue);
    virtual void WriteInt64(TInt64 aValue);
    virtual void WriteUint64(TUint64 aValue);
    virtual void WriteHex(TUint aValue);
    virtual void WriteHex(TByte aValue);
    virtual void WriteHexPrefix();
    virtual void WriteUintPadded(TUint aValue);
    virtual void WriteIntPadded(TInt aValue);
protected:
    IWriter& iWriter;
};

} // namespace OpenHome

#endif // HEADER_ASCII_ASCII
