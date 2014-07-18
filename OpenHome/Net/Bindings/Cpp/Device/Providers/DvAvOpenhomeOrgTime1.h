#ifndef HEADER_DVAVOPENHOMEORGTIME1CPP
#define HEADER_DVAVOPENHOMEORGTIME1CPP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

#include <string>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the av.openhome.org:Time:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgTime1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgTime1Cpp() {}
    /**
     * Set the value of the TrackCount property
     *
     * Can only be called if EnablePropertyTrackCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTrackCount(uint32_t aValue);
    /**
     * Get a copy of the value of the TrackCount property
     *
     * Can only be called if EnablePropertyTrackCount has previously been called.
     */
    void GetPropertyTrackCount(uint32_t& aValue);
    /**
     * Set the value of the Duration property
     *
     * Can only be called if EnablePropertyDuration has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyDuration(uint32_t aValue);
    /**
     * Get a copy of the value of the Duration property
     *
     * Can only be called if EnablePropertyDuration has previously been called.
     */
    void GetPropertyDuration(uint32_t& aValue);
    /**
     * Set the value of the Seconds property
     *
     * Can only be called if EnablePropertySeconds has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySeconds(uint32_t aValue);
    /**
     * Get a copy of the value of the Seconds property
     *
     * Can only be called if EnablePropertySeconds has previously been called.
     */
    void GetPropertySeconds(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgTime1Cpp(DvDeviceStd& aDevice);
    /**
     * Enable the TrackCount property.
     */
    void EnablePropertyTrackCount();
    /**
     * Enable the Duration property.
     */
    void EnablePropertyDuration();
    /**
     * Enable the Seconds property.
     */
    void EnablePropertySeconds();
    /**
     * Signal that the action Time is supported.
     * The action's availability will be published in the device's service.xml.
     * Time must be overridden if this is called.
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
    virtual void Time(IDvInvocationStd& aInvocation, uint32_t& aTrackCount, uint32_t& aDuration, uint32_t& aSeconds);
private:
    DvProviderAvOpenhomeOrgTime1Cpp();
    void DoTime(IDviInvocation& aInvocation);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGTIME1CPP

