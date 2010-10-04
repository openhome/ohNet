#include <Std/CpLinnCoUkDs1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncPlayLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncPlayLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
};

SyncPlayLinnCoUkDs1Cpp::SyncPlayLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService)
    : iService(aService)
{
}

void SyncPlayLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPlay(aAsync);
}


class SyncPauseLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncPauseLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
};

SyncPauseLinnCoUkDs1Cpp::SyncPauseLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService)
    : iService(aService)
{
}

void SyncPauseLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndPause(aAsync);
}


class SyncStopLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncStopLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
};

SyncStopLinnCoUkDs1Cpp::SyncStopLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService)
    : iService(aService)
{
}

void SyncStopLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStop(aAsync);
}


class SyncSeekSecondAbsoluteLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncSeekSecondAbsoluteLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
};

SyncSeekSecondAbsoluteLinnCoUkDs1Cpp::SyncSeekSecondAbsoluteLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService)
    : iService(aService)
{
}

void SyncSeekSecondAbsoluteLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondAbsolute(aAsync);
}


class SyncSeekSecondRelativeLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncSeekSecondRelativeLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
};

SyncSeekSecondRelativeLinnCoUkDs1Cpp::SyncSeekSecondRelativeLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService)
    : iService(aService)
{
}

void SyncSeekSecondRelativeLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekSecondRelative(aAsync);
}


class SyncSeekTrackIdLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncSeekTrackIdLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
};

SyncSeekTrackIdLinnCoUkDs1Cpp::SyncSeekTrackIdLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService)
    : iService(aService)
{
}

void SyncSeekTrackIdLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackId(aAsync);
}


class SyncSeekTrackAbsoluteLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncSeekTrackAbsoluteLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
};

SyncSeekTrackAbsoluteLinnCoUkDs1Cpp::SyncSeekTrackAbsoluteLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService)
    : iService(aService)
{
}

void SyncSeekTrackAbsoluteLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackAbsolute(aAsync);
}


class SyncSeekTrackRelativeLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncSeekTrackRelativeLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
};

SyncSeekTrackRelativeLinnCoUkDs1Cpp::SyncSeekTrackRelativeLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService)
    : iService(aService)
{
}

void SyncSeekTrackRelativeLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSeekTrackRelative(aAsync);
}


class SyncStateLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncStateLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService, std::string& aaTransportState, uint32_t& aaTrackDuration, uint32_t& aaTrackBitRate, bool& aaTrackLossless, uint32_t& aaTrackBitDepth, uint32_t& aaTrackSampleRate, std::string& aaTrackCodecName, uint32_t& aaTrackId);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
    std::string& iaTransportState;
    uint32_t& iaTrackDuration;
    uint32_t& iaTrackBitRate;
    bool& iaTrackLossless;
    uint32_t& iaTrackBitDepth;
    uint32_t& iaTrackSampleRate;
    std::string& iaTrackCodecName;
    uint32_t& iaTrackId;
};

SyncStateLinnCoUkDs1Cpp::SyncStateLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService, std::string& aaTransportState, uint32_t& aaTrackDuration, uint32_t& aaTrackBitRate, bool& aaTrackLossless, uint32_t& aaTrackBitDepth, uint32_t& aaTrackSampleRate, std::string& aaTrackCodecName, uint32_t& aaTrackId)
    : iService(aService)
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

void SyncStateLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndState(aAsync, iaTransportState, iaTrackDuration, iaTrackBitRate, iaTrackLossless, iaTrackBitDepth, iaTrackSampleRate, iaTrackCodecName, iaTrackId);
}


class SyncProtocolInfoLinnCoUkDs1Cpp : public SyncProxyAction
{
public:
    SyncProtocolInfoLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService, std::string& aaSupportedProtocols);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDs1Cpp& iService;
    std::string& iaSupportedProtocols;
};

SyncProtocolInfoLinnCoUkDs1Cpp::SyncProtocolInfoLinnCoUkDs1Cpp(CpProxyLinnCoUkDs1Cpp& aService, std::string& aaSupportedProtocols)
    : iService(aService)
    , iaSupportedProtocols(aaSupportedProtocols)
{
}

void SyncProtocolInfoLinnCoUkDs1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndProtocolInfo(aAsync, iaSupportedProtocols);
}


