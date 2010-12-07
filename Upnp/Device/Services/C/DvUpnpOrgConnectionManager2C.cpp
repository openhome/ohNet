#include <C/DvUpnpOrgConnectionManager2.h>
#include <Core/DvUpnpOrgConnectionManager2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgConnectionManager2C : public DvProviderUpnpOrgConnectionManager2
{
public:
    DvProviderUpnpOrgConnectionManager2C(DvDevice& aDevice);
    void EnableActionGetProtocolInfo(CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr);
    void EnableActionPrepareForConnection(CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr);
    void EnableActionConnectionComplete(CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionIDs(CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionInfo(CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr);
private:
    void GetProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSource, IInvocationResponseString& aSink);
    void PrepareForConnection(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IInvocationResponseInt& aConnectionID, IInvocationResponseInt& aAVTransportID, IInvocationResponseInt& aRcsID);
    void ConnectionComplete(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID);
    void GetCurrentConnectionIDs(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aConnectionIDs);
    void GetCurrentConnectionInfo(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IInvocationResponseInt& aRcsID, IInvocationResponseInt& aAVTransportID, IInvocationResponseString& aProtocolInfo, IInvocationResponseString& aPeerConnectionManager, IInvocationResponseInt& aPeerConnectionID, IInvocationResponseString& aDirection, IInvocationResponseString& aStatus);
private:
    CallbackConnectionManager2GetProtocolInfo iCallbackGetProtocolInfo;
    void* iPtrGetProtocolInfo;
    CallbackConnectionManager2PrepareForConnection iCallbackPrepareForConnection;
    void* iPtrPrepareForConnection;
    CallbackConnectionManager2ConnectionComplete iCallbackConnectionComplete;
    void* iPtrConnectionComplete;
    CallbackConnectionManager2GetCurrentConnectionIDs iCallbackGetCurrentConnectionIDs;
    void* iPtrGetCurrentConnectionIDs;
    CallbackConnectionManager2GetCurrentConnectionInfo iCallbackGetCurrentConnectionInfo;
    void* iPtrGetCurrentConnectionInfo;
};

DvProviderUpnpOrgConnectionManager2C::DvProviderUpnpOrgConnectionManager2C(DvDevice& aDevice)
    : DvProviderUpnpOrgConnectionManager2(aDevice)
{
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionGetProtocolInfo(CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr)
{
    iCallbackGetProtocolInfo = aCallback;
    iPtrGetProtocolInfo = aPtr;
    DvProviderUpnpOrgConnectionManager2::EnableActionGetProtocolInfo();
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionPrepareForConnection(CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr)
{
    iCallbackPrepareForConnection = aCallback;
    iPtrPrepareForConnection = aPtr;
    DvProviderUpnpOrgConnectionManager2::EnableActionPrepareForConnection();
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionConnectionComplete(CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr)
{
    iCallbackConnectionComplete = aCallback;
    iPtrConnectionComplete = aPtr;
    DvProviderUpnpOrgConnectionManager2::EnableActionConnectionComplete();
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionGetCurrentConnectionIDs(CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionIDs = aCallback;
    iPtrGetCurrentConnectionIDs = aPtr;
    DvProviderUpnpOrgConnectionManager2::EnableActionGetCurrentConnectionIDs();
}

void DvProviderUpnpOrgConnectionManager2C::EnableActionGetCurrentConnectionInfo(CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionInfo = aCallback;
    iPtrGetCurrentConnectionInfo = aPtr;
    DvProviderUpnpOrgConnectionManager2::EnableActionGetCurrentConnectionInfo();
}

void DvProviderUpnpOrgConnectionManager2C::GetProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSource, IInvocationResponseString& aSink)
{
    char* Source;
    char* Sink;
    ASSERT(iCallbackGetProtocolInfo != NULL);
    if (0 != iCallbackGetProtocolInfo(iPtrGetProtocolInfo, aVersion, &Source, &Sink)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufSource((const TChar*)Source);
    ZappFreeExternal(Source);
    aSource.Write(bufSource);
    aSource.WriteFlush();
    Brhz bufSink((const TChar*)Sink);
    ZappFreeExternal(Sink);
    aSink.Write(bufSink);
    aSink.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgConnectionManager2C::PrepareForConnection(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IInvocationResponseInt& aConnectionID, IInvocationResponseInt& aAVTransportID, IInvocationResponseInt& aRcsID)
{
    int32_t ConnectionID;
    int32_t AVTransportID;
    int32_t RcsID;
    ASSERT(iCallbackPrepareForConnection != NULL);
    if (0 != iCallbackPrepareForConnection(iPtrPrepareForConnection, aVersion, (const char*)aRemoteProtocolInfo.Ptr(), (const char*)aPeerConnectionManager.Ptr(), aPeerConnectionID, (const char*)aDirection.Ptr(), &ConnectionID, &AVTransportID, &RcsID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aConnectionID.Write(ConnectionID);
    aAVTransportID.Write(AVTransportID);
    aRcsID.Write(RcsID);
    aResponse.End();
}

void DvProviderUpnpOrgConnectionManager2C::ConnectionComplete(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID)
{
    ASSERT(iCallbackConnectionComplete != NULL);
    if (0 != iCallbackConnectionComplete(iPtrConnectionComplete, aVersion, aConnectionID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgConnectionManager2C::GetCurrentConnectionIDs(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aConnectionIDs)
{
    char* ConnectionIDs;
    ASSERT(iCallbackGetCurrentConnectionIDs != NULL);
    if (0 != iCallbackGetCurrentConnectionIDs(iPtrGetCurrentConnectionIDs, aVersion, &ConnectionIDs)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufConnectionIDs((const TChar*)ConnectionIDs);
    ZappFreeExternal(ConnectionIDs);
    aConnectionIDs.Write(bufConnectionIDs);
    aConnectionIDs.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgConnectionManager2C::GetCurrentConnectionInfo(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IInvocationResponseInt& aRcsID, IInvocationResponseInt& aAVTransportID, IInvocationResponseString& aProtocolInfo, IInvocationResponseString& aPeerConnectionManager, IInvocationResponseInt& aPeerConnectionID, IInvocationResponseString& aDirection, IInvocationResponseString& aStatus)
{
    int32_t RcsID;
    int32_t AVTransportID;
    char* ProtocolInfo;
    char* PeerConnectionManager;
    int32_t PeerConnectionID;
    char* Direction;
    char* Status;
    ASSERT(iCallbackGetCurrentConnectionInfo != NULL);
    if (0 != iCallbackGetCurrentConnectionInfo(iPtrGetCurrentConnectionInfo, aVersion, aConnectionID, &RcsID, &AVTransportID, &ProtocolInfo, &PeerConnectionManager, &PeerConnectionID, &Direction, &Status)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aRcsID.Write(RcsID);
    aAVTransportID.Write(AVTransportID);
    Brhz bufProtocolInfo((const TChar*)ProtocolInfo);
    ZappFreeExternal(ProtocolInfo);
    aProtocolInfo.Write(bufProtocolInfo);
    aProtocolInfo.WriteFlush();
    Brhz bufPeerConnectionManager((const TChar*)PeerConnectionManager);
    ZappFreeExternal(PeerConnectionManager);
    aPeerConnectionManager.Write(bufPeerConnectionManager);
    aPeerConnectionManager.WriteFlush();
    aPeerConnectionID.Write(PeerConnectionID);
    Brhz bufDirection((const TChar*)Direction);
    ZappFreeExternal(Direction);
    aDirection.Write(bufDirection);
    aDirection.WriteFlush();
    Brhz bufStatus((const TChar*)Status);
    ZappFreeExternal(Status);
    aStatus.Write(bufStatus);
    aStatus.WriteFlush();
    aResponse.End();
}



THandle DvProviderUpnpOrgConnectionManager2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgConnectionManager2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgConnectionManager2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider);
}

void DvProviderUpnpOrgConnectionManager2EnableActionGetProtocolInfo(THandle aProvider, CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionGetProtocolInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager2EnableActionPrepareForConnection(THandle aProvider, CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionPrepareForConnection(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager2EnableActionConnectionComplete(THandle aProvider, CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionConnectionComplete(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionIDs(THandle aProvider, CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionGetCurrentConnectionIDs(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager2EnableActionGetCurrentConnectionInfo(THandle aProvider, CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->EnableActionGetCurrentConnectionInfo(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgConnectionManager2SetPropertySourceProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->SetPropertySourceProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager2GetPropertySourceProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->GetPropertySourceProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgConnectionManager2SetPropertySinkProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->SetPropertySinkProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager2GetPropertySinkProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->GetPropertySinkProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->SetPropertyCurrentConnectionIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager2GetPropertyCurrentConnectionIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager2C*>(aProvider)->GetPropertyCurrentConnectionIDs(buf);
    *aValue = (char*)buf.Transfer();
}

