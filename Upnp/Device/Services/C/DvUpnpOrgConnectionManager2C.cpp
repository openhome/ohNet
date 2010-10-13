#include <C/DvUpnpOrgConnectionManager2.h>
#include <Core/DvUpnpOrgConnectionManager2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgConnectionManager2C : public DvServiceUpnpOrgConnectionManager2
{
public:
    DvServiceUpnpOrgConnectionManager2C(DvDevice& aDevice);
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

DvServiceUpnpOrgConnectionManager2C::DvServiceUpnpOrgConnectionManager2C(DvDevice& aDevice)
    : DvServiceUpnpOrgConnectionManager2(aDevice)
{
}

void DvServiceUpnpOrgConnectionManager2C::EnableActionGetProtocolInfo(CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr)
{
    iCallbackGetProtocolInfo = aCallback;
    iPtrGetProtocolInfo = aPtr;
    DvServiceUpnpOrgConnectionManager2::EnableActionGetProtocolInfo();
}

void DvServiceUpnpOrgConnectionManager2C::EnableActionPrepareForConnection(CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr)
{
    iCallbackPrepareForConnection = aCallback;
    iPtrPrepareForConnection = aPtr;
    DvServiceUpnpOrgConnectionManager2::EnableActionPrepareForConnection();
}

void DvServiceUpnpOrgConnectionManager2C::EnableActionConnectionComplete(CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr)
{
    iCallbackConnectionComplete = aCallback;
    iPtrConnectionComplete = aPtr;
    DvServiceUpnpOrgConnectionManager2::EnableActionConnectionComplete();
}

void DvServiceUpnpOrgConnectionManager2C::EnableActionGetCurrentConnectionIDs(CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionIDs = aCallback;
    iPtrGetCurrentConnectionIDs = aPtr;
    DvServiceUpnpOrgConnectionManager2::EnableActionGetCurrentConnectionIDs();
}

void DvServiceUpnpOrgConnectionManager2C::EnableActionGetCurrentConnectionInfo(CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr)
{
    iCallbackGetCurrentConnectionInfo = aCallback;
    iPtrGetCurrentConnectionInfo = aPtr;
    DvServiceUpnpOrgConnectionManager2::EnableActionGetCurrentConnectionInfo();
}

void DvServiceUpnpOrgConnectionManager2C::GetProtocolInfo(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSource, IInvocationResponseString& aSink)
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

void DvServiceUpnpOrgConnectionManager2C::PrepareForConnection(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRemoteProtocolInfo, const Brx& aPeerConnectionManager, TInt aPeerConnectionID, const Brx& aDirection, IInvocationResponseInt& aConnectionID, IInvocationResponseInt& aAVTransportID, IInvocationResponseInt& aRcsID)
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

void DvServiceUpnpOrgConnectionManager2C::ConnectionComplete(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID)
{
    ASSERT(iCallbackConnectionComplete != NULL);
    if (0 != iCallbackConnectionComplete(iPtrConnectionComplete, aVersion, aConnectionID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgConnectionManager2C::GetCurrentConnectionIDs(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aConnectionIDs)
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

void DvServiceUpnpOrgConnectionManager2C::GetCurrentConnectionInfo(IInvocationResponse& aResponse, TUint aVersion, TInt aConnectionID, IInvocationResponseInt& aRcsID, IInvocationResponseInt& aAVTransportID, IInvocationResponseString& aProtocolInfo, IInvocationResponseString& aPeerConnectionManager, IInvocationResponseInt& aPeerConnectionID, IInvocationResponseString& aDirection, IInvocationResponseString& aStatus)
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



THandle DvServiceUpnpOrgConnectionManager2Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgConnectionManager2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgConnectionManager2Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService);
}

void DvServiceUpnpOrgConnectionManager2EnableActionGetProtocolInfo(THandle aService, CallbackConnectionManager2GetProtocolInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->EnableActionGetProtocolInfo(aCallback, aPtr);
}

void DvServiceUpnpOrgConnectionManager2EnableActionPrepareForConnection(THandle aService, CallbackConnectionManager2PrepareForConnection aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->EnableActionPrepareForConnection(aCallback, aPtr);
}

void DvServiceUpnpOrgConnectionManager2EnableActionConnectionComplete(THandle aService, CallbackConnectionManager2ConnectionComplete aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->EnableActionConnectionComplete(aCallback, aPtr);
}

void DvServiceUpnpOrgConnectionManager2EnableActionGetCurrentConnectionIDs(THandle aService, CallbackConnectionManager2GetCurrentConnectionIDs aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->EnableActionGetCurrentConnectionIDs(aCallback, aPtr);
}

void DvServiceUpnpOrgConnectionManager2EnableActionGetCurrentConnectionInfo(THandle aService, CallbackConnectionManager2GetCurrentConnectionInfo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->EnableActionGetCurrentConnectionInfo(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgConnectionManager2SetPropertySourceProtocolInfo(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->SetPropertySourceProtocolInfo(buf);
    return 0;
}

void DvServiceUpnpOrgConnectionManager2GetPropertySourceProtocolInfo(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->GetPropertySourceProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceUpnpOrgConnectionManager2SetPropertySinkProtocolInfo(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->SetPropertySinkProtocolInfo(buf);
    return 0;
}

void DvServiceUpnpOrgConnectionManager2GetPropertySinkProtocolInfo(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->GetPropertySinkProtocolInfo(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDs(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->SetPropertyCurrentConnectionIDs(buf);
    return 0;
}

void DvServiceUpnpOrgConnectionManager2GetPropertyCurrentConnectionIDs(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgConnectionManager2C*>(aService)->GetPropertyCurrentConnectionIDs(buf);
    *aValue = (char*)buf.Transfer();
}

