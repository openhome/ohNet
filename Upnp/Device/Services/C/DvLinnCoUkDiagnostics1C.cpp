#include "DvLinnCoUkDiagnostics1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/Zapp.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace Zapp;

class DvProviderLinnCoUkDiagnostics1C : public DvProvider
{
public:
    DvProviderLinnCoUkDiagnostics1C(DvDeviceC aDevice);
    TBool SetPropertyaStateVariable(TUint aValue);
    void GetPropertyaStateVariable(TUint& aValue);
    void EnableActionEcho(CallbackDiagnostics1Echo aCallback, void* aPtr);
    void EnableActionElfFile(CallbackDiagnostics1ElfFile aCallback, void* aPtr);
    void EnableActionElfFingerprint(CallbackDiagnostics1ElfFingerprint aCallback, void* aPtr);
    void EnableActionCrashDataStatus(CallbackDiagnostics1CrashDataStatus aCallback, void* aPtr);
    void EnableActionCrashDataFetch(CallbackDiagnostics1CrashDataFetch aCallback, void* aPtr);
    void EnableActionCrashDataClear(CallbackDiagnostics1CrashDataClear aCallback, void* aPtr);
    void EnableActionSysLog(CallbackDiagnostics1SysLog aCallback, void* aPtr);
    void EnableActionDiagnostic(CallbackDiagnostics1Diagnostic aCallback, void* aPtr);
    void EnableActionStateVariable(CallbackDiagnostics1StateVariable aCallback, void* aPtr);
    void EnableActionSetStateVariable(CallbackDiagnostics1SetStateVariable aCallback, void* aPtr);
    void EnableActionStateVariablePeriod(CallbackDiagnostics1StateVariablePeriod aCallback, void* aPtr);
    void EnableActionSetStateVariablePeriod(CallbackDiagnostics1SetStateVariablePeriod aCallback, void* aPtr);
    void EnableActionReboot(CallbackDiagnostics1Reboot aCallback, void* aPtr);
private:
    void DoEcho(IDviInvocation& aInvocation, TUint aVersion);
    void DoElfFile(IDviInvocation& aInvocation, TUint aVersion);
    void DoElfFingerprint(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataStatus(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataFetch(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataClear(IDviInvocation& aInvocation, TUint aVersion);
    void DoSysLog(IDviInvocation& aInvocation, TUint aVersion);
    void DoDiagnostic(IDviInvocation& aInvocation, TUint aVersion);
    void DoStateVariable(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariable(IDviInvocation& aInvocation, TUint aVersion);
    void DoStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion);
    void DoReboot(IDviInvocation& aInvocation, TUint aVersion);
private:
    CallbackDiagnostics1Echo iCallbackEcho;
    void* iPtrEcho;
    CallbackDiagnostics1ElfFile iCallbackElfFile;
    void* iPtrElfFile;
    CallbackDiagnostics1ElfFingerprint iCallbackElfFingerprint;
    void* iPtrElfFingerprint;
    CallbackDiagnostics1CrashDataStatus iCallbackCrashDataStatus;
    void* iPtrCrashDataStatus;
    CallbackDiagnostics1CrashDataFetch iCallbackCrashDataFetch;
    void* iPtrCrashDataFetch;
    CallbackDiagnostics1CrashDataClear iCallbackCrashDataClear;
    void* iPtrCrashDataClear;
    CallbackDiagnostics1SysLog iCallbackSysLog;
    void* iPtrSysLog;
    CallbackDiagnostics1Diagnostic iCallbackDiagnostic;
    void* iPtrDiagnostic;
    CallbackDiagnostics1StateVariable iCallbackStateVariable;
    void* iPtrStateVariable;
    CallbackDiagnostics1SetStateVariable iCallbackSetStateVariable;
    void* iPtrSetStateVariable;
    CallbackDiagnostics1StateVariablePeriod iCallbackStateVariablePeriod;
    void* iPtrStateVariablePeriod;
    CallbackDiagnostics1SetStateVariablePeriod iCallbackSetStateVariablePeriod;
    void* iPtrSetStateVariablePeriod;
    CallbackDiagnostics1Reboot iCallbackReboot;
    void* iPtrReboot;
    PropertyUint* iPropertyaStateVariable;
};

DvProviderLinnCoUkDiagnostics1C::DvProviderLinnCoUkDiagnostics1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "linn.co.uk", "Diagnostics", 1)
{
    
    iPropertyaStateVariable = new PropertyUint(new ParameterUint("aStateVariable"));
    iService->AddProperty(iPropertyaStateVariable); // passes ownership
}

TBool DvProviderLinnCoUkDiagnostics1C::SetPropertyaStateVariable(TUint aValue)
{
    return SetPropertyUint(*iPropertyaStateVariable, aValue);
}

void DvProviderLinnCoUkDiagnostics1C::GetPropertyaStateVariable(TUint& aValue)
{
    aValue = iPropertyaStateVariable->Value();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionEcho(CallbackDiagnostics1Echo aCallback, void* aPtr)
{
    iCallbackEcho = aCallback;
    iPtrEcho = aPtr;
    Zapp::Action* action = new Zapp::Action("Echo");
    action->AddInputParameter(new ParameterString("aIn"));
    action->AddOutputParameter(new ParameterString("aOut"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoEcho);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionElfFile(CallbackDiagnostics1ElfFile aCallback, void* aPtr)
{
    iCallbackElfFile = aCallback;
    iPtrElfFile = aPtr;
    Zapp::Action* action = new Zapp::Action("ElfFile");
    action->AddOutputParameter(new ParameterString("aElfFile"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoElfFile);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionElfFingerprint(CallbackDiagnostics1ElfFingerprint aCallback, void* aPtr)
{
    iCallbackElfFingerprint = aCallback;
    iPtrElfFingerprint = aPtr;
    Zapp::Action* action = new Zapp::Action("ElfFingerprint");
    action->AddOutputParameter(new ParameterString("aElfFileFingerprint"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoElfFingerprint);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionCrashDataStatus(CallbackDiagnostics1CrashDataStatus aCallback, void* aPtr)
{
    iCallbackCrashDataStatus = aCallback;
    iPtrCrashDataStatus = aPtr;
    Zapp::Action* action = new Zapp::Action("CrashDataStatus");
    action->AddOutputParameter(new ParameterString("aCrashDataStatus"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoCrashDataStatus);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionCrashDataFetch(CallbackDiagnostics1CrashDataFetch aCallback, void* aPtr)
{
    iCallbackCrashDataFetch = aCallback;
    iPtrCrashDataFetch = aPtr;
    Zapp::Action* action = new Zapp::Action("CrashDataFetch");
    action->AddOutputParameter(new ParameterBinary("aCrashData"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoCrashDataFetch);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionCrashDataClear(CallbackDiagnostics1CrashDataClear aCallback, void* aPtr)
{
    iCallbackCrashDataClear = aCallback;
    iPtrCrashDataClear = aPtr;
    Zapp::Action* action = new Zapp::Action("CrashDataClear");
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoCrashDataClear);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionSysLog(CallbackDiagnostics1SysLog aCallback, void* aPtr)
{
    iCallbackSysLog = aCallback;
    iPtrSysLog = aPtr;
    Zapp::Action* action = new Zapp::Action("SysLog");
    action->AddOutputParameter(new ParameterBinary("aSysLog"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoSysLog);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionDiagnostic(CallbackDiagnostics1Diagnostic aCallback, void* aPtr)
{
    iCallbackDiagnostic = aCallback;
    iPtrDiagnostic = aPtr;
    Zapp::Action* action = new Zapp::Action("Diagnostic");
    action->AddInputParameter(new ParameterString("aDiagnosticType"));
    action->AddOutputParameter(new ParameterString("aDiagnosticInfo"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoDiagnostic);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionStateVariable(CallbackDiagnostics1StateVariable aCallback, void* aPtr)
{
    iCallbackStateVariable = aCallback;
    iPtrStateVariable = aPtr;
    Zapp::Action* action = new Zapp::Action("StateVariable");
    action->AddOutputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoStateVariable);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionSetStateVariable(CallbackDiagnostics1SetStateVariable aCallback, void* aPtr)
{
    iCallbackSetStateVariable = aCallback;
    iPtrSetStateVariable = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStateVariable");
    action->AddInputParameter(new ParameterRelated("aStateVariable", *iPropertyaStateVariable));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoSetStateVariable);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionStateVariablePeriod(CallbackDiagnostics1StateVariablePeriod aCallback, void* aPtr)
{
    iCallbackStateVariablePeriod = aCallback;
    iPtrStateVariablePeriod = aPtr;
    Zapp::Action* action = new Zapp::Action("StateVariablePeriod");
    action->AddOutputParameter(new ParameterUint("aPeriod"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionSetStateVariablePeriod(CallbackDiagnostics1SetStateVariablePeriod aCallback, void* aPtr)
{
    iCallbackSetStateVariablePeriod = aCallback;
    iPtrSetStateVariablePeriod = aPtr;
    Zapp::Action* action = new Zapp::Action("SetStateVariablePeriod");
    action->AddInputParameter(new ParameterUint("aPeriod"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoSetStateVariablePeriod);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionReboot(CallbackDiagnostics1Reboot aCallback, void* aPtr)
{
    iCallbackReboot = aCallback;
    iPtrReboot = aPtr;
    Zapp::Action* action = new Zapp::Action("Reboot");
    action->AddInputParameter(new ParameterUint("aDelay"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderLinnCoUkDiagnostics1C::DoReboot);
    iService->AddAction(action, functor);
}

void DvProviderLinnCoUkDiagnostics1C::DoEcho(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aIn;
    aInvocation.InvocationReadString("aIn", aIn);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aOut;
    ASSERT(iCallbackEcho != NULL);
    if (0 != iCallbackEcho(iPtrEcho, aVersion, (const char*)aIn.Ptr(), &aOut)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaOut(aInvocation, "aOut");
    resp.Start();
    Brhz bufaOut((const TChar*)aOut);
    ZappFreeExternal(aOut);
    respaOut.Write(bufaOut);
    respaOut.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoElfFile(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aElfFile;
    ASSERT(iCallbackElfFile != NULL);
    if (0 != iCallbackElfFile(iPtrElfFile, aVersion, &aElfFile)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaElfFile(aInvocation, "aElfFile");
    resp.Start();
    Brhz bufaElfFile((const TChar*)aElfFile);
    ZappFreeExternal(aElfFile);
    respaElfFile.Write(bufaElfFile);
    respaElfFile.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoElfFingerprint(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aElfFileFingerprint;
    ASSERT(iCallbackElfFingerprint != NULL);
    if (0 != iCallbackElfFingerprint(iPtrElfFingerprint, aVersion, &aElfFileFingerprint)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaElfFileFingerprint(aInvocation, "aElfFileFingerprint");
    resp.Start();
    Brhz bufaElfFileFingerprint((const TChar*)aElfFileFingerprint);
    ZappFreeExternal(aElfFileFingerprint);
    respaElfFileFingerprint.Write(bufaElfFileFingerprint);
    respaElfFileFingerprint.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoCrashDataStatus(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aCrashDataStatus;
    ASSERT(iCallbackCrashDataStatus != NULL);
    if (0 != iCallbackCrashDataStatus(iPtrCrashDataStatus, aVersion, &aCrashDataStatus)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaCrashDataStatus(aInvocation, "aCrashDataStatus");
    resp.Start();
    Brhz bufaCrashDataStatus((const TChar*)aCrashDataStatus);
    ZappFreeExternal(aCrashDataStatus);
    respaCrashDataStatus.Write(bufaCrashDataStatus);
    respaCrashDataStatus.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoCrashDataFetch(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aCrashData;
    uint32_t aCrashDataLen;
    ASSERT(iCallbackCrashDataFetch != NULL);
    if (0 != iCallbackCrashDataFetch(iPtrCrashDataFetch, aVersion, &aCrashData, &aCrashDataLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBinary respaCrashData(aInvocation, "aCrashData");
    resp.Start();
    Brh bufaCrashData;
    bufaCrashData.Set((const TByte*)aCrashData, aCrashDataLen);
    ZappFreeExternal(aCrashData);
    respaCrashData.Write(bufaCrashData);
    respaCrashData.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoCrashDataClear(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackCrashDataClear != NULL);
    if (0 != iCallbackCrashDataClear(iPtrCrashDataClear, aVersion)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoSysLog(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aSysLog;
    uint32_t aSysLogLen;
    ASSERT(iCallbackSysLog != NULL);
    if (0 != iCallbackSysLog(iPtrSysLog, aVersion, &aSysLog, &aSysLogLen)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseBinary respaSysLog(aInvocation, "aSysLog");
    resp.Start();
    Brh bufaSysLog;
    bufaSysLog.Set((const TByte*)aSysLog, aSysLogLen);
    ZappFreeExternal(aSysLog);
    respaSysLog.Write(bufaSysLog);
    respaSysLog.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoDiagnostic(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz aDiagnosticType;
    aInvocation.InvocationReadString("aDiagnosticType", aDiagnosticType);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* aDiagnosticInfo;
    ASSERT(iCallbackDiagnostic != NULL);
    if (0 != iCallbackDiagnostic(iPtrDiagnostic, aVersion, (const char*)aDiagnosticType.Ptr(), &aDiagnosticInfo)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respaDiagnosticInfo(aInvocation, "aDiagnosticInfo");
    resp.Start();
    Brhz bufaDiagnosticInfo((const TChar*)aDiagnosticInfo);
    ZappFreeExternal(aDiagnosticInfo);
    respaDiagnosticInfo.Write(bufaDiagnosticInfo);
    respaDiagnosticInfo.WriteFlush();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoStateVariable(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aStateVariable;
    ASSERT(iCallbackStateVariable != NULL);
    if (0 != iCallbackStateVariable(iPtrStateVariable, aVersion, &aStateVariable)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaStateVariable(aInvocation, "aStateVariable");
    resp.Start();
    respaStateVariable.Write(aStateVariable);
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoSetStateVariable(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aStateVariable = aInvocation.InvocationReadUint("aStateVariable");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStateVariable != NULL);
    if (0 != iCallbackSetStateVariable(iPtrSetStateVariable, aVersion, aStateVariable)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t aPeriod;
    ASSERT(iCallbackStateVariablePeriod != NULL);
    if (0 != iCallbackStateVariablePeriod(iPtrStateVariablePeriod, aVersion, &aPeriod)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respaPeriod(aInvocation, "aPeriod");
    resp.Start();
    respaPeriod.Write(aPeriod);
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoSetStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aPeriod = aInvocation.InvocationReadUint("aPeriod");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackSetStateVariablePeriod != NULL);
    if (0 != iCallbackSetStateVariablePeriod(iPtrSetStateVariablePeriod, aVersion, aPeriod)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderLinnCoUkDiagnostics1C::DoReboot(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    TUint aDelay = aInvocation.InvocationReadUint("aDelay");
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackReboot != NULL);
    if (0 != iCallbackReboot(iPtrReboot, aVersion, aDelay)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}



THandle DvProviderLinnCoUkDiagnostics1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkDiagnostics1C(aDevice);
}

void DvProviderLinnCoUkDiagnostics1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider);
}

void DvProviderLinnCoUkDiagnostics1EnableActionEcho(THandle aProvider, CallbackDiagnostics1Echo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionEcho(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionElfFile(THandle aProvider, CallbackDiagnostics1ElfFile aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionElfFile(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionElfFingerprint(THandle aProvider, CallbackDiagnostics1ElfFingerprint aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionElfFingerprint(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataStatus(THandle aProvider, CallbackDiagnostics1CrashDataStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionCrashDataStatus(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataFetch(THandle aProvider, CallbackDiagnostics1CrashDataFetch aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionCrashDataFetch(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataClear(THandle aProvider, CallbackDiagnostics1CrashDataClear aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionCrashDataClear(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionSysLog(THandle aProvider, CallbackDiagnostics1SysLog aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionSysLog(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionDiagnostic(THandle aProvider, CallbackDiagnostics1Diagnostic aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionDiagnostic(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionStateVariable(THandle aProvider, CallbackDiagnostics1StateVariable aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionStateVariable(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariable(THandle aProvider, CallbackDiagnostics1SetStateVariable aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionSetStateVariable(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionStateVariablePeriod(THandle aProvider, CallbackDiagnostics1StateVariablePeriod aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionStateVariablePeriod(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod(THandle aProvider, CallbackDiagnostics1SetStateVariablePeriod aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionSetStateVariablePeriod(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionReboot(THandle aProvider, CallbackDiagnostics1Reboot aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->EnableActionReboot(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkDiagnostics1SetPropertyaStateVariable(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->SetPropertyaStateVariable(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDiagnostics1GetPropertyaStateVariable(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aProvider)->GetPropertyaStateVariable(val);
    *aValue = val;
}

