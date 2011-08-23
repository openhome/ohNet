#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER2
#define HEADER_DVUPNPORGCONNECTIONMANAGER2

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
 * Provider for the upnp.org:ConnectionManager:2 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgConnectionManager2 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgConnectionManager2() {}
    /**
     * Set the value of the SourceProtocolInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySourceProtocolInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the SourceProtocolInfo property
     */
    void GetPropertySourceProtocolInfo(Brhz& aValue);
    /**
     * Set the value of the SinkProtocolInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySinkProtocolInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the SinkProtocolInfo property
     */
    void GetPropertySinkProtocolInfo(Brhz& aValue);
    /**
     * Set the value of the CurrentConnectionIDs property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyCurrentConnectionIDs(const Brx& aValue);
    /**
     * Get a copy of the value of the CurrentConnectionIDs property
     */
    void GetPropertyCurrentConnectionIDs(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgConnectionManager2(DvDevice& aDevice);
    /**
     * Signal that the action GetProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * GetProtocolInfo must be overridden if this is called.
     */
    void EnableActionGetProtocolInfo();
    /**
     * Signal that the action PrepareForConnection is supported.
     * The action's availability will be published in the device's service.xml.
     * PrepareForConnection must be overridden if this is called.
     */
    void EnableActionPrepareForConnection();
    /**
     * Signal that the action ConnectionComplete is supported.
     * The action's availability will be published in the device's service.xml.
     * ConnectionComplete must be overridden if this is called.
     */
    void EnableActionConnectionComplete();
    /**
     * Signal that the action GetCurrentConnectionIDs is supported.
     * The action's availability will be published in the device's service.xml.
     * GetCurrentConnectionIDs must be overridden if this is called.
     */
    void EnableActionGetCurrentConnectionIDs();
    /**
     * Signal that the action GetCurrentConnectionInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * GetCurrentConnectionInfo must be overridden if this is called.
     */
    void EnableActionGetCurrentConnectionInfo();
private:
    /**
     * GetProtocolInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetProtocolInfo action for the owning device.
     * Must be implemented iff EnableActionGetProtocolInfo was called.
     */
    virtual void GetProtocolInfo(IDvInvocationResponse& aResponse, TUint aVersion, IDvInvocationResponseString& aSource, IDvInvocationResponseString& aSink);
    /**
     * PrepareForConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * PrepareForConnection action for the owning device.
     * Must be implemented iff EnableActionPrepareForConnection was called.
     */
    virtual void PrepareForConnection(IDvInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IDvInvocationResponseInt& aConnectionID, IDvInvocationResponseInt& aAVTransportID, IDvInvocationResponseInt& aRcsID);
    /**
     * ConnectionComplete action.
     *
     * Will be called when the device stack receives an invocation of the
     * ConnectionComplete action for the owning device.
     * Must be implemented iff EnableActionConnectionComplete was called.
     */
    virtual void ConnectionComplete(IDvInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID);
    /**
     * GetCurrentConnectionIDs action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionIDs action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionIDs was called.
     */
    virtual void GetCurrentConnectionIDs(IDvInvocationResponse& aResponse, TUint aVersion, IDvInvocationResponseString& aConnectionIDs);
    /**
     * GetCurrentConnectionInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionInfo action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionInfo was called.
     */
    virtual void GetCurrentConnectionInfo(IDvInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IDvInvocationResponseInt& aRcsID, IDvInvocationResponseInt& aAVTransportID, IDvInvocationResponseString& aProtocolInfo, IDvInvocationResponseString& aPeerConnectionManager, IDvInvocationResponseInt& aPeerConnectionID, IDvInvocationResponseString& aDirection, IDvInvocationResponseString& aStatus);
private:
    DvProviderUpnpOrgConnectionManager2();
    void DoGetProtocolInfo(IDviInvocation& aInvocation, TUint aVersion);
    void DoPrepareForConnection(IDviInvocation& aInvocation, TUint aVersion);
    void DoConnectionComplete(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentConnectionIDs(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentConnectionInfo(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertySourceProtocolInfo;
    PropertyString* iPropertySinkProtocolInfo;
    PropertyString* iPropertyCurrentConnectionIDs;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER2

