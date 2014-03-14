#include "CpOpenhomeOrgTestLights1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncGetCountOpenhomeOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetCountOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, uint32_t& aCount);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCountOpenhomeOrgTestLights1Cpp() {}
private:
    CpProxyOpenhomeOrgTestLights1Cpp& iService;
    uint32_t& iCount;
};

SyncGetCountOpenhomeOrgTestLights1Cpp::SyncGetCountOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, uint32_t& aCount)
    : iService(aProxy)
    , iCount(aCount)
{
}

void SyncGetCountOpenhomeOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCount(aAsync, iCount);
}


class SyncGetRoomOpenhomeOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetRoomOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, std::string& aRoomName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRoomOpenhomeOrgTestLights1Cpp() {}
private:
    CpProxyOpenhomeOrgTestLights1Cpp& iService;
    std::string& iRoomName;
};

SyncGetRoomOpenhomeOrgTestLights1Cpp::SyncGetRoomOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, std::string& aRoomName)
    : iService(aProxy)
    , iRoomName(aRoomName)
{
}

void SyncGetRoomOpenhomeOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRoom(aAsync, iRoomName);
}


class SyncGetNameOpenhomeOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetNameOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, std::string& aFriendlyName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetNameOpenhomeOrgTestLights1Cpp() {}
private:
    CpProxyOpenhomeOrgTestLights1Cpp& iService;
    std::string& iFriendlyName;
};

SyncGetNameOpenhomeOrgTestLights1Cpp::SyncGetNameOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, std::string& aFriendlyName)
    : iService(aProxy)
    , iFriendlyName(aFriendlyName)
{
}

void SyncGetNameOpenhomeOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetName(aAsync, iFriendlyName);
}


class SyncGetPositionOpenhomeOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetPositionOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, uint32_t& aX, uint32_t& aY, uint32_t& aZ);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPositionOpenhomeOrgTestLights1Cpp() {}
private:
    CpProxyOpenhomeOrgTestLights1Cpp& iService;
    uint32_t& iX;
    uint32_t& iY;
    uint32_t& iZ;
};

SyncGetPositionOpenhomeOrgTestLights1Cpp::SyncGetPositionOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, uint32_t& aX, uint32_t& aY, uint32_t& aZ)
    : iService(aProxy)
    , iX(aX)
    , iY(aY)
    , iZ(aZ)
{
}

void SyncGetPositionOpenhomeOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPosition(aAsync, iX, iY, iZ);
}


class SyncSetColorOpenhomeOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncSetColorOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetColorOpenhomeOrgTestLights1Cpp() {}
private:
    CpProxyOpenhomeOrgTestLights1Cpp& iService;
};

SyncSetColorOpenhomeOrgTestLights1Cpp::SyncSetColorOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorOpenhomeOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColor(aAsync);
}


class SyncGetColorOpenhomeOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetColorOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, uint32_t& aColor);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetColorOpenhomeOrgTestLights1Cpp() {}
private:
    CpProxyOpenhomeOrgTestLights1Cpp& iService;
    uint32_t& iColor;
};

SyncGetColorOpenhomeOrgTestLights1Cpp::SyncGetColorOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, uint32_t& aColor)
    : iService(aProxy)
    , iColor(aColor)
{
}

void SyncGetColorOpenhomeOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColor(aAsync, iColor);
}


class SyncGetColorComponentsOpenhomeOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetColorComponentsOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetColorComponentsOpenhomeOrgTestLights1Cpp() {}
private:
    CpProxyOpenhomeOrgTestLights1Cpp& iService;
    uint32_t& iBrightness;
    uint32_t& iRed;
    uint32_t& iGreen;
    uint32_t& iBlue;
};

SyncGetColorComponentsOpenhomeOrgTestLights1Cpp::SyncGetColorComponentsOpenhomeOrgTestLights1Cpp(CpProxyOpenhomeOrgTestLights1Cpp& aProxy, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
    : iService(aProxy)
    , iBrightness(aBrightness)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetColorComponentsOpenhomeOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorComponents(aAsync, iBrightness, iRed, iGreen, iBlue);
}


