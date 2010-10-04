#include <C/CpLinnCoUkProduct3.h>
#include <Core/CpLinnCoUkProduct3.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkProduct3C : public CpProxyC
{
public:
    CpProxyLinnCoUkProduct3C(CpDeviceC aDevice);
    CpProxyLinnCoUkProduct3* Proxy() { return static_cast<CpProxyLinnCoUkProduct3*>(iProxy); }
};

CpProxyLinnCoUkProduct3C::CpProxyLinnCoUkProduct3C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkProduct3(*iDevice);
}


THandle CpProxyLinnCoUkProduct3Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkProduct3C(aDevice);
}

void CpProxyLinnCoUkProduct3Destroy(THandle aHandle)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkProduct3SyncType(THandle aHandle, char** aaType)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaType;
    proxyC->Proxy()->SyncType(buf_aaType);
    *aaType = buf_aaType.Extract();
}

void CpProxyLinnCoUkProduct3BeginType(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginType(functor);
}

int32_t CpProxyLinnCoUkProduct3EndType(THandle aHandle, ZappHandleAsync aAsync, char** aaType)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncModel(THandle aHandle, char** aaModel)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaModel;
    proxyC->Proxy()->SyncModel(buf_aaModel);
    *aaModel = buf_aaModel.Extract();
}

void CpProxyLinnCoUkProduct3BeginModel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginModel(functor);
}

int32_t CpProxyLinnCoUkProduct3EndModel(THandle aHandle, ZappHandleAsync aAsync, char** aaModel)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncName(THandle aHandle, char** aaName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName;
    proxyC->Proxy()->SyncName(buf_aaName);
    *aaName = buf_aaName.Extract();
}

void CpProxyLinnCoUkProduct3BeginName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginName(functor);
}

int32_t CpProxyLinnCoUkProduct3EndName(THandle aHandle, ZappHandleAsync aAsync, char** aaName)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncSetName(THandle aHandle, const char* aaName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    proxyC->Proxy()->SyncSetName(buf_aaName);
}

void CpProxyLinnCoUkProduct3BeginSetName(THandle aHandle, const char* aaName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetName(buf_aaName, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncRoom(THandle aHandle, char** aaRoom)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom;
    proxyC->Proxy()->SyncRoom(buf_aaRoom);
    *aaRoom = buf_aaRoom.Extract();
}

void CpProxyLinnCoUkProduct3BeginRoom(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRoom(functor);
}

int32_t CpProxyLinnCoUkProduct3EndRoom(THandle aHandle, ZappHandleAsync aAsync, char** aaRoom)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncSetRoom(THandle aHandle, const char* aaRoom)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    proxyC->Proxy()->SyncSetRoom(buf_aaRoom);
}

