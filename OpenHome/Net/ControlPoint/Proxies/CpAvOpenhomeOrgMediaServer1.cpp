#include "CpAvOpenhomeOrgMediaServer1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Net/Private/CpiDevice.h>

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


class SyncQueryPortAvOpenhomeOrgMediaServer1 : public SyncProxyAction
{
public:
    SyncQueryPortAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncQueryPortAvOpenhomeOrgMediaServer1() {}
private:
    CpProxyAvOpenhomeOrgMediaServer1& iService;
    TUint& iValue;
};

SyncQueryPortAvOpenhomeOrgMediaServer1::SyncQueryPortAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncQueryPortAvOpenhomeOrgMediaServer1::CompleteRequest(IAsync& aAsync)
{
    iService.EndQueryPort(aAsync, iValue);
}


class SyncBrowsePortAvOpenhomeOrgMediaServer1 : public SyncProxyAction
{
public:
    SyncBrowsePortAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncBrowsePortAvOpenhomeOrgMediaServer1() {}
private:
    CpProxyAvOpenhomeOrgMediaServer1& iService;
    TUint& iValue;
};

SyncBrowsePortAvOpenhomeOrgMediaServer1::SyncBrowsePortAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncBrowsePortAvOpenhomeOrgMediaServer1::CompleteRequest(IAsync& aAsync)
{
    iService.EndBrowsePort(aAsync, iValue);
}


class SyncUpdateCountAvOpenhomeOrgMediaServer1 : public SyncProxyAction
{
public:
    SyncUpdateCountAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, TUint& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncUpdateCountAvOpenhomeOrgMediaServer1() {}
private:
    CpProxyAvOpenhomeOrgMediaServer1& iService;
    TUint& iValue;
};

SyncUpdateCountAvOpenhomeOrgMediaServer1::SyncUpdateCountAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1& aProxy, TUint& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncUpdateCountAvOpenhomeOrgMediaServer1::CompleteRequest(IAsync& aAsync)
{
    iService.EndUpdateCount(aAsync, iValue);
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

    iActionQueryPort = new Action("QueryPort");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionQueryPort->AddOutputParameter(param);

    iActionBrowsePort = new Action("BrowsePort");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionBrowsePort->AddOutputParameter(param);

    iActionUpdateCount = new Action("UpdateCount");
    param = new OpenHome::Net::ParameterUint("Value");
    iActionUpdateCount->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ManufacturerNamePropertyChanged);
    iManufacturerName = new PropertyString(aDevice.Device().GetCpStack().Env(), "ManufacturerName", functor);
    AddProperty(iManufacturerName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ManufacturerInfoPropertyChanged);
    iManufacturerInfo = new PropertyString(aDevice.Device().GetCpStack().Env(), "ManufacturerInfo", functor);
    AddProperty(iManufacturerInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ManufacturerUrlPropertyChanged);
    iManufacturerUrl = new PropertyString(aDevice.Device().GetCpStack().Env(), "ManufacturerUrl", functor);
    AddProperty(iManufacturerUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ManufacturerImageUriPropertyChanged);
    iManufacturerImageUri = new PropertyString(aDevice.Device().GetCpStack().Env(), "ManufacturerImageUri", functor);
    AddProperty(iManufacturerImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ModelNamePropertyChanged);
    iModelName = new PropertyString(aDevice.Device().GetCpStack().Env(), "ModelName", functor);
    AddProperty(iModelName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ModelInfoPropertyChanged);
    iModelInfo = new PropertyString(aDevice.Device().GetCpStack().Env(), "ModelInfo", functor);
    AddProperty(iModelInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ModelUrlPropertyChanged);
    iModelUrl = new PropertyString(aDevice.Device().GetCpStack().Env(), "ModelUrl", functor);
    AddProperty(iModelUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ModelImageUriPropertyChanged);
    iModelImageUri = new PropertyString(aDevice.Device().GetCpStack().Env(), "ModelImageUri", functor);
    AddProperty(iModelImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ProductNamePropertyChanged);
    iProductName = new PropertyString(aDevice.Device().GetCpStack().Env(), "ProductName", functor);
    AddProperty(iProductName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ProductInfoPropertyChanged);
    iProductInfo = new PropertyString(aDevice.Device().GetCpStack().Env(), "ProductInfo", functor);
    AddProperty(iProductInfo);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ProductUrlPropertyChanged);
    iProductUrl = new PropertyString(aDevice.Device().GetCpStack().Env(), "ProductUrl", functor);
    AddProperty(iProductUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::ProductImageUriPropertyChanged);
    iProductImageUri = new PropertyString(aDevice.Device().GetCpStack().Env(), "ProductImageUri", functor);
    AddProperty(iProductImageUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::AttributesPropertyChanged);
    iAttributes = new PropertyString(aDevice.Device().GetCpStack().Env(), "Attributes", functor);
    AddProperty(iAttributes);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::QueryPortPropertyChanged);
    iQueryPort = new PropertyUint(aDevice.Device().GetCpStack().Env(), "QueryPort", functor);
    AddProperty(iQueryPort);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::BrowsePortPropertyChanged);
    iBrowsePort = new PropertyUint(aDevice.Device().GetCpStack().Env(), "BrowsePort", functor);
    AddProperty(iBrowsePort);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgMediaServer1::UpdateCountPropertyChanged);
    iUpdateCount = new PropertyUint(aDevice.Device().GetCpStack().Env(), "UpdateCount", functor);
    AddProperty(iUpdateCount);
}

