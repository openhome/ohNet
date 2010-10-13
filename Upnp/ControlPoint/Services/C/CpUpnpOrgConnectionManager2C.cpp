#include <C/CpUpnpOrgConnectionManager2.h>
#include <Core/CpUpnpOrgConnectionManager2.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgConnectionManager2C : public CpProxyC
{
public:
    CpProxyUpnpOrgConnectionManager2C(CpDeviceC aDevice);
    CpProxyUpnpOrgConnectionManager2* Proxy() { return static_cast<CpProxyUpnpOrgConnectionManager2*>(iProxy); }
};

CpProxyUpnpOrgConnectionManager2C::CpProxyUpnpOrgConnectionManager2C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgConnectionManager2(*iDevice);
}


THandle CpProxyUpnpOrgConnectionManager2Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgConnectionManager2C(aDevice);
}

void CpProxyUpnpOrgConnectionManager2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgConnectionManager2SyncGetProtocolInfo(THandle aHandle, char** aSource, char** aSink)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSource;
    Brh buf_aSink;
    proxyC->Proxy()->SyncGetProtocolInfo(buf_aSource, buf_aSink);
    *aSource = buf_aSource.Extract();
    *aSink = buf_aSink.Extract();
}

void CpProxyUpnpOrgConnectionManager2BeginGetProtocolInfo(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetProtocolInfo(functor);
}

int32_t CpProxyUpnpOrgConnectionManager2EndGetProtocolInfo(THandle aHandle, ZappHandleAsync aAsync, char** aSource, char** aSink)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
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

void CpProxyUpnpOrgConnectionManager2SyncPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRemoteProtocolInfo(aRemoteProtocolInfo);
    Brh buf_aPeerConnectionManager(aPeerConnectionManager);
    Brh buf_aDirection(aDirection);
    proxyC->Proxy()->SyncPrepareForConnection(buf_aRemoteProtocolInfo, buf_aPeerConnectionManager, aPeerConnectionID, buf_aDirection, *aConnectionID, *aAVTransportID, *aRcsID);
}

void CpProxyUpnpOrgConnectionManager2BeginPrepareForConnection(THandle aHandle, const char* aRemoteProtocolInfo, const char* aPeerConnectionManager, int32_t aPeerConnectionID, const char* aDirection, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRemoteProtocolInfo(aRemoteProtocolInfo);
    Brh buf_aPeerConnectionManager(aPeerConnectionManager);
    Brh buf_aDirection(aDirection);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPrepareForConnection(buf_aRemoteProtocolInfo, buf_aPeerConnectionManager, aPeerConnectionID, buf_aDirection, functor);
}

int32_t CpProxyUpnpOrgConnectionManager2EndPrepareForConnection(THandle aHandle, ZappHandleAsync aAsync, int32_t* aConnectionID, int32_t* aAVTransportID, int32_t* aRcsID)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
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

void CpProxyUpnpOrgConnectionManager2SyncConnectionComplete(THandle aHandle, int32_t aConnectionID)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncConnectionComplete(aConnectionID);
}

void CpProxyUpnpOrgConnectionManager2BeginConnectionComplete(THandle aHandle, int32_t aConnectionID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginConnectionComplete(aConnectionID, functor);
}

int32_t CpProxyUpnpOrgConnectionManager2EndConnectionComplete(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
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

void CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionIDs(THandle aHandle, char** aConnectionIDs)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aConnectionIDs;
    proxyC->Proxy()->SyncGetCurrentConnectionIDs(buf_aConnectionIDs);
    *aConnectionIDs = buf_aConnectionIDs.Extract();
}

void CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionIDs(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetCurrentConnectionIDs(functor);
}

int32_t CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionIDs(THandle aHandle, ZappHandleAsync aAsync, char** aConnectionIDs)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
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

void CpProxyUpnpOrgConnectionManager2SyncGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
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

void CpProxyUpnpOrgConnectionManager2BeginGetCurrentConnectionInfo(THandle aHandle, int32_t aConnectionID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetCurrentConnectionInfo(aConnectionID, functor);
}

int32_t CpProxyUpnpOrgConnectionManager2EndGetCurrentConnectionInfo(THandle aHandle, ZappHandleAsync aAsync, int32_t* aRcsID, int32_t* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int32_t* aPeerConnectionID, char** aDirection, char** aStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
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

void CpProxyUpnpOrgConnectionManager2SetPropertySourceProtocolInfoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySourceProtocolInfoChanged(functor);
}

void CpProxyUpnpOrgConnectionManager2SetPropertySinkProtocolInfoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySinkProtocolInfoChanged(functor);
}

void CpProxyUpnpOrgConnectionManager2SetPropertyCurrentConnectionIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyCurrentConnectionIDsChanged(functor);
}

void CpProxyUpnpOrgConnectionManager2PropertySourceProtocolInfo(THandle aHandle, char** aSourceProtocolInfo)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSourceProtocolInfo;
    proxyC->Proxy()->PropertySourceProtocolInfo(buf_aSourceProtocolInfo);
    *aSourceProtocolInfo = buf_aSourceProtocolInfo.Transfer();
}

void CpProxyUpnpOrgConnectionManager2PropertySinkProtocolInfo(THandle aHandle, char** aSinkProtocolInfo)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSinkProtocolInfo;
    proxyC->Proxy()->PropertySinkProtocolInfo(buf_aSinkProtocolInfo);
    *aSinkProtocolInfo = buf_aSinkProtocolInfo.Transfer();
}

void CpProxyUpnpOrgConnectionManager2PropertyCurrentConnectionIDs(THandle aHandle, char** aCurrentConnectionIDs)
{
    CpProxyUpnpOrgConnectionManager2C* proxyC = reinterpret_cast<CpProxyUpnpOrgConnectionManager2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aCurrentConnectionIDs;
    proxyC->Proxy()->PropertyCurrentConnectionIDs(buf_aCurrentConnectionIDs);
    *aCurrentConnectionIDs = buf_aCurrentConnectionIDs.Transfer();
}

