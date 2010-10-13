#include <C/CpLinnCoUkRadio1.h>
#include <Core/CpLinnCoUkRadio1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkRadio1C : public CpProxyC
{
public:
    CpProxyLinnCoUkRadio1C(CpDeviceC aDevice);
    CpProxyLinnCoUkRadio1* Proxy() { return static_cast<CpProxyLinnCoUkRadio1*>(iProxy); }
};

CpProxyLinnCoUkRadio1C::CpProxyLinnCoUkRadio1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkRadio1(*iDevice);
}


THandle CpProxyLinnCoUkRadio1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkRadio1C(aDevice);
}

void CpProxyLinnCoUkRadio1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkRadio1SyncPlay(THandle aHandle)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPlay();
}

void CpProxyLinnCoUkRadio1BeginPlay(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPlay(functor);
}

int32_t CpProxyLinnCoUkRadio1EndPlay(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPlay(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncPause(THandle aHandle)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPause();
}

void CpProxyLinnCoUkRadio1BeginPause(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPause(functor);
}

int32_t CpProxyLinnCoUkRadio1EndPause(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPause(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncStop(THandle aHandle)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStop();
}

void CpProxyLinnCoUkRadio1BeginStop(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStop(functor);
}

int32_t CpProxyLinnCoUkRadio1EndStop(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStop(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncSeekSecondAbsolute(THandle aHandle, uint32_t aaSecond)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSeekSecondAbsolute(aaSecond);
}

void CpProxyLinnCoUkRadio1BeginSeekSecondAbsolute(THandle aHandle, uint32_t aaSecond, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeekSecondAbsolute(aaSecond, functor);
}

int32_t CpProxyLinnCoUkRadio1EndSeekSecondAbsolute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeekSecondAbsolute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncSeekSecondRelative(THandle aHandle, int32_t aaSecond)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSeekSecondRelative(aaSecond);
}

void CpProxyLinnCoUkRadio1BeginSeekSecondRelative(THandle aHandle, int32_t aaSecond, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeekSecondRelative(aaSecond, functor);
}

int32_t CpProxyLinnCoUkRadio1EndSeekSecondRelative(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeekSecondRelative(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncChannel(THandle aHandle, char** aaUri, char** aaMetadata)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri;
    Brh buf_aaMetadata;
    proxyC->Proxy()->SyncChannel(buf_aaUri, buf_aaMetadata);
    *aaUri = buf_aaUri.Extract();
    *aaMetadata = buf_aaMetadata.Extract();
}

void CpProxyLinnCoUkRadio1BeginChannel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginChannel(functor);
}

int32_t CpProxyLinnCoUkRadio1EndChannel(THandle aHandle, ZappHandleAsync aAsync, char** aaUri, char** aaMetadata)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUri;
    *aaUri = NULL;
    Brh buf_aaMetadata;
    *aaMetadata = NULL;
    try {
        proxyC->Proxy()->EndChannel(*async, buf_aaUri, buf_aaMetadata);
        *aaUri = buf_aaUri.Extract();
        *aaMetadata = buf_aaMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncSetChannel(THandle aHandle, const char* aaUri, const char* aaMetadata)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    Brh buf_aaMetadata(aaMetadata);
    proxyC->Proxy()->SyncSetChannel(buf_aaUri, buf_aaMetadata);
}

void CpProxyLinnCoUkRadio1BeginSetChannel(THandle aHandle, const char* aaUri, const char* aaMetadata, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    Brh buf_aaMetadata(aaMetadata);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetChannel(buf_aaUri, buf_aaMetadata, functor);
}

int32_t CpProxyLinnCoUkRadio1EndSetChannel(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetChannel(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncProtocolInfo(THandle aHandle, char** aaInfo)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaInfo;
    proxyC->Proxy()->SyncProtocolInfo(buf_aaInfo);
    *aaInfo = buf_aaInfo.Extract();
}

void CpProxyLinnCoUkRadio1BeginProtocolInfo(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginProtocolInfo(functor);
}

int32_t CpProxyLinnCoUkRadio1EndProtocolInfo(THandle aHandle, ZappHandleAsync aAsync, char** aaInfo)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaInfo;
    *aaInfo = NULL;
    try {
        proxyC->Proxy()->EndProtocolInfo(*async, buf_aaInfo);
        *aaInfo = buf_aaInfo.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncTransportState(THandle aHandle, char** aaState)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaState;
    proxyC->Proxy()->SyncTransportState(buf_aaState);
    *aaState = buf_aaState.Extract();
}

void CpProxyLinnCoUkRadio1BeginTransportState(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginTransportState(functor);
}

int32_t CpProxyLinnCoUkRadio1EndTransportState(THandle aHandle, ZappHandleAsync aAsync, char** aaState)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaState;
    *aaState = NULL;
    try {
        proxyC->Proxy()->EndTransportState(*async, buf_aaState);
        *aaState = buf_aaState.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncId(THandle aHandle, uint32_t* aaId)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncId(*aaId);
}

void CpProxyLinnCoUkRadio1BeginId(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginId(functor);
}

int32_t CpProxyLinnCoUkRadio1EndId(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaId)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndId(*async, *aaId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncSetId(THandle aHandle, uint32_t aaId, const char* aaUri)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    proxyC->Proxy()->SyncSetId(aaId, buf_aaUri);
}

void CpProxyLinnCoUkRadio1BeginSetId(THandle aHandle, uint32_t aaId, const char* aaUri, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetId(aaId, buf_aaUri, functor);
}

int32_t CpProxyLinnCoUkRadio1EndSetId(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncRead(THandle aHandle, uint32_t aaId, char** aaMetadata)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMetadata;
    proxyC->Proxy()->SyncRead(aaId, buf_aaMetadata);
    *aaMetadata = buf_aaMetadata.Extract();
}

void CpProxyLinnCoUkRadio1BeginRead(THandle aHandle, uint32_t aaId, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRead(aaId, functor);
}

int32_t CpProxyLinnCoUkRadio1EndRead(THandle aHandle, ZappHandleAsync aAsync, char** aaMetadata)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetadata;
    *aaMetadata = NULL;
    try {
        proxyC->Proxy()->EndRead(*async, buf_aaMetadata);
        *aaMetadata = buf_aaMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncReadList(THandle aHandle, const char* aaIdList, char** aaMetadataList)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdList(aaIdList);
    Brh buf_aaMetadataList;
    proxyC->Proxy()->SyncReadList(buf_aaIdList, buf_aaMetadataList);
    *aaMetadataList = buf_aaMetadataList.Extract();
}

void CpProxyLinnCoUkRadio1BeginReadList(THandle aHandle, const char* aaIdList, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdList(aaIdList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginReadList(buf_aaIdList, functor);
}

int32_t CpProxyLinnCoUkRadio1EndReadList(THandle aHandle, ZappHandleAsync aAsync, char** aaMetadataList)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetadataList;
    *aaMetadataList = NULL;
    try {
        proxyC->Proxy()->EndReadList(*async, buf_aaMetadataList);
        *aaMetadataList = buf_aaMetadataList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncIdArray(THandle aHandle, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdArray;
    proxyC->Proxy()->SyncIdArray(*aaIdArrayToken, buf_aaIdArray);
    *aaIdArrayLen = buf_aaIdArray.Bytes();
    *aaIdArray = buf_aaIdArray.Extract();
}

void CpProxyLinnCoUkRadio1BeginIdArray(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginIdArray(functor);
}

int32_t CpProxyLinnCoUkRadio1EndIdArray(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaIdArray;
    *aaIdArray = NULL;
    *aaIdArrayLen = 0;
    try {
        proxyC->Proxy()->EndIdArray(*async, *aaIdArrayToken, buf_aaIdArray);
        *aaIdArrayLen = buf_aaIdArray.Bytes();
        *aaIdArray = buf_aaIdArray.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, uint32_t* aaIdArrayChanged)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaIdArrayChanged = 0;
    proxyC->Proxy()->SyncIdArrayChanged(aaIdArrayToken, *(TBool*)aaIdArrayChanged);
}

void CpProxyLinnCoUkRadio1BeginIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginIdArrayChanged(aaIdArrayToken, functor);
}

int32_t CpProxyLinnCoUkRadio1EndIdArrayChanged(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayChanged)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaIdArrayChanged = 0;
    try {
        proxyC->Proxy()->EndIdArrayChanged(*async, *(TBool*)aaIdArrayChanged);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SyncIdsMax(THandle aHandle, uint32_t* aaIdsMax)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncIdsMax(*aaIdsMax);
}

void CpProxyLinnCoUkRadio1BeginIdsMax(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginIdsMax(functor);
}

int32_t CpProxyLinnCoUkRadio1EndIdsMax(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdsMax)
{
    int32_t err = 0;
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndIdsMax(*async, *aaIdsMax);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkRadio1SetPropertyChannelUriChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyChannelUriChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyChannelMetadataChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyChannelMetadataChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyTransportStateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTransportStateChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyProtocolInfoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProtocolInfoChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyIdChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyIdChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyIdArrayChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyIdArrayChanged(functor);
}

void CpProxyLinnCoUkRadio1SetPropertyIdsMaxChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyIdsMaxChanged(functor);
}

void CpProxyLinnCoUkRadio1PropertyChannelUri(THandle aHandle, char** aChannelUri)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aChannelUri;
    proxyC->Proxy()->PropertyChannelUri(buf_aChannelUri);
    *aChannelUri = buf_aChannelUri.Transfer();
}

void CpProxyLinnCoUkRadio1PropertyChannelMetadata(THandle aHandle, char** aChannelMetadata)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aChannelMetadata;
    proxyC->Proxy()->PropertyChannelMetadata(buf_aChannelMetadata);
    *aChannelMetadata = buf_aChannelMetadata.Transfer();
}

void CpProxyLinnCoUkRadio1PropertyTransportState(THandle aHandle, char** aTransportState)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransportState;
    proxyC->Proxy()->PropertyTransportState(buf_aTransportState);
    *aTransportState = buf_aTransportState.Transfer();
}

void CpProxyLinnCoUkRadio1PropertyProtocolInfo(THandle aHandle, char** aProtocolInfo)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProtocolInfo;
    proxyC->Proxy()->PropertyProtocolInfo(buf_aProtocolInfo);
    *aProtocolInfo = buf_aProtocolInfo.Transfer();
}

void CpProxyLinnCoUkRadio1PropertyId(THandle aHandle, uint32_t* aId)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyId(*aId);
}

void CpProxyLinnCoUkRadio1PropertyIdArray(THandle aHandle, char** aIdArray, uint32_t* aLen)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdArray;
    proxyC->Proxy()->PropertyIdArray(buf_aIdArray);
    *aLen = buf_aIdArray.Bytes();
    *aIdArray = buf_aIdArray.Extract();
}

void CpProxyLinnCoUkRadio1PropertyIdsMax(THandle aHandle, uint32_t* aIdsMax)
{
    CpProxyLinnCoUkRadio1C* proxyC = reinterpret_cast<CpProxyLinnCoUkRadio1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyIdsMax(*aIdsMax);
}

