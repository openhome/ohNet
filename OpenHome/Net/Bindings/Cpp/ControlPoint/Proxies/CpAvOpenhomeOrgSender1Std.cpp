#include "CpAvOpenhomeOrgSender1.h"
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

#include <string>

using namespace OpenHome;
using namespace OpenHome::Net;


class SyncPresentationUrlAvOpenhomeOrgSender1Cpp : public SyncProxyAction
{
public:
    SyncPresentationUrlAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncPresentationUrlAvOpenhomeOrgSender1Cpp() {}
private:
    CpProxyAvOpenhomeOrgSender1Cpp& iService;
    std::string& iValue;
};

SyncPresentationUrlAvOpenhomeOrgSender1Cpp::SyncPresentationUrlAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncPresentationUrlAvOpenhomeOrgSender1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPresentationUrl(aAsync, iValue);
}


class SyncMetadataAvOpenhomeOrgSender1Cpp : public SyncProxyAction
{
public:
    SyncMetadataAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMetadataAvOpenhomeOrgSender1Cpp() {}
private:
    CpProxyAvOpenhomeOrgSender1Cpp& iService;
    std::string& iValue;
};

SyncMetadataAvOpenhomeOrgSender1Cpp::SyncMetadataAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncMetadataAvOpenhomeOrgSender1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetadata(aAsync, iValue);
}


class SyncAudioAvOpenhomeOrgSender1Cpp : public SyncProxyAction
{
public:
    SyncAudioAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, bool& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAudioAvOpenhomeOrgSender1Cpp() {}
private:
    CpProxyAvOpenhomeOrgSender1Cpp& iService;
    bool& iValue;
};

SyncAudioAvOpenhomeOrgSender1Cpp::SyncAudioAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, bool& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncAudioAvOpenhomeOrgSender1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAudio(aAsync, iValue);
}


class SyncStatusAvOpenhomeOrgSender1Cpp : public SyncProxyAction
{
public:
    SyncStatusAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncStatusAvOpenhomeOrgSender1Cpp() {}
private:
    CpProxyAvOpenhomeOrgSender1Cpp& iService;
    std::string& iValue;
};

SyncStatusAvOpenhomeOrgSender1Cpp::SyncStatusAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncStatusAvOpenhomeOrgSender1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStatus(aAsync, iValue);
}


class SyncAttributesAvOpenhomeOrgSender1Cpp : public SyncProxyAction
{
public:
    SyncAttributesAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncAttributesAvOpenhomeOrgSender1Cpp() {}
private:
    CpProxyAvOpenhomeOrgSender1Cpp& iService;
    std::string& iValue;
};

SyncAttributesAvOpenhomeOrgSender1Cpp::SyncAttributesAvOpenhomeOrgSender1Cpp(CpProxyAvOpenhomeOrgSender1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncAttributesAvOpenhomeOrgSender1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndAttributes(aAsync, iValue);
}


CpProxyAvOpenhomeOrgSender1Cpp::CpProxyAvOpenhomeOrgSender1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("av-openhome-org", "Sender", 1, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1Cpp::PresentationUrlPropertyChanged);
    iPresentationUrl = new PropertyString("PresentationUrl", functor);
    AddProperty(iPresentationUrl);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1Cpp::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1Cpp::AudioPropertyChanged);
    iAudio = new PropertyBool("Audio", functor);
    AddProperty(iAudio);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1Cpp::StatusPropertyChanged);
    iStatus = new PropertyString("Status", functor);
    AddProperty(iStatus);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgSender1Cpp::AttributesPropertyChanged);
    iAttributes = new PropertyString("Attributes", functor);
    AddProperty(iAttributes);
}

CpProxyAvOpenhomeOrgSender1Cpp::~CpProxyAvOpenhomeOrgSender1Cpp()
{
    DestroyService();
    delete iActionPresentationUrl;
    delete iActionMetadata;
    delete iActionAudio;
    delete iActionStatus;
    delete iActionAttributes;
}

void CpProxyAvOpenhomeOrgSender1Cpp::SyncPresentationUrl(std::string& aValue)
{
    SyncPresentationUrlAvOpenhomeOrgSender1Cpp sync(*this, aValue);
    BeginPresentationUrl(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1Cpp::BeginPresentationUrl(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPresentationUrl, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionPresentationUrl->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1Cpp::EndPresentationUrl(IAsync& aAsync, std::string& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("PresentationUrl"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgSender1Cpp::SyncMetadata(std::string& aValue)
{
    SyncMetadataAvOpenhomeOrgSender1Cpp sync(*this, aValue);
    BeginMetadata(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1Cpp::BeginMetadata(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMetadata, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetadata->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1Cpp::EndMetadata(IAsync& aAsync, std::string& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metadata"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgSender1Cpp::SyncAudio(bool& aValue)
{
    SyncAudioAvOpenhomeOrgSender1Cpp sync(*this, aValue);
    BeginAudio(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1Cpp::BeginAudio(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAudio, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAudio->OutputParameters();
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1Cpp::EndAudio(IAsync& aAsync, bool& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Audio"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aValue = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgSender1Cpp::SyncStatus(std::string& aValue)
{
    SyncStatusAvOpenhomeOrgSender1Cpp sync(*this, aValue);
    BeginStatus(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1Cpp::BeginStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStatus->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1Cpp::EndStatus(IAsync& aAsync, std::string& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Status"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgSender1Cpp::SyncAttributes(std::string& aValue)
{
    SyncAttributesAvOpenhomeOrgSender1Cpp sync(*this, aValue);
    BeginAttributes(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgSender1Cpp::BeginAttributes(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionAttributes, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionAttributes->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgSender1Cpp::EndAttributes(IAsync& aAsync, std::string& aValue)
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
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aValue.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgSender1Cpp::SetPropertyPresentationUrlChanged(Functor& aFunctor)
{
    iLock->Wait();
    iPresentationUrlChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgSender1Cpp::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgSender1Cpp::SetPropertyAudioChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAudioChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgSender1Cpp::SetPropertyStatusChanged(Functor& aFunctor)
{
    iLock->Wait();
    iStatusChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgSender1Cpp::SetPropertyAttributesChanged(Functor& aFunctor)
{
    iLock->Wait();
    iAttributesChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgSender1Cpp::PropertyPresentationUrl(std::string& aPresentationUrl) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iPresentationUrl->Value();
    aPresentationUrl.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgSender1Cpp::PropertyMetadata(std::string& aMetadata) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iMetadata->Value();
    aMetadata.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgSender1Cpp::PropertyAudio(bool& aAudio) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aAudio = iAudio->Value();
}

void CpProxyAvOpenhomeOrgSender1Cpp::PropertyStatus(std::string& aStatus) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iStatus->Value();
    aStatus.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgSender1Cpp::PropertyAttributes(std::string& aAttributes) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iAttributes->Value();
    aAttributes.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgSender1Cpp::PresentationUrlPropertyChanged()
{
    ReportEvent(iPresentationUrlChanged);
}

void CpProxyAvOpenhomeOrgSender1Cpp::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgSender1Cpp::AudioPropertyChanged()
{
    ReportEvent(iAudioChanged);
}

void CpProxyAvOpenhomeOrgSender1Cpp::StatusPropertyChanged()
{
    ReportEvent(iStatusChanged);
}

void CpProxyAvOpenhomeOrgSender1Cpp::AttributesPropertyChanged()
{
    ReportEvent(iAttributesChanged);
}

