#include <C/CpLinnCoUkVolkano1.h>
#include <Core/CpLinnCoUkVolkano1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkVolkano1C : public CpProxyC
{
public:
    CpProxyLinnCoUkVolkano1C(CpDeviceC aDevice);
    CpProxyLinnCoUkVolkano1* Proxy() { return static_cast<CpProxyLinnCoUkVolkano1*>(iProxy); }
};

CpProxyLinnCoUkVolkano1C::CpProxyLinnCoUkVolkano1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkVolkano1(*iDevice);
}


THandle CpProxyLinnCoUkVolkano1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkVolkano1C(aDevice);
}

void CpProxyLinnCoUkVolkano1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkVolkano1SyncReboot(THandle aHandle)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncReboot();
}

void CpProxyLinnCoUkVolkano1BeginReboot(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginReboot(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndReboot(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
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

void CpProxyLinnCoUkVolkano1SyncBootMode(THandle aHandle, char** aaMode)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMode;
    proxyC->Proxy()->SyncBootMode(buf_aaMode);
    *aaMode = buf_aaMode.Extract();
}

void CpProxyLinnCoUkVolkano1BeginBootMode(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBootMode(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndBootMode(THandle aHandle, ZappHandleAsync aAsync, char** aaMode)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMode;
    *aaMode = NULL;
    try {
        proxyC->Proxy()->EndBootMode(*async, buf_aaMode);
        *aaMode = buf_aaMode.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncSetBootMode(THandle aHandle, const char* aaMode)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMode(aaMode);
    proxyC->Proxy()->SyncSetBootMode(buf_aaMode);
}

void CpProxyLinnCoUkVolkano1BeginSetBootMode(THandle aHandle, const char* aaMode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMode(aaMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetBootMode(buf_aaMode, functor);
}

int32_t CpProxyLinnCoUkVolkano1EndSetBootMode(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetBootMode(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncBspType(THandle aHandle, char** aaBspType)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaBspType;
    proxyC->Proxy()->SyncBspType(buf_aaBspType);
    *aaBspType = buf_aaBspType.Extract();
}

void CpProxyLinnCoUkVolkano1BeginBspType(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBspType(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndBspType(THandle aHandle, ZappHandleAsync aAsync, char** aaBspType)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaBspType;
    *aaBspType = NULL;
    try {
        proxyC->Proxy()->EndBspType(*async, buf_aaBspType);
        *aaBspType = buf_aaBspType.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncUglyName(THandle aHandle, char** aaUglyName)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaUglyName;
    proxyC->Proxy()->SyncUglyName(buf_aaUglyName);
    *aaUglyName = buf_aaUglyName.Extract();
}

void CpProxyLinnCoUkVolkano1BeginUglyName(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginUglyName(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndUglyName(THandle aHandle, ZappHandleAsync aAsync, char** aaUglyName)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaUglyName;
    *aaUglyName = NULL;
    try {
        proxyC->Proxy()->EndUglyName(*async, buf_aaUglyName);
        *aaUglyName = buf_aaUglyName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncMacAddress(THandle aHandle, char** aaMacAddress)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaMacAddress;
    proxyC->Proxy()->SyncMacAddress(buf_aaMacAddress);
    *aaMacAddress = buf_aaMacAddress.Extract();
}

void CpProxyLinnCoUkVolkano1BeginMacAddress(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginMacAddress(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndMacAddress(THandle aHandle, ZappHandleAsync aAsync, char** aaMacAddress)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaMacAddress;
    *aaMacAddress = NULL;
    try {
        proxyC->Proxy()->EndMacAddress(*async, buf_aaMacAddress);
        *aaMacAddress = buf_aaMacAddress.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncProductId(THandle aHandle, char** aaProductNumber)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaProductNumber;
    proxyC->Proxy()->SyncProductId(buf_aaProductNumber);
    *aaProductNumber = buf_aaProductNumber.Extract();
}

void CpProxyLinnCoUkVolkano1BeginProductId(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginProductId(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndProductId(THandle aHandle, ZappHandleAsync aAsync, char** aaProductNumber)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaProductNumber;
    *aaProductNumber = NULL;
    try {
        proxyC->Proxy()->EndProductId(*async, buf_aaProductNumber);
        *aaProductNumber = buf_aaProductNumber.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncBoardId(THandle aHandle, uint32_t aaIndex, char** aaBoardNumber)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaBoardNumber;
    proxyC->Proxy()->SyncBoardId(aaIndex, buf_aaBoardNumber);
    *aaBoardNumber = buf_aaBoardNumber.Extract();
}

void CpProxyLinnCoUkVolkano1BeginBoardId(THandle aHandle, uint32_t aaIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBoardId(aaIndex, functor);
}

int32_t CpProxyLinnCoUkVolkano1EndBoardId(THandle aHandle, ZappHandleAsync aAsync, char** aaBoardNumber)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaBoardNumber;
    *aaBoardNumber = NULL;
    try {
        proxyC->Proxy()->EndBoardId(*async, buf_aaBoardNumber);
        *aaBoardNumber = buf_aaBoardNumber.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncBoardType(THandle aHandle, uint32_t aaIndex, char** aaBoardNumber)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaBoardNumber;
    proxyC->Proxy()->SyncBoardType(aaIndex, buf_aaBoardNumber);
    *aaBoardNumber = buf_aaBoardNumber.Extract();
}

void CpProxyLinnCoUkVolkano1BeginBoardType(THandle aHandle, uint32_t aaIndex, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBoardType(aaIndex, functor);
}

int32_t CpProxyLinnCoUkVolkano1EndBoardType(THandle aHandle, ZappHandleAsync aAsync, char** aaBoardNumber)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaBoardNumber;
    *aaBoardNumber = NULL;
    try {
        proxyC->Proxy()->EndBoardType(*async, buf_aaBoardNumber);
        *aaBoardNumber = buf_aaBoardNumber.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncMaxBoards(THandle aHandle, uint32_t* aaMaxBoards)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncMaxBoards(*aaMaxBoards);
}

void CpProxyLinnCoUkVolkano1BeginMaxBoards(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginMaxBoards(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndMaxBoards(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaMaxBoards)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndMaxBoards(*async, *aaMaxBoards);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkVolkano1SyncSoftwareVersion(THandle aHandle, char** aaSoftwareVersion)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSoftwareVersion;
    proxyC->Proxy()->SyncSoftwareVersion(buf_aaSoftwareVersion);
    *aaSoftwareVersion = buf_aaSoftwareVersion.Extract();
}

void CpProxyLinnCoUkVolkano1BeginSoftwareVersion(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSoftwareVersion(functor);
}

int32_t CpProxyLinnCoUkVolkano1EndSoftwareVersion(THandle aHandle, ZappHandleAsync aAsync, char** aaSoftwareVersion)
{
    int32_t err = 0;
    CpProxyLinnCoUkVolkano1C* proxyC = reinterpret_cast<CpProxyLinnCoUkVolkano1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSoftwareVersion;
    *aaSoftwareVersion = NULL;
    try {
        proxyC->Proxy()->EndSoftwareVersion(*async, buf_aaSoftwareVersion);
        *aaSoftwareVersion = buf_aaSoftwareVersion.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

