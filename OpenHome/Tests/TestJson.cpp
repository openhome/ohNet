#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Private/SuiteUnitTest.h>
#include <OpenHome/Private/Json.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Stream.h>
#include <functional>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

namespace OpenHome {

class SuiteJsonEncode : public Suite, private IWriter
{
public:
    SuiteJsonEncode();
private: // from Suite
    void Test();
private:
    void EncodeChar(TByte aChar, const TChar* aEncoded);
    void EncodeUni(TByte aChar);
private: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    Bws<128> iEncoded;
};

class SuiteJsonDecode : public Suite
{
public:
    SuiteJsonDecode();
private: // from Suite
    void Test();
private:
    static void DecodeChar(const TChar* aEncoded, TByte aDecoded);
};

class SuiteJsonParser : public SuiteUnitTest
{
public:
    SuiteJsonParser();
public: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestParseUnescapeInPlace();
    void TestParseNoUnescapeInPlace();
    void TestParseArray();
    void TestParseObject();
    void TestParseEmptyObject();
    void TestValidKey();
    void TestInvalidKey();
    void TestGetValidString();
    void TestGetInvalidString();
    void TestGetOptionalString();
    void TestGetValidNum();
    void TestGetInvalidNum();
    void TestGetStringAsNum();
    void TestGetNumAsString();
    void TestGetValidBool();
    void TestCorruptInput();
    void TestParseNull();
    void TestParseUnicodeEscaped();
private:
    JsonParser* iParser;
};

class SuiteWriterJson : public SuiteUnitTest
{
public:
    SuiteWriterJson();
public: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestWriteInt();
    void TestWriteString();
    void TestWriteBool();
};

class SuiteWriterJsonObject : public SuiteUnitTest
{
public:
    SuiteWriterJsonObject();
public: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestWriteEmptyObject();
    void TestWriteInt();
    void TestWriteString();
    void TestWriteBool();
    void TestWriteStringStreamed();
    void TestWriteArray();
    void TestWriteObject();
    void TestWriteMixed();
    void TestAutoWriteEnd();
private:
    Bws<512> iBuf;
    WriterBuffer* iWriterBuf;
};

class SuiteWriterJsonArray : public SuiteUnitTest
{
public:
    SuiteWriterJsonArray();
public: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestWriteEmptyNull();
    void TestWriteEmptyArray();
    void TestWriteInt();
    void TestWriteString();
    void TestWriteBool();
    void TestWriteArray();
    void TestWriteObject();
    void TestWriteMixed();
    void TestAutoWriteEnd();
private:
    Bws<512> iBuf;
    WriterBuffer* iWriterBuf;
};

class SuiteParserJsonArray : public SuiteUnitTest
{
public:
    SuiteParserJsonArray();
public: // from SuiteUnitTest
    void Setup();
    void TearDown();
private:
    void TestIdentifyType();
    void TestIntArray();
    void TestBoolArray();
    void TestStringArray();
    void TestObjectArray();
    void TestArrayArray();
    void TestEmptyArray();
    void TestArrayInObject();
    void TestNullObjectArray();
    void TestNullArrayArray();
    void TestMultiTypeArray();
    void TestSubsetTypeArray();
    void TestCorruptArray();
    void TestArrayConclusion();
};

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
        EncodeUni((TByte)i);
    }
    // with very few exceptions, characters [0x20..0x7F] should not be encoded
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

void SuiteJsonEncode::EncodeUni(TByte aChar)
{
    iEncoded.SetBytes(0);
    Bws<1> ch(&aChar, 1);
    Json::Escape(*this, ch);
    TEST(iEncoded.Bytes() > 1);
    if (iEncoded.Bytes() > 2) {
        Brn start(iEncoded.Ptr(), 2);
        TEST(start == Brn("\\u"));
        TEST(Ascii::UintHex(iEncoded.Split(2)) == aChar);
    }
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

    for (TUint i=0; i<128; i++)
    {
        // Quotation marks are treated differently
        // See below...
        if (i == '\"') { // 34 | 0x22
            continue;
        }

        Bws<7> enc("\\u00");
        Ascii::AppendHex(enc, (TByte)i);
        DecodeChar(enc.PtrZ(), (TByte)i);
    }

    Bws<64> url("http:\\/\\/domain\\/path?query");
    Json::Unescape(url);
    TEST(url == Brn("http://domain/path?query"));

    Bws<32> buf("Dvo\\u0159\\u00e1k");
    TEST_THROWS(Json::Unescape(buf), JsonInvalid);
    Json::Unescape(buf, Json::Encoding::Utf16);
    TEST(buf == Brn("Dvo\xc5\x99\xc3\xa1k"));

    // Testing that unicode escaped quoaion marks are correctly
    // escaped to prevent invalid JSON
    const Brn unicodeExpected("{\"x\":\"\\\"value\\\"\"}"); // "x" : "\"value\""
    Bws<64> unicodeBuf("{\"x\":\"\\u0022value\\u0022\"}");
    Bws<64> unicodeAsUtf8(unicodeBuf);
    Bws<64> unicodeAsUtf16(unicodeAsUtf8);

    Json::Unescape(unicodeAsUtf8); // Default is UTF8
    Json::Unescape(unicodeAsUtf16);

    TEST(unicodeAsUtf8 == unicodeExpected);
    TEST(unicodeAsUtf16 == unicodeExpected);
}

void SuiteJsonDecode::DecodeChar(const TChar* aEncoded, TByte aDecoded)
{ // static
    Bws<6> buf(aEncoded);
    Json::Unescape(buf);
    TEST(buf.Bytes() == 1);
    TEST(buf[0] == aDecoded);
}


// SuiteJsonParser

SuiteJsonParser::SuiteJsonParser()
    : SuiteUnitTest("SuiteJsonParser")
{
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestParseUnescapeInPlace), "TestParseUnescapeInPlace");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestParseNoUnescapeInPlace), "TestParseNoUnescapeInPlace");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestParseArray), "TestParseArray");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestParseObject), "TestParseObject");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestParseEmptyObject), "TestParseEmptyObject");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestValidKey), "TestValidKey");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestInvalidKey), "TestInvalidKey");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestGetValidString), "TestGetValidString");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestGetInvalidString), "TestGetInvalidString");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestGetOptionalString), "TestGetOptionalString");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestGetValidNum), "TestGetValidNum");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestGetInvalidNum), "TestGetInvalidNum");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestGetStringAsNum), "TestGetStringAsNum");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestGetNumAsString), "TestGetNumAsString");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestGetValidBool), "TestGetValidBool");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestCorruptInput), "TestCorruptInput");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestParseNull), "TestParseNull");
    AddTest(MakeFunctor(*this, &SuiteJsonParser::TestParseUnicodeEscaped), "TestParseUnicodeEscaped");
}

