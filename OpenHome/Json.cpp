#include <OpenHome/Json.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Stream.h>

#include <map>
#include <vector>

using namespace OpenHome;

// Json

// see RFC4627 - http://www.ietf.org/rfc/rfc4627.txt

const Brn Json::kEscapedDoubleQuote("\\\"");
const Brn Json::kEscapedBackslash("\\\\");
const Brn Json::kEscapedForwardSlash("\\/");
const Brn Json::kEscapedBackspace("\\b");
const Brn Json::kEscapedFormfeed("\\f");
const Brn Json::kEscapedNewline("\\n");
const Brn Json::kEscapedLinefeed("\\r");
const Brn Json::kEscapedTab("\\t");

void Json::Escape(IWriter& aWriter, const Brx& aValue)
{
    // FIXME - no support for multi-byte chars
    const TUint bytes = aValue.Bytes();
    for (TUint i=0; i<bytes; i++) {
        TByte ch = aValue[i];
        switch (ch)
        {
        case '\"':
            aWriter.Write(kEscapedDoubleQuote);
            break;
        case '\\':
            aWriter.Write(kEscapedBackslash);
            break;
        case '/':
            aWriter.Write(kEscapedForwardSlash);
            break;
        case '\b':
            aWriter.Write(kEscapedBackspace);
            break;
        case '\f':
            aWriter.Write(kEscapedFormfeed);
            break;
        case '\n':
            aWriter.Write(kEscapedNewline);
            break;
        case '\r':
            aWriter.Write(kEscapedLinefeed);
            break;
        case '\t':
            aWriter.Write(kEscapedTab);
            break;
        default:
            if (ch > 0x1F) {
                aWriter.Write(ch);
            }
            else {
                Bws<6> hexBuf("\\u00");
                Ascii::AppendHex(hexBuf, ch);
                aWriter.Write(hexBuf);
            }
            break;
        }
    }
}

void Json::Unescape(Bwx& aValue)
{
    TUint j = 0;
    const TUint bytes = aValue.Bytes();
    for (TUint i=0; i<bytes; i++) {
        TByte ch = aValue[i];
        if (ch != '\\') {
            aValue[j++] = ch;
        }
        else {
            if (++i == bytes) {
                THROW(JsonInvalid);
            }
            switch (aValue[i])
            {
            case '\"':
                aValue[j++] = '\"';
                break;
            case '\\':
                aValue[j++] = '\\';
                break;
            case '/':
                aValue[j++] = '/';
                break;
            case 'b':
                aValue[j++] = '\b';
                break;
            case 'f':
                aValue[j++] = '\f';
                break;
            case 'n':
                aValue[j++] = '\n';
                break;
            case 'r':
                aValue[j++] = '\r';
                break;
            case 't':
                aValue[j++] = '\t';
                break;
            case 'u':
            {
                if (i+4 >= bytes) {
                    THROW(JsonInvalid);
                }
                Brn hexBuf = aValue.Split(i+1, 4);
                i += 4;
                const TUint hex = Ascii::UintHex(hexBuf);
                if (hex > 0xFF) {
                    THROW(JsonUnsupported);
                }
                aValue[j++] = (TByte)hex;
            }
                break;
            default:
                THROW(JsonInvalid);
            }
        }
    }
    aValue.SetBytes(j);
}


// JsonParser

const Brn JsonParser::kBoolValTrue("true");
const Brn JsonParser::kBoolValFalse("false");

JsonParser::JsonParser()
{
}

void JsonParser::Reset()
{
    iPairs.clear();
}

inline void JsonParser::Add(const Brn& aKey, const TByte* aValStart, TUint aValBytes)
{
    Brn val(aValStart, aValBytes);
//    Log::Print("Add %.*s, %.*s\n", PBUF(aKey), PBUF(val));
    iPairs.insert(std::pair<Brn, Brn>(aKey, val));
}

void JsonParser::Parse(const Brx& aJson)
{
    Parse(aJson, false);
}

void JsonParser::ParseAndUnescape(Bwx& aJson)
{
    Parse(aJson, true);
}

