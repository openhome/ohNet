#include "CpLinnCoUkDiagnostics1.h"
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

class CpProxyLinnCoUkDiagnostics1C : public CpProxyC
{
public:
    CpProxyLinnCoUkDiagnostics1C(CpDeviceC aDevice);
    ~CpProxyLinnCoUkDiagnostics1C();
    //CpProxyLinnCoUkDiagnostics1* Proxy() { return static_cast<CpProxyLinnCoUkDiagnostics1*>(iProxy); }

    void SyncEcho(const Brx& aaIn, Brh& aaOut);
    void BeginEcho(const Brx& aaIn, FunctorAsync& aFunctor);
    void EndEcho(IAsync& aAsync, Brh& aaOut);

    void SyncElfFile(Brh& aaElfFile);
    void BeginElfFile(FunctorAsync& aFunctor);
    void EndElfFile(IAsync& aAsync, Brh& aaElfFile);

    void SyncElfFingerprint(Brh& aaElfFileFingerprint);
    void BeginElfFingerprint(FunctorAsync& aFunctor);
    void EndElfFingerprint(IAsync& aAsync, Brh& aaElfFileFingerprint);

    void SyncCrashDataStatus(Brh& aaCrashDataStatus);
    void BeginCrashDataStatus(FunctorAsync& aFunctor);
    void EndCrashDataStatus(IAsync& aAsync, Brh& aaCrashDataStatus);

    void SyncCrashDataFetch(Brh& aaCrashData);
    void BeginCrashDataFetch(FunctorAsync& aFunctor);
    void EndCrashDataFetch(IAsync& aAsync, Brh& aaCrashData);

    void SyncCrashDataClear();
    void BeginCrashDataClear(FunctorAsync& aFunctor);
    void EndCrashDataClear(IAsync& aAsync);

    void SyncSysLog(Brh& aaSysLog);
    void BeginSysLog(FunctorAsync& aFunctor);
    void EndSysLog(IAsync& aAsync, Brh& aaSysLog);

    void SyncDiagnostic(const Brx& aaDiagnosticType, Brh& aaDiagnosticInfo);
    void BeginDiagnostic(const Brx& aaDiagnosticType, FunctorAsync& aFunctor);
    void EndDiagnostic(IAsync& aAsync, Brh& aaDiagnosticInfo);

    void SyncStateVariable(TUint& aaStateVariable);
    void BeginStateVariable(FunctorAsync& aFunctor);
    void EndStateVariable(IAsync& aAsync, TUint& aaStateVariable);

    void SyncSetStateVariable(TUint aaStateVariable);
    void BeginSetStateVariable(TUint aaStateVariable, FunctorAsync& aFunctor);
    void EndSetStateVariable(IAsync& aAsync);

    void SyncStateVariablePeriod(TUint& aaPeriod);
    void BeginStateVariablePeriod(FunctorAsync& aFunctor);
    void EndStateVariablePeriod(IAsync& aAsync, TUint& aaPeriod);

    void SyncSetStateVariablePeriod(TUint aaPeriod);
    void BeginSetStateVariablePeriod(TUint aaPeriod, FunctorAsync& aFunctor);
    void EndSetStateVariablePeriod(IAsync& aAsync);

    void SyncReboot(TUint aaDelay);
    void BeginReboot(TUint aaDelay, FunctorAsync& aFunctor);
    void EndReboot(IAsync& aAsync);

    void SetPropertyaStateVariableChanged(Functor& aFunctor);

    void PropertyaStateVariable(TUint& aaStateVariable) const;
private:
    void aStateVariablePropertyChanged();
private:
    Mutex iLock;
    Action* iActionEcho;
    Action* iActionElfFile;
    Action* iActionElfFingerprint;
    Action* iActionCrashDataStatus;
    Action* iActionCrashDataFetch;
    Action* iActionCrashDataClear;
    Action* iActionSysLog;
    Action* iActionDiagnostic;
    Action* iActionStateVariable;
    Action* iActionSetStateVariable;
    Action* iActionStateVariablePeriod;
    Action* iActionSetStateVariablePeriod;
    Action* iActionReboot;
    PropertyUint* iaStateVariable;
    Functor iaStateVariableChanged;
};


class SyncEchoLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncEchoLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaOut);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    Brh& iaOut;
};

SyncEchoLinnCoUkDiagnostics1C::SyncEchoLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaOut)
    : iService(aProxy)
    , iaOut(aaOut)
{
}

void SyncEchoLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndEcho(aAsync, iaOut);
}


class SyncElfFileLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncElfFileLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaElfFile);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    Brh& iaElfFile;
};

SyncElfFileLinnCoUkDiagnostics1C::SyncElfFileLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaElfFile)
    : iService(aProxy)
    , iaElfFile(aaElfFile)
{
}

void SyncElfFileLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndElfFile(aAsync, iaElfFile);
}


class SyncElfFingerprintLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncElfFingerprintLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaElfFileFingerprint);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    Brh& iaElfFileFingerprint;
};

SyncElfFingerprintLinnCoUkDiagnostics1C::SyncElfFingerprintLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaElfFileFingerprint)
    : iService(aProxy)
    , iaElfFileFingerprint(aaElfFileFingerprint)
{
}

void SyncElfFingerprintLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndElfFingerprint(aAsync, iaElfFileFingerprint);
}


class SyncCrashDataStatusLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncCrashDataStatusLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaCrashDataStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    Brh& iaCrashDataStatus;
};

SyncCrashDataStatusLinnCoUkDiagnostics1C::SyncCrashDataStatusLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaCrashDataStatus)
    : iService(aProxy)
    , iaCrashDataStatus(aaCrashDataStatus)
{
}

void SyncCrashDataStatusLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataStatus(aAsync, iaCrashDataStatus);
}


class SyncCrashDataFetchLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncCrashDataFetchLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaCrashData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    Brh& iaCrashData;
};

SyncCrashDataFetchLinnCoUkDiagnostics1C::SyncCrashDataFetchLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaCrashData)
    : iService(aProxy)
    , iaCrashData(aaCrashData)
{
}

void SyncCrashDataFetchLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataFetch(aAsync, iaCrashData);
}


class SyncCrashDataClearLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncCrashDataClearLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
};

SyncCrashDataClearLinnCoUkDiagnostics1C::SyncCrashDataClearLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy)
    : iService(aProxy)
{
}

void SyncCrashDataClearLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataClear(aAsync);
}


class SyncSysLogLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncSysLogLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaSysLog);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    Brh& iaSysLog;
};

SyncSysLogLinnCoUkDiagnostics1C::SyncSysLogLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaSysLog)
    : iService(aProxy)
    , iaSysLog(aaSysLog)
{
}

void SyncSysLogLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSysLog(aAsync, iaSysLog);
}


class SyncDiagnosticLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncDiagnosticLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaDiagnosticInfo);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    Brh& iaDiagnosticInfo;
};

SyncDiagnosticLinnCoUkDiagnostics1C::SyncDiagnosticLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, Brh& aaDiagnosticInfo)
    : iService(aProxy)
    , iaDiagnosticInfo(aaDiagnosticInfo)
{
}

void SyncDiagnosticLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiagnostic(aAsync, iaDiagnosticInfo);
}


class SyncStateVariableLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncStateVariableLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, TUint& aaStateVariable);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    TUint& iaStateVariable;
};

SyncStateVariableLinnCoUkDiagnostics1C::SyncStateVariableLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, TUint& aaStateVariable)
    : iService(aProxy)
    , iaStateVariable(aaStateVariable)
{
}

void SyncStateVariableLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStateVariable(aAsync, iaStateVariable);
}


class SyncSetStateVariableLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncSetStateVariableLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
};

SyncSetStateVariableLinnCoUkDiagnostics1C::SyncSetStateVariableLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStateVariableLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariable(aAsync);
}


class SyncStateVariablePeriodLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncStateVariablePeriodLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, TUint& aaPeriod);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
    TUint& iaPeriod;
};

SyncStateVariablePeriodLinnCoUkDiagnostics1C::SyncStateVariablePeriodLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy, TUint& aaPeriod)
    : iService(aProxy)
    , iaPeriod(aaPeriod)
{
}

void SyncStateVariablePeriodLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndStateVariablePeriod(aAsync, iaPeriod);
}


class SyncSetStateVariablePeriodLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncSetStateVariablePeriodLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
};

SyncSetStateVariablePeriodLinnCoUkDiagnostics1C::SyncSetStateVariablePeriodLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy)
    : iService(aProxy)
{
}

void SyncSetStateVariablePeriodLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariablePeriod(aAsync);
}


class SyncRebootLinnCoUkDiagnostics1C : public SyncProxyAction
{
public:
    SyncRebootLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1C& iService;
};

SyncRebootLinnCoUkDiagnostics1C::SyncRebootLinnCoUkDiagnostics1C(CpProxyLinnCoUkDiagnostics1C& aProxy)
    : iService(aProxy)
{
}

void SyncRebootLinnCoUkDiagnostics1C::CompleteRequest(IAsync& aAsync)
{
    iService.EndReboot(aAsync);
}

CpProxyLinnCoUkDiagnostics1C::CpProxyLinnCoUkDiagnostics1C(CpDeviceC aDevice)
    : CpProxyC("linn-co-uk", "Diagnostics", 1, *reinterpret_cast<CpiDevice*>(aDevice))
    , iLock("MPCS")
{
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDiagnostics1C::aStateVariablePropertyChanged);
    iaStateVariable = new PropertyUint("aStateVariable", functor);
    AddProperty(iaStateVariable);
}

