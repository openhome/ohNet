#ifndef HEADER_CONFIGMANAGER
#define HEADER_CONFIGMANAGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <map>
#include <vector>

EXCEPTION(AvConfigInvalidRange);
EXCEPTION(AvConfigValueOutOfRange);
EXCEPTION(AvConfigValueAlreadyExists);
EXCEPTION(AvConfigIndexOutOfRange);
EXCEPTION(AvConfigValueTooLong);
EXCEPTION(AvConfigIdAlreadyExists);

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

class CVal : public IObservable
{
public:
    CVal();
    virtual ~CVal() = 0;
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
class CVNum : public CVal
{
public:
    CVNum(TInt aMin, TInt aMax, TInt aVal);
    CVNum(TInt aMin, TInt aMax); // initialise value of CVNum to aMin
    TInt Min() const;
    TInt Max() const;
    TInt Get() const;
    TBool Set(TInt aVal);
    inline TBool operator==(const CVNum& aNum) const;
private:
    TInt iMin;
    TInt iMax;
    TInt iVal;
};

inline TBool CVNum::operator==(const CVNum& aNum) const
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
class CVChoice : public CVal
{
public:
    CVChoice();
    ~CVChoice();
    void Add(const Brx& aVal);
    std::vector<const Brx*> Options();
    const Brx& Get() const;
    TBool Set(TUint aIndex);
    inline TBool operator==(const CVChoice& aChoice) const;
private:
    std::vector<const Brx*> iAllowedValues;
    TUint iSelected;
};

inline TBool CVChoice::operator==(const CVChoice& aChoice) const
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
class CVText : public CVal
{
public:
    CVText(TUint aMaxBytes);
    TUint MaxLength() const;
    const Brx& Get() const;
    TBool Set(const Brx& aText);
    inline TBool operator==(const CVText& aText) const;
private:
    Bwh iText;
};

inline TBool CVText::operator==(const CVText& aText) const
{
    return (iText == aText.iText);
}

/*
 * Interface for a configuration manager.
 */
class IConfigurationManager
{
public:
    virtual void Add(const Brx& aId, CVNum& aNum) = 0;
    virtual void Add(const Brx& aId, CVChoice& aChoice) = 0;
    virtual void Add(const Brx& aId, CVText& aText) = 0;

    virtual TBool HasNum(const Brx& aId) = 0;
    virtual CVNum& GetNum(const Brx& aId) = 0;
    virtual TBool HasChoice(const Brx& aId) = 0;
    virtual CVChoice& GetChoice(const Brx& aId) = 0;
    virtual TBool HasText(const Brx& aId) = 0;
    virtual CVText& GetText(const Brx& aId) = 0;
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
    //void Remove(const Brx& aId);
private:
    typedef std::map<Brn, T&, BufferCmp> Map;
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
    Map::iterator it = iMap.find(id);
    if (it != iMap.end()) {
        THROW(AvConfigIdAlreadyExists);
    }
    iMap.insert(std::pair<Brn, T&>(id, aVal));
}

template <class T> TBool SerialisedMap<T>::Has(const Brx& aId)
{
    TBool found = false;
    Brn id(aId);
    AutoMutex a(iLock);
    Map::iterator it = iMap.find(id);
    if (it != iMap.end()) {
        found = true;
    }

    return found;
}

template <class T> T& SerialisedMap<T>::Get(const Brx& aId)
{
    Brn id(aId);
    AutoMutex a(iLock);
    Map::iterator it = iMap.find(id);
    ASSERT(it != iMap.end());

    return it->second;
}


/*
 * Class storing a collection of CVals. Values are stored with, and retrievable
 * via, an ID of form "some.value.identifier". Classes that create CVals own
 * them and are responsible for their destruction.
 *
 * Known identifiers are listed elsewhere.
 */
class ConfigurationManager : public IConfigurationManager
{
public: // from IConfigurationManager
    void Add(const Brx& aId, CVNum& aNum);
    void Add(const Brx& aId, CVChoice& aChoice);
    void Add(const Brx& aId, CVText& aText);

    TBool HasNum(const Brx& aId);
    CVNum& GetNum(const Brx& aId);
    TBool HasChoice(const Brx& aId);
    CVChoice& GetChoice(const Brx& aId);
    TBool HasText(const Brx& aId);
    CVText& GetText(const Brx& aId);
private:
    template <class T> void Add(SerialisedMap<T>& aMap, const Brx& aId, T& aVal);
private:
    SerialisedMap<CVNum> iMapNum;
    SerialisedMap<CVChoice> iMapChoice;
    SerialisedMap<CVText> iMapText;
};


} // namespace Av
} // namespace OpenHome

#endif // HEADER_CONFIGMANAGER
