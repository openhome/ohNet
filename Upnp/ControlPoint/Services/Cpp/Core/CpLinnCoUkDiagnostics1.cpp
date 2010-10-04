#include <Core/CpLinnCoUkDiagnostics1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Core/CpDevice.h>

using namespace Zapp;


class SyncEchoLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncEchoLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaOut);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    Brh& iaOut;
};

SyncEchoLinnCoUkDiagnostics1::SyncEchoLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaOut)
    : iService(aService)
    , iaOut(aaOut)
{
}

void SyncEchoLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndEcho(aAsync, iaOut);
}


class SyncElfFileLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncElfFileLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaElfFile);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    Brh& iaElfFile;
};

SyncElfFileLinnCoUkDiagnostics1::SyncElfFileLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaElfFile)
    : iService(aService)
    , iaElfFile(aaElfFile)
{
}

void SyncElfFileLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndElfFile(aAsync, iaElfFile);
}


class SyncElfFingerprintLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncElfFingerprintLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaElfFileFingerprint);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    Brh& iaElfFileFingerprint;
};

SyncElfFingerprintLinnCoUkDiagnostics1::SyncElfFingerprintLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaElfFileFingerprint)
    : iService(aService)
    , iaElfFileFingerprint(aaElfFileFingerprint)
{
}

void SyncElfFingerprintLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndElfFingerprint(aAsync, iaElfFileFingerprint);
}


class SyncCrashDataStatusLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncCrashDataStatusLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaCrashDataStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    Brh& iaCrashDataStatus;
};

SyncCrashDataStatusLinnCoUkDiagnostics1::SyncCrashDataStatusLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaCrashDataStatus)
    : iService(aService)
    , iaCrashDataStatus(aaCrashDataStatus)
{
}

void SyncCrashDataStatusLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataStatus(aAsync, iaCrashDataStatus);
}


class SyncCrashDataFetchLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncCrashDataFetchLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaCrashData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    Brh& iaCrashData;
};

SyncCrashDataFetchLinnCoUkDiagnostics1::SyncCrashDataFetchLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaCrashData)
    : iService(aService)
    , iaCrashData(aaCrashData)
{
}

void SyncCrashDataFetchLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataFetch(aAsync, iaCrashData);
}


class SyncCrashDataClearLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncCrashDataClearLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
};

SyncCrashDataClearLinnCoUkDiagnostics1::SyncCrashDataClearLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService)
    : iService(aService)
{
}

void SyncCrashDataClearLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataClear(aAsync);
}


class SyncSysLogLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncSysLogLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaSysLog);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    Brh& iaSysLog;
};

SyncSysLogLinnCoUkDiagnostics1::SyncSysLogLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaSysLog)
    : iService(aService)
    , iaSysLog(aaSysLog)
{
}

void SyncSysLogLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSysLog(aAsync, iaSysLog);
}


class SyncDiagnosticLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncDiagnosticLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaDiagnosticInfo);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    Brh& iaDiagnosticInfo;
};

SyncDiagnosticLinnCoUkDiagnostics1::SyncDiagnosticLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, Brh& aaDiagnosticInfo)
    : iService(aService)
    , iaDiagnosticInfo(aaDiagnosticInfo)
{
}

void SyncDiagnosticLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiagnostic(aAsync, iaDiagnosticInfo);
}


class SyncStateVariableLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncStateVariableLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, TUint& aaStateVariable);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    TUint& iaStateVariable;
};

SyncStateVariableLinnCoUkDiagnostics1::SyncStateVariableLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, TUint& aaStateVariable)
    : iService(aService)
    , iaStateVariable(aaStateVariable)
{
}

void SyncStateVariableLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStateVariable(aAsync, iaStateVariable);
}


class SyncSetStateVariableLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncSetStateVariableLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
};

SyncSetStateVariableLinnCoUkDiagnostics1::SyncSetStateVariableLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService)
    : iService(aService)
{
}

void SyncSetStateVariableLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariable(aAsync);
}


class SyncStateVariablePeriodLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncStateVariablePeriodLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, TUint& aaPeriod);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
    TUint& iaPeriod;
};

SyncStateVariablePeriodLinnCoUkDiagnostics1::SyncStateVariablePeriodLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService, TUint& aaPeriod)
    : iService(aService)
    , iaPeriod(aaPeriod)
{
}

void SyncStateVariablePeriodLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndStateVariablePeriod(aAsync, iaPeriod);
}


class SyncSetStateVariablePeriodLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncSetStateVariablePeriodLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
};

SyncSetStateVariablePeriodLinnCoUkDiagnostics1::SyncSetStateVariablePeriodLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService)
    : iService(aService)
{
}

void SyncSetStateVariablePeriodLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariablePeriod(aAsync);
}


class SyncRebootLinnCoUkDiagnostics1 : public SyncProxyAction
{
public:
    SyncRebootLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1& iService;
};

