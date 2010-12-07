#include <C/DvUpnpOrgScheduledRecording1.h>
#include <Core/DvUpnpOrgScheduledRecording1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgScheduledRecording1C : public DvProviderUpnpOrgScheduledRecording1
{
public:
    DvProviderUpnpOrgScheduledRecording1C(DvDevice& aDevice);
    void EnableActionGetSortCapabilities(CallbackScheduledRecording1GetSortCapabilities aCallback, void* aPtr);
    void EnableActionGetPropertyList(CallbackScheduledRecording1GetPropertyList aCallback, void* aPtr);
    void EnableActionGetAllowedValues(CallbackScheduledRecording1GetAllowedValues aCallback, void* aPtr);
    void EnableActionGetStateUpdateID(CallbackScheduledRecording1GetStateUpdateID aCallback, void* aPtr);
    void EnableActionBrowseRecordSchedules(CallbackScheduledRecording1BrowseRecordSchedules aCallback, void* aPtr);
    void EnableActionBrowseRecordTasks(CallbackScheduledRecording1BrowseRecordTasks aCallback, void* aPtr);
    void EnableActionCreateRecordSchedule(CallbackScheduledRecording1CreateRecordSchedule aCallback, void* aPtr);
    void EnableActionDeleteRecordSchedule(CallbackScheduledRecording1DeleteRecordSchedule aCallback, void* aPtr);
    void EnableActionGetRecordSchedule(CallbackScheduledRecording1GetRecordSchedule aCallback, void* aPtr);
    void EnableActionEnableRecordSchedule(CallbackScheduledRecording1EnableRecordSchedule aCallback, void* aPtr);
    void EnableActionDisableRecordSchedule(CallbackScheduledRecording1DisableRecordSchedule aCallback, void* aPtr);
    void EnableActionDeleteRecordTask(CallbackScheduledRecording1DeleteRecordTask aCallback, void* aPtr);
    void EnableActionGetRecordTask(CallbackScheduledRecording1GetRecordTask aCallback, void* aPtr);
    void EnableActionEnableRecordTask(CallbackScheduledRecording1EnableRecordTask aCallback, void* aPtr);
    void EnableActionDisableRecordTask(CallbackScheduledRecording1DisableRecordTask aCallback, void* aPtr);
    void EnableActionResetRecordTask(CallbackScheduledRecording1ResetRecordTask aCallback, void* aPtr);
    void EnableActionGetRecordScheduleConflicts(CallbackScheduledRecording1GetRecordScheduleConflicts aCallback, void* aPtr);
    void EnableActionGetRecordTaskConflicts(CallbackScheduledRecording1GetRecordTaskConflicts aCallback, void* aPtr);
private:
    void GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps, IInvocationResponseUint& aSortLevelCap);
    void GetPropertyList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aDataTypeID, IInvocationResponseString& aPropertyList);
    void GetAllowedValues(IInvocationResponse& aResponse, TUint aVersion, const Brx& aDataTypeID, const Brx& aFilter, IInvocationResponseString& aPropertyInfo);
    void GetStateUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId);
    void BrowseRecordSchedules(IInvocationResponse& aResponse, TUint aVersion, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    void BrowseRecordTasks(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    void CreateRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aElements, IInvocationResponseString& aRecordScheduleID, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID);
    void DeleteRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID);
    void GetRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, const Brx& aFilter, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID);
    void EnableRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID);
    void DisableRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID);
    void DeleteRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID);
    void GetRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID, const Brx& aFilter, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID);
    void EnableRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID);
    void DisableRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID);
    void ResetRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID);
    void GetRecordScheduleConflicts(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, IInvocationResponseString& aRecordScheduleConflictIDList, IInvocationResponseUint& aUpdateID);
    void GetRecordTaskConflicts(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID, IInvocationResponseString& aRecordTaskConflictIDList, IInvocationResponseUint& aUpdateID);
