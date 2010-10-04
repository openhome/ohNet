/**
 * List(s) of devices suitable for use in control points
 *
 * Cp prefixes show that classes are intended for use in control points
 * Route inside a name implies that a class requires one instance per network interface
 */

#ifndef HEADER_CPIDEVICE
#define HEADER_CPIDEVICE

#include <ZappTypes.h>
#include <Buffer.h>
#include <Thread.h>
#include <Discovery.h>
#include <Timer.h>
#include <FunctorCpiDevice.h>

#include <vector>
#include <map>

namespace Zapp {


class CpiDeviceList;
class Invocation;
class ServiceType;
class Subscription;
class Property;
class IPropertyProcessor;
typedef std::map<Brn,Property*,BufferCmp> PropertyMap;

/**
 * Protocol-independent device
 *
 * Instance of this class are reference counted and are automatically deleted
 * when the reference count falls to zero
 */
class CpiDevice
{
public:
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

    virtual TBool GetAttribute(const char* aKey, Brh& aValue) const = 0;
    virtual void Invoke(Invocation& aInvocation) = 0;
    virtual TUint Subscribe(Subscription& aSubscription, const Uri& aSubscriber) = 0;
    virtual TUint Renew(Subscription& aSubscription) = 0;
    virtual void Unsubscribe(Subscription& aSubscription, const Brx& aSid) = 0;
    virtual void ProcessPropertyNotification(const Brx& aNotification, PropertyMap& aProperties) = 0;

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
protected:
    /**
     * Sets the ref count to 1
     */
    CpiDevice(const Brx& aUdn);
    
    /**
     * Not intended for client use.  The call to RemoveRef() which reduces the
     * ref count to 0 will delete
     */
    virtual ~CpiDevice();
protected:
    Brhz iUdn;
    Mutex iLock;
private:
    TInt iRefCount;
    TBool iReady;
    TBool iExpired;

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

/**
 * Protocol-independent list of devices
 *
 * This class is not intended for use outside this module.
 */
class CpiDeviceList : public IDeviceRemover
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
protected:
    /**
     * Construct the list but don't start populating it yet.
     * Population is deferred until Start() is called.
     */
    CpiDeviceList(FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved);

    /**
     * Add a device to the list.  Relies on aDevice being newly constructed
     * and having no references claimed.  If the device is already in the list
     * then aDevice will be deleted.
     */
    void Add(CpiDevice* aDevice);

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
    void RefreshComplete();

    /**
     * Must be called with the list unlocked and a reference held on aDevice
     */
    void SetDeviceReady(CpiDevice& aDevice);

    typedef std::map<Brn,CpiDevice*,BufferCmp> Map;
    static void ClearMap(Map& aMap);
protected:
    TBool iActive; // true if Start() has been called
    TBool iRefreshing;
    Map iMap;
    Map iRefreshMap;
    mutable Mutex iLock;
private:
    FunctorCpiDevice iAdded;
    FunctorCpiDevice iRemoved;
};

} // namespace Zapp

#endif // HEADER_CPIDEVICE
