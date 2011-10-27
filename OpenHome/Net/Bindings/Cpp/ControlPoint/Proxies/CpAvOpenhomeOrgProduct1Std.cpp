#include "CpAvOpenhomeOrgProduct1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncManufacturerAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncManufacturerAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncManufacturerAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    std::string& iName;
    std::string& iInfo;
    std::string& iUrl;
    std::string& iImageUri;
};

SyncManufacturerAvOpenhomeOrgProduct1Cpp::SyncManufacturerAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
    : iService(aProxy)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncManufacturerAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndManufacturer(aAsync, iName, iInfo, iUrl, iImageUri);
}


class SyncModelAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncModelAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncModelAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    std::string& iName;
    std::string& iInfo;
    std::string& iUrl;
    std::string& iImageUri;
};

SyncModelAvOpenhomeOrgProduct1Cpp::SyncModelAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
    : iService(aProxy)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncModelAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iName, iInfo, iUrl, iImageUri);
}


class SyncProductAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncProductAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aRoom, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncProductAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    std::string& iRoom;
    std::string& iName;
    std::string& iInfo;
    std::string& iUrl;
    std::string& iImageUri;
};

SyncProductAvOpenhomeOrgProduct1Cpp::SyncProductAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aRoom, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
    : iService(aProxy)
    , iRoom(aRoom)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncProductAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndProduct(aAsync, iRoom, iName, iInfo, iUrl, iImageUri);
}


class SyncStandbyAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncStandbyAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, bool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStandbyAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    bool& iValue;
};

SyncStandbyAvOpenhomeOrgProduct1Cpp::SyncStandbyAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, bool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncStandbyAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStandby(aAsync, iValue);
}


class SyncSetStandbyAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncSetStandbyAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetStandbyAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
};

SyncSetStandbyAvOpenhomeOrgProduct1Cpp::SyncSetStandbyAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetStandbyAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStandby(aAsync);
}


class SyncSourceCountAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncSourceCountAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSourceCountAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    uint32_t& iValue;
};

SyncSourceCountAvOpenhomeOrgProduct1Cpp::SyncSourceCountAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncSourceCountAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceCount(aAsync, iValue);
}


class SyncSourceXmlAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncSourceXmlAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSourceXmlAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    std::string& iValue;
};

SyncSourceXmlAvOpenhomeOrgProduct1Cpp::SyncSourceXmlAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncSourceXmlAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceXml(aAsync, iValue);
}


class SyncSourceIndexAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncSourceIndexAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSourceIndexAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    uint32_t& iValue;
};

SyncSourceIndexAvOpenhomeOrgProduct1Cpp::SyncSourceIndexAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncSourceIndexAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceIndex(aAsync, iValue);
}


class SyncSetSourceIndexAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncSetSourceIndexAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetSourceIndexAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
};

SyncSetSourceIndexAvOpenhomeOrgProduct1Cpp::SyncSetSourceIndexAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetSourceIndexAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndex(aAsync);
}


class SyncSetSourceIndexByNameAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncSetSourceIndexByNameAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSetSourceIndexByNameAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
};

SyncSetSourceIndexByNameAvOpenhomeOrgProduct1Cpp::SyncSetSourceIndexByNameAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy)
    : iService(aProxy)
{
}

void SyncSetSourceIndexByNameAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetSourceIndexByName(aAsync);
}


class SyncSourceAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncSourceAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aSystemName, std::string& aType, std::string& aName, bool& aVisible);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSourceAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    std::string& iSystemName;
    std::string& iType;
    std::string& iName;
    bool& iVisible;
};

SyncSourceAvOpenhomeOrgProduct1Cpp::SyncSourceAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aSystemName, std::string& aType, std::string& aName, bool& aVisible)
    : iService(aProxy)
    , iSystemName(aSystemName)
    , iType(aType)
    , iName(aName)
    , iVisible(aVisible)
{
}

void SyncSourceAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSource(aAsync, iSystemName, iType, iName, iVisible);
}


class SyncAttributesAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncAttributesAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAttributesAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    std::string& iValue;
};

SyncAttributesAvOpenhomeOrgProduct1Cpp::SyncAttributesAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncAttributesAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAttributes(aAsync, iValue);
}


class SyncSourceXmlChangeCountAvOpenhomeOrgProduct1Cpp : public SyncProxyAction
{
public:
    SyncSourceXmlChangeCountAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, uint32_t& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncSourceXmlChangeCountAvOpenhomeOrgProduct1Cpp() {}
private:
    CpProxyAvOpenhomeOrgProduct1Cpp& iService;
    uint32_t& iValue;
};

