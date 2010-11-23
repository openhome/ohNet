#include <C/CpZappOrgTestWidgetController1.h>
#include <Core/CpZappOrgTestWidgetController1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyZappOrgTestWidgetController1C : public CpProxyC
{
public:
    CpProxyZappOrgTestWidgetController1C(CpDeviceC aDevice);
    CpProxyZappOrgTestWidgetController1* Proxy() { return static_cast<CpProxyZappOrgTestWidgetController1*>(iProxy); }
};

CpProxyZappOrgTestWidgetController1C::CpProxyZappOrgTestWidgetController1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyZappOrgTestWidgetController1(*iDevice);
}


THandle CpProxyZappOrgTestWidgetController1Create(CpDeviceC aDevice)
{
    return new CpProxyZappOrgTestWidgetController1C(aDevice);
}

void CpProxyZappOrgTestWidgetController1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestWidgetController1SyncCreateWidget(THandle aHandle, const char* aWidgetUdn, uint32_t aWidgetClass)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    proxyC->Proxy()->SyncCreateWidget(buf_aWidgetUdn, aWidgetClass);
}

void CpProxyZappOrgTestWidgetController1BeginCreateWidget(THandle aHandle, const char* aWidgetUdn, uint32_t aWidgetClass, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateWidget(buf_aWidgetUdn, aWidgetClass, functor);
}

int32_t CpProxyZappOrgTestWidgetController1EndCreateWidget(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndCreateWidget(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidgetController1SyncRemoveWidget(THandle aHandle, const char* aWidgetUdn)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    proxyC->Proxy()->SyncRemoveWidget(buf_aWidgetUdn);
}

void CpProxyZappOrgTestWidgetController1BeginRemoveWidget(THandle aHandle, const char* aWidgetUdn, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRemoveWidget(buf_aWidgetUdn, functor);
}

int32_t CpProxyZappOrgTestWidgetController1EndRemoveWidget(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndRemoveWidget(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidgetController1SyncSetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    proxyC->Proxy()->SyncSetWidgetRegister(buf_aWidgetUdn, aRegisterIndex, aRegisterValue);
}

void CpProxyZappOrgTestWidgetController1BeginSetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t aRegisterValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetWidgetRegister(buf_aWidgetUdn, aRegisterIndex, aRegisterValue, functor);
}

int32_t CpProxyZappOrgTestWidgetController1EndSetWidgetRegister(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetWidgetRegister(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidgetController1SyncGetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, uint32_t* aRegisterValue)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    proxyC->Proxy()->SyncGetWidgetRegister(buf_aWidgetUdn, aRegisterIndex, *aRegisterValue);
}

void CpProxyZappOrgTestWidgetController1BeginGetWidgetRegister(THandle aHandle, const char* aWidgetUdn, uint32_t aRegisterIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aWidgetUdn(aWidgetUdn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetWidgetRegister(buf_aWidgetUdn, aRegisterIndex, functor);
}

int32_t CpProxyZappOrgTestWidgetController1EndGetWidgetRegister(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRegisterValue)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidgetController1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidgetController1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetWidgetRegister(*async, *aRegisterValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