void JsonParser::Parse(const Brx& aJson, TBool aUnescapeInPlace)
{
    Reset();

    const TByte* ptr = aJson.Ptr();
    const TByte* end = ptr + aJson.Bytes();

    enum ParseState {
        DocStart,
        KeyStart,
        KeyEnd,
        ValueStart,
        NumEnd,
        StringEnd,
        ArrayEnd,
        ObjectEnd,
        MiscEnd,
        Complete
    } state;
    state = DocStart;
    const TByte* keyStart = nullptr;
    const TByte* valStart = nullptr;
    Brn key;
    TUint nestCount = 0;
    TBool escapeChar = false;

    while (state != Complete && ptr < end) {
        TChar ch = (TChar)*ptr++;
        if (Ascii::IsWhitespace(ch)) {
            continue;
        }
        switch (state)
        {
        case DocStart:
            if (ch == '{') {
                state = KeyStart;
            }
            break;
        case KeyStart:
            switch (ch)
            {
            case '\"':
                keyStart = ptr;
                state = KeyEnd;
                break;
            case '}':
                state = Complete;
                break;
            default:
                if (ch != ',') {
                    THROW(JsonCorrupt);
                }
                break;
            }
            break;
        case KeyEnd:
            if (ch == '\"') {
                key.Set(keyStart, ptr - keyStart - 1);
                state = ValueStart;
            }
            break;
        case ValueStart:
            if (ch != ':') {
                if (ch == '\"') {
                    valStart = ptr;
                    state = StringEnd;
                }
                else {
                    valStart = ptr - 1;
                    if (ch == '[') {
                        state = ArrayEnd;
                        nestCount = 1;
                    }
                    else if (ch == '{') {
                        state = ObjectEnd;
                        nestCount = 1;
                    }
                    else if (ch == '-' || Ascii::IsDigit(ch)) {
                        // FIXME - no support for frac or exp
                        state = NumEnd;
                    }
                    else {
                        state = MiscEnd;
                    }
                }
            }
            break;
        case NumEnd:
        case MiscEnd:
            if (ch == ',') {
                Add(key, valStart, ptr - valStart - 1);
                state = KeyStart;
            }
            else if (ch == '}') {
                if (nestCount != 0) {
                    THROW(JsonUnsupported);
                }
                Add(key, valStart, ptr - valStart - 1);
                state = Complete;
            }
            break;
        case StringEnd:
            if (ch == '\\') {
                escapeChar = !escapeChar;
            }
            else if (ch == '\"') {
                if (!escapeChar) {
                    const TUint bytes = ptr - valStart - 1;
                    if (!aUnescapeInPlace) {
                        Add(key, valStart, bytes);
                    }
                    else {
                        Bwn buf(valStart, bytes, bytes);
                        Json::Unescape(buf);
                        Add(key, buf.Ptr(), buf.Bytes());
                    }
                    state = KeyStart;
                }
                escapeChar = false;
            }
            break;
        case ArrayEnd:
            if (ch == '[') {
                nestCount++;
            }
            else if (ch == ']') {
                nestCount--;
                if (nestCount == 0) {
                    Add(key, valStart, ptr - valStart);
                    state = KeyStart;
                }
            }
            break;
        case ObjectEnd:
            if (ch == '{') {
                nestCount++;
            }
            else if (ch == '}') {
                nestCount--;
                if (nestCount == 0) {
                    Add(key, valStart, ptr - valStart);
                    state = KeyStart;
                }
            }
            break;
        default:
            ASSERTS();
        }

    }

    if (state != Complete) {
        THROW(JsonCorrupt);
    }
}

TBool JsonParser::HasKey(const TChar* aKey) const
{
    Brn key(aKey);
    return HasKey(key);
}

TBool JsonParser::HasKey(const Brx& aKey) const
{
    Brn key(aKey);
    const auto it = iPairs.find(key);
    return it != iPairs.end();
}

Brn JsonParser::String(const TChar* aKey) const
{
    Brn key(aKey);
    return String(key);
}

Brn JsonParser::String(const Brx& aKey) const
{
    return Value(aKey);
}

TInt JsonParser::Num(const TChar* aKey) const
{
    Brn key(aKey);
    return Num(key);
}

