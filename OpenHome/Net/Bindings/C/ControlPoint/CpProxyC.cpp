#include <OpenHome/Net/C/CpProxy.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include "CpProxyCPrivate.h"
#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Net/C/CpDevice.h>
#include <OpenHome/Private/Printer.h>

using namespace OpenHome;
using namespace OpenHome::Net;

CpProxyC::CpProxyC(CpiDevice& aDevice)
{
    iDevice = new CpDevice(aDevice);
}
CpProxyC::CpProxyC(const TChar* aDomain, const TChar* aName, TUint aVersion, CpiDevice& aDevice)
{
    iProxy = new CpProxy(aDomain, aName, aVersion, aDevice);
    iDevice = NULL;
}

CpProxyC::~CpProxyC()
{
    iProxy->DestroyService();
    delete iProxy;
    if (iDevice != NULL) {
        iDevice->RemoveRef();
    }
}


THandle STDCALL CpProxyCreate(const char* aDomain, const char* aName, uint32_t aVersion, CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    ASSERT(device != NULL);
    return new CpProxyC(aDomain, aName, aVersion, *device);
}

void STDCALL CpProxyDestroy(THandle aProxy)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aProxy);
    delete proxyC;
}

THandle STDCALL CpProxyService(THandle aProxy)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aProxy);
    ASSERT(proxyC != NULL);
    return (THandle)proxyC->Service();
}

void STDCALL CpProxySubscribe(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Subscribe();
}

void STDCALL CpProxyUnsubscribe(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Unsubscribe();
}

void STDCALL CpProxySetPropertyChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyChanged(functor);
}

void STDCALL CpProxySetPropertyInitialEvent(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyInitialEvent(functor);
}

TUint STDCALL CpProxyVersion(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    return proxyC->Version();
}

void STDCALL CpProxyPropertyReadLock(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadLock();
}

void STDCALL CpProxyPropertyReadUnlock(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyReadUnlock();
}

void STDCALL CpProxyAddProperty(THandle aHandle, ServiceProperty aProperty)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    OpenHome::Net::Property* prop = reinterpret_cast<OpenHome::Net::Property*>(aProperty);
    ASSERT(prop != NULL);
    proxyC->AddProperty(prop);
}
