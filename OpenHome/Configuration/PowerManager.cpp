#include <OpenHome/Configuration/PowerManager.h>

using namespace OpenHome;
using namespace OpenHome::Configuration;


// PowerManager

PowerManager::PowerManager()
    : iLock("PMLO")
{
}

void PowerManager::PowerDown()
{
    // This call can only be made ONCE as PriorityFunctors are deleted as they
    // are called and removed. Subsequent calls will call no functors.
    // If it must be possible to reuse the PriorityFunctors, two pointers to
    // priority_queues can be stored, with values copied into second queue
    // before being popped, and then swapping queue pointers.
    AutoMutex a(iLock);
    while (!iQueue.empty()) {
        const PriorityFunctor& functor = iQueue.top();
        functor.Callback();
        iQueue.pop(); // deletes PriorityFunctor
    }
}

void PowerManager::RegisterObserver(Functor aFunctor, TUint aPriority)
{
    ASSERT(aPriority <= kPriorityHighest)
    ASSERT(aPriority >= kPriorityLowest); // shouldn't matter as lowest is 0, and parameter type is TUint
    const PriorityFunctor functor(aFunctor, aPriority);
    AutoMutex a(iLock);
    iQueue.push(functor); // PriorityFunctor copied into queue
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


// PowerManager::PriorityFunctorCmp

TBool PowerManager::PriorityFunctorCmp::operator()(const PriorityFunctor& aFunc1, const PriorityFunctor& aFunc2) const
{
    return aFunc1.Priority() < aFunc2.Priority();
}
