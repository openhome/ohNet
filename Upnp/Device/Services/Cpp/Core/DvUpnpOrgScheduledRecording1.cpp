#include <Core/DvUpnpOrgScheduledRecording1.h>
#include <ZappTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgScheduledRecording1::SetPropertyLastChange(const Brx& aValue)
{
    SetPropertyString(*iPropertyLastChange, aValue);
}

void DvServiceUpnpOrgScheduledRecording1::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

DvServiceUpnpOrgScheduledRecording1::DvServiceUpnpOrgScheduledRecording1(DvDevice& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "ScheduledRecording", 1)
{
    Functor empty;
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"), empty);
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionGetSortCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    action->AddOutputParameter(new ParameterUint("SortLevelCap"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionGetPropertyList()
{
    Zapp::Action* action = new Zapp::Action("GetPropertyList");
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoGetPropertyList);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionGetAllowedValues()
{
    Zapp::Action* action = new Zapp::Action("GetAllowedValues");
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoGetAllowedValues);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionGetStateUpdateID()
{
    Zapp::Action* action = new Zapp::Action("GetStateUpdateID");
    action->AddOutputParameter(new ParameterUint("Id"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoGetStateUpdateID);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionBrowseRecordSchedules()
{
    Zapp::Action* action = new Zapp::Action("BrowseRecordSchedules");
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoBrowseRecordSchedules);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionBrowseRecordTasks()
{
    Zapp::Action* action = new Zapp::Action("BrowseRecordTasks");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoBrowseRecordTasks);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionCreateRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("CreateRecordSchedule");
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoCreateRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionDeleteRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("DeleteRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoDeleteRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionGetRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("GetRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoGetRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionEnableRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("EnableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoEnableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionDisableRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("DisableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoDisableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionDeleteRecordTask()
{
    Zapp::Action* action = new Zapp::Action("DeleteRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoDeleteRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionGetRecordTask()
{
    Zapp::Action* action = new Zapp::Action("GetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoGetRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionEnableRecordTask()
{
    Zapp::Action* action = new Zapp::Action("EnableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoEnableRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionDisableRecordTask()
{
    Zapp::Action* action = new Zapp::Action("DisableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoDisableRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionResetRecordTask()
{
    Zapp::Action* action = new Zapp::Action("ResetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoResetRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionGetRecordScheduleConflicts()
{
    Zapp::Action* action = new Zapp::Action("GetRecordScheduleConflicts");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("RecordScheduleConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoGetRecordScheduleConflicts);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::EnableActionGetRecordTaskConflicts()
{
    Zapp::Action* action = new Zapp::Action("GetRecordTaskConflicts");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddOutputParameter(new ParameterString("RecordTaskConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording1::DoGetRecordTaskConflicts);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording1::DoGetSortCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSortCaps(aInvocation, "SortCaps");
    InvocationResponseUint respSortLevelCap(aInvocation, "SortLevelCap");
    GetSortCapabilities(resp, aVersion, respSortCaps, respSortLevelCap);
}

void DvServiceUpnpOrgScheduledRecording1::DoGetPropertyList(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respPropertyList(aInvocation, "PropertyList");
    GetPropertyList(resp, aVersion, DataTypeID, respPropertyList);
}

void DvServiceUpnpOrgScheduledRecording1::DoGetAllowedValues(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respPropertyInfo(aInvocation, "PropertyInfo");
    GetAllowedValues(resp, aVersion, DataTypeID, Filter, respPropertyInfo);
}

void DvServiceUpnpOrgScheduledRecording1::DoGetStateUpdateID(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respId(aInvocation, "Id");
    GetStateUpdateID(resp, aVersion, respId);
}

void DvServiceUpnpOrgScheduledRecording1::DoBrowseRecordSchedules(IDvInvocation& aInvocation, TUint aVersion)
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
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    InvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    BrowseRecordSchedules(resp, aVersion, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvServiceUpnpOrgScheduledRecording1::DoBrowseRecordTasks(IDvInvocation& aInvocation, TUint aVersion)
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
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    InvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    BrowseRecordTasks(resp, aVersion, RecordScheduleID, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvServiceUpnpOrgScheduledRecording1::DoCreateRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Elements;
    aInvocation.InvocationReadString("Elements", Elements);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respRecordScheduleID(aInvocation, "RecordScheduleID");
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    CreateRecordSchedule(resp, aVersion, Elements, respRecordScheduleID, respResult, respUpdateID);
}

void DvServiceUpnpOrgScheduledRecording1::DoDeleteRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvServiceUpnpOrgScheduledRecording1::DoGetRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    GetRecordSchedule(resp, aVersion, RecordScheduleID, Filter, respResult, respUpdateID);
}

void DvServiceUpnpOrgScheduledRecording1::DoEnableRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    EnableRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvServiceUpnpOrgScheduledRecording1::DoDisableRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisableRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvServiceUpnpOrgScheduledRecording1::DoDeleteRecordTask(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteRecordTask(resp, aVersion, RecordTaskID);
}

void DvServiceUpnpOrgScheduledRecording1::DoGetRecordTask(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respResult(aInvocation, "Result");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    GetRecordTask(resp, aVersion, RecordTaskID, Filter, respResult, respUpdateID);
}

void DvServiceUpnpOrgScheduledRecording1::DoEnableRecordTask(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    EnableRecordTask(resp, aVersion, RecordTaskID);
}

void DvServiceUpnpOrgScheduledRecording1::DoDisableRecordTask(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisableRecordTask(resp, aVersion, RecordTaskID);
}

void DvServiceUpnpOrgScheduledRecording1::DoResetRecordTask(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ResetRecordTask(resp, aVersion, RecordTaskID);
}

void DvServiceUpnpOrgScheduledRecording1::DoGetRecordScheduleConflicts(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respRecordScheduleConflictIDList(aInvocation, "RecordScheduleConflictIDList");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    GetRecordScheduleConflicts(resp, aVersion, RecordScheduleID, respRecordScheduleConflictIDList, respUpdateID);
}

void DvServiceUpnpOrgScheduledRecording1::DoGetRecordTaskConflicts(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respRecordTaskConflictIDList(aInvocation, "RecordTaskConflictIDList");
    InvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    GetRecordTaskConflicts(resp, aVersion, RecordTaskID, respRecordTaskConflictIDList, respUpdateID);
}

void DvServiceUpnpOrgScheduledRecording1::GetSortCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSortCaps*/, IInvocationResponseUint& /*aSortLevelCap*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::GetPropertyList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aDataTypeID*/, IInvocationResponseString& /*aPropertyList*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::GetAllowedValues(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aDataTypeID*/, const Brx& /*aFilter*/, IInvocationResponseString& /*aPropertyInfo*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::GetStateUpdateID(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aId*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::BrowseRecordSchedules(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::BrowseRecordTasks(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::CreateRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aElements*/, IInvocationResponseString& /*aRecordScheduleID*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::DeleteRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::GetRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, const Brx& /*aFilter*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::EnableRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::DisableRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::DeleteRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::GetRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/, const Brx& /*aFilter*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::EnableRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::DisableRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::ResetRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::GetRecordScheduleConflicts(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, IInvocationResponseString& /*aRecordScheduleConflictIDList*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording1::GetRecordTaskConflicts(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/, IInvocationResponseString& /*aRecordTaskConflictIDList*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

