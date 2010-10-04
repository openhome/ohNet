#include <Core/DvLinnCoUkDiagnostics1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkDiagnostics1::SetPropertyaStateVariable(TUint aValue)
{
    SetPropertyUint(*iPropertyaStateVariable, aValue);
}

void DvServiceLinnCoUkDiagnostics1::GetPropertyaStateVariable(TUint& aValue)
{
    aValue = iPropertyaStateVariable->Value();
}

DvServiceLinnCoUkDiagnostics1::DvServiceLinnCoUkDiagnostics1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Diagnostics", 1)
{
    Functor empty;
    iPropertyaStateVariable = new PropertyUint(new ParameterUint("aStateVariable"), empty);
    iService->AddProperty(iPropertyaStateVariable); // passes ownership
}

void DvServiceLinnCoUkDiagnostics1::EnableActionEcho()
{
    Zapp::Action* action = new Zapp::Action("Echo");
    action->AddInputParameter(new ParameterString("aIn"));
    action->AddOutputParameter(new ParameterString("aOut"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoEcho);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionElfFile()
{
    Zapp::Action* action = new Zapp::Action("ElfFile");
    action->AddOutputParameter(new ParameterString("aElfFile"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoElfFile);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionElfFingerprint()
{
    Zapp::Action* action = new Zapp::Action("ElfFingerprint");
    action->AddOutputParameter(new ParameterString("aElfFileFingerprint"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoElfFingerprint);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionCrashDataStatus()
{
    Zapp::Action* action = new Zapp::Action("CrashDataStatus");
    action->AddOutputParameter(new ParameterString("aCrashDataStatus"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoCrashDataStatus);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionCrashDataFetch()
{
    Zapp::Action* action = new Zapp::Action("CrashDataFetch");
    action->AddOutputParameter(new ParameterBinary("aCrashData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoCrashDataFetch);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionCrashDataClear()
{
    Zapp::Action* action = new Zapp::Action("CrashDataClear");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoCrashDataClear);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionSysLog()
{
    Zapp::Action* action = new Zapp::Action("SysLog");
    action->AddOutputParameter(new ParameterBinary("aSysLog"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoSysLog);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionDiagnostic()
{
    Zapp::Action* action = new Zapp::Action("Diagnostic");
    action->AddInputParameter(new ParameterString("aDiagnosticType"));
    action->AddOutputParameter(new ParameterString("aDiagnosticInfo"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoDiagnostic);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionStateVariable()
{
    Zapp::Action* action = new Zapp::Action("StateVariable");
    action->AddOutputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoStateVariable);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionSetStateVariable()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariable");
    action->AddInputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoSetStateVariable);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionStateVariablePeriod()
{
    Zapp::Action* action = new Zapp::Action("StateVariablePeriod");
    action->AddOutputParameter(new ParameterUint("aPeriod"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionSetStateVariablePeriod()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariablePeriod");
    action->AddInputParameter(new ParameterUint("aPeriod"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoSetStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::EnableActionReboot()
{
    Zapp::Action* action = new Zapp::Action("Reboot");
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1::DoReboot);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1::DoEcho(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIn;
    aInvocation.InvocationReadString("aIn", aIn);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaOut(aInvocation, "aOut");
    Echo(resp, aVersion, aIn, respaOut);
}

void DvServiceLinnCoUkDiagnostics1::DoElfFile(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaElfFile(aInvocation, "aElfFile");
    ElfFile(resp, aVersion, respaElfFile);
}

void DvServiceLinnCoUkDiagnostics1::DoElfFingerprint(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaElfFileFingerprint(aInvocation, "aElfFileFingerprint");
    ElfFingerprint(resp, aVersion, respaElfFileFingerprint);
}

void DvServiceLinnCoUkDiagnostics1::DoCrashDataStatus(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaCrashDataStatus(aInvocation, "aCrashDataStatus");
    CrashDataStatus(resp, aVersion, respaCrashDataStatus);
}

void DvServiceLinnCoUkDiagnostics1::DoCrashDataFetch(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBinary respaCrashData(aInvocation, "aCrashData");
    CrashDataFetch(resp, aVersion, respaCrashData);
}

void DvServiceLinnCoUkDiagnostics1::DoCrashDataClear(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    CrashDataClear(resp, aVersion);
}

void DvServiceLinnCoUkDiagnostics1::DoSysLog(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBinary respaSysLog(aInvocation, "aSysLog");
    SysLog(resp, aVersion, respaSysLog);
}

void DvServiceLinnCoUkDiagnostics1::DoDiagnostic(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aDiagnosticType;
    aInvocation.InvocationReadString("aDiagnosticType", aDiagnosticType);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaDiagnosticInfo(aInvocation, "aDiagnosticInfo");
    Diagnostic(resp, aVersion, aDiagnosticType, respaDiagnosticInfo);
}

void DvServiceLinnCoUkDiagnostics1::DoStateVariable(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaStateVariable(aInvocation, "aStateVariable");
    StateVariable(resp, aVersion, respaStateVariable);
}

void DvServiceLinnCoUkDiagnostics1::DoSetStateVariable(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aStateVariable = aInvocation.InvocationReadUint("aStateVariable");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStateVariable(resp, aVersion, aStateVariable);
}

void DvServiceLinnCoUkDiagnostics1::DoStateVariablePeriod(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaPeriod(aInvocation, "aPeriod");
    StateVariablePeriod(resp, aVersion, respaPeriod);
}

void DvServiceLinnCoUkDiagnostics1::DoSetStateVariablePeriod(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPeriod = aInvocation.InvocationReadUint("aPeriod");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStateVariablePeriod(resp, aVersion, aPeriod);
}

void DvServiceLinnCoUkDiagnostics1::DoReboot(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Reboot(resp, aVersion, aDelay);
}

void DvServiceLinnCoUkDiagnostics1::Echo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaIn*/, IInvocationResponseString& /*aaOut*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::ElfFile(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaElfFile*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::ElfFingerprint(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaElfFileFingerprint*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::CrashDataStatus(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaCrashDataStatus*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::CrashDataFetch(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBinary& /*aaCrashData*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::CrashDataClear(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::SysLog(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBinary& /*aaSysLog*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::Diagnostic(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaDiagnosticType*/, IInvocationResponseString& /*aaDiagnosticInfo*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::StateVariable(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaStateVariable*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::SetStateVariable(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaStateVariable*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::StateVariablePeriod(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaPeriod*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::SetStateVariablePeriod(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaPeriod*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1::Reboot(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaDelay*/)
{
    ASSERTS();
}

