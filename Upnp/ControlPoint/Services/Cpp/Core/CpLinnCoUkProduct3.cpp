#include <Core/CpLinnCoUkProduct3.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncTypeLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncTypeLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    Brh& iaType;
};

SyncTypeLinnCoUkProduct3::SyncTypeLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaType)
    : iService(aService)
    , iaType(aaType)
{
}

void SyncTypeLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndType(aAsync, iaType);
}


class SyncModelLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncModelLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaModel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    Brh& iaModel;
};

SyncModelLinnCoUkProduct3::SyncModelLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaModel)
    : iService(aService)
    , iaModel(aaModel)
{
}

void SyncModelLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iaModel);
}


class SyncNameLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    Brh& iaName;
};

SyncNameLinnCoUkProduct3::SyncNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaName)
    : iService(aService)
    , iaName(aaName)
{
}

void SyncNameLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndName(aAsync, iaName);
}


class SyncSetNameLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetNameLinnCoUkProduct3::SyncSetNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetNameLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetName(aAsync);
}


class SyncRoomLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    Brh& iaRoom;
};

SyncRoomLinnCoUkProduct3::SyncRoomLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaRoom)
    : iService(aService)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetRoomLinnCoUkProduct3::SyncSetRoomLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetRoomLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TBool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    TBool& iaStandby;
};

SyncStandbyLinnCoUkProduct3::SyncStandbyLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TBool& aaStandby)
    : iService(aService)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetStandbyLinnCoUkProduct3::SyncSetStandbyLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetStandbyLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


class SyncSourceCountLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSourceCountLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TUint& aaSourceCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    TUint& iaSourceCount;
};

SyncSourceCountLinnCoUkProduct3::SyncSourceCountLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TUint& aaSourceCount)
    : iService(aService)
    , iaSourceCount(aaSourceCount)
{
}

void SyncSourceCountLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceCount(aAsync, iaSourceCount);
}


class SyncSourceXmlLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSourceXmlLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaSourceXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    Brh& iaSourceXml;
};

SyncSourceXmlLinnCoUkProduct3::SyncSourceXmlLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaSourceXml)
    : iService(aService)
    , iaSourceXml(aaSourceXml)
{
}

void SyncSourceXmlLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceXml(aAsync, iaSourceXml);
}


class SyncSourceIndexLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TUint& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    TUint& iaSourceIndex;
};

SyncSourceIndexLinnCoUkProduct3::SyncSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TUint& aaSourceIndex)
    : iService(aService)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncSourceIndexLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetSourceIndexLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetSourceIndexLinnCoUkProduct3::SyncSetSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetSourceIndexLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndex(aAsync);
}


class SyncSetSourceIndexByNameLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetSourceIndexByNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetSourceIndexByNameLinnCoUkProduct3::SyncSetSourceIndexByNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetSourceIndexByNameLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndexByName(aAsync);
}


class SyncSetStartupSourceIndexByNameLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetStartupSourceIndexByNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetStartupSourceIndexByNameLinnCoUkProduct3::SyncSetStartupSourceIndexByNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetStartupSourceIndexByNameLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceIndexByName(aAsync);
}


class SyncStartupSourceIndexLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncStartupSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TUint& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    TUint& iaSourceIndex;
};

SyncStartupSourceIndexLinnCoUkProduct3::SyncStartupSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TUint& aaSourceIndex)
    : iService(aService)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncStartupSourceIndexLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetStartupSourceIndexLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetStartupSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetStartupSourceIndexLinnCoUkProduct3::SyncSetStartupSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetStartupSourceIndexLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceIndex(aAsync);
}


class SyncStartupSourceEnabledLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncStartupSourceEnabledLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TBool& aaStartupSourceEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    TBool& iaStartupSourceEnabled;
};

SyncStartupSourceEnabledLinnCoUkProduct3::SyncStartupSourceEnabledLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TBool& aaStartupSourceEnabled)
    : iService(aService)
    , iaStartupSourceEnabled(aaStartupSourceEnabled)
{
}

void SyncStartupSourceEnabledLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupSourceEnabled(aAsync, iaStartupSourceEnabled);
}


class SyncSetStartupSourceEnabledLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetStartupSourceEnabledLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetStartupSourceEnabledLinnCoUkProduct3::SyncSetStartupSourceEnabledLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetStartupSourceEnabledLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceEnabled(aAsync);
}


class SyncSourceSystemNameLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSourceSystemNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaSourceName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    Brh& iaSourceName;
};

SyncSourceSystemNameLinnCoUkProduct3::SyncSourceSystemNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaSourceName)
    : iService(aService)
    , iaSourceName(aaSourceName)
{
}

void SyncSourceSystemNameLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceSystemName(aAsync, iaSourceName);
}


class SyncSourceNameLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSourceNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaSourceName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    Brh& iaSourceName;
};

SyncSourceNameLinnCoUkProduct3::SyncSourceNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaSourceName)
    : iService(aService)
    , iaSourceName(aaSourceName)
{
}

void SyncSourceNameLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceName(aAsync, iaSourceName);
}


class SyncSetSourceNameLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetSourceNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetSourceNameLinnCoUkProduct3::SyncSetSourceNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetSourceNameLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceName(aAsync);
}


class SyncSourceTypeLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSourceTypeLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaSourceType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    Brh& iaSourceType;
};

SyncSourceTypeLinnCoUkProduct3::SyncSourceTypeLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, Brh& aaSourceType)
    : iService(aService)
    , iaSourceType(aaSourceType)
{
}

void SyncSourceTypeLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceType(aAsync, iaSourceType);
}


class SyncSourceVisibleLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSourceVisibleLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TBool& aaSourceVisible);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
    TBool& iaSourceVisible;
};

SyncSourceVisibleLinnCoUkProduct3::SyncSourceVisibleLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService, TBool& aaSourceVisible)
    : iService(aService)
    , iaSourceVisible(aaSourceVisible)
{
}

void SyncSourceVisibleLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceVisible(aAsync, iaSourceVisible);
}


class SyncSetSourceVisibleLinnCoUkProduct3 : public SyncProxyAction
{
public:
    SyncSetSourceVisibleLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3& iService;
};

SyncSetSourceVisibleLinnCoUkProduct3::SyncSetSourceVisibleLinnCoUkProduct3(CpProxyLinnCoUkProduct3& aService)
    : iService(aService)
{
}

void SyncSetSourceVisibleLinnCoUkProduct3::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceVisible(aAsync);
}


CpProxyLinnCoUkProduct3::CpProxyLinnCoUkProduct3(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Product", 3, aDevice.Device());
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

    iActionSourceXml = new Action("SourceXml");
    param = new Zapp::ParameterString("aSourceXml");
    iActionSourceXml->AddOutputParameter(param);

    iActionSourceIndex = new Action("SourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceIndex->AddOutputParameter(param);

    iActionSetSourceIndex = new Action("SetSourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetSourceIndex->AddInputParameter(param);

    iActionSetSourceIndexByName = new Action("SetSourceIndexByName");
    param = new Zapp::ParameterString("aSourceName");
    iActionSetSourceIndexByName->AddInputParameter(param);

    iActionSetStartupSourceIndexByName = new Action("SetStartupSourceIndexByName");
    param = new Zapp::ParameterString("aSourceName");
    iActionSetStartupSourceIndexByName->AddInputParameter(param);

    iActionStartupSourceIndex = new Action("StartupSourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionStartupSourceIndex->AddOutputParameter(param);

    iActionSetStartupSourceIndex = new Action("SetStartupSourceIndex");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetStartupSourceIndex->AddInputParameter(param);

    iActionStartupSourceEnabled = new Action("StartupSourceEnabled");
    param = new Zapp::ParameterBool("aStartupSourceEnabled");
    iActionStartupSourceEnabled->AddOutputParameter(param);

    iActionSetStartupSourceEnabled = new Action("SetStartupSourceEnabled");
    param = new Zapp::ParameterBool("aStartupSourceEnabled");
    iActionSetStartupSourceEnabled->AddInputParameter(param);

    iActionSourceSystemName = new Action("SourceSystemName");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceSystemName->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceName");
    iActionSourceSystemName->AddOutputParameter(param);

    iActionSourceName = new Action("SourceName");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceName->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceName");
    iActionSourceName->AddOutputParameter(param);

    iActionSetSourceName = new Action("SetSourceName");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetSourceName->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceName");
    iActionSetSourceName->AddInputParameter(param);

    iActionSourceType = new Action("SourceType");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceType->AddInputParameter(param);
    param = new Zapp::ParameterString("aSourceType");
    iActionSourceType->AddOutputParameter(param);

    iActionSourceVisible = new Action("SourceVisible");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSourceVisible->AddInputParameter(param);
    param = new Zapp::ParameterBool("aSourceVisible");
    iActionSourceVisible->AddOutputParameter(param);

    iActionSetSourceVisible = new Action("SetSourceVisible");
    param = new Zapp::ParameterUint("aSourceIndex");
    iActionSetSourceVisible->AddInputParameter(param);
    param = new Zapp::ParameterBool("aSourceVisible");
    iActionSetSourceVisible->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductTypePropertyChanged);
    iProductType = new PropertyString("ProductType", functor);
    iService->AddProperty(iProductType);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductModelPropertyChanged);
    iProductModel = new PropertyString("ProductModel", functor);
    iService->AddProperty(iProductModel);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    iService->AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductRoomPropertyChanged);
    iProductRoom = new PropertyString("ProductRoom", functor);
    iService->AddProperty(iProductRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductStandbyPropertyChanged);
    iProductStandby = new PropertyBool("ProductStandby", functor);
    iService->AddProperty(iProductStandby);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductSourceIndexPropertyChanged);
    iProductSourceIndex = new PropertyUint("ProductSourceIndex", functor);
    iService->AddProperty(iProductSourceIndex);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductSourceCountPropertyChanged);
    iProductSourceCount = new PropertyUint("ProductSourceCount", functor);
    iService->AddProperty(iProductSourceCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductSourceXmlPropertyChanged);
    iProductSourceXml = new PropertyString("ProductSourceXml", functor);
    iService->AddProperty(iProductSourceXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::StartupSourceIndexPropertyChanged);
    iStartupSourceIndex = new PropertyUint("StartupSourceIndex", functor);
    iService->AddProperty(iStartupSourceIndex);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::StartupSourceEnabledPropertyChanged);
    iStartupSourceEnabled = new PropertyBool("StartupSourceEnabled", functor);
    iService->AddProperty(iStartupSourceEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductAnySourceNamePropertyChanged);
    iProductAnySourceName = new PropertyUint("ProductAnySourceName", functor);
    iService->AddProperty(iProductAnySourceName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductAnySourceVisiblePropertyChanged);
    iProductAnySourceVisible = new PropertyUint("ProductAnySourceVisible", functor);
    iService->AddProperty(iProductAnySourceVisible);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3::ProductAnySourceTypePropertyChanged);
    iProductAnySourceType = new PropertyUint("ProductAnySourceType", functor);
    iService->AddProperty(iProductAnySourceType);
}

