#include "CpAvOpenhomeOrgInfo1.h"
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/C/CpProxyCPrivate.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Private/CpiDevice.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class CpProxyAvOpenhomeOrgInfo1C : public CpProxyC
{
public:
    CpProxyAvOpenhomeOrgInfo1C(CpDeviceC aDevice);
    ~CpProxyAvOpenhomeOrgInfo1C();
    //CpProxyAvOpenhomeOrgInfo1* Proxy() { return static_cast<CpProxyAvOpenhomeOrgInfo1*>(iProxy); }

    void SyncCounters(TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount);
    void BeginCounters(FunctorAsync& aFunctor);
    void EndCounters(IAsync& aAsync, TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount);

    void SyncTrack(Brh& aUri, Brh& aMetadata);
    void BeginTrack(FunctorAsync& aFunctor);
    void EndTrack(IAsync& aAsync, Brh& aUri, Brh& aMetadata);

    void SyncDetails(TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName);
    void BeginDetails(FunctorAsync& aFunctor);
    void EndDetails(IAsync& aAsync, TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName);

    void SyncMetatext(Brh& aValue);
    void BeginMetatext(FunctorAsync& aFunctor);
    void EndMetatext(IAsync& aAsync, Brh& aValue);

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


class SyncCountersAvOpenhomeOrgInfo1C : public SyncProxyAction
{
public:
    SyncCountersAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncCountersAvOpenhomeOrgInfo1C() {};
private:
    CpProxyAvOpenhomeOrgInfo1C& iService;
    TUint& iTrackCount;
    TUint& iDetailsCount;
    TUint& iMetatextCount;
};

SyncCountersAvOpenhomeOrgInfo1C::SyncCountersAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount)
    : iService(aProxy)
    , iTrackCount(aTrackCount)
    , iDetailsCount(aDetailsCount)
    , iMetatextCount(aMetatextCount)
{
}

void SyncCountersAvOpenhomeOrgInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCounters(aAsync, iTrackCount, iDetailsCount, iMetatextCount);
}


class SyncTrackAvOpenhomeOrgInfo1C : public SyncProxyAction
{
public:
    SyncTrackAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, Brh& aUri, Brh& aMetadata);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncTrackAvOpenhomeOrgInfo1C() {};
private:
    CpProxyAvOpenhomeOrgInfo1C& iService;
    Brh& iUri;
    Brh& iMetadata;
};

SyncTrackAvOpenhomeOrgInfo1C::SyncTrackAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, Brh& aUri, Brh& aMetadata)
    : iService(aProxy)
    , iUri(aUri)
    , iMetadata(aMetadata)
{
}

void SyncTrackAvOpenhomeOrgInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndTrack(aAsync, iUri, iMetadata);
}


class SyncDetailsAvOpenhomeOrgInfo1C : public SyncProxyAction
{
public:
    SyncDetailsAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncDetailsAvOpenhomeOrgInfo1C() {};
private:
    CpProxyAvOpenhomeOrgInfo1C& iService;
    TUint& iDuration;
    TUint& iBitRate;
    TUint& iBitDepth;
    TUint& iSampleRate;
    TBool& iLossless;
    Brh& iCodecName;
};

SyncDetailsAvOpenhomeOrgInfo1C::SyncDetailsAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName)
    : iService(aProxy)
    , iDuration(aDuration)
    , iBitRate(aBitRate)
    , iBitDepth(aBitDepth)
    , iSampleRate(aSampleRate)
    , iLossless(aLossless)
    , iCodecName(aCodecName)
{
}

void SyncDetailsAvOpenhomeOrgInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDetails(aAsync, iDuration, iBitRate, iBitDepth, iSampleRate, iLossless, iCodecName);
}


class SyncMetatextAvOpenhomeOrgInfo1C : public SyncProxyAction
{
public:
    SyncMetatextAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, Brh& aValue);
    virtual void CompleteRequest(IAsync& aAsync);
    virtual ~SyncMetatextAvOpenhomeOrgInfo1C() {};
private:
    CpProxyAvOpenhomeOrgInfo1C& iService;
    Brh& iValue;
};

SyncMetatextAvOpenhomeOrgInfo1C::SyncMetatextAvOpenhomeOrgInfo1C(CpProxyAvOpenhomeOrgInfo1C& aProxy, Brh& aValue)
    : iService(aProxy)
    , iValue(aValue)
{
}

void SyncMetatextAvOpenhomeOrgInfo1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndMetatext(aAsync, iValue);
}