private:
    CallbackScheduledRecording1GetSortCapabilities iCallbackGetSortCapabilities;
    void* iPtrGetSortCapabilities;
    CallbackScheduledRecording1GetPropertyList iCallbackGetPropertyList;
    void* iPtrGetPropertyList;
    CallbackScheduledRecording1GetAllowedValues iCallbackGetAllowedValues;
    void* iPtrGetAllowedValues;
    CallbackScheduledRecording1GetStateUpdateID iCallbackGetStateUpdateID;
    void* iPtrGetStateUpdateID;
    CallbackScheduledRecording1BrowseRecordSchedules iCallbackBrowseRecordSchedules;
    void* iPtrBrowseRecordSchedules;
    CallbackScheduledRecording1BrowseRecordTasks iCallbackBrowseRecordTasks;
    void* iPtrBrowseRecordTasks;
    CallbackScheduledRecording1CreateRecordSchedule iCallbackCreateRecordSchedule;
    void* iPtrCreateRecordSchedule;
    CallbackScheduledRecording1DeleteRecordSchedule iCallbackDeleteRecordSchedule;
    void* iPtrDeleteRecordSchedule;
    CallbackScheduledRecording1GetRecordSchedule iCallbackGetRecordSchedule;
    void* iPtrGetRecordSchedule;
    CallbackScheduledRecording1EnableRecordSchedule iCallbackEnableRecordSchedule;
    void* iPtrEnableRecordSchedule;
    CallbackScheduledRecording1DisableRecordSchedule iCallbackDisableRecordSchedule;
    void* iPtrDisableRecordSchedule;
    CallbackScheduledRecording1DeleteRecordTask iCallbackDeleteRecordTask;
    void* iPtrDeleteRecordTask;
    CallbackScheduledRecording1GetRecordTask iCallbackGetRecordTask;
    void* iPtrGetRecordTask;
    CallbackScheduledRecording1EnableRecordTask iCallbackEnableRecordTask;
    void* iPtrEnableRecordTask;
    CallbackScheduledRecording1DisableRecordTask iCallbackDisableRecordTask;
    void* iPtrDisableRecordTask;
    CallbackScheduledRecording1ResetRecordTask iCallbackResetRecordTask;
    void* iPtrResetRecordTask;
    CallbackScheduledRecording1GetRecordScheduleConflicts iCallbackGetRecordScheduleConflicts;
    void* iPtrGetRecordScheduleConflicts;
    CallbackScheduledRecording1GetRecordTaskConflicts iCallbackGetRecordTaskConflicts;
    void* iPtrGetRecordTaskConflicts;
};

