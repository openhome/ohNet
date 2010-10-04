#include <C/CpLinnCoUkProduct2.h>
#include <Core/CpLinnCoUkProduct2.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkProduct2C : public CpProxyC
{
public:
    CpProxyLinnCoUkProduct2C(CpDeviceC aDevice);
    CpProxyLinnCoUkProduct2* Proxy() { return static_cast<CpProxyLinnCoUkProduct2*>(iProxy); }
};

CpProxyLinnCoUkProduct2C::CpProxyLinnCoUkProduct2C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkProduct2(*iDevice);
}


THandle CpProxyLinnCoUkProduct2Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkProduct2C(aDevice);
}

void CpProxyLinnCoUkProduct2Destroy(THandle aHandle)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkProduct2SyncType(THandle aHandle, char** aaType)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaType;
    proxyC->Proxy()->SyncType(buf_aaType);
    *aaType = buf_aaType.Extract();
}

void CpProxyLinnCoUkProduct2BeginType(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginType(functor);
}

int32_t CpProxyLinnCoUkProduct2EndType(THandle aHandle, ZappHandleAsync aAsync, char** aaType)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaType;
    *aaType = NULL;
    try {
        proxyC->Proxy()->EndType(*async, buf_aaType);
        *aaType = buf_aaType.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncModel(THandle aHandle, char** aaModel)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaModel;
    proxyC->Proxy()->SyncModel(buf_aaModel);
    *aaModel = buf_aaModel.Extract();
}

void CpProxyLinnCoUkProduct2BeginModel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginModel(functor);
}

int32_t CpProxyLinnCoUkProduct2EndModel(THandle aHandle, ZappHandleAsync aAsync, char** aaModel)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaModel;
    *aaModel = NULL;
    try {
        proxyC->Proxy()->EndModel(*async, buf_aaModel);
        *aaModel = buf_aaModel.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncName(THandle aHandle, char** aaName)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName;
    proxyC->Proxy()->SyncName(buf_aaName);
    *aaName = buf_aaName.Extract();
}

void CpProxyLinnCoUkProduct2BeginName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginName(functor);
}

int32_t CpProxyLinnCoUkProduct2EndName(THandle aHandle, ZappHandleAsync aAsync, char** aaName)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaName;
    *aaName = NULL;
    try {
        proxyC->Proxy()->EndName(*async, buf_aaName);
        *aaName = buf_aaName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSetName(THandle aHandle, const char* aaName)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    proxyC->Proxy()->SyncSetName(buf_aaName);
}

void CpProxyLinnCoUkProduct2BeginSetName(THandle aHandle, const char* aaName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetName(buf_aaName, functor);
}

int32_t CpProxyLinnCoUkProduct2EndSetName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncRoom(THandle aHandle, char** aaRoom)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom;
    proxyC->Proxy()->SyncRoom(buf_aaRoom);
    *aaRoom = buf_aaRoom.Extract();
}

void CpProxyLinnCoUkProduct2BeginRoom(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRoom(functor);
}

int32_t CpProxyLinnCoUkProduct2EndRoom(THandle aHandle, ZappHandleAsync aAsync, char** aaRoom)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaRoom;
    *aaRoom = NULL;
    try {
        proxyC->Proxy()->EndRoom(*async, buf_aaRoom);
        *aaRoom = buf_aaRoom.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSetRoom(THandle aHandle, const char* aaRoom)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    proxyC->Proxy()->SyncSetRoom(buf_aaRoom);
}

void CpProxyLinnCoUkProduct2BeginSetRoom(THandle aHandle, const char* aaRoom, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRoom(buf_aaRoom, functor);
}

int32_t CpProxyLinnCoUkProduct2EndSetRoom(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetRoom(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncStandby(THandle aHandle, uint32_t* aaStandby)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStandby = 0;
    proxyC->Proxy()->SyncStandby(*(TBool*)aaStandby);
}

void CpProxyLinnCoUkProduct2BeginStandby(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStandby(functor);
}

int32_t CpProxyLinnCoUkProduct2EndStandby(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStandby)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaStandby = 0;
    try {
        proxyC->Proxy()->EndStandby(*async, *(TBool*)aaStandby);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSetStandby(THandle aHandle, uint32_t aaStandby)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetStandby((aaStandby==0? false : true));
}

void CpProxyLinnCoUkProduct2BeginSetStandby(THandle aHandle, uint32_t aaStandby, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStandby((aaStandby==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct2EndSetStandby(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStandby(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSourceCount(THandle aHandle, uint32_t* aaSourceCount)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSourceCount(*aaSourceCount);
}

void CpProxyLinnCoUkProduct2BeginSourceCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceCount(functor);
}

int32_t CpProxyLinnCoUkProduct2EndSourceCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceCount)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSourceCount(*async, *aaSourceCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSourceIndex(THandle aHandle, uint32_t* aaSourceIndex)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSourceIndex(*aaSourceIndex);
}

void CpProxyLinnCoUkProduct2BeginSourceIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceIndex(functor);
}

int32_t CpProxyLinnCoUkProduct2EndSourceIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceIndex)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSourceIndex(*async, *aaSourceIndex);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetSourceIndex(aaSourceIndex);
}

void CpProxyLinnCoUkProduct2BeginSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetSourceIndex(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct2EndSetSourceIndex(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetSourceIndex(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSourceType(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceType)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceType;
    proxyC->Proxy()->SyncSourceType(aaSourceIndex, buf_aaSourceType);
    *aaSourceType = buf_aaSourceType.Extract();
}

void CpProxyLinnCoUkProduct2BeginSourceType(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceType(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct2EndSourceType(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceType)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceType;
    *aaSourceType = NULL;
    try {
        proxyC->Proxy()->EndSourceType(*async, buf_aaSourceType);
        *aaSourceType = buf_aaSourceType.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SetPropertyProductNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductNameChanged(functor);
}

void CpProxyLinnCoUkProduct2SetPropertyProductRoomChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductRoomChanged(functor);
}

void CpProxyLinnCoUkProduct2SetPropertyProductStandbyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductStandbyChanged(functor);
}

void CpProxyLinnCoUkProduct2SetPropertyProductSourceIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductSourceIndexChanged(functor);
}

void CpProxyLinnCoUkProduct2PropertyProductName(THandle aHandle, char** aProductName)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductName;
    proxyC->Proxy()->PropertyProductName(buf_aProductName);
    *aProductName = buf_aProductName.Transfer();
}

void CpProxyLinnCoUkProduct2PropertyProductRoom(THandle aHandle, char** aProductRoom)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductRoom;
    proxyC->Proxy()->PropertyProductRoom(buf_aProductRoom);
    *aProductRoom = buf_aProductRoom.Transfer();
}

void CpProxyLinnCoUkProduct2PropertyProductStandby(THandle aHandle, uint32_t* aProductStandby)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aProductStandby = false;
    proxyC->Proxy()->PropertyProductStandby(*(TBool*)aProductStandby);
}

void CpProxyLinnCoUkProduct2PropertyProductSourceIndex(THandle aHandle, uint32_t* aProductSourceIndex)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyProductSourceIndex(*aProductSourceIndex);
}

