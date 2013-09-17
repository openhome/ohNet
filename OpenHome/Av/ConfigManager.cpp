#include <OpenHome/Av/ConfigManager.h>

using namespace OpenHome;
using namespace OpenHome::Av;


// CVal

CVal::CVal()
    : iObserverLock("CVOL")
    , iNextObserverId(0)
{
}

CVal::~CVal()
{
    ASSERT(iObservers.size() == 0);
}

TUint CVal::Subscribe(Functor aFunctor)
{
    iObserverLock.Wait();
    TUint id = iNextObserverId;
    iObservers.insert(std::pair<TUint,Functor>(id, aFunctor));
    iNextObserverId++;
    iObserverLock.Signal();
    return id;
}

void CVal::Unsubscribe(TUint aId)
{
    iObserverLock.Wait();
    Map::iterator it = iObservers.find(aId);
    if (it != iObservers.end()) {
        iObservers.erase(it);
    }
    iObserverLock.Signal();
}

void CVal::NotifySubscribers()
{
    AutoMutex a(iObserverLock);
    for (Map::iterator it = iObservers.begin(); it != iObservers.end(); it++) {
        it->second();
    }
}


// CVNum

CVNum::CVNum(TInt aMin, TInt aMax, TInt aVal)
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

CVNum::CVNum(TInt aMin, TInt aMax)
    : iMin(aMin)
    , iMax(aMax)
    , iVal(iMin)
{
    if (iMin > iMax) {
        THROW(AvConfigInvalidRange);
    }
}

TInt CVNum::Min() const
{
    return iMin;
}

TInt CVNum::Max() const
{
    return iMax;
}

TInt CVNum::Get() const
{
    return iVal;
}

TBool CVNum::Set(TInt aVal)
{
    TBool changed = false;

    if (aVal < iMin || aVal > iMax) {
        THROW(AvConfigValueOutOfRange);
    }

    if (aVal != iVal) {
        iVal = aVal;
        CVal::NotifySubscribers();
        changed = true;
    }

    return changed;
}


// CVChoice

CVChoice::CVChoice()
    : iSelected(0)
{
}

CVChoice::~CVChoice()
{
}


void CVChoice::Add(const Brx& aVal)
{
    Brn val(aVal);
    std::vector<Brn>::iterator it;
    for (it = iAllowedValues.begin(); it != iAllowedValues.end(); it++) {
        if (*it == aVal) {
            THROW(AvConfigValueAlreadyExists);
        }
    }
    iAllowedValues.push_back(val);
}

std::vector<const Brx*> CVChoice::Options()
{
    std::vector<const Brx*> options;
    std::vector<Brn>::iterator it;
    for (it = iAllowedValues.begin(); it != iAllowedValues.end(); it++) {
        options.push_back(&*it);
    }
    return options;
}

const Brx& CVChoice::Get() const
{
    ASSERT(iAllowedValues.size() > 0);

    return iAllowedValues[iSelected];
}

TBool CVChoice::Set(TUint aIndex)
{
    TBool changed = false;

    if (aIndex >= iAllowedValues.size()) {
        THROW(AvConfigIndexOutOfRange);
    }

    if (aIndex != iSelected) {
        iSelected = aIndex;
        CVal::NotifySubscribers();
        changed = true;
    }

    return changed;
}


// CVText

CVText::CVText(TUint aMaxBytes)
    : iText(aMaxBytes)
{
}

TUint CVText::MaxLength() const
{
    return iText.MaxBytes();
}

const Brx& CVText::Get() const
{
    return iText;
}

TBool CVText::Set(const Brx& aText)
{
    TBool changed = false;

    if (aText.Bytes() > iText.MaxBytes()) {
        THROW(AvConfigValueTooLong);
    }

    if (aText != iText) {
        iText.Replace(aText);
        CVal::NotifySubscribers();
        changed = true;
    }

    return changed;
}


// ConfigurationManager

template <class T> void ConfigurationManager::Add(SerialisedMap<T>& aMap, const Brx& aId, T& aVal)
{
    if (iMapNum.Has(aId) || iMapChoice.Has(aId) || iMapText.Has(aId)) {
        THROW(AvConfigIdAlreadyExists);
    }

    aMap.Add(aId, aVal);
}

void ConfigurationManager::Add(const Brx& aId, CVNum& aNum)
{
    Add(iMapNum, aId, aNum);
}

void ConfigurationManager::Add(const Brx& aId, CVChoice& aChoice)
{
    Add(iMapChoice, aId, aChoice);
}

void ConfigurationManager::Add(const Brx& aId, CVText& aText)
{
    Add(iMapText, aId, aText);
}

TBool ConfigurationManager::HasNum(const Brx& aId)
{
    return iMapNum.Has(aId);
}

CVNum& ConfigurationManager::GetNum(const Brx& aId)
{
    return iMapNum.Get(aId);
}

TBool ConfigurationManager::HasChoice(const Brx& aId)
{
    return iMapChoice.Has(aId);
}

CVChoice& ConfigurationManager::GetChoice(const Brx& aId)
{
    return iMapChoice.Get(aId);
}

TBool ConfigurationManager::HasText(const Brx& aId)
{
    return iMapText.Has(aId);
}

CVText& ConfigurationManager::GetText(const Brx& aId)
{
    return iMapText.Get(aId);
}
