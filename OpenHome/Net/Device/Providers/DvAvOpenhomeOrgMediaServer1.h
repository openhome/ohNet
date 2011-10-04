#ifndef HEADER_DVAVOPENHOMEORGMEDIASERVER1
#define HEADER_DVAVOPENHOMEORGMEDIASERVER1

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

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
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyManufacturerName(const Brx& aValue);
    /**
     * Get a copy of the value of the ManufacturerName property
     */
    void GetPropertyManufacturerName(Brhz& aValue);
    /**
     * Set the value of the ManufacturerInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyManufacturerInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the ManufacturerInfo property
     */
    void GetPropertyManufacturerInfo(Brhz& aValue);
    /**
     * Set the value of the ManufacturerUrl property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyManufacturerUrl(const Brx& aValue);
    /**
     * Get a copy of the value of the ManufacturerUrl property
     */
    void GetPropertyManufacturerUrl(Brhz& aValue);
    /**
     * Set the value of the ManufacturerImageUri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyManufacturerImageUri(const Brx& aValue);
    /**
     * Get a copy of the value of the ManufacturerImageUri property
     */
    void GetPropertyManufacturerImageUri(Brhz& aValue);
    /**
     * Set the value of the ModelName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyModelName(const Brx& aValue);
    /**
     * Get a copy of the value of the ModelName property
     */
    void GetPropertyModelName(Brhz& aValue);
    /**
     * Set the value of the ModelInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyModelInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the ModelInfo property
     */
    void GetPropertyModelInfo(Brhz& aValue);
    /**
     * Set the value of the ModelUrl property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyModelUrl(const Brx& aValue);
    /**
     * Get a copy of the value of the ModelUrl property
     */
    void GetPropertyModelUrl(Brhz& aValue);
    /**
     * Set the value of the ModelImageUri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyModelImageUri(const Brx& aValue);
    /**
     * Get a copy of the value of the ModelImageUri property
     */
    void GetPropertyModelImageUri(Brhz& aValue);
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
     * Set the value of the ProductInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductInfo property
     */
    void GetPropertyProductInfo(Brhz& aValue);
    /**
     * Set the value of the ProductUrl property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductUrl(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductUrl property
     */
    void GetPropertyProductUrl(Brhz& aValue);
    /**
     * Set the value of the ProductImageUri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyProductImageUri(const Brx& aValue);
    /**
     * Get a copy of the value of the ProductImageUri property
     */
    void GetPropertyProductImageUri(Brhz& aValue);
    /**
     * Set the value of the Attributes property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyAttributes(const Brx& aValue);
    /**
     * Get a copy of the value of the Attributes property
     */
    void GetPropertyAttributes(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgMediaServer1(DvDevice& aDevice);
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
     * Signal that the action Query is supported.
     * The action's availability will be published in the device's service.xml.
     * Query must be overridden if this is called.
     */
    void EnableActionQuery();
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
     * Query action.
     *
     * Will be called when the device stack receives an invocation of the
     * Query action for the owning device.
     * Must be implemented iff EnableActionQuery was called.
     */
    virtual void Query(IDvInvocation& aInvocation, const Brx& aRequest, IDvInvocationResponseString& aResult);
private:
    DvProviderAvOpenhomeOrgMediaServer1();
    void DoManufacturer(IDviInvocation& aInvocation);
    void DoModel(IDviInvocation& aInvocation);
    void DoProduct(IDviInvocation& aInvocation);
    void DoAttributes(IDviInvocation& aInvocation);
    void DoQuery(IDviInvocation& aInvocation);
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
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGMEDIASERVER1

