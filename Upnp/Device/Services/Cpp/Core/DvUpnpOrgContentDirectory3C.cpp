#include "DvUpnpOrgContentDirectory3C.h"
#include "DvUpnpOrgContentDirectory3.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgContentDirectory3C : public DvProviderUpnpOrgContentDirectory3
{
public:
    DvProviderUpnpOrgContentDirectory3C(DvDevice& aDevice);
    void EnableActionGetSearchCapabilities(CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr);
    void EnableActionGetSortCapabilities(CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr);
    void EnableActionGetSortExtensionCapabilities(CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr);
    void EnableActionGetFeatureList(CallbackContentDirectory3GetFeatureList aCallback, void* aPtr);
    void EnableActionGetSystemUpdateID(CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr);
    void EnableActionGetServiceResetToken(CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr);
    void EnableActionBrowse(CallbackContentDirectory3Browse aCallback, void* aPtr);
    void EnableActionSearch(CallbackContentDirectory3Search aCallback, void* aPtr);
    void EnableActionCreateObject(CallbackContentDirectory3CreateObject aCallback, void* aPtr);
    void EnableActionDestroyObject(CallbackContentDirectory3DestroyObject aCallback, void* aPtr);
    void EnableActionUpdateObject(CallbackContentDirectory3UpdateObject aCallback, void* aPtr);
    void EnableActionMoveObject(CallbackContentDirectory3MoveObject aCallback, void* aPtr);
    void EnableActionImportResource(CallbackContentDirectory3ImportResource aCallback, void* aPtr);
    void EnableActionExportResource(CallbackContentDirectory3ExportResource aCallback, void* aPtr);
    void EnableActionDeleteResource(CallbackContentDirectory3DeleteResource aCallback, void* aPtr);
    void EnableActionStopTransferResource(CallbackContentDirectory3StopTransferResource aCallback, void* aPtr);
    void EnableActionGetTransferProgress(CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr);
    void EnableActionCreateReference(CallbackContentDirectory3CreateReference aCallback, void* aPtr);
    void EnableActionFreeFormQuery(CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr);
    void EnableActionGetFreeFormQueryCapabilities(CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr);
private:
    void GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps);
    void GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps);
    void GetSortExtensionCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortExtensionCaps);
    void GetFeatureList(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFeatureList);
    void GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId);
    void GetServiceResetToken(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aResetToken);
    void Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    void Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    void CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult);
    void DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID);
    void UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue);
    void MoveObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aNewParentID, IInvocationResponseString& aNewObjectID);
    void ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID);
    void ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID);
    void DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI);
    void StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID);
    void GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal);
    void CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID);
    void FreeFormQuery(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, TUint aCDSView, const Brx& aQueryRequest, IInvocationResponseString& aQueryResult, IInvocationResponseUint& aUpdateID);
    void GetFreeFormQueryCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFFQCapabilities);
