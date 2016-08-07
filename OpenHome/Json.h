#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>

#include <map>

EXCEPTION(JsonInvalid);
EXCEPTION(JsonUnsupported);
EXCEPTION(JsonKeyNotFound);
EXCEPTION(JsonCorrupt);

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
            no unit tests
*/

class JsonParser
{
public:
    JsonParser();
    void Reset();
    void Parse(const Brx& aJson, TBool aUnescapeInPlace);
    TBool HasKey(const TChar* aKey) const;
    TBool HasKey(const Brx& aKey) const;
    Brn String(const TChar* aKey) const;
    Brn String(const Brx& aKey) const;
    TInt Num(const TChar* aKey) const;
    TInt Num(const Brx& aKey) const;
private:
    inline void Add(const Brn& aKey, const TByte* aValStart, TUint aValBytes);
    Brn Value(const Brx& aKey) const;
private:
    std::map<Brn, Brn, BufferCmp> iPairs;
};

class JsonWriter : private INonCopyable
{
    static const Brn kQuote;
public:
    JsonWriter(IWriter& aWriter);
    void WriteKey(const TChar* aKey);
    void WriteString(const TChar* aKey, const TChar* aValue);
    void WriteString(const TChar* aKey, const Brx& aValue);
    void WriteInt(const TChar* aKey, TInt aValue);
    void WriteEnd();
private:
    void CheckStarted();
private:
    IWriter& iWriter;
    TBool iStarted;
    TBool iEnded;
    TBool iWrittenFirstKey;
};

} // namespace OpenHome
