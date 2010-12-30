#include "CpLinnCoUkDs1.h"
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

class CpProxyLinnCoUkDs1C : public CpProxyC
{
public:
    CpProxyLinnCoUkDs1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkDs1C();
    //CpProxyLinnCoUkDs1* Proxy() { return static_cast<CpProxyLinnCoUkDs1*>(iProxy); }

    void SyncPlay();
    void BeginPlay(FunctorAsync& aFunctor);
    void EndPlay(IAsync& aAsync);

    void SyncPause();
    void BeginPause(FunctorAsync& aFunctor);
    void EndPause(IAsync& aAsync);

    void SyncStop();
    void BeginStop(FunctorAsync& aFunctor);
    void EndStop(IAsync& aAsync);

    void SyncSeekSecondAbsolute(TUint aaSecond);
    void BeginSeekSecondAbsolute(TUint aaSecond, FunctorAsync& aFunctor);
    void EndSeekSecondAbsolute(IAsync& aAsync);

    void SyncSeekSecondRelative(TInt aaSecond);
    void BeginSeekSecondRelative(TInt aaSecond, FunctorAsync& aFunctor);
    void EndSeekSecondRelative(IAsync& aAsync);

    void SyncSeekTrackId(TUint aaTrackId);
    void BeginSeekTrackId(TUint aaTrackId, FunctorAsync& aFunctor);
    void EndSeekTrackId(IAsync& aAsync);

    void SyncSeekTrackAbsolute(TUint aaTrack);
    void BeginSeekTrackAbsolute(TUint aaTrack, FunctorAsync& aFunctor);
    void EndSeekTrackAbsolute(IAsync& aAsync);

    void SyncSeekTrackRelative(TInt aaTrack);
    void BeginSeekTrackRelative(TInt aaTrack, FunctorAsync& aFunctor);
    void EndSeekTrackRelative(IAsync& aAsync);

    void SyncState(Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId);
    void BeginState(FunctorAsync& aFunctor);
    void EndState(IAsync& aAsync, Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId);

    void SyncProtocolInfo(Brh& aaSupportedProtocols);
    void BeginProtocolInfo(FunctorAsync& aFunctor);
    void EndProtocolInfo(IAsync& aAsync, Brh& aaSupportedProtocols);

    void SetPropertySupportedProtocolsChanged(Functor& aFunctor);
    void SetPropertyTrackDurationChanged(Functor& aFunctor);
    void SetPropertyTrackBitRateChanged(Functor& aFunctor);
    void SetPropertyTrackLosslessChanged(Functor& aFunctor);
    void SetPropertyTrackBitDepthChanged(Functor& aFunctor);
    void SetPropertyTrackSampleRateChanged(Functor& aFunctor);
    void SetPropertyTrackCodecNameChanged(Functor& aFunctor);
    void SetPropertyTrackIdChanged(Functor& aFunctor);
    void SetPropertyTransportStateChanged(Functor& aFunctor);

    void PropertySupportedProtocols(Brhz& aSupportedProtocols) const;
    void PropertyTrackDuration(TUint& aTrackDuration) const;
    void PropertyTrackBitRate(TUint& aTrackBitRate) const;
    void PropertyTrackLossless(TBool& aTrackLossless) const;
    void PropertyTrackBitDepth(TUint& aTrackBitDepth) const;
    void PropertyTrackSampleRate(TUint& aTrackSampleRate) const;
    void PropertyTrackCodecName(Brhz& aTrackCodecName) const;
    void PropertyTrackId(TUint& aTrackId) const;
    void PropertyTransportState(Brhz& aTransportState) const;
private:
    void SupportedProtocolsPropertyChanged();
    void TrackDurationPropertyChanged();
    void TrackBitRatePropertyChanged();
    void TrackLosslessPropertyChanged();
    void TrackBitDepthPropertyChanged();
    void TrackSampleRatePropertyChanged();
    void TrackCodecNamePropertyChanged();
    void TrackIdPropertyChanged();
    void TransportStatePropertyChanged();
private:
    Mutex iLock;
    mutable Mutex iPropertyLock;
    Action* iActionPlay;
    Action* iActionPause;
    Action* iActionStop;
    Action* iActionSeekSecondAbsolute;
    Action* iActionSeekSecondRelative;
    Action* iActionSeekTrackId;
    Action* iActionSeekTrackAbsolute;
    Action* iActionSeekTrackRelative;
    Action* iActionState;
    Action* iActionProtocolInfo;
    PropertyString* iSupportedProtocols;
    PropertyUint* iTrackDuration;
    PropertyUint* iTrackBitRate;
    PropertyBool* iTrackLossless;
    PropertyUint* iTrackBitDepth;
    PropertyUint* iTrackSampleRate;
    PropertyString* iTrackCodecName;
    PropertyUint* iTrackId;
    PropertyString* iTransportState;
    Functor iSupportedProtocolsChanged;
    Functor iTrackDurationChanged;
    Functor iTrackBitRateChanged;
    Functor iTrackLosslessChanged;
    Functor iTrackBitDepthChanged;
    Functor iTrackSampleRateChanged;
    Functor iTrackCodecNameChanged;
    Functor iTrackIdChanged;
    Functor iTransportStateChanged;
};


class SyncPlayLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncPlayLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
};

SyncPlayLinnCoUkDs1C::SyncPlayLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy)
    : iService(aProxy)
{
}

void SyncPlayLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncPauseLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
};

SyncPauseLinnCoUkDs1C::SyncPauseLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy)
    : iService(aProxy)
{
}

void SyncPauseLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncStopLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
};

SyncStopLinnCoUkDs1C::SyncStopLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy)
    : iService(aProxy)
{
}

void SyncStopLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
};

SyncSeekSecondAbsoluteLinnCoUkDs1C::SyncSeekSecondAbsoluteLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondAbsoluteLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
};

SyncSeekSecondRelativeLinnCoUkDs1C::SyncSeekSecondRelativeLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondRelativeLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncSeekTrackIdLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncSeekTrackIdLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
};

SyncSeekTrackIdLinnCoUkDs1C::SyncSeekTrackIdLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekTrackIdLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackId(aAsync);
}


class SyncSeekTrackAbsoluteLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncSeekTrackAbsoluteLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
};

SyncSeekTrackAbsoluteLinnCoUkDs1C::SyncSeekTrackAbsoluteLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekTrackAbsoluteLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackAbsolute(aAsync);
}


class SyncSeekTrackRelativeLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncSeekTrackRelativeLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
};

SyncSeekTrackRelativeLinnCoUkDs1C::SyncSeekTrackRelativeLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy)
    : iService(aProxy)
{
}

void SyncSeekTrackRelativeLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackRelative(aAsync);
}


class SyncStateLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncStateLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy, Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
    Brh& iaTransportState;
    TUint& iaTrackDuration;
    TUint& iaTrackBitRate;
    TBool& iaTrackLossless;
    TUint& iaTrackBitDepth;
    TUint& iaTrackSampleRate;
    Brh& iaTrackCodecName;
    TUint& iaTrackId;
};

SyncStateLinnCoUkDs1C::SyncStateLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy, Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId)
    : iService(aProxy)
    , iaTransportState(aaTransportState)
    , iaTrackDuration(aaTrackDuration)
    , iaTrackBitRate(aaTrackBitRate)
    , iaTrackLossless(aaTrackLossless)
    , iaTrackBitDepth(aaTrackBitDepth)
    , iaTrackSampleRate(aaTrackSampleRate)
    , iaTrackCodecName(aaTrackCodecName)
    , iaTrackId(aaTrackId)
{
}

void SyncStateLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndState(aAsync, iaTransportState, iaTrackDuration, iaTrackBitRate, iaTrackLossless, iaTrackBitDepth, iaTrackSampleRate, iaTrackCodecName, iaTrackId);
}


class SyncProtocolInfoLinnCoUkDs1C : public SyncProxyAction
{
public:
    SyncProtocolInfoLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy, Brh& aaSupportedProtocols);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1C& iService;
    Brh& iaSupportedProtocols;
};

SyncProtocolInfoLinnCoUkDs1C::SyncProtocolInfoLinnCoUkDs1C(CpProxyLinnCoUkDs1C& aProxy, Brh& aaSupportedProtocols)
    : iService(aProxy)
    , iaSupportedProtocols(aaSupportedProtocols)
{
}

void SyncProtocolInfoLinnCoUkDs1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iaSupportedProtocols);
}

CpProxyLinnCoUkDs1C::CpProxyLinnCoUkDs1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Ds", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
    , iPropertyLock("MPCP")
{
    Zapp::Parameter* param;
    TChar** allowedValues;
    TUint index;

    iActionPlay = new Action("Play");

    iActionPause = new Action("Pause");

    iActionStop = new Action("Stop");

    iActionSeekSecondAbsolute = new Action("SeekSecondAbsolute");
    param = new Zapp::ParameterUint("aSecond");
    iActionSeekSecondAbsolute->AddInputParameter(param);

    iActionSeekSecondRelative = new Action("SeekSecondRelative");
    param = new Zapp::ParameterInt("aSecond");
    iActionSeekSecondRelative->AddInputParameter(param);

    iActionSeekTrackId = new Action("SeekTrackId");
    param = new Zapp::ParameterUint("aTrackId");
    iActionSeekTrackId->AddInputParameter(param);

    iActionSeekTrackAbsolute = new Action("SeekTrackAbsolute");
    param = new Zapp::ParameterUint("aTrack");
    iActionSeekTrackAbsolute->AddInputParameter(param);

    iActionSeekTrackRelative = new Action("SeekTrackRelative");
    param = new Zapp::ParameterInt("aTrack");
    iActionSeekTrackRelative->AddInputParameter(param);

    iActionState = new Action("State");
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"Playing";
    allowedValues[index++] = (TChar*)"Paused";
    allowedValues[index++] = (TChar*)"Stopped";
    allowedValues[index++] = (TChar*)"Buffering";
    param = new Zapp::ParameterString("aTransportState", allowedValues, 4);
    iActionState->AddOutputParameter(param);
    delete[] allowedValues;
    param = new Zapp::ParameterUint("aTrackDuration");
    iActionState->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aTrackBitRate");
    iActionState->AddOutputParameter(param);
    param = new Zapp::ParameterBool("aTrackLossless");
    iActionState->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aTrackBitDepth");
    iActionState->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aTrackSampleRate");
    iActionState->AddOutputParameter(param);
    param = new Zapp::ParameterString("aTrackCodecName");
    iActionState->AddOutputParameter(param);
    param = new Zapp::ParameterUint("aTrackId");
    iActionState->AddOutputParameter(param);

    iActionProtocolInfo = new Action("ProtocolInfo");
    param = new Zapp::ParameterString("aSupportedProtocols");
    iActionProtocolInfo->AddOutputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::SupportedProtocolsPropertyChanged);
    iSupportedProtocols = new PropertyString("SupportedProtocols", functor);
    AddProperty(iSupportedProtocols);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::TrackDurationPropertyChanged);
    iTrackDuration = new PropertyUint("TrackDuration", functor);
    AddProperty(iTrackDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::TrackBitRatePropertyChanged);
    iTrackBitRate = new PropertyUint("TrackBitRate", functor);
    AddProperty(iTrackBitRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::TrackLosslessPropertyChanged);
    iTrackLossless = new PropertyBool("TrackLossless", functor);
    AddProperty(iTrackLossless);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::TrackBitDepthPropertyChanged);
    iTrackBitDepth = new PropertyUint("TrackBitDepth", functor);
    AddProperty(iTrackBitDepth);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::TrackSampleRatePropertyChanged);
    iTrackSampleRate = new PropertyUint("TrackSampleRate", functor);
    AddProperty(iTrackSampleRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::TrackCodecNamePropertyChanged);
    iTrackCodecName = new PropertyString("TrackCodecName", functor);
    AddProperty(iTrackCodecName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::TrackIdPropertyChanged);
    iTrackId = new PropertyUint("TrackId", functor);
    AddProperty(iTrackId);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1C::TransportStatePropertyChanged);
    iTransportState = new PropertyString("TransportState", functor);
    AddProperty(iTransportState);
}

CpProxyLinnCoUkDs1C::~CpProxyLinnCoUkDs1C()
{
    DestroyService();
    delete iActionPlay;
    delete iActionPause;
    delete iActionStop;
    delete iActionSeekSecondAbsolute;
    delete iActionSeekSecondRelative;
    delete iActionSeekTrackId;
    delete iActionSeekTrackAbsolute;
    delete iActionSeekTrackRelative;
    delete iActionState;
    delete iActionProtocolInfo;
}

