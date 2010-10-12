#include <C/CpUpnpOrgAVTransport1.h>
#include <Core/CpUpnpOrgAVTransport1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgAVTransport1C : public CpProxyC
{
public:
    CpProxyUpnpOrgAVTransport1C(CpDeviceC aDevice);
    CpProxyUpnpOrgAVTransport1* Proxy() { return static_cast<CpProxyUpnpOrgAVTransport1*>(iProxy); }
};

CpProxyUpnpOrgAVTransport1C::CpProxyUpnpOrgAVTransport1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgAVTransport1(*iDevice);
}


THandle CpProxyUpnpOrgAVTransport1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgAVTransport1C(aDevice);
}

void CpProxyUpnpOrgAVTransport1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgAVTransport1SyncSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentURI(aCurrentURI);
    Brh buf_aCurrentURIMetaData(aCurrentURIMetaData);
    proxyC->Proxy()->SyncSetAVTransportURI(aInstanceID, buf_aCurrentURI, buf_aCurrentURIMetaData);
}

void CpProxyUpnpOrgAVTransport1BeginSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentURI(aCurrentURI);
    Brh buf_aCurrentURIMetaData(aCurrentURIMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetAVTransportURI(aInstanceID, buf_aCurrentURI, buf_aCurrentURIMetaData, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndSetAVTransportURI(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetAVTransportURI(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNextURI(aNextURI);
    Brh buf_aNextURIMetaData(aNextURIMetaData);
    proxyC->Proxy()->SyncSetNextAVTransportURI(aInstanceID, buf_aNextURI, buf_aNextURIMetaData);
}

void CpProxyUpnpOrgAVTransport1BeginSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNextURI(aNextURI);
    Brh buf_aNextURIMetaData(aNextURIMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetNextAVTransportURI(aInstanceID, buf_aNextURI, buf_aNextURIMetaData, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndSetNextAVTransportURI(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetNextAVTransportURI(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncGetMediaInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aMediaDuration;
    Brh buf_aCurrentURI;
    Brh buf_aCurrentURIMetaData;
    Brh buf_aNextURI;
    Brh buf_aNextURIMetaData;
    Brh buf_aPlayMedium;
    Brh buf_aRecordMedium;
    Brh buf_aWriteStatus;
    proxyC->Proxy()->SyncGetMediaInfo(aInstanceID, *aNrTracks, buf_aMediaDuration, buf_aCurrentURI, buf_aCurrentURIMetaData, buf_aNextURI, buf_aNextURIMetaData, buf_aPlayMedium, buf_aRecordMedium, buf_aWriteStatus);
    *aMediaDuration = buf_aMediaDuration.Extract();
    *aCurrentURI = buf_aCurrentURI.Extract();
    *aCurrentURIMetaData = buf_aCurrentURIMetaData.Extract();
    *aNextURI = buf_aNextURI.Extract();
    *aNextURIMetaData = buf_aNextURIMetaData.Extract();
    *aPlayMedium = buf_aPlayMedium.Extract();
    *aRecordMedium = buf_aRecordMedium.Extract();
    *aWriteStatus = buf_aWriteStatus.Extract();
}

void CpProxyUpnpOrgAVTransport1BeginGetMediaInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetMediaInfo(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndGetMediaInfo(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aMediaDuration;
    *aMediaDuration = NULL;
    Brh buf_aCurrentURI;
    *aCurrentURI = NULL;
    Brh buf_aCurrentURIMetaData;
    *aCurrentURIMetaData = NULL;
    Brh buf_aNextURI;
    *aNextURI = NULL;
    Brh buf_aNextURIMetaData;
    *aNextURIMetaData = NULL;
    Brh buf_aPlayMedium;
    *aPlayMedium = NULL;
    Brh buf_aRecordMedium;
    *aRecordMedium = NULL;
    Brh buf_aWriteStatus;
    *aWriteStatus = NULL;
    try {
        proxyC->Proxy()->EndGetMediaInfo(*async, *aNrTracks, buf_aMediaDuration, buf_aCurrentURI, buf_aCurrentURIMetaData, buf_aNextURI, buf_aNextURIMetaData, buf_aPlayMedium, buf_aRecordMedium, buf_aWriteStatus);
        *aMediaDuration = buf_aMediaDuration.Extract();
        *aCurrentURI = buf_aCurrentURI.Extract();
        *aCurrentURIMetaData = buf_aCurrentURIMetaData.Extract();
        *aNextURI = buf_aNextURI.Extract();
        *aNextURIMetaData = buf_aNextURIMetaData.Extract();
        *aPlayMedium = buf_aPlayMedium.Extract();
        *aRecordMedium = buf_aRecordMedium.Extract();
        *aWriteStatus = buf_aWriteStatus.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncGetTransportInfo(THandle aHandle, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentTransportState;
    Brh buf_aCurrentTransportStatus;
    Brh buf_aCurrentSpeed;
    proxyC->Proxy()->SyncGetTransportInfo(aInstanceID, buf_aCurrentTransportState, buf_aCurrentTransportStatus, buf_aCurrentSpeed);
    *aCurrentTransportState = buf_aCurrentTransportState.Extract();
    *aCurrentTransportStatus = buf_aCurrentTransportStatus.Extract();
    *aCurrentSpeed = buf_aCurrentSpeed.Extract();
}

void CpProxyUpnpOrgAVTransport1BeginGetTransportInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetTransportInfo(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndGetTransportInfo(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aCurrentTransportState;
    *aCurrentTransportState = NULL;
    Brh buf_aCurrentTransportStatus;
    *aCurrentTransportStatus = NULL;
    Brh buf_aCurrentSpeed;
    *aCurrentSpeed = NULL;
    try {
        proxyC->Proxy()->EndGetTransportInfo(*async, buf_aCurrentTransportState, buf_aCurrentTransportStatus, buf_aCurrentSpeed);
        *aCurrentTransportState = buf_aCurrentTransportState.Extract();
        *aCurrentTransportStatus = buf_aCurrentTransportStatus.Extract();
        *aCurrentSpeed = buf_aCurrentSpeed.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncGetPositionInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTrackDuration;
    Brh buf_aTrackMetaData;
    Brh buf_aTrackURI;
    Brh buf_aRelTime;
    Brh buf_aAbsTime;
    proxyC->Proxy()->SyncGetPositionInfo(aInstanceID, *aTrack, buf_aTrackDuration, buf_aTrackMetaData, buf_aTrackURI, buf_aRelTime, buf_aAbsTime, *aRelCount, *aAbsCount);
    *aTrackDuration = buf_aTrackDuration.Extract();
    *aTrackMetaData = buf_aTrackMetaData.Extract();
    *aTrackURI = buf_aTrackURI.Extract();
    *aRelTime = buf_aRelTime.Extract();
    *aAbsTime = buf_aAbsTime.Extract();
}

void CpProxyUpnpOrgAVTransport1BeginGetPositionInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetPositionInfo(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndGetPositionInfo(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aTrackDuration;
    *aTrackDuration = NULL;
    Brh buf_aTrackMetaData;
    *aTrackMetaData = NULL;
    Brh buf_aTrackURI;
    *aTrackURI = NULL;
    Brh buf_aRelTime;
    *aRelTime = NULL;
    Brh buf_aAbsTime;
    *aAbsTime = NULL;
    try {
        proxyC->Proxy()->EndGetPositionInfo(*async, *aTrack, buf_aTrackDuration, buf_aTrackMetaData, buf_aTrackURI, buf_aRelTime, buf_aAbsTime, *aRelCount, *aAbsCount);
        *aTrackDuration = buf_aTrackDuration.Extract();
        *aTrackMetaData = buf_aTrackMetaData.Extract();
        *aTrackURI = buf_aTrackURI.Extract();
        *aRelTime = buf_aRelTime.Extract();
        *aAbsTime = buf_aAbsTime.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPlayMedia;
    Brh buf_aRecMedia;
    Brh buf_aRecQualityModes;
    proxyC->Proxy()->SyncGetDeviceCapabilities(aInstanceID, buf_aPlayMedia, buf_aRecMedia, buf_aRecQualityModes);
    *aPlayMedia = buf_aPlayMedia.Extract();
    *aRecMedia = buf_aRecMedia.Extract();
    *aRecQualityModes = buf_aRecQualityModes.Extract();
}

void CpProxyUpnpOrgAVTransport1BeginGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetDeviceCapabilities(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndGetDeviceCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPlayMedia;
    *aPlayMedia = NULL;
    Brh buf_aRecMedia;
    *aRecMedia = NULL;
    Brh buf_aRecQualityModes;
    *aRecQualityModes = NULL;
    try {
        proxyC->Proxy()->EndGetDeviceCapabilities(*async, buf_aPlayMedia, buf_aRecMedia, buf_aRecQualityModes);
        *aPlayMedia = buf_aPlayMedia.Extract();
        *aRecMedia = buf_aRecMedia.Extract();
        *aRecQualityModes = buf_aRecQualityModes.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncGetTransportSettings(THandle aHandle, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPlayMode;
    Brh buf_aRecQualityMode;
    proxyC->Proxy()->SyncGetTransportSettings(aInstanceID, buf_aPlayMode, buf_aRecQualityMode);
    *aPlayMode = buf_aPlayMode.Extract();
    *aRecQualityMode = buf_aRecQualityMode.Extract();
}

void CpProxyUpnpOrgAVTransport1BeginGetTransportSettings(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetTransportSettings(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndGetTransportSettings(THandle aHandle, ZappHandleAsync aAsync, char** aPlayMode, char** aRecQualityMode)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPlayMode;
    *aPlayMode = NULL;
    Brh buf_aRecQualityMode;
    *aRecQualityMode = NULL;
    try {
        proxyC->Proxy()->EndGetTransportSettings(*async, buf_aPlayMode, buf_aRecQualityMode);
        *aPlayMode = buf_aPlayMode.Extract();
        *aRecQualityMode = buf_aRecQualityMode.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncStop(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStop(aInstanceID);
}

void CpProxyUpnpOrgAVTransport1BeginStop(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStop(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndStop(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport1SyncPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSpeed(aSpeed);
    proxyC->Proxy()->SyncPlay(aInstanceID, buf_aSpeed);
}

void CpProxyUpnpOrgAVTransport1BeginPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSpeed(aSpeed);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPlay(aInstanceID, buf_aSpeed, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndPlay(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport1SyncPause(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPause(aInstanceID);
}

void CpProxyUpnpOrgAVTransport1BeginPause(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPause(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndPause(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport1SyncRecord(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncRecord(aInstanceID);
}

void CpProxyUpnpOrgAVTransport1BeginRecord(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRecord(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndRecord(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndRecord(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUnit(aUnit);
    Brh buf_aTarget(aTarget);
    proxyC->Proxy()->SyncSeek(aInstanceID, buf_aUnit, buf_aTarget);
}

void CpProxyUpnpOrgAVTransport1BeginSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUnit(aUnit);
    Brh buf_aTarget(aTarget);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeek(aInstanceID, buf_aUnit, buf_aTarget, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndSeek(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSeek(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncNext(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncNext(aInstanceID);
}

void CpProxyUpnpOrgAVTransport1BeginNext(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginNext(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndNext(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndNext(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncPrevious(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPrevious(aInstanceID);
}

void CpProxyUpnpOrgAVTransport1BeginPrevious(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPrevious(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndPrevious(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndPrevious(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewPlayMode(aNewPlayMode);
    proxyC->Proxy()->SyncSetPlayMode(aInstanceID, buf_aNewPlayMode);
}

void CpProxyUpnpOrgAVTransport1BeginSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewPlayMode(aNewPlayMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetPlayMode(aInstanceID, buf_aNewPlayMode, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndSetPlayMode(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetPlayMode(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewRecordQualityMode(aNewRecordQualityMode);
    proxyC->Proxy()->SyncSetRecordQualityMode(aInstanceID, buf_aNewRecordQualityMode);
}

void CpProxyUpnpOrgAVTransport1BeginSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewRecordQualityMode(aNewRecordQualityMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRecordQualityMode(aInstanceID, buf_aNewRecordQualityMode, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndSetRecordQualityMode(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndSetRecordQualityMode(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SyncGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, char** aActions)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aActions;
    proxyC->Proxy()->SyncGetCurrentTransportActions(aInstanceID, buf_aActions);
    *aActions = buf_aActions.Extract();
}

void CpProxyUpnpOrgAVTransport1BeginGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetCurrentTransportActions(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport1EndGetCurrentTransportActions(THandle aHandle, ZappHandleAsync aAsync, char** aActions)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aActions;
    *aActions = NULL;
    try {
        proxyC->Proxy()->EndGetCurrentTransportActions(*async, buf_aActions);
        *aActions = buf_aActions.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport1SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLastChangeChanged(functor);
}

void CpProxyUpnpOrgAVTransport1PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgAVTransport1C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->Proxy()->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

