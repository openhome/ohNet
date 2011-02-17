#include "CpLinnCoUkInfo1.h"
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;

class CpProxyLinnCoUkInfo1C : public CpProxyC
{
public:
    CpProxyLinnCoUkInfo1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkInfo1C();
    //CpProxyLinnCoUkInfo1* Proxy() { return static_cast<CpProxyLinnCoUkInfo1*>(iProxy); }

    void SyncCounters(TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount);
    void BeginCounters(FunctorAsync& aFunctor);
    void EndCounters(IAsync& aAsync, TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount);

    void SyncTrack(Brh& aaUri, Brh& aaMetadata);
    void BeginTrack(FunctorAsync& aFunctor);
    void EndTrack(IAsync& aAsync, Brh& aaUri, Brh& aaMetadata);

    void SyncDetails(TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName);
    void BeginDetails(FunctorAsync& aFunctor);
    void EndDetails(IAsync& aAsync, TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName);

    void SyncMetatext(Brh& aaMetatext);
    void BeginMetatext(FunctorAsync& aFunctor);
    void EndMetatext(IAsync& aAsync, Brh& aaMetatext);

    void SetPropertyTrackCountChanged(Functor& aFunctor);
    void SetPropertyDetailsCountChanged(Functor& aFunctor);
    void SetPropertyMetatextCountChanged(Functor& aFunctor);
    void SetPropertyUriChanged(Functor& aFunctor);
    void SetPropertyMetadataChanged(Functor& aFunctor);
    void SetPropertyDurationChanged(Functor& aFunctor);
    void SetPropertyBitRateChanged(Functor& aFunctor);
    void SetPropertyBitDepthChanged(Functor& aFunctor);
    void SetPropertySampleRateChanged(Functor& aFunctor);
    void SetPropertyLosslessChanged(Functor& aFunctor);
    void SetPropertyCodecNameChanged(Functor& aFunctor);
    void SetPropertyMetatextChanged(Functor& aFunctor);

    void PropertyTrackCount(TUint& aTrackCount) const;
    void PropertyDetailsCount(TUint& aDetailsCount) const;
    void PropertyMetatextCount(TUint& aMetatextCount) const;
    void PropertyUri(Brhz& aUri) const;
    void PropertyMetadata(Brhz& aMetadata) const;
    void PropertyDuration(TUint& aDuration) const;
    void PropertyBitRate(TUint& aBitRate) const;
    void PropertyBitDepth(TUint& aBitDepth) const;
    void PropertySampleRate(TUint& aSampleRate) const;
    void PropertyLossless(TBool& aLossless) const;
    void PropertyCodecName(Brhz& aCodecName) const;
    void PropertyMetatext(Brhz& aMetatext) const;
private:
    void TrackCountPropertyChanged();
    void DetailsCountPropertyChanged();
    void MetatextCountPropertyChanged();
    void UriPropertyChanged();
    void MetadataPropertyChanged();
    void DurationPropertyChanged();
    void BitRatePropertyChanged();
    void BitDepthPropertyChanged();
    void SampleRatePropertyChanged();
    void LosslessPropertyChanged();
    void CodecNamePropertyChanged();
    void MetatextPropertyChanged();
private:
    Mutex iLock;
    Action* iActionCounters;
    Action* iActionTrack;
    Action* iActionDetails;
    Action* iActionMetatext;
    PropertyUint* iTrackCount;
    PropertyUint* iDetailsCount;
    PropertyUint* iMetatextCount;
    PropertyString* iUri;
    PropertyString* iMetadata;
    PropertyUint* iDuration;
    PropertyUint* iBitRate;
    PropertyUint* iBitDepth;
    PropertyUint* iSampleRate;
    PropertyBool* iLossless;
    PropertyString* iCodecName;
    PropertyString* iMetatext;
    Functor iTrackCountChanged;
    Functor iDetailsCountChanged;
    Functor iMetatextCountChanged;
    Functor iUriChanged;
    Functor iMetadataChanged;
    Functor iDurationChanged;
    Functor iBitRateChanged;
    Functor iBitDepthChanged;
    Functor iSampleRateChanged;
    Functor iLosslessChanged;
    Functor iCodecNameChanged;
    Functor iMetatextChanged;
};


