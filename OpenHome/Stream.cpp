#include <OpenHome/Private/Stream.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Ascii.h>

#include <string.h>
#include <algorithm>

using namespace OpenHome;

// Sxx

Sxx::Sxx(TUint aMaxBytes)
    : iMaxBytes(aMaxBytes)
{
}

Sxx::~Sxx()
{
}


// Srx

Srx::Srx(TUint aMaxBytes, IReaderSource& aSource)
    : Sxx(aMaxBytes)
    , iSource(aSource)
    , iBytes(0)
    , iOffset(0)
{
}

Brn Srx::Read(TUint aBytes)
{
    TByte* ptr = Ptr();
    if (iBytes == 0) {
        Bwn buffer(ptr, iMaxBytes);
        iSource.Read(buffer);
        iBytes += buffer.Bytes();
        iSource.ReadFlush();
    }
    const TUint bytes = std::min(iBytes - iOffset, aBytes);
    Brn buf(ptr + iOffset, bytes);
    iOffset += bytes;
    if (iOffset == iBytes) {
        iBytes = 0;
        iOffset = 0;
    }
    return buf;
}

void Srx::ReadFlush()
{
    iBytes = 0;
    iOffset = 0;
    iSource.ReadFlush();
}

void Srx::ReadInterrupt()
{
    iSource.ReadInterrupt();
}


// Srd

Srd::Srd(TUint aMaxBytes, IReaderSource& aSource)
    : Srx(aMaxBytes, aSource)
    , iPtr(new TByte[aMaxBytes])
{
}

TByte* Srd::Ptr()
{
    return iPtr;
}

Srd::~Srd()
{
    delete[] iPtr;
}


// ReaderUntil

Brn ReaderUntil::ReadUntil(TByte aSeparator)
{
    TByte* ptr = Ptr();
    TByte* start = ptr + iOffset;
    TByte* current = start;
    TUint count = 0;
    TUint remaining = iBytes - iOffset;

    for (;;) {
        while (remaining) {
            if (*current++ == aSeparator) {
                iOffset += count + 1; // skip over the separator
                if (iOffset == iBytes) {
                    iBytes = 0;
                    iOffset = 0;
                }
                return Brn(start, count);
            }
            count++;
            remaining--;
        }
    
        // separator not found in current buffer
        if (iOffset > 0 && iBytes == iMaxBytes) { // so move everything down
            start -= iOffset;
            iBytes -= iOffset;
            current -= iOffset;
            if (iBytes) {
                (void)memmove(ptr, ptr + iOffset, iBytes);
            }
            iOffset = 0;
        }
        if (iBytes == iMaxBytes) { // buffer full and no separator
            THROW(ReaderError);
        }

        Bwn buffer(ptr + iBytes, iMaxBytes - iBytes); // collect more data from the source
        buffer.Append(iReader.Read(iMaxBytes - iBytes));
        TUint additional = buffer.Bytes();
        iBytes += additional;
        remaining += additional;
    }
}

Brn ReaderUntil::ReadProtocol(TUint aBytes)
{
    ASSERT(aBytes <= iMaxBytes);
    TByte* start = Ptr() + iOffset;
    TByte* p = start;
    if (aBytes <= iBytes - iOffset) {
        iOffset += aBytes;
        if (iOffset == iBytes) {
            iBytes = 0;
            iOffset = 0;
        }
        return Brn(start, aBytes);
    }
    if (iBytes > 0) {
        iBytes -= iOffset;
        start = Ptr();
        (void)memmove(start, start + iOffset, iBytes);
        p = start + iBytes;
        iOffset = 0;
        aBytes -= iBytes;
    }
    TUint remaining = aBytes;
    while (remaining > 0) {
        Brn buf = iReader.Read(remaining);
        (void)memcpy(p, buf.Ptr(), buf.Bytes());
        p += buf.Bytes();
    }
    iBytes = 0;
    iOffset = 0;
    return Brn(start, p - start);
}

Brn ReaderUntil::Read(TUint aBytes)
{
    if (iBytes > 0) {
        ASSERT(iOffset < iBytes);
        const TUint bytes = std::min(aBytes, iBytes - iOffset);
        Brn buf(Ptr() + iOffset, bytes);
        iOffset += bytes;
        if (iOffset == iBytes) {
            iBytes = 0;
            iOffset = 0;
        }
        return buf;
    }
    return iReader.Read(aBytes);
}

void ReaderUntil::ReadFlush()
{
    iBytes = 0;
    iOffset = 0;
    iReader.ReadFlush();
}

void ReaderUntil::ReadInterrupt()
{
    iReader.ReadInterrupt();
}

