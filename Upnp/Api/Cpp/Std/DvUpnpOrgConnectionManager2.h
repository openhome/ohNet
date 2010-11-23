#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER2CPP
#define HEADER_DVUPNPORGCONNECTIONMANAGER2CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the upnp.org:ConnectionManager:2 UPnP service
 */
class DvProviderUpnpOrgConnectionManager2Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgConnectionManager2Cpp() {}
    /**
     * Set the value of the SourceProtocolInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySourceProtocolInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the SourceProtocolInfo property
     */
    void GetPropertySourceProtocolInfo(std::string& aValue);
    /**
     * Set the value of the SinkProtocolInfo property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySinkProtocolInfo(const std::string& aValue);
    /**
     * Get a copy of the value of the SinkProtocolInfo property
     */
    void GetPropertySinkProtocolInfo(std::string& aValue);
    /**
     * Set the value of the CurrentConnectionIDs property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyCurrentConnectionIDs(const std::string& aValue);
    /**
     * Get a copy of the value of the CurrentConnectionIDs property
     */
    void GetPropertyCurrentConnectionIDs(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgConnectionManager2Cpp(DvDeviceStd& aDevice);
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
    virtual void GetProtocolInfo(uint32_t aVersion, std::string& aSource, std::string& aSink);
    /**
     * PrepareForConnection action.
     *
     * Will be called when the device stack receives an invocation of the
     * PrepareForConnection action for the owning device.
     * Must be implemented iff EnableActionPrepareForConnection was called.
     */
    virtual void PrepareForConnection(uint32_t aVersion, const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID);
    /**
     * ConnectionComplete action.
     *
     * Will be called when the device stack receives an invocation of the
     * ConnectionComplete action for the owning device.
     * Must be implemented iff EnableActionConnectionComplete was called.
     */
    virtual void ConnectionComplete(uint32_t aVersion, int32_t aConnectionID);
    /**
     * GetCurrentConnectionIDs action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionIDs action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionIDs was called.
     */
    virtual void GetCurrentConnectionIDs(uint32_t aVersion, std::string& aConnectionIDs);
    /**
     * GetCurrentConnectionInfo action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionInfo action for the owning device.
     * Must be implemented iff EnableActionGetCurrentConnectionInfo was called.
     */
    virtual void GetCurrentConnectionInfo(uint32_t aVersion, int32_t aConnectionID, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus);
private:
    DvProviderUpnpOrgConnectionManager2Cpp();
    void DoGetProtocolInfo(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoPrepareForConnection(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoConnectionComplete(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetCurrentConnectionIDs(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetCurrentConnectionInfo(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertySourceProtocolInfo;
    PropertyString* iPropertySinkProtocolInfo;
    PropertyString* iPropertyCurrentConnectionIDs;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER2CPP

