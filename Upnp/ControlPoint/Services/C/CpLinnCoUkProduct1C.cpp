#include "CpLinnCoUkProduct1.h"
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

class CpProxyLinnCoUkProduct1C : public CpProxyC
{
public:
    CpProxyLinnCoUkProduct1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkProduct1C();
    //CpProxyLinnCoUkProduct1* Proxy() { return static_cast<CpProxyLinnCoUkProduct1*>(iProxy); }

    void SyncRoom(Brh& aaRoom);
    void BeginRoom(FunctorAsync& aFunctor);
    void EndRoom(IAsync& aAsync, Brh& aaRoom);

    void SyncSetRoom(const Brx& aaRoom);
    void BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor);
    void EndSetRoom(IAsync& aAsync);

    void SyncStandby(TBool& aaStandby);
    void BeginStandby(FunctorAsync& aFunctor);
    void EndStandby(IAsync& aAsync, TBool& aaStandby);

    void SyncSetStandby(TBool aaStandby);
    void BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor);
    void EndSetStandby(IAsync& aAsync);

    void SetPropertyRoomChanged(Functor& aFunctor);
    void SetPropertyStandbyChanged(Functor& aFunctor);

    void PropertyRoom(Brhz& aRoom) const;
    void PropertyStandby(TBool& aStandby) const;
private:
    void RoomPropertyChanged();
    void StandbyPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionRoom;
    Action* iActionSetRoom;
    Action* iActionStandby;
    Action* iActionSetStandby;
    PropertyString* iRoom;
    PropertyBool* iStandby;
    Functor iRoomChanged;
    Functor iStandbyChanged;
};


class SyncRoomLinnCoUkProduct1C : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct1C(CpProxyLinnCoUkProduct1C& aProxy, Brh& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1C& iService;
    Brh& iaRoom;
};

SyncRoomLinnCoUkProduct1C::SyncRoomLinnCoUkProduct1C(CpProxyLinnCoUkProduct1C& aProxy, Brh& aaRoom)
    : iService(aProxy)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct1C : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct1C(CpProxyLinnCoUkProduct1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1C& iService;
};

SyncSetRoomLinnCoUkProduct1C::SyncSetRoomLinnCoUkProduct1C(CpProxyLinnCoUkProduct1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRoomLinnCoUkProduct1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct1C : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct1C(CpProxyLinnCoUkProduct1C& aProxy, TBool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1C& iService;
    TBool& iaStandby;
};

SyncStandbyLinnCoUkProduct1C::SyncStandbyLinnCoUkProduct1C(CpProxyLinnCoUkProduct1C& aProxy, TBool& aaStandby)
    : iService(aProxy)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct1C : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct1C(CpProxyLinnCoUkProduct1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1C& iService;
};

SyncSetStandbyLinnCoUkProduct1C::SyncSetStandbyLinnCoUkProduct1C(CpProxyLinnCoUkProduct1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStandbyLinnCoUkProduct1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}

CpProxyLinnCoUkProduct1C::CpProxyLinnCoUkProduct1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Product", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;

    iActionRoom = new Action("Room");
    param = new Zapp::ParameterString("aRoom");
    iActionRoom->AddOutputParameter(param);

    iActionSetRoom = new Action("SetRoom");
    param = new Zapp::ParameterString("aRoom");
    iActionSetRoom->AddInputParameter(param);

    iActionStandby = new Action("Standby");
    param = new Zapp::ParameterBool("aStandby");
    iActionStandby->AddOutputParameter(param);

    iActionSetStandby = new Action("SetStandby");
    param = new Zapp::ParameterBool("aStandby");
    iActionSetStandby->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct1C::RoomPropertyChanged);
    iRoom = new PropertyString("Room", functor);
    AddProperty(iRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct1C::StandbyPropertyChanged);
    iStandby = new PropertyBool("Standby", functor);
    AddProperty(iStandby);
}

CpProxyLinnCoUkProduct1C::~CpProxyLinnCoUkProduct1C()
{
    DestroyService();
    delete iActionRoom;
    delete iActionSetRoom;
    delete iActionStandby;
    delete iActionSetStandby;
}

