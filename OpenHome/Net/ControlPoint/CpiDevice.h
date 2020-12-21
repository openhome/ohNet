/**
 * List(s) of devices suitable for use in control points
 *
 * Cp prefixes show that classes are intended for use in control points
 * Route inside a name implies that a class requires one instance per network interface
 */

#ifndef HEADER_CPIDEVICE
#define HEADER_CPIDEVICE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Net/Private/FunctorCpiDevice.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>
#include <map>
#include <list>

namespace OpenHome {
namespace Net {

class CpiDeviceList;
class Invocation;
class ServiceType;
class CpiSubscription;
class Property;
class IPropertyProcessor;
typedef std::map<Brn,Property*,BufferCmp> PropertyMap;
typedef std::map<Brn,CpiDevice*,BufferCmp> CpDeviceMap;

class IInvocable
{
public:
    virtual ~IInvocable() {}
    virtual void InvokeAction(Invocation& aInvocation) = 0;
};

class ICpiProtocol : public IInvocable
{
public:
    virtual ~ICpiProtocol() {}
    virtual TBool GetAttribute(const char* aKey, Brh& aValue) const = 0;
    virtual TUint Subscribe(CpiSubscription& aSubscription, const OpenHome::Uri& aSubscriber) = 0;
    virtual TUint Renew(CpiSubscription& aSubscription) = 0;
    virtual void Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid) = 0;
    virtual TBool OrphanSubscriptionsOnSubnetChange() const = 0;
    virtual void NotifyRemovedBeforeReady() = 0;
    virtual TUint Version(const TChar* aDomain, const TChar* aName, TUint aProxyVersion) const = 0;
};

class ICpiDeviceObserver
{
public:
    virtual void Release() = 0;
};

/**
 * Protocol-independent device
 *
 * Instance of this class are reference counted and are automatically deleted
 * when the reference count falls to zero
 */
class CpiDevice : public ICpiProtocol, private IStackObject
{
public:
    /**
     * Sets the ref count to 1
     */
    CpiDevice(CpStack& aStack, const Brx& aUdn, ICpiProtocol& aProtocol, ICpiDeviceObserver& aObserver, void* aOwnerData);
    
    /**
     * Return the Unique Device Name
     * This is guaranteed to uniquely identify a single device
     */
    const Brx& Udn() const;
    
    /**
     * Return the device name as a C string
     */
    const TChar* UdnAsCString() const;
    
    TBool operator==(const CpiDevice& aDevice) const;
    TBool operator!=(const CpiDevice& aDevice) const;
    OpenHome::Net::CpStack& GetCpStack();
    void* OwnerData();

    /**
     * Claim a reference to a device.
     * Can only be called from code that can guarantee another reference is already held
     */
    void AddRef();

    /**
     * Remove a reference to a device.
     * Removing the final reference causes a device to be deleted.
     */
    void RemoveRef();

    virtual TBool GetAttribute(const char* aKey, Brh& aValue) const;
    virtual void InvokeAction(Invocation& aInvocation);
    virtual TUint Subscribe(CpiSubscription& aSubscription, const Uri& aSubscriber);
    virtual TUint Renew(CpiSubscription& aSubscription);
    virtual void Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid);
    virtual TBool OrphanSubscriptionsOnSubnetChange() const;
    virtual void NotifyRemovedBeforeReady();
    virtual TUint Version(const TChar* aDomain, const TChar* aName, TUint aProxyVersion) const;

    /**
     * Mark a device as ready to use.
     * See CpiDeviceList::IsDeviceReady().
     * Note that device list observers won't be notified about a device until it becomes ready
     */
    void SetReady();

    /**
     * True if a device is ready to use; false otherwise
     */
    TBool IsReady() const;

    /**
     * Not intended for use outside this module
     */
    void SetExpired(TBool aExpired);

    /**
     * True if a device's maxAge timer expires before it is added to a list
     * Not intended for use outside this module
     */
    TBool HasExpired() const;

    /**
     * Not intended for use outside this module
     */
    void SetRemoved();

    /**
     * True if a device has been removed.
     * The object may persist for some time after this as its references are released.
     */
    TBool IsRemoved() const;
private: // from IStackObject
    void ListObjectDetails() const;
private:
    /**
     * Not intended for client use.  The call to RemoveRef() which reduces the
     * ref count to 0 will delete
     */
    virtual ~CpiDevice();
private:
    OpenHome::Net::CpStack& iCpStack;
    Brhz iUdn;
    OpenHome::Mutex iLock;
    ICpiProtocol& iProtocol;
    ICpiDeviceObserver& iObserver;
    void* iOwnerData;
    TInt iRefCount;
    TBool iReady;
    TBool iExpired;
    TBool iRemoved;

    friend class CpiDeviceList;
};

/**
 * Callback to allow a UPnP device to signal to its owning list that its maxage
 * timer has expired (implying that the device is no longer active).
 *
 * This class is not intended for use outside this module.
 */
class IDeviceRemover
{
public:
    virtual void Remove(const Brx& aUdn) = 0;
};

