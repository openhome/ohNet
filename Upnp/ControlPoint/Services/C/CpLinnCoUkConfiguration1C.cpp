#include <C/CpLinnCoUkConfiguration1.h>
#include <Core/CpLinnCoUkConfiguration1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkConfiguration1C : public CpProxyC
{
public:
    CpProxyLinnCoUkConfiguration1C(CpDeviceC aDevice);
    CpProxyLinnCoUkConfiguration1* Proxy() { return static_cast<CpProxyLinnCoUkConfiguration1*>(iProxy); }
};

CpProxyLinnCoUkConfiguration1C::CpProxyLinnCoUkConfiguration1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkConfiguration1(*iDevice);
}


THandle CpProxyLinnCoUkConfiguration1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkConfiguration1C(aDevice);
}

void CpProxyLinnCoUkConfiguration1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkConfiguration1SyncConfigurationXml(THandle aHandle, char** aaConfigurationXml)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaConfigurationXml;
    proxyC->Proxy()->SyncConfigurationXml(buf_aaConfigurationXml);
    *aaConfigurationXml = buf_aaConfigurationXml.Extract();
}

void CpProxyLinnCoUkConfiguration1BeginConfigurationXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginConfigurationXml(functor);
}

int32_t CpProxyLinnCoUkConfiguration1EndConfigurationXml(THandle aHandle, ZappHandleAsync aAsync, char** aaConfigurationXml)
{
    int32_t err = 0;
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaConfigurationXml;
    *aaConfigurationXml = NULL;
    try {
        proxyC->Proxy()->EndConfigurationXml(*async, buf_aaConfigurationXml);
        *aaConfigurationXml = buf_aaConfigurationXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkConfiguration1SyncParameterXml(THandle aHandle, char** aaParameterXml)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaParameterXml;
    proxyC->Proxy()->SyncParameterXml(buf_aaParameterXml);
    *aaParameterXml = buf_aaParameterXml.Extract();
}

void CpProxyLinnCoUkConfiguration1BeginParameterXml(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginParameterXml(functor);
}

int32_t CpProxyLinnCoUkConfiguration1EndParameterXml(THandle aHandle, ZappHandleAsync aAsync, char** aaParameterXml)
{
    int32_t err = 0;
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaParameterXml;
    *aaParameterXml = NULL;
    try {
        proxyC->Proxy()->EndParameterXml(*async, buf_aaParameterXml);
        *aaParameterXml = buf_aaParameterXml.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkConfiguration1SyncSetParameter(THandle aHandle, const char* aaTarget, const char* aaName, const char* aaValue)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaTarget(aaTarget);
    Brh buf_aaName(aaName);
    Brh buf_aaValue(aaValue);
    proxyC->Proxy()->SyncSetParameter(buf_aaTarget, buf_aaName, buf_aaValue);
}

void CpProxyLinnCoUkConfiguration1BeginSetParameter(THandle aHandle, const char* aaTarget, const char* aaName, const char* aaValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaTarget(aaTarget);
    Brh buf_aaName(aaName);
    Brh buf_aaValue(aaValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetParameter(buf_aaTarget, buf_aaName, buf_aaValue, functor);
}

int32_t CpProxyLinnCoUkConfiguration1EndSetParameter(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetParameter(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkConfiguration1SetPropertyConfigurationXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyConfigurationXmlChanged(functor);
}

void CpProxyLinnCoUkConfiguration1SetPropertyParameterXmlChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyParameterXmlChanged(functor);
}

void CpProxyLinnCoUkConfiguration1PropertyConfigurationXml(THandle aHandle, char** aConfigurationXml)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aConfigurationXml;
    proxyC->Proxy()->PropertyConfigurationXml(buf_aConfigurationXml);
    *aConfigurationXml = buf_aConfigurationXml.Transfer();
}

void CpProxyLinnCoUkConfiguration1PropertyParameterXml(THandle aHandle, char** aParameterXml)
{
    CpProxyLinnCoUkConfiguration1C* proxyC = reinterpret_cast<CpProxyLinnCoUkConfiguration1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aParameterXml;
    proxyC->Proxy()->PropertyParameterXml(buf_aParameterXml);
    *aParameterXml = buf_aParameterXml.Transfer();
}