SyncRebootLinnCoUkDiagnostics1::SyncRebootLinnCoUkDiagnostics1(CpProxyLinnCoUkDiagnostics1& aService)
    : iService(aService)
{
}

void SyncRebootLinnCoUkDiagnostics1::CompleteRequest(IAsync& aAsync)
{
    iService.EndReboot(aAsync);
}


CpProxyLinnCoUkDiagnostics1::CpProxyLinnCoUkDiagnostics1(CpDevice& aDevice)
{
    iService = new CpiService("linn-co-uk", "Diagnostics", 1, aDevice.Device());
    Zapp::Parameter* param;

    iActionEcho = new Action("Echo");
    param = new Zapp::ParameterString("aIn");
    iActionEcho->AddInputParameter(param);
    param = new Zapp::ParameterString("aOut");
    iActionEcho->AddOutputParameter(param);

    iActionElfFile = new Action("ElfFile");
    param = new Zapp::ParameterString("aElfFile");
    iActionElfFile->AddOutputParameter(param);

    iActionElfFingerprint = new Action("ElfFingerprint");
    param = new Zapp::ParameterString("aElfFileFingerprint");
    iActionElfFingerprint->AddOutputParameter(param);

    iActionCrashDataStatus = new Action("CrashDataStatus");
    param = new Zapp::ParameterString("aCrashDataStatus");
    iActionCrashDataStatus->AddOutputParameter(param);

    iActionCrashDataFetch = new Action("CrashDataFetch");
    param = new Zapp::ParameterBinary("aCrashData");
    iActionCrashDataFetch->AddOutputParameter(param);

    iActionCrashDataClear = new Action("CrashDataClear");

    iActionSysLog = new Action("SysLog");
    param = new Zapp::ParameterBinary("aSysLog");
    iActionSysLog->AddOutputParameter(param);

    iActionDiagnostic = new Action("Diagnostic");
    param = new Zapp::ParameterString("aDiagnosticType");
    iActionDiagnostic->AddInputParameter(param);
    param = new Zapp::ParameterString("aDiagnosticInfo");
    iActionDiagnostic->AddOutputParameter(param);

    iActionStateVariable = new Action("StateVariable");
    param = new Zapp::ParameterUint("aStateVariable");
    iActionStateVariable->AddOutputParameter(param);

    iActionSetStateVariable = new Action("SetStateVariable");
    param = new Zapp::ParameterUint("aStateVariable");
    iActionSetStateVariable->AddInputParameter(param);

    iActionStateVariablePeriod = new Action("StateVariablePeriod");
    param = new Zapp::ParameterUint("aPeriod");
    iActionStateVariablePeriod->AddOutputParameter(param);

    iActionSetStateVariablePeriod = new Action("SetStateVariablePeriod");
    param = new Zapp::ParameterUint("aPeriod");
    iActionSetStateVariablePeriod->AddInputParameter(param);

    iActionReboot = new Action("Reboot");
    param = new Zapp::ParameterUint("aDelay");
    iActionReboot->AddInputParameter(param);

    Functor functor;
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDiagnostics1::aStateVariablePropertyChanged);
    iaStateVariable = new PropertyUint("aStateVariable", functor);
    iService->AddProperty(iaStateVariable);
}

CpProxyLinnCoUkDiagnostics1::~CpProxyLinnCoUkDiagnostics1()
{
    delete iService;
    delete iActionEcho;
    delete iActionElfFile;
    delete iActionElfFingerprint;
    delete iActionCrashDataStatus;
    delete iActionCrashDataFetch;
    delete iActionCrashDataClear;
    delete iActionSysLog;
    delete iActionDiagnostic;
    delete iActionStateVariable;
    delete iActionSetStateVariable;
    delete iActionStateVariablePeriod;
    delete iActionSetStateVariablePeriod;
    delete iActionReboot;
}

void CpProxyLinnCoUkDiagnostics1::SyncEcho(const Brx& aaIn, Brh& aaOut)
{
    SyncEchoLinnCoUkDiagnostics1 sync(*this, aaOut);
    BeginEcho(aaIn, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginEcho(const Brx& aaIn, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEcho, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEcho->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaIn));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEcho->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndEcho(IAsync& aAsync, Brh& aaOut)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Echo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaOut);
}

