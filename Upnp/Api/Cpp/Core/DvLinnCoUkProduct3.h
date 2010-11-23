#ifndef HEADER_DVLINNCOUKPRODUCT3
#define HEADER_DVLINNCOUKPRODUCT3

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
 * Provider for the linn.co.uk:Product:3 UPnP service
 */
class DvProviderLinnCoUkProduct3 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct3() {}
    /**
     * Set the value of the ProductType property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductType(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductType property
     */
    void GetPropertyProductType(Brhz& aValue);
    /**
     * Set the value of the ProductModel property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductModel(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductModel property
     */
    void GetPropertyProductModel(Brhz& aValue);
    /**
     * Set the value of the ProductName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductName(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductName property
     */
    void GetPropertyProductName(Brhz& aValue);
    /**
     * Set the value of the ProductRoom property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductRoom(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductRoom property
     */
    void GetPropertyProductRoom(Brhz& aValue);
    /**
     * Set the value of the ProductStandby property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductStandby(TBool aValue);
    /**
     * Get a copy of the value of the ProductStandby property
     */
    void GetPropertyProductStandby(TBool& aValue);
    /**
     * Set the value of the ProductSourceIndex property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductSourceIndex(TUint aValue);
    /**
     * Get a copy of the value of the ProductSourceIndex property
     */
    void GetPropertyProductSourceIndex(TUint& aValue);
    /**
     * Set the value of the ProductSourceCount property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductSourceCount(TUint aValue);
    /**
     * Get a copy of the value of the ProductSourceCount property
     */
    void GetPropertyProductSourceCount(TUint& aValue);
    /**
     * Set the value of the ProductSourceXml property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductSourceXml(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductSourceXml property
     */
    void GetPropertyProductSourceXml(Brhz& aValue);
    /**
     * Set the value of the StartupSourceIndex property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStartupSourceIndex(TUint aValue);
    /**
     * Get a copy of the value of the StartupSourceIndex property
     */
    void GetPropertyStartupSourceIndex(TUint& aValue);
    /**
     * Set the value of the StartupSourceEnabled property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStartupSourceEnabled(TBool aValue);
    /**
     * Get a copy of the value of the StartupSourceEnabled property
     */
    void GetPropertyStartupSourceEnabled(TBool& aValue);
    /**
     * Set the value of the ProductAnySourceName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductAnySourceName(TUint aValue);
    /**
     * Get a copy of the value of the ProductAnySourceName property
     */
    void GetPropertyProductAnySourceName(TUint& aValue);
    /**
     * Set the value of the ProductAnySourceVisible property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductAnySourceVisible(TUint aValue);
    /**
     * Get a copy of the value of the ProductAnySourceVisible property
     */
    void GetPropertyProductAnySourceVisible(TUint& aValue);
    /**
     * Set the value of the ProductAnySourceType property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductAnySourceType(TUint aValue);
    /**
     * Get a copy of the value of the ProductAnySourceType property
     */
    void GetPropertyProductAnySourceType(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkProduct3(DvDevice& aDevice);
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
    virtual void Type(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaType);
    /**
     * Model action.
     *
     * Will be called when the device stack receives an invocation of the
     * Model action for the owning device.
     * Must be implemented iff EnableActionModel was called.
     */
    virtual void Model(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaModel);
    /**
     * Name action.
     *
     * Will be called when the device stack receives an invocation of the
     * Name action for the owning device.
     * Must be implemented iff EnableActionName was called.
     */
    virtual void Name(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaName);
    /**
     * SetName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetName action for the owning device.
     * Must be implemented iff EnableActionSetName was called.
     */
    virtual void SetName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaName);
    /**
     * Room action.
     *
     * Will be called when the device stack receives an invocation of the
     * Room action for the owning device.
     * Must be implemented iff EnableActionRoom was called.
     */
    virtual void Room(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaRoom);
    /**
     * SetRoom action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetRoom action for the owning device.
     * Must be implemented iff EnableActionSetRoom was called.
     */
    virtual void SetRoom(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaRoom);
    /**
     * Standby action.
     *
     * Will be called when the device stack receives an invocation of the
     * Standby action for the owning device.
     * Must be implemented iff EnableActionStandby was called.
     */
    virtual void Standby(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStandby);
    /**
     * SetStandby action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStandby action for the owning device.
     * Must be implemented iff EnableActionSetStandby was called.
     */
    virtual void SetStandby(IInvocationResponse& aResponse, TUint aVersion, TBool aaStandby);
    /**
     * SourceCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceCount action for the owning device.
     * Must be implemented iff EnableActionSourceCount was called.
     */
    virtual void SourceCount(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceCount);
    /**
     * SourceXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceXml action for the owning device.
     * Must be implemented iff EnableActionSourceXml was called.
     */
    virtual void SourceXml(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaSourceXml);
    /**
     * SourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceIndex action for the owning device.
     * Must be implemented iff EnableActionSourceIndex was called.
     */
    virtual void SourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex);
    /**
     * SetSourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceIndex action for the owning device.
     * Must be implemented iff EnableActionSetSourceIndex was called.
     */
    virtual void SetSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex);
    /**
     * SetSourceIndexByName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceIndexByName action for the owning device.
     * Must be implemented iff EnableActionSetSourceIndexByName was called.
     */
    virtual void SetSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName);
    /**
     * SetStartupSourceIndexByName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupSourceIndexByName action for the owning device.
     * Must be implemented iff EnableActionSetStartupSourceIndexByName was called.
     */
    virtual void SetStartupSourceIndexByName(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaSourceName);
    /**
     * StartupSourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartupSourceIndex action for the owning device.
     * Must be implemented iff EnableActionStartupSourceIndex was called.
     */
    virtual void StartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaSourceIndex);
    /**
     * SetStartupSourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupSourceIndex action for the owning device.
     * Must be implemented iff EnableActionSetStartupSourceIndex was called.
     */
    virtual void SetStartupSourceIndex(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex);
    /**
     * StartupSourceEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * StartupSourceEnabled action for the owning device.
     * Must be implemented iff EnableActionStartupSourceEnabled was called.
     */
    virtual void StartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aaStartupSourceEnabled);
    /**
     * SetStartupSourceEnabled action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStartupSourceEnabled action for the owning device.
     * Must be implemented iff EnableActionSetStartupSourceEnabled was called.
     */
    virtual void SetStartupSourceEnabled(IInvocationResponse& aResponse, TUint aVersion, TBool aaStartupSourceEnabled);
    /**
     * SourceSystemName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceSystemName action for the owning device.
     * Must be implemented iff EnableActionSourceSystemName was called.
     */
    virtual void SourceSystemName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName);
    /**
     * SourceName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceName action for the owning device.
     * Must be implemented iff EnableActionSourceName was called.
     */
    virtual void SourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceName);
    /**
     * SetSourceName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceName action for the owning device.
     * Must be implemented iff EnableActionSetSourceName was called.
     */
    virtual void SetSourceName(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, const Brx& aaSourceName);
    /**
     * SourceType action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceType action for the owning device.
     * Must be implemented iff EnableActionSourceType was called.
     */
    virtual void SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType);
    /**
     * SourceVisible action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceVisible action for the owning device.
     * Must be implemented iff EnableActionSourceVisible was called.
     */
    virtual void SourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseBool& aaSourceVisible);
    /**
     * SetSourceVisible action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceVisible action for the owning device.
     * Must be implemented iff EnableActionSetSourceVisible was called.
     */
    virtual void SetSourceVisible(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, TBool aaSourceVisible);
private:
    DvProviderLinnCoUkProduct3();
    void DoType(IDviInvocation& aInvocation, TUint aVersion);
    void DoModel(IDviInvocation& aInvocation, TUint aVersion);
    void DoName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoStandby(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceCount(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceXml(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndexByName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceIndexByName(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoStartupSourceEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStartupSourceEnabled(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceSystemName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceType(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceVisible(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceVisible(IDviInvocation& aInvocation, TUint aVersion);
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

#endif // HEADER_DVLINNCOUKPRODUCT3

