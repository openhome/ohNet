#include <Std/CpLinnCoUkProduct3.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncTypeLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncTypeLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    std::string& iaType;
};

SyncTypeLinnCoUkProduct3Cpp::SyncTypeLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaType)
    : iService(aService)
    , iaType(aaType)
{
}

void SyncTypeLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndType(aAsync, iaType);
}


class SyncModelLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncModelLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaModel);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    std::string& iaModel;
};

SyncModelLinnCoUkProduct3Cpp::SyncModelLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaModel)
    : iService(aService)
    , iaModel(aaModel)
{
}

void SyncModelLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iaModel);
}


class SyncNameLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    std::string& iaName;
};

SyncNameLinnCoUkProduct3Cpp::SyncNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaName)
    : iService(aService)
    , iaName(aaName)
{
}

void SyncNameLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndName(aAsync, iaName);
}


class SyncSetNameLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetNameLinnCoUkProduct3Cpp::SyncSetNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetNameLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetName(aAsync);
}


class SyncRoomLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncRoomLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaRoom);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    std::string& iaRoom;
};

SyncRoomLinnCoUkProduct3Cpp::SyncRoomLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaRoom)
    : iService(aService)
    , iaRoom(aaRoom)
{
}

void SyncRoomLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndRoom(aAsync, iaRoom);
}


class SyncSetRoomLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetRoomLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetRoomLinnCoUkProduct3Cpp::SyncSetRoomLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetRoomLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetRoom(aAsync);
}


class SyncStandbyLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncStandbyLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, bool& aaStandby);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    bool& iaStandby;
};

SyncStandbyLinnCoUkProduct3Cpp::SyncStandbyLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, bool& aaStandby)
    : iService(aService)
    , iaStandby(aaStandby)
{
}

void SyncStandbyLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iaStandby);
}


class SyncSetStandbyLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetStandbyLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetStandbyLinnCoUkProduct3Cpp::SyncSetStandbyLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetStandbyLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


class SyncSourceCountLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSourceCountLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, uint32_t& aaSourceCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    uint32_t& iaSourceCount;
};

SyncSourceCountLinnCoUkProduct3Cpp::SyncSourceCountLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, uint32_t& aaSourceCount)
    : iService(aService)
    , iaSourceCount(aaSourceCount)
{
}

void SyncSourceCountLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceCount(aAsync, iaSourceCount);
}


class SyncSourceXmlLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSourceXmlLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaSourceXml);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    std::string& iaSourceXml;
};

SyncSourceXmlLinnCoUkProduct3Cpp::SyncSourceXmlLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaSourceXml)
    : iService(aService)
    , iaSourceXml(aaSourceXml)
{
}

void SyncSourceXmlLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceXml(aAsync, iaSourceXml);
}


class SyncSourceIndexLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSourceIndexLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, uint32_t& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    uint32_t& iaSourceIndex;
};

SyncSourceIndexLinnCoUkProduct3Cpp::SyncSourceIndexLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, uint32_t& aaSourceIndex)
    : iService(aService)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncSourceIndexLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetSourceIndexLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetSourceIndexLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetSourceIndexLinnCoUkProduct3Cpp::SyncSetSourceIndexLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetSourceIndexLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndex(aAsync);
}


class SyncSetSourceIndexByNameLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetSourceIndexByNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetSourceIndexByNameLinnCoUkProduct3Cpp::SyncSetSourceIndexByNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetSourceIndexByNameLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndexByName(aAsync);
}


class SyncSetStartupSourceIndexByNameLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetStartupSourceIndexByNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetStartupSourceIndexByNameLinnCoUkProduct3Cpp::SyncSetStartupSourceIndexByNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetStartupSourceIndexByNameLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceIndexByName(aAsync);
}


class SyncStartupSourceIndexLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncStartupSourceIndexLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, uint32_t& aaSourceIndex);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    uint32_t& iaSourceIndex;
};

SyncStartupSourceIndexLinnCoUkProduct3Cpp::SyncStartupSourceIndexLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, uint32_t& aaSourceIndex)
    : iService(aService)
    , iaSourceIndex(aaSourceIndex)
{
}

void SyncStartupSourceIndexLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupSourceIndex(aAsync, iaSourceIndex);
}


class SyncSetStartupSourceIndexLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetStartupSourceIndexLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetStartupSourceIndexLinnCoUkProduct3Cpp::SyncSetStartupSourceIndexLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetStartupSourceIndexLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceIndex(aAsync);
}


class SyncStartupSourceEnabledLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncStartupSourceEnabledLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, bool& aaStartupSourceEnabled);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    bool& iaStartupSourceEnabled;
};

SyncStartupSourceEnabledLinnCoUkProduct3Cpp::SyncStartupSourceEnabledLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, bool& aaStartupSourceEnabled)
    : iService(aService)
    , iaStartupSourceEnabled(aaStartupSourceEnabled)
{
}

void SyncStartupSourceEnabledLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStartupSourceEnabled(aAsync, iaStartupSourceEnabled);
}


class SyncSetStartupSourceEnabledLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetStartupSourceEnabledLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetStartupSourceEnabledLinnCoUkProduct3Cpp::SyncSetStartupSourceEnabledLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetStartupSourceEnabledLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStartupSourceEnabled(aAsync);
}


class SyncSourceSystemNameLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSourceSystemNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaSourceName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    std::string& iaSourceName;
};

SyncSourceSystemNameLinnCoUkProduct3Cpp::SyncSourceSystemNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaSourceName)
    : iService(aService)
    , iaSourceName(aaSourceName)
{
}

void SyncSourceSystemNameLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceSystemName(aAsync, iaSourceName);
}


class SyncSourceNameLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSourceNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaSourceName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    std::string& iaSourceName;
};

SyncSourceNameLinnCoUkProduct3Cpp::SyncSourceNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaSourceName)
    : iService(aService)
    , iaSourceName(aaSourceName)
{
}

void SyncSourceNameLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceName(aAsync, iaSourceName);
}


class SyncSetSourceNameLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetSourceNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetSourceNameLinnCoUkProduct3Cpp::SyncSetSourceNameLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetSourceNameLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceName(aAsync);
}


class SyncSourceTypeLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSourceTypeLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaSourceType);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    std::string& iaSourceType;
};

SyncSourceTypeLinnCoUkProduct3Cpp::SyncSourceTypeLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, std::string& aaSourceType)
    : iService(aService)
    , iaSourceType(aaSourceType)
{
}

void SyncSourceTypeLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceType(aAsync, iaSourceType);
}


class SyncSourceVisibleLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSourceVisibleLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, bool& aaSourceVisible);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
    bool& iaSourceVisible;
};

SyncSourceVisibleLinnCoUkProduct3Cpp::SyncSourceVisibleLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService, bool& aaSourceVisible)
    : iService(aService)
    , iaSourceVisible(aaSourceVisible)
{
}

void SyncSourceVisibleLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceVisible(aAsync, iaSourceVisible);
}


class SyncSetSourceVisibleLinnCoUkProduct3Cpp : public SyncProxyAction
{
public:
    SyncSetSourceVisibleLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkProduct3Cpp& iService;
};

SyncSetSourceVisibleLinnCoUkProduct3Cpp::SyncSetSourceVisibleLinnCoUkProduct3Cpp(CpProxyLinnCoUkProduct3Cpp& aService)
    : iService(aService)
{
}

void SyncSetSourceVisibleLinnCoUkProduct3Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceVisible(aAsync);
}


CpProxyLinnCoUkProduct3Cpp::CpProxyLinnCoUkProduct3Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductTypePropertyChanged);
    iProductType = new PropertyString("ProductType", functor);
    iService->AddProperty(iProductType);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductModelPropertyChanged);
    iProductModel = new PropertyString("ProductModel", functor);
    iService->AddProperty(iProductModel);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    iService->AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductRoomPropertyChanged);
    iProductRoom = new PropertyString("ProductRoom", functor);
    iService->AddProperty(iProductRoom);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductStandbyPropertyChanged);
    iProductStandby = new PropertyBool("ProductStandby", functor);
    iService->AddProperty(iProductStandby);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductSourceIndexPropertyChanged);
    iProductSourceIndex = new PropertyUint("ProductSourceIndex", functor);
    iService->AddProperty(iProductSourceIndex);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductSourceCountPropertyChanged);
    iProductSourceCount = new PropertyUint("ProductSourceCount", functor);
    iService->AddProperty(iProductSourceCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductSourceXmlPropertyChanged);
    iProductSourceXml = new PropertyString("ProductSourceXml", functor);
    iService->AddProperty(iProductSourceXml);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::StartupSourceIndexPropertyChanged);
    iStartupSourceIndex = new PropertyUint("StartupSourceIndex", functor);
    iService->AddProperty(iStartupSourceIndex);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::StartupSourceEnabledPropertyChanged);
    iStartupSourceEnabled = new PropertyBool("StartupSourceEnabled", functor);
    iService->AddProperty(iStartupSourceEnabled);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductAnySourceNamePropertyChanged);
    iProductAnySourceName = new PropertyUint("ProductAnySourceName", functor);
    iService->AddProperty(iProductAnySourceName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductAnySourceVisiblePropertyChanged);
    iProductAnySourceVisible = new PropertyUint("ProductAnySourceVisible", functor);
    iService->AddProperty(iProductAnySourceVisible);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkProduct3Cpp::ProductAnySourceTypePropertyChanged);
    iProductAnySourceType = new PropertyUint("ProductAnySourceType", functor);
    iService->AddProperty(iProductAnySourceType);
}