private:
    CallbackContentDirectory3GetSearchCapabilities iCallbackGetSearchCapabilities;
    void* iPtrGetSearchCapabilities;
    CallbackContentDirectory3GetSortCapabilities iCallbackGetSortCapabilities;
    void* iPtrGetSortCapabilities;
    CallbackContentDirectory3GetSortExtensionCapabilities iCallbackGetSortExtensionCapabilities;
    void* iPtrGetSortExtensionCapabilities;
    CallbackContentDirectory3GetFeatureList iCallbackGetFeatureList;
    void* iPtrGetFeatureList;
    CallbackContentDirectory3GetSystemUpdateID iCallbackGetSystemUpdateID;
    void* iPtrGetSystemUpdateID;
    CallbackContentDirectory3GetServiceResetToken iCallbackGetServiceResetToken;
    void* iPtrGetServiceResetToken;
    CallbackContentDirectory3Browse iCallbackBrowse;
    void* iPtrBrowse;
    CallbackContentDirectory3Search iCallbackSearch;
    void* iPtrSearch;
    CallbackContentDirectory3CreateObject iCallbackCreateObject;
    void* iPtrCreateObject;
    CallbackContentDirectory3DestroyObject iCallbackDestroyObject;
    void* iPtrDestroyObject;
    CallbackContentDirectory3UpdateObject iCallbackUpdateObject;
    void* iPtrUpdateObject;
    CallbackContentDirectory3MoveObject iCallbackMoveObject;
    void* iPtrMoveObject;
    CallbackContentDirectory3ImportResource iCallbackImportResource;
    void* iPtrImportResource;
    CallbackContentDirectory3ExportResource iCallbackExportResource;
    void* iPtrExportResource;
    CallbackContentDirectory3DeleteResource iCallbackDeleteResource;
    void* iPtrDeleteResource;
    CallbackContentDirectory3StopTransferResource iCallbackStopTransferResource;
    void* iPtrStopTransferResource;
    CallbackContentDirectory3GetTransferProgress iCallbackGetTransferProgress;
    void* iPtrGetTransferProgress;
    CallbackContentDirectory3CreateReference iCallbackCreateReference;
    void* iPtrCreateReference;
    CallbackContentDirectory3FreeFormQuery iCallbackFreeFormQuery;
    void* iPtrFreeFormQuery;
    CallbackContentDirectory3GetFreeFormQueryCapabilities iCallbackGetFreeFormQueryCapabilities;
    void* iPtrGetFreeFormQueryCapabilities;
};

