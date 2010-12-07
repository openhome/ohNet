#include <C/DvUpnpOrgContentDirectory2.h>
#include <Core/DvUpnpOrgContentDirectory2.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgContentDirectory2C : public DvProviderUpnpOrgContentDirectory2
{
public:
    DvProviderUpnpOrgContentDirectory2C(DvDevice& aDevice);
    void EnableActionGetSearchCapabilities(CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr);
    void EnableActionGetSortCapabilities(CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr);
    void EnableActionGetSortExtensionCapabilities(CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr);
    void EnableActionGetFeatureList(CallbackContentDirectory2GetFeatureList aCallback, void* aPtr);
    void EnableActionGetSystemUpdateID(CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr);
    void EnableActionBrowse(CallbackContentDirectory2Browse aCallback, void* aPtr);
    void EnableActionSearch(CallbackContentDirectory2Search aCallback, void* aPtr);
    void EnableActionCreateObject(CallbackContentDirectory2CreateObject aCallback, void* aPtr);
    void EnableActionDestroyObject(CallbackContentDirectory2DestroyObject aCallback, void* aPtr);
    void EnableActionUpdateObject(CallbackContentDirectory2UpdateObject aCallback, void* aPtr);
    void EnableActionMoveObject(CallbackContentDirectory2MoveObject aCallback, void* aPtr);
    void EnableActionImportResource(CallbackContentDirectory2ImportResource aCallback, void* aPtr);
    void EnableActionExportResource(CallbackContentDirectory2ExportResource aCallback, void* aPtr);
    void EnableActionDeleteResource(CallbackContentDirectory2DeleteResource aCallback, void* aPtr);
    void EnableActionStopTransferResource(CallbackContentDirectory2StopTransferResource aCallback, void* aPtr);
    void EnableActionGetTransferProgress(CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr);
    void EnableActionCreateReference(CallbackContentDirectory2CreateReference aCallback, void* aPtr);
private:
    void GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps);
    void GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps);
    void GetSortExtensionCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortExtensionCaps);
    void GetFeatureList(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFeatureList);
    void GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId);
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
private:
    CallbackContentDirectory2GetSearchCapabilities iCallbackGetSearchCapabilities;
    void* iPtrGetSearchCapabilities;
    CallbackContentDirectory2GetSortCapabilities iCallbackGetSortCapabilities;
    void* iPtrGetSortCapabilities;
    CallbackContentDirectory2GetSortExtensionCapabilities iCallbackGetSortExtensionCapabilities;
    void* iPtrGetSortExtensionCapabilities;
    CallbackContentDirectory2GetFeatureList iCallbackGetFeatureList;
    void* iPtrGetFeatureList;
    CallbackContentDirectory2GetSystemUpdateID iCallbackGetSystemUpdateID;
    void* iPtrGetSystemUpdateID;
    CallbackContentDirectory2Browse iCallbackBrowse;
    void* iPtrBrowse;
    CallbackContentDirectory2Search iCallbackSearch;
    void* iPtrSearch;
    CallbackContentDirectory2CreateObject iCallbackCreateObject;
    void* iPtrCreateObject;
    CallbackContentDirectory2DestroyObject iCallbackDestroyObject;
    void* iPtrDestroyObject;
    CallbackContentDirectory2UpdateObject iCallbackUpdateObject;
    void* iPtrUpdateObject;
    CallbackContentDirectory2MoveObject iCallbackMoveObject;
    void* iPtrMoveObject;
    CallbackContentDirectory2ImportResource iCallbackImportResource;
    void* iPtrImportResource;
    CallbackContentDirectory2ExportResource iCallbackExportResource;
    void* iPtrExportResource;
    CallbackContentDirectory2DeleteResource iCallbackDeleteResource;
    void* iPtrDeleteResource;
    CallbackContentDirectory2StopTransferResource iCallbackStopTransferResource;
    void* iPtrStopTransferResource;
    CallbackContentDirectory2GetTransferProgress iCallbackGetTransferProgress;
    void* iPtrGetTransferProgress;
    CallbackContentDirectory2CreateReference iCallbackCreateReference;
    void* iPtrCreateReference;
};

