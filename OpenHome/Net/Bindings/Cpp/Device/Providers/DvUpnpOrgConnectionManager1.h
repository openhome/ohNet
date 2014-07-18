#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER1CPP
#define HEADER_DVUPNPORGCONNECTIONMANAGER1CPP

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
 * Provider for the upnp.org:ConnectionManager:1 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgConnectionManager1Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgConnectionManager1Cpp() {}
    /**
     * Set the value of the SourceProtocolInfo property
     *
     * Can only be called if EnablePropertySourceProtocolInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySourceProtocolInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the SourceProtocolInfo property
     *
     * Can only be called if EnablePropertySourceProtocolInfo has previously been called.
     */
    void GetPropertySourceProtocolInfo(std::string& aValue);
    /**
     * Set the value of the SinkProtocolInfo property
     *
     * Can only be called if EnablePropertySinkProtocolInfo has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySinkProtocolInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the SinkProtocolInfo property
     *
     * Can only be called if EnablePropertySinkProtocolInfo has previously been called.
     */
    void GetPropertySinkProtocolInfo(std::string& aValue);
    /**
     * Set the value of the CurrentConnectionIDs property
     *
     * Can only be called if EnablePropertyCurrentConnectionIDs has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyCurrentConnectionIDs(const std::string& aValue);
    /**
     * Get a copy of the value of the CurrentConnectionIDs property
     *
     * Can only be called if EnablePropertyCurrentConnectionIDs has previously been called.
     */
    void GetPropertyCurrentConnectionIDs(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgConnectionManager1Cpp(DvDeviceStd& aDevice);
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
    virtual void GetProtocolInfo(IDvInvocationStd& aInvocation, std::string& aSource, std::string& aSink);
    /**
     * PrepareForConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * PrepareForConnection action for the owning device.
     * Must be implemented iff EnableActionPrepareForConnection was called.
     */
    virtual void PrepareForConnection(IDvInvocationStd& aInvocation, const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID);
    /**
     * ConnectionComplete action.
     *
     * Will be called when the device stack receives an invocation of the
     * ConnectionComplete action for the owning device.
     * Must be implemented iff EnableActionConnectionComplete was called.
     */
    virtual void ConnectionComplete(IDvInvocationStd& aInvocation, int32_t aConnectionID);
    /**
     * GetCurrentConnectionIDs action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionIDs action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionIDs was called.
     */
    virtual void GetCurrentConnectionIDs(IDvInvocationStd& aInvocation, std::string& aConnectionIDs);
    /**
     * GetCurrentConnectionInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionInfo action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionInfo was called.
     */
    virtual void GetCurrentConnectionInfo(IDvInvocationStd& aInvocation, int32_t aConnectionID, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus);
private:
    DvProviderUpnpOrgConnectionManager1Cpp();
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

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER1CPP