ReaderUntil::ReaderUntil(TUint aMaxBytes, IReader& aReader)
    : iMaxBytes(aMaxBytes)
    , iBytes(0)
    , iOffset(0)
    , iReader(aReader)
{
}


// ReaderText

Brn ReaderText::ReadLine()
{
    Brn line;
    try {
        line.Set(Ascii::Trim(ReadUntil(Ascii::kLf)));
    }
    catch (ReaderError&) {
        // treat any content following the last newline as a final line
        line.Set(Read(iMaxBytes));
        if (line.Bytes() == 0) {
            throw;
        }
    }
    return line;
}

Brn ReaderText::ReadLine(TUint& aBytesConsumed)
{
    Brn line;
    try {
        Brn buf = ReadUntil(Ascii::kLf);
        aBytesConsumed = buf.Bytes() + 1; // +1 for Ascii::kLf
        line.Set(Ascii::Trim(buf));
    }
    catch (ReaderError&) {
        // treat any content following the last newline as a final line
        Brn buf = Read(iMaxBytes);
        aBytesConsumed = buf.Bytes() + 1; // +1 for Ascii::kLf
        line.Set(Ascii::Trim(buf));
        if (line.Bytes() == 0) {
            throw;
        }
    }
    return line;
}

ReaderText::ReaderText(TUint aMaxBytes, IReader& aReader)
    : ReaderUntil(aMaxBytes, aReader)
{
}


// ReaderBuffer

ReaderBuffer::ReaderBuffer()
{
    Set(Brx::Empty());
}

ReaderBuffer::ReaderBuffer(const Brx& aBuffer)
{
    Set(aBuffer);
}

void ReaderBuffer::Set(const Brx& aBuffer)
{
    iBuffer.Set(aBuffer);
    ReadFlush();
}

Brn ReaderBuffer::Read(TUint aBytes)
{
    if (iOffset == iBuffer.Bytes()) {
        THROW(ReaderError);
    }
    TUint offset = iOffset + aBytes;
    if (offset > iBuffer.Bytes()) {
        offset = iBuffer.Bytes();
        aBytes = iBuffer.Bytes() - iOffset;
    }
    Brn result = iBuffer.Split(iOffset, aBytes);
    iOffset = offset;
    
    return result;
}

TUint ReaderBuffer::Bytes() const
{   
    return (iBuffer.Bytes() - iOffset);
}

Brn ReaderBuffer::ReadRemaining()
{
    Brn result = iBuffer.Split(iOffset);
    iOffset = iBuffer.Bytes();
    return result;
}

Brn ReaderBuffer::ReadPartial(TUint aBytes)
{
    TUint remaining = iBuffer.Bytes() - iOffset;
    if (remaining == 0) {
        THROW(ReaderError);
    }
    TUint bytes = aBytes;
    if (bytes > remaining) {
        bytes = remaining;
    }
    Brn result = iBuffer.Split(iOffset, bytes);
    iOffset += bytes;
    
    return result;
}

Brn ReaderBuffer::ReadUntil(TByte aSeparator)
{
    TUint start = iOffset;
    TUint offset = iOffset;
    TUint bytes = iBuffer.Bytes();
    while (offset < bytes) {
        if (iBuffer[offset++] == aSeparator) {
            iOffset = offset;
            return iBuffer.Split(start, offset - start - 1);
        }
    }
    
    THROW(ReaderError);
}

void ReaderBuffer::ReadFlush()
{
    iOffset = 0;
}

void ReaderBuffer::ReadInterrupt()
{
}


// ReaderBinary

ReaderBinary::ReaderBinary(IReader& aReader)
    : iReader(aReader)
{
}

void ReaderBinary::ReadReplace(TUint aBytes, Bwx& aBuffer)
{
    ASSERT(aBytes <= aBuffer.MaxBytes());
    aBuffer.SetBytes(0);
    while (aBytes > 0) {
        Brn buf = iReader.Read(aBytes);
        aBuffer.Append(buf);
        aBytes -= buf.Bytes();
    }
}

TUint ReaderBinary::ReadUintBe(TUint aBytes)
{
    ASSERT(aBytes > 0);
    ASSERT(aBytes <= sizeof(TUint));
    TUint val = 0;
    TUint count = 0;
    Read(aBytes);
    TUint index = 0;
    while(count < aBytes) {
        TUint byte = iBuf[index++];
        val += byte << ((aBytes - count - 1)*8);
        count++;
    }
    return val;
}

TInt ReaderBinary::ReadIntBe(TUint aBytes)
{
    ASSERT(aBytes > 0);
    ASSERT(aBytes <= sizeof(TInt));
    TInt val = 0;
    TUint count = 0;
    Read(aBytes);
    TUint index = 0;

    TInt sbyte = iBuf[index++];
    val += sbyte << ((aBytes - count - 1) * 8);
    count++;

    while(count < aBytes) {
        TUint byte = iBuf[index++];
        val += byte << ((aBytes - count - 1) * 8);
        count++;
    }
    return val;
}

