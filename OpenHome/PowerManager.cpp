#include <OpenHome/PowerManager.h>
#include <OpenHome/Configuration/ConfigManager.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>

using namespace OpenHome;


// PowerManager

PowerManager::PowerManager()
    : iNextHandlerId(0)
    , iPowerDown(false)
    , iLock("PMLO")
{
}

PowerManager::~PowerManager()
{
    iLock.Wait();
    if (!iList.empty()) {
        iLock.Signal();
        ASSERTS(); // ensure all registered observers have deregistered
    }
    iLock.Signal();
}

void PowerManager::PowerDown()
{
    // FIXME - the caller of power down should provide some kind of interrupt
    // for stopping any non-essential store tasks in progress
    iLock.Wait();
    if (iPowerDown) {
        iLock.Signal();
        ASSERTS();  // PowerDown() should never be called more than once
    }
    iPowerDown = true;
    PriorityList::const_iterator it;
    for (it = iList.cbegin(); it != iList.cend(); ++it) {
        IPowerHandler& handler = (*it)->PowerHandler();
        handler.PowerDown();
    }
    iLock.Signal();
}

IPowerManagerObserver* PowerManager::Register(IPowerHandler& aHandler, TUint aPriority)
{
    ASSERT(aPriority <= kPowerPriorityHighest)
    ASSERT(aPriority >= kPowerPriorityLowest); // shouldn't matter as lowest is 0, and parameter type is TUint

    AutoMutex a(iLock);
    if (iPowerDown) {
        return new PowerManagerObserverNull();
    }

    PowerManagerObserver* observer = new PowerManagerObserver(*this, aHandler, iNextHandlerId++, aPriority);

    PriorityList::iterator it;
    for (it = iList.begin(); it != iList.end(); ++it) {
        if ((*it)->Priority() < observer->Priority()) {
            iList.insert(it, observer);
            break;
        }
    }

    if (it == iList.cend()) {
        // Callback is lower priority than anything in list.
        iList.push_back(observer);
    }

    aHandler.PowerUp();
    return observer;
}

// Called from destructor of PowerManagerObserver.
void PowerManager::Deregister(TUint aId)
{
    AutoMutex a(iLock);
    PriorityList::iterator it;
    for (it = iList.begin(); it != iList.end(); ++it) {
        if ((*it)->Id() == aId) {
            // Call PowerDown() on handler under normal shutdown circumstances.
            // PowerDown() may have been invoked on the PowerManager itself,
            // and object destruction started before power failure. Don't want
            // to call PowerDown() on the handler again in that case.
            if (!iPowerDown) {
                IPowerHandler& handler = (*it)->PowerHandler();
                handler.PowerDown();
            }
            iList.erase(it);
            return;
        }
    }
}


// PowerManagerObserverNull

PowerManagerObserverNull::~PowerManagerObserverNull()
{
    // Not actually registered in PowerManager, so do nothing.
}


// PowerManagerObserver

PowerManagerObserver::PowerManagerObserver(PowerManager& aPowerManager, IPowerHandler& aHandler, TUint aId, TUint aPriority)
    : iPowerManager(aPowerManager)
    , iHandler(aHandler)
    , iId(aId)
    , iPriority(aPriority)
{
}

PowerManagerObserver::~PowerManagerObserver()
{
    iPowerManager.Deregister(iId);
}

IPowerHandler& PowerManagerObserver::PowerHandler() const
{
    return iHandler;
}

TUint PowerManagerObserver::Id() const
{
    return iId;
}

TUint PowerManagerObserver::Priority() const
{
    return iPriority;
}


// StoreVal

StoreVal::StoreVal(Configuration::IStoreReadWrite& aStore, const Brx& aKey)
    : iObserver(nullptr)
    , iStore(aStore)
    , iKey(aKey)
    , iLock("STVM")
{
}


// StoreInt

StoreInt::StoreInt(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, TUint aPriority, const Brx& aKey, TInt aDefault)
    : StoreVal(aStore, aKey)
    , iVal(aDefault)
{
    // Cannot allow StoreVal to register, as IPowerManager will call PowerUp()
    // after successful registration, and can't successfully call an overridden
    // virtual function from constructor (or destructor).
    iObserver = aPowerManager.Register(*this, aPriority);
}

StoreInt::~StoreInt()
{
    delete iObserver;
}

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

void StoreInt::PowerUp()
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

void StoreInt::PowerDown()
{
    Write();
}

void StoreInt::Write()
{
    AutoMutex a(iLock);
    Bws<sizeof(TInt)> buf;
    WriterBuffer writerBuf(buf);
    WriterBinary writerBin(writerBuf);
    writerBin.WriteUint32Be(iVal);
    iStore.Write(iKey, buf);
}


// StoreText

StoreText::StoreText(Configuration::IStoreReadWrite& aStore, IPowerManager& aPowerManager, TUint aPriority, const Brx& aKey, const Brx& aDefault, TUint aMaxLength)
    : StoreVal(aStore, aKey)
    , iVal(aMaxLength)
{
    iVal.Replace(aDefault);
    iObserver = aPowerManager.Register(*this, aPriority);
}

StoreText::~StoreText()
{
    delete iObserver;
}

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

void StoreText::PowerUp()
{
    iLock.Wait();
    try {
        iStore.Read(iKey, iVal);
        iLock.Signal();
    }
    catch (StoreKeyNotFound&) {
        //iVal.Replace(aDefault);
        iLock.Signal();
        Write();
    }
}

void StoreText::PowerDown()
{
    Write();
}

void StoreText::Write()
{
    AutoMutex a(iLock);
    iStore.Write(iKey, iVal);
}
