#ifndef HEADER_CONFIGMANAGER
#define HEADER_CONFIGMANAGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Av/FunctorBuf.h>
#include <OpenHome/Av/FunctorInt.h>
#include <OpenHome/Av/FunctorUint.h>
#include <OpenHome/Av/IStore.h>

#include <map>
#include <vector>

EXCEPTION(AvConfigInvalidRange);
EXCEPTION(AvConfigValueOutOfRange);
EXCEPTION(AvConfigValueExists);
EXCEPTION(AvConfigIndexOutOfRange);
EXCEPTION(AvConfigValueTooLong);
EXCEPTION(AvConfigIdExists);

namespace OpenHome {
namespace Av {

class IObservable
{
public:
    // subscribers should either
    // - (ideally) define a separate functor for each IObservable subscribed to
    // OR
    // - check all IObservable they hold for which one has changed
    virtual TUint Subscribe(Functor aFunctor) = 0;
    virtual void Unsubscribe(TUint aId) = 0;
};

class ConfigVal : public IObservable
{
protected:
    ConfigVal();
public:
    virtual ~ConfigVal() = 0;
public: // from IObservable
    TUint Subscribe(Functor aFunctor);
    void Unsubscribe(TUint aId);
protected:
    void NotifySubscribers();
private:
    typedef std::map<TUint,Functor> Map;
    Map iObservers;
    Mutex iObserverLock;
    TUint iNextObserverId;
};

/*
 * Class representing a numerical value, which can be positive or negative,
 * with upper and lower limits.
 */
class ConfigNum : public ConfigVal
{
public:
    ConfigNum(TInt aMin, TInt aMax, TInt aVal);
    TInt Min() const;
    TInt Max() const;
    TInt Get() const;
    TBool Set(TInt aVal);
    inline TBool operator==(const ConfigNum& aNum) const;
private:
    TInt iMin;
    TInt iMax;
    TInt iVal;
};

inline TBool ConfigNum::operator==(const ConfigNum& aNum) const
{
    return iMin == aNum.iMin
        && iVal == aNum.iVal
        && iMax == aNum.iMax;
}

/*
 * Class representing a multiple choice value (such as true/false, on/off,
 * monkey/chicken/meerkat, etc.)
 *
 * Empty when created. When first option value is added, defaults to that value
 * as the selected one.
 */
class ConfigChoice : public ConfigVal
{
public:
    ConfigChoice();
    ~ConfigChoice();
    void Add(const Brx& aVal);
    std::vector<const Brx*> Options();
    TUint Get() const;
    TBool Set(TUint aIndex);
    inline TBool operator==(const ConfigChoice& aChoice) const;
private:
    std::vector<Brn> iAllowedValues;
    TUint iSelected;
};

inline TBool ConfigChoice::operator==(const ConfigChoice& aChoice) const
{
    TBool optionsEqual = true;
    for (TUint i=0; i<iAllowedValues.size(); i++) {
        if (iAllowedValues[i] != aChoice.iAllowedValues[i]) {
            optionsEqual = false;
        }
    }
    return optionsEqual && (iSelected == aChoice.iSelected);
}

/*
 * Class representing a text value. Length of text that can be allocated is
 * fixed at construction.
 */
class ConfigText : public ConfigVal
{
public:
    ConfigText(TUint aMaxBytes);
    TUint MaxLength() const;
    const Brx& Get() const;
    TBool Set(const Brx& aText);
    inline TBool operator==(const ConfigText& aText) const;
private:
    Bwh iText;
};

inline TBool ConfigText::operator==(const ConfigText& aText) const
{
    return (iText == aText.iText);
}

/*
 * Interface for a configuration manager.
 */
class IConfigurationManager
{
public:
    virtual void Add(const Brx& aId, ConfigNum& aNum) = 0;
    virtual void Add(const Brx& aId, ConfigChoice& aChoice) = 0;
    virtual void Add(const Brx& aId, ConfigText& aText) = 0;

    virtual TBool HasNum(const Brx& aId) = 0;
    virtual ConfigNum& GetNum(const Brx& aId) = 0;
    virtual TBool HasChoice(const Brx& aId) = 0;
    virtual ConfigChoice& GetChoice(const Brx& aId) = 0;
    virtual TBool HasText(const Brx& aId) = 0;
    virtual ConfigText& GetText(const Brx& aId) = 0;
};

/*
 * Helper class for ConfigurationManager.
 */
template <class T> class SerialisedMap
{
public:
    SerialisedMap();
    void Add(const Brx& aId, T& aVal);
    TBool Has(const Brx& aId);
    T& Get(const Brx& aId);
private:
    typedef std::map<Brn, T*, BufferCmp> Map;
    Map iMap;
    Mutex iLock;
};

// SerialisedMap
template <class T> SerialisedMap<T>::SerialisedMap()
    : iLock("SLML")
{
}

template <class T> void SerialisedMap<T>::Add(const Brx& aId, T& aVal)
{
    Brn id(aId);
    AutoMutex a(iLock);
    typename Map::iterator it = iMap.find(id);
    if (it != iMap.end()) {
        THROW(AvConfigIdExists);
    }
    iMap.insert(std::pair<Brn, T*>(id, &aVal));
}

template <class T> TBool SerialisedMap<T>::Has(const Brx& aId)
{
    TBool found = false;
    Brn id(aId);
    AutoMutex a(iLock);
    typename Map::iterator it = iMap.find(id);
    if (it != iMap.end()) {
        found = true;
    }

    return found;
}

template <class T> T& SerialisedMap<T>::Get(const Brx& aId)
{
    Brn id(aId);
    AutoMutex a(iLock);
    typename Map::iterator it = iMap.find(id);
    ASSERT(it != iMap.end()); // Has() should have been called prior to this

    return *(it->second);
}


/*
 * Class storing a collection of ConfigVals. Values are stored with, and
 * retrievable via, an ID of form "some.value.identifier". Classes that create
 * ConfigVals own them and are responsible for their destruction.
 *
 * Known identifiers are listed elsewhere.
 */
class ConfigurationManager : public IConfigurationManager
{
public:
    virtual ~ConfigurationManager();
public: // from IConfigurationManager
    void Add(const Brx& aId, ConfigNum& aNum);
    void Add(const Brx& aId, ConfigChoice& aChoice);
    void Add(const Brx& aId, ConfigText& aText);

