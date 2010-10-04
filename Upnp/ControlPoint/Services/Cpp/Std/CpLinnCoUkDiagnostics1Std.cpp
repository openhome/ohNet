#include <Std/CpLinnCoUkDiagnostics1.h>
#include <CpProxy.h>
#include <CpiService.h>
#include <Thread.h>
#include <AsyncPrivate.h>
#include <Buffer.h>
#include <Std/CpDevice.h>

#include <string>

using namespace Zapp;


class SyncEchoLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncEchoLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaOut);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    std::string& iaOut;
};

SyncEchoLinnCoUkDiagnostics1Cpp::SyncEchoLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaOut)
    : iService(aService)
    , iaOut(aaOut)
{
}

void SyncEchoLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndEcho(aAsync, iaOut);
}


class SyncElfFileLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncElfFileLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaElfFile);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    std::string& iaElfFile;
};

SyncElfFileLinnCoUkDiagnostics1Cpp::SyncElfFileLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaElfFile)
    : iService(aService)
    , iaElfFile(aaElfFile)
{
}

void SyncElfFileLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndElfFile(aAsync, iaElfFile);
}


class SyncElfFingerprintLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncElfFingerprintLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaElfFileFingerprint);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    std::string& iaElfFileFingerprint;
};

SyncElfFingerprintLinnCoUkDiagnostics1Cpp::SyncElfFingerprintLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaElfFileFingerprint)
    : iService(aService)
    , iaElfFileFingerprint(aaElfFileFingerprint)
{
}

void SyncElfFingerprintLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndElfFingerprint(aAsync, iaElfFileFingerprint);
}


class SyncCrashDataStatusLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncCrashDataStatusLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaCrashDataStatus);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    std::string& iaCrashDataStatus;
};

SyncCrashDataStatusLinnCoUkDiagnostics1Cpp::SyncCrashDataStatusLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaCrashDataStatus)
    : iService(aService)
    , iaCrashDataStatus(aaCrashDataStatus)
{
}

void SyncCrashDataStatusLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataStatus(aAsync, iaCrashDataStatus);
}


class SyncCrashDataFetchLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncCrashDataFetchLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaCrashData);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    std::string& iaCrashData;
};

SyncCrashDataFetchLinnCoUkDiagnostics1Cpp::SyncCrashDataFetchLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaCrashData)
    : iService(aService)
    , iaCrashData(aaCrashData)
{
}

void SyncCrashDataFetchLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataFetch(aAsync, iaCrashData);
}


class SyncCrashDataClearLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncCrashDataClearLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
};

SyncCrashDataClearLinnCoUkDiagnostics1Cpp::SyncCrashDataClearLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService)
    : iService(aService)
{
}

void SyncCrashDataClearLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndCrashDataClear(aAsync);
}


class SyncSysLogLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncSysLogLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaSysLog);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    std::string& iaSysLog;
};

SyncSysLogLinnCoUkDiagnostics1Cpp::SyncSysLogLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaSysLog)
    : iService(aService)
    , iaSysLog(aaSysLog)
{
}

void SyncSysLogLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSysLog(aAsync, iaSysLog);
}


class SyncDiagnosticLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncDiagnosticLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaDiagnosticInfo);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    std::string& iaDiagnosticInfo;
};

SyncDiagnosticLinnCoUkDiagnostics1Cpp::SyncDiagnosticLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, std::string& aaDiagnosticInfo)
    : iService(aService)
    , iaDiagnosticInfo(aaDiagnosticInfo)
{
}

void SyncDiagnosticLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndDiagnostic(aAsync, iaDiagnosticInfo);
}


class SyncStateVariableLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncStateVariableLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, uint32_t& aaStateVariable);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    uint32_t& iaStateVariable;
};

SyncStateVariableLinnCoUkDiagnostics1Cpp::SyncStateVariableLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, uint32_t& aaStateVariable)
    : iService(aService)
    , iaStateVariable(aaStateVariable)
{
}

void SyncStateVariableLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStateVariable(aAsync, iaStateVariable);
}


class SyncSetStateVariableLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncSetStateVariableLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
};

SyncSetStateVariableLinnCoUkDiagnostics1Cpp::SyncSetStateVariableLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService)
    : iService(aService)
{
}

void SyncSetStateVariableLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariable(aAsync);
}


class SyncStateVariablePeriodLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncStateVariablePeriodLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, uint32_t& aaPeriod);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
    uint32_t& iaPeriod;
};

SyncStateVariablePeriodLinnCoUkDiagnostics1Cpp::SyncStateVariablePeriodLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService, uint32_t& aaPeriod)
    : iService(aService)
    , iaPeriod(aaPeriod)
{
}

void SyncStateVariablePeriodLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndStateVariablePeriod(aAsync, iaPeriod);
}


class SyncSetStateVariablePeriodLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncSetStateVariablePeriodLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
};

SyncSetStateVariablePeriodLinnCoUkDiagnostics1Cpp::SyncSetStateVariablePeriodLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService)
    : iService(aService)
{
}

void SyncSetStateVariablePeriodLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndSetStateVariablePeriod(aAsync);
}


class SyncRebootLinnCoUkDiagnostics1Cpp : public SyncProxyAction
{
public:
    SyncRebootLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService);
    virtual void CompleteRequest(IAsync& aAsync);
private:
    CpProxyLinnCoUkDiagnostics1Cpp& iService;
};

SyncRebootLinnCoUkDiagnostics1Cpp::SyncRebootLinnCoUkDiagnostics1Cpp(CpProxyLinnCoUkDiagnostics1Cpp& aService)
    : iService(aService)
{
}

void SyncRebootLinnCoUkDiagnostics1Cpp::CompleteRequest(IAsync& aAsync)
{
    iService.EndReboot(aAsync);
}


CpProxyLinnCoUkDiagnostics1Cpp::CpProxyLinnCoUkDiagnostics1Cpp(CpDeviceCpp& aDevice)
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
    functor = MakeFunctor(*this, &CpProxyLinnCoUkDiagnostics1Cpp::aStateVariablePropertyChanged);
    iaStateVariable = new PropertyUint("aStateVariable", functor);
    iService->AddProperty(iaStateVariable);
}

CpProxyLinnCoUkDiagnostics1Cpp::~CpProxyLinnCoUkDiagnostics1Cpp()
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

