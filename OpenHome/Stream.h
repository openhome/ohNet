#ifndef HEADER_STREAM
#define HEADER_STREAM

#include <OpenHome/Private/Standard.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>

EXCEPTION(ReaderError)
EXCEPTION(WriterError)

namespace OpenHome {

class IReader
{
public:
    virtual Brn Read(TUint aBytes) = 0; // Returns [0..aBytes].  0 => stream closed
    virtual void ReadFlush() = 0;
    virtual void ReadInterrupt() = 0;
    virtual ~IReader() {};
};

class IReaderSource
{
public:
    virtual void Read(Bwx& aBuffer) = 0; // Replace contents of aBuffer with [0..MaxBytes].  0 => stream closed
    virtual void ReadFlush() = 0;
    virtual void ReadInterrupt() = 0;
    virtual ~IReaderSource() {};
};

class IWriter
{
public:
    virtual void Write(TByte aValue) = 0;
    virtual void Write(const Brx& aBuffer) = 0;
    virtual void WriteFlush() = 0;
    virtual ~IWriter() {};
};

class Sxx : public INonCopyable
{
    friend class Swp;
protected:
    Sxx(TUint aMaxBytes);
    virtual ~Sxx();
protected:
    virtual TByte* Ptr() = 0;
protected:
    TUint iMaxBytes;
};

class Srx : public Sxx, public IReader
{
public: // from IReader
    Brn Read(TUint aBytes);
    void ReadFlush();
    void ReadInterrupt();
protected:
    Srx(TUint aMaxBytes, IReaderSource& aSource);
protected:
    IReaderSource& iSource;
    TUint iBytes;
    TUint iOffset;
};

template <TUint S> class Srs : public Srx
{
public:
    Srs(IReaderSource& aSource) : Srx(S, aSource) {}
private:
    virtual TByte* Ptr() { return (iBuf); }
private:
    TByte iBuf[S];
};

class Srd : public Srx
{
public:
    Srd(TUint aMaxBytes, IReaderSource& aSource);
    virtual ~Srd();
private:
    virtual TByte* Ptr();
private:
    TByte* iPtr;
};

class ReaderUntil : public IReader, private INonCopyable
{
public:
    Brn ReadUntil(TByte aSeparator);
    Brn ReadProtocol(TUint aBytes); // reads exactly aBytes or throws
public: // from IReader
    Brn Read(TUint aBytes);
    void ReadFlush();
    void ReadInterrupt();
protected:
    ReaderUntil(TUint aMaxBytes, IReader& aReader);
    virtual TByte* Ptr() = 0;
protected:
    TUint iMaxBytes;
    TUint iBytes;
    TUint iOffset;
    IReader& iReader;
};

template <TUint T> class ReaderUntilS : public ReaderUntil
{
public:
    ReaderUntilS(IReader& aReader) : ReaderUntil(T, aReader) {}
private: // from ReaderUntil
    TByte* Ptr() { return iBuf; }
private:
    TByte iBuf[T];
};

class ReaderText : public ReaderUntil
{
public:
    Brn ReadLine();
    Brn ReadLine(TUint& aBytesConsumed);
protected:
    ReaderText(TUint aMaxBytes, IReader& aReader);
};

template <TUint T> class ReaderTextS : public ReaderText
{
public:
    ReaderTextS(IReader& aReader) : ReaderText(T, aReader) {}
private: // from ReaderUntilBase
    TByte* Ptr() { return iBuf; }
private:
    TByte iBuf[T];
};

class ReaderBuffer : public IReader
{
public:
    ReaderBuffer();
    ReaderBuffer(const Brx& aBuffer);
    void Set(const Brx& aBuffer);
    TUint Bytes() const;
    Brn ReadRemaining();
    Brn ReadPartial(TUint aBytes);
    Brn ReadUntil(TByte aSeparator);
public: // from IReader
    Brn Read(TUint aBytes);
    void ReadFlush();
    void ReadInterrupt();
private:
    Brn iBuffer;
    TUint iOffset;
};

class ReaderBinary : private INonCopyable
{
public:
    ReaderBinary(IReader& aReader);
    void ReadReplace(TUint aBytes, Bwx& aBuffer); // replaces any existing content of aBuffer
    TUint ReadUintBe(TUint aBytes);
    TUint ReadUintLe(TUint aBytes);
    TUint64 ReadUint64Be(TUint aBytes);
    TUint64 ReadUint64Le(TUint aBytes);
    TInt ReadIntBe(TUint aBytes);
    TInt ReadIntLe(TUint aBytes);
private:
    void Read(TUint aBytes);
protected:
    IReader& iReader;
private:
    Bws<8> iBuf;
};

class ReaderProtocol : public ReaderBinary
{
public:
    Brn Read(TUint aBytes); // reads exactly aBytes or throws
protected:
    ReaderProtocol(TUint aMaxBytes, IReader& aReader);
    virtual TByte* Ptr() = 0;
protected:
    TUint iMaxBytes;
};

template <TUint T> class ReaderProtocolS : public ReaderProtocol
{
public:
    ReaderProtocolS(IReader& aReader) : ReaderProtocol(T, aReader) {}
private: // from ReaderUntil
    TByte* Ptr() { return iBuf; }
private:
    TByte iBuf[T];
};

class Swx : public Sxx, public IWriter
{
public: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    void WriteDrain();
protected:
    Swx(TUint aMaxBytes, IWriter& aWriter);
private:
    void Error();
    virtual TByte* Ptr() = 0;
protected:
    IWriter& iWriter;
    TUint iBytes;
};

template <TUint S> class Sws : public Swx
{
public:
    Sws(IWriter& aWriter) : Swx(S, aWriter) {}
private:
    virtual TByte* Ptr() { return (iBuf); }
private:
    TByte iBuf[S];
};

class WriterBuffer : public IWriter, public INonCopyable
{
public:
    WriterBuffer(Bwx& aBuffer);
    void Flush();
public: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    Bwx& iBuffer;
};

class WriterBwh : public IWriter
{
public:
    WriterBwh(TInt aGranularity);
    void TransferTo(Bwh& aDest);
    void TransferTo(Brh& aDest);
    void Write(const TChar* aBuffer);
public: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    Bwh iBuf;
    TInt iGranularity;
};

class WriterBinary : private INonCopyable
{
public:
    WriterBinary(IWriter& aWriter);
    void Write(const Brx& aBuffer);
    void WriteUint8(TUint aValue);
    void WriteUint16Be(TUint aValue);
    void WriteUint24Be(TUint aValue);
    void WriteUint32Be(TUint aValue);
    void WriteUint64Be(TUint64 aValue);
    void WriteUint16Le(TUint aValue);
    void WriteUint24Le(TUint aValue);
    void WriteUint32Le(TUint aValue);
    void WriteUint64Le(TUint64 aValue);
    void WriteInt8(TInt aValue);
    void WriteInt16Be(TInt aValue);
    void WriteInt24Be(TInt aValue);
    void WriteInt32Be(TInt aValue);
    void WriteInt64Be(TInt64 aValue);
    void WriteInt16Le(TInt aValue);
    void WriteInt24Le(TInt aValue);
    void WriteInt32Le(TInt aValue);
    void WriteInt64Le(TInt64 aValue);
private:
    IWriter& iWriter;
};

} // namespace OpenHome

#endif // HEADER_STREAM
