#ifndef HEADER_DVAVOPENHOMEORGTIME1
#define HEADER_DVAVOPENHOMEORGTIME1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
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
class DvProviderAvOpenhomeOrgTime1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgTime1() {}
    /**
     * Set the value of the TrackCount property
     *
     * Can only be called if EnablePropertyTrackCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackCount(TUint aValue);
    /**
     * Get a copy of the value of the TrackCount property
     *
     * Can only be called if EnablePropertyTrackCount has previously been called.
     */
    void GetPropertyTrackCount(TUint& aValue);
    /**
     * Set the value of the Duration property
     *
     * Can only be called if EnablePropertyDuration has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDuration(TUint aValue);
    /**
     * Get a copy of the value of the Duration property
     *
     * Can only be called if EnablePropertyDuration has previously been called.
     */
    void GetPropertyDuration(TUint& aValue);
    /**
     * Set the value of the Seconds property
     *
     * Can only be called if EnablePropertySeconds has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySeconds(TUint aValue);
    /**
     * Get a copy of the value of the Seconds property
     *
     * Can only be called if EnablePropertySeconds has previously been called.
     */
    void GetPropertySeconds(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgTime1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgTime1(DviDevice& aDevice);
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
    virtual void Time(IDvInvocation& aInvocation, IDvInvocationResponseUint& aTrackCount, IDvInvocationResponseUint& aDuration, IDvInvocationResponseUint& aSeconds);
private:
    DvProviderAvOpenhomeOrgTime1();
    void Construct();
    void DoTime(IDviInvocation& aInvocation);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGTIME1

