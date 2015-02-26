#include <OpenHome/Private/Stream.h>

#include <string.h>

using namespace OpenHome;

// Sxx

Sxx::Sxx(TUint aMaxBytes)
    : iMaxBytes(aMaxBytes)
    , iBytes(0)
{
}

Sxx::~Sxx()
{
}

// Srx

Srx::Srx(TUint aMaxBytes, IReaderSource& aSource)
    : Sxx(aMaxBytes)
    , iSource(aSource)
    , iOffset(0)
{
}

Brn Srx::Read(TUint aBytes)
{
    TByte* ptr = Ptr();

    if (iBytes - iOffset < aBytes) {  // read not satisfied from data already in the buffer
        if (aBytes > iMaxBytes) { // unable to store the requested number of bytes in the buffer
            THROW(ReaderError);
        }

        if (iMaxBytes - iOffset < aBytes) {
            (void)memmove(ptr, ptr + iOffset, iBytes - iOffset); // so make some more room
            iBytes -= iOffset;
            iOffset = 0;
        }

        while (iBytes - iOffset < aBytes) { // collect more data from the source
            Bwn buffer(ptr + iBytes, iMaxBytes - iBytes);
            iSource.Read(buffer);
            iBytes += buffer.Bytes();
            iSource.ReadFlush();
        }
    }

    TUint offset = iOffset;
    iOffset += aBytes;
    return (Brn(ptr + offset, aBytes));
}

Brn Srx::ReadUntil(TByte aSeparator)
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
                return (Brn(start, count));
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
                memmove(ptr, ptr + iOffset, iBytes);
            }
            iOffset = 0;
        }
        
        if (iBytes == iMaxBytes) { // buffer full and no separator
            THROW(ReaderError);
        }
        Bwn buffer(ptr + iBytes, iMaxBytes - iBytes); // collect more data from the source
        iSource.Read(buffer);
        TUint additional = buffer.Bytes();
        iBytes += additional;
        remaining += additional;
    }
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

TUint Srx::ReadCapacity() const
{
    return iMaxBytes;
}

Brn Srx::Peek(TUint aBytes)
{
    Brn buf;
    try {
        buf.Set(Read(aBytes));
        iOffset -= buf.Bytes(); // rewind to the start of the buffer we've just read
    }
    catch (ReaderError&) {
        buf.Set(Ptr() + iOffset, iBytes - iOffset); // Snaffle without manipulation of iBytes or iOffset
    }
    return buf;
}

Brn Srx::Snaffle()
{
    Brn rem(Ptr() + iOffset, iBytes - iOffset);
    iOffset = 0;
    iBytes = 0;
    return rem;
}

Brn Srx::Buffer()
{
    Brn buf(Ptr(), iBytes);
    return buf;
}


// Srd

Srd::Srd(TUint aMaxBytes, IReaderSource& aSource)
    : Srx(aMaxBytes, aSource)
    , iPtr(new TByte[aMaxBytes])
{
}

TByte* Srd::Ptr()
{
    return (iPtr);
}

Srd::~Srd()
{
    delete[] iPtr;
}

// Swx

Swx::Swx(TUint aMaxBytes, IWriter& aWriter)
    : Sxx(aMaxBytes) 
    , iWriter(aWriter)
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

// Swd

Swd::Swd(TUint aMaxBytes, IWriter& aWriter)
    : Swx(aMaxBytes, aWriter)
    , iPtr(new TByte[aMaxBytes])
{
}

TByte* Swd::Ptr()
{
    return (iPtr);
}

Swd::~Swd()
{
    delete (iPtr);
}

// Swp (Parasite on a host read stream)

Swp::Swp(Srx& aHost, IWriter& aWriter)
    : Swx(aHost.iMaxBytes, aWriter)
    , iHost(aHost)
{
}

TByte* Swp::Ptr()
{
    return (iHost.Ptr());
}

Swp::~Swp()
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
    TUint offset = iOffset + aBytes;
    
    if (offset > iBuffer.Bytes()) {
        THROW(ReaderError);
    }
    
    Brn result = iBuffer.Split(iOffset, aBytes);
    
    iOffset = offset;
    
    return (result);
}

TUint ReaderBuffer::Bytes() const
{   
    return (iBuffer.Bytes() - iOffset);
}

Brn ReaderBuffer::ReadRemaining()
{
    Brn result = iBuffer.Split(iOffset);

    iOffset = iBuffer.Bytes();
    
    return (result);
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
    
    return (result);
}

Brn ReaderBuffer::ReadUntil(TByte aSeparator)
{
    TUint start = iOffset;
    TUint offset = iOffset;
    
    TUint bytes = iBuffer.Bytes();
    
    while (offset < bytes) {
        if (iBuffer[offset++] == aSeparator) {
            iOffset = offset;
            return (iBuffer.Split(start, offset - start - 1));
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

TUint ReaderBuffer::ReadCapacity() const
{
    return iBuffer.Bytes(); // Value may change after ::Set() is called.
}



// WriterBuffer

WriterBuffer::WriterBuffer(Bwx& aBuffer) : iBuffer(aBuffer)
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

// ReaderBinary

ReaderBinary::ReaderBinary(IReader& aReader)
    : iReader(aReader)
{
}

const Brn ReaderBinary::Read(TUint aBytes)
{
    return (iReader.Read(aBytes));    
}

TUint ReaderBinary::ReadUintBe(TUint aBytes)
{
    ASSERT(aBytes > 0);
    ASSERT(aBytes <= sizeof(TUint));
    TUint val = 0;
    TUint count = 0;
    while(count < aBytes) {
        TUint byte = iReader.Read(1).At(0);
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

    TInt sbyte = iReader.Read(1).At(0);
    val += sbyte << ((aBytes - count - 1) * 8);
    count++;

    while(count < aBytes) {
        TUint byte = iReader.Read(1).At(0);
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

    TInt sbyte = iReader.Read(1).At(0);
    val += sbyte << (shift*8);
    shift++;

    while(shift < aBytes) {
        TUint byte = iReader.Read(1).At(0);
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
    while(shift < aBytes) {
        TUint byte = iReader.Read(1).At(0);
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
    while(count < aBytes) {
        TUint64 byte = iReader.Read(1).At(0);
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
    while(shift < aBytes) {
        TUint64 byte = iReader.Read(1).At(0);
        val += byte << (shift*8);
        shift++;
    }
    return val;
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

