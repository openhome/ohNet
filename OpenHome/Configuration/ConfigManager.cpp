#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Stream.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Configuration;


// ConfigNum

ConfigNum::ConfigNum(IConfigInitialiser& aManager, const Brx& aKey, TInt aMin, TInt aMax, TInt aDefault)
    : ConfigVal(aManager, aKey)
    , iMin(aMin)
    , iMax(aMax)
    , iMutex("CVNM")
{
    ASSERT(iMax >= iMin);

    Bws<sizeof(TInt)> initialBuf;
    Bws<sizeof(TInt)> defaultBuf;
    WriterBuffer writerBuf(defaultBuf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(aDefault);
    iConfigManager.FromStore(iKey, initialBuf, defaultBuf);
    TInt initialVal = Converter::BeUint32At(initialBuf, 0);

    ASSERT(IsValid(initialVal));
    iConfigManager.Add(*this);
    iVal = initialVal;

    AddInitialSubscribers();
}

TInt ConfigNum::Min() const
{
    return iMin;
}

TInt ConfigNum::Max() const
{
    return iMax;
}

void ConfigNum::Set(TInt aVal)
{
    if (!IsValid(aVal)) {
        THROW(ConfigValueOutOfRange);
    }

    AutoMutex a(iMutex);
    if (aVal != iVal) {
        iVal = aVal;
        NotifySubscribers(iVal);
    }
}

TBool ConfigNum::IsValid(TInt aVal) const
{
    if (aVal < iMin || aVal > iMax) {
        return false;
    }
    return true;
}

TUint ConfigNum::Subscribe(FunctorGeneric<KeyValuePair<TInt>&> aFunctor)
{
    AutoMutex a(iMutex);
    return ConfigVal::Subscribe(aFunctor, iVal);
}

void ConfigNum::Serialise(IWriter& aWriter) const
{
    Bws<kMaxNumLength> buf;
    AutoMutex a(iMutex);
    Ascii::AppendDec(buf, iVal);
    aWriter.Write(buf);
    aWriter.WriteFlush();
}

void ConfigNum::Deserialise(const Brx& aString)
{
    TInt val = 0;

    try {
        val = Ascii::Int(aString);
    }
    catch (AsciiError&) {
        THROW(ConfigNotANumber);
    }
    Set(val);
}

void ConfigNum::Write(KeyValuePair<TInt>& aKvp)
{
    Bws<sizeof(TInt)> valBuf;
    WriterBuffer writerBuf(valBuf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(aKvp.Value());
    iConfigManager.ToStore(iKey, valBuf);
}


// ConfigChoice

ConfigChoice::ConfigChoice(IConfigInitialiser& aManager, const Brx& aKey, const std::vector<TUint>& aChoices, TUint aDefault)
    : ConfigVal(aManager, aKey)
    , iChoices(aChoices)
    , iMapper(nullptr)
    , iMutex("CVCM")
{
    Init(aDefault);
}

ConfigChoice::ConfigChoice(IConfigInitialiser& aManager, const Brx& aKey, const std::vector<TUint>& aChoices, TUint aDefault, IConfigChoiceMapper& aMapper)
    : ConfigVal(aManager, aKey)
    , iChoices(aChoices)
    , iMapper(&aMapper)
    , iMutex("CVCM")
{
    Init(aDefault);
}

const std::vector<TUint>& ConfigChoice::Choices() const
{
    return iChoices;
}

void ConfigChoice::Set(TUint aVal)
{
    if (!IsValid(aVal)) {
        THROW(ConfigInvalidSelection);
    }

    AutoMutex a(iMutex);
    if (aVal != iSelected) {
        iSelected = aVal;
        NotifySubscribers(iSelected);
    }
}

TBool ConfigChoice::HasInternalMapping() const
{
    if (iMapper != nullptr) {
        return true;
    }
    return false;
}

IConfigChoiceMapper& ConfigChoice::Mapper() const
{
    ASSERT(iMapper != nullptr);
    return *iMapper;
}

void ConfigChoice::Init(TUint aDefault)
{
    Bws<sizeof(TUint)> initialBuf;
    Bws<sizeof(TUint)> defaultBuf;
    WriterBuffer writerBuf(defaultBuf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(aDefault);
    iConfigManager.FromStore(iKey, initialBuf, defaultBuf);
    TUint initialVal = Converter::BeUint32At(initialBuf, 0);

    ASSERT(IsValid(initialVal));
    iConfigManager.Add(*this);
    iSelected = initialVal;

    AddInitialSubscribers();
}

TBool ConfigChoice::IsValid(TUint aVal) const
{
    std::vector<TUint>::const_iterator it;
    it = std::find(iChoices.begin(), iChoices.end(), aVal);
    if (it == iChoices.end()) {
        return false;
    }
    return true;
}

TUint ConfigChoice::Subscribe(FunctorGeneric<KeyValuePair<TUint>&> aFunctor)
{
    AutoMutex a(iMutex);
    return ConfigVal::Subscribe(aFunctor, iSelected);
}

void ConfigChoice::Serialise(IWriter& aWriter) const
{
    Bws<kMaxChoiceLength> buf;
    AutoMutex a(iMutex);
    Ascii::AppendDec(buf, iSelected);
    aWriter.Write(buf);
    aWriter.WriteFlush();
}

void ConfigChoice::Deserialise(const Brx& aString)
{
    TUint val = 0;

    try {
        val = Ascii::Uint(aString);
    }
    catch (AsciiError&) {
        THROW(ConfigNotANumber);
    }
    Set(val);
}

void ConfigChoice::Write(KeyValuePair<TUint>& aKvp)
{
    Bws<sizeof(TUint)> valBuf;
    WriterBuffer writerBuf(valBuf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(aKvp.Value());
    iConfigManager.ToStore(iKey, valBuf);
}


// ConfigText

ConfigText::ConfigText(IConfigInitialiser& aManager, const Brx& aKey, TUint aMaxLength, const Brx& aDefault)
    : ConfigVal(aManager, aKey)
    , iText(aMaxLength)
    , iMutex("CVTM")
{
    ASSERT(aMaxLength <= kMaxBytes);
    Bwh initialBuf(aMaxLength);
    iConfigManager.FromStore(iKey, initialBuf, aDefault);

    ASSERT(IsValid(initialBuf));
    iConfigManager.Add(*this);
    iText.Replace(initialBuf);

    AddInitialSubscribers();
}

TUint ConfigText::MaxLength() const
{
    return iText.MaxBytes();
}

void ConfigText::Set(const Brx& aText)
{
    if (!IsValid(aText)) {
        THROW(ConfigValueTooLong);
    }

    AutoMutex a(iMutex);
    if (aText != iText) {
        iText.Replace(aText);
        NotifySubscribers(iText);
    }
}

TBool ConfigText::IsValid(const Brx& aVal) const
{
    if (aVal.Bytes() > iText.MaxBytes()) {
        return false;
    }
    return true;
}

TUint ConfigText::Subscribe(FunctorGeneric<KeyValuePair<const Brx&>&> aFunctor)
{
    AutoMutex a(iMutex);
    return ConfigVal::Subscribe(aFunctor, iText);
}

void ConfigText::Serialise(IWriter& aWriter) const
{
    AutoMutex a(iMutex);
    aWriter.Write(iText);
    aWriter.WriteFlush();
}

void ConfigText::Deserialise(const Brx& aString)
{
    Set(aString);
}

void ConfigText::Write(KeyValuePair<const Brx&>& aKvp)
{
    iConfigManager.ToStore(iKey, aKvp.Value());
}


// WriterPrinter

void WriterPrinter::Write(TByte aValue)
{
    Bws<1> buf(aValue);
    Log::Print(buf);
}

void WriterPrinter::Write(const Brx& aBuffer)
{
    Log::Print(aBuffer);
}

void WriterPrinter::WriteFlush()
{
}


// ConfigManager

ConfigManager::ConfigManager(IStoreReadWrite& aStore)
    : iStore(aStore)
    , iOpen(false)
    , iLock("CFML")
{
}

void ConfigManager::WriteKeys(IKeyWriter& aWriter) const
{
    AutoMutex a(iLock);
    ASSERT(iOpen);
    aWriter.WriteKeys(iKeyListOrdered);
}

TBool ConfigManager::HasNum(const Brx& aKey) const
{
    return iMapNum.Has(aKey);
}

ConfigNum& ConfigManager::GetNum(const Brx& aKey) const
{
    return iMapNum.Get(aKey);
}

TBool ConfigManager::HasChoice(const Brx& aKey) const
{
    return iMapChoice.Has(aKey);
}

ConfigChoice& ConfigManager::GetChoice(const Brx& aKey) const
{
    return iMapChoice.Get(aKey);
}

TBool ConfigManager::HasText(const Brx& aKey) const
{
    return iMapText.Has(aKey);
}

ConfigText& ConfigManager::GetText(const Brx& aKey) const
{
    return iMapText.Get(aKey);
}

TBool ConfigManager::Has(const Brx& aKey) const
{
    return HasNum(aKey) || HasChoice(aKey) || HasText(aKey);
}

ISerialisable& ConfigManager::Get(const Brx& aKey) const
{
    // FIXME - ASSERT if !iOpen?
    if (HasNum(aKey)) {
        return iMapNum.Get(aKey);
    }
    else if (HasChoice(aKey)) {
        return iMapChoice.Get(aKey);
    }
    else if (HasText(aKey)) {
        return iMapText.Get(aKey);
    }
    else {
        ASSERTS();
        return iMapNum.Get(aKey); // control will never reach here
    }
}

void ConfigManager::Print() const
{
    Log::Print("ConfigManager: [\n");

    Log::Print("ConfigNum:\n");
    Print(iMapNum);
    Log::Print("ConfigChoice:\n");
    Print(iMapChoice);
    Log::Print("ConfigText:\n");
    Print(iMapText);

    Log::Print("]\n");
}

void ConfigManager::DumpToStore()
{
    StoreDumper dumper(*this);
    dumper.DumpToStore(iMapNum);
    dumper.DumpToStore(iMapChoice);
    dumper.DumpToStore(iMapText);
}

IStoreReadWrite& ConfigManager::Store()
{
    return iStore;
}

void ConfigManager::Open()
{
    AutoMutex a(iLock);
    // All keys should have been added, so sort key list.
    std::sort(iKeyListOrdered.begin(), iKeyListOrdered.end(), BufferPtrCmp());
    iOpen = true;
}

void ConfigManager::Add(ConfigNum& aNum)
{
    AddNum(aNum.Key(), aNum);
    iKeyListOrdered.push_back(&aNum.Key());
}

void ConfigManager::Add(ConfigChoice& aChoice)
{
    AddChoice(aChoice.Key(), aChoice);
    iKeyListOrdered.push_back(&aChoice.Key());
}

void ConfigManager::Add(ConfigText& aText)
{
    AddText(aText.Key(), aText);
    iKeyListOrdered.push_back(&aText.Key());
}

void ConfigManager::FromStore(const Brx& aKey, Bwx& aDest, const Brx& aDefault)
{
    // try retrieve from store; create entry if it doesn't exist
    try {
        iStore.Read(aKey, aDest);
    }
    catch (StoreKeyNotFound&) {
        // Don't attempt to write default value out to store here. It will be
        // written if/when the value is changed.
        aDest.Replace(aDefault);
    }
}

void ConfigManager::ToStore(const Brx& aKey, const Brx& aValue)
{
    iStore.Write(aKey, aValue);
}

void ConfigManager::AddNum(const Brx& aKey, ConfigNum& aNum)
{
    Add(iMapNum, aKey, aNum);
}

void ConfigManager::AddChoice(const Brx& aKey, ConfigChoice& aChoice)
{
    Add(iMapChoice, aKey, aChoice);
}

void ConfigManager::AddText(const Brx& aKey, ConfigText& aText)
{
    Add(iMapText, aKey, aText);
}

template <class T> void ConfigManager::Add(SerialisedMap<T>& aMap, const Brx& aKey, T& aVal)
{
    {
        AutoMutex _(iLock);
        if (iOpen) {
            ASSERTS();
        }
    }
    if (HasNum(aKey) || HasChoice(aKey) || HasText(aKey)) {
        THROW(ConfigKeyExists);
    }

    aMap.Add(aKey, aVal);
}

template <class T> void ConfigManager::Print(const ConfigVal<T>& aVal) const
{
    WriterPrinter writerPrinter;
    Log::Print("    {");
    Log::Print(aVal.Key());
    Log::Print(", ");
    aVal.Serialise(writerPrinter);
    Log::Print("}\n");
}

template <class T> void ConfigManager::Print(const SerialisedMap<T>& aMap) const
{
    // Map iterators are not invalidated by any of the actions that
    // SerialisedMap allows, so don't need to lock.
    typename SerialisedMap<T>::Iterator it;
    for (it = aMap.Begin(); it != aMap.End(); ++it) {
        Print(*it->second);
    }
}


// ConfigManager::StoreDumper

ConfigManager::StoreDumper::StoreDumper(IConfigInitialiser& aConfigInit)
    : iConfigInit(aConfigInit)
{
}

void ConfigManager::StoreDumper::DumpToStore(const SerialisedMap<ConfigNum>& aMap)
{
    SerialisedMap<ConfigNum>::Iterator it;
    for (it = aMap.Begin(); it != aMap.End(); ++it) {
        ConfigNum& configVal = *it->second;
        TUint id = configVal.Subscribe(MakeFunctorConfigNum(*this, &ConfigManager::StoreDumper::NotifyChangedNum));
        configVal.Unsubscribe(id);
    }
}

void ConfigManager::StoreDumper::DumpToStore(const SerialisedMap<ConfigChoice>& aMap)
{
    SerialisedMap<ConfigChoice>::Iterator it;
    for (it = aMap.Begin(); it != aMap.End(); ++it) {
        ConfigChoice& configVal = *it->second;
        TUint id = configVal.Subscribe(MakeFunctorConfigChoice(*this, &ConfigManager::StoreDumper::NotifyChangedChoice));
        configVal.Unsubscribe(id);
    }
}

void ConfigManager::StoreDumper::DumpToStore(const SerialisedMap<ConfigText>& aMap)
{
    SerialisedMap<ConfigText>::Iterator it;
    for (it = aMap.Begin(); it != aMap.End(); ++it) {
        ConfigText& configVal = *it->second;
        TUint id = configVal.Subscribe(MakeFunctorConfigText(*this, &ConfigManager::StoreDumper::NotifyChangedText));
        configVal.Unsubscribe(id);
    }
}

void ConfigManager::StoreDumper::NotifyChangedNum(ConfigNum::KvpNum& aKvp)
{
    Bws<sizeof(TInt)> valBuf;
    WriterBuffer writerBuf(valBuf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(aKvp.Value());
    iConfigInit.ToStore(aKvp.Key(), valBuf);
}

void ConfigManager::StoreDumper::NotifyChangedChoice(ConfigChoice::KvpChoice& aKvp)
{
    Bws<sizeof(TUint)> valBuf;
    WriterBuffer writerBuf(valBuf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(aKvp.Value());
    iConfigInit.ToStore(aKvp.Key(), valBuf);
}

void ConfigManager::StoreDumper::NotifyChangedText(ConfigText::KvpText& aKvp)
{
    iConfigInit.ToStore(aKvp.Key(), aKvp.Value());
}
