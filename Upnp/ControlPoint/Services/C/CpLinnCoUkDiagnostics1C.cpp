#include <C/CpLinnCoUkDiagnostics1.h>
#include <Core/CpLinnCoUkDiagnostics1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkDiagnostics1C : public CpProxyC
{
public:
    CpProxyLinnCoUkDiagnostics1C(CpDeviceC aDevice);
    CpProxyLinnCoUkDiagnostics1* Proxy() { return static_cast<CpProxyLinnCoUkDiagnostics1*>(iProxy); }
};

CpProxyLinnCoUkDiagnostics1C::CpProxyLinnCoUkDiagnostics1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkDiagnostics1(*iDevice);
}


THandle CpProxyLinnCoUkDiagnostics1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkDiagnostics1C(aDevice);
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
    proxyC->Proxy()->SyncEcho(buf_aaIn, buf_aaOut);
    *aaOut = buf_aaOut.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginEcho(THandle aHandle, const char* aaIn, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaIn(aaIn);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginEcho(buf_aaIn, functor);
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
        proxyC->Proxy()->EndEcho(*async, buf_aaOut);
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
    proxyC->Proxy()->SyncElfFile(buf_aaElfFile);
    *aaElfFile = buf_aaElfFile.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginElfFile(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginElfFile(functor);
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
        proxyC->Proxy()->EndElfFile(*async, buf_aaElfFile);
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
    proxyC->Proxy()->SyncElfFingerprint(buf_aaElfFileFingerprint);
    *aaElfFileFingerprint = buf_aaElfFileFingerprint.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginElfFingerprint(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginElfFingerprint(functor);
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
        proxyC->Proxy()->EndElfFingerprint(*async, buf_aaElfFileFingerprint);
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
    proxyC->Proxy()->SyncCrashDataStatus(buf_aaCrashDataStatus);
    *aaCrashDataStatus = buf_aaCrashDataStatus.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginCrashDataStatus(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCrashDataStatus(functor);
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
        proxyC->Proxy()->EndCrashDataStatus(*async, buf_aaCrashDataStatus);
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
    proxyC->Proxy()->SyncCrashDataFetch(buf_aaCrashData);
    *aaCrashDataLen = buf_aaCrashData.Bytes();
    *aaCrashData = buf_aaCrashData.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginCrashDataFetch(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCrashDataFetch(functor);
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
        proxyC->Proxy()->EndCrashDataFetch(*async, buf_aaCrashData);
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
    proxyC->Proxy()->SyncCrashDataClear();
}

void CpProxyLinnCoUkDiagnostics1BeginCrashDataClear(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCrashDataClear(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndCrashDataClear(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndCrashDataClear(*async);
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
    proxyC->Proxy()->SyncSysLog(buf_aaSysLog);
    *aaSysLogLen = buf_aaSysLog.Bytes();
    *aaSysLog = buf_aaSysLog.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginSysLog(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSysLog(functor);
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
        proxyC->Proxy()->EndSysLog(*async, buf_aaSysLog);
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
    proxyC->Proxy()->SyncDiagnostic(buf_aaDiagnosticType, buf_aaDiagnosticInfo);
    *aaDiagnosticInfo = buf_aaDiagnosticInfo.Extract();
}

void CpProxyLinnCoUkDiagnostics1BeginDiagnostic(THandle aHandle, const char* aaDiagnosticType, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaDiagnosticType(aaDiagnosticType);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDiagnostic(buf_aaDiagnosticType, functor);
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
        proxyC->Proxy()->EndDiagnostic(*async, buf_aaDiagnosticInfo);
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
    proxyC->Proxy()->SyncStateVariable(*aaStateVariable);
}

void CpProxyLinnCoUkDiagnostics1BeginStateVariable(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStateVariable(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndStateVariable(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaStateVariable)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStateVariable(*async, *aaStateVariable);
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
    proxyC->Proxy()->SyncSetStateVariable(aaStateVariable);
}

void CpProxyLinnCoUkDiagnostics1BeginSetStateVariable(THandle aHandle, uint32_t aaStateVariable, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStateVariable(aaStateVariable, functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndSetStateVariable(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStateVariable(*async);
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
    proxyC->Proxy()->SyncStateVariablePeriod(*aaPeriod);
}

void CpProxyLinnCoUkDiagnostics1BeginStateVariablePeriod(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStateVariablePeriod(functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndStateVariablePeriod(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaPeriod)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStateVariablePeriod(*async, *aaPeriod);
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
    proxyC->Proxy()->SyncSetStateVariablePeriod(aaPeriod);
}

void CpProxyLinnCoUkDiagnostics1BeginSetStateVariablePeriod(THandle aHandle, uint32_t aaPeriod, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStateVariablePeriod(aaPeriod, functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndSetStateVariablePeriod(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetStateVariablePeriod(*async);
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
    proxyC->Proxy()->SyncReboot(aaDelay);
}

void CpProxyLinnCoUkDiagnostics1BeginReboot(THandle aHandle, uint32_t aaDelay, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginReboot(aaDelay, functor);
}

int32_t CpProxyLinnCoUkDiagnostics1EndReboot(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndReboot(*async);
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
    proxyC->Proxy()->SetPropertyaStateVariableChanged(functor);
}

void CpProxyLinnCoUkDiagnostics1PropertyaStateVariable(THandle aHandle, uint32_t* aaStateVariable)
{
    CpProxyLinnCoUkDiagnostics1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDiagnostics1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyaStateVariable(*aaStateVariable);
}

