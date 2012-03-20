#ifndef HEADER_CPDEVICECPP
#define HEADER_CPDEVICECPP

#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/FunctorCpDevice.h>

#include <string>
#include <map>

namespace OpenHome {
class Mutex;
namespace Net {

class CpiDevice;
/**
 * Protocol-independent device
 *
 * Instance of this class are reference counted and are automatically deleted
 * when the reference count falls to zero
 * @ingroup ControlPoint
 */
class CpDeviceCpp
{
public:
    /**
     * Query the unique identifier associated with a device
     *
     * @return  Reference to the device's (universally unique) name
     */
    const std::string& Udn() const;
    TBool operator==(const CpDeviceCpp& aDevice) const;
    TBool operator!=(const CpDeviceCpp& aDevice) const;
    /**
     * Claim a reference to a device.
     * Can only be called from code that can guarantee another reference is already held.
     * Each call to AddRef() must later have exactly one matching call to RemoveRef().
     */
    void AddRef();
    /**
     * Remove a reference to a device.
     * Removing the final reference causes a device to be deleted.
     */
    void RemoveRef();
    /**
     * Query the value of one of the device's attributes
     *
     * @param[in]  aKey    The name of the attribute being queried.  Available attributes
     *                     will be listed in a protocol-specific header
     * @param[out] aValue  The value of the attribute
     *
     * @return  true if the attribute was available on the device; false otherwise
     *          aValue will not have been set if false is returned
     */
    TBool GetAttribute(const char* aKey, std::string& aValue) const;
    /**
     * Not intended for external use
     */
    CpiDevice& Device();
protected:
    /**
     * Constructor. Not intended for external use.
     * Devices should be constructed via CpDeviceCpp or CpDeviceListCpp subclasses.
     */
    CpDeviceCpp(CpiDevice& aDevice);
    virtual ~CpDeviceCpp();
private:
    CpDeviceCpp(const CpDeviceCpp&);
    void operator=(const CpDeviceCpp&);
    friend class CpDeviceListCpp;
private:
    CpiDevice& iDevice;
    std::string iUdn;
    uint32_t iRefCount;
};

class CpiDeviceList;
class FunctorCpiDevice;
/**
 * List of devices available on the current subnet
 *
 * Runs callbacks when a device is detected on or removed from a network.
 * Clients can't iterate the list's contents so must take note of the device in their 'added'
 * callback and remove the device in their 'removed' callback.
 * Since CpDevice instances are reference counted, a reference must be claimed inside the
 * 'added' callback and removed inside the 'removed' callback.
 *
 * This class can't be directly instantiated.  Clients should instead use subclasses which
 * will define policy on how to detect devices etc.
 * @ingroup ControlPoint
 */
class CpDeviceListCpp
{
public:
    virtual ~CpDeviceListCpp();
    /**
     * Refresh the contents of the list.
     *
     * This may be a useful way to quickly update a list after a device has been removed
     * abruptly from the network (without announcing its removal).
     *
     * The 'added' callback may run any time after this is called to notify new devices.
     * Any removed devices will be notified by a burst of calls to the 'removed' callback
     * InitialisationParams::MsearchTimeSecs() seconds after this call is made.
     * There is no notification that a refresh has completed.  Existing CpDevice instances
     * can be used as normal throughout the refresh.
     */
    void Refresh();
protected:
    /**
     * Constructor
     *
     * @param[in] aAdded    Callback which will be run when a new device is detected
     *                      Clients who are interested this new device should call AddRef()
     *                      on it and add it to some local collection.
     *                      This callback will never be run for a device that is already in the list.
     * @param[in] aRemoved  Callback which will be run when a device is removed from the network
     *                      Clients who had previously stored a reference to the device in their
     *                      aAdded callback should call RemoveRef() and remove the device from
     *                      their local collection.  Clients who had not previously claimed a
     *                      reference to a device must not call ReleaseRef().
     */
    CpDeviceListCpp(FunctorCpDeviceCpp aAdded, FunctorCpDeviceCpp aRemoved);
    /**
     * Not intended for external use
     */
    void GetAddedFunctor(FunctorCpiDevice& aFunctor);
    /**
     * Not intended for external use
     */
    void GetRemovedFunctor(FunctorCpiDevice& aFunctor);
private:
    void Added(CpiDevice& aDevice);
    void Removed(CpiDevice& aDevice);
    TBool LockIfActive();
protected:
    CpiDeviceList* iList;
private:
    typedef std::map<Brn,CpDeviceCpp*,BufferCmp> Map;
    Map iMap;
    FunctorCpDeviceCpp iAdded;
    FunctorCpDeviceCpp iRemoved;
    Mutex* iLock;
    TBool iActive;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPDEVICECPP
