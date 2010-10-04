#include <Core/CpLinnCoUkInfo1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncCountersLinnCoUkInfo1 : public SyncProxyAction
{
public:
    SyncCountersLinnCoUkInfo1(CpProxyLinnCoUkInfo1& aService, TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1& iService;
    TUint& iaTrackCount;
    TUint& iaDetailsCount;
    TUint& iaMetatextCount;
};

SyncCountersLinnCoUkInfo1::SyncCountersLinnCoUkInfo1(CpProxyLinnCoUkInfo1& aService, TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount)
    : iService(aService)
    , iaTrackCount(aaTrackCount)
    , iaDetailsCount(aaDetailsCount)
    , iaMetatextCount(aaMetatextCount)
{
}

void SyncCountersLinnCoUkInfo1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCounters(aAsync, iaTrackCount, iaDetailsCount, iaMetatextCount);
}


class SyncTrackLinnCoUkInfo1 : public SyncProxyAction
{
public:
    SyncTrackLinnCoUkInfo1(CpProxyLinnCoUkInfo1& aService, Brh& aaUri, Brh& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1& iService;
    Brh& iaUri;
    Brh& iaMetadata;
};

SyncTrackLinnCoUkInfo1::SyncTrackLinnCoUkInfo1(CpProxyLinnCoUkInfo1& aService, Brh& aaUri, Brh& aaMetadata)
    : iService(aService)
    , iaUri(aaUri)
    , iaMetadata(aaMetadata)
{
}

void SyncTrackLinnCoUkInfo1::CompleteRequest(IAsync& aAsync)
{
    iService.EndTrack(aAsync, iaUri, iaMetadata);
}


class SyncDetailsLinnCoUkInfo1 : public SyncProxyAction
{
public:
    SyncDetailsLinnCoUkInfo1(CpProxyLinnCoUkInfo1& aService, TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1& iService;
    TUint& iaDuration;
    TUint& iaBitRate;
    TUint& iaBitDepth;
    TUint& iaSampleRate;
    TBool& iaLossless;
    Brh& iaCodecName;
};

SyncDetailsLinnCoUkInfo1::SyncDetailsLinnCoUkInfo1(CpProxyLinnCoUkInfo1& aService, TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName)
    : iService(aService)
    , iaDuration(aaDuration)
    , iaBitRate(aaBitRate)
    , iaBitDepth(aaBitDepth)
    , iaSampleRate(aaSampleRate)
    , iaLossless(aaLossless)
    , iaCodecName(aaCodecName)
{
}

void SyncDetailsLinnCoUkInfo1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDetails(aAsync, iaDuration, iaBitRate, iaBitDepth, iaSampleRate, iaLossless, iaCodecName);
}


class SyncMetatextLinnCoUkInfo1 : public SyncProxyAction
{
public:
    SyncMetatextLinnCoUkInfo1(CpProxyLinnCoUkInfo1& aService, Brh& aaMetatext);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1& iService;
    Brh& iaMetatext;
};

SyncMetatextLinnCoUkInfo1::SyncMetatextLinnCoUkInfo1(CpProxyLinnCoUkInfo1& aService, Brh& aaMetatext)
    : iService(aService)
    , iaMetatext(aaMetatext)
{
}

void SyncMetatextLinnCoUkInfo1::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetatext(aAsync, iaMetatext);
}


CpProxyLinnCoUkInfo1::CpProxyLinnCoUkInfo1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Info", 1, aDevice.Device());
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    iService->AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::DetailsCountPropertyChanged);
    iDetailsCount = new PropertyUint("DetailsCount", functor);
    iService->AddProperty(iDetailsCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::MetatextCountPropertyChanged);
    iMetatextCount = new PropertyUint("MetatextCount", functor);
    iService->AddProperty(iMetatextCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::UriPropertyChanged);
    iUri = new PropertyString("Uri", functor);
    iService->AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    iService->AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    iService->AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::BitRatePropertyChanged);
    iBitRate = new PropertyUint("BitRate", functor);
    iService->AddProperty(iBitRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::BitDepthPropertyChanged);
    iBitDepth = new PropertyUint("BitDepth", functor);
    iService->AddProperty(iBitDepth);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::SampleRatePropertyChanged);
    iSampleRate = new PropertyUint("SampleRate", functor);
    iService->AddProperty(iSampleRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::LosslessPropertyChanged);
    iLossless = new PropertyBool("Lossless", functor);
    iService->AddProperty(iLossless);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::CodecNamePropertyChanged);
    iCodecName = new PropertyString("CodecName", functor);
    iService->AddProperty(iCodecName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1::MetatextPropertyChanged);
    iMetatext = new PropertyString("Metatext", functor);
    iService->AddProperty(iMetatext);
}

CpProxyLinnCoUkInfo1::~CpProxyLinnCoUkInfo1()
{
    delete iService;
    delete iActionCounters;
    delete iActionTrack;
    delete iActionDetails;
    delete iActionMetatext;
}

