#include "DvUpnpOrgScheduledRecording2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgScheduledRecording2Cpp::SetPropertyLastChange(const std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetPropertyLastChange(std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgScheduledRecording2Cpp::DvProviderUpnpOrgScheduledRecording2Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ScheduledRecording", 2)
{
    iPropertyLastChange = NULL;
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionGetSortCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    action->AddOutputParameter(new ParameterUint("SortLevelCap"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionGetPropertyList()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoGetPropertyList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionGetAllowedValues()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoGetAllowedValues);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionGetStateUpdateID()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetStateUpdateID");
    action->AddOutputParameter(new ParameterUint("Id"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoGetStateUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionBrowseRecordSchedules()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoBrowseRecordSchedules);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionBrowseRecordTasks()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoBrowseRecordTasks);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionCreateRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateRecordSchedule");
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoCreateRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionDeleteRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoDeleteRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionGetRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionEnableRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoEnableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionDisableRecordSchedule()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoDisableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionDeleteRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoDeleteRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionGetRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionEnableRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("EnableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoEnableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionDisableRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DisableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoDisableRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionResetRecordTask()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ResetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoResetRecordTask);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionGetRecordScheduleConflicts()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordScheduleConflicts");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("RecordScheduleConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordScheduleConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableActionGetRecordTaskConflicts()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetRecordTaskConflicts");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddOutputParameter(new ParameterString("RecordTaskConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordTaskConflicts);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetSortCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSortCaps;
    uint32_t respSortLevelCap;
    DvInvocationStd invocation(aInvocation);
    GetSortCapabilities(invocation, respSortCaps, respSortLevelCap);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterSortCaps(aInvocation, "SortCaps");
    Brn buf_SortCaps((const TByte*)respSortCaps.c_str(), (TUint)respSortCaps.length());
    respWriterSortCaps.Write(buf_SortCaps);
    aInvocation.InvocationWriteStringEnd("SortCaps");
    DviInvocationResponseUint respWriterSortLevelCap(aInvocation, "SortLevelCap");
    respWriterSortLevelCap.Write(respSortLevelCap);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetPropertyList(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", buf_DataTypeID);
    std::string DataTypeID((const char*)buf_DataTypeID.Ptr(), buf_DataTypeID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respPropertyList;
    DvInvocationStd invocation(aInvocation);
    GetPropertyList(invocation, DataTypeID, respPropertyList);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterPropertyList(aInvocation, "PropertyList");
    Brn buf_PropertyList((const TByte*)respPropertyList.c_str(), (TUint)respPropertyList.length());
    respWriterPropertyList.Write(buf_PropertyList);
    aInvocation.InvocationWriteStringEnd("PropertyList");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetAllowedValues(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", buf_DataTypeID);
    std::string DataTypeID((const char*)buf_DataTypeID.Ptr(), buf_DataTypeID.Bytes());
    Brhz buf_Filter;
    aInvocation.InvocationReadString("Filter", buf_Filter);
    std::string Filter((const char*)buf_Filter.Ptr(), buf_Filter.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respPropertyInfo;
    DvInvocationStd invocation(aInvocation);
    GetAllowedValues(invocation, DataTypeID, Filter, respPropertyInfo);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterPropertyInfo(aInvocation, "PropertyInfo");
    Brn buf_PropertyInfo((const TByte*)respPropertyInfo.c_str(), (TUint)respPropertyInfo.length());
    respWriterPropertyInfo.Write(buf_PropertyInfo);
    aInvocation.InvocationWriteStringEnd("PropertyInfo");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetStateUpdateID(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respId;
    DvInvocationStd invocation(aInvocation);
    GetStateUpdateID(invocation, respId);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterId(aInvocation, "Id");
    respWriterId.Write(respId);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoBrowseRecordSchedules(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Filter;
    aInvocation.InvocationReadString("Filter", buf_Filter);
    std::string Filter((const char*)buf_Filter.Ptr(), buf_Filter.Bytes());
    uint32_t StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    uint32_t RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz buf_SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", buf_SortCriteria);
    std::string SortCriteria((const char*)buf_SortCriteria.Ptr(), buf_SortCriteria.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    uint32_t respNumberReturned;
    uint32_t respTotalMatches;
    uint32_t respUpdateID;
    DvInvocationStd invocation(aInvocation);
    BrowseRecordSchedules(invocation, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    DviInvocationResponseUint respWriterNumberReturned(aInvocation, "NumberReturned");
    respWriterNumberReturned.Write(respNumberReturned);
    DviInvocationResponseUint respWriterTotalMatches(aInvocation, "TotalMatches");
    respWriterTotalMatches.Write(respTotalMatches);
    DviInvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoBrowseRecordTasks(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    Brhz buf_Filter;
    aInvocation.InvocationReadString("Filter", buf_Filter);
    std::string Filter((const char*)buf_Filter.Ptr(), buf_Filter.Bytes());
    uint32_t StartingIndex = aInvocation.InvocationReadUint("StartingIndex");
    uint32_t RequestedCount = aInvocation.InvocationReadUint("RequestedCount");
    Brhz buf_SortCriteria;
    aInvocation.InvocationReadString("SortCriteria", buf_SortCriteria);
    std::string SortCriteria((const char*)buf_SortCriteria.Ptr(), buf_SortCriteria.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    uint32_t respNumberReturned;
    uint32_t respTotalMatches;
    uint32_t respUpdateID;
    DvInvocationStd invocation(aInvocation);
    BrowseRecordTasks(invocation, RecordScheduleID, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    DviInvocationResponseUint respWriterNumberReturned(aInvocation, "NumberReturned");
    respWriterNumberReturned.Write(respNumberReturned);
    DviInvocationResponseUint respWriterTotalMatches(aInvocation, "TotalMatches");
    respWriterTotalMatches.Write(respTotalMatches);
    DviInvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoCreateRecordSchedule(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Elements;
    aInvocation.InvocationReadString("Elements", buf_Elements);
    std::string Elements((const char*)buf_Elements.Ptr(), buf_Elements.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respRecordScheduleID;
    std::string respResult;
    uint32_t respUpdateID;
    DvInvocationStd invocation(aInvocation);
    CreateRecordSchedule(invocation, Elements, respRecordScheduleID, respResult, respUpdateID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterRecordScheduleID(aInvocation, "RecordScheduleID");
    Brn buf_RecordScheduleID((const TByte*)respRecordScheduleID.c_str(), (TUint)respRecordScheduleID.length());
    respWriterRecordScheduleID.Write(buf_RecordScheduleID);
    aInvocation.InvocationWriteStringEnd("RecordScheduleID");
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    DviInvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoDeleteRecordSchedule(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DeleteRecordSchedule(invocation, RecordScheduleID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordSchedule(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    Brhz buf_Filter;
    aInvocation.InvocationReadString("Filter", buf_Filter);
    std::string Filter((const char*)buf_Filter.Ptr(), buf_Filter.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    uint32_t respUpdateID;
    DvInvocationStd invocation(aInvocation);
    GetRecordSchedule(invocation, RecordScheduleID, Filter, respResult, respUpdateID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    DviInvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoEnableRecordSchedule(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    EnableRecordSchedule(invocation, RecordScheduleID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoDisableRecordSchedule(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DisableRecordSchedule(invocation, RecordScheduleID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoDeleteRecordTask(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DeleteRecordTask(invocation, RecordTaskID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordTask(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    Brhz buf_Filter;
    aInvocation.InvocationReadString("Filter", buf_Filter);
    std::string Filter((const char*)buf_Filter.Ptr(), buf_Filter.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respResult;
    uint32_t respUpdateID;
    DvInvocationStd invocation(aInvocation);
    GetRecordTask(invocation, RecordTaskID, Filter, respResult, respUpdateID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    DviInvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoEnableRecordTask(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    EnableRecordTask(invocation, RecordTaskID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoDisableRecordTask(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DisableRecordTask(invocation, RecordTaskID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoResetRecordTask(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    ResetRecordTask(invocation, RecordTaskID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordScheduleConflicts(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respRecordScheduleConflictIDList;
    uint32_t respUpdateID;
    DvInvocationStd invocation(aInvocation);
    GetRecordScheduleConflicts(invocation, RecordScheduleID, respRecordScheduleConflictIDList, respUpdateID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterRecordScheduleConflictIDList(aInvocation, "RecordScheduleConflictIDList");
    Brn buf_RecordScheduleConflictIDList((const TByte*)respRecordScheduleConflictIDList.c_str(), (TUint)respRecordScheduleConflictIDList.length());
    respWriterRecordScheduleConflictIDList.Write(buf_RecordScheduleConflictIDList);
    aInvocation.InvocationWriteStringEnd("RecordScheduleConflictIDList");
    DviInvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordTaskConflicts(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respRecordTaskConflictIDList;
    uint32_t respUpdateID;
    DvInvocationStd invocation(aInvocation);
    GetRecordTaskConflicts(invocation, RecordTaskID, respRecordTaskConflictIDList, respUpdateID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterRecordTaskConflictIDList(aInvocation, "RecordTaskConflictIDList");
    Brn buf_RecordTaskConflictIDList((const TByte*)respRecordTaskConflictIDList.c_str(), (TUint)respRecordTaskConflictIDList.length());
    respWriterRecordTaskConflictIDList.Write(buf_RecordTaskConflictIDList);
    aInvocation.InvocationWriteStringEnd("RecordTaskConflictIDList");
    DviInvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetSortCapabilities(IDvInvocationStd& /*aInvocation*/, std::string& /*aSortCaps*/, uint32_t& /*aSortLevelCap*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetPropertyList(IDvInvocationStd& /*aInvocation*/, const std::string& /*aDataTypeID*/, std::string& /*aPropertyList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetAllowedValues(IDvInvocationStd& /*aInvocation*/, const std::string& /*aDataTypeID*/, const std::string& /*aFilter*/, std::string& /*aPropertyInfo*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetStateUpdateID(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::BrowseRecordSchedules(IDvInvocationStd& /*aInvocation*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::BrowseRecordTasks(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordScheduleID*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::CreateRecordSchedule(IDvInvocationStd& /*aInvocation*/, const std::string& /*aElements*/, std::string& /*aRecordScheduleID*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DeleteRecordSchedule(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetRecordSchedule(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordScheduleID*/, const std::string& /*aFilter*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableRecordSchedule(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DisableRecordSchedule(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DeleteRecordTask(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetRecordTask(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordTaskID*/, const std::string& /*aFilter*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableRecordTask(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DisableRecordTask(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::ResetRecordTask(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetRecordScheduleConflicts(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordScheduleID*/, std::string& /*aRecordScheduleConflictIDList*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetRecordTaskConflicts(IDvInvocationStd& /*aInvocation*/, const std::string& /*aRecordTaskID*/, std::string& /*aRecordTaskConflictIDList*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

