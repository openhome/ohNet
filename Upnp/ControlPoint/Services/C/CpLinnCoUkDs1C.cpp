#include <C/CpLinnCoUkDs1.h>
#include <Core/CpLinnCoUkDs1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyLinnCoUkDs1C : public CpProxyC
{
public:
    CpProxyLinnCoUkDs1C(CpDeviceC aDevice);
    CpProxyLinnCoUkDs1* Proxy() { return static_cast<CpProxyLinnCoUkDs1*>(iProxy); }
};

CpProxyLinnCoUkDs1C::CpProxyLinnCoUkDs1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyLinnCoUkDs1(*iDevice);
}


THandle CpProxyLinnCoUkDs1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyLinnCoUkDs1C(aDevice);
}

void CpProxyLinnCoUkDs1Destroy(THandle aHandle)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    delete proxyC;
}

void CpProxyLinnCoUkDs1SyncPlay(THandle aHandle)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPlay();
}

void CpProxyLinnCoUkDs1BeginPlay(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPlay(functor);
}

int32_t CpProxyLinnCoUkDs1EndPlay(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPlay(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncPause(THandle aHandle)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPause();
}

void CpProxyLinnCoUkDs1BeginPause(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPause(functor);
}

int32_t CpProxyLinnCoUkDs1EndPause(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPause(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncStop(THandle aHandle)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStop();
}

void CpProxyLinnCoUkDs1BeginStop(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStop(functor);
}

int32_t CpProxyLinnCoUkDs1EndStop(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStop(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekSecondAbsolute(THandle aHandle, uint32_t aaSecond)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSeekSecondAbsolute(aaSecond);
}

void CpProxyLinnCoUkDs1BeginSeekSecondAbsolute(THandle aHandle, uint32_t aaSecond, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeekSecondAbsolute(aaSecond, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekSecondAbsolute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeekSecondAbsolute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekSecondRelative(THandle aHandle, int32_t aaSecond)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSeekSecondRelative(aaSecond);
}

void CpProxyLinnCoUkDs1BeginSeekSecondRelative(THandle aHandle, int32_t aaSecond, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeekSecondRelative(aaSecond, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekSecondRelative(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeekSecondRelative(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekTrackId(THandle aHandle, uint32_t aaTrackId)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSeekTrackId(aaTrackId);
}

void CpProxyLinnCoUkDs1BeginSeekTrackId(THandle aHandle, uint32_t aaTrackId, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeekTrackId(aaTrackId, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekTrackId(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeekTrackId(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekTrackAbsolute(THandle aHandle, uint32_t aaTrack)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSeekTrackAbsolute(aaTrack);
}

void CpProxyLinnCoUkDs1BeginSeekTrackAbsolute(THandle aHandle, uint32_t aaTrack, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeekTrackAbsolute(aaTrack, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekTrackAbsolute(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeekTrackAbsolute(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncSeekTrackRelative(THandle aHandle, int32_t aaTrack)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncSeekTrackRelative(aaTrack);
}

void CpProxyLinnCoUkDs1BeginSeekTrackRelative(THandle aHandle, int32_t aaTrack, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeekTrackRelative(aaTrack, functor);
}

int32_t CpProxyLinnCoUkDs1EndSeekTrackRelative(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeekTrackRelative(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncState(THandle aHandle, char** aaTransportState, uint32_t* aaTrackDuration, uint32_t* aaTrackBitRate, uint32_t* aaTrackLossless, uint32_t* aaTrackBitDepth, uint32_t* aaTrackSampleRate, char** aaTrackCodecName, uint32_t* aaTrackId)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaTransportState;
    *aaTrackLossless = 0;
    Brh buf_aaTrackCodecName;
    proxyC->Proxy()->SyncState(buf_aaTransportState, *aaTrackDuration, *aaTrackBitRate, *(TBool*)aaTrackLossless, *aaTrackBitDepth, *aaTrackSampleRate, buf_aaTrackCodecName, *aaTrackId);
    *aaTransportState = buf_aaTransportState.Extract();
    *aaTrackCodecName = buf_aaTrackCodecName.Extract();
}

void CpProxyLinnCoUkDs1BeginState(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginState(functor);
}

int32_t CpProxyLinnCoUkDs1EndState(THandle aHandle, ZappHandleAsync aAsync, char** aaTransportState, uint32_t* aaTrackDuration, uint32_t* aaTrackBitRate, uint32_t* aaTrackLossless, uint32_t* aaTrackBitDepth, uint32_t* aaTrackSampleRate, char** aaTrackCodecName, uint32_t* aaTrackId)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaTransportState;
    *aaTransportState = NULL;
    *aaTrackLossless = 0;
    Brh buf_aaTrackCodecName;
    *aaTrackCodecName = NULL;
    try {
        proxyC->Proxy()->EndState(*async, buf_aaTransportState, *aaTrackDuration, *aaTrackBitRate, *(TBool*)aaTrackLossless, *aaTrackBitDepth, *aaTrackSampleRate, buf_aaTrackCodecName, *aaTrackId);
        *aaTransportState = buf_aaTransportState.Extract();
        *aaTrackCodecName = buf_aaTrackCodecName.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SyncProtocolInfo(THandle aHandle, char** aaSupportedProtocols)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aaSupportedProtocols;
    proxyC->Proxy()->SyncProtocolInfo(buf_aaSupportedProtocols);
    *aaSupportedProtocols = buf_aaSupportedProtocols.Extract();
}

void CpProxyLinnCoUkDs1BeginProtocolInfo(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginProtocolInfo(functor);
}

int32_t CpProxyLinnCoUkDs1EndProtocolInfo(THandle aHandle, ZappHandleAsync aAsync, char** aaSupportedProtocols)
{
    int32_t err = 0;
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aaSupportedProtocols;
    *aaSupportedProtocols = NULL;
    try {
        proxyC->Proxy()->EndProtocolInfo(*async, buf_aaSupportedProtocols);
        *aaSupportedProtocols = buf_aaSupportedProtocols.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyLinnCoUkDs1SetPropertySupportedProtocolsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySupportedProtocolsChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackDurationChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackDurationChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackBitRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackBitRateChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackLosslessChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackLosslessChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackBitDepthChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackBitDepthChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackSampleRateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackSampleRateChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackCodecNameChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackCodecNameChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTrackIdChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTrackIdChanged(functor);
}

void CpProxyLinnCoUkDs1SetPropertyTransportStateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTransportStateChanged(functor);
}

void CpProxyLinnCoUkDs1PropertySupportedProtocols(THandle aHandle, char** aSupportedProtocols)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aSupportedProtocols;
    proxyC->Proxy()->PropertySupportedProtocols(buf_aSupportedProtocols);
    *aSupportedProtocols = buf_aSupportedProtocols.Transfer();
}

void CpProxyLinnCoUkDs1PropertyTrackDuration(THandle aHandle, uint32_t* aTrackDuration)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTrackDuration(*aTrackDuration);
}

void CpProxyLinnCoUkDs1PropertyTrackBitRate(THandle aHandle, uint32_t* aTrackBitRate)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTrackBitRate(*aTrackBitRate);
}

void CpProxyLinnCoUkDs1PropertyTrackLossless(THandle aHandle, uint32_t* aTrackLossless)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    *aTrackLossless = false;
    proxyC->Proxy()->PropertyTrackLossless(*(TBool*)aTrackLossless);
}

void CpProxyLinnCoUkDs1PropertyTrackBitDepth(THandle aHandle, uint32_t* aTrackBitDepth)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTrackBitDepth(*aTrackBitDepth);
}

void CpProxyLinnCoUkDs1PropertyTrackSampleRate(THandle aHandle, uint32_t* aTrackSampleRate)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTrackSampleRate(*aTrackSampleRate);
}

void CpProxyLinnCoUkDs1PropertyTrackCodecName(THandle aHandle, char** aTrackCodecName)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTrackCodecName;
    proxyC->Proxy()->PropertyTrackCodecName(buf_aTrackCodecName);
    *aTrackCodecName = buf_aTrackCodecName.Transfer();
}

void CpProxyLinnCoUkDs1PropertyTrackId(THandle aHandle, uint32_t* aTrackId)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertyTrackId(*aTrackId);
}

void CpProxyLinnCoUkDs1PropertyTransportState(THandle aHandle, char** aTransportState)
{
    CpProxyLinnCoUkDs1C* proxyC = reinterpret_cast<CpProxyLinnCoUkDs1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransportState;
    proxyC->Proxy()->PropertyTransportState(buf_aTransportState);
    *aTransportState = buf_aTransportState.Transfer();
}

