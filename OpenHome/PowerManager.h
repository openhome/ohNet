#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Configuration/ConfigManager.h>

#include <list>
#include <vector>
#include <memory>

namespace OpenHome {

enum PowerDownPriority {
    kPowerPriorityLowest = 0
   ,kPowerPriorityNormal = 50
   ,kPowerPriorityHighest = 100
};

enum StandbyHandlerPriority {
    kStandbyHandlerPriorityLowest = 0    // first to be called for StandbyEnabled(), last for StandbyDisabled()
   ,kStandbyHandlerPriorityNormal = 50
   ,kStandbyHandlerPriorityHighest = 100 // last to be called for StandbyEnabled(), first for StandbyDisabled()
};

enum class StandbyDisableReason {
     User
    ,Boot
    ,Alarm
};

class IPowerHandler
{
public:
    virtual void PowerUp() = 0;
    virtual void PowerDown() = 0;
    virtual ~IPowerHandler() {}
};

class IStandbyHandler
{
public:
    virtual void StandbyEnabled() = 0;
    virtual void StandbyDisabled(StandbyDisableReason aReason) = 0;
    virtual ~IStandbyHandler() {}
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

class IStandbyObserver
{
public:
    virtual ~IStandbyObserver() {}
};

class IPowerManager
{
public:
    virtual void NotifyPowerDown() = 0;
    virtual void StandbyEnable() = 0;
    virtual void StandbyDisable(StandbyDisableReason aReason) = 0;
    virtual IPowerManagerObserver* RegisterPowerHandler(IPowerHandler& aHandler, TUint aPriority) = 0;
    virtual IStandbyObserver* RegisterStandbyHandler(IStandbyHandler& aHandler, TUint aPriority) = 0;
    virtual ~IPowerManager() {}
};

class PowerManagerObserver;
class StandbyObserver;

class PowerManager : public IPowerManager
{
    friend class PowerManagerObserver;
    friend class StandbyObserver;
    static const Brn kConfigKey;
    static const TUint kConfigIdStartupStandbyEnabled;
    static const TUint kConfigIdStartupStandbyDisabled;
public:
    PowerManager(Configuration::IConfigInitialiser& aConfigInit);
    ~PowerManager();
    void Start();
public: // from IPowerManager
    void NotifyPowerDown() override;
    void StandbyEnable() override;
    void StandbyDisable(StandbyDisableReason aReason) override;
    IPowerManagerObserver* RegisterPowerHandler(IPowerHandler& aHandler, TUint aPriority) override;
    IStandbyObserver* RegisterStandbyHandler(IStandbyHandler& aHandler, TUint aPriority) override;
private:
    void DeregisterPower(TUint aId);
    void DeregisterStandby(TUint aId);
    void StartupStandbyChanged(Configuration::KeyValuePair<TUint>& aKvp);
private:
    enum class Standby {
        On,
        Off,
        Undefined
    };
private:
    typedef std::list<PowerManagerObserver*> PriorityList;  // efficient insertion and removal
    PriorityList iPowerObservers;
    std::vector<StandbyObserver*> iStandbyObservers;
    TUint iNextPowerId;
    TUint iNextStandbyId;
    TBool iPowerDown;
    Standby iStandby;
    StandbyDisableReason iLastDisableReason;
    mutable Mutex iLock;
    Configuration::ConfigChoice* iConfigStartupStandby;
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

class StandbyObserver : public IStandbyObserver, private INonCopyable
{
public:
    StandbyObserver(PowerManager& aPowerManager, IStandbyHandler& aHandler, TUint aId, TUint aPriority);
    ~StandbyObserver();
    IStandbyHandler& Handler() const;
    TUint Id() const;
    TUint Priority() const;
private:
    PowerManager& iPowerManager;
    IStandbyHandler& iHandler;
    const TUint iId;
    const TUint iPriority;
};

/*
 * Abstract class that only writes its value out to store at power down.
 */
class StoreVal : protected IPowerHandler, protected IStandbyHandler
{
public:
    static const TUint kMaxIdLength = 32;
protected:
    StoreVal(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, const Brx& aKey);
protected: // from IPowerHandler
    virtual void PowerUp() override = 0;
    void PowerDown() override;
private: // from IStandbyHandler
    void StandbyEnabled() override;
    void StandbyDisabled(StandbyDisableReason aReason) override;
public:
    virtual void Write() = 0;
protected:
    IPowerManagerObserver* iObserver;
    Configuration::IStoreReadWrite& iStore;
    const Bws<kMaxIdLength> iKey;
    mutable Mutex iLock;
private:
    std::unique_ptr<IStandbyObserver> iStandbyObserver;
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
    static void Write(const Brx& aKey, TInt aValue, Configuration::IStoreReadWrite& aStore);
private: // from StoreVal
    void PowerUp() override;
public: // from StoreVal
    void Write() override;
private:
    TInt iVal;
    TBool iChanged;
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
public: // from StoreVal
    void Write() override;
private:
    Bwh iVal;
    TBool iChanged;
};

} // namespace OpenHome