CpProxyAvOpenhomeOrgInfo1C::CpProxyAvOpenhomeOrgInfo1C(CpDeviceC aDevice)
    : CpProxyC("av-openhome-org", "Info", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
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
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::TrackCountPropertyChanged);
    iTrackCount = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "TrackCount", functor);
    AddProperty(iTrackCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::DetailsCountPropertyChanged);
    iDetailsCount = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "DetailsCount", functor);
    AddProperty(iDetailsCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::MetatextCountPropertyChanged);
    iMetatextCount = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "MetatextCount", functor);
    AddProperty(iMetatextCount);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::UriPropertyChanged);
    iUri = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Uri", functor);
    AddProperty(iUri);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::MetadataPropertyChanged);
    iMetadata = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Metadata", functor);
    AddProperty(iMetadata);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::DurationPropertyChanged);
    iDuration = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Duration", functor);
    AddProperty(iDuration);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::BitRatePropertyChanged);
    iBitRate = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "BitRate", functor);
    AddProperty(iBitRate);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::BitDepthPropertyChanged);
    iBitDepth = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "BitDepth", functor);
    AddProperty(iBitDepth);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::SampleRatePropertyChanged);
    iSampleRate = new PropertyUint(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "SampleRate", functor);
    AddProperty(iSampleRate);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::LosslessPropertyChanged);
    iLossless = new PropertyBool(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Lossless", functor);
    AddProperty(iLossless);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::CodecNamePropertyChanged);
    iCodecName = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "CodecName", functor);
    AddProperty(iCodecName);
    functor = MakeFunctor(*this, &CpProxyAvOpenhomeOrgInfo1C::MetatextPropertyChanged);
    iMetatext = new PropertyString(reinterpret_cast<CpiDevice*>(aDevice)->GetCpStack().Env(), "Metatext", functor);
    AddProperty(iMetatext);
}

CpProxyAvOpenhomeOrgInfo1C::~CpProxyAvOpenhomeOrgInfo1C()
{
    DestroyService();
    delete iActionCounters;
    delete iActionTrack;
    delete iActionDetails;
    delete iActionMetatext;
}

