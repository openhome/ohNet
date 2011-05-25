#include "DvUpnpOrgScheduledRecording1.h"
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

class DvProviderUpnpOrgScheduledRecording1C : public DvProvider
{
public:
    DvProviderUpnpOrgScheduledRecording1C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
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
    PropertyString* iPropertyLastChange;
};

DvProviderUpnpOrgScheduledRecording1C::DvProviderUpnpOrgScheduledRecording1C(DvDeviceC aDevice)
    : DvProvider(DviDeviceC::DeviceFromHandle(aDevice)->Device(), "upnp.org", "ScheduledRecording", 1)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

TBool DvProviderUpnpOrgScheduledRecording1C::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgScheduledRecording1C::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetSortCapabilities(CallbackScheduledRecording1GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    action->AddOutputParameter(new ParameterUint("SortLevelCap"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetPropertyList(CallbackScheduledRecording1GetPropertyList aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoGetPropertyList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetAllowedValues(CallbackScheduledRecording1GetAllowedValues aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoGetAllowedValues);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetStateUpdateID(CallbackScheduledRecording1GetStateUpdateID aCallback, void* aPtr)
{
    iCallbackGetStateUpdateID = aCallback;
    iPtrGetStateUpdateID = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateUpdateID");
    action->AddOutputParameter(new ParameterUint("Id"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoGetStateUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionBrowseRecordSchedules(CallbackScheduledRecording1BrowseRecordSchedules aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoBrowseRecordSchedules);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionBrowseRecordTasks(CallbackScheduledRecording1BrowseRecordTasks aCallback, void* aPtr)
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoBrowseRecordTasks);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionCreateRecordSchedule(CallbackScheduledRecording1CreateRecordSchedule aCallback, void* aPtr)
{
    iCallbackCreateRecordSchedule = aCallback;
    iPtrCreateRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateRecordSchedule");
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoCreateRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionDeleteRecordSchedule(CallbackScheduledRecording1DeleteRecordSchedule aCallback, void* aPtr)
{
    iCallbackDeleteRecordSchedule = aCallback;
    iPtrDeleteRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoDeleteRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetRecordSchedule(CallbackScheduledRecording1GetRecordSchedule aCallback, void* aPtr)
{
    iCallbackGetRecordSchedule = aCallback;
    iPtrGetRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoGetRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionEnableRecordSchedule(CallbackScheduledRecording1EnableRecordSchedule aCallback, void* aPtr)
{
    iCallbackEnableRecordSchedule = aCallback;
    iPtrEnableRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoEnableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionDisableRecordSchedule(CallbackScheduledRecording1DisableRecordSchedule aCallback, void* aPtr)
{
    iCallbackDisableRecordSchedule = aCallback;
    iPtrDisableRecordSchedule = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoDisableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionDeleteRecordTask(CallbackScheduledRecording1DeleteRecordTask aCallback, void* aPtr)
{
    iCallbackDeleteRecordTask = aCallback;
    iPtrDeleteRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoDeleteRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetRecordTask(CallbackScheduledRecording1GetRecordTask aCallback, void* aPtr)
{
    iCallbackGetRecordTask = aCallback;
    iPtrGetRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoGetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionEnableRecordTask(CallbackScheduledRecording1EnableRecordTask aCallback, void* aPtr)
{
    iCallbackEnableRecordTask = aCallback;
    iPtrEnableRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoEnableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionDisableRecordTask(CallbackScheduledRecording1DisableRecordTask aCallback, void* aPtr)
{
    iCallbackDisableRecordTask = aCallback;
    iPtrDisableRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoDisableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionResetRecordTask(CallbackScheduledRecording1ResetRecordTask aCallback, void* aPtr)
{
    iCallbackResetRecordTask = aCallback;
    iPtrResetRecordTask = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ResetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoResetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetRecordScheduleConflicts(CallbackScheduledRecording1GetRecordScheduleConflicts aCallback, void* aPtr)
{
    iCallbackGetRecordScheduleConflicts = aCallback;
    iPtrGetRecordScheduleConflicts = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordScheduleConflicts");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("RecordScheduleConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoGetRecordScheduleConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::EnableActionGetRecordTaskConflicts(CallbackScheduledRecording1GetRecordTaskConflicts aCallback, void* aPtr)
{
    iCallbackGetRecordTaskConflicts = aCallback;
    iPtrGetRecordTaskConflicts = aPtr;
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTaskConflicts");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddOutputParameter(new ParameterString("RecordTaskConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1C::DoGetRecordTaskConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1C::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoGetPropertyList(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoGetAllowedValues(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoGetStateUpdateID(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoBrowseRecordSchedules(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoBrowseRecordTasks(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoCreateRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoDeleteRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoGetRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoEnableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoDisableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoDeleteRecordTask(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoGetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoEnableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoDisableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoResetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoGetRecordScheduleConflicts(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording1C::DoGetRecordTaskConflicts(IDviInvocation& aInvocation, TUint aVersion)
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



THandle DvProviderUpnpOrgScheduledRecording1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgScheduledRecording1C(aDevice);
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

