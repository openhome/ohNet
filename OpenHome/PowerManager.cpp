#include <OpenHome/PowerManager.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>

using namespace OpenHome;


// PowerManager

PowerManager::PowerManager()
    : iLock("PMLO")
{
}

PowerManager::~PowerManager() {}

void PowerManager::PowerDown()
{
    // This call can only be made ONCE as PriorityFunctors are deleted as they
    // are called and removed. Subsequent calls will call no functors.
    // If it must be possible to reuse the PriorityFunctors, two pointers to
    // priority_queues can be stored, with values copied into second queue
    // before being popped, and then swapping queue pointers.

    // FIXME - the caller of power down should provide some kind of interrupt
    // for stopping any non-essential store tasks in progress
    AutoMutex a(iLock);
    while (!iList.empty()) {
        const PriorityFunctor& functor = iList.front();
        functor.Callback();
        iList.pop_front(); // deletes PriorityFunctor
    }
}

void PowerManager::RegisterObserver(Functor aFunctor, TUint aPriority)
{
    ASSERT(aPriority <= kPowerPriorityHighest)
    ASSERT(aPriority >= kPowerPriorityLowest); // shouldn't matter as lowest is 0, and parameter type is TUint
    const PriorityFunctor functor(aFunctor, aPriority);
    AutoMutex a(iLock);
    PriorityList::const_iterator it;
    for (it = iList.cbegin(); it != iList.cend(); ++it) {
        if ((*it).Priority() < functor.Priority()) {
            iList.insert(it, functor);
            return;
        }
    }
    // Callback is lower priority than anything in list.
    iList.push_back(functor); // PriorityFunctor copied into queue
}


// PowerManager::PriorityFunctor

PowerManager::PriorityFunctor::PriorityFunctor(Functor aFunctor, TUint aPriority)
    : iFunctor(aFunctor)
    , iPriority(aPriority)
{
}

void PowerManager::PriorityFunctor::Callback() const
{
    iFunctor();
}

TUint PowerManager::PriorityFunctor::Priority() const
{
    return iPriority;
}


// StoreVal

StoreVal::StoreVal(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, TUint aPriority, const Brx& aKey)
    : iStore(aStore)
    , iKey(aKey)
    , iLock("STVM")
{
    // register with IPowerManager
    aPowerManager.RegisterObserver(MakeFunctor(*this, &StoreVal::Write), aPriority);
}


// StoreInt

StoreInt::StoreInt(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, TUint aPriority, const Brx& aKey, TInt aDefault)
    : StoreVal(aStore, aPowerManager, aPriority, aKey)
    , iVal(aDefault)
{
    // read value from store (if it exists; otherwise write default)
    Bws<sizeof(TInt)> buf;
    iLock.Wait();
    try {
        iStore.Read(iKey, buf);
        iVal = Converter::BeUint32At(buf, 0);
        iLock.Signal();
    }
    catch (StoreKeyNotFound&) {
        iLock.Signal();
        Write();
    }
}

StoreInt::~StoreInt() {}

TInt StoreInt::Get() const
{
    AutoMutex a(iLock);
    return iVal;
}

void StoreInt::Set(TInt aValue)
{
    AutoMutex a(iLock);
    iVal = aValue;
}

void StoreInt::Write()
{
    AutoMutex a(iLock);
    Bws<sizeof(TInt)> buf;
    buf.Append(Arch::BigEndian4(iVal));
    iStore.Write(iKey, buf);
}


// StoreText

StoreText::StoreText(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, TUint aPriority, const Brx& aKey, const Brx& aDefault, TUint aMaxLength)
    : StoreVal(aStore, aPowerManager, aPriority, aKey)
    , iVal(aMaxLength)
{
    iLock.Wait();
    try {
        iStore.Read(iKey, iVal);
        iLock.Signal();
    }
    catch (StoreKeyNotFound&) {
        iVal.Replace(aDefault);
        iLock.Signal();
        Write();
    }
}

StoreText::~StoreText() {}

void StoreText::Get(Bwx& aBuf) const
{
    AutoMutex a(iLock);
    aBuf.Replace(iVal);
}

void StoreText::Set(const Brx& aValue)
{
    AutoMutex a(iLock);
    iVal.Replace(aValue);
}

void StoreText::Write()
{
    AutoMutex a(iLock);
    iStore.Write(iKey, iVal);
}
