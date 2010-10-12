#include <C/CpUpnpOrgScheduledRecording2.h>
#include <Core/CpUpnpOrgScheduledRecording2.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgScheduledRecording2C : public CpProxyC
{
public:
    CpProxyUpnpOrgScheduledRecording2C(CpDeviceC aDevice);
    CpProxyUpnpOrgScheduledRecording2* Proxy() { return static_cast<CpProxyUpnpOrgScheduledRecording2*>(iProxy); }
};

CpProxyUpnpOrgScheduledRecording2C::CpProxyUpnpOrgScheduledRecording2C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgScheduledRecording2(*iDevice);
}


THandle CpProxyUpnpOrgScheduledRecording2Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgScheduledRecording2C(aDevice);
}

void CpProxyUpnpOrgScheduledRecording2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgScheduledRecording2SyncGetSortCapabilities(THandle aHandle, char** aSortCaps, uint32_t* aSortLevelCap)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortCaps;
    proxyC->Proxy()->SyncGetSortCapabilities(buf_aSortCaps, *aSortLevelCap);
    *aSortCaps = buf_aSortCaps.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginGetSortCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSortCapabilities(functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndGetSortCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortCaps, uint32_t* aSortLevelCap)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncGetPropertyList(THandle aHandle, const char* aDataTypeID, char** aPropertyList)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aPropertyList;
    proxyC->Proxy()->SyncGetPropertyList(buf_aDataTypeID, buf_aPropertyList);
    *aPropertyList = buf_aPropertyList.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginGetPropertyList(THandle aHandle, const char* aDataTypeID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetPropertyList(buf_aDataTypeID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndGetPropertyList(THandle aHandle, ZappHandleAsync aAsync, char** aPropertyList)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, char** aPropertyInfo)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aFilter(aFilter);
    Brh buf_aPropertyInfo;
    proxyC->Proxy()->SyncGetAllowedValues(buf_aDataTypeID, buf_aFilter, buf_aPropertyInfo);
    *aPropertyInfo = buf_aPropertyInfo.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginGetAllowedValues(THandle aHandle, const char* aDataTypeID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aDataTypeID(aDataTypeID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetAllowedValues(buf_aDataTypeID, buf_aFilter, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndGetAllowedValues(THandle aHandle, ZappHandleAsync aAsync, char** aPropertyInfo)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncGetStateUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetStateUpdateID(*aId);
}

void CpProxyUpnpOrgScheduledRecording2BeginGetStateUpdateID(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetStateUpdateID(functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndGetStateUpdateID(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncBrowseRecordSchedules(buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordSchedules(THandle aHandle, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBrowseRecordSchedules(buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndBrowseRecordSchedules(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncBrowseRecordTasks(buf_aRecordScheduleID, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginBrowseRecordTasks(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBrowseRecordTasks(buf_aRecordScheduleID, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndBrowseRecordTasks(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncCreateRecordSchedule(THandle aHandle, const char* aElements, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aElements(aElements);
    Brh buf_aRecordScheduleID;
    Brh buf_aResult;
    proxyC->Proxy()->SyncCreateRecordSchedule(buf_aElements, buf_aRecordScheduleID, buf_aResult, *aUpdateID);
    *aRecordScheduleID = buf_aRecordScheduleID.Extract();
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginCreateRecordSchedule(THandle aHandle, const char* aElements, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateRecordSchedule(buf_aElements, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndCreateRecordSchedule(THandle aHandle, ZappHandleAsync aAsync, char** aRecordScheduleID, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    proxyC->Proxy()->SyncDeleteRecordSchedule(buf_aRecordScheduleID);
}

void CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDeleteRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndDeleteRecordSchedule(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    Brh buf_aResult;
    proxyC->Proxy()->SyncGetRecordSchedule(buf_aRecordScheduleID, buf_aFilter, buf_aResult, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginGetRecordSchedule(THandle aHandle, const char* aRecordScheduleID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRecordSchedule(buf_aRecordScheduleID, buf_aFilter, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndGetRecordSchedule(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    proxyC->Proxy()->SyncEnableRecordSchedule(buf_aRecordScheduleID);
}

void CpProxyUpnpOrgScheduledRecording2BeginEnableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginEnableRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndEnableRecordSchedule(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    proxyC->Proxy()->SyncDisableRecordSchedule(buf_aRecordScheduleID);
}

void CpProxyUpnpOrgScheduledRecording2BeginDisableRecordSchedule(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisableRecordSchedule(buf_aRecordScheduleID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndDisableRecordSchedule(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncDeleteRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    proxyC->Proxy()->SyncDeleteRecordTask(buf_aRecordTaskID);
}

void CpProxyUpnpOrgScheduledRecording2BeginDeleteRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDeleteRecordTask(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndDeleteRecordTask(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, char** aResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aFilter(aFilter);
    Brh buf_aResult;
    proxyC->Proxy()->SyncGetRecordTask(buf_aRecordTaskID, buf_aFilter, buf_aResult, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginGetRecordTask(THandle aHandle, const char* aRecordTaskID, const char* aFilter, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aFilter(aFilter);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRecordTask(buf_aRecordTaskID, buf_aFilter, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndGetRecordTask(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncEnableRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    proxyC->Proxy()->SyncEnableRecordTask(buf_aRecordTaskID);
}

void CpProxyUpnpOrgScheduledRecording2BeginEnableRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginEnableRecordTask(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndEnableRecordTask(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncDisableRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    proxyC->Proxy()->SyncDisableRecordTask(buf_aRecordTaskID);
}

void CpProxyUpnpOrgScheduledRecording2BeginDisableRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDisableRecordTask(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndDisableRecordTask(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncResetRecordTask(THandle aHandle, const char* aRecordTaskID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    proxyC->Proxy()->SyncResetRecordTask(buf_aRecordTaskID);
}

void CpProxyUpnpOrgScheduledRecording2BeginResetRecordTask(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginResetRecordTask(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndResetRecordTask(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    Brh buf_aRecordScheduleConflictIDList;
    proxyC->Proxy()->SyncGetRecordScheduleConflicts(buf_aRecordScheduleID, buf_aRecordScheduleConflictIDList, *aUpdateID);
    *aRecordScheduleConflictIDList = buf_aRecordScheduleConflictIDList.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginGetRecordScheduleConflicts(THandle aHandle, const char* aRecordScheduleID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordScheduleID(aRecordScheduleID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRecordScheduleConflicts(buf_aRecordScheduleID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndGetRecordScheduleConflicts(THandle aHandle, ZappHandleAsync aAsync, char** aRecordScheduleConflictIDList, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SyncGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, char** aRecordTaskConflictIDList, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    Brh buf_aRecordTaskConflictIDList;
    proxyC->Proxy()->SyncGetRecordTaskConflicts(buf_aRecordTaskID, buf_aRecordTaskConflictIDList, *aUpdateID);
    *aRecordTaskConflictIDList = buf_aRecordTaskConflictIDList.Extract();
}

void CpProxyUpnpOrgScheduledRecording2BeginGetRecordTaskConflicts(THandle aHandle, const char* aRecordTaskID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aRecordTaskID(aRecordTaskID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetRecordTaskConflicts(buf_aRecordTaskID, functor);
}

int32_t CpProxyUpnpOrgScheduledRecording2EndGetRecordTaskConflicts(THandle aHandle, ZappHandleAsync aAsync, char** aRecordTaskConflictIDList, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
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

void CpProxyUpnpOrgScheduledRecording2SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLastChangeChanged(functor);
}

void CpProxyUpnpOrgScheduledRecording2PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgScheduledRecording2C* proxyC = reinterpret_cast<CpProxyUpnpOrgScheduledRecording2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->Proxy()->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

