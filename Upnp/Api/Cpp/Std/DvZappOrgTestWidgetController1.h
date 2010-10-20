#ifndef HEADER_DVZAPPORGTESTWIDGETCONTROLLER1CPP
#define HEADER_DVZAPPORGTESTWIDGETCONTROLLER1CPP

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
 * Base Device for zapp.org:TestWidgetController:1
 */
class DvServiceZappOrgTestWidgetController1Cpp : public DvService
{
public:
    virtual ~DvServiceZappOrgTestWidgetController1Cpp() {}
protected:
    DvServiceZappOrgTestWidgetController1Cpp(DvDeviceStd& aDevice);
    void EnableActionCreateWidget();
    void EnableActionRemoveWidget();
    void EnableActionSetWidgetRegister();
private:
    virtual void CreateWidget(uint32_t aVersion, const std::string& aWidgetUdn);
    virtual void RemoveWidget(uint32_t aVersion, const std::string& aWidgetUdn);
    virtual void SetWidgetRegister(uint32_t aVersion, const std::string& aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue);
private:
    DvServiceZappOrgTestWidgetController1Cpp();
    void DoCreateWidget(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoRemoveWidget(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetWidgetRegister(IDvInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTWIDGETCONTROLLER1CPP

