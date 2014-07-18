#ifndef HEADER_DVAVOPENHOMEORGNETWORKMONITOR1
#define HEADER_DVAVOPENHOMEORGNETWORKMONITOR1

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
 * Provider for the av.openhome.org:NetworkMonitor:1 UPnP service
 * @ingroup Providers
 */
class DvProviderAvOpenhomeOrgNetworkMonitor1 : public DvProvider
{
public:
    virtual ~DvProviderAvOpenhomeOrgNetworkMonitor1() {}
    /**
     * Set the value of the Name property
     *
     * Can only be called if EnablePropertyName has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyName(const Brx& aValue);
    /**
     * Get a copy of the value of the Name property
     *
     * Can only be called if EnablePropertyName has previously been called.
     */
    void GetPropertyName(Brhz& aValue);
    /**
     * Set the value of the Sender property
     *
     * Can only be called if EnablePropertySender has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySender(TUint aValue);
    /**
     * Get a copy of the value of the Sender property
     *
     * Can only be called if EnablePropertySender has previously been called.
     */
    void GetPropertySender(TUint& aValue);
    /**
     * Set the value of the Receiver property
     *
     * Can only be called if EnablePropertyReceiver has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyReceiver(TUint aValue);
    /**
     * Get a copy of the value of the Receiver property
     *
     * Can only be called if EnablePropertyReceiver has previously been called.
     */
    void GetPropertyReceiver(TUint& aValue);
    /**
     * Set the value of the Results property
     *
     * Can only be called if EnablePropertyResults has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyResults(TUint aValue);
    /**
     * Get a copy of the value of the Results property
     *
     * Can only be called if EnablePropertyResults has previously been called.
     */
    void GetPropertyResults(TUint& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgNetworkMonitor1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderAvOpenhomeOrgNetworkMonitor1(DviDevice& aDevice);
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
    virtual void Name(IDvInvocation& aInvocation, IDvInvocationResponseString& aName);
    /**
     * Ports action.
     *
     * Will be called when the device stack receives an invocation of the
     * Ports action for the owning device.
     * Must be implemented iff EnableActionPorts was called.
     */
    virtual void Ports(IDvInvocation& aInvocation, IDvInvocationResponseUint& aSender, IDvInvocationResponseUint& aReceiver, IDvInvocationResponseUint& aResults);
private:
    DvProviderAvOpenhomeOrgNetworkMonitor1();
    void Construct();
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

#endif // HEADER_DVAVOPENHOMEORGNETWORKMONITOR1

