#ifndef HEADER_DVLINNCOUKPRODUCT1CPP
#define HEADER_DVLINNCOUKPRODUCT1CPP

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
 * Base Device for linn.co.uk:Product:1
 */
class DvServiceLinnCoUkProduct1Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkProduct1Cpp() {}
    void SetPropertyRoom(const std::string& aValue);
    void GetPropertyRoom(std::string& aValue);
    void SetPropertyStandby(bool aValue);
    void GetPropertyStandby(bool& aValue);
protected:
    DvServiceLinnCoUkProduct1Cpp(DvDeviceStd& aDevice);
    void EnableActionRoom();
    void EnableActionSetRoom();
    void EnableActionStandby();
    void EnableActionSetStandby();
private:
    virtual void Room(uint32_t aVersion, std::string& aaRoom);
    virtual void SetRoom(uint32_t aVersion, const std::string& aaRoom);
    virtual void Standby(uint32_t aVersion, bool& aaStandby);
    virtual void SetStandby(uint32_t aVersion, bool aaStandby);
private:
    DvServiceLinnCoUkProduct1Cpp();
    void DoRoom(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetRoom(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStandby(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStandby(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyRoom;
    PropertyBool* iPropertyStandby;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT1CPP

