#ifndef HEADER_DVAVOPENHOMEORGMEDIASERVER1
#define HEADER_DVAVOPENHOMEORGMEDIASERVER1

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
 * Provider for the av.openhome.org:MediaServer:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgMediaServer1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgMediaServer1() {}
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
     * Set the value of the QueryPort property
     *
     * Can only be called if EnablePropertyQueryPort has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyQueryPort(TUint aValue);
    /**
     * Get a copy of the value of the QueryPort property
     *
     * Can only be called if EnablePropertyQueryPort has previously been called.
     */
    void GetPropertyQueryPort(TUint& aValue);
    /**
     * Set the value of the BrowsePort property
     *
     * Can only be called if EnablePropertyBrowsePort has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyBrowsePort(TUint aValue);
    /**
     * Get a copy of the value of the BrowsePort property
     *
     * Can only be called if EnablePropertyBrowsePort has previously been called.
     */
    void GetPropertyBrowsePort(TUint& aValue);
    /**
     * Set the value of the UpdateCount property
     *
     * Can only be called if EnablePropertyUpdateCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyUpdateCount(TUint aValue);
    /**
     * Get a copy of the value of the UpdateCount property
     *
     * Can only be called if EnablePropertyUpdateCount has previously been called.
     */
    void GetPropertyUpdateCount(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgMediaServer1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgMediaServer1(DviDevice& aDevice);
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
     * Enable the Attributes property.
     */
    void EnablePropertyAttributes();
    /**
     * Enable the QueryPort property.
     */
    void EnablePropertyQueryPort();
    /**
     * Enable the BrowsePort property.
     */
    void EnablePropertyBrowsePort();
    /**
     * Enable the UpdateCount property.
     */
    void EnablePropertyUpdateCount();
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
     * Signal that the action Attributes is supported.
     * The action's availability will be published in the device's service.xml.
     * Attributes must be overridden if this is called.
     */
    void EnableActionAttributes();
    /**
     * Signal that the action QueryPort is supported.
     * The action's availability will be published in the device's service.xml.
     * QueryPort must be overridden if this is called.
     */
    void EnableActionQueryPort();
    /**
     * Signal that the action BrowsePort is supported.
     * The action's availability will be published in the device's service.xml.
     * BrowsePort must be overridden if this is called.
     */
    void EnableActionBrowsePort();
    /**
     * Signal that the action UpdateCount is supported.
     * The action's availability will be published in the device's service.xml.
     * UpdateCount must be overridden if this is called.
     */
    void EnableActionUpdateCount();
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
    virtual void Product(IDvInvocation& aInvocation, IDvInvocationResponseString& aName, IDvInvocationResponseString& aInfo, IDvInvocationResponseString& aUrl, IDvInvocationResponseString& aImageUri);
    /**
     * Attributes action.
     *
     * Will be called when the device stack receives an invocation of the
     * Attributes action for the owning device.
     * Must be implemented iff EnableActionAttributes was called.
     */
    virtual void Attributes(IDvInvocation& aInvocation, IDvInvocationResponseString& aValue);
    /**
     * QueryPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * QueryPort action for the owning device.
     * Must be implemented iff EnableActionQueryPort was called.
     */
    virtual void QueryPort(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    /**
     * BrowsePort action.
     *
     * Will be called when the device stack receives an invocation of the
     * BrowsePort action for the owning device.
     * Must be implemented iff EnableActionBrowsePort was called.
     */
    virtual void BrowsePort(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
    /**
     * UpdateCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * UpdateCount action for the owning device.
     * Must be implemented iff EnableActionUpdateCount was called.
     */
    virtual void UpdateCount(IDvInvocation& aInvocation, IDvInvocationResponseUint& aValue);
private:
    DvProviderAvOpenhomeOrgMediaServer1();
    void Construct();
    void DoManufacturer(IDviInvocation& aInvocation);
    void DoModel(IDviInvocation& aInvocation);
    void DoProduct(IDviInvocation& aInvocation);
    void DoAttributes(IDviInvocation& aInvocation);
    void DoQueryPort(IDviInvocation& aInvocation);
    void DoBrowsePort(IDviInvocation& aInvocation);
    void DoUpdateCount(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyManufacturerName;
    PropertyString* iPropertyManufacturerInfo;
    PropertyString* iPropertyManufacturerUrl;
    PropertyString* iPropertyManufacturerImageUri;
    PropertyString* iPropertyModelName;
    PropertyString* iPropertyModelInfo;
    PropertyString* iPropertyModelUrl;
    PropertyString* iPropertyModelImageUri;
    PropertyString* iPropertyProductName;
    PropertyString* iPropertyProductInfo;
    PropertyString* iPropertyProductUrl;
    PropertyString* iPropertyProductImageUri;
    PropertyString* iPropertyAttributes;
    PropertyUint* iPropertyQueryPort;
    PropertyUint* iPropertyBrowsePort;
    PropertyUint* iPropertyUpdateCount;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGMEDIASERVER1