DvProviderUpnpOrgScheduledRecording1C::DvProviderUpnpOrgScheduledRecording1C(DvDevice& aDevice)
    : DvProviderUpnpOrgScheduledRecording1(aDevice)
{
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetSortCapabilities(CallbackScheduledRecording1GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionGetSortCapabilities();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetPropertyList(CallbackScheduledRecording1GetPropertyList aCallback, void* aPtr)
{
    iCallbackGetPropertyList = aCallback;
    iPtrGetPropertyList = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionGetPropertyList();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetAllowedValues(CallbackScheduledRecording1GetAllowedValues aCallback, void* aPtr)
{
    iCallbackGetAllowedValues = aCallback;
    iPtrGetAllowedValues = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionGetAllowedValues();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetStateUpdateID(CallbackScheduledRecording1GetStateUpdateID aCallback, void* aPtr)
{
    iCallbackGetStateUpdateID = aCallback;
    iPtrGetStateUpdateID = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionGetStateUpdateID();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionBrowseRecordSchedules(CallbackScheduledRecording1BrowseRecordSchedules aCallback, void* aPtr)
{
    iCallbackBrowseRecordSchedules = aCallback;
    iPtrBrowseRecordSchedules = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionBrowseRecordSchedules();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionBrowseRecordTasks(CallbackScheduledRecording1BrowseRecordTasks aCallback, void* aPtr)
{
    iCallbackBrowseRecordTasks = aCallback;
    iPtrBrowseRecordTasks = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionBrowseRecordTasks();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionCreateRecordSchedule(CallbackScheduledRecording1CreateRecordSchedule aCallback, void* aPtr)
{
    iCallbackCreateRecordSchedule = aCallback;
    iPtrCreateRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionCreateRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionDeleteRecordSchedule(CallbackScheduledRecording1DeleteRecordSchedule aCallback, void* aPtr)
{
    iCallbackDeleteRecordSchedule = aCallback;
    iPtrDeleteRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionDeleteRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetRecordSchedule(CallbackScheduledRecording1GetRecordSchedule aCallback, void* aPtr)
{
    iCallbackGetRecordSchedule = aCallback;
    iPtrGetRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionGetRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionEnableRecordSchedule(CallbackScheduledRecording1EnableRecordSchedule aCallback, void* aPtr)
{
    iCallbackEnableRecordSchedule = aCallback;
    iPtrEnableRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionEnableRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionDisableRecordSchedule(CallbackScheduledRecording1DisableRecordSchedule aCallback, void* aPtr)
{
    iCallbackDisableRecordSchedule = aCallback;
    iPtrDisableRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionDisableRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionDeleteRecordTask(CallbackScheduledRecording1DeleteRecordTask aCallback, void* aPtr)
{
    iCallbackDeleteRecordTask = aCallback;
    iPtrDeleteRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionDeleteRecordTask();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetRecordTask(CallbackScheduledRecording1GetRecordTask aCallback, void* aPtr)
{
    iCallbackGetRecordTask = aCallback;
    iPtrGetRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionGetRecordTask();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionEnableRecordTask(CallbackScheduledRecording1EnableRecordTask aCallback, void* aPtr)
{
    iCallbackEnableRecordTask = aCallback;
    iPtrEnableRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionEnableRecordTask();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionDisableRecordTask(CallbackScheduledRecording1DisableRecordTask aCallback, void* aPtr)
{
    iCallbackDisableRecordTask = aCallback;
    iPtrDisableRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionDisableRecordTask();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionResetRecordTask(CallbackScheduledRecording1ResetRecordTask aCallback, void* aPtr)
{
    iCallbackResetRecordTask = aCallback;
    iPtrResetRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionResetRecordTask();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetRecordScheduleConflicts(CallbackScheduledRecording1GetRecordScheduleConflicts aCallback, void* aPtr)
{
    iCallbackGetRecordScheduleConflicts = aCallback;
    iPtrGetRecordScheduleConflicts = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionGetRecordScheduleConflicts();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetRecordTaskConflicts(CallbackScheduledRecording1GetRecordTaskConflicts aCallback, void* aPtr)
{
    iCallbackGetRecordTaskConflicts = aCallback;
    iPtrGetRecordTaskConflicts = aPtr;
    DvProviderUpnpOrgScheduledRecording1::EnableActionGetRecordTaskConflicts();
}

void DvProviderUpnpOrgScheduledRecording1C::GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps, IInvocationResponseUint& aSortLevelCap)
{
    char* SortCaps;
    uint32_t SortLevelCap;
    ASSERT(iCallbackGetSortCapabilities != NULL);
    if (0 != iCallbackGetSortCapabilities(iPtrGetSortCapabilities, aVersion, &SortCaps, &SortLevelCap)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufSortCaps((const TChar*)SortCaps);
    ZappFreeExternal(SortCaps);
    aSortCaps.Write(bufSortCaps);
    aSortCaps.WriteFlush();
    aSortLevelCap.Write(SortLevelCap);
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::GetPropertyList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aDataTypeID, IInvocationResponseString& aPropertyList)
{
    char* PropertyList;
    ASSERT(iCallbackGetPropertyList != NULL);
    if (0 != iCallbackGetPropertyList(iPtrGetPropertyList, aVersion, (const char*)aDataTypeID.Ptr(), &PropertyList)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufPropertyList((const TChar*)PropertyList);
    ZappFreeExternal(PropertyList);
    aPropertyList.Write(bufPropertyList);
    aPropertyList.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::GetAllowedValues(IInvocationResponse& aResponse, TUint aVersion, const Brx& aDataTypeID, const Brx& aFilter, IInvocationResponseString& aPropertyInfo)
{
    char* PropertyInfo;
    ASSERT(iCallbackGetAllowedValues != NULL);
    if (0 != iCallbackGetAllowedValues(iPtrGetAllowedValues, aVersion, (const char*)aDataTypeID.Ptr(), (const char*)aFilter.Ptr(), &PropertyInfo)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufPropertyInfo((const TChar*)PropertyInfo);
    ZappFreeExternal(PropertyInfo);
    aPropertyInfo.Write(bufPropertyInfo);
    aPropertyInfo.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::GetStateUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId)
{
    uint32_t Id;
    ASSERT(iCallbackGetStateUpdateID != NULL);
    if (0 != iCallbackGetStateUpdateID(iPtrGetStateUpdateID, aVersion, &Id)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aId.Write(Id);
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::BrowseRecordSchedules(IInvocationResponse& aResponse, TUint aVersion, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
{
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowseRecordSchedules != NULL);
    if (0 != iCallbackBrowseRecordSchedules(iPtrBrowseRecordSchedules, aVersion, (const char*)aFilter.Ptr(), aStartingIndex, aRequestedCount, (const char*)aSortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aNumberReturned.Write(NumberReturned);
    aTotalMatches.Write(TotalMatches);
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::BrowseRecordTasks(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
{
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowseRecordTasks != NULL);
    if (0 != iCallbackBrowseRecordTasks(iPtrBrowseRecordTasks, aVersion, (const char*)aRecordScheduleID.Ptr(), (const char*)aFilter.Ptr(), aStartingIndex, aRequestedCount, (const char*)aSortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aNumberReturned.Write(NumberReturned);
    aTotalMatches.Write(TotalMatches);
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::CreateRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aElements, IInvocationResponseString& aRecordScheduleID, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID)
{
    char* RecordScheduleID;
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackCreateRecordSchedule != NULL);
    if (0 != iCallbackCreateRecordSchedule(iPtrCreateRecordSchedule, aVersion, (const char*)aElements.Ptr(), &RecordScheduleID, &Result, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufRecordScheduleID((const TChar*)RecordScheduleID);
    ZappFreeExternal(RecordScheduleID);
    aRecordScheduleID.Write(bufRecordScheduleID);
    aRecordScheduleID.WriteFlush();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::DeleteRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID)
{
    ASSERT(iCallbackDeleteRecordSchedule != NULL);
    if (0 != iCallbackDeleteRecordSchedule(iPtrDeleteRecordSchedule, aVersion, (const char*)aRecordScheduleID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::GetRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, const Brx& aFilter, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID)
{
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordSchedule != NULL);
    if (0 != iCallbackGetRecordSchedule(iPtrGetRecordSchedule, aVersion, (const char*)aRecordScheduleID.Ptr(), (const char*)aFilter.Ptr(), &Result, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID)
{
    ASSERT(iCallbackEnableRecordSchedule != NULL);
    if (0 != iCallbackEnableRecordSchedule(iPtrEnableRecordSchedule, aVersion, (const char*)aRecordScheduleID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::DisableRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID)
{
    ASSERT(iCallbackDisableRecordSchedule != NULL);
    if (0 != iCallbackDisableRecordSchedule(iPtrDisableRecordSchedule, aVersion, (const char*)aRecordScheduleID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::DeleteRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID)
{
    ASSERT(iCallbackDeleteRecordTask != NULL);
    if (0 != iCallbackDeleteRecordTask(iPtrDeleteRecordTask, aVersion, (const char*)aRecordTaskID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::GetRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID, const Brx& aFilter, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID)
{
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordTask != NULL);
    if (0 != iCallbackGetRecordTask(iPtrGetRecordTask, aVersion, (const char*)aRecordTaskID.Ptr(), (const char*)aFilter.Ptr(), &Result, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::EnableRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID)
{
    ASSERT(iCallbackEnableRecordTask != NULL);
    if (0 != iCallbackEnableRecordTask(iPtrEnableRecordTask, aVersion, (const char*)aRecordTaskID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::DisableRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID)
{
    ASSERT(iCallbackDisableRecordTask != NULL);
    if (0 != iCallbackDisableRecordTask(iPtrDisableRecordTask, aVersion, (const char*)aRecordTaskID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::ResetRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID)
{
    ASSERT(iCallbackResetRecordTask != NULL);
    if (0 != iCallbackResetRecordTask(iPtrResetRecordTask, aVersion, (const char*)aRecordTaskID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::GetRecordScheduleConflicts(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, IInvocationResponseString& aRecordScheduleConflictIDList, IInvocationResponseUint& aUpdateID)
{
    char* RecordScheduleConflictIDList;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordScheduleConflicts != NULL);
    if (0 != iCallbackGetRecordScheduleConflicts(iPtrGetRecordScheduleConflicts, aVersion, (const char*)aRecordScheduleID.Ptr(), &RecordScheduleConflictIDList, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufRecordScheduleConflictIDList((const TChar*)RecordScheduleConflictIDList);
    ZappFreeExternal(RecordScheduleConflictIDList);
    aRecordScheduleConflictIDList.Write(bufRecordScheduleConflictIDList);
    aRecordScheduleConflictIDList.WriteFlush();
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording1C::GetRecordTaskConflicts(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID, IInvocationResponseString& aRecordTaskConflictIDList, IInvocationResponseUint& aUpdateID)
{
    char* RecordTaskConflictIDList;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordTaskConflicts != NULL);
    if (0 != iCallbackGetRecordTaskConflicts(iPtrGetRecordTaskConflicts, aVersion, (const char*)aRecordTaskID.Ptr(), &RecordTaskConflictIDList, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufRecordTaskConflictIDList((const TChar*)RecordTaskConflictIDList);
    ZappFreeExternal(RecordTaskConflictIDList);
    aRecordTaskConflictIDList.Write(bufRecordTaskConflictIDList);
    aRecordTaskConflictIDList.WriteFlush();
    aUpdateID.Write(UpdateID);
    aResponse.End();
}



THandle DvProviderUpnpOrgScheduledRecording1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgScheduledRecording1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgScheduledRecording1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionGetSortCapabilities(THandle aProvider, CallbackScheduledRecording1GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionGetPropertyList(THandle aProvider, CallbackScheduledRecording1GetPropertyList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionGetPropertyList(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionGetAllowedValues(THandle aProvider, CallbackScheduledRecording1GetAllowedValues aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionGetAllowedValues(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionGetStateUpdateID(THandle aProvider, CallbackScheduledRecording1GetStateUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionGetStateUpdateID(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionBrowseRecordSchedules(THandle aProvider, CallbackScheduledRecording1BrowseRecordSchedules aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionBrowseRecordSchedules(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionBrowseRecordTasks(THandle aProvider, CallbackScheduledRecording1BrowseRecordTasks aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionBrowseRecordTasks(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionCreateRecordSchedule(THandle aProvider, CallbackScheduledRecording1CreateRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionCreateRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionDeleteRecordSchedule(THandle aProvider, CallbackScheduledRecording1DeleteRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionDeleteRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordSchedule(THandle aProvider, CallbackScheduledRecording1GetRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionGetRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionEnableRecordSchedule(THandle aProvider, CallbackScheduledRecording1EnableRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionEnableRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionDisableRecordSchedule(THandle aProvider, CallbackScheduledRecording1DisableRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionDisableRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionDeleteRecordTask(THandle aProvider, CallbackScheduledRecording1DeleteRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionDeleteRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordTask(THandle aProvider, CallbackScheduledRecording1GetRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionGetRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionEnableRecordTask(THandle aProvider, CallbackScheduledRecording1EnableRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionEnableRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionDisableRecordTask(THandle aProvider, CallbackScheduledRecording1DisableRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionDisableRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionResetRecordTask(THandle aProvider, CallbackScheduledRecording1ResetRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionResetRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordScheduleConflicts(THandle aProvider, CallbackScheduledRecording1GetRecordScheduleConflicts aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionGetRecordScheduleConflicts(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording1EnableActionGetRecordTaskConflicts(THandle aProvider, CallbackScheduledRecording1GetRecordTaskConflicts aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->EnableActionGetRecordTaskConflicts(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgScheduledRecording1SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgScheduledRecording1GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording1C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

