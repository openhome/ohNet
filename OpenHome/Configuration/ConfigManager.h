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
EXCEPTION(ConfigKeyExists);

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
    typedef FunctorGeneric<KeyValuePair<T>&> FunctorObserver;
public:
    virtual TUint Subscribe(FunctorObserver aFunctor) = 0;
    virtual void Unsubscribe(TUint aId) = 0;
    virtual ~IObservable() {}
};

/*
 * Helper function for creating a FunctorObserver.
 */
template<class Type, class Object, class CallType>
inline MemberTranslatorGeneric<KeyValuePair<Type>&,Object,void (CallType::*)(KeyValuePair<Type>&)>
    MakeFunctorObserver(Object& aC, void(CallType::* const &aF)(KeyValuePair<Type>&))
{
    typedef void(CallType::*MemFunc)(KeyValuePair<Type>&);
    return MemberTranslatorGeneric<KeyValuePair<Type>&,Object,MemFunc>(aC,aF);
}

class IConfigManagerWriter;

class ISerialisable
{
public:
    virtual void Serialise(IWriter& aWriter) const = 0;
    virtual TBool Deserialise(const Brx& aString) = 0;
    virtual ~ISerialisable() {}
};

template <class T>
class ConfigVal : public IObservable<T>, public ISerialisable
{
public:
    static const TUint kSubscriptionIdInvalid = 0;
protected:
    ConfigVal(IConfigManagerWriter& aManager, const Brx& aKey);
public:
    virtual ~ConfigVal();
    const Brx& Key();
public: // from IObservable
    virtual TUint Subscribe(FunctorObserver aFunctor) = 0;
    void Unsubscribe(TUint aId);
public: // from ISerialisable
    virtual void Serialise(IWriter& aWriter) const = 0;
    virtual TBool Deserialise(const Brx& aString) = 0;
protected:
    TUint Subscribe(FunctorObserver aFunctor, T aVal);
    void NotifySubscribers(T aVal);
    void AddInitialSubscribers();
    virtual void Write(KeyValuePair<T>& aKvp) = 0;
protected:
    IConfigManagerWriter& iConfigManager;
    Bwh iKey;
private:
    typedef std::map<TUint,FunctorObserver> Map;
    Map iObservers;
    Mutex iObserverLock;
    TUint iWriteObserverId; // ID for own Write() observer
    TUint iNextObserverId;
};

// ConfigVal
template <class T> ConfigVal<T>::ConfigVal(IConfigManagerWriter& aManager, const Brx& aKey)
    : iConfigManager(aManager)
    , iKey(aKey)
    , iObserverLock("CVOL")
    , iWriteObserverId(0)
    , iNextObserverId(1)
{
}

template <class T> void ConfigVal<T>::AddInitialSubscribers()
{
    ASSERT(iWriteObserverId == 0);
    iWriteObserverId = Subscribe(MakeFunctorObserver<T>(*this, &ConfigVal::Write));
}

template <class T> ConfigVal<T>::~ConfigVal()
{
    Unsubscribe(iWriteObserverId);
    ASSERT(iObservers.size() == 0);
}

