#include <Std/CpLinnCoUkProduct1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncRoomLinnCoUkProduct1Cpp : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct1Cpp(CpProxyLinnCoUkProduct1Cpp& aService, std::string& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1Cpp& iService;
    std::string& iaRoom;
};

SyncRoomLinnCoUkProduct1Cpp::SyncRoomLinnCoUkProduct1Cpp(CpProxyLinnCoUkProduct1Cpp& aService, std::string& aaRoom)
    : iService(aService)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct1Cpp : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct1Cpp(CpProxyLinnCoUkProduct1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1Cpp& iService;
};

SyncSetRoomLinnCoUkProduct1Cpp::SyncSetRoomLinnCoUkProduct1Cpp(CpProxyLinnCoUkProduct1Cpp& aService)
    : iService(aService)
{
}

void SyncSetRoomLinnCoUkProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct1Cpp : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct1Cpp(CpProxyLinnCoUkProduct1Cpp& aService, bool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1Cpp& iService;
    bool& iaStandby;
};

SyncStandbyLinnCoUkProduct1Cpp::SyncStandbyLinnCoUkProduct1Cpp(CpProxyLinnCoUkProduct1Cpp& aService, bool& aaStandby)
    : iService(aService)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct1Cpp : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct1Cpp(CpProxyLinnCoUkProduct1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct1Cpp& iService;
};

SyncSetStandbyLinnCoUkProduct1Cpp::SyncSetStandbyLinnCoUkProduct1Cpp(CpProxyLinnCoUkProduct1Cpp& aService)
    : iService(aService)
{
}

void SyncSetStandbyLinnCoUkProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


CpProxyLinnCoUkProduct1Cpp::CpProxyLinnCoUkProduct1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct1Cpp::RoomPropertyChanged);
    iRoom = new PropertyString("Room", functor);
    iService->AddProperty(iRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct1Cpp::StandbyPropertyChanged);
    iStandby = new PropertyBool("Standby", functor);
    iService->AddProperty(iStandby);
}

CpProxyLinnCoUkProduct1Cpp::~CpProxyLinnCoUkProduct1Cpp()
{
    delete iService;
    delete iActionRoom;
    delete iActionSetRoom;
    delete iActionStandby;
    delete iActionSetStandby;
}

void CpProxyLinnCoUkProduct1Cpp::SyncRoom(std::string& aaRoom)
{
    SyncRoomLinnCoUkProduct1Cpp sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1Cpp::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct1Cpp::EndRoom(IAsync& aAsync, std::string& aaRoom)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Room"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaRoom.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProduct1Cpp::SyncSetRoom(const std::string& aaRoom)
{
    SyncSetRoomLinnCoUkProduct1Cpp sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1Cpp::BeginSetRoom(const std::string& aaRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoom->InputParameters();
    {
        Brn buf((const TByte*)aaRoom.c_str(), aaRoom.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct1Cpp::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct1Cpp::SyncStandby(bool& aaStandby)
{
    SyncStandbyLinnCoUkProduct1Cpp sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1Cpp::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct1Cpp::EndStandby(IAsync& aAsync, bool& aaStandby)
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

void CpProxyLinnCoUkProduct1Cpp::SyncSetStandby(bool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct1Cpp sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct1Cpp::BeginSetStandby(bool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct1Cpp::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct1Cpp::SetPropertyRoomChanged(Functor& aFunctor)
{
    iLock->Wait();
    iRoomChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct1Cpp::SetPropertyStandbyChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStandbyChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct1Cpp::PropertyRoom(std::string& aRoom) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iRoom->Value();
    aRoom.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProduct1Cpp::PropertyStandby(bool& aStandby) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStandby = iStandby->Value();
}

void CpProxyLinnCoUkProduct1Cpp::RoomPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iRoomChanged != NULL) {
        iRoomChanged();
    }
}

void CpProxyLinnCoUkProduct1Cpp::StandbyPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStandbyChanged != NULL) {
        iStandbyChanged();
    }
}

