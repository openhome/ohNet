#include "CpAvOpenhomeOrgInfo1.h"
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


class SyncCountersAvOpenhomeOrgInfo1Cpp : public SyncProxyAction
{
public:
    SyncCountersAvOpenhomeOrgInfo1Cpp(CpProxyAvOpenhomeOrgInfo1Cpp& aProxy, uint32_t& aTrackCount, uint32_t& aDetailsCount, uint32_t& aMetatextCount);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCountersAvOpenhomeOrgInfo1Cpp() {}
private:
    CpProxyAvOpenhomeOrgInfo1Cpp& iService;
    uint32_t& iTrackCount;
    uint32_t& iDetailsCount;
    uint32_t& iMetatextCount;
};

SyncCountersAvOpenhomeOrgInfo1Cpp::SyncCountersAvOpenhomeOrgInfo1Cpp(CpProxyAvOpenhomeOrgInfo1Cpp& aProxy, uint32_t& aTrackCount, uint32_t& aDetailsCount, uint32_t& aMetatextCount)
    : iService(aProxy)
    , iTrackCount(aTrackCount)
    , iDetailsCount(aDetailsCount)
    , iMetatextCount(aMetatextCount)
{
}

void SyncCountersAvOpenhomeOrgInfo1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCounters(aAsync, iTrackCount, iDetailsCount, iMetatextCount);
}