template <class T> const Brx& ConfigVal<T>::Key()
{
    return iKey;
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

template <class T> TUint ConfigVal<T>::Subscribe(FunctorObserver aFunctor, T aVal)
{
    KeyValuePair<T> kvp(iKey, aVal);
    iObserverLock.Wait();
    TUint id = iNextObserverId;
    iObservers.insert(std::pair<TUint,FunctorObserver>(id, aFunctor));
    iNextObserverId++;
    iObserverLock.Signal();
    aFunctor(kvp);
    return id;
}

template <class T> void ConfigVal<T>::NotifySubscribers(T aVal)
{
    ASSERT(iWriteObserverId != 0);
    KeyValuePair<T> kvp(iKey, aVal);
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
    typedef FunctorGeneric<KeyValuePair<TInt>&> FunctorConfigNum;
public:
    ConfigNum(IConfigManagerWriter& aManager, const Brx& aKey, TInt aMin, TInt aMax, TInt aDefault);
    TInt Min() const;
    TInt Max() const;
    TBool Set(TInt aVal);
private:
    TBool IsValid(TInt aVal) const;
public: // from ConfigVal
    TUint Subscribe(FunctorConfigNum aFunctor);
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    TBool Deserialise(const Brx& aString);
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
 * Helper function for creating a FunctorConfigNum.
 */
template<class Object, class CallType>
inline MemberTranslatorGeneric<KeyValuePair<TInt>&,Object,void (CallType::*)(KeyValuePair<TInt>&)>
    MakeFunctorConfigNum(Object& aC, void(CallType::* const &aF)(KeyValuePair<TInt>&))
{
    typedef void(CallType::*MemFunc)(KeyValuePair<TInt>&);
    return MemberTranslatorGeneric<KeyValuePair<TInt>&,Object,MemFunc>(aC,aF);
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
    typedef FunctorGeneric<KeyValuePair<TUint>&> FunctorConfigChoice;
public:
    ConfigChoice(IConfigManagerWriter& aManager, const Brx& aKey, const std::vector<TUint>& aChoices, TUint aDefault);
    const std::vector<TUint>& Choices() const;
    TBool Set(TUint aVal);
private:
    TBool IsValid(TUint aVal) const;
public: // from ConfigVal
    TUint Subscribe(FunctorConfigChoice aFunctor);
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    TBool Deserialise(const Brx& aString);
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
 * Helper function for creating a FunctorConfigChoice.
 */
template<class Object, class CallType>
inline MemberTranslatorGeneric<KeyValuePair<TUint>&,Object,void (CallType::*)(KeyValuePair<TUint>&)>
    MakeFunctorConfigChoice(Object& aC, void(CallType::* const &aF)(KeyValuePair<TUint>&))
{
    typedef void(CallType::*MemFunc)(KeyValuePair<TUint>&);
    return MemberTranslatorGeneric<KeyValuePair<TUint>&,Object,MemFunc>(aC,aF);
}

/*
 * Class representing a text value. Length of text that can be allocated is
 * fixed at construction.
 */
class ConfigText : public ConfigVal<const Brx&>
{
    friend class SuiteConfigManager;
public:
    typedef FunctorGeneric<KeyValuePair<const Brx&>&> FunctorConfigText;
public:
    ConfigText(IConfigManagerWriter& aManager, const Brx& aKey, TUint aMaxLength, const Brx& aDefault);
    TUint MaxLength() const;
    TBool Set(const Brx& aText);
private:
    TBool IsValid(const Brx& aVal) const;
public: // from ConfigVal
    TUint Subscribe(FunctorConfigText aFunctor);
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    TBool Deserialise(const Brx& aString);
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
 * Helper function for creating a FunctorConfigText.
 */
template<class Object, class CallType>
inline MemberTranslatorGeneric<KeyValuePair<const Brx&>&,Object,void (CallType::*)(KeyValuePair<const Brx&>&)>
    MakeFunctorConfigText(Object& aC, void(CallType::* const &aF)(KeyValuePair<const Brx&>&))
{
    typedef void(CallType::*MemFunc)(KeyValuePair<const Brx&>&);
    return MemberTranslatorGeneric<KeyValuePair<const Brx&>&,Object,MemFunc>(aC,aF);
}

/*
 * Interface for reading config vals from a configuration manager.
 */
class IConfigManagerReader
{
public:
    virtual TBool HasNum(const Brx& aKey) const = 0;
    virtual ConfigNum& GetNum(const Brx& aKey) const = 0;
    virtual TBool HasChoice(const Brx& aKey) const = 0;
    virtual ConfigChoice& GetChoice(const Brx& aKey) const = 0;
    virtual TBool HasText(const Brx& aKey) const = 0;
    virtual ConfigText& GetText(const Brx& aKey) const = 0;
    virtual TBool Has(const Brx& aKey) const = 0;
    virtual ISerialisable& Get(const Brx& aKey) const = 0;
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
    void Add(const Brx& aKey, T& aVal);
    TBool Has(const Brx& aKey) const;
    T& Get(const Brx& aKey) const;
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

template <class T> void SerialisedMap<T>::Add(const Brx& aKey, T& aVal)
{
    Brn key(aKey);
    AutoMutex a(iLock);
    typename Map::iterator it = iMap.find(key);
    if (it != iMap.end()) {
        THROW(ConfigKeyExists);
    }
    iMap.insert(std::pair<Brn, T*>(key, &aVal));
}

template <class T> TBool SerialisedMap<T>::Has(const Brx& aKey) const
{
    TBool found = false;
    Brn key(aKey);
    AutoMutex a(iLock);
    typename Map::const_iterator it = iMap.find(key);
    if (it != iMap.end()) {
        found = true;
    }

    return found;
}

template <class T> T& SerialisedMap<T>::Get(const Brx& aKey) const
{
    Brn key(aKey);
    AutoMutex a(iLock);
    typename Map::const_iterator it = iMap.find(key);
    ASSERT(it != iMap.end()); // assert value with ID of aKey exists

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
    TBool HasNum(const Brx& aKey) const;
    ConfigNum& GetNum(const Brx& aKey) const;
    TBool HasChoice(const Brx& aKey) const;
    ConfigChoice& GetChoice(const Brx& aKey) const;
    TBool HasText(const Brx& aKey) const;
    ConfigText& GetText(const Brx& aKey) const;
    TBool Has(const Brx& aKey) const;
    ISerialisable& Get(const Brx& aKey) const;
public: // from IConfigManagerWriter
    void Close();
    void Add(ConfigNum& aNum);
    void Add(ConfigChoice& aChoice);
    void Add(ConfigText& aText);
    void FromStore(const Brx& aKey, Bwx& aDest, const Brx& aDefault);
    void ToStore(const Brx& aKey, const Brx& aValue);
private:
    template <class T> void Add(SerialisedMap<T>& aMap, const Brx& aKey, T& aVal);
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
