#include <C/DvLinnCoUkDiagnostics1.h>
#include <Core/DvLinnCoUkDiagnostics1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceLinnCoUkDiagnostics1C : public DvServiceLinnCoUkDiagnostics1
{
public:
    DvServiceLinnCoUkDiagnostics1C(DvDevice& aDevice);
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

DvServiceLinnCoUkDiagnostics1C::DvServiceLinnCoUkDiagnostics1C(DvDevice& aDevice)
    : DvServiceLinnCoUkDiagnostics1(aDevice)
{
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionEcho(CallbackDiagnostics1Echo aCallback, void* aPtr)
{
    iCallbackEcho = aCallback;
    iPtrEcho = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionEcho();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionElfFile(CallbackDiagnostics1ElfFile aCallback, void* aPtr)
{
    iCallbackElfFile = aCallback;
    iPtrElfFile = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionElfFile();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionElfFingerprint(CallbackDiagnostics1ElfFingerprint aCallback, void* aPtr)
{
    iCallbackElfFingerprint = aCallback;
    iPtrElfFingerprint = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionElfFingerprint();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionCrashDataStatus(CallbackDiagnostics1CrashDataStatus aCallback, void* aPtr)
{
    iCallbackCrashDataStatus = aCallback;
    iPtrCrashDataStatus = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionCrashDataStatus();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionCrashDataFetch(CallbackDiagnostics1CrashDataFetch aCallback, void* aPtr)
{
    iCallbackCrashDataFetch = aCallback;
    iPtrCrashDataFetch = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionCrashDataFetch();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionCrashDataClear(CallbackDiagnostics1CrashDataClear aCallback, void* aPtr)
{
    iCallbackCrashDataClear = aCallback;
    iPtrCrashDataClear = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionCrashDataClear();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionSysLog(CallbackDiagnostics1SysLog aCallback, void* aPtr)
{
    iCallbackSysLog = aCallback;
    iPtrSysLog = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionSysLog();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionDiagnostic(CallbackDiagnostics1Diagnostic aCallback, void* aPtr)
{
    iCallbackDiagnostic = aCallback;
    iPtrDiagnostic = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionDiagnostic();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionStateVariable(CallbackDiagnostics1StateVariable aCallback, void* aPtr)
{
    iCallbackStateVariable = aCallback;
    iPtrStateVariable = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionStateVariable();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionSetStateVariable(CallbackDiagnostics1SetStateVariable aCallback, void* aPtr)
{
    iCallbackSetStateVariable = aCallback;
    iPtrSetStateVariable = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionSetStateVariable();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionStateVariablePeriod(CallbackDiagnostics1StateVariablePeriod aCallback, void* aPtr)
{
    iCallbackStateVariablePeriod = aCallback;
    iPtrStateVariablePeriod = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionStateVariablePeriod();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionSetStateVariablePeriod(CallbackDiagnostics1SetStateVariablePeriod aCallback, void* aPtr)
{
    iCallbackSetStateVariablePeriod = aCallback;
    iPtrSetStateVariablePeriod = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionSetStateVariablePeriod();
}

void DvServiceLinnCoUkDiagnostics1C::EnableActionReboot(CallbackDiagnostics1Reboot aCallback, void* aPtr)
{
    iCallbackReboot = aCallback;
    iPtrReboot = aPtr;
    DvServiceLinnCoUkDiagnostics1::EnableActionReboot();
}

void DvServiceLinnCoUkDiagnostics1C::Echo(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIn, IInvocationResponseString& aaOut)
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

void DvServiceLinnCoUkDiagnostics1C::ElfFile(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFile)
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

void DvServiceLinnCoUkDiagnostics1C::ElfFingerprint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFileFingerprint)
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

void DvServiceLinnCoUkDiagnostics1C::CrashDataStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCrashDataStatus)
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

void DvServiceLinnCoUkDiagnostics1C::CrashDataFetch(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaCrashData)
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

void DvServiceLinnCoUkDiagnostics1C::CrashDataClear(IInvocationResponse& aResponse, TUint aVersion)
{
    ASSERT(iCallbackCrashDataClear != NULL);
    if (0 != iCallbackCrashDataClear(iPtrCrashDataClear, aVersion)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDiagnostics1C::SysLog(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaSysLog)
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

void DvServiceLinnCoUkDiagnostics1C::Diagnostic(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaDiagnosticType, IInvocationResponseString& aaDiagnosticInfo)
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

void DvServiceLinnCoUkDiagnostics1C::StateVariable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStateVariable)
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

void DvServiceLinnCoUkDiagnostics1C::SetStateVariable(IInvocationResponse& aResponse, TUint aVersion, TUint aaStateVariable)
{
    ASSERT(iCallbackSetStateVariable != NULL);
    if (0 != iCallbackSetStateVariable(iPtrSetStateVariable, aVersion, aaStateVariable)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDiagnostics1C::StateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPeriod)
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

void DvServiceLinnCoUkDiagnostics1C::SetStateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, TUint aaPeriod)
{
    ASSERT(iCallbackSetStateVariablePeriod != NULL);
    if (0 != iCallbackSetStateVariablePeriod(iPtrSetStateVariablePeriod, aVersion, aaPeriod)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceLinnCoUkDiagnostics1C::Reboot(IInvocationResponse& aResponse, TUint aVersion, TUint aaDelay)
{
    ASSERT(iCallbackReboot != NULL);
    if (0 != iCallbackReboot(iPtrReboot, aVersion, aaDelay)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}



THandle DvServiceLinnCoUkDiagnostics1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceLinnCoUkDiagnostics1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceLinnCoUkDiagnostics1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService);
}

void DvServiceLinnCoUkDiagnostics1EnableActionEcho(THandle aService, CallbackDiagnostics1Echo aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionEcho(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionElfFile(THandle aService, CallbackDiagnostics1ElfFile aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionElfFile(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionElfFingerprint(THandle aService, CallbackDiagnostics1ElfFingerprint aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionElfFingerprint(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionCrashDataStatus(THandle aService, CallbackDiagnostics1CrashDataStatus aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionCrashDataStatus(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionCrashDataFetch(THandle aService, CallbackDiagnostics1CrashDataFetch aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionCrashDataFetch(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionCrashDataClear(THandle aService, CallbackDiagnostics1CrashDataClear aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionCrashDataClear(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionSysLog(THandle aService, CallbackDiagnostics1SysLog aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionSysLog(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionDiagnostic(THandle aService, CallbackDiagnostics1Diagnostic aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionDiagnostic(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionStateVariable(THandle aService, CallbackDiagnostics1StateVariable aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionStateVariable(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionSetStateVariable(THandle aService, CallbackDiagnostics1SetStateVariable aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionSetStateVariable(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionStateVariablePeriod(THandle aService, CallbackDiagnostics1StateVariablePeriod aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionStateVariablePeriod(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionSetStateVariablePeriod(THandle aService, CallbackDiagnostics1SetStateVariablePeriod aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionSetStateVariablePeriod(aCallback, aPtr);
}

void DvServiceLinnCoUkDiagnostics1EnableActionReboot(THandle aService, CallbackDiagnostics1Reboot aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->EnableActionReboot(aCallback, aPtr);
}

int32_t DvServiceLinnCoUkDiagnostics1SetPropertyaStateVariable(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->SetPropertyaStateVariable(aValue);
    return 0;
}

void DvServiceLinnCoUkDiagnostics1GetPropertyaStateVariable(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceLinnCoUkDiagnostics1C*>(aService)->GetPropertyaStateVariable(val);
    *aValue = val;
}

