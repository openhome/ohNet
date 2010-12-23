#include "DvUpnpOrgContentDirectory1C.h"
#include "DvUpnpOrgContentDirectory1.h"
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvProviderUpnpOrgContentDirectory1C : public DvProviderUpnpOrgContentDirectory1
{
public:
    DvProviderUpnpOrgContentDirectory1C(DvDevice& aDevice);
    void EnableActionGetSearchCapabilities(CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr);
    void EnableActionGetSortCapabilities(CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr);
    void EnableActionGetSystemUpdateID(CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr);
    void EnableActionBrowse(CallbackContentDirectory1Browse aCallback, void* aPtr);
    void EnableActionSearch(CallbackContentDirectory1Search aCallback, void* aPtr);
    void EnableActionCreateObject(CallbackContentDirectory1CreateObject aCallback, void* aPtr);
    void EnableActionDestroyObject(CallbackContentDirectory1DestroyObject aCallback, void* aPtr);
    void EnableActionUpdateObject(CallbackContentDirectory1UpdateObject aCallback, void* aPtr);
    void EnableActionImportResource(CallbackContentDirectory1ImportResource aCallback, void* aPtr);
    void EnableActionExportResource(CallbackContentDirectory1ExportResource aCallback, void* aPtr);
    void EnableActionStopTransferResource(CallbackContentDirectory1StopTransferResource aCallback, void* aPtr);
    void EnableActionGetTransferProgress(CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr);
    void EnableActionDeleteResource(CallbackContentDirectory1DeleteResource aCallback, void* aPtr);
    void EnableActionCreateReference(CallbackContentDirectory1CreateReference aCallback, void* aPtr);
private:
    void GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps);
    void GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps);
    void GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId);
    void Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    void Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    void CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult);
    void DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID);
    void UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue);
    void ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID);
    void ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID);
    void StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID);
    void GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal);
    void DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI);
    void CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID);
private:
    CallbackContentDirectory1GetSearchCapabilities iCallbackGetSearchCapabilities;
    void* iPtrGetSearchCapabilities;
    CallbackContentDirectory1GetSortCapabilities iCallbackGetSortCapabilities;
    void* iPtrGetSortCapabilities;
    CallbackContentDirectory1GetSystemUpdateID iCallbackGetSystemUpdateID;
    void* iPtrGetSystemUpdateID;
    CallbackContentDirectory1Browse iCallbackBrowse;
    void* iPtrBrowse;
    CallbackContentDirectory1Search iCallbackSearch;
    void* iPtrSearch;
    CallbackContentDirectory1CreateObject iCallbackCreateObject;
    void* iPtrCreateObject;
    CallbackContentDirectory1DestroyObject iCallbackDestroyObject;
    void* iPtrDestroyObject;
    CallbackContentDirectory1UpdateObject iCallbackUpdateObject;
    void* iPtrUpdateObject;
    CallbackContentDirectory1ImportResource iCallbackImportResource;
    void* iPtrImportResource;
    CallbackContentDirectory1ExportResource iCallbackExportResource;
    void* iPtrExportResource;
    CallbackContentDirectory1StopTransferResource iCallbackStopTransferResource;
    void* iPtrStopTransferResource;
    CallbackContentDirectory1GetTransferProgress iCallbackGetTransferProgress;
    void* iPtrGetTransferProgress;
    CallbackContentDirectory1DeleteResource iCallbackDeleteResource;
    void* iPtrDeleteResource;
    CallbackContentDirectory1CreateReference iCallbackCreateReference;
    void* iPtrCreateReference;
};

