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
private:
    TInt iMin;
    TInt iMax;
    TInt iVal;
};

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
private:
    std::vector<const Brx*> iAllowedValues;
    TUint iSelected;
};

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
private:
    Bwh iText;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_CONFIGMANAGER