CpProxyLinnCoUkProduct3::~CpProxyLinnCoUkProduct3()
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
    delete iActionSourceXml;
    delete iActionSourceIndex;
    delete iActionSetSourceIndex;
    delete iActionSetSourceIndexByName;
    delete iActionSetStartupSourceIndexByName;
    delete iActionStartupSourceIndex;
    delete iActionSetStartupSourceIndex;
    delete iActionStartupSourceEnabled;
    delete iActionSetStartupSourceEnabled;
    delete iActionSourceSystemName;
    delete iActionSourceName;
    delete iActionSetSourceName;
    delete iActionSourceType;
    delete iActionSourceVisible;
    delete iActionSetSourceVisible;
}

void CpProxyLinnCoUkProduct3::SyncType(Brh& aaType)
{
    SyncTypeLinnCoUkProduct3 sync(*this, aaType);
    BeginType(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginType(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionType, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndType(IAsync& aAsync, Brh& aaType)
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

void CpProxyLinnCoUkProduct3::SyncModel(Brh& aaModel)
{
    SyncModelLinnCoUkProduct3 sync(*this, aaModel);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginModel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionModel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionModel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndModel(IAsync& aAsync, Brh& aaModel)
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

void CpProxyLinnCoUkProduct3::SyncName(Brh& aaName)
{
    SyncNameLinnCoUkProduct3 sync(*this, aaName);
    BeginName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndName(IAsync& aAsync, Brh& aaName)
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

void CpProxyLinnCoUkProduct3::SyncSetName(const Brx& aaName)
{
    SyncSetNameLinnCoUkProduct3 sync(*this);
    BeginSetName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetName(const Brx& aaName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaName));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncRoom(Brh& aaRoom)
{
    SyncRoomLinnCoUkProduct3 sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndRoom(IAsync& aAsync, Brh& aaRoom)
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

void CpProxyLinnCoUkProduct3::SyncSetRoom(const Brx& aaRoom)
{
    SyncSetRoomLinnCoUkProduct3 sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetRoom, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetRoom->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaRoom));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncStandby(TBool& aaStandby)
{
    SyncStandbyLinnCoUkProduct3 sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndStandby(IAsync& aAsync, TBool& aaStandby)
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

void CpProxyLinnCoUkProduct3::SyncSetStandby(TBool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct3 sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncSourceCount(TUint& aaSourceCount)
{
    SyncSourceCountLinnCoUkProduct3 sync(*this, aaSourceCount);
    BeginSourceCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSourceCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSourceCount(IAsync& aAsync, TUint& aaSourceCount)
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

void CpProxyLinnCoUkProduct3::SyncSourceXml(Brh& aaSourceXml)
{
    SyncSourceXmlLinnCoUkProduct3 sync(*this, aaSourceXml);
    BeginSourceXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSourceXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSourceXml(IAsync& aAsync, Brh& aaSourceXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSourceXml);
}

void CpProxyLinnCoUkProduct3::SyncSourceIndex(TUint& aaSourceIndex)
{
    SyncSourceIndexLinnCoUkProduct3 sync(*this, aaSourceIndex);
    BeginSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSourceIndex(IAsync& aAsync, TUint& aaSourceIndex)
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

void CpProxyLinnCoUkProduct3::SyncSetSourceIndex(TUint aaSourceIndex)
{
    SyncSetSourceIndexLinnCoUkProduct3 sync(*this);
    BeginSetSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncSetSourceIndexByName(const Brx& aaSourceName)
{
    SyncSetSourceIndexByNameLinnCoUkProduct3 sync(*this);
    BeginSetSourceIndexByName(aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetSourceIndexByName(const Brx& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceIndexByName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndexByName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaSourceName));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetSourceIndexByName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndexByName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncSetStartupSourceIndexByName(const Brx& aaSourceName)
{
    SyncSetStartupSourceIndexByNameLinnCoUkProduct3 sync(*this);
    BeginSetStartupSourceIndexByName(aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetStartupSourceIndexByName(const Brx& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupSourceIndexByName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceIndexByName->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaSourceName));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetStartupSourceIndexByName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceIndexByName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncStartupSourceIndex(TUint& aaSourceIndex)
{
    SyncStartupSourceIndexLinnCoUkProduct3 sync(*this, aaSourceIndex);
    BeginStartupSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginStartupSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartupSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndStartupSourceIndex(IAsync& aAsync, TUint& aaSourceIndex)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartupSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSourceIndex = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3::SyncSetStartupSourceIndex(TUint aaSourceIndex)
{
    SyncSetStartupSourceIndexLinnCoUkProduct3 sync(*this);
    BeginSetStartupSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetStartupSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetStartupSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncStartupSourceEnabled(TBool& aaStartupSourceEnabled)
{
    SyncStartupSourceEnabledLinnCoUkProduct3 sync(*this, aaStartupSourceEnabled);
    BeginStartupSourceEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginStartupSourceEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartupSourceEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupSourceEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndStartupSourceEnabled(IAsync& aAsync, TBool& aaStartupSourceEnabled)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StartupSourceEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaStartupSourceEnabled = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3::SyncSetStartupSourceEnabled(TBool aaStartupSourceEnabled)
{
    SyncSetStartupSourceEnabledLinnCoUkProduct3 sync(*this);
    BeginSetStartupSourceEnabled(aaStartupSourceEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetStartupSourceEnabled(TBool aaStartupSourceEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupSourceEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStartupSourceEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetStartupSourceEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncSourceSystemName(TUint aaSourceIndex, Brh& aaSourceName)
{
    SyncSourceSystemNameLinnCoUkProduct3 sync(*this, aaSourceName);
    BeginSourceSystemName(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSourceSystemName(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceSystemName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceSystemName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceSystemName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSourceSystemName(IAsync& aAsync, Brh& aaSourceName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceSystemName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSourceName);
}

void CpProxyLinnCoUkProduct3::SyncSourceName(TUint aaSourceIndex, Brh& aaSourceName)
{
    SyncSourceNameLinnCoUkProduct3 sync(*this, aaSourceName);
    BeginSourceName(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSourceName(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSourceName(IAsync& aAsync, Brh& aaSourceName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSourceName);
}

void CpProxyLinnCoUkProduct3::SyncSetSourceName(TUint aaSourceIndex, const Brx& aaSourceName)
{
    SyncSetSourceNameLinnCoUkProduct3 sync(*this);
    BeginSetSourceName(aaSourceIndex, aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetSourceName(TUint aaSourceIndex, const Brx& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaSourceName));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetSourceName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SyncSourceType(TUint aaSourceIndex, Brh& aaSourceType)
{
    SyncSourceTypeLinnCoUkProduct3 sync(*this, aaSourceType);
    BeginSourceType(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSourceType(TUint aaSourceIndex, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct3::EndSourceType(IAsync& aAsync, Brh& aaSourceType)
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

void CpProxyLinnCoUkProduct3::SyncSourceVisible(TUint aaSourceIndex, TBool& aaSourceVisible)
{
    SyncSourceVisibleLinnCoUkProduct3 sync(*this, aaSourceVisible);
    BeginSourceVisible(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSourceVisible(TUint aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceVisible, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSourceVisible->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceVisible->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSourceVisible(IAsync& aAsync, TBool& aaSourceVisible)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceVisible"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaSourceVisible = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkProduct3::SyncSetSourceVisible(TUint aaSourceIndex, TBool aaSourceVisible)
{
    SyncSetSourceVisibleLinnCoUkProduct3 sync(*this);
    BeginSetSourceVisible(aaSourceIndex, aaSourceVisible, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3::BeginSetSourceVisible(TUint aaSourceIndex, TBool aaSourceVisible, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceVisible, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceVisible->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaSourceVisible));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3::EndSetSourceVisible(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceVisible"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3::SetPropertyProductTypeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductTypeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductModelChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductModelChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductRoomChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductRoomChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductStandbyChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductStandbyChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductSourceIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductSourceIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductSourceCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductSourceCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductSourceXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductSourceXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyStartupSourceIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStartupSourceIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyStartupSourceEnabledChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStartupSourceEnabledChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductAnySourceNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductAnySourceNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductAnySourceVisibleChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductAnySourceVisibleChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::SetPropertyProductAnySourceTypeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductAnySourceTypeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3::PropertyProductType(Brhz& aProductType) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductType.Set(iProductType->Value());
}

void CpProxyLinnCoUkProduct3::PropertyProductModel(Brhz& aProductModel) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductModel.Set(iProductModel->Value());
}

void CpProxyLinnCoUkProduct3::PropertyProductName(Brhz& aProductName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductName.Set(iProductName->Value());
}

void CpProxyLinnCoUkProduct3::PropertyProductRoom(Brhz& aProductRoom) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductRoom.Set(iProductRoom->Value());
}

void CpProxyLinnCoUkProduct3::PropertyProductStandby(TBool& aProductStandby) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductStandby = iProductStandby->Value();
}

void CpProxyLinnCoUkProduct3::PropertyProductSourceIndex(TUint& aProductSourceIndex) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductSourceIndex = iProductSourceIndex->Value();
}

void CpProxyLinnCoUkProduct3::PropertyProductSourceCount(TUint& aProductSourceCount) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductSourceCount = iProductSourceCount->Value();
}

void CpProxyLinnCoUkProduct3::PropertyProductSourceXml(Brhz& aProductSourceXml) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductSourceXml.Set(iProductSourceXml->Value());
}

void CpProxyLinnCoUkProduct3::PropertyStartupSourceIndex(TUint& aStartupSourceIndex) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStartupSourceIndex = iStartupSourceIndex->Value();
}

void CpProxyLinnCoUkProduct3::PropertyStartupSourceEnabled(TBool& aStartupSourceEnabled) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStartupSourceEnabled = iStartupSourceEnabled->Value();
}

void CpProxyLinnCoUkProduct3::PropertyProductAnySourceName(TUint& aProductAnySourceName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductAnySourceName = iProductAnySourceName->Value();
}

void CpProxyLinnCoUkProduct3::PropertyProductAnySourceVisible(TUint& aProductAnySourceVisible) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductAnySourceVisible = iProductAnySourceVisible->Value();
}

void CpProxyLinnCoUkProduct3::PropertyProductAnySourceType(TUint& aProductAnySourceType) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductAnySourceType = iProductAnySourceType->Value();
}

void CpProxyLinnCoUkProduct3::ProductTypePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductTypeChanged != NULL) {
        iProductTypeChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductModelPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductModelChanged != NULL) {
        iProductModelChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductNameChanged != NULL) {
        iProductNameChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductRoomPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductRoomChanged != NULL) {
        iProductRoomChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductStandbyPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductStandbyChanged != NULL) {
        iProductStandbyChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductSourceIndexPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductSourceIndexChanged != NULL) {
        iProductSourceIndexChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductSourceCountPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductSourceCountChanged != NULL) {
        iProductSourceCountChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductSourceXmlPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductSourceXmlChanged != NULL) {
        iProductSourceXmlChanged();
    }
}

void CpProxyLinnCoUkProduct3::StartupSourceIndexPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStartupSourceIndexChanged != NULL) {
        iStartupSourceIndexChanged();
    }
}

void CpProxyLinnCoUkProduct3::StartupSourceEnabledPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStartupSourceEnabledChanged != NULL) {
        iStartupSourceEnabledChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductAnySourceNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductAnySourceNameChanged != NULL) {
        iProductAnySourceNameChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductAnySourceVisiblePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductAnySourceVisibleChanged != NULL) {
        iProductAnySourceVisibleChanged();
    }
}

void CpProxyLinnCoUkProduct3::ProductAnySourceTypePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductAnySourceTypeChanged != NULL) {
        iProductAnySourceTypeChanged();
    }
}

