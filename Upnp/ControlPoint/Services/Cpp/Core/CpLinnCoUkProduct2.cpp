#include <Core/CpLinnCoUkProduct2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncTypeLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncTypeLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
    Brh& iaType;
};

SyncTypeLinnCoUkProduct2::SyncTypeLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaType)
    : iService(aService)
    , iaType(aaType)
{
}

void SyncTypeLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndType(aAsync, iaType);
}


class SyncModelLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncModelLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaModel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
    Brh& iaModel;
};

SyncModelLinnCoUkProduct2::SyncModelLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaModel)
    : iService(aService)
    , iaModel(aaModel)
{
}

void SyncModelLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iaModel);
}


class SyncNameLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncNameLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
    Brh& iaName;
};

SyncNameLinnCoUkProduct2::SyncNameLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaName)
    : iService(aService)
    , iaName(aaName)
{
}

void SyncNameLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndName(aAsync, iaName);
}


class SyncSetNameLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncSetNameLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
};

SyncSetNameLinnCoUkProduct2::SyncSetNameLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService)
    : iService(aService)
{
}

void SyncSetNameLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetName(aAsync);
}


class SyncRoomLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
    Brh& iaRoom;
};

SyncRoomLinnCoUkProduct2::SyncRoomLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaRoom)
    : iService(aService)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
};

SyncSetRoomLinnCoUkProduct2::SyncSetRoomLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService)
    : iService(aService)
{
}

void SyncSetRoomLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, TBool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
    TBool& iaStandby;
};

SyncStandbyLinnCoUkProduct2::SyncStandbyLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, TBool& aaStandby)
    : iService(aService)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
};

SyncSetStandbyLinnCoUkProduct2::SyncSetStandbyLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService)
    : iService(aService)
{
}

void SyncSetStandbyLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


class SyncSourceCountLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncSourceCountLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, TUint& aaSourceCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
    TUint& iaSourceCount;
};

SyncSourceCountLinnCoUkProduct2::SyncSourceCountLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, TUint& aaSourceCount)
    : iService(aService)
    , iaSourceCount(aaSourceCount)
{
}

void SyncSourceCountLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceCount(aAsync, iaSourceCount);
}


class SyncSourceIndexLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncSourceIndexLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, TUint& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
    TUint& iaSourceIndex;
};

SyncSourceIndexLinnCoUkProduct2::SyncSourceIndexLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, TUint& aaSourceIndex)
    : iService(aService)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncSourceIndexLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetSourceIndexLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncSetSourceIndexLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
};

SyncSetSourceIndexLinnCoUkProduct2::SyncSetSourceIndexLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService)
    : iService(aService)
{
}

void SyncSetSourceIndexLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndex(aAsync);
}


class SyncSourceTypeLinnCoUkProduct2 : public SyncProxyAction
{
public:
    SyncSourceTypeLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaSourceType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2& iService;
    Brh& iaSourceType;
};

SyncSourceTypeLinnCoUkProduct2::SyncSourceTypeLinnCoUkProduct2(CpProxyLinnCoUkProduct2& aService, Brh& aaSourceType)
    : iService(aService)
    , iaSourceType(aaSourceType)
{
}

void SyncSourceTypeLinnCoUkProduct2::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceType(aAsync, iaSourceType);
}


CpProxyLinnCoUkProduct2::CpProxyLinnCoUkProduct2(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Product", 2, aDevice.Device());
    Zapp::Parameter* param;

    iActionType = new Action("Type");
    param = new Zapp::ParameterString("aType");
    iActionType->AddOutputParameter(param);

    iActionModel = new Action("Model");
    param = new Zapp::ParameterString("aModel");
    iActionModel->AddOutputParameter(param);

    iActionName = new Action("Name");
    param = new Zapp::ParameterString("aName");
    iActionName->AddOutputParameter(param);

    iActionSetName = new Action("SetName");
    param = new Zapp::ParameterString("aName");
    iActionSetName->AddInputParameter(param);

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

    iActionSourceCount = new Action("SourceCount");
    param = new Zapp::ParameterUint("aSourceCount");
    iActionSourceCount->AddOutputParameter(param);

    iActionSourceIndex = new Action("SourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceIndex->AddOutputParameter(param);

    iActionSetSourceIndex = new Action("SetSourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetSourceIndex->AddInputParameter(param);

    iActionSourceType = new Action("SourceType");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceType->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceType");
    iActionSourceType->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    iService->AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2::ProductRoomPropertyChanged);
    iProductRoom = new PropertyString("ProductRoom", functor);
    iService->AddProperty(iProductRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2::ProductStandbyPropertyChanged);
    iProductStandby = new PropertyBool("ProductStandby", functor);
    iService->AddProperty(iProductStandby);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2::ProductSourceIndexPropertyChanged);
    iProductSourceIndex = new PropertyUint("ProductSourceIndex", functor);
    iService->AddProperty(iProductSourceIndex);
}

