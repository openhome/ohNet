#ifndef HEADER_DVLINNCOUKMEDIATIME1CPP
#define HEADER_DVLINNCOUKMEDIATIME1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the linn.co.uk:MediaTime:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkMediaTime1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkMediaTime1Cpp() {}
    /**
     * Set the value of the Seconds property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySeconds(uint32_t aValue);
    /**
     * Get a copy of the value of the Seconds property
     */
    void GetPropertySeconds(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkMediaTime1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Seconds is supported.
     * The action's availability will be published in the device's service.xml.
     * Seconds must be overridden if this is called.
     */
    void EnableActionSeconds();
private:
    /**
     * Seconds action.
     *
     * Will be called when the device stack receives an invocation of the
     * Seconds action for the owning device.
     * Must be implemented iff EnableActionSeconds was called.
     */
    virtual void Seconds(uint32_t aVersion, uint32_t& aaSeconds);
private:
    DvProviderLinnCoUkMediaTime1Cpp();
    void DoSeconds(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKMEDIATIME1CPP

