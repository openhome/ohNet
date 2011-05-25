#include "DvUpnpOrgScheduledRecording2.h"
#include <OhNetTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <DvProvider.h>
#include <C/OhNet.h>
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

class DvProviderUpnpOrgScheduledRecording2C : public DvProvider
{
public:
    DvProviderUpnpOrgScheduledRecording2C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
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
    void DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetPropertyList(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetAllowedValues(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStateUpdateID(IDviInvocation& aInvocation, TUint aVersion);
    void DoBrowseRecordSchedules(IDviInvocation& aInvocation, TUint aVersion);
    void DoBrowseRecordTasks(IDviInvocation& aInvocation, TUint aVersion);
    void DoCreateRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoEnableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoEnableRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoDisableRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoResetRecordTask(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRecordScheduleConflicts(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRecordTaskConflicts(IDviInvocation& aInvocation, TUint aVersion);
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
    PropertyString* iPropertyLastChange;
};

DvProviderUpnpOrgScheduledRecording2C::DvProviderUpnpOrgScheduledRecording2C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "ScheduledRecording", 2)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

TBool DvProviderUpnpOrgScheduledRecording2C::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgScheduledRecording2C::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetSortCapabilities(CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    action->AddOutputParameter(new ParameterUint("SortLevelCap"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetPropertyList(CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr)
{
    iCallbackGetPropertyList = aCallback;
    iPtrGetPropertyList = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetPropertyList");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordSchedule";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordTask";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordScheduleParts";
    action->AddInputParameter(new ParameterString("DataTypeID", allowedValues, 3));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterString("PropertyList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoGetPropertyList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetAllowedValues(CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr)
{
    iCallbackGetAllowedValues = aCallback;
    iPtrGetAllowedValues = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetAllowedValues");
    TChar** allowedValues;
    TUint index;
    index = 0;
    allowedValues = new TChar*[3];
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordSchedule";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordTask";
    allowedValues[index++] = (TChar*)"A_ARG_TYPE_RecordScheduleParts";
    action->AddInputParameter(new ParameterString("DataTypeID", allowedValues, 3));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("PropertyInfo"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoGetAllowedValues);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetStateUpdateID(CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr)
{
    iCallbackGetStateUpdateID = aCallback;
    iPtrGetStateUpdateID = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateUpdateID");
    action->AddOutputParameter(new ParameterUint("Id"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoGetStateUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionBrowseRecordSchedules(CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr)
{
    iCallbackBrowseRecordSchedules = aCallback;
    iPtrBrowseRecordSchedules = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BrowseRecordSchedules");
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoBrowseRecordSchedules);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionBrowseRecordTasks(CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr)
{
    iCallbackBrowseRecordTasks = aCallback;
    iPtrBrowseRecordTasks = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BrowseRecordTasks");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoBrowseRecordTasks);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionCreateRecordSchedule(CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr)
{
    iCallbackCreateRecordSchedule = aCallback;
    iPtrCreateRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateRecordSchedule");
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoCreateRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionDeleteRecordSchedule(CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr)
{
    iCallbackDeleteRecordSchedule = aCallback;
    iPtrDeleteRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoDeleteRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetRecordSchedule(CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr)
{
    iCallbackGetRecordSchedule = aCallback;
    iPtrGetRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoGetRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionEnableRecordSchedule(CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr)
{
    iCallbackEnableRecordSchedule = aCallback;
    iPtrEnableRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoEnableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionDisableRecordSchedule(CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr)
{
    iCallbackDisableRecordSchedule = aCallback;
    iPtrDisableRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoDisableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionDeleteRecordTask(CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr)
{
    iCallbackDeleteRecordTask = aCallback;
    iPtrDeleteRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoDeleteRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetRecordTask(CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr)
{
    iCallbackGetRecordTask = aCallback;
    iPtrGetRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoGetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionEnableRecordTask(CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr)
{
    iCallbackEnableRecordTask = aCallback;
    iPtrEnableRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoEnableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionDisableRecordTask(CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr)
{
    iCallbackDisableRecordTask = aCallback;
    iPtrDisableRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoDisableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionResetRecordTask(CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr)
{
    iCallbackResetRecordTask = aCallback;
    iPtrResetRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ResetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoResetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetRecordScheduleConflicts(CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr)
{
    iCallbackGetRecordScheduleConflicts = aCallback;
    iPtrGetRecordScheduleConflicts = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordScheduleConflicts");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("RecordScheduleConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoGetRecordScheduleConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::EnableActionGetRecordTaskConflicts(CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr)
{
    iCallbackGetRecordTaskConflicts = aCallback;
    iPtrGetRecordTaskConflicts = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTaskConflicts");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddOutputParameter(new ParameterString("RecordTaskConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2C::DoGetRecordTaskConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* SortCaps;
    uint32_t SortLevelCap;
    ASSERT(iCallbackGetSortCapabilities != NULL);
    if (0 != iCallbackGetSortCapabilities(iPtrGetSortCapabilities, aVersion, &SortCaps, &SortLevelCap)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respSortCaps(aInvocation, "SortCaps");
    InvocationResponseUint respSortLevelCap(aInvocation, "SortLevelCap");
    resp.Start();
    Brhz bufSortCaps((const TChar*)SortCaps);
    OhNetFreeExternal(SortCaps);
    respSortCaps.Write(bufSortCaps);
    respSortCaps.WriteFlush();
    respSortLevelCap.Write(SortLevelCap);
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetPropertyList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* PropertyList;
    ASSERT(iCallbackGetPropertyList != NULL);
    if (0 != iCallbackGetPropertyList(iPtrGetPropertyList, aVersion, (const char*)DataTypeID.Ptr(), &PropertyList)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respPropertyList(aInvocation, "PropertyList");
    resp.Start();
    Brhz bufPropertyList((const TChar*)PropertyList);
    OhNetFreeExternal(PropertyList);
    respPropertyList.Write(bufPropertyList);
    respPropertyList.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetAllowedValues(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* PropertyInfo;
    ASSERT(iCallbackGetAllowedValues != NULL);
    if (0 != iCallbackGetAllowedValues(iPtrGetAllowedValues, aVersion, (const char*)DataTypeID.Ptr(), (const char*)Filter.Ptr(), &PropertyInfo)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respPropertyInfo(aInvocation, "PropertyInfo");
    resp.Start();
    Brhz bufPropertyInfo((const TChar*)PropertyInfo);
    OhNetFreeExternal(PropertyInfo);
    respPropertyInfo.Write(bufPropertyInfo);
    respPropertyInfo.WriteFlush();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetStateUpdateID(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    uint32_t Id;
    ASSERT(iCallbackGetStateUpdateID != NULL);
    if (0 != iCallbackGetStateUpdateID(iPtrGetStateUpdateID, aVersion, &Id)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseUint respId(aInvocation, "Id");
    resp.Start();
    respId.Write(Id);
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoBrowseRecordSchedules(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    TUint StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    TUint RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", SortCriteria);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowseRecordSchedules != NULL);
    if (0 != iCallbackBrowseRecordSchedules(iPtrBrowseRecordSchedules, aVersion, (const char*)Filter.Ptr(), StartingIndex, RequestedCount, (const char*)SortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    InvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoBrowseRecordTasks(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    TUint StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    TUint RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", SortCriteria);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowseRecordTasks != NULL);
    if (0 != iCallbackBrowseRecordTasks(iPtrBrowseRecordTasks, aVersion, (const char*)RecordScheduleID.Ptr(), (const char*)Filter.Ptr(), StartingIndex, RequestedCount, (const char*)SortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    InvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoCreateRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Elements;
    aInvocation.InvocationReadString("Elements", Elements);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* RecordScheduleID;
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackCreateRecordSchedule != NULL);
    if (0 != iCallbackCreateRecordSchedule(iPtrCreateRecordSchedule, aVersion, (const char*)Elements.Ptr(), &RecordScheduleID, &Result, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respRecordScheduleID(aInvocation, "RecordScheduleID");
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufRecordScheduleID((const TChar*)RecordScheduleID);
    OhNetFreeExternal(RecordScheduleID);
    respRecordScheduleID.Write(bufRecordScheduleID);
    respRecordScheduleID.WriteFlush();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoDeleteRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDeleteRecordSchedule != NULL);
    if (0 != iCallbackDeleteRecordSchedule(iPtrDeleteRecordSchedule, aVersion, (const char*)RecordScheduleID.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordSchedule != NULL);
    if (0 != iCallbackGetRecordSchedule(iPtrGetRecordSchedule, aVersion, (const char*)RecordScheduleID.Ptr(), (const char*)Filter.Ptr(), &Result, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoEnableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackEnableRecordSchedule != NULL);
    if (0 != iCallbackEnableRecordSchedule(iPtrEnableRecordSchedule, aVersion, (const char*)RecordScheduleID.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoDisableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDisableRecordSchedule != NULL);
    if (0 != iCallbackDisableRecordSchedule(iPtrDisableRecordSchedule, aVersion, (const char*)RecordScheduleID.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoDeleteRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDeleteRecordTask != NULL);
    if (0 != iCallbackDeleteRecordTask(iPtrDeleteRecordTask, aVersion, (const char*)RecordTaskID.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordTask != NULL);
    if (0 != iCallbackGetRecordTask(iPtrGetRecordTask, aVersion, (const char*)RecordTaskID.Ptr(), (const char*)Filter.Ptr(), &Result, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoEnableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackEnableRecordTask != NULL);
    if (0 != iCallbackEnableRecordTask(iPtrEnableRecordTask, aVersion, (const char*)RecordTaskID.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoDisableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackDisableRecordTask != NULL);
    if (0 != iCallbackDisableRecordTask(iPtrDisableRecordTask, aVersion, (const char*)RecordTaskID.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoResetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ASSERT(iCallbackResetRecordTask != NULL);
    if (0 != iCallbackResetRecordTask(iPtrResetRecordTask, aVersion, (const char*)RecordTaskID.Ptr())) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    resp.Start();
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetRecordScheduleConflicts(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* RecordScheduleConflictIDList;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordScheduleConflicts != NULL);
    if (0 != iCallbackGetRecordScheduleConflicts(iPtrGetRecordScheduleConflicts, aVersion, (const char*)RecordScheduleID.Ptr(), &RecordScheduleConflictIDList, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respRecordScheduleConflictIDList(aInvocation, "RecordScheduleConflictIDList");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufRecordScheduleConflictIDList((const TChar*)RecordScheduleConflictIDList);
    OhNetFreeExternal(RecordScheduleConflictIDList);
    respRecordScheduleConflictIDList.Write(bufRecordScheduleConflictIDList);
    respRecordScheduleConflictIDList.WriteFlush();
    respUpdateID.Write(UpdateID);
    resp.End();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetRecordTaskConflicts(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    char* RecordTaskConflictIDList;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordTaskConflicts != NULL);
    if (0 != iCallbackGetRecordTaskConflicts(iPtrGetRecordTaskConflicts, aVersion, (const char*)RecordTaskID.Ptr(), &RecordTaskConflictIDList, &UpdateID)) {
        resp.Error(502, Brn("Action failed"));
        return;
    }
    InvocationResponseString respRecordTaskConflictIDList(aInvocation, "RecordTaskConflictIDList");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    resp.Start();
    Brhz bufRecordTaskConflictIDList((const TChar*)RecordTaskConflictIDList);
    OhNetFreeExternal(RecordTaskConflictIDList);
    respRecordTaskConflictIDList.Write(bufRecordTaskConflictIDList);
    respRecordTaskConflictIDList.WriteFlush();
    respUpdateID.Write(UpdateID);
    resp.End();
}



THandle DvProviderUpnpOrgScheduledRecording2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgScheduledRecording2C(aDevice);
}

void DvProviderUpnpOrgScheduledRecording2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(THandle aProvider, CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList(THandle aProvider, CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetPropertyList(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues(THandle aProvider, CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetAllowedValues(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(THandle aProvider, CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetStateUpdateID(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(THandle aProvider, CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionBrowseRecordSchedules(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(THandle aProvider, CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionBrowseRecordTasks(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(THandle aProvider, CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionCreateRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(THandle aProvider, CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionDeleteRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(THandle aProvider, CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(THandle aProvider, CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionEnableRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(THandle aProvider, CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionDisableRecordSchedule(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(THandle aProvider, CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionDeleteRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask(THandle aProvider, CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask(THandle aProvider, CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionEnableRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask(THandle aProvider, CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionDisableRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask(THandle aProvider, CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionResetRecordTask(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(THandle aProvider, CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetRecordScheduleConflicts(aCallback, aPtr);
}

void DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(THandle aProvider, CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetRecordTaskConflicts(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgScheduledRecording2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgScheduledRecording2GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

