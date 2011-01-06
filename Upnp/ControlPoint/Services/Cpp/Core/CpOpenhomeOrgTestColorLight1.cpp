#include "CpOpenhomeOrgTestColorLight1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncGetNameOpenhomeOrgTestColorLight1 : public SyncProxyAction
{
public:
    SyncGetNameOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1& aProxy, Brh& aFriendlyName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1& iService;
    Brh& iFriendlyName;
};

SyncGetNameOpenhomeOrgTestColorLight1::SyncGetNameOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1& aProxy, Brh& aFriendlyName)
    : iService(aProxy)
    , iFriendlyName(aFriendlyName)
{
}

void SyncGetNameOpenhomeOrgTestColorLight1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetName(aAsync, iFriendlyName);
}


class SyncSetColorOpenhomeOrgTestColorLight1 : public SyncProxyAction
{
public:
    SyncSetColorOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1& iService;
};

SyncSetColorOpenhomeOrgTestColorLight1::SyncSetColorOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorOpenhomeOrgTestColorLight1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColor(aAsync);
}


class SyncGetColorOpenhomeOrgTestColorLight1 : public SyncProxyAction
{
public:
    SyncGetColorOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1& aProxy, TUint& aRed, TUint& aGreen, TUint& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1& iService;
    TUint& iRed;
    TUint& iGreen;
    TUint& iBlue;
};

SyncGetColorOpenhomeOrgTestColorLight1::SyncGetColorOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1& aProxy, TUint& aRed, TUint& aGreen, TUint& aBlue)
    : iService(aProxy)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetColorOpenhomeOrgTestColorLight1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColor(aAsync, iRed, iGreen, iBlue);
}


class SyncGetMaxColorsOpenhomeOrgTestColorLight1 : public SyncProxyAction
{
public:
    SyncGetMaxColorsOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1& aProxy, TUint& aRed, TUint& aGreen, TUint& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1& iService;
    TUint& iRed;
    TUint& iGreen;
    TUint& iBlue;
};

SyncGetMaxColorsOpenhomeOrgTestColorLight1::SyncGetMaxColorsOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1& aProxy, TUint& aRed, TUint& aGreen, TUint& aBlue)
    : iService(aProxy)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetMaxColorsOpenhomeOrgTestColorLight1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMaxColors(aAsync, iRed, iGreen, iBlue);
}


CpProxyOpenhomeOrgTestColorLight1::CpProxyOpenhomeOrgTestColorLight1(CpDevice& aDevice)
    : CpProxy("openhome-org", "TestColorLight", 1, aDevice.Device())
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

CpProxyOpenhomeOrgTestColorLight1::~CpProxyOpenhomeOrgTestColorLight1()
{
    DestroyService();
    delete iActionGetName;
    delete iActionSetColor;
    delete iActionGetColor;
    delete iActionGetMaxColors;
}

void CpProxyOpenhomeOrgTestColorLight1::SyncGetName(Brh& aFriendlyName)
{
    SyncGetNameOpenhomeOrgTestColorLight1 sync(*this, aFriendlyName);
    BeginGetName(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1::BeginGetName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1::EndGetName(IAsync& aAsync, Brh& aFriendlyName)
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

void CpProxyOpenhomeOrgTestColorLight1::SyncSetColor(TUint aRed, TUint aGreen, TUint aBlue)
{
    SyncSetColorOpenhomeOrgTestColorLight1 sync(*this);
    BeginSetColor(aRed, aGreen, aBlue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1::BeginSetColor(TUint aRed, TUint aGreen, TUint aBlue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRed));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aGreen));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aBlue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1::EndSetColor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestColorLight1::SyncGetColor(TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    SyncGetColorOpenhomeOrgTestColorLight1 sync(*this, aRed, aGreen, aBlue);
    BeginGetColor(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1::BeginGetColor(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetColor, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColor->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1::EndGetColor(IAsync& aAsync, TUint& aRed, TUint& aGreen, TUint& aBlue)
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

void CpProxyOpenhomeOrgTestColorLight1::SyncGetMaxColors(TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    SyncGetMaxColorsOpenhomeOrgTestColorLight1 sync(*this, aRed, aGreen, aBlue);
    BeginGetMaxColors(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1::BeginGetMaxColors(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetMaxColors, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMaxColors->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1::EndGetMaxColors(IAsync& aAsync, TUint& aRed, TUint& aGreen, TUint& aBlue)
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

