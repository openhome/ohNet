#include "CpAvOpenhomeOrgMediaServer1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncManufacturerAvOpenhomeOrgMediaServer1Cpp : public SyncProxyAction
{
public:
    SyncManufacturerAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgMediaServer1Cpp& iService;
    std::string& iName;
    std::string& iInfo;
    std::string& iUrl;
    std::string& iImageUri;
};

SyncManufacturerAvOpenhomeOrgMediaServer1Cpp::SyncManufacturerAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
    : iService(aProxy)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncManufacturerAvOpenhomeOrgMediaServer1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndManufacturer(aAsync, iName, iInfo, iUrl, iImageUri);
}


class SyncModelAvOpenhomeOrgMediaServer1Cpp : public SyncProxyAction
{
public:
    SyncModelAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgMediaServer1Cpp& iService;
    std::string& iName;
    std::string& iInfo;
    std::string& iUrl;
    std::string& iImageUri;
};

SyncModelAvOpenhomeOrgMediaServer1Cpp::SyncModelAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
    : iService(aProxy)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncModelAvOpenhomeOrgMediaServer1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iName, iInfo, iUrl, iImageUri);
}


class SyncProductAvOpenhomeOrgMediaServer1Cpp : public SyncProxyAction
{
public:
    SyncProductAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgMediaServer1Cpp& iService;
    std::string& iName;
    std::string& iInfo;
    std::string& iUrl;
    std::string& iImageUri;
};

SyncProductAvOpenhomeOrgMediaServer1Cpp::SyncProductAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
    : iService(aProxy)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncProductAvOpenhomeOrgMediaServer1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndProduct(aAsync, iName, iInfo, iUrl, iImageUri);
}


class SyncAttributesAvOpenhomeOrgMediaServer1Cpp : public SyncProxyAction
{
public:
    SyncAttributesAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgMediaServer1Cpp& iService;
    std::string& iValue;
};

SyncAttributesAvOpenhomeOrgMediaServer1Cpp::SyncAttributesAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncAttributesAvOpenhomeOrgMediaServer1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAttributes(aAsync, iValue);
}


class SyncQueryAvOpenhomeOrgMediaServer1Cpp : public SyncProxyAction
{
public:
    SyncQueryAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyAvOpenhomeOrgMediaServer1Cpp& iService;
    std::string& iResult;
};

SyncQueryAvOpenhomeOrgMediaServer1Cpp::SyncQueryAvOpenhomeOrgMediaServer1Cpp(CpProxyAvOpenhomeOrgMediaServer1Cpp& aProxy, std::string& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncQueryAvOpenhomeOrgMediaServer1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndQuery(aAsync, iResult);
}


CpProxyAvOpenhomeOrgMediaServer1Cpp::CpProxyAvOpenhomeOrgMediaServer1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("av-openhome-org", "MediaServer", 1, aDevice.Device())
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
    param = new OpenHome::Net::ParameterString("Name");
    iActionProduct->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Info");
    iActionProduct->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Url");
    iActionProduct->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("ImageUri");
    iActionProduct->AddOutputParameter(param);

    iActionAttributes = new Action("Attributes");
    param = new OpenHome::Net::ParameterString("Value");
    iActionAttributes->AddOutputParameter(param);

    iActionQuery = new Action("Query");
    param = new OpenHome::Net::ParameterString("Request");
    iActionQuery->AddInputParameter(param);
    param = new OpenHome::Net::ParameterString("Result");
    iActionQuery->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ManufacturerNamePropertyChanged);
    iManufacturerName = new PropertyString("ManufacturerName", functor);
    AddProperty(iManufacturerName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ManufacturerInfoPropertyChanged);
    iManufacturerInfo = new PropertyString("ManufacturerInfo", functor);
    AddProperty(iManufacturerInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ManufacturerUrlPropertyChanged);
    iManufacturerUrl = new PropertyString("ManufacturerUrl", functor);
    AddProperty(iManufacturerUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ManufacturerImageUriPropertyChanged);
    iManufacturerImageUri = new PropertyString("ManufacturerImageUri", functor);
    AddProperty(iManufacturerImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ModelNamePropertyChanged);
    iModelName = new PropertyString("ModelName", functor);
    AddProperty(iModelName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ModelInfoPropertyChanged);
    iModelInfo = new PropertyString("ModelInfo", functor);
    AddProperty(iModelInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ModelUrlPropertyChanged);
    iModelUrl = new PropertyString("ModelUrl", functor);
    AddProperty(iModelUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ModelImageUriPropertyChanged);
    iModelImageUri = new PropertyString("ModelImageUri", functor);
    AddProperty(iModelImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ProductInfoPropertyChanged);
    iProductInfo = new PropertyString("ProductInfo", functor);
    AddProperty(iProductInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ProductUrlPropertyChanged);
    iProductUrl = new PropertyString("ProductUrl", functor);
    AddProperty(iProductUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::ProductImageUriPropertyChanged);
    iProductImageUri = new PropertyString("ProductImageUri", functor);
    AddProperty(iProductImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1Cpp::AttributesPropertyChanged);
    iAttributes = new PropertyString("Attributes", functor);
    AddProperty(iAttributes);
}