void CpProxyLinnCoUkDiagnostics1::SyncElfFile(Brh& aaElfFile)
{
    SyncElfFileLinnCoUkDiagnostics1 sync(*this, aaElfFile);
    BeginElfFile(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginElfFile(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionElfFile, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionElfFile->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndElfFile(IAsync& aAsync, Brh& aaElfFile)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ElfFile"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaElfFile);
}

void CpProxyLinnCoUkDiagnostics1::SyncElfFingerprint(Brh& aaElfFileFingerprint)
{
    SyncElfFingerprintLinnCoUkDiagnostics1 sync(*this, aaElfFileFingerprint);
    BeginElfFingerprint(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginElfFingerprint(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionElfFingerprint, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionElfFingerprint->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndElfFingerprint(IAsync& aAsync, Brh& aaElfFileFingerprint)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ElfFingerprint"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaElfFileFingerprint);
}

void CpProxyLinnCoUkDiagnostics1::SyncCrashDataStatus(Brh& aaCrashDataStatus)
{
    SyncCrashDataStatusLinnCoUkDiagnostics1 sync(*this, aaCrashDataStatus);
    BeginCrashDataStatus(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginCrashDataStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCrashDataStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCrashDataStatus->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndCrashDataStatus(IAsync& aAsync, Brh& aaCrashDataStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CrashDataStatus"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaCrashDataStatus);
}

void CpProxyLinnCoUkDiagnostics1::SyncCrashDataFetch(Brh& aaCrashData)
{
    SyncCrashDataFetchLinnCoUkDiagnostics1 sync(*this, aaCrashData);
    BeginCrashDataFetch(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginCrashDataFetch(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCrashDataFetch, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCrashDataFetch->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndCrashDataFetch(IAsync& aAsync, Brh& aaCrashData)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CrashDataFetch"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aaCrashData);
}

void CpProxyLinnCoUkDiagnostics1::SyncCrashDataClear()
{
    SyncCrashDataClearLinnCoUkDiagnostics1 sync(*this);
    BeginCrashDataClear(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginCrashDataClear(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCrashDataClear, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndCrashDataClear(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CrashDataClear"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1::SyncSysLog(Brh& aaSysLog)
{
    SyncSysLogLinnCoUkDiagnostics1 sync(*this, aaSysLog);
    BeginSysLog(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginSysLog(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSysLog, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSysLog->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndSysLog(IAsync& aAsync, Brh& aaSysLog)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SysLog"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentBinary*)invocation.OutputArguments()[index++])->TransferTo(aaSysLog);
}

void CpProxyLinnCoUkDiagnostics1::SyncDiagnostic(const Brx& aaDiagnosticType, Brh& aaDiagnosticInfo)
{
    SyncDiagnosticLinnCoUkDiagnostics1 sync(*this, aaDiagnosticInfo);
    BeginDiagnostic(aaDiagnosticType, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginDiagnostic(const Brx& aaDiagnosticType, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDiagnostic, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDiagnostic->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaDiagnosticType));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiagnostic->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndDiagnostic(IAsync& aAsync, Brh& aaDiagnosticInfo)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Diagnostic"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    ((ArgumentString*)invocation.OutputArguments()[index++])->TransferTo(aaDiagnosticInfo);
}

void CpProxyLinnCoUkDiagnostics1::SyncStateVariable(TUint& aaStateVariable)
{
    SyncStateVariableLinnCoUkDiagnostics1 sync(*this, aaStateVariable);
    BeginStateVariable(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginStateVariable(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStateVariable, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStateVariable->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndStateVariable(IAsync& aAsync, TUint& aaStateVariable)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StateVariable"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaStateVariable = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDiagnostics1::SyncSetStateVariable(TUint aaStateVariable)
{
    SyncSetStateVariableLinnCoUkDiagnostics1 sync(*this);
    BeginSetStateVariable(aaStateVariable, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginSetStateVariable(TUint aaStateVariable, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStateVariable, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariable->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaStateVariable));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndSetStateVariable(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariable"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1::SyncStateVariablePeriod(TUint& aaPeriod)
{
    SyncStateVariablePeriodLinnCoUkDiagnostics1 sync(*this, aaPeriod);
    BeginStateVariablePeriod(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginStateVariablePeriod(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStateVariablePeriod, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStateVariablePeriod->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndStateVariablePeriod(IAsync& aAsync, TUint& aaPeriod)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("StateVariablePeriod"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    aaPeriod = ((ArgumentUint*)invocation.OutputArguments()[index++])->Value();
}

void CpProxyLinnCoUkDiagnostics1::SyncSetStateVariablePeriod(TUint aaPeriod)
{
    SyncSetStateVariablePeriodLinnCoUkDiagnostics1 sync(*this);
    BeginSetStateVariablePeriod(aaPeriod, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginSetStateVariablePeriod(TUint aaPeriod, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStateVariablePeriod, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariablePeriod->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPeriod));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndSetStateVariablePeriod(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariablePeriod"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1::SyncReboot(TUint aaDelay)
{
    SyncRebootLinnCoUkDiagnostics1 sync(*this);
    BeginReboot(aaDelay, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1::BeginReboot(TUint aaDelay, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReboot, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReboot->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDelay));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1::EndReboot(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Reboot"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1::SetPropertyaStateVariableChanged(Functor& aFunctor)
{
    iLock->Wait();
    iaStateVariableChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDiagnostics1::PropertyaStateVariable(TUint& aaStateVariable) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aaStateVariable = iaStateVariable->Value();
}

void CpProxyLinnCoUkDiagnostics1::aStateVariablePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iaStateVariableChanged != NULL) {
        iaStateVariableChanged();
    }
}

