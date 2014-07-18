#include "DvUpnpOrgContentDirectory3.h"
#include <OpenHome/Types.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Net/Private/FunctorDviInvocation.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

bool DvProviderUpnpOrgContentDirectory3Cpp::SetPropertySystemUpdateID(uint32_t aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    return SetPropertyUint(*iPropertySystemUpdateID, aValue);
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetPropertySystemUpdateID(uint32_t& aValue)
{
    ASSERT(iPropertySystemUpdateID != NULL);
    aValue = iPropertySystemUpdateID->Value();
}

bool DvProviderUpnpOrgContentDirectory3Cpp::SetPropertyContainerUpdateIDs(const std::string& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyContainerUpdateIDs, buf);
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetPropertyContainerUpdateIDs(std::string& aValue)
{
    ASSERT(iPropertyContainerUpdateIDs != NULL);
    const Brx& val = iPropertyContainerUpdateIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderUpnpOrgContentDirectory3Cpp::SetPropertyLastChange(const std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyLastChange, buf);
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetPropertyLastChange(std::string& aValue)
{
    ASSERT(iPropertyLastChange != NULL);
    const Brx& val = iPropertyLastChange->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

bool DvProviderUpnpOrgContentDirectory3Cpp::SetPropertyTransferIDs(const std::string& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    Brn buf((const TByte*)aValue.c_str(), (TUint)aValue.length());
    return SetPropertyString(*iPropertyTransferIDs, buf);
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetPropertyTransferIDs(std::string& aValue)
{
    ASSERT(iPropertyTransferIDs != NULL);
    const Brx& val = iPropertyTransferIDs->Value();
    aValue.assign((const char*)val.Ptr(), val.Bytes());
}

DvProviderUpnpOrgContentDirectory3Cpp::DvProviderUpnpOrgContentDirectory3Cpp(DvDeviceStd& aDevice)
    : DvProvider(aDevice.Device(), "upnp.org", "ContentDirectory", 3)
{
    iPropertySystemUpdateID = NULL;
    iPropertyContainerUpdateIDs = NULL;
    iPropertyLastChange = NULL;
    iPropertyTransferIDs = NULL;
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnablePropertySystemUpdateID()
{
    iPropertySystemUpdateID = new PropertyUint(iDvStack.Env(), new ParameterUint("SystemUpdateID"));
    iService->AddProperty(iPropertySystemUpdateID); // passes ownership
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnablePropertyContainerUpdateIDs()
{
    iPropertyContainerUpdateIDs = new PropertyString(iDvStack.Env(), new ParameterString("ContainerUpdateIDs"));
    iService->AddProperty(iPropertyContainerUpdateIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnablePropertyLastChange()
{
    iPropertyLastChange = new PropertyString(iDvStack.Env(), new ParameterString("LastChange"));
    iService->AddProperty(iPropertyLastChange); // passes ownership
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnablePropertyTransferIDs()
{
    iPropertyTransferIDs = new PropertyString(iDvStack.Env(), new ParameterString("TransferIDs"));
    iService->AddProperty(iPropertyTransferIDs); // passes ownership
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionGetSearchCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSearchCapabilities");
    action->AddOutputParameter(new ParameterString("SearchCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoGetSearchCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionGetSortCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortCapabilities");
    action->AddOutputParameter(new ParameterString("SortCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoGetSortCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionGetSortExtensionCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSortExtensionCapabilities");
    action->AddOutputParameter(new ParameterString("SortExtensionCaps"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoGetSortExtensionCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionGetFeatureList()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetFeatureList");
    action->AddOutputParameter(new ParameterString("FeatureList"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoGetFeatureList);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionGetSystemUpdateID()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetSystemUpdateID");
    action->AddOutputParameter(new ParameterRelated("Id", *iPropertySystemUpdateID));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoGetSystemUpdateID);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionGetServiceResetToken()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetServiceResetToken");
    action->AddOutputParameter(new ParameterString("ResetToken"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoGetServiceResetToken);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionBrowse()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoBrowse);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionSearch()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoSearch);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionCreateObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateObject");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("Elements"));
    action->AddOutputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("Result"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoCreateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionDestroyObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DestroyObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoDestroyObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionUpdateObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("UpdateObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("CurrentTagValue"));
    action->AddInputParameter(new ParameterString("NewTagValue"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoUpdateObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionMoveObject()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("MoveObject");
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddInputParameter(new ParameterString("NewParentID"));
    action->AddOutputParameter(new ParameterString("NewObjectID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoMoveObject);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionImportResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ImportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoImportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionExportResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("ExportResource");
    action->AddInputParameter(new ParameterString("SourceURI"));
    action->AddInputParameter(new ParameterString("DestinationURI"));
    action->AddOutputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoExportResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionDeleteResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("DeleteResource");
    action->AddInputParameter(new ParameterString("ResourceURI"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoDeleteResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionStopTransferResource()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("StopTransferResource");
    action->AddInputParameter(new ParameterUint("TransferID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoStopTransferResource);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionGetTransferProgress()
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
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoGetTransferProgress);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionCreateReference()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("CreateReference");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterString("ObjectID"));
    action->AddOutputParameter(new ParameterString("NewID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoCreateReference);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionFreeFormQuery()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("FreeFormQuery");
    action->AddInputParameter(new ParameterString("ContainerID"));
    action->AddInputParameter(new ParameterUint("CDSView"));
    action->AddInputParameter(new ParameterString("QueryRequest"));
    action->AddOutputParameter(new ParameterString("QueryResult"));
    action->AddOutputParameter(new ParameterUint("UpdateID"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoFreeFormQuery);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::EnableActionGetFreeFormQueryCapabilities()
{
    OpenHome::Net::Action* action = new OpenHome::Net::Action("GetFreeFormQueryCapabilities");
    action->AddOutputParameter(new ParameterString("FFQCapabilities"));
    FunctorDviInvocation functor = MakeFunctorDviInvocation(*this, &DvProviderUpnpOrgContentDirectory3Cpp::DoGetFreeFormQueryCapabilities);
    iService->AddAction(action, functor);
}

void DvProviderUpnpOrgContentDirectory3Cpp::DoGetSearchCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoGetSortCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoGetSortExtensionCapabilities(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoGetFeatureList(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoGetSystemUpdateID(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoGetServiceResetToken(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respResetToken;
    DvInvocationStd invocation(aInvocation);
    GetServiceResetToken(invocation, respResetToken);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterResetToken(aInvocation, "ResetToken");
    Brn buf_ResetToken((const TByte*)respResetToken.c_str(), (TUint)respResetToken.length());
    respWriterResetToken.Write(buf_ResetToken);
    aInvocation.InvocationWriteStringEnd("ResetToken");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory3Cpp::DoBrowse(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoSearch(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoCreateObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoDestroyObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoUpdateObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoMoveObject(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoImportResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoExportResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoDeleteResource(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoStopTransferResource(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    uint32_t TransferID = aInvocation.InvocationReadUint("TransferID");
    aInvocation.InvocationReadEnd();
    DvInvocationStd invocation(aInvocation);
    StopTransferResource(invocation, TransferID);
    aInvocation.InvocationWriteStart();
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory3Cpp::DoGetTransferProgress(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoCreateReference(IDviInvocation& aInvocation)
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

void DvProviderUpnpOrgContentDirectory3Cpp::DoFreeFormQuery(IDviInvocation& aInvocation)
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
    DvInvocationStd invocation(aInvocation);
    FreeFormQuery(invocation, ContainerID, CDSView, QueryRequest, respQueryResult, respUpdateID);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterQueryResult(aInvocation, "QueryResult");
    Brn buf_QueryResult((const TByte*)respQueryResult.c_str(), (TUint)respQueryResult.length());
    respWriterQueryResult.Write(buf_QueryResult);
    aInvocation.InvocationWriteStringEnd("QueryResult");
    DviInvocationResponseUint respWriterUpdateID(aInvocation, "UpdateID");
    respWriterUpdateID.Write(respUpdateID);
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory3Cpp::DoGetFreeFormQueryCapabilities(IDviInvocation& aInvocation)
{
    aInvocation.InvocationReadStart();
    aInvocation.InvocationReadEnd();
    std::string respFFQCapabilities;
    DvInvocationStd invocation(aInvocation);
    GetFreeFormQueryCapabilities(invocation, respFFQCapabilities);
    aInvocation.InvocationWriteStart();
    DviInvocationResponseString respWriterFFQCapabilities(aInvocation, "FFQCapabilities");
    Brn buf_FFQCapabilities((const TByte*)respFFQCapabilities.c_str(), (TUint)respFFQCapabilities.length());
    respWriterFFQCapabilities.Write(buf_FFQCapabilities);
    aInvocation.InvocationWriteStringEnd("FFQCapabilities");
    aInvocation.InvocationWriteEnd();
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetSearchCapabilities(IDvInvocationStd& /*aInvocation*/, std::string& /*aSearchCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetSortCapabilities(IDvInvocationStd& /*aInvocation*/, std::string& /*aSortCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetSortExtensionCapabilities(IDvInvocationStd& /*aInvocation*/, std::string& /*aSortExtensionCaps*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetFeatureList(IDvInvocationStd& /*aInvocation*/, std::string& /*aFeatureList*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetSystemUpdateID(IDvInvocationStd& /*aInvocation*/, uint32_t& /*aId*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetServiceResetToken(IDvInvocationStd& /*aInvocation*/, std::string& /*aResetToken*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::Browse(IDvInvocationStd& /*aInvocation*/, const std::string& /*aObjectID*/, const std::string& /*aBrowseFlag*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::Search(IDvInvocationStd& /*aInvocation*/, const std::string& /*aContainerID*/, const std::string& /*aSearchCriteria*/, const std::string& /*aFilter*/, uint32_t /*aStartingIndex*/, uint32_t /*aRequestedCount*/, const std::string& /*aSortCriteria*/, std::string& /*aResult*/, uint32_t& /*aNumberReturned*/, uint32_t& /*aTotalMatches*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::CreateObject(IDvInvocationStd& /*aInvocation*/, const std::string& /*aContainerID*/, const std::string& /*aElements*/, std::string& /*aObjectID*/, std::string& /*aResult*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::DestroyObject(IDvInvocationStd& /*aInvocation*/, const std::string& /*aObjectID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::UpdateObject(IDvInvocationStd& /*aInvocation*/, const std::string& /*aObjectID*/, const std::string& /*aCurrentTagValue*/, const std::string& /*aNewTagValue*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::MoveObject(IDvInvocationStd& /*aInvocation*/, const std::string& /*aObjectID*/, const std::string& /*aNewParentID*/, std::string& /*aNewObjectID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::ImportResource(IDvInvocationStd& /*aInvocation*/, const std::string& /*aSourceURI*/, const std::string& /*aDestinationURI*/, uint32_t& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::ExportResource(IDvInvocationStd& /*aInvocation*/, const std::string& /*aSourceURI*/, const std::string& /*aDestinationURI*/, uint32_t& /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::DeleteResource(IDvInvocationStd& /*aInvocation*/, const std::string& /*aResourceURI*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::StopTransferResource(IDvInvocationStd& /*aInvocation*/, uint32_t /*aTransferID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetTransferProgress(IDvInvocationStd& /*aInvocation*/, uint32_t /*aTransferID*/, std::string& /*aTransferStatus*/, std::string& /*aTransferLength*/, std::string& /*aTransferTotal*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::CreateReference(IDvInvocationStd& /*aInvocation*/, const std::string& /*aContainerID*/, const std::string& /*aObjectID*/, std::string& /*aNewID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::FreeFormQuery(IDvInvocationStd& /*aInvocation*/, const std::string& /*aContainerID*/, uint32_t /*aCDSView*/, const std::string& /*aQueryRequest*/, std::string& /*aQueryResult*/, uint32_t& /*aUpdateID*/)
{
    ASSERTS();
}

void DvProviderUpnpOrgContentDirectory3Cpp::GetFreeFormQueryCapabilities(IDvInvocationStd& /*aInvocation*/, std::string& /*aFFQCapabilities*/)
{
    ASSERTS();
}

