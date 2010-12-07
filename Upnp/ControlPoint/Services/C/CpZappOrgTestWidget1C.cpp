#include <C/CpZappOrgTestWidget1.h>
#include <Core/CpZappOrgTestWidget1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyZappOrgTestWidget1C : public CpProxyC
{
public:
    CpProxyZappOrgTestWidget1C(CpDeviceC aDevice);
    CpProxyZappOrgTestWidget1* Proxy() { return static_cast<CpProxyZappOrgTestWidget1*>(iProxy); }
};

CpProxyZappOrgTestWidget1C::CpProxyZappOrgTestWidget1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyZappOrgTestWidget1(*iDevice);
}


THandle CpProxyZappOrgTestWidget1Create(CpDeviceC aDevice)
{
    return new CpProxyZappOrgTestWidget1C(aDevice);
}

void CpProxyZappOrgTestWidget1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestWidget1SyncSetReadWriteRegister(THandle aHandle, uint32_t aRegisterIndex, uint32_t aRegisterValue)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetReadWriteRegister(aRegisterIndex, aRegisterValue);
}

void CpProxyZappOrgTestWidget1BeginSetReadWriteRegister(THandle aHandle, uint32_t aRegisterIndex, uint32_t aRegisterValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetReadWriteRegister(aRegisterIndex, aRegisterValue, functor);
}

int32_t CpProxyZappOrgTestWidget1EndSetReadWriteRegister(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetReadWriteRegister(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidget1SyncGetWidgetClass(THandle aHandle, uint32_t* aWidgetClass)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetWidgetClass(*aWidgetClass);
}

void CpProxyZappOrgTestWidget1BeginGetWidgetClass(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetWidgetClass(functor);
}

int32_t CpProxyZappOrgTestWidget1EndGetWidgetClass(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aWidgetClass)
{
    int32_t err = 0;
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetWidgetClass(*async, *aWidgetClass);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister0Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyReadWriteRegister0Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister1Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyReadWriteRegister1Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister2Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyReadWriteRegister2Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadWriteRegister3Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyReadWriteRegister3Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister4Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyReadOnlyRegister4Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister5Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyReadOnlyRegister5Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister6Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyReadOnlyRegister6Changed(functor);
}

void CpProxyZappOrgTestWidget1SetPropertyReadOnlyRegister7Changed(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyReadOnlyRegister7Changed(functor);
}

void CpProxyZappOrgTestWidget1PropertyReadWriteRegister0(THandle aHandle, uint32_t* aReadWriteRegister0)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyReadWriteRegister0(*aReadWriteRegister0);
}

void CpProxyZappOrgTestWidget1PropertyReadWriteRegister1(THandle aHandle, uint32_t* aReadWriteRegister1)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyReadWriteRegister1(*aReadWriteRegister1);
}

void CpProxyZappOrgTestWidget1PropertyReadWriteRegister2(THandle aHandle, uint32_t* aReadWriteRegister2)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyReadWriteRegister2(*aReadWriteRegister2);
}

void CpProxyZappOrgTestWidget1PropertyReadWriteRegister3(THandle aHandle, uint32_t* aReadWriteRegister3)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyReadWriteRegister3(*aReadWriteRegister3);
}

void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister4(THandle aHandle, uint32_t* aReadOnlyRegister4)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyReadOnlyRegister4(*aReadOnlyRegister4);
}

void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister5(THandle aHandle, uint32_t* aReadOnlyRegister5)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyReadOnlyRegister5(*aReadOnlyRegister5);
}

void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister6(THandle aHandle, uint32_t* aReadOnlyRegister6)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyReadOnlyRegister6(*aReadOnlyRegister6);
}

void CpProxyZappOrgTestWidget1PropertyReadOnlyRegister7(THandle aHandle, uint32_t* aReadOnlyRegister7)
{
    CpProxyZappOrgTestWidget1C* proxyC = reinterpret_cast<CpProxyZappOrgTestWidget1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyReadOnlyRegister7(*aReadOnlyRegister7);
}

