#ifndef HEADER_DVSERVERUPNP
#define HEADER_DVSERVERUPNP

// client is required to include the appropriate version (Std or Core) of DvDevice.h

namespace OpenHome {
namespace Net {

class DvDevice;
class DviServerUpnp;
class DvStack;
    
/**
 * UPnP device server.
 *
 * Publishes DvDevices as UPnP devices, serves UIs (depending on device configuration) and
 * manages subscriptions.  This works automatically across all active network interfaces.
 * One of these servers is setup automatically by the device stack.  This default instance
 * will be used automatically by all devices.
 * Additional servers should not be requried for normal use of the device stack.  They may
 * however be necessary for unusual * cases where a provider is required to make blocking
 * calls to a proxy.
 *
 * @ingroup Device
 */
class DvServerUpnp
{
public:
    /**
     * Constructor
     *
     * @param[in] aDvStack   Returned by UpnpLibrary::StartDv().
     */
    DvServerUpnp(DvStack& aDvStack);
    /**
     * Destructor
     *
     * Any devices previously added will no longer be contactable but will still need to
     * be manually destroyed.
     */
    ~DvServerUpnp();
    /**
     * Instruct a device to publish itself using (only) this server.
     *
     * @param[in] aDevice   Device to publish.  Device must be disabled when this is called.
     */
    void AddDevice(DvDevice& aDevice);
private:
    DviServerUpnp* iServer;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVSERVERUPNP
