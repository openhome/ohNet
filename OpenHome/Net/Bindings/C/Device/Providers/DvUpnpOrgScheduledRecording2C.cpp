#include "DvUpnpOrgScheduledRecording2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/C/DviDeviceC.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/C/OhNet.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/C/DvInvocation.h>
#include <OpenHome/Net/C/DvInvocationPrivate.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

class DvProviderUpnpOrgScheduledRecording2C : public DvProvider
{
public:
    DvProviderUpnpOrgScheduledRecording2C(DvDeviceC aDevice);
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
    void EnablePropertyLastChange();
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
    void DoGetSortCapabilities(IDviInvocation& aInvocation);
    void DoGetPropertyList(IDviInvocation& aInvocation);
    void DoGetAllowedValues(IDviInvocation& aInvocation);
    void DoGetStateUpdateID(IDviInvocation& aInvocation);
    void DoBrowseRecordSchedules(IDviInvocation& aInvocation);
    void DoBrowseRecordTasks(IDviInvocation& aInvocation);
    void DoCreateRecordSchedule(IDviInvocation& aInvocation);
    void DoDeleteRecordSchedule(IDviInvocation& aInvocation);
    void DoGetRecordSchedule(IDviInvocation& aInvocation);
    void DoEnableRecordSchedule(IDviInvocation& aInvocation);
    void DoDisableRecordSchedule(IDviInvocation& aInvocation);
    void DoDeleteRecordTask(IDviInvocation& aInvocation);
    void DoGetRecordTask(IDviInvocation& aInvocation);
    void DoEnableRecordTask(IDviInvocation& aInvocation);
    void DoDisableRecordTask(IDviInvocation& aInvocation);
    void DoResetRecordTask(IDviInvocation& aInvocation);
    void DoGetRecordScheduleConflicts(IDviInvocation& aInvocation);
    void DoGetRecordTaskConflicts(IDviInvocation& aInvocation);
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
    iPropertyLastChange = NULL;
}