class SyncCountersLinnCoUkInfo1C : public SyncProxyAction
{
public:
    SyncCountersLinnCoUkInfo1C(CpProxyLinnCoUkInfo1C& aProxy, TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1C& iService;
    TUint& iaTrackCount;
    TUint& iaDetailsCount;
    TUint& iaMetatextCount;
};

SyncCountersLinnCoUkInfo1C::SyncCountersLinnCoUkInfo1C(CpProxyLinnCoUkInfo1C& aProxy, TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount)
    : iService(aProxy)
    , iaTrackCount(aaTrackCount)
    , iaDetailsCount(aaDetailsCount)
    , iaMetatextCount(aaMetatextCount)
{
}

void SyncCountersLinnCoUkInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCounters(aAsync, iaTrackCount, iaDetailsCount, iaMetatextCount);
}


class SyncTrackLinnCoUkInfo1C : public SyncProxyAction
{
public:
    SyncTrackLinnCoUkInfo1C(CpProxyLinnCoUkInfo1C& aProxy, Brh& aaUri, Brh& aaMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1C& iService;
    Brh& iaUri;
    Brh& iaMetadata;
};

SyncTrackLinnCoUkInfo1C::SyncTrackLinnCoUkInfo1C(CpProxyLinnCoUkInfo1C& aProxy, Brh& aaUri, Brh& aaMetadata)
    : iService(aProxy)
    , iaUri(aaUri)
    , iaMetadata(aaMetadata)
{
}

void SyncTrackLinnCoUkInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTrack(aAsync, iaUri, iaMetadata);
}


class SyncDetailsLinnCoUkInfo1C : public SyncProxyAction
{
public:
    SyncDetailsLinnCoUkInfo1C(CpProxyLinnCoUkInfo1C& aProxy, TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1C& iService;
    TUint& iaDuration;
    TUint& iaBitRate;
    TUint& iaBitDepth;
    TUint& iaSampleRate;
    TBool& iaLossless;
    Brh& iaCodecName;
};

SyncDetailsLinnCoUkInfo1C::SyncDetailsLinnCoUkInfo1C(CpProxyLinnCoUkInfo1C& aProxy, TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName)
    : iService(aProxy)
    , iaDuration(aaDuration)
    , iaBitRate(aaBitRate)
    , iaBitDepth(aaBitDepth)
    , iaSampleRate(aaSampleRate)
    , iaLossless(aaLossless)
    , iaCodecName(aaCodecName)
{
}

void SyncDetailsLinnCoUkInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDetails(aAsync, iaDuration, iaBitRate, iaBitDepth, iaSampleRate, iaLossless, iaCodecName);
}


class SyncMetatextLinnCoUkInfo1C : public SyncProxyAction
{
public:
    SyncMetatextLinnCoUkInfo1C(CpProxyLinnCoUkInfo1C& aProxy, Brh& aaMetatext);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkInfo1C& iService;
    Brh& iaMetatext;
};

SyncMetatextLinnCoUkInfo1C::SyncMetatextLinnCoUkInfo1C(CpProxyLinnCoUkInfo1C& aProxy, Brh& aaMetatext)
    : iService(aProxy)
    , iaMetatext(aaMetatext)
{
}

void SyncMetatextLinnCoUkInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetatext(aAsync, iaMetatext);
}

