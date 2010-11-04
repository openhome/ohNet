#include <C/DvUpnpOrgScheduledRecording2.h>
#include <Core/DvUpnpOrgScheduledRecording2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgScheduledRecording2C : public DvProviderUpnpOrgScheduledRecording2
{
public:
    DvProviderUpnpOrgScheduledRecording2C(DvDevice& aDevice);
    void EnableActionGetSortCapabilities(CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr);
    void EnableActionGetPropertyList(CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr);
    void EnableActionGetAllowedValues(CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr);
    void EnableActionGetStateUpdateID(CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr);
    void EnableActionBrowseRecordSchedules(CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr);
    void EnableActionBrowseRecordTasks(CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr);
    void EnableActionCreateRecordSchedule(CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr);
    void EnableActionDeleteRecordSchedule(CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr);
    void EnableActionGetRecordSchedule(CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr);
    void EnableActionEnableRecordSchedule(CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr);
    void EnableActionDisableRecordSchedule(CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr);
    void EnableActionDeleteRecordTask(CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr);
    void EnableActionGetRecordTask(CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr);
    void EnableActionEnableRecordTask(CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr);
    void EnableActionDisableRecordTask(CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr);
    void EnableActionResetRecordTask(CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr);
    void EnableActionGetRecordScheduleConflicts(CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr);
    void EnableActionGetRecordTaskConflicts(CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr);
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
    CallbackScheduledRecording2GetSortCapabilities iCallbackGetSortCapabilities;
    void* iPtrGetSortCapabilities;
    CallbackScheduledRecording2GetPropertyList iCallbackGetPropertyList;
    void* iPtrGetPropertyList;
    CallbackScheduledRecording2GetAllowedValues iCallbackGetAllowedValues;
    void* iPtrGetAllowedValues;
    CallbackScheduledRecording2GetStateUpdateID iCallbackGetStateUpdateID;
    void* iPtrGetStateUpdateID;
    CallbackScheduledRecording2BrowseRecordSchedules iCallbackBrowseRecordSchedules;
    void* iPtrBrowseRecordSchedules;
    CallbackScheduledRecording2BrowseRecordTasks iCallbackBrowseRecordTasks;
    void* iPtrBrowseRecordTasks;
    CallbackScheduledRecording2CreateRecordSchedule iCallbackCreateRecordSchedule;
    void* iPtrCreateRecordSchedule;
    CallbackScheduledRecording2DeleteRecordSchedule iCallbackDeleteRecordSchedule;
    void* iPtrDeleteRecordSchedule;
    CallbackScheduledRecording2GetRecordSchedule iCallbackGetRecordSchedule;
    void* iPtrGetRecordSchedule;
    CallbackScheduledRecording2EnableRecordSchedule iCallbackEnableRecordSchedule;
    void* iPtrEnableRecordSchedule;
    CallbackScheduledRecording2DisableRecordSchedule iCallbackDisableRecordSchedule;
    void* iPtrDisableRecordSchedule;
    CallbackScheduledRecording2DeleteRecordTask iCallbackDeleteRecordTask;
    void* iPtrDeleteRecordTask;
    CallbackScheduledRecording2GetRecordTask iCallbackGetRecordTask;
    void* iPtrGetRecordTask;
    CallbackScheduledRecording2EnableRecordTask iCallbackEnableRecordTask;
    void* iPtrEnableRecordTask;
    CallbackScheduledRecording2DisableRecordTask iCallbackDisableRecordTask;
    void* iPtrDisableRecordTask;
    CallbackScheduledRecording2ResetRecordTask iCallbackResetRecordTask;
    void* iPtrResetRecordTask;
    CallbackScheduledRecording2GetRecordScheduleConflicts iCallbackGetRecordScheduleConflicts;
    void* iPtrGetRecordScheduleConflicts;
    CallbackScheduledRecording2GetRecordTaskConflicts iCallbackGetRecordTaskConflicts;
    void* iPtrGetRecordTaskConflicts;
};

DvProviderUpnpOrgScheduledRecording2C::DvProviderUpnpOrgScheduledRecording2C(DvDevice& aDevice)
    : DvProviderUpnpOrgScheduledRecording2(aDevice)
{
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetSortCapabilities(CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionGetSortCapabilities();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetPropertyList(CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr)
{
    iCallbackGetPropertyList = aCallback;
    iPtrGetPropertyList = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionGetPropertyList();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetAllowedValues(CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr)
{
    iCallbackGetAllowedValues = aCallback;
    iPtrGetAllowedValues = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionGetAllowedValues();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetStateUpdateID(CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr)
{
    iCallbackGetStateUpdateID = aCallback;
    iPtrGetStateUpdateID = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionGetStateUpdateID();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionBrowseRecordSchedules(CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr)
{
    iCallbackBrowseRecordSchedules = aCallback;
    iPtrBrowseRecordSchedules = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionBrowseRecordSchedules();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionBrowseRecordTasks(CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr)
{
    iCallbackBrowseRecordTasks = aCallback;
    iPtrBrowseRecordTasks = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionBrowseRecordTasks();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionCreateRecordSchedule(CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr)
{
    iCallbackCreateRecordSchedule = aCallback;
    iPtrCreateRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionCreateRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionDeleteRecordSchedule(CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr)
{
    iCallbackDeleteRecordSchedule = aCallback;
    iPtrDeleteRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionDeleteRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetRecordSchedule(CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr)
{
    iCallbackGetRecordSchedule = aCallback;
    iPtrGetRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionGetRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionEnableRecordSchedule(CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr)
{
    iCallbackEnableRecordSchedule = aCallback;
    iPtrEnableRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionEnableRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionDisableRecordSchedule(CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr)
{
    iCallbackDisableRecordSchedule = aCallback;
    iPtrDisableRecordSchedule = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionDisableRecordSchedule();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionDeleteRecordTask(CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr)
{
    iCallbackDeleteRecordTask = aCallback;
    iPtrDeleteRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionDeleteRecordTask();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetRecordTask(CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr)
{
    iCallbackGetRecordTask = aCallback;
    iPtrGetRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionGetRecordTask();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionEnableRecordTask(CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr)
{
    iCallbackEnableRecordTask = aCallback;
    iPtrEnableRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionEnableRecordTask();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionDisableRecordTask(CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr)
{
    iCallbackDisableRecordTask = aCallback;
    iPtrDisableRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionDisableRecordTask();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionResetRecordTask(CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr)
{
    iCallbackResetRecordTask = aCallback;
    iPtrResetRecordTask = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionResetRecordTask();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetRecordScheduleConflicts(CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr)
{
    iCallbackGetRecordScheduleConflicts = aCallback;
    iPtrGetRecordScheduleConflicts = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionGetRecordScheduleConflicts();
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetRecordTaskConflicts(CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr)
{
    iCallbackGetRecordTaskConflicts = aCallback;
    iPtrGetRecordTaskConflicts = aPtr;
    DvProviderUpnpOrgScheduledRecording2::EnableActionGetRecordTaskConflicts();
}

void DvProviderUpnpOrgScheduledRecording2C::GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps, IInvocationResponseUint& aSortLevelCap)
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

void DvProviderUpnpOrgScheduledRecording2C::GetPropertyList(IInvocationResponse& aResponse, TUint aVersion, const Brx& aDataTypeID, IInvocationResponseString& aPropertyList)
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

void DvProviderUpnpOrgScheduledRecording2C::GetAllowedValues(IInvocationResponse& aResponse, TUint aVersion, const Brx& aDataTypeID, const Brx& aFilter, IInvocationResponseString& aPropertyInfo)
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

void DvProviderUpnpOrgScheduledRecording2C::GetStateUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId)
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

void DvProviderUpnpOrgScheduledRecording2C::BrowseRecordSchedules(IInvocationResponse& aResponse, TUint aVersion, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgScheduledRecording2C::BrowseRecordTasks(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgScheduledRecording2C::CreateRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aElements, IInvocationResponseString& aRecordScheduleID, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgScheduledRecording2C::DeleteRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID)
{
    ASSERT(iCallbackDeleteRecordSchedule != NULL);
    if (0 != iCallbackDeleteRecordSchedule(iPtrDeleteRecordSchedule, aVersion, (const char*)aRecordScheduleID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording2C::GetRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, const Brx& aFilter, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgScheduledRecording2C::EnableRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID)
{
    ASSERT(iCallbackEnableRecordSchedule != NULL);
    if (0 != iCallbackEnableRecordSchedule(iPtrEnableRecordSchedule, aVersion, (const char*)aRecordScheduleID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DisableRecordSchedule(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID)
{
    ASSERT(iCallbackDisableRecordSchedule != NULL);
    if (0 != iCallbackDisableRecordSchedule(iPtrDisableRecordSchedule, aVersion, (const char*)aRecordScheduleID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DeleteRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID)
{
    ASSERT(iCallbackDeleteRecordTask != NULL);
    if (0 != iCallbackDeleteRecordTask(iPtrDeleteRecordTask, aVersion, (const char*)aRecordTaskID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording2C::GetRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID, const Brx& aFilter, IInvocationResponseString& aResult, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgScheduledRecording2C::EnableRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID)
{
    ASSERT(iCallbackEnableRecordTask != NULL);
    if (0 != iCallbackEnableRecordTask(iPtrEnableRecordTask, aVersion, (const char*)aRecordTaskID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DisableRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID)
{
    ASSERT(iCallbackDisableRecordTask != NULL);
    if (0 != iCallbackDisableRecordTask(iPtrDisableRecordTask, aVersion, (const char*)aRecordTaskID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording2C::ResetRecordTask(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID)
{
    ASSERT(iCallbackResetRecordTask != NULL);
    if (0 != iCallbackResetRecordTask(iPtrResetRecordTask, aVersion, (const char*)aRecordTaskID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgScheduledRecording2C::GetRecordScheduleConflicts(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordScheduleID, IInvocationResponseString& aRecordScheduleConflictIDList, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgScheduledRecording2C::GetRecordTaskConflicts(IInvocationResponse& aResponse, TUint aVersion, const Brx& aRecordTaskID, IInvocationResponseString& aRecordTaskConflictIDList, IInvocationResponseUint& aUpdateID)
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



THandle DvProviderUpnpOrgScheduledRecording2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgScheduledRecording2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgScheduledRecording2Destroy(THandle aService)
{
    delete reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(THandle aService, CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList(THandle aService, CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionGetPropertyList(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues(THandle aService, CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionGetAllowedValues(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(THandle aService, CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionGetStateUpdateID(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(THandle aService, CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionBrowseRecordSchedules(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(THandle aService, CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionBrowseRecordTasks(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(THandle aService, CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionCreateRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(THandle aService, CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionDeleteRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(THandle aService, CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionGetRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(THandle aService, CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionEnableRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(THandle aService, CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionDisableRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(THandle aService, CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionDeleteRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask(THandle aService, CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionGetRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask(THandle aService, CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionEnableRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask(THandle aService, CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionDisableRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask(THandle aService, CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionResetRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(THandle aService, CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionGetRecordScheduleConflicts(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(THandle aService, CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->EnableActionGetRecordTaskConflicts(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgScheduledRecording2SetPropertyLastChange(THandle aService, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgScheduledRecording2GetPropertyLastChange(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aService)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

