#ifndef HEADER_DVUPNPORGSWITCHPOWER1
#define HEADER_DVUPNPORGSWITCHPOWER1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:SwitchPower:1
 */
class DvServiceUpnpOrgSwitchPower1 : public DvService
{
public:
    virtual ~DvServiceUpnpOrgSwitchPower1() {}
    void SetPropertyStatus(TBool aValue);
    void GetPropertyStatus(TBool& aValue);
protected:
    DvServiceUpnpOrgSwitchPower1(DvDevice& aDevice);
    void EnableActionSetTarget();
    void EnableActionGetTarget();
    void EnableActionGetStatus();
private:
    virtual void SetTarget(IInvocationResponse& aResponse, TUint aVersion, TBool anewTargetValue);
    virtual void GetTarget(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aRetTargetValue);
    virtual void GetStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aResultStatus);
private:
    DvServiceUpnpOrgSwitchPower1();
    void DoSetTarget(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetTarget(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetStatus(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyBool* iPropertyStatus;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGSWITCHPOWER1