void SuiteJsonParser::Setup()
{
    iParser = new JsonParser();
}

void SuiteJsonParser::TearDown()
{
    delete iParser;
}

void SuiteJsonParser::TestParseUnescapeInPlace()
{
    Bwh json1("{\"key\":\"\\\"\"}");
    iParser->ParseAndUnescape(json1);
    TEST(iParser->HasKey("key"));
    TEST(iParser->String("key") == Brn("\""));

    Bwh json2("{\"key1\":\"line1\\\"\\\\\\/\\b\\f\\n\\r\\tline2\"}");
    iParser->ParseAndUnescape(json2);
    TEST(iParser->HasKey("key1"));
    TEST(iParser->String("key1") == Brn("line1\"\\/\b\f\n\r\tline2"));

    Bwh json3("{\"key1\":\"foo\",\"stringified\":\"{\\\"bool1\\\":true,\\\"bool2\\\":false}\"}");
    iParser->ParseAndUnescape(json3);
    TEST(iParser->HasKey("key1"));
    TEST(iParser->String("key1") == Brn("foo"));
    TEST(iParser->HasKey("stringified"));
    JsonParser parser2;
    Brn stringified(iParser->String("stringified"));
    Bwn json4(stringified.Ptr(), stringified.Bytes(), stringified.Bytes());
    parser2.ParseAndUnescape(json4);
    TEST(parser2.HasKey("bool1"));
    TEST(parser2.HasKey("bool2"));
    TEST(parser2.Bool("bool1"));
    TEST(!parser2.Bool("bool2"));
}

void SuiteJsonParser::TestParseNoUnescapeInPlace()
{
    Bwh json("{\"key1\":\"line1\\\"\\\\\\/\\b\\f\\n\\r\\tline2\"}");
    iParser->Parse(json);
    TEST(iParser->HasKey("key1"));
    TEST(iParser->String("key1") == Brn("line1\\\"\\\\\\/\\b\\f\\n\\r\\tline2"));
}

void SuiteJsonParser::TestParseArray()
{
    const Brn json("[\"val1\", 2, false, \"val4\"]");

    // FIXME - arrays appear to be unsupported.
    // FIXME - maybe throw a JsonUnsupported instead?
    TEST_THROWS(iParser->Parse(json), JsonCorrupt);
}

void SuiteJsonParser::TestParseObject()
{
    const Brn json("{\"key1\":{\"key2\":{\"key3\": 3, \"key4\":4}, \"key5\":\"val5\"}}");

    iParser->Parse(json);
    TEST(iParser->HasKey("key1"));
    Brn nextObject = iParser->String("key1");
    TEST(nextObject == Brn("{\"key2\":{\"key3\": 3, \"key4\":4}, \"key5\":\"val5\"}"));

    iParser->Parse(nextObject);
    TEST(iParser->HasKey("key2"));
    nextObject = iParser->String("key2");
    TEST(nextObject == Brn("{\"key3\": 3, \"key4\":4}"));

    TEST(iParser->HasKey("key5"));
    TEST(iParser->String("key5") == Brn("val5"));

    iParser->Parse(nextObject);
    TEST(iParser->HasKey("key3"));
    TEST(iParser->Num("key3") == 3);

    TEST(iParser->HasKey("key4"));
    TEST(iParser->Num("key4") == 4);
}

void SuiteJsonParser::TestParseEmptyObject()
{
    Brn json("{}");
    iParser->Parse(json);
    std::vector<Brn> keys;
    iParser->GetKeys(keys);
    TEST(keys.size() == 0);

    iParser->Reset();
    json.Set("");
    iParser->Parse(json);
    iParser->GetKeys(keys);
    TEST(keys.size() == 0);

    iParser->Reset();
    json.Set("null");
    iParser->Parse(json);
    iParser->GetKeys(keys);
    TEST(keys.size() == 0);
}

void SuiteJsonParser::TestValidKey()
{
    const Brn json("{\"key1\":\"val1\"}");

    iParser->Parse(json);
    TEST(iParser->HasKey("key1"));
    TEST(iParser->HasKey(Brn("key1")));
}

void SuiteJsonParser::TestInvalidKey()
{
    const Brn json("{\"key1\":\"val1\"}");

    iParser->Parse(json);
    TEST(iParser->HasKey("key2") == false);
    TEST(iParser->HasKey(Brn("key2")) == false);
}

void SuiteJsonParser::TestGetValidString()
{
    const Brn json("{\"key1\":\"val1\"}");

    iParser->Parse(json);
    TEST(iParser->String("key1") == Brn("val1"));
    TEST(iParser->String(Brn("key1")) == Brn("val1"));
}

void SuiteJsonParser::TestGetInvalidString()
{
    const Brn json("{\"key1\":\"val1\"}");

    iParser->Parse(json);
    TEST_THROWS(iParser->String("key2"), JsonKeyNotFound);
    TEST_THROWS(iParser->String(Brn("key2")), JsonKeyNotFound);
}

void SuiteJsonParser::TestGetOptionalString()
{
    Brn json("{\"key1\":null}");

    iParser->Parse(json);
    TEST(iParser->StringOptional("key1") == Brx::Empty());
    TEST(iParser->StringOptional("key2") == Brx::Empty());
}

void SuiteJsonParser::TestGetValidNum()
{
    // FIXME - fails

    //const TBool unescapeInPlace = false;
    //const Brn json("{\"key1\": 1}");

    //iParser->Parse(json, unescapeInPlace);
    //TEST(iParser->Num("key1") == 1);
    //TEST(iParser->Num(Brn("key1")) == 1);
}

void SuiteJsonParser::TestGetInvalidNum()
{
    // FIXME - fails

    //const TBool unescapeInPlace = false;
    //const Brn json("{\"key1\":1}");

    //iParser->Parse(json, unescapeInPlace);
    //TEST_THROWS(iParser->Num("key2"), JsonKeyNotFound);
    //TEST_THROWS(iParser->Num(Brn("key2")), JsonKeyNotFound);
}

void SuiteJsonParser::TestGetStringAsNum()
{
    const Brn json("{\"key1\":\"val1\"}");

    iParser->Parse(json);
    TEST_THROWS(iParser->Num("key2"), JsonKeyNotFound);
    TEST_THROWS(iParser->Num(Brn("key2")), JsonKeyNotFound);
}

void SuiteJsonParser::TestGetNumAsString()
{
    // FIXME - fails
    //const TBool unescapeInPlace = false;
    //const Brn json("{\"key1\":1}");

    //iParser->Parse(json, unescapeInPlace);
    //TEST_THROWS(iParser->String("key2"), JsonKeyNotFound);
    //TEST_THROWS(iParser->String(Brn("key2")), JsonKeyNotFound);
}

