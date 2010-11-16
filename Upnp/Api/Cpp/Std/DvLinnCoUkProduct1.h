#ifndef HEADER_DVLINNCOUKPRODUCT1CPP
#define HEADER_DVLINNCOUKPRODUCT1CPP

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
 * Base Device for linn.co.uk:Product:1
 */
class DvProviderLinnCoUkProduct1Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct1Cpp() {}
    bool SetPropertyRoom(const std::string& aValue);
    void GetPropertyRoom(std::string& aValue);
    bool SetPropertyStandby(bool aValue);
    void GetPropertyStandby(bool& aValue);
protected:
    DvProviderLinnCoUkProduct1Cpp(DvDeviceStd& aDevice);
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
    DvProviderLinnCoUkProduct1Cpp();
    void DoRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStandby(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyRoom;
    PropertyBool* iPropertyStandby;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT1CPP