CpProxyAvOpenhomeOrgMediaServer1::~CpProxyAvOpenhomeOrgMediaServer1()
{
    DestroyService();
    delete iActionManufacturer;
    delete iActionModel;
    delete iActionProduct;
    delete iActionAttributes;
    delete iActionQueryPort;
    delete iActionBrowsePort;
    delete iActionUpdateCount;
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
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

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgMediaServer1::SyncQueryPort(TUint& aValue)
{
    SyncQueryPortAvOpenhomeOrgMediaServer1 sync(*this, aValue);
    BeginQueryPort(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1::BeginQueryPort(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionQueryPort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionQueryPort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgMediaServer1::EndQueryPort(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("QueryPort"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgMediaServer1::SyncBrowsePort(TUint& aValue)
{
    SyncBrowsePortAvOpenhomeOrgMediaServer1 sync(*this, aValue);
    BeginBrowsePort(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1::BeginBrowsePort(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionBrowsePort, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionBrowsePort->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgMediaServer1::EndBrowsePort(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("BrowsePort"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgMediaServer1::SyncUpdateCount(TUint& aValue)
{
    SyncUpdateCountAvOpenhomeOrgMediaServer1 sync(*this, aValue);
    BeginUpdateCount(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgMediaServer1::BeginUpdateCount(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionUpdateCount, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionUpdateCount->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgMediaServer1::EndUpdateCount(IAsync& aAsync, TUint& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("UpdateCount"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
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

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyQueryPortChanged(Functor& aFunctor)
{
    iLock->Wait();
    iQueryPortChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyBrowsePortChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBrowsePortChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::SetPropertyUpdateCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iUpdateCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyManufacturerName(Brhz& aManufacturerName) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aManufacturerName.Set(iManufacturerName->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyManufacturerInfo(Brhz& aManufacturerInfo) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aManufacturerInfo.Set(iManufacturerInfo->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyManufacturerUrl(Brhz& aManufacturerUrl) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aManufacturerUrl.Set(iManufacturerUrl->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyManufacturerImageUri(Brhz& aManufacturerImageUri) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aManufacturerImageUri.Set(iManufacturerImageUri->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyModelName(Brhz& aModelName) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aModelName.Set(iModelName->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyModelInfo(Brhz& aModelInfo) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aModelInfo.Set(iModelInfo->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyModelUrl(Brhz& aModelUrl) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aModelUrl.Set(iModelUrl->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyModelImageUri(Brhz& aModelImageUri) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aModelImageUri.Set(iModelImageUri->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyProductName(Brhz& aProductName) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductName.Set(iProductName->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyProductInfo(Brhz& aProductInfo) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductInfo.Set(iProductInfo->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyProductUrl(Brhz& aProductUrl) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductUrl.Set(iProductUrl->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyProductImageUri(Brhz& aProductImageUri) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aProductImageUri.Set(iProductImageUri->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyAttributes(Brhz& aAttributes) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aAttributes.Set(iAttributes->Value());
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyQueryPort(TUint& aQueryPort) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aQueryPort = iQueryPort->Value();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyBrowsePort(TUint& aBrowsePort) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBrowsePort = iBrowsePort->Value();
}

void CpProxyAvOpenhomeOrgMediaServer1::PropertyUpdateCount(TUint& aUpdateCount) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aUpdateCount = iUpdateCount->Value();
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

void CpProxyAvOpenhomeOrgMediaServer1::QueryPortPropertyChanged()
{
    ReportEvent(iQueryPortChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::BrowsePortPropertyChanged()
{
    ReportEvent(iBrowsePortChanged);
}

void CpProxyAvOpenhomeOrgMediaServer1::UpdateCountPropertyChanged()
{
    ReportEvent(iUpdateCountChanged);
}

