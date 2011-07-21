#ifndef HEADER_DVAVOPENHOMEORGTIME1
#define HEADER_DVAVOPENHOMEORGTIME1

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

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
class DvProviderAvOpenhomeOrgTime1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgTime1() {}
    /**
     * Set the value of the TrackCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTrackCount(TUint aValue);
    /**
     * Get a copy of the value of the TrackCount property
     */
    void GetPropertyTrackCount(TUint& aValue);
    /**
     * Set the value of the Duration property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyDuration(TUint aValue);
    /**
     * Get a copy of the value of the Duration property
     */
    void GetPropertyDuration(TUint& aValue);
    /**
     * Set the value of the Seconds property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySeconds(TUint aValue);
    /**
     * Get a copy of the value of the Seconds property
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
    virtual void Time(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aTrackCount, IInvocationResponseUint& aDuration, IInvocationResponseUint& aSeconds);
private:
    DvProviderAvOpenhomeOrgTime1();
    void DoTime(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyTrackCount;
    PropertyUint* iPropertyDuration;
    PropertyUint* iPropertySeconds;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGTIME1