void CpProxyAvOpenhomeOrgInfo1C::SyncCounters(TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount)
{
    SyncCountersAvOpenhomeOrgInfo1C sync(*this, aTrackCount, aDetailsCount, aMetatextCount);
    BeginCounters(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1C::BeginCounters(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCounters, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCounters->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1C::EndCounters(IAsync& aAsync, TUint& aTrackCount, TUint& aDetailsCount, TUint& aMetatextCount)
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

void CpProxyAvOpenhomeOrgInfo1C::SyncTrack(Brh& aUri, Brh& aMetadata)
{
    SyncTrackAvOpenhomeOrgInfo1C sync(*this, aUri, aMetadata);
    BeginTrack(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1C::BeginTrack(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionTrack, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionTrack->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1C::EndTrack(IAsync& aAsync, Brh& aUri, Brh& aMetadata)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aUri);
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aMetadata);
}

void CpProxyAvOpenhomeOrgInfo1C::SyncDetails(TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName)
{
    SyncDetailsAvOpenhomeOrgInfo1C sync(*this, aDuration, aBitRate, aBitDepth, aSampleRate, aLossless, aCodecName);
    BeginDetails(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1C::BeginDetails(FunctorAsync& aFunctor)
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

void CpProxyAvOpenhomeOrgInfo1C::EndDetails(IAsync& aAsync, TUint& aDuration, TUint& aBitRate, TUint& aBitDepth, TUint& aSampleRate, TBool& aLossless, Brh& aCodecName)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aCodecName);
}

void CpProxyAvOpenhomeOrgInfo1C::SyncMetatext(Brh& aValue)
{
    SyncMetatextAvOpenhomeOrgInfo1C sync(*this, aValue);
    BeginMetatext(sync.Functor());
    sync.Wait();
}

void CpProxyAvOpenhomeOrgInfo1C::BeginMetatext(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionMetatext, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionMetatext->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyAvOpenhomeOrgInfo1C::EndMetatext(IAsync& aAsync, Brh& aValue)
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
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aValue);
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyTrackCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyDetailsCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDetailsCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyMetatextCountChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetatextCountChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyUriChanged(Functor& aFunctor)
{
    iLock.Wait();
    iUriChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyMetadataChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetadataChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyDurationChanged(Functor& aFunctor)
{
    iLock.Wait();
    iDurationChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyBitRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBitRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyBitDepthChanged(Functor& aFunctor)
{
    iLock.Wait();
    iBitDepthChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertySampleRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSampleRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyLosslessChanged(Functor& aFunctor)
{
    iLock.Wait();
    iLosslessChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyCodecNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iCodecNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::SetPropertyMetatextChanged(Functor& aFunctor)
{
    iLock.Wait();
    iMetatextChanged = aFunctor;
    iLock.Signal();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyTrackCount(TUint& aTrackCount) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aTrackCount = iTrackCount->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyDetailsCount(TUint& aDetailsCount) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aDetailsCount = iDetailsCount->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyMetatextCount(TUint& aMetatextCount) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aMetatextCount = iMetatextCount->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyUri(Brhz& aUri) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aUri.Set(iUri->Value());
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyMetadata(Brhz& aMetadata) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aMetadata.Set(iMetadata->Value());
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyDuration(TUint& aDuration) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aDuration = iDuration->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyBitRate(TUint& aBitRate) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aBitRate = iBitRate->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyBitDepth(TUint& aBitDepth) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aBitDepth = iBitDepth->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertySampleRate(TUint& aSampleRate) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aSampleRate = iSampleRate->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyLossless(TBool& aLossless) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aLossless = iLossless->Value();
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyCodecName(Brhz& aCodecName) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aCodecName.Set(iCodecName->Value());
}

void CpProxyAvOpenhomeOrgInfo1C::PropertyMetatext(Brhz& aMetatext) const
{
    AutoMutex a(GetPropertyReadLock());
    ASSERT(IsSubscribed());
    aMetatext.Set(iMetatext->Value());
}

void CpProxyAvOpenhomeOrgInfo1C::TrackCountPropertyChanged()
{
    ReportEvent(iTrackCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::DetailsCountPropertyChanged()
{
    ReportEvent(iDetailsCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::MetatextCountPropertyChanged()
{
    ReportEvent(iMetatextCountChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::UriPropertyChanged()
{
    ReportEvent(iUriChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::MetadataPropertyChanged()
{
    ReportEvent(iMetadataChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::DurationPropertyChanged()
{
    ReportEvent(iDurationChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::BitRatePropertyChanged()
{
    ReportEvent(iBitRateChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::BitDepthPropertyChanged()
{
    ReportEvent(iBitDepthChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::SampleRatePropertyChanged()
{
    ReportEvent(iSampleRateChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::LosslessPropertyChanged()
{
    ReportEvent(iLosslessChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::CodecNamePropertyChanged()
{
    ReportEvent(iCodecNameChanged);
}

void CpProxyAvOpenhomeOrgInfo1C::MetatextPropertyChanged()
{
    ReportEvent(iMetatextChanged);
}


THandle STDCALL CpProxyAvOpenhomeOrgInfo1Create(CpDeviceC aDevice)
{
    return new CpProxyAvOpenhomeOrgInfo1C(aDevice);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1Destroy(THandle aHandle)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    delete proxyC;
}

int32_t STDCALL CpProxyAvOpenhomeOrgInfo1SyncCounters(THandle aHandle, uint32_t* aTrackCount, uint32_t* aDetailsCount, uint32_t* aMetatextCount)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    int32_t err = 0;
    try {
        proxyC->SyncCounters(*aTrackCount, *aDetailsCount, *aMetatextCount);
    }
    catch (ProxyError& ) {
        err = -1;
        *aTrackCount = 0;
        *aDetailsCount = 0;
        *aMetatextCount = 0;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgInfo1BeginCounters(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginCounters(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgInfo1EndCounters(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aTrackCount, uint32_t* aDetailsCount, uint32_t* aMetatextCount)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndCounters(*async, *aTrackCount, *aDetailsCount, *aMetatextCount);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgInfo1SyncTrack(THandle aHandle, char** aUri, char** aMetadata)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUri;
    Brh buf_aMetadata;
    int32_t err = 0;
    try {
        proxyC->SyncTrack(buf_aUri, buf_aMetadata);
        *aUri = buf_aUri.Extract();
        *aMetadata = buf_aMetadata.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aUri = NULL;
        *aMetadata = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgInfo1BeginTrack(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginTrack(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgInfo1EndTrack(THandle aHandle, OhNetHandleAsync aAsync, char** aUri, char** aMetadata)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aUri;
    *aUri = NULL;
    Brh buf_aMetadata;
    *aMetadata = NULL;
    try {
        proxyC->EndTrack(*async, buf_aUri, buf_aMetadata);
        *aUri = buf_aUri.Extract();
        *aMetadata = buf_aMetadata.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgInfo1SyncDetails(THandle aHandle, uint32_t* aDuration, uint32_t* aBitRate, uint32_t* aBitDepth, uint32_t* aSampleRate, uint32_t* aLossless, char** aCodecName)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Lossless;
    Brh buf_aCodecName;
    int32_t err = 0;
    try {
        proxyC->SyncDetails(*aDuration, *aBitRate, *aBitDepth, *aSampleRate, Lossless, buf_aCodecName);
        *aLossless = Lossless? 1 : 0;
        *aCodecName = buf_aCodecName.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aDuration = 0;
        *aBitRate = 0;
        *aBitDepth = 0;
        *aSampleRate = 0;
        *aLossless = false;
        *aCodecName = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgInfo1BeginDetails(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginDetails(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgInfo1EndDetails(THandle aHandle, OhNetHandleAsync aAsync, uint32_t* aDuration, uint32_t* aBitRate, uint32_t* aBitDepth, uint32_t* aSampleRate, uint32_t* aLossless, char** aCodecName)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    TBool Lossless;
    Brh buf_aCodecName;
    *aCodecName = NULL;
    try {
        proxyC->EndDetails(*async, *aDuration, *aBitRate, *aBitDepth, *aSampleRate, Lossless, buf_aCodecName);
        *aLossless = Lossless? 1 : 0;
        *aCodecName = buf_aCodecName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

int32_t STDCALL CpProxyAvOpenhomeOrgInfo1SyncMetatext(THandle aHandle, char** aValue)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    int32_t err = 0;
    try {
        proxyC->SyncMetatext(buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch (ProxyError& ) {
        err = -1;
        *aValue = NULL;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgInfo1BeginMetatext(THandle aHandle, OhNetCallbackAsync aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (OhNetFunctorAsync)aCallback);
    proxyC->BeginMetatext(functor);
}

int32_t STDCALL CpProxyAvOpenhomeOrgInfo1EndMetatext(THandle aHandle, OhNetHandleAsync aAsync, char** aValue)
{
    int32_t err = 0;
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValue;
    *aValue = NULL;
    try {
        proxyC->EndMetatext(*async, buf_aValue);
        *aValue = buf_aValue.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyTrackCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackCountChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyDetailsCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDetailsCountChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyMetatextCountChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetatextCountChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyUriChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyUriChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyMetadataChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetadataChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyDurationChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyDurationChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyBitRateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBitRateChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyBitDepthChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyBitDepthChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertySampleRateChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySampleRateChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyLosslessChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyLosslessChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyCodecNameChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyCodecNameChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1SetPropertyMetatextChanged(THandle aHandle, OhNetCallback aCallback, void* aPtr)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyMetatextChanged(functor);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyTrackCount(THandle aHandle, uint32_t* aTrackCount)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackCount(*aTrackCount);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyDetailsCount(THandle aHandle, uint32_t* aDetailsCount)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDetailsCount(*aDetailsCount);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyMetatextCount(THandle aHandle, uint32_t* aMetatextCount)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyMetatextCount(*aMetatextCount);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyUri(THandle aHandle, char** aUri)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aUri;
    proxyC->PropertyUri(buf_aUri);
    *aUri = buf_aUri.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyMetadata(THandle aHandle, char** aMetadata)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetadata;
    proxyC->PropertyMetadata(buf_aMetadata);
    *aMetadata = buf_aMetadata.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyDuration(THandle aHandle, uint32_t* aDuration)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyDuration(*aDuration);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyBitRate(THandle aHandle, uint32_t* aBitRate)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBitRate(*aBitRate);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyBitDepth(THandle aHandle, uint32_t* aBitDepth)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyBitDepth(*aBitDepth);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertySampleRate(THandle aHandle, uint32_t* aSampleRate)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertySampleRate(*aSampleRate);
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyLossless(THandle aHandle, uint32_t* aLossless)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    TBool Lossless;
    proxyC->PropertyLossless(Lossless);
    *aLossless = Lossless? 1 : 0;
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyCodecName(THandle aHandle, char** aCodecName)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aCodecName;
    proxyC->PropertyCodecName(buf_aCodecName);
    *aCodecName = buf_aCodecName.Transfer();
}

void STDCALL CpProxyAvOpenhomeOrgInfo1PropertyMetatext(THandle aHandle, char** aMetatext)
{
    CpProxyAvOpenhomeOrgInfo1C* proxyC = reinterpret_cast<CpProxyAvOpenhomeOrgInfo1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aMetatext;
    proxyC->PropertyMetatext(buf_aMetatext);
    *aMetatext = buf_aMetatext.Transfer();
}

