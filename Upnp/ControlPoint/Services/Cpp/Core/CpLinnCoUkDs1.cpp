#include <Core/CpLinnCoUkDs1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncPlayLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncPlayLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
};

SyncPlayLinnCoUkDs1::SyncPlayLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy)
    : iService(aProxy)
{
}

void SyncPlayLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncPauseLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
};

SyncPauseLinnCoUkDs1::SyncPauseLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy)
    : iService(aProxy)
{
}

void SyncPauseLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncStopLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
};

SyncStopLinnCoUkDs1::SyncStopLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy)
    : iService(aProxy)
{
}

void SyncStopLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
};

SyncSeekSecondAbsoluteLinnCoUkDs1::SyncSeekSecondAbsoluteLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondAbsoluteLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
};

SyncSeekSecondRelativeLinnCoUkDs1::SyncSeekSecondRelativeLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy)
    : iService(aProxy)
{
}

void SyncSeekSecondRelativeLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncSeekTrackIdLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncSeekTrackIdLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
};

SyncSeekTrackIdLinnCoUkDs1::SyncSeekTrackIdLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy)
    : iService(aProxy)
{
}

void SyncSeekTrackIdLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackId(aAsync);
}


class SyncSeekTrackAbsoluteLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncSeekTrackAbsoluteLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
};

SyncSeekTrackAbsoluteLinnCoUkDs1::SyncSeekTrackAbsoluteLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy)
    : iService(aProxy)
{
}

void SyncSeekTrackAbsoluteLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackAbsolute(aAsync);
}


class SyncSeekTrackRelativeLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncSeekTrackRelativeLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
};

SyncSeekTrackRelativeLinnCoUkDs1::SyncSeekTrackRelativeLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy)
    : iService(aProxy)
{
}

void SyncSeekTrackRelativeLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackRelative(aAsync);
}


class SyncStateLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncStateLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy, Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
    Brh& iaTransportState;
    TUint& iaTrackDuration;
    TUint& iaTrackBitRate;
    TBool& iaTrackLossless;
    TUint& iaTrackBitDepth;
    TUint& iaTrackSampleRate;
    Brh& iaTrackCodecName;
    TUint& iaTrackId;
};

SyncStateLinnCoUkDs1::SyncStateLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy, Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId)
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

void SyncStateLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndState(aAsync, iaTransportState, iaTrackDuration, iaTrackBitRate, iaTrackLossless, iaTrackBitDepth, iaTrackSampleRate, iaTrackCodecName, iaTrackId);
}


class SyncProtocolInfoLinnCoUkDs1 : public SyncProxyAction
{
public:
    SyncProtocolInfoLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy, Brh& aaSupportedProtocols);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1& iService;
    Brh& iaSupportedProtocols;
};

SyncProtocolInfoLinnCoUkDs1::SyncProtocolInfoLinnCoUkDs1(CpProxyLinnCoUkDs1& aProxy, Brh& aaSupportedProtocols)
    : iService(aProxy)
    , iaSupportedProtocols(aaSupportedProtocols)
{
}

void SyncProtocolInfoLinnCoUkDs1::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iaSupportedProtocols);
}


CpProxyLinnCoUkDs1::CpProxyLinnCoUkDs1(CpDevice& aDevice)
    : CpProxy("linn-co-uk", "Ds", 1, aDevice.Device())
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::SupportedProtocolsPropertyChanged);
    iSupportedProtocols = new PropertyString("SupportedProtocols", functor);
    AddProperty(iSupportedProtocols);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::TrackDurationPropertyChanged);
    iTrackDuration = new PropertyUint("TrackDuration", functor);
    AddProperty(iTrackDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::TrackBitRatePropertyChanged);
    iTrackBitRate = new PropertyUint("TrackBitRate", functor);
    AddProperty(iTrackBitRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::TrackLosslessPropertyChanged);
    iTrackLossless = new PropertyBool("TrackLossless", functor);
    AddProperty(iTrackLossless);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::TrackBitDepthPropertyChanged);
    iTrackBitDepth = new PropertyUint("TrackBitDepth", functor);
    AddProperty(iTrackBitDepth);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::TrackSampleRatePropertyChanged);
    iTrackSampleRate = new PropertyUint("TrackSampleRate", functor);
    AddProperty(iTrackSampleRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::TrackCodecNamePropertyChanged);
    iTrackCodecName = new PropertyString("TrackCodecName", functor);
    AddProperty(iTrackCodecName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::TrackIdPropertyChanged);
    iTrackId = new PropertyUint("TrackId", functor);
    AddProperty(iTrackId);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1::TransportStatePropertyChanged);
    iTransportState = new PropertyString("TransportState", functor);
    AddProperty(iTransportState);
}

CpProxyLinnCoUkDs1::~CpProxyLinnCoUkDs1()
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