void SuiteJsonParser::TestGetValidBool()
{
    const Brn json("{\"key1\":true,\"key2\":     \n\n\n\nfalse      \n \n}");

    iParser->Parse(json);
    TEST(iParser->Bool("key1"));
    TEST(!iParser->Bool("key2"));
    TEST_THROWS(iParser->Bool("key3"), JsonKeyNotFound);
}

void SuiteJsonParser::TestCorruptInput()
{
    TEST_THROWS(iParser->Parse(Brn("{\"key1:1}")), JsonCorrupt);   // No closing quote around key string.
    TEST_THROWS(iParser->Parse(Brn("\"key1\":1")), JsonCorrupt);   // Unenclosed object.
    TEST_THROWS(iParser->Parse(Brn("\"key1\":1}")), JsonCorrupt);  // Object not opened.
    TEST_THROWS(iParser->Parse(Brn("{\"key1\":1")), JsonCorrupt);  // Object not closed.
    TEST_THROWS(iParser->Parse(Brn("{\"key1\":}")), JsonCorrupt);  // No value.
    TEST_THROWS(iParser->Parse(Brn("{:1}")), JsonCorrupt);         // No key.
    TEST_THROWS(iParser->Parse(Brn("{\"key1\" 1")), JsonCorrupt);  // No separator.
    TEST_THROWS(iParser->Parse(Brn("{1:2}")), JsonCorrupt);        // Number as key.
    TEST_THROWS(iParser->Parse(Brn("{true:2}")), JsonCorrupt);     // Boolean as key.
}

void SuiteJsonParser::TestParseNull()
{
    const Brn json("{\"obj\":null,\"str\":null,\"foo\":\"bar\"}");
    iParser->Parse(json);

    TEST(iParser->HasKey("obj"));
    TEST(iParser->HasKey("str"));
    TEST(iParser->HasKey("foo"));
    TEST(iParser->IsNull("obj"));
    TEST(iParser->IsNull("str"));
    TEST(!iParser->IsNull("foo"));
    TEST_THROWS(iParser->String("obj"), JsonValueNull);
    TEST_THROWS(iParser->String("str"), JsonValueNull);
    TEST(iParser->String("foo") == Brn("bar"));
}

void SuiteJsonParser::TestParseUnicodeEscaped()
{
    const Brn json("{\"key\":\"\\u0000\\u0000\\u0000U\"}");
    iParser->Parse(json);

    TEST(iParser->HasKey("key"));
    TEST(!iParser->IsNull("key"));
    TEST(iParser->String("key") == Brn("\\u0000\\u0000\\u0000U"));
    iParser->Reset();

    Bws<4> valueExpected;
    WriterBuffer writerBuffer(valueExpected);
    WriterBinary writerBinary(writerBuffer);
    writerBinary.WriteUint32Be(85);

    Bwh jsonWritable(json);
    iParser->ParseAndUnescape(jsonWritable);
    TEST(iParser->HasKey("key"));
    TEST(!iParser->IsNull("key"));
    TEST(iParser->String("key") == valueExpected);
}


// SuiteWriterJson

SuiteWriterJson::SuiteWriterJson()
    : SuiteUnitTest("SuiteWriterJson")
{
    AddTest(MakeFunctor(*this, &SuiteWriterJson::TestWriteInt), "TestWriteInt");
    AddTest(MakeFunctor(*this, &SuiteWriterJson::TestWriteString), "TestWriteString");
    AddTest(MakeFunctor(*this, &SuiteWriterJson::TestWriteBool), "TestWriteBool");
}

void SuiteWriterJson::Setup()
{
}

void SuiteWriterJson::TearDown()
{
}

void SuiteWriterJson::TestWriteInt()
{
    Bws<32> buf;
    WriterBuffer writerBuf(buf);

    WriterJson::WriteValueInt(writerBuf, -2147483647);
    TEST(buf == Brn("-2147483647"));

    buf.SetBytes(0);
    WriterJson::WriteValueInt(writerBuf, 2147483647);
    TEST(buf == Brn("2147483647"));

    buf.SetBytes(0);
    WriterJson::WriteValueInt(writerBuf, 0);
    TEST(buf == Brn("0"));

    buf.SetBytes(0);
    WriterJson::WriteValueInt(writerBuf, -256);
    TEST(buf == Brn("-256"));

    buf.SetBytes(0);
    WriterJson::WriteValueInt(writerBuf, 256);
    TEST(buf == Brn("256"));
}

void SuiteWriterJson::TestWriteString()
{
    Bws<32> buf;
    WriterBuffer writerBuf(buf);

    WriterJson::WriteValueString(writerBuf, Brn());
    TEST(buf == Brn("\"\""));

    buf.SetBytes(0);
    WriterJson::WriteValueString(writerBuf, Brn("a string"));
    TEST(buf == (Brn("\"a string\"")));

    buf.SetBytes(0);
    WriterJson::WriteValueString(writerBuf, Brn("line1\"\\/\b\f\n\r\tline2"));
    TEST(buf == Brn("\"line1\\\"\\\\\\/\\b\\f\\n\\r\\tline2\""));
}

void SuiteWriterJson::TestWriteBool()
{
    Bws<32> buf;
    WriterBuffer writerBuf(buf);

    WriterJson::WriteValueBool(writerBuf, false);
    TEST(buf == Brn("false"));

    buf.SetBytes(0);
    WriterJson::WriteValueBool(writerBuf, true);
    TEST(buf == Brn("true"));
}


// SuiteWriterJsonObject

SuiteWriterJsonObject::SuiteWriterJsonObject()
    : SuiteUnitTest("SuiteWriterJsonObject")
{
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestWriteEmptyObject), "TestWriteEmptyObject");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestWriteInt), "TestWriteInt");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestWriteString), "TestWriteString");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestWriteBool), "TestWriteBool");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestWriteStringStreamed), "TestWriteStringStreamed");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestWriteArray), "TestWriteArray");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestWriteObject), "TestWriteObject");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestWriteMixed), "TestWriteMixed");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonObject::TestAutoWriteEnd), "TestAutoWriteEnd");
}

void SuiteWriterJsonObject::Setup()
{
    iWriterBuf = new WriterBuffer(iBuf);
}

void SuiteWriterJsonObject::TearDown()
{
    delete iWriterBuf;
    iBuf.SetBytes(0);
}

void SuiteWriterJsonObject::TestWriteEmptyObject()
{
    WriterJsonObject jsonWriter1(*iWriterBuf);
    jsonWriter1.WriteEnd();
    TEST(iBuf == Brn("null"));
}

