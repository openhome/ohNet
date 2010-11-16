#include <Std/DvLinnCoUkDiagnostics1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

bool DvProviderLinnCoUkDiagnostics1Cpp::SetPropertyaStateVariable(uint32_t aValue)
{
    return SetPropertyUint(*iPropertyaStateVariable, aValue);
}

void DvProviderLinnCoUkDiagnostics1Cpp::GetPropertyaStateVariable(uint32_t& aValue)
{
    aValue = iPropertyaStateVariable->Value();
}

DvProviderLinnCoUkDiagnostics1Cpp::DvProviderLinnCoUkDiagnostics1Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "linn.co.uk", "Diagnostics", 1)
{
    Functor empty;
    iPropertyaStateVariable = new PropertyUint(new ParameterUint("aStateVariable"), empty);
    iService->AddProperty(iPropertyaStateVariable); // passes ownership
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionEcho()
{
    Zapp::Action* action = new Zapp::Action("Echo");
    action->AddInputParameter(new ParameterString("aIn"));
    action->AddOutputParameter(new ParameterString("aOut"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoEcho);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionElfFile()
{
    Zapp::Action* action = new Zapp::Action("ElfFile");
    action->AddOutputParameter(new ParameterString("aElfFile"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoElfFile);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionElfFingerprint()
{
    Zapp::Action* action = new Zapp::Action("ElfFingerprint");
    action->AddOutputParameter(new ParameterString("aElfFileFingerprint"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoElfFingerprint);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionCrashDataStatus()
{
    Zapp::Action* action = new Zapp::Action("CrashDataStatus");
    action->AddOutputParameter(new ParameterString("aCrashDataStatus"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoCrashDataStatus);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionCrashDataFetch()
{
    Zapp::Action* action = new Zapp::Action("CrashDataFetch");
    action->AddOutputParameter(new ParameterBinary("aCrashData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoCrashDataFetch);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionCrashDataClear()
{
    Zapp::Action* action = new Zapp::Action("CrashDataClear");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoCrashDataClear);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionSysLog()
{
    Zapp::Action* action = new Zapp::Action("SysLog");
    action->AddOutputParameter(new ParameterBinary("aSysLog"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoSysLog);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionDiagnostic()
{
    Zapp::Action* action = new Zapp::Action("Diagnostic");
    action->AddInputParameter(new ParameterString("aDiagnosticType"));
    action->AddOutputParameter(new ParameterString("aDiagnosticInfo"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoDiagnostic);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionStateVariable()
{
    Zapp::Action* action = new Zapp::Action("StateVariable");
    action->AddOutputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoStateVariable);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionSetStateVariable()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariable");
    action->AddInputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoSetStateVariable);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionStateVariablePeriod()
{
    Zapp::Action* action = new Zapp::Action("StateVariablePeriod");
    action->AddOutputParameter(new ParameterUint("aPeriod"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionSetStateVariablePeriod()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariablePeriod");
    action->AddInputParameter(new ParameterUint("aPeriod"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoSetStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::EnableActionReboot()
{
    Zapp::Action* action = new Zapp::Action("Reboot");
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1Cpp::DoReboot);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoEcho(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aIn;
    aInvocation.InvocationReadString("aIn", buf_aIn);
    std::string aIn((const char*)buf_aIn.Ptr(), buf_aIn.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respaOut;
    Echo(aVersion, aIn, respaOut);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraOut(aInvocation, "aOut");
    Brn buf_aOut((const TByte*)respaOut.c_str(), (TUint)respaOut.length());
    respWriteraOut.Write(buf_aOut);
    aInvocation.InvocationWriteStringEnd("aOut");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoElfFile(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaElfFile;
    ElfFile(aVersion, respaElfFile);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraElfFile(aInvocation, "aElfFile");
    Brn buf_aElfFile((const TByte*)respaElfFile.c_str(), (TUint)respaElfFile.length());
    respWriteraElfFile.Write(buf_aElfFile);
    aInvocation.InvocationWriteStringEnd("aElfFile");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoElfFingerprint(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaElfFileFingerprint;
    ElfFingerprint(aVersion, respaElfFileFingerprint);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraElfFileFingerprint(aInvocation, "aElfFileFingerprint");
    Brn buf_aElfFileFingerprint((const TByte*)respaElfFileFingerprint.c_str(), (TUint)respaElfFileFingerprint.length());
    respWriteraElfFileFingerprint.Write(buf_aElfFileFingerprint);
    aInvocation.InvocationWriteStringEnd("aElfFileFingerprint");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoCrashDataStatus(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaCrashDataStatus;
    CrashDataStatus(aVersion, respaCrashDataStatus);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraCrashDataStatus(aInvocation, "aCrashDataStatus");
    Brn buf_aCrashDataStatus((const TByte*)respaCrashDataStatus.c_str(), (TUint)respaCrashDataStatus.length());
    respWriteraCrashDataStatus.Write(buf_aCrashDataStatus);
    aInvocation.InvocationWriteStringEnd("aCrashDataStatus");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoCrashDataFetch(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaCrashData;
    CrashDataFetch(aVersion, respaCrashData);
	aInvocation.InvocationWriteStart();
    InvocationResponseBinary respWriteraCrashData(aInvocation, "aCrashData");
    Brn buf_aCrashData((const TByte*)respaCrashData.c_str(), (TUint)respaCrashData.length());
    respWriteraCrashData.Write(buf_aCrashData);
    aInvocation.InvocationWriteBinaryEnd("aCrashData");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoCrashDataClear(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    CrashDataClear(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoSysLog(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaSysLog;
    SysLog(aVersion, respaSysLog);
	aInvocation.InvocationWriteStart();
    InvocationResponseBinary respWriteraSysLog(aInvocation, "aSysLog");
    Brn buf_aSysLog((const TByte*)respaSysLog.c_str(), (TUint)respaSysLog.length());
    respWriteraSysLog.Write(buf_aSysLog);
    aInvocation.InvocationWriteBinaryEnd("aSysLog");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoDiagnostic(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_aDiagnosticType;
    aInvocation.InvocationReadString("aDiagnosticType", buf_aDiagnosticType);
    std::string aDiagnosticType((const char*)buf_aDiagnosticType.Ptr(), buf_aDiagnosticType.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respaDiagnosticInfo;
    Diagnostic(aVersion, aDiagnosticType, respaDiagnosticInfo);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraDiagnosticInfo(aInvocation, "aDiagnosticInfo");
    Brn buf_aDiagnosticInfo((const TByte*)respaDiagnosticInfo.c_str(), (TUint)respaDiagnosticInfo.length());
    respWriteraDiagnosticInfo.Write(buf_aDiagnosticInfo);
    aInvocation.InvocationWriteStringEnd("aDiagnosticInfo");
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoStateVariable(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaStateVariable;
    StateVariable(aVersion, respaStateVariable);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraStateVariable(aInvocation, "aStateVariable");
    respWriteraStateVariable.Write(respaStateVariable);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoSetStateVariable(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aStateVariable = aInvocation.InvocationReadUint("aStateVariable");
    aInvocation.InvocationReadEnd();
    SetStateVariable(aVersion, aStateVariable);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respaPeriod;
    StateVariablePeriod(aVersion, respaPeriod);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriteraPeriod(aInvocation, "aPeriod");
    respWriteraPeriod.Write(respaPeriod);
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoSetStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aPeriod = aInvocation.InvocationReadUint("aPeriod");
    aInvocation.InvocationReadEnd();
    SetStateVariablePeriod(aVersion, aPeriod);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::DoReboot(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    Reboot(aVersion, aDelay);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderLinnCoUkDiagnostics1Cpp::Echo(uint32_t /*aVersion*/, const std::string& /*aaIn*/, std::string& /*aaOut*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::ElfFile(uint32_t /*aVersion*/, std::string& /*aaElfFile*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::ElfFingerprint(uint32_t /*aVersion*/, std::string& /*aaElfFileFingerprint*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::CrashDataStatus(uint32_t /*aVersion*/, std::string& /*aaCrashDataStatus*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::CrashDataFetch(uint32_t /*aVersion*/, std::string& /*aaCrashData*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::CrashDataClear(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::SysLog(uint32_t /*aVersion*/, std::string& /*aaSysLog*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::Diagnostic(uint32_t /*aVersion*/, const std::string& /*aaDiagnosticType*/, std::string& /*aaDiagnosticInfo*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::StateVariable(uint32_t /*aVersion*/, uint32_t& /*aaStateVariable*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::SetStateVariable(uint32_t /*aVersion*/, uint32_t /*aaStateVariable*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::StateVariablePeriod(uint32_t /*aVersion*/, uint32_t& /*aaPeriod*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::SetStateVariablePeriod(uint32_t /*aVersion*/, uint32_t /*aaPeriod*/)
{
    ASSERTS();
}

void DvProviderLinnCoUkDiagnostics1Cpp::Reboot(uint32_t /*aVersion*/, uint32_t /*aaDelay*/)
{
    ASSERTS();
}

