#include <C/DvUpnpOrgConnectionManager1.h>
#include <Core/DvUpnpOrgConnectionManager1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgConnectionManager1C : public DvServiceUpnpOrgConnectionManager1
{
public:
    DvServiceUpnpOrgConnectionManager1C(DvDevice& aDevice);
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

DvServiceUpnpOrgConnectionManager1C::DvServiceUpnpOrgConnectionManager1C(DvDevice& aDevice)
    : DvServiceUpnpOrgConnectionManager1(aDevice)
{
}

void DvServiceUpnpOrgConnectionManager1C::EnableActionGetProtocolInfo(CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr)
{
    iCallbackGetProtocolInfo = aCallback;
    iPtrGetProtocolInfo = aPtr;
    DvServiceUpnpOrgConnectionManager1::EnableActionGetProtocolInfo();
}

void DvServiceUpnpOrgConnectionManager1C::EnableActionPrepareForConnection(CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr)
{
    iCallbackPrepareForConnection = aCallback;
    iPtrPrepareForConnection = aPtr;
    DvServiceUpnpOrgConnectionManager1::EnableActionPrepareForConnection();
}

void DvServiceUpnpOrgConnectionManager1C::EnableActionConnectionComplete(CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr)
{
    iCallbackConnectionComplete = aCallback;
    iPtrConnectionComplete = aPtr;
    DvServiceUpnpOrgConnectionManager1::EnableActionConnectionComplete();
}

void DvServiceUpnpOrgConnectionManager1C::EnableActionGetCurrentConnectionIDs(CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionIDs = aCallback;
    iPtrGetCurrentConnectionIDs = aPtr;
    DvServiceUpnpOrgConnectionManager1::EnableActionGetCurrentConnectionIDs();
}

void DvServiceUpnpOrgConnectionManager1C::EnableActionGetCurrentConnectionInfo(CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionInfo = aCallback;
    iPtrGetCurrentConnectionInfo = aPtr;
    DvServiceUpnpOrgConnectionManager1::EnableActionGetCurrentConnectionInfo();
}

void DvServiceUpnpOrgConnectionManager1C::GetProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSource, IInvocationResponseString& aSink)
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

void DvServiceUpnpOrgConnectionManager1C::PrepareForConnection(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IInvocationResponseInt& aConnectionID, IInvocationResponseInt& aAVTransportID, IInvocationResponseInt& aRcsID)
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

void DvServiceUpnpOrgConnectionManager1C::ConnectionComplete(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID)
{
    ASSERT(iCallbackConnectionComplete != NULL);
    if (0 != iCallbackConnectionComplete(iPtrConnectionComplete, aVersion, aConnectionID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgConnectionManager1C::GetCurrentConnectionIDs(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aConnectionIDs)
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

void DvServiceUpnpOrgConnectionManager1C::GetCurrentConnectionInfo(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IInvocationResponseInt& aRcsID, IInvocationResponseInt& aAVTransportID, IInvocationResponseString& aProtocolInfo, IInvocationResponseString& aPeerConnectionManager, IInvocationResponseInt& aPeerConnectionID, IInvocationResponseString& aDirection, IInvocationResponseString& aStatus)
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



THandle DvServiceUpnpOrgConnectionManager1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgConnectionManager1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgConnectionManager1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService);
}

void DvServiceUpnpOrgConnectionManager1EnableActionGetProtocolInfo(THandle aService, CallbackConnectionManager1GetProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->EnableActionGetProtocolInfo(aCallback, aPtr);
}

void DvServiceUpnpOrgConnectionManager1EnableActionPrepareForConnection(THandle aService, CallbackConnectionManager1PrepareForConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->EnableActionPrepareForConnection(aCallback, aPtr);
}

void DvServiceUpnpOrgConnectionManager1EnableActionConnectionComplete(THandle aService, CallbackConnectionManager1ConnectionComplete aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->EnableActionConnectionComplete(aCallback, aPtr);
}

void DvServiceUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(THandle aService, CallbackConnectionManager1GetCurrentConnectionIDs aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->EnableActionGetCurrentConnectionIDs(aCallback, aPtr);
}

void DvServiceUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(THandle aService, CallbackConnectionManager1GetCurrentConnectionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->EnableActionGetCurrentConnectionInfo(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->SetPropertySourceProtocolInfo(buf);
    return 0;
}

void DvServiceUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->GetPropertySourceProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->SetPropertySinkProtocolInfo(buf);
    return 0;
}

void DvServiceUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->GetPropertySinkProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->SetPropertyCurrentConnectionIDs(buf);
    return 0;
}

void DvServiceUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgConnectionManager1C*>(aService)->GetPropertyCurrentConnectionIDs(buf);
    *aValue = (char*)buf.Transfer();
}