TInt JsonParser::Num(const Brx& aKey) const
{
    try {
        Brn numBuf = Value(aKey);
        return Ascii::Int(numBuf);
    }
    catch (AsciiError&) {
        THROW(JsonCorrupt);
    }
}

TBool JsonParser::Bool(const TChar* aKey) const
{
    Brn key(aKey);
    return Bool(key);
}

TBool JsonParser::Bool(const Brx& aKey) const
{
    Brn buf = Value(aKey);
    if (buf == kBoolValTrue) {
        return true;
    }
    else if (buf == kBoolValFalse) {
        return false;
    }
    THROW(JsonCorrupt);
}

TBool JsonParser::IsNull(const TChar* aKey) const
{
    return IsNull(Brn(aKey));
}

TBool JsonParser::IsNull(const Brx& aKey) const
{
    try {
        (void)Value(aKey);
        return false;
    }
    catch (JsonValueNull&) {
        return true;
    }
}

void JsonParser::GetKeys(std::vector<Brn>& aKeys) const
{
    aKeys.reserve(iPairs.size());
    for (auto it=iPairs.begin(); it!=iPairs.end(); ++it) {
        aKeys.push_back(it->first);
    }
}

Brn JsonParser::Value(const Brx& aKey) const
{
    Brn key(aKey);
    const auto it = iPairs.find(key);
    if (it == iPairs.end()) {
        THROW(JsonKeyNotFound);
    }
    if (it->second == WriterJson::kNull) {
        THROW(JsonValueNull);
    }
    return it->second;
}


// JsonParserArray
enum class Type
{
    Undefined,
    NumBool,
    String,
    Object,
    Array
};
JsonParserArray JsonParserArray::Create(const Brx& aArray)
{
    JsonParserArray self(aArray);
    self.StartParse();
    return self;
}

JsonParserArray::ValType JsonParserArray::Type() const
{
    ASSERT(iType != ValType::Undefined);
    return iType;
}

TInt JsonParserArray::NextInt()
{
    if (iType != ValType::Int) {
        THROW(JsonWrongType);
    }
    Brn val = NextNumOrBool();
    try {
        return Ascii::Int(val);
    }
    catch (AsciiError&) {
        THROW(JsonCorrupt);
    }
}

TBool JsonParserArray::NextBool()
{
    if (iType != ValType::Bool) {
        THROW(JsonWrongType);
    }
    Brn val = NextNumOrBool();
    if (val == WriterJson::kBoolTrue) {
        return true;
    }
    else if (val == WriterJson::kBoolFalse) {
        return false;
    }
    THROW(JsonCorrupt);
}

Brn JsonParserArray::NextString()
{
    if (iType != ValType::String) {
        THROW(JsonWrongType);
    }

    while (iPtr < iEnd) {
        if (*iPtr++ == '\"') {
            break;
        }
    }
    const TByte* valStart = iPtr;
    Brn val;
    if (iPtr == iEnd) {
        THROW(JsonArrayEnumerationComplete);
    }
    if (*(valStart-1) != '\"') {
        THROW(JsonCorrupt);
    }

    TBool escapeChar = false;
    TBool complete = false;
    while (iPtr < iEnd) {
        TChar ch = (TChar)*iPtr++;
        if (ch == '\\') {
            escapeChar = !escapeChar;
        }
        else if (ch == '\"' || ch == ']') {
            complete = (ch == ']');
            if (!escapeChar) {
                val.Set(valStart, iPtr - valStart - 1);
                break;
            }
            escapeChar = false;
        }
    }
    if (val.Bytes() == 0 && complete) {
        THROW(JsonArrayEnumerationComplete);
    }

    return val;
}

Brn JsonParserArray::NextStringEscaped()
{
    Brn val = NextString();
    Bwn buf(val.Ptr(), val.Bytes(), val.Bytes());
    Json::Unescape(buf);
    val.Set(buf.Ptr(), buf.Bytes());
    return val;
}

Brn JsonParserArray::NextArray()
{
    if (iType != ValType::Array) {
        THROW(JsonWrongType);
    }

    return NextCollection('[', ']');
}

Brn JsonParserArray::NextObject()
{
    if (iType != ValType::Object) {
        THROW(JsonWrongType);
    }

    return NextCollection('{', '}');
}

