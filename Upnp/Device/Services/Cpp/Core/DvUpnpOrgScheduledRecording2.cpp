#include "DvUpnpOrgScheduledRecording2.h"
#include <OhNetTypes.h>
#include <Core/DvInvocationResponse.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome::Net;

TBool DvProviderUpnpOrgScheduledRecording2::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgScheduledRecording2::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

DvProviderUpnpOrgScheduledRecording2::DvProviderUpnpOrgScheduledRecording2(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ScheduledRecording", 2)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionGetSortCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    action->AddOutputParameter(new ParameterUint("SortLevelCap"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionGetPropertyList()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoGetPropertyList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionGetAllowedValues()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoGetAllowedValues);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionGetStateUpdateID()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateUpdateID");
    action->AddOutputParameter(new ParameterUint("Id"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoGetStateUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionBrowseRecordSchedules()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("BrowseRecordSchedules");
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoBrowseRecordSchedules);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionBrowseRecordTasks()
{
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoBrowseRecordTasks);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionCreateRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateRecordSchedule");
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoCreateRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionDeleteRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoDeleteRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionGetRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoGetRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionEnableRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoEnableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionDisableRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoDisableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionDeleteRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoDeleteRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionGetRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoGetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionEnableRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoEnableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionDisableRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoDisableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionResetRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ResetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoResetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionGetRecordScheduleConflicts()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordScheduleConflicts");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("RecordScheduleConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoGetRecordScheduleConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::EnableActionGetRecordTaskConflicts()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTaskConflicts");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddOutputParameter(new ParameterString("RecordTaskConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2::DoGetRecordTaskConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respSortCaps(aInvocation, "SortCaps");
    InvocationResponseUint respSortLevelCap(aInvocation, "SortLevelCap");
    GetSortCapabilities(resp, aVersion, respSortCaps, respSortLevelCap);
}

void DvProviderUpnpOrgScheduledRecording2::DoGetPropertyList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseString respPropertyList(aInvocation, "PropertyList");
    GetPropertyList(resp, aVersion, DataTypeID, respPropertyList);
}

void DvProviderUpnpOrgScheduledRecording2::DoGetAllowedValues(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording2::DoGetStateUpdateID(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    InvocationResponseUint respId(aInvocation, "Id");
    GetStateUpdateID(resp, aVersion, respId);
}

void DvProviderUpnpOrgScheduledRecording2::DoBrowseRecordSchedules(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording2::DoBrowseRecordTasks(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording2::DoCreateRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording2::DoDeleteRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvProviderUpnpOrgScheduledRecording2::DoGetRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording2::DoEnableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    EnableRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvProviderUpnpOrgScheduledRecording2::DoDisableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisableRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvProviderUpnpOrgScheduledRecording2::DoDeleteRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DeleteRecordTask(resp, aVersion, RecordTaskID);
}

void DvProviderUpnpOrgScheduledRecording2::DoGetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording2::DoEnableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    EnableRecordTask(resp, aVersion, RecordTaskID);
}

void DvProviderUpnpOrgScheduledRecording2::DoDisableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    DisableRecordTask(resp, aVersion, RecordTaskID);
}

void DvProviderUpnpOrgScheduledRecording2::DoResetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    InvocationResponse resp(aInvocation);
    ResetRecordTask(resp, aVersion, RecordTaskID);
}

void DvProviderUpnpOrgScheduledRecording2::DoGetRecordScheduleConflicts(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording2::DoGetRecordTaskConflicts(IDviInvocation& aInvocation, TUint aVersion)
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

void DvProviderUpnpOrgScheduledRecording2::GetSortCapabilities(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseString& /*aSortCaps*/, IInvocationResponseUint& /*aSortLevelCap*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::GetPropertyList(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aDataTypeID*/, IInvocationResponseString& /*aPropertyList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::GetAllowedValues(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aDataTypeID*/, const Brx& /*aFilter*/, IInvocationResponseString& /*aPropertyInfo*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::GetStateUpdateID(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IInvocationResponseUint& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::BrowseRecordSchedules(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::BrowseRecordTasks(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aNumberReturned*/, IInvocationResponseUint& /*aTotalMatches*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::CreateRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aElements*/, IInvocationResponseString& /*aRecordScheduleID*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::DeleteRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::GetRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, const Brx& /*aFilter*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::EnableRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::DisableRecordSchedule(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::DeleteRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::GetRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/, const Brx& /*aFilter*/, IInvocationResponseString& /*aResult*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::EnableRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::DisableRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::ResetRecordTask(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::GetRecordScheduleConflicts(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, IInvocationResponseString& /*aRecordScheduleConflictIDList*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2::GetRecordTaskConflicts(IInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/, IInvocationResponseString& /*aRecordTaskConflictIDList*/, IInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

