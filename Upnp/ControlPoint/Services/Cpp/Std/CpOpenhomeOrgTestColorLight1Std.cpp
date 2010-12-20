#include <Std/CpOpenhomeOrgTestColorLight1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncGetNameOpenhomeOrgTestColorLight1Cpp : public SyncProxyAction
{
public:
    SyncGetNameOpenhomeOrgTestColorLight1Cpp(CpProxyOpenhomeOrgTestColorLight1Cpp& aProxy, std::string& aFriendlyName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1Cpp& iService;
    std::string& iFriendlyName;
};

SyncGetNameOpenhomeOrgTestColorLight1Cpp::SyncGetNameOpenhomeOrgTestColorLight1Cpp(CpProxyOpenhomeOrgTestColorLight1Cpp& aProxy, std::string& aFriendlyName)
    : iService(aProxy)
    , iFriendlyName(aFriendlyName)
{
}

void SyncGetNameOpenhomeOrgTestColorLight1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetName(aAsync, iFriendlyName);
}


class SyncSetColorOpenhomeOrgTestColorLight1Cpp : public SyncProxyAction
{
public:
    SyncSetColorOpenhomeOrgTestColorLight1Cpp(CpProxyOpenhomeOrgTestColorLight1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1Cpp& iService;
};

SyncSetColorOpenhomeOrgTestColorLight1Cpp::SyncSetColorOpenhomeOrgTestColorLight1Cpp(CpProxyOpenhomeOrgTestColorLight1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorOpenhomeOrgTestColorLight1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColor(aAsync);
}


class SyncGetColorOpenhomeOrgTestColorLight1Cpp : public SyncProxyAction
{
public:
    SyncGetColorOpenhomeOrgTestColorLight1Cpp(CpProxyOpenhomeOrgTestColorLight1Cpp& aProxy, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1Cpp& iService;
    uint32_t& iRed;
    uint32_t& iGreen;
    uint32_t& iBlue;
};

SyncGetColorOpenhomeOrgTestColorLight1Cpp::SyncGetColorOpenhomeOrgTestColorLight1Cpp(CpProxyOpenhomeOrgTestColorLight1Cpp& aProxy, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
    : iService(aProxy)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetColorOpenhomeOrgTestColorLight1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColor(aAsync, iRed, iGreen, iBlue);
}


class SyncGetMaxColorsOpenhomeOrgTestColorLight1Cpp : public SyncProxyAction
{
public:
    SyncGetMaxColorsOpenhomeOrgTestColorLight1Cpp(CpProxyOpenhomeOrgTestColorLight1Cpp& aProxy, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyOpenhomeOrgTestColorLight1Cpp& iService;
    uint32_t& iRed;
    uint32_t& iGreen;
    uint32_t& iBlue;
};

SyncGetMaxColorsOpenhomeOrgTestColorLight1Cpp::SyncGetMaxColorsOpenhomeOrgTestColorLight1Cpp(CpProxyOpenhomeOrgTestColorLight1Cpp& aProxy, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
    : iService(aProxy)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetMaxColorsOpenhomeOrgTestColorLight1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetMaxColors(aAsync, iRed, iGreen, iBlue);
}


CpProxyOpenhomeOrgTestColorLight1Cpp::CpProxyOpenhomeOrgTestColorLight1Cpp(CpDeviceCpp& aDevice)
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

CpProxyOpenhomeOrgTestColorLight1Cpp::~CpProxyOpenhomeOrgTestColorLight1Cpp()
{
    DestroyService();
    delete iActionGetName;
    delete iActionSetColor;
    delete iActionGetColor;
    delete iActionGetMaxColors;
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::SyncGetName(std::string& aFriendlyName)
{
    SyncGetNameOpenhomeOrgTestColorLight1Cpp sync(*this, aFriendlyName);
    BeginGetName(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::BeginGetName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::EndGetName(IAsync& aAsync, std::string& aFriendlyName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aFriendlyName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::SyncSetColor(uint32_t aRed, uint32_t aGreen, uint32_t aBlue)
{
    SyncSetColorOpenhomeOrgTestColorLight1Cpp sync(*this);
    BeginSetColor(aRed, aGreen, aBlue, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::BeginSetColor(uint32_t aRed, uint32_t aGreen, uint32_t aBlue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aRed));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aGreen));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aBlue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::EndSetColor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::SyncGetColor(uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
{
    SyncGetColorOpenhomeOrgTestColorLight1Cpp sync(*this, aRed, aGreen, aBlue);
    BeginGetColor(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::BeginGetColor(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetColor, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColor->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::EndGetColor(IAsync& aAsync, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
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

void CpProxyOpenhomeOrgTestColorLight1Cpp::SyncGetMaxColors(uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
{
    SyncGetMaxColorsOpenhomeOrgTestColorLight1Cpp sync(*this, aRed, aGreen, aBlue);
    BeginGetMaxColors(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::BeginGetMaxColors(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetMaxColors, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetMaxColors->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestColorLight1Cpp::EndGetMaxColors(IAsync& aAsync, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
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