JsonParserArray::JsonParserArray(const Brx& aArray)
    : iBuf(Ascii::Trim(aArray))
    , iType(ValType::Undefined)
    , iPtr(iBuf.Ptr())
    , iEnd(iPtr + iBuf.Bytes())
{
}

void JsonParserArray::StartParse()
{
    if (iBuf == WriterJson::kNull) {
        iType = ValType::Null;
        return;
    }

    if (*iPtr++ != '[') {
        THROW(JsonCorrupt);
    }
    while (iType == ValType::Undefined && iPtr < iEnd) {
        const TChar ch = (TChar)*iPtr;
        if (Ascii::IsWhitespace(ch)) {
            iPtr++;
            continue;
        }
        if (ch == '{') {
            iType = ValType::Object;
        }
        else if (ch == '[') {
            iType = ValType::Array;
        }
        else if (ch == '\"') {
            iType = ValType::String;
        }
        else if (ch == '-' || Ascii::IsDigit(ch)) {
            iType = ValType::Int;
        }
        else if (iBuf == WriterJson::kNull) {
            iType = ValType::Null;
        }
        else if (ch == 't' || ch == 'f') {
            iType = ValType::Bool;
        }
        else {
            THROW(JsonCorrupt);
        }
    }
    if (iType == ValType::Undefined) {
        THROW(JsonCorrupt);
    }
}

Brn JsonParserArray::NextNumOrBool()
{
    while (iPtr < iEnd) {
        TChar ch = (TChar)*iPtr;
        if (!Ascii::IsWhitespace(ch)) {
            break;
        }
        iPtr++;
    }
    const TByte* valStart = iPtr;
    Brn val;

    while (iPtr < iEnd) {
        TChar ch = (TChar)*iPtr++;
        if (ch == ',' || ch == ']' || ch == ' ') {
            val.Set(valStart, iPtr - valStart - 1);
            break;
        }
    }
    if (val.Bytes() == 0) {
        THROW(JsonArrayEnumerationComplete);
    }

    return val;
}

Brn JsonParserArray::NextCollection(TChar aStart, TChar aEnd)
{
    while (iPtr < iEnd) {
        if (*iPtr == aStart) {
            break;
        }
        iPtr++;
    }
    if (iPtr == iEnd) {
        THROW(JsonArrayEnumerationComplete);
    }
    const TByte* valStart = iPtr;
    Brn val;


    TBool escapeChar = false;
    TBool inString = false;
    TUint nestCount = 0;
    while (iPtr < iEnd) {
        TChar ch = (TChar)*iPtr++;
        if (ch == '\\') {
            escapeChar = !escapeChar;
        }
        else if (ch == '\"') {
            if (!escapeChar) {
                inString = !inString;
            }
            escapeChar = false;
        }
        else if (ch == aStart) {
            nestCount++;
        }
        else if (ch == aEnd) {
            if (--nestCount == 0) {
                val.Set(valStart, iPtr - valStart);
                break;
            }
        }
    }
    if (val.Bytes() == 0) {
        THROW(JsonArrayEnumerationComplete);
    }

    return val;
}


// class WriterJson

const Brn WriterJson::kQuote("\"");
const Brn WriterJson::kSeparator(",");
const Brn WriterJson::kBoolTrue("true");
const Brn WriterJson::kBoolFalse("false");
const Brn WriterJson::kNull("null");

void WriterJson::WriteValueInt(IWriter& aWriter, TInt aValue)
{ // static
    Bws<Ascii::kMaxIntStringBytes> valBuf;
    (void)Ascii::AppendDec(valBuf, aValue);
    aWriter.Write(valBuf);
}

void WriterJson::WriteValueString(IWriter& aWriter, const Brx& aValue)
{ // static
    aWriter.Write(kQuote);
    Json::Escape(aWriter, aValue);
    aWriter.Write(kQuote);
}

void WriterJson::WriteValueBinary(IWriter& aWriter, const Brx& aValue)
{ // static
    aWriter.Write(kQuote);
    Converter::ToBase64(aWriter, aValue);
    aWriter.Write(kQuote);
}

void WriterJson::WriteValueBool(IWriter& aWriter, TBool aValue)
{ // static
    aWriter.Write(aValue? kBoolTrue : kBoolFalse);
}


