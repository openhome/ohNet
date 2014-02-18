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

EXCEPTION(ConfigInvalidValue);
EXCEPTION(ConfigValueOutOfRange);
EXCEPTION(ConfigValueExists);
EXCEPTION(ConfigInvalidChoice);
EXCEPTION(ConfigValueTooLong);
EXCEPTION(ConfigIdExists);

namespace OpenHome {
    class IWriter;
namespace Configuration {

template <class T>
class KeyValuePair : public INonCopyable
{
public:
    // Does not make a copy; owner is responsible for persisting parameter values.
    KeyValuePair(const Brx& aKey, T aValue);
    const Brx& Key() const;
    T Value() const;
private:
    const Brx& iKey;
    T iValue;
};

// KeyValuePair
template <class T> KeyValuePair<T>::KeyValuePair(const Brx& aKey, T aValue)
    : iKey(aKey)
    , iValue(aValue)
{
}

template <class T> const Brx& KeyValuePair<T>::Key() const
{
    return iKey;
}

template <class T> T KeyValuePair<T>::Value() const
{
    return iValue;
}


template <class T>
class IObservable
{
public:
    virtual TUint Subscribe(FunctorGeneric<KeyValuePair<T>&> aFunctor) = 0;
    virtual void Unsubscribe(TUint aId) = 0;
    virtual ~IObservable() {}
};

class IConfigManagerWriter;

template <class T>
class ConfigVal : public IObservable<T>
{
public:
    static const TUint kSubscriptionIdInvalid = 0;
protected:
    ConfigVal(IConfigManagerWriter& aManager, const Brx& aId);
public:
    virtual ~ConfigVal();
    const Brx& Id();
    virtual void Serialise(IWriter& aWriter) const = 0;
    virtual TBool Deserialise(const Brx& aString) = 0;
public: // from IObservable
    virtual TUint Subscribe(FunctorGeneric<KeyValuePair<T>&> aFunctor) = 0;
    void Unsubscribe(TUint aId);
protected:
    TUint Subscribe(FunctorGeneric<KeyValuePair<T>&> aFunctor, T aVal);
    void NotifySubscribers(T aVal);
    void AddInitialSubscribers();
    virtual void Write(KeyValuePair<T>& aKvp) = 0;
protected:
    IConfigManagerWriter& iConfigManager;
    Bwh iId;
private:
    typedef std::map<TUint,FunctorGeneric<KeyValuePair<T>&>> Map;
    Map iObservers;
    Mutex iObserverLock;
    TUint iWriteObserverId; // ID for own Write() observer
    TUint iNextObserverId;  // 0 is symbolic: invalid value
};

// ConfigVal
template <class T> ConfigVal<T>::ConfigVal(IConfigManagerWriter& aManager, const Brx& aId)
    : iConfigManager(aManager)
    , iId(aId)
    , iObserverLock("CVOL")
    , iWriteObserverId(0)
    , iNextObserverId(1)
{
}

template <class T> void ConfigVal<T>::AddInitialSubscribers()
{
    ASSERT(iWriteObserverId == 0);
    iWriteObserverId = Subscribe(MakeFunctorGeneric<KeyValuePair<T>&>(*this, &ConfigVal::Write));
}

template <class T> ConfigVal<T>::~ConfigVal()
{
    Unsubscribe(iWriteObserverId);
    ASSERT(iObservers.size() == 0);
}

template <class T> const Brx& ConfigVal<T>::Id()
{
    return iId;
}

template <class T> void ConfigVal<T>::Unsubscribe(TUint aId)
{
    iObserverLock.Wait();
    typename Map::iterator it = iObservers.find(aId);
    if (it != iObservers.end()) {
        iObservers.erase(it);
    }
    iObserverLock.Signal();
}

template <class T> TUint ConfigVal<T>::Subscribe(FunctorGeneric<KeyValuePair<T>&> aFunctor, T aVal)
{
    KeyValuePair<T> kvp(iId, aVal);
    iObserverLock.Wait();
    TUint id = iNextObserverId;
    iObservers.insert(std::pair<TUint,FunctorGeneric<KeyValuePair<T>&>>(id, aFunctor));
    iNextObserverId++;
    iObserverLock.Signal();
    aFunctor(kvp);
    return id;
}

template <class T> void ConfigVal<T>::NotifySubscribers(T aVal)
{
    ASSERT(iWriteObserverId != 0);
    KeyValuePair<T> kvp(iId, aVal);
    AutoMutex a(iObserverLock);
    typename Map::iterator it;
    for (it = iObservers.begin(); it != iObservers.end(); it++) {
        it->second(kvp);
    }
}


/*
 * Class representing a numerical value, which can be positive or negative,
 * with upper and lower limits.
 */
class ConfigNum : public ConfigVal<TInt>
{
    friend class SuiteConfigManager;
public:
    ConfigNum(IConfigManagerWriter& aManager, const Brx& aId, TInt aMin, TInt aMax, TInt aDefault);
    TInt Min() const;
    TInt Max() const;
    TBool Set(TInt aVal);
private:
    TBool IsValid(TInt aVal) const;
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    TBool Deserialise(const Brx& aString);
public: // from ConfigVal
    TUint Subscribe(FunctorGeneric<KeyValuePair<TInt>&> aFunctor);
private: // from ConfigVal
    void Write(KeyValuePair<TInt>& aKvp);
private:
    inline TBool operator==(const ConfigNum& aNum) const;
private:
    TInt iMin;
    TInt iMax;
    TInt iVal;
    mutable Mutex iMutex;
};

inline TBool ConfigNum::operator==(const ConfigNum& aNum) const
{
    AutoMutex a(iMutex);
    return iMin == aNum.iMin
        && iVal == aNum.iVal
        && iMax == aNum.iMax;
}

/*
 * Class representing a multiple choice value (such as true/false, on/off,
 * monkey/chicken/meerkat, etc.)
 *
 * Empty when created. When first choice value is added, defaults to that value
 * as the selected one.
 */
class ConfigChoice : public ConfigVal<TUint>
{
    friend class SuiteConfigManager;
public:
    ConfigChoice(IConfigManagerWriter& aManager, const Brx& aId, const std::vector<TUint>& aChoices, TUint aDefault);
    const std::vector<TUint>& Choices() const;
    TBool Set(TUint aVal);
private:
    TBool IsValid(TUint aVal) const;
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    TBool Deserialise(const Brx& aString);
public: // from ConfigVal
    TUint Subscribe(FunctorGeneric<KeyValuePair<TUint>&> aFunctor);
private: // from ConfigVal
    void Write(KeyValuePair<TUint>& aKvp);
private:
    inline TBool operator==(const ConfigChoice& aChoice) const;
private:
    std::vector<TUint> iChoices;
    TUint iSelected;
    mutable Mutex iMutex;
};

inline TBool ConfigChoice::operator==(const ConfigChoice& aChoice) const
{
    TBool choicesEqual = true;
    for (TUint i=0; i<iChoices.size(); i++) {
        if (iChoices[i] != aChoice.iChoices[i]) {
            choicesEqual = false;
        }
    }
    AutoMutex a(iMutex);
    return choicesEqual && (iSelected == aChoice.iSelected);
}

/*
 * Class representing a text value. Length of text that can be allocated is
 * fixed at construction.
 */
class ConfigText : public ConfigVal<const Brx&>
{
    friend class SuiteConfigManager;
public:
    ConfigText(IConfigManagerWriter& aManager, const Brx& aId, TUint aMaxLength, const Brx& aDefault);
    TUint MaxLength() const;
    TBool Set(const Brx& aText);
private:
    TBool IsValid(const Brx& aVal) const;
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    TBool Deserialise(const Brx& aString);
public: // from ConfigVal
    TUint Subscribe(FunctorGeneric<KeyValuePair<const Brx&>&> aFunctor);
private: // from ConfigVal
    void Write(KeyValuePair<const Brx&>& aKvp);
private:
    inline TBool operator==(const ConfigText& aText) const;
private:
    Bwh iText;
    mutable Mutex iMutex;
};

inline TBool ConfigText::operator==(const ConfigText& aText) const
{
    AutoMutex a(iMutex);
    return (iText == aText.iText);
}

/*
 * Interface for reading config vals from a configuration manager.
 */
class IConfigManagerReader
{
public:
    virtual TBool HasNum(const Brx& aId) const = 0;
    virtual ConfigNum& GetNum(const Brx& aId) const = 0;
    virtual TBool HasChoice(const Brx& aId) const = 0;
    virtual ConfigChoice& GetChoice(const Brx& aId) const = 0;
    virtual TBool HasText(const Brx& aId) const = 0;
    virtual ConfigText& GetText(const Brx& aId) const = 0;
    virtual ~IConfigManagerReader() {}
};

/*
 * Interface for adding values to a configuration manager.
 * Should only ever be used by ConfigVal items and a class that decides when
 * all values have been added to the config manager.
 */
class IConfigManagerWriter
{
public:
    virtual void Close() = 0;
    virtual void Add(ConfigNum& aNum) = 0;
    virtual void Add(ConfigChoice& aChoice) = 0;
    virtual void Add(ConfigText& aText) = 0;
    virtual void FromStore(const Brx& aKey, Bwx& aDest, const Brx& aDefault) = 0;
    virtual void ToStore(const Brx& aKey, const Brx& aValue) = 0;
    virtual ~IConfigManagerWriter() {}
};

/*
 * Helper class for ConfigManager.
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
    ASSERT(it != iMap.end()); // assert value with ID of aId exists

    return *(it->second);
}

/*
 * Class storing a collection of ConfigVals. Values are stored with, and
 * retrievable via, an ID of form "some.value.identifier". Classes that create
 * ConfigVals own them and are responsible for their destruction.
 *
 * Known identifiers are listed elsewhere.
 */
class ConfigManager : public IConfigManagerReader, public IConfigManagerWriter
{
public:
    ConfigManager(IStoreReadWrite& aStore);
    virtual ~ConfigManager();
public: // from IConfigManagerReader
    TBool HasNum(const Brx& aId) const;
    ConfigNum& GetNum(const Brx& aId) const;
    TBool HasChoice(const Brx& aId) const;
    ConfigChoice& GetChoice(const Brx& aId) const;
    TBool HasText(const Brx& aId) const;
    ConfigText& GetText(const Brx& aId) const;
public: // from IConfigManagerWriter
    void Close();
    void Add(ConfigNum& aNum);
    void Add(ConfigChoice& aChoice);
    void Add(ConfigText& aText);
    void FromStore(const Brx& aKey, Bwx& aDest, const Brx& aDefault);
    void ToStore(const Brx& aKey, const Brx& aValue);
private:
    TBool Has(const Brx& aId) const;
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
