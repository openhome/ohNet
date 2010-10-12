#include <Std/CpLinnCoUkProduct2.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncTypeLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncTypeLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
    std::string& iaType;
};

SyncTypeLinnCoUkProduct2Cpp::SyncTypeLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaType)
    : iService(aService)
    , iaType(aaType)
{
}

void SyncTypeLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndType(aAsync, iaType);
}


class SyncModelLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncModelLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaModel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
    std::string& iaModel;
};

SyncModelLinnCoUkProduct2Cpp::SyncModelLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaModel)
    : iService(aService)
    , iaModel(aaModel)
{
}

void SyncModelLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iaModel);
}


class SyncNameLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncNameLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
    std::string& iaName;
};

SyncNameLinnCoUkProduct2Cpp::SyncNameLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaName)
    : iService(aService)
    , iaName(aaName)
{
}

void SyncNameLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndName(aAsync, iaName);
}


class SyncSetNameLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncSetNameLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
};

SyncSetNameLinnCoUkProduct2Cpp::SyncSetNameLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService)
    : iService(aService)
{
}

void SyncSetNameLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetName(aAsync);
}


class SyncRoomLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
    std::string& iaRoom;
};

SyncRoomLinnCoUkProduct2Cpp::SyncRoomLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaRoom)
    : iService(aService)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
};

SyncSetRoomLinnCoUkProduct2Cpp::SyncSetRoomLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService)
    : iService(aService)
{
}

void SyncSetRoomLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, bool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
    bool& iaStandby;
};

SyncStandbyLinnCoUkProduct2Cpp::SyncStandbyLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, bool& aaStandby)
    : iService(aService)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
};

SyncSetStandbyLinnCoUkProduct2Cpp::SyncSetStandbyLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService)
    : iService(aService)
{
}

void SyncSetStandbyLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


class SyncSourceCountLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncSourceCountLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, uint32_t& aaSourceCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
    uint32_t& iaSourceCount;
};

SyncSourceCountLinnCoUkProduct2Cpp::SyncSourceCountLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, uint32_t& aaSourceCount)
    : iService(aService)
    , iaSourceCount(aaSourceCount)
{
}

void SyncSourceCountLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceCount(aAsync, iaSourceCount);
}


class SyncSourceIndexLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncSourceIndexLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, uint32_t& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
    uint32_t& iaSourceIndex;
};

SyncSourceIndexLinnCoUkProduct2Cpp::SyncSourceIndexLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, uint32_t& aaSourceIndex)
    : iService(aService)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncSourceIndexLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetSourceIndexLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncSetSourceIndexLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
};

SyncSetSourceIndexLinnCoUkProduct2Cpp::SyncSetSourceIndexLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService)
    : iService(aService)
{
}

void SyncSetSourceIndexLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndex(aAsync);
}


class SyncSourceTypeLinnCoUkProduct2Cpp : public SyncProxyAction
{
public:
    SyncSourceTypeLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaSourceType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct2Cpp& iService;
    std::string& iaSourceType;
};

SyncSourceTypeLinnCoUkProduct2Cpp::SyncSourceTypeLinnCoUkProduct2Cpp(CpProxyLinnCoUkProduct2Cpp& aService, std::string& aaSourceType)
    : iService(aService)
    , iaSourceType(aaSourceType)
{
}

void SyncSourceTypeLinnCoUkProduct2Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceType(aAsync, iaSourceType);
}


CpProxyLinnCoUkProduct2Cpp::CpProxyLinnCoUkProduct2Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2Cpp::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    iService->AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2Cpp::ProductRoomPropertyChanged);
    iProductRoom = new PropertyString("ProductRoom", functor);
    iService->AddProperty(iProductRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2Cpp::ProductStandbyPropertyChanged);
    iProductStandby = new PropertyBool("ProductStandby", functor);
    iService->AddProperty(iProductStandby);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct2Cpp::ProductSourceIndexPropertyChanged);
    iProductSourceIndex = new PropertyUint("ProductSourceIndex", functor);
    iService->AddProperty(iProductSourceIndex);
}

CpProxyLinnCoUkProduct2Cpp::~CpProxyLinnCoUkProduct2Cpp()
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

void CpProxyLinnCoUkProduct2Cpp::SyncType(std::string& aaType)
{
    SyncTypeLinnCoUkProduct2Cpp sync(*this, aaType);
    BeginType(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginType(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionType, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndType(IAsync& aAsync, std::string& aaType)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Type"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaType.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProduct2Cpp::SyncModel(std::string& aaModel)
{
    SyncModelLinnCoUkProduct2Cpp sync(*this, aaModel);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginModel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionModel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionModel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndModel(IAsync& aAsync, std::string& aaModel)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Model"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaModel.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProduct2Cpp::SyncName(std::string& aaName)
{
    SyncNameLinnCoUkProduct2Cpp sync(*this, aaName);
    BeginName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndName(IAsync& aAsync, std::string& aaName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Name"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProduct2Cpp::SyncSetName(const std::string& aaName)
{
    SyncSetNameLinnCoUkProduct2Cpp sync(*this);
    BeginSetName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginSetName(const std::string& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetName->InputParameters();
    {
        Brn buf((const TByte*)aaName.c_str(), aaName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndSetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2Cpp::SyncRoom(std::string& aaRoom)
{
    SyncRoomLinnCoUkProduct2Cpp sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndRoom(IAsync& aAsync, std::string& aaRoom)
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

void CpProxyLinnCoUkProduct2Cpp::SyncSetRoom(const std::string& aaRoom)
{
    SyncSetRoomLinnCoUkProduct2Cpp sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginSetRoom(const std::string& aaRoom, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct2Cpp::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2Cpp::SyncStandby(bool& aaStandby)
{
    SyncStandbyLinnCoUkProduct2Cpp sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndStandby(IAsync& aAsync, bool& aaStandby)
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

void CpProxyLinnCoUkProduct2Cpp::SyncSetStandby(bool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct2Cpp sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginSetStandby(bool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2Cpp::SyncSourceCount(uint32_t& aaSourceCount)
{
    SyncSourceCountLinnCoUkProduct2Cpp sync(*this, aaSourceCount);
    BeginSourceCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginSourceCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndSourceCount(IAsync& aAsync, uint32_t& aaSourceCount)
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

void CpProxyLinnCoUkProduct2Cpp::SyncSourceIndex(uint32_t& aaSourceIndex)
{
    SyncSourceIndexLinnCoUkProduct2Cpp sync(*this, aaSourceIndex);
    BeginSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndSourceIndex(IAsync& aAsync, uint32_t& aaSourceIndex)
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

void CpProxyLinnCoUkProduct2Cpp::SyncSetSourceIndex(uint32_t aaSourceIndex)
{
    SyncSetSourceIndexLinnCoUkProduct2Cpp sync(*this);
    BeginSetSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginSetSourceIndex(uint32_t aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct2Cpp::EndSetSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct2Cpp::SyncSourceType(uint32_t aaSourceIndex, std::string& aaSourceType)
{
    SyncSourceTypeLinnCoUkProduct2Cpp sync(*this, aaSourceType);
    BeginSourceType(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct2Cpp::BeginSourceType(uint32_t aaSourceIndex, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct2Cpp::EndSourceType(IAsync& aAsync, std::string& aaSourceType)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceType"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaSourceType.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProduct2Cpp::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct2Cpp::SetPropertyProductRoomChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductRoomChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct2Cpp::SetPropertyProductStandbyChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductStandbyChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct2Cpp::SetPropertyProductSourceIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductSourceIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct2Cpp::PropertyProductName(std::string& aProductName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductName->Value();
    aProductName.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProduct2Cpp::PropertyProductRoom(std::string& aProductRoom) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductRoom->Value();
    aProductRoom.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProduct2Cpp::PropertyProductStandby(bool& aProductStandby) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductStandby = iProductStandby->Value();
}

void CpProxyLinnCoUkProduct2Cpp::PropertyProductSourceIndex(uint32_t& aProductSourceIndex) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductSourceIndex = iProductSourceIndex->Value();
}

void CpProxyLinnCoUkProduct2Cpp::ProductNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductNameChanged != NULL) {
        iProductNameChanged();
    }
}

void CpProxyLinnCoUkProduct2Cpp::ProductRoomPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductRoomChanged != NULL) {
        iProductRoomChanged();
    }
}

void CpProxyLinnCoUkProduct2Cpp::ProductStandbyPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductStandbyChanged != NULL) {
        iProductStandbyChanged();
    }
}

void CpProxyLinnCoUkProduct2Cpp::ProductSourceIndexPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductSourceIndexChanged != NULL) {
        iProductSourceIndexChanged();
    }
}