DvProviderUpnpOrgContentDirectory3C::DvProviderUpnpOrgContentDirectory3C(DvDevice& aDevice)
    : DvProviderUpnpOrgContentDirectory3(aDevice)
{
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetSearchCapabilities(CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionGetSearchCapabilities();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetSortCapabilities(CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionGetSortCapabilities();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetSortExtensionCapabilities(CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortExtensionCapabilities = aCallback;
    iPtrGetSortExtensionCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionGetSortExtensionCapabilities();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetFeatureList(CallbackContentDirectory3GetFeatureList aCallback, void* aPtr)
{
    iCallbackGetFeatureList = aCallback;
    iPtrGetFeatureList = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionGetFeatureList();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetSystemUpdateID(CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionGetSystemUpdateID();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetServiceResetToken(CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr)
{
    iCallbackGetServiceResetToken = aCallback;
    iPtrGetServiceResetToken = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionGetServiceResetToken();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionBrowse(CallbackContentDirectory3Browse aCallback, void* aPtr)
{
    iCallbackBrowse = aCallback;
    iPtrBrowse = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionBrowse();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionSearch(CallbackContentDirectory3Search aCallback, void* aPtr)
{
    iCallbackSearch = aCallback;
    iPtrSearch = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionSearch();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionCreateObject(CallbackContentDirectory3CreateObject aCallback, void* aPtr)
{
    iCallbackCreateObject = aCallback;
    iPtrCreateObject = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionCreateObject();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionDestroyObject(CallbackContentDirectory3DestroyObject aCallback, void* aPtr)
{
    iCallbackDestroyObject = aCallback;
    iPtrDestroyObject = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionDestroyObject();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionUpdateObject(CallbackContentDirectory3UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionUpdateObject();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionMoveObject(CallbackContentDirectory3MoveObject aCallback, void* aPtr)
{
    iCallbackMoveObject = aCallback;
    iPtrMoveObject = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionMoveObject();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionImportResource(CallbackContentDirectory3ImportResource aCallback, void* aPtr)
{
    iCallbackImportResource = aCallback;
    iPtrImportResource = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionImportResource();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionExportResource(CallbackContentDirectory3ExportResource aCallback, void* aPtr)
{
    iCallbackExportResource = aCallback;
    iPtrExportResource = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionExportResource();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionDeleteResource(CallbackContentDirectory3DeleteResource aCallback, void* aPtr)
{
    iCallbackDeleteResource = aCallback;
    iPtrDeleteResource = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionDeleteResource();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionStopTransferResource(CallbackContentDirectory3StopTransferResource aCallback, void* aPtr)
{
    iCallbackStopTransferResource = aCallback;
    iPtrStopTransferResource = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionStopTransferResource();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetTransferProgress(CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr)
{
    iCallbackGetTransferProgress = aCallback;
    iPtrGetTransferProgress = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionGetTransferProgress();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionCreateReference(CallbackContentDirectory3CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionCreateReference();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionFreeFormQuery(CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr)
{
    iCallbackFreeFormQuery = aCallback;
    iPtrFreeFormQuery = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionFreeFormQuery();
}

void DvProviderUpnpOrgContentDirectory3C::EnableActionGetFreeFormQueryCapabilities(CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr)
{
    iCallbackGetFreeFormQueryCapabilities = aCallback;
    iPtrGetFreeFormQueryCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory3::EnableActionGetFreeFormQueryCapabilities();
}

void DvProviderUpnpOrgContentDirectory3C::GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps)
{
    char* SearchCaps;
    ASSERT(iCallbackGetSearchCapabilities != NULL);
    if (0 != iCallbackGetSearchCapabilities(iPtrGetSearchCapabilities, aVersion, &SearchCaps)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufSearchCaps((const TChar*)SearchCaps);
    ZappFreeExternal(SearchCaps);
    aSearchCaps.Write(bufSearchCaps);
    aSearchCaps.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps)
{
    char* SortCaps;
    ASSERT(iCallbackGetSortCapabilities != NULL);
    if (0 != iCallbackGetSortCapabilities(iPtrGetSortCapabilities, aVersion, &SortCaps)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufSortCaps((const TChar*)SortCaps);
    ZappFreeExternal(SortCaps);
    aSortCaps.Write(bufSortCaps);
    aSortCaps.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::GetSortExtensionCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortExtensionCaps)
{
    char* SortExtensionCaps;
    ASSERT(iCallbackGetSortExtensionCapabilities != NULL);
    if (0 != iCallbackGetSortExtensionCapabilities(iPtrGetSortExtensionCapabilities, aVersion, &SortExtensionCaps)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufSortExtensionCaps((const TChar*)SortExtensionCaps);
    ZappFreeExternal(SortExtensionCaps);
    aSortExtensionCaps.Write(bufSortExtensionCaps);
    aSortExtensionCaps.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::GetFeatureList(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFeatureList)
{
    char* FeatureList;
    ASSERT(iCallbackGetFeatureList != NULL);
    if (0 != iCallbackGetFeatureList(iPtrGetFeatureList, aVersion, &FeatureList)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufFeatureList((const TChar*)FeatureList);
    ZappFreeExternal(FeatureList);
    aFeatureList.Write(bufFeatureList);
    aFeatureList.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId)
{
    uint32_t Id;
    ASSERT(iCallbackGetSystemUpdateID != NULL);
    if (0 != iCallbackGetSystemUpdateID(iPtrGetSystemUpdateID, aVersion, &Id)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aId.Write(Id);
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::GetServiceResetToken(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aResetToken)
{
    char* ResetToken;
    ASSERT(iCallbackGetServiceResetToken != NULL);
    if (0 != iCallbackGetServiceResetToken(iPtrGetServiceResetToken, aVersion, &ResetToken)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufResetToken((const TChar*)ResetToken);
    ZappFreeExternal(ResetToken);
    aResetToken.Write(bufResetToken);
    aResetToken.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
{
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackBrowse != NULL);
    if (0 != iCallbackBrowse(iPtrBrowse, aVersion, (const char*)aObjectID.Ptr(), (const char*)aBrowseFlag.Ptr(), (const char*)aFilter.Ptr(), aStartingIndex, aRequestedCount, (const char*)aSortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aNumberReturned.Write(NumberReturned);
    aTotalMatches.Write(TotalMatches);
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
{
    char* Result;
    uint32_t NumberReturned;
    uint32_t TotalMatches;
    uint32_t UpdateID;
    ASSERT(iCallbackSearch != NULL);
    if (0 != iCallbackSearch(iPtrSearch, aVersion, (const char*)aContainerID.Ptr(), (const char*)aSearchCriteria.Ptr(), (const char*)aFilter.Ptr(), aStartingIndex, aRequestedCount, (const char*)aSortCriteria.Ptr(), &Result, &NumberReturned, &TotalMatches, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aNumberReturned.Write(NumberReturned);
    aTotalMatches.Write(TotalMatches);
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult)
{
    char* ObjectID;
    char* Result;
    ASSERT(iCallbackCreateObject != NULL);
    if (0 != iCallbackCreateObject(iPtrCreateObject, aVersion, (const char*)aContainerID.Ptr(), (const char*)aElements.Ptr(), &ObjectID, &Result)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufObjectID((const TChar*)ObjectID);
    ZappFreeExternal(ObjectID);
    aObjectID.Write(bufObjectID);
    aObjectID.WriteFlush();
    Brhz bufResult((const TChar*)Result);
    ZappFreeExternal(Result);
    aResult.Write(bufResult);
    aResult.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID)
{
    ASSERT(iCallbackDestroyObject != NULL);
    if (0 != iCallbackDestroyObject(iPtrDestroyObject, aVersion, (const char*)aObjectID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    ASSERT(iCallbackUpdateObject != NULL);
    if (0 != iCallbackUpdateObject(iPtrUpdateObject, aVersion, (const char*)aObjectID.Ptr(), (const char*)aCurrentTagValue.Ptr(), (const char*)aNewTagValue.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::MoveObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aNewParentID, IInvocationResponseString& aNewObjectID)
{
    char* NewObjectID;
    ASSERT(iCallbackMoveObject != NULL);
    if (0 != iCallbackMoveObject(iPtrMoveObject, aVersion, (const char*)aObjectID.Ptr(), (const char*)aNewParentID.Ptr(), &NewObjectID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufNewObjectID((const TChar*)NewObjectID);
    ZappFreeExternal(NewObjectID);
    aNewObjectID.Write(bufNewObjectID);
    aNewObjectID.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
{
    uint32_t TransferID;
    ASSERT(iCallbackImportResource != NULL);
    if (0 != iCallbackImportResource(iPtrImportResource, aVersion, (const char*)aSourceURI.Ptr(), (const char*)aDestinationURI.Ptr(), &TransferID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aTransferID.Write(TransferID);
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
{
    uint32_t TransferID;
    ASSERT(iCallbackExportResource != NULL);
    if (0 != iCallbackExportResource(iPtrExportResource, aVersion, (const char*)aSourceURI.Ptr(), (const char*)aDestinationURI.Ptr(), &TransferID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aTransferID.Write(TransferID);
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI)
{
    ASSERT(iCallbackDeleteResource != NULL);
    if (0 != iCallbackDeleteResource(iPtrDeleteResource, aVersion, (const char*)aResourceURI.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID)
{
    ASSERT(iCallbackStopTransferResource != NULL);
    if (0 != iCallbackStopTransferResource(iPtrStopTransferResource, aVersion, aTransferID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal)
{
    char* TransferStatus;
    char* TransferLength;
    char* TransferTotal;
    ASSERT(iCallbackGetTransferProgress != NULL);
    if (0 != iCallbackGetTransferProgress(iPtrGetTransferProgress, aVersion, aTransferID, &TransferStatus, &TransferLength, &TransferTotal)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufTransferStatus((const TChar*)TransferStatus);
    ZappFreeExternal(TransferStatus);
    aTransferStatus.Write(bufTransferStatus);
    aTransferStatus.WriteFlush();
    Brhz bufTransferLength((const TChar*)TransferLength);
    ZappFreeExternal(TransferLength);
    aTransferLength.Write(bufTransferLength);
    aTransferLength.WriteFlush();
    Brhz bufTransferTotal((const TChar*)TransferTotal);
    ZappFreeExternal(TransferTotal);
    aTransferTotal.Write(bufTransferTotal);
    aTransferTotal.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID)
{
    char* NewID;
    ASSERT(iCallbackCreateReference != NULL);
    if (0 != iCallbackCreateReference(iPtrCreateReference, aVersion, (const char*)aContainerID.Ptr(), (const char*)aObjectID.Ptr(), &NewID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufNewID((const TChar*)NewID);
    ZappFreeExternal(NewID);
    aNewID.Write(bufNewID);
    aNewID.WriteFlush();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::FreeFormQuery(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, TUint aCDSView, const Brx& aQueryRequest, IInvocationResponseString& aQueryResult, IInvocationResponseUint& aUpdateID)
{
    char* QueryResult;
    uint32_t UpdateID;
    ASSERT(iCallbackFreeFormQuery != NULL);
    if (0 != iCallbackFreeFormQuery(iPtrFreeFormQuery, aVersion, (const char*)aContainerID.Ptr(), aCDSView, (const char*)aQueryRequest.Ptr(), &QueryResult, &UpdateID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufQueryResult((const TChar*)QueryResult);
    ZappFreeExternal(QueryResult);
    aQueryResult.Write(bufQueryResult);
    aQueryResult.WriteFlush();
    aUpdateID.Write(UpdateID);
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory3C::GetFreeFormQueryCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFFQCapabilities)
{
    char* FFQCapabilities;
    ASSERT(iCallbackGetFreeFormQueryCapabilities != NULL);
    if (0 != iCallbackGetFreeFormQueryCapabilities(iPtrGetFreeFormQueryCapabilities, aVersion, &FFQCapabilities)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    Brhz bufFFQCapabilities((const TChar*)FFQCapabilities);
    ZappFreeExternal(FFQCapabilities);
    aFFQCapabilities.Write(bufFFQCapabilities);
    aFFQCapabilities.WriteFlush();
    aResponse.End();
}



THandle DvProviderUpnpOrgContentDirectory3Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgContentDirectory3C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgContentDirectory3Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider);
}

void DvProviderUpnpOrgContentDirectory3EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionGetSortExtensionCapabilities(THandle aProvider, CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetSortExtensionCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionGetFeatureList(THandle aProvider, CallbackContentDirectory3GetFeatureList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetFeatureList(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionGetServiceResetToken(THandle aProvider, CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetServiceResetToken(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionBrowse(THandle aProvider, CallbackContentDirectory3Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionBrowse(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionSearch(THandle aProvider, CallbackContentDirectory3Search aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionSearch(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionCreateObject(THandle aProvider, CallbackContentDirectory3CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionCreateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory3DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionDestroyObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory3UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionUpdateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionMoveObject(THandle aProvider, CallbackContentDirectory3MoveObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionMoveObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionImportResource(THandle aProvider, CallbackContentDirectory3ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionImportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionExportResource(THandle aProvider, CallbackContentDirectory3ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionExportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory3DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionDeleteResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory3StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionStopTransferResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionCreateReference(THandle aProvider, CallbackContentDirectory3CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionCreateReference(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionFreeFormQuery(THandle aProvider, CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionFreeFormQuery(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory3EnableActionGetFreeFormQueryCapabilities(THandle aProvider, CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->EnableActionGetFreeFormQueryCapabilities(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgContentDirectory3SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->SetPropertySystemUpdateID(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory3GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgContentDirectory3SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->SetPropertyContainerUpdateIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory3GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgContentDirectory3SetPropertyLastChange(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->SetPropertyLastChange(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory3GetPropertyLastChange(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgContentDirectory3SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->SetPropertyTransferIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory3GetPropertyTransferIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory3C*>(aProvider)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

