#ifndef HEADER_DVLINNCOUKPRODUCT2CPP
#define HEADER_DVLINNCOUKPRODUCT2CPP

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
 * Base Device for linn.co.uk:Product:2
 */
class DvProviderLinnCoUkProduct2Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct2Cpp() {}
    bool SetPropertyProductName(const std::string& aValue);
    void GetPropertyProductName(std::string& aValue);
    bool SetPropertyProductRoom(const std::string& aValue);
    void GetPropertyProductRoom(std::string& aValue);
    bool SetPropertyProductStandby(bool aValue);
    void GetPropertyProductStandby(bool& aValue);
    bool SetPropertyProductSourceIndex(uint32_t aValue);
    void GetPropertyProductSourceIndex(uint32_t& aValue);
protected:
    DvProviderLinnCoUkProduct2Cpp(DvDeviceStd& aDevice);
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
    DvProviderLinnCoUkProduct2Cpp();
    void DoType(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoModel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStandby(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceCount(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceType(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductRoom;
    PropertyBool* iPropertyProductStandby;
    PropertyUint* iPropertyProductSourceIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT2CPP