void CpProxyLinnCoUkInfo1::SyncCounters(TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount)
{
    SyncCountersLinnCoUkInfo1 sync(*this, aaTrackCount, aaDetailsCount, aaMetatextCount);
    BeginCounters(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1::BeginCounters(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCounters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCounters->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkInfo1::EndCounters(IAsync& aAsync, TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount)
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

void CpProxyLinnCoUkInfo1::SyncTrack(Brh& aaUri, Brh& aaMetadata)
{
    SyncTrackLinnCoUkInfo1 sync(*this, aaUri, aaMetadata);
    BeginTrack(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1::BeginTrack(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionTrack, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTrack->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkInfo1::EndTrack(IAsync& aAsync, Brh& aaUri, Brh& aaMetadata)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Track"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaUri);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMetadata);
}

void CpProxyLinnCoUkInfo1::SyncDetails(TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName)
{
    SyncDetailsLinnCoUkInfo1 sync(*this, aaDuration, aaBitRate, aaBitDepth, aaSampleRate, aaLossless, aaCodecName);
    BeginDetails(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1::BeginDetails(FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyLinnCoUkInfo1::EndDetails(IAsync& aAsync, TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaCodecName);
}

void CpProxyLinnCoUkInfo1::SyncMetatext(Brh& aaMetatext)
{
    SyncMetatextLinnCoUkInfo1 sync(*this, aaMetatext);
    BeginMetatext(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1::BeginMetatext(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionMetatext, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetatext->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkInfo1::EndMetatext(IAsync& aAsync, Brh& aaMetatext)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Metatext"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaMetatext);
}

void CpProxyLinnCoUkInfo1::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyDetailsCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDetailsCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyMetatextCountChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetatextCountChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock->Wait();
    iUriChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetadataChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyBitRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBitRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyBitDepthChanged(Functor& aFunctor)
{
    iLock->Wait();
    iBitDepthChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertySampleRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSampleRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyLosslessChanged(Functor& aFunctor)
{
    iLock->Wait();
    iLosslessChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyCodecNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iCodecNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::SetPropertyMetatextChanged(Functor& aFunctor)
{
    iLock->Wait();
    iMetatextChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkInfo1::PropertyTrackCount(TUint& aTrackCount) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCount = iTrackCount->Value();
}

void CpProxyLinnCoUkInfo1::PropertyDetailsCount(TUint& aDetailsCount) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDetailsCount = iDetailsCount->Value();
}

void CpProxyLinnCoUkInfo1::PropertyMetatextCount(TUint& aMetatextCount) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMetatextCount = iMetatextCount->Value();
}

void CpProxyLinnCoUkInfo1::PropertyUri(Brhz& aUri) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aUri.Set(iUri->Value());
}

void CpProxyLinnCoUkInfo1::PropertyMetadata(Brhz& aMetadata) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMetadata.Set(iMetadata->Value());
}

void CpProxyLinnCoUkInfo1::PropertyDuration(TUint& aDuration) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aDuration = iDuration->Value();
}

void CpProxyLinnCoUkInfo1::PropertyBitRate(TUint& aBitRate) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBitRate = iBitRate->Value();
}

void CpProxyLinnCoUkInfo1::PropertyBitDepth(TUint& aBitDepth) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aBitDepth = iBitDepth->Value();
}

void CpProxyLinnCoUkInfo1::PropertySampleRate(TUint& aSampleRate) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSampleRate = iSampleRate->Value();
}

void CpProxyLinnCoUkInfo1::PropertyLossless(TBool& aLossless) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aLossless = iLossless->Value();
}

void CpProxyLinnCoUkInfo1::PropertyCodecName(Brhz& aCodecName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aCodecName.Set(iCodecName->Value());
}

void CpProxyLinnCoUkInfo1::PropertyMetatext(Brhz& aMetatext) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aMetatext.Set(iMetatext->Value());
}

void CpProxyLinnCoUkInfo1::TrackCountPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackCountChanged != NULL) {
        iTrackCountChanged();
    }
}

void CpProxyLinnCoUkInfo1::DetailsCountPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDetailsCountChanged != NULL) {
        iDetailsCountChanged();
    }
}

void CpProxyLinnCoUkInfo1::MetatextCountPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iMetatextCountChanged != NULL) {
        iMetatextCountChanged();
    }
}

void CpProxyLinnCoUkInfo1::UriPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iUriChanged != NULL) {
        iUriChanged();
    }
}

void CpProxyLinnCoUkInfo1::MetadataPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iMetadataChanged != NULL) {
        iMetadataChanged();
    }
}

void CpProxyLinnCoUkInfo1::DurationPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iDurationChanged != NULL) {
        iDurationChanged();
    }
}

void CpProxyLinnCoUkInfo1::BitRatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iBitRateChanged != NULL) {
        iBitRateChanged();
    }
}

void CpProxyLinnCoUkInfo1::BitDepthPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iBitDepthChanged != NULL) {
        iBitDepthChanged();
    }
}

void CpProxyLinnCoUkInfo1::SampleRatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iSampleRateChanged != NULL) {
        iSampleRateChanged();
    }
}

void CpProxyLinnCoUkInfo1::LosslessPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iLosslessChanged != NULL) {
        iLosslessChanged();
    }
}

void CpProxyLinnCoUkInfo1::CodecNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iCodecNameChanged != NULL) {
        iCodecNameChanged();
    }
}

void CpProxyLinnCoUkInfo1::MetatextPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iMetatextChanged != NULL) {
        iMetatextChanged();
    }
}

