#include "CpAvOpenhomeOrgSender1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyAvOpenhomeOrgSender1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgSender1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgSender1C();
    //CpProxyAvOpenhomeOrgSender1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgSender1*>(iProxy); }

    void SyncPresentationUrl(Brh& aValue);
    void BeginPresentationUrl(FunctorAsync& aFunctor);
    void EndPresentationUrl(IAsync& aAsync, Brh& aValue);

    void SyncMetadata(Brh& aValue);
    void BeginMetadata(FunctorAsync& aFunctor);
    void EndMetadata(IAsync& aAsync, Brh& aValue);

    void SyncAudio(TBool& aValue);
    void BeginAudio(FunctorAsync& aFunctor);
    void EndAudio(IAsync& aAsync, TBool& aValue);

    void SyncStatus(Brh& aValue);
    void BeginStatus(FunctorAsync& aFunctor);
    void EndStatus(IAsync& aAsync, Brh& aValue);

    void SyncAttributes(Brh& aValue);
    void BeginAttributes(FunctorAsync& aFunctor);
    void EndAttributes(IAsync& aAsync, Brh& aValue);

    void SetPropertyPresentationUrlChanged(Functor& aFunctor);
    void SetPropertyMetadataChanged(Functor& aFunctor);
    void SetPropertyAudioChanged(Functor& aFunctor);
    void SetPropertyStatusChanged(Functor& aFunctor);
    void SetPropertyAttributesChanged(Functor& aFunctor);

    void PropertyPresentationUrl(Brhz& aPresentationUrl) const;
    void PropertyMetadata(Brhz& aMetadata) const;
    void PropertyAudio(TBool& aAudio) const;
    void PropertyStatus(Brhz& aStatus) const;
    void PropertyAttributes(Brhz& aAttributes) const;
private:
    void PresentationUrlPropertyChanged();
    void MetadataPropertyChanged();
    void AudioPropertyChanged();
    void StatusPropertyChanged();
    void AttributesPropertyChanged();
private:
    Mutex iLock;
    Action* iActionPresentationUrl;
    Action* iActionMetadata;
    Action* iActionAudio;
    Action* iActionStatus;
    Action* iActionAttributes;
    PropertyString* iPresentationUrl;
    PropertyString* iMetadata;
    PropertyBool* iAudio;
    PropertyString* iStatus;
    PropertyString* iAttributes;
    Functor iPresentationUrlChanged;
    Functor iMetadataChanged;
    Functor iAudioChanged;
    Functor iStatusChanged;
    Functor iAttributesChanged;
};


class SyncPresentationUrlAvOpenhomeOrgSender1C : public SyncProxyAction
{
public:
    SyncPresentationUrlAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPresentationUrlAvOpenhomeOrgSender1C() {};
private:
    CpProxyAvOpenhomeOrgSender1C& iService;
    Brh& iValue;
};

SyncPresentationUrlAvOpenhomeOrgSender1C::SyncPresentationUrlAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncPresentationUrlAvOpenhomeOrgSender1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresentationUrl(aAsync, iValue);
}


class SyncMetadataAvOpenhomeOrgSender1C : public SyncProxyAction
{
public:
    SyncMetadataAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMetadataAvOpenhomeOrgSender1C() {};
private:
    CpProxyAvOpenhomeOrgSender1C& iService;
    Brh& iValue;
};

SyncMetadataAvOpenhomeOrgSender1C::SyncMetadataAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncMetadataAvOpenhomeOrgSender1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetadata(aAsync, iValue);
}


class SyncAudioAvOpenhomeOrgSender1C : public SyncProxyAction
{
public:
    SyncAudioAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, TBool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAudioAvOpenhomeOrgSender1C() {};
private:
    CpProxyAvOpenhomeOrgSender1C& iService;
    TBool& iValue;
};

SyncAudioAvOpenhomeOrgSender1C::SyncAudioAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, TBool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncAudioAvOpenhomeOrgSender1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndAudio(aAsync, iValue);
}


class SyncStatusAvOpenhomeOrgSender1C : public SyncProxyAction
{
public:
    SyncStatusAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStatusAvOpenhomeOrgSender1C() {};
private:
    CpProxyAvOpenhomeOrgSender1C& iService;
    Brh& iValue;
};

SyncStatusAvOpenhomeOrgSender1C::SyncStatusAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncStatusAvOpenhomeOrgSender1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStatus(aAsync, iValue);
}


