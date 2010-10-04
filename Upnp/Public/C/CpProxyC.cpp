#include <C/CpProxy.h>
#include <C/Zapp.h>
#include <CpProxy.h>
#include <C/CpProxyCPrivate.h>
#include <CpiDevice.h>
#include <Core/CpDevice.h>

using namespace Zapp;

CpProxyC::CpProxyC(CpiDevice& aDevice)
{
    iDevice = new CpDevice(aDevice);
}

CpProxyC::~CpProxyC()
{
    delete iProxy;
    iDevice->RemoveRef();
}


void CpProxyCSubscribe(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Subscribe();
}

void CpProxyCUnsubscribe(THandle aHandle)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Unsubscribe();
}

void CpProxyCSetPropertyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyC* proxyC = reinterpret_cast<CpProxyC*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyChanged(functor);
}
