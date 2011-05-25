#ifndef HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1
#define HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the openhome.org:TestDimmableLight:1 UPnP service
 * @ingroup Providers
 */
class DvProviderOpenhomeOrgTestDimmableLight1 : public DvProvider
{
public:
    virtual ~DvProviderOpenhomeOrgTestDimmableLight1() {}
    /**
     * Set the value of the A_ARG_Level property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyA_ARG_Level(TUint aValue);
    /**
     * Get a copy of the value of the A_ARG_Level property
     */
    void GetPropertyA_ARG_Level(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderOpenhomeOrgTestDimmableLight1(DvDevice& aDevice);
    /**
     * Signal that the action GetLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * GetLevel must be overridden if this is called.
     */
    void EnableActionGetLevel();
    /**
     * Signal that the action SetLevel is supported.
     * The action's availability will be published in the device's service.xml.
     * SetLevel must be overridden if this is called.
     */
    void EnableActionSetLevel();
private:
    /**
     * GetLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetLevel action for the owning device.
     * Must be implemented iff EnableActionGetLevel was called.
     */
    virtual void GetLevel(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aLevel);
    /**
     * SetLevel action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetLevel action for the owning device.
     * Must be implemented iff EnableActionSetLevel was called.
     */
    virtual void SetLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aLevel);
private:
    DvProviderOpenhomeOrgTestDimmableLight1();
    void DoGetLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetLevel(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyA_ARG_Level;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVOPENHOMEORGTESTDIMMABLELIGHT1

