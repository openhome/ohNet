#include <Std/CpZappOrgTestLights1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncGetCountZappOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetCountZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, uint32_t& aCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1Cpp& iService;
    uint32_t& iCount;
};

SyncGetCountZappOrgTestLights1Cpp::SyncGetCountZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, uint32_t& aCount)
    : iService(aService)
    , iCount(aCount)
{
}

void SyncGetCountZappOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCount(aAsync, iCount);
}


class SyncGetRoomZappOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetRoomZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, std::string& aRoomName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1Cpp& iService;
    std::string& iRoomName;
};

SyncGetRoomZappOrgTestLights1Cpp::SyncGetRoomZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, std::string& aRoomName)
    : iService(aService)
    , iRoomName(aRoomName)
{
}

void SyncGetRoomZappOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRoom(aAsync, iRoomName);
}


class SyncGetNameZappOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetNameZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, std::string& aFriendlyName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1Cpp& iService;
    std::string& iFriendlyName;
};

SyncGetNameZappOrgTestLights1Cpp::SyncGetNameZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, std::string& aFriendlyName)
    : iService(aService)
    , iFriendlyName(aFriendlyName)
{
}

void SyncGetNameZappOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetName(aAsync, iFriendlyName);
}


class SyncGetPositionZappOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetPositionZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, uint32_t& aX, uint32_t& aY, uint32_t& aZ);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1Cpp& iService;
    uint32_t& iX;
    uint32_t& iY;
    uint32_t& iZ;
};

SyncGetPositionZappOrgTestLights1Cpp::SyncGetPositionZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, uint32_t& aX, uint32_t& aY, uint32_t& aZ)
    : iService(aService)
    , iX(aX)
    , iY(aY)
    , iZ(aZ)
{
}

void SyncGetPositionZappOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPosition(aAsync, iX, iY, iZ);
}


class SyncSetColorZappOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncSetColorZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1Cpp& iService;
};

SyncSetColorZappOrgTestLights1Cpp::SyncSetColorZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService)
    : iService(aService)
{
}

void SyncSetColorZappOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColor(aAsync);
}


class SyncGetColorZappOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetColorZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, uint32_t& aColor);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1Cpp& iService;
    uint32_t& iColor;
};

SyncGetColorZappOrgTestLights1Cpp::SyncGetColorZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, uint32_t& aColor)
    : iService(aService)
    , iColor(aColor)
{
}

void SyncGetColorZappOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColor(aAsync, iColor);
}


class SyncGetColorComponentsZappOrgTestLights1Cpp : public SyncProxyAction
{
public:
    SyncGetColorComponentsZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1Cpp& iService;
    uint32_t& iBrightness;
    uint32_t& iRed;
    uint32_t& iGreen;
    uint32_t& iBlue;
};

SyncGetColorComponentsZappOrgTestLights1Cpp::SyncGetColorComponentsZappOrgTestLights1Cpp(CpProxyZappOrgTestLights1Cpp& aService, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
    : iService(aService)
    , iBrightness(aBrightness)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetColorComponentsZappOrgTestLights1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorComponents(aAsync, iBrightness, iRed, iGreen, iBlue);
}


CpProxyZappOrgTestLights1Cpp::CpProxyZappOrgTestLights1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("zapp-org", "TestLights", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionGetCount = new Action("GetCount");
    param = new Zapp::ParameterUint("Count");
    iActionGetCount->AddOutputParameter(param);

    iActionGetRoom = new Action("GetRoom");
    param = new Zapp::ParameterUint("Index");
    iActionGetRoom->AddInputParameter(param);
    param = new Zapp::ParameterString("RoomName");
    iActionGetRoom->AddOutputParameter(param);

    iActionGetName = new Action("GetName");
    param = new Zapp::ParameterUint("Index");
    iActionGetName->AddInputParameter(param);
    param = new Zapp::ParameterString("FriendlyName");
    iActionGetName->AddOutputParameter(param);

    iActionGetPosition = new Action("GetPosition");
    param = new Zapp::ParameterUint("Index");
    iActionGetPosition->AddInputParameter(param);
    param = new Zapp::ParameterUint("X");
    iActionGetPosition->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Y");
    iActionGetPosition->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Z");
    iActionGetPosition->AddOutputParameter(param);

    iActionSetColor = new Action("SetColor");
    param = new Zapp::ParameterUint("Index");
    iActionSetColor->AddInputParameter(param);
    param = new Zapp::ParameterUint("Color");
    iActionSetColor->AddInputParameter(param);

    iActionGetColor = new Action("GetColor");
    param = new Zapp::ParameterUint("Index");
    iActionGetColor->AddInputParameter(param);
    param = new Zapp::ParameterUint("Color");
    iActionGetColor->AddOutputParameter(param);

    iActionGetColorComponents = new Action("GetColorComponents");
    param = new Zapp::ParameterUint("Color");
    iActionGetColorComponents->AddInputParameter(param);
    param = new Zapp::ParameterUint("Brightness");
    iActionGetColorComponents->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Red");
    iActionGetColorComponents->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Green");
    iActionGetColorComponents->AddOutputParameter(param);
    param = new Zapp::ParameterUint("Blue");
    iActionGetColorComponents->AddOutputParameter(param);
}