TInt ReaderBinary::ReadIntLe(TUint aBytes)
{
    ASSERT(aBytes > 0);
    ASSERT(aBytes <= sizeof(TInt));
    TInt val = 0;
    TUint shift = 0;
    Read(aBytes);
    TUint index = 0;

    TInt sbyte = iBuf[index++];
    val += sbyte << (shift*8);
    shift++;

    while(shift < aBytes) {
        TUint byte = iBuf[index++];
        val += byte << (shift*8);
        shift++;
    }
    return val;
}

TUint ReaderBinary::ReadUintLe(TUint aBytes)
{
    ASSERT(aBytes > 0);
    ASSERT(aBytes <= sizeof(TUint));
    TUint val = 0;
    TUint shift = 0;
    Read(aBytes);
    TUint index = 0;
    while(shift < aBytes) {
        TUint byte = iBuf[index++];
        val += byte << (shift*8);
        shift++;
    }
    return val;
}

TUint64 ReaderBinary::ReadUint64Be(TUint aBytes)
{
    ASSERT(aBytes > 0);
    ASSERT(aBytes <= sizeof(TUint64));
    TUint64 val = 0;
    TUint count = 0;
    Read(aBytes);
    TUint index = 0;
    while(count < aBytes) {
        TUint64 byte = iBuf[index++];
        val += byte << ((aBytes - count - 1)*8);
        count++;
    }
    return val;
}

TUint64 ReaderBinary::ReadUint64Le(TUint aBytes)
{
    ASSERT(aBytes > 0);
    ASSERT(aBytes <= sizeof(TUint64));
    TUint64 val = 0;
    TUint shift = 0;
    Read(aBytes);
    TUint index = 0;
    while(shift < aBytes) {
        TUint64 byte = iBuf[index++];
        val += byte << (shift*8);
        shift++;
    }
    return val;
}

void ReaderBinary::Read(TUint aBytes)
{
    ASSERT(aBytes <= iBuf.MaxBytes());
    iBuf.SetBytes(0);
    while (aBytes > 0) {
        Brn buf = iReader.Read(aBytes);
        iBuf.Append(buf);
        aBytes -= buf.Bytes();
    }
}


// ReaderProtocol

Brn ReaderProtocol::Read(TUint aBytes)
{
    ASSERT(aBytes <= iMaxBytes);
    TByte* p = Ptr();
    TUint remaining = aBytes;
    Bwn buf;
    while (remaining > 0) {
        buf.Set(p + aBytes - remaining, remaining);
        buf.Append(iReader.Read(remaining));
        remaining -= buf.Bytes();
    }
    return Brn(p, aBytes);
}

ReaderProtocol::ReaderProtocol(TUint aMaxBytes, IReader& aReader)
    : ReaderBinary(aReader)
    , iMaxBytes(aMaxBytes)
{
}


// Swx

Swx::Swx(TUint aMaxBytes, IWriter& aWriter)
    : Sxx(aMaxBytes)
    , iWriter(aWriter)
    , iBytes(0)
{
}

void Swx::Error()
{
    iBytes = 0;
    THROW(WriterError);
}

void Swx::Write(TByte aValue)
{
    TByte* ptr = Ptr();
    if (iBytes >= iMaxBytes) { // would overflow, flush the buffer
        iWriter.Write(Brn(ptr, iBytes));
        iBytes = 0;
    }

    *(ptr + iBytes++) = aValue;
}

void Swx::Write(const Brx& aBuffer)
{
    TByte* ptr = Ptr();
    TUint bytes = aBuffer.Bytes();
    if (iBytes + bytes > iMaxBytes) { // would overflow, drain the buffer
        WriteDrain();
        if (bytes > iMaxBytes) { // would still overflow
            try {
                iWriter.Write(aBuffer); // pass it on
                return;
            }
            catch (WriterError&) {
                Error();
            }
        }
    }
    memcpy(ptr + iBytes, aBuffer.Ptr(), bytes);
    iBytes += bytes;
}

void Swx::WriteDrain()
{
    if (iBytes) {
        TByte* ptr = Ptr();
        try {
            iWriter.Write(Brn(ptr, iBytes));
            iBytes = 0;
        }
        catch (WriterError&) {
            Error();
        }
    }
}

void Swx::WriteFlush()
{
    WriteDrain();
    iWriter.WriteFlush();
}


// WriterBuffer

WriterBuffer::WriterBuffer(Bwx& aBuffer)
    : iBuffer(aBuffer)
{
}

