#include <C/DvUpnpOrgConnectionManager1.h>
#include <Core/DvUpnpOrgConnectionManager1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgConnectionManager1C : public DvProviderUpnpOrgConnectionManager1
{
public:
    DvProviderUpnpOrgConnectionManager1C(DvDevice& aDevice);
    void EnableActionGetProtocolInfo(CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr);
    void EnableActionPrepareForConnection(CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr);
    void EnableActionConnectionComplete(CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionIDs(CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr);
    void EnableActionGetCurrentConnectionInfo(CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr);
private:
    void GetProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSource, IInvocationResponseString& aSink);
    void PrepareForConnection(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IInvocationResponseInt& aConnectionID, IInvocationResponseInt& aAVTransportID, IInvocationResponseInt& aRcsID);
    void ConnectionComplete(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID);
    void GetCurrentConnectionIDs(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aConnectionIDs);
    void GetCurrentConnectionInfo(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IInvocationResponseInt& aRcsID, IInvocationResponseInt& aAVTransportID, IInvocationResponseString& aProtocolInfo, IInvocationResponseString& aPeerConnectionManager, IInvocationResponseInt& aPeerConnectionID, IInvocationResponseString& aDirection, IInvocationResponseString& aStatus);
private:
    CallbackConnectionManager1GetProtocolInfo iCallbackGetProtocolInfo;
    void* iPtrGetProtocolInfo;
    CallbackConnectionManager1PrepareForConnection iCallbackPrepareForConnection;
    void* iPtrPrepareForConnection;
    CallbackConnectionManager1ConnectionComplete iCallbackConnectionComplete;
    void* iPtrConnectionComplete;
    CallbackConnectionManager1GetCurrentConnectionIDs iCallbackGetCurrentConnectionIDs;
    void* iPtrGetCurrentConnectionIDs;
    CallbackConnectionManager1GetCurrentConnectionInfo iCallbackGetCurrentConnectionInfo;
    void* iPtrGetCurrentConnectionInfo;
};

DvProviderUpnpOrgConnectionManager1C::DvProviderUpnpOrgConnectionManager1C(DvDevice& aDevice)
    : DvProviderUpnpOrgConnectionManager1(aDevice)
{
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionGetProtocolInfo(CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr)
{
    iCallbackGetProtocolInfo = aCallback;
    iPtrGetProtocolInfo = aPtr;
    DvProviderUpnpOrgConnectionManager1::EnableActionGetProtocolInfo();
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionPrepareForConnection(CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr)
{
    iCallbackPrepareForConnection = aCallback;
    iPtrPrepareForConnection = aPtr;
    DvProviderUpnpOrgConnectionManager1::EnableActionPrepareForConnection();
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionConnectionComplete(CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr)
{
    iCallbackConnectionComplete = aCallback;
    iPtrConnectionComplete = aPtr;
    DvProviderUpnpOrgConnectionManager1::EnableActionConnectionComplete();
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionGetCurrentConnectionIDs(CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionIDs = aCallback;
    iPtrGetCurrentConnectionIDs = aPtr;
    DvProviderUpnpOrgConnectionManager1::EnableActionGetCurrentConnectionIDs();
}

void DvProviderUpnpOrgConnectionManager1C::EnableActionGetCurrentConnectionInfo(CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionInfo = aCallback;
    iPtrGetCurrentConnectionInfo = aPtr;
    DvProviderUpnpOrgConnectionManager1::EnableActionGetCurrentConnectionInfo();
}

void DvProviderUpnpOrgConnectionManager1C::GetProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSource, IInvocationResponseString& aSink)
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

void DvProviderUpnpOrgConnectionManager1C::PrepareForConnection(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IInvocationResponseInt& aConnectionID, IInvocationResponseInt& aAVTransportID, IInvocationResponseInt& aRcsID)
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

void DvProviderUpnpOrgConnectionManager1C::ConnectionComplete(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID)
{
    ASSERT(iCallbackConnectionComplete != NULL);
    if (0 != iCallbackConnectionComplete(iPtrConnectionComplete, aVersion, aConnectionID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgConnectionManager1C::GetCurrentConnectionIDs(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aConnectionIDs)
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

void DvProviderUpnpOrgConnectionManager1C::GetCurrentConnectionInfo(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IInvocationResponseInt& aRcsID, IInvocationResponseInt& aAVTransportID, IInvocationResponseString& aProtocolInfo, IInvocationResponseString& aPeerConnectionManager, IInvocationResponseInt& aPeerConnectionID, IInvocationResponseString& aDirection, IInvocationResponseString& aStatus)
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



THandle DvProviderUpnpOrgConnectionManager1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgConnectionManager1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgConnectionManager1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider);
}

void DvProviderUpnpOrgConnectionManager1EnableActionGetProtocolInfo(THandle aProvider, CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionGetProtocolInfo(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager1EnableActionPrepareForConnection(THandle aProvider, CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionPrepareForConnection(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager1EnableActionConnectionComplete(THandle aProvider, CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionConnectionComplete(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(THandle aProvider, CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionGetCurrentConnectionIDs(aCallback, aPtr);
}

void DvProviderUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(THandle aProvider, CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->EnableActionGetCurrentConnectionInfo(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->SetPropertySourceProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->GetPropertySourceProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->SetPropertySinkProtocolInfo(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->GetPropertySinkProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->SetPropertyCurrentConnectionIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgConnectionManager1C*>(aProvider)->GetPropertyCurrentConnectionIDs(buf);
    *aValue = (char*)buf.Transfer();
}

