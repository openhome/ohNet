#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Av/Json.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;

namespace OpenHome {
namespace Av {

class SuiteJsonEncode : public Suite, private IWriter
{
public:
    SuiteJsonEncode();
private: // from Suite
    void Test() override;
private:
    void EncodeChar(TByte aChar, const TChar* aEncoded);
private: // from IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
private:
    Bws<128> iEncoded;
};

class SuiteJsonDecode : public Suite
{
public:
    SuiteJsonDecode();
private: // from Suite
    void Test() override;
private:
    static void DecodeChar(const TChar* aEncoded, TByte aDecoded);
};

} // namespace Av
} // namespace OpenHome


SuiteJsonEncode::SuiteJsonEncode()
    : Suite("Encode")
{
}

void SuiteJsonEncode::Test()
{
    EncodeChar('\"', "\\\"");
    EncodeChar('\\', "\\\\");
    EncodeChar( '/', "\\/");
    EncodeChar('\b', "\\b");
    EncodeChar('\f', "\\f");
    EncodeChar('\n', "\\n");
    EncodeChar('\r', "\\r");
    EncodeChar('\t', "\\t");
    for (TUint i=0; i<32; i++) {
        iEncoded.SetBytes(0);
        TByte b = (TByte)i;
        Bws<1> ch(&b, 1);
        Json::Escape(*this, ch);
        TEST(iEncoded.Bytes() > 1);
        if (iEncoded.Bytes() > 2) {
            Brn start(iEncoded.Ptr(), 2);
            TEST(start == Brn("\\u"));
            TEST(Ascii::UintHex(iEncoded.Split(2)) == i);
        }
    }
    // with very few exceptions, characters above 0x1F should not be encded
    for (TUint i=32; i<256; i++) {
        if (i == '\"' || i == '/' || i == '\\') {
            // ...the exceptions mentioned above
            continue;
        }
        iEncoded.SetBytes(0);
        TByte b = (TByte)i;
        Bws<1> ch(&b, 1);
        Json::Escape(*this, ch);
        TEST(iEncoded == ch);
    }
}

void SuiteJsonEncode::EncodeChar(TByte aChar, const TChar* aEncoded)
{
    iEncoded.SetBytes(0);
    Bws<1> ch(&aChar, 1);
    Json::Escape(*this, ch);
    Brn expected(aEncoded);
    TEST(iEncoded == expected);
}

void SuiteJsonEncode::Write(TByte aValue)
{
    iEncoded.Append(aValue);
}

void SuiteJsonEncode::Write(const Brx& aBuffer)
{
    iEncoded.Append(aBuffer);
}

void SuiteJsonEncode::WriteFlush()
{
}


SuiteJsonDecode::SuiteJsonDecode()
    : Suite("Decode")
{
}

void SuiteJsonDecode::Test()
{
    DecodeChar("\\\"", '\"');
    DecodeChar("\\\\", '\\');
    DecodeChar("\\/", '/');
    DecodeChar("\\b", '\b');
    DecodeChar("\\f", '\f');
    DecodeChar("\\n", '\n');
    DecodeChar("\\r", '\r');
    DecodeChar("\\t", '\t');
    for (TUint i=0; i<256; i++) {
        Bws<7> enc("\\u00");
        Ascii::AppendHex(enc, (TByte)i);
        DecodeChar(enc.PtrZ(), (TByte)i);
    }
    Bws<64> url("http:\\/\\/domain\\/path?query");
    Json::Unescape(url);
    TEST(url == Brn("http://domain/path?query"));
}

void SuiteJsonDecode::DecodeChar(const TChar* aEncoded, TByte aDecoded)
{ // static
    Bws<6> buf(aEncoded);
    Json::Unescape(buf);
    TEST(buf.Bytes() == 1);
    TEST(buf[0] == aDecoded);
}

void TestJson()
{
    Runner runner("JSON tests\n");
    runner.Add(new SuiteJsonEncode());
    runner.Add(new SuiteJsonDecode());
    runner.Run();
}
