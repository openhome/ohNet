#include <C/CpLinnCoUkPlaylist1.h>
#include <Core/CpLinnCoUkPlaylist1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkPlaylist1C : public CpProxyC
{
public:
    CpProxyLinnCoUkPlaylist1C(CpDeviceC aDevice);
    CpProxyLinnCoUkPlaylist1* Proxy() { return static_cast<CpProxyLinnCoUkPlaylist1*>(iProxy); }
};

CpProxyLinnCoUkPlaylist1C::CpProxyLinnCoUkPlaylist1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkPlaylist1(*iDevice);
}


THandle CpProxyLinnCoUkPlaylist1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkPlaylist1C(aDevice);
}

void CpProxyLinnCoUkPlaylist1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkPlaylist1SyncRead(THandle aHandle, uint32_t aaId, char** aaUri, char** aaMetaData)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri;
    Brh buf_aaMetaData;
    proxyC->Proxy()->SyncRead(aaId, buf_aaUri, buf_aaMetaData);
    *aaUri = buf_aaUri.Extract();
    *aaMetaData = buf_aaMetaData.Extract();
}

void CpProxyLinnCoUkPlaylist1BeginRead(THandle aHandle, uint32_t aaId, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRead(aaId, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndRead(THandle aHandle, ZappHandleAsync aAsync, char** aaUri, char** aaMetaData)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUri;
    *aaUri = NULL;
    Brh buf_aaMetaData;
    *aaMetaData = NULL;
    try {
        proxyC->Proxy()->EndRead(*async, buf_aaUri, buf_aaMetaData);
        *aaUri = buf_aaUri.Extract();
        *aaMetaData = buf_aaMetaData.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncReadList(THandle aHandle, const char* aaIdList, char** aaMetaDataList)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdList(aaIdList);
    Brh buf_aaMetaDataList;
    proxyC->Proxy()->SyncReadList(buf_aaIdList, buf_aaMetaDataList);
    *aaMetaDataList = buf_aaMetaDataList.Extract();
}

void CpProxyLinnCoUkPlaylist1BeginReadList(THandle aHandle, const char* aaIdList, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdList(aaIdList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginReadList(buf_aaIdList, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndReadList(THandle aHandle, ZappHandleAsync aAsync, char** aaMetaDataList)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetaDataList;
    *aaMetaDataList = NULL;
    try {
        proxyC->Proxy()->EndReadList(*async, buf_aaMetaDataList);
        *aaMetaDataList = buf_aaMetaDataList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncInsert(THandle aHandle, uint32_t aaAfterId, const char* aaUri, const char* aaMetaData, uint32_t* aaNewId)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    Brh buf_aaMetaData(aaMetaData);
    proxyC->Proxy()->SyncInsert(aaAfterId, buf_aaUri, buf_aaMetaData, *aaNewId);
}

void CpProxyLinnCoUkPlaylist1BeginInsert(THandle aHandle, uint32_t aaAfterId, const char* aaUri, const char* aaMetaData, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri(aaUri);
    Brh buf_aaMetaData(aaMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginInsert(aaAfterId, buf_aaUri, buf_aaMetaData, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndInsert(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaNewId)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndInsert(*async, *aaNewId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncDelete(THandle aHandle, uint32_t aaId)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDelete(aaId);
}

void CpProxyLinnCoUkPlaylist1BeginDelete(THandle aHandle, uint32_t aaId, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDelete(aaId, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndDelete(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDelete(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncDeleteAll(THandle aHandle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDeleteAll();
}

void CpProxyLinnCoUkPlaylist1BeginDeleteAll(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDeleteAll(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndDeleteAll(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDeleteAll(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncSetRepeat(THandle aHandle, uint32_t aaRepeat)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetRepeat((aaRepeat==0? false : true));
}

void CpProxyLinnCoUkPlaylist1BeginSetRepeat(THandle aHandle, uint32_t aaRepeat, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRepeat((aaRepeat==0? false : true), functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndSetRepeat(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetRepeat(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncRepeat(THandle aHandle, uint32_t* aaRepeat)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaRepeat = 0;
    proxyC->Proxy()->SyncRepeat(*(TBool*)aaRepeat);
}

void CpProxyLinnCoUkPlaylist1BeginRepeat(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRepeat(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndRepeat(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaRepeat)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaRepeat = 0;
    try {
        proxyC->Proxy()->EndRepeat(*async, *(TBool*)aaRepeat);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncSetShuffle(THandle aHandle, uint32_t aaShuffle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetShuffle((aaShuffle==0? false : true));
}

void CpProxyLinnCoUkPlaylist1BeginSetShuffle(THandle aHandle, uint32_t aaShuffle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetShuffle((aaShuffle==0? false : true), functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndSetShuffle(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetShuffle(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncShuffle(THandle aHandle, uint32_t* aaShuffle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaShuffle = 0;
    proxyC->Proxy()->SyncShuffle(*(TBool*)aaShuffle);
}

void CpProxyLinnCoUkPlaylist1BeginShuffle(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginShuffle(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndShuffle(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaShuffle)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaShuffle = 0;
    try {
        proxyC->Proxy()->EndShuffle(*async, *(TBool*)aaShuffle);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncTracksMax(THandle aHandle, uint32_t* aaTracksMax)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncTracksMax(*aaTracksMax);
}

void CpProxyLinnCoUkPlaylist1BeginTracksMax(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginTracksMax(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndTracksMax(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTracksMax)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndTracksMax(*async, *aaTracksMax);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkPlaylist1SyncIdArray(THandle aHandle, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIdArray;
    proxyC->Proxy()->SyncIdArray(*aaIdArrayToken, buf_aaIdArray);
    *aaIdArrayLen = buf_aaIdArray.Bytes();
    *aaIdArray = buf_aaIdArray.Extract();
}

void CpProxyLinnCoUkPlaylist1BeginIdArray(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginIdArray(functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndIdArray(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayToken, char** aaIdArray, uint32_t* aaIdArrayLen)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
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

void CpProxyLinnCoUkPlaylist1SyncIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, uint32_t* aaIdArrayChanged)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaIdArrayChanged = 0;
    proxyC->Proxy()->SyncIdArrayChanged(aaIdArrayToken, *(TBool*)aaIdArrayChanged);
}

void CpProxyLinnCoUkPlaylist1BeginIdArrayChanged(THandle aHandle, uint32_t aaIdArrayToken, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginIdArrayChanged(aaIdArrayToken, functor);
}

int32_t CpProxyLinnCoUkPlaylist1EndIdArrayChanged(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaIdArrayChanged)
{
    int32_t err = 0;
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
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

void CpProxyLinnCoUkPlaylist1SetPropertyIdArrayChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyIdArrayChanged(functor);
}

void CpProxyLinnCoUkPlaylist1SetPropertyRepeatChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyRepeatChanged(functor);
}

void CpProxyLinnCoUkPlaylist1SetPropertyShuffleChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyShuffleChanged(functor);
}

void CpProxyLinnCoUkPlaylist1SetPropertyTracksMaxChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTracksMaxChanged(functor);
}

void CpProxyLinnCoUkPlaylist1PropertyIdArray(THandle aHandle, char** aIdArray, uint32_t* aLen)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aIdArray;
    proxyC->Proxy()->PropertyIdArray(buf_aIdArray);
    *aLen = buf_aIdArray.Bytes();
    *aIdArray = buf_aIdArray.Extract();
}

void CpProxyLinnCoUkPlaylist1PropertyRepeat(THandle aHandle, uint32_t* aRepeat)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aRepeat = false;
    proxyC->Proxy()->PropertyRepeat(*(TBool*)aRepeat);
}

void CpProxyLinnCoUkPlaylist1PropertyShuffle(THandle aHandle, uint32_t* aShuffle)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aShuffle = false;
    proxyC->Proxy()->PropertyShuffle(*(TBool*)aShuffle);
}

void CpProxyLinnCoUkPlaylist1PropertyTracksMax(THandle aHandle, uint32_t* aTracksMax)
{
    CpProxyLinnCoUkPlaylist1C* proxyC = reinterpret_cast<CpProxyLinnCoUkPlaylist1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTracksMax(*aTracksMax);
}

