#ifndef HEADER_DVAVOPENHOMEORGPRODUCT1
#define HEADER_DVAVOPENHOMEORGPRODUCT1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the av.openhome.org:Product:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgProduct1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgProduct1() {}
    /**
     * Set the value of the ManufacturerName property
     *
     * Can only be called if EnablePropertyManufacturerName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyManufacturerName(const Brx& aValue);
    /**
     * Get a copy of the value of the ManufacturerName property
     *
     * Can only be called if EnablePropertyManufacturerName has previously been called.
     */
    void GetPropertyManufacturerName(Brhz& aValue);
    /**
     * Output the value of the ManufacturerName property without an intermediate copy.
     *
     * Can only be called if EnablePropertyManufacturerName has previously been called.
     */
    void WritePropertyManufacturerName(IWriter& aWriter);
    /**
     * Set the value of the ManufacturerInfo property
     *
     * Can only be called if EnablePropertyManufacturerInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyManufacturerInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the ManufacturerInfo property
     *
     * Can only be called if EnablePropertyManufacturerInfo has previously been called.
     */
    void GetPropertyManufacturerInfo(Brhz& aValue);
    /**
     * Output the value of the ManufacturerInfo property without an intermediate copy.
     *
     * Can only be called if EnablePropertyManufacturerInfo has previously been called.
     */
    void WritePropertyManufacturerInfo(IWriter& aWriter);
    /**
     * Set the value of the ManufacturerUrl property
     *
     * Can only be called if EnablePropertyManufacturerUrl has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyManufacturerUrl(const Brx& aValue);
    /**
     * Get a copy of the value of the ManufacturerUrl property
     *
     * Can only be called if EnablePropertyManufacturerUrl has previously been called.
     */
    void GetPropertyManufacturerUrl(Brhz& aValue);
    /**
     * Output the value of the ManufacturerUrl property without an intermediate copy.
     *
     * Can only be called if EnablePropertyManufacturerUrl has previously been called.
     */
    void WritePropertyManufacturerUrl(IWriter& aWriter);
    /**
     * Set the value of the ManufacturerImageUri property
     *
     * Can only be called if EnablePropertyManufacturerImageUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyManufacturerImageUri(const Brx& aValue);
    /**
     * Get a copy of the value of the ManufacturerImageUri property
     *
     * Can only be called if EnablePropertyManufacturerImageUri has previously been called.
     */
    void GetPropertyManufacturerImageUri(Brhz& aValue);
    /**
     * Output the value of the ManufacturerImageUri property without an intermediate copy.
     *
     * Can only be called if EnablePropertyManufacturerImageUri has previously been called.
     */
    void WritePropertyManufacturerImageUri(IWriter& aWriter);
    /**
     * Set the value of the ModelName property
     *
     * Can only be called if EnablePropertyModelName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyModelName(const Brx& aValue);
    /**
     * Get a copy of the value of the ModelName property
     *
     * Can only be called if EnablePropertyModelName has previously been called.
     */
    void GetPropertyModelName(Brhz& aValue);
    /**
     * Output the value of the ModelName property without an intermediate copy.
     *
     * Can only be called if EnablePropertyModelName has previously been called.
     */
    void WritePropertyModelName(IWriter& aWriter);
    /**
     * Set the value of the ModelInfo property
     *
     * Can only be called if EnablePropertyModelInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyModelInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the ModelInfo property
     *
     * Can only be called if EnablePropertyModelInfo has previously been called.
     */
    void GetPropertyModelInfo(Brhz& aValue);
    /**
     * Output the value of the ModelInfo property without an intermediate copy.
     *
     * Can only be called if EnablePropertyModelInfo has previously been called.
     */
    void WritePropertyModelInfo(IWriter& aWriter);
    /**
     * Set the value of the ModelUrl property
     *
     * Can only be called if EnablePropertyModelUrl has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyModelUrl(const Brx& aValue);
    /**
     * Get a copy of the value of the ModelUrl property
     *
     * Can only be called if EnablePropertyModelUrl has previously been called.
     */
    void GetPropertyModelUrl(Brhz& aValue);
    /**
     * Output the value of the ModelUrl property without an intermediate copy.
     *
     * Can only be called if EnablePropertyModelUrl has previously been called.
     */
    void WritePropertyModelUrl(IWriter& aWriter);
    /**
     * Set the value of the ModelImageUri property
     *
     * Can only be called if EnablePropertyModelImageUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyModelImageUri(const Brx& aValue);
    /**
     * Get a copy of the value of the ModelImageUri property
     *
     * Can only be called if EnablePropertyModelImageUri has previously been called.
     */
    void GetPropertyModelImageUri(Brhz& aValue);
    /**
     * Output the value of the ModelImageUri property without an intermediate copy.
     *
     * Can only be called if EnablePropertyModelImageUri has previously been called.
     */
    void WritePropertyModelImageUri(IWriter& aWriter);
    /**
     * Set the value of the ProductRoom property
     *
     * Can only be called if EnablePropertyProductRoom has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductRoom(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductRoom property
     *
     * Can only be called if EnablePropertyProductRoom has previously been called.
     */
    void GetPropertyProductRoom(Brhz& aValue);
    /**
     * Output the value of the ProductRoom property without an intermediate copy.
     *
     * Can only be called if EnablePropertyProductRoom has previously been called.
     */
    void WritePropertyProductRoom(IWriter& aWriter);
    /**
     * Set the value of the ProductName property
     *
     * Can only be called if EnablePropertyProductName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductName(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductName property
     *
     * Can only be called if EnablePropertyProductName has previously been called.
     */
    void GetPropertyProductName(Brhz& aValue);
    /**
     * Output the value of the ProductName property without an intermediate copy.
     *
     * Can only be called if EnablePropertyProductName has previously been called.
     */
    void WritePropertyProductName(IWriter& aWriter);
    /**
     * Set the value of the ProductInfo property
     *
     * Can only be called if EnablePropertyProductInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductInfo property
     *
     * Can only be called if EnablePropertyProductInfo has previously been called.
     */
    void GetPropertyProductInfo(Brhz& aValue);
    /**
     * Output the value of the ProductInfo property without an intermediate copy.
     *
     * Can only be called if EnablePropertyProductInfo has previously been called.
     */
    void WritePropertyProductInfo(IWriter& aWriter);
    /**
     * Set the value of the ProductUrl property
     *
     * Can only be called if EnablePropertyProductUrl has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductUrl(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductUrl property
     *
     * Can only be called if EnablePropertyProductUrl has previously been called.
     */
    void GetPropertyProductUrl(Brhz& aValue);
    /**
     * Output the value of the ProductUrl property without an intermediate copy.
     *
     * Can only be called if EnablePropertyProductUrl has previously been called.
     */
    void WritePropertyProductUrl(IWriter& aWriter);
    /**
     * Set the value of the ProductImageUri property
     *
     * Can only be called if EnablePropertyProductImageUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductImageUri(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductImageUri property
     *
     * Can only be called if EnablePropertyProductImageUri has previously been called.
     */
    void GetPropertyProductImageUri(Brhz& aValue);
    /**
     * Output the value of the ProductImageUri property without an intermediate copy.
     *
     * Can only be called if EnablePropertyProductImageUri has previously been called.
     */
    void WritePropertyProductImageUri(IWriter& aWriter);
    /**
     * Set the value of the Standby property
     *
     * Can only be called if EnablePropertyStandby has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyStandby(TBool aValue);
    /**
     * Get a copy of the value of the Standby property
     *
     * Can only be called if EnablePropertyStandby has previously been called.
     */
    void GetPropertyStandby(TBool& aValue);
    /**
     * Set the value of the SourceIndex property
     *
     * Can only be called if EnablePropertySourceIndex has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySourceIndex(TUint aValue);
    /**
     * Get a copy of the value of the SourceIndex property
     *
     * Can only be called if EnablePropertySourceIndex has previously been called.
     */
    void GetPropertySourceIndex(TUint& aValue);
    /**
     * Set the value of the SourceCount property
     *
     * Can only be called if EnablePropertySourceCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySourceCount(TUint aValue);
    /**
     * Get a copy of the value of the SourceCount property
     *
     * Can only be called if EnablePropertySourceCount has previously been called.
     */
    void GetPropertySourceCount(TUint& aValue);
    /**
     * Set the value of the SourceXml property
     *
     * Can only be called if EnablePropertySourceXml has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySourceXml(const Brx& aValue);
    /**
     * Get a copy of the value of the SourceXml property
     *
     * Can only be called if EnablePropertySourceXml has previously been called.
     */
    void GetPropertySourceXml(Brhz& aValue);
    /**
     * Output the value of the SourceXml property without an intermediate copy.
     *
     * Can only be called if EnablePropertySourceXml has previously been called.
     */
    void WritePropertySourceXml(IWriter& aWriter);
    /**
     * Set the value of the Attributes property
     *
     * Can only be called if EnablePropertyAttributes has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAttributes(const Brx& aValue);
    /**
     * Get a copy of the value of the Attributes property
     *
     * Can only be called if EnablePropertyAttributes has previously been called.
     */
    void GetPropertyAttributes(Brhz& aValue);
    /**
     * Output the value of the Attributes property without an intermediate copy.
     *
     * Can only be called if EnablePropertyAttributes has previously been called.
     */
    void WritePropertyAttributes(IWriter& aWriter);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgProduct1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgProduct1(DviDevice& aDevice);
    /**
     * Enable the ManufacturerName property.
     */
    void EnablePropertyManufacturerName();
    /**
     * Enable the ManufacturerInfo property.
     */
    void EnablePropertyManufacturerInfo();
    /**
     * Enable the ManufacturerUrl property.
     */
    void EnablePropertyManufacturerUrl();
    /**
     * Enable the ManufacturerImageUri property.
     */
    void EnablePropertyManufacturerImageUri();
    /**
     * Enable the ModelName property.
     */
    void EnablePropertyModelName();
    /**
     * Enable the ModelInfo property.
     */
    void EnablePropertyModelInfo();
    /**
     * Enable the ModelUrl property.
     */
    void EnablePropertyModelUrl();
    /**
     * Enable the ModelImageUri property.
     */
    void EnablePropertyModelImageUri();
    /**
     * Enable the ProductRoom property.
     */
    void EnablePropertyProductRoom();
    /**
     * Enable the ProductName property.
     */
    void EnablePropertyProductName();
    /**
     * Enable the ProductInfo property.
     */
    void EnablePropertyProductInfo();
    /**
     * Enable the ProductUrl property.
     */
    void EnablePropertyProductUrl();
    /**
     * Enable the ProductImageUri property.
     */
    void EnablePropertyProductImageUri();
    /**
     * Enable the Standby property.
     */
    void EnablePropertyStandby();
    /**
     * Enable the SourceIndex property.
     */
    void EnablePropertySourceIndex();
    /**
     * Enable the SourceCount property.
     */
    void EnablePropertySourceCount();
    /**
     * Enable the SourceXml property.
     */
    void EnablePropertySourceXml();
    /**
     * Enable the Attributes property.
     */
    void EnablePropertyAttributes();
    /**
     * Signal that the action Manufacturer is supported.
     * The action's availability will be published in the device's service.xml.
     * Manufacturer must be overridden if this is called.
     */
    void EnableActionManufacturer();
    /**
     * Signal that the action Model is supported.
     * The action's availability will be published in the device's service.xml.
     * Model must be overridden if this is called.
     */
    void EnableActionModel();
    /**
     * Signal that the action Product is supported.
     * The action's availability will be published in the device's service.xml.
     * Product must be overridden if this is called.
     */
    void EnableActionProduct();
    /**
     * Signal that the action Standby is supported.
     * The action's availability will be published in the device's service.xml.
     * Standby must be overridden if this is called.
     */
    void EnableActionStandby();
    /**
     * Signal that the action SetStandby is supported.
     * The action's availability will be published in the device's service.xml.
     * SetStandby must be overridden if this is called.
     */
    void EnableActionSetStandby();
    /**
     * Signal that the action SourceCount is supported.
     * The action's availability will be published in the device's service.xml.
     * SourceCount must be overridden if this is called.
     */
    void EnableActionSourceCount();
    /**
     * Signal that the action SourceXml is supported.
     * The action's availability will be published in the device's service.xml.
     * SourceXml must be overridden if this is called.
     */
    void EnableActionSourceXml();
    /**
     * Signal that the action SourceIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * SourceIndex must be overridden if this is called.
     */
    void EnableActionSourceIndex();
    /**
     * Signal that the action SetSourceIndex is supported.
     * The action's availability will be published in the device's service.xml.
     * SetSourceIndex must be overridden if this is called.
     */
    void EnableActionSetSourceIndex();
    /**
     * Signal that the action SetSourceIndexByName is supported.
     * The action's availability will be published in the device's service.xml.
     * SetSourceIndexByName must be overridden if this is called.
     */
    void EnableActionSetSourceIndexByName();
    /**
     * Signal that the action Source is supported.
     * The action's availability will be published in the device's service.xml.
     * Source must be overridden if this is called.
     */
    void EnableActionSource();
    /**
     * Signal that the action Attributes is supported.
     * The action's availability will be published in the device's service.xml.
     * Attributes must be overridden if this is called.
     */
    void EnableActionAttributes();
    /**
     * Signal that the action SourceXmlChangeCount is supported.
     * The action's availability will be published in the device's service.xml.
     * SourceXmlChangeCount must be overridden if this is called.
     */
    void EnableActionSourceXmlChangeCount();
