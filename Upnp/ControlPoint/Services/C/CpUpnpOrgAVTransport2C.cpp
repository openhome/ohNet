#include <C/CpUpnpOrgAVTransport2.h>
#include <Core/CpUpnpOrgAVTransport2.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgAVTransport2C : public CpProxyC
{
public:
    CpProxyUpnpOrgAVTransport2C(CpDeviceC aDevice);
    CpProxyUpnpOrgAVTransport2* Proxy() { return static_cast<CpProxyUpnpOrgAVTransport2*>(iProxy); }
};

CpProxyUpnpOrgAVTransport2C::CpProxyUpnpOrgAVTransport2C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgAVTransport2(*iDevice);
}


THandle CpProxyUpnpOrgAVTransport2Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgAVTransport2C(aDevice);
}

void CpProxyUpnpOrgAVTransport2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgAVTransport2SyncSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentURI(aCurrentURI);
    Brh buf_aCurrentURIMetaData(aCurrentURIMetaData);
    proxyC->Proxy()->SyncSetAVTransportURI(aInstanceID, buf_aCurrentURI, buf_aCurrentURIMetaData);
}

void CpProxyUpnpOrgAVTransport2BeginSetAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aCurrentURI, const char* aCurrentURIMetaData, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentURI(aCurrentURI);
    Brh buf_aCurrentURIMetaData(aCurrentURIMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetAVTransportURI(aInstanceID, buf_aCurrentURI, buf_aCurrentURIMetaData, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndSetAVTransportURI(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNextURI(aNextURI);
    Brh buf_aNextURIMetaData(aNextURIMetaData);
    proxyC->Proxy()->SyncSetNextAVTransportURI(aInstanceID, buf_aNextURI, buf_aNextURIMetaData);
}

void CpProxyUpnpOrgAVTransport2BeginSetNextAVTransportURI(THandle aHandle, uint32_t aInstanceID, const char* aNextURI, const char* aNextURIMetaData, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNextURI(aNextURI);
    Brh buf_aNextURIMetaData(aNextURIMetaData);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetNextAVTransportURI(aInstanceID, buf_aNextURI, buf_aNextURIMetaData, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndSetNextAVTransportURI(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncGetMediaInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2BeginGetMediaInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetMediaInfo(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetMediaInfo(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncGetMediaInfo_Ext(THandle aHandle, uint32_t aInstanceID, char** aCurrentType, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentType;
    Brh buf_aMediaDuration;
    Brh buf_aCurrentURI;
    Brh buf_aCurrentURIMetaData;
    Brh buf_aNextURI;
    Brh buf_aNextURIMetaData;
    Brh buf_aPlayMedium;
    Brh buf_aRecordMedium;
    Brh buf_aWriteStatus;
    proxyC->Proxy()->SyncGetMediaInfo_Ext(aInstanceID, buf_aCurrentType, *aNrTracks, buf_aMediaDuration, buf_aCurrentURI, buf_aCurrentURIMetaData, buf_aNextURI, buf_aNextURIMetaData, buf_aPlayMedium, buf_aRecordMedium, buf_aWriteStatus);
    *aCurrentType = buf_aCurrentType.Extract();
    *aMediaDuration = buf_aMediaDuration.Extract();
    *aCurrentURI = buf_aCurrentURI.Extract();
    *aCurrentURIMetaData = buf_aCurrentURIMetaData.Extract();
    *aNextURI = buf_aNextURI.Extract();
    *aNextURIMetaData = buf_aNextURIMetaData.Extract();
    *aPlayMedium = buf_aPlayMedium.Extract();
    *aRecordMedium = buf_aRecordMedium.Extract();
    *aWriteStatus = buf_aWriteStatus.Extract();
}

void CpProxyUpnpOrgAVTransport2BeginGetMediaInfo_Ext(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetMediaInfo_Ext(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetMediaInfo_Ext(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentType, uint32_t* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aCurrentType;
    *aCurrentType = NULL;
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
        proxyC->Proxy()->EndGetMediaInfo_Ext(*async, buf_aCurrentType, *aNrTracks, buf_aMediaDuration, buf_aCurrentURI, buf_aCurrentURIMetaData, buf_aNextURI, buf_aNextURIMetaData, buf_aPlayMedium, buf_aRecordMedium, buf_aWriteStatus);
        *aCurrentType = buf_aCurrentType.Extract();
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

void CpProxyUpnpOrgAVTransport2SyncGetTransportInfo(THandle aHandle, uint32_t aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentTransportState;
    Brh buf_aCurrentTransportStatus;
    Brh buf_aCurrentSpeed;
    proxyC->Proxy()->SyncGetTransportInfo(aInstanceID, buf_aCurrentTransportState, buf_aCurrentTransportStatus, buf_aCurrentSpeed);
    *aCurrentTransportState = buf_aCurrentTransportState.Extract();
    *aCurrentTransportStatus = buf_aCurrentTransportStatus.Extract();
    *aCurrentSpeed = buf_aCurrentSpeed.Extract();
}

void CpProxyUpnpOrgAVTransport2BeginGetTransportInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetTransportInfo(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetTransportInfo(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncGetPositionInfo(THandle aHandle, uint32_t aInstanceID, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2BeginGetPositionInfo(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetPositionInfo(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetPositionInfo(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int32_t* aRelCount, int32_t* aAbsCount)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPlayMedia;
    Brh buf_aRecMedia;
    Brh buf_aRecQualityModes;
    proxyC->Proxy()->SyncGetDeviceCapabilities(aInstanceID, buf_aPlayMedia, buf_aRecMedia, buf_aRecQualityModes);
    *aPlayMedia = buf_aPlayMedia.Extract();
    *aRecMedia = buf_aRecMedia.Extract();
    *aRecQualityModes = buf_aRecQualityModes.Extract();
}

void CpProxyUpnpOrgAVTransport2BeginGetDeviceCapabilities(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetDeviceCapabilities(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetDeviceCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncGetTransportSettings(THandle aHandle, uint32_t aInstanceID, char** aPlayMode, char** aRecQualityMode)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aPlayMode;
    Brh buf_aRecQualityMode;
    proxyC->Proxy()->SyncGetTransportSettings(aInstanceID, buf_aPlayMode, buf_aRecQualityMode);
    *aPlayMode = buf_aPlayMode.Extract();
    *aRecQualityMode = buf_aRecQualityMode.Extract();
}

void CpProxyUpnpOrgAVTransport2BeginGetTransportSettings(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetTransportSettings(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetTransportSettings(THandle aHandle, ZappHandleAsync aAsync, char** aPlayMode, char** aRecQualityMode)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncStop(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStop(aInstanceID);
}

void CpProxyUpnpOrgAVTransport2BeginStop(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStop(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndStop(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSpeed(aSpeed);
    proxyC->Proxy()->SyncPlay(aInstanceID, buf_aSpeed);
}

void CpProxyUpnpOrgAVTransport2BeginPlay(THandle aHandle, uint32_t aInstanceID, const char* aSpeed, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSpeed(aSpeed);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPlay(aInstanceID, buf_aSpeed, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndPlay(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncPause(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPause(aInstanceID);
}

void CpProxyUpnpOrgAVTransport2BeginPause(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPause(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndPause(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncRecord(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncRecord(aInstanceID);
}

void CpProxyUpnpOrgAVTransport2BeginRecord(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginRecord(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndRecord(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUnit(aUnit);
    Brh buf_aTarget(aTarget);
    proxyC->Proxy()->SyncSeek(aInstanceID, buf_aUnit, buf_aTarget);
}

void CpProxyUpnpOrgAVTransport2BeginSeek(THandle aHandle, uint32_t aInstanceID, const char* aUnit, const char* aTarget, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aUnit(aUnit);
    Brh buf_aTarget(aTarget);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSeek(aInstanceID, buf_aUnit, buf_aTarget, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndSeek(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncNext(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncNext(aInstanceID);
}

void CpProxyUpnpOrgAVTransport2BeginNext(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginNext(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndNext(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncPrevious(THandle aHandle, uint32_t aInstanceID)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncPrevious(aInstanceID);
}

void CpProxyUpnpOrgAVTransport2BeginPrevious(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginPrevious(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndPrevious(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewPlayMode(aNewPlayMode);
    proxyC->Proxy()->SyncSetPlayMode(aInstanceID, buf_aNewPlayMode);
}

void CpProxyUpnpOrgAVTransport2BeginSetPlayMode(THandle aHandle, uint32_t aInstanceID, const char* aNewPlayMode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewPlayMode(aNewPlayMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetPlayMode(aInstanceID, buf_aNewPlayMode, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndSetPlayMode(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewRecordQualityMode(aNewRecordQualityMode);
    proxyC->Proxy()->SyncSetRecordQualityMode(aInstanceID, buf_aNewRecordQualityMode);
}

void CpProxyUpnpOrgAVTransport2BeginSetRecordQualityMode(THandle aHandle, uint32_t aInstanceID, const char* aNewRecordQualityMode, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aNewRecordQualityMode(aNewRecordQualityMode);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetRecordQualityMode(aInstanceID, buf_aNewRecordQualityMode, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndSetRecordQualityMode(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, char** aActions)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aActions;
    proxyC->Proxy()->SyncGetCurrentTransportActions(aInstanceID, buf_aActions);
    *aActions = buf_aActions.Extract();
}

void CpProxyUpnpOrgAVTransport2BeginGetCurrentTransportActions(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetCurrentTransportActions(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetCurrentTransportActions(THandle aHandle, ZappHandleAsync aAsync, char** aActions)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
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

void CpProxyUpnpOrgAVTransport2SyncGetDRMState(THandle aHandle, uint32_t aInstanceID, char** aCurrentDRMState)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aCurrentDRMState;
    proxyC->Proxy()->SyncGetDRMState(aInstanceID, buf_aCurrentDRMState);
    *aCurrentDRMState = buf_aCurrentDRMState.Extract();
}

void CpProxyUpnpOrgAVTransport2BeginGetDRMState(THandle aHandle, uint32_t aInstanceID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetDRMState(aInstanceID, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetDRMState(THandle aHandle, ZappHandleAsync aAsync, char** aCurrentDRMState)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aCurrentDRMState;
    *aCurrentDRMState = NULL;
    try {
        proxyC->Proxy()->EndGetDRMState(*async, buf_aCurrentDRMState);
        *aCurrentDRMState = buf_aCurrentDRMState.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport2SyncGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, char** aStateVariableValuePairs)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aStateVariableList(aStateVariableList);
    Brh buf_aStateVariableValuePairs;
    proxyC->Proxy()->SyncGetStateVariables(aInstanceID, buf_aStateVariableList, buf_aStateVariableValuePairs);
    *aStateVariableValuePairs = buf_aStateVariableValuePairs.Extract();
}

void CpProxyUpnpOrgAVTransport2BeginGetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aStateVariableList, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aStateVariableList(aStateVariableList);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetStateVariables(aInstanceID, buf_aStateVariableList, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndGetStateVariables(THandle aHandle, ZappHandleAsync aAsync, char** aStateVariableValuePairs)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aStateVariableValuePairs;
    *aStateVariableValuePairs = NULL;
    try {
        proxyC->Proxy()->EndGetStateVariables(*async, buf_aStateVariableValuePairs);
        *aStateVariableValuePairs = buf_aStateVariableValuePairs.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport2SyncSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aAVTransportUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, char** aStateVariableList)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aAVTransportUDN(aAVTransportUDN);
    Brh buf_aServiceType(aServiceType);
    Brh buf_aServiceId(aServiceId);
    Brh buf_aStateVariableValuePairs(aStateVariableValuePairs);
    Brh buf_aStateVariableList;
    proxyC->Proxy()->SyncSetStateVariables(aInstanceID, buf_aAVTransportUDN, buf_aServiceType, buf_aServiceId, buf_aStateVariableValuePairs, buf_aStateVariableList);
    *aStateVariableList = buf_aStateVariableList.Extract();
}

void CpProxyUpnpOrgAVTransport2BeginSetStateVariables(THandle aHandle, uint32_t aInstanceID, const char* aAVTransportUDN, const char* aServiceType, const char* aServiceId, const char* aStateVariableValuePairs, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aAVTransportUDN(aAVTransportUDN);
    Brh buf_aServiceType(aServiceType);
    Brh buf_aServiceId(aServiceId);
    Brh buf_aStateVariableValuePairs(aStateVariableValuePairs);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSetStateVariables(aInstanceID, buf_aAVTransportUDN, buf_aServiceType, buf_aServiceId, buf_aStateVariableValuePairs, functor);
}

int32_t CpProxyUpnpOrgAVTransport2EndSetStateVariables(THandle aHandle, ZappHandleAsync aAsync, char** aStateVariableList)
{
    int32_t err = 0;
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aStateVariableList;
    *aStateVariableList = NULL;
    try {
        proxyC->Proxy()->EndSetStateVariables(*async, buf_aStateVariableList);
        *aStateVariableList = buf_aStateVariableList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgAVTransport2SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLastChangeChanged(functor);
}

void CpProxyUpnpOrgAVTransport2SetPropertyDRMStateChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyDRMStateChanged(functor);
}

void CpProxyUpnpOrgAVTransport2PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->Proxy()->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

void CpProxyUpnpOrgAVTransport2PropertyDRMState(THandle aHandle, char** aDRMState)
{
    CpProxyUpnpOrgAVTransport2C* proxyC = reinterpret_cast<CpProxyUpnpOrgAVTransport2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aDRMState;
    proxyC->Proxy()->PropertyDRMState(buf_aDRMState);
    *aDRMState = buf_aDRMState.Transfer();
}