class IDeviceListUpdater
{
public:
    virtual void AddRef() = 0;
    virtual void RemoveRef() = 0;
    virtual void NotifyAdded(CpiDevice& aDevice) = 0;
    virtual void NotifyRemoved(CpiDevice& aDevice) = 0;
    virtual void NotifyRefreshed(CpDeviceMap& aRefreshMap) = 0;
};

/**
 * Protocol-independent list of devices
 *
 * This class is not intended for use outside this module.
 */
class CpiDeviceList : public IDeviceRemover, private IDeviceListUpdater, private IStackObject
{
public:
    virtual ~CpiDeviceList();

    /**
     * Start populating the list
     */
    virtual void Start() = 0;
    
    /**
     * Refresh the list of devices, making added/removed calls to the observer
     * only for devices that have changed from the list when this was called.
     * Implementations of this will almost certainly be asynchronous.
     */
    virtual void Refresh();

    /**
     * Return the device with the name matching aUdn (or NULL if no such device
     * is in the list).  Non-NULL devices are returned with an extra reference
     * claimed.  The caller is responsible for freeing this reference.
     */
    CpiDevice* RefDevice(const Brx& aUdn);

    /**
     * Add a device to the list.  Relies on aDevice being newly constructed
     * and having no references claimed.  If the device is already in the list
     * then aDevice will be deleted.
     */
    void Add(CpiDevice* aDevice);
protected:
    /**
     * Construct the list but don't start populating it yet.
     * Population is deferred until Start() is called.
     */
    CpiDeviceList(CpStack& aCpStack, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved);

    /**
     * Remove a device from the list.  Does nothing if aDevice is not in the list
     */
    void Remove(const Brx& aUdn);

    /**
     * Called when a device has been newly added to the list and returns whether
     * the device is ready for immediate use.
     *
     * By default, devices are assumed to be ready immediately.  Some protocols may
     * however need to perform additional, asynchronous, initialisation.  Such
     * protocols should return false here then call SetDeviceReady() when this
     * initialisation completes.
     */
    virtual TBool IsDeviceReady(CpiDevice& aDevice);

    /**
     * Like RefDevice() but does not lock the list.
     */
    CpiDevice* RefDeviceLocked(const Brx& aUdn);
    TBool StartRefresh();
    void RefreshComplete(TBool aReportRemoved);
    void CancelRefresh();

    /**
     * Must be called with the list unlocked and a reference held on aDevice
     */
    void SetDeviceReady(CpiDevice& aDevice);

    static void ClearMap(CpDeviceMap& aMap);
private:
    void AddRef();
    void RemoveRef();
    void NotifyAdded(CpiDevice& aDevice);
    void NotifyRemoved(CpiDevice& aDevice);
    TBool DoRemove(CpiDevice& aDevice);
    void NotifyRefreshed(CpDeviceMap& aRefreshMap);
private: // from IStackObject
    void ListObjectDetails() const;
protected:
    CpStack& iCpStack;
    TBool iActive; // true if Start() has been called
    TBool iRefreshing;
    CpDeviceMap iMap;
    CpDeviceMap iRefreshMap;
    std::vector<CpiDevice*> iPendingRemove;
    mutable OpenHome::Mutex iLock;
    OpenHome::Mutex iRefreshLock;
private:
    FunctorCpiDevice iAdded;
    FunctorCpiDevice iRemoved;
    Mutex iRefLock;
    TUint iRefCount;
    Semaphore iShutdownSem;
};

class CpiDeviceListUpdater : public Thread
{
public:
    CpiDeviceListUpdater();
    ~CpiDeviceListUpdater();
    void QueueAdded(IDeviceListUpdater& aUpdater, CpiDevice& aDevice);
    void QueueRemoved(IDeviceListUpdater& aUpdater, CpiDevice& aDevice);
    void QueueRefreshed(IDeviceListUpdater& aUpdater, CpDeviceMap& aRefreshMap);
private:
    class UpdateBase : private INonCopyable
    {
    public:
        virtual ~UpdateBase();
        virtual void Update() = 0;
    protected:
        UpdateBase(IDeviceListUpdater& aUpdater);
    protected:
        IDeviceListUpdater& iUpdater;
    };
    class UpdateAdded : public UpdateBase
    {
    public:
        UpdateAdded(IDeviceListUpdater& aUpdater, CpiDevice& aDevice);
        ~UpdateAdded();
    private:
        void Update();
    private:
        CpiDevice& iDevice;
    };
    class UpdateRemoved : public UpdateBase
    {
    public:
        UpdateRemoved(IDeviceListUpdater& aUpdater, CpiDevice& aDevice);
        ~UpdateRemoved();
    private:
        void Update();
    private:
        CpiDevice& iDevice;
    };
    class UpdateRefresh : public UpdateBase
    {
    public:
        UpdateRefresh(IDeviceListUpdater& aUpdater, CpDeviceMap& aRefreshMap);
    private:
        void Update();
    private:
        CpDeviceMap iRefreshMap;
    };
private:
    void Queue(UpdateBase* aUpdate);
    void Run();
private:
    OpenHome::Mutex iLock;
    std::list<UpdateBase*> iList;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPIDEVICE
