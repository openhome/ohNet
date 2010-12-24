#include "CpLinnCoUkProduct2.h"
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

class CpProxyLinnCoUkProduct2C : public CpProxyC
{
public:
    CpProxyLinnCoUkProduct2C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkProduct2C();
    //CpProxyLinnCoUkProduct2* Proxy() { return static_cast<CpProxyLinnCoUkProduct2*>(iProxy); }

    void SyncType(Brh& aaType);
    void BeginType(FunctorAsync& aFunctor);
    void EndType(IAsync& aAsync, Brh& aaType);

    void SyncModel(Brh& aaModel);
    void BeginModel(FunctorAsync& aFunctor);
    void EndModel(IAsync& aAsync, Brh& aaModel);

    void SyncName(Brh& aaName);
    void BeginName(FunctorAsync& aFunctor);
    void EndName(IAsync& aAsync, Brh& aaName);

    void SyncSetName(const Brx& aaName);
    void BeginSetName(const Brx& aaName, FunctorAsync& aFunctor);
    void EndSetName(IAsync& aAsync);

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

    void SyncSourceCount(TUint& aaSourceCount);
    void BeginSourceCount(FunctorAsync& aFunctor);
    void EndSourceCount(IAsync& aAsync, TUint& aaSourceCount);

    void SyncSourceIndex(TUint& aaSourceIndex);
    void BeginSourceIndex(FunctorAsync& aFunctor);
    void EndSourceIndex(IAsync& aAsync, TUint& aaSourceIndex);

    void SyncSetSourceIndex(TUint aaSourceIndex);
    void BeginSetSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor);
    void EndSetSourceIndex(IAsync& aAsync);

    void SyncSourceType(TUint aaSourceIndex, Brh& aaSourceType);
    void BeginSourceType(TUint aaSourceIndex, FunctorAsync& aFunctor);
    void EndSourceType(IAsync& aAsync, Brh& aaSourceType);

    void SetPropertyProductNameChanged(Functor& aFunctor);
    void SetPropertyProductRoomChanged(Functor& aFunctor);
    void SetPropertyProductStandbyChanged(Functor& aFunctor);
    void SetPropertyProductSourceIndexChanged(Functor& aFunctor);

    void PropertyProductName(Brhz& aProductName) const;
    void PropertyProductRoom(Brhz& aProductRoom) const;
    void PropertyProductStandby(TBool& aProductStandby) const;
    void PropertyProductSourceIndex(TUint& aProductSourceIndex) const;
private:
    void ProductNamePropertyChanged();
    void ProductRoomPropertyChanged();
    void ProductStandbyPropertyChanged();
    void ProductSourceIndexPropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionType;
    Action* iActionModel;
    Action* iActionName;
    Action* iActionSetName;
    Action* iActionRoom;
    Action* iActionSetRoom;
    Action* iActionStandby;
    Action* iActionSetStandby;
    Action* iActionSourceCount;
    Action* iActionSourceIndex;
    Action* iActionSetSourceIndex;
    Action* iActionSourceType;
    PropertyString* iProductName;
    PropertyString* iProductRoom;
    PropertyBool* iProductStandby;
    PropertyUint* iProductSourceIndex;
    Functor iProductNameChanged;
    Functor iProductRoomChanged;
    Functor iProductStandbyChanged;
    Functor iProductSourceIndexChanged;
};


class SyncTypeLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncTypeLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
    Brh& iaType;
};

SyncTypeLinnCoUkProduct2C::SyncTypeLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaType)
    : iService(aProxy)
    , iaType(aaType)
{
}

void SyncTypeLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndType(aAsync, iaType);
}


class SyncModelLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncModelLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaModel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
    Brh& iaModel;
};

SyncModelLinnCoUkProduct2C::SyncModelLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaModel)
    : iService(aProxy)
    , iaModel(aaModel)
{
}

void SyncModelLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iaModel);
}


class SyncNameLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncNameLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
    Brh& iaName;
};

SyncNameLinnCoUkProduct2C::SyncNameLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaName)
    : iService(aProxy)
    , iaName(aaName)
{
}

void SyncNameLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndName(aAsync, iaName);
}


class SyncSetNameLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncSetNameLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
};

SyncSetNameLinnCoUkProduct2C::SyncSetNameLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetNameLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetName(aAsync);
}


class SyncRoomLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
    Brh& iaRoom;
};

SyncRoomLinnCoUkProduct2C::SyncRoomLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaRoom)
    : iService(aProxy)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
};

SyncSetRoomLinnCoUkProduct2C::SyncSetRoomLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetRoomLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, TBool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
    TBool& iaStandby;
};

SyncStandbyLinnCoUkProduct2C::SyncStandbyLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, TBool& aaStandby)
    : iService(aProxy)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
};

SyncSetStandbyLinnCoUkProduct2C::SyncSetStandbyLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStandbyLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


class SyncSourceCountLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncSourceCountLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, TUint& aaSourceCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
    TUint& iaSourceCount;
};

SyncSourceCountLinnCoUkProduct2C::SyncSourceCountLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, TUint& aaSourceCount)
    : iService(aProxy)
    , iaSourceCount(aaSourceCount)
{
}

void SyncSourceCountLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceCount(aAsync, iaSourceCount);
}


class SyncSourceIndexLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncSourceIndexLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, TUint& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
    TUint& iaSourceIndex;
};

SyncSourceIndexLinnCoUkProduct2C::SyncSourceIndexLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, TUint& aaSourceIndex)
    : iService(aProxy)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncSourceIndexLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetSourceIndexLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncSetSourceIndexLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
};

SyncSetSourceIndexLinnCoUkProduct2C::SyncSetSourceIndexLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy)
    : iService(aProxy)
{
}

void SyncSetSourceIndexLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndex(aAsync);
}


class SyncSourceTypeLinnCoUkProduct2C : public SyncProxyAction
{
public:
    SyncSourceTypeLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaSourceType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2C& iService;
    Brh& iaSourceType;
};

SyncSourceTypeLinnCoUkProduct2C::SyncSourceTypeLinnCoUkProduct2C(CpProxyLinnCoUkProduct2C& aProxy, Brh& aaSourceType)
    : iService(aProxy)
    , iaSourceType(aaSourceType)
{
}

void SyncSourceTypeLinnCoUkProduct2C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceType(aAsync, iaSourceType);
}

CpProxyLinnCoUkProduct2C::CpProxyLinnCoUkProduct2C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Product", 2, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2C::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2C::ProductRoomPropertyChanged);
    iProductRoom = new PropertyString("ProductRoom", functor);
    AddProperty(iProductRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2C::ProductStandbyPropertyChanged);
    iProductStandby = new PropertyBool("ProductStandby", functor);
    AddProperty(iProductStandby);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2C::ProductSourceIndexPropertyChanged);
    iProductSourceIndex = new PropertyUint("ProductSourceIndex", functor);
    AddProperty(iProductSourceIndex);
}

