#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Stream.h>

#include <map>
#include <vector>

EXCEPTION(JsonInvalid);
EXCEPTION(JsonUnsupported);
EXCEPTION(JsonKeyNotFound);
EXCEPTION(JsonCorrupt);
EXCEPTION(JsonValueNull);
EXCEPTION(JsonArrayEnumerationComplete);
EXCEPTION(JsonWrongType);

namespace OpenHome {

class IWriter;

typedef enum {
    eJsonEncodingUtf8,
    eJsonEncodingUtf16
} EJsonEncoding;

typedef enum {
    eJsonValTypeUndefined,
    eJsonValTypeNull,
    eJsonValTypeNullEntry,
    eJsonValTypeInt,
    eJsonValTypeBool,
    eJsonValTypeString,
    eJsonValTypeObject,
    eJsonValTypeArray,
    eJsonValTypeEnd
} EJsonValType;

typedef enum {
    eJsonWriteOnEmptyNull,          // "null"
    eJsonWriteOnEmptyEmptyArray     // "[]"
} EJsonWriteOnEmpty;

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
    static void Unescape(Bwx& aValue, EJsonEncoding aEncoding = eJsonEncodingUtf8); // converts in place
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
private:
    typedef std::map<Brn, Brn, BufferCmp> PairMap;
public:
    JsonParser();
    void Parse(const Brx& aJson);
    void ParseAndUnescape(Bwx& aJson);
    void Reset();
    TBool HasKey(const TChar* aKey) const;
    TBool HasKey(const Brx& aKey) const;
    Brn String(const TChar* aKey) const;
    Brn String(const Brx& aKey) const;
    Brn StringOptional(const TChar* aKey) const; // returns empty buffer if aKey had null value or was missing
    Brn StringOptional(const Brx& aKey) const; // returns empty buffer if aKey had null value or was missing
    TInt Num(const TChar* aKey) const;
    TInt Num(const Brx& aKey) const;
    TBool Bool(const TChar* aKey) const;
    TBool Bool(const Brx& aKey) const;
    TBool IsNull(const TChar* aKey) const;
    TBool IsNull(const Brx& aKey) const;
    void GetKeys(std::vector<Brn>& aKeys) const;
private:
    void Parse(const Brx& aJson, TBool aUnescapeInPlace);
    inline void Add(const Brn& aKey, const TByte* aValStart, TUint aValBytes);
    Brn Value(const Brx& aKey) const;
private:
    PairMap iPairs;
};

class JsonParserArray
{
public:
    static JsonParserArray Create(const Brx& aArray);
    /*
     * Deprecated.
     *
     * Identfies type of array based on first entry. Not suitable for heterogeneous arrays. Use EntryType() to check type of each entry instead.
     */
    EJsonValType Type() const;
    EJsonValType EntryType() const;
    TInt NextInt();
    TBool NextBool();
    Brn NextNull();
    Brn NextString();
    Brn NextStringEscaped(EJsonEncoding aEncoding = eJsonEncodingUtf8); // array passed to Set must be writable in this case
    Brn NextArray();
    Brn NextObject();
    Brn Next();

    // These methods don't throw an exception when no value is present. Saves constructing a full exception when parsing content
    // NOTE: NextInt/NextBool/NextNull don't throw JsonArrayEnumerationComplete so don't have a TryXXX() overload
    TBool TryNextString(Brn& aResult);
    TBool TryNextStringEscaped(Brn& aResult, EJsonEncoding aEncoding = eJsonEncodingUtf8); // array passed to Set must be writable in this case
    TBool TryNextArray(Brn& aResult);
    TBool TryNextObject(Brn& aResult);
    TBool TryNext(Brn& aResult);
private:
    JsonParserArray(const Brx& aArray);
    void StartParse();
    void StartParseEntry();
    void ReturnType();
    Brn ValueToDelimiter();
    TBool NextCollection(TChar aStart, TChar aEnd, Brn& aResult);
    TBool TryEndEnumerationIfNull();
private:
    Brn iBuf;
    EJsonValType iType;
    const TByte* iPtr;
    const TByte* iEnd;
    EJsonValType iEntryType;
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
    static void WriteValueUint(IWriter& aWriter, TUint aValue);
    static void WriteValueString(IWriter& aWriter, const Brx& aValue);
    static void WriteValueBinary(IWriter& aWriter, const Brx& aValue);
    static void WriteValueBool(IWriter& aWriter, TBool aValue);
};

