#include <C/CpLinnCoUkProduct1.h>
#include <Core/CpLinnCoUkProduct1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkProduct1C : public CpProxyC
{
public:
    CpProxyLinnCoUkProduct1C(CpDeviceC aDevice);
    CpProxyLinnCoUkProduct1* Proxy() { return static_cast<CpProxyLinnCoUkProduct1*>(iProxy); }
};

CpProxyLinnCoUkProduct1C::CpProxyLinnCoUkProduct1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkProduct1(*iDevice);
}


THandle CpProxyLinnCoUkProduct1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkProduct1C(aDevice);
}

void CpProxyLinnCoUkProduct1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkProduct1SyncRoom(THandle aHandle, char** aaRoom)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom;
    proxyC->Proxy()->SyncRoom(buf_aaRoom);
    *aaRoom = buf_aaRoom.Extract();
}

void CpProxyLinnCoUkProduct1BeginRoom(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRoom(functor);
}

int32_t CpProxyLinnCoUkProduct1EndRoom(THandle aHandle, ZappHandleAsync aAsync, char** aaRoom)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
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

void CpProxyLinnCoUkProduct1SyncSetRoom(THandle aHandle, const char* aaRoom)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    proxyC->Proxy()->SyncSetRoom(buf_aaRoom);
}

void CpProxyLinnCoUkProduct1BeginSetRoom(THandle aHandle, const char* aaRoom, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRoom(buf_aaRoom, functor);
}

int32_t CpProxyLinnCoUkProduct1EndSetRoom(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
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

void CpProxyLinnCoUkProduct1SyncStandby(THandle aHandle, uint32_t* aaStandby)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStandby = 0;
    proxyC->Proxy()->SyncStandby(*(TBool*)aaStandby);
}

void CpProxyLinnCoUkProduct1BeginStandby(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStandby(functor);
}

int32_t CpProxyLinnCoUkProduct1EndStandby(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStandby)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
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

void CpProxyLinnCoUkProduct1SyncSetStandby(THandle aHandle, uint32_t aaStandby)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetStandby((aaStandby==0? false : true));
}

void CpProxyLinnCoUkProduct1BeginSetStandby(THandle aHandle, uint32_t aaStandby, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStandby((aaStandby==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct1EndSetStandby(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
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

void CpProxyLinnCoUkProduct1SetPropertyRoomChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyRoomChanged(functor);
}

void CpProxyLinnCoUkProduct1SetPropertyStandbyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyStandbyChanged(functor);
}

void CpProxyLinnCoUkProduct1PropertyRoom(THandle aHandle, char** aRoom)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aRoom;
    proxyC->Proxy()->PropertyRoom(buf_aRoom);
    *aRoom = buf_aRoom.Transfer();
}

void CpProxyLinnCoUkProduct1PropertyStandby(THandle aHandle, uint32_t* aStandby)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aStandby = false;
    proxyC->Proxy()->PropertyStandby(*(TBool*)aStandby);
}

