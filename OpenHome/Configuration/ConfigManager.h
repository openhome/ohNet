#ifndef HEADER_CONFIGMANAGER
#define HEADER_CONFIGMANAGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Configuration/FunctorGeneric.h>
#include <OpenHome/Configuration/IStore.h>

#include <map>
#include <vector>

EXCEPTION(ConfigValueOutOfRange);
EXCEPTION(ConfigValueExists);
EXCEPTION(ConfigIndexOutOfRange);
EXCEPTION(ConfigValueTooLong);
EXCEPTION(ConfigIdExists);

namespace OpenHome {
namespace Configuration {

template <class T>
class IObservable
{
public:
    virtual TUint Subscribe(FunctorGeneric<T> aFunctor) = 0;
    virtual void Unsubscribe(TUint aId) = 0;
    virtual ~IObservable() {}
};

class IConfigurationManager;

template <class T>
class ConfigVal : public IObservable<T>
{
protected:
    ConfigVal(IConfigurationManager& aManager, const Brx& aId);
public:
    virtual ~ConfigVal();
    void AddInitialSubscribers(FunctorGeneric<T> aOwnerFunc);
    const Brx& Id();
public: // from IObservable
    TUint Subscribe(FunctorGeneric<T> aFunctor) = 0;
    void Unsubscribe(TUint aId);
protected:
    TUint Subscribe(FunctorGeneric<T> aFunctor, T aVal);
    void NotifySubscribers(T aVal);
    virtual void Write(T aVal) = 0;
protected:
    IConfigurationManager& iConfigManager;
    const Brx& iId;
private:
    typedef std::map<TUint,FunctorGeneric<T>> Map;
    Map iObservers;
    Mutex iObserverLock;
    TUint iOwnerObserverId;
    TUint iWriteObserverId; // ID for own Write() observer
    TUint iNextObserverId;  // 0 is symbolic: invalid value
};

// ConfigVal
template <class T> ConfigVal<T>::ConfigVal(IConfigurationManager& aManager, const Brx& aId)
    : iConfigManager(aManager)
    , iId(aId)
    , iObserverLock("CVOL")
    , iOwnerObserverId(0)
    , iWriteObserverId(0)
    , iNextObserverId(1)
{
}

template <class T> void ConfigVal<T>::AddInitialSubscribers(FunctorGeneric<T> aOwnerFunc)
{
    ASSERT(iOwnerObserverId == 0);
    ASSERT(iWriteObserverId == 0);
    iOwnerObserverId = Subscribe(aOwnerFunc);
    iWriteObserverId = Subscribe(MakeFunctorGeneric<T>(*this, &ConfigVal::Write));
}

template <class T> ConfigVal<T>::~ConfigVal()
{
    Unsubscribe(iWriteObserverId);
    Unsubscribe(iOwnerObserverId);
    ASSERT(iObservers.size() == 0);
}

template <class T> const Brx& ConfigVal<T>::Id()
{
    return iId;
}

template <class T> void ConfigVal<T>::Unsubscribe(TUint aId)
{
    iObserverLock.Wait();
    Map::iterator it = iObservers.find(aId);
    if (it != iObservers.end()) {
        iObservers.erase(it);
    }
    iObserverLock.Signal();
}

template <class T> TUint ConfigVal<T>::Subscribe(FunctorGeneric<T> aFunctor, T aVal)
{
    iObserverLock.Wait();
    TUint id = iNextObserverId;
    iObservers.insert(std::pair<TUint,FunctorGeneric<T>>(id, aFunctor));
    iNextObserverId++;
    iObserverLock.Signal();
    aFunctor(aVal);
    return id;
}

template <class T> void ConfigVal<T>::NotifySubscribers(T aVal)
{
    ASSERT(iOwnerObserverId != 0);
    ASSERT(iWriteObserverId != 0);
    AutoMutex a(iObserverLock);
    for (Map::iterator it = iObservers.begin(); it != iObservers.end(); it++) {
        it->second(aVal);
    }
}


/*
 * Class representing a numerical value, which can be positive or negative,
 * with upper and lower limits.
 */
class ConfigNum : public ConfigVal<TInt>
{
public:
    ConfigNum(IConfigurationManager& aManager, const Brx& aId, FunctorGeneric<TInt> aFunc, TInt aMin, TInt aMax, TInt aDefault);
    TInt Min() const;
    TInt Max() const;
    TBool Set(TInt aVal);
    inline TBool operator==(const ConfigNum& aNum) const;
private:
    TBool IsValid(TInt aVal);
public: // from ConfigVal
    TUint Subscribe(FunctorGeneric<TInt> aFunctor);
private: // from ConfigVal
    void Write(TInt aVal);
private:
    TInt iMin;
    TInt iMax;
    TInt iVal;
    Mutex iMutex;
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
class ConfigChoice : public ConfigVal<TUint>
{
public:
    ConfigChoice(IConfigurationManager& aManager, const Brx& aId, FunctorGeneric<TUint> aFunc, std::vector<const Brx*> aOptions, TUint aDefault);
    std::vector<const Brx*> Options();
    TBool Set(TUint aIndex);
    inline TBool operator==(const ConfigChoice& aChoice) const;
private:
    void Add(const Brx& aVal);
    TBool IsValid(TUint aVal);
public: // from ConfigVal
    TUint Subscribe(FunctorGeneric<TUint> aFunctor);
private: // from ConfigVal
    void Write(TUint aVal);
private:
    std::vector<Brn> iAllowedValues;
    TUint iSelected;
    Mutex iMutex;
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
class ConfigText : public ConfigVal<const Brx&>
{
public:
    ConfigText(IConfigurationManager& aManager, const Brx& aId, FunctorGeneric<const Brx&> aFunc, TUint aMaxLength, const Brx& aDefault);
    TUint MaxLength() const;
    TBool Set(const Brx& aText);
    inline TBool operator==(const ConfigText& aText) const;
private:
    TBool IsValid(const Brx& aVal);
public: // from ConfigVal
    TUint Subscribe(FunctorGeneric<const Brx&> aFunctor);
private: // from ConfigVal
    void Write(const Brx&);
private:
    Bwh iText;
    mutable Mutex iMutex;
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
    virtual void Close() = 0;

