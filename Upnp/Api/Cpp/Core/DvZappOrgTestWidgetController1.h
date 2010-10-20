#ifndef HEADER_DVZAPPORGTESTWIDGETCONTROLLER1
#define HEADER_DVZAPPORGTESTWIDGETCONTROLLER1

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
 * Base Device for zapp.org:TestWidgetController:1
 */
class DvServiceZappOrgTestWidgetController1 : public DvService
{
public:
    virtual ~DvServiceZappOrgTestWidgetController1() {}
protected:
    DvServiceZappOrgTestWidgetController1(DvDevice& aDevice);
    void EnableActionCreateWidget();
    void EnableActionRemoveWidget();
    void EnableActionSetWidgetRegister();
private:
    virtual void CreateWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn);
    virtual void RemoveWidget(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn);
    virtual void SetWidgetRegister(IInvocationResponse& aResponse, TUint aVersion, const Brx& aWidgetUdn, TUint aRegisterIndex, TUint aRegisterValue);
private:
    DvServiceZappOrgTestWidgetController1();
    void DoCreateWidget(IDvInvocation& aInvocation, TUint aVersion);
    void DoRemoveWidget(IDvInvocation& aInvocation, TUint aVersion);
    void DoSetWidgetRegister(IDvInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTWIDGETCONTROLLER1

