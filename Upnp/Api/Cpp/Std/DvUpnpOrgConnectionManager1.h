#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER1CPP
#define HEADER_DVUPNPORGCONNECTIONMANAGER1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ConnectionManager:1
 */
class DvServiceUpnpOrgConnectionManager1Cpp : public DvService
{
public:
    virtual ~DvServiceUpnpOrgConnectionManager1Cpp() {}
    void SetPropertySourceProtocolInfo(const std::string& aValue);
    void GetPropertySourceProtocolInfo(std::string& aValue);
    void SetPropertySinkProtocolInfo(const std::string& aValue);
    void GetPropertySinkProtocolInfo(std::string& aValue);
    void SetPropertyCurrentConnectionIDs(const std::string& aValue);
    void GetPropertyCurrentConnectionIDs(std::string& aValue);
protected:
    DvServiceUpnpOrgConnectionManager1Cpp(DvDeviceStd& aDevice);
    void EnableActionGetProtocolInfo();
    void EnableActionPrepareForConnection();
    void EnableActionConnectionComplete();
    void EnableActionGetCurrentConnectionIDs();
    void EnableActionGetCurrentConnectionInfo();
private:
    virtual void GetProtocolInfo(uint32_t aVersion, std::string& aSource, std::string& aSink);
    virtual void PrepareForConnection(uint32_t aVersion, const std::string& aRemoteProtocolInfo, const std::string& aPeerConnectionManager, int32_t aPeerConnectionID, const std::string& aDirection, int32_t& aConnectionID, int32_t& aAVTransportID, int32_t& aRcsID);
    virtual void ConnectionComplete(uint32_t aVersion, int32_t aConnectionID);
    virtual void GetCurrentConnectionIDs(uint32_t aVersion, std::string& aConnectionIDs);
    virtual void GetCurrentConnectionInfo(uint32_t aVersion, int32_t aConnectionID, int32_t& aRcsID, int32_t& aAVTransportID, std::string& aProtocolInfo, std::string& aPeerConnectionManager, int32_t& aPeerConnectionID, std::string& aDirection, std::string& aStatus);
private:
    DvServiceUpnpOrgConnectionManager1Cpp();
    void DoGetProtocolInfo(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoPrepareForConnection(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoConnectionComplete(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetCurrentConnectionIDs(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetCurrentConnectionInfo(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertySourceProtocolInfo;
    PropertyString* iPropertySinkProtocolInfo;
    PropertyString* iPropertyCurrentConnectionIDs;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER1CPP

