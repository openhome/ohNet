#include <C/CpZappOrgTestBasic1.h>
#include <Core/CpZappOrgTestBasic1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyZappOrgTestBasic1C : public CpProxyC
{
public:
    CpProxyZappOrgTestBasic1C(CpDeviceC aDevice);
    CpProxyZappOrgTestBasic1* Proxy() { return static_cast<CpProxyZappOrgTestBasic1*>(iProxy); }
};

CpProxyZappOrgTestBasic1C::CpProxyZappOrgTestBasic1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyZappOrgTestBasic1(*iDevice);
}


THandle CpProxyZappOrgTestBasic1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyZappOrgTestBasic1C(aDevice);
}

void CpProxyZappOrgTestBasic1Destroy(THandle aHandle)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    delete proxyC;
}

void CpProxyZappOrgTestBasic1SyncIncrement(THandle aHandle, uint32_t aValue, uint32_t* aResult)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncIncrement(aValue, *aResult);
}

void CpProxyZappOrgTestBasic1BeginIncrement(THandle aHandle, uint32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginIncrement(aValue, functor);
}

int32_t CpProxyZappOrgTestBasic1EndIncrement(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aResult)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndIncrement(*async, *aResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncDecrement(THandle aHandle, int32_t aValue, int32_t* aResult)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDecrement(aValue, *aResult);
}

void CpProxyZappOrgTestBasic1BeginDecrement(THandle aHandle, int32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDecrement(aValue, functor);
}

int32_t CpProxyZappOrgTestBasic1EndDecrement(THandle aHandle, ZappHandleAsync aAsync, int32_t* aResult)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDecrement(*async, *aResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncToggle(THandle aHandle, uint32_t aValue, uint32_t* aResult)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aResult = 0;
    proxyC->Proxy()->SyncToggle((aValue==0? false : true), *(TBool*)aResult);
}

void CpProxyZappOrgTestBasic1BeginToggle(THandle aHandle, uint32_t aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginToggle((aValue==0? false : true), functor);
}

int32_t CpProxyZappOrgTestBasic1EndToggle(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aResult)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aResult = 0;
    try {
        proxyC->Proxy()->EndToggle(*async, *(TBool*)aResult);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncEchoString(THandle aHandle, const char* aValue, char** aResult)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue(aValue);
    Brh buf_aResult;
    proxyC->Proxy()->SyncEchoString(buf_aValue, buf_aResult);
    *aResult = buf_aResult.Extract();
}

void CpProxyZappOrgTestBasic1BeginEchoString(THandle aHandle, const char* aValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue(aValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginEchoString(buf_aValue, functor);
}

int32_t CpProxyZappOrgTestBasic1EndEchoString(THandle aHandle, ZappHandleAsync aAsync, char** aResult)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndEchoString(*async, buf_aResult);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, char** aResult, uint32_t* aResultLen)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    buf_aValue.Set((const TByte*)aValue, aValueLen);
    Brh buf_aResult;
    proxyC->Proxy()->SyncEchoBinary(buf_aValue, buf_aResult);
    *aResultLen = buf_aResult.Bytes();
    *aResult = buf_aResult.Extract();
}

void CpProxyZappOrgTestBasic1BeginEchoBinary(THandle aHandle, const char* aValue, uint32_t aValueLen, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValue;
    buf_aValue.Set((const TByte*)aValue, aValueLen);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginEchoBinary(buf_aValue, functor);
}

int32_t CpProxyZappOrgTestBasic1EndEchoBinary(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aResultLen)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    *aResultLen = 0;
    try {
        proxyC->Proxy()->EndEchoBinary(*async, buf_aResult);
        *aResultLen = buf_aResult.Bytes();
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetUint(THandle aHandle, uint32_t aValueUint)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetUint(aValueUint);
}

