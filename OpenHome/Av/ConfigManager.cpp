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
    std::vector<const Brx*>::iterator it;
    for (it = iAllowedValues.begin() ; it != iAllowedValues.end(); it++) {
        if (**it == aVal) {
            THROW(AvConfigValueAlreadyExists);
        }
    }
    iAllowedValues.push_back(&aVal);
}

std::vector<const Brx*> CVChoice::Options()
{
    return iAllowedValues;
}

const Brx& CVChoice::Get() const
{
    ASSERT(iAllowedValues.size() > 0);

    return *iAllowedValues[iSelected];
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
