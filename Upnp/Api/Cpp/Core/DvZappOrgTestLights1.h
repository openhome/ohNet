#ifndef HEADER_DVZAPPORGTESTLIGHTS1
#define HEADER_DVZAPPORGTESTLIGHTS1

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
 * Base Device for zapp.org:TestLights:1
 */
class DvProviderZappOrgTestLights1 : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestLights1() {}
protected:
    DvProviderZappOrgTestLights1(DvDevice& aDevice);
    void EnableActionGetCount();
    void EnableActionGetRoom();
    void EnableActionGetName();
    void EnableActionGetPosition();
    void EnableActionSetColor();
    void EnableActionGetColor();
    void EnableActionGetColorComponents();
private:
    virtual void GetCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aCount);
    virtual void GetRoom(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aRoomName);
    virtual void GetName(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseString& aFriendlyName);
    virtual void GetPosition(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseUint& aX, IInvocationResponseUint& aY, IInvocationResponseUint& aZ);
    virtual void SetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, TUint aColor);
    virtual void GetColor(IInvocationResponse& aResponse, TUint aVersion, TUint aIndex, IInvocationResponseUint& aColor);
    virtual void GetColorComponents(IInvocationResponse& aResponse, TUint aVersion, TUint aColor, IInvocationResponseUint& aBrightness, IInvocationResponseUint& aRed, IInvocationResponseUint& aGreen, IInvocationResponseUint& aBlue);
private:
    DvProviderZappOrgTestLights1();
    void DoGetCount(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetPosition(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetColor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetColor(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetColorComponents(IDviInvocation& aInvocation, TUint aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTLIGHTS1

