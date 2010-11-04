#include <C/DvLinnCoUkDiagnostics1.h>
#include <Core/DvLinnCoUkDiagnostics1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderLinnCoUkDiagnostics1C : public DvProviderLinnCoUkDiagnostics1
{
public:
    DvProviderLinnCoUkDiagnostics1C(DvDevice& aDevice);
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
    void Echo(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIn, IInvocationResponseString& aaOut);
    void ElfFile(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFile);
    void ElfFingerprint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFileFingerprint);
    void CrashDataStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCrashDataStatus);
    void CrashDataFetch(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaCrashData);
    void CrashDataClear(IInvocationResponse& aResponse, TUint aVersion);
    void SysLog(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaSysLog);
    void Diagnostic(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaDiagnosticType, IInvocationResponseString& aaDiagnosticInfo);
    void StateVariable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStateVariable);
    void SetStateVariable(IInvocationResponse& aResponse, TUint aVersion, TUint aaStateVariable);
    void StateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPeriod);
    void SetStateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, TUint aaPeriod);
    void Reboot(IInvocationResponse& aResponse, TUint aVersion, TUint aaDelay);
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
};

DvProviderLinnCoUkDiagnostics1C::DvProviderLinnCoUkDiagnostics1C(DvDevice& aDevice)
    : DvProviderLinnCoUkDiagnostics1(aDevice)
{
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionEcho(CallbackDiagnostics1Echo aCallback, void* aPtr)
{
    iCallbackEcho = aCallback;
    iPtrEcho = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionEcho();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionElfFile(CallbackDiagnostics1ElfFile aCallback, void* aPtr)
{
    iCallbackElfFile = aCallback;
    iPtrElfFile = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionElfFile();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionElfFingerprint(CallbackDiagnostics1ElfFingerprint aCallback, void* aPtr)
{
    iCallbackElfFingerprint = aCallback;
    iPtrElfFingerprint = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionElfFingerprint();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionCrashDataStatus(CallbackDiagnostics1CrashDataStatus aCallback, void* aPtr)
{
    iCallbackCrashDataStatus = aCallback;
    iPtrCrashDataStatus = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionCrashDataStatus();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionCrashDataFetch(CallbackDiagnostics1CrashDataFetch aCallback, void* aPtr)
{
    iCallbackCrashDataFetch = aCallback;
    iPtrCrashDataFetch = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionCrashDataFetch();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionCrashDataClear(CallbackDiagnostics1CrashDataClear aCallback, void* aPtr)
{
    iCallbackCrashDataClear = aCallback;
    iPtrCrashDataClear = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionCrashDataClear();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionSysLog(CallbackDiagnostics1SysLog aCallback, void* aPtr)
{
    iCallbackSysLog = aCallback;
    iPtrSysLog = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionSysLog();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionDiagnostic(CallbackDiagnostics1Diagnostic aCallback, void* aPtr)
{
    iCallbackDiagnostic = aCallback;
    iPtrDiagnostic = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionDiagnostic();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionStateVariable(CallbackDiagnostics1StateVariable aCallback, void* aPtr)
{
    iCallbackStateVariable = aCallback;
    iPtrStateVariable = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionStateVariable();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionSetStateVariable(CallbackDiagnostics1SetStateVariable aCallback, void* aPtr)
{
    iCallbackSetStateVariable = aCallback;
    iPtrSetStateVariable = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionSetStateVariable();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionStateVariablePeriod(CallbackDiagnostics1StateVariablePeriod aCallback, void* aPtr)
{
    iCallbackStateVariablePeriod = aCallback;
    iPtrStateVariablePeriod = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionStateVariablePeriod();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionSetStateVariablePeriod(CallbackDiagnostics1SetStateVariablePeriod aCallback, void* aPtr)
{
    iCallbackSetStateVariablePeriod = aCallback;
    iPtrSetStateVariablePeriod = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionSetStateVariablePeriod();
}

void DvProviderLinnCoUkDiagnostics1C::EnableActionReboot(CallbackDiagnostics1Reboot aCallback, void* aPtr)
{
    iCallbackReboot = aCallback;
    iPtrReboot = aPtr;
    DvProviderLinnCoUkDiagnostics1::EnableActionReboot();
}

void DvProviderLinnCoUkDiagnostics1C::Echo(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIn, IInvocationResponseString& aaOut)
{
    char* aOut;
    ASSERT(iCallbackEcho != NULL);
    if (0 != iCallbackEcho(iPtrEcho, aVersion, (const char*)aaIn.Ptr(), &aOut)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaOut((const TChar*)aOut);
    ZappFreeExternal(aOut);
    aaOut.Write(bufaOut);
    aaOut.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::ElfFile(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFile)
{
    char* aElfFile;
    ASSERT(iCallbackElfFile != NULL);
    if (0 != iCallbackElfFile(iPtrElfFile, aVersion, &aElfFile)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaElfFile((const TChar*)aElfFile);
    ZappFreeExternal(aElfFile);
    aaElfFile.Write(bufaElfFile);
    aaElfFile.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::ElfFingerprint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFileFingerprint)
{
    char* aElfFileFingerprint;
    ASSERT(iCallbackElfFingerprint != NULL);
    if (0 != iCallbackElfFingerprint(iPtrElfFingerprint, aVersion, &aElfFileFingerprint)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaElfFileFingerprint((const TChar*)aElfFileFingerprint);
    ZappFreeExternal(aElfFileFingerprint);
    aaElfFileFingerprint.Write(bufaElfFileFingerprint);
    aaElfFileFingerprint.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::CrashDataStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCrashDataStatus)
{
    char* aCrashDataStatus;
    ASSERT(iCallbackCrashDataStatus != NULL);
    if (0 != iCallbackCrashDataStatus(iPtrCrashDataStatus, aVersion, &aCrashDataStatus)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaCrashDataStatus((const TChar*)aCrashDataStatus);
    ZappFreeExternal(aCrashDataStatus);
    aaCrashDataStatus.Write(bufaCrashDataStatus);
    aaCrashDataStatus.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::CrashDataFetch(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaCrashData)
{
    char* aCrashData;
    uint32_t aCrashDataLen;
    ASSERT(iCallbackCrashDataFetch != NULL);
    if (0 != iCallbackCrashDataFetch(iPtrCrashDataFetch, aVersion, &aCrashData, &aCrashDataLen)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brh bufaCrashData;
    bufaCrashData.Set((const TByte*)aCrashData, aCrashDataLen);
    ZappFreeExternal(aCrashData);
    aaCrashData.Write(bufaCrashData);
    aaCrashData.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::CrashDataClear(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackCrashDataClear != NULL);
    if (0 != iCallbackCrashDataClear(iPtrCrashDataClear, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::SysLog(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaSysLog)
{
    char* aSysLog;
    uint32_t aSysLogLen;
    ASSERT(iCallbackSysLog != NULL);
    if (0 != iCallbackSysLog(iPtrSysLog, aVersion, &aSysLog, &aSysLogLen)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brh bufaSysLog;
    bufaSysLog.Set((const TByte*)aSysLog, aSysLogLen);
    ZappFreeExternal(aSysLog);
    aaSysLog.Write(bufaSysLog);
    aaSysLog.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::Diagnostic(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaDiagnosticType, IInvocationResponseString& aaDiagnosticInfo)
{
    char* aDiagnosticInfo;
    ASSERT(iCallbackDiagnostic != NULL);
    if (0 != iCallbackDiagnostic(iPtrDiagnostic, aVersion, (const char*)aaDiagnosticType.Ptr(), &aDiagnosticInfo)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufaDiagnosticInfo((const TChar*)aDiagnosticInfo);
    ZappFreeExternal(aDiagnosticInfo);
    aaDiagnosticInfo.Write(bufaDiagnosticInfo);
    aaDiagnosticInfo.WriteFlush();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::StateVariable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStateVariable)
{
    uint32_t aStateVariable;
    ASSERT(iCallbackStateVariable != NULL);
    if (0 != iCallbackStateVariable(iPtrStateVariable, aVersion, &aStateVariable)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaStateVariable.Write(aStateVariable);
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::SetStateVariable(IInvocationResponse& aResponse, TUint aVersion, TUint aaStateVariable)
{
    ASSERT(iCallbackSetStateVariable != NULL);
    if (0 != iCallbackSetStateVariable(iPtrSetStateVariable, aVersion, aaStateVariable)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::StateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPeriod)
{
    uint32_t aPeriod;
    ASSERT(iCallbackStateVariablePeriod != NULL);
    if (0 != iCallbackStateVariablePeriod(iPtrStateVariablePeriod, aVersion, &aPeriod)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aaPeriod.Write(aPeriod);
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::SetStateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, TUint aaPeriod)
{
    ASSERT(iCallbackSetStateVariablePeriod != NULL);
    if (0 != iCallbackSetStateVariablePeriod(iPtrSetStateVariablePeriod, aVersion, aaPeriod)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderLinnCoUkDiagnostics1C::Reboot(IInvocationResponse& aResponse, TUint aVersion, TUint aaDelay)
{
    ASSERT(iCallbackReboot != NULL);
    if (0 != iCallbackReboot(iPtrReboot, aVersion, aaDelay)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvProviderLinnCoUkDiagnostics1Create(DvDeviceC aDevice)
{
	return new DvProviderLinnCoUkDiagnostics1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderLinnCoUkDiagnostics1Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService);
}

void DvProviderLinnCoUkDiagnostics1EnableActionEcho(THandle aService, CallbackDiagnostics1Echo aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionEcho(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionElfFile(THandle aService, CallbackDiagnostics1ElfFile aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionElfFile(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionElfFingerprint(THandle aService, CallbackDiagnostics1ElfFingerprint aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionElfFingerprint(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataStatus(THandle aService, CallbackDiagnostics1CrashDataStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionCrashDataStatus(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataFetch(THandle aService, CallbackDiagnostics1CrashDataFetch aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionCrashDataFetch(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionCrashDataClear(THandle aService, CallbackDiagnostics1CrashDataClear aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionCrashDataClear(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionSysLog(THandle aService, CallbackDiagnostics1SysLog aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionSysLog(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionDiagnostic(THandle aService, CallbackDiagnostics1Diagnostic aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionDiagnostic(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionStateVariable(THandle aService, CallbackDiagnostics1StateVariable aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionStateVariable(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariable(THandle aService, CallbackDiagnostics1SetStateVariable aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionSetStateVariable(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionStateVariablePeriod(THandle aService, CallbackDiagnostics1StateVariablePeriod aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionStateVariablePeriod(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod(THandle aService, CallbackDiagnostics1SetStateVariablePeriod aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionSetStateVariablePeriod(aCallback, aPtr);
}

void DvProviderLinnCoUkDiagnostics1EnableActionReboot(THandle aService, CallbackDiagnostics1Reboot aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->EnableActionReboot(aCallback, aPtr);
}

int32_t DvProviderLinnCoUkDiagnostics1SetPropertyaStateVariable(THandle aService, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->SetPropertyaStateVariable(aValue)? 1 : 0);
    return 0;
}

void DvProviderLinnCoUkDiagnostics1GetPropertyaStateVariable(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderLinnCoUkDiagnostics1C*>(aService)->GetPropertyaStateVariable(val);
    *aValue = val;
}

