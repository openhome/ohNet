#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>

#include <algorithm>

using namespace OpenHome;
using namespace OpenHome::Configuration;


// ConfigNum

ConfigNum::ConfigNum(IConfigManagerWriter& aManager, const Brx& aId, TInt aMin, TInt aMax, TInt aDefault)
    : ConfigVal(aManager, aId)
    , iMin(aMin)
    , iMax(aMax)
    , iMutex("CVNM")
{
    ASSERT(iMax >= iMin);

    Bws<sizeof(TInt)> initialBuf;
    Bws<sizeof(TInt)> defaultBuf;
    defaultBuf.Append(Arch::BigEndian4(aDefault));
    iConfigManager.FromStore(iId, initialBuf, defaultBuf);
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

TBool ConfigNum::Set(TInt aVal)
{
    TBool changed = false;

    if (!IsValid(aVal)) {
        THROW(ConfigValueOutOfRange);
    }

    iMutex.Wait();
    if (aVal != iVal) {
        iVal = aVal;
        NotifySubscribers(iVal);
        changed = true;
    }
    iMutex.Signal();

    return changed;
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

void ConfigNum::Write(KeyValuePair<TInt>& aKvp)
{
    Bws<sizeof(TInt)> valBuf;
    valBuf.Append(Arch::BigEndian4(aKvp.Value()));
    iConfigManager.ToStore(iId, valBuf);
}


// ConfigChoice

ConfigChoice::ConfigChoice(IConfigManagerWriter& aManager, const Brx& aId, const std::vector<TUint>& aChoices, TUint aDefault)
    : ConfigVal(aManager, aId)
    , iChoices(aChoices)
    , iMutex("CVCM")
{
    Bws<sizeof(TUint)> initialBuf;
    Bws<sizeof(TUint)> defaultBuf;
    defaultBuf.Append(Arch::BigEndian4(aDefault));
    iConfigManager.FromStore(iId, initialBuf, defaultBuf);
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

TBool ConfigChoice::Set(TUint aVal)
{
    TBool changed = false;

    if (!IsValid(aVal)) {
        THROW(ConfigInvalidChoice);
    }

    iMutex.Wait();
    if (aVal != iSelected) {
        iSelected = aVal;
        NotifySubscribers(iSelected);
        changed = true;
    }
    iMutex.Signal();

    return changed;
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

void ConfigChoice::Write(KeyValuePair<TUint>& aKvp)
{
    Bws<sizeof(TUint)> valBuf;
    valBuf.Append(Arch::BigEndian4(aKvp.Value()));
    iConfigManager.ToStore(iId, valBuf);
}


// ConfigText

ConfigText::ConfigText(IConfigManagerWriter& aManager, const Brx& aId, TUint aMaxLength, const Brx& aDefault)
    : ConfigVal(aManager, aId)
    , iText(aMaxLength)
    , iMutex("CVTM")
{
    Bwh initialBuf(aMaxLength);
    iConfigManager.FromStore(iId, initialBuf, aDefault);

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

TBool ConfigText::Set(const Brx& aText)
{
    TBool changed = false;
    AutoMutex a(iMutex);

    if (!IsValid(aText)) {
        THROW(ConfigValueTooLong);
    }

    if (aText != iText) {
        iText.Replace(aText);
        NotifySubscribers(iText);
        changed = true;
    }

    return changed;
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

void ConfigText::Write(KeyValuePair<const Brx&>& aKvp)
{
    iConfigManager.ToStore(iId, aKvp.Value());
}


// ConfigManager

ConfigManager::ConfigManager(IStoreReadWrite& aStore)
    : iStore(aStore)
    , iClosed(false)
{
}

ConfigManager::~ConfigManager() {}

template <class T> void ConfigManager::Add(SerialisedMap<T>& aMap, const Brx& aId, T& aVal)
{
    if (iClosed) {
        ASSERTS();
    }
    if (HasNum(aId) || HasChoice(aId) || HasText(aId)) {
        THROW(ConfigIdExists);
    }

    aMap.Add(aId, aVal);
}

void ConfigManager::Close()
{
    iClosed = true;
}

void ConfigManager::Add(ConfigNum& aNum)
{
    Add(iMapNum, aNum.Id(), aNum);
}

void ConfigManager::Add(ConfigChoice& aChoice)
{
    Add(iMapChoice, aChoice.Id(), aChoice);
}

void ConfigManager::Add(ConfigText& aText)
{
    Add(iMapText, aText.Id(), aText);
}

void ConfigManager::FromStore(const Brx& aKey, Bwx& aDest, const Brx& aDefault)
{
    // try retrieve from store; create entry if it doesn't exist
    try {
        iStore.Read(aKey, aDest);
    }
    catch (StoreKeyNotFound&) {
        ToStore(aKey, aDefault);
        aDest.Replace(aDefault);
    }
}

void ConfigManager::ToStore(const Brx& aKey, const Brx& aValue)
{
    iStore.Write(aKey, aValue);
}

TBool ConfigManager::Has(const Brx& aId) const
{
    return HasNum(aId) || HasChoice(aId) || HasText(aId);
}

TBool ConfigManager::HasNum(const Brx& aId) const
{
    return iMapNum.Has(aId);
}

ConfigNum& ConfigManager::GetNum(const Brx& aId) const
{
    return iMapNum.Get(aId);
}

TBool ConfigManager::HasChoice(const Brx& aId) const
{
    return iMapChoice.Has(aId);
}

ConfigChoice& ConfigManager::GetChoice(const Brx& aId) const
{
    return iMapChoice.Get(aId);
}

TBool ConfigManager::HasText(const Brx& aId) const
{
    return iMapText.Has(aId);
}

ConfigText& ConfigManager::GetText(const Brx& aId) const
{
    return iMapText.Get(aId);
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

void ConfigRamStore::Print()
{
    Log::Print("RamStore: [\n");
    AutoMutex a(iLock);
    Map::iterator it = iMap.begin();
    while (it!= iMap.end()) {
        Log::Print("   {");
        Log::Print(it->first);
        Log::Print(", ");
        Brh& valBuf = *it->second;
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
    Map::iterator it = iMap.find(key);
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
    Brn key(aKey);
    AutoMutex a(iLock);
    Brh* val = new Brh(aSource);

    // std::map doesn't insert a value if key exists, so first remove existing
    // key-value pair, if new value is different
    Map::iterator it = iMap.find(key);
    if (it != iMap.end()) {
        if (*(it->second) == aSource) {
            // new value is the same; free memory
            delete val;
            return;
        }
        else {
            // new value is different; remove old value
            delete it->second;
            iMap.erase(it);
        }
    }

    iMap.insert(std::pair<Brn,Brh*>(key, val));
}

void ConfigRamStore::Delete(const Brx& aKey)
{
    Brn key(aKey);
    AutoMutex a(iLock);
    Map::iterator it = iMap.find(key);
    if (it == iMap.end()) {
        THROW(StoreKeyNotFound);
    }

    delete it->second;
    iMap.erase(it);
}

void ConfigRamStore::Clear()
{
    AutoMutex a(iLock);
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        delete it->second;
        it++;
    }
    iMap.clear();
}