CpProxyOpenhomeOrgTestLights1Cpp::CpProxyOpenhomeOrgTestLights1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("openhome-org", "TestLights", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionGetCount = new Action("GetCount");
    param = new OpenHome::Net::ParameterUint("Count");
    iActionGetCount->AddOutputParameter(param);

    iActionGetRoom = new Action("GetRoom");
    param = new OpenHome::Net::ParameterUint("Index");
    iActionGetRoom->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("RoomName");
    iActionGetRoom->AddOutputParameter(param);

    iActionGetName = new Action("GetName");
    param = new OpenHome::Net::ParameterUint("Index");
    iActionGetName->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("FriendlyName");
    iActionGetName->AddOutputParameter(param);

    iActionGetPosition = new Action("GetPosition");
    param = new OpenHome::Net::ParameterUint("Index");
    iActionGetPosition->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("X");
    iActionGetPosition->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Y");
    iActionGetPosition->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Z");
    iActionGetPosition->AddOutputParameter(param);

    iActionSetColor = new Action("SetColor");
    param = new OpenHome::Net::ParameterUint("Index");
    iActionSetColor->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Color");
    iActionSetColor->AddInputParameter(param);

    iActionGetColor = new Action("GetColor");
    param = new OpenHome::Net::ParameterUint("Index");
    iActionGetColor->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Color");
    iActionGetColor->AddOutputParameter(param);

    iActionGetColorComponents = new Action("GetColorComponents");
    param = new OpenHome::Net::ParameterUint("Color");
    iActionGetColorComponents->AddInputParameter(param);
    param = new OpenHome::Net::ParameterUint("Brightness");
    iActionGetColorComponents->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Red");
    iActionGetColorComponents->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Green");
    iActionGetColorComponents->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("Blue");
    iActionGetColorComponents->AddOutputParameter(param);
}

CpProxyOpenhomeOrgTestLights1Cpp::~CpProxyOpenhomeOrgTestLights1Cpp()
{
    DestroyService();
    delete iActionGetCount;
    delete iActionGetRoom;
    delete iActionGetName;
    delete iActionGetPosition;
    delete iActionSetColor;
    delete iActionGetColor;
    delete iActionGetColorComponents;
}

void CpProxyOpenhomeOrgTestLights1Cpp::SyncGetCount(uint32_t& aCount)
{
    SyncGetCountOpenhomeOrgTestLights1Cpp sync(*this, aCount);
    BeginGetCount(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1Cpp::BeginGetCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1Cpp::EndGetCount(IAsync& aAsync, uint32_t& aCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCount"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgTestLights1Cpp::SyncGetRoom(uint32_t aIndex, std::string& aRoomName)
{
    SyncGetRoomOpenhomeOrgTestLights1Cpp sync(*this, aRoomName);
    BeginGetRoom(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1Cpp::BeginGetRoom(uint32_t aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRoom->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1Cpp::EndGetRoom(IAsync& aAsync, std::string& aRoomName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRoom"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRoomName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyOpenhomeOrgTestLights1Cpp::SyncGetName(uint32_t aIndex, std::string& aFriendlyName)
{
    SyncGetNameOpenhomeOrgTestLights1Cpp sync(*this, aFriendlyName);
    BeginGetName(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1Cpp::BeginGetName(uint32_t aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1Cpp::EndGetName(IAsync& aAsync, std::string& aFriendlyName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetName"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aFriendlyName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyOpenhomeOrgTestLights1Cpp::SyncGetPosition(uint32_t aIndex, uint32_t& aX, uint32_t& aY, uint32_t& aZ)
{
    SyncGetPositionOpenhomeOrgTestLights1Cpp sync(*this, aX, aY, aZ);
    BeginGetPosition(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1Cpp::BeginGetPosition(uint32_t aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetPosition, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPosition->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPosition->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1Cpp::EndGetPosition(IAsync& aAsync, uint32_t& aX, uint32_t& aY, uint32_t& aZ)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPosition"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aX = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aY = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aZ = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgTestLights1Cpp::SyncSetColor(uint32_t aIndex, uint32_t aColor)
{
    SyncSetColorOpenhomeOrgTestLights1Cpp sync(*this);
    BeginSetColor(aIndex, aColor, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1Cpp::BeginSetColor(uint32_t aIndex, uint32_t aColor, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aColor));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1Cpp::EndSetColor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColor"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
}

void CpProxyOpenhomeOrgTestLights1Cpp::SyncGetColor(uint32_t aIndex, uint32_t& aColor)
{
    SyncGetColorOpenhomeOrgTestLights1Cpp sync(*this, aColor);
    BeginGetColor(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1Cpp::BeginGetColor(uint32_t aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColor->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1Cpp::EndGetColor(IAsync& aAsync, uint32_t& aColor)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetColor"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aColor = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyOpenhomeOrgTestLights1Cpp::SyncGetColorComponents(uint32_t aColor, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
{
    SyncGetColorComponentsOpenhomeOrgTestLights1Cpp sync(*this, aBrightness, aRed, aGreen, aBlue);
    BeginGetColorComponents(aColor, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1Cpp::BeginGetColorComponents(uint32_t aColor, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetColorComponents, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetColorComponents->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aColor));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColorComponents->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1Cpp::EndGetColorComponents(IAsync& aAsync, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetColorComponents"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aBrightness = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aRed = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aGreen = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBlue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

