#include <Core/DvLinnCoUkDiagnostics1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

TBool DvProviderLinnCoUkDiagnostics1::SetPropertyaStateVariable(TUint aValue)
{
    return SetPropertyUint(*iPropertyaStateVariable, aValue);
}

void DvProviderLinnCoUkDiagnostics1::GetPropertyaStateVariable(TUint& aValue)
{
    aValue = iPropertyaStateVariable->Value();
}

DvProviderLinnCoUkDiagnostics1::DvProviderLinnCoUkDiagnostics1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Diagnostics", 1)
{
    
    iPropertyaStateVariable = new PropertyUint(new ParameterUint("aStateVariable"));
    iService->AddProperty(iPropertyaStateVariable); // passes ownership
}

void DvProviderLinnCoUkDiagnostics1::EnableActionEcho()
{
    Zapp::Action* action = new Zapp::Action("Echo");
    action->AddInputParameter(new ParameterString("aIn"));
    action->AddOutputParameter(new ParameterString("aOut"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoEcho);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionElfFile()
{
    Zapp::Action* action = new Zapp::Action("ElfFile");
    action->AddOutputParameter(new ParameterString("aElfFile"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoElfFile);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionElfFingerprint()
{
    Zapp::Action* action = new Zapp::Action("ElfFingerprint");
    action->AddOutputParameter(new ParameterString("aElfFileFingerprint"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoElfFingerprint);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionCrashDataStatus()
{
    Zapp::Action* action = new Zapp::Action("CrashDataStatus");
    action->AddOutputParameter(new ParameterString("aCrashDataStatus"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoCrashDataStatus);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionCrashDataFetch()
{
    Zapp::Action* action = new Zapp::Action("CrashDataFetch");
    action->AddOutputParameter(new ParameterBinary("aCrashData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoCrashDataFetch);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionCrashDataClear()
{
    Zapp::Action* action = new Zapp::Action("CrashDataClear");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoCrashDataClear);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionSysLog()
{
    Zapp::Action* action = new Zapp::Action("SysLog");
    action->AddOutputParameter(new ParameterBinary("aSysLog"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoSysLog);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionDiagnostic()
{
    Zapp::Action* action = new Zapp::Action("Diagnostic");
    action->AddInputParameter(new ParameterString("aDiagnosticType"));
    action->AddOutputParameter(new ParameterString("aDiagnosticInfo"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoDiagnostic);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionStateVariable()
{
    Zapp::Action* action = new Zapp::Action("StateVariable");
    action->AddOutputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoStateVariable);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionSetStateVariable()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariable");
    action->AddInputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoSetStateVariable);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionStateVariablePeriod()
{
    Zapp::Action* action = new Zapp::Action("StateVariablePeriod");
    action->AddOutputParameter(new ParameterUint("aPeriod"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionSetStateVariablePeriod()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariablePeriod");
    action->AddInputParameter(new ParameterUint("aPeriod"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoSetStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::EnableActionReboot()
{
    Zapp::Action* action = new Zapp::Action("Reboot");
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1::DoReboot);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1::DoEcho(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIn;
    aInvocation.InvocationReadString("aIn", aIn);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaOut(aInvocation, "aOut");
    Echo(resp, aVersion, aIn, respaOut);
}

void DvProviderLinnCoUkDiagnostics1::DoElfFile(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaElfFile(aInvocation, "aElfFile");
    ElfFile(resp, aVersion, respaElfFile);
}

void DvProviderLinnCoUkDiagnostics1::DoElfFingerprint(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaElfFileFingerprint(aInvocation, "aElfFileFingerprint");
    ElfFingerprint(resp, aVersion, respaElfFileFingerprint);
}

void DvProviderLinnCoUkDiagnostics1::DoCrashDataStatus(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaCrashDataStatus(aInvocation, "aCrashDataStatus");
    CrashDataStatus(resp, aVersion, respaCrashDataStatus);
}

void DvProviderLinnCoUkDiagnostics1::DoCrashDataFetch(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBinary respaCrashData(aInvocation, "aCrashData");
    CrashDataFetch(resp, aVersion, respaCrashData);
}

void DvProviderLinnCoUkDiagnostics1::DoCrashDataClear(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    CrashDataClear(resp, aVersion);
}

void DvProviderLinnCoUkDiagnostics1::DoSysLog(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseBinary respaSysLog(aInvocation, "aSysLog");
    SysLog(resp, aVersion, respaSysLog);
}

void DvProviderLinnCoUkDiagnostics1::DoDiagnostic(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aDiagnosticType;
    aInvocation.InvocationReadString("aDiagnosticType", aDiagnosticType);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respaDiagnosticInfo(aInvocation, "aDiagnosticInfo");
    Diagnostic(resp, aVersion, aDiagnosticType, respaDiagnosticInfo);
}

void DvProviderLinnCoUkDiagnostics1::DoStateVariable(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaStateVariable(aInvocation, "aStateVariable");
    StateVariable(resp, aVersion, respaStateVariable);
}

void DvProviderLinnCoUkDiagnostics1::DoSetStateVariable(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aStateVariable = aInvocation.InvocationReadUint("aStateVariable");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStateVariable(resp, aVersion, aStateVariable);
}

void DvProviderLinnCoUkDiagnostics1::DoStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respaPeriod(aInvocation, "aPeriod");
    StateVariablePeriod(resp, aVersion, respaPeriod);
}

void DvProviderLinnCoUkDiagnostics1::DoSetStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPeriod = aInvocation.InvocationReadUint("aPeriod");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    SetStateVariablePeriod(resp, aVersion, aPeriod);
}

void DvProviderLinnCoUkDiagnostics1::DoReboot(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    Reboot(resp, aVersion, aDelay);
}

void DvProviderLinnCoUkDiagnostics1::Echo(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaIn*/, IInvocationResponseString& /*aaOut*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::ElfFile(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaElfFile*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::ElfFingerprint(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaElfFileFingerprint*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::CrashDataStatus(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aaCrashDataStatus*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::CrashDataFetch(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBinary& /*aaCrashData*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::CrashDataClear(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::SysLog(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseBinary& /*aaSysLog*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::Diagnostic(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aaDiagnosticType*/, IInvocationResponseString& /*aaDiagnosticInfo*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::StateVariable(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaStateVariable*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::SetStateVariable(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaStateVariable*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::StateVariablePeriod(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aaPeriod*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::SetStateVariablePeriod(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaPeriod*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1::Reboot(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, TUint /*aaDelay*/)
{
    ASSERTS();
}

