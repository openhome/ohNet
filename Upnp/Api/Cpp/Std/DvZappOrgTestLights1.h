#ifndef HEADER_DVZAPPORGTESTLIGHTS1CPP
#define HEADER_DVZAPPORGTESTLIGHTS1CPP

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
 * Base Device for zapp.org:TestLights:1
 */
class DvServiceZappOrgTestLights1Cpp : public DvService
{
public:
    virtual ~DvServiceZappOrgTestLights1Cpp() {}
protected:
    DvServiceZappOrgTestLights1Cpp(DvDeviceStd& aDevice);
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
    DvServiceZappOrgTestLights1Cpp();
    void DoGetCount(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetRoom(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetPosition(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetColor(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetColor(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetColorComponents(IDvInvocation& aInvocation, uint32_t aVersion);
private:
};

} // namespace Zapp

#endif // HEADER_DVZAPPORGTESTLIGHTS1CPP