CpProxyAvOpenhomeOrgMediaServer1Cpp::~CpProxyAvOpenhomeOrgMediaServer1Cpp()
{
    DestroyService();
    delete iActionManufacturer;
    delete iActionModel;
    delete iActionProduct;
    delete iActionAttributes;
    delete iActionQuery;
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SyncManufacturer(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
{
    SyncManufacturerAvOpenhomeOrgMediaServer1Cpp sync(*this, aName, aInfo, aUrl, aImageUri);
    BeginManufacturer(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::BeginManufacturer(FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgMediaServer1Cpp::EndManufacturer(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
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

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SyncModel(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
{
    SyncModelAvOpenhomeOrgMediaServer1Cpp sync(*this, aName, aInfo, aUrl, aImageUri);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::BeginModel(FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgMediaServer1Cpp::EndModel(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
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

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SyncProduct(std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
{
    SyncProductAvOpenhomeOrgMediaServer1Cpp sync(*this, aName, aInfo, aUrl, aImageUri);
    BeginProduct(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::BeginProduct(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProduct, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProduct->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::EndProduct(IAsync& aAsync, std::string& aName, std::string& aInfo, std::string& aUrl, std::string& aImageUri)
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

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SyncAttributes(std::string& aValue)
{
    SyncAttributesAvOpenhomeOrgMediaServer1Cpp sync(*this, aValue);
    BeginAttributes(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::BeginAttributes(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAttributes, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAttributes->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::EndAttributes(IAsync& aAsync, std::string& aValue)
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

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SyncQuery(const std::string& aRequest, std::string& aResult)
{
    SyncQueryAvOpenhomeOrgMediaServer1Cpp sync(*this, aResult);
    BeginQuery(aRequest, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::BeginQuery(const std::string& aRequest, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionQuery, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionQuery->InputParameters();
    {
        Brn buf((const TByte*)aRequest.c_str(), (TUint)aRequest.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionQuery->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::EndQuery(IAsync& aAsync, std::string& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Query"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aResult.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyManufacturerImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyModelImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyProductImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::SetPropertyAttributesChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAttributesChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyManufacturerName(std::string& aManufacturerName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iManufacturerName->Value();
    aManufacturerName.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyManufacturerInfo(std::string& aManufacturerInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iManufacturerInfo->Value();
    aManufacturerInfo.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyManufacturerUrl(std::string& aManufacturerUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iManufacturerUrl->Value();
    aManufacturerUrl.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyManufacturerImageUri(std::string& aManufacturerImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iManufacturerImageUri->Value();
    aManufacturerImageUri.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyModelName(std::string& aModelName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iModelName->Value();
    aModelName.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyModelInfo(std::string& aModelInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iModelInfo->Value();
    aModelInfo.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyModelUrl(std::string& aModelUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iModelUrl->Value();
    aModelUrl.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyModelImageUri(std::string& aModelImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iModelImageUri->Value();
    aModelImageUri.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyProductName(std::string& aProductName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductName->Value();
    aProductName.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyProductInfo(std::string& aProductInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductInfo->Value();
    aProductInfo.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyProductUrl(std::string& aProductUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductUrl->Value();
    aProductUrl.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyProductImageUri(std::string& aProductImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iProductImageUri->Value();
    aProductImageUri.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::PropertyAttributes(std::string& aAttributes) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iAttributes->Value();
    aAttributes.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ManufacturerNamePropertyChanged()
{
    ReportEvent(iManufacturerNameChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ManufacturerInfoPropertyChanged()
{
    ReportEvent(iManufacturerInfoChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ManufacturerUrlPropertyChanged()
{
    ReportEvent(iManufacturerUrlChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ManufacturerImageUriPropertyChanged()
{
    ReportEvent(iManufacturerImageUriChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ModelNamePropertyChanged()
{
    ReportEvent(iModelNameChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ModelInfoPropertyChanged()
{
    ReportEvent(iModelInfoChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ModelUrlPropertyChanged()
{
    ReportEvent(iModelUrlChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ModelImageUriPropertyChanged()
{
    ReportEvent(iModelImageUriChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ProductNamePropertyChanged()
{
    ReportEvent(iProductNameChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ProductInfoPropertyChanged()
{
    ReportEvent(iProductInfoChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ProductUrlPropertyChanged()
{
    ReportEvent(iProductUrlChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::ProductImageUriPropertyChanged()
{
    ReportEvent(iProductImageUriChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1Cpp::AttributesPropertyChanged()
{
    ReportEvent(iAttributesChanged);
}

