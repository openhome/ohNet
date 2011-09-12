#ifndef HEADER_DVAVOPENHOMEORGMEDIASERVER1CPP
#define HEADER_DVAVOPENHOMEORGMEDIASERVER1CPP

#include <OpenHome/OhNetTypes.h>
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
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyManufacturerName(const std::string& aValue);
    /**
     * Get a copy of the value of the ManufacturerName property
     */
    void GetPropertyManufacturerName(std::string& aValue);
    /**
     * Set the value of the ManufacturerInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyManufacturerInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ManufacturerInfo property
     */
    void GetPropertyManufacturerInfo(std::string& aValue);
    /**
     * Set the value of the ManufacturerUrl property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyManufacturerUrl(const std::string& aValue);
    /**
     * Get a copy of the value of the ManufacturerUrl property
     */
    void GetPropertyManufacturerUrl(std::string& aValue);
    /**
     * Set the value of the ManufacturerImageUri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyManufacturerImageUri(const std::string& aValue);
    /**
     * Get a copy of the value of the ManufacturerImageUri property
     */
    void GetPropertyManufacturerImageUri(std::string& aValue);
    /**
     * Set the value of the ModelName property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyModelName(const std::string& aValue);
    /**
     * Get a copy of the value of the ModelName property
     */
    void GetPropertyModelName(std::string& aValue);
    /**
     * Set the value of the ModelInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyModelInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ModelInfo property
     */
    void GetPropertyModelInfo(std::string& aValue);
    /**
     * Set the value of the ModelUrl property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyModelUrl(const std::string& aValue);
    /**
     * Get a copy of the value of the ModelUrl property
     */
    void GetPropertyModelUrl(std::string& aValue);
    /**
     * Set the value of the ModelImageUri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyModelImageUri(const std::string& aValue);
    /**
     * Get a copy of the value of the ModelImageUri property
     */
    void GetPropertyModelImageUri(std::string& aValue);
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
     * Set the value of the ProductInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductInfo property
     */
    void GetPropertyProductInfo(std::string& aValue);
    /**
     * Set the value of the ProductUrl property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductUrl(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductUrl property
     */
    void GetPropertyProductUrl(std::string& aValue);
    /**
     * Set the value of the ProductImageUri property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyProductImageUri(const std::string& aValue);
    /**
     * Get a copy of the value of the ProductImageUri property
     */
    void GetPropertyProductImageUri(std::string& aValue);
    /**
     * Set the value of the Attributes property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyAttributes(const std::string& aValue);
    /**
     * Get a copy of the value of the Attributes property
     */
    void GetPropertyAttributes(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgMediaServer1Cpp(DvDeviceStd& aDevice);
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
     * Query action.
     *
     * Will be called when the device stack receives an invocation of the
     * Query action for the owning device.
     * Must be implemented iff EnableActionQuery was called.
     */
    virtual void Query(IDvInvocationStd& aInvocation, const std::string& aRequest, std::string& aResult);
private:
    DvProviderAvOpenhomeOrgMediaServer1Cpp();
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

#endif // HEADER_DVAVOPENHOMEORGMEDIASERVER1CPP