void SuiteWriterJsonObject::TestWriteInt()
{
    // Write key using const TChar*.
    WriterJsonObject jsonWriter1(*iWriterBuf);
    jsonWriter1.WriteInt("key1", 256);
    jsonWriter1.WriteEnd();
    TEST(iBuf == Brn("{\"key1\":256}"));

    iBuf.SetBytes(0);
    // Write key using const Brx&.
    WriterJsonObject jsonWriter2(*iWriterBuf);
    jsonWriter2.WriteInt(Brn("key2"), 256);
    jsonWriter2.WriteEnd();
    TEST(iBuf == Brn("{\"key2\":256}"));
}

void SuiteWriterJsonObject::TestWriteString()
{
    // Write key using const TChar*, val using const TChar*.
    WriterJsonObject jsonWriter1(*iWriterBuf);
    jsonWriter1.WriteString("key1", "val1");
    jsonWriter1.WriteEnd();
    TEST(iBuf == Brn("{\"key1\":\"val1\"}"));

    iBuf.SetBytes(0);
    // Write key using const TChar*, val using const Brx&.
    WriterJsonObject jsonWriter2(*iWriterBuf);
    jsonWriter2.WriteString("key2", Brn("val2"));
    jsonWriter2.WriteEnd();
    TEST(iBuf == Brn("{\"key2\":\"val2\"}"));

    iBuf.SetBytes(0);
    // Write key using const Brx&, val using const Brx&.
    WriterJsonObject jsonWriter3(*iWriterBuf);
    jsonWriter3.WriteString(Brn("key3"), Brn("val3"));
    jsonWriter3.WriteEnd();
    TEST(iBuf == Brn("{\"key3\":\"val3\"}"));

    iBuf.SetBytes(0);
    // Write empty key and val.
    WriterJsonObject jsonWriter4(*iWriterBuf);
    jsonWriter4.WriteString(Brn(""), Brn(""));
    jsonWriter4.WriteEnd();
    TEST(iBuf == Brn("{\"\":\"\"}"));
}

void SuiteWriterJsonObject::TestWriteBool()
{
    // Write key using const TChar*, val false.
    WriterJsonObject jsonWriter1(*iWriterBuf);
    jsonWriter1.WriteBool("key1", false);
    jsonWriter1.WriteEnd();
    TEST(iBuf == Brn("{\"key1\":false}"));

    iBuf.SetBytes(0);
    // Write key using const Brx&, val false.
    WriterJsonObject jsonWriter2(*iWriterBuf);
    jsonWriter2.WriteBool(Brn("key2"), false);
    jsonWriter2.WriteEnd();
    TEST(iBuf == Brn("{\"key2\":false}"));

    iBuf.SetBytes(0);
    // Write key using const TChar*, val true.
    WriterJsonObject jsonWriter3(*iWriterBuf);
    jsonWriter3.WriteBool("key3", true);
    jsonWriter3.WriteEnd();
    TEST(iBuf == Brn("{\"key3\":true}"));

    iBuf.SetBytes(0);
    // Write key using const Brx&, val true.
    WriterJsonObject jsonWriter4(*iWriterBuf);
    jsonWriter4.WriteBool(Brn("key4"), true);
    jsonWriter4.WriteEnd();
    TEST(iBuf == Brn("{\"key4\":true}"));
}

void SuiteWriterJsonObject::TestWriteStringStreamed()
{
    WriterJsonObject jsonWriter1(*iWriterBuf);
    WriterJsonValueString jsonWriter2 = jsonWriter1.CreateStringStreamed("key1");
    jsonWriter2.Write(Brn("123"));
    jsonWriter2.Write(Brn("4567"));
    jsonWriter2.Write(Brn("89"));
    jsonWriter2.WriteEnd();
    jsonWriter1.WriteEnd();
    TEST(iBuf == Brn("{\"key1\":\"123456789\"}"));

    iBuf.SetBytes(0);
    WriterJsonObject jsonWriter3(*iWriterBuf);
    WriterJsonValueString jsonWriter4 = jsonWriter3.CreateStringStreamed("key2");
    jsonWriter4.WriteEscaped(Brn("\r\n"));
    jsonWriter4.WriteEscaped(Brn("\t"));
    jsonWriter4.WriteEnd();
    jsonWriter3.WriteEnd();
    TEST(iBuf == Brn("{\"key2\":\"\\r\\n\\t\"}"));
}

void SuiteWriterJsonObject::TestWriteArray()
{
    // Write key using const TChar*.
    WriterJsonObject jsonWriter1(*iWriterBuf);
    WriterJsonArray array1 = jsonWriter1.CreateArray("key1");
    array1.WriteInt(256);
    array1.WriteString(Brn("val2"));
    array1.WriteBool(false);
    array1.WriteEnd();
    jsonWriter1.WriteEnd();
    TEST(iBuf == Brn("{\"key1\":[256,\"val2\",false]}"));

    iBuf.SetBytes(0);
    // Write key using const TChar*.
    WriterJsonObject jsonWriter2(*iWriterBuf);
    WriterJsonArray array2 = jsonWriter2.CreateArray("key2");
    array2.WriteInt(256);
    array2.WriteString(Brn("val2"));
    array2.WriteBool(false);
    array2.WriteEnd();
    jsonWriter2.WriteEnd();
    TEST(iBuf == Brn("{\"key2\":[256,\"val2\",false]}"));

    // Write empty array.
    iBuf.SetBytes(0);
    WriterJsonObject jsonWriter3(*iWriterBuf);
    WriterJsonArray array3 = jsonWriter3.CreateArray("key3");
    array3.WriteEnd();
    jsonWriter3.WriteEnd();
    TEST(iBuf == Brn("{\"key3\":null}"));
}

void SuiteWriterJsonObject::TestWriteObject()
{
    // Write key using const TChar*.
    WriterJsonObject jsonWriter1(*iWriterBuf);
    WriterJsonObject obj1 = jsonWriter1.CreateObject("key1");
    obj1.WriteInt("key2", 256);
    obj1.WriteEnd();
    jsonWriter1.WriteEnd();
    TEST(iBuf == Brn("{\"key1\":{\"key2\":256}}"));

    iBuf.SetBytes(0);
    // Write key using const TChar*.
    WriterJsonObject jsonWriter2(*iWriterBuf);
    WriterJsonObject obj2 = jsonWriter2.CreateObject("key1");
    obj2.WriteInt("key2", 256);
    obj2.WriteEnd();
    jsonWriter2.WriteEnd();
    TEST(iBuf == Brn("{\"key1\":{\"key2\":256}}"));

    // Write empty object.
    iBuf.SetBytes(0);
    WriterJsonObject jsonWriter3(*iWriterBuf);
    WriterJsonObject obj3 = jsonWriter3.CreateObject("key3");
    obj3.WriteEnd();
    jsonWriter3.WriteEnd();
    TEST(iBuf == Brn("{\"key3\":null}"));   // FIXME - why is this "null" and not an empty object (i.e., {})? TestWriteEmptyObject() writes {}.
}

