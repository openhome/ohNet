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

ConfigNum::ConfigNum(IConfigManagerInitialiser& aManager, const Brx& aKey, TInt aMin, TInt aMax, TInt aDefault)
    : ConfigVal(aManager, aKey)
    , iMin(aMin)
    , iMax(aMax)
    , iMutex("CVNM")
{
    ASSERT(iMax >= iMin);

    Bws<sizeof(TInt)> initialBuf;
    Bws<sizeof(TInt)> defaultBuf;
    defaultBuf.Append(Arch::BigEndian4(aDefault));
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
    valBuf.Append(Arch::BigEndian4(aKvp.Value()));
    iConfigManager.ToStore(iKey, valBuf);
}


// ConfigChoice

ConfigChoice::ConfigChoice(IConfigManagerInitialiser& aManager, const Brx& aKey, const std::vector<TUint>& aChoices, TUint aDefault)
    : ConfigVal(aManager, aKey)
    , iChoices(aChoices)
    , iMutex("CVCM")
{
    Bws<sizeof(TUint)> initialBuf;
    Bws<sizeof(TUint)> defaultBuf;
    defaultBuf.Append(Arch::BigEndian4(aDefault));
    iConfigManager.FromStore(iKey, initialBuf, defaultBuf);
    TUint initialVal = Converter::BeUint32At(initialBuf, 0);

    ASSERT(IsValid(initialVal));
    iConfigManager.Add(*this);
    iSelected = initialVal;

    AddInitialSubscribers();
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
    valBuf.Append(Arch::BigEndian4(aKvp.Value()));
    iConfigManager.ToStore(iKey, valBuf);
}


// ConfigText

ConfigText::ConfigText(IConfigManagerInitialiser& aManager, const Brx& aKey, TUint aMaxLength, const Brx& aDefault)
    : ConfigVal(aManager, aKey)
    , iText(aMaxLength)
    , iMutex("CVTM")
{
    Bwh initialBuf(aMaxLength);
    iConfigManager.FromStore(iKey, initialBuf, aDefault);

    ASSERT(IsValid(initialBuf));
    iConfigManager.Add(*this);
    iText.Replace(initialBuf);

    AddInitialSubscribers();
}

TUint ConfigText::MaxLength() const
{
    AutoMutex a(iMutex);
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


// BufferPtrCmp

TBool BufferPtrCmp::operator()(const Brx* aStr1, const Brx* aStr2) const
{
    return BufferCmp()(*aStr1, *aStr2);
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

void ConfigManager::Print() const
{
    WriterPrinter writerPrinter;
    Log::Print("ConfigManager: [\n");

    Log::Print("ConfigNum:\n");
    Print(iMapNum);
    Log::Print("ConfigChoice:\n");
    Print(iMapChoice);
    Log::Print("ConfigText:\n");
    Print(iMapText);

    Log::Print("]\n");
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

IStoreReadWrite& ConfigManager::Store()
{
    return iStore;
}

void ConfigManager::Open()
{
    AutoMutex a(iLock);
    iOpen = true;
}

void ConfigManager::Add(ConfigNum& aNum)
{
    AddNum(aNum.Key(), aNum);
}

void ConfigManager::Add(ConfigChoice& aChoice)
{
    AddChoice(aChoice.Key(), aChoice);
}

void ConfigManager::Add(ConfigText& aText)
{
    AddText(aText.Key(), aText);
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
    iLock.Wait();
    if (iOpen) {
        iLock.Signal();
        ASSERTS();
    }
    iLock.Signal();
    if (HasNum(aKey) || HasChoice(aKey) || HasText(aKey)) {
        THROW(ConfigKeyExists);
    }

    aMap.Add(aKey, aVal);
}

template <class T> void ConfigManager::Print(const ConfigVal<T>& aVal) const
{
    WriterPrinter writerPrinter;
    Log::Print("   {");
    Log::Print(aVal.Key());
    Log::Print(", ");
    aVal.Serialise(writerPrinter);
    Log::Print("}\n");
}

template <class T> void ConfigManager::Print(const SerialisedMap<T>& aMap) const
{
    // Map iterators are not invalidated by any of the actions that
    // SerialisedMap allows, so don't need to lock.
    SerialisedMap<T>::Iterator it;
    for (it = aMap.Begin(); it != aMap.End(); ++it) {
        Log::Print("    ");
        Log::Print(*it->first);
        Log::Print(": ");
        Print(*it->second);
    }
}


// ConfigRamStore

ConfigRamStore::ConfigRamStore()
    : iLock("RAMS")
{
}

ConfigRamStore::~ConfigRamStore()
{
    Clear();
}

void ConfigRamStore::Print() const
{
    Log::Print("RamStore: [\n");
    AutoMutex a(iLock);
    Map::const_iterator it = iMap.begin();
    while (it!= iMap.end()) {
        Log::Print("   {");
        Log::Print(*it->first);
        Log::Print(", ");
        const Brx& valBuf = *it->second;
        if (valBuf.Bytes() == sizeof(TUint32)) {
            TUint32 val = Converter::BeUint32At(valBuf, 0);
            Log::Print("%u/", val);
            Log::Print(valBuf);
        }
        else {
            Log::Print(valBuf);
        }
        Log::Print("}\n");
        it++;
    }
    Log::Print("]\n");
}

void ConfigRamStore::Read(const Brx& aKey, Bwx& aDest)
{
    Brn key(aKey);
    AutoMutex a(iLock);
    Map::iterator it = iMap.find(&key);
    if (it == iMap.end()) {
        THROW(StoreKeyNotFound);
    }

    if (it->second->Bytes() > aDest.MaxBytes()) {
        THROW(StoreReadBufferUndersized);
    }

    aDest.Replace(*(it->second));
}

void ConfigRamStore::Write(const Brx& aKey, const Brx& aSource)
{
    Brh* key = new Brh(aKey);
    Brh* val = new Brh(aSource);

    AutoMutex a(iLock);

    // std::map doesn't insert a value if key exists, so first remove existing
    // key-value pair, if new value is different
    Map::iterator it = iMap.find(key);
    if (it != iMap.end()) {
        if (*(it->second) == aSource) {
            // new value is the same; free memory
            delete key;
            delete val;
            return;
        }
        else {
            // new value is different; remove old value
            delete it->first;
            delete it->second;
            iMap.erase(it);
        }
    }

    iMap.insert(std::pair<const Brx*, const Brx*>(key, val));
}

void ConfigRamStore::Delete(const Brx& aKey)
{
    Brn key(aKey);
    AutoMutex a(iLock);
    Map::iterator it = iMap.find(&key);
    if (it == iMap.end()) {
        THROW(StoreKeyNotFound);
    }

    delete it->first;
    delete it->second;
    iMap.erase(it);
}

void ConfigRamStore::Clear()
{
    AutoMutex a(iLock);
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        delete it->first;
        delete it->second;
        it++;
    }
    iMap.clear();
}