void CpProxyZappOrgTestBasic1BeginSetUint(THandle aHandle, uint32_t aValueUint, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetUint(aValueUint, functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetUint(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetUint(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetUint(THandle aHandle, uint32_t* aValueUint)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetUint(*aValueUint);
}

void CpProxyZappOrgTestBasic1BeginGetUint(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetUint(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetUint(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValueUint)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetUint(*async, *aValueUint);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetInt(THandle aHandle, int32_t aValueInt)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetInt(aValueInt);
}

void CpProxyZappOrgTestBasic1BeginSetInt(THandle aHandle, int32_t aValueInt, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetInt(aValueInt, functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetInt(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetInt(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetInt(THandle aHandle, int32_t* aValueInt)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetInt(*aValueInt);
}

void CpProxyZappOrgTestBasic1BeginGetInt(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetInt(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetInt(THandle aHandle, ZappHandleAsync aAsync, int32_t* aValueInt)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetInt(*async, *aValueInt);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetBool(THandle aHandle, uint32_t aValueBool)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetBool((aValueBool==0? false : true));
}

void CpProxyZappOrgTestBasic1BeginSetBool(THandle aHandle, uint32_t aValueBool, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBool((aValueBool==0? false : true), functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetBool(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetBool(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetBool(THandle aHandle, uint32_t* aValueBool)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aValueBool = 0;
    proxyC->Proxy()->SyncGetBool(*(TBool*)aValueBool);
}

void CpProxyZappOrgTestBasic1BeginGetBool(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetBool(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetBool(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aValueBool)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aValueBool = 0;
    try {
        proxyC->Proxy()->EndGetBool(*async, *(TBool*)aValueBool);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetMultiple(aValueUint, aValueInt, (aValueBool==0? false : true));
}

void CpProxyZappOrgTestBasic1BeginSetMultiple(THandle aHandle, uint32_t aValueUint, int32_t aValueInt, uint32_t aValueBool, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetMultiple(aValueUint, aValueInt, (aValueBool==0? false : true), functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetMultiple(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetMultiple(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetString(THandle aHandle, const char* aValueStr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr(aValueStr);
    proxyC->Proxy()->SyncSetString(buf_aValueStr);
}

void CpProxyZappOrgTestBasic1BeginSetString(THandle aHandle, const char* aValueStr, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr(aValueStr);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetString(buf_aValueStr, functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetString(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetString(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetString(THandle aHandle, char** aValueStr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueStr;
    proxyC->Proxy()->SyncGetString(buf_aValueStr);
    *aValueStr = buf_aValueStr.Extract();
}

void CpProxyZappOrgTestBasic1BeginGetString(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetString(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetString(THandle aHandle, ZappHandleAsync aAsync, char** aValueStr)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValueStr;
    *aValueStr = NULL;
    try {
        proxyC->Proxy()->EndGetString(*async, buf_aValueStr);
        *aValueStr = buf_aValueStr.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    buf_aValueBin.Set((const TByte*)aValueBin, aValueBinLen);
    proxyC->Proxy()->SyncSetBinary(buf_aValueBin);
}

void CpProxyZappOrgTestBasic1BeginSetBinary(THandle aHandle, const char* aValueBin, uint32_t aValueBinLen, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    buf_aValueBin.Set((const TByte*)aValueBin, aValueBinLen);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBinary(buf_aValueBin, functor);
}

int32_t CpProxyZappOrgTestBasic1EndSetBinary(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetBinary(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SyncGetBinary(THandle aHandle, char** aValueBin, uint32_t* aValueBinLen)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aValueBin;
    proxyC->Proxy()->SyncGetBinary(buf_aValueBin);
    *aValueBinLen = buf_aValueBin.Bytes();
    *aValueBin = buf_aValueBin.Extract();
}

void CpProxyZappOrgTestBasic1BeginGetBinary(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetBinary(functor);
}

int32_t CpProxyZappOrgTestBasic1EndGetBinary(THandle aHandle, ZappHandleAsync aAsync, char** aValueBin, uint32_t* aValueBinLen)
{
    int32_t err = 0;
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aValueBin;
    *aValueBin = NULL;
    *aValueBinLen = 0;
    try {
        proxyC->Proxy()->EndGetBinary(*async, buf_aValueBin);
        *aValueBinLen = buf_aValueBin.Bytes();
        *aValueBin = buf_aValueBin.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyZappOrgTestBasic1SetPropertyVarUintChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyVarUintChanged(functor);
}

void CpProxyZappOrgTestBasic1SetPropertyVarIntChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyVarIntChanged(functor);
}

void CpProxyZappOrgTestBasic1SetPropertyVarBoolChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyVarBoolChanged(functor);
}

void CpProxyZappOrgTestBasic1SetPropertyVarStrChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyVarStrChanged(functor);
}

void CpProxyZappOrgTestBasic1SetPropertyVarBinChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyVarBinChanged(functor);
}

void CpProxyZappOrgTestBasic1PropertyVarUint(THandle aHandle, uint32_t* aVarUint)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyVarUint(*aVarUint);
}

void CpProxyZappOrgTestBasic1PropertyVarInt(THandle aHandle, int32_t* aVarInt)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyVarInt(*aVarInt);
}

void CpProxyZappOrgTestBasic1PropertyVarBool(THandle aHandle, uint32_t* aVarBool)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aVarBool = false;
    proxyC->Proxy()->PropertyVarBool(*(TBool*)aVarBool);
}

void CpProxyZappOrgTestBasic1PropertyVarStr(THandle aHandle, char** aVarStr)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aVarStr;
    proxyC->Proxy()->PropertyVarStr(buf_aVarStr);
    *aVarStr = buf_aVarStr.Transfer();
}

void CpProxyZappOrgTestBasic1PropertyVarBin(THandle aHandle, char** aVarBin, uint32_t* aLen)
{
    CpProxyZappOrgTestBasic1C* proxyC = reinterpret_cast<CpProxyZappOrgTestBasic1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aVarBin;
    proxyC->Proxy()->PropertyVarBin(buf_aVarBin);
    *aLen = buf_aVarBin.Bytes();
    *aVarBin = buf_aVarBin.Extract();
}

