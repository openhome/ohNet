#ifndef HEADER_DVLINNCOUKPRODUCT2CPP
#define HEADER_DVLINNCOUKPRODUCT2CPP

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
 * Base Device for linn.co.uk:Product:2
 */
class DvServiceLinnCoUkProduct2Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkProduct2Cpp() {}
    void SetPropertyProductName(const std::string& aValue);
    void GetPropertyProductName(std::string& aValue);
    void SetPropertyProductRoom(const std::string& aValue);
    void GetPropertyProductRoom(std::string& aValue);
    void SetPropertyProductStandby(bool aValue);
    void GetPropertyProductStandby(bool& aValue);
    void SetPropertyProductSourceIndex(uint32_t aValue);
    void GetPropertyProductSourceIndex(uint32_t& aValue);
protected:
    DvServiceLinnCoUkProduct2Cpp(DvDeviceStd& aDevice);
    void EnableActionType();
    void EnableActionModel();
    void EnableActionName();
    void EnableActionSetName();
    void EnableActionRoom();
    void EnableActionSetRoom();
    void EnableActionStandby();
    void EnableActionSetStandby();
    void EnableActionSourceCount();
    void EnableActionSourceIndex();
    void EnableActionSetSourceIndex();
    void EnableActionSourceType();
private:
    virtual void Type(uint32_t aVersion, std::string& aaType);
    virtual void Model(uint32_t aVersion, std::string& aaModel);
    virtual void Name(uint32_t aVersion, std::string& aaName);
    virtual void SetName(uint32_t aVersion, const std::string& aaName);
    virtual void Room(uint32_t aVersion, std::string& aaRoom);
    virtual void SetRoom(uint32_t aVersion, const std::string& aaRoom);
    virtual void Standby(uint32_t aVersion, bool& aaStandby);
    virtual void SetStandby(uint32_t aVersion, bool aaStandby);
    virtual void SourceCount(uint32_t aVersion, uint32_t& aaSourceCount);
    virtual void SourceIndex(uint32_t aVersion, uint32_t& aaSourceIndex);
    virtual void SetSourceIndex(uint32_t aVersion, uint32_t aaSourceIndex);
    virtual void SourceType(uint32_t aVersion, uint32_t aaSourceIndex, std::string& aaSourceType);
private:
    DvServiceLinnCoUkProduct2Cpp();
    void DoType(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoModel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoRoom(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetRoom(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStandby(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStandby(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceCount(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceIndex(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceIndex(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceType(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductRoom;
    PropertyBool* iPropertyProductStandby;
    PropertyUint* iPropertyProductSourceIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT2CPP

