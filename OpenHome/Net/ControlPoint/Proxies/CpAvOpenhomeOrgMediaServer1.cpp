#include "CpAvOpenhomeOrgMediaServer1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncManufacturerAvOpenhomeOrgMediaServer1 : public SyncProxyAction
{
public:
    SyncManufacturerAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncManufacturerAvOpenhomeOrgMediaServer1() {}
private:
    CpProxyAvOpenhomeOrgMediaServer1& iService;
    Brh& iName;
    Brh& iInfo;
    Brh& iUrl;
    Brh& iImageUri;
};

SyncManufacturerAvOpenhomeOrgMediaServer1::SyncManufacturerAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
    : iService(aProxy)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncManufacturerAvOpenhomeOrgMediaServer1::CompleteRequest(IAsync& aAsync)
{
    iService.EndManufacturer(aAsync, iName, iInfo, iUrl, iImageUri);
}


class SyncModelAvOpenhomeOrgMediaServer1 : public SyncProxyAction
{
public:
    SyncModelAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncModelAvOpenhomeOrgMediaServer1() {}
private:
    CpProxyAvOpenhomeOrgMediaServer1& iService;
    Brh& iName;
    Brh& iInfo;
    Brh& iUrl;
    Brh& iImageUri;
};

SyncModelAvOpenhomeOrgMediaServer1::SyncModelAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
    : iService(aProxy)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncModelAvOpenhomeOrgMediaServer1::CompleteRequest(IAsync& aAsync)
{
    iService.EndModel(aAsync, iName, iInfo, iUrl, iImageUri);
}


class SyncProductAvOpenhomeOrgMediaServer1 : public SyncProxyAction
{
public:
    SyncProductAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncProductAvOpenhomeOrgMediaServer1() {}
private:
    CpProxyAvOpenhomeOrgMediaServer1& iService;
    Brh& iName;
    Brh& iInfo;
    Brh& iUrl;
    Brh& iImageUri;
};

SyncProductAvOpenhomeOrgMediaServer1::SyncProductAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
    : iService(aProxy)
    , iName(aName)
    , iInfo(aInfo)
    , iUrl(aUrl)
    , iImageUri(aImageUri)
{
}

void SyncProductAvOpenhomeOrgMediaServer1::CompleteRequest(IAsync& aAsync)
{
    iService.EndProduct(aAsync, iName, iInfo, iUrl, iImageUri);
}


class SyncAttributesAvOpenhomeOrgMediaServer1 : public SyncProxyAction
{
public:
    SyncAttributesAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAttributesAvOpenhomeOrgMediaServer1() {}
private:
    CpProxyAvOpenhomeOrgMediaServer1& iService;
    Brh& iValue;
};

SyncAttributesAvOpenhomeOrgMediaServer1::SyncAttributesAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncAttributesAvOpenhomeOrgMediaServer1::CompleteRequest(IAsync& aAsync)
{
    iService.EndAttributes(aAsync, iValue);
}


class SyncQueryAvOpenhomeOrgMediaServer1 : public SyncProxyAction
{
public:
    SyncQueryAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aResult);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncQueryAvOpenhomeOrgMediaServer1() {}
private:
    CpProxyAvOpenhomeOrgMediaServer1& iService;
    Brh& iResult;
};

SyncQueryAvOpenhomeOrgMediaServer1::SyncQueryAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, Brh& aResult)
    : iService(aProxy)
    , iResult(aResult)
{
}

void SyncQueryAvOpenhomeOrgMediaServer1::CompleteRequest(IAsync& aAsync)
{
    iService.EndQuery(aAsync, iResult);
}


CpProxyAvOpenhomeOrgMediaServer1::CpProxyAvOpenhomeOrgMediaServer1(CpDevice& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ManufacturerNamePropertyChanged);
    iManufacturerName = new PropertyString("ManufacturerName", functor);
    AddProperty(iManufacturerName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ManufacturerInfoPropertyChanged);
    iManufacturerInfo = new PropertyString("ManufacturerInfo", functor);
    AddProperty(iManufacturerInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ManufacturerUrlPropertyChanged);
    iManufacturerUrl = new PropertyString("ManufacturerUrl", functor);
    AddProperty(iManufacturerUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ManufacturerImageUriPropertyChanged);
    iManufacturerImageUri = new PropertyString("ManufacturerImageUri", functor);
    AddProperty(iManufacturerImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ModelNamePropertyChanged);
    iModelName = new PropertyString("ModelName", functor);
    AddProperty(iModelName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ModelInfoPropertyChanged);
    iModelInfo = new PropertyString("ModelInfo", functor);
    AddProperty(iModelInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ModelUrlPropertyChanged);
    iModelUrl = new PropertyString("ModelUrl", functor);
    AddProperty(iModelUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ModelImageUriPropertyChanged);
    iModelImageUri = new PropertyString("ModelImageUri", functor);
    AddProperty(iModelImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ProductNamePropertyChanged);
    iProductName = new PropertyString("ProductName", functor);
    AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ProductInfoPropertyChanged);
    iProductInfo = new PropertyString("ProductInfo", functor);
    AddProperty(iProductInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ProductUrlPropertyChanged);
    iProductUrl = new PropertyString("ProductUrl", functor);
    AddProperty(iProductUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ProductImageUriPropertyChanged);
    iProductImageUri = new PropertyString("ProductImageUri", functor);
    AddProperty(iProductImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::AttributesPropertyChanged);
    iAttributes = new PropertyString("Attributes", functor);
    AddProperty(iAttributes);
}