void CpProxyLinnCoUkDiagnostics1Cpp::SyncEcho(const std::string& aaIn, std::string& aaOut)
{
    SyncEchoLinnCoUkDiagnostics1Cpp sync(*this, aaOut);
    BeginEcho(aaIn, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginEcho(const std::string& aaIn, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionEcho, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionEcho->InputParameters();
    {
        Brn buf((const TByte*)aaIn.c_str(), aaIn.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionEcho->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndEcho(IAsync& aAsync, std::string& aaOut)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Echo"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaOut.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncElfFile(std::string& aaElfFile)
{
    SyncElfFileLinnCoUkDiagnostics1Cpp sync(*this, aaElfFile);
    BeginElfFile(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginElfFile(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionElfFile, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionElfFile->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndElfFile(IAsync& aAsync, std::string& aaElfFile)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ElfFile"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaElfFile.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncElfFingerprint(std::string& aaElfFileFingerprint)
{
    SyncElfFingerprintLinnCoUkDiagnostics1Cpp sync(*this, aaElfFileFingerprint);
    BeginElfFingerprint(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginElfFingerprint(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionElfFingerprint, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionElfFingerprint->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndElfFingerprint(IAsync& aAsync, std::string& aaElfFileFingerprint)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("ElfFingerprint"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaElfFileFingerprint.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncCrashDataStatus(std::string& aaCrashDataStatus)
{
    SyncCrashDataStatusLinnCoUkDiagnostics1Cpp sync(*this, aaCrashDataStatus);
    BeginCrashDataStatus(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginCrashDataStatus(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCrashDataStatus, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCrashDataStatus->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndCrashDataStatus(IAsync& aAsync, std::string& aaCrashDataStatus)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CrashDataStatus"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaCrashDataStatus.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncCrashDataFetch(std::string& aaCrashData)
{
    SyncCrashDataFetchLinnCoUkDiagnostics1Cpp sync(*this, aaCrashData);
    BeginCrashDataFetch(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginCrashDataFetch(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCrashDataFetch, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionCrashDataFetch->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndCrashDataFetch(IAsync& aAsync, std::string& aaCrashData)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CrashDataFetch"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaCrashData.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncCrashDataClear()
{
    SyncCrashDataClearLinnCoUkDiagnostics1Cpp sync(*this);
    BeginCrashDataClear(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginCrashDataClear(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionCrashDataClear, aFunctor);
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndCrashDataClear(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("CrashDataClear"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncSysLog(std::string& aaSysLog)
{
    SyncSysLogLinnCoUkDiagnostics1Cpp sync(*this, aaSysLog);
    BeginSysLog(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginSysLog(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSysLog, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionSysLog->OutputParameters();
    invocation->AddOutput(new ArgumentBinary(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndSysLog(IAsync& aAsync, std::string& aaSysLog)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SysLog"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaSysLog.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncDiagnostic(const std::string& aaDiagnosticType, std::string& aaDiagnosticInfo)
{
    SyncDiagnosticLinnCoUkDiagnostics1Cpp sync(*this, aaDiagnosticInfo);
    BeginDiagnostic(aaDiagnosticType, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginDiagnostic(const std::string& aaDiagnosticType, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionDiagnostic, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionDiagnostic->InputParameters();
    {
        Brn buf((const TByte*)aaDiagnosticType.c_str(), aaDiagnosticType.length());
        invocation->AddInput(new ArgumentString(*inParams[inIndex++], buf));
    }
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionDiagnostic->OutputParameters();
    invocation->AddOutput(new ArgumentString(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndDiagnostic(IAsync& aAsync, std::string& aaDiagnosticInfo)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Diagnostic"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
    TUint index = 0;
    {
        const Brx& val = ((ArgumentString*)invocation.OutputArguments()[index++])->Value();
        aaDiagnosticInfo.assign((const char*)val.Ptr(), val.Bytes());
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncStateVariable(uint32_t& aaStateVariable)
{
    SyncStateVariableLinnCoUkDiagnostics1Cpp sync(*this, aaStateVariable);
    BeginStateVariable(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginStateVariable(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStateVariable, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStateVariable->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndStateVariable(IAsync& aAsync, uint32_t& aaStateVariable)
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

void CpProxyLinnCoUkDiagnostics1Cpp::SyncSetStateVariable(uint32_t aaStateVariable)
{
    SyncSetStateVariableLinnCoUkDiagnostics1Cpp sync(*this);
    BeginSetStateVariable(aaStateVariable, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginSetStateVariable(uint32_t aaStateVariable, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStateVariable, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariable->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaStateVariable));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndSetStateVariable(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariable"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncStateVariablePeriod(uint32_t& aaPeriod)
{
    SyncStateVariablePeriodLinnCoUkDiagnostics1Cpp sync(*this, aaPeriod);
    BeginStateVariablePeriod(sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginStateVariablePeriod(FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionStateVariablePeriod, aFunctor);
    TUint outIndex = 0;
    const Action::VectorParameters& outParams = iActionStateVariablePeriod->OutputParameters();
    invocation->AddOutput(new ArgumentUint(*outParams[outIndex++]));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndStateVariablePeriod(IAsync& aAsync, uint32_t& aaPeriod)
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

void CpProxyLinnCoUkDiagnostics1Cpp::SyncSetStateVariablePeriod(uint32_t aaPeriod)
{
    SyncSetStateVariablePeriodLinnCoUkDiagnostics1Cpp sync(*this);
    BeginSetStateVariablePeriod(aaPeriod, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginSetStateVariablePeriod(uint32_t aaPeriod, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionSetStateVariablePeriod, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionSetStateVariablePeriod->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaPeriod));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndSetStateVariablePeriod(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("SetStateVariablePeriod"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SyncReboot(uint32_t aaDelay)
{
    SyncRebootLinnCoUkDiagnostics1Cpp sync(*this);
    BeginReboot(aaDelay, sync.Functor());
    sync.Wait();
}

void CpProxyLinnCoUkDiagnostics1Cpp::BeginReboot(uint32_t aaDelay, FunctorAsync& aFunctor)
{
    Invocation* invocation = iService->Invocation(*iActionReboot, aFunctor);
    TUint inIndex = 0;
    const Action::VectorParameters& inParams = iActionReboot->InputParameters();
    invocation->AddInput(new ArgumentUint(*inParams[inIndex++], aaDelay));
    invocation->Invoke();
}

void CpProxyLinnCoUkDiagnostics1Cpp::EndReboot(IAsync& aAsync)
{
    ASSERT(((Async&)aAsync).Type() == Async::eInvocation);
    Invocation& invocation = (Invocation&)aAsync;
    ASSERT(invocation.Action().Name() == Brn("Reboot"));

    if (invocation.Error()) {
        THROW(ProxyError);
    }
}

void CpProxyLinnCoUkDiagnostics1Cpp::SetPropertyaStateVariableChanged(Functor& aFunctor)
{
    iLock->Wait();
    iaStateVariableChanged = aFunctor;
    iLock->Signal();
}

void CpProxyLinnCoUkDiagnostics1Cpp::PropertyaStateVariable(uint32_t& aaStateVariable) const
{
    ASSERT(iCpSubscriptionStatus == CpProxy::eSubscribed);
    aaStateVariable = iaStateVariable->Value();
}

void CpProxyLinnCoUkDiagnostics1Cpp::aStateVariablePropertyChanged()
{
    if (!ReportEvent()) {
        return;
    }
    AutoMutex a(*iLock);
    if (iCpSubscriptionStatus == CpProxy::eSubscribed && iaStateVariableChanged != NULL) {
        iaStateVariableChanged();
    }
}