void SuiteWriterJsonObject::TestWriteMixed()
{
    WriterJsonObject jsonWriter(*iWriterBuf);
    jsonWriter.WriteInt("key1", -128);
    jsonWriter.WriteString("key2", "str1");
    jsonWriter.WriteBool("key3", false);

    WriterJsonArray jsonArray = jsonWriter.CreateArray("key4");
    jsonArray.WriteInt(128);
    jsonArray.WriteString(Brn("str2"));
    jsonArray.WriteBool(true);
    jsonArray.WriteEnd();

    WriterJsonObject jsonObject = jsonWriter.CreateObject("key5");
    jsonObject.WriteInt("key6", 256);
    jsonObject.WriteString("key7", "str3");
    jsonObject.WriteBool("key8", true);
    jsonObject.WriteEnd();

    jsonWriter.WriteEnd();

    TEST(iBuf == Brn("{\"key1\":-128,\"key2\":\"str1\",\"key3\":false,\"key4\":[128,\"str2\",true],\"key5\":{\"key6\":256,\"key7\":\"str3\",\"key8\":true}}"));
}

void SuiteWriterJsonObject::TestAutoWriteEnd()
{
    {
        WriterJsonObject jsonWriter(*iWriterBuf);
        AutoWriterJson _(jsonWriter);
        jsonWriter.WriteInt("key1", 256);
    }
    TEST(iBuf == Brn("{\"key1\":256}"));
}


// SuiteWriterJsonArray

SuiteWriterJsonArray::SuiteWriterJsonArray()
    : SuiteUnitTest("SuiteWriterJsonArray")
{
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestWriteEmptyNull), "TestWriteEmptyNull");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestWriteEmptyArray), "TestWriteEmptyArray");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestWriteInt), "TestWriteInt");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestWriteString), "TestWriteString");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestWriteBool), "TestWriteBool");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestWriteArray), "TestWriteArray");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestWriteObject), "TestWriteObject");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestWriteMixed), "TestWriteMixed");
    AddTest(MakeFunctor(*this, &SuiteWriterJsonArray::TestAutoWriteEnd), "TestAutoWriteEnd");
}

void SuiteWriterJsonArray::Setup()
{
    iWriterBuf = new WriterBuffer(iBuf);
}

void SuiteWriterJsonArray::TearDown()
{
    delete iWriterBuf;
    iBuf.SetBytes(0);
}

void SuiteWriterJsonArray::TestWriteEmptyNull()
{
    // By default, WriterJsonArray writes a "null" object when no array entries
    // written.
    WriterJsonArray jsonArray1(*iWriterBuf);
    jsonArray1.WriteEnd();
    TEST(iBuf == Brn("null"));

    iBuf.SetBytes(0);
    // Check behaviour is the same when writing of "null" object is
    // specifically requested.
    WriterJsonArray jsonArray2(*iWriterBuf, WriterJsonArray::WriteOnEmpty::eNull);
    jsonArray2.WriteEnd();
    TEST(iBuf == Brn("null"));
}

void SuiteWriterJsonArray::TestWriteEmptyArray()
{
    WriterJsonArray jsonArray(*iWriterBuf, WriterJsonArray::WriteOnEmpty::eEmptyArray);
    jsonArray.WriteEnd();
    TEST(iBuf == Brn("[]"));
}

void SuiteWriterJsonArray::TestWriteInt()
{
    WriterJsonArray jsonArray(*iWriterBuf);
    jsonArray.WriteInt(256);
    jsonArray.WriteEnd();
    TEST(iBuf == Brn("[256]"));
}

void SuiteWriterJsonArray::TestWriteString()
{
    // Empty string.
    WriterJsonArray jsonArray1(*iWriterBuf);
    jsonArray1.WriteString(Brn(""));
    jsonArray1.WriteEnd();
    TEST(iBuf == Brn("[\"\"]"));

    iBuf.SetBytes(0);
    // Non-empty string, with chars requiring escaping.
    WriterJsonArray jsonArray2(*iWriterBuf);
    jsonArray2.WriteString(Brn("line1\r\nline2"));
    jsonArray2.WriteEnd();
    TEST(iBuf == Brn("[\"line1\\r\\nline2\"]"));
}

void SuiteWriterJsonArray::TestWriteBool()
{
    // Write false.
    WriterJsonArray jsonArray1(*iWriterBuf);
    jsonArray1.WriteBool(false);
    jsonArray1.WriteEnd();
    TEST(iBuf == Brn("[false]"));

    iBuf.SetBytes(0);
    // Write true.
    WriterJsonArray jsonArray2(*iWriterBuf);
    jsonArray2.WriteBool(true);
    jsonArray2.WriteEnd();
    TEST(iBuf == Brn("[true]"));
}

void SuiteWriterJsonArray::TestWriteArray()
{
    WriterJsonArray jsonArray(*iWriterBuf);
    WriterJsonArray jsonArrayNested = jsonArray.CreateArray();
    jsonArrayNested.WriteInt(256);
    jsonArrayNested.WriteString(Brn("str"));
    jsonArrayNested.WriteBool(false);
    jsonArrayNested.WriteEnd();
    jsonArray.WriteEnd();
    TEST(iBuf == Brn("[[256,\"str\",false]]"));
}

void SuiteWriterJsonArray::TestWriteObject()
{
    WriterJsonArray jsonArray(*iWriterBuf);
    WriterJsonObject jsonObjectNested = jsonArray.CreateObject();
    jsonObjectNested.WriteInt("key1", 256);
    jsonObjectNested.WriteString("key2", "str");
    jsonObjectNested.WriteBool("key3", false);
    jsonObjectNested.WriteEnd();
    jsonArray.WriteEnd();
    TEST(iBuf == Brn("[{\"key1\":256,\"key2\":\"str\",\"key3\":false}]"));
}

void SuiteWriterJsonArray::TestWriteMixed()
{
    WriterJsonArray jsonArray(*iWriterBuf);
    jsonArray.WriteInt(256);
    jsonArray.WriteString(Brn("line1\r\nline2"));
    jsonArray.WriteBool(false);

    WriterJsonArray jsonArrayNested = jsonArray.CreateArray();
    jsonArrayNested.WriteInt(256);
    jsonArrayNested.WriteString(Brn("str"));
    jsonArrayNested.WriteBool(false);
    jsonArrayNested.WriteEnd();

    WriterJsonObject jsonObjectNested = jsonArray.CreateObject();
    jsonObjectNested.WriteInt("key1", 256);
    jsonObjectNested.WriteString("key2", "str");
    jsonObjectNested.WriteBool("key3", false);
    jsonObjectNested.WriteEnd();

    jsonArray.WriteEnd();

    TEST(iBuf == Brn("[256,\"line1\\r\\nline2\",false,[256,\"str\",false],{\"key1\":256,\"key2\":\"str\",\"key3\":false}]"));
}

