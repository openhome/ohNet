#include <C/CpLinnCoUkProxyManager1.h>
#include <Core/CpLinnCoUkProxyManager1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkProxyManager1C : public CpProxyC
{
public:
    CpProxyLinnCoUkProxyManager1C(CpDeviceC aDevice);
    CpProxyLinnCoUkProxyManager1* Proxy() { return static_cast<CpProxyLinnCoUkProxyManager1*>(iProxy); }
};

CpProxyLinnCoUkProxyManager1C::CpProxyLinnCoUkProxyManager1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkProxyManager1(*iDevice);
}


THandle CpProxyLinnCoUkProxyManager1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkProxyManager1C(aDevice);
}

void CpProxyLinnCoUkProxyManager1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkProxyManager1SyncKontrolProductConnected(THandle aHandle, char** aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected;
    proxyC->Proxy()->SyncKontrolProductConnected(buf_aaConnected);
    *aaConnected = buf_aaConnected.Extract();
}

void CpProxyLinnCoUkProxyManager1BeginKontrolProductConnected(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginKontrolProductConnected(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndKontrolProductConnected(THandle aHandle, ZappHandleAsync aAsync, char** aaConnected)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaConnected;
    *aaConnected = NULL;
    try {
        proxyC->Proxy()->EndKontrolProductConnected(*async, buf_aaConnected);
        *aaConnected = buf_aaConnected.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductConnected(THandle aHandle, const char* aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected(aaConnected);
    proxyC->Proxy()->SyncSetKontrolProductConnected(buf_aaConnected);
}

void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductConnected(THandle aHandle, const char* aaConnected, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected(aaConnected);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetKontrolProductConnected(buf_aaConnected, functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndSetKontrolProductConnected(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetKontrolProductConnected(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncKontrolProductComPort(THandle aHandle, uint32_t* aaPort)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncKontrolProductComPort(*aaPort);
}

void CpProxyLinnCoUkProxyManager1BeginKontrolProductComPort(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginKontrolProductComPort(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndKontrolProductComPort(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPort)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndKontrolProductComPort(*async, *aaPort);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncSetKontrolProductComPort(THandle aHandle, uint32_t aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetKontrolProductComPort(aaConnected);
}

void CpProxyLinnCoUkProxyManager1BeginSetKontrolProductComPort(THandle aHandle, uint32_t aaConnected, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetKontrolProductComPort(aaConnected, functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndSetKontrolProductComPort(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetKontrolProductComPort(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncDiscPlayerConnected(THandle aHandle, char** aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected;
    proxyC->Proxy()->SyncDiscPlayerConnected(buf_aaConnected);
    *aaConnected = buf_aaConnected.Extract();
}

void CpProxyLinnCoUkProxyManager1BeginDiscPlayerConnected(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDiscPlayerConnected(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndDiscPlayerConnected(THandle aHandle, ZappHandleAsync aAsync, char** aaConnected)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaConnected;
    *aaConnected = NULL;
    try {
        proxyC->Proxy()->EndDiscPlayerConnected(*async, buf_aaConnected);
        *aaConnected = buf_aaConnected.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerConnected(THandle aHandle, const char* aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected(aaConnected);
    proxyC->Proxy()->SyncSetDiscPlayerConnected(buf_aaConnected);
}

void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerConnected(THandle aHandle, const char* aaConnected, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConnected(aaConnected);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDiscPlayerConnected(buf_aaConnected, functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndSetDiscPlayerConnected(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDiscPlayerConnected(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncDiscPlayerComPort(THandle aHandle, uint32_t* aaPort)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDiscPlayerComPort(*aaPort);
}

void CpProxyLinnCoUkProxyManager1BeginDiscPlayerComPort(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDiscPlayerComPort(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndDiscPlayerComPort(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPort)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDiscPlayerComPort(*async, *aaPort);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncSetDiscPlayerComPort(THandle aHandle, uint32_t aaConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetDiscPlayerComPort(aaConnected);
}

void CpProxyLinnCoUkProxyManager1BeginSetDiscPlayerComPort(THandle aHandle, uint32_t aaConnected, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDiscPlayerComPort(aaConnected, functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndSetDiscPlayerComPort(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDiscPlayerComPort(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncTestKontrolProductConnection(THandle aHandle, uint32_t* aaResult)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaResult = 0;
    proxyC->Proxy()->SyncTestKontrolProductConnection(*(TBool*)aaResult);
}

void CpProxyLinnCoUkProxyManager1BeginTestKontrolProductConnection(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginTestKontrolProductConnection(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndTestKontrolProductConnection(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaResult)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaResult = 0;
    try {
        proxyC->Proxy()->EndTestKontrolProductConnection(*async, *(TBool*)aaResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SyncTestDiscPlayerConnection(THandle aHandle, uint32_t* aaResult)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaResult = 0;
    proxyC->Proxy()->SyncTestDiscPlayerConnection(*(TBool*)aaResult);
}

void CpProxyLinnCoUkProxyManager1BeginTestDiscPlayerConnection(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginTestDiscPlayerConnection(functor);
}

int32_t CpProxyLinnCoUkProxyManager1EndTestDiscPlayerConnection(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaResult)
{
    int32_t err = 0;
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaResult = 0;
    try {
        proxyC->Proxy()->EndTestDiscPlayerConnection(*async, *(TBool*)aaResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductConnectedChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyKontrolProductConnectedChanged(functor);
}

void CpProxyLinnCoUkProxyManager1SetPropertyKontrolProductComPortChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyKontrolProductComPortChanged(functor);
}

void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerConnectedChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDiscPlayerConnectedChanged(functor);
}

void CpProxyLinnCoUkProxyManager1SetPropertyDiscPlayerComPortChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDiscPlayerComPortChanged(functor);
}

void CpProxyLinnCoUkProxyManager1PropertyKontrolProductConnected(THandle aHandle, char** aKontrolProductConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aKontrolProductConnected;
    proxyC->Proxy()->PropertyKontrolProductConnected(buf_aKontrolProductConnected);
    *aKontrolProductConnected = buf_aKontrolProductConnected.Transfer();
}

void CpProxyLinnCoUkProxyManager1PropertyKontrolProductComPort(THandle aHandle, uint32_t* aKontrolProductComPort)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyKontrolProductComPort(*aKontrolProductComPort);
}

void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerConnected(THandle aHandle, char** aDiscPlayerConnected)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aDiscPlayerConnected;
    proxyC->Proxy()->PropertyDiscPlayerConnected(buf_aDiscPlayerConnected);
    *aDiscPlayerConnected = buf_aDiscPlayerConnected.Transfer();
}

void CpProxyLinnCoUkProxyManager1PropertyDiscPlayerComPort(THandle aHandle, uint32_t* aDiscPlayerComPort)
{
    CpProxyLinnCoUkProxyManager1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProxyManager1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyDiscPlayerComPort(*aDiscPlayerComPort);
}

