#include <Core/CpZappOrgTestLights1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncGetCountZappOrgTestLights1 : public SyncProxyAction
{
public:
    SyncGetCountZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, TUint& aCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1& iService;
    TUint& iCount;
};

SyncGetCountZappOrgTestLights1::SyncGetCountZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, TUint& aCount)
    : iService(aService)
    , iCount(aCount)
{
}

void SyncGetCountZappOrgTestLights1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCount(aAsync, iCount);
}


class SyncGetRoomZappOrgTestLights1 : public SyncProxyAction
{
public:
    SyncGetRoomZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, Brh& aRoomName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1& iService;
    Brh& iRoomName;
};

SyncGetRoomZappOrgTestLights1::SyncGetRoomZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, Brh& aRoomName)
    : iService(aService)
    , iRoomName(aRoomName)
{
}

void SyncGetRoomZappOrgTestLights1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRoom(aAsync, iRoomName);
}


class SyncGetNameZappOrgTestLights1 : public SyncProxyAction
{
public:
    SyncGetNameZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, Brh& aFriendlyName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1& iService;
    Brh& iFriendlyName;
};

SyncGetNameZappOrgTestLights1::SyncGetNameZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, Brh& aFriendlyName)
    : iService(aService)
    , iFriendlyName(aFriendlyName)
{
}

void SyncGetNameZappOrgTestLights1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetName(aAsync, iFriendlyName);
}


class SyncGetPositionZappOrgTestLights1 : public SyncProxyAction
{
public:
    SyncGetPositionZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, TUint& aX, TUint& aY, TUint& aZ);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1& iService;
    TUint& iX;
    TUint& iY;
    TUint& iZ;
};

SyncGetPositionZappOrgTestLights1::SyncGetPositionZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, TUint& aX, TUint& aY, TUint& aZ)
    : iService(aService)
    , iX(aX)
    , iY(aY)
    , iZ(aZ)
{
}

void SyncGetPositionZappOrgTestLights1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPosition(aAsync, iX, iY, iZ);
}


class SyncSetColorZappOrgTestLights1 : public SyncProxyAction
{
public:
    SyncSetColorZappOrgTestLights1(CpProxyZappOrgTestLights1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1& iService;
};

SyncSetColorZappOrgTestLights1::SyncSetColorZappOrgTestLights1(CpProxyZappOrgTestLights1& aService)
    : iService(aService)
{
}

void SyncSetColorZappOrgTestLights1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColor(aAsync);
}


class SyncGetColorZappOrgTestLights1 : public SyncProxyAction
{
public:
    SyncGetColorZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, TUint& aColor);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1& iService;
    TUint& iColor;
};

SyncGetColorZappOrgTestLights1::SyncGetColorZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, TUint& aColor)
    : iService(aService)
    , iColor(aColor)
{
}

void SyncGetColorZappOrgTestLights1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColor(aAsync, iColor);
}


class SyncGetColorComponentsZappOrgTestLights1 : public SyncProxyAction
{
public:
    SyncGetColorComponentsZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1& iService;
    TUint& iBrightness;
    TUint& iRed;
    TUint& iGreen;
    TUint& iBlue;
};

SyncGetColorComponentsZappOrgTestLights1::SyncGetColorComponentsZappOrgTestLights1(CpProxyZappOrgTestLights1& aService, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
    : iService(aService)
    , iBrightness(aBrightness)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetColorComponentsZappOrgTestLights1::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorComponents(aAsync, iBrightness, iRed, iGreen, iBlue);
}


CpProxyZappOrgTestLights1::CpProxyZappOrgTestLights1(CpDevice& aDevice)
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

CpProxyZappOrgTestLights1::~CpProxyZappOrgTestLights1()
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

void CpProxyZappOrgTestLights1::SyncGetCount(TUint& aCount)
{
    SyncGetCountZappOrgTestLights1 sync(*this, aCount);
    BeginGetCount(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1::BeginGetCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionGetCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1::EndGetCount(IAsync& aAsync, TUint& aCount)
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

void CpProxyZappOrgTestLights1::SyncGetRoom(TUint aIndex, Brh& aRoomName)
{
    SyncGetRoomZappOrgTestLights1 sync(*this, aRoomName);
    BeginGetRoom(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1::BeginGetRoom(TUint aIndex, FunctorAsync& aFunctor)
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

void CpProxyZappOrgTestLights1::EndGetRoom(IAsync& aAsync, Brh& aRoomName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("GetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRoomName);
}

void CpProxyZappOrgTestLights1::SyncGetName(TUint aIndex, Brh& aFriendlyName)
{
    SyncGetNameZappOrgTestLights1 sync(*this, aFriendlyName);
    BeginGetName(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1::BeginGetName(TUint aIndex, FunctorAsync& aFunctor)
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

void CpProxyZappOrgTestLights1::EndGetName(IAsync& aAsync, Brh& aFriendlyName)
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

void CpProxyZappOrgTestLights1::SyncGetPosition(TUint aIndex, TUint& aX, TUint& aY, TUint& aZ)
{
    SyncGetPositionZappOrgTestLights1 sync(*this, aX, aY, aZ);
    BeginGetPosition(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1::BeginGetPosition(TUint aIndex, FunctorAsync& aFunctor)
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

void CpProxyZappOrgTestLights1::EndGetPosition(IAsync& aAsync, TUint& aX, TUint& aY, TUint& aZ)
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

void CpProxyZappOrgTestLights1::SyncSetColor(TUint aIndex, TUint aColor)
{
    SyncSetColorZappOrgTestLights1 sync(*this);
    BeginSetColor(aIndex, aColor, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1::BeginSetColor(TUint aIndex, TUint aColor, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aColor));
    invocation->Invoke();
}

void CpProxyZappOrgTestLights1::EndSetColor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestLights1::SyncGetColor(TUint aIndex, TUint& aColor)
{
    SyncGetColorZappOrgTestLights1 sync(*this, aColor);
    BeginGetColor(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1::BeginGetColor(TUint aIndex, FunctorAsync& aFunctor)
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

void CpProxyZappOrgTestLights1::EndGetColor(IAsync& aAsync, TUint& aColor)
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

void CpProxyZappOrgTestLights1::SyncGetColorComponents(TUint aColor, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    SyncGetColorComponentsZappOrgTestLights1 sync(*this, aBrightness, aRed, aGreen, aBlue);
    BeginGetColorComponents(aColor, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1::BeginGetColorComponents(TUint aColor, FunctorAsync& aFunctor)
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

void CpProxyZappOrgTestLights1::EndGetColorComponents(IAsync& aAsync, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
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

