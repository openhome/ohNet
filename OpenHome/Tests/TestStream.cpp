#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Stream.h>
#include <cstdarg>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class SuiteReaderBinary : public Suite
{
public:
    SuiteReaderBinary() : Suite("Test ReaderBinary") {}
    void Test();
};

void SuiteReaderBinary::Test()
{
    TByte data[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0, 0x00 };
    Brn buffer(data, sizeof(data));

    ReaderBuffer readerBuffer(buffer);
    ReaderBinary readerBinary(readerBuffer);

    // ReaderBinary::ReadUintBe

    TEST(readerBinary.ReadUintBe(1) == 0x12);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUintBe(2) == 0x1234);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUintBe(3) == 0x123456);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUintBe(4) == 0x12345678);
    readerBuffer.Set(buffer);
    TEST_THROWS(readerBinary.ReadUintBe(5), AssertionFailed);

    // ReaderBinary::ReadUintBe64

    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(1) == 0x12ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(2) == 0x1234ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(3) == 0x123456ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(4) == 0x12345678ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(5) == 0x123456789aULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(6) == 0x123456789abcULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(7) == 0x123456789abcdeULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(8) == 0x123456789abcdef0ULL);
    readerBuffer.Set(buffer);
    TEST_THROWS(readerBinary.ReadUint64Be(9), AssertionFailed);

    // ReaderBinary::ReadUintLe

    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUintLe(1) == 0x12);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUintLe(2) == 0x3412);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUintLe(3) == 0x563412);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUintLe(4) == 0x78563412);
    readerBuffer.Set(buffer);
    TEST_THROWS(readerBinary.ReadUintLe(5), AssertionFailed);

    // ReaderBinary::ReadUintLe64

    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(1) == 0x12ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(2) == 0x3412ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(3) == 0x563412ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(4) == 0x78563412ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(5) == 0x9a78563412ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(6) == 0xbc9a78563412ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(7) == 0xdebc9a78563412ULL);
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(8) == 0xf0debc9a78563412ULL);
    readerBuffer.Set(buffer);
    TEST_THROWS(readerBinary.ReadUint64Le(9), AssertionFailed);

    // ReaderBinary::ReadIntBe

    TByte dataSigned[] = { 0xff, 0xaa, 0xbb, 0xff };
    Brn bufferSigned(dataSigned, sizeof(dataSigned));

    readerBuffer.Set(bufferSigned);
    TEST(readerBinary.ReadIntBe(1) == TInt(0xff));
    readerBuffer.Set(bufferSigned);
    TEST(readerBinary.ReadIntBe(2) == TInt(0xffaa));
    readerBuffer.Set(bufferSigned);
    TEST(readerBinary.ReadIntBe(3) == TInt(0xffaabb));
    readerBuffer.Set(bufferSigned);
    TEST(readerBinary.ReadIntBe(4) == TInt(0xffaabbff));
    readerBuffer.Set(bufferSigned);
    TEST_THROWS(readerBinary.ReadIntBe(5), AssertionFailed);

    // ReaderBinary::ReadIntLe

    readerBuffer.Set(bufferSigned);
    TEST(readerBinary.ReadIntLe(1) == TInt(0xff));
    readerBuffer.Set(bufferSigned);
    TEST(readerBinary.ReadIntLe(2) == TInt(0xaaff));
    readerBuffer.Set(bufferSigned);
    TEST(readerBinary.ReadIntLe(3) == TInt(0xbbaaff));
    readerBuffer.Set(bufferSigned);
    TEST(readerBinary.ReadIntLe(4) == TInt(0xffbbaaff));
    readerBuffer.Set(bufferSigned);
    TEST_THROWS(readerBinary.ReadIntLe(5), AssertionFailed);
}

class SuiteWriterBinary : public Suite
{
public:
    SuiteWriterBinary();
    void Test();
private:
    TBool CheckBuffer(TUint aCount, ...);
    void ResetBuffer();
private:
    Bws<256> iBuffer;
    WriterBuffer iWriterBuffer;
    WriterBinary iWb;
};

SuiteWriterBinary::SuiteWriterBinary()
    : Suite("Test WriterBinary")
    , iWriterBuffer(iBuffer)
    , iWb(iWriterBuffer)
{
    ResetBuffer();
}

TBool SuiteWriterBinary::CheckBuffer(TUint aCount, ...)
{
    va_list args;
    va_start(args, aCount);
    Bwh buffer(aCount+1);
    buffer.Append(TByte(0xae)); // We're expecting the first byte of the buffer to be set to 0xae
    for ( TUint i = 0 ; i < aCount ; ++i )
        buffer.Append(TByte(va_arg(args, int)));

    va_end(args);

    TBool result = (iBuffer == buffer);
    ResetBuffer();
    return result;
}

void SuiteWriterBinary::ResetBuffer()
{
    iBuffer.SetBytes(0);
    iBuffer.Append(TByte(0xae));    // Set first byte to 0xae. This will help check that WriterBuffer methods /append/
}

void SuiteWriterBinary::Test()
{
    // Write Uint*Be

    iWb.WriteUint8(0x12);
    TEST(CheckBuffer(1, 0x12));

    iWb.WriteUint16Be(0x1234);
    TEST(CheckBuffer(2, 0x12, 0x34));

    iWb.WriteUint24Be(0x123456UL);
    TEST(CheckBuffer(3, 0x12, 0x34, 0x56));

    iWb.WriteUint32Be(0x12345678UL);
    TEST(CheckBuffer(4, 0x12, 0x34, 0x56, 0x78));

    iWb.WriteUint64Be(0x123456789abcdef0ULL);
    TEST(CheckBuffer(8, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0));

    // Write Uint*Le

    iWb.WriteUint16Le(0x1234);
    TEST(CheckBuffer(2, 0x34, 0x12));

    iWb.WriteUint24Le(0x123456UL);
    TEST(CheckBuffer(3, 0x56, 0x34, 0x12));

    iWb.WriteUint32Le(0x12345678UL);
    TEST(CheckBuffer(4, 0x78, 0x56, 0x34, 0x12));

    iWb.WriteUint64Le(0x123456789abcdef0ULL);
    TEST(CheckBuffer(8, 0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12));

    // Write Int*Be

    iWb.WriteInt8(0x12);
    TEST(CheckBuffer(1, 0x12));

    iWb.WriteInt16Be(0x1234);
    TEST(CheckBuffer(2, 0x12, 0x34));

    iWb.WriteInt24Be(0x123456UL);
    TEST(CheckBuffer(3, 0x12, 0x34, 0x56));

    iWb.WriteInt32Be(0x12345678UL);
    TEST(CheckBuffer(4, 0x12, 0x34, 0x56, 0x78));

    iWb.WriteInt64Be(0x123456789abcdef0ULL);
    TEST(CheckBuffer(8, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0));

    // Write Int*Le

    iWb.WriteInt16Le(0x1234);
    TEST(CheckBuffer(2, 0x34, 0x12));

    iWb.WriteInt24Le(0x123456UL);
    TEST(CheckBuffer(3, 0x56, 0x34, 0x12));

    iWb.WriteInt32Le(0x12345678UL);
    TEST(CheckBuffer(4, 0x78, 0x56, 0x34, 0x12));

    iWb.WriteInt64Le(0x123456789abcdef0ULL);
    TEST(CheckBuffer(8, 0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12));
}

void TestStream()
{
    Runner runner("Stream Testing\n");
    runner.Add(new SuiteReaderBinary());
    runner.Add(new SuiteWriterBinary());
    runner.Run();
}