void SuiteWriterJsonArray::TestAutoWriteEnd()
{
    {
        WriterJsonArray jsonArray(*iWriterBuf);
        AutoWriterJson _(jsonArray);
        jsonArray.WriteInt(256);
    }
    TEST(iBuf == Brn("[256]"));
}


// SuiteParserJsonArray

SuiteParserJsonArray::SuiteParserJsonArray()
    : SuiteUnitTest("SuiteParserJsonArray")
{
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestIdentifyType), "TestIdentifyType");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestIntArray), "TestIntArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestBoolArray), "TestBoolArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestStringArray), "TestStringArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestObjectArray), "TestObjectArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestArrayArray), "TestArrayArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestEmptyArray), "TestEmptyArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestArrayInObject), "TestArrayInObject");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestNullObjectArray), "TestNullObjectArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestNullArrayArray), "TestNullArrayArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestMultiTypeArray), "TestMultiTypeArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestSubsetTypeArray), "TestSubsetTypeArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestCorruptArray), "TestCorruptArray");
    AddTest(MakeFunctor(*this, &SuiteParserJsonArray::TestArrayConclusion), "TestArrayConclusion");

}

void SuiteParserJsonArray::Setup()
{
}

void SuiteParserJsonArray::TearDown()
{
}

void SuiteParserJsonArray::TestIdentifyType()
{
    JsonParserArray parser1 = JsonParserArray::Create(Brn("[1,2,3]"));
    TEST(parser1.Type() == JsonParserArray::ValType::Int);
    TEST(parser1.EntryType() == JsonParserArray::ValType::Int);
    JsonParserArray parser2 = JsonParserArray::Create(Brn("[-9,0]"));
    TEST(parser2.Type() == JsonParserArray::ValType::Int);
    TEST(parser2.EntryType() == JsonParserArray::ValType::Int);

    JsonParserArray parser3 = JsonParserArray::Create(Brn("[true]"));
    TEST(parser3.Type() == JsonParserArray::ValType::Bool);
    TEST(parser3.EntryType() == JsonParserArray::ValType::Bool);
    JsonParserArray parser4 = JsonParserArray::Create(Brn("[false]"));
    TEST(parser4.Type() == JsonParserArray::ValType::Bool);
    TEST(parser4.EntryType() == JsonParserArray::ValType::Bool);

    JsonParserArray parser5 = JsonParserArray::Create(Brn("null"));
    TEST(parser5.Type() == JsonParserArray::ValType::Null);
    TEST(parser5.EntryType() == JsonParserArray::ValType::Null);

    JsonParserArray parser6 = JsonParserArray::Create(Brn("[\"foo\"]"));
    TEST(parser6.Type() == JsonParserArray::ValType::String);
    TEST(parser6.EntryType() == JsonParserArray::ValType::String);

    JsonParserArray parser7 = JsonParserArray::Create(Brn("[{\"foo\":1}]"));
    TEST(parser7.Type() == JsonParserArray::ValType::Object);
    TEST(parser7.EntryType() == JsonParserArray::ValType::Object);

    JsonParserArray parser8 = JsonParserArray::Create(Brn("[[1,2],[3,4,5]]"));
    TEST(parser8.Type() == JsonParserArray::ValType::Array);
    TEST(parser8.EntryType() == JsonParserArray::ValType::Array);

    JsonParserArray parser9 = JsonParserArray::Create(Brn("[null]"));
    TEST(parser9.Type() == JsonParserArray::ValType::NullEntry);
    TEST(parser9.EntryType() == JsonParserArray::ValType::NullEntry);

    JsonParserArray parser10 = JsonParserArray::Create(Brn("[]"));
    TEST(parser10.Type() == JsonParserArray::ValType::Null);
    TEST(parser10.EntryType() == JsonParserArray::ValType::Null);
}

void SuiteParserJsonArray::TestIntArray()
{
    JsonParserArray parser = JsonParserArray::Create(Brn("[ 1,2, -3]"));
    TEST(parser.NextInt() == 1);
    TEST_THROWS(parser.NextBool(), JsonWrongType);
    TEST_THROWS(parser.NextString(), JsonWrongType);
    TEST_THROWS(parser.NextObject(), JsonWrongType);
    TEST_THROWS(parser.NextArray(), JsonWrongType);
    TEST_THROWS(parser.NextNull(), JsonWrongType);
    TEST(parser.NextInt() == 2);
    TEST(parser.NextInt() == -3);
    TEST(parser.EntryType() == JsonParserArray::ValType::End);
}

void SuiteParserJsonArray::TestBoolArray()
{
    JsonParserArray parser = JsonParserArray::Create(Brn("[true, false,true ]"));
    TEST(parser.NextBool());
    TEST_THROWS(parser.NextInt(), JsonWrongType);
    TEST_THROWS(parser.NextString(), JsonWrongType);
    TEST_THROWS(parser.NextObject(), JsonWrongType);
    TEST_THROWS(parser.NextArray(), JsonWrongType);
    TEST_THROWS(parser.NextNull(), JsonWrongType);
    TEST(!parser.NextBool());
    TEST(parser.NextBool());
    TEST(parser.EntryType() == JsonParserArray::ValType::End);
}

