#ifndef HEADER_DVUPNPORGCONNECTIONMANAGER2
#define HEADER_DVUPNPORGCONNECTIONMANAGER2

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ConnectionManager:2
 */
class DvProviderUpnpOrgConnectionManager2 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgConnectionManager2() {}
    TBool SetPropertySourceProtocolInfo(const Brx& aValue);
    void GetPropertySourceProtocolInfo(Brhz& aValue);
    TBool SetPropertySinkProtocolInfo(const Brx& aValue);
    void GetPropertySinkProtocolInfo(Brhz& aValue);
    TBool SetPropertyCurrentConnectionIDs(const Brx& aValue);
    void GetPropertyCurrentConnectionIDs(Brhz& aValue);
protected:
    DvProviderUpnpOrgConnectionManager2(DvDevice& aDevice);
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
    DvProviderUpnpOrgConnectionManager2();
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