CpProxyLinnCoUkInfo1C::CpProxyLinnCoUkInfo1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Info", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint("TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::DetailsCountPropertyChanged);
    iDetailsCount = new PropertyUint("DetailsCount", functor);
    AddProperty(iDetailsCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::MetatextCountPropertyChanged);
    iMetatextCount = new PropertyUint("MetatextCount", functor);
    AddProperty(iMetatextCount);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::UriPropertyChanged);
    iUri = new PropertyString("Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::MetadataPropertyChanged);
    iMetadata = new PropertyString("Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::DurationPropertyChanged);
    iDuration = new PropertyUint("Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::BitRatePropertyChanged);
    iBitRate = new PropertyUint("BitRate", functor);
    AddProperty(iBitRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::BitDepthPropertyChanged);
    iBitDepth = new PropertyUint("BitDepth", functor);
    AddProperty(iBitDepth);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::SampleRatePropertyChanged);
    iSampleRate = new PropertyUint("SampleRate", functor);
    AddProperty(iSampleRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::LosslessPropertyChanged);
    iLossless = new PropertyBool("Lossless", functor);
    AddProperty(iLossless);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::CodecNamePropertyChanged);
    iCodecName = new PropertyString("CodecName", functor);
    AddProperty(iCodecName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkInfo1C::MetatextPropertyChanged);
    iMetatext = new PropertyString("Metatext", functor);
    AddProperty(iMetatext);
}

CpProxyLinnCoUkInfo1C::~CpProxyLinnCoUkInfo1C()
{
    DestroyService();
    delete iActionCounters;
    delete iActionTrack;
    delete iActionDetails;
    delete iActionMetatext;
}

