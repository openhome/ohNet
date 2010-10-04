#include <C/CpUpnpOrgScheduledRecording1.h>
#include <Core/CpUpnpOrgScheduledRecording1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgScheduledRecording1C : public CpProxyC
{
public:
    CpProxyUpnpOrgScheduledRecording1C(CpDeviceC aDevice);
    CpProxyUpnpOrgScheduledRecording1* Proxy() { return static_cast<CpProxyUpnpOrgScheduledRecording1*>(iProxy); }
};

CpProxyUpnpOrgScheduledRecording1C::CpProxyUpnpOrgScheduledRecording1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgScheduledRecording1(*iDevice);
}


THandle CpProxyUpnpOrgScheduledRecording1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgScheduledRecording1C(aDevice);
}

void CpProxyUpnpOrgScheduledRecording1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgScheduledRecording1SyncGetSortCapabilities(THandle aHandle, char** aSortCaps, uint32_t* aSortLevelCap)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortCaps;
    proxyC->Proxy()->SyncGetSortCapabilities(buf_aSortCaps, *aSortLevelCap);
    *aSortCaps = buf_aSortCaps.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginGetSortCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSortCapabilities(functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndGetSortCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortCaps, uint32_t* aSortLevelCap)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSortCaps;
    *aSortCaps = NULL;
    try {
        proxyC->Proxy()->EndGetSortCapabilities(*async, buf_aSortCaps, *aSortLevelCap);
        *aSortCaps = buf_aSortCaps.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncGetPropertyList(THandle aHandle, const char* aDataTypeID, char** aPropertyList)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aPropertyList;
    proxyC->Proxy()->SyncGetPropertyList(buf_aDataTypeID, buf_aPropertyList);
    *aPropertyList = buf_aPropertyList.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginGetPropertyList(THandle aHandle, const char* aDataTypeID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetPropertyList(buf_aDataTypeID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndGetPropertyList(THandle aHandle, ZappHandleAsync aAsync, char** aPropertyList)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPropertyList;
    *aPropertyList = NULL;
    try {
        proxyC->Proxy()->EndGetPropertyList(*async, buf_aPropertyList);
        *aPropertyList = buf_aPropertyList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aFilter(aFilter);
    Brh buf_aPropertyInfo;
    proxyC->Proxy()->SyncGetAllowedValues(buf_aDataTypeID, buf_aFilter, buf_aPropertyInfo);
    *aPropertyInfo = buf_aPropertyInfo.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetAllowedValues(buf_aDataTypeID, buf_aFilter, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndGetAllowedValues(THandle aHandle, ZappHandleAsync aAsync, char** aPropertyInfo)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aPropertyInfo;
    *aPropertyInfo = NULL;
    try {
        proxyC->Proxy()->EndGetAllowedValues(*async, buf_aPropertyInfo);
        *aPropertyInfo = buf_aPropertyInfo.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncGetStateUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetStateUpdateID(*aId);
}

void CpProxyUpnpOrgScheduledRecording1BeginGetStateUpdateID(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetStateUpdateID(functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndGetStateUpdateID(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetStateUpdateID(*async, *aId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncBrowseRecordSchedules(buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBrowseRecordSchedules(buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndBrowseRecordSchedules(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndBrowseRecordSchedules(*async, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncBrowseRecordTasks(buf_aRecordScheduleID, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBrowseRecordTasks(buf_aRecordScheduleID, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndBrowseRecordTasks(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndBrowseRecordTasks(*async, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncCreateRecordSchedule(THandle aHandle, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aElements(aElements);
    Brh buf_aRecordScheduleID;
    Brh buf_aResult;
    proxyC->Proxy()->SyncCreateRecordSchedule(buf_aElements, buf_aRecordScheduleID, buf_aResult, *aUpdateID);
    *aRecordScheduleID = buf_aRecordScheduleID.Extract();
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginCreateRecordSchedule(THandle aHandle, const char* aElements, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateRecordSchedule(buf_aElements, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndCreateRecordSchedule(THandle aHandle, ZappHandleAsync aAsync, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aRecordScheduleID;
    *aRecordScheduleID = NULL;
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndCreateRecordSchedule(*async, buf_aRecordScheduleID, buf_aResult, *aUpdateID);
        *aRecordScheduleID = buf_aRecordScheduleID.Extract();
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    proxyC->Proxy()->SyncDeleteRecordSchedule(buf_aRecordScheduleID);
}

void CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDeleteRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndDeleteRecordSchedule(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDeleteRecordSchedule(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aResult;
    proxyC->Proxy()->SyncGetRecordSchedule(buf_aRecordScheduleID, buf_aFilter, buf_aResult, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRecordSchedule(buf_aRecordScheduleID, buf_aFilter, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndGetRecordSchedule(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndGetRecordSchedule(*async, buf_aResult, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    proxyC->Proxy()->SyncEnableRecordSchedule(buf_aRecordScheduleID);
}

void CpProxyUpnpOrgScheduledRecording1BeginEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginEnableRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndEnableRecordSchedule(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndEnableRecordSchedule(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    proxyC->Proxy()->SyncDisableRecordSchedule(buf_aRecordScheduleID);
}

void CpProxyUpnpOrgScheduledRecording1BeginDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisableRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndDisableRecordSchedule(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDisableRecordSchedule(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncDeleteRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    proxyC->Proxy()->SyncDeleteRecordTask(buf_aRecordTaskID);
}

void CpProxyUpnpOrgScheduledRecording1BeginDeleteRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDeleteRecordTask(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndDeleteRecordTask(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDeleteRecordTask(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aFilter(aFilter);
    Brh buf_aResult;
    proxyC->Proxy()->SyncGetRecordTask(buf_aRecordTaskID, buf_aFilter, buf_aResult, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRecordTask(buf_aRecordTaskID, buf_aFilter, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndGetRecordTask(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndGetRecordTask(*async, buf_aResult, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncEnableRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    proxyC->Proxy()->SyncEnableRecordTask(buf_aRecordTaskID);
}

void CpProxyUpnpOrgScheduledRecording1BeginEnableRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginEnableRecordTask(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndEnableRecordTask(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndEnableRecordTask(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncDisableRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    proxyC->Proxy()->SyncDisableRecordTask(buf_aRecordTaskID);
}

void CpProxyUpnpOrgScheduledRecording1BeginDisableRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisableRecordTask(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndDisableRecordTask(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDisableRecordTask(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncResetRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    proxyC->Proxy()->SyncResetRecordTask(buf_aRecordTaskID);
}

void CpProxyUpnpOrgScheduledRecording1BeginResetRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginResetRecordTask(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndResetRecordTask(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndResetRecordTask(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aRecordScheduleConflictIDList;
    proxyC->Proxy()->SyncGetRecordScheduleConflicts(buf_aRecordScheduleID, buf_aRecordScheduleConflictIDList, *aUpdateID);
    *aRecordScheduleConflictIDList = buf_aRecordScheduleConflictIDList.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRecordScheduleConflicts(buf_aRecordScheduleID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndGetRecordScheduleConflicts(THandle aHandle, ZappHandleAsync aAsync, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aRecordScheduleConflictIDList;
    *aRecordScheduleConflictIDList = NULL;
    try {
        proxyC->Proxy()->EndGetRecordScheduleConflicts(*async, buf_aRecordScheduleConflictIDList, *aUpdateID);
        *aRecordScheduleConflictIDList = buf_aRecordScheduleConflictIDList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SyncGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aRecordTaskConflictIDList;
    proxyC->Proxy()->SyncGetRecordTaskConflicts(buf_aRecordTaskID, buf_aRecordTaskConflictIDList, *aUpdateID);
    *aRecordTaskConflictIDList = buf_aRecordTaskConflictIDList.Extract();
}

void CpProxyUpnpOrgScheduledRecording1BeginGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRecordTaskConflicts(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording1EndGetRecordTaskConflicts(THandle aHandle, ZappHandleAsync aAsync, char** aRecordTaskConflictIDList, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aRecordTaskConflictIDList;
    *aRecordTaskConflictIDList = NULL;
    try {
        proxyC->Proxy()->EndGetRecordTaskConflicts(*async, buf_aRecordTaskConflictIDList, *aUpdateID);
        *aRecordTaskConflictIDList = buf_aRecordTaskConflictIDList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgScheduledRecording1SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLastChangeChanged(functor);
}

void CpProxyUpnpOrgScheduledRecording1PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgScheduledRecording1C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->Proxy()->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

