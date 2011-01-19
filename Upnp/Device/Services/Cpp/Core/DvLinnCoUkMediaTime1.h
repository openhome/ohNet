#ifndef HEADER_DVLINNCOUKMEDIATIME1
#define HEADER_DVLINNCOUKMEDIATIME1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

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
class DvProviderLinnCoUkMediaTime1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkMediaTime1() {}
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
    DvProviderLinnCoUkMediaTime1(DvDevice& aDevice);
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
    virtual void Seconds(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSeconds);
private:
    DvProviderLinnCoUkMediaTime1();
    void DoSeconds(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertySeconds;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKMEDIATIME1