DvProviderUpnpOrgContentDirectory1C::DvProviderUpnpOrgContentDirectory1C(DvDevice& aDevice)
    : DvProviderUpnpOrgContentDirectory1(aDevice)
{
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSearchCapabilities(CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionGetSearchCapabilities();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSortCapabilities(CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionGetSortCapabilities();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetSystemUpdateID(CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionGetSystemUpdateID();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionBrowse(CallbackContentDirectory1Browse aCallback, void* aPtr)
{
    iCallbackBrowse = aCallback;
    iPtrBrowse = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionBrowse();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionSearch(CallbackContentDirectory1Search aCallback, void* aPtr)
{
    iCallbackSearch = aCallback;
    iPtrSearch = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionSearch();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionCreateObject(CallbackContentDirectory1CreateObject aCallback, void* aPtr)
{
    iCallbackCreateObject = aCallback;
    iPtrCreateObject = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionCreateObject();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionDestroyObject(CallbackContentDirectory1DestroyObject aCallback, void* aPtr)
{
    iCallbackDestroyObject = aCallback;
    iPtrDestroyObject = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionDestroyObject();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionUpdateObject(CallbackContentDirectory1UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionUpdateObject();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionImportResource(CallbackContentDirectory1ImportResource aCallback, void* aPtr)
{
    iCallbackImportResource = aCallback;
    iPtrImportResource = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionImportResource();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionExportResource(CallbackContentDirectory1ExportResource aCallback, void* aPtr)
{
    iCallbackExportResource = aCallback;
    iPtrExportResource = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionExportResource();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionStopTransferResource(CallbackContentDirectory1StopTransferResource aCallback, void* aPtr)
{
    iCallbackStopTransferResource = aCallback;
    iPtrStopTransferResource = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionStopTransferResource();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionGetTransferProgress(CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr)
{
    iCallbackGetTransferProgress = aCallback;
    iPtrGetTransferProgress = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionGetTransferProgress();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionDeleteResource(CallbackContentDirectory1DeleteResource aCallback, void* aPtr)
{
    iCallbackDeleteResource = aCallback;
    iPtrDeleteResource = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionDeleteResource();
}

void DvProviderUpnpOrgContentDirectory1C::EnableActionCreateReference(CallbackContentDirectory1CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    DvProviderUpnpOrgContentDirectory1::EnableActionCreateReference();
}

void DvProviderUpnpOrgContentDirectory1C::GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps)
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

void DvProviderUpnpOrgContentDirectory1C::GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps)
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

void DvProviderUpnpOrgContentDirectory1C::GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId)
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

void DvProviderUpnpOrgContentDirectory1C::Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgContentDirectory1C::Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvProviderUpnpOrgContentDirectory1C::CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult)
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

void DvProviderUpnpOrgContentDirectory1C::DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID)
{
    ASSERT(iCallbackDestroyObject != NULL);
    if (0 != iCallbackDestroyObject(iPtrDestroyObject, aVersion, (const char*)aObjectID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory1C::UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    ASSERT(iCallbackUpdateObject != NULL);
    if (0 != iCallbackUpdateObject(iPtrUpdateObject, aVersion, (const char*)aObjectID.Ptr(), (const char*)aCurrentTagValue.Ptr(), (const char*)aNewTagValue.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory1C::ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
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

void DvProviderUpnpOrgContentDirectory1C::ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
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

void DvProviderUpnpOrgContentDirectory1C::StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID)
{
    ASSERT(iCallbackStopTransferResource != NULL);
    if (0 != iCallbackStopTransferResource(iPtrStopTransferResource, aVersion, aTransferID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory1C::GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal)
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

void DvProviderUpnpOrgContentDirectory1C::DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI)
{
    ASSERT(iCallbackDeleteResource != NULL);
    if (0 != iCallbackDeleteResource(iPtrDeleteResource, aVersion, (const char*)aResourceURI.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvProviderUpnpOrgContentDirectory1C::CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID)
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



THandle DvProviderUpnpOrgContentDirectory1Create(DvDeviceC aDevice)
{
	return new DvProviderUpnpOrgContentDirectory1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvProviderUpnpOrgContentDirectory1Destroy(THandle aProvider)
{
    delete reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider);
}

void DvProviderUpnpOrgContentDirectory1EnableActionGetSearchCapabilities(THandle aProvider, CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionGetSortCapabilities(THandle aProvider, CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionGetSystemUpdateID(THandle aProvider, CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionBrowse(THandle aProvider, CallbackContentDirectory1Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionBrowse(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionSearch(THandle aProvider, CallbackContentDirectory1Search aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionSearch(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionCreateObject(THandle aProvider, CallbackContentDirectory1CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionCreateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionDestroyObject(THandle aProvider, CallbackContentDirectory1DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionDestroyObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionUpdateObject(THandle aProvider, CallbackContentDirectory1UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionUpdateObject(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionImportResource(THandle aProvider, CallbackContentDirectory1ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionImportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionExportResource(THandle aProvider, CallbackContentDirectory1ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionExportResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionStopTransferResource(THandle aProvider, CallbackContentDirectory1StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionStopTransferResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionGetTransferProgress(THandle aProvider, CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionDeleteResource(THandle aProvider, CallbackContentDirectory1DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionDeleteResource(aCallback, aPtr);
}

void DvProviderUpnpOrgContentDirectory1EnableActionCreateReference(THandle aProvider, CallbackContentDirectory1CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->EnableActionCreateReference(aCallback, aPtr);
}

int32_t DvProviderUpnpOrgContentDirectory1SetPropertyTransferIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertyTransferIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory1GetPropertyTransferIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvProviderUpnpOrgContentDirectory1SetPropertySystemUpdateID(THandle aProvider, uint32_t aValue, uint32_t* aChanged)
{
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertySystemUpdateID(aValue)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory1GetPropertySystemUpdateID(THandle aProvider, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t DvProviderUpnpOrgContentDirectory1SetPropertyContainerUpdateIDs(THandle aProvider, const char* aValue, uint32_t* aChanged)
{
    Brhz buf(aValue);
    *aChanged = (reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->SetPropertyContainerUpdateIDs(buf)? 1 : 0);
    return 0;
}

void DvProviderUpnpOrgContentDirectory1GetPropertyContainerUpdateIDs(THandle aProvider, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvProviderUpnpOrgContentDirectory1C*>(aProvider)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