SyncSourceXmlChangeCountAvOpenhomeOrgProduct1Cpp::SyncSourceXmlChangeCountAvOpenhomeOrgProduct1Cpp(CpProxyAvOpenhomeOrgProduct1Cpp& aProxy, uint32_t& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncSourceXmlChangeCountAvOpenhomeOrgProduct1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSourceXmlChangeCount(aAsync, iValue);
}


CpProxyAvOpenhomeOrgProduct1Cpp::CpProxyAvOpenhomeOrgProduct1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("av-openhome-org", "Product", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionManufacturer = new Action("Manufacturer");
    param = new OpenHome::Net::ParameterString("Name");
    iActionManufacturer->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Info");
    iActionManufacturer->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Url");
    iActionManufacturer->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("ImageUri");
    iActionManufacturer->AddOutputParameter(param);

    iActionModel = new Action("Model");
    param = new OpenHome::Net::ParameterString("Name");
    iActionModel->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Info");
    iActionModel->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Url");
    iActionModel->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("ImageUri");
    iActionModel->AddOutputParameter(param);

    iActionProduct = new Action("Product");
    param = new OpenHome::Net::ParameterString("Room");
    iActionProduct->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Name");
    iActionProduct->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Info");
    iActionProduct->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Url");
    iActionProduct->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("ImageUri");
    iActionProduct->AddOutputParameter(param);

    iActionStandby = new Action("Standby");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionStandby->AddOutputParameter(param);

    iActionSetStandby = new Action("SetStandby");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionSetStandby->AddInputParameter(param);

    iActionSourceCount = new Action("SourceCount");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSourceCount->AddOutputParameter(param);

    iActionSourceXml = new Action("SourceXml");
    param = new OpenHome::Net::ParameterString("Value");
    iActionSourceXml->AddOutputParameter(param);

    iActionSourceIndex = new Action("SourceIndex");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSourceIndex->AddOutputParameter(param);

    iActionSetSourceIndex = new Action("SetSourceIndex");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSetSourceIndex->AddInputParameter(param);

    iActionSetSourceIndexByName = new Action("SetSourceIndexByName");
    param = new OpenHome::Net::ParameterString("Value");
    iActionSetSourceIndexByName->AddInputParameter(param);

    iActionSource = new Action("Source");
    param = new OpenHome::Net::ParameterUint("Index");
    iActionSource->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("SystemName");
    iActionSource->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Type");
    iActionSource->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Name");
    iActionSource->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBool("Visible");
    iActionSource->AddOutputParameter(param);

    iActionAttributes = new Action("Attributes");
    param = new OpenHome::Net::ParameterString("Value");
    iActionAttributes->AddOutputParameter(param);

    iActionSourceXmlChangeCount = new Action("SourceXmlChangeCount");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionSourceXmlChangeCount->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ManufacturerNamePropertyChanged);
    iManufacturerName = new PropertyString("ManufacturerName", functor);
    AddProperty(iManufacturerName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ManufacturerInfoPropertyChanged);
    iManufacturerInfo = new PropertyString("ManufacturerInfo", functor);
    AddProperty(iManufacturerInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ManufacturerUrlPropertyChanged);
    iManufacturerUrl = new PropertyString("ManufacturerUrl", functor);
    AddProperty(iManufacturerUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ManufacturerImageUriPropertyChanged);
    iManufacturerImageUri = new PropertyString("ManufacturerImageUri", functor);
    AddProperty(iManufacturerImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ModelNamePropertyChanged);
    iModelName = new PropertyString("ModelName", functor);
    AddProperty(iModelName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ModelInfoPropertyChanged);
    iModelInfo = new PropertyString("ModelInfo", functor);
    AddProperty(iModelInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ModelUrlPropertyChanged);
    iModelUrl = new PropertyString("ModelUrl", functor);
    AddProperty(iModelUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ModelImageUriPropertyChanged);
    iModelImageUri = new PropertyString("ModelImageUri", functor);
    AddProperty(iModelImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ProductRoomPropertyChanged);
    iProductRoom = new PropertyString("ProductRoom", functor);
    AddProperty(iProductRoom);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ProductInfoPropertyChanged);
    iProductInfo = new PropertyString("ProductInfo", functor);
    AddProperty(iProductInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ProductUrlPropertyChanged);
    iProductUrl = new PropertyString("ProductUrl", functor);
    AddProperty(iProductUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::ProductImageUriPropertyChanged);
    iProductImageUri = new PropertyString("ProductImageUri", functor);
    AddProperty(iProductImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::StandbyPropertyChanged);
    iStandby = new PropertyBool("Standby", functor);
    AddProperty(iStandby);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::SourceIndexPropertyChanged);
    iSourceIndex = new PropertyUint("SourceIndex", functor);
    AddProperty(iSourceIndex);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::SourceCountPropertyChanged);
    iSourceCount = new PropertyUint("SourceCount", functor);
    AddProperty(iSourceCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::SourceXmlPropertyChanged);
    iSourceXml = new PropertyString("SourceXml", functor);
    AddProperty(iSourceXml);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgProduct1Cpp::AttributesPropertyChanged);
    iAttributes = new PropertyString("Attributes", functor);
    AddProperty(iAttributes);
}