CpProxyLinnCoUkDs1Cpp::CpProxyLinnCoUkDs1Cpp(CpDeviceCpp& aDevice)
{
    iService = new CpiService("linn-co-uk", "Ds", 1, aDevice.Device());
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::SupportedProtocolsPropertyChanged);
    iSupportedProtocols = new PropertyString("SupportedProtocols", functor);
    iService->AddProperty(iSupportedProtocols);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::TrackDurationPropertyChanged);
    iTrackDuration = new PropertyUint("TrackDuration", functor);
    iService->AddProperty(iTrackDuration);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::TrackBitRatePropertyChanged);
    iTrackBitRate = new PropertyUint("TrackBitRate", functor);
    iService->AddProperty(iTrackBitRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::TrackLosslessPropertyChanged);
    iTrackLossless = new PropertyBool("TrackLossless", functor);
    iService->AddProperty(iTrackLossless);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::TrackBitDepthPropertyChanged);
    iTrackBitDepth = new PropertyUint("TrackBitDepth", functor);
    iService->AddProperty(iTrackBitDepth);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::TrackSampleRatePropertyChanged);
    iTrackSampleRate = new PropertyUint("TrackSampleRate", functor);
    iService->AddProperty(iTrackSampleRate);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::TrackCodecNamePropertyChanged);
    iTrackCodecName = new PropertyString("TrackCodecName", functor);
    iService->AddProperty(iTrackCodecName);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::TrackIdPropertyChanged);
    iTrackId = new PropertyUint("TrackId", functor);
    iService->AddProperty(iTrackId);
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDs1Cpp::TransportStatePropertyChanged);
    iTransportState = new PropertyString("TransportState", functor);
    iService->AddProperty(iTransportState);
}

