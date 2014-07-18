#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/Stream.h>

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

    // ReaderBinary::Read()

    TEST(readerBinary.Read(8) == buffer.Split(0, 8));

    // ReaderBinary::ReadUintBe

    readerBuffer.Set(buffer);
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
    TEST(readerBinary.ReadUint64Be(1) == TUint64(0x12));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(2) == TUint64(0x1234));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(3) == TUint64(0x123456));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(4) == TUint64(0x12345678));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(5) == TUint64(0x123456789a));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(6) == TUint64(0x123456789abc));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(7) == TUint64(0x123456789abcde));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Be(8) == TUint64(0x123456789abcdef0));
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
    TEST(readerBinary.ReadUint64Le(1) == TUint64(0x12));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(2) == TUint64(0x3412));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(3) == TUint64(0x563412));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(4) == TUint64(0x78563412));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(5) == TUint64(0x9a78563412));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(6) == TUint64(0xbc9a78563412));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(7) == TUint64(0xdebc9a78563412));
    readerBuffer.Set(buffer);
    TEST(readerBinary.ReadUint64Le(8) == TUint64(0xf0debc9a78563412));
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

void TestStream()
{
    Runner runner("Stream Testing\n");
    runner.Add(new SuiteReaderBinary());
    runner.Run();
}
