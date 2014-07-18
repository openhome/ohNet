#include "DvUpnpOrgContentDirectory2.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgContentDirectory2Cpp::SetPropertySystemUpdateID(uint32_t aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetPropertySystemUpdateID(uint32_t& aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    aValue = iPropertySystemUpdateID->Value();
}

bool DvProviderUpnpOrgContentDirectory2Cpp::SetPropertyContainerUpdateIDs(const std::string& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyContainerUpdateIDs, buf);
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetPropertyContainerUpdateIDs(std::string& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    const Brx& val = iPropertyContainerUpdateIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderUpnpOrgContentDirectory2Cpp::SetPropertyTransferIDs(const std::string& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTransferIDs, buf);
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetPropertyTransferIDs(std::string& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    const Brx& val = iPropertyTransferIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgContentDirectory2Cpp::DvProviderUpnpOrgContentDirectory2Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ContentDirectory", 2)
{
    iPropertySystemUpdateID = NULL;
    iPropertyContainerUpdateIDs = NULL;
    iPropertyTransferIDs = NULL;
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnablePropertySystemUpdateID()
{
    iPropertySystemUpdateID = new PropertyUint(iDvStack.Env(), new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnablePropertyContainerUpdateIDs()
{
    iPropertyContainerUpdateIDs = new PropertyString(iDvStack.Env(), new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnablePropertyTransferIDs()
{
    iPropertyTransferIDs = new PropertyString(iDvStack.Env(), new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionGetSearchCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionGetSortCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionGetSortExtensionCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortExtensionCapabilities");
    action->AddOutputParameter(new ParameterString("SortExtensionCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoGetSortExtensionCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionGetFeatureList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetFeatureList");
    action->AddOutputParameter(new ParameterString("FeatureList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoGetFeatureList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionGetSystemUpdateID()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionBrowse()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Browse");
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoBrowse);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionSearch()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("Search");
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoSearch);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionCreateObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionDestroyObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionUpdateObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionMoveObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("MoveObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("NewParentID"));
    action->AddOutputParameter(new ParameterString("NewObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoMoveObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionImportResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoImportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionExportResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoExportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionDeleteResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionStopTransferResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionGetTransferProgress()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetTransferProgress");
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::EnableActionCreateReference()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory2Cpp::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoGetSearchCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSearchCaps;
    DvInvocationStd invocation(aInvocation);
    GetSearchCapabilities(invocation, respSearchCaps);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterSearchCaps(aInvocation, "SearchCaps");
    Brn buf_SearchCaps((const TByte*)respSearchCaps.c_str(), (TUint)respSearchCaps.length());
    respWriterSearchCaps.Write(buf_SearchCaps);
    aInvocation.InvocationWriteStringEnd("SearchCaps");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoGetSortCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSortCaps;
    DvInvocationStd invocation(aInvocation);
    GetSortCapabilities(invocation, respSortCaps);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterSortCaps(aInvocation, "SortCaps");
    Brn buf_SortCaps((const TByte*)respSortCaps.c_str(), (TUint)respSortCaps.length());
    respWriterSortCaps.Write(buf_SortCaps);
    aInvocation.InvocationWriteStringEnd("SortCaps");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoGetSortExtensionCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respSortExtensionCaps;
    DvInvocationStd invocation(aInvocation);
    GetSortExtensionCapabilities(invocation, respSortExtensionCaps);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterSortExtensionCaps(aInvocation, "SortExtensionCaps");
    Brn buf_SortExtensionCaps((const TByte*)respSortExtensionCaps.c_str(), (TUint)respSortExtensionCaps.length());
    respWriterSortExtensionCaps.Write(buf_SortExtensionCaps);
    aInvocation.InvocationWriteStringEnd("SortExtensionCaps");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoGetFeatureList(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respFeatureList;
    DvInvocationStd invocation(aInvocation);
    GetFeatureList(invocation, respFeatureList);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterFeatureList(aInvocation, "FeatureList");
    Brn buf_FeatureList((const TByte*)respFeatureList.c_str(), (TUint)respFeatureList.length());
    respWriterFeatureList.Write(buf_FeatureList);
    aInvocation.InvocationWriteStringEnd("FeatureList");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoGetSystemUpdateID(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    uint32_t respId;
    DvInvocationStd invocation(aInvocation);
    GetSystemUpdateID(invocation, respId);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterId(aInvocation, "Id");
    respWriterId.Write(respId);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoBrowse(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    Browse(invocation, ObjectID, BrowseFlag, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
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

void DvProviderUpnpOrgContentDirectory2Cpp::DoSearch(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    Search(invocation, ContainerID, SearchCriteria, Filter, StartingIndex, RequestedCount, SortCriteria, respResult, respNumberReturned, respTotalMatches, respUpdateID);
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

void DvProviderUpnpOrgContentDirectory2Cpp::DoCreateObject(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    CreateObject(invocation, ContainerID, Elements, respObjectID, respResult);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterObjectID(aInvocation, "ObjectID");
    Brn buf_ObjectID((const TByte*)respObjectID.c_str(), (TUint)respObjectID.length());
    respWriterObjectID.Write(buf_ObjectID);
    aInvocation.InvocationWriteStringEnd("ObjectID");
    DviInvocationResponseString respWriterResult(aInvocation, "Result");
    Brn buf_Result((const TByte*)respResult.c_str(), (TUint)respResult.length());
    respWriterResult.Write(buf_Result);
    aInvocation.InvocationWriteStringEnd("Result");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoDestroyObject(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ObjectID;
    aInvocation.InvocationReadString("ObjectID", buf_ObjectID);
    std::string ObjectID((const char*)buf_ObjectID.Ptr(), buf_ObjectID.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DestroyObject(invocation, ObjectID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoUpdateObject(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    UpdateObject(invocation, ObjectID, CurrentTagValue, NewTagValue);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoMoveObject(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    MoveObject(invocation, ObjectID, NewParentID, respNewObjectID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterNewObjectID(aInvocation, "NewObjectID");
    Brn buf_NewObjectID((const TByte*)respNewObjectID.c_str(), (TUint)respNewObjectID.length());
    respWriterNewObjectID.Write(buf_NewObjectID);
    aInvocation.InvocationWriteStringEnd("NewObjectID");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoImportResource(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    ImportResource(invocation, SourceURI, DestinationURI, respTransferID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterTransferID(aInvocation, "TransferID");
    respWriterTransferID.Write(respTransferID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoExportResource(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    ExportResource(invocation, SourceURI, DestinationURI, respTransferID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseUint respWriterTransferID(aInvocation, "TransferID");
    respWriterTransferID.Write(respTransferID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoDeleteResource(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    Brhz buf_ResourceURI;
    aInvocation.InvocationReadString("ResourceURI", buf_ResourceURI);
    std::string ResourceURI((const char*)buf_ResourceURI.Ptr(), buf_ResourceURI.Bytes());
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    DeleteResource(invocation, ResourceURI);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoStopTransferResource(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    StopTransferResource(invocation, TransferID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoGetTransferProgress(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    std::string respTransferStatus;
    std::string respTransferLength;
    std::string respTransferTotal;
    DvInvocationStd invocation(aInvocation);
    GetTransferProgress(invocation, TransferID, respTransferStatus, respTransferLength, respTransferTotal);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterTransferStatus(aInvocation, "TransferStatus");
    Brn buf_TransferStatus((const TByte*)respTransferStatus.c_str(), (TUint)respTransferStatus.length());
    respWriterTransferStatus.Write(buf_TransferStatus);
    aInvocation.InvocationWriteStringEnd("TransferStatus");
    DviInvocationResponseString respWriterTransferLength(aInvocation, "TransferLength");
    Brn buf_TransferLength((const TByte*)respTransferLength.c_str(), (TUint)respTransferLength.length());
    respWriterTransferLength.Write(buf_TransferLength);
    aInvocation.InvocationWriteStringEnd("TransferLength");
    DviInvocationResponseString respWriterTransferTotal(aInvocation, "TransferTotal");
    Brn buf_TransferTotal((const TByte*)respTransferTotal.c_str(), (TUint)respTransferTotal.length());
    respWriterTransferTotal.Write(buf_TransferTotal);
    aInvocation.InvocationWriteStringEnd("TransferTotal");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DoCreateReference(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    CreateReference(invocation, ContainerID, ObjectID, respNewID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterNewID(aInvocation, "NewID");
    Brn buf_NewID((const TByte*)respNewID.c_str(), (TUint)respNewID.length());
    respWriterNewID.Write(buf_NewID);
    aInvocation.InvocationWriteStringEnd("NewID");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetSearchCapabilities(IDvInvocationStd& /*aInvocation*/, std::string& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetSortCapabilities(IDvInvocationStd& /*aInvocation*/, std::string& /*aSortCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetSortExtensionCapabilities(IDvInvocationStd& /*aInvocation*/, std::string& /*aSortExtensionCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetFeatureList(IDvInvocationStd& /*aInvocation*/, std::string& /*aFeatureList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetSystemUpdateID(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::Browse(IDvInvocationStd& /*aInvocation*/, const std::string& /*aObjectID*/, const std::string& /*aBrowseFlag*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::Search(IDvInvocationStd& /*aInvocation*/, const std::string& /*aContainerID*/, const std::string& /*aSearchCriteria*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::CreateObject(IDvInvocationStd& /*aInvocation*/, const std::string& /*aContainerID*/, const std::string& /*aElements*/, std::string& /*aObjectID*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DestroyObject(IDvInvocationStd& /*aInvocation*/, const std::string& /*aObjectID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::UpdateObject(IDvInvocationStd& /*aInvocation*/, const std::string& /*aObjectID*/, const std::string& /*aCurrentTagValue*/, const std::string& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::MoveObject(IDvInvocationStd& /*aInvocation*/, const std::string& /*aObjectID*/, const std::string& /*aNewParentID*/, std::string& /*aNewObjectID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::ImportResource(IDvInvocationStd& /*aInvocation*/, const std::string& /*aSourceURI*/, const std::string& /*aDestinationURI*/, uint32_t& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::ExportResource(IDvInvocationStd& /*aInvocation*/, const std::string& /*aSourceURI*/, const std::string& /*aDestinationURI*/, uint32_t& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::DeleteResource(IDvInvocationStd& /*aInvocation*/, const std::string& /*aResourceURI*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::StopTransferResource(IDvInvocationStd& /*aInvocation*/, uint32_t /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::GetTransferProgress(IDvInvocationStd& /*aInvocation*/, uint32_t /*aTransferID*/, std::string& /*aTransferStatus*/, std::string& /*aTransferLength*/, std::string& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory2Cpp::CreateReference(IDvInvocationStd& /*aInvocation*/, const std::string& /*aContainerID*/, const std::string& /*aObjectID*/, std::string& /*aNewID*/)
{
    ASSERTS();
}