CpProxyLinnCoUkProduct2C::~CpProxyLinnCoUkProduct2C()
{
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

void CpProxyLinnCoUkProduct2C::SyncType(Brh& aaType)
{
    SyncTypeLinnCoUkProduct2C sync(*this, aaType);
    BeginType(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginType(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionType, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndType(IAsync& aAsync, Brh& aaType)
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

void CpProxyLinnCoUkProduct2C::SyncModel(Brh& aaModel)
{
    SyncModelLinnCoUkProduct2C sync(*this, aaModel);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginModel(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionModel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionModel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndModel(IAsync& aAsync, Brh& aaModel)
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

void CpProxyLinnCoUkProduct2C::SyncName(Brh& aaName)
{
    SyncNameLinnCoUkProduct2C sync(*this, aaName);
    BeginName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginName(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndName(IAsync& aAsync, Brh& aaName)
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

void CpProxyLinnCoUkProduct2C::SyncSetName(const Brx& aaName)
{
    SyncSetNameLinnCoUkProduct2C sync(*this);
    BeginSetName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginSetName(const Brx& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndSetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2C::SyncRoom(Brh& aaRoom)
{
    SyncRoomLinnCoUkProduct2C sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndRoom(IAsync& aAsync, Brh& aaRoom)
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

void CpProxyLinnCoUkProduct2C::SyncSetRoom(const Brx& aaRoom)
{
    SyncSetRoomLinnCoUkProduct2C sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoom->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaRoom));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2C::SyncStandby(TBool& aaStandby)
{
    SyncStandbyLinnCoUkProduct2C sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndStandby(IAsync& aAsync, TBool& aaStandby)
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

void CpProxyLinnCoUkProduct2C::SyncSetStandby(TBool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct2C sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2C::SyncSourceCount(TUint& aaSourceCount)
{
    SyncSourceCountLinnCoUkProduct2C sync(*this, aaSourceCount);
    BeginSourceCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginSourceCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndSourceCount(IAsync& aAsync, TUint& aaSourceCount)
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

void CpProxyLinnCoUkProduct2C::SyncSourceIndex(TUint& aaSourceIndex)
{
    SyncSourceIndexLinnCoUkProduct2C sync(*this, aaSourceIndex);
    BeginSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndSourceIndex(IAsync& aAsync, TUint& aaSourceIndex)
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

void CpProxyLinnCoUkProduct2C::SyncSetSourceIndex(TUint aaSourceIndex)
{
    SyncSetSourceIndexLinnCoUkProduct2C sync(*this);
    BeginSetSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginSetSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndSetSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2C::SyncSourceType(TUint aaSourceIndex, Brh& aaSourceType)
{
    SyncSourceTypeLinnCoUkProduct2C sync(*this, aaSourceType);
    BeginSourceType(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2C::BeginSourceType(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSourceType, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceType->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkProduct2C::EndSourceType(IAsync& aAsync, Brh& aaSourceType)
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

void CpProxyLinnCoUkProduct2C::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct2C::SetPropertyProductRoomChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductRoomChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct2C::SetPropertyProductStandbyChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductStandbyChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct2C::SetPropertyProductSourceIndexChanged(Functor& aFunctor)
{
    iLock.Wait();
    iProductSourceIndexChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkProduct2C::PropertyProductName(Brhz& aProductName) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aProductName.Set(iProductName->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkProduct2C::PropertyProductRoom(Brhz& aProductRoom) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aProductRoom.Set(iProductRoom->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkProduct2C::PropertyProductStandby(TBool& aProductStandby) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aProductStandby = iProductStandby->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkProduct2C::PropertyProductSourceIndex(TUint& aProductSourceIndex) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aProductSourceIndex = iProductSourceIndex->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkProduct2C::ProductNamePropertyChanged()
{
    ReportEvent(iProductNameChanged);
}

void CpProxyLinnCoUkProduct2C::ProductRoomPropertyChanged()
{
    ReportEvent(iProductRoomChanged);
}

void CpProxyLinnCoUkProduct2C::ProductStandbyPropertyChanged()
{
    ReportEvent(iProductStandbyChanged);
}

void CpProxyLinnCoUkProduct2C::ProductSourceIndexPropertyChanged()
{
    ReportEvent(iProductSourceIndexChanged);
}


THandle CpProxyLinnCoUkProduct2Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkProduct2C(aDevice);
}

void CpProxyLinnCoUkProduct2Destroy(THandle aHandle)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkProduct2SyncType(THandle aHandle, char** aaType)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaType;
    proxyC->SyncType(buf_aaType);
    *aaType = buf_aaType.Extract();
}

void CpProxyLinnCoUkProduct2BeginType(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginType(functor);
}

int32_t CpProxyLinnCoUkProduct2EndType(THandle aHandle, ZappHandleAsync aAsync, char** aaType)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaType;
    *aaType = NULL;
    try {
        proxyC->EndType(*async, buf_aaType);
        *aaType = buf_aaType.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncModel(THandle aHandle, char** aaModel)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaModel;
    proxyC->SyncModel(buf_aaModel);
    *aaModel = buf_aaModel.Extract();
}

void CpProxyLinnCoUkProduct2BeginModel(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginModel(functor);
}

int32_t CpProxyLinnCoUkProduct2EndModel(THandle aHandle, ZappHandleAsync aAsync, char** aaModel)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaModel;
    *aaModel = NULL;
    try {
        proxyC->EndModel(*async, buf_aaModel);
        *aaModel = buf_aaModel.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncName(THandle aHandle, char** aaName)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName;
    proxyC->SyncName(buf_aaName);
    *aaName = buf_aaName.Extract();
}

void CpProxyLinnCoUkProduct2BeginName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginName(functor);
}

int32_t CpProxyLinnCoUkProduct2EndName(THandle aHandle, ZappHandleAsync aAsync, char** aaName)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaName;
    *aaName = NULL;
    try {
        proxyC->EndName(*async, buf_aaName);
        *aaName = buf_aaName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSetName(THandle aHandle, const char* aaName)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    proxyC->SyncSetName(buf_aaName);
}

void CpProxyLinnCoUkProduct2BeginSetName(THandle aHandle, const char* aaName, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaName(aaName);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetName(buf_aaName, functor);
}

int32_t CpProxyLinnCoUkProduct2EndSetName(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetName(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncRoom(THandle aHandle, char** aaRoom)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom;
    proxyC->SyncRoom(buf_aaRoom);
    *aaRoom = buf_aaRoom.Extract();
}

void CpProxyLinnCoUkProduct2BeginRoom(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginRoom(functor);
}

int32_t CpProxyLinnCoUkProduct2EndRoom(THandle aHandle, ZappHandleAsync aAsync, char** aaRoom)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
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

void CpProxyLinnCoUkProduct2SyncSetRoom(THandle aHandle, const char* aaRoom)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    proxyC->SyncSetRoom(buf_aaRoom);
}

void CpProxyLinnCoUkProduct2BeginSetRoom(THandle aHandle, const char* aaRoom, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaRoom(aaRoom);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetRoom(buf_aaRoom, functor);
}

int32_t CpProxyLinnCoUkProduct2EndSetRoom(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
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

void CpProxyLinnCoUkProduct2SyncStandby(THandle aHandle, uint32_t* aaStandby)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaStandby = 0;
    proxyC->SyncStandby(*(TBool*)aaStandby);
}

void CpProxyLinnCoUkProduct2BeginStandby(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStandby(functor);
}

int32_t CpProxyLinnCoUkProduct2EndStandby(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStandby)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
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

void CpProxyLinnCoUkProduct2SyncSetStandby(THandle aHandle, uint32_t aaStandby)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStandby((aaStandby==0? false : true));
}

void CpProxyLinnCoUkProduct2BeginSetStandby(THandle aHandle, uint32_t aaStandby, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStandby((aaStandby==0? false : true), functor);
}

int32_t CpProxyLinnCoUkProduct2EndSetStandby(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
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

void CpProxyLinnCoUkProduct2SyncSourceCount(THandle aHandle, uint32_t* aaSourceCount)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSourceCount(*aaSourceCount);
}

void CpProxyLinnCoUkProduct2BeginSourceCount(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceCount(functor);
}

int32_t CpProxyLinnCoUkProduct2EndSourceCount(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceCount)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSourceCount(*async, *aaSourceCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSourceIndex(THandle aHandle, uint32_t* aaSourceIndex)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSourceIndex(*aaSourceIndex);
}

void CpProxyLinnCoUkProduct2BeginSourceIndex(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceIndex(functor);
}

int32_t CpProxyLinnCoUkProduct2EndSourceIndex(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaSourceIndex)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSourceIndex(*async, *aaSourceIndex);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetSourceIndex(aaSourceIndex);
}

void CpProxyLinnCoUkProduct2BeginSetSourceIndex(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetSourceIndex(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct2EndSetSourceIndex(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetSourceIndex(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SyncSourceType(THandle aHandle, uint32_t aaSourceIndex, char** aaSourceType)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSourceType;
    proxyC->SyncSourceType(aaSourceIndex, buf_aaSourceType);
    *aaSourceType = buf_aaSourceType.Extract();
}

void CpProxyLinnCoUkProduct2BeginSourceType(THandle aHandle, uint32_t aaSourceIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSourceType(aaSourceIndex, functor);
}

int32_t CpProxyLinnCoUkProduct2EndSourceType(THandle aHandle, ZappHandleAsync aAsync, char** aaSourceType)
{
    int32_t err = 0;
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSourceType;
    *aaSourceType = NULL;
    try {
        proxyC->EndSourceType(*async, buf_aaSourceType);
        *aaSourceType = buf_aaSourceType.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkProduct2SetPropertyProductNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductNameChanged(functor);
}

void CpProxyLinnCoUkProduct2SetPropertyProductRoomChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductRoomChanged(functor);
}

void CpProxyLinnCoUkProduct2SetPropertyProductStandbyChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductStandbyChanged(functor);
}

void CpProxyLinnCoUkProduct2SetPropertyProductSourceIndexChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyProductSourceIndexChanged(functor);
}

void CpProxyLinnCoUkProduct2PropertyProductName(THandle aHandle, char** aProductName)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductName;
    proxyC->PropertyProductName(buf_aProductName);
    *aProductName = buf_aProductName.Transfer();
}

void CpProxyLinnCoUkProduct2PropertyProductRoom(THandle aHandle, char** aProductRoom)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aProductRoom;
    proxyC->PropertyProductRoom(buf_aProductRoom);
    *aProductRoom = buf_aProductRoom.Transfer();
}

void CpProxyLinnCoUkProduct2PropertyProductStandby(THandle aHandle, uint32_t* aProductStandby)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aProductStandby = false;
    proxyC->PropertyProductStandby(*(TBool*)aProductStandby);
}

void CpProxyLinnCoUkProduct2PropertyProductSourceIndex(THandle aHandle, uint32_t* aProductSourceIndex)
{
    CpProxyLinnCoUkProduct2C* proxyC = reinterpret_cast<CpProxyLinnCoUkProduct2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyProductSourceIndex(*aProductSourceIndex);
}

