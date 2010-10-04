#include <Core/CpLinnCoUkProduct1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncRoomLinnCoUkProduct1 : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct1(CpProxyLinnCoUkProduct1& aService, Brh& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1& iService;
    Brh& iaRoom;
};

SyncRoomLinnCoUkProduct1::SyncRoomLinnCoUkProduct1(CpProxyLinnCoUkProduct1& aService, Brh& aaRoom)
    : iService(aService)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct1::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct1 : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct1(CpProxyLinnCoUkProduct1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1& iService;
};

SyncSetRoomLinnCoUkProduct1::SyncSetRoomLinnCoUkProduct1(CpProxyLinnCoUkProduct1& aService)
    : iService(aService)
{
}

void SyncSetRoomLinnCoUkProduct1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct1 : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct1(CpProxyLinnCoUkProduct1& aService, TBool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1& iService;
    TBool& iaStandby;
};

SyncStandbyLinnCoUkProduct1::SyncStandbyLinnCoUkProduct1(CpProxyLinnCoUkProduct1& aService, TBool& aaStandby)
    : iService(aService)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct1 : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct1(CpProxyLinnCoUkProduct1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1& iService;
};

SyncSetStandbyLinnCoUkProduct1::SyncSetStandbyLinnCoUkProduct1(CpProxyLinnCoUkProduct1& aService)
    : iService(aService)
{
}

void SyncSetStandbyLinnCoUkProduct1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


CpProxyLinnCoUkProduct1::CpProxyLinnCoUkProduct1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Product", 1, aDevice.Device());
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct1::RoomPropertyChanged);
    iRoom = new PropertyString("Room", functor);
    iService->AddProperty(iRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct1::StandbyPropertyChanged);
    iStandby = new PropertyBool("Standby", functor);
    iService->AddProperty(iStandby);
}

CpProxyLinnCoUkProduct1::~CpProxyLinnCoUkProduct1()
{
    delete iService;
    delete iActionRoom;
    delete iActionSetRoom;
    delete iActionStandby;
    delete iActionSetStandby;
}

void CpProxyLinnCoUkProduct1::SyncRoom(Brh& aaRoom)
{
    SyncRoomLinnCoUkProduct1 sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct1::EndRoom(IAsync& aAsync, Brh& aaRoom)
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

void CpProxyLinnCoUkProduct1::SyncSetRoom(const Brx& aaRoom)
{
    SyncSetRoomLinnCoUkProduct1 sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1::BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoom->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaRoom));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct1::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct1::SyncStandby(TBool& aaStandby)
{
    SyncStandbyLinnCoUkProduct1 sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct1::EndStandby(IAsync& aAsync, TBool& aaStandby)
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

void CpProxyLinnCoUkProduct1::SyncSetStandby(TBool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct1 sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1::BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct1::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct1::SetPropertyRoomChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRoomChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct1::SetPropertyStandbyChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStandbyChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct1::PropertyRoom(Brhz& aRoom) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aRoom.Set(iRoom->Value());
}

void CpProxyLinnCoUkProduct1::PropertyStandby(TBool& aStandby) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStandby = iStandby->Value();
}

void CpProxyLinnCoUkProduct1::RoomPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iRoomChanged != NULL) {
        iRoomChanged();
    }
}

void CpProxyLinnCoUkProduct1::StandbyPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStandbyChanged != NULL) {
        iStandbyChanged();
    }
}