CpProxyLinnCoUkDs1Cpp::~CpProxyLinnCoUkDs1Cpp()
{
    delete iService;
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

void CpProxyLinnCoUkDs1Cpp::SyncPlay()
{
    SyncPlayLinnCoUkDs1Cpp sync(*this);
    BeginPlay(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginPlay(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPlay, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndPlay(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Play"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1Cpp::SyncPause()
{
    SyncPauseLinnCoUkDs1Cpp sync(*this);
    BeginPause(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginPause(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionPause, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndPause(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Pause"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1Cpp::SyncStop()
{
    SyncStopLinnCoUkDs1Cpp sync(*this);
    BeginStop(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginStop(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStop, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndStop(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Stop"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1Cpp::SyncSeekSecondAbsolute(uint32_t aaSecond)
{
    SyncSeekSecondAbsoluteLinnCoUkDs1Cpp sync(*this);
    BeginSeekSecondAbsolute(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginSeekSecondAbsolute(uint32_t aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaSecond));
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndSeekSecondAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1Cpp::SyncSeekSecondRelative(int32_t aaSecond)
{
    SyncSeekSecondRelativeLinnCoUkDs1Cpp sync(*this);
    BeginSeekSecondRelative(aaSecond, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginSeekSecondRelative(int32_t aaSecond, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekSecondRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekSecondRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaSecond));
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndSeekSecondRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekSecondRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1Cpp::SyncSeekTrackId(uint32_t aaTrackId)
{
    SyncSeekTrackIdLinnCoUkDs1Cpp sync(*this);
    BeginSeekTrackId(aaTrackId, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginSeekTrackId(uint32_t aaTrackId, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekTrackId, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackId->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaTrackId));
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndSeekTrackId(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackId"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1Cpp::SyncSeekTrackAbsolute(uint32_t aaTrack)
{
    SyncSeekTrackAbsoluteLinnCoUkDs1Cpp sync(*this);
    BeginSeekTrackAbsolute(aaTrack, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginSeekTrackAbsolute(uint32_t aaTrack, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekTrackAbsolute, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackAbsolute->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaTrack));
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndSeekTrackAbsolute(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackAbsolute"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1Cpp::SyncSeekTrackRelative(int32_t aaTrack)
{
    SyncSeekTrackRelativeLinnCoUkDs1Cpp sync(*this);
    BeginSeekTrackRelative(aaTrack, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginSeekTrackRelative(int32_t aaTrack, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSeekTrackRelative, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSeekTrackRelative->InputParameters();
    invocation->AddInput(new ArgumentInt(*inParams[inIndex++], aaTrack));
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndSeekTrackRelative(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SeekTrackRelative"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDs1Cpp::SyncState(std::string& aaTransportState, uint32_t& aaTrackDuration, uint32_t& aaTrackBitRate, bool& aaTrackLossless, uint32_t& aaTrackBitDepth, uint32_t& aaTrackSampleRate, std::string& aaTrackCodecName, uint32_t& aaTrackId)
{
    SyncStateLinnCoUkDs1Cpp sync(*this, aaTransportState, aaTrackDuration, aaTrackBitRate, aaTrackLossless, aaTrackBitDepth, aaTrackSampleRate, aaTrackCodecName, aaTrackId);
    BeginState(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginState(FunctorAsync& aFunctor)
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
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndState(IAsync& aAsync, std::string& aaTransportState, uint32_t& aaTrackDuration, uint32_t& aaTrackBitRate, bool& aaTrackLossless, uint32_t& aaTrackBitDepth, uint32_t& aaTrackSampleRate, std::string& aaTrackCodecName, uint32_t& aaTrackId)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("State"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaTransportState.assign((const char*)val.Ptr(), val.Bytes());
    }
    aaTrackDuration = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaTrackBitRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaTrackLossless = ((ArgumentBool*)invocation.OutputArguments()[index++])->Value();
    aaTrackBitDepth = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    aaTrackSampleRate = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaTrackCodecName.assign((const char*)val.Ptr(), val.Bytes());
    }
    aaTrackId = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDs1Cpp::SyncProtocolInfo(std::string& aaSupportedProtocols)
{
    SyncProtocolInfoLinnCoUkDs1Cpp sync(*this, aaSupportedProtocols);
    BeginProtocolInfo(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDs1Cpp::BeginProtocolInfo(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionProtocolInfo, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionProtocolInfo->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDs1Cpp::EndProtocolInfo(IAsync& aAsync, std::string& aaSupportedProtocols)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ProtocolInfo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaSupportedProtocols.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDs1Cpp::SetPropertySupportedProtocolsChanged(Functor& aFunctor)
{
    iLock->Wait();
    iSupportedProtocolsChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::SetPropertyTrackDurationChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackDurationChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::SetPropertyTrackBitRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackBitRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::SetPropertyTrackLosslessChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackLosslessChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::SetPropertyTrackBitDepthChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackBitDepthChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::SetPropertyTrackSampleRateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackSampleRateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::SetPropertyTrackCodecNameChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackCodecNameChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::SetPropertyTrackIdChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTrackIdChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::SetPropertyTransportStateChanged(Functor& aFunctor)
{
    iLock->Wait();
    iTransportStateChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDs1Cpp::PropertySupportedProtocols(std::string& aSupportedProtocols) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iSupportedProtocols->Value();
    aSupportedProtocols.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkDs1Cpp::PropertyTrackDuration(uint32_t& aTrackDuration) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackDuration = iTrackDuration->Value();
}

void CpProxyLinnCoUkDs1Cpp::PropertyTrackBitRate(uint32_t& aTrackBitRate) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackBitRate = iTrackBitRate->Value();
}

void CpProxyLinnCoUkDs1Cpp::PropertyTrackLossless(bool& aTrackLossless) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackLossless = iTrackLossless->Value();
}

void CpProxyLinnCoUkDs1Cpp::PropertyTrackBitDepth(uint32_t& aTrackBitDepth) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackBitDepth = iTrackBitDepth->Value();
}

void CpProxyLinnCoUkDs1Cpp::PropertyTrackSampleRate(uint32_t& aTrackSampleRate) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackSampleRate = iTrackSampleRate->Value();
}

void CpProxyLinnCoUkDs1Cpp::PropertyTrackCodecName(std::string& aTrackCodecName) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTrackCodecName->Value();
    aTrackCodecName.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkDs1Cpp::PropertyTrackId(uint32_t& aTrackId) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aTrackId = iTrackId->Value();
}

void CpProxyLinnCoUkDs1Cpp::PropertyTransportState(std::string& aTransportState) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    const Brx& val = iTransportState->Value();
    aTransportState.assign((const char*)val.Ptr(), val.Bytes());
}

void CpProxyLinnCoUkDs1Cpp::SupportedProtocolsPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iSupportedProtocolsChanged != NULL) {
        iSupportedProtocolsChanged();
    }
}

void CpProxyLinnCoUkDs1Cpp::TrackDurationPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackDurationChanged != NULL) {
        iTrackDurationChanged();
    }
}

void CpProxyLinnCoUkDs1Cpp::TrackBitRatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackBitRateChanged != NULL) {
        iTrackBitRateChanged();
    }
}

void CpProxyLinnCoUkDs1Cpp::TrackLosslessPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackLosslessChanged != NULL) {
        iTrackLosslessChanged();
    }
}

void CpProxyLinnCoUkDs1Cpp::TrackBitDepthPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackBitDepthChanged != NULL) {
        iTrackBitDepthChanged();
    }
}

void CpProxyLinnCoUkDs1Cpp::TrackSampleRatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackSampleRateChanged != NULL) {
        iTrackSampleRateChanged();
    }
}

void CpProxyLinnCoUkDs1Cpp::TrackCodecNamePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackCodecNameChanged != NULL) {
        iTrackCodecNameChanged();
    }
}

void CpProxyLinnCoUkDs1Cpp::TrackIdPropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTrackIdChanged != NULL) {
        iTrackIdChanged();
    }
}

void CpProxyLinnCoUkDs1Cpp::TransportStatePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iTransportStateChanged != NULL) {
        iTransportStateChanged();
    }
}