CpProxyAvOpenhomeOrgProduct1Cpp::~CpProxyAvOpenhomeOrgProduct1Cpp()
{
    DestroyService();
    delete iActionManufacturer;
    delete iActionModel;
    delete iActionProduct;
    delete iActionStandby;
    delete iActionSetStandby;
    delete iActionSourceCount;
    delete iActionSourceXml;
    delete iActionSourceIndex;
    delete iActionSetSourceIndex;
    delete iActionSetSourceIndexByName;
    delete iActionSource;
    delete iActionAttributes;
    delete iActionSourceXmlChangeCount;
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncManufacturer(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
{
    SyncManufacturerAvOpenhomeOrgProduct1Cpp sync(*this, aName, aInfo, aUrl, aImageUri);
    BeginManufacturer(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginManufacturer(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionManufacturer, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionManufacturer->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndManufacturer(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Manufacturer"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aName.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aInfo.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aUrl.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aImageUri.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncModel(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
{
    SyncModelAvOpenhomeOrgProduct1Cpp sync(*this, aName, aInfo, aUrl, aImageUri);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginModel(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionModel, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionModel->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndModel(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
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
        aName.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aInfo.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aUrl.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aImageUri.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncProduct(std::string& aRoom, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
{
    SyncProductAvOpenhomeOrgProduct1Cpp sync(*this, aRoom, aName, aInfo, aUrl, aImageUri);
    BeginProduct(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginProduct(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProduct, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProduct->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndProduct(IAsync& aAsync, std::string& aRoom, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Product"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aRoom.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aName.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aInfo.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aUrl.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aImageUri.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncStandby(bool& aValue)
{
    SyncStandbyAvOpenhomeOrgProduct1Cpp sync(*this, aValue);
    BeginStandby(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginStandby(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStandby, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStandby->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndStandby(IAsync& aAsync, bool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Standby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncSetStandby(bool aValue)
{
    SyncSetStandbyAvOpenhomeOrgProduct1Cpp sync(*this);
    BeginSetStandby(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginSetStandby(bool aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStandby, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStandby->InputParameters();
    invocation->AddInput(new ArgumentBool(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndSetStandby(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStandby"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncSourceCount(uint32_t& aValue)
{
    SyncSourceCountAvOpenhomeOrgProduct1Cpp sync(*this, aValue);
    BeginSourceCount(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginSourceCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndSourceCount(IAsync& aAsync, uint32_t& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceCount"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncSourceXml(std::string& aValue)
{
    SyncSourceXmlAvOpenhomeOrgProduct1Cpp sync(*this, aValue);
    BeginSourceXml(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginSourceXml(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceXml, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceXml->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndSourceXml(IAsync& aAsync, std::string& aValue)
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
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncSourceIndex(uint32_t& aValue)
{
    SyncSourceIndexAvOpenhomeOrgProduct1Cpp sync(*this, aValue);
    BeginSourceIndex(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginSourceIndex(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceIndex, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceIndex->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndSourceIndex(IAsync& aAsync, uint32_t& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncSetSourceIndex(uint32_t aValue)
{
    SyncSetSourceIndexAvOpenhomeOrgProduct1Cpp sync(*this);
    BeginSetSourceIndex(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginSetSourceIndex(uint32_t aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceIndex, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndex->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aValue));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndSetSourceIndex(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndex"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncSetSourceIndexByName(const std::string& aValue)
{
    SyncSetSourceIndexByNameAvOpenhomeOrgProduct1Cpp sync(*this);
    BeginSetSourceIndexByName(aValue, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginSetSourceIndexByName(const std::string& aValue, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetSourceIndexByName, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetSourceIndexByName->InputParameters();
    {
        Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndSetSourceIndexByName(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetSourceIndexByName"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncSource(uint32_t aIndex, std::string& aSystemName, std::string& aType, std::string& aName, bool& aVisible)
{
    SyncSourceAvOpenhomeOrgProduct1Cpp sync(*this, aSystemName, aType, aName, aVisible);
    BeginSource(aIndex, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginSource(uint32_t aIndex, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSource, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSource->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aIndex));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSource->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndSource(IAsync& aAsync, std::string& aSystemName, std::string& aType, std::string& aName, bool& aVisible)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Source"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aSystemName.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aType.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aName.assign((const char*)val.Ptr(), val.Bytes());
    }
    aVisible = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncAttributes(std::string& aValue)
{
    SyncAttributesAvOpenhomeOrgProduct1Cpp sync(*this, aValue);
    BeginAttributes(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginAttributes(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAttributes, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAttributes->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndAttributes(IAsync& aAsync, std::string& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Attributes"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SyncSourceXmlChangeCount(uint32_t& aValue)
{
    SyncSourceXmlChangeCountAvOpenhomeOrgProduct1Cpp sync(*this, aValue);
    BeginSourceXmlChangeCount(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::BeginSourceXmlChangeCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSourceXmlChangeCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSourceXmlChangeCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::EndSourceXmlChangeCount(IAsync& aAsync, uint32_t& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SourceXmlChangeCount"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyManufacturerNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyManufacturerInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyManufacturerUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyManufacturerImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyModelNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyModelInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyModelUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyModelImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyProductRoomChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductRoomChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyProductInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyProductUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyProductImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyStandbyChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStandbyChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertySourceIndexChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSourceIndexChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertySourceCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSourceCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertySourceXmlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSourceXmlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SetPropertyAttributesChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAttributesChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyManufacturerName(std::string& aManufacturerName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iManufacturerName->Value();
    aManufacturerName.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyManufacturerInfo(std::string& aManufacturerInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iManufacturerInfo->Value();
    aManufacturerInfo.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyManufacturerUrl(std::string& aManufacturerUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iManufacturerUrl->Value();
    aManufacturerUrl.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyManufacturerImageUri(std::string& aManufacturerImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iManufacturerImageUri->Value();
    aManufacturerImageUri.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyModelName(std::string& aModelName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iModelName->Value();
    aModelName.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyModelInfo(std::string& aModelInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iModelInfo->Value();
    aModelInfo.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyModelUrl(std::string& aModelUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iModelUrl->Value();
    aModelUrl.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyModelImageUri(std::string& aModelImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iModelImageUri->Value();
    aModelImageUri.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyProductRoom(std::string& aProductRoom) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductRoom->Value();
    aProductRoom.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyProductName(std::string& aProductName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductName->Value();
    aProductName.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyProductInfo(std::string& aProductInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductInfo->Value();
    aProductInfo.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyProductUrl(std::string& aProductUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductUrl->Value();
    aProductUrl.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyProductImageUri(std::string& aProductImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductImageUri->Value();
    aProductImageUri.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyStandby(bool& aStandby) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aStandby = iStandby->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertySourceIndex(uint32_t& aSourceIndex) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSourceIndex = iSourceIndex->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertySourceCount(uint32_t& aSourceCount) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSourceCount = iSourceCount->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertySourceXml(std::string& aSourceXml) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iSourceXml->Value();
    aSourceXml.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::PropertyAttributes(std::string& aAttributes) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iAttributes->Value();
    aAttributes.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ManufacturerNamePropertyChanged()
{
    ReportEvent(iManufacturerNameChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ManufacturerInfoPropertyChanged()
{
    ReportEvent(iManufacturerInfoChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ManufacturerUrlPropertyChanged()
{
    ReportEvent(iManufacturerUrlChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ManufacturerImageUriPropertyChanged()
{
    ReportEvent(iManufacturerImageUriChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ModelNamePropertyChanged()
{
    ReportEvent(iModelNameChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ModelInfoPropertyChanged()
{
    ReportEvent(iModelInfoChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ModelUrlPropertyChanged()
{
    ReportEvent(iModelUrlChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ModelImageUriPropertyChanged()
{
    ReportEvent(iModelImageUriChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ProductRoomPropertyChanged()
{
    ReportEvent(iProductRoomChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ProductNamePropertyChanged()
{
    ReportEvent(iProductNameChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ProductInfoPropertyChanged()
{
    ReportEvent(iProductInfoChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ProductUrlPropertyChanged()
{
    ReportEvent(iProductUrlChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::ProductImageUriPropertyChanged()
{
    ReportEvent(iProductImageUriChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::StandbyPropertyChanged()
{
    ReportEvent(iStandbyChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SourceIndexPropertyChanged()
{
    ReportEvent(iSourceIndexChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SourceCountPropertyChanged()
{
    ReportEvent(iSourceCountChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::SourceXmlPropertyChanged()
{
    ReportEvent(iSourceXmlChanged);
}

void CpProxyAvOpenhomeOrgProduct1Cpp::AttributesPropertyChanged()
{
    ReportEvent(iAttributesChanged);
}

