#ifndef HEADER_DVLINNCOUKPRODUCT3CPP
#define HEADER_DVLINNCOUKPRODUCT3CPP

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
 * Base Device for linn.co.uk:Product:3
 */
class DvServiceLinnCoUkProduct3Cpp : public DvService
{
public:
    virtual ~DvServiceLinnCoUkProduct3Cpp() {}
    void SetPropertyProductType(const std::string& aValue);
    void GetPropertyProductType(std::string& aValue);
    void SetPropertyProductModel(const std::string& aValue);
    void GetPropertyProductModel(std::string& aValue);
    void SetPropertyProductName(const std::string& aValue);
    void GetPropertyProductName(std::string& aValue);
    void SetPropertyProductRoom(const std::string& aValue);
    void GetPropertyProductRoom(std::string& aValue);
    void SetPropertyProductStandby(bool aValue);
    void GetPropertyProductStandby(bool& aValue);
    void SetPropertyProductSourceIndex(uint32_t aValue);
    void GetPropertyProductSourceIndex(uint32_t& aValue);
    void SetPropertyProductSourceCount(uint32_t aValue);
    void GetPropertyProductSourceCount(uint32_t& aValue);
    void SetPropertyProductSourceXml(const std::string& aValue);
    void GetPropertyProductSourceXml(std::string& aValue);
    void SetPropertyStartupSourceIndex(uint32_t aValue);
    void GetPropertyStartupSourceIndex(uint32_t& aValue);
    void SetPropertyStartupSourceEnabled(bool aValue);
    void GetPropertyStartupSourceEnabled(bool& aValue);
    void SetPropertyProductAnySourceName(uint32_t aValue);
    void GetPropertyProductAnySourceName(uint32_t& aValue);
    void SetPropertyProductAnySourceVisible(uint32_t aValue);
    void GetPropertyProductAnySourceVisible(uint32_t& aValue);
    void SetPropertyProductAnySourceType(uint32_t aValue);
    void GetPropertyProductAnySourceType(uint32_t& aValue);
protected:
    DvServiceLinnCoUkProduct3Cpp(DvDeviceStd& aDevice);
    void EnableActionType();
    void EnableActionModel();
    void EnableActionName();
    void EnableActionSetName();
    void EnableActionRoom();
    void EnableActionSetRoom();
    void EnableActionStandby();
    void EnableActionSetStandby();
    void EnableActionSourceCount();
    void EnableActionSourceXml();
    void EnableActionSourceIndex();
    void EnableActionSetSourceIndex();
    void EnableActionSetSourceIndexByName();
    void EnableActionSetStartupSourceIndexByName();
    void EnableActionStartupSourceIndex();
    void EnableActionSetStartupSourceIndex();
    void EnableActionStartupSourceEnabled();
    void EnableActionSetStartupSourceEnabled();
    void EnableActionSourceSystemName();
    void EnableActionSourceName();
    void EnableActionSetSourceName();
    void EnableActionSourceType();
    void EnableActionSourceVisible();
    void EnableActionSetSourceVisible();
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
    virtual void SourceXml(uint32_t aVersion, std::string& aaSourceXml);
    virtual void SourceIndex(uint32_t aVersion, uint32_t& aaSourceIndex);
    virtual void SetSourceIndex(uint32_t aVersion, uint32_t aaSourceIndex);
    virtual void SetSourceIndexByName(uint32_t aVersion, const std::string& aaSourceName);
    virtual void SetStartupSourceIndexByName(uint32_t aVersion, const std::string& aaSourceName);
    virtual void StartupSourceIndex(uint32_t aVersion, uint32_t& aaSourceIndex);
    virtual void SetStartupSourceIndex(uint32_t aVersion, uint32_t aaSourceIndex);
    virtual void StartupSourceEnabled(uint32_t aVersion, bool& aaStartupSourceEnabled);
    virtual void SetStartupSourceEnabled(uint32_t aVersion, bool aaStartupSourceEnabled);
    virtual void SourceSystemName(uint32_t aVersion, uint32_t aaSourceIndex, std::string& aaSourceName);
    virtual void SourceName(uint32_t aVersion, uint32_t aaSourceIndex, std::string& aaSourceName);
    virtual void SetSourceName(uint32_t aVersion, uint32_t aaSourceIndex, const std::string& aaSourceName);
    virtual void SourceType(uint32_t aVersion, uint32_t aaSourceIndex, std::string& aaSourceType);
    virtual void SourceVisible(uint32_t aVersion, uint32_t aaSourceIndex, bool& aaSourceVisible);
    virtual void SetSourceVisible(uint32_t aVersion, uint32_t aaSourceIndex, bool aaSourceVisible);
private:
    DvServiceLinnCoUkProduct3Cpp();
    void DoType(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoModel(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoRoom(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetRoom(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStandby(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStandby(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceCount(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceXml(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceIndex(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceIndex(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceIndexByName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupSourceIndexByName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStartupSourceIndex(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupSourceIndex(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStartupSourceEnabled(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupSourceEnabled(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceSystemName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceName(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceType(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSourceVisible(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceVisible(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyProductType;
    PropertyString* iPropertyProductModel;
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductRoom;
    PropertyBool* iPropertyProductStandby;
    PropertyUint* iPropertyProductSourceIndex;
    PropertyUint* iPropertyProductSourceCount;
    PropertyString* iPropertyProductSourceXml;
    PropertyUint* iPropertyStartupSourceIndex;
    PropertyBool* iPropertyStartupSourceEnabled;
    PropertyUint* iPropertyProductAnySourceName;
    PropertyUint* iPropertyProductAnySourceVisible;
    PropertyUint* iPropertyProductAnySourceType;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT3CPP

