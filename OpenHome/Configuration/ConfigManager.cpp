#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Configuration;


// ConfigVal

ConfigVal::ConfigVal(ConfigurationManager& aManager, const Brx& aId, Functor aFunc)
    : iConfigManager(aManager)
    , iId(aId)
    , iObserverLock("CVOL")
    , iNextObserverId(0)
{
    iOwnerObserverId = Subscribe(aFunc);
    iWriteObserverId = Subscribe(MakeFunctor(*this, &ConfigVal::Write));
}

ConfigVal::~ConfigVal()
{
    Unsubscribe(iWriteObserverId);
    Unsubscribe(iOwnerObserverId);
    ASSERT(iObservers.size() == 0);
}

const Brx& ConfigVal::Id()
{
    return iId;
}

TUint ConfigVal::Subscribe(Functor aFunctor)
{
    iObserverLock.Wait();
    TUint id = iNextObserverId;
    iObservers.insert(std::pair<TUint,Functor>(id, aFunctor));
    iNextObserverId++;
    iObserverLock.Signal();
    return id;
}

void ConfigVal::Unsubscribe(TUint aId)
{
    iObserverLock.Wait();
    Map::iterator it = iObservers.find(aId);
    if (it != iObservers.end()) {
        iObservers.erase(it);
    }
    iObserverLock.Signal();
}

void ConfigVal::NotifySubscribers()
{
    AutoMutex a(iObserverLock);
    for (Map::iterator it = iObservers.begin(); it != iObservers.end(); it++) {
        it->second();
    }
}


// ConfigNum

ConfigNum::ConfigNum(ConfigurationManager& aManager, const Brx& aId, Functor aFunc, TInt aMin, TInt aMax, TInt aDefault)
    : ConfigVal(aManager, aId, aFunc)
    , iMin(aMin)
    , iMax(aMax)
{
    if (iMin > iMax) {
        THROW(AvConfigInvalidRange);
    }

    Bws<sizeof(TInt)> initialBuf;
    Bws<sizeof(TInt)> defaultBuf;
    defaultBuf.Append(Arch::BigEndian4(aDefault));
    iConfigManager.Read(iId, initialBuf, defaultBuf);
    TInt initialVal = Converter::BeUint32At(initialBuf, 0);
    Set(initialVal); // FIXME - calling this causes observers to be called - do we want that?

    iConfigManager.Add(*this);
}

TInt ConfigNum::Min() const
{
    return iMin;
}

TInt ConfigNum::Max() const
{
    return iMax;
}

TInt ConfigNum::Get() const
{
    return iVal;
}

TBool ConfigNum::Set(TInt aVal)
{
    TBool changed = false;

    if (aVal < iMin || aVal > iMax) {
        THROW(AvConfigValueOutOfRange);
    }

    if (aVal != iVal) {
        iVal = aVal;
        ConfigVal::NotifySubscribers();
        changed = true;
    }

    return changed;
}

void ConfigNum::Write()
{
    Bws<sizeof(TInt)> valBuf;
    valBuf.Append(Arch::BigEndian4(Get()));
    iConfigManager.Write(iId, valBuf);
}


// ConfigChoice

ConfigChoice::ConfigChoice(ConfigurationManager& aManager, const Brx& aId, Functor aFunc, std::vector<const Brx*> aOptions, TUint aDefault)
    : ConfigVal(aManager, aId, aFunc)
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
    try {
        Set(initialVal);
    }
    catch (AvConfigIndexOutOfRange&) {
        ASSERTS();
    }

    iConfigManager.Add(*this);
}

void ConfigChoice::Add(const Brx& aVal)
{
    Brn val(aVal);
    std::vector<Brn>::iterator it;
    for (it = iAllowedValues.begin(); it != iAllowedValues.end(); it++) {
        if (*it == aVal) {
            THROW(AvConfigValueExists);
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

TUint ConfigChoice::Get() const
{
    ASSERT(iAllowedValues.size() > 0);
    return iSelected;
}

TBool ConfigChoice::Set(TUint aIndex)
{
    TBool changed = false;

    if (aIndex >= iAllowedValues.size()) {
        THROW(AvConfigIndexOutOfRange);
    }

    if (aIndex != iSelected) {
        iSelected = aIndex;
        ConfigVal::NotifySubscribers();
        changed = true;
    }

    return changed;
}

void ConfigChoice::Write()
{
    Bws<sizeof(TUint)> valBuf;
    valBuf.Append(Arch::BigEndian4(Get()));
    iConfigManager.Write(iId, valBuf);
}


// ConfigText

ConfigText::ConfigText(ConfigurationManager& aManager, const Brx& aId, Functor aFunc, TUint aMaxLength, const Brx& aDefault)
    : ConfigVal(aManager, aId, aFunc)
    , iText(aMaxLength)
{
    Bwh initialBuf(aMaxLength);
    iConfigManager.Read(iId, initialBuf, aDefault);
    try {
        Set(initialBuf);
    }
    catch (AvConfigValueTooLong&) {
        ASSERTS();
    }

    iConfigManager.Add(*this);
}

TUint ConfigText::MaxLength() const
{
    return iText.MaxBytes();
}

const Brx& ConfigText::Get() const
{
    return iText;
}

TBool ConfigText::Set(const Brx& aText)
{
    TBool changed = false;

    if (aText.Bytes() > iText.MaxBytes()) {
        THROW(AvConfigValueTooLong);
    }

    if (aText != iText) {
        iText.Replace(aText);
        ConfigVal::NotifySubscribers();
        changed = true;
    }

    return changed;
}

void ConfigText::Write()
{
    iConfigManager.Write(iId, Get());
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
        THROW(AvConfigIdExists);
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

ConfigVal& ConfigurationManager::Get(const Brx& aId) const
{
    ASSERT(Has(aId));
    if (HasNum(aId)) {
        return GetNum(aId);
    }
    else if (HasChoice(aId)) {
        return GetChoice(aId);
    }
    else {
        return GetText(aId);
    }
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
            // new value is the same; do nothing
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
