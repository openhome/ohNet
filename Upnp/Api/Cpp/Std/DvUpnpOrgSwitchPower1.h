#ifndef HEADER_DVUPNPORGSWITCHPOWER1CPP
#define HEADER_DVUPNPORGSWITCHPOWER1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:SwitchPower:1
 */
class DvServiceUpnpOrgSwitchPower1Cpp : public DvService
{
public:
    virtual ~DvServiceUpnpOrgSwitchPower1Cpp() {}
    void SetPropertyStatus(bool aValue);
    void GetPropertyStatus(bool& aValue);
protected:
    DvServiceUpnpOrgSwitchPower1Cpp(DvDeviceStd& aDevice);
    void EnableActionSetTarget();
    void EnableActionGetTarget();
    void EnableActionGetStatus();
private:
    virtual void SetTarget(uint32_t aVersion, bool anewTargetValue);
    virtual void GetTarget(uint32_t aVersion, bool& aRetTargetValue);
    virtual void GetStatus(uint32_t aVersion, bool& aResultStatus);
private:
    DvServiceUpnpOrgSwitchPower1Cpp();
    void DoSetTarget(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetTarget(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetStatus(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyBool* iPropertyStatus;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGSWITCHPOWER1CPP