class SyncAttributesAvOpenhomeOrgSender1C : public SyncProxyAction
{
public:
    SyncAttributesAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAttributesAvOpenhomeOrgSender1C() {};
private:
    CpProxyAvOpenhomeOrgSender1C& iService;
    Brh& iValue;
};

SyncAttributesAvOpenhomeOrgSender1C::SyncAttributesAvOpenhomeOrgSender1C(CpProxyAvOpenhomeOrgSender1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncAttributesAvOpenhomeOrgSender1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndAttributes(aAsync, iValue);
}

CpProxyAvOpenhomeOrgSender1C::CpProxyAvOpenhomeOrgSender1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Sender", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
    OpenHome::Net::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionPresentationUrl = new Action("PresentationUrl");
    param = new OpenHome::Net::ParameterString("Value");
    iActionPresentationUrl->AddOutputParameter(param);

    iActionMetadata = new Action("Metadata");
    param = new OpenHome::Net::ParameterString("Value");
    iActionMetadata->AddOutputParameter(param);

    iActionAudio = new Action("Audio");
    param = new OpenHome::Net::ParameterBool("Value");
    iActionAudio->AddOutputParameter(param);

    iActionStatus = new Action("Status");
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"Enabled";
    allowedValues[index++] = (TChar*)"Disabled";
    allowedValues[index++] = (TChar*)"Blocked";
    param = new OpenHome::Net::ParameterString("Value", allowedValues, 3);
    iActionStatus->AddOutputParameter(param);
    delete[] allowedValues;

    iActionAttributes = new Action("Attributes");
    param = new OpenHome::Net::ParameterString("Value");
    iActionAttributes->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1C::PresentationUrlPropertyChanged);
    iPresentationUrl = new PropertyString("PresentationUrl", functor);
    AddProperty(iPresentationUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1C::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1C::AudioPropertyChanged);
    iAudio = new PropertyBool("Audio", functor);
    AddProperty(iAudio);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1C::StatusPropertyChanged);
    iStatus = new PropertyString("Status", functor);
    AddProperty(iStatus);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1C::AttributesPropertyChanged);
    iAttributes = new PropertyString("Attributes", functor);
    AddProperty(iAttributes);
}

CpProxyAvOpenhomeOrgSender1C::~CpProxyAvOpenhomeOrgSender1C()
{
    DestroyService();
    delete iActionPresentationUrl;
    delete iActionMetadata;
    delete iActionAudio;
    delete iActionStatus;
    delete iActionAttributes;
}

