#include <Std/DvLinnCoUkDiagnostics1.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceLinnCoUkDiagnostics1Cpp::SetPropertyaStateVariable(uint32_t aValue)
{
    SetPropertyUint(*iPropertyaStateVariable, aValue);
}

void DvServiceLinnCoUkDiagnostics1Cpp::GetPropertyaStateVariable(uint32_t& aValue)
{
    aValue = iPropertyaStateVariable->Value();
}

DvServiceLinnCoUkDiagnostics1Cpp::DvServiceLinnCoUkDiagnostics1Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "linn.co.uk", "Diagnostics", 1)
{
    Functor empty;
    iPropertyaStateVariable = new PropertyUint(new ParameterUint("aStateVariable"), empty);
    iService->AddProperty(iPropertyaStateVariable); // passes ownership
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionEcho()
{
    Zapp::Action* action = new Zapp::Action("Echo");
    action->AddInputParameter(new ParameterString("aIn"));
    action->AddOutputParameter(new ParameterString("aOut"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoEcho);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionElfFile()
{
    Zapp::Action* action = new Zapp::Action("ElfFile");
    action->AddOutputParameter(new ParameterString("aElfFile"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoElfFile);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionElfFingerprint()
{
    Zapp::Action* action = new Zapp::Action("ElfFingerprint");
    action->AddOutputParameter(new ParameterString("aElfFileFingerprint"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoElfFingerprint);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionCrashDataStatus()
{
    Zapp::Action* action = new Zapp::Action("CrashDataStatus");
    action->AddOutputParameter(new ParameterString("aCrashDataStatus"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoCrashDataStatus);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionCrashDataFetch()
{
    Zapp::Action* action = new Zapp::Action("CrashDataFetch");
    action->AddOutputParameter(new ParameterBinary("aCrashData"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoCrashDataFetch);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionCrashDataClear()
{
    Zapp::Action* action = new Zapp::Action("CrashDataClear");
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoCrashDataClear);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionSysLog()
{
    Zapp::Action* action = new Zapp::Action("SysLog");
    action->AddOutputParameter(new ParameterBinary("aSysLog"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoSysLog);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionDiagnostic()
{
    Zapp::Action* action = new Zapp::Action("Diagnostic");
    action->AddInputParameter(new ParameterString("aDiagnosticType"));
    action->AddOutputParameter(new ParameterString("aDiagnosticInfo"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoDiagnostic);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionStateVariable()
{
    Zapp::Action* action = new Zapp::Action("StateVariable");
    action->AddOutputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoStateVariable);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionSetStateVariable()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariable");
    action->AddInputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoSetStateVariable);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionStateVariablePeriod()
{
    Zapp::Action* action = new Zapp::Action("StateVariablePeriod");
    action->AddOutputParameter(new ParameterUint("aPeriod"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionSetStateVariablePeriod()
{
    Zapp::Action* action = new Zapp::Action("SetStateVariablePeriod");
    action->AddInputParameter(new ParameterUint("aPeriod"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoSetStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::EnableActionReboot()
{
    Zapp::Action* action = new Zapp::Action("Reboot");
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceLinnCoUkDiagnostics1Cpp::DoReboot);
    iService->AddAction(action, functor);
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoEcho(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_aOut((const TByte*)respaOut.c_str(), respaOut.length());
    respWriteraOut.Write(buf_aOut);
    aInvocation.InvocationWriteStringEnd("aOut");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoElfFile(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaElfFile;
    ElfFile(aVersion, respaElfFile);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraElfFile(aInvocation, "aElfFile");
    Brn buf_aElfFile((const TByte*)respaElfFile.c_str(), respaElfFile.length());
    respWriteraElfFile.Write(buf_aElfFile);
    aInvocation.InvocationWriteStringEnd("aElfFile");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoElfFingerprint(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaElfFileFingerprint;
    ElfFingerprint(aVersion, respaElfFileFingerprint);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraElfFileFingerprint(aInvocation, "aElfFileFingerprint");
    Brn buf_aElfFileFingerprint((const TByte*)respaElfFileFingerprint.c_str(), respaElfFileFingerprint.length());
    respWriteraElfFileFingerprint.Write(buf_aElfFileFingerprint);
    aInvocation.InvocationWriteStringEnd("aElfFileFingerprint");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoCrashDataStatus(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaCrashDataStatus;
    CrashDataStatus(aVersion, respaCrashDataStatus);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriteraCrashDataStatus(aInvocation, "aCrashDataStatus");
    Brn buf_aCrashDataStatus((const TByte*)respaCrashDataStatus.c_str(), respaCrashDataStatus.length());
    respWriteraCrashDataStatus.Write(buf_aCrashDataStatus);
    aInvocation.InvocationWriteStringEnd("aCrashDataStatus");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoCrashDataFetch(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaCrashData;
    CrashDataFetch(aVersion, respaCrashData);
	aInvocation.InvocationWriteStart();
    InvocationResponseBinary respWriteraCrashData(aInvocation, "aCrashData");
    Brn buf_aCrashData((const TByte*)respaCrashData.c_str(), respaCrashData.length());
    respWriteraCrashData.Write(buf_aCrashData);
    aInvocation.InvocationWriteBinaryEnd("aCrashData");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoCrashDataClear(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    CrashDataClear(aVersion);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoSysLog(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respaSysLog;
    SysLog(aVersion, respaSysLog);
	aInvocation.InvocationWriteStart();
    InvocationResponseBinary respWriteraSysLog(aInvocation, "aSysLog");
    Brn buf_aSysLog((const TByte*)respaSysLog.c_str(), respaSysLog.length());
    respWriteraSysLog.Write(buf_aSysLog);
    aInvocation.InvocationWriteBinaryEnd("aSysLog");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoDiagnostic(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_aDiagnosticInfo((const TByte*)respaDiagnosticInfo.c_str(), respaDiagnosticInfo.length());
    respWriteraDiagnosticInfo.Write(buf_aDiagnosticInfo);
    aInvocation.InvocationWriteStringEnd("aDiagnosticInfo");
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoStateVariable(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkDiagnostics1Cpp::DoSetStateVariable(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aStateVariable = aInvocation.InvocationReadUint("aStateVariable");
    aInvocation.InvocationReadEnd();
    SetStateVariable(aVersion, aStateVariable);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoStateVariablePeriod(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceLinnCoUkDiagnostics1Cpp::DoSetStateVariablePeriod(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aPeriod = aInvocation.InvocationReadUint("aPeriod");
    aInvocation.InvocationReadEnd();
    SetStateVariablePeriod(aVersion, aPeriod);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::DoReboot(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    Reboot(aVersion, aDelay);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceLinnCoUkDiagnostics1Cpp::Echo(uint32_t /*aVersion*/, const std::string& /*aaIn*/, std::string& /*aaOut*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::ElfFile(uint32_t /*aVersion*/, std::string& /*aaElfFile*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::ElfFingerprint(uint32_t /*aVersion*/, std::string& /*aaElfFileFingerprint*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::CrashDataStatus(uint32_t /*aVersion*/, std::string& /*aaCrashDataStatus*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::CrashDataFetch(uint32_t /*aVersion*/, std::string& /*aaCrashData*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::CrashDataClear(uint32_t /*aVersion*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::SysLog(uint32_t /*aVersion*/, std::string& /*aaSysLog*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::Diagnostic(uint32_t /*aVersion*/, const std::string& /*aaDiagnosticType*/, std::string& /*aaDiagnosticInfo*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::StateVariable(uint32_t /*aVersion*/, uint32_t& /*aaStateVariable*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::SetStateVariable(uint32_t /*aVersion*/, uint32_t /*aaStateVariable*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::StateVariablePeriod(uint32_t /*aVersion*/, uint32_t& /*aaPeriod*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::SetStateVariablePeriod(uint32_t /*aVersion*/, uint32_t /*aaPeriod*/)
{
    ASSERTS();
}

void DvServiceLinnCoUkDiagnostics1Cpp::Reboot(uint32_t /*aVersion*/, uint32_t /*aaDelay*/)
{
    ASSERTS();
}

