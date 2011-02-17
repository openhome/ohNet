#include "CpLinnCoUkInfo1.h"
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncCountersLinnCoUkInfo1Cpp : public SyncProxyAction
{
public:
    SyncCountersLinnCoUkInfo1Cpp(CpProxyLinnCoUkInfo1Cpp& aProxy, uint32_t& aaTrackCount, uint32_t& aaDetailsCount, uint32_t& aaMetatextCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1Cpp& iService;
    uint32_t& iaTrackCount;
    uint32_t& iaDetailsCount;
    uint32_t& iaMetatextCount;
};

SyncCountersLinnCoUkInfo1Cpp::SyncCountersLinnCoUkInfo1Cpp(CpProxyLinnCoUkInfo1Cpp& aProxy, uint32_t& aaTrackCount, uint32_t& aaDetailsCount, uint32_t& aaMetatextCount)
    : iService(aProxy)
    , iaTrackCount(aaTrackCount)
    , iaDetailsCount(aaDetailsCount)
    , iaMetatextCount(aaMetatextCount)
{
}

void SyncCountersLinnCoUkInfo1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCounters(aAsync, iaTrackCount, iaDetailsCount, iaMetatextCount);
}


class SyncTrackLinnCoUkInfo1Cpp : public SyncProxyAction
{
public:
    SyncTrackLinnCoUkInfo1Cpp(CpProxyLinnCoUkInfo1Cpp& aProxy, std::string& aaUri, std::string& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1Cpp& iService;
    std::string& iaUri;
    std::string& iaMetadata;
};

SyncTrackLinnCoUkInfo1Cpp::SyncTrackLinnCoUkInfo1Cpp(CpProxyLinnCoUkInfo1Cpp& aProxy, std::string& aaUri, std::string& aaMetadata)
    : iService(aProxy)
    , iaUri(aaUri)
    , iaMetadata(aaMetadata)
{
}

void SyncTrackLinnCoUkInfo1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndTrack(aAsync, iaUri, iaMetadata);
}


class SyncDetailsLinnCoUkInfo1Cpp : public SyncProxyAction
{
public:
    SyncDetailsLinnCoUkInfo1Cpp(CpProxyLinnCoUkInfo1Cpp& aProxy, uint32_t& aaDuration, uint32_t& aaBitRate, uint32_t& aaBitDepth, uint32_t& aaSampleRate, bool& aaLossless, std::string& aaCodecName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1Cpp& iService;
    uint32_t& iaDuration;
    uint32_t& iaBitRate;
    uint32_t& iaBitDepth;
    uint32_t& iaSampleRate;
    bool& iaLossless;
    std::string& iaCodecName;
};

SyncDetailsLinnCoUkInfo1Cpp::SyncDetailsLinnCoUkInfo1Cpp(CpProxyLinnCoUkInfo1Cpp& aProxy, uint32_t& aaDuration, uint32_t& aaBitRate, uint32_t& aaBitDepth, uint32_t& aaSampleRate, bool& aaLossless, std::string& aaCodecName)
    : iService(aProxy)
    , iaDuration(aaDuration)
    , iaBitRate(aaBitRate)
    , iaBitDepth(aaBitDepth)
    , iaSampleRate(aaSampleRate)
    , iaLossless(aaLossless)
    , iaCodecName(aaCodecName)
{
}

void SyncDetailsLinnCoUkInfo1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDetails(aAsync, iaDuration, iaBitRate, iaBitDepth, iaSampleRate, iaLossless, iaCodecName);
}


class SyncMetatextLinnCoUkInfo1Cpp : public SyncProxyAction
{
public:
    SyncMetatextLinnCoUkInfo1Cpp(CpProxyLinnCoUkInfo1Cpp& aProxy, std::string& aaMetatext);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1Cpp& iService;
    std::string& iaMetatext;
};

SyncMetatextLinnCoUkInfo1Cpp::SyncMetatextLinnCoUkInfo1Cpp(CpProxyLinnCoUkInfo1Cpp& aProxy, std::string& aaMetatext)
    : iService(aProxy)
    , iaMetatext(aaMetatext)
{
}

