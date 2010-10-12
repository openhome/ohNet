#include <C/CpLinnCoUkUi2.h>
#include <Core/CpLinnCoUkUi2.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkUi2C : public CpProxyC
{
public:
    CpProxyLinnCoUkUi2C(CpDeviceC aDevice);
    CpProxyLinnCoUkUi2* Proxy() { return static_cast<CpProxyLinnCoUkUi2*>(iProxy); }
};

CpProxyLinnCoUkUi2C::CpProxyLinnCoUkUi2C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkUi2(*iDevice);
}


THandle CpProxyLinnCoUkUi2Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkUi2C(aDevice);
}

void CpProxyLinnCoUkUi2Destroy(THandle aHandle)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkUi2SyncDisplayTestPattern(THandle aHandle, int32_t aaTestPattern)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDisplayTestPattern(aaTestPattern);
}

void CpProxyLinnCoUkUi2BeginDisplayTestPattern(THandle aHandle, int32_t aaTestPattern, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplayTestPattern(aaTestPattern, functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayTestPattern(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDisplayTestPattern(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayFill(THandle aHandle)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDisplayFill();
}

void CpProxyLinnCoUkUi2BeginDisplayFill(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplayFill(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayFill(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDisplayFill(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayClear(THandle aHandle)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDisplayClear();
}

void CpProxyLinnCoUkUi2BeginDisplayClear(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplayClear(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayClear(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDisplayClear(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetTestModeEnabled(THandle aHandle, uint32_t aaEnabled)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetTestModeEnabled((aaEnabled==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetTestModeEnabled(THandle aHandle, uint32_t aaEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetTestModeEnabled((aaEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetTestModeEnabled(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetTestModeEnabled(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSimulateInfraredInput(THandle aHandle, uint32_t aaCode)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSimulateInfraredInput(aaCode);
}

void CpProxyLinnCoUkUi2BeginSimulateInfraredInput(THandle aHandle, uint32_t aaCode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSimulateInfraredInput(aaCode, functor);
}

int32_t CpProxyLinnCoUkUi2EndSimulateInfraredInput(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSimulateInfraredInput(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSimulateButtonInput(THandle aHandle, uint32_t aaCode)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSimulateButtonInput(aaCode);
}

void CpProxyLinnCoUkUi2BeginSimulateButtonInput(THandle aHandle, uint32_t aaCode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSimulateButtonInput(aaCode, functor);
}

int32_t CpProxyLinnCoUkUi2EndSimulateButtonInput(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSimulateButtonInput(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSimulateLightSensor(THandle aHandle, uint32_t aaLightLevel)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSimulateLightSensor(aaLightLevel);
}

void CpProxyLinnCoUkUi2BeginSimulateLightSensor(THandle aHandle, uint32_t aaLightLevel, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSimulateLightSensor(aaLightLevel, functor);
}

int32_t CpProxyLinnCoUkUi2EndSimulateLightSensor(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSimulateLightSensor(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncGetLightSensorData(THandle aHandle, uint32_t* aaLightLevel)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetLightSensorData(*aaLightLevel);
}

void CpProxyLinnCoUkUi2BeginGetLightSensorData(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetLightSensorData(functor);
}

int32_t CpProxyLinnCoUkUi2EndGetLightSensorData(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaLightLevel)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetLightSensorData(*async, *aaLightLevel);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayBrightness(THandle aHandle, uint32_t aaBrightness)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetDisplayBrightness(aaBrightness);
}

void CpProxyLinnCoUkUi2BeginSetDisplayBrightness(THandle aHandle, uint32_t aaBrightness, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDisplayBrightness(aaBrightness, functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayBrightness(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDisplayBrightness(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayBrightnessAuto(THandle aHandle, uint32_t aaBrightnessAuto)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetDisplayBrightnessAuto((aaBrightnessAuto==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplayBrightnessAuto(THandle aHandle, uint32_t aaBrightnessAuto, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDisplayBrightnessAuto((aaBrightnessAuto==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayBrightnessAuto(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDisplayBrightnessAuto(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetInfraredCommands(THandle aHandle, const char* aaCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands(aaCommands);
    proxyC->Proxy()->SyncSetInfraredCommands(buf_aaCommands);
}

void CpProxyLinnCoUkUi2BeginSetInfraredCommands(THandle aHandle, const char* aaCommands, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands(aaCommands);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetInfraredCommands(buf_aaCommands, functor);
}

int32_t CpProxyLinnCoUkUi2EndSetInfraredCommands(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetInfraredCommands(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncInfraredCommands(THandle aHandle, char** aaCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands;
    proxyC->Proxy()->SyncInfraredCommands(buf_aaCommands);
    *aaCommands = buf_aaCommands.Extract();
}

void CpProxyLinnCoUkUi2BeginInfraredCommands(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginInfraredCommands(functor);
}

int32_t CpProxyLinnCoUkUi2EndInfraredCommands(THandle aHandle, ZappHandleAsync aAsync, char** aaCommands)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaCommands;
    *aaCommands = NULL;
    try {
        proxyC->Proxy()->EndInfraredCommands(*async, buf_aaCommands);
        *aaCommands = buf_aaCommands.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetInfraredTerminalCommands(THandle aHandle, const char* aaCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands(aaCommands);
    proxyC->Proxy()->SyncSetInfraredTerminalCommands(buf_aaCommands);
}

void CpProxyLinnCoUkUi2BeginSetInfraredTerminalCommands(THandle aHandle, const char* aaCommands, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands(aaCommands);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetInfraredTerminalCommands(buf_aaCommands, functor);
}

int32_t CpProxyLinnCoUkUi2EndSetInfraredTerminalCommands(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetInfraredTerminalCommands(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncInfraredTerminalCommands(THandle aHandle, char** aaCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaCommands;
    proxyC->Proxy()->SyncInfraredTerminalCommands(buf_aaCommands);
    *aaCommands = buf_aaCommands.Extract();
}

void CpProxyLinnCoUkUi2BeginInfraredTerminalCommands(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginInfraredTerminalCommands(functor);
}

int32_t CpProxyLinnCoUkUi2EndInfraredTerminalCommands(THandle aHandle, ZappHandleAsync aAsync, char** aaCommands)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaCommands;
    *aaCommands = NULL;
    try {
        proxyC->Proxy()->EndInfraredTerminalCommands(*async, buf_aaCommands);
        *aaCommands = buf_aaCommands.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayBrightness(THandle aHandle, uint32_t* aaBrightness)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncDisplayBrightness(*aaBrightness);
}

void CpProxyLinnCoUkUi2BeginDisplayBrightness(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplayBrightness(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayBrightness(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaBrightness)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDisplayBrightness(*async, *aaBrightness);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayBrightnessAuto(THandle aHandle, uint32_t* aaBrightnessAuto)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaBrightnessAuto = 0;
    proxyC->Proxy()->SyncDisplayBrightnessAuto(*(TBool*)aaBrightnessAuto);
}

void CpProxyLinnCoUkUi2BeginDisplayBrightnessAuto(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplayBrightnessAuto(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayBrightnessAuto(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaBrightnessAuto)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaBrightnessAuto = 0;
    try {
        proxyC->Proxy()->EndDisplayBrightnessAuto(*async, *(TBool*)aaBrightnessAuto);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayUpsideDown(THandle aHandle, uint32_t* aaUpsideDown)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaUpsideDown = 0;
    proxyC->Proxy()->SyncDisplayUpsideDown(*(TBool*)aaUpsideDown);
}

void CpProxyLinnCoUkUi2BeginDisplayUpsideDown(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplayUpsideDown(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayUpsideDown(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaUpsideDown)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaUpsideDown = 0;
    try {
        proxyC->Proxy()->EndDisplayUpsideDown(*async, *(TBool*)aaUpsideDown);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayUpsideDown(THandle aHandle, uint32_t aaUpsideDown)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetDisplayUpsideDown((aaUpsideDown==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplayUpsideDown(THandle aHandle, uint32_t aaUpsideDown, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDisplayUpsideDown((aaUpsideDown==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayUpsideDown(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDisplayUpsideDown(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayScrollText(THandle aHandle, uint32_t aaDisplayScrollText)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetDisplayScrollText((aaDisplayScrollText==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplayScrollText(THandle aHandle, uint32_t aaDisplayScrollText, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDisplayScrollText((aaDisplayScrollText==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayScrollText(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDisplayScrollText(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayScrollText(THandle aHandle, uint32_t* aaDisplayScrollTextEnabled)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaDisplayScrollTextEnabled = 0;
    proxyC->Proxy()->SyncDisplayScrollText(*(TBool*)aaDisplayScrollTextEnabled);
}

void CpProxyLinnCoUkUi2BeginDisplayScrollText(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplayScrollText(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayScrollText(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaDisplayScrollTextEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaDisplayScrollTextEnabled = 0;
    try {
        proxyC->Proxy()->EndDisplayScrollText(*async, *(TBool*)aaDisplayScrollTextEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplaySleep(THandle aHandle, uint32_t aaEnabled)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetDisplaySleep((aaEnabled==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplaySleep(THandle aHandle, uint32_t aaEnabled, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDisplaySleep((aaEnabled==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplaySleep(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDisplaySleep(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplaySleep(THandle aHandle, uint32_t* aaEnabled)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaEnabled = 0;
    proxyC->Proxy()->SyncDisplaySleep(*(TBool*)aaEnabled);
}

void CpProxyLinnCoUkUi2BeginDisplaySleep(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplaySleep(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplaySleep(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaEnabled)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaEnabled = 0;
    try {
        proxyC->Proxy()->EndDisplaySleep(*async, *(TBool*)aaEnabled);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncSetDisplayLedOff(THandle aHandle, uint32_t aaOff)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSetDisplayLedOff((aaOff==0? false : true));
}

void CpProxyLinnCoUkUi2BeginSetDisplayLedOff(THandle aHandle, uint32_t aaOff, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetDisplayLedOff((aaOff==0? false : true), functor);
}

int32_t CpProxyLinnCoUkUi2EndSetDisplayLedOff(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetDisplayLedOff(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SyncDisplayLedOff(THandle aHandle, uint32_t* aaOff)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aaOff = 0;
    proxyC->Proxy()->SyncDisplayLedOff(*(TBool*)aaOff);
}

void CpProxyLinnCoUkUi2BeginDisplayLedOff(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisplayLedOff(functor);
}

int32_t CpProxyLinnCoUkUi2EndDisplayLedOff(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aaOff)
{
    int32_t err = 0;
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    *aaOff = 0;
    try {
        proxyC->Proxy()->EndDisplayLedOff(*async, *(TBool*)aaOff);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDisplayBrightnessChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayBrightnessAutoChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDisplayBrightnessAutoChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyInfraredCommandsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyInfraredCommandsChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyInfraredTerminalCommandsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyInfraredTerminalCommandsChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayUpsideDownChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDisplayUpsideDownChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayScrollTextChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDisplayScrollTextChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplaySleepChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDisplaySleepChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayLedOffChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDisplayLedOffChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyTerminalInputCodeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTerminalInputCodeChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyTerminalInputNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTerminalInputNameChanged(functor);
}

void CpProxyLinnCoUkUi2SetPropertyDisplayPixelsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDisplayPixelsChanged(functor);
}

void CpProxyLinnCoUkUi2PropertyDisplayBrightness(THandle aHandle, uint32_t* aDisplayBrightness)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyDisplayBrightness(*aDisplayBrightness);
}

void CpProxyLinnCoUkUi2PropertyDisplayBrightnessAuto(THandle aHandle, uint32_t* aDisplayBrightnessAuto)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplayBrightnessAuto = false;
    proxyC->Proxy()->PropertyDisplayBrightnessAuto(*(TBool*)aDisplayBrightnessAuto);
}

void CpProxyLinnCoUkUi2PropertyInfraredCommands(THandle aHandle, char** aInfraredCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aInfraredCommands;
    proxyC->Proxy()->PropertyInfraredCommands(buf_aInfraredCommands);
    *aInfraredCommands = buf_aInfraredCommands.Transfer();
}

void CpProxyLinnCoUkUi2PropertyInfraredTerminalCommands(THandle aHandle, char** aInfraredTerminalCommands)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aInfraredTerminalCommands;
    proxyC->Proxy()->PropertyInfraredTerminalCommands(buf_aInfraredTerminalCommands);
    *aInfraredTerminalCommands = buf_aInfraredTerminalCommands.Transfer();
}

void CpProxyLinnCoUkUi2PropertyDisplayUpsideDown(THandle aHandle, uint32_t* aDisplayUpsideDown)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplayUpsideDown = false;
    proxyC->Proxy()->PropertyDisplayUpsideDown(*(TBool*)aDisplayUpsideDown);
}

void CpProxyLinnCoUkUi2PropertyDisplayScrollText(THandle aHandle, uint32_t* aDisplayScrollText)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplayScrollText = false;
    proxyC->Proxy()->PropertyDisplayScrollText(*(TBool*)aDisplayScrollText);
}

void CpProxyLinnCoUkUi2PropertyDisplaySleep(THandle aHandle, uint32_t* aDisplaySleep)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplaySleep = false;
    proxyC->Proxy()->PropertyDisplaySleep(*(TBool*)aDisplaySleep);
}

void CpProxyLinnCoUkUi2PropertyDisplayLedOff(THandle aHandle, uint32_t* aDisplayLedOff)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aDisplayLedOff = false;
    proxyC->Proxy()->PropertyDisplayLedOff(*(TBool*)aDisplayLedOff);
}

void CpProxyLinnCoUkUi2PropertyTerminalInputCode(THandle aHandle, uint32_t* aTerminalInputCode)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTerminalInputCode(*aTerminalInputCode);
}

void CpProxyLinnCoUkUi2PropertyTerminalInputName(THandle aHandle, char** aTerminalInputName)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTerminalInputName;
    proxyC->Proxy()->PropertyTerminalInputName(buf_aTerminalInputName);
    *aTerminalInputName = buf_aTerminalInputName.Transfer();
}

void CpProxyLinnCoUkUi2PropertyDisplayPixels(THandle aHandle, char** aDisplayPixels, uint32_t* aLen)
{
    CpProxyLinnCoUkUi2C* proxyC = reinterpret_cast<CpProxyLinnCoUkUi2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDisplayPixels;
    proxyC->Proxy()->PropertyDisplayPixels(buf_aDisplayPixels);
    *aLen = buf_aDisplayPixels.Bytes();
    *aDisplayPixels = buf_aDisplayPixels.Extract();
}