// WriterJsonArray

const Brn WriterJsonArray::kArrayStart("[");
const Brn WriterJsonArray::kArrayEnd("]");

WriterJsonArray::WriterJsonArray(IWriter& aWriter, WriteOnEmpty aWriteOnEmpty)
    : iWriter(&aWriter)
    , iWriteOnEmpty(aWriteOnEmpty)
    , iStarted(false)
    , iEnded(false)
{
}

WriterJsonArray::WriterJsonArray(const WriterJsonArray& aWriter)
    : iWriter(aWriter.iWriter)
    , iWriteOnEmpty(aWriter.iWriteOnEmpty)
    , iStarted(aWriter.iStarted)
    , iEnded(aWriter.iEnded)
{
}

void WriterJsonArray::WriteInt(TInt aValue)
{
    WriteStartOrSeparator();
    WriterJson::WriteValueInt(*iWriter, aValue);
}

void WriterJsonArray::WriteString(const Brx& aValue)
{
    WriteStartOrSeparator();
    WriterJson::WriteValueString(*iWriter, aValue);
}

void WriterJsonArray::WriteBool(TBool aValue)
{
    WriteStartOrSeparator();
    WriterJson::WriteValueBool(*iWriter, aValue);
}

WriterJsonArray WriterJsonArray::CreateArray(WriterJsonArray::WriteOnEmpty aWriteOnEmpty)
{
    WriteStartOrSeparator();
    WriterJsonArray writer(*iWriter, aWriteOnEmpty);
    return writer;
}

WriterJsonObject WriterJsonArray::CreateObject()
{
    WriteStartOrSeparator();
    WriterJsonObject writer(*iWriter);
    return writer;
}

void WriterJsonArray::WriteEnd()
{
    if (iStarted) {
        iWriter->Write(kArrayEnd);
    }
    else {
        if (iWriteOnEmpty == WriteOnEmpty::eNull) {
            iWriter->Write(WriterJson::kNull);
        }
        else if (iWriteOnEmpty == WriteOnEmpty::eEmptyArray) {
            iWriter->Write(kArrayStart);
            iWriter->Write(kArrayEnd);
        }
        else {
            // Unhandled WriteOnEmpty value.
            ASSERTS();
        }
    }
    iEnded = true;
}

void WriterJsonArray::WriteStartOrSeparator()
{
    ASSERT(!iEnded);
    if (iStarted) {
        iWriter->Write(WriterJson::kSeparator);
    }
    else {
        iWriter->Write(kArrayStart);
        iStarted = true;
    }
}


// WriterJsonObject

const Brn WriterJsonObject::kObjectStart("{");
const Brn WriterJsonObject::kObjectEnd("}");

WriterJsonObject::WriterJsonObject()
{
    Set(nullptr);
}

WriterJsonObject::WriterJsonObject(IWriter& aWriter)
{
    Set(aWriter);
}

void WriterJsonObject::Set(IWriter& aWriter)
{
    Set(&aWriter);
}

void WriterJsonObject::Set(IWriter* aWriter)
{
    iWriter = aWriter;
    iStarted = iEnded = iWrittenFirstKey = false;
}

void WriterJsonObject::WriteKey(const TChar* aKey)
{
    WriteKey(Brn(aKey));
}

void WriterJsonObject::WriteKey(const Brx& aKey)
{
    if (iWrittenFirstKey) {
        iWriter->Write(WriterJson::kSeparator);
    }
    iWriter->Write(WriterJson::kQuote);
    Brn key(aKey);
    iWriter->Write(key);
    iWriter->Write(WriterJson::kQuote);
    iWriter->Write(Brn(":"));
    iWrittenFirstKey = true;
}

void WriterJsonObject::WriteInt(const TChar* aKey, TInt aValue)
{
    WriteInt(Brn(aKey), aValue);
}

void WriterJsonObject::WriteInt(const Brx& aKey, TInt aValue)
{
    CheckStarted();
    WriteKey(aKey);
    WriterJson::WriteValueInt(*iWriter, aValue);
}