void CpProxyAvOpenhomeOrgSender1C::SyncPresentationUrl(Brh& aValue)
{
    SyncPresentationUrlAvOpenhomeOrgSender1C sync(*this, aValue);
    BeginPresentationUrl(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1C::BeginPresentationUrl(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPresentationUrl, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresentationUrl->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1C::EndPresentationUrl(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresentationUrl"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgSender1C::SyncMetadata(Brh& aValue)
{
    SyncMetadataAvOpenhomeOrgSender1C sync(*this, aValue);
    BeginMetadata(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1C::BeginMetadata(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMetadata, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetadata->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1C::EndMetadata(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metadata"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgSender1C::SyncAudio(TBool& aValue)
{
    SyncAudioAvOpenhomeOrgSender1C sync(*this, aValue);
    BeginAudio(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1C::BeginAudio(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionAudio, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAudio->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1C::EndAudio(IAsync& aAsync, TBool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Audio"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgSender1C::SyncStatus(Brh& aValue)
{
    SyncStatusAvOpenhomeOrgSender1C sync(*this, aValue);
    BeginStatus(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1C::BeginStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStatus->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1C::EndStatus(IAsync& aAsync, Brh& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Status"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgSender1C::SyncAttributes(Brh& aValue)
{
    SyncAttributesAvOpenhomeOrgSender1C sync(*this, aValue);
    BeginAttributes(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1C::BeginAttributes(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionAttributes, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAttributes->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1C::EndAttributes(IAsync& aAsync, Brh& aValue)
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

void CpProxyAvOpenhomeOrgSender1C::SetPropertyPresentationUrlChanged(Functor& aFunctor)
{
    iLock.Wait();
    iPresentationUrlChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgSender1C::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetadataChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgSender1C::SetPropertyAudioChanged(Functor& aFunctor)
{
    iLock.Wait();
    iAudioChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgSender1C::SetPropertyStatusChanged(Functor& aFunctor)
{
    iLock.Wait();
    iStatusChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgSender1C::SetPropertyAttributesChanged(Functor& aFunctor)
{
    iLock.Wait();
    iAttributesChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgSender1C::PropertyPresentationUrl(Brhz& aPresentationUrl) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aPresentationUrl.Set(iPresentationUrl->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgSender1C::PropertyMetadata(Brhz& aMetadata) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aMetadata.Set(iMetadata->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgSender1C::PropertyAudio(TBool& aAudio) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aAudio = iAudio->Value();
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgSender1C::PropertyStatus(Brhz& aStatus) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aStatus.Set(iStatus->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgSender1C::PropertyAttributes(Brhz& aAttributes) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aAttributes.Set(iAttributes->Value());
    PropertyReadUnlock();
}

void CpProxyAvOpenhomeOrgSender1C::PresentationUrlPropertyChanged()
{
    ReportEvent(iPresentationUrlChanged);
}

void CpProxyAvOpenhomeOrgSender1C::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgSender1C::AudioPropertyChanged()
{
    ReportEvent(iAudioChanged);
}

void CpProxyAvOpenhomeOrgSender1C::StatusPropertyChanged()
{
    ReportEvent(iStatusChanged);
}

void CpProxyAvOpenhomeOrgSender1C::AttributesPropertyChanged()
{
    ReportEvent(iAttributesChanged);
}


THandle STDCALL CpProxyAvOpenhomeOrgSender1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgSender1C(aDevice);
}

void STDCALL CpProxyAvOpenhomeOrgSender1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    delete proxyC;
}

void STDCALL CpProxyAvOpenhomeOrgSender1SyncPresentationUrl(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    proxyC->SyncPresentationUrl(buf_aValue);
    *aValue = buf_aValue.Extract();
}

void STDCALL CpProxyAvOpenhomeOrgSender1BeginPresentationUrl(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginPresentationUrl(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgSender1EndPresentationUrl(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndPresentationUrl(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgSender1SyncMetadata(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    proxyC->SyncMetadata(buf_aValue);
    *aValue = buf_aValue.Extract();
}

void STDCALL CpProxyAvOpenhomeOrgSender1BeginMetadata(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginMetadata(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgSender1EndMetadata(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndMetadata(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgSender1SyncAudio(THandle aHandle, uint32_t* aValue)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aValue = 0;
    proxyC->SyncAudio(*(TBool*)aValue);
}

void STDCALL CpProxyAvOpenhomeOrgSender1BeginAudio(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginAudio(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgSender1EndAudio(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aValue = 0;
    try {
        proxyC->EndAudio(*async, *(TBool*)aValue);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgSender1SyncStatus(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    proxyC->SyncStatus(buf_aValue);
    *aValue = buf_aValue.Extract();
}

void STDCALL CpProxyAvOpenhomeOrgSender1BeginStatus(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginStatus(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgSender1EndStatus(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndStatus(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgSender1SyncAttributes(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    proxyC->SyncAttributes(buf_aValue);
    *aValue = buf_aValue.Extract();
}

void STDCALL CpProxyAvOpenhomeOrgSender1BeginAttributes(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginAttributes(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgSender1EndAttributes(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndAttributes(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgSender1SetPropertyPresentationUrlChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyPresentationUrlChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgSender1SetPropertyMetadataChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetadataChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgSender1SetPropertyAudioChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyAudioChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgSender1SetPropertyStatusChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyStatusChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgSender1SetPropertyAttributesChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyAttributesChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgSender1PropertyPresentationUrl(THandle aHandle, char** aPresentationUrl)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aPresentationUrl;
    proxyC->PropertyPresentationUrl(buf_aPresentationUrl);
    *aPresentationUrl = buf_aPresentationUrl.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgSender1PropertyMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetadata;
    proxyC->PropertyMetadata(buf_aMetadata);
    *aMetadata = buf_aMetadata.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgSender1PropertyAudio(THandle aHandle, uint32_t* aAudio)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aAudio = false;
    proxyC->PropertyAudio(*(TBool*)aAudio);
}

void STDCALL CpProxyAvOpenhomeOrgSender1PropertyStatus(THandle aHandle, char** aStatus)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aStatus;
    proxyC->PropertyStatus(buf_aStatus);
    *aStatus = buf_aStatus.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgSender1PropertyAttributes(THandle aHandle, char** aAttributes)
{
    CpProxyAvOpenhomeOrgSender1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgSender1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aAttributes;
    proxyC->PropertyAttributes(buf_aAttributes);
    *aAttributes = buf_aAttributes.Transfer();
}