void SyncMetatextLinnCoUkInfo1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetatext(aAsync, iaMetatext);
}


CpProxyLinnCoUkInfo1Cpp::CpProxyLinnCoUkInfo1Cpp(CpDeviceCpp& aDevice)
    : CpProxy("linn-co-uk", "Info", 1, aDevice.Device())
{
    Zapp::Parameter* param;

    iActionCounters = new Action("Counters");
    param = new Zapp::ParameterUint("aTrackCount");
    iActionCounters->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aDetailsCount");
    iActionCounters->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aMetatextCount");
    iActionCounters->AddOutputParameter(param);

    iActionTrack = new Action("Track");
    param = new Zapp::ParameterString("aUri");
    iActionTrack->AddOutputParameter(param);
    param = new Zapp::ParameterString("aMetadata");
    iActionTrack->AddOutputParameter(param);

    iActionDetails = new Action("Details");
    param = new Zapp::ParameterUint("aDuration");
    iActionDetails->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aBitRate");
    iActionDetails->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aBitDepth");
    iActionDetails->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aSampleRate");
    iActionDetails->AddOutputParameter(param);
    param = new Zapp::ParameterBool("aLossless");
    iActionDetails->AddOutputParameter(param);
    param = new Zapp::ParameterString("aCodecName");
    iActionDetails->AddOutputParameter(param);

    iActionMetatext = new Action("Metatext");
    param = new Zapp::ParameterString("aMetatext");
    iActionMetatext->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::DetailsCountPropertyChanged);
    iDetailsCount = new PropertyUint("DetailsCount", functor);
    AddProperty(iDetailsCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::MetatextCountPropertyChanged);
    iMetatextCount = new PropertyUint("MetatextCount", functor);
    AddProperty(iMetatextCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::UriPropertyChanged);
    iUri = new PropertyString("Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::BitRatePropertyChanged);
    iBitRate = new PropertyUint("BitRate", functor);
    AddProperty(iBitRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::BitDepthPropertyChanged);
    iBitDepth = new PropertyUint("BitDepth", functor);
    AddProperty(iBitDepth);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::SampleRatePropertyChanged);
    iSampleRate = new PropertyUint("SampleRate", functor);
    AddProperty(iSampleRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::LosslessPropertyChanged);
    iLossless = new PropertyBool("Lossless", functor);
    AddProperty(iLossless);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::CodecNamePropertyChanged);
    iCodecName = new PropertyString("CodecName", functor);
    AddProperty(iCodecName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1Cpp::MetatextPropertyChanged);
    iMetatext = new PropertyString("Metatext", functor);
    AddProperty(iMetatext);
}

CpProxyLinnCoUkInfo1Cpp::~CpProxyLinnCoUkInfo1Cpp()
{
    DestroyService();
    delete iActionCounters;
    delete iActionTrack;
    delete iActionDetails;
    delete iActionMetatext;
}

