#ifndef HEADER_DVLINNCOUKPRODUCT3CPP
#define HEADER_DVLINNCOUKPRODUCT3CPP

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
 * Provider for the linn.co.uk:Product:3 UPnP service
 */
class DvProviderLinnCoUkProduct3Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct3Cpp() {}
    /**
     * Set the value of the ProductType property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductType(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductType property
     */
    void GetPropertyProductType(std::string& aValue);
    /**
     * Set the value of the ProductModel property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductModel(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductModel property
     */
    void GetPropertyProductModel(std::string& aValue);
    /**
     * Set the value of the ProductName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductName(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductName property
     */
    void GetPropertyProductName(std::string& aValue);
    /**
     * Set the value of the ProductRoom property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductRoom(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductRoom property
     */
    void GetPropertyProductRoom(std::string& aValue);
    /**
     * Set the value of the ProductStandby property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductStandby(bool aValue);
    /**
     * Get a copy of the value of the ProductStandby property
     */
    void GetPropertyProductStandby(bool& aValue);
    /**
     * Set the value of the ProductSourceIndex property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductSourceIndex(uint32_t aValue);
    /**
     * Get a copy of the value of the ProductSourceIndex property
     */
    void GetPropertyProductSourceIndex(uint32_t& aValue);
    /**
     * Set the value of the ProductSourceCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductSourceCount(uint32_t aValue);
    /**
     * Get a copy of the value of the ProductSourceCount property
     */
    void GetPropertyProductSourceCount(uint32_t& aValue);
    /**
     * Set the value of the ProductSourceXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductSourceXml(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductSourceXml property
     */
    void GetPropertyProductSourceXml(std::string& aValue);
    /**
     * Set the value of the StartupSourceIndex property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyStartupSourceIndex(uint32_t aValue);
    /**
     * Get a copy of the value of the StartupSourceIndex property
     */
    void GetPropertyStartupSourceIndex(uint32_t& aValue);
    /**
     * Set the value of the StartupSourceEnabled property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyStartupSourceEnabled(bool aValue);
    /**
     * Get a copy of the value of the StartupSourceEnabled property
     */
    void GetPropertyStartupSourceEnabled(bool& aValue);
    /**
     * Set the value of the ProductAnySourceName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductAnySourceName(uint32_t aValue);
    /**
     * Get a copy of the value of the ProductAnySourceName property
     */
    void GetPropertyProductAnySourceName(uint32_t& aValue);
    /**
     * Set the value of the ProductAnySourceVisible property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductAnySourceVisible(uint32_t aValue);
    /**
     * Get a copy of the value of the ProductAnySourceVisible property
     */
    void GetPropertyProductAnySourceVisible(uint32_t& aValue);
    /**
     * Set the value of the ProductAnySourceType property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductAnySourceType(uint32_t aValue);
    /**
     * Get a copy of the value of the ProductAnySourceType property
     */
    void GetPropertyProductAnySourceType(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkProduct3Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action Type is supported.
     * The action's availability will be published in the device's service.xml.
     * DoType must be overridden if this is called.
     */
    void EnableActionType();
    /**
     * Signal that the action Model is supported.
     * The action's availability will be published in the device's service.xml.
     * DoModel must be overridden if this is called.
     */
    void EnableActionModel();
    /**
     * Signal that the action Name is supported.
     * The action's availability will be published in the device's service.xml.
     * DoName must be overridden if this is called.
     */
    void EnableActionName();
    /**
     * Signal that the action SetName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetName must be overridden if this is called.
     */
    void EnableActionSetName();
    /**
     * Signal that the action Room is supported.
     * The action's availability will be published in the device's service.xml.
     * DoRoom must be overridden if this is called.
     */
    void EnableActionRoom();
    /**
     * Signal that the action SetRoom is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetRoom must be overridden if this is called.
     */
    void EnableActionSetRoom();
    /**
     * Signal that the action Standby is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStandby must be overridden if this is called.
     */
    void EnableActionStandby();
    /**
     * Signal that the action SetStandby is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStandby must be overridden if this is called.
     */
    void EnableActionSetStandby();
    /**
     * Signal that the action SourceCount is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSourceCount must be overridden if this is called.
     */
    void EnableActionSourceCount();
    /**
     * Signal that the action SourceXml is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSourceXml must be overridden if this is called.
     */
    void EnableActionSourceXml();
    /**
     * Signal that the action SourceIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSourceIndex must be overridden if this is called.
     */
    void EnableActionSourceIndex();
    /**
     * Signal that the action SetSourceIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetSourceIndex must be overridden if this is called.
     */
    void EnableActionSetSourceIndex();
    /**
     * Signal that the action SetSourceIndexByName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetSourceIndexByName must be overridden if this is called.
     */
    void EnableActionSetSourceIndexByName();
    /**
     * Signal that the action SetStartupSourceIndexByName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStartupSourceIndexByName must be overridden if this is called.
     */
    void EnableActionSetStartupSourceIndexByName();
    /**
     * Signal that the action StartupSourceIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStartupSourceIndex must be overridden if this is called.
     */
    void EnableActionStartupSourceIndex();
    /**
     * Signal that the action SetStartupSourceIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStartupSourceIndex must be overridden if this is called.
     */
    void EnableActionSetStartupSourceIndex();
    /**
     * Signal that the action StartupSourceEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStartupSourceEnabled must be overridden if this is called.
     */
    void EnableActionStartupSourceEnabled();
    /**
     * Signal that the action SetStartupSourceEnabled is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetStartupSourceEnabled must be overridden if this is called.
     */
    void EnableActionSetStartupSourceEnabled();
    /**
     * Signal that the action SourceSystemName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSourceSystemName must be overridden if this is called.
     */
    void EnableActionSourceSystemName();
    /**
     * Signal that the action SourceName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSourceName must be overridden if this is called.
     */
    void EnableActionSourceName();
    /**
     * Signal that the action SetSourceName is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetSourceName must be overridden if this is called.
     */
    void EnableActionSetSourceName();
    /**
     * Signal that the action SourceType is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSourceType must be overridden if this is called.
     */
    void EnableActionSourceType();
    /**
     * Signal that the action SourceVisible is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSourceVisible must be overridden if this is called.
     */
    void EnableActionSourceVisible();
    /**
     * Signal that the action SetSourceVisible is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSetSourceVisible must be overridden if this is called.
     */
    void EnableActionSetSourceVisible();
private:
    /**
     * Type action.
     *
     * Will be called when the device stack receives an invocation of the
     * Type action for the owning device.
     * Must be implemented iff EnableActionType was called.
     */
    virtual void Type(uint32_t aVersion, std::string& aaType);
    /**
     * Model action.
     *
     * Will be called when the device stack receives an invocation of the
     * Model action for the owning device.
     * Must be implemented iff EnableActionModel was called.
     */
    virtual void Model(uint32_t aVersion, std::string& aaModel);
    /**
     * Name action.
     *
     * Will be called when the device stack receives an invocation of the
     * Name action for the owning device.
     * Must be implemented iff EnableActionName was called.
     */
    virtual void Name(uint32_t aVersion, std::string& aaName);
    /**
     * SetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetName action for the owning device.
     * Must be implemented iff EnableActionSetName was called.
     */
    virtual void SetName(uint32_t aVersion, const std::string& aaName);
    /**
     * Room action.
     *
     * Will be called when the device stack receives an invocation of the
     * Room action for the owning device.
     * Must be implemented iff EnableActionRoom was called.
     */
    virtual void Room(uint32_t aVersion, std::string& aaRoom);
    /**
     * SetRoom action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRoom action for the owning device.
     * Must be implemented iff EnableActionSetRoom was called.
     */
    virtual void SetRoom(uint32_t aVersion, const std::string& aaRoom);
    /**
     * Standby action.
     *
     * Will be called when the device stack receives an invocation of the
     * Standby action for the owning device.
     * Must be implemented iff EnableActionStandby was called.
     */
    virtual void Standby(uint32_t aVersion, bool& aaStandby);
    /**
     * SetStandby action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStandby action for the owning device.
     * Must be implemented iff EnableActionSetStandby was called.
     */
    virtual void SetStandby(uint32_t aVersion, bool aaStandby);
    /**
     * SourceCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceCount action for the owning device.
     * Must be implemented iff EnableActionSourceCount was called.
     */
    virtual void SourceCount(uint32_t aVersion, uint32_t& aaSourceCount);
    /**
     * SourceXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceXml action for the owning device.
     * Must be implemented iff EnableActionSourceXml was called.
     */
    virtual void SourceXml(uint32_t aVersion, std::string& aaSourceXml);
    /**
     * SourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceIndex action for the owning device.
     * Must be implemented iff EnableActionSourceIndex was called.
     */
    virtual void SourceIndex(uint32_t aVersion, uint32_t& aaSourceIndex);
    /**
     * SetSourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceIndex action for the owning device.
     * Must be implemented iff EnableActionSetSourceIndex was called.
     */
    virtual void SetSourceIndex(uint32_t aVersion, uint32_t aaSourceIndex);
    /**
     * SetSourceIndexByName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceIndexByName action for the owning device.
     * Must be implemented iff EnableActionSetSourceIndexByName was called.
     */
    virtual void SetSourceIndexByName(uint32_t aVersion, const std::string& aaSourceName);
    /**
     * SetStartupSourceIndexByName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupSourceIndexByName action for the owning device.
     * Must be implemented iff EnableActionSetStartupSourceIndexByName was called.
     */
    virtual void SetStartupSourceIndexByName(uint32_t aVersion, const std::string& aaSourceName);
    /**
     * StartupSourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartupSourceIndex action for the owning device.
     * Must be implemented iff EnableActionStartupSourceIndex was called.
     */
    virtual void StartupSourceIndex(uint32_t aVersion, uint32_t& aaSourceIndex);
    /**
     * SetStartupSourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupSourceIndex action for the owning device.
     * Must be implemented iff EnableActionSetStartupSourceIndex was called.
     */
    virtual void SetStartupSourceIndex(uint32_t aVersion, uint32_t aaSourceIndex);
    /**
     * StartupSourceEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartupSourceEnabled action for the owning device.
     * Must be implemented iff EnableActionStartupSourceEnabled was called.
     */
    virtual void StartupSourceEnabled(uint32_t aVersion, bool& aaStartupSourceEnabled);
    /**
     * SetStartupSourceEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupSourceEnabled action for the owning device.
     * Must be implemented iff EnableActionSetStartupSourceEnabled was called.
     */
    virtual void SetStartupSourceEnabled(uint32_t aVersion, bool aaStartupSourceEnabled);
    /**
     * SourceSystemName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceSystemName action for the owning device.
     * Must be implemented iff EnableActionSourceSystemName was called.
     */
    virtual void SourceSystemName(uint32_t aVersion, uint32_t aaSourceIndex, std::string& aaSourceName);
    /**
     * SourceName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceName action for the owning device.
     * Must be implemented iff EnableActionSourceName was called.
     */
    virtual void SourceName(uint32_t aVersion, uint32_t aaSourceIndex, std::string& aaSourceName);
    /**
     * SetSourceName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceName action for the owning device.
     * Must be implemented iff EnableActionSetSourceName was called.
     */
    virtual void SetSourceName(uint32_t aVersion, uint32_t aaSourceIndex, const std::string& aaSourceName);
    /**
     * SourceType action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceType action for the owning device.
     * Must be implemented iff EnableActionSourceType was called.
     */
    virtual void SourceType(uint32_t aVersion, uint32_t aaSourceIndex, std::string& aaSourceType);
    /**
     * SourceVisible action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceVisible action for the owning device.
     * Must be implemented iff EnableActionSourceVisible was called.
     */
    virtual void SourceVisible(uint32_t aVersion, uint32_t aaSourceIndex, bool& aaSourceVisible);
    /**
     * SetSourceVisible action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceVisible action for the owning device.
     * Must be implemented iff EnableActionSetSourceVisible was called.
     */
    virtual void SetSourceVisible(uint32_t aVersion, uint32_t aaSourceIndex, bool aaSourceVisible);
private:
    DvProviderLinnCoUkProduct3Cpp();
    void DoType(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoModel(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStandby(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceCount(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceXml(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceIndexByName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupSourceIndexByName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStartupSourceIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupSourceIndex(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStartupSourceEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetStartupSourceEnabled(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceSystemName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceName(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceType(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSourceVisible(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSetSourceVisible(IDviInvocation& aInvocation, uint32_t aVersion);
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

