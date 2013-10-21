#ifndef HEADER_POWERMANAGER
#define HEADER_POWERMANAGER

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <queue>
#include <vector>

namespace OpenHome {
namespace Configuration {
    class IStoreReadWrite;
}

enum PowerDownPriority {
    kPowerPriorityLowest = 0
   ,kPowerPriorityNormal = 50
   ,kPowerPriorityHighest = 100
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
    virtual ~PowerManager();
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
    typedef std::priority_queue<const PriorityFunctor, std::vector<PriorityFunctor>, PriorityFunctorCmp> PriorityQueue;
    PriorityQueue iQueue;
    Mutex iLock;
};

/*
 * Int class that only writes its value out to store at power down.
 */
class StoreInt : private INonCopyable
{
public:
    StoreInt(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, TUint aPriority, const Brx& aKey, TInt aDefault);
    TInt Get() const;
    void Set(TInt aValue); // owning class knows limits
private:
    void Write();
private:
    Configuration::IStoreReadWrite& iStore;
    IPowerManager& iPowerManager;
    const Brx& iKey;
    TInt iVal;
};

} // namespace OpenHome

#endif // HEADER_POWERMANAGER