void WriterJsonObject::WriteString(const TChar* aKey, const TChar* aValue)
{
    WriteString(Brn(aKey), Brn(aValue));
}

void WriterJsonObject::WriteString(const TChar* aKey, const Brx& aValue)
{
    WriteString(Brn(aKey), aValue);
}

void WriterJsonObject::WriteString(const Brx& aKey, const Brx& aValue)
{
    CheckStarted();
    WriteKey(aKey);
    WriterJson::WriteValueString(*iWriter, aValue);
}

void WriterJsonObject::WriteBinary(const TChar* aKey, const Brx& aValue)
{
    WriteBinary(Brn(aKey), aValue);
}

void WriterJsonObject::WriteBinary(const Brx& aKey, const Brx& aValue)
{
    CheckStarted();
    WriteKey(aKey);
    WriterJson::WriteValueBinary(*iWriter, aValue);
}

void WriterJsonObject::WriteBool(const TChar* aKey, TBool aValue)
{
    WriteBool(Brn(aKey), aValue);
}

void WriterJsonObject::WriteBool(const Brx& aKey, TBool aValue)
{
    CheckStarted();
    WriteKey(aKey);
    WriterJson::WriteValueBool(*iWriter, aValue);
}

WriterJsonArray WriterJsonObject::CreateArray(const TChar* aKey, WriterJsonArray::WriteOnEmpty aWriteOnEmpty)
{
    return CreateArray(Brn(aKey), aWriteOnEmpty);
}

WriterJsonArray WriterJsonObject::CreateArray(const Brx& aKey, WriterJsonArray::WriteOnEmpty aWriteOnEmpty)
{
    CheckStarted();
    WriteKey(aKey);
    WriterJsonArray writer(*iWriter, aWriteOnEmpty);
    return writer;
}

WriterJsonObject WriterJsonObject::CreateObject(const TChar* aKey)
{
    return CreateObject(Brn(aKey));
}

WriterJsonObject WriterJsonObject::CreateObject(const Brx& aKey)
{
    CheckStarted();
    WriteKey(aKey);
    WriterJsonObject writer(*iWriter);
    return writer;
}

WriterJsonValueString WriterJsonObject::CreateStringStreamed(const TChar* aKey)
{
    Brn key(aKey);
    return CreateStringStreamed(key);
}

WriterJsonValueString WriterJsonObject::CreateStringStreamed(const Brx& aKey)
{
    CheckStarted();
    WriteKey(aKey);
    WriterJsonValueString writer(*iWriter);
    return writer;
}

void WriterJsonObject::WriteEnd()
{
    if (iStarted) {
        iWriter->Write(kObjectEnd);
    }
    else {
        iWriter->Write(WriterJson::kNull);
    }
    iEnded = true;
}

void WriterJsonObject::CheckStarted()
{
    ASSERT(!iEnded);
    if (!iStarted) {
        iWriter->Write(kObjectStart);
        iStarted = true;
    }
}


// WriterJsonValueString

WriterJsonValueString::WriterJsonValueString()
    : iWriter(nullptr)
    , iStarted(false)
    , iEnded(false)
{
}

WriterJsonValueString::WriterJsonValueString(IWriter& aWriter)
    : iWriter(&aWriter)
    , iStarted(false)
    , iEnded(false)
{
}

void WriterJsonValueString::WriteEscaped(const Brx& aFragment)
{
    CheckStarted();
    Json::Escape(*this, aFragment);
}

void WriterJsonValueString::WriteEnd()
{
    if (iStarted) {
        iWriter->Write(WriterJson::kQuote);
    }
    else {
        iWriter->Write(WriterJson::kNull);
    }
    iEnded = true;
}

void WriterJsonValueString::Write(TByte aValue)
{
    iWriter->Write(aValue);
}

void WriterJsonValueString::Write(const Brx& aBuffer)
{
    CheckStarted();
    iWriter->Write(aBuffer);
}

void WriterJsonValueString::WriteFlush()
{
    iWriter->WriteFlush();
}

void WriterJsonValueString::CheckStarted()
{
    ASSERT(!iEnded);
    ASSERT(iWriter != nullptr);
    if (!iStarted) {
        iStarted = true;
        iWriter->Write(WriterJson::kQuote);
    }
}