void SuiteParserJsonArray::TestStringArray()
{
    JsonParserArray parser1 = JsonParserArray::Create(Brn("[\"foo\",\"bar\"]"));
    TEST(parser1.NextString() == Brn("foo"));
    TEST_THROWS(parser1.NextInt(), JsonWrongType);
    TEST_THROWS(parser1.NextBool(), JsonWrongType);
    TEST_THROWS(parser1.NextObject(), JsonWrongType);
    TEST_THROWS(parser1.NextArray(), JsonWrongType);
    TEST_THROWS(parser1.NextNull(), JsonWrongType);
    TEST(parser1.NextString() == Brn("bar"));
    TEST(parser1.EntryType() == JsonParserArray::ValType::End);

    JsonParserArray parser2 = JsonParserArray::Create(Brn("[ \"foo\" , \"bar\" ]"));
    TEST(parser2.NextString() == Brn("foo"));
    TEST(parser2.NextString() == Brn("bar"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::End);

    Bws<16> arrW("[\"\\\"\"]");
    JsonParserArray parser3 = JsonParserArray::Create(arrW);
    TEST(parser3.NextStringEscaped() == Brn("\""));
    TEST(parser3.EntryType() == JsonParserArray::ValType::End);

    Bws<64> arrW2("[\" \\\" \\\\ \\/ \\b \\f \\n \\r \\t \"]");
    JsonParserArray parser4 = JsonParserArray::Create(arrW2);
    TEST(parser4.NextStringEscaped() == Brn(" \" \\ / \b \f \n \r \t "));
    TEST(parser4.EntryType() == JsonParserArray::ValType::End);


    Brn result;

    // Using TryNextString()
    JsonParserArray parser5 = JsonParserArray::Create(Brn("[\"foo\",\"bar\"]"));
    TEST(parser5.TryNextString(result));
    TEST(result == Brn("foo"));
    TEST(parser5.TryNextString(result));
    TEST(result == Brn("bar"));

    JsonParserArray parser6 = JsonParserArray::Create(Brn("[ \"foo\" , \"bar\" ]"));
    TEST(parser6.TryNextString(result));
    TEST(result == Brn("foo"));
    TEST(parser6.TryNextString(result));
    TEST(result == Brn("bar"));
}

void SuiteParserJsonArray::TestObjectArray()
{
    {
        JsonParserArray parser = JsonParserArray::Create(Brn("[{\"val\":0}, {\"val\":1} ]"));
        TEST(parser.NextObject() == Brn("{\"val\":0}"));
        TEST_THROWS(parser.NextBool(), JsonWrongType);
        TEST_THROWS(parser.NextInt(), JsonWrongType);
        TEST_THROWS(parser.NextString(), JsonWrongType);
        TEST_THROWS(parser.NextArray(), JsonWrongType);
        TEST_THROWS(parser.NextNull(), JsonWrongType);
        TEST(parser.NextObject() == Brn("{\"val\":1}"));
        TEST(parser.EntryType() == JsonParserArray::ValType::End);

        JsonParserArray parser2 = JsonParserArray::Create(Brn("[{\"val\":\"open{\"}, {\"val\":\"close}\"} ]"));
        TEST(parser2.NextObject() == Brn("{\"val\":\"open{\"}"));
        TEST(parser2.NextObject() == Brn("{\"val\":\"close}\"}"));
        TEST(parser2.EntryType() == JsonParserArray::ValType::End);
    }

    {
        Brn result;
        JsonParserArray parser = JsonParserArray::Create(Brn("[{\"val\":0}, {\"val\":1} ]"));

        TEST(parser.TryNextObject(result));
        TEST(result == Brn("{\"val\":0}"));
        TEST(parser.TryNextObject(result));
        TEST(result == Brn("{\"val\":1}"));
        TEST(parser.EntryType() == JsonParserArray::ValType::End);

        JsonParserArray parser2 = JsonParserArray::Create(Brn("[{\"val\":\"open{\"}, {\"val\":\"close}\"} ]"));
        TEST(parser2.TryNextObject(result));
        TEST(result == Brn("{\"val\":\"open{\"}"));
        TEST(parser2.TryNextObject(result));
        TEST(result == Brn("{\"val\":\"close}\"}"));
        TEST(parser2.EntryType() == JsonParserArray::ValType::End);
    }
}

void SuiteParserJsonArray::TestArrayArray()
{
    {
        JsonParserArray parser = JsonParserArray::Create(Brn("[[1,2],[3,4,5]]"));
        TEST(parser.NextArray() == Brn("[1,2]"));
        TEST_THROWS(parser.NextBool(), JsonWrongType);
        TEST_THROWS(parser.NextInt(), JsonWrongType);
        TEST_THROWS(parser.NextString(), JsonWrongType);
        TEST_THROWS(parser.NextObject(), JsonWrongType);
        TEST_THROWS(parser.NextNull(), JsonWrongType);
        TEST(parser.NextArray() == Brn("[3,4,5]"));
        TEST(parser.EntryType() == JsonParserArray::ValType::End);
    }
    {
        Brn result;
        JsonParserArray parser = JsonParserArray::Create(Brn("[[1,2],[3,4,5]]"));
        TEST(parser.TryNextArray(result));
        TEST(result == Brn("[1,2]"));

        TEST(parser.TryNextArray(result));
        TEST(result == Brn("[3,4,5]"));
        TEST(parser.EntryType() == JsonParserArray::ValType::End);
    }
}

void SuiteParserJsonArray::TestEmptyArray()
{
    Brn result;

    {
        JsonParserArray parser = JsonParserArray::Create(Brn("[]"));
        TEST_THROWS(
            parser.NextBool(),
            JsonArrayEnumerationComplete);
    }
    {
        JsonParserArray parser = JsonParserArray::Create(Brn("[]"));
        TEST_THROWS(
            parser.NextInt(),
            JsonArrayEnumerationComplete);
    }
    {
        JsonParserArray parser = JsonParserArray::Create(Brn("[]"));
        TEST_THROWS(
            parser.NextString(),
            JsonArrayEnumerationComplete);
        TEST(parser.TryNextString(result) == false);
        TEST(result.Bytes() == 0);
    }
    {
        JsonParserArray parser = JsonParserArray::Create(Brn("[]"));
        TEST_THROWS(
            parser.NextStringEscaped(),
            JsonArrayEnumerationComplete);
        TEST(parser.TryNextStringEscaped(result) == false);
        TEST(result.Bytes() == 0);
    }
    {
        JsonParserArray parser = JsonParserArray::Create(Brn("[]"));
        TEST_THROWS(
            parser.NextArray(),
            JsonArrayEnumerationComplete);
        TEST(parser.TryNextArray(result) == false);
        TEST(result.Bytes() == 0);
    }
    {
        JsonParserArray parser = JsonParserArray::Create(Brn("[]"));
        TEST_THROWS(
            parser.NextObject(),
            JsonArrayEnumerationComplete);
        TEST(parser.TryNextObject(result) == false);
        TEST(result.Bytes() == 0);
    }
}

void SuiteParserJsonArray::TestArrayInObject()
{
    Brn json("{\"arr\":[-7,9]}");
    JsonParser parser;
    parser.Parse(json);
    Brn arr = parser.String("arr");
    JsonParserArray arrParser = JsonParserArray::Create(arr);
    TEST(arrParser.EntryType() == JsonParserArray::ValType::Int);
    TEST(arrParser.NextInt() == -7);
    TEST(arrParser.NextInt() == 9);
}

void SuiteParserJsonArray::TestNullObjectArray()
{
    JsonParserArray parser = JsonParserArray::Create(Brn("[{\"val\":0}, null]"));
    TEST(parser.NextObject() == Brn("{\"val\":0}"));
    TEST_THROWS(parser.NextBool(), JsonWrongType);
    TEST_THROWS(parser.NextInt(), JsonWrongType);
    TEST_THROWS(parser.NextString(), JsonWrongType);
    TEST_THROWS(parser.NextArray(), JsonWrongType);
    TEST(parser.NextNull() == Brn("null"));
    TEST(parser.EntryType() == JsonParserArray::ValType::End);

    JsonParserArray parser2 = JsonParserArray::Create(Brn("[ null, {\"val\":0}]"));
    TEST(parser2.NextNull() == Brn("null"));
    TEST_THROWS(parser2.NextBool(), JsonWrongType);
    TEST_THROWS(parser2.NextInt(), JsonWrongType);
    TEST_THROWS(parser2.NextString(), JsonWrongType);
    TEST_THROWS(parser2.NextArray(), JsonWrongType);
    TEST(parser2.NextObject() == Brn("{\"val\":0}"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::End);
}

void SuiteParserJsonArray::TestNullArrayArray()
{
    JsonParserArray parser = JsonParserArray::Create(Brn("[[1,2], null]"));
    TEST(parser.NextArray() == Brn("[1,2]"));
    TEST_THROWS(parser.NextBool(), JsonWrongType);
    TEST_THROWS(parser.NextInt(), JsonWrongType);
    TEST_THROWS(parser.NextString(), JsonWrongType);
    TEST_THROWS(parser.NextObject(), JsonWrongType);
    TEST(parser.NextNull() == Brn("null"));
    TEST(parser.EntryType() == JsonParserArray::ValType::End);

    JsonParserArray parser2 = JsonParserArray::Create(Brn("[null, [3,4,5]]"));
    TEST(parser2.NextNull() == Brn("null"));
    TEST_THROWS(parser2.NextBool(), JsonWrongType);
    TEST_THROWS(parser2.NextInt(), JsonWrongType);
    TEST_THROWS(parser2.NextString(), JsonWrongType);
    TEST_THROWS(parser2.NextObject(), JsonWrongType);
    TEST(parser2.NextArray() == Brn("[3,4,5]"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::End);
}

void SuiteParserJsonArray::TestMultiTypeArray()
{
    JsonParserArray parser = JsonParserArray::Create(Brn("[42, true,[1,2] ,null, \"foo\", {\"val\":0}]"));
    // Type() method is deprecated. Its value is set based on first array entry and does not change as array is parsed. For compatbility with existing clients, ensure that remains the case.
    TEST(parser.Type() == JsonParserArray::ValType::Int);
    TEST(parser.EntryType() == JsonParserArray::ValType::Int);
    TEST(parser.NextInt() == 42);
    TEST(parser.Type() == JsonParserArray::ValType::Int);
    TEST(parser.EntryType() == JsonParserArray::ValType::Bool);
    TEST(parser.NextBool());
    TEST(parser.Type() == JsonParserArray::ValType::Int);
    TEST(parser.EntryType() == JsonParserArray::ValType::Array);
    TEST(parser.NextArray() == Brn("[1,2]"));
    TEST(parser.Type() == JsonParserArray::ValType::Int);
    TEST(parser.EntryType() == JsonParserArray::ValType::NullEntry);
    TEST(parser.Next() == Brn("null"));
    TEST(parser.Type() == JsonParserArray::ValType::Int);
    TEST(parser.EntryType() == JsonParserArray::ValType::String);
    TEST(parser.NextString() == Brn("foo"));
    TEST(parser.Type() == JsonParserArray::ValType::Int);
    TEST(parser.EntryType() == JsonParserArray::ValType::Object);
    TEST(parser.NextObject() == Brn("{\"val\":0}"));
    TEST(parser.Type() == JsonParserArray::ValType::Int);
    TEST(parser.EntryType() == JsonParserArray::ValType::End);
}

void SuiteParserJsonArray::TestSubsetTypeArray()
{
    JsonParserArray parser = JsonParserArray::Create(Brn("[[1,2] ,null, \"foo\", {\"val\":0}]"));
    TEST(parser.EntryType() == JsonParserArray::ValType::Array);
    TEST(parser.Next() == Brn("[1,2]"));
    TEST(parser.Next() == Brn("null"));
    TEST(parser.Next() == Brn("foo"));
    TEST(parser.Next() == Brn("{\"val\":0}"));
    TEST(parser.EntryType() == JsonParserArray::ValType::End);
    TEST_THROWS(parser.Next(), JsonArrayEnumerationComplete);

    JsonParserArray parser2 = JsonParserArray::Create(Brn("[42, true, [1,2],null ,\"foo\", {\"val\":0}]"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::Int);
    TEST(parser2.Next() == Brn("42"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::Bool);
    TEST(parser2.Next() == Brn("true"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::Array);
    TEST(parser2.Next() == Brn("[1,2]"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::NullEntry);
    TEST(parser2.Next() == Brn("null"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::String);
    TEST(parser2.Next() == Brn("foo"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::Object);
    TEST(parser2.Next() == Brn("{\"val\":0}"));
    TEST(parser2.EntryType() == JsonParserArray::ValType::End);
    TEST_THROWS(parser.Next(), JsonArrayEnumerationComplete);
}

void SuiteParserJsonArray::TestCorruptArray()
{
    TEST_THROWS(JsonParserArray::Create(Brn("[abc]")), JsonCorrupt);
}

void SuiteParserJsonArray::TestArrayConclusion()
{
    JsonParserArray parser = JsonParserArray::Create(Brn("[1, 2]"));
    TEST(parser.NextInt() == 1);
    TEST(parser.NextInt() == 2);
    TEST(parser.EntryType() == JsonParserArray::ValType::End);
    TEST_THROWS(parser.Next(), JsonArrayEnumerationComplete);
    TEST_THROWS(parser.NextInt(), JsonArrayEnumerationComplete);
    TEST_THROWS(parser.NextBool(), JsonArrayEnumerationComplete);
    TEST_THROWS(parser.NextNull(), JsonArrayEnumerationComplete);
    TEST_THROWS(parser.NextString(), JsonArrayEnumerationComplete);
    TEST_THROWS(parser.NextStringEscaped(), JsonArrayEnumerationComplete);
    TEST_THROWS(parser.NextArray(), JsonArrayEnumerationComplete);
    TEST_THROWS(parser.NextObject(), JsonArrayEnumerationComplete);

    Brn result;
    TEST(parser.TryNext(result) == false);
    TEST(result.Bytes() == 0);

    TEST(parser.TryNextString(result) == false);
    TEST(result.Bytes() == 0);

    TEST(parser.TryNextStringEscaped(result) == false);
    TEST(result.Bytes() == 0);

    TEST(parser.TryNextArray(result) == false);
    TEST(result.Bytes() == 0);

    TEST(parser.TryNextObject(result) == false);
    TEST(result.Bytes() == 0);
}

void TestJson()
{
    Runner runner("JSON tests\n");
    runner.Add(new SuiteJsonEncode());
    runner.Add(new SuiteJsonDecode());
    runner.Add(new SuiteJsonParser());
    runner.Add(new SuiteWriterJson());
    runner.Add(new SuiteWriterJsonObject());
    runner.Add(new SuiteWriterJsonArray());
    runner.Add(new SuiteParserJsonArray());
    runner.Run();
}