CpProxyLinnCoUkDiagnostics1C::~CpProxyLinnCoUkDiagnostics1C()
{
    DestroyService();
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

void CpProxyLinnCoUkDiagnostics1C::SyncEcho(const Brx& aaIn, Brh& aaOut)
{
    SyncEchoLinnCoUkDiagnostics1C sync(*this, aaOut);
    BeginEcho(aaIn, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginEcho(const Brx& aaIn, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionEcho, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEcho->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaIn));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEcho->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndEcho(IAsync& aAsync, Brh& aaOut)
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

void CpProxyLinnCoUkDiagnostics1C::SyncElfFile(Brh& aaElfFile)
{
    SyncElfFileLinnCoUkDiagnostics1C sync(*this, aaElfFile);
    BeginElfFile(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginElfFile(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionElfFile, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionElfFile->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndElfFile(IAsync& aAsync, Brh& aaElfFile)
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

void CpProxyLinnCoUkDiagnostics1C::SyncElfFingerprint(Brh& aaElfFileFingerprint)
{
    SyncElfFingerprintLinnCoUkDiagnostics1C sync(*this, aaElfFileFingerprint);
    BeginElfFingerprint(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginElfFingerprint(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionElfFingerprint, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionElfFingerprint->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndElfFingerprint(IAsync& aAsync, Brh& aaElfFileFingerprint)
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

void CpProxyLinnCoUkDiagnostics1C::SyncCrashDataStatus(Brh& aaCrashDataStatus)
{
    SyncCrashDataStatusLinnCoUkDiagnostics1C sync(*this, aaCrashDataStatus);
    BeginCrashDataStatus(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginCrashDataStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCrashDataStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCrashDataStatus->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndCrashDataStatus(IAsync& aAsync, Brh& aaCrashDataStatus)
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

void CpProxyLinnCoUkDiagnostics1C::SyncCrashDataFetch(Brh& aaCrashData)
{
    SyncCrashDataFetchLinnCoUkDiagnostics1C sync(*this, aaCrashData);
    BeginCrashDataFetch(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginCrashDataFetch(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCrashDataFetch, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCrashDataFetch->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndCrashDataFetch(IAsync& aAsync, Brh& aaCrashData)
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

void CpProxyLinnCoUkDiagnostics1C::SyncCrashDataClear()
{
    SyncCrashDataClearLinnCoUkDiagnostics1C sync(*this);
    BeginCrashDataClear(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginCrashDataClear(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionCrashDataClear, aFunctor);
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndCrashDataClear(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CrashDataClear"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1C::SyncSysLog(Brh& aaSysLog)
{
    SyncSysLogLinnCoUkDiagnostics1C sync(*this, aaSysLog);
    BeginSysLog(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginSysLog(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSysLog, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSysLog->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndSysLog(IAsync& aAsync, Brh& aaSysLog)
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

void CpProxyLinnCoUkDiagnostics1C::SyncDiagnostic(const Brx& aaDiagnosticType, Brh& aaDiagnosticInfo)
{
    SyncDiagnosticLinnCoUkDiagnostics1C sync(*this, aaDiagnosticInfo);
    BeginDiagnostic(aaDiagnosticType, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginDiagnostic(const Brx& aaDiagnosticType, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionDiagnostic, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDiagnostic->InputParameters();
    invocation->AddInput(new ArgumentString(*inParams[inIndex++], aaDiagnosticType));
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiagnostic->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndDiagnostic(IAsync& aAsync, Brh& aaDiagnosticInfo)
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

void CpProxyLinnCoUkDiagnostics1C::SyncStateVariable(TUint& aaStateVariable)
{
    SyncStateVariableLinnCoUkDiagnostics1C sync(*this, aaStateVariable);
    BeginStateVariable(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginStateVariable(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStateVariable, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStateVariable->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndStateVariable(IAsync& aAsync, TUint& aaStateVariable)
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

void CpProxyLinnCoUkDiagnostics1C::SyncSetStateVariable(TUint aaStateVariable)
{
    SyncSetStateVariableLinnCoUkDiagnostics1C sync(*this);
    BeginSetStateVariable(aaStateVariable, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginSetStateVariable(TUint aaStateVariable, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStateVariable, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariable->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaStateVariable));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndSetStateVariable(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariable"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1C::SyncStateVariablePeriod(TUint& aaPeriod)
{
    SyncStateVariablePeriodLinnCoUkDiagnostics1C sync(*this, aaPeriod);
    BeginStateVariablePeriod(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginStateVariablePeriod(FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionStateVariablePeriod, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStateVariablePeriod->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndStateVariablePeriod(IAsync& aAsync, TUint& aaPeriod)
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

void CpProxyLinnCoUkDiagnostics1C::SyncSetStateVariablePeriod(TUint aaPeriod)
{
    SyncSetStateVariablePeriodLinnCoUkDiagnostics1C sync(*this);
    BeginSetStateVariablePeriod(aaPeriod, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginSetStateVariablePeriod(TUint aaPeriod, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionSetStateVariablePeriod, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariablePeriod->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPeriod));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndSetStateVariablePeriod(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariablePeriod"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1C::SyncReboot(TUint aaDelay)
{
    SyncRebootLinnCoUkDiagnostics1C sync(*this);
    BeginReboot(aaDelay, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1C::BeginReboot(TUint aaDelay, FunctorAsync& aFunctor)
{
    Invocation* invocation = Service()->Invocation(*iActionReboot, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReboot->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDelay));
    Invocable().InvokeAction(*invocation);
}

void CpProxyLinnCoUkDiagnostics1C::EndReboot(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Reboot"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1C::SetPropertyaStateVariableChanged(Functor& aFunctor)
{
    iLock.Wait();
    iaStateVariableChanged = aFunctor;
    iLock.Signal();
}

void CpProxyLinnCoUkDiagnostics1C::PropertyaStateVariable(TUint& aaStateVariable) const
{
    PropertyReadLock();
    ASSERT(IsSubscribed());
    aaStateVariable = iaStateVariable->Value();
    PropertyReadUnlock();
}

void CpProxyLinnCoUkDiagnostics1C::aStateVariablePropertyChanged()
{
    ReportEvent(iaStateVariableChanged);
}


THandle CpProxyLinnCoUkDiagnostics1Create(CpDeviceC aDevice)
{
    return new CpProxyLinnCoUkDiagnostics1C(aDevice);
}

void CpProxyLinnCoUkDiagnostics1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkDiagnostics1SyncEcho(THandle aHandle, const char* aaIn, char** aaOut)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIn(aaIn);
    Brh buf_aaOut;
    proxyC->SyncEcho(buf_aaIn, buf_aaOut);
    *aaOut = buf_aaOut.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginEcho(THandle aHandle, const char* aaIn, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIn(aaIn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginEcho(buf_aaIn, functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndEcho(THandle aHandle, ZappHandleAsync aAsync, char** aaOut)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaOut;
    *aaOut = NULL;
    try {
        proxyC->EndEcho(*async, buf_aaOut);
        *aaOut = buf_aaOut.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncElfFile(THandle aHandle, char** aaElfFile)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaElfFile;
    proxyC->SyncElfFile(buf_aaElfFile);
    *aaElfFile = buf_aaElfFile.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginElfFile(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginElfFile(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndElfFile(THandle aHandle, ZappHandleAsync aAsync, char** aaElfFile)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaElfFile;
    *aaElfFile = NULL;
    try {
        proxyC->EndElfFile(*async, buf_aaElfFile);
        *aaElfFile = buf_aaElfFile.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncElfFingerprint(THandle aHandle, char** aaElfFileFingerprint)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaElfFileFingerprint;
    proxyC->SyncElfFingerprint(buf_aaElfFileFingerprint);
    *aaElfFileFingerprint = buf_aaElfFileFingerprint.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginElfFingerprint(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginElfFingerprint(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndElfFingerprint(THandle aHandle, ZappHandleAsync aAsync, char** aaElfFileFingerprint)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaElfFileFingerprint;
    *aaElfFileFingerprint = NULL;
    try {
        proxyC->EndElfFingerprint(*async, buf_aaElfFileFingerprint);
        *aaElfFileFingerprint = buf_aaElfFileFingerprint.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncCrashDataStatus(THandle aHandle, char** aaCrashDataStatus)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCrashDataStatus;
    proxyC->SyncCrashDataStatus(buf_aaCrashDataStatus);
    *aaCrashDataStatus = buf_aaCrashDataStatus.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginCrashDataStatus(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginCrashDataStatus(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndCrashDataStatus(THandle aHandle, ZappHandleAsync aAsync, char** aaCrashDataStatus)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaCrashDataStatus;
    *aaCrashDataStatus = NULL;
    try {
        proxyC->EndCrashDataStatus(*async, buf_aaCrashDataStatus);
        *aaCrashDataStatus = buf_aaCrashDataStatus.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncCrashDataFetch(THandle aHandle, char** aaCrashData, uint32_t* aaCrashDataLen)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCrashData;
    proxyC->SyncCrashDataFetch(buf_aaCrashData);
    *aaCrashDataLen = buf_aaCrashData.Bytes();
    *aaCrashData = buf_aaCrashData.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginCrashDataFetch(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginCrashDataFetch(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndCrashDataFetch(THandle aHandle, ZappHandleAsync aAsync, char** aaCrashData, uint32_t* aaCrashDataLen)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaCrashData;
    *aaCrashData = NULL;
    *aaCrashDataLen = 0;
    try {
        proxyC->EndCrashDataFetch(*async, buf_aaCrashData);
        *aaCrashDataLen = buf_aaCrashData.Bytes();
        *aaCrashData = buf_aaCrashData.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncCrashDataClear(THandle aHandle)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncCrashDataClear();
}

void CpProxyLinnCoUkDiagnostics1BeginCrashDataClear(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginCrashDataClear(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndCrashDataClear(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndCrashDataClear(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncSysLog(THandle aHandle, char** aaSysLog, uint32_t* aaSysLogLen)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSysLog;
    proxyC->SyncSysLog(buf_aaSysLog);
    *aaSysLogLen = buf_aaSysLog.Bytes();
    *aaSysLog = buf_aaSysLog.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginSysLog(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSysLog(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndSysLog(THandle aHandle, ZappHandleAsync aAsync, char** aaSysLog, uint32_t* aaSysLogLen)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSysLog;
    *aaSysLog = NULL;
    *aaSysLogLen = 0;
    try {
        proxyC->EndSysLog(*async, buf_aaSysLog);
        *aaSysLogLen = buf_aaSysLog.Bytes();
        *aaSysLog = buf_aaSysLog.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncDiagnostic(THandle aHandle, const char* aaDiagnosticType, char** aaDiagnosticInfo)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaDiagnosticType(aaDiagnosticType);
    Brh buf_aaDiagnosticInfo;
    proxyC->SyncDiagnostic(buf_aaDiagnosticType, buf_aaDiagnosticInfo);
    *aaDiagnosticInfo = buf_aaDiagnosticInfo.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginDiagnostic(THandle aHandle, const char* aaDiagnosticType, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaDiagnosticType(aaDiagnosticType);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginDiagnostic(buf_aaDiagnosticType, functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndDiagnostic(THandle aHandle, ZappHandleAsync aAsync, char** aaDiagnosticInfo)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaDiagnosticInfo;
    *aaDiagnosticInfo = NULL;
    try {
        proxyC->EndDiagnostic(*async, buf_aaDiagnosticInfo);
        *aaDiagnosticInfo = buf_aaDiagnosticInfo.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncStateVariable(THandle aHandle, uint32_t* aaStateVariable)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStateVariable(*aaStateVariable);
}

void CpProxyLinnCoUkDiagnostics1BeginStateVariable(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStateVariable(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndStateVariable(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStateVariable)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStateVariable(*async, *aaStateVariable);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncSetStateVariable(THandle aHandle, uint32_t aaStateVariable)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStateVariable(aaStateVariable);
}

void CpProxyLinnCoUkDiagnostics1BeginSetStateVariable(THandle aHandle, uint32_t aaStateVariable, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStateVariable(aaStateVariable, functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndSetStateVariable(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStateVariable(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncStateVariablePeriod(THandle aHandle, uint32_t* aaPeriod)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncStateVariablePeriod(*aaPeriod);
}

void CpProxyLinnCoUkDiagnostics1BeginStateVariablePeriod(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginStateVariablePeriod(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndStateVariablePeriod(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPeriod)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndStateVariablePeriod(*async, *aaPeriod);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncSetStateVariablePeriod(THandle aHandle, uint32_t aaPeriod)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncSetStateVariablePeriod(aaPeriod);
}

void CpProxyLinnCoUkDiagnostics1BeginSetStateVariablePeriod(THandle aHandle, uint32_t aaPeriod, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginSetStateVariablePeriod(aaPeriod, functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndSetStateVariablePeriod(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndSetStateVariablePeriod(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SyncReboot(THandle aHandle, uint32_t aaDelay)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->SyncReboot(aaDelay);
}

void CpProxyLinnCoUkDiagnostics1BeginReboot(THandle aHandle, uint32_t aaDelay, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->BeginReboot(aaDelay, functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndReboot(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->EndReboot(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDiagnostics1SetPropertyaStateVariableChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->SetPropertyaStateVariableChanged(functor);
}

void CpProxyLinnCoUkDiagnostics1PropertyaStateVariable(THandle aHandle, uint32_t* aaStateVariable)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->PropertyaStateVariable(*aaStateVariable);
}