    TBool Has(const Brx& aId);
    ConfigVal& Get(const Brx& aId);

    TBool HasNum(const Brx& aId);
    ConfigNum& GetNum(const Brx& aId);
    TBool HasChoice(const Brx& aId);
    ConfigChoice& GetChoice(const Brx& aId);
    TBool HasText(const Brx& aId);
    ConfigText& GetText(const Brx& aId);
private:
    template <class T> void Add(SerialisedMap<T>& aMap, const Brx& aId, T& aVal);
private:
    SerialisedMap<ConfigNum> iMapNum;
    SerialisedMap<ConfigChoice> iMapChoice;
    SerialisedMap<ConfigText> iMapText;
};

/*
 * Interface for value types able to have deferred updates and that know how to
 * write their value out to a store.
 */
class IStoreVal
{
public:
    virtual TBool UpdatePending() = 0;
    virtual void Write() = 0;
};

/*
 * Wrapper class for ConfigVals that hold a reference to a read/write store and
 * should know how to write their value out to the store. Writes can be
 * immediate (i.e., upon update) or deferred (i.e., at power down).
 * StoreVals own their ConfigVals and are responsible for their destruction.
 */
class StoreVal : public IStoreVal
{
protected:
    StoreVal(IStoreReadWrite& aStore, const Brx& aId, TBool aUpdatesDeferred, ConfigVal* aVal);
public:
    ~StoreVal();
public: // from IStoreVal
    TBool UpdatePending();
    void Write() = 0;
private:
    void NotifyChanged();
protected:
    IStoreReadWrite& iStore;
    const Brx& iId;
    Mutex iLock;
    TBool iUpdatePending;
private:
    ConfigVal* iVal;
    TUint iListenerId;
    const TBool iUpdatesDeferred;
};

class StoreNum : public StoreVal
{
public:
    StoreNum(IStoreReadWrite& aStore, const Brx& aId, TBool aUpdatesDeferred, ConfigNum* aVal);
public: // from StoreVal
    void Write();
private:
    ConfigNum* iNum;
};

class StoreChoice : public StoreVal
{
public:
    StoreChoice(IStoreReadWrite& aStore, const Brx& aId, TBool aUpdatesDeferred, ConfigChoice* aVal);
public: // from StoreVal
    void Write();
private:
    ConfigChoice* iChoice;
};

class StoreText : public StoreVal
{
public:
    StoreText(IStoreReadWrite& aStore, const Brx& aId, TBool aUpdatesDeferred, ConfigText* aVal);
public: // from StoreVal
    void Write();
private:
    ConfigText* iText;
};

/*
 * Class handling access to read/write store on behalf of any modules creating
 * config vals.
 */
class StoreManager
{
public:
    StoreManager(IStoreReadWrite& aStore, ConfigurationManager& aConfigManager);
    ~StoreManager();
    TInt CreateNum(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, TInt aMin, TInt aMax, TInt aDefault);
    TUint CreateChoice(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, std::vector<const Brx*> aOptions, TUint aDefault);
    const Brx& CreateText(const Brx& aId, TBool aUpdatesDeferred, Functor aFunc, TUint aMaxLength, const Brx& aDefault);
    void WritePendingUpdates();
private:
    void AddListener(const Brx& aId, TUint aListenerId);
    void Add(const Brx& aId, TBool aUpdatesDeferred, StoreVal* aSVal);
private:
    IStoreReadWrite& iStore;
    ConfigurationManager& iConfigManager;
    Mutex iUpdateLock;
    Mutex iListenersLock;
    typedef std::map<Brn, StoreVal*, BufferCmp> StoreMap;
    typedef std::map<Brn, TUint, BufferCmp> ListenerMap;
    StoreMap iUpdateImmediate;
    StoreMap iUpdateDeferred;
    ListenerMap iListeners;
};

/*
 * Class providing a basic implementation of a read/write store for storing
 * configuration in memory (no file writing, so no persistence between runs).
 */
class ConfigRamStore : public IStoreReadWrite
{
public:
    ConfigRamStore();
    ~ConfigRamStore();
public: // from IStoreReadWrite
    void Read(const Brx& aKey, Bwx& aDest);
    void Write(const Brx& aKey, const Brx& aSource);
    void Delete(const Brx& aKey);
private:
    void Clear();
private:
    typedef std::map<Brn, Brh*, BufferCmp> Map;
    Map iMap;
    Mutex iLock;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CONFIGMANAGER
