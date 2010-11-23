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
 * Provider for the linn.co.uk:Product:2 UPnP service
 */
class DvProviderLinnCoUkProduct2Cpp : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct2Cpp() {}
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
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkProduct2Cpp(DvDeviceStd& aDevice);
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
     * Signal that the action SourceType is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSourceType must be overridden if this is called.
     */
    void EnableActionSourceType();
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
     * SourceType action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceType action for the owning device.
     * Must be implemented iff EnableActionSourceType was called.
     */
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