void CpProxyLinnCoUkDs1C::SyncPlay()
{
    SyncPlayLinnCoUkDs1C sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPlay, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1C::SyncPause()
{
    SyncPauseLinnCoUkDs1C sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionPause, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1C::SyncStop()
{
    SyncStopLinnCoUkDs1C sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStop, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1C::SyncSeekSecondAbsolute(TUint aaSecond)
{
    SyncSeekSecondAbsoluteLinnCoUkDs1C sync(*this);
    BeginSeekSecondAbsolute(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginSeekSecondAbsolute(TUint aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSecond));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1C::SyncSeekSecondRelative(TInt aaSecond)
{
    SyncSeekSecondRelativeLinnCoUkDs1C sync(*this);
    BeginSeekSecondRelative(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginSeekSecondRelative(TInt aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaSecond));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1C::SyncSeekTrackId(TUint aaTrackId)
{
    SyncSeekTrackIdLinnCoUkDs1C sync(*this);
    BeginSeekTrackId(aaTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginSeekTrackId(TUint aaTrackId, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekTrackId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaTrackId));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndSeekTrackId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1C::SyncSeekTrackAbsolute(TUint aaTrack)
{
    SyncSeekTrackAbsoluteLinnCoUkDs1C sync(*this);
    BeginSeekTrackAbsolute(aaTrack, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginSeekTrackAbsolute(TUint aaTrack, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekTrackAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaTrack));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndSeekTrackAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1C::SyncSeekTrackRelative(TInt aaTrack)
{
    SyncSeekTrackRelativeLinnCoUkDs1C sync(*this);
    BeginSeekTrackRelative(aaTrack, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginSeekTrackRelative(TInt aaTrack, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSeekTrackRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaTrack));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndSeekTrackRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1C::SyncState(Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId)
{
    SyncStateLinnCoUkDs1C sync(*this, aaTransportState, aaTrackDuration, aaTrackBitRate, aaTrackLossless, aaTrackBitDepth, aaTrackSampleRate, aaTrackCodecName, aaTrackId);
    BeginState(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginState(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionState, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionState->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentBool(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndState(IAsync& aAsync, Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("State"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaTransportState);
    aaTrackDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaTrackBitRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaTrackLossless = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
    aaTrackBitDepth = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaTrackSampleRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaTrackCodecName);
    aaTrackId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDs1C::SyncProtocolInfo(Brh& aaSupportedProtocols)
{
    SyncProtocolInfoLinnCoUkDs1C sync(*this, aaSupportedProtocols);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1C::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1C::EndProtocolInfo(IAsync& aAsync, Brh& aaSupportedProtocols)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProtocolInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaSupportedProtocols);
}

void CpProxyLinnCoUkDs1C::SetPropertySupportedProtocolsChanged(Functor& aFunctor)
{
    iLock.Wait();
    iSupportedProtocolsChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::SetPropertyTrackDurationChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackDurationChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::SetPropertyTrackBitRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackBitRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::SetPropertyTrackLosslessChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackLosslessChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::SetPropertyTrackBitDepthChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackBitDepthChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::SetPropertyTrackSampleRateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackSampleRateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::SetPropertyTrackCodecNameChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackCodecNameChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::SetPropertyTrackIdChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTrackIdChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock.Wait();
    iTransportStateChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertySupportedProtocols(Brhz& aSupportedProtocols) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aSupportedProtocols.Set(iSupportedProtocols->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertyTrackDuration(TUint& aTrackDuration) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTrackDuration = iTrackDuration->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertyTrackBitRate(TUint& aTrackBitRate) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTrackBitRate = iTrackBitRate->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertyTrackLossless(TBool& aTrackLossless) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTrackLossless = iTrackLossless->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertyTrackBitDepth(TUint& aTrackBitDepth) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTrackBitDepth = iTrackBitDepth->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertyTrackSampleRate(TUint& aTrackSampleRate) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTrackSampleRate = iTrackSampleRate->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertyTrackCodecName(Brhz& aTrackCodecName) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTrackCodecName.Set(iTrackCodecName->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertyTrackId(TUint& aTrackId) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTrackId = iTrackId->Value();
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::PropertyTransportState(Brhz& aTransportState) const
{
    iPropertyLock.Wait();
    ASSERT(IsSubscribed());
    aTransportState.Set(iTransportState->Value());
    iPropertyLock.Signal();
}

void CpProxyLinnCoUkDs1C::SupportedProtocolsPropertyChanged()
{
    ReportEvent(iSupportedProtocolsChanged);
}

void CpProxyLinnCoUkDs1C::TrackDurationPropertyChanged()
{
    ReportEvent(iTrackDurationChanged);
}

void CpProxyLinnCoUkDs1C::TrackBitRatePropertyChanged()
{
    ReportEvent(iTrackBitRateChanged);
}

void CpProxyLinnCoUkDs1C::TrackLosslessPropertyChanged()
{
    ReportEvent(iTrackLosslessChanged);
}

void CpProxyLinnCoUkDs1C::TrackBitDepthPropertyChanged()
{
    ReportEvent(iTrackBitDepthChanged);
}

void CpProxyLinnCoUkDs1C::TrackSampleRatePropertyChanged()
{
    ReportEvent(iTrackSampleRateChanged);
}

void CpProxyLinnCoUkDs1C::TrackCodecNamePropertyChanged()
{
    ReportEvent(iTrackCodecNameChanged);
}

void CpProxyLinnCoUkDs1C::TrackIdPropertyChanged()
{
    ReportEvent(iTrackIdChanged);
}

void CpProxyLinnCoUkDs1C::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}


THandle CpProxyLinnCoUkDs1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkDs1C(aDevice);
}

void CpProxyLinnCoUkDs1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkDs1SyncPlay(THandle aHandle)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncPlay();
}

void CpProxyLinnCoUkDs1BeginPlay(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPlay(functor);
}

int32_t CpProxyLinnCoUkDs1EndPlay(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPlay(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncPause(THandle aHandle)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncPause();
}

void CpProxyLinnCoUkDs1BeginPause(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginPause(functor);
}

int32_t CpProxyLinnCoUkDs1EndPause(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndPause(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncStop(THandle aHandle)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStop();
}

void CpProxyLinnCoUkDs1BeginStop(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStop(functor);
}

int32_t CpProxyLinnCoUkDs1EndStop(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStop(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekSecondAbsolute(THandle aHandle, uint32_t aaSecond)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSeekSecondAbsolute(aaSecond);
}

void CpProxyLinnCoUkDs1BeginSeekSecondAbsolute(THandle aHandle, uint32_t aaSecond, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSeekSecondAbsolute(aaSecond, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekSecondAbsolute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekSecondAbsolute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekSecondRelative(THandle aHandle, int32_t aaSecond)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSeekSecondRelative(aaSecond);
}

void CpProxyLinnCoUkDs1BeginSeekSecondRelative(THandle aHandle, int32_t aaSecond, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSeekSecondRelative(aaSecond, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekSecondRelative(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekSecondRelative(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekTrackId(THandle aHandle, uint32_t aaTrackId)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSeekTrackId(aaTrackId);
}

void CpProxyLinnCoUkDs1BeginSeekTrackId(THandle aHandle, uint32_t aaTrackId, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSeekTrackId(aaTrackId, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekTrackId(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekTrackId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekTrackAbsolute(THandle aHandle, uint32_t aaTrack)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSeekTrackAbsolute(aaTrack);
}

void CpProxyLinnCoUkDs1BeginSeekTrackAbsolute(THandle aHandle, uint32_t aaTrack, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSeekTrackAbsolute(aaTrack, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekTrackAbsolute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekTrackAbsolute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekTrackRelative(THandle aHandle, int32_t aaTrack)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSeekTrackRelative(aaTrack);
}

void CpProxyLinnCoUkDs1BeginSeekTrackRelative(THandle aHandle, int32_t aaTrack, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSeekTrackRelative(aaTrack, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekTrackRelative(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSeekTrackRelative(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncState(THandle aHandle, char** aaTransportState, uint32_t* aaTrackDuration, uint32_t* aaTrackBitRate, uint32_t* aaTrackLossless, uint32_t* aaTrackBitDepth, uint32_t* aaTrackSampleRate, char** aaTrackCodecName, uint32_t* aaTrackId)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaTransportState;
    *aaTrackLossless = 0;
    Brh buf_aaTrackCodecName;
    proxyC->SyncState(buf_aaTransportState, *aaTrackDuration, *aaTrackBitRate, *(TBool*)aaTrackLossless, *aaTrackBitDepth, *aaTrackSampleRate, buf_aaTrackCodecName, *aaTrackId);
    *aaTransportState = buf_aaTransportState.Extract();
    *aaTrackCodecName = buf_aaTrackCodecName.Extract();
}

void CpProxyLinnCoUkDs1BeginState(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginState(functor);
}

int32_t CpProxyLinnCoUkDs1EndState(THandle aHandle, ZappHandleAsync aAsync, char** aaTransportState, uint32_t* aaTrackDuration, uint32_t* aaTrackBitRate, uint32_t* aaTrackLossless, uint32_t* aaTrackBitDepth, uint32_t* aaTrackSampleRate, char** aaTrackCodecName, uint32_t* aaTrackId)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaTransportState;
    *aaTransportState = NULL;
    *aaTrackLossless = 0;
    Brh buf_aaTrackCodecName;
    *aaTrackCodecName = NULL;
    try {
        proxyC->EndState(*async, buf_aaTransportState, *aaTrackDuration, *aaTrackBitRate, *(TBool*)aaTrackLossless, *aaTrackBitDepth, *aaTrackSampleRate, buf_aaTrackCodecName, *aaTrackId);
        *aaTransportState = buf_aaTransportState.Extract();
        *aaTrackCodecName = buf_aaTrackCodecName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncProtocolInfo(THandle aHandle, char** aaSupportedProtocols)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSupportedProtocols;
    proxyC->SyncProtocolInfo(buf_aaSupportedProtocols);
    *aaSupportedProtocols = buf_aaSupportedProtocols.Extract();
}

void CpProxyLinnCoUkDs1BeginProtocolInfo(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginProtocolInfo(functor);
}

int32_t CpProxyLinnCoUkDs1EndProtocolInfo(THandle aHandle, ZappHandleAsync aAsync, char** aaSupportedProtocols)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSupportedProtocols;
    *aaSupportedProtocols = NULL;
    try {
        proxyC->EndProtocolInfo(*async, buf_aaSupportedProtocols);
        *aaSupportedProtocols = buf_aaSupportedProtocols.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SetPropertySupportedProtocolsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertySupportedProtocolsChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackDurationChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackBitRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackBitRateChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackLosslessChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackLosslessChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackBitDepthChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackBitDepthChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackSampleRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackSampleRateChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackCodecNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackCodecNameChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackIdChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTrackIdChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTransportStateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyTransportStateChanged(functor);
}

void CpProxyLinnCoUkDs1PropertySupportedProtocols(THandle aHandle, char** aSupportedProtocols)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSupportedProtocols;
    proxyC->PropertySupportedProtocols(buf_aSupportedProtocols);
    *aSupportedProtocols = buf_aSupportedProtocols.Transfer();
}

void CpProxyLinnCoUkDs1PropertyTrackDuration(THandle aHandle, uint32_t* aTrackDuration)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackDuration(*aTrackDuration);
}

void CpProxyLinnCoUkDs1PropertyTrackBitRate(THandle aHandle, uint32_t* aTrackBitRate)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackBitRate(*aTrackBitRate);
}

void CpProxyLinnCoUkDs1PropertyTrackLossless(THandle aHandle, uint32_t* aTrackLossless)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aTrackLossless = false;
    proxyC->PropertyTrackLossless(*(TBool*)aTrackLossless);
}

void CpProxyLinnCoUkDs1PropertyTrackBitDepth(THandle aHandle, uint32_t* aTrackBitDepth)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackBitDepth(*aTrackBitDepth);
}

void CpProxyLinnCoUkDs1PropertyTrackSampleRate(THandle aHandle, uint32_t* aTrackSampleRate)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackSampleRate(*aTrackSampleRate);
}

void CpProxyLinnCoUkDs1PropertyTrackCodecName(THandle aHandle, char** aTrackCodecName)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTrackCodecName;
    proxyC->PropertyTrackCodecName(buf_aTrackCodecName);
    *aTrackCodecName = buf_aTrackCodecName.Transfer();
}

void CpProxyLinnCoUkDs1PropertyTrackId(THandle aHandle, uint32_t* aTrackId)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyTrackId(*aTrackId);
}

void CpProxyLinnCoUkDs1PropertyTransportState(THandle aHandle, char** aTransportState)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransportState;
    proxyC->PropertyTransportState(buf_aTransportState);
    *aTransportState = buf_aTransportState.Transfer();
}

