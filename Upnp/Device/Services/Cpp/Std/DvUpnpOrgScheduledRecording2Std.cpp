#include "DvUpnpOrgScheduledRecording2.h"
#include <OhNetTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDviInvocation.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgScheduledRecording2Cpp::SetPropertyLastChange(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetPropertyLastChange(std::string& aValue)
{
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgScheduledRecording2Cpp::DvProviderUpnpOrgScheduledRecording2Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ScheduledRecording", 2)
{
    
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"));
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

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSortCaps;
    uint32_t respSortLevelCap;
    GetSortCapabilities(aVersion, respSortCaps, respSortLevelCap);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterSortCaps(aInvocation, "SortCaps");
    Brn buf_SortCaps((const TByte*)respSortCaps.c_str(), (TUint)respSortCaps.length());
    respWriterSortCaps.Write(buf_SortCaps);
    aInvocation.InvocationWriteStringEnd("SortCaps");
    InvocationResponseUint respWriterSortLevelCap(aInvocation, "SortLevelCap");
    respWriterSortLevelCap.Write(respSortLevelCap);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetPropertyList(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_DataTypeID;
    aInvocation.InvocationReadString("DataTypeID", buf_DataTypeID);
    std::string DataTypeID((const char*)buf_DataTypeID.Ptr(), buf_DataTypeID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respPropertyList;
    GetPropertyList(aVersion, DataTypeID, respPropertyList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterPropertyList(aInvocation, "PropertyList");
    Brn buf_PropertyList((const TByte*)respPropertyList.c_str(), (TUint)respPropertyList.length());
    respWriterPropertyList.Write(buf_PropertyList);
    aInvocation.InvocationWriteStringEnd("PropertyList");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetAllowedValues(IDviInvocation& aInvocation, TUint aVersion)
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
    GetAllowedValues(aVersion, DataTypeID, Filter, respPropertyInfo);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterPropertyInfo(aInvocation, "PropertyInfo");
    Brn buf_PropertyInfo((const TByte*)respPropertyInfo.c_str(), (TUint)respPropertyInfo.length());
    respWriterPropertyInfo.Write(buf_PropertyInfo);
    aInvocation.InvocationWriteStringEnd("PropertyInfo");
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetStateUpdateID(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respId;
    GetStateUpdateID(aVersion, respId);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterId(aInvocation, "Id");
    respWriterId.Write(respId);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoBrowseRecordSchedules(IDviInvocation& aInvocation, TUint aVersion)
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
    BrowseRecordSchedules(aVersion, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterNumberReturned(aInvocation, "NumberReturned");
    respWriterNumberReturned.Write(respNumberReturned);
    InvocationResponseUint respWriterTotalMatches(aInvocation, "TotalMatches");
    respWriterTotalMatches.Write(respTotalMatches);
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoBrowseRecordTasks(IDviInvocation& aInvocation, TUint aVersion)
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
    BrowseRecordTasks(aVersion, RecordScheduleID, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterNumberReturned(aInvocation, "NumberReturned");
    respWriterNumberReturned.Write(respNumberReturned);
    InvocationResponseUint respWriterTotalMatches(aInvocation, "TotalMatches");
    respWriterTotalMatches.Write(respTotalMatches);
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoCreateRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_Elements;
    aInvocation.InvocationReadString("Elements", buf_Elements);
    std::string Elements((const char*)buf_Elements.Ptr(), buf_Elements.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respRecordScheduleID;
    std::string respResult;
    uint32_t respUpdateID;
    CreateRecordSchedule(aVersion, Elements, respRecordScheduleID, respResult, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterRecordScheduleID(aInvocation, "RecordScheduleID");
    Brn buf_RecordScheduleID((const TByte*)respRecordScheduleID.c_str(), (TUint)respRecordScheduleID.length());
    respWriterRecordScheduleID.Write(buf_RecordScheduleID);
    aInvocation.InvocationWriteStringEnd("RecordScheduleID");
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoDeleteRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    aInvocation.InvocationReadEnd();
    DeleteRecordSchedule(aVersion, RecordScheduleID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
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
    GetRecordSchedule(aVersion, RecordScheduleID, Filter, respResult, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoEnableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    aInvocation.InvocationReadEnd();
    EnableRecordSchedule(aVersion, RecordScheduleID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoDisableRecordSchedule(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    aInvocation.InvocationReadEnd();
    DisableRecordSchedule(aVersion, RecordScheduleID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoDeleteRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    DeleteRecordTask(aVersion, RecordTaskID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
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
    GetRecordTask(aVersion, RecordTaskID, Filter, respResult, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoEnableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    EnableRecordTask(aVersion, RecordTaskID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoDisableRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    DisableRecordTask(aVersion, RecordTaskID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoResetRecordTask(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    ResetRecordTask(aVersion, RecordTaskID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordScheduleConflicts(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordScheduleID;
    aInvocation.InvocationReadString("RecordScheduleID", buf_RecordScheduleID);
    std::string RecordScheduleID((const char*)buf_RecordScheduleID.Ptr(), buf_RecordScheduleID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respRecordScheduleConflictIDList;
    uint32_t respUpdateID;
    GetRecordScheduleConflicts(aVersion, RecordScheduleID, respRecordScheduleConflictIDList, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterRecordScheduleConflictIDList(aInvocation, "RecordScheduleConflictIDList");
    Brn buf_RecordScheduleConflictIDList((const TByte*)respRecordScheduleConflictIDList.c_str(), (TUint)respRecordScheduleConflictIDList.length());
    respWriterRecordScheduleConflictIDList.Write(buf_RecordScheduleConflictIDList);
    aInvocation.InvocationWriteStringEnd("RecordScheduleConflictIDList");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DoGetRecordTaskConflicts(IDviInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_RecordTaskID;
    aInvocation.InvocationReadString("RecordTaskID", buf_RecordTaskID);
    std::string RecordTaskID((const char*)buf_RecordTaskID.Ptr(), buf_RecordTaskID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respRecordTaskConflictIDList;
    uint32_t respUpdateID;
    GetRecordTaskConflicts(aVersion, RecordTaskID, respRecordTaskConflictIDList, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterRecordTaskConflictIDList(aInvocation, "RecordTaskConflictIDList");
    Brn buf_RecordTaskConflictIDList((const TByte*)respRecordTaskConflictIDList.c_str(), (TUint)respRecordTaskConflictIDList.length());
    respWriterRecordTaskConflictIDList.Write(buf_RecordTaskConflictIDList);
    aInvocation.InvocationWriteStringEnd("RecordTaskConflictIDList");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetSortCapabilities(uint32_t /*aVersion*/, std::string& /*aSortCaps*/, uint32_t& /*aSortLevelCap*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetPropertyList(uint32_t /*aVersion*/, const std::string& /*aDataTypeID*/, std::string& /*aPropertyList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetAllowedValues(uint32_t /*aVersion*/, const std::string& /*aDataTypeID*/, const std::string& /*aFilter*/, std::string& /*aPropertyInfo*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetStateUpdateID(uint32_t /*aVersion*/, uint32_t& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::BrowseRecordSchedules(uint32_t /*aVersion*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::BrowseRecordTasks(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::CreateRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aElements*/, std::string& /*aRecordScheduleID*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DeleteRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/, const std::string& /*aFilter*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DisableRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DeleteRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/, const std::string& /*aFilter*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::EnableRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::DisableRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::ResetRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetRecordScheduleConflicts(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/, std::string& /*aRecordScheduleConflictIDList*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgScheduledRecording2Cpp::GetRecordTaskConflicts(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/, std::string& /*aRecordTaskConflictIDList*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