void CpProxyLinnCoUkProduct1C::SyncRoom(Brh& aaRoom)
{
    SyncRoomLinnCoUkProduct1C sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1C::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct1C::EndRoom(IAsync& aAsync, Brh& aaRoom)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Room"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaRoom);
}

void CpProxyLinnCoUkProduct1C::SyncSetRoom(const Brx& aaRoom)
{
    SyncSetRoomLinnCoUkProduct1C sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1C::BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoom->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaRoom));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct1C::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct1C::SyncStandby(TBool& aaStandby)
{
    SyncStandbyLinnCoUkProduct1C sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1C::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct1C::EndStandby(IAsync& aAsync, TBool& aaStandby)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Standby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaStandby = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct1C::SyncSetStandby(TBool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct1C sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1C::BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct1C::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct1C::SetPropertyRoomChanged(Functor& aFunctor)
{
    iLock.Wait();
    iRoomChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct1C::SetPropertyStandbyChanged(Functor& aFunctor)
{
    iLock.Wait();
    iStandbyChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct1C::PropertyRoom(Brhz& aRoom) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aRoom.Set(iRoom->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkProduct1C::PropertyStandby(TBool& aStandby) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aStandby = iStandby->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkProduct1C::RoomPropertyChanged()
{
    ReportEvent(iRoomChanged);
}

void CpProxyLinnCoUkProduct1C::StandbyPropertyChanged()
{
    ReportEvent(iStandbyChanged);
}


THandle CpProxyLinnCoUkProduct1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkProduct1C(aDevice);
}

void CpProxyLinnCoUkProduct1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkProduct1SyncRoom(THandle aHandle, char** aaRoom)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom;
    proxyC->SyncRoom(buf_aaRoom);
    *aaRoom = buf_aaRoom.Extract();
}

void CpProxyLinnCoUkProduct1BeginRoom(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginRoom(functor);
}

int32_t CpProxyLinnCoUkProduct1EndRoom(THandle aHandle, ZappHandleAsync aAsync, char** aaRoom)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaRoom;
    *aaRoom = NULL;
    try {
        proxyC->EndRoom(*async, buf_aaRoom);
        *aaRoom = buf_aaRoom.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct1SyncSetRoom(THandle aHandle, const char* aaRoom)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    proxyC->SyncSetRoom(buf_aaRoom);
}

void CpProxyLinnCoUkProduct1BeginSetRoom(THandle aHandle, const char* aaRoom, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetRoom(buf_aaRoom, functor);
}

int32_t CpProxyLinnCoUkProduct1EndSetRoom(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetRoom(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct1SyncStandby(THandle aHandle, uint32_t* aaStandby)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStandby = 0;
    proxyC->SyncStandby(*(TBool*)aaStandby);
}

void CpProxyLinnCoUkProduct1BeginStandby(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStandby(functor);
}

int32_t CpProxyLinnCoUkProduct1EndStandby(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStandby)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaStandby = 0;
    try {
        proxyC->EndStandby(*async, *(TBool*)aaStandby);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct1SyncSetStandby(THandle aHandle, uint32_t aaStandby)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStandby((aaStandby==0? false : true));
}

void CpProxyLinnCoUkProduct1BeginSetStandby(THandle aHandle, uint32_t aaStandby, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStandby((aaStandby==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct1EndSetStandby(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStandby(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct1SetPropertyRoomChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyRoomChanged(functor);
}

void CpProxyLinnCoUkProduct1SetPropertyStandbyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStandbyChanged(functor);
}

void CpProxyLinnCoUkProduct1PropertyRoom(THandle aHandle, char** aRoom)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aRoom;
    proxyC->PropertyRoom(buf_aRoom);
    *aRoom = buf_aRoom.Transfer();
}

void CpProxyLinnCoUkProduct1PropertyStandby(THandle aHandle, uint32_t* aStandby)
{
    CpProxyLinnCoUkProduct1C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aStandby = false;
    proxyC->PropertyStandby(*(TBool*)aStandby);
}

