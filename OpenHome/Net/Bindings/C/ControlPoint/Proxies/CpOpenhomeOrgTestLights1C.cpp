#include "CpOpenhomeOrgTestLights1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyOpenhomeOrgTestLights1C : public CpProxyC
{
public:
    CpProxyOpenhomeOrgTestLights1C(CpDeviceC aDevice);
    ~CpProxyOpenhomeOrgTestLights1C();
    //CpProxyOpenhomeOrgTestLights1* Proxy() { return static_cast<CpProxyOpenhomeOrgTestLights1*>(iProxy); }

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
    Action* iActionGetCount;
    Action* iActionGetRoom;
    Action* iActionGetName;
    Action* iActionGetPosition;
    Action* iActionSetColor;
    Action* iActionGetColor;
    Action* iActionGetColorComponents;
};


class SyncGetCountOpenhomeOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetCountOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, TUint& aCount);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetCountOpenhomeOrgTestLights1C() {};
private:
    CpProxyOpenhomeOrgTestLights1C& iService;
    TUint& iCount;
};

SyncGetCountOpenhomeOrgTestLights1C::SyncGetCountOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, TUint& aCount)
    : iService(aProxy)
    , iCount(aCount)
{
}

void SyncGetCountOpenhomeOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetCount(aAsync, iCount);
}


class SyncGetRoomOpenhomeOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetRoomOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, Brh& aRoomName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetRoomOpenhomeOrgTestLights1C() {};
private:
    CpProxyOpenhomeOrgTestLights1C& iService;
    Brh& iRoomName;
};

SyncGetRoomOpenhomeOrgTestLights1C::SyncGetRoomOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, Brh& aRoomName)
    : iService(aProxy)
    , iRoomName(aRoomName)
{
}

void SyncGetRoomOpenhomeOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetRoom(aAsync, iRoomName);
}


class SyncGetNameOpenhomeOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetNameOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, Brh& aFriendlyName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetNameOpenhomeOrgTestLights1C() {};
private:
    CpProxyOpenhomeOrgTestLights1C& iService;
    Brh& iFriendlyName;
};

SyncGetNameOpenhomeOrgTestLights1C::SyncGetNameOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, Brh& aFriendlyName)
    : iService(aProxy)
    , iFriendlyName(aFriendlyName)
{
}

void SyncGetNameOpenhomeOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetName(aAsync, iFriendlyName);
}


class SyncGetPositionOpenhomeOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetPositionOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, TUint& aX, TUint& aY, TUint& aZ);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetPositionOpenhomeOrgTestLights1C() {};
private:
    CpProxyOpenhomeOrgTestLights1C& iService;
    TUint& iX;
    TUint& iY;
    TUint& iZ;
};

SyncGetPositionOpenhomeOrgTestLights1C::SyncGetPositionOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, TUint& aX, TUint& aY, TUint& aZ)
    : iService(aProxy)
    , iX(aX)
    , iY(aY)
    , iZ(aZ)
{
}

void SyncGetPositionOpenhomeOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetPosition(aAsync, iX, iY, iZ);
}


class SyncSetColorOpenhomeOrgTestLights1C : public SyncProxyAction
{
public:
    SyncSetColorOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetColorOpenhomeOrgTestLights1C() {};
private:
    CpProxyOpenhomeOrgTestLights1C& iService;
};

SyncSetColorOpenhomeOrgTestLights1C::SyncSetColorOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetColorOpenhomeOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetColor(aAsync);
}


class SyncGetColorOpenhomeOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetColorOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, TUint& aColor);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetColorOpenhomeOrgTestLights1C() {};
private:
    CpProxyOpenhomeOrgTestLights1C& iService;
    TUint& iColor;
};

SyncGetColorOpenhomeOrgTestLights1C::SyncGetColorOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, TUint& aColor)
    : iService(aProxy)
    , iColor(aColor)
{
}

void SyncGetColorOpenhomeOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColor(aAsync, iColor);
}


