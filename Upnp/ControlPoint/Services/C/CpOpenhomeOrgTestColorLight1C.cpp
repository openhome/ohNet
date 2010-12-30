#include "CpOpenhomeOrgTestColorLight1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyOpenhomeOrgTestColorLight1C : public CpProxyC
{
public:
    CpProxyOpenhomeOrgTestColorLight1C(CpDeviceC aDevice);
    ~CpProxyOpenhomeOrgTestColorLight1C();
    //CpProxyOpenhomeOrgTestColorLight1* Proxy() { return static_cast<CpProxyOpenhomeOrgTestColorLight1*>(iProxy); }

    void SyncGetName(Brh& aFriendlyName);
    void BeginGetName(FunctorAsync& aFunctor);
    void EndGetName(IAsync& aAsync, Brh& aFriendlyName);

    void SyncSetColor(TUint aRed, TUint aGreen, TUint aBlue);
    void BeginSetColor(TUint aRed, TUint aGreen, TUint aBlue, FunctorAsync& aFunctor);
    void EndSetColor(IAsync& aAsync);

    void SyncGetColor(TUint& aRed, TUint& aGreen, TUint& aBlue);
    void BeginGetColor(FunctorAsync& aFunctor);
    void EndGetColor(IAsync& aAsync, TUint& aRed, TUint& aGreen, TUint& aBlue);

    void SyncGetMaxColors(TUint& aRed, TUint& aGreen, TUint& aBlue);
    void BeginGetMaxColors(FunctorAsync& aFunctor);
    void EndGetMaxColors(IAsync& aAsync, TUint& aRed, TUint& aGreen, TUint& aBlue);


private:
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionGetName;
    Action* iActionSetColor;
    Action* iActionGetColor;
    Action* iActionGetMaxColors;
};


class SyncGetNameOpenhomeOrgTestColorLight1C : public SyncProxyAction
{
public:
    SyncGetNameOpenhomeOrgTestColorLight1C(CpProxyOpenhomeOrgTestColorLight1C& aProxy, Brh& aFriendlyName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1C& iService;
    Brh& iFriendlyName;
};

SyncGetNameOpenhomeOrgTestColorLight1C::SyncGetNameOpenhomeOrgTestColorLight1C(CpProxyOpenhomeOrgTestColorLight1C& aProxy, Brh& aFriendlyName)
    : iService(aProxy)
    , iFriendlyName(aFriendlyName)
{
}

void SyncGetNameOpenhomeOrgTestColorLight1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetName(aAsync, iFriendlyName);
}


