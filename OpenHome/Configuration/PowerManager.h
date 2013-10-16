#ifndef HEADER_POWERMANAGER
#define HEADER_POWERMANAGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <queue>
#include <vector>

namespace OpenHome {
namespace Configuration {

enum PowerDownPriority {
    kPriorityLowest = 0
   ,kPriorityNormal = 50
   ,kPriorityHighest = 100
};

class IPowerManager
{
public:
    virtual void PowerDown() = 0;
    virtual void RegisterObserver(Functor aFunctor, TUint aPriority) = 0;
};

class PowerManager : public IPowerManager
{
public:
    PowerManager();
public: // from IPowerManager
    void PowerDown();
    void RegisterObserver(Functor aFunctor, TUint aPriority);
private:
    class PriorityFunctor
    {
    public:
        PriorityFunctor(Functor aFunctor, TUint aPriority);
        void Callback() const;
        TUint Priority() const;
    private:
        Functor iFunctor;
        TUint iPriority;
    };
    class PriorityFunctorCmp
    {
    public:
        TBool operator()(const PriorityFunctor& aFunc1, const PriorityFunctor& aFunc2) const;
    };
private:
    typedef std::priority_queue<const PriorityFunctor, std::vector<const PriorityFunctor>, PriorityFunctorCmp> PriorityQueue;
    PriorityQueue iQueue;
    Mutex iLock;
};

} // namespace Configuration
} // namespace OpenHome

#endif // HEADER_POWERMANAGER