class IWriterJson
{
public:
    virtual void WriteEnd() = 0;
    virtual ~IWriterJson() {}
};

class WriterJsonObject;
class WriterJsonValueString;

class WriterJsonArray : public IWriterJson
{
public:
    WriterJsonArray();
    WriterJsonArray(IWriter& aWriter, EJsonWriteOnEmpty aWriteOnEmpty = eJsonWriteOnEmptyNull);
    WriterJsonArray(const WriterJsonArray& aWriter);
    void WriteInt(TInt aValue);
    void WriteUint(TUint aValue);
    void WriteString(const TChar* aValue);
    void WriteString(const Brx& aValue);
    void WriteBool(TBool aValue);
    WriterJsonArray CreateArray(EJsonWriteOnEmpty aWriteOnEmpty = eJsonWriteOnEmptyNull);
    WriterJsonObject CreateObject();
public: // from IWriterJson
    void WriteEnd();
private:
    void WriteStartOrSeparator();
private:
    static const Brn kArrayStart;
    static const Brn kArrayEnd;
    IWriter* iWriter;
    EJsonWriteOnEmpty iWriteOnEmpty;
    TBool iStarted;
    TBool iEnded;
};

class WriterJsonObject : public IWriterJson
{
    friend class WriterJsonArray;
public:
    WriterJsonObject();
    WriterJsonObject(IWriter& aWriter);
    void Set(IWriter& aWriter);
    void WriteKey(const TChar* aKey);
    void WriteKey(const Brx& aKey);
    void WriteInt(const TChar* aKey, TInt aValue);
    void WriteInt(const Brx& aKey, TInt aValue);
    void WriteUint(const TChar* aKey, TUint aValue);
    void WriteUint(const Brx& aKey, TUint aValue);
    void WriteString(const TChar* aKey, const TChar* aValue);
    void WriteString(const TChar* aKey, const Brx& aValue);
    void WriteString(const Brx& aKey, const TChar* aValue);
    void WriteString(const Brx& aKey, const Brx& aValue);
    void WriteBool(const TChar* aKey, TBool aValue);
    void WriteBool(const Brx& aKey, TBool aValue);
    void WriteBinary(const TChar* aKey, const Brx& aValue);
    void WriteBinary(const Brx& aKey, const Brx& aValue);
    void WriteRaw(const TChar* aKey, const Brx& aValue);
    void WriteRaw(const Brx& aKey, const Brx& aValue);
    WriterJsonArray CreateArray(const TChar* aKey, EJsonWriteOnEmpty aWriteOnEmpty = eJsonWriteOnEmptyNull);
    WriterJsonArray CreateArray(const Brx& aKey, EJsonWriteOnEmpty aWriteOnEmpty = eJsonWriteOnEmptyNull);
    WriterJsonObject CreateObject(const TChar* aKey);
    WriterJsonObject CreateObject(const Brx& aKey);
    WriterJsonValueString CreateStringStreamed(const TChar* aKey);
    WriterJsonValueString CreateStringStreamed(const Brx& aKey);
public: // from IWriterJson
    void WriteEnd();
private:
    void Set(IWriter* aWriter);
    void CheckStarted();
private:
    static const Brn kObjectStart;
    static const Brn kObjectEnd;
    IWriter* iWriter;
    TBool iStarted;
    TBool iEnded;
    TBool iWrittenFirstKey;
};

class WriterJsonValueString : public IWriter, public IWriterJson
{
public:
    WriterJsonValueString();
    WriterJsonValueString(IWriter& aWriter);
    void WriteEscaped(const Brx& aFragment);
public: // from IWriterJson
    void WriteEnd();
public: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
private:
    void CheckStarted();
private:
    IWriter* iWriter;
    TBool iStarted;
    TBool iEnded;
};

class AutoWriterJson : private INonCopyable
{
public:
    AutoWriterJson(IWriterJson& aWriterJson);
    ~AutoWriterJson();
private:
    IWriterJson& iWriterJson;
};

} // namespace OpenHome