class SyncGetColorComponentsOpenhomeOrgTestLights1C : public SyncProxyAction
{
public:
    SyncGetColorComponentsOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncGetColorComponentsOpenhomeOrgTestLights1C() {};
private:
    CpProxyOpenhomeOrgTestLights1C& iService;
    TUint& iBrightness;
    TUint& iRed;
    TUint& iGreen;
    TUint& iBlue;
};

SyncGetColorComponentsOpenhomeOrgTestLights1C::SyncGetColorComponentsOpenhomeOrgTestLights1C(CpProxyOpenhomeOrgTestLights1C& aProxy, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
    : iService(aProxy)
    , iBrightness(aBrightness)
    , iRed(aRed)
    , iGreen(aGreen)
    , iBlue(aBlue)
{
}

void SyncGetColorComponentsOpenhomeOrgTestLights1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndGetColorComponents(aAsync, iBrightness, iRed, iGreen, iBlue);
}

CpProxyOpenhomeOrgTestLights1C::CpProxyOpenhomeOrgTestLights1C(CpDeviceC aDevice)
    : CpProxyC("openhome-org", "TestLights", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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

CpProxyOpenhomeOrgTestLights1C::~CpProxyOpenhomeOrgTestLights1C()
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

void CpProxyOpenhomeOrgTestLights1C::SyncGetCount(TUint& aCount)
{
    SyncGetCountOpenhomeOrgTestLights1C sync(*this, aCount);
    BeginGetCount(sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1C::BeginGetCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionGetCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionGetCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1C::EndGetCount(IAsync& aAsync, TUint& aCount)
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

void CpProxyOpenhomeOrgTestLights1C::SyncGetRoom(TUint aIndex, Brh& aRoomName)
{
    SyncGetRoomOpenhomeOrgTestLights1C sync(*this, aRoomName);
    BeginGetRoom(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1C::BeginGetRoom(TUint aIndex, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestLights1C::EndGetRoom(IAsync& aAsync, Brh& aRoomName)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aRoomName);
}

void CpProxyOpenhomeOrgTestLights1C::SyncGetName(TUint aIndex, Brh& aFriendlyName)
{
    SyncGetNameOpenhomeOrgTestLights1C sync(*this, aFriendlyName);
    BeginGetName(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1C::BeginGetName(TUint aIndex, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestLights1C::EndGetName(IAsync& aAsync, Brh& aFriendlyName)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aFriendlyName);
}

void CpProxyOpenhomeOrgTestLights1C::SyncGetPosition(TUint aIndex, TUint& aX, TUint& aY, TUint& aZ)
{
    SyncGetPositionOpenhomeOrgTestLights1C sync(*this, aX, aY, aZ);
    BeginGetPosition(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1C::BeginGetPosition(TUint aIndex, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestLights1C::EndGetPosition(IAsync& aAsync, TUint& aX, TUint& aY, TUint& aZ)
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

void CpProxyOpenhomeOrgTestLights1C::SyncSetColor(TUint aIndex, TUint aColor)
{
    SyncSetColorOpenhomeOrgTestLights1C sync(*this);
    BeginSetColor(aIndex, aColor, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1C::BeginSetColor(TUint aIndex, TUint aColor, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetColor, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetColor->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aColor));
    Invocable().InvokeAction(*invocation);
}

void CpProxyOpenhomeOrgTestLights1C::EndSetColor(IAsync& aAsync)
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

void CpProxyOpenhomeOrgTestLights1C::SyncGetColor(TUint aIndex, TUint& aColor)
{
    SyncGetColorOpenhomeOrgTestLights1C sync(*this, aColor);
    BeginGetColor(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1C::BeginGetColor(TUint aIndex, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestLights1C::EndGetColor(IAsync& aAsync, TUint& aColor)
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

void CpProxyOpenhomeOrgTestLights1C::SyncGetColorComponents(TUint aColor, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
{
    SyncGetColorComponentsOpenhomeOrgTestLights1C sync(*this, aBrightness, aRed, aGreen, aBlue);
    BeginGetColorComponents(aColor, sync.Functor());
    sync.Wait();
}

void CpProxyOpenhomeOrgTestLights1C::BeginGetColorComponents(TUint aColor, FunctorAsync& aFunctor)
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

void CpProxyOpenhomeOrgTestLights1C::EndGetColorComponents(IAsync& aAsync, TUint& aBrightness, TUint& aRed, TUint& aGreen, TUint& aBlue)
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


THandle STDCALL CpProxyOpenhomeOrgTestLights1Create(CpDeviceC aDevice)
{
    return new CpProxyOpenhomeOrgTestLights1C(aDevice);
}

void STDCALL CpProxyOpenhomeOrgTestLights1Destroy(THandle aHandle)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetCount(THandle aHandle, uint32_t* aCount)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetCount(*aCount);
    }
    catch (ProxyError& ) {
        err = -1;
        *aCount = 0;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetCount(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetCount(functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetCount(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aCount)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
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

int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetRoom(THandle aHandle, uint32_t aIndex, char** aRoomName)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRoomName;
    int32_t err = 0;
    try {
        proxyC->SyncGetRoom(aIndex, buf_aRoomName);
        *aRoomName = buf_aRoomName.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aRoomName = NULL;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetRoom(THandle aHandle, uint32_t aIndex, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetRoom(aIndex, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetRoom(THandle aHandle, OhNetHandleAsync aAsync, char** aRoomName)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
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

int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetName(THandle aHandle, uint32_t aIndex, char** aFriendlyName)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFriendlyName;
    int32_t err = 0;
    try {
        proxyC->SyncGetName(aIndex, buf_aFriendlyName);
        *aFriendlyName = buf_aFriendlyName.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aFriendlyName = NULL;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetName(THandle aHandle, uint32_t aIndex, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetName(aIndex, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetName(THandle aHandle, OhNetHandleAsync aAsync, char** aFriendlyName)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
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

int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetPosition(THandle aHandle, uint32_t aIndex, uint32_t* aX, uint32_t* aY, uint32_t* aZ)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetPosition(aIndex, *aX, *aY, *aZ);
    }
    catch (ProxyError& ) {
        err = -1;
        *aX = 0;
        *aY = 0;
        *aZ = 0;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetPosition(THandle aHandle, uint32_t aIndex, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetPosition(aIndex, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetPosition(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aX, uint32_t* aY, uint32_t* aZ)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
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

int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncSetColor(THandle aHandle, uint32_t aIndex, uint32_t aColor)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncSetColor(aIndex, aColor);
    }
    catch (ProxyError& ) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgTestLights1BeginSetColor(THandle aHandle, uint32_t aIndex, uint32_t aColor, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginSetColor(aIndex, aColor, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndSetColor(THandle aHandle, OhNetHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
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

int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetColor(THandle aHandle, uint32_t aIndex, uint32_t* aColor)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetColor(aIndex, *aColor);
    }
    catch (ProxyError& ) {
        err = -1;
        *aColor = 0;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetColor(THandle aHandle, uint32_t aIndex, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetColor(aIndex, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetColor(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aColor)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
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

int32_t STDCALL CpProxyOpenhomeOrgTestLights1SyncGetColorComponents(THandle aHandle, uint32_t aColor, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncGetColorComponents(aColor, *aBrightness, *aRed, *aGreen, *aBlue);
    }
    catch (ProxyError& ) {
        err = -1;
        *aBrightness = 0;
        *aRed = 0;
        *aGreen = 0;
        *aBlue = 0;
    }
    return err;
}

void STDCALL CpProxyOpenhomeOrgTestLights1BeginGetColorComponents(THandle aHandle, uint32_t aColor, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginGetColorComponents(aColor, functor);
}

int32_t STDCALL CpProxyOpenhomeOrgTestLights1EndGetColorComponents(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aBrightness, uint32_t* aRed, uint32_t* aGreen, uint32_t* aBlue)
{
    int32_t err = 0;
    CpProxyOpenhomeOrgTestLights1C* proxyC = reinterpret_cast<CpProxyOpenhomeOrgTestLights1C*>(aHandle);
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

