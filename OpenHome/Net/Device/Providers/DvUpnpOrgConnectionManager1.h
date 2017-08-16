#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER1
#define HEADER_DVUPNPORGCONNECTIONMANAGER1

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
     * Can only be called if EnablePropertySourceProtocolInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySourceProtocolInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the SourceProtocolInfo property
     *
     * Can only be called if EnablePropertySourceProtocolInfo has previously been called.
     */
    void GetPropertySourceProtocolInfo(Brhz& aValue);
    /**
     * Output the value of the SourceProtocolInfo property without an intermediate copy.
     *
     * Can only be called if EnablePropertySourceProtocolInfo has previously been called.
     */
    void WritePropertySourceProtocolInfo(IWriter& aWriter);
    /**
     * Set the value of the SinkProtocolInfo property
     *
     * Can only be called if EnablePropertySinkProtocolInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySinkProtocolInfo(const Brx& aValue);
    /**
     * Get a copy of the value of the SinkProtocolInfo property
     *
     * Can only be called if EnablePropertySinkProtocolInfo has previously been called.
     */
    void GetPropertySinkProtocolInfo(Brhz& aValue);
    /**
     * Output the value of the SinkProtocolInfo property without an intermediate copy.
     *
     * Can only be called if EnablePropertySinkProtocolInfo has previously been called.
     */
    void WritePropertySinkProtocolInfo(IWriter& aWriter);
    /**
     * Set the value of the CurrentConnectionIDs property
     *
     * Can only be called if EnablePropertyCurrentConnectionIDs has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyCurrentConnectionIDs(const Brx& aValue);
    /**
     * Get a copy of the value of the CurrentConnectionIDs property
     *
     * Can only be called if EnablePropertyCurrentConnectionIDs has previously been called.
     */
    void GetPropertyCurrentConnectionIDs(Brhz& aValue);
    /**
     * Output the value of the CurrentConnectionIDs property without an intermediate copy.
     *
     * Can only be called if EnablePropertyCurrentConnectionIDs has previously been called.
     */
    void WritePropertyCurrentConnectionIDs(IWriter& aWriter);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgConnectionManager1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgConnectionManager1(DviDevice& aDevice);
    /**
     * Enable the SourceProtocolInfo property.
     */
    void EnablePropertySourceProtocolInfo();
    /**
     * Enable the SinkProtocolInfo property.
     */
    void EnablePropertySinkProtocolInfo();
    /**
     * Enable the CurrentConnectionIDs property.
     */
    void EnablePropertyCurrentConnectionIDs();
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
    virtual void GetProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aSource, IDvInvocationResponseString& aSink);
    /**
     * PrepareForConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * PrepareForConnection action for the owning device.
     * Must be implemented iff EnableActionPrepareForConnection was called.
     */
    virtual void PrepareForConnection(IDvInvocation& aInvocation, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IDvInvocationResponseInt& aConnectionID, IDvInvocationResponseInt& aAVTransportID, IDvInvocationResponseInt& aRcsID);
    /**
     * ConnectionComplete action.
     *
     * Will be called when the device stack receives an invocation of the
     * ConnectionComplete action for the owning device.
     * Must be implemented iff EnableActionConnectionComplete was called.
     */
    virtual void ConnectionComplete(IDvInvocation& aInvocation, TInt aConnectionID);
    /**
     * GetCurrentConnectionIDs action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionIDs action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionIDs was called.
     */
    virtual void GetCurrentConnectionIDs(IDvInvocation& aInvocation, IDvInvocationResponseString& aConnectionIDs);
    /**
     * GetCurrentConnectionInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionInfo action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionInfo was called.
     */
    virtual void GetCurrentConnectionInfo(IDvInvocation& aInvocation, TInt aConnectionID, IDvInvocationResponseInt& aRcsID, IDvInvocationResponseInt& aAVTransportID, IDvInvocationResponseString& aProtocolInfo, IDvInvocationResponseString& aPeerConnectionManager, IDvInvocationResponseInt& aPeerConnectionID, IDvInvocationResponseString& aDirection, IDvInvocationResponseString& aStatus);
private:
    DvProviderUpnpOrgConnectionManager1();
    void Construct();
    void DoGetProtocolInfo(IDviInvocation& aInvocation);
    void DoPrepareForConnection(IDviInvocation& aInvocation);
    void DoConnectionComplete(IDviInvocation& aInvocation);
    void DoGetCurrentConnectionIDs(IDviInvocation& aInvocation);
    void DoGetCurrentConnectionInfo(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertySourceProtocolInfo;
    PropertyString* iPropertySinkProtocolInfo;
    PropertyString* iPropertyCurrentConnectionIDs;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER1

