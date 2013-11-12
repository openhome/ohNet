#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Configuration;


// ConfigNum

ConfigNum::ConfigNum(IConfigurationManager& aManager, const Brx& aId, FunctorGeneric<TInt> aFunc, TInt aMin, TInt aMax, TInt aDefault)
    : ConfigVal(aManager, aId)
    , iMin(aMin)
    , iMax(aMax)
{
    ASSERT(iMax >= iMin);

    Bws<sizeof(TInt)> initialBuf;
    Bws<sizeof(TInt)> defaultBuf;
    defaultBuf.Append(Arch::BigEndian4(aDefault));
    iConfigManager.Read(iId, initialBuf, defaultBuf);
    TInt initialVal = Converter::BeUint32At(initialBuf, 0);

    ASSERT(IsValid(initialVal));
    iConfigManager.Add(*this);
    iVal = initialVal;

    AddInitialSubscribers(aFunc);
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

    if (aVal != iVal) {
        iVal = aVal;
        NotifySubscribers(iVal);
        changed = true;
    }

    return changed;
}

TBool ConfigNum::IsValid(TInt aVal)
{
    if (aVal < iMin || aVal > iMax) {
        return false;
    }
    return true;
}

TUint ConfigNum::Subscribe(FunctorGeneric<TInt> aFunctor)
{
    return ConfigVal::Subscribe(aFunctor, iVal);
}

void ConfigNum::Write(TInt aVal)
{
    Bws<sizeof(TInt)> valBuf;
    valBuf.Append(Arch::BigEndian4(aVal));
    iConfigManager.Write(iId, valBuf);
}


// ConfigChoice

ConfigChoice::ConfigChoice(IConfigurationManager& aManager, const Brx& aId, FunctorGeneric<TUint> aFunc, std::vector<const Brx*> aOptions, TUint aDefault)
    : ConfigVal(aManager, aId)
{
    for (TUint i=0; i<aOptions.size(); i++)
    {
        Add(*aOptions[i]);
    }

    Bws<sizeof(TUint)> initialBuf;
    Bws<sizeof(TUint)> defaultBuf;
    defaultBuf.Append(Arch::BigEndian4(aDefault));
    iConfigManager.Read(iId, initialBuf, defaultBuf);
    TUint initialVal = Converter::BeUint32At(initialBuf, 0);

    ASSERT(IsValid(initialVal));
    iConfigManager.Add(*this);
    iSelected = initialVal;

    AddInitialSubscribers(aFunc);
}

void ConfigChoice::Add(const Brx& aVal)
{
    Brn val(aVal);
    std::vector<Brn>::iterator it;
    for (it = iAllowedValues.begin(); it != iAllowedValues.end(); it++) {
        if (*it == aVal) {
            THROW(ConfigValueExists);
        }
    }
    iAllowedValues.push_back(val);
}

std::vector<const Brx*> ConfigChoice::Options()
{
    std::vector<const Brx*> options;
    std::vector<Brn>::iterator it;
    for (it = iAllowedValues.begin(); it != iAllowedValues.end(); it++) {
        options.push_back(&*it);
    }
    return options;
}

TBool ConfigChoice::Set(TUint aIndex)
{
    TBool changed = false;

    if (!IsValid(aIndex)) {
        THROW(ConfigIndexOutOfRange);
    }

    if (aIndex != iSelected) {
        iSelected = aIndex;
        NotifySubscribers(iSelected);
        changed = true;
    }

    return changed;
}

TBool ConfigChoice::IsValid(TUint aVal)
{
    if (aVal >= iAllowedValues.size()) {
        return false;
    }
    return true;
}

TUint ConfigChoice::Subscribe(FunctorGeneric<TUint> aFunctor)
{
    return ConfigVal::Subscribe(aFunctor, iSelected);
}

void ConfigChoice::Write(TUint aVal)
{
    Bws<sizeof(TUint)> valBuf;
    valBuf.Append(Arch::BigEndian4(aVal));
    iConfigManager.Write(iId, valBuf);
}


// ConfigText

ConfigText::ConfigText(IConfigurationManager& aManager, const Brx& aId, FunctorGeneric<const Brx&> aFunc, TUint aMaxLength, const Brx& aDefault)
    : ConfigVal(aManager, aId)
    , iText(aMaxLength)
{
    Bwh initialBuf(aMaxLength);
    iConfigManager.Read(iId, initialBuf, aDefault);

    ASSERT(IsValid(initialBuf));
    iConfigManager.Add(*this);
    iText.Replace(initialBuf);

    AddInitialSubscribers(aFunc);
}

TUint ConfigText::MaxLength() const
{
    return iText.MaxBytes();
}

TBool ConfigText::Set(const Brx& aText)
{
    TBool changed = false;

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

TBool ConfigText::IsValid(const Brx& aVal)
{
    if (aVal.Bytes() > iText.MaxBytes()) {
        return false;
    }
    return true;
}

TUint ConfigText::Subscribe(FunctorGeneric<const Brx&> aFunctor)
{
    return ConfigVal::Subscribe(aFunctor, iText);
}

void ConfigText::Write(const Brx& aVal)
{
    iConfigManager.Write(iId, aVal);
}


// ConfigurationManager

ConfigurationManager::ConfigurationManager(IStoreReadWrite& aStore)
    : iStore(aStore)
    , iClosed(false)
{
}

ConfigurationManager::~ConfigurationManager() {}

template <class T> void ConfigurationManager::Add(SerialisedMap<T>& aMap, const Brx& aId, T& aVal)
{
    if (iClosed) {
        ASSERTS();
    }
    if (HasNum(aId) || HasChoice(aId) || HasText(aId)) {
        THROW(ConfigIdExists);
    }

    aMap.Add(aId, aVal);
}

void ConfigurationManager::Close()
{
    iClosed = true;
}

void ConfigurationManager::Add(ConfigNum& aNum)
{
    Add(iMapNum, aNum.Id(), aNum);
}

void ConfigurationManager::Add(ConfigChoice& aChoice)
{
    Add(iMapChoice, aChoice.Id(), aChoice);
}

void ConfigurationManager::Add(ConfigText& aText)
{
    Add(iMapText, aText.Id(), aText);
}

void ConfigurationManager::Read(const Brx& aKey, Bwx& aDest, const Brx& aDefault)
{
    // try retrieve from store; create entry if it doesn't exist
    try {
        iStore.Read(aKey, aDest);
    }
    catch (StoreKeyNotFound&) {
        Write(aKey, aDefault);
        aDest.Replace(aDefault);
    }
}

void ConfigurationManager::Write(const Brx& aKey, const Brx& aValue)
{
    iStore.Write(aKey, aValue);
}

TBool ConfigurationManager::Has(const Brx& aId) const
{
    return HasNum(aId) || HasChoice(aId) || HasText(aId);
}

TBool ConfigurationManager::HasNum(const Brx& aId) const
{
    return iMapNum.Has(aId);
}

ConfigNum& ConfigurationManager::GetNum(const Brx& aId) const
{
    return iMapNum.Get(aId);
}

TBool ConfigurationManager::HasChoice(const Brx& aId) const
{
    return iMapChoice.Has(aId);
}

ConfigChoice& ConfigurationManager::GetChoice(const Brx& aId) const
{
    return iMapChoice.Get(aId);
}

TBool ConfigurationManager::HasText(const Brx& aId) const
{
    return iMapText.Has(aId);
}

ConfigText& ConfigurationManager::GetText(const Brx& aId) const
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
        Log::Print(*it->second);
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
