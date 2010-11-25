#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER1
#define HEADER_DVUPNPORGCONNECTIONMANAGER1

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
 * Provider for the upnp.org:ConnectionManager:1 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgConnectionManager1 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgConnectionManager1() {}
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
    DvProviderUpnpOrgConnectionManager1(DvDevice& aDevice);
    /**
     * Signal that the action GetProtocolInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetProtocolInfo must be overridden if this is called.
     */
    void EnableActionGetProtocolInfo();
    /**
     * Signal that the action PrepareForConnection is supported.
     * The action's availability will be published in the device's service.xml.
     * DoPrepareForConnection must be overridden if this is called.
     */
    void EnableActionPrepareForConnection();
    /**
     * Signal that the action ConnectionComplete is supported.
     * The action's availability will be published in the device's service.xml.
     * DoConnectionComplete must be overridden if this is called.
     */
    void EnableActionConnectionComplete();
    /**
     * Signal that the action GetCurrentConnectionIDs is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetCurrentConnectionIDs must be overridden if this is called.
     */
    void EnableActionGetCurrentConnectionIDs();
    /**
     * Signal that the action GetCurrentConnectionInfo is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetCurrentConnectionInfo must be overridden if this is called.
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
    virtual void GetProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSource, IInvocationResponseString& aSink);
    /**
     * PrepareForConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * PrepareForConnection action for the owning device.
     * Must be implemented iff EnableActionPrepareForConnection was called.
     */
    virtual void PrepareForConnection(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IInvocationResponseInt& aConnectionID, IInvocationResponseInt& aAVTransportID, IInvocationResponseInt& aRcsID);
    /**
     * ConnectionComplete action.
     *
     * Will be called when the device stack receives an invocation of the
     * ConnectionComplete action for the owning device.
     * Must be implemented iff EnableActionConnectionComplete was called.
     */
    virtual void ConnectionComplete(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID);
    /**
     * GetCurrentConnectionIDs action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionIDs action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionIDs was called.
     */
    virtual void GetCurrentConnectionIDs(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aConnectionIDs);
    /**
     * GetCurrentConnectionInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionInfo action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionInfo was called.
     */
    virtual void GetCurrentConnectionInfo(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IInvocationResponseInt& aRcsID, IInvocationResponseInt& aAVTransportID, IInvocationResponseString& aProtocolInfo, IInvocationResponseString& aPeerConnectionManager, IInvocationResponseInt& aPeerConnectionID, IInvocationResponseString& aDirection, IInvocationResponseString& aStatus);
private:
    DvProviderUpnpOrgConnectionManager1();
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

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER1

