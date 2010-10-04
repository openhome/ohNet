#include <C/CpUpnpOrgConnectionManager1.h>
#include <Core/CpUpnpOrgConnectionManager1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgConnectionManager1C : public CpProxyC
{
public:
    CpProxyUpnpOrgConnectionManager1C(CpDeviceC aDevice);
    CpProxyUpnpOrgConnectionManager1* Proxy() { return static_cast<CpProxyUpnpOrgConnectionManager1*>(iProxy); }
};

CpProxyUpnpOrgConnectionManager1C::CpProxyUpnpOrgConnectionManager1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgConnectionManager1(*iDevice);
}


THandle CpProxyUpnpOrgConnectionManager1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgConnectionManager1C(aDevice);
}

void CpProxyUpnpOrgConnectionManager1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgConnectionManager1SyncGetProtocolInfo(THandle aHandle, char** aSource, char** aSink)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSource;
    Brh buf_aSink;
    proxyC->Proxy()->SyncGetProtocolInfo(buf_aSource, buf_aSink);
    *aSource = buf_aSource.Extract();
    *aSink = buf_aSink.Extract();
}

void CpProxyUpnpOrgConnectionManager1BeginGetProtocolInfo(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetProtocolInfo(functor);
}

int32_t CpProxyUpnpOrgConnectionManager1EndGetProtocolInfo(THandle aHandle, ZappHandleAsync aAsync, char** aSource, char** aSink)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSource;
    *aSource = NULL;
    Brh buf_aSink;
    *aSink = NULL;
    try {
        proxyC->Proxy()->EndGetProtocolInfo(*async, buf_aSource, buf_aSink);
        *aSource = buf_aSource.Extract();
        *aSink = buf_aSink.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgConnectionManager1SyncPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRemoteProtocolInfo(aRemoteProtocolInfo);
    Brh buf_aPeerConnectionManager(aPeerConnectionManager);
    Brh buf_aDirection(aDirection);
    proxyC->Proxy()->SyncPrepareForConnection(buf_aRemoteProtocolInfo, buf_aPeerConnectionManager, aPeerConnectionID, buf_aDirection, *aConnectionID, *aAVTransportID, *aRcsID);
}

void CpProxyUpnpOrgConnectionManager1BeginPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRemoteProtocolInfo(aRemoteProtocolInfo);
    Brh buf_aPeerConnectionManager(aPeerConnectionManager);
    Brh buf_aDirection(aDirection);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPrepareForConnection(buf_aRemoteProtocolInfo, buf_aPeerConnectionManager, aPeerConnectionID, buf_aDirection, functor);
}

int32_t CpProxyUpnpOrgConnectionManager1EndPrepareForConnection(THandle aHandle, ZappHandleAsync aAsync, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPrepareForConnection(*async, *aConnectionID, *aAVTransportID, *aRcsID);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgConnectionManager1SyncConnectionComplete(THandle aHandle, int32_t aConnectionID)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncConnectionComplete(aConnectionID);
}

void CpProxyUpnpOrgConnectionManager1BeginConnectionComplete(THandle aHandle, int32_t aConnectionID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginConnectionComplete(aConnectionID, functor);
}

int32_t CpProxyUpnpOrgConnectionManager1EndConnectionComplete(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndConnectionComplete(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgConnectionManager1SyncGetCurrentConnectionIDs(THandle aHandle, char** aConnectionIDs)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aConnectionIDs;
    proxyC->Proxy()->SyncGetCurrentConnectionIDs(buf_aConnectionIDs);
    *aConnectionIDs = buf_aConnectionIDs.Extract();
}

void CpProxyUpnpOrgConnectionManager1BeginGetCurrentConnectionIDs(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetCurrentConnectionIDs(functor);
}

int32_t CpProxyUpnpOrgConnectionManager1EndGetCurrentConnectionIDs(THandle aHandle, ZappHandleAsync aAsync, char** aConnectionIDs)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aConnectionIDs;
    *aConnectionIDs = NULL;
    try {
        proxyC->Proxy()->EndGetCurrentConnectionIDs(*async, buf_aConnectionIDs);
        *aConnectionIDs = buf_aConnectionIDs.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgConnectionManager1SyncGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aProtocolInfo;
    Brh buf_aPeerConnectionManager;
    Brh buf_aDirection;
    Brh buf_aStatus;
    proxyC->Proxy()->SyncGetCurrentConnectionInfo(aConnectionID, *aRcsID, *aAVTransportID, buf_aProtocolInfo, buf_aPeerConnectionManager, *aPeerConnectionID, buf_aDirection, buf_aStatus);
    *aProtocolInfo = buf_aProtocolInfo.Extract();
    *aPeerConnectionManager = buf_aPeerConnectionManager.Extract();
    *aDirection = buf_aDirection.Extract();
    *aStatus = buf_aStatus.Extract();
}

void CpProxyUpnpOrgConnectionManager1BeginGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetCurrentConnectionInfo(aConnectionID, functor);
}

int32_t CpProxyUpnpOrgConnectionManager1EndGetCurrentConnectionInfo(THandle aHandle, ZappHandleAsync aAsync, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aProtocolInfo;
    *aProtocolInfo = NULL;
    Brh buf_aPeerConnectionManager;
    *aPeerConnectionManager = NULL;
    Brh buf_aDirection;
    *aDirection = NULL;
    Brh buf_aStatus;
    *aStatus = NULL;
    try {
        proxyC->Proxy()->EndGetCurrentConnectionInfo(*async, *aRcsID, *aAVTransportID, buf_aProtocolInfo, buf_aPeerConnectionManager, *aPeerConnectionID, buf_aDirection, buf_aStatus);
        *aProtocolInfo = buf_aProtocolInfo.Extract();
        *aPeerConnectionManager = buf_aPeerConnectionManager.Extract();
        *aDirection = buf_aDirection.Extract();
        *aStatus = buf_aStatus.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgConnectionManager1SetPropertySourceProtocolInfoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySourceProtocolInfoChanged(functor);
}

void CpProxyUpnpOrgConnectionManager1SetPropertySinkProtocolInfoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySinkProtocolInfoChanged(functor);
}

void CpProxyUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyCurrentConnectionIDsChanged(functor);
}

void CpProxyUpnpOrgConnectionManager1PropertySourceProtocolInfo(THandle aHandle, char** aSourceProtocolInfo)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSourceProtocolInfo;
    proxyC->Proxy()->PropertySourceProtocolInfo(buf_aSourceProtocolInfo);
    *aSourceProtocolInfo = buf_aSourceProtocolInfo.Transfer();
}

void CpProxyUpnpOrgConnectionManager1PropertySinkProtocolInfo(THandle aHandle, char** aSinkProtocolInfo)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSinkProtocolInfo;
    proxyC->Proxy()->PropertySinkProtocolInfo(buf_aSinkProtocolInfo);
    *aSinkProtocolInfo = buf_aSinkProtocolInfo.Transfer();
}

void CpProxyUpnpOrgConnectionManager1PropertyCurrentConnectionIDs(THandle aHandle, char** aCurrentConnectionIDs)
{
    CpProxyUpnpOrgConnectionManager1C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aCurrentConnectionIDs;
    proxyC->Proxy()->PropertyCurrentConnectionIDs(buf_aCurrentConnectionIDs);
    *aCurrentConnectionIDs = buf_aCurrentConnectionIDs.Transfer();
}

