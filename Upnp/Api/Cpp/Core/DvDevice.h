#ifndef HEADER_DVDEVICE
#define HEADER_DVDEVICE

#include <ZappTypes.h>
#include <Buffer.h>
#include <Functor.h>
#include <DvResourceWriter.h>

namespace Zapp {

/**
 * Interface used by devices to publish data (typically files).
 * @ingroup Device
 */
class IResourceManager
{
public:
    virtual ~IResourceManager() {}
    virtual void WriteResource(const Brx& aUriTail, TIpAddress aInterface, IResourceWriter& aResourceWriter) = 0;
};

class DviDevice;
/**
 * Device
 *
 * Has a universally unique name and operates on 0..n protocols.
 * Services are added by constructing DvProvider derived classes, passing a reference to a
 * DvDevice to their c'tor
 * @ingroup Device
 */
class DllExportClass DvDevice
{
public:
    /**
     * Constructor.  Creates a device capable of serving UI files and of operating on any of the
     * protocols the device stack supports but with no services or attributes as yet
     *
     * @param[in] aUdn    Universally unique identifier.  The caller is responsible for
     *                    calculating/assigning this
     */
    DvDevice(const Brx& aUdn);
    /**
     * Constructor.  Creates a device capable of operating on any of the protocols the device
     * stack supports but with no services or attributes as yet
     *
     * @param[in] aUdn    Universally unique identifier.  The caller is responsible for
     *                    calculating/assigning this
     * @param[in] aResourceManager  Allows the owner of a device to serve UI files
     */
    DvDevice(const Brx& aUdn, IResourceManager& aResourceManager);
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
    /**
     * Add a block of xml which will be returned as part of the device description
     *
     * Use is limited to UPnP for now.  Xml is returned with device xml inside the <device>
     * tag (at the same level as most attributes)
     *
     * @param[in] aXml  One or more tag+value blocks
     */
    void SetXmlExtension(const TChar* aXml);
private:
    DviDevice* iDevice;
};

} // namespace Zapp

#endif // HEADER_DVDEVICE
