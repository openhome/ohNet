#ifndef HEADER_CONFIGMANAGER
#define HEADER_CONFIGMANAGER

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Configuration/BufferPtrCmp.h>
#include <OpenHome/Configuration/IStore.h>

#include <map>
#include <vector>

EXCEPTION(ConfigKeyExists);
EXCEPTION(ConfigNotANumber);
EXCEPTION(ConfigValueOutOfRange);
EXCEPTION(ConfigInvalidSelection);
EXCEPTION(ConfigValueTooLong);

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

class IConfigManagerInitialiser;

class ISerialisable
{
public:
    virtual void Serialise(IWriter& aWriter) const = 0;
    virtual void Deserialise(const Brx& aString) = 0;
    virtual ~ISerialisable() {}
};

template <class T>
class ConfigVal : public IObservable<T>, public ISerialisable
{
    using typename IObservable<T>::FunctorObserver;
public:
    static const TUint kSubscriptionIdInvalid = 0; // FIXME - move to ConfigManager
protected:
    ConfigVal(IConfigManagerInitialiser& aManager, const Brx& aKey);
public:
    virtual ~ConfigVal();
    const Brx& Key() const;
public: // from IObservable
    virtual TUint Subscribe(FunctorObserver aFunctor) = 0;
    void Unsubscribe(TUint aId);
public: // from ISerialisable
    virtual void Serialise(IWriter& aWriter) const = 0;
    virtual void Deserialise(const Brx& aString) = 0;
protected:
    TUint Subscribe(FunctorObserver aFunctor, T aVal);
    void NotifySubscribers(T aVal);
    void AddInitialSubscribers();
    virtual void Write(KeyValuePair<T>& aKvp) = 0;
private:
    TUint SubscribeNoCallback(FunctorObserver aFunctor);
protected:
    IConfigManagerInitialiser& iConfigManager;
    Bwh iKey;
private:
    typedef std::map<TUint,FunctorObserver> Map;
    Map iObservers;
    Mutex iObserverLock;
    TUint iWriteObserverId; // ID for own Write() observer
    TUint iNextObserverId;
};

// ConfigVal
template <class T> ConfigVal<T>::ConfigVal(IConfigManagerInitialiser& aManager, const Brx& aKey)
    : iConfigManager(aManager)
    , iKey(aKey)
    , iObserverLock("CVOL")
    , iWriteObserverId(0)
    , iNextObserverId(1)
{
}

template <class T> ConfigVal<T>::~ConfigVal()
{
    Unsubscribe(iWriteObserverId);
    ASSERT(iObservers.size() == 0);
}

template <class T> const Brx& ConfigVal<T>::Key() const
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

template <class T> TUint ConfigVal<T>::SubscribeNoCallback(FunctorObserver aFunctor)
{
    iObserverLock.Wait();
    TUint id = iNextObserverId;
    iObservers.insert(std::pair<TUint,FunctorObserver>(id, aFunctor));
    iNextObserverId++;
    iObserverLock.Signal();
    return id;
}

