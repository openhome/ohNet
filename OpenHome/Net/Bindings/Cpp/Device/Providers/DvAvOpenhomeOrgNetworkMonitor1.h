#ifndef HEADER_DVAVOPENHOMEORGNETWORKMONITOR1CPP
#define HEADER_DVAVOPENHOMEORGNETWORKMONITOR1CPP

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
 * Provider for the av.openhome.org:NetworkMonitor:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgNetworkMonitor1Cpp : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgNetworkMonitor1Cpp() {}
    /**
     * Set the value of the Name property
     *
     * Can only be called if EnablePropertyName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyName(const std::string& aValue);
    /**
     * Get a copy of the value of the Name property
     *
     * Can only be called if EnablePropertyName has previously been called.
     */
    void GetPropertyName(std::string& aValue);
    /**
     * Set the value of the Sender property
     *
     * Can only be called if EnablePropertySender has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySender(uint32_t aValue);
    /**
     * Get a copy of the value of the Sender property
     *
     * Can only be called if EnablePropertySender has previously been called.
     */
    void GetPropertySender(uint32_t& aValue);
    /**
     * Set the value of the Receiver property
     *
     * Can only be called if EnablePropertyReceiver has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyReceiver(uint32_t aValue);
    /**
     * Get a copy of the value of the Receiver property
     *
     * Can only be called if EnablePropertyReceiver has previously been called.
     */
    void GetPropertyReceiver(uint32_t& aValue);
    /**
     * Set the value of the Results property
     *
     * Can only be called if EnablePropertyResults has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyResults(uint32_t aValue);
    /**
     * Get a copy of the value of the Results property
     *
     * Can only be called if EnablePropertyResults has previously been called.
     */
    void GetPropertyResults(uint32_t& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgNetworkMonitor1Cpp(DvDeviceStd& aDevice);
    /**
     * Enable the Name property.
     */
    void EnablePropertyName();
    /**
     * Enable the Sender property.
     */
    void EnablePropertySender();
    /**
     * Enable the Receiver property.
     */
    void EnablePropertyReceiver();
    /**
     * Enable the Results property.
     */
    void EnablePropertyResults();
    /**
     * Signal that the action Name is supported.
     * The action's availability will be published in the device's service.xml.
     * Name must be overridden if this is called.
     */
    void EnableActionName();
    /**
     * Signal that the action Ports is supported.
     * The action's availability will be published in the device's service.xml.
     * Ports must be overridden if this is called.
     */
    void EnableActionPorts();
private:
    /**
     * Name action.
     *
     * Will be called when the device stack receives an invocation of the
     * Name action for the owning device.
     * Must be implemented iff EnableActionName was called.
     */
    virtual void Name(IDvInvocationStd& aInvocation, std::string& aName);
    /**
     * Ports action.
     *
     * Will be called when the device stack receives an invocation of the
     * Ports action for the owning device.
     * Must be implemented iff EnableActionPorts was called.
     */
    virtual void Ports(IDvInvocationStd& aInvocation, uint32_t& aSender, uint32_t& aReceiver, uint32_t& aResults);
private:
    DvProviderAvOpenhomeOrgNetworkMonitor1Cpp();
    void DoName(IDviInvocation& aInvocation);
    void DoPorts(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyName;
    PropertyUint* iPropertySender;
    PropertyUint* iPropertyReceiver;
    PropertyUint* iPropertyResults;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVAVOPENHOMEORGNETWORKMONITOR1CPP

