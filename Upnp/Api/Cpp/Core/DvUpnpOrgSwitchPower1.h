#ifndef HEADER_DVUPNPORGSWITCHPOWER1
#define HEADER_DVUPNPORGSWITCHPOWER1

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
 * Base Device for upnp.org:SwitchPower:1
 */
class DvProviderUpnpOrgSwitchPower1 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgSwitchPower1() {}
    TBool SetPropertyStatus(TBool aValue);
    void GetPropertyStatus(TBool& aValue);
protected:
    DvProviderUpnpOrgSwitchPower1(DvDevice& aDevice);
    void EnableActionSetTarget();
    void EnableActionGetTarget();
    void EnableActionGetStatus();
private:
    virtual void SetTarget(IInvocationResponse& aResponse, TUint aVersion, TBool anewTargetValue);
    virtual void GetTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aRetTargetValue);
    virtual void GetStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aResultStatus);
private:
    DvProviderUpnpOrgSwitchPower1();
    void DoSetTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTarget(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStatus(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyBool* iPropertyStatus;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGSWITCHPOWER1