    virtual void Add(ConfigNum& aNum) = 0;
    virtual void Add(ConfigChoice& aChoice) = 0;
    virtual void Add(ConfigText& aText) = 0;

    virtual void Read(const Brx& aKey, Bwx& aDest, const Brx& aDefault) = 0;
    virtual void Write(const Brx& aKey, const Brx& aValue) = 0;

    virtual TBool HasNum(const Brx& aId) const = 0;
    virtual ConfigNum& GetNum(const Brx& aId) const = 0;
    virtual TBool HasChoice(const Brx& aId) const = 0;
    virtual ConfigChoice& GetChoice(const Brx& aId) const = 0;
    virtual TBool HasText(const Brx& aId) const = 0;
    virtual ConfigText& GetText(const Brx& aId) const = 0;

    virtual ~IConfigurationManager() {}
};

/*
 * Helper class for ConfigurationManager.
 */
template <class T>
class SerialisedMap
{
public:
    SerialisedMap();
    void Add(const Brx& aId, T& aVal);
    TBool Has(const Brx& aId) const;
    T& Get(const Brx& aId) const;
private:
    typedef std::map<Brn, T*, BufferCmp> Map;
    Map iMap;
    mutable Mutex iLock;
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
        THROW(ConfigIdExists);
    }
    iMap.insert(std::pair<Brn, T*>(id, &aVal));
}

template <class T> TBool SerialisedMap<T>::Has(const Brx& aId) const
{
    TBool found = false;
    Brn id(aId);
    AutoMutex a(iLock);
    typename Map::const_iterator it = iMap.find(id);
    if (it != iMap.end()) {
        found = true;
    }

    return found;
}

template <class T> T& SerialisedMap<T>::Get(const Brx& aId) const
{
    Brn id(aId);
    AutoMutex a(iLock);
    typename Map::const_iterator it = iMap.find(id);
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
    ConfigurationManager(IStoreReadWrite& aStore);
    virtual ~ConfigurationManager();
public: // from IConfigurationManager
    void Close();

    void Add(ConfigNum& aNum);
    void Add(ConfigChoice& aChoice);
    void Add(ConfigText& aText);

    void Read(const Brx& aKey, Bwx& aDest, const Brx& aDefault);
    void Write(const Brx& aKey, const Brx& aValue);

    TBool Has(const Brx& aId) const; // FIXME - is this required?

    TBool HasNum(const Brx& aId) const;
    ConfigNum& GetNum(const Brx& aId) const;
    TBool HasChoice(const Brx& aId) const;
    ConfigChoice& GetChoice(const Brx& aId) const;
    TBool HasText(const Brx& aId) const;
    ConfigText& GetText(const Brx& aId) const;
private:
    template <class T> void Add(SerialisedMap<T>& aMap, const Brx& aId, T& aVal);
private:
    IStoreReadWrite& iStore;
    SerialisedMap<ConfigNum> iMapNum;
    SerialisedMap<ConfigChoice> iMapChoice;
    SerialisedMap<ConfigText> iMapText;
    TBool iClosed;
};

/*
 * Class providing a basic implementation of a read/write store for storing
 * configuration in memory (no file writing, so no persistence between runs).
 */
class ConfigRamStore : public IStoreReadWrite
{
public:
    ConfigRamStore();
    virtual ~ConfigRamStore();
    void Print();
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

} // namespace Configuration
} // namespace OpenHome

#endif // HEADER_CONFIGMANAGER