CpProxyLinnCoUkProduct3Cpp::~CpProxyLinnCoUkProduct3Cpp()
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

void CpProxyLinnCoUkProduct3Cpp::SyncType(std::string& aaType)
{
    SyncTypeLinnCoUkProduct3Cpp sync(*this, aaType);
    BeginType(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginType(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionType, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionType->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndType(IAsync& aAsync, std::string& aaType)
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

void CpProxyLinnCoUkProduct3Cpp::SyncModel(std::string& aaModel)
{
    SyncModelLinnCoUkProduct3Cpp sync(*this, aaModel);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginModel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionModel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionModel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndModel(IAsync& aAsync, std::string& aaModel)
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

void CpProxyLinnCoUkProduct3Cpp::SyncName(std::string& aaName)
{
    SyncNameLinnCoUkProduct3Cpp sync(*this, aaName);
    BeginName(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginName(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionName, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionName->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndName(IAsync& aAsync, std::string& aaName)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSetName(const std::string& aaName)
{
    SyncSetNameLinnCoUkProduct3Cpp sync(*this);
    BeginSetName(aaName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetName(const std::string& aaName, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct3Cpp::EndSetName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncRoom(std::string& aaRoom)
{
    SyncRoomLinnCoUkProduct3Cpp sync(*this, aaRoom);
    BeginRoom(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginRoom(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionRoom, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionRoom->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndRoom(IAsync& aAsync, std::string& aaRoom)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSetRoom(const std::string& aaRoom)
{
    SyncSetRoomLinnCoUkProduct3Cpp sync(*this);
    BeginSetRoom(aaRoom, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetRoom(const std::string& aaRoom, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct3Cpp::EndSetRoom(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetRoom"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncStandby(bool& aaStandby)
{
    SyncStandbyLinnCoUkProduct3Cpp sync(*this, aaStandby);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndStandby(IAsync& aAsync, bool& aaStandby)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSetStandby(bool aaStandby)
{
    SyncSetStandbyLinnCoUkProduct3Cpp sync(*this);
    BeginSetStandby(aaStandby, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetStandby(bool aaStandby, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStandby));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncSourceCount(uint32_t& aaSourceCount)
{
    SyncSourceCountLinnCoUkProduct3Cpp sync(*this, aaSourceCount);
    BeginSourceCount(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSourceCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSourceCount(IAsync& aAsync, uint32_t& aaSourceCount)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSourceXml(std::string& aaSourceXml)
{
    SyncSourceXmlLinnCoUkProduct3Cpp sync(*this, aaSourceXml);
    BeginSourceXml(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSourceXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSourceXml(IAsync& aAsync, std::string& aaSourceXml)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceXml"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaSourceXml.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncSourceIndex(uint32_t& aaSourceIndex)
{
    SyncSourceIndexLinnCoUkProduct3Cpp sync(*this, aaSourceIndex);
    BeginSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSourceIndex(IAsync& aAsync, uint32_t& aaSourceIndex)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSetSourceIndex(uint32_t aaSourceIndex)
{
    SyncSetSourceIndexLinnCoUkProduct3Cpp sync(*this);
    BeginSetSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetSourceIndex(uint32_t aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSetSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncSetSourceIndexByName(const std::string& aaSourceName)
{
    SyncSetSourceIndexByNameLinnCoUkProduct3Cpp sync(*this);
    BeginSetSourceIndexByName(aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetSourceIndexByName(const std::string& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceIndexByName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndexByName->InputParameters();
    {
        Brn buf((const TByte*)aaSourceName.c_str(), aaSourceName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSetSourceIndexByName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndexByName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncSetStartupSourceIndexByName(const std::string& aaSourceName)
{
    SyncSetStartupSourceIndexByNameLinnCoUkProduct3Cpp sync(*this);
    BeginSetStartupSourceIndexByName(aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetStartupSourceIndexByName(const std::string& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupSourceIndexByName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceIndexByName->InputParameters();
    {
        Brn buf((const TByte*)aaSourceName.c_str(), aaSourceName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSetStartupSourceIndexByName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceIndexByName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncStartupSourceIndex(uint32_t& aaSourceIndex)
{
    SyncStartupSourceIndexLinnCoUkProduct3Cpp sync(*this, aaSourceIndex);
    BeginStartupSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginStartupSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartupSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndStartupSourceIndex(IAsync& aAsync, uint32_t& aaSourceIndex)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSetStartupSourceIndex(uint32_t aaSourceIndex)
{
    SyncSetStartupSourceIndexLinnCoUkProduct3Cpp sync(*this);
    BeginSetStartupSourceIndex(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetStartupSourceIndex(uint32_t aaSourceIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSetStartupSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncStartupSourceEnabled(bool& aaStartupSourceEnabled)
{
    SyncStartupSourceEnabledLinnCoUkProduct3Cpp sync(*this, aaStartupSourceEnabled);
    BeginStartupSourceEnabled(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginStartupSourceEnabled(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStartupSourceEnabled, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStartupSourceEnabled->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndStartupSourceEnabled(IAsync& aAsync, bool& aaStartupSourceEnabled)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSetStartupSourceEnabled(bool aaStartupSourceEnabled)
{
    SyncSetStartupSourceEnabledLinnCoUkProduct3Cpp sync(*this);
    BeginSetStartupSourceEnabled(aaStartupSourceEnabled, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetStartupSourceEnabled(bool aaStartupSourceEnabled, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStartupSourceEnabled, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStartupSourceEnabled->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaStartupSourceEnabled));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSetStartupSourceEnabled(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStartupSourceEnabled"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncSourceSystemName(uint32_t aaSourceIndex, std::string& aaSourceName)
{
    SyncSourceSystemNameLinnCoUkProduct3Cpp sync(*this, aaSourceName);
    BeginSourceSystemName(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSourceSystemName(uint32_t aaSourceIndex, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct3Cpp::EndSourceSystemName(IAsync& aAsync, std::string& aaSourceName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceSystemName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaSourceName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncSourceName(uint32_t aaSourceIndex, std::string& aaSourceName)
{
    SyncSourceNameLinnCoUkProduct3Cpp sync(*this, aaSourceName);
    BeginSourceName(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSourceName(uint32_t aaSourceIndex, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct3Cpp::EndSourceName(IAsync& aAsync, std::string& aaSourceName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaSourceName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncSetSourceName(uint32_t aaSourceIndex, const std::string& aaSourceName)
{
    SyncSetSourceNameLinnCoUkProduct3Cpp sync(*this);
    BeginSetSourceName(aaSourceIndex, aaSourceName, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetSourceName(uint32_t aaSourceIndex, const std::string& aaSourceName, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceName->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    {
        Brn buf((const TByte*)aaSourceName.c_str(), aaSourceName.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSetSourceName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SyncSourceType(uint32_t aaSourceIndex, std::string& aaSourceType)
{
    SyncSourceTypeLinnCoUkProduct3Cpp sync(*this, aaSourceType);
    BeginSourceType(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSourceType(uint32_t aaSourceIndex, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct3Cpp::EndSourceType(IAsync& aAsync, std::string& aaSourceType)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSourceVisible(uint32_t aaSourceIndex, bool& aaSourceVisible)
{
    SyncSourceVisibleLinnCoUkProduct3Cpp sync(*this, aaSourceVisible);
    BeginSourceVisible(aaSourceIndex, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSourceVisible(uint32_t aaSourceIndex, FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkProduct3Cpp::EndSourceVisible(IAsync& aAsync, bool& aaSourceVisible)
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

void CpProxyLinnCoUkProduct3Cpp::SyncSetSourceVisible(uint32_t aaSourceIndex, bool aaSourceVisible)
{
    SyncSetSourceVisibleLinnCoUkProduct3Cpp sync(*this);
    BeginSetSourceVisible(aaSourceIndex, aaSourceVisible, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkProduct3Cpp::BeginSetSourceVisible(uint32_t aaSourceIndex, bool aaSourceVisible, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceVisible, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceVisible->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSourceIndex));
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aaSourceVisible));
    invocation->Invoke();
}

void CpProxyLinnCoUkProduct3Cpp::EndSetSourceVisible(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceVisible"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductTypeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductTypeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductModelChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductModelChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductRoomChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductRoomChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductStandbyChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductStandbyChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductSourceIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductSourceIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductSourceCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductSourceCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductSourceXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductSourceXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyStartupSourceIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStartupSourceIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyStartupSourceEnabledChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStartupSourceEnabledChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductAnySourceNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductAnySourceNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductAnySourceVisibleChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductAnySourceVisibleChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::SetPropertyProductAnySourceTypeChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductAnySourceTypeChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductType(std::string& aProductType) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductType->Value();
    aProductType.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductModel(std::string& aProductModel) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductModel->Value();
    aProductModel.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductName(std::string& aProductName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductName->Value();
    aProductName.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductRoom(std::string& aProductRoom) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductRoom->Value();
    aProductRoom.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductStandby(bool& aProductStandby) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductStandby = iProductStandby->Value();
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductSourceIndex(uint32_t& aProductSourceIndex) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductSourceIndex = iProductSourceIndex->Value();
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductSourceCount(uint32_t& aProductSourceCount) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductSourceCount = iProductSourceCount->Value();
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductSourceXml(std::string& aProductSourceXml) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductSourceXml->Value();
    aProductSourceXml.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkProduct3Cpp::PropertyStartupSourceIndex(uint32_t& aStartupSourceIndex) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStartupSourceIndex = iStartupSourceIndex->Value();
}

void CpProxyLinnCoUkProduct3Cpp::PropertyStartupSourceEnabled(bool& aStartupSourceEnabled) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStartupSourceEnabled = iStartupSourceEnabled->Value();
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductAnySourceName(uint32_t& aProductAnySourceName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductAnySourceName = iProductAnySourceName->Value();
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductAnySourceVisible(uint32_t& aProductAnySourceVisible) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductAnySourceVisible = iProductAnySourceVisible->Value();
}

void CpProxyLinnCoUkProduct3Cpp::PropertyProductAnySourceType(uint32_t& aProductAnySourceType) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductAnySourceType = iProductAnySourceType->Value();
}

void CpProxyLinnCoUkProduct3Cpp::ProductTypePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductTypeChanged != NULL) {
        iProductTypeChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductModelPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductModelChanged != NULL) {
        iProductModelChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductNameChanged != NULL) {
        iProductNameChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductRoomPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductRoomChanged != NULL) {
        iProductRoomChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductStandbyPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductStandbyChanged != NULL) {
        iProductStandbyChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductSourceIndexPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductSourceIndexChanged != NULL) {
        iProductSourceIndexChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductSourceCountPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductSourceCountChanged != NULL) {
        iProductSourceCountChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductSourceXmlPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductSourceXmlChanged != NULL) {
        iProductSourceXmlChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::StartupSourceIndexPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStartupSourceIndexChanged != NULL) {
        iStartupSourceIndexChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::StartupSourceEnabledPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iStartupSourceEnabledChanged != NULL) {
        iStartupSourceEnabledChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductAnySourceNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductAnySourceNameChanged != NULL) {
        iProductAnySourceNameChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductAnySourceVisiblePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductAnySourceVisibleChanged != NULL) {
        iProductAnySourceVisibleChanged();
    }
}

void CpProxyLinnCoUkProduct3Cpp::ProductAnySourceTypePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iProductAnySourceTypeChanged != NULL) {
        iProductAnySourceTypeChanged();
    }
}

