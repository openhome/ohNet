#ifndef HEADER_DVLINNCOUKPRODUCT2
#define HEADER_DVLINNCOUKPRODUCT2

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
 * Provider for the linn.co.uk:Product:2 UPnP service
 * @ingroup Providers
 */
class DvProviderLinnCoUkProduct2 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkProduct2() {}
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
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderLinnCoUkProduct2(DvDevice& aDevice);
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
     * SourceType action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceType action for the owning device.
     * Must be implemented iff EnableActionSourceType was called.
     */
    virtual void SourceType(IInvocationResponse& aResponse, TUint aVersion, TUint aaSourceIndex, IInvocationResponseString& aaSourceType);
private:
    DvProviderLinnCoUkProduct2();
    void DoType(IDviInvocation& aInvocation, TUint aVersion);
    void DoModel(IDviInvocation& aInvocation, TUint aVersion);
    void DoName(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetName(IDviInvocation& aInvocation, TUint aVersion);
    void DoRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRoom(IDviInvocation& aInvocation, TUint aVersion);
    void DoStandby(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStandby(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceCount(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSourceIndex(IDviInvocation& aInvocation, TUint aVersion);
    void DoSourceType(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductRoom;
    PropertyBool* iPropertyProductStandby;
    PropertyUint* iPropertyProductSourceIndex;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKPRODUCT2