void CpProxyLinnCoUkDs1::SyncPlay()
{
    SyncPlayLinnCoUkDs1 sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1::SyncPause()
{
    SyncPauseLinnCoUkDs1 sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1::SyncStop()
{
    SyncStopLinnCoUkDs1 sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1::SyncSeekSecondAbsolute(TUint aaSecond)
{
    SyncSeekSecondAbsoluteLinnCoUkDs1 sync(*this);
    BeginSeekSecondAbsolute(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginSeekSecondAbsolute(TUint aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSecond));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1::SyncSeekSecondRelative(TInt aaSecond)
{
    SyncSeekSecondRelativeLinnCoUkDs1 sync(*this);
    BeginSeekSecondRelative(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginSeekSecondRelative(TInt aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaSecond));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1::SyncSeekTrackId(TUint aaTrackId)
{
    SyncSeekTrackIdLinnCoUkDs1 sync(*this);
    BeginSeekTrackId(aaTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginSeekTrackId(TUint aaTrackId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekTrackId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaTrackId));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndSeekTrackId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1::SyncSeekTrackAbsolute(TUint aaTrack)
{
    SyncSeekTrackAbsoluteLinnCoUkDs1 sync(*this);
    BeginSeekTrackAbsolute(aaTrack, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginSeekTrackAbsolute(TUint aaTrack, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekTrackAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaTrack));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndSeekTrackAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1::SyncSeekTrackRelative(TInt aaTrack)
{
    SyncSeekTrackRelativeLinnCoUkDs1 sync(*this);
    BeginSeekTrackRelative(aaTrack, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginSeekTrackRelative(TInt aaTrack, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekTrackRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaTrack));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndSeekTrackRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1::SyncState(Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId)
{
    SyncStateLinnCoUkDs1 sync(*this, aaTransportState, aaTrackDuration, aaTrackBitRate, aaTrackLossless, aaTrackBitDepth, aaTrackSampleRate, aaTrackCodecName, aaTrackId);
    BeginState(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginState(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionState, aFunctor);
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
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndState(IAsync& aAsync, Brh& aaTransportState, TUint& aaTrackDuration, TUint& aaTrackBitRate, TBool& aaTrackLossless, TUint& aaTrackBitDepth, TUint& aaTrackSampleRate, Brh& aaTrackCodecName, TUint& aaTrackId)
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

void CpProxyLinnCoUkDs1::SyncProtocolInfo(Brh& aaSupportedProtocols)
{
    SyncProtocolInfoLinnCoUkDs1 sync(*this, aaSupportedProtocols);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    iInvocable.InvokeAction(*invocation);
}

void CpProxyLinnCoUkDs1::EndProtocolInfo(IAsync& aAsync, Brh& aaSupportedProtocols)
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

void CpProxyLinnCoUkDs1::SetPropertySupportedProtocolsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSupportedProtocolsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::SetPropertyTrackDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::SetPropertyTrackBitRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackBitRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::SetPropertyTrackLosslessChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackLosslessChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::SetPropertyTrackBitDepthChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackBitDepthChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::SetPropertyTrackSampleRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackSampleRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::SetPropertyTrackCodecNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCodecNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::SetPropertyTrackIdChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackIdChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransportStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertySupportedProtocols(Brhz& aSupportedProtocols) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aSupportedProtocols.Set(iSupportedProtocols->Value());
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertyTrackDuration(TUint& aTrackDuration) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackDuration = iTrackDuration->Value();
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertyTrackBitRate(TUint& aTrackBitRate) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackBitRate = iTrackBitRate->Value();
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertyTrackLossless(TBool& aTrackLossless) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackLossless = iTrackLossless->Value();
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertyTrackBitDepth(TUint& aTrackBitDepth) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackBitDepth = iTrackBitDepth->Value();
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertyTrackSampleRate(TUint& aTrackSampleRate) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackSampleRate = iTrackSampleRate->Value();
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertyTrackCodecName(Brhz& aTrackCodecName) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackCodecName.Set(iTrackCodecName->Value());
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertyTrackId(TUint& aTrackId) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackId = iTrackId->Value();
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::PropertyTransportState(Brhz& aTransportState) const
{
    iPropertyLock->Wait();
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTransportState.Set(iTransportState->Value());
    iPropertyLock->Signal();
}

void CpProxyLinnCoUkDs1::SupportedProtocolsPropertyChanged()
{
    ReportEvent(iSupportedProtocolsChanged);
}

void CpProxyLinnCoUkDs1::TrackDurationPropertyChanged()
{
    ReportEvent(iTrackDurationChanged);
}

void CpProxyLinnCoUkDs1::TrackBitRatePropertyChanged()
{
    ReportEvent(iTrackBitRateChanged);
}

void CpProxyLinnCoUkDs1::TrackLosslessPropertyChanged()
{
    ReportEvent(iTrackLosslessChanged);
}

void CpProxyLinnCoUkDs1::TrackBitDepthPropertyChanged()
{
    ReportEvent(iTrackBitDepthChanged);
}

void CpProxyLinnCoUkDs1::TrackSampleRatePropertyChanged()
{
    ReportEvent(iTrackSampleRateChanged);
}

void CpProxyLinnCoUkDs1::TrackCodecNamePropertyChanged()
{
    ReportEvent(iTrackCodecNameChanged);
}

void CpProxyLinnCoUkDs1::TrackIdPropertyChanged()
{
    ReportEvent(iTrackIdChanged);
}

void CpProxyLinnCoUkDs1::TransportStatePropertyChanged()
{
    ReportEvent(iTransportStateChanged);
}