void CpProxyLinnCoUkProduct3BeginSetRoom(THandle aHandle, const char* aaRoom, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRoom(buf_aaRoom, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetRoom(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncStandby(THandle aHandle, uint32_t* aaStandby)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStandby = 0;
    proxyC->Proxy()->SyncStandby(*(TBool*)aaStandby);
}

void CpProxyLinnCoUkProduct3BeginStandby(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStandby(functor);
}

int32_t CpProxyLinnCoUkProduct3EndStandby(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStandby)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncSetStandby(THandle aHandle, uint32_t aaStandby)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetStandby((aaStandby==0? false : true));
}

void CpProxyLinnCoUkProduct3BeginSetStandby(THandle aHandle, uint32_t aaStandby, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStandby((aaStandby==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetStandby(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncSourceCount(THandle aHandle, uint32_t* aaSourceCount)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSourceCount(*aaSourceCount);
}

void CpProxyLinnCoUkProduct3BeginSourceCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceCount(functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceCount)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncSourceXml(THandle aHandle, char** aaSourceXml)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceXml;
    proxyC->Proxy()->SyncSourceXml(buf_aaSourceXml);
    *aaSourceXml = buf_aaSourceXml.Extract();
}

void CpProxyLinnCoUkProduct3BeginSourceXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceXml(functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceXml(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceXml)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceXml;
    *aaSourceXml = NULL;
    try {
        proxyC->Proxy()->EndSourceXml(*async, buf_aaSourceXml);
        *aaSourceXml = buf_aaSourceXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceIndex(THandle aHandle, uint32_t* aaSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSourceIndex(*aaSourceIndex);
}

void CpProxyLinnCoUkProduct3BeginSourceIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceIndex(functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceIndex)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetSourceIndex(aaSourceIndex);
}

void CpProxyLinnCoUkProduct3BeginSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetSourceIndex(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetSourceIndex(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncSetSourceIndexByName(THandle aHandle, const char* aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    proxyC->Proxy()->SyncSetSourceIndexByName(buf_aaSourceName);
}

void CpProxyLinnCoUkProduct3BeginSetSourceIndexByName(THandle aHandle, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetSourceIndexByName(buf_aaSourceName, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetSourceIndexByName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetSourceIndexByName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndexByName(THandle aHandle, const char* aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    proxyC->Proxy()->SyncSetStartupSourceIndexByName(buf_aaSourceName);
}

void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndexByName(THandle aHandle, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStartupSourceIndexByName(buf_aaSourceName, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceIndexByName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStartupSourceIndexByName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncStartupSourceIndex(THandle aHandle, uint32_t* aaSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStartupSourceIndex(*aaSourceIndex);
}

void CpProxyLinnCoUkProduct3BeginStartupSourceIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStartupSourceIndex(functor);
}

int32_t CpProxyLinnCoUkProduct3EndStartupSourceIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceIndex)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStartupSourceIndex(*async, *aaSourceIndex);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndex(THandle aHandle, uint32_t aaSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetStartupSourceIndex(aaSourceIndex);
}

void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndex(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStartupSourceIndex(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceIndex(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStartupSourceIndex(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncStartupSourceEnabled(THandle aHandle, uint32_t* aaStartupSourceEnabled)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStartupSourceEnabled = 0;
    proxyC->Proxy()->SyncStartupSourceEnabled(*(TBool*)aaStartupSourceEnabled);
}

void CpProxyLinnCoUkProduct3BeginStartupSourceEnabled(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStartupSourceEnabled(functor);
}

int32_t CpProxyLinnCoUkProduct3EndStartupSourceEnabled(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStartupSourceEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaStartupSourceEnabled = 0;
    try {
        proxyC->Proxy()->EndStartupSourceEnabled(*async, *(TBool*)aaStartupSourceEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetStartupSourceEnabled(THandle aHandle, uint32_t aaStartupSourceEnabled)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetStartupSourceEnabled((aaStartupSourceEnabled==0? false : true));
}

void CpProxyLinnCoUkProduct3BeginSetStartupSourceEnabled(THandle aHandle, uint32_t aaStartupSourceEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStartupSourceEnabled((aaStartupSourceEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetStartupSourceEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStartupSourceEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceSystemName(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName;
    proxyC->Proxy()->SyncSourceSystemName(aaSourceIndex, buf_aaSourceName);
    *aaSourceName = buf_aaSourceName.Extract();
}

void CpProxyLinnCoUkProduct3BeginSourceSystemName(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceSystemName(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceSystemName(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceName)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceName;
    *aaSourceName = NULL;
    try {
        proxyC->Proxy()->EndSourceSystemName(*async, buf_aaSourceName);
        *aaSourceName = buf_aaSourceName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceName(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName;
    proxyC->Proxy()->SyncSourceName(aaSourceIndex, buf_aaSourceName);
    *aaSourceName = buf_aaSourceName.Extract();
}

void CpProxyLinnCoUkProduct3BeginSourceName(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceName(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceName(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceName)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceName;
    *aaSourceName = NULL;
    try {
        proxyC->Proxy()->EndSourceName(*async, buf_aaSourceName);
        *aaSourceName = buf_aaSourceName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetSourceName(THandle aHandle, uint32_t aaSourceIndex, const char* aaSourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    proxyC->Proxy()->SyncSetSourceName(aaSourceIndex, buf_aaSourceName);
}

void CpProxyLinnCoUkProduct3BeginSetSourceName(THandle aHandle, uint32_t aaSourceIndex, const char* aaSourceName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceName(aaSourceName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetSourceName(aaSourceIndex, buf_aaSourceName, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetSourceName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetSourceName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSourceType(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceType)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceType;
    proxyC->Proxy()->SyncSourceType(aaSourceIndex, buf_aaSourceType);
    *aaSourceType = buf_aaSourceType.Extract();
}

void CpProxyLinnCoUkProduct3BeginSourceType(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceType(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceType(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceType)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
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

void CpProxyLinnCoUkProduct3SyncSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t* aaSourceVisible)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaSourceVisible = 0;
    proxyC->Proxy()->SyncSourceVisible(aaSourceIndex, *(TBool*)aaSourceVisible);
}

void CpProxyLinnCoUkProduct3BeginSourceVisible(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSourceVisible(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct3EndSourceVisible(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceVisible)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaSourceVisible = 0;
    try {
        proxyC->Proxy()->EndSourceVisible(*async, *(TBool*)aaSourceVisible);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SyncSetSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t aaSourceVisible)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetSourceVisible(aaSourceIndex, (aaSourceVisible==0? false : true));
}

void CpProxyLinnCoUkProduct3BeginSetSourceVisible(THandle aHandle, uint32_t aaSourceIndex, uint32_t aaSourceVisible, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetSourceVisible(aaSourceIndex, (aaSourceVisible==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct3EndSetSourceVisible(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetSourceVisible(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct3SetPropertyProductTypeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductTypeChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductModelChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductModelChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductNameChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductRoomChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductRoomChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductStandbyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductStandbyChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductSourceIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductSourceIndexChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductSourceCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductSourceCountChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductSourceXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductSourceXmlChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyStartupSourceIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyStartupSourceIndexChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyStartupSourceEnabledChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyStartupSourceEnabledChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductAnySourceNameChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceVisibleChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductAnySourceVisibleChanged(functor);
}

void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceTypeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyProductAnySourceTypeChanged(functor);
}

void CpProxyLinnCoUkProduct3PropertyProductType(THandle aHandle, char** aProductType)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductType;
    proxyC->Proxy()->PropertyProductType(buf_aProductType);
    *aProductType = buf_aProductType.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyProductModel(THandle aHandle, char** aProductModel)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductModel;
    proxyC->Proxy()->PropertyProductModel(buf_aProductModel);
    *aProductModel = buf_aProductModel.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyProductName(THandle aHandle, char** aProductName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductName;
    proxyC->Proxy()->PropertyProductName(buf_aProductName);
    *aProductName = buf_aProductName.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyProductRoom(THandle aHandle, char** aProductRoom)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductRoom;
    proxyC->Proxy()->PropertyProductRoom(buf_aProductRoom);
    *aProductRoom = buf_aProductRoom.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyProductStandby(THandle aHandle, uint32_t* aProductStandby)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aProductStandby = false;
    proxyC->Proxy()->PropertyProductStandby(*(TBool*)aProductStandby);
}

void CpProxyLinnCoUkProduct3PropertyProductSourceIndex(THandle aHandle, uint32_t* aProductSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyProductSourceIndex(*aProductSourceIndex);
}

void CpProxyLinnCoUkProduct3PropertyProductSourceCount(THandle aHandle, uint32_t* aProductSourceCount)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyProductSourceCount(*aProductSourceCount);
}

void CpProxyLinnCoUkProduct3PropertyProductSourceXml(THandle aHandle, char** aProductSourceXml)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductSourceXml;
    proxyC->Proxy()->PropertyProductSourceXml(buf_aProductSourceXml);
    *aProductSourceXml = buf_aProductSourceXml.Transfer();
}

void CpProxyLinnCoUkProduct3PropertyStartupSourceIndex(THandle aHandle, uint32_t* aStartupSourceIndex)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyStartupSourceIndex(*aStartupSourceIndex);
}

void CpProxyLinnCoUkProduct3PropertyStartupSourceEnabled(THandle aHandle, uint32_t* aStartupSourceEnabled)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aStartupSourceEnabled = false;
    proxyC->Proxy()->PropertyStartupSourceEnabled(*(TBool*)aStartupSourceEnabled);
}

void CpProxyLinnCoUkProduct3PropertyProductAnySourceName(THandle aHandle, uint32_t* aProductAnySourceName)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyProductAnySourceName(*aProductAnySourceName);
}

void CpProxyLinnCoUkProduct3PropertyProductAnySourceVisible(THandle aHandle, uint32_t* aProductAnySourceVisible)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyProductAnySourceVisible(*aProductAnySourceVisible);
}

void CpProxyLinnCoUkProduct3PropertyProductAnySourceType(THandle aHandle, uint32_t* aProductAnySourceType)
{
    CpProxyLinnCoUkProduct3C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyProductAnySourceType(*aProductAnySourceType);
}

