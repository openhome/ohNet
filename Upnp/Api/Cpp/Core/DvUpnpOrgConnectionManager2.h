#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER2
#define HEADER_DVUPNPORGCONNECTIONMANAGER2

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ConnectionManager:2
 */
class DvServiceUpnpOrgConnectionManager2 : public DvService
{
public:
    virtual ~DvServiceUpnpOrgConnectionManager2() {}
    void SetPropertySourceProtocolInfo(const Brx& aValue);
    void GetPropertySourceProtocolInfo(Brhz& aValue);
    void SetPropertySinkProtocolInfo(const Brx& aValue);
    void GetPropertySinkProtocolInfo(Brhz& aValue);
    void SetPropertyCurrentConnectionIDs(const Brx& aValue);
    void GetPropertyCurrentConnectionIDs(Brhz& aValue);
protected:
    DvServiceUpnpOrgConnectionManager2(DvDevice& aDevice);
    void EnableActionGetProtocolInfo();
    void EnableActionPrepareForConnection();
    void EnableActionConnectionComplete();
    void EnableActionGetCurrentConnectionIDs();
    void EnableActionGetCurrentConnectionInfo();
private:
    virtual void GetProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSource, IInvocationResponseString& aSink);
    virtual void PrepareForConnection(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IInvocationResponseInt& aConnectionID, IInvocationResponseInt& aAVTransportID, IInvocationResponseInt& aRcsID);
    virtual void ConnectionComplete(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID);
    virtual void GetCurrentConnectionIDs(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aConnectionIDs);
    virtual void GetCurrentConnectionInfo(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IInvocationResponseInt& aRcsID, IInvocationResponseInt& aAVTransportID, IInvocationResponseString& aProtocolInfo, IInvocationResponseString& aPeerConnectionManager, IInvocationResponseInt& aPeerConnectionID, IInvocationResponseString& aDirection, IInvocationResponseString& aStatus);
private:
    DvServiceUpnpOrgConnectionManager2();
    void DoGetProtocolInfo(IDvInvocation& aInvocation, TUint aVersion);
    void DoPrepareForConnection(IDvInvocation& aInvocation, TUint aVersion);
    void DoConnectionComplete(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentConnectionIDs(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetCurrentConnectionInfo(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertySourceProtocolInfo;
    PropertyString* iPropertySinkProtocolInfo;
    PropertyString* iPropertyCurrentConnectionIDs;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONNECTIONMANAGER2

