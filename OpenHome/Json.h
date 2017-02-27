#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Stream.h>

#include <map>

EXCEPTION(JsonInvalid);
EXCEPTION(JsonUnsupported);
EXCEPTION(JsonKeyNotFound);
EXCEPTION(JsonCorrupt);
EXCEPTION(JsonValueNull);

namespace OpenHome {

class IWriter;

class Json
{
    static const Brn kEscapedDoubleQuote;
    static const Brn kEscapedBackslash;
    static const Brn kEscapedForwardSlash;
    static const Brn kEscapedBackspace;
    static const Brn kEscapedFormfeed;
    static const Brn kEscapedNewline;
    static const Brn kEscapedLinefeed;
    static const Brn kEscapedTab;
public:
    static void Escape(IWriter& aWriter, const Brx& aValue);
    static void Unescape(Bwx& aValue); // converts in place
};

/*
    FIXME - limited support for objects
            limited support for arrays
*/

// FIXME - assumes all JSON must be contained within an object.
class JsonParser
{
    static const Brn kBoolValTrue;
    static const Brn kBoolValFalse;
public:
    JsonParser();
    void Parse(const Brx& aJson);
    void ParseAndUnescape(Bwx& aJson);
    TBool HasKey(const TChar* aKey) const;
    TBool HasKey(const Brx& aKey) const;
    Brn String(const TChar* aKey) const;
    Brn String(const Brx& aKey) const;
    TInt Num(const TChar* aKey) const;
    TInt Num(const Brx& aKey) const;
    TBool Bool(const TChar* aKey) const;
    TBool Bool(const Brx& aKey) const;
    TBool IsNull(const TChar* aKey) const;
    TBool IsNull(const Brx& aKey) const;
private:
    void Reset();
    void Parse(const Brx& aJson, TBool aUnescapeInPlace);
    inline void Add(const Brn& aKey, const TByte* aValStart, TUint aValBytes);
    Brn Value(const Brx& aKey) const;
private:
    std::map<Brn, Brn, BufferCmp> iPairs;
};

class WriterJson
{
public:
    static const Brn kQuote;
    static const Brn kSeparator;
    static const Brn kBoolTrue;
    static const Brn kBoolFalse;
    static const Brn kNull;
public:
    static void WriteValueInt(IWriter& aWriter, TInt aValue);
    static void WriteValueString(IWriter& aWriter, const Brx& aValue);
    static void WriteValueBinary(IWriter& aWriter, const Brx& aValue);
    static void WriteValueBool(IWriter& aWriter, TBool aValue);
};

class WriterJsonObject;
class WriterJsonValueString;

class WriterJsonArray : private INonCopyable
{
public:
    enum class WriteOnEmpty
    {
        eNull,          // "null"
        eEmptyArray     // "[]"
    };
public:
    WriterJsonArray(IWriter& aWriter, WriteOnEmpty aWriteOnEmpty = WriteOnEmpty::eNull);
    WriterJsonArray(const WriterJsonArray& aWriter);
    void WriteInt(TInt aValue);
    void WriteString(const Brx& aValue);
    void WriteBool(TBool aValue);
    WriterJsonArray CreateArray(WriterJsonArray::WriteOnEmpty aWriteOnEmpty = WriterJsonArray::WriteOnEmpty::eNull);
    WriterJsonObject CreateObject();
    void WriteEnd();
private:
    void WriteStartOrSeparator();
private:
    static const Brn kArrayStart;
    static const Brn kArrayEnd;
    IWriter* iWriter;
    const WriteOnEmpty iWriteOnEmpty;
    TBool iStarted;
    TBool iEnded;
};

class WriterJsonObject
{
    friend class WriterJsonArray;
public:
    WriterJsonObject();
    WriterJsonObject(IWriter& aWriter);
    void Set(IWriter& aWriter);
    void WriteInt(const TChar* aKey, TInt aValue);
    void WriteInt(const Brx& aKey, TInt aValue);
    void WriteString(const TChar* aKey, const TChar* aValue);
    void WriteString(const TChar* aKey, const Brx& aValue);
    void WriteString(const Brx& aKey, const Brx& aValue);
    void WriteBool(const TChar* aKey, TBool aValue);
    void WriteBool(const Brx& aKey, TBool aValue);
    void WriteBinary(const TChar* aKey, const Brx& aValue);
    void WriteBinary(const Brx& aKey, const Brx& aValue);
    WriterJsonArray CreateArray(const TChar* aKey, WriterJsonArray::WriteOnEmpty aWriteOnEmpty = WriterJsonArray::WriteOnEmpty::eNull);
    WriterJsonArray CreateArray(const Brx& aKey, WriterJsonArray::WriteOnEmpty aWriteOnEmpty = WriterJsonArray::WriteOnEmpty::eNull);
    WriterJsonObject CreateObject(const TChar* aKey);
    WriterJsonObject CreateObject(const Brx& aKey);
    WriterJsonValueString CreateStringStreamed(const TChar* aKey);
    WriterJsonValueString CreateStringStreamed(const Brx& aKey);
    void WriteEnd();
private:
    void Set(IWriter* aWriter);
    void WriteKey(const TChar* aKey);
    void WriteKey(const Brx& aKey);
    void CheckStarted();
private:
    static const Brn kObjectStart;
    static const Brn kObjectEnd;
    IWriter* iWriter;
    TBool iStarted;
    TBool iEnded;
    TBool iWrittenFirstKey;
};

class WriterJsonValueString : public OpenHome::IWriter
{
public:
    WriterJsonValueString();
    WriterJsonValueString(IWriter& aWriter);
    void WriteEscaped(const Brx& aFragment);
    void WriteEnd();
public: // from OpenHome::IWriter
    void Write(TByte aValue) override;
    void Write(const Brx& aBuffer) override;
    void WriteFlush() override;
private:
    void CheckStarted();
private:
    IWriter* iWriter;
    TBool iStarted;
    TBool iEnded;
};

} // namespace OpenHome
