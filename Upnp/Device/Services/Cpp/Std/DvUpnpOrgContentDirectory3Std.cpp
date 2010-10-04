#include <Std/DvUpnpOrgContentDirectory3.h>
#include <ZappTypes.h>
#include <DviService.h>
#include <Service.h>
#include <FunctorDvInvocation.h>

using namespace Zapp;

void DvServiceUpnpOrgContentDirectory3Cpp::SetPropertySystemUpdateID(uint32_t aValue)
{
    SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetPropertySystemUpdateID(uint32_t& aValue)
{
    aValue = iPropertySystemUpdateID->Value();
}

void DvServiceUpnpOrgContentDirectory3Cpp::SetPropertyContainerUpdateIDs(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyContainerUpdateIDs, buf);
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetPropertyContainerUpdateIDs(std::string& aValue)
{
    const Brx& val = iPropertyContainerUpdateIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceUpnpOrgContentDirectory3Cpp::SetPropertyLastChange(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyLastChange, buf);
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetPropertyLastChange(std::string& aValue)
{
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

void DvServiceUpnpOrgContentDirectory3Cpp::SetPropertyTransferIDs(const std::string& aValue)
{
    Brn buf((const TByte*)aValue.c_str(), aValue.length());
    SetPropertyString(*iPropertyTransferIDs, buf);
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetPropertyTransferIDs(std::string& aValue)
{
    const Brx& val = iPropertyTransferIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvServiceUpnpOrgContentDirectory3Cpp::DvServiceUpnpOrgContentDirectory3Cpp(DvDeviceStd& aDevice)
    : DvService(aDevice.Device(), "upnp.org", "ContentDirectory", 3)
{
    Functor empty;
    iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"), empty);
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
    iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs"), empty);
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
    iPropertyLastChange = new PropertyString(new ParameterString("LastChange"), empty);
    iService->AddProperty(iPropertyLastChange); // passes ownership
    iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs"), empty);
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionGetSearchCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionGetSortCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionGetSortExtensionCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetSortExtensionCapabilities");
    action->AddOutputParameter(new ParameterString("SortExtensionCaps"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoGetSortExtensionCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionGetFeatureList()
{
    Zapp::Action* action = new Zapp::Action("GetFeatureList");
    action->AddOutputParameter(new ParameterString("FeatureList"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoGetFeatureList);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionGetSystemUpdateID()
{
    Zapp::Action* action = new Zapp::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionGetServiceResetToken()
{
    Zapp::Action* action = new Zapp::Action("GetServiceResetToken");
    action->AddOutputParameter(new ParameterString("ResetToken"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoGetServiceResetToken);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionBrowse()
{
    Zapp::Action* action = new Zapp::Action("Browse");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterString("ObjectID"));
    index = 0;
    allowedValues = new TChar*[2];
    allowedValues[index++] = (TChar*)"BrowseMetadata";
    allowedValues[index++] = (TChar*)"BrowseDirectChildren";
    action->AddInputParameter(new ParameterString("BrowseFlag", allowedValues, 2));
    delete[] allowedValues;
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoBrowse);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionSearch()
{
    Zapp::Action* action = new Zapp::Action("Search");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("SearchCriteria"));
    action->AddInputParameter(new ParameterString("Filter"));
    action->AddInputParameter(new ParameterUint("StartingIndex"));
    action->AddInputParameter(new ParameterUint("RequestedCount"));
    action->AddInputParameter(new ParameterString("SortCriteria"));
    action->AddOutputParameter(new ParameterString("Result"));
    action->AddOutputParameter(new ParameterUint("NumberReturned"));
    action->AddOutputParameter(new ParameterUint("TotalMatches"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoSearch);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionCreateObject()
{
    Zapp::Action* action = new Zapp::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionDestroyObject()
{
    Zapp::Action* action = new Zapp::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionUpdateObject()
{
    Zapp::Action* action = new Zapp::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionMoveObject()
{
    Zapp::Action* action = new Zapp::Action("MoveObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("NewParentID"));
    action->AddOutputParameter(new ParameterString("NewObjectID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoMoveObject);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionImportResource()
{
    Zapp::Action* action = new Zapp::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoImportResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionExportResource()
{
    Zapp::Action* action = new Zapp::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoExportResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionDeleteResource()
{
    Zapp::Action* action = new Zapp::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionStopTransferResource()
{
    Zapp::Action* action = new Zapp::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionGetTransferProgress()
{
    Zapp::Action* action = new Zapp::Action("GetTransferProgress");
    TChar** allowedValues;
    TUint index;
    action->AddInputParameter(new ParameterUint("TransferID"));
    index = 0;
    allowedValues = new TChar*[4];
    allowedValues[index++] = (TChar*)"COMPLETED";
    allowedValues[index++] = (TChar*)"ERROR";
    allowedValues[index++] = (TChar*)"IN_PROGRESS";
    allowedValues[index++] = (TChar*)"STOPPED";
    action->AddOutputParameter(new ParameterString("TransferStatus", allowedValues, 4));
    delete[] allowedValues;
    action->AddOutputParameter(new ParameterString("TransferLength"));
    action->AddOutputParameter(new ParameterString("TransferTotal"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionCreateReference()
{
    Zapp::Action* action = new Zapp::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionFreeFormQuery()
{
    Zapp::Action* action = new Zapp::Action("FreeFormQuery");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterUint("CDSView"));
    action->AddInputParameter(new ParameterString("QueryRequest"));
    action->AddOutputParameter(new ParameterString("QueryResult"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoFreeFormQuery);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::EnableActionGetFreeFormQueryCapabilities()
{
    Zapp::Action* action = new Zapp::Action("GetFreeFormQueryCapabilities");
    action->AddOutputParameter(new ParameterString("FFQCapabilities"));
    FunctorDvInvocation functor = MakeFunctorDvInvocation(*this, &DvServiceUpnpOrgContentDirectory3Cpp::DoGetFreeFormQueryCapabilities);
    iService->AddAction(action, functor);
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoGetSearchCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSearchCaps;
    GetSearchCapabilities(aVersion, respSearchCaps);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterSearchCaps(aInvocation, "SearchCaps");
    Brn buf_SearchCaps((const TByte*)respSearchCaps.c_str(), respSearchCaps.length());
    respWriterSearchCaps.Write(buf_SearchCaps);
    aInvocation.InvocationWriteStringEnd("SearchCaps");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoGetSortCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSortCaps;
    GetSortCapabilities(aVersion, respSortCaps);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterSortCaps(aInvocation, "SortCaps");
    Brn buf_SortCaps((const TByte*)respSortCaps.c_str(), respSortCaps.length());
    respWriterSortCaps.Write(buf_SortCaps);
    aInvocation.InvocationWriteStringEnd("SortCaps");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoGetSortExtensionCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSortExtensionCaps;
    GetSortExtensionCapabilities(aVersion, respSortExtensionCaps);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterSortExtensionCaps(aInvocation, "SortExtensionCaps");
    Brn buf_SortExtensionCaps((const TByte*)respSortExtensionCaps.c_str(), respSortExtensionCaps.length());
    respWriterSortExtensionCaps.Write(buf_SortExtensionCaps);
    aInvocation.InvocationWriteStringEnd("SortExtensionCaps");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoGetFeatureList(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respFeatureList;
    GetFeatureList(aVersion, respFeatureList);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterFeatureList(aInvocation, "FeatureList");
    Brn buf_FeatureList((const TByte*)respFeatureList.c_str(), respFeatureList.length());
    respWriterFeatureList.Write(buf_FeatureList);
    aInvocation.InvocationWriteStringEnd("FeatureList");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoGetSystemUpdateID(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respId;
    GetSystemUpdateID(aVersion, respId);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterId(aInvocation, "Id");
    respWriterId.Write(respId);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoGetServiceResetToken(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respResetToken;
    GetServiceResetToken(aVersion, respResetToken);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterResetToken(aInvocation, "ResetToken");
    Brn buf_ResetToken((const TByte*)respResetToken.c_str(), respResetToken.length());
    respWriterResetToken.Write(buf_ResetToken);
    aInvocation.InvocationWriteStringEnd("ResetToken");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoBrowse(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    Brhz buf_BrowseFlag;
    aInvocation.InvocationReadString("BrowseFlag", buf_BrowseFlag);
    std::string BrowseFlag((const char*)buf_BrowseFlag.Ptr(), buf_BrowseFlag.Bytes());
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
    Browse(aVersion, ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
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

void DvServiceUpnpOrgContentDirectory3Cpp::DoSearch(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ContainerID;
    aInvocation.InvocationReadString("ContainerID", buf_ContainerID);
    std::string ContainerID((const char*)buf_ContainerID.Ptr(), buf_ContainerID.Bytes());
    Brhz buf_SearchCriteria;
    aInvocation.InvocationReadString("SearchCriteria", buf_SearchCriteria);
    std::string SearchCriteria((const char*)buf_SearchCriteria.Ptr(), buf_SearchCriteria.Bytes());
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
    Search(aVersion, ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
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

void DvServiceUpnpOrgContentDirectory3Cpp::DoCreateObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ContainerID;
    aInvocation.InvocationReadString("ContainerID", buf_ContainerID);
    std::string ContainerID((const char*)buf_ContainerID.Ptr(), buf_ContainerID.Bytes());
    Brhz buf_Elements;
    aInvocation.InvocationReadString("Elements", buf_Elements);
    std::string Elements((const char*)buf_Elements.Ptr(), buf_Elements.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respObjectID;
    std::string respResult;
    CreateObject(aVersion, ContainerID, Elements, respObjectID, respResult);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterObjectID(aInvocation, "ObjectID");
    Brn buf_ObjectID((const TByte*)respObjectID.c_str(), respObjectID.length());
    respWriterObjectID.Write(buf_ObjectID);
    aInvocation.InvocationWriteStringEnd("ObjectID");
    InvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoDestroyObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    aInvocation.InvocationReadEnd();
    DestroyObject(aVersion, ObjectID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoUpdateObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    Brhz buf_CurrentTagValue;
    aInvocation.InvocationReadString("CurrentTagValue", buf_CurrentTagValue);
    std::string CurrentTagValue((const char*)buf_CurrentTagValue.Ptr(), buf_CurrentTagValue.Bytes());
    Brhz buf_NewTagValue;
    aInvocation.InvocationReadString("NewTagValue", buf_NewTagValue);
    std::string NewTagValue((const char*)buf_NewTagValue.Ptr(), buf_NewTagValue.Bytes());
    aInvocation.InvocationReadEnd();
    UpdateObject(aVersion, ObjectID, CurrentTagValue, NewTagValue);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoMoveObject(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    Brhz buf_NewParentID;
    aInvocation.InvocationReadString("NewParentID", buf_NewParentID);
    std::string NewParentID((const char*)buf_NewParentID.Ptr(), buf_NewParentID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respNewObjectID;
    MoveObject(aVersion, ObjectID, NewParentID, respNewObjectID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterNewObjectID(aInvocation, "NewObjectID");
    Brn buf_NewObjectID((const TByte*)respNewObjectID.c_str(), respNewObjectID.length());
    respWriterNewObjectID.Write(buf_NewObjectID);
    aInvocation.InvocationWriteStringEnd("NewObjectID");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoImportResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_SourceURI;
    aInvocation.InvocationReadString("SourceURI", buf_SourceURI);
    std::string SourceURI((const char*)buf_SourceURI.Ptr(), buf_SourceURI.Bytes());
    Brhz buf_DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", buf_DestinationURI);
    std::string DestinationURI((const char*)buf_DestinationURI.Ptr(), buf_DestinationURI.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respTransferID;
    ImportResource(aVersion, SourceURI, DestinationURI, respTransferID);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterTransferID(aInvocation, "TransferID");
    respWriterTransferID.Write(respTransferID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoExportResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_SourceURI;
    aInvocation.InvocationReadString("SourceURI", buf_SourceURI);
    std::string SourceURI((const char*)buf_SourceURI.Ptr(), buf_SourceURI.Bytes());
    Brhz buf_DestinationURI;
    aInvocation.InvocationReadString("DestinationURI", buf_DestinationURI);
    std::string DestinationURI((const char*)buf_DestinationURI.Ptr(), buf_DestinationURI.Bytes());
    aInvocation.InvocationReadEnd();
    uint32_t respTransferID;
    ExportResource(aVersion, SourceURI, DestinationURI, respTransferID);
	aInvocation.InvocationWriteStart();
    InvocationResponseUint respWriterTransferID(aInvocation, "TransferID");
    respWriterTransferID.Write(respTransferID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoDeleteResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", buf_ResourceURI);
    std::string ResourceURI((const char*)buf_ResourceURI.Ptr(), buf_ResourceURI.Bytes());
    aInvocation.InvocationReadEnd();
    DeleteResource(aVersion, ResourceURI);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoStopTransferResource(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    StopTransferResource(aVersion, TransferID);
	aInvocation.InvocationWriteStart();
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoGetTransferProgress(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    uint32_t TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    std::string respTransferStatus;
    std::string respTransferLength;
    std::string respTransferTotal;
    GetTransferProgress(aVersion, TransferID, respTransferStatus, respTransferLength, respTransferTotal);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterTransferStatus(aInvocation, "TransferStatus");
    Brn buf_TransferStatus((const TByte*)respTransferStatus.c_str(), respTransferStatus.length());
    respWriterTransferStatus.Write(buf_TransferStatus);
    aInvocation.InvocationWriteStringEnd("TransferStatus");
    InvocationResponseString respWriterTransferLength(aInvocation, "TransferLength");
    Brn buf_TransferLength((const TByte*)respTransferLength.c_str(), respTransferLength.length());
    respWriterTransferLength.Write(buf_TransferLength);
    aInvocation.InvocationWriteStringEnd("TransferLength");
    InvocationResponseString respWriterTransferTotal(aInvocation, "TransferTotal");
    Brn buf_TransferTotal((const TByte*)respTransferTotal.c_str(), respTransferTotal.length());
    respWriterTransferTotal.Write(buf_TransferTotal);
    aInvocation.InvocationWriteStringEnd("TransferTotal");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoCreateReference(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ContainerID;
    aInvocation.InvocationReadString("ContainerID", buf_ContainerID);
    std::string ContainerID((const char*)buf_ContainerID.Ptr(), buf_ContainerID.Bytes());
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respNewID;
    CreateReference(aVersion, ContainerID, ObjectID, respNewID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterNewID(aInvocation, "NewID");
    Brn buf_NewID((const TByte*)respNewID.c_str(), respNewID.length());
    respWriterNewID.Write(buf_NewID);
    aInvocation.InvocationWriteStringEnd("NewID");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoFreeFormQuery(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ContainerID;
    aInvocation.InvocationReadString("ContainerID", buf_ContainerID);
    std::string ContainerID((const char*)buf_ContainerID.Ptr(), buf_ContainerID.Bytes());
    uint32_t CDSView = aInvocation.InvocationReadUint("CDSView");
    Brhz buf_QueryRequest;
    aInvocation.InvocationReadString("QueryRequest", buf_QueryRequest);
    std::string QueryRequest((const char*)buf_QueryRequest.Ptr(), buf_QueryRequest.Bytes());
    aInvocation.InvocationReadEnd();
    std::string respQueryResult;
    uint32_t respUpdateID;
    FreeFormQuery(aVersion, ContainerID, CDSView, QueryRequest, respQueryResult, respUpdateID);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterQueryResult(aInvocation, "QueryResult");
    Brn buf_QueryResult((const TByte*)respQueryResult.c_str(), respQueryResult.length());
    respWriterQueryResult.Write(buf_QueryResult);
    aInvocation.InvocationWriteStringEnd("QueryResult");
    InvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DoGetFreeFormQueryCapabilities(IDvInvocation& aInvocation, TUint aVersion)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respFFQCapabilities;
    GetFreeFormQueryCapabilities(aVersion, respFFQCapabilities);
	aInvocation.InvocationWriteStart();
    InvocationResponseString respWriterFFQCapabilities(aInvocation, "FFQCapabilities");
    Brn buf_FFQCapabilities((const TByte*)respFFQCapabilities.c_str(), respFFQCapabilities.length());
    respWriterFFQCapabilities.Write(buf_FFQCapabilities);
    aInvocation.InvocationWriteStringEnd("FFQCapabilities");
	aInvocation.InvocationWriteEnd();
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetSearchCapabilities(uint32_t /*aVersion*/, std::string& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetSortCapabilities(uint32_t /*aVersion*/, std::string& /*aSortCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetSortExtensionCapabilities(uint32_t /*aVersion*/, std::string& /*aSortExtensionCaps*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetFeatureList(uint32_t /*aVersion*/, std::string& /*aFeatureList*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetSystemUpdateID(uint32_t /*aVersion*/, uint32_t& /*aId*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetServiceResetToken(uint32_t /*aVersion*/, std::string& /*aResetToken*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::Browse(uint32_t /*aVersion*/, const std::string& /*aObjectID*/, const std::string& /*aBrowseFlag*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::Search(uint32_t /*aVersion*/, const std::string& /*aContainerID*/, const std::string& /*aSearchCriteria*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::CreateObject(uint32_t /*aVersion*/, const std::string& /*aContainerID*/, const std::string& /*aElements*/, std::string& /*aObjectID*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DestroyObject(uint32_t /*aVersion*/, const std::string& /*aObjectID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::UpdateObject(uint32_t /*aVersion*/, const std::string& /*aObjectID*/, const std::string& /*aCurrentTagValue*/, const std::string& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::MoveObject(uint32_t /*aVersion*/, const std::string& /*aObjectID*/, const std::string& /*aNewParentID*/, std::string& /*aNewObjectID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::ImportResource(uint32_t /*aVersion*/, const std::string& /*aSourceURI*/, const std::string& /*aDestinationURI*/, uint32_t& /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::ExportResource(uint32_t /*aVersion*/, const std::string& /*aSourceURI*/, const std::string& /*aDestinationURI*/, uint32_t& /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::DeleteResource(uint32_t /*aVersion*/, const std::string& /*aResourceURI*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::StopTransferResource(uint32_t /*aVersion*/, uint32_t /*aTransferID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetTransferProgress(uint32_t /*aVersion*/, uint32_t /*aTransferID*/, std::string& /*aTransferStatus*/, std::string& /*aTransferLength*/, std::string& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::CreateReference(uint32_t /*aVersion*/, const std::string& /*aContainerID*/, const std::string& /*aObjectID*/, std::string& /*aNewID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::FreeFormQuery(uint32_t /*aVersion*/, const std::string& /*aContainerID*/, uint32_t /*aCDSView*/, const std::string& /*aQueryRequest*/, std::string& /*aQueryResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvServiceUpnpOrgContentDirectory3Cpp::GetFreeFormQueryCapabilities(uint32_t /*aVersion*/, std::string& /*aFFQCapabilities*/)
{
    ASSERTS();
}

