#include <C/CpProxy.h>
#include <C/Zapp.h>
#include <CpProxy.h>
#include <C/CpProxyCPrivate.h>
#include <CpiDevice.h>
#include <C/CpDevice.h>
#include <Printer.h>

using namespace Zapp;

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
    delete iProxy;
    if (iDevice != NULL) {
        iDevice->RemoveRef();
    }
}


THandle CpProxyCreate(const char* aDomain, const char* aName, uint32_t aVersion, CpDeviceC aDevice)
{
    CpiDevice* device = reinterpret_cast<CpiDevice*>(aDevice);
    return new CpProxyC(aDomain, aName, aVersion, *device);
}

void CpProxyDestroy(THandle aProxy)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aProxy);
    delete proxyC;
}

THandle CpProxyService(THandle aProxy)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aProxy);
    return (THandle)proxyC->Service();
}

void CpProxySubscribe(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Subscribe();
}

void CpProxyUnsubscribe(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Unsubscribe();
}

void CpProxySetPropertyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyChanged(functor);
}

void CpProxySetPropertyInitialEvent(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyInitialEvent(functor);
}

void CpProxyAddProperty(THandle aHandle, ServiceProperty aProperty)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    Zapp::Property* prop = reinterpret_cast<Zapp::Property*>(aProperty);
    ASSERT(prop != NULL);
    proxyC->AddProperty(prop);
}
