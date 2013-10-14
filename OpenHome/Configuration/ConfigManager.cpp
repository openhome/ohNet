#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Converter.h>

using namespace OpenHome;
using namespace OpenHome::Configuration;


// ConfigVal

ConfigVal::ConfigVal()
    : iObserverLock("CVOL")
    , iNextObserverId(0)
{
}

ConfigVal::~ConfigVal()
{
    ASSERT(iObservers.size() == 0);
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

ConfigNum::ConfigNum(TInt aMin, TInt aMax, TInt aVal)
    : iMin(aMin)
    , iMax(aMax)
    , iVal(aVal)
{
    if (iMin > iMax) {
        THROW(AvConfigInvalidRange);
    }

    if (iVal < iMin || iVal > iMax) {
        THROW(AvConfigValueOutOfRange);
    }
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


// ConfigChoice

ConfigChoice::ConfigChoice()
    : iSelected(0)
{
}

ConfigChoice::~ConfigChoice()
{
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


// ConfigText

ConfigText::ConfigText(TUint aMaxBytes)
    : iText(aMaxBytes)
{
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


// ConfigurationManager

ConfigurationManager::~ConfigurationManager() {}

template <class T> void ConfigurationManager::Add(SerialisedMap<T>& aMap, const Brx& aId, T& aVal)
{
    if (HasNum(aId) || HasChoice(aId) || HasText(aId)) {
        THROW(AvConfigIdExists);
    }

    aMap.Add(aId, aVal);
}

void ConfigurationManager::Add(const Brx& aId, ConfigNum& aNum)
{
    Add(iMapNum, aId, aNum);
}

void ConfigurationManager::Add(const Brx& aId, ConfigChoice& aChoice)
{
    Add(iMapChoice, aId, aChoice);
}

void ConfigurationManager::Add(const Brx& aId, ConfigText& aText)
{
    Add(iMapText, aId, aText);
}

TBool ConfigurationManager::Has(const Brx& aId)
{
    return HasNum(aId) || HasChoice(aId) || HasText(aId);
}

ConfigVal& ConfigurationManager::Get(const Brx& aId)
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

TBool ConfigurationManager::HasNum(const Brx& aId)
{
    return iMapNum.Has(aId);
}

ConfigNum& ConfigurationManager::GetNum(const Brx& aId)
{
    return iMapNum.Get(aId);
}

TBool ConfigurationManager::HasChoice(const Brx& aId)
{
    return iMapChoice.Has(aId);
}

ConfigChoice& ConfigurationManager::GetChoice(const Brx& aId)
{
    return iMapChoice.Get(aId);
}

TBool ConfigurationManager::HasText(const Brx& aId)
{
    return iMapText.Has(aId);
}

ConfigText& ConfigurationManager::GetText(const Brx& aId)
{
    return iMapText.Get(aId);
}


// StoreVal

StoreVal::StoreVal(IStoreReadWrite& aStore, const Brx& aId, TBool aUpdatesDeferred, ConfigVal* aVal)
    : iStore(aStore)
    , iId(aId)
    , iLock("SVLK")
    , iUpdatePending(false)
    , iVal(aVal)
    , iUpdatesDeferred(aUpdatesDeferred)
{
    // StoreVal takes ownership of its ConfigVal
    ASSERT(iVal != NULL);
    iListenerId = aVal->Subscribe(MakeFunctor(*this, &StoreVal::NotifyChanged));
}

StoreVal::~StoreVal()
{
    iVal->Unsubscribe(iListenerId);
    delete iVal;
}

TBool StoreVal::UpdatePending()
{
    AutoMutex a(iLock);
    return iUpdatePending;
}

void StoreVal::NotifyChanged()
{
    iLock.Wait();
    iUpdatePending = true;
    iLock.Signal();
    if (!iUpdatesDeferred) {
        // the Write() method of classes deriving from this should regain iLock to set iUpdatePending
        Write();
    }
}


// StoreNum

StoreNum::StoreNum(IStoreReadWrite& aStore, const Brx& aId, TBool aUpdatesDeferred, ConfigNum* aVal)
    : StoreVal(aStore, aId, aUpdatesDeferred, aVal)
    , iNum(aVal)
{
}

void StoreNum::Write()
{
    AutoMutex a(iLock);
    if (iUpdatePending) {
        iUpdatePending = false;
        Bws<sizeof(TInt)> buf;
        buf.Append(iNum->Get());
        iStore.Write(iId, buf);
    }
}


// StoreChoice

StoreChoice::StoreChoice(IStoreReadWrite& aStore, const Brx& aId, TBool aUpdatesDeferred, ConfigChoice* aVal)
    : StoreVal(aStore, aId, aUpdatesDeferred, aVal)
    , iChoice(aVal)
{
}

void StoreChoice::Write()
{
    AutoMutex a(iLock);
    if (iUpdatePending) {
        iUpdatePending = false;
        Bws<sizeof(TUint)> buf;
        buf.Append(iChoice->Get());
        iStore.Write(iId, buf);
    }
}


// StoreText

StoreText::StoreText(IStoreReadWrite& aStore, const Brx& aId, TBool aUpdatesDeferred, ConfigText* aVal)
    : StoreVal(aStore, aId, aUpdatesDeferred, aVal)
    , iText(aVal)
{
}

void StoreText::Write()
{
    AutoMutex a(iLock);
    if (iUpdatePending) {
        iUpdatePending = false;
        iStore.Write(iId, iText->Get());
    }
}


// StoreManager

StoreManager::StoreManager(IStoreReadWrite& aStore, ConfigurationManager& aConfigManager)
    : iStore(aStore)
    , iConfigManager(aConfigManager)
    , iUpdateLock("SMUL")
    , iListenersLock("SMLL")
{
}

StoreManager::~StoreManager()
{
    // remove subscribers that were added during CreateX calls
    AutoMutex a(iListenersLock);
    for (ListenerMap::iterator it = iListeners.begin(); it != iListeners.end(); it++) {
        ASSERT(iConfigManager.Has(it->first));
        ConfigVal& cVal = iConfigManager.Get(it->first);
        cVal.Unsubscribe(it->second);
    }
    // StoreManager has ownership of its StoreVals, so delete them
    for (StoreMap::iterator it = iUpdateImmediate.begin(); it != iUpdateImmediate.end(); it++) {
        delete it->second;
    }
    for (StoreMap::iterator it = iUpdateDeferred.begin(); it != iUpdateDeferred.end(); it++) {
        delete it->second;
    }
}

TInt StoreManager::CreateNum(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, TInt aMin, TInt aMax, TInt aDefault)
{
    if (iConfigManager.HasNum(aId)) {
        THROW(AvConfigIdExists);
    }

    Bws<sizeof(TInt)> storeVal;

    // try retrieve from store; create entry if it doesn't exist
    try {
        iStore.Read(aId, storeVal);
    }
    catch (StoreKeyNotFound&) {
        Bwh buf(sizeof(TInt));
        buf.Append(aDefault);
        iStore.Write(aId, buf);
        iStore.Read(aId, storeVal);
    }

    TInt initial = Converter::BeUint32At(storeVal, 0);
    ConfigNum* cVal = new ConfigNum(aMin, aMax, initial);
    TUint listenerId = cVal->Subscribe(aFunc);
    AddListener(aId, listenerId);
    StoreNum* sVal = new StoreNum(iStore, aId, aUpdatesDeferred, cVal);

    iConfigManager.Add(aId, *cVal);
    Add(aId, aUpdatesDeferred, sVal);

    return cVal->Get();
}

TUint StoreManager::CreateChoice(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, std::vector<const Brx*> aOptions, TUint aDefault)
{
    if (iConfigManager.HasChoice(aId)) {
        THROW(AvConfigIdExists);
    }

    Bws<sizeof(TUint)> storeVal;

    // try retrieve from store; create entry if it doesn't exist
    try {
        iStore.Read(aId, storeVal);
    }
    catch (StoreKeyNotFound&) {
        Bwh buf(sizeof(TUint));
        buf.Append(aDefault);
        iStore.Write(aId, buf);
        iStore.Read(aId, storeVal);
    }

    TUint initial = Converter::BeUint32At(storeVal, 0);
    ConfigChoice* cVal = new ConfigChoice();
    for (TUint i=0; i<aOptions.size(); i++)
    {
        cVal->Add(*aOptions[i]);
    }
    cVal->Set(initial);
    TUint listenerId = cVal->Subscribe(aFunc);
    AddListener(aId, listenerId);
    StoreChoice* sVal = new StoreChoice(iStore, aId, aUpdatesDeferred, cVal);

    iConfigManager.Add(aId, *cVal);
    Add(aId, aUpdatesDeferred, sVal);

    return initial;
}

const Brx& StoreManager::CreateText(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, TUint aMaxLength, const Brx& aDefault)
{
    if (iConfigManager.HasText(aId)) {
        THROW(AvConfigIdExists);
    }

    Bwh storeVal(aMaxLength);

    // try retrieve from store; create entry if it doesn't exist
    try {
        iStore.Read(aId, storeVal);
    }
    catch (StoreKeyNotFound&) {
        iStore.Write(aId, aDefault);
        iStore.Read(aId, storeVal);
    }

    ConfigText* cVal = new ConfigText(aMaxLength);
    cVal->Set(storeVal);
    TUint listenerId = cVal->Subscribe(aFunc);
    AddListener(aId, listenerId);
    StoreText* sVal = new StoreText(iStore, aId, aUpdatesDeferred, cVal);

    iConfigManager.Add(aId, *cVal);
    Add(aId, aUpdatesDeferred, sVal);

    return cVal->Get();
}

void StoreManager::AddListener(const Brx& aId, TUint aListenerId)
{
    Brn id(aId);
    AutoMutex a(iListenersLock);
    iListeners.insert(std::pair<Brn, TUint>(id, aListenerId));
}

void StoreManager::Add(const Brx& aId, TBool aUpdatesDeferred, StoreVal* aSVal)
{
    ASSERT(aSVal != NULL);
    Brn id(aId);
    AutoMutex a(iUpdateLock);
    if (aUpdatesDeferred) {
        iUpdateDeferred.insert(std::pair<Brn, StoreVal*>(id, aSVal));
    }
    else {
        iUpdateImmediate.insert(std::pair<Brn, StoreVal*>(id, aSVal));
    }
}

void StoreManager::WritePendingUpdates()
{
    AutoMutex a(iUpdateLock);
    for (StoreMap::iterator it = iUpdateDeferred.begin(); it != iUpdateDeferred.end(); it++) {
        it->second->Write();
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