void CpProxyLinnCoUkInfo1C::SyncCounters(TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount)
{
    SyncCountersLinnCoUkInfo1C sync(*this, aaTrackCount, aaDetailsCount, aaMetatextCount);
    BeginCounters(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1C::BeginCounters(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCounters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCounters->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkInfo1C::EndCounters(IAsync& aAsync, TUint& aaTrackCount, TUint& aaDetailsCount, TUint& aaMetatextCount)
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

void CpProxyLinnCoUkInfo1C::SyncTrack(Brh& aaUri, Brh& aaMetadata)
{
    SyncTrackLinnCoUkInfo1C sync(*this, aaUri, aaMetadata);
    BeginTrack(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1C::BeginTrack(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTrack, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTrack->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkInfo1C::EndTrack(IAsync& aAsync, Brh& aaUri, Brh& aaMetadata)
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

void CpProxyLinnCoUkInfo1C::SyncDetails(TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName)
{
    SyncDetailsLinnCoUkInfo1C sync(*this, aaDuration, aaBitRate, aaBitDepth, aaSampleRate, aaLossless, aaCodecName);
    BeginDetails(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1C::BeginDetails(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDetails, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDetails->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkInfo1C::EndDetails(IAsync& aAsync, TUint& aaDuration, TUint& aaBitRate, TUint& aaBitDepth, TUint& aaSampleRate, TBool& aaLossless, Brh& aaCodecName)
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

void CpProxyLinnCoUkInfo1C::SyncMetatext(Brh& aaMetatext)
{
    SyncMetatextLinnCoUkInfo1C sync(*this, aaMetatext);
    BeginMetatext(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkInfo1C::BeginMetatext(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMetatext, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetatext->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkInfo1C::EndMetatext(IAsync& aAsync, Brh& aaMetatext)
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

void CpProxyLinnCoUkInfo1C::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyDetailsCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDetailsCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyMetatextCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetatextCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock.Wait();
    iUriChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetadataChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDurationChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyBitRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBitRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyBitDepthChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBitDepthChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertySampleRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSampleRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyLosslessChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLosslessChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyCodecNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iCodecNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::SetPropertyMetatextChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetatextChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkInfo1C::PropertyTrackCount(TUint& aTrackCount) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aTrackCount = iTrackCount->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyDetailsCount(TUint& aDetailsCount) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aDetailsCount = iDetailsCount->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyMetatextCount(TUint& aMetatextCount) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aMetatextCount = iMetatextCount->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyUri(Brhz& aUri) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aUri.Set(iUri->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyMetadata(Brhz& aMetadata) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aMetadata.Set(iMetadata->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyDuration(TUint& aDuration) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aDuration = iDuration->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyBitRate(TUint& aBitRate) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aBitRate = iBitRate->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyBitDepth(TUint& aBitDepth) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aBitDepth = iBitDepth->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertySampleRate(TUint& aSampleRate) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aSampleRate = iSampleRate->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyLossless(TBool& aLossless) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aLossless = iLossless->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyCodecName(Brhz& aCodecName) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aCodecName.Set(iCodecName->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::PropertyMetatext(Brhz& aMetatext) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aMetatext.Set(iMetatext->Value());
    PropertyReadUnlock();
}

void CpProxyLinnCoUkInfo1C::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyLinnCoUkInfo1C::DetailsCountPropertyChanged()
{
    ReportEvent(iDetailsCountChanged);
}

void CpProxyLinnCoUkInfo1C::MetatextCountPropertyChanged()
{
    ReportEvent(iMetatextCountChanged);
}

void CpProxyLinnCoUkInfo1C::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyLinnCoUkInfo1C::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyLinnCoUkInfo1C::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyLinnCoUkInfo1C::BitRatePropertyChanged()
{
    ReportEvent(iBitRateChanged);
}

void CpProxyLinnCoUkInfo1C::BitDepthPropertyChanged()
{
    ReportEvent(iBitDepthChanged);
}

void CpProxyLinnCoUkInfo1C::SampleRatePropertyChanged()
{
    ReportEvent(iSampleRateChanged);
}

void CpProxyLinnCoUkInfo1C::LosslessPropertyChanged()
{
    ReportEvent(iLosslessChanged);
}

void CpProxyLinnCoUkInfo1C::CodecNamePropertyChanged()
{
    ReportEvent(iCodecNameChanged);
}

void CpProxyLinnCoUkInfo1C::MetatextPropertyChanged()
{
    ReportEvent(iMetatextChanged);
}


THandle CpProxyLinnCoUkInfo1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkInfo1C(aDevice);
}

void CpProxyLinnCoUkInfo1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkInfo1SyncCounters(THandle aHandle, uint32_t* aaTrackCount, uint32_t* aaDetailsCount, uint32_t* aaMetatextCount)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncCounters(*aaTrackCount, *aaDetailsCount, *aaMetatextCount);
}

void CpProxyLinnCoUkInfo1BeginCounters(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginCounters(functor);
}

int32_t CpProxyLinnCoUkInfo1EndCounters(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaTrackCount, uint32_t* aaDetailsCount, uint32_t* aaMetatextCount)
{
    int32_t err = 0;
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndCounters(*async, *aaTrackCount, *aaDetailsCount, *aaMetatextCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkInfo1SyncTrack(THandle aHandle, char** aaUri, char** aaMetadata)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUri;
    Brh buf_aaMetadata;
    proxyC->SyncTrack(buf_aaUri, buf_aaMetadata);
    *aaUri = buf_aaUri.Extract();
    *aaMetadata = buf_aaMetadata.Extract();
}

void CpProxyLinnCoUkInfo1BeginTrack(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginTrack(functor);
}

int32_t CpProxyLinnCoUkInfo1EndTrack(THandle aHandle, ZappHandleAsync aAsync, char** aaUri, char** aaMetadata)
{
    int32_t err = 0;
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUri;
    *aaUri = NULL;
    Brh buf_aaMetadata;
    *aaMetadata = NULL;
    try {
        proxyC->EndTrack(*async, buf_aaUri, buf_aaMetadata);
        *aaUri = buf_aaUri.Extract();
        *aaMetadata = buf_aaMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkInfo1SyncDetails(THandle aHandle, uint32_t* aaDuration, uint32_t* aaBitRate, uint32_t* aaBitDepth, uint32_t* aaSampleRate, uint32_t* aaLossless, char** aaCodecName)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaLossless = 0;
    Brh buf_aaCodecName;
    proxyC->SyncDetails(*aaDuration, *aaBitRate, *aaBitDepth, *aaSampleRate, *(TBool*)aaLossless, buf_aaCodecName);
    *aaCodecName = buf_aaCodecName.Extract();
}

void CpProxyLinnCoUkInfo1BeginDetails(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDetails(functor);
}

int32_t CpProxyLinnCoUkInfo1EndDetails(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDuration, uint32_t* aaBitRate, uint32_t* aaBitDepth, uint32_t* aaSampleRate, uint32_t* aaLossless, char** aaCodecName)
{
    int32_t err = 0;
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaLossless = 0;
    Brh buf_aaCodecName;
    *aaCodecName = NULL;
    try {
        proxyC->EndDetails(*async, *aaDuration, *aaBitRate, *aaBitDepth, *aaSampleRate, *(TBool*)aaLossless, buf_aaCodecName);
        *aaCodecName = buf_aaCodecName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkInfo1SyncMetatext(THandle aHandle, char** aaMetatext)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMetatext;
    proxyC->SyncMetatext(buf_aaMetatext);
    *aaMetatext = buf_aaMetatext.Extract();
}

void CpProxyLinnCoUkInfo1BeginMetatext(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginMetatext(functor);
}

int32_t CpProxyLinnCoUkInfo1EndMetatext(THandle aHandle, ZappHandleAsync aAsync, char** aaMetatext)
{
    int32_t err = 0;
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMetatext;
    *aaMetatext = NULL;
    try {
        proxyC->EndMetatext(*async, buf_aaMetatext);
        *aaMetatext = buf_aaMetatext.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkInfo1SetPropertyTrackCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackCountChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyDetailsCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDetailsCountChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyMetatextCountChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetatextCountChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyUriChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyUriChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyMetadataChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetadataChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDurationChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyBitRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBitRateChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyBitDepthChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBitDepthChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertySampleRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySampleRateChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyLosslessChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLosslessChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyCodecNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyCodecNameChanged(functor);
}

void CpProxyLinnCoUkInfo1SetPropertyMetatextChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetatextChanged(functor);
}

void CpProxyLinnCoUkInfo1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackCount(*aTrackCount);
}

void CpProxyLinnCoUkInfo1PropertyDetailsCount(THandle aHandle, uint32_t* aDetailsCount)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDetailsCount(*aDetailsCount);
}

void CpProxyLinnCoUkInfo1PropertyMetatextCount(THandle aHandle, uint32_t* aMetatextCount)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyMetatextCount(*aMetatextCount);
}

void CpProxyLinnCoUkInfo1PropertyUri(THandle aHandle, char** aUri)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aUri;
    proxyC->PropertyUri(buf_aUri);
    *aUri = buf_aUri.Transfer();
}

void CpProxyLinnCoUkInfo1PropertyMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetadata;
    proxyC->PropertyMetadata(buf_aMetadata);
    *aMetadata = buf_aMetadata.Transfer();
}

void CpProxyLinnCoUkInfo1PropertyDuration(THandle aHandle, uint32_t* aDuration)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDuration(*aDuration);
}

void CpProxyLinnCoUkInfo1PropertyBitRate(THandle aHandle, uint32_t* aBitRate)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBitRate(*aBitRate);
}

void CpProxyLinnCoUkInfo1PropertyBitDepth(THandle aHandle, uint32_t* aBitDepth)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBitDepth(*aBitDepth);
}

void CpProxyLinnCoUkInfo1PropertySampleRate(THandle aHandle, uint32_t* aSampleRate)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySampleRate(*aSampleRate);
}

void CpProxyLinnCoUkInfo1PropertyLossless(THandle aHandle, uint32_t* aLossless)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aLossless = false;
    proxyC->PropertyLossless(*(TBool*)aLossless);
}

void CpProxyLinnCoUkInfo1PropertyCodecName(THandle aHandle, char** aCodecName)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aCodecName;
    proxyC->PropertyCodecName(buf_aCodecName);
    *aCodecName = buf_aCodecName.Transfer();
}

void CpProxyLinnCoUkInfo1PropertyMetatext(THandle aHandle, char** aMetatext)
{
    CpProxyLinnCoUkInfo1C* proxyC = reinterpret_cast<CpProxyLinnCoUkInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetatext;
    proxyC->PropertyMetatext(buf_aMetatext);
    *aMetatext = buf_aMetatext.Transfer();
}

