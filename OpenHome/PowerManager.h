#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>

#include <list>

namespace OpenHome {
namespace Configuration {
    class IStoreReadWrite;
}

enum PowerDownPriority {
    kPowerPriorityLowest = 0
   ,kPowerPriorityNormal = 50
   ,kPowerPriorityHighest = 100
};

class IPowerHandler
{
public:
    virtual void PowerUp() = 0;
    virtual void PowerDown() = 0;
    virtual ~IPowerHandler() {}
};

/**
 * Interface that IPowerHandlers will be returned when they register with an
 * IPowerManager.
 *
 * Deleting an instance of a class implementing this interface causes the class
 * to be deregistered from the IPowerManager.
 */
class IPowerManagerObserver
{
public:
    virtual ~IPowerManagerObserver() {}
};

class IPowerManager
{
public:
    virtual IPowerManagerObserver* Register(IPowerHandler& aHandler, TUint aPriority) = 0;
    virtual ~IPowerManager() {}
};

class PowerManagerObserver;

class PowerManager : public IPowerManager
{
    friend class PowerManagerObserver;
public:
    PowerManager();
    ~PowerManager();
    void PowerDown();
public: // from IPowerManager
    IPowerManagerObserver* Register(IPowerHandler& aHandler, TUint aPriority) override;
private:
    void Deregister(TUint aId);
private:
    typedef std::list<PowerManagerObserver*> PriorityList;  // efficient insertion and removal
    PriorityList iList;
    TUint iNextHandlerId;
    TBool iPowerDown;
    Mutex iLock;
};

/**
 * Class that is returned by IPowerManager::Register if registration of an
 * IPowerHandler fails.
 */
class PowerManagerObserverNull : public IPowerManagerObserver
{
public:
    ~PowerManagerObserverNull();
};

/**
 * Class that is returned by IPowerManager::Register if registration of an
 * IPowerHandler succeeds.
 */
class PowerManagerObserver : public IPowerManagerObserver, public INonCopyable
{
public:
    PowerManagerObserver(PowerManager& aPowerManager, IPowerHandler& aHandler, TUint aId, TUint aPriority);
    ~PowerManagerObserver();
    IPowerHandler& PowerHandler() const;
    TUint Id() const;
    TUint Priority() const;
private:
    PowerManager& iPowerManager;
    IPowerHandler& iHandler;
    const TUint iId;
    const TUint iPriority;
};

/*
 * Abstract class that only writes its value out to store at power down.
 */
class StoreVal : public IPowerHandler
{
public:
    static const TUint kMaxIdLength = 32;
protected:
    StoreVal(Configuration::IStoreReadWrite& aStore, const Brx& aKey);
protected: // from IPowerHandler
    virtual void PowerUp() = 0;
    virtual void PowerDown() = 0;
protected:
    IPowerManagerObserver* iObserver;
    Configuration::IStoreReadWrite& iStore;
    const Bws<kMaxIdLength> iKey;
    mutable Mutex iLock;
};

/*
 * Int class that only writes its value out to store at power down.
 */
class StoreInt : public StoreVal
{
public:
    StoreInt(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, TUint aPriority, const Brx& aKey, TInt aDefault);
    ~StoreInt();
    TInt Get() const;
    void Set(TInt aValue); // owning class knows limits
private: // from StoreVal
    void PowerUp() override;
    void PowerDown() override;
private:
    void Write();
private:
    TInt iVal;
};

/*
 * Text class that only writes its value out to store at power down.
 */
class StoreText : public StoreVal
{
public:
    StoreText(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, TUint aPriority, const Brx& aKey, const Brx& aDefault, TUint aMaxLength);
    ~StoreText();
    void Get(Bwx& aVal) const;
    void Set(const Brx& aValue);
private: // from StoreVal
    void PowerUp() override;
    void PowerDown() override;
private:
    void Write();
private:
    Bwh iVal;
};

} // namespace OpenHome

