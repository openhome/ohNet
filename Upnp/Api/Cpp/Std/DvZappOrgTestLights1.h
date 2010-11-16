#ifndef HEADER_DVZAPPORGTESTLIGHTS1CPP
#define HEADER_DVZAPPORGTESTLIGHTS1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

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
class DvProviderZappOrgTestLights1Cpp : public DvProvider
{
public:
    virtual ~DvProviderZappOrgTestLights1Cpp() {}
protected:
    DvProviderZappOrgTestLights1Cpp(DvDeviceStd& aDevice);
    void EnableActionGetCount();
    void EnableActionGetRoom();
    void EnableActionGetName();
    void EnableActionGetPosition();
    void EnableActionSetColor();
    void EnableActionGetColor();
    void EnableActionGetColorComponents();
private:
    virtual void GetCount(uint32_t aVersion, uint32_t& aCount);
    virtual void GetRoom(uint32_t aVersion, uint32_t aIndex, std::string& aRoomName);
    virtual void GetName(uint32_t aVersion, uint32_t aIndex, std::string& aFriendlyName);
    virtual void GetPosition(uint32_t aVersion, uint32_t aIndex, uint32_t& aX, uint32_t& aY, uint32_t& aZ);
    virtual void SetColor(uint32_t aVersion, uint32_t aIndex, uint32_t aColor);
    virtual void GetColor(uint32_t aVersion, uint32_t aIndex, uint32_t& aColor);
    virtual void GetColorComponents(uint32_t aVersion, uint32_t aColor, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
private:
    DvProviderZappOrgTestLights1Cpp();
    void DoGetCount(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetPosition(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetColor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetColor(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetColorComponents(IDviInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTLIGHTS1CPP