TBool DvProviderUpnpOrgScheduledRecording2C::SetPropertyLastChange(const Brx& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgScheduledRecording2C::GetPropertyLastChange(Brhz& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    aValue.Set(iPropertyLastChange->Value());
}

void DvProviderUpnpOrgScheduledRecording2C::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
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

void DvProviderUpnpOrgScheduledRecording2C::DoGetSortCapabilities(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* SortCaps;
    uint32_t SortLevelCap;
    ASSERT(iCallbackGetSortCapabilities != NULL);
    if (0 != iCallbackGetSortCapabilities(iPtrGetSortCapabilities, invocationC, invocationCPtr, &SortCaps, &SortLevelCap)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respSortCaps(aInvocation, "SortCaps");
    DviInvocationResponseUint respSortLevelCap(aInvocation, "SortLevelCap");
    invocation.StartResponse();
    Brhz bufSortCaps((const TChar*)SortCaps);
    OhNetFreeExternal(SortCaps);
    respSortCaps.Write(bufSortCaps);
    respSortCaps.WriteFlush();
    respSortLevelCap.Write(SortLevelCap);
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetPropertyList(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* PropertyList;
    ASSERT(iCallbackGetPropertyList != NULL);
    if (0 != iCallbackGetPropertyList(iPtrGetPropertyList, invocationC, invocationCPtr, (const char*)DataTypeID.Ptr(), &PropertyList)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respPropertyList(aInvocation, "PropertyList");
    invocation.StartResponse();
    Brhz bufPropertyList((const TChar*)PropertyList);
    OhNetFreeExternal(PropertyList);
    respPropertyList.Write(bufPropertyList);
    respPropertyList.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetAllowedValues(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* PropertyInfo;
    ASSERT(iCallbackGetAllowedValues != NULL);
    if (0 != iCallbackGetAllowedValues(iPtrGetAllowedValues, invocationC, invocationCPtr, (const char*)DataTypeID.Ptr(), (const char*)Filter.Ptr(), &PropertyInfo)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respPropertyInfo(aInvocation, "PropertyInfo");
    invocation.StartResponse();
    Brhz bufPropertyInfo((const TChar*)PropertyInfo);
    OhNetFreeExternal(PropertyInfo);
    respPropertyInfo.Write(bufPropertyInfo);
    respPropertyInfo.WriteFlush();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetStateUpdateID(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    uint32_t Id;
    ASSERT(iCallbackGetStateUpdateID != NULL);
    if (0 != iCallbackGetStateUpdateID(iPtrGetStateUpdateID, invocationC, invocationCPtr, &Id)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseUint respId(aInvocation, "Id");
    invocation.StartResponse();
    respId.Write(Id);
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoBrowseRecordSchedules(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    TUint StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    TUint RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", SortCriteria);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowseRecordSchedules != NULL);
    if (0 != iCallbackBrowseRecordSchedules(iPtrBrowseRecordSchedules, invocationC, invocationCPtr, (const char*)Filter.Ptr(), StartingIndex, RequestedCount, (const char*)SortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoBrowseRecordTasks(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
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
    DviInvocation invocation(aInvocation);
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowseRecordTasks != NULL);
    if (0 != iCallbackBrowseRecordTasks(iPtrBrowseRecordTasks, invocationC, invocationCPtr, (const char*)RecordScheduleID.Ptr(), (const char*)Filter.Ptr(), StartingIndex, RequestedCount, (const char*)SortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respNumberReturned.Write(NumberReturned);
    respTotalMatches.Write(TotalMatches);
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoCreateRecordSchedule(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz Elements;
    aInvocation.InvocationReadString("Elements", Elements);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* RecordScheduleID;
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackCreateRecordSchedule != NULL);
    if (0 != iCallbackCreateRecordSchedule(iPtrCreateRecordSchedule, invocationC, invocationCPtr, (const char*)Elements.Ptr(), &RecordScheduleID, &Result, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respRecordScheduleID(aInvocation, "RecordScheduleID");
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufRecordScheduleID((const TChar*)RecordScheduleID);
    OhNetFreeExternal(RecordScheduleID);
    respRecordScheduleID.Write(bufRecordScheduleID);
    respRecordScheduleID.WriteFlush();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoDeleteRecordSchedule(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDeleteRecordSchedule != NULL);
    if (0 != iCallbackDeleteRecordSchedule(iPtrDeleteRecordSchedule, invocationC, invocationCPtr, (const char*)RecordScheduleID.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetRecordSchedule(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordSchedule != NULL);
    if (0 != iCallbackGetRecordSchedule(iPtrGetRecordSchedule, invocationC, invocationCPtr, (const char*)RecordScheduleID.Ptr(), (const char*)Filter.Ptr(), &Result, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoEnableRecordSchedule(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackEnableRecordSchedule != NULL);
    if (0 != iCallbackEnableRecordSchedule(iPtrEnableRecordSchedule, invocationC, invocationCPtr, (const char*)RecordScheduleID.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoDisableRecordSchedule(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDisableRecordSchedule != NULL);
    if (0 != iCallbackDisableRecordSchedule(iPtrDisableRecordSchedule, invocationC, invocationCPtr, (const char*)RecordScheduleID.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoDeleteRecordTask(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDeleteRecordTask != NULL);
    if (0 != iCallbackDeleteRecordTask(iPtrDeleteRecordTask, invocationC, invocationCPtr, (const char*)RecordTaskID.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetRecordTask(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* Result;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordTask != NULL);
    if (0 != iCallbackGetRecordTask(iPtrGetRecordTask, invocationC, invocationCPtr, (const char*)RecordTaskID.Ptr(), (const char*)Filter.Ptr(), &Result, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufResult((const TChar*)Result);
    OhNetFreeExternal(Result);
    respResult.Write(bufResult);
    respResult.WriteFlush();
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoEnableRecordTask(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackEnableRecordTask != NULL);
    if (0 != iCallbackEnableRecordTask(iPtrEnableRecordTask, invocationC, invocationCPtr, (const char*)RecordTaskID.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoDisableRecordTask(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackDisableRecordTask != NULL);
    if (0 != iCallbackDisableRecordTask(iPtrDisableRecordTask, invocationC, invocationCPtr, (const char*)RecordTaskID.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoResetRecordTask(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    ASSERT(iCallbackResetRecordTask != NULL);
    if (0 != iCallbackResetRecordTask(iPtrResetRecordTask, invocationC, invocationCPtr, (const char*)RecordTaskID.Ptr())) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    invocation.StartResponse();
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetRecordScheduleConflicts(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* RecordScheduleConflictIDList;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordScheduleConflicts != NULL);
    if (0 != iCallbackGetRecordScheduleConflicts(iPtrGetRecordScheduleConflicts, invocationC, invocationCPtr, (const char*)RecordScheduleID.Ptr(), &RecordScheduleConflictIDList, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respRecordScheduleConflictIDList(aInvocation, "RecordScheduleConflictIDList");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufRecordScheduleConflictIDList((const TChar*)RecordScheduleConflictIDList);
    OhNetFreeExternal(RecordScheduleConflictIDList);
    respRecordScheduleConflictIDList.Write(bufRecordScheduleConflictIDList);
    respRecordScheduleConflictIDList.WriteFlush();
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}

void DvProviderUpnpOrgScheduledRecording2C::DoGetRecordTaskConflicts(IDviInvocation& aInvocation)
{
    DvInvocationCPrivate invocationWrapper(aInvocation);
    IDvInvocationC* invocationC;
    void* invocationCPtr;
    invocationWrapper.GetInvocationC(&invocationC, &invocationCPtr);
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocation invocation(aInvocation);
    char* RecordTaskConflictIDList;
    uint32_t UpdateID;
    ASSERT(iCallbackGetRecordTaskConflicts != NULL);
    if (0 != iCallbackGetRecordTaskConflicts(iPtrGetRecordTaskConflicts, invocationC, invocationCPtr, (const char*)RecordTaskID.Ptr(), &RecordTaskConflictIDList, &UpdateID)) {
        invocation.Error(502, Brn("Action failed"));
        return;
    }
    DviInvocationResponseString respRecordTaskConflictIDList(aInvocation, "RecordTaskConflictIDList");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    invocation.StartResponse();
    Brhz bufRecordTaskConflictIDList((const TChar*)RecordTaskConflictIDList);
    OhNetFreeExternal(RecordTaskConflictIDList);
    respRecordTaskConflictIDList.Write(bufRecordTaskConflictIDList);
    respRecordTaskConflictIDList.WriteFlush();
    respUpdateID.Write(UpdateID);
    invocation.EndResponse();
}



THandle STDCALL DvProviderUpnpOrgScheduledRecording2Create(DvDeviceC aDevice)
{
    return new DvProviderUpnpOrgScheduledRecording2C(aDevice);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetSortCapabilities(THandle aProvider, CallbackScheduledRecording2GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetPropertyList(THandle aProvider, CallbackScheduledRecording2GetPropertyList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetPropertyList(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetAllowedValues(THandle aProvider, CallbackScheduledRecording2GetAllowedValues aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetAllowedValues(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetStateUpdateID(THandle aProvider, CallbackScheduledRecording2GetStateUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetStateUpdateID(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordSchedules(THandle aProvider, CallbackScheduledRecording2BrowseRecordSchedules aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionBrowseRecordSchedules(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionBrowseRecordTasks(THandle aProvider, CallbackScheduledRecording2BrowseRecordTasks aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionBrowseRecordTasks(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionCreateRecordSchedule(THandle aProvider, CallbackScheduledRecording2CreateRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionCreateRecordSchedule(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordSchedule(THandle aProvider, CallbackScheduledRecording2DeleteRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionDeleteRecordSchedule(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordSchedule(THandle aProvider, CallbackScheduledRecording2GetRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetRecordSchedule(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordSchedule(THandle aProvider, CallbackScheduledRecording2EnableRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionEnableRecordSchedule(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordSchedule(THandle aProvider, CallbackScheduledRecording2DisableRecordSchedule aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionDisableRecordSchedule(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionDeleteRecordTask(THandle aProvider, CallbackScheduledRecording2DeleteRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionDeleteRecordTask(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTask(THandle aProvider, CallbackScheduledRecording2GetRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetRecordTask(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionEnableRecordTask(THandle aProvider, CallbackScheduledRecording2EnableRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionEnableRecordTask(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionDisableRecordTask(THandle aProvider, CallbackScheduledRecording2DisableRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionDisableRecordTask(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionResetRecordTask(THandle aProvider, CallbackScheduledRecording2ResetRecordTask aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionResetRecordTask(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordScheduleConflicts(THandle aProvider, CallbackScheduledRecording2GetRecordScheduleConflicts aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetRecordScheduleConflicts(aCallback, aPtr);
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnableActionGetRecordTaskConflicts(THandle aProvider, CallbackScheduledRecording2GetRecordTaskConflicts aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnableActionGetRecordTaskConflicts(aCallback, aPtr);
}

int32_t STDCALL DvProviderUpnpOrgScheduledRecording2SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void STDCALL DvProviderUpnpOrgScheduledRecording2GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

void STDCALL DvProviderUpnpOrgScheduledRecording2EnablePropertyLastChange(THandle aProvider)
{
    reinterpret_cast<DvProviderUpnpOrgScheduledRecording2C*>(aProvider)->EnablePropertyLastChange();
}