class SyncSetColorOpenhomeOrgTestColorLight1C : public SyncProxyAction
{
public:
    SyncSetColorOpenhomeOrgTestColorLight1C(CpProxyOpenhomeOrgTestColorLight1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1C& iService;
};

SyncSetColorOpenhomeOrgTestColorLight1C::SyncSetColorOpenhomeOrgTestColorLight1C(CpProxyOpenhomeOrgTestColorLight1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorOpenhomeOrgTestColorLight1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColor(aAsync);
}


class SyncGetColorOpenhomeOrgTestColorLight1C : public SyncProxyAction
{
public:
    SyncGetColorOpenhomeOrgTestColorLight1C(CpProxyOpenhomeOrgTestColorLight1C& aProxy, TUint& aRed, TUint& aGreen, TUint& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1C& iService;
    TUint& iRed;
    TUint& iGreen;
    TUint& iBlue;
};

SyncGetColorOpenhomeOrgTestColorLight1C::SyncGetColorOpenhomeOrgTestColorLight1C(CpProxyOpenhomeOrgTestColorLight1C& aProxy, TUint& aRed, TUint& aGreen, TUint& aBlue)
    : iService(aProxy)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetColorOpenhomeOrgTestColorLight1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColor(aAsync, iRed, iGreen, iBlue);
}


class SyncGetMaxColorsOpenhomeOrgTestColorLight1C : public SyncProxyAction
{
public:
    SyncGetMaxColorsOpenhomeOrgTestColorLight1C(CpProxyOpenhomeOrgTestColorLight1C& aProxy, TUint& aRed, TUint& aGreen, TUint& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1C& iService;
    TUint& iRed;
    TUint& iGreen;
    TUint& iBlue;
};

SyncGetMaxColorsOpenhomeOrgTestColorLight1C::SyncGetMaxColorsOpenhomeOrgTestColorLight1C(CpProxyOpenhomeOrgTestColorLight1C& aProxy, TUint& aRed, TUint& aGreen, TUint& aBlue)
    : iService(aProxy)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetMaxColorsOpenhomeOrgTestColorLight1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMaxColors(aAsync, iRed, iGreen, iBlue);
}

CpProxyOpenhomeOrgTestColorLight1C::CpProxyOpenhomeOrgTestColorLight1C(CpDeviceC aDevice)
    : CpProxyC("openhome-org", "TestColorLight", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;

    iActionGetName = new Action("GetName");
    param = new Zapp::ParameterString("FriendlyName");
    iActionGetName->AddOutputParameter(param);

    iActionSetColor = new Action("SetColor");
    param = new Zapp::ParameterUint("Red");
    iActionSetColor->AddInputParameter(param);
    param = new Zapp::ParameterUint("Green");
    iActionSetColor->AddInputParameter(param);
    param = new Zapp::ParameterUint("Blue");
    iActionSetColor->AddInputParameter(param);

    iActionGetColor = new Action("GetColor");
    param = new Zapp::ParameterUint("Red");
    iActionGetColor->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Green");
    iActionGetColor->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Blue");
    iActionGetColor->AddOutputParameter(param);

    iActionGetMaxColors = new Action("GetMaxColors");
    param = new Zapp::ParameterUint("Red");
    iActionGetMaxColors->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Green");
    iActionGetMaxColors->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Blue");
    iActionGetMaxColors->AddOutputParameter(param);
}

CpProxyOpenhomeOrgTestColorLight1C::~CpProxyOpenhomeOrgTestColorLight1C()
{
    DestroyService();
    delete iActionGetName;
    delete iActionSetColor;
    delete iActionGetColor;
    delete iActionGetMaxColors;
}

void CpProxyOpenhomeOrgTestColorLight1C::SyncGetName(Brh& aFriendlyName)
{
    SyncGetNameOpenhomeOrgTestColorLight1C sync(*this, aFriendlyName);
    BeginGetName(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1C::BeginGetName(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1C::EndGetName(IAsync& aAsync, Brh& aFriendlyName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aFriendlyName);
}

void CpProxyOpenhomeOrgTestColorLight1C::SyncSetColor(TUint aRed, TUint aGreen, TUint aBlue)
{
    SyncSetColorOpenhomeOrgTestColorLight1C sync(*this);
    BeginSetColor(aRed, aGreen, aBlue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1C::BeginSetColor(TUint aRed, TUint aGreen, TUint aBlue, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRed));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aGreen));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aBlue));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1C::EndSetColor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestColorLight1C::SyncGetColor(TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    SyncGetColorOpenhomeOrgTestColorLight1C sync(*this, aRed, aGreen, aBlue);
    BeginGetColor(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1C::BeginGetColor(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetColor, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColor->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1C::EndGetColor(IAsync& aAsync, TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetColor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aRed = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aGreen = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBlue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgTestColorLight1C::SyncGetMaxColors(TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    SyncGetMaxColorsOpenhomeOrgTestColorLight1C sync(*this, aRed, aGreen, aBlue);
    BeginGetMaxColors(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1C::BeginGetMaxColors(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetMaxColors, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMaxColors->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1C::EndGetMaxColors(IAsync& aAsync, TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetMaxColors"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aRed = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aGreen = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBlue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}


THandle CpProxyOpenhomeOrgTestColorLight1Create(CpDeviceC aDevice)
{
    return new CpProxyOpenhomeOrgTestColorLight1C(aDevice);
}

void CpProxyOpenhomeOrgTestColorLight1Destroy(THandle aHandle)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    delete proxyC;
}

void CpProxyOpenhomeOrgTestColorLight1SyncGetName(THandle aHandle, char** aFriendlyName)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFriendlyName;
    proxyC->SyncGetName(buf_aFriendlyName);
    *aFriendlyName = buf_aFriendlyName.Extract();
}

void CpProxyOpenhomeOrgTestColorLight1BeginGetName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetName(functor);
}

int32_t CpProxyOpenhomeOrgTestColorLight1EndGetName(THandle aHandle, ZappHandleAsync aAsync, char** aFriendlyName)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aFriendlyName;
    *aFriendlyName = NULL;
    try {
        proxyC->EndGetName(*async, buf_aFriendlyName);
        *aFriendlyName = buf_aFriendlyName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyOpenhomeOrgTestColorLight1SyncSetColor(THandle aHandle, uint32_t aRed, uint32_t aGreen, uint32_t aBlue)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetColor(aRed, aGreen, aBlue);
}

void CpProxyOpenhomeOrgTestColorLight1BeginSetColor(THandle aHandle, uint32_t aRed, uint32_t aGreen, uint32_t aBlue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetColor(aRed, aGreen, aBlue, functor);
}

int32_t CpProxyOpenhomeOrgTestColorLight1EndSetColor(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetColor(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyOpenhomeOrgTestColorLight1SyncGetColor(THandle aHandle, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetColor(*aRed, *aGreen, *aBlue);
}

void CpProxyOpenhomeOrgTestColorLight1BeginGetColor(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetColor(functor);
}

int32_t CpProxyOpenhomeOrgTestColorLight1EndGetColor(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetColor(*async, *aRed, *aGreen, *aBlue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyOpenhomeOrgTestColorLight1SyncGetMaxColors(THandle aHandle, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetMaxColors(*aRed, *aGreen, *aBlue);
}

void CpProxyOpenhomeOrgTestColorLight1BeginGetMaxColors(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetMaxColors(functor);
}

int32_t CpProxyOpenhomeOrgTestColorLight1EndGetMaxColors(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestColorLight1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestColorLight1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetMaxColors(*async, *aRed, *aGreen, *aBlue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