DvProviderUpnpOrgContentDirectory2C::DvProviderUpnpOrgContentDirectory2C(DvDevice& aDevice)
    : DvProviderUpnpOrgContentDirectory2(aDevice)
{
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetSearchCapabilities(CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionGetSearchCapabilities();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetSortCapabilities(CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionGetSortCapabilities();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetSortExtensionCapabilities(CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortExtensionCapabilities = aCallback;
    iPtrGetSortExtensionCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionGetSortExtensionCapabilities();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetFeatureList(CallbackContentDirectory2GetFeatureList aCallback, void* aPtr)
{
    iCallbackGetFeatureList = aCallback;
    iPtrGetFeatureList = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionGetFeatureList();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetSystemUpdateID(CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionGetSystemUpdateID();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionBrowse(CallbackContentDirectory2Browse aCallback, void* aPtr)
{
    iCallbackBrowse = aCallback;
    iPtrBrowse = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionBrowse();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionSearch(CallbackContentDirectory2Search aCallback, void* aPtr)
{
    iCallbackSearch = aCallback;
    iPtrSearch = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionSearch();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionCreateObject(CallbackContentDirectory2CreateObject aCallback, void* aPtr)
{
    iCallbackCreateObject = aCallback;
    iPtrCreateObject = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionCreateObject();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionDestroyObject(CallbackContentDirectory2DestroyObject aCallback, void* aPtr)
{
    iCallbackDestroyObject = aCallback;
    iPtrDestroyObject = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionDestroyObject();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionUpdateObject(CallbackContentDirectory2UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionUpdateObject();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionMoveObject(CallbackContentDirectory2MoveObject aCallback, void* aPtr)
{
    iCallbackMoveObject = aCallback;
    iPtrMoveObject = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionMoveObject();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionImportResource(CallbackContentDirectory2ImportResource aCallback, void* aPtr)
{
    iCallbackImportResource = aCallback;
    iPtrImportResource = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionImportResource();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionExportResource(CallbackContentDirectory2ExportResource aCallback, void* aPtr)
{
    iCallbackExportResource = aCallback;
    iPtrExportResource = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionExportResource();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionDeleteResource(CallbackContentDirectory2DeleteResource aCallback, void* aPtr)
{
    iCallbackDeleteResource = aCallback;
    iPtrDeleteResource = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionDeleteResource();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionStopTransferResource(CallbackContentDirectory2StopTransferResource aCallback, void* aPtr)
{
    iCallbackStopTransferResource = aCallback;
    iPtrStopTransferResource = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionStopTransferResource();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionGetTransferProgress(CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr)
{
    iCallbackGetTransferProgress = aCallback;
    iPtrGetTransferProgress = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionGetTransferProgress();
}

void DvProviderUpnpOrgContentDirectory2C::EnableActionCreateReference(CallbackContentDirectory2CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    DvProviderUpnpOrgContentDirectory2::EnableActionCreateReference();
}

void DvProviderUpnpOrgContentDirectory2C::GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps)
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

void DvProviderUpnpOrgContentDirectory2C::GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps)
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

void DvProviderUpnpOrgContentDirectory2C::GetSortExtensionCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortExtensionCaps)
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

void DvProviderUpnpOrgContentDirectory2C::GetFeatureList(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFeatureList)
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

void DvProviderUpnpOrgContentDirectory2C::GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId)
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

void DvProviderUpnpOrgContentDirectory2C::Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgContentDirectory2C::Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgContentDirectory2C::CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult)
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

void DvProviderUpnpOrgContentDirectory2C::DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID)
{
    ASSERT(iCallbackDestroyObject != NULL);
    if (0 != iCallbackDestroyObject(iPtrDestroyObject, aVersion, (const char*)aObjectID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory2C::UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    ASSERT(iCallbackUpdateObject != NULL);
    if (0 != iCallbackUpdateObject(iPtrUpdateObject, aVersion, (const char*)aObjectID.Ptr(), (const char*)aCurrentTagValue.Ptr(), (const char*)aNewTagValue.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory2C::MoveObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aNewParentID, IInvocationResponseString& aNewObjectID)
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

void DvProviderUpnpOrgContentDirectory2C::ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
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

void DvProviderUpnpOrgContentDirectory2C::ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
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

void DvProviderUpnpOrgContentDirectory2C::DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI)
{
    ASSERT(iCallbackDeleteResource != NULL);
    if (0 != iCallbackDeleteResource(iPtrDeleteResource, aVersion, (const char*)aResourceURI.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory2C::StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID)
{
    ASSERT(iCallbackStopTransferResource != NULL);
    if (0 != iCallbackStopTransferResource(iPtrStopTransferResource, aVersion, aTransferID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory2C::GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal)
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

void DvProviderUpnpOrgContentDirectory2C::CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID)
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



THandle DvProviderUpnpOrgContentDirectory2Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgContentDirectory2C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgContentDirectory2Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory2GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory2GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetSortExtensionCapabilities(THandle aProvider, CallbackContentDirectory2GetSortExtensionCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSortExtensionCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetFeatureList(THandle aProvider, CallbackContentDirectory2GetFeatureList aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetFeatureList(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory2GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionBrowse(THandle aProvider, CallbackContentDirectory2Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionBrowse(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionSearch(THandle aProvider, CallbackContentDirectory2Search aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionSearch(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionCreateObject(THandle aProvider, CallbackContentDirectory2CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionCreateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory2DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionDestroyObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory2UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionUpdateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionMoveObject(THandle aProvider, CallbackContentDirectory2MoveObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionMoveObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionImportResource(THandle aProvider, CallbackContentDirectory2ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionImportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionExportResource(THandle aProvider, CallbackContentDirectory2ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionExportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory2DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionDeleteResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory2StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionStopTransferResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory2GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory2EnableActionCreateReference(THandle aProvider, CallbackContentDirectory2CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->EnableActionCreateReference(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgContentDirectory2SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertySystemUpdateID(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory2GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgContentDirectory2SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertyContainerUpdateIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory2GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgContentDirectory2SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->SetPropertyTransferIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory2GetPropertyTransferIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory2C*>(aProvider)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

