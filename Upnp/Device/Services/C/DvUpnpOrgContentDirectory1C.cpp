#include <C/DvUpnpOrgContentDirectory1.h>
#include <Core/DvUpnpOrgContentDirectory1.h>
#include <ZappTypes.h>
#include <Buffer.h>
#include <C/DviDeviceC.h>
#include <C/Zapp.h>

using namespace Zapp;

class DvServiceUpnpOrgContentDirectory1C : public DvServiceUpnpOrgContentDirectory1
{
public:
    DvServiceUpnpOrgContentDirectory1C(DvDevice& aDevice);
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

DvServiceUpnpOrgContentDirectory1C::DvServiceUpnpOrgContentDirectory1C(DvDevice& aDevice)
    : DvServiceUpnpOrgContentDirectory1(aDevice)
{
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionGetSearchCapabilities(CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr)
{
    iCallbackGetSearchCapabilities = aCallback;
    iPtrGetSearchCapabilities = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionGetSearchCapabilities();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionGetSortCapabilities(CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr)
{
    iCallbackGetSortCapabilities = aCallback;
    iPtrGetSortCapabilities = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionGetSortCapabilities();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionGetSystemUpdateID(CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr)
{
    iCallbackGetSystemUpdateID = aCallback;
    iPtrGetSystemUpdateID = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionGetSystemUpdateID();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionBrowse(CallbackContentDirectory1Browse aCallback, void* aPtr)
{
    iCallbackBrowse = aCallback;
    iPtrBrowse = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionBrowse();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionSearch(CallbackContentDirectory1Search aCallback, void* aPtr)
{
    iCallbackSearch = aCallback;
    iPtrSearch = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionSearch();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionCreateObject(CallbackContentDirectory1CreateObject aCallback, void* aPtr)
{
    iCallbackCreateObject = aCallback;
    iPtrCreateObject = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionCreateObject();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionDestroyObject(CallbackContentDirectory1DestroyObject aCallback, void* aPtr)
{
    iCallbackDestroyObject = aCallback;
    iPtrDestroyObject = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionDestroyObject();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionUpdateObject(CallbackContentDirectory1UpdateObject aCallback, void* aPtr)
{
    iCallbackUpdateObject = aCallback;
    iPtrUpdateObject = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionUpdateObject();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionImportResource(CallbackContentDirectory1ImportResource aCallback, void* aPtr)
{
    iCallbackImportResource = aCallback;
    iPtrImportResource = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionImportResource();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionExportResource(CallbackContentDirectory1ExportResource aCallback, void* aPtr)
{
    iCallbackExportResource = aCallback;
    iPtrExportResource = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionExportResource();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionStopTransferResource(CallbackContentDirectory1StopTransferResource aCallback, void* aPtr)
{
    iCallbackStopTransferResource = aCallback;
    iPtrStopTransferResource = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionStopTransferResource();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionGetTransferProgress(CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr)
{
    iCallbackGetTransferProgress = aCallback;
    iPtrGetTransferProgress = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionGetTransferProgress();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionDeleteResource(CallbackContentDirectory1DeleteResource aCallback, void* aPtr)
{
    iCallbackDeleteResource = aCallback;
    iPtrDeleteResource = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionDeleteResource();
}

void DvServiceUpnpOrgContentDirectory1C::EnableActionCreateReference(CallbackContentDirectory1CreateReference aCallback, void* aPtr)
{
    iCallbackCreateReference = aCallback;
    iPtrCreateReference = aPtr;
    DvServiceUpnpOrgContentDirectory1::EnableActionCreateReference();
}

void DvServiceUpnpOrgContentDirectory1C::GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps)
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

void DvServiceUpnpOrgContentDirectory1C::GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps)
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

void DvServiceUpnpOrgContentDirectory1C::GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId)
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

void DvServiceUpnpOrgContentDirectory1C::Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvServiceUpnpOrgContentDirectory1C::Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID)
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

void DvServiceUpnpOrgContentDirectory1C::CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult)
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

void DvServiceUpnpOrgContentDirectory1C::DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID)
{
    ASSERT(iCallbackDestroyObject != NULL);
    if (0 != iCallbackDestroyObject(iPtrDestroyObject, aVersion, (const char*)aObjectID.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgContentDirectory1C::UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue)
{
    ASSERT(iCallbackUpdateObject != NULL);
    if (0 != iCallbackUpdateObject(iPtrUpdateObject, aVersion, (const char*)aObjectID.Ptr(), (const char*)aCurrentTagValue.Ptr(), (const char*)aNewTagValue.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgContentDirectory1C::ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
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

void DvServiceUpnpOrgContentDirectory1C::ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID)
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

void DvServiceUpnpOrgContentDirectory1C::StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID)
{
    ASSERT(iCallbackStopTransferResource != NULL);
    if (0 != iCallbackStopTransferResource(iPtrStopTransferResource, aVersion, aTransferID)) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgContentDirectory1C::GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal)
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

void DvServiceUpnpOrgContentDirectory1C::DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI)
{
    ASSERT(iCallbackDeleteResource != NULL);
    if (0 != iCallbackDeleteResource(iPtrDeleteResource, aVersion, (const char*)aResourceURI.Ptr())) {
        aResponse.Error(502, Brn("Action failed"));
        return;
    }
    aResponse.Start();
    aResponse.End();
}

void DvServiceUpnpOrgContentDirectory1C::CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID)
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



THandle DvServiceUpnpOrgContentDirectory1Create(DvDeviceC aDevice)
{
    return (THandle)new DvServiceUpnpOrgContentDirectory1C(*(DviDeviceC::DeviceFromHandle(aDevice)));
}

void DvServiceUpnpOrgContentDirectory1Destroy(THandle aService)
{
    delete reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService);
}

void DvServiceUpnpOrgContentDirectory1EnableActionGetSearchCapabilities(THandle aService, CallbackContentDirectory1GetSearchCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionGetSearchCapabilities(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionGetSortCapabilities(THandle aService, CallbackContentDirectory1GetSortCapabilities aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionGetSortCapabilities(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionGetSystemUpdateID(THandle aService, CallbackContentDirectory1GetSystemUpdateID aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionGetSystemUpdateID(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionBrowse(THandle aService, CallbackContentDirectory1Browse aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionBrowse(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionSearch(THandle aService, CallbackContentDirectory1Search aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionSearch(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionCreateObject(THandle aService, CallbackContentDirectory1CreateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionCreateObject(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionDestroyObject(THandle aService, CallbackContentDirectory1DestroyObject aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionDestroyObject(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionUpdateObject(THandle aService, CallbackContentDirectory1UpdateObject aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionUpdateObject(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionImportResource(THandle aService, CallbackContentDirectory1ImportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionImportResource(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionExportResource(THandle aService, CallbackContentDirectory1ExportResource aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionExportResource(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionStopTransferResource(THandle aService, CallbackContentDirectory1StopTransferResource aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionStopTransferResource(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionGetTransferProgress(THandle aService, CallbackContentDirectory1GetTransferProgress aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionGetTransferProgress(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionDeleteResource(THandle aService, CallbackContentDirectory1DeleteResource aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionDeleteResource(aCallback, aPtr);
}

void DvServiceUpnpOrgContentDirectory1EnableActionCreateReference(THandle aService, CallbackContentDirectory1CreateReference aCallback, void* aPtr)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->EnableActionCreateReference(aCallback, aPtr);
}

int32_t DvServiceUpnpOrgContentDirectory1SetPropertyTransferIDs(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->SetPropertyTransferIDs(buf);
    return 0;
}

void DvServiceUpnpOrgContentDirectory1GetPropertyTransferIDs(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->GetPropertyTransferIDs(buf);
    *aValue = (char*)buf.Transfer();
}

int32_t DvServiceUpnpOrgContentDirectory1SetPropertySystemUpdateID(THandle aService, uint32_t aValue)
{
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->SetPropertySystemUpdateID(aValue);
    return 0;
}

void DvServiceUpnpOrgContentDirectory1GetPropertySystemUpdateID(THandle aService, uint32_t* aValue)
{
    uint32_t val;
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->GetPropertySystemUpdateID(val);
    *aValue = val;
}

int32_t DvServiceUpnpOrgContentDirectory1SetPropertyContainerUpdateIDs(THandle aService, const char* aValue)
{
    Brhz buf(aValue);
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->SetPropertyContainerUpdateIDs(buf);
    return 0;
}

void DvServiceUpnpOrgContentDirectory1GetPropertyContainerUpdateIDs(THandle aService, char** aValue)
{
    Brhz buf;
    reinterpret_cast<DvServiceUpnpOrgContentDirectory1C*>(aService)->GetPropertyContainerUpdateIDs(buf);
    *aValue = (char*)buf.Transfer();
}

