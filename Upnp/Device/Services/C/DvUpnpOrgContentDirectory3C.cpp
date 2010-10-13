#include <C/DvUpnpOrgContentDirectory3.h>
#include <Core/DvUpnpOrgContentDirectory3.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgContentDirectory3C : public DvServiceUpnpOrgContentDirectory3
{
public:
    DvServiceUpnpOrgContentDirectory3C(DvDevice& aDevice);
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

DvServiceUpnpOrgContentDirectory3C::DvServiceUpnpOrgContentDirectory3C(DvDevice& aDevice)
    : DvServiceUpnpOrgContentDirectory3(aDevice)
{
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionGetSearchCapabilities(CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionGetSearchCapabilities();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionGetSortCapabilities(CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionGetSortCapabilities();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionGetSortExtensionCapabilities(CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortExtensionCapabilities = aCallback;
    iPtrGetSortExtensionCapabilities = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionGetSortExtensionCapabilities();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionGetFeatureList(CallbackContentDirectory3GetFeatureList aCallback, void* aPtr)
{
    iCallbackGetFeatureList = aCallback;
    iPtrGetFeatureList = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionGetFeatureList();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionGetSystemUpdateID(CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionGetSystemUpdateID();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionGetServiceResetToken(CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr)
{
    iCallbackGetServiceResetToken = aCallback;
    iPtrGetServiceResetToken = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionGetServiceResetToken();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionBrowse(CallbackContentDirectory3Browse aCallback, void* aPtr)
{
    iCallbackBrowse = aCallback;
    iPtrBrowse = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionBrowse();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionSearch(CallbackContentDirectory3Search aCallback, void* aPtr)
{
    iCallbackSearch = aCallback;
    iPtrSearch = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionSearch();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionCreateObject(CallbackContentDirectory3CreateObject aCallback, void* aPtr)
{
    iCallbackCreateObject = aCallback;
    iPtrCreateObject = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionCreateObject();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionDestroyObject(CallbackContentDirectory3DestroyObject aCallback, void* aPtr)
{
    iCallbackDestroyObject = aCallback;
    iPtrDestroyObject = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionDestroyObject();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionUpdateObject(CallbackContentDirectory3UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionUpdateObject();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionMoveObject(CallbackContentDirectory3MoveObject aCallback, void* aPtr)
{
    iCallbackMoveObject = aCallback;
    iPtrMoveObject = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionMoveObject();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionImportResource(CallbackContentDirectory3ImportResource aCallback, void* aPtr)
{
    iCallbackImportResource = aCallback;
    iPtrImportResource = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionImportResource();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionExportResource(CallbackContentDirectory3ExportResource aCallback, void* aPtr)
{
    iCallbackExportResource = aCallback;
    iPtrExportResource = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionExportResource();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionDeleteResource(CallbackContentDirectory3DeleteResource aCallback, void* aPtr)
{
    iCallbackDeleteResource = aCallback;
    iPtrDeleteResource = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionDeleteResource();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionStopTransferResource(CallbackContentDirectory3StopTransferResource aCallback, void* aPtr)
{
    iCallbackStopTransferResource = aCallback;
    iPtrStopTransferResource = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionStopTransferResource();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionGetTransferProgress(CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr)
{
    iCallbackGetTransferProgress = aCallback;
    iPtrGetTransferProgress = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionGetTransferProgress();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionCreateReference(CallbackContentDirectory3CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionCreateReference();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionFreeFormQuery(CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr)
{
    iCallbackFreeFormQuery = aCallback;
    iPtrFreeFormQuery = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionFreeFormQuery();
}

void DvServiceUpnpOrgContentDirectory3C::EnableActionGetFreeFormQueryCapabilities(CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr)
{
    iCallbackGetFreeFormQueryCapabilities = aCallback;
    iPtrGetFreeFormQueryCapabilities = aPtr;
    DvServiceUpnpOrgContentDirectory3::EnableActionGetFreeFormQueryCapabilities();
}

void DvServiceUpnpOrgContentDirectory3C::GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps)
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

void DvServiceUpnpOrgContentDirectory3C::GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps)
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

void DvServiceUpnpOrgContentDirectory3C::GetSortExtensionCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortExtensionCaps)
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

void DvServiceUpnpOrgContentDirectory3C::GetFeatureList(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFeatureList)
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

void DvServiceUpnpOrgContentDirectory3C::GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId)
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

void DvServiceUpnpOrgContentDirectory3C::GetServiceResetToken(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aResetToken)
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

void DvServiceUpnpOrgContentDirectory3C::Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvServiceUpnpOrgContentDirectory3C::Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvServiceUpnpOrgContentDirectory3C::CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult)
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

void DvServiceUpnpOrgContentDirectory3C::DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID)
{
    ASSERT(iCallbackDestroyObject != NULL);
    if (0 != iCallbackDestroyObject(iPtrDestroyObject, aVersion, (const char*)aObjectID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgContentDirectory3C::UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    ASSERT(iCallbackUpdateObject != NULL);
    if (0 != iCallbackUpdateObject(iPtrUpdateObject, aVersion, (const char*)aObjectID.Ptr(), (const char*)aCurrentTagValue.Ptr(), (const char*)aNewTagValue.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgContentDirectory3C::MoveObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aNewParentID, IInvocationResponseString& aNewObjectID)
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

void DvServiceUpnpOrgContentDirectory3C::ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
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

void DvServiceUpnpOrgContentDirectory3C::ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
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

void DvServiceUpnpOrgContentDirectory3C::DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI)
{
    ASSERT(iCallbackDeleteResource != NULL);
    if (0 != iCallbackDeleteResource(iPtrDeleteResource, aVersion, (const char*)aResourceURI.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgContentDirectory3C::StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID)
{
    ASSERT(iCallbackStopTransferResource != NULL);
    if (0 != iCallbackStopTransferResource(iPtrStopTransferResource, aVersion, aTransferID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgContentDirectory3C::GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal)
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

void DvServiceUpnpOrgContentDirectory3C::CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID)
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

void DvServiceUpnpOrgContentDirectory3C::FreeFormQuery(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, TUint aCDSView, const Brx& aQueryRequest, IInvocationResponseString& aQueryResult, IInvocationResponseUint& aUpdateID)
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

void DvServiceUpnpOrgContentDirectory3C::GetFreeFormQueryCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFFQCapabilities)
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



THandle DvServiceUpnpOrgContentDirectory3Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgContentDirectory3C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgContentDirectory3Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService);
}

void DvServiceUpnpOrgContentDirectory3EnableActionGetSearchCapabilities(THandle aService, CallbackContentDirectory3GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionGetSortCapabilities(THandle aService, CallbackContentDirectory3GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionGetSortExtensionCapabilities(THandle aService, CallbackContentDirectory3GetSortExtensionCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionGetSortExtensionCapabilities(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionGetFeatureList(THandle aService, CallbackContentDirectory3GetFeatureList aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionGetFeatureList(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionGetSystemUpdateID(THandle aService, CallbackContentDirectory3GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionGetServiceResetToken(THandle aService, CallbackContentDirectory3GetServiceResetToken aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionGetServiceResetToken(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionBrowse(THandle aService, CallbackContentDirectory3Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionBrowse(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionSearch(THandle aService, CallbackContentDirectory3Search aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionSearch(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionCreateObject(THandle aService, CallbackContentDirectory3CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionCreateObject(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionDestroyObject(THandle aService, CallbackContentDirectory3DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionDestroyObject(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionUpdateObject(THandle aService, CallbackContentDirectory3UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionUpdateObject(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionMoveObject(THandle aService, CallbackContentDirectory3MoveObject aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionMoveObject(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionImportResource(THandle aService, CallbackContentDirectory3ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionImportResource(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionExportResource(THandle aService, CallbackContentDirectory3ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionExportResource(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionDeleteResource(THandle aService, CallbackContentDirectory3DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionDeleteResource(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionStopTransferResource(THandle aService, CallbackContentDirectory3StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionStopTransferResource(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionGetTransferProgress(THandle aService, CallbackContentDirectory3GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionCreateReference(THandle aService, CallbackContentDirectory3CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionCreateReference(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionFreeFormQuery(THandle aService, CallbackContentDirectory3FreeFormQuery aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionFreeFormQuery(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory3EnableActionGetFreeFormQueryCapabilities(THandle aService, CallbackContentDirectory3GetFreeFormQueryCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->EnableActionGetFreeFormQueryCapabilities(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgContentDirectory3SetPropertySystemUpdateID(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->SetPropertySystemUpdateID(aValue);
    return 0;
}

void DvServiceUpnpOrgContentDirectory3GetPropertySystemUpdateID(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t DvServiceUpnpOrgContentDirectory3SetPropertyContainerUpdateIDs(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->SetPropertyContainerUpdateIDs(buf);
    return 0;
}

void DvServiceUpnpOrgContentDirectory3GetPropertyContainerUpdateIDs(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceUpnpOrgContentDirectory3SetPropertyLastChange(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->SetPropertyLastChange(buf);
    return 0;
}

void DvServiceUpnpOrgContentDirectory3GetPropertyLastChange(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->GetPropertyLastChange(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceUpnpOrgContentDirectory3SetPropertyTransferIDs(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->SetPropertyTransferIDs(buf);
    return 0;
}

void DvServiceUpnpOrgContentDirectory3GetPropertyTransferIDs(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgContentDirectory3C*>(aService)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