class SyncTrackAvOpenhomeOrgInfo1Cpp : public SyncProxyAction
{
public:
    SyncTrackAvOpenhomeOrgInfo1Cpp(CpProxyAvOpenhomeOrgInfo1Cpp& aProxy, std::string& aUri, std::string& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTrackAvOpenhomeOrgInfo1Cpp() {}
private:
    CpProxyAvOpenhomeOrgInfo1Cpp& iService;
    std::string& iUri;
    std::string& iMetadata;
};

SyncTrackAvOpenhomeOrgInfo1Cpp::SyncTrackAvOpenhomeOrgInfo1Cpp(CpProxyAvOpenhomeOrgInfo1Cpp& aProxy, std::string& aUri, std::string& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncTrackAvOpenhomeOrgInfo1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTrack(aAsync, iUri, iMetadata);
}


class SyncDetailsAvOpenhomeOrgInfo1Cpp : public SyncProxyAction
{
public:
    SyncDetailsAvOpenhomeOrgInfo1Cpp(CpProxyAvOpenhomeOrgInfo1Cpp& aProxy, uint32_t& aDuration, uint32_t& aBitRate, uint32_t& aBitDepth, uint32_t& aSampleRate, bool& aLossless, std::string& aCodecName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDetailsAvOpenhomeOrgInfo1Cpp() {}
private:
    CpProxyAvOpenhomeOrgInfo1Cpp& iService;
    uint32_t& iDuration;
    uint32_t& iBitRate;
    uint32_t& iBitDepth;
    uint32_t& iSampleRate;
    bool& iLossless;
    std::string& iCodecName;
};

SyncDetailsAvOpenhomeOrgInfo1Cpp::SyncDetailsAvOpenhomeOrgInfo1Cpp(CpProxyAvOpenhomeOrgInfo1Cpp& aProxy, uint32_t& aDuration, uint32_t& aBitRate, uint32_t& aBitDepth, uint32_t& aSampleRate, bool& aLossless, std::string& aCodecName)
    : iService(aProxy)
    , iDuration(aDuration)
    , iBitRate(aBitRate)
    , iBitDepth(aBitDepth)
    , iSampleRate(aSampleRate)
    , iLossless(aLossless)
    , iCodecName(aCodecName)
{
}

void SyncDetailsAvOpenhomeOrgInfo1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDetails(aAsync, iDuration, iBitRate, iBitDepth, iSampleRate, iLossless, iCodecName);
}


class SyncMetatextAvOpenhomeOrgInfo1Cpp : public SyncProxyAction
{
public:
    SyncMetatextAvOpenhomeOrgInfo1Cpp(CpProxyAvOpenhomeOrgInfo1Cpp& aProxy, std::string& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMetatextAvOpenhomeOrgInfo1Cpp() {}
private:
    CpProxyAvOpenhomeOrgInfo1Cpp& iService;
    std::string& iValue;
};

SyncMetatextAvOpenhomeOrgInfo1Cpp::SyncMetatextAvOpenhomeOrgInfo1Cpp(CpProxyAvOpenhomeOrgInfo1Cpp& aProxy, std::string& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncMetatextAvOpenhomeOrgInfo1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetatext(aAsync, iValue);
}


CpProxyAvOpenhomeOrgInfo1Cpp::CpProxyAvOpenhomeOrgInfo1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("av-openhome-org", "Info", 1, aDevice.Device())
{
    OpenHome::Net::Parameter* param;

    iActionCounters = new Action("Counters");
    param = new OpenHome::Net::ParameterUint("TrackCount");
    iActionCounters->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("DetailsCount");
    iActionCounters->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("MetatextCount");
    iActionCounters->AddOutputParameter(param);

    iActionTrack = new Action("Track");
    param = new OpenHome::Net::ParameterString("Uri");
    iActionTrack->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("Metadata");
    iActionTrack->AddOutputParameter(param);

    iActionDetails = new Action("Details");
    param = new OpenHome::Net::ParameterUint("Duration");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("BitRate");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("BitDepth");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterUint("SampleRate");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterBool("Lossless");
    iActionDetails->AddOutputParameter(param);
    param = new OpenHome::Net::ParameterString("CodecName");
    iActionDetails->AddOutputParameter(param);

    iActionMetatext = new Action("Metatext");
    param = new OpenHome::Net::ParameterString("Value");
    iActionMetatext->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint(aDevice.Device().GetCpStack().Env(), "TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::DetailsCountPropertyChanged);
    iDetailsCount = new PropertyUint(aDevice.Device().GetCpStack().Env(), "DetailsCount", functor);
    AddProperty(iDetailsCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::MetatextCountPropertyChanged);
    iMetatextCount = new PropertyUint(aDevice.Device().GetCpStack().Env(), "MetatextCount", functor);
    AddProperty(iMetatextCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::UriPropertyChanged);
    iUri = new PropertyString(aDevice.Device().GetCpStack().Env(), "Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::MetadataPropertyChanged);
    iMetadata = new PropertyString(aDevice.Device().GetCpStack().Env(), "Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::DurationPropertyChanged);
    iDuration = new PropertyUint(aDevice.Device().GetCpStack().Env(), "Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::BitRatePropertyChanged);
    iBitRate = new PropertyUint(aDevice.Device().GetCpStack().Env(), "BitRate", functor);
    AddProperty(iBitRate);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::BitDepthPropertyChanged);
    iBitDepth = new PropertyUint(aDevice.Device().GetCpStack().Env(), "BitDepth", functor);
    AddProperty(iBitDepth);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::SampleRatePropertyChanged);
    iSampleRate = new PropertyUint(aDevice.Device().GetCpStack().Env(), "SampleRate", functor);
    AddProperty(iSampleRate);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::LosslessPropertyChanged);
    iLossless = new PropertyBool(aDevice.Device().GetCpStack().Env(), "Lossless", functor);
    AddProperty(iLossless);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::CodecNamePropertyChanged);
    iCodecName = new PropertyString(aDevice.Device().GetCpStack().Env(), "CodecName", functor);
    AddProperty(iCodecName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1Cpp::MetatextPropertyChanged);
    iMetatext = new PropertyString(aDevice.Device().GetCpStack().Env(), "Metatext", functor);
    AddProperty(iMetatext);
}

CpProxyAvOpenhomeOrgInfo1Cpp::~CpProxyAvOpenhomeOrgInfo1Cpp()
{
    DestroyService();
    delete iActionCounters;
    delete iActionTrack;
    delete iActionDetails;
    delete iActionMetatext;
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SyncCounters(uint32_t& aTrackCount, uint32_t& aDetailsCount, uint32_t& aMetatextCount)
{
    SyncCountersAvOpenhomeOrgInfo1Cpp sync(*this, aTrackCount, aDetailsCount, aMetatextCount);
    BeginCounters(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::BeginCounters(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCounters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCounters->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::EndCounters(IAsync& aAsync, uint32_t& aTrackCount, uint32_t& aDetailsCount, uint32_t& aMetatextCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Counters"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aTrackCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aDetailsCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aMetatextCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SyncTrack(std::string& aUri, std::string& aMetadata)
{
    SyncTrackAvOpenhomeOrgInfo1Cpp sync(*this, aUri, aMetadata);
    BeginTrack(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::BeginTrack(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTrack, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTrack->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::EndTrack(IAsync& aAsync, std::string& aUri, std::string& aMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Track"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aUri.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SyncDetails(uint32_t& aDuration, uint32_t& aBitRate, uint32_t& aBitDepth, uint32_t& aSampleRate, bool& aLossless, std::string& aCodecName)
{
    SyncDetailsAvOpenhomeOrgInfo1Cpp sync(*this, aDuration, aBitRate, aBitDepth, aSampleRate, aLossless, aCodecName);
    BeginDetails(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::BeginDetails(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDetails, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDetails->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::EndDetails(IAsync& aAsync, uint32_t& aDuration, uint32_t& aBitRate, uint32_t& aBitDepth, uint32_t& aSampleRate, bool& aLossless, std::string& aCodecName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Details"));

    Error::ELevel level;
    TUint code;
    const TChar* ignore;
    if (invocation.Error(level, code, ignore)) {
        THROW_PROXYERROR(level, code);
    }
    TUint index = 0;
    aDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBitRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aBitDepth = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aSampleRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aLossless = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aCodecName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SyncMetatext(std::string& aValue)
{
    SyncMetatextAvOpenhomeOrgInfo1Cpp sync(*this, aValue);
    BeginMetatext(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::BeginMetatext(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMetatext, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetatext->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::EndMetatext(IAsync& aAsync, std::string& aValue)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metatext"));

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

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyDetailsCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDetailsCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyMetatextCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetatextCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyBitRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBitRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyBitDepthChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBitDepthChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertySampleRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSampleRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyLosslessChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLosslessChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyCodecNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iCodecNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SetPropertyMetatextChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetatextChanged = aFunctor;
    iLock->Signal();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyTrackCount(uint32_t& aTrackCount) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyDetailsCount(uint32_t& aDetailsCount) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDetailsCount = iDetailsCount->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyMetatextCount(uint32_t& aMetatextCount) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMetatextCount = iMetatextCount->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyUri(std::string& aUri) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iUri->Value();
    aUri.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyMetadata(std::string& aMetadata) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iMetadata->Value();
    aMetadata.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyDuration(uint32_t& aDuration) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyBitRate(uint32_t& aBitRate) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBitRate = iBitRate->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyBitDepth(uint32_t& aBitDepth) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBitDepth = iBitDepth->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertySampleRate(uint32_t& aSampleRate) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSampleRate = iSampleRate->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyLossless(bool& aLossless) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLossless = iLossless->Value();
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyCodecName(std::string& aCodecName) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iCodecName->Value();
    aCodecName.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgInfo1Cpp::PropertyMetatext(std::string& aMetatext) const
{
    AutoMutex a(PropertyReadLock());
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iMetatext->Value();
    aMetatext.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyAvOpenhomeOrgInfo1Cpp::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::DetailsCountPropertyChanged()
{
    ReportEvent(iDetailsCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::MetatextCountPropertyChanged()
{
    ReportEvent(iMetatextCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::BitRatePropertyChanged()
{
    ReportEvent(iBitRateChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::BitDepthPropertyChanged()
{
    ReportEvent(iBitDepthChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::SampleRatePropertyChanged()
{
    ReportEvent(iSampleRateChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::LosslessPropertyChanged()
{
    ReportEvent(iLosslessChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::CodecNamePropertyChanged()
{
    ReportEvent(iCodecNameChanged);
}

void CpProxyAvOpenhomeOrgInfo1Cpp::MetatextPropertyChanged()
{
    ReportEvent(iMetatextChanged);
}

