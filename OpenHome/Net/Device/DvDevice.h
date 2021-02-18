#ifndef HEADER_DVDEVICE
#define HEADER_DVDEVICE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/DvResourceWriter.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>

namespace OpenHome {
namespace Net {

/**
 * Interface used by devices to publish data (typically files).
 * @ingroup Device
 */
class IResourceManager
{
public:
    virtual ~IResourceManager() {}
    virtual void WriteResource(const Brx& aUriTail, const TIpAddress& aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter) = 0;
};

class DviDevice;
class DvStack;
/**
 * Device
 *
 * Has a universally unique name.  Does not operate on any protocols itself but can be extended
 * by sub-classes to add support for various protocols.
 * Lack of protocol support makes this class unsuitable for most use cases but it may be useful for
 * CpDeviceDv (where a control point device communicates directly with a DvDevice) and related classes.
 * Services are added by constructing DvProvider derived classes, passing a reference to a
 * DvDevice to their c'tor
 * @ingroup Device
 */
class DllExportClass DvDevice
{
public:
    /**
     * Constructor.  Creates a device ready to have services or attributes added.
     * Addition of any protocols to operate over is the responsibility of any sub-classes.
     *
     * @param[in] aDvStack  Returned from UpnpLibrary::StartDv().
     * @param[in] aUdn      Universally unique identifier.  The caller is responsible for
     *                      calculating/assigning this
     */
    DvDevice(DvStack& aDvStack, const Brx& aUdn);
    /**
     * Destructor.  Can be called regardless of whether the device is enabled or disabled.
     */
    ~DvDevice();
    /**
     * Not intended for external use
     */
    DllExport DviDevice& Device();
    /**
     * Query the (client-specified) unique device name
     *
     * @return  The name passed to the c'tor
     */
    const Brx& Udn() const;
    /**
     * Query whether a device is enabled
     *
     * @return  true if the device is enabled; false otherwise
     */
    TBool Enabled() const;
    /**
     * Set the device ready for external use
     *
     * When this returns, the device will be available for use using any of the protocols
     * the device stack supports.  Services must not be added (DvProvider-derived classes
     * created using this device) and attributes must not be set while a device is enabled.
     * If these need to change in future, the device must first be disabled.
     */
    void SetEnabled();
    /**
     * Disable the device, withdrawing its availability for external use
     *
     * Services can be added and attributes can be set once a device is disabled.  The device
     * will not be available for use again until SetEnabled() is called again.
     * This call is asynchronous so returns before the device is fully disabled.  Wait for the
     * aCompleted callback before adding services or setting attributes.
     *
     * @param[in] aCompleted  Callback which runs when the device is fully disabled.
     *                        Until this runs, the device should be considered to still be enabled.
     */
    void SetDisabled(Functor aCompleted);
    /**
     * Query the value of an atrribute
     *
     * @param[in]  aKey    string of the form protocol_name.protocol_specific_key
     *                     Commonly used keys are published ... (!!!! where?)
     * @param[out] aValue  const pointer to the attribute or NULL if the attribute has not been set.
     */
    void GetAttribute(const TChar* aKey, const TChar** aValue) const;
    /**
     * Set the value of an attribute
     *
     * @param[in] aKey    string of the form protocol_name.protocol_specific_key
     * @param[in] aValue  attribute will be set to a copy of this string
     */
    void SetAttribute(const TChar* aKey, const TChar* aValue);
protected:
    DvDevice();
protected:
    DviDevice* iDevice;
};

/**
 * Device
 *
 * Has a universally unique name and on all the protocols the device stack supports as standard.
 * Services are added by constructing DvProvider derived classes, passing a reference to a
 * DvDevice to their c'tor
 * @ingroup Device
 */
class DvDeviceStandard : public DvDevice
{
public:
    /**
     * Constructor.  Creates a device capable of operating on any of the protocols the device
     * stack supports as standard but with no services or attributes as yet
     *
     * @param[in] aDvStack  Returned from UpnpLibrary::StartDv().
     * @param[in] aUdn      Universally unique identifier.  The caller is responsible for
     *                      calculating/assigning this
     */
    DvDeviceStandard(DvStack& aDvStack, const Brx& aUdn);
    /**
     * Constructor.  Creates a device capable of serving UI files and of operating on any of the
     * protocols the device stack supports as standard but with no services or attributes as yet
     *
     * @param[in] aDvStack  Returned from UpnpLibrary::StartDv().
     * @param[in] aUdn      Universally unique identifier.  The caller is responsible for
     *                      calculating/assigning this
     * @param[in] aResourceManager  Allows the owner of a device to serve UI files
     */
    DvDeviceStandard(DvStack& aDvStack, const Brx& aUdn, IResourceManager& aResourceManager);
    /**
     * Query the base uri for the resource manager.
     *
     * @param[in]  aAdapter  the network adapter to return a uri for.
     * @param[out] aUri      the base uri.  May be zero length if there is no resource manager.
     */
    void GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVDEVICE
