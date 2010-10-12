#include <Std/DvUpnpOrgScheduledRecording2.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgScheduledRecording2Cpp::SetPropertyLastChange(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyLastChange, buf);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetPropertyLastChange(std::string& aValue)
{
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceUpnpOrgScheduledRecording2Cpp::DvServiceUpnpOrgScheduledRecording2Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "ScheduledRecording", 2)
{
    Functor empty;
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"), empty);
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionGetSortCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    action->AddOutputParameter(new ParameterUint("SortLevelCap"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionGetPropertyList()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoGetPropertyList);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionGetAllowedValues()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoGetAllowedValues);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionGetStateUpdateID()
{
    Zapp::Action* action = new Zapp::Action("GetStateUpdateID");
    action->AddOutputParameter(new ParameterUint("Id"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoGetStateUpdateID);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionBrowseRecordSchedules()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoBrowseRecordSchedules);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionBrowseRecordTasks()
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
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoBrowseRecordTasks);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionCreateRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("CreateRecordSchedule");
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoCreateRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionDeleteRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("DeleteRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoDeleteRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionGetRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("GetRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoGetRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionEnableRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("EnableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoEnableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionDisableRecordSchedule()
{
    Zapp::Action* action = new Zapp::Action("DisableRecordSchedule");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoDisableRecordSchedule);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionDeleteRecordTask()
{
    Zapp::Action* action = new Zapp::Action("DeleteRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoDeleteRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionGetRecordTask()
{
    Zapp::Action* action = new Zapp::Action("GetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoGetRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionEnableRecordTask()
{
    Zapp::Action* action = new Zapp::Action("EnableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoEnableRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionDisableRecordTask()
{
    Zapp::Action* action = new Zapp::Action("DisableRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoDisableRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionResetRecordTask()
{
    Zapp::Action* action = new Zapp::Action("ResetRecordTask");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoResetRecordTask);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionGetRecordScheduleConflicts()
{
    Zapp::Action* action = new Zapp::Action("GetRecordScheduleConflicts");
    action->AddInputParameter(new ParameterString("RecordScheduleID"));
    action->AddOutputParameter(new ParameterString("RecordScheduleConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoGetRecordScheduleConflicts);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableActionGetRecordTaskConflicts()
{
    Zapp::Action* action = new Zapp::Action("GetRecordTaskConflicts");
    action->AddInputParameter(new ParameterString("RecordTaskID"));
    action->AddOutputParameter(new ParameterString("RecordTaskConflictIDList"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgScheduledRecording2Cpp::DoGetRecordTaskConflicts);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DoGetSortCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSortCaps;
    uint32_t respSortLevelCap;
    GetSortCapabilities(aVersion, respSortCaps, respSortLevelCap);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterSortCaps(aInvocation, "SortCaps");
    Brn buf_SortCaps((const TByte*)respSortCaps.c_str(), respSortCaps.length());
    respWriterSortCaps.Write(buf_SortCaps);
    aInvocation.InvocationWriteStringEnd("SortCaps");
    InvocationResponseUint respWriterSortLevelCap(aInvocation, "SortLevelCap");
    respWriterSortLevelCap.Write(respSortLevelCap);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DoGetPropertyList(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_PropertyList((const TByte*)respPropertyList.c_str(), respPropertyList.length());
    respWriterPropertyList.Write(buf_PropertyList);
    aInvocation.InvocationWriteStringEnd("PropertyList");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DoGetAllowedValues(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_PropertyInfo((const TByte*)respPropertyInfo.c_str(), respPropertyInfo.length());
    respWriterPropertyInfo.Write(buf_PropertyInfo);
    aInvocation.InvocationWriteStringEnd("PropertyInfo");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DoGetStateUpdateID(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoBrowseRecordSchedules(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoBrowseRecordTasks(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoCreateRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_RecordScheduleID((const TByte*)respRecordScheduleID.c_str(), respRecordScheduleID.length());
    respWriterRecordScheduleID.Write(buf_RecordScheduleID);
    aInvocation.InvocationWriteStringEnd("RecordScheduleID");
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DoDeleteRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoGetRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DoEnableRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoDisableRecordSchedule(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoDeleteRecordTask(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoGetRecordTask(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DoEnableRecordTask(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoDisableRecordTask(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoResetRecordTask(IDvInvocation& aInvocation, TUint aVersion)
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

void DvServiceUpnpOrgScheduledRecording2Cpp::DoGetRecordScheduleConflicts(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_RecordScheduleConflictIDList((const TByte*)respRecordScheduleConflictIDList.c_str(), respRecordScheduleConflictIDList.length());
    respWriterRecordScheduleConflictIDList.Write(buf_RecordScheduleConflictIDList);
    aInvocation.InvocationWriteStringEnd("RecordScheduleConflictIDList");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DoGetRecordTaskConflicts(IDvInvocation& aInvocation, TUint aVersion)
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
    Brn buf_RecordTaskConflictIDList((const TByte*)respRecordTaskConflictIDList.c_str(), respRecordTaskConflictIDList.length());
    respWriterRecordTaskConflictIDList.Write(buf_RecordTaskConflictIDList);
    aInvocation.InvocationWriteStringEnd("RecordTaskConflictIDList");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetSortCapabilities(uint32_t /*aVersion*/, std::string& /*aSortCaps*/, uint32_t& /*aSortLevelCap*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetPropertyList(uint32_t /*aVersion*/, const std::string& /*aDataTypeID*/, std::string& /*aPropertyList*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetAllowedValues(uint32_t /*aVersion*/, const std::string& /*aDataTypeID*/, const std::string& /*aFilter*/, std::string& /*aPropertyInfo*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetStateUpdateID(uint32_t /*aVersion*/, uint32_t& /*aId*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::BrowseRecordSchedules(uint32_t /*aVersion*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::BrowseRecordTasks(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::CreateRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aElements*/, std::string& /*aRecordScheduleID*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DeleteRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/, const std::string& /*aFilter*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DisableRecordSchedule(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DeleteRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/, const std::string& /*aFilter*/, std::string& /*aResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::EnableRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::DisableRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::ResetRecordTask(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetRecordScheduleConflicts(uint32_t /*aVersion*/, const std::string& /*aRecordScheduleID*/, std::string& /*aRecordScheduleConflictIDList*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgScheduledRecording2Cpp::GetRecordTaskConflicts(uint32_t /*aVersion*/, const std::string& /*aRecordTaskID*/, std::string& /*aRecordTaskConflictIDList*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