void CpProxyLinnCoUkInfo1Cpp::SyncCounters(uint32_t& aaTrackCount, uint32_t& aaDetailsCount, uint32_t& aaMetatextCount)
{
    SyncCountersLinnCoUkInfo1Cpp sync(*this, aaTrackCount, aaDetailsCount, aaMetatextCount);
    BeginCounters(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1Cpp::BeginCounters(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCounters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCounters->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkInfo1Cpp::EndCounters(IAsync& aAsync, uint32_t& aaTrackCount, uint32_t& aaDetailsCount, uint32_t& aaMetatextCount)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Counters"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaTrackCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaDetailsCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaMetatextCount = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkInfo1Cpp::SyncTrack(std::string& aaUri, std::string& aaMetadata)
{
    SyncTrackLinnCoUkInfo1Cpp sync(*this, aaUri, aaMetadata);
    BeginTrack(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1Cpp::BeginTrack(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTrack, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTrack->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkInfo1Cpp::EndTrack(IAsync& aAsync, std::string& aaUri, std::string& aaMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Track"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaUri.assign((const char*)val.Ptr(), val.Bytes());
    }
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaMetadata.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkInfo1Cpp::SyncDetails(uint32_t& aaDuration, uint32_t& aaBitRate, uint32_t& aaBitDepth, uint32_t& aaSampleRate, bool& aaLossless, std::string& aaCodecName)
{
    SyncDetailsLinnCoUkInfo1Cpp sync(*this, aaDuration, aaBitRate, aaBitDepth, aaSampleRate, aaLossless, aaCodecName);
    BeginDetails(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1Cpp::BeginDetails(FunctorAsync& aFunctor)
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

void CpProxyLinnCoUkInfo1Cpp::EndDetails(IAsync& aAsync, uint32_t& aaDuration, uint32_t& aaBitRate, uint32_t& aaBitDepth, uint32_t& aaSampleRate, bool& aaLossless, std::string& aaCodecName)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Details"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaBitRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaBitDepth = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaSampleRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaLossless = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaCodecName.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkInfo1Cpp::SyncMetatext(std::string& aaMetatext)
{
    SyncMetatextLinnCoUkInfo1Cpp sync(*this, aaMetatext);
    BeginMetatext(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1Cpp::BeginMetatext(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMetatext, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetatext->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkInfo1Cpp::EndMetatext(IAsync& aAsync, std::string& aaMetatext)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metatext"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaMetatext.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyDetailsCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDetailsCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyMetatextCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetatextCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyBitRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBitRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyBitDepthChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBitDepthChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertySampleRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSampleRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyLosslessChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLosslessChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyCodecNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iCodecNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::SetPropertyMetatextChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetatextChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyTrackCount(uint32_t& aTrackCount) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyDetailsCount(uint32_t& aDetailsCount) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDetailsCount = iDetailsCount->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyMetatextCount(uint32_t& aMetatextCount) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMetatextCount = iMetatextCount->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyUri(std::string& aUri) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iUri->Value();
    aUri.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyMetadata(std::string& aMetadata) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iMetadata->Value();
    aMetadata.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyDuration(uint32_t& aDuration) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyBitRate(uint32_t& aBitRate) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBitRate = iBitRate->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyBitDepth(uint32_t& aBitDepth) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBitDepth = iBitDepth->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertySampleRate(uint32_t& aSampleRate) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSampleRate = iSampleRate->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyLossless(bool& aLossless) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLossless = iLossless->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyCodecName(std::string& aCodecName) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iCodecName->Value();
    aCodecName.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::PropertyMetatext(std::string& aMetatext) const
{
    PropertyReadLock();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iMetatext->Value();
    aMetatext.assign((const char*)val.Ptr(), val.Bytes());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1Cpp::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyLinnCoUkInfo1Cpp::DetailsCountPropertyChanged()
{
    ReportEvent(iDetailsCountChanged);
}

void CpProxyLinnCoUkInfo1Cpp::MetatextCountPropertyChanged()
{
    ReportEvent(iMetatextCountChanged);
}

void CpProxyLinnCoUkInfo1Cpp::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyLinnCoUkInfo1Cpp::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyLinnCoUkInfo1Cpp::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyLinnCoUkInfo1Cpp::BitRatePropertyChanged()
{
    ReportEvent(iBitRateChanged);
}

void CpProxyLinnCoUkInfo1Cpp::BitDepthPropertyChanged()
{
    ReportEvent(iBitDepthChanged);
}

void CpProxyLinnCoUkInfo1Cpp::SampleRatePropertyChanged()
{
    ReportEvent(iSampleRateChanged);
}

void CpProxyLinnCoUkInfo1Cpp::LosslessPropertyChanged()
{
    ReportEvent(iLosslessChanged);
}

void CpProxyLinnCoUkInfo1Cpp::CodecNamePropertyChanged()
{
    ReportEvent(iCodecNameChanged);
}

void CpProxyLinnCoUkInfo1Cpp::MetatextPropertyChanged()
{
    ReportEvent(iMetatextChanged);
}