CpProxyZappOrgTestLights1Cpp::~CpProxyZappOrgTestLights1Cpp()
{
    delete iService;
    delete iActionGetCount;
    delete iActionGetRoom;
    delete iActionGetName;
    delete iActionGetPosition;
    delete iActionSetColor;
    delete iActionGetColor;
    delete iActionGetColorComponents;
}

void CpProxyZappOrgTestLights1Cpp::SyncGetCount(uint32_t& aCount)
{
    SyncGetCountZappOrgTestLights1Cpp sync(*this, aCount);
    BeginGetCount(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1Cpp::BeginGetCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1Cpp::EndGetCount(IAsync& aAsync, uint32_t& aCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetCount"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestLights1Cpp::SyncGetRoom(uint32_t aIndex, std::string& aRoomName)
{
    SyncGetRoomZappOrgTestLights1Cpp sync(*this, aRoomName);
    BeginGetRoom(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1Cpp::BeginGetRoom(uint32_t aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRoom->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1Cpp::EndGetRoom(IAsync& aAsync, std::string& aRoomName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRoomName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyZappOrgTestLights1Cpp::SyncGetName(uint32_t aIndex, std::string& aFriendlyName)
{
    SyncGetNameZappOrgTestLights1Cpp sync(*this, aFriendlyName);
    BeginGetName(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1Cpp::BeginGetName(uint32_t aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1Cpp::EndGetName(IAsync& aAsync, std::string& aFriendlyName)
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

void CpProxyZappOrgTestLights1Cpp::SyncGetPosition(uint32_t aIndex, uint32_t& aX, uint32_t& aY, uint32_t& aZ)
{
    SyncGetPositionZappOrgTestLights1Cpp sync(*this, aX, aY, aZ);
    BeginGetPosition(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1Cpp::BeginGetPosition(uint32_t aIndex, FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1Cpp::EndGetPosition(IAsync& aAsync, uint32_t& aX, uint32_t& aY, uint32_t& aZ)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetPosition"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aX = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aY = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aZ = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestLights1Cpp::SyncSetColor(uint32_t aIndex, uint32_t aColor)
{
    SyncSetColorZappOrgTestLights1Cpp sync(*this);
    BeginSetColor(aIndex, aColor, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1Cpp::BeginSetColor(uint32_t aIndex, uint32_t aColor, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aColor));
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1Cpp::EndSetColor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestLights1Cpp::SyncGetColor(uint32_t aIndex, uint32_t& aColor)
{
    SyncGetColorZappOrgTestLights1Cpp sync(*this, aColor);
    BeginGetColor(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1Cpp::BeginGetColor(uint32_t aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColor->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1Cpp::EndGetColor(IAsync& aAsync, uint32_t& aColor)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetColor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aColor = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyZappOrgTestLights1Cpp::SyncGetColorComponents(uint32_t aColor, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
{
    SyncGetColorComponentsZappOrgTestLights1Cpp sync(*this, aBrightness, aRed, aGreen, aBlue);
    BeginGetColorComponents(aColor, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1Cpp::BeginGetColorComponents(uint32_t aColor, FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1Cpp::EndGetColorComponents(IAsync& aAsync, uint32_t& aBrightness, uint32_t& aRed, uint32_t& aGreen, uint32_t& aBlue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetColorComponents"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aBrightness = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aRed = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aGreen = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBlue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