void WriterBuffer::Write(TByte aValue)
{
    iBuffer.Append(aValue);
}

void WriterBuffer::Write(const Brx& aBuffer)
{
    iBuffer.Append(aBuffer);
}

void WriterBuffer::WriteFlush()
{
}

void WriterBuffer::Flush()
{
    iBuffer.Replace(Brx::Empty());
}


// WriterBwh

WriterBwh::WriterBwh(TInt aGranularity)
    : iBuf(aGranularity)
    , iGranularity(aGranularity)
{
}

void WriterBwh::TransferTo(Bwh& aDest)
{
    iBuf.TransferTo(aDest);
}

void WriterBwh::TransferTo(Brh& aDest)
{
    iBuf.TransferTo(aDest);
}

void WriterBwh::Write(const TChar* aBuffer)
{
    Brn buf(aBuffer);
    Write(buf);
}

void WriterBwh::Write(TByte aValue)
{
    Brn byte(&aValue, 1);
    Write(byte);
}

void WriterBwh::Write(const Brx& aBuffer)
{
    TInt maxBytes = iBuf.MaxBytes();
    TInt reqMaxBytes = iBuf.Bytes() + aBuffer.Bytes();
    if (reqMaxBytes > maxBytes) {
        do {
            maxBytes += iGranularity;
        } while (reqMaxBytes > maxBytes);
        iBuf.Grow(maxBytes);
    }
    iBuf.Append(aBuffer);
}

void WriterBwh::WriteFlush()
{
}


// WriterBinary

WriterBinary::WriterBinary(IWriter& aWriter)
    : iWriter(aWriter)
{
}

void WriterBinary::Write(const Brx& aBuf)
{
    iWriter.Write(aBuf);
}

void WriterBinary::WriteUint8(TUint aValue)
{
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteUint16Be(TUint aValue)
{
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteUint24Be(TUint aValue)
{
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteUint32Be(TUint aValue)
{
    iWriter.Write((TByte)(aValue >> 24));
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteUint64Be(TUint64 aValue)
{
    iWriter.Write((TByte)(aValue >> 56));
    iWriter.Write((TByte)(aValue >> 48));
    iWriter.Write((TByte)(aValue >> 40));
    iWriter.Write((TByte)(aValue >> 32));
    iWriter.Write((TByte)(aValue >> 24));
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteUint16Le(TUint aValue)
{
    iWriter.Write((TByte)(aValue));
    iWriter.Write((TByte)(aValue >> 8));
}

void WriterBinary::WriteUint24Le(TUint aValue)
{
    iWriter.Write((TByte)(aValue));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue >> 16));
}

void WriterBinary::WriteUint32Le(TUint aValue)
{
    iWriter.Write((TByte)(aValue));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 24));
}

void WriterBinary::WriteUint64Le(TUint64 aValue)
{
    iWriter.Write((TByte)(aValue));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 24));
    iWriter.Write((TByte)(aValue >> 32));
    iWriter.Write((TByte)(aValue >> 40));
    iWriter.Write((TByte)(aValue >> 48));
    iWriter.Write((TByte)(aValue >> 56));
}

void WriterBinary::WriteInt8(TInt aValue)
{
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteInt16Be(TInt aValue)
{
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteInt24Be(TInt aValue)
{
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteInt32Be(TInt aValue)
{
    iWriter.Write((TByte)(aValue >> 24));
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteInt64Be(TInt64 aValue)
{
    iWriter.Write((TByte)(aValue >> 56));
    iWriter.Write((TByte)(aValue >> 48));
    iWriter.Write((TByte)(aValue >> 40));
    iWriter.Write((TByte)(aValue >> 32));
    iWriter.Write((TByte)(aValue >> 24));
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue));
}

void WriterBinary::WriteInt16Le(TInt aValue)
{
    iWriter.Write((TByte)(aValue));
    iWriter.Write((TByte)(aValue >> 8));
}

void WriterBinary::WriteInt24Le(TInt aValue)
{
    iWriter.Write((TByte)(aValue));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue >> 16));
}

void WriterBinary::WriteInt32Le(TInt aValue)
{
    iWriter.Write((TByte)(aValue));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 24));
}

void WriterBinary::WriteInt64Le(TInt64 aValue)
{
    iWriter.Write((TByte)(aValue));
    iWriter.Write((TByte)(aValue >> 8));
    iWriter.Write((TByte)(aValue >> 16));
    iWriter.Write((TByte)(aValue >> 24));
    iWriter.Write((TByte)(aValue >> 32));
    iWriter.Write((TByte)(aValue >> 40));
    iWriter.Write((TByte)(aValue >> 48));
    iWriter.Write((TByte)(aValue >> 56));
}