template <class T> TUint ConfigVal<T>::Subscribe(FunctorObserver aFunctor, T aVal)
{
    KeyValuePair<T> kvp(iKey, aVal);
    TUint id = SubscribeNoCallback(aFunctor);
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

template <class T> void ConfigVal<T>::AddInitialSubscribers()
{
    // Don't write initial val out at startup.
    // - If it already exists in store, no need to write it out.
    // - If it doesn't exist in store, it will be the default val regardless of
    //   whether it is ever written to store - only write to store on
    //   subsequent changes.
    ASSERT(iWriteObserverId == 0);
    iWriteObserverId = SubscribeNoCallback(MakeFunctorObserver<T>(*this, &ConfigVal::Write));
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
    typedef KeyValuePair<TInt> KvpNum;
public:
    ConfigNum(IConfigManagerInitialiser& aManager, const Brx& aKey, TInt aMin, TInt aMax, TInt aDefault);
    TInt Min() const;
    TInt Max() const;
    void Set(TInt aVal);    // THROWS ConfigValueOutOfRange
private:
    TBool IsValid(TInt aVal) const;
public: // from ConfigVal
    TUint Subscribe(FunctorConfigNum aFunctor);
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    void Deserialise(const Brx& aString);   // THROWS ConfigNotANumber, ConfigValueOutOfRange
private: // from ConfigVal
    void Write(KvpNum& aKvp);
private:
    inline TBool operator==(const ConfigNum& aNum) const;
private:
    static const TUint kMaxNumLength = 11;
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
    typedef KeyValuePair<TUint> KvpChoice;
public:
    ConfigChoice(IConfigManagerInitialiser& aManager, const Brx& aKey, const std::vector<TUint>& aChoices, TUint aDefault);
    const std::vector<TUint>& Choices() const;
    void Set(TUint aVal);   // THROWS ConfigInvalidSelection
private:
    TBool IsValid(TUint aVal) const;
public: // from ConfigVal
    TUint Subscribe(FunctorConfigChoice aFunctor);
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    void Deserialise(const Brx& aString);   // THROWS ConfigNotANumber, ConfigInvalidSelection
private: // from ConfigVal
    void Write(KvpChoice& aKvp);
private:
    inline TBool operator==(const ConfigChoice& aChoice) const;
private:
    static const TUint kMaxChoiceLength = 10;
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
    typedef KeyValuePair<const Brx&> KvpText;
public:
    ConfigText(IConfigManagerInitialiser& aManager, const Brx& aKey, TUint aMaxLength, const Brx& aDefault);
    TUint MaxLength() const;
    void Set(const Brx& aText); // THROWS ConfigValueTooLong
private:
    TBool IsValid(const Brx& aVal) const;
public: // from ConfigVal
    TUint Subscribe(FunctorConfigText aFunctor);
public: // from ConfigVal
    void Serialise(IWriter& aWriter) const;
    void Deserialise(const Brx& aString);   // THROWS ConfigValueTooLong
private: // from ConfigVal
    void Write(KvpText& aKvp);
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
 * Should only ever be used by owners of ConfigVal items and the class
 * responsible for Open()ing the config manager once all values have been
 * added.
 *
 * Calling Open() ensures uniqueness of keys from that point on. If an attempt
 * is made to add a duplicate key at startup, before Open() is called, an
 * implementer of this should throw ConfigKeyExists. (And any attempt to create
 * a ConfigVal after Open() has been called should also cause an ASSERT.)
 */
class IConfigManagerInitialiser
{
public:
    virtual IStoreReadWrite& Store() = 0;
    virtual void Open() = 0;
    virtual void Add(ConfigNum& aNum) = 0;
    virtual void Add(ConfigChoice& aChoice) = 0;
    virtual void Add(ConfigText& aText) = 0;
    virtual void FromStore(const Brx& aKey, Bwx& aDest, const Brx& aDefault) = 0;
    virtual void ToStore(const Brx& aKey, const Brx& aValue) = 0;
    virtual ~IConfigManagerInitialiser() {}
};

/*
 * Helper class for ConfigManager.
 */
template <class T>
class SerialisedMap
{
private:
    typedef std::map<const Brx*, T*, BufferPtrCmp> Map;
public:
    typedef typename Map::const_iterator Iterator;
public:
    SerialisedMap();
    ~SerialisedMap();
    void Add(const Brx& aKey, T& aVal);
    TBool Has(const Brx& aKey) const;
    T& Get(const Brx& aKey) const;
    Iterator Begin() const;
    Iterator End() const;
private:
    Map iMap;
    mutable Mutex iLock;
};

// SerialisedMap
template <class T> SerialisedMap<T>::SerialisedMap()
    : iLock("SLML")
{
}

template <class T> SerialisedMap<T>::~SerialisedMap()
{
    // Delete all keys.
    AutoMutex a(iLock);
    typename Map::iterator it;
    for (it = iMap.begin(); it != iMap.end(); ++it) {
        delete (*it).first;
    }
}

template <class T> void SerialisedMap<T>::Add(const Brx& aKey, T& aVal)
{
    Brh* key = new Brh(aKey);
    AutoMutex a(iLock);
    typename Map::iterator it = iMap.find(key);
    if (it != iMap.end()) {
        THROW(ConfigKeyExists);
    }
    iMap.insert(std::pair<const Brx*, T*>(key, &aVal));
}

template <class T> TBool SerialisedMap<T>::Has(const Brx& aKey) const
{
    TBool found = false;
    Brn key(aKey);
    AutoMutex a(iLock);
    typename Map::const_iterator it = iMap.find(&key);
    if (it != iMap.end()) {
        found = true;
    }

    return found;
}

template <class T> T& SerialisedMap<T>::Get(const Brx& aKey) const
{
    Brn key(aKey);
    AutoMutex a(iLock);
    typename Map::const_iterator it = iMap.find(&key);
    //ASSERT(it != iMap.end()); // assert value with ID of aKey exists
    if (it == iMap.end()) {
        ASSERTS();
    }

    return *(it->second);
}

template <class T> typename SerialisedMap<T>::Iterator SerialisedMap<T>::Begin() const
{
    return iMap.cbegin();
}

template <class T> typename SerialisedMap<T>::Iterator SerialisedMap<T>::End() const
{
    return iMap.cend();
}

/**
 * Class implementing IWriter that writes all values using Log::Print().
 */
class WriterPrinter : public IWriter
{
public: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
};

/*
 * Class storing a collection of ConfigVals. Values are stored with, and
 * retrievable via, an ID of form "some.value.identifier". Classes that create
 * ConfigVals own them and are responsible for their destruction.
 *
 * Known identifiers are listed elsewhere.
 */
class ConfigManager : public IConfigManagerReader, public IConfigManagerInitialiser
{
private:
    typedef SerialisedMap<ConfigNum> ConfigNumMap;
    typedef SerialisedMap<ConfigChoice> ConfigChoiceMap;
    typedef SerialisedMap<ConfigText> ConfigTextMap;
public:
    ConfigManager(IStoreReadWrite& aStore);
    void Print() const;     // for debugging!
    void DumpToStore();     // for debugging!
public: // from IConfigManagerReader
    TBool HasNum(const Brx& aKey) const;
    ConfigNum& GetNum(const Brx& aKey) const;
    TBool HasChoice(const Brx& aKey) const;
    ConfigChoice& GetChoice(const Brx& aKey) const;
    TBool HasText(const Brx& aKey) const;
    ConfigText& GetText(const Brx& aKey) const;
    TBool Has(const Brx& aKey) const;
    ISerialisable& Get(const Brx& aKey) const;
public: // from IConfigManagerInitialiser
    IStoreReadWrite& Store();
    void Open();
    void Add(ConfigNum& aNum);
    void Add(ConfigChoice& aChoice);
    void Add(ConfigText& aText);
    void FromStore(const Brx& aKey, Bwx& aDest, const Brx& aDefault);
    void ToStore(const Brx& aKey, const Brx& aValue);
private:
    void AddNum(const Brx& aKey, ConfigNum& aNum);
    void AddChoice(const Brx& aKey, ConfigChoice& aChoice);
    void AddText(const Brx& aKey, ConfigText& aText);
private:
    template <class T> void Add(SerialisedMap<T>& aMap, const Brx& aKey, T& aVal);
    template <class T> void Print(const ConfigVal<T>& aVal) const;
    template <class T> void Print(const SerialisedMap<T>& aMap) const;
    template <class T> void DumpToStore(const ConfigVal<T>& aVal);
    template <class T> void DumpToStore(const SerialisedMap<T>& aMap);
private:
    IStoreReadWrite& iStore;
    ConfigNumMap iMapNum;
    ConfigChoiceMap iMapChoice;
    ConfigTextMap iMapText;
    TBool iOpen;
    Mutex iLock;
};

} // namespace Configuration
} // namespace OpenHome

#endif // HEADER_CONFIGMANAGER