private:
    /**
     * Manufacturer action.
     *
     * Will be called when the device stack receives an invocation of the
     * Manufacturer action for the owning device.
     * Must be implemented iff EnableActionManufacturer was called.
     */
    virtual void Manufacturer(IDvInvocation& aInvocation, IDvInvocationResponseString& aName, IDvInvocationResponseString& aInfo, IDvInvocationResponseString& aUrl, IDvInvocationResponseString& aImageUri);
    /**
     * Model action.
     *
     * Will be called when the device stack receives an invocation of the
     * Model action for the owning device.
     * Must be implemented iff EnableActionModel was called.
     */
    virtual void Model(IDvInvocation& aInvocation, IDvInvocationResponseString& aName, IDvInvocationResponseString& aInfo, IDvInvocationResponseString& aUrl, IDvInvocationResponseString& aImageUri);
    /**
     * Product action.
     *
     * Will be called when the device stack receives an invocation of the
     * Product action for the owning device.
     * Must be implemented iff EnableActionProduct was called.
     */
    virtual void Product(IDvInvocation& aInvocation, IDvInvocationResponseString& aRoom, IDvInvocationResponseString& aName, IDvInvocationResponseString& aInfo, IDvInvocationResponseString& aUrl, IDvInvocationResponseString& aImageUri);
    /**
     * Standby action.
     *
     * Will be called when the device stack receives an invocation of the
     * Standby action for the owning device.
     * Must be implemented iff EnableActionStandby was called.
     */
    virtual void Standby(IDvInvocation& aInvocation, IDvInvocationResponseBool& aValue);
    /**
     * SetStandby action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetStandby action for the owning device.
     * Must be implemented iff EnableActionSetStandby was called.
     */
    virtual void SetStandby(IDvInvocation& aInvocation, TBool aValue);
    /**
     * SourceCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceCount action for the owning device.
     * Must be implemented iff EnableActionSourceCount was called.
     */
    virtual void SourceCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    /**
     * SourceXml action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceXml action for the owning device.
     * Must be implemented iff EnableActionSourceXml was called.
     */
    virtual void SourceXml(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    /**
     * SourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceIndex action for the owning device.
     * Must be implemented iff EnableActionSourceIndex was called.
     */
    virtual void SourceIndex(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    /**
     * SetSourceIndex action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceIndex action for the owning device.
     * Must be implemented iff EnableActionSetSourceIndex was called.
     */
    virtual void SetSourceIndex(IDvInvocation& aInvocation, TUint aValue);
    /**
     * SetSourceIndexByName action.
     *
     * Will be called when the device stack receives an invocation of the
     * SetSourceIndexByName action for the owning device.
     * Must be implemented iff EnableActionSetSourceIndexByName was called.
     */
    virtual void SetSourceIndexByName(IDvInvocation& aInvocation, const Brx& aValue);
    /**
     * Source action.
     *
     * Will be called when the device stack receives an invocation of the
     * Source action for the owning device.
     * Must be implemented iff EnableActionSource was called.
     */
    virtual void Source(IDvInvocation& aInvocation, TUint aIndex, IDvInvocationResponseString& aSystemName, IDvInvocationResponseString& aType, IDvInvocationResponseString& aName, IDvInvocationResponseBool& aVisible);
    /**
     * Attributes action.
     *
     * Will be called when the device stack receives an invocation of the
     * Attributes action for the owning device.
     * Must be implemented iff EnableActionAttributes was called.
     */
    virtual void Attributes(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    /**
     * SourceXmlChangeCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * SourceXmlChangeCount action for the owning device.
     * Must be implemented iff EnableActionSourceXmlChangeCount was called.
     */
    virtual void SourceXmlChangeCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
private:
    DvProviderAvOpenhomeOrgProduct1();
    void Construct();
    void DoManufacturer(IDviInvocation& aInvocation);
    void DoModel(IDviInvocation& aInvocation);
    void DoProduct(IDviInvocation& aInvocation);
    void DoStandby(IDviInvocation& aInvocation);
    void DoSetStandby(IDviInvocation& aInvocation);
    void DoSourceCount(IDviInvocation& aInvocation);
    void DoSourceXml(IDviInvocation& aInvocation);
    void DoSourceIndex(IDviInvocation& aInvocation);
    void DoSetSourceIndex(IDviInvocation& aInvocation);
    void DoSetSourceIndexByName(IDviInvocation& aInvocation);
    void DoSource(IDviInvocation& aInvocation);
    void DoAttributes(IDviInvocation& aInvocation);
    void DoSourceXmlChangeCount(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyManufacturerName;
    PropertyString* iPropertyManufacturerInfo;
    PropertyString* iPropertyManufacturerUrl;
    PropertyString* iPropertyManufacturerImageUri;
    PropertyString* iPropertyModelName;
    PropertyString* iPropertyModelInfo;
    PropertyString* iPropertyModelUrl;
    PropertyString* iPropertyModelImageUri;
    PropertyString* iPropertyProductRoom;
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductInfo;
    PropertyString* iPropertyProductUrl;
    PropertyString* iPropertyProductImageUri;
    PropertyBool* iPropertyStandby;
    PropertyUint* iPropertySourceIndex;
    PropertyUint* iPropertySourceCount;
    PropertyString* iPropertySourceXml;
    PropertyString* iPropertyAttributes;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGPRODUCT1

