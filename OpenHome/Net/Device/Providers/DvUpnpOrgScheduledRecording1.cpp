#include "DvUpnpOrgScheduledRecording1.h"
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

TBool DvProviderUpnpOrgScheduledRecording1::SetPropertyLastChange(const Brx& aValue)
{
    return SetPropertyString(*iPropertyLastChange, aValue);
}

void DvProviderUpnpOrgScheduledRecording1::GetPropertyLastChange(Brhz& aValue)
{
    aValue.Set(iPropertyLastChange->Value());
}

DvProviderUpnpOrgScheduledRecording1::DvProviderUpnpOrgScheduledRecording1(DvDevice& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ScheduledRecording", 1)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionGetSortCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    action->AddOutputParameter(new ParameterUint("SortLevelCap"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionGetPropertyList()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoGetPropertyList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionGetAllowedValues()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoGetAllowedValues);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionGetStateUpdateID()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateUpdateID");
    action->AddOutputParameter(new ParameterUint("Id"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoGetStateUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionBrowseRecordSchedules()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoBrowseRecordSchedules);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionBrowseRecordTasks()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoBrowseRecordTasks);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionCreateRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateRecordSchedule");
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoCreateRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionDeleteRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoDeleteRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionGetRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoGetRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionEnableRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoEnableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionDisableRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoDisableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionDeleteRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoDeleteRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionGetRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoGetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionEnableRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoEnableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionDisableRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoDisableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionResetRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ResetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoResetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionGetRecordScheduleConflicts()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordScheduleConflicts");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("RecordScheduleConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoGetRecordScheduleConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::EnableActionGetRecordTaskConflicts()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTaskConflicts");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddOutputParameter(new ParameterString("RecordTaskConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording1::DoGetRecordTaskConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording1::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respSortCaps(aInvocation, "SortCaps");
    DviInvocationResponseUint respSortLevelCap(aInvocation, "SortLevelCap");
    GetSortCapabilities(resp, aVersion, respSortCaps, respSortLevelCap);
}

void DvProviderUpnpOrgScheduledRecording1::DoGetPropertyList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respPropertyList(aInvocation, "PropertyList");
    GetPropertyList(resp, aVersion, DataTypeID, respPropertyList);
}

void DvProviderUpnpOrgScheduledRecording1::DoGetAllowedValues(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", DataTypeID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respPropertyInfo(aInvocation, "PropertyInfo");
    GetAllowedValues(resp, aVersion, DataTypeID, Filter, respPropertyInfo);
}

void DvProviderUpnpOrgScheduledRecording1::DoGetStateUpdateID(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseUint respId(aInvocation, "Id");
    GetStateUpdateID(resp, aVersion, respId);
}

void DvProviderUpnpOrgScheduledRecording1::DoBrowseRecordSchedules(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    TUint StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    TUint RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", SortCriteria);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    BrowseRecordSchedules(resp, aVersion, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvProviderUpnpOrgScheduledRecording1::DoBrowseRecordTasks(IDviInvocation& aInvocation, TUint aVersion)
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
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respNumberReturned(aInvocation, "NumberReturned");
    DviInvocationResponseUint respTotalMatches(aInvocation, "TotalMatches");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    BrowseRecordTasks(resp, aVersion, RecordScheduleID, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
}

void DvProviderUpnpOrgScheduledRecording1::DoCreateRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz Elements;
    aInvocation.InvocationReadString("Elements", Elements);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respRecordScheduleID(aInvocation, "RecordScheduleID");
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    CreateRecordSchedule(resp, aVersion, Elements, respRecordScheduleID, respResult, respUpdateID);
}

void DvProviderUpnpOrgScheduledRecording1::DoDeleteRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DeleteRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvProviderUpnpOrgScheduledRecording1::DoGetRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    GetRecordSchedule(resp, aVersion, RecordScheduleID, Filter, respResult, respUpdateID);
}

void DvProviderUpnpOrgScheduledRecording1::DoEnableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    EnableRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvProviderUpnpOrgScheduledRecording1::DoDisableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DisableRecordSchedule(resp, aVersion, RecordScheduleID);
}

void DvProviderUpnpOrgScheduledRecording1::DoDeleteRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DeleteRecordTask(resp, aVersion, RecordTaskID);
}

void DvProviderUpnpOrgScheduledRecording1::DoGetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    Brhz Filter;
    aInvocation.InvocationReadString("Filter", Filter);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respResult(aInvocation, "Result");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    GetRecordTask(resp, aVersion, RecordTaskID, Filter, respResult, respUpdateID);
}

void DvProviderUpnpOrgScheduledRecording1::DoEnableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    EnableRecordTask(resp, aVersion, RecordTaskID);
}

void DvProviderUpnpOrgScheduledRecording1::DoDisableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DisableRecordTask(resp, aVersion, RecordTaskID);
}

void DvProviderUpnpOrgScheduledRecording1::DoResetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    ResetRecordTask(resp, aVersion, RecordTaskID);
}

void DvProviderUpnpOrgScheduledRecording1::DoGetRecordScheduleConflicts(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", RecordScheduleID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respRecordScheduleConflictIDList(aInvocation, "RecordScheduleConflictIDList");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    GetRecordScheduleConflicts(resp, aVersion, RecordScheduleID, respRecordScheduleConflictIDList, respUpdateID);
}

void DvProviderUpnpOrgScheduledRecording1::DoGetRecordTaskConflicts(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", RecordTaskID);
    aInvocation.InvocationReadEnd();
    DviInvocationResponse resp(aInvocation);
    DviInvocationResponseString respRecordTaskConflictIDList(aInvocation, "RecordTaskConflictIDList");
    DviInvocationResponseUint respUpdateID(aInvocation, "UpdateID");
    GetRecordTaskConflicts(resp, aVersion, RecordTaskID, respRecordTaskConflictIDList, respUpdateID);
}

void DvProviderUpnpOrgScheduledRecording1::GetSortCapabilities(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseString& /*aSortCaps*/, IDvInvocationResponseUint& /*aSortLevelCap*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::GetPropertyList(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aDataTypeID*/, IDvInvocationResponseString& /*aPropertyList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::GetAllowedValues(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aDataTypeID*/, const Brx& /*aFilter*/, IDvInvocationResponseString& /*aPropertyInfo*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::GetStateUpdateID(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, IDvInvocationResponseUint& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::BrowseRecordSchedules(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aNumberReturned*/, IDvInvocationResponseUint& /*aTotalMatches*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::BrowseRecordTasks(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, const Brx& /*aFilter*/, TUint /*aStartingIndex*/, TUint /*aRequestedCount*/, const Brx& /*aSortCriteria*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aNumberReturned*/, IDvInvocationResponseUint& /*aTotalMatches*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::CreateRecordSchedule(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aElements*/, IDvInvocationResponseString& /*aRecordScheduleID*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::DeleteRecordSchedule(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::GetRecordSchedule(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, const Brx& /*aFilter*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::EnableRecordSchedule(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::DisableRecordSchedule(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::DeleteRecordTask(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::GetRecordTask(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/, const Brx& /*aFilter*/, IDvInvocationResponseString& /*aResult*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::EnableRecordTask(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::DisableRecordTask(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::ResetRecordTask(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::GetRecordScheduleConflicts(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordScheduleID*/, IDvInvocationResponseString& /*aRecordScheduleConflictIDList*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording1::GetRecordTaskConflicts(IDvInvocationResponse& /*aResponse*/, TUint /*aVersion*/, const Brx& /*aRecordTaskID*/, IDvInvocationResponseString& /*aRecordTaskConflictIDList*/, IDvInvocationResponseUint& /*aUpdateID*/)
{
    ASSERTS();
}

