#include "CpZappOrgTestLights1.h"
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

class CpProxyZappOrgTestLights1C : public CpProxyC
{
public:
    CpProxyZappOrgTestLights1C(CpDeviceC aDevice);
    ~CpProxyZappOrgTestLights1C();
    //CpProxyZappOrgTestLights1* Proxy() { return static_cast<CpProxyZappOrgTestLights1*>(iProxy); }

    void SyncGetCount(TUint& aCount);
    void BeginGetCount(FunctorAsync& aFunctor);
    void EndGetCount(IAsync& aAsync, TUint& aCount);

    void SyncGetRoom(TUint aIndex, Brh& aRoomName);
    void BeginGetRoom(TUint aIndex, FunctorAsync& aFunctor);
    void EndGetRoom(IAsync& aAsync, Brh& aRoomName);

    void SyncGetName(TUint aIndex, Brh& aFriendlyName);
    void BeginGetName(TUint aIndex, FunctorAsync& aFunctor);
    void EndGetName(IAsync& aAsync, Brh& aFriendlyName);

    void SyncGetPosition(TUint aIndex, TUint& aX, TUint& aY, TUint& aZ);
    void BeginGetPosition(TUint aIndex, FunctorAsync& aFunctor);
    void EndGetPosition(IAsync& aAsync, TUint& aX, TUint& aY, TUint& aZ);

    void SyncSetColor(TUint aIndex, TUint aColor);
    void BeginSetColor(TUint aIndex, TUint aColor, FunctorAsync& aFunctor);
    void EndSetColor(IAsync& aAsync);

    void SyncGetColor(TUint aIndex, TUint& aColor);
    void BeginGetColor(TUint aIndex, FunctorAsync& aFunctor);
    void EndGetColor(IAsync& aAsync, TUint& aColor);

    void SyncGetColorComponents(TUint aColor, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue);
    void BeginGetColorComponents(TUint aColor, FunctorAsync& aFunctor);
    void EndGetColorComponents(IAsync& aAsync, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue);


private:
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionGetCount;
    Action* iActionGetRoom;
    Action* iActionGetName;
    Action* iActionGetPosition;
    Action* iActionSetColor;
    Action* iActionGetColor;
    Action* iActionGetColorComponents;
};


class SyncGetCountZappOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetCountZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, TUint& aCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1C& iService;
    TUint& iCount;
};

SyncGetCountZappOrgTestLights1C::SyncGetCountZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, TUint& aCount)
    : iService(aProxy)
    , iCount(aCount)
{
}

void SyncGetCountZappOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCount(aAsync, iCount);
}


class SyncGetRoomZappOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetRoomZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, Brh& aRoomName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1C& iService;
    Brh& iRoomName;
};

SyncGetRoomZappOrgTestLights1C::SyncGetRoomZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, Brh& aRoomName)
    : iService(aProxy)
    , iRoomName(aRoomName)
{
}

void SyncGetRoomZappOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRoom(aAsync, iRoomName);
}


class SyncGetNameZappOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetNameZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, Brh& aFriendlyName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1C& iService;
    Brh& iFriendlyName;
};

SyncGetNameZappOrgTestLights1C::SyncGetNameZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, Brh& aFriendlyName)
    : iService(aProxy)
    , iFriendlyName(aFriendlyName)
{
}

void SyncGetNameZappOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetName(aAsync, iFriendlyName);
}


class SyncGetPositionZappOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetPositionZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, TUint& aX, TUint& aY, TUint& aZ);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1C& iService;
    TUint& iX;
    TUint& iY;
    TUint& iZ;
};

SyncGetPositionZappOrgTestLights1C::SyncGetPositionZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, TUint& aX, TUint& aY, TUint& aZ)
    : iService(aProxy)
    , iX(aX)
    , iY(aY)
    , iZ(aZ)
{
}

void SyncGetPositionZappOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPosition(aAsync, iX, iY, iZ);
}


