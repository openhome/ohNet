#ifndef HEADER_DVLINNCOUKTIME1CPP
#define HEADER_DVLINNCOUKTIME1CPP

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
 * Provider for the linn.co.uk:Time:1 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkTime1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkTime1Cpp() {}
    /**
     * Set the value of the TrackCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackCount(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackCount property
     */
    void GetPropertyTrackCount(uint32_t& aValue);
    /**
     * Set the value of the Duration property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDuration(uint32_t aValue);
    /**
     * Get a copy of the value of the Duration property
     */
    void GetPropertyDuration(uint32_t& aValue);
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
    DvProviderLinnCoUkTime1Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Time is supported.
     * The action's availability will be published in the device's service.xml.
     * DoTime must be overridden if this is called.
     */
    void EnableActionTime();
private:
    /**
     * Time action.
     *
     * Will be called when the device stack receives an invocation of the
     * Time action for the owning device.
     * Must be implemented iff EnableActionTime was called.
     */
    virtual void Time(uint32_t aVersion, uint32_t& aaTrackCount, uint32_t& aaDuration, uint32_t& aaSeconds);
private:
    DvProviderLinnCoUkTime1Cpp();
    void DoTime(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKTIME1CPP

