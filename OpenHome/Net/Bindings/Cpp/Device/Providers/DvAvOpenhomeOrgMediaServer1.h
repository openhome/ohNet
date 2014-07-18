#ifndef HEADER_DVAVOPENHOMEORGMEDIASERVER1CPP
#define HEADER_DVAVOPENHOMEORGMEDIASERVER1CPP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

#include <string>

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
class DvProviderAvOpenhomeOrgMediaServer1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgMediaServer1Cpp() {}
    /**
     * Set the value of the ManufacturerName property
     *
     * Can only be called if EnablePropertyManufacturerName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyManufacturerName(const std::string& aValue);
    /**
     * Get a copy of the value of the ManufacturerName property
     *
     * Can only be called if EnablePropertyManufacturerName has previously been called.
     */
    void GetPropertyManufacturerName(std::string& aValue);
    /**
     * Set the value of the ManufacturerInfo property
     *
     * Can only be called if EnablePropertyManufacturerInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyManufacturerInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ManufacturerInfo property
     *
     * Can only be called if EnablePropertyManufacturerInfo has previously been called.
     */
    void GetPropertyManufacturerInfo(std::string& aValue);
    /**
     * Set the value of the ManufacturerUrl property
     *
     * Can only be called if EnablePropertyManufacturerUrl has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyManufacturerUrl(const std::string& aValue);
    /**
     * Get a copy of the value of the ManufacturerUrl property
     *
     * Can only be called if EnablePropertyManufacturerUrl has previously been called.
     */
    void GetPropertyManufacturerUrl(std::string& aValue);
    /**
     * Set the value of the ManufacturerImageUri property
     *
     * Can only be called if EnablePropertyManufacturerImageUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyManufacturerImageUri(const std::string& aValue);
    /**
     * Get a copy of the value of the ManufacturerImageUri property
     *
     * Can only be called if EnablePropertyManufacturerImageUri has previously been called.
     */
    void GetPropertyManufacturerImageUri(std::string& aValue);
    /**
     * Set the value of the ModelName property
     *
     * Can only be called if EnablePropertyModelName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyModelName(const std::string& aValue);
    /**
     * Get a copy of the value of the ModelName property
     *
     * Can only be called if EnablePropertyModelName has previously been called.
     */
    void GetPropertyModelName(std::string& aValue);
    /**
     * Set the value of the ModelInfo property
     *
     * Can only be called if EnablePropertyModelInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyModelInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ModelInfo property
     *
     * Can only be called if EnablePropertyModelInfo has previously been called.
     */
    void GetPropertyModelInfo(std::string& aValue);
    /**
     * Set the value of the ModelUrl property
     *
     * Can only be called if EnablePropertyModelUrl has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyModelUrl(const std::string& aValue);
    /**
     * Get a copy of the value of the ModelUrl property
     *
     * Can only be called if EnablePropertyModelUrl has previously been called.
     */
    void GetPropertyModelUrl(std::string& aValue);
    /**
     * Set the value of the ModelImageUri property
     *
     * Can only be called if EnablePropertyModelImageUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyModelImageUri(const std::string& aValue);
    /**
     * Get a copy of the value of the ModelImageUri property
     *
     * Can only be called if EnablePropertyModelImageUri has previously been called.
     */
    void GetPropertyModelImageUri(std::string& aValue);
    /**
     * Set the value of the ProductName property
     *
     * Can only be called if EnablePropertyProductName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductName(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductName property
     *
     * Can only be called if EnablePropertyProductName has previously been called.
     */
    void GetPropertyProductName(std::string& aValue);
    /**
     * Set the value of the ProductInfo property
     *
     * Can only be called if EnablePropertyProductInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductInfo property
     *
     * Can only be called if EnablePropertyProductInfo has previously been called.
     */
    void GetPropertyProductInfo(std::string& aValue);
    /**
     * Set the value of the ProductUrl property
     *
     * Can only be called if EnablePropertyProductUrl has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductUrl(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductUrl property
     *
     * Can only be called if EnablePropertyProductUrl has previously been called.
     */
    void GetPropertyProductUrl(std::string& aValue);
    /**
     * Set the value of the ProductImageUri property
     *
     * Can only be called if EnablePropertyProductImageUri has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductImageUri(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductImageUri property
     *
     * Can only be called if EnablePropertyProductImageUri has previously been called.
     */
    void GetPropertyProductImageUri(std::string& aValue);
    /**
     * Set the value of the Attributes property
     *
     * Can only be called if EnablePropertyAttributes has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyAttributes(const std::string& aValue);
    /**
     * Get a copy of the value of the Attributes property
     *
     * Can only be called if EnablePropertyAttributes has previously been called.
     */
    void GetPropertyAttributes(std::string& aValue);
    /**
     * Set the value of the QueryPort property
     *
     * Can only be called if EnablePropertyQueryPort has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyQueryPort(uint32_t aValue);
    /**
     * Get a copy of the value of the QueryPort property
     *
     * Can only be called if EnablePropertyQueryPort has previously been called.
     */
    void GetPropertyQueryPort(uint32_t& aValue);
    /**
     * Set the value of the BrowsePort property
     *
     * Can only be called if EnablePropertyBrowsePort has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyBrowsePort(uint32_t aValue);
    /**
     * Get a copy of the value of the BrowsePort property
     *
     * Can only be called if EnablePropertyBrowsePort has previously been called.
     */
    void GetPropertyBrowsePort(uint32_t& aValue);
    /**
     * Set the value of the UpdateCount property
     *
     * Can only be called if EnablePropertyUpdateCount has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyUpdateCount(uint32_t aValue);
    /**
     * Get a copy of the value of the UpdateCount property
     *
     * Can only be called if EnablePropertyUpdateCount has previously been called.
     */
    void GetPropertyUpdateCount(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgMediaServer1Cpp(DvDeviceStd& aDevice);
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
    virtual void Manufacturer(IDvInvocationStd& aInvocation, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    /**
     * Model action.
     *
     * Will be called when the device stack receives an invocation of the
     * Model action for the owning device.
     * Must be implemented iff EnableActionModel was called.
     */
    virtual void Model(IDvInvocationStd& aInvocation, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    /**
     * Product action.
     *
     * Will be called when the device stack receives an invocation of the
     * Product action for the owning device.
     * Must be implemented iff EnableActionProduct was called.
     */
    virtual void Product(IDvInvocationStd& aInvocation, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    /**
     * Attributes action.
     *
     * Will be called when the device stack receives an invocation of the
     * Attributes action for the owning device.
     * Must be implemented iff EnableActionAttributes was called.
     */
    virtual void Attributes(IDvInvocationStd& aInvocation, std::string& aValue);
    /**
     * QueryPort action.
     *
     * Will be called when the device stack receives an invocation of the
     * QueryPort action for the owning device.
     * Must be implemented iff EnableActionQueryPort was called.
     */
    virtual void QueryPort(IDvInvocationStd& aInvocation, uint32_t& aValue);
    /**
     * BrowsePort action.
     *
     * Will be called when the device stack receives an invocation of the
     * BrowsePort action for the owning device.
     * Must be implemented iff EnableActionBrowsePort was called.
     */
    virtual void BrowsePort(IDvInvocationStd& aInvocation, uint32_t& aValue);
    /**
     * UpdateCount action.
     *
     * Will be called when the device stack receives an invocation of the
     * UpdateCount action for the owning device.
     * Must be implemented iff EnableActionUpdateCount was called.
     */
    virtual void UpdateCount(IDvInvocationStd& aInvocation, uint32_t& aValue);
private:
    DvProviderAvOpenhomeOrgMediaServer1Cpp();
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

#endif // HEADER_DVAVOPENHOMEORGMEDIASERVER1CPP