class SyncSetColorZappOrgTestLights1C : public SyncProxyAction
{
public:
    SyncSetColorZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1C& iService;
};

SyncSetColorZappOrgTestLights1C::SyncSetColorZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorZappOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColor(aAsync);
}


class SyncGetColorZappOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetColorZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, TUint& aColor);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1C& iService;
    TUint& iColor;
};

SyncGetColorZappOrgTestLights1C::SyncGetColorZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, TUint& aColor)
    : iService(aProxy)
    , iColor(aColor)
{
}

void SyncGetColorZappOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColor(aAsync, iColor);
}


class SyncGetColorComponentsZappOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetColorComponentsZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyZappOrgTestLights1C& iService;
    TUint& iBrightness;
    TUint& iRed;
    TUint& iGreen;
    TUint& iBlue;
};

SyncGetColorComponentsZappOrgTestLights1C::SyncGetColorComponentsZappOrgTestLights1C(CpProxyZappOrgTestLights1C& aProxy, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
    : iService(aProxy)
    , iBrightness(aBrightness)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetColorComponentsZappOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorComponents(aAsync, iBrightness, iRed, iGreen, iBlue);
}

CpProxyZappOrgTestLights1C::CpProxyZappOrgTestLights1C(CpDeviceC aDevice)
    : CpProxyC("zapp-org", "TestLights", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
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

CpProxyZappOrgTestLights1C::~CpProxyZappOrgTestLights1C()
{
    delete iActionGetCount;
    delete iActionGetRoom;
    delete iActionGetName;
    delete iActionGetPosition;
    delete iActionSetColor;
    delete iActionGetColor;
    delete iActionGetColorComponents;
}

void CpProxyZappOrgTestLights1C::SyncGetCount(TUint& aCount)
{
    SyncGetCountZappOrgTestLights1C sync(*this, aCount);
    BeginGetCount(sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1C::BeginGetCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestLights1C::EndGetCount(IAsync& aAsync, TUint& aCount)
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

void CpProxyZappOrgTestLights1C::SyncGetRoom(TUint aIndex, Brh& aRoomName)
{
    SyncGetRoomZappOrgTestLights1C sync(*this, aRoomName);
    BeginGetRoom(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1C::BeginGetRoom(TUint aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetRoom->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestLights1C::EndGetRoom(IAsync& aAsync, Brh& aRoomName)
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

void CpProxyZappOrgTestLights1C::SyncGetName(TUint aIndex, Brh& aFriendlyName)
{
    SyncGetNameZappOrgTestLights1C sync(*this, aFriendlyName);
    BeginGetName(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1C::BeginGetName(TUint aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestLights1C::EndGetName(IAsync& aAsync, Brh& aFriendlyName)
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

void CpProxyZappOrgTestLights1C::SyncGetPosition(TUint aIndex, TUint& aX, TUint& aY, TUint& aZ)
{
    SyncGetPositionZappOrgTestLights1C sync(*this, aX, aY, aZ);
    BeginGetPosition(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1C::BeginGetPosition(TUint aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetPosition, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetPosition->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetPosition->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestLights1C::EndGetPosition(IAsync& aAsync, TUint& aX, TUint& aY, TUint& aZ)
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

void CpProxyZappOrgTestLights1C::SyncSetColor(TUint aIndex, TUint aColor)
{
    SyncSetColorZappOrgTestLights1C sync(*this);
    BeginSetColor(aIndex, aColor, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1C::BeginSetColor(TUint aIndex, TUint aColor, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aColor));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestLights1C::EndSetColor(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetColor"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyZappOrgTestLights1C::SyncGetColor(TUint aIndex, TUint& aColor)
{
    SyncGetColorZappOrgTestLights1C sync(*this, aColor);
    BeginGetColor(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1C::BeginGetColor(TUint aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColor->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestLights1C::EndGetColor(IAsync& aAsync, TUint& aColor)
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

void CpProxyZappOrgTestLights1C::SyncGetColorComponents(TUint aColor, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    SyncGetColorComponentsZappOrgTestLights1C sync(*this, aBrightness, aRed, aGreen, aBlue);
    BeginGetColorComponents(aColor, sync.Functor());
    sync.Wait();
}

void CpProxyZappOrgTestLights1C::BeginGetColorComponents(TUint aColor, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetColorComponents, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionGetColorComponents->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aColor));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetColorComponents->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyZappOrgTestLights1C::EndGetColorComponents(IAsync& aAsync, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
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


THandle CpProxyZappOrgTestLights1Create(CpDeviceC aDevice)
{
    return new CpProxyZappOrgTestLights1C(aDevice);
}

void CpProxyZappOrgTestLights1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestLights1SyncGetCount(THandle aHandle, uint32_t* aCount)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetCount(*aCount);
}

void CpProxyZappOrgTestLights1BeginGetCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetCount(functor);
}

int32_t CpProxyZappOrgTestLights1EndGetCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aCount)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetCount(*async, *aCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestLights1SyncGetRoom(THandle aHandle, uint32_t aIndex, char** aRoomName)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRoomName;
    proxyC->SyncGetRoom(aIndex, buf_aRoomName);
    *aRoomName = buf_aRoomName.Extract();
}

void CpProxyZappOrgTestLights1BeginGetRoom(THandle aHandle, uint32_t aIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetRoom(aIndex, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetRoom(THandle aHandle, ZappHandleAsync aAsync, char** aRoomName)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aRoomName;
    *aRoomName = NULL;
    try {
        proxyC->EndGetRoom(*async, buf_aRoomName);
        *aRoomName = buf_aRoomName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestLights1SyncGetName(THandle aHandle, uint32_t aIndex, char** aFriendlyName)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFriendlyName;
    proxyC->SyncGetName(aIndex, buf_aFriendlyName);
    *aFriendlyName = buf_aFriendlyName.Extract();
}

void CpProxyZappOrgTestLights1BeginGetName(THandle aHandle, uint32_t aIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetName(aIndex, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetName(THandle aHandle, ZappHandleAsync aAsync, char** aFriendlyName)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
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

void CpProxyZappOrgTestLights1SyncGetPosition(THandle aHandle, uint32_t aIndex, uint32_t* aX, uint32_t* aY, uint32_t* aZ)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetPosition(aIndex, *aX, *aY, *aZ);
}

void CpProxyZappOrgTestLights1BeginGetPosition(THandle aHandle, uint32_t aIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetPosition(aIndex, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetPosition(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aX, uint32_t* aY, uint32_t* aZ)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetPosition(*async, *aX, *aY, *aZ);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestLights1SyncSetColor(THandle aHandle, uint32_t aIndex, uint32_t aColor)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetColor(aIndex, aColor);
}

void CpProxyZappOrgTestLights1BeginSetColor(THandle aHandle, uint32_t aIndex, uint32_t aColor, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetColor(aIndex, aColor, functor);
}

int32_t CpProxyZappOrgTestLights1EndSetColor(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
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

void CpProxyZappOrgTestLights1SyncGetColor(THandle aHandle, uint32_t aIndex, uint32_t* aColor)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetColor(aIndex, *aColor);
}

void CpProxyZappOrgTestLights1BeginGetColor(THandle aHandle, uint32_t aIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetColor(aIndex, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetColor(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aColor)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetColor(*async, *aColor);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestLights1SyncGetColorComponents(THandle aHandle, uint32_t aColor, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncGetColorComponents(aColor, *aBrightness, *aRed, *aGreen, *aBlue);
}

void CpProxyZappOrgTestLights1BeginGetColorComponents(THandle aHandle, uint32_t aColor, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginGetColorComponents(aColor, functor);
}

int32_t CpProxyZappOrgTestLights1EndGetColorComponents(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    int32_t err = 0;
    CpProxyZappOrgTestLights1C* proxyC = reinterpret_cast<CpProxyZappOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndGetColorComponents(*async, *aBrightness, *aRed, *aGreen, *aBlue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