CpProxyAvOpenhomeOrgMediaServer1::~CpProxyAvOpenhomeOrgMediaServer1()
{
    DestroyService();
    delete iActionManufacturer;
    delete iActionModel;
    delete iActionProduct;
    delete iActionAttributes;
    delete iActionQuery;
}

void CpProxyAvOpenhomeOrgMediaServer1::SyncManufacturer(Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
{
    SyncManufacturerAvOpenhomeOrgMediaServer1 sync(*this, aName, aInfo, aUrl, aImageUri);
    BeginManufacturer(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1::BeginManufacturer(FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgMediaServer1::EndManufacturer(IAsync& aAsync, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Manufacturer"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aName);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aInfo);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUrl);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aImageUri);
}

void CpProxyAvOpenhomeOrgMediaServer1::SyncModel(Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
{
    SyncModelAvOpenhomeOrgMediaServer1 sync(*this, aName, aInfo, aUrl, aImageUri);
    BeginModel(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1::BeginModel(FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgMediaServer1::EndModel(IAsync& aAsync, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Model"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aName);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aInfo);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUrl);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aImageUri);
}

void CpProxyAvOpenhomeOrgMediaServer1::SyncProduct(Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
{
    SyncProductAvOpenhomeOrgMediaServer1 sync(*this, aName, aInfo, aUrl, aImageUri);
    BeginProduct(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1::BeginProduct(FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgMediaServer1::EndProduct(IAsync& aAsync, Brh& aName, Brh& aInfo, Brh& aUrl, Brh& aImageUri)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Product"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aName);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aInfo);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUrl);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aImageUri);
}

void CpProxyAvOpenhomeOrgMediaServer1::SyncAttributes(Brh& aValue)
{
    SyncAttributesAvOpenhomeOrgMediaServer1 sync(*this, aValue);
    BeginAttributes(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1::BeginAttributes(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAttributes, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAttributes->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgMediaServer1::EndAttributes(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Attributes"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgMediaServer1::SyncQuery(const Brx& aRequest, Brh& aResult)
{
    SyncQueryAvOpenhomeOrgMediaServer1 sync(*this, aResult);
    BeginQuery(aRequest, sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1::BeginQuery(const Brx& aRequest, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionQuery, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionQuery->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aRequest));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionQuery->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgMediaServer1::EndQuery(IAsync& aAsync, Brh& aResult)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Query"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aResult);
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyManufacturerNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyManufacturerInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyManufacturerUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyManufacturerImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iManufacturerImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyModelNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyModelInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyModelUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyModelImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iModelImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyProductNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyProductInfoChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductInfoChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyProductUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyProductImageUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iProductImageUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyAttributesChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAttributesChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyManufacturerName(Brhz& aManufacturerName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aManufacturerName.Set(iManufacturerName->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyManufacturerInfo(Brhz& aManufacturerInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aManufacturerInfo.Set(iManufacturerInfo->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyManufacturerUrl(Brhz& aManufacturerUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aManufacturerUrl.Set(iManufacturerUrl->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyManufacturerImageUri(Brhz& aManufacturerImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aManufacturerImageUri.Set(iManufacturerImageUri->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyModelName(Brhz& aModelName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aModelName.Set(iModelName->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyModelInfo(Brhz& aModelInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aModelInfo.Set(iModelInfo->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyModelUrl(Brhz& aModelUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aModelUrl.Set(iModelUrl->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyModelImageUri(Brhz& aModelImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aModelImageUri.Set(iModelImageUri->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyProductName(Brhz& aProductName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductName.Set(iProductName->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyProductInfo(Brhz& aProductInfo) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductInfo.Set(iProductInfo->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyProductUrl(Brhz& aProductUrl) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductUrl.Set(iProductUrl->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyProductImageUri(Brhz& aProductImageUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductImageUri.Set(iProductImageUri->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyAttributes(Brhz& aAttributes) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aAttributes.Set(iAttributes->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgMediaServer1::ManufacturerNamePropertyChanged()
{
    ReportEvent(iManufacturerNameChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ManufacturerInfoPropertyChanged()
{
    ReportEvent(iManufacturerInfoChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ManufacturerUrlPropertyChanged()
{
    ReportEvent(iManufacturerUrlChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ManufacturerImageUriPropertyChanged()
{
    ReportEvent(iManufacturerImageUriChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ModelNamePropertyChanged()
{
    ReportEvent(iModelNameChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ModelInfoPropertyChanged()
{
    ReportEvent(iModelInfoChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ModelUrlPropertyChanged()
{
    ReportEvent(iModelUrlChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ModelImageUriPropertyChanged()
{
    ReportEvent(iModelImageUriChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ProductNamePropertyChanged()
{
    ReportEvent(iProductNameChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ProductInfoPropertyChanged()
{
    ReportEvent(iProductInfoChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ProductUrlPropertyChanged()
{
    ReportEvent(iProductUrlChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::ProductImageUriPropertyChanged()
{
    ReportEvent(iProductImageUriChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::AttributesPropertyChanged()
{
    ReportEvent(iAttributesChanged);
}