CpProxyLinnCoUkProduct2::~CpProxyLinnCoUkProduct2()
{
    delete iService;
    delete iActionType;
    delete iActionModel;
    delete iActionName;
    delete iActionSetName;
    delete iActionRoom;
    delete iActionSetRoom;
    delete iActionStandby;
    delete iActionSetStandby;
    delete iActionSourceCount;
    delete iActionSourceIndex;
    delete iActionSetSourceIndex;
    delete iActionSourceType;
}

void CpProxyLinnCoUkProduct2::SyncType(Brh& aaType)
{
    SyncTypeLinnCoUkProduct2 sync(*this, aaType);
    BeginType(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginType(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionType, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndType(IAsync& aAsync, Brh& aaType)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Type"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaType);
}

void CpProxyLinnCoUkProduct2::SyncModel(Brh& aaModel)
{
    SyncModelLinnCoUkProduct2 sync(*this, aaModel);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginModel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionModel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionModel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndModel(IAsync& aAsync, Brh& aaModel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Model"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaModel);
}

void CpProxyLinnCoUkProduct2::SyncName(Brh& aaName)
{
    SyncNameLinnCoUkProduct2 sync(*this, aaName);
    BeginName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndName(IAsync& aAsync, Brh& aaName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Name"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaName);
}

void CpProxyLinnCoUkProduct2::SyncSetName(const Brx& aaName)
{
    SyncSetNameLinnCoUkProduct2 sync(*this);
    BeginSetName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginSetName(const Brx& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndSetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2::SyncRoom(Brh& aaRoom)
{
    SyncRoomLinnCoUkProduct2 sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndRoom(IAsync& aAsync, Brh& aaRoom)
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

void CpProxyLinnCoUkProduct2::SyncSetRoom(const Brx& aaRoom)
{
    SyncSetRoomLinnCoUkProduct2 sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoom->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaRoom));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2::SyncStandby(TBool& aaStandby)
{
    SyncStandbyLinnCoUkProduct2 sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndStandby(IAsync& aAsync, TBool& aaStandby)
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

void CpProxyLinnCoUkProduct2::SyncSetStandby(TBool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct2 sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2::SyncSourceCount(TUint& aaSourceCount)
{
    SyncSourceCountLinnCoUkProduct2 sync(*this, aaSourceCount);
    BeginSourceCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginSourceCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndSourceCount(IAsync& aAsync, TUint& aaSourceCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceCount"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSourceCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct2::SyncSourceIndex(TUint& aaSourceIndex)
{
    SyncSourceIndexLinnCoUkProduct2 sync(*this, aaSourceIndex);
    BeginSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndSourceIndex(IAsync& aAsync, TUint& aaSourceIndex)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSourceIndex = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct2::SyncSetSourceIndex(TUint aaSourceIndex)
{
    SyncSetSourceIndexLinnCoUkProduct2 sync(*this);
    BeginSetSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginSetSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndSetSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2::SyncSourceType(TUint aaSourceIndex, Brh& aaSourceType)
{
    SyncSourceTypeLinnCoUkProduct2 sync(*this, aaSourceType);
    BeginSourceType(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2::BeginSourceType(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceType, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceType->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2::EndSourceType(IAsync& aAsync, Brh& aaSourceType)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceType"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSourceType);
}

void CpProxyLinnCoUkProduct2::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct2::SetPropertyProductRoomChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductRoomChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct2::SetPropertyProductStandbyChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductStandbyChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct2::SetPropertyProductSourceIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductSourceIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct2::PropertyProductName(Brhz& aProductName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductName.Set(iProductName->Value());
}

void CpProxyLinnCoUkProduct2::PropertyProductRoom(Brhz& aProductRoom) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductRoom.Set(iProductRoom->Value());
}

void CpProxyLinnCoUkProduct2::PropertyProductStandby(TBool& aProductStandby) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductStandby = iProductStandby->Value();
}

void CpProxyLinnCoUkProduct2::PropertyProductSourceIndex(TUint& aProductSourceIndex) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductSourceIndex = iProductSourceIndex->Value();
}

void CpProxyLinnCoUkProduct2::ProductNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductNameChanged != NULL) {
        iProductNameChanged();
    }
}

void CpProxyLinnCoUkProduct2::ProductRoomPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductRoomChanged != NULL) {
        iProductRoomChanged();
    }
}

void CpProxyLinnCoUkProduct2::ProductStandbyPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductStandbyChanged != NULL) {
        iProductStandbyChanged();
    }
}

void CpProxyLinnCoUkProduct2::ProductSourceIndexPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductSourceIndexChanged != NULL) {
        iProductSourceIndexChanged();
    }
}

