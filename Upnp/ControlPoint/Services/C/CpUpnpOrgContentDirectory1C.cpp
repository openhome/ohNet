#include <C/CpUpnpOrgContentDirectory1.h>
#include <Core/CpUpnpOrgContentDirectory1.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgContentDirectory1C : public CpProxyC
{
public:
    CpProxyUpnpOrgContentDirectory1C(CpDeviceC aDevice);
    CpProxyUpnpOrgContentDirectory1* Proxy() { return static_cast<CpProxyUpnpOrgContentDirectory1*>(iProxy); }
};

CpProxyUpnpOrgContentDirectory1C::CpProxyUpnpOrgContentDirectory1C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgContentDirectory1(*iDevice);
}


THandle CpProxyUpnpOrgContentDirectory1Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgContentDirectory1C(aDevice);
}

void CpProxyUpnpOrgContentDirectory1Destroy(THandle aHandle)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgContentDirectory1SyncGetSearchCapabilities(THandle aHandle, char** aSearchCaps)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSearchCaps;
    proxyC->Proxy()->SyncGetSearchCapabilities(buf_aSearchCaps);
    *aSearchCaps = buf_aSearchCaps.Extract();
}

void CpProxyUpnpOrgContentDirectory1BeginGetSearchCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSearchCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndGetSearchCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSearchCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSearchCaps;
    *aSearchCaps = NULL;
    try {
        proxyC->Proxy()->EndGetSearchCapabilities(*async, buf_aSearchCaps);
        *aSearchCaps = buf_aSearchCaps.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncGetSortCapabilities(THandle aHandle, char** aSortCaps)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortCaps;
    proxyC->Proxy()->SyncGetSortCapabilities(buf_aSortCaps);
    *aSortCaps = buf_aSortCaps.Extract();
}

void CpProxyUpnpOrgContentDirectory1BeginGetSortCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSortCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndGetSortCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSortCaps;
    *aSortCaps = NULL;
    try {
        proxyC->Proxy()->EndGetSortCapabilities(*async, buf_aSortCaps);
        *aSortCaps = buf_aSortCaps.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncGetSystemUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetSystemUpdateID(*aId);
}

void CpProxyUpnpOrgContentDirectory1BeginGetSystemUpdateID(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSystemUpdateID(functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndGetSystemUpdateID(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndGetSystemUpdateID(*async, *aId);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory1BeginBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndBrowse(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndBrowse(*async, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory1BeginSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndSearch(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndSearch(*async, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    Brh buf_aObjectID;
    Brh buf_aResult;
    proxyC->Proxy()->SyncCreateObject(buf_aContainerID, buf_aElements, buf_aObjectID, buf_aResult);
    *aObjectID = buf_aObjectID.Extract();
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory1BeginCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateObject(buf_aContainerID, buf_aElements, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndCreateObject(THandle aHandle, ZappHandleAsync aAsync, char** aObjectID, char** aResult)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aObjectID;
    *aObjectID = NULL;
    Brh buf_aResult;
    *aResult = NULL;
    try {
        proxyC->Proxy()->EndCreateObject(*async, buf_aObjectID, buf_aResult);
        *aObjectID = buf_aObjectID.Extract();
        *aResult = buf_aResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncDestroyObject(THandle aHandle, const char* aObjectID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    proxyC->Proxy()->SyncDestroyObject(buf_aObjectID);
}

void CpProxyUpnpOrgContentDirectory1BeginDestroyObject(THandle aHandle, const char* aObjectID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDestroyObject(buf_aObjectID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndDestroyObject(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDestroyObject(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    proxyC->Proxy()->SyncUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue);
}

void CpProxyUpnpOrgContentDirectory1BeginUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndUpdateObject(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndUpdateObject(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    proxyC->Proxy()->SyncImportResource(buf_aSourceURI, buf_aDestinationURI, *aTransferID);
}

void CpProxyUpnpOrgContentDirectory1BeginImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginImportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndImportResource(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndImportResource(*async, *aTransferID);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    proxyC->Proxy()->SyncExportResource(buf_aSourceURI, buf_aDestinationURI, *aTransferID);
}

void CpProxyUpnpOrgContentDirectory1BeginExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginExportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndExportResource(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndExportResource(*async, *aTransferID);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncStopTransferResource(THandle aHandle, uint32_t aTransferID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStopTransferResource(aTransferID);
}

void CpProxyUpnpOrgContentDirectory1BeginStopTransferResource(THandle aHandle, uint32_t aTransferID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStopTransferResource(aTransferID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndStopTransferResource(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndStopTransferResource(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncGetTransferProgress(THandle aHandle, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTransferStatus;
    Brh buf_aTransferLength;
    Brh buf_aTransferTotal;
    proxyC->Proxy()->SyncGetTransferProgress(aTransferID, buf_aTransferStatus, buf_aTransferLength, buf_aTransferTotal);
    *aTransferStatus = buf_aTransferStatus.Extract();
    *aTransferLength = buf_aTransferLength.Extract();
    *aTransferTotal = buf_aTransferTotal.Extract();
}

void CpProxyUpnpOrgContentDirectory1BeginGetTransferProgress(THandle aHandle, uint32_t aTransferID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetTransferProgress(aTransferID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndGetTransferProgress(THandle aHandle, ZappHandleAsync aAsync, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aTransferStatus;
    *aTransferStatus = NULL;
    Brh buf_aTransferLength;
    *aTransferLength = NULL;
    Brh buf_aTransferTotal;
    *aTransferTotal = NULL;
    try {
        proxyC->Proxy()->EndGetTransferProgress(*async, buf_aTransferStatus, buf_aTransferLength, buf_aTransferTotal);
        *aTransferStatus = buf_aTransferStatus.Extract();
        *aTransferLength = buf_aTransferLength.Extract();
        *aTransferTotal = buf_aTransferTotal.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncDeleteResource(THandle aHandle, const char* aResourceURI)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    proxyC->Proxy()->SyncDeleteResource(buf_aResourceURI);
}

void CpProxyUpnpOrgContentDirectory1BeginDeleteResource(THandle aHandle, const char* aResourceURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDeleteResource(buf_aResourceURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndDeleteResource(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    try {
        proxyC->Proxy()->EndDeleteResource(*async);
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SyncCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, char** aNewID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewID;
    proxyC->Proxy()->SyncCreateReference(buf_aContainerID, buf_aObjectID, buf_aNewID);
    *aNewID = buf_aNewID.Extract();
}

void CpProxyUpnpOrgContentDirectory1BeginCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateReference(buf_aContainerID, buf_aObjectID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory1EndCreateReference(THandle aHandle, ZappHandleAsync aAsync, char** aNewID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aNewID;
    *aNewID = NULL;
    try {
        proxyC->Proxy()->EndCreateReference(*async, buf_aNewID);
        *aNewID = buf_aNewID.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory1SetPropertyTransferIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTransferIDsChanged(functor);
}

void CpProxyUpnpOrgContentDirectory1SetPropertySystemUpdateIDChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySystemUpdateIDChanged(functor);
}

void CpProxyUpnpOrgContentDirectory1SetPropertyContainerUpdateIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyContainerUpdateIDsChanged(functor);
}

void CpProxyUpnpOrgContentDirectory1PropertyTransferIDs(THandle aHandle, char** aTransferIDs)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransferIDs;
    proxyC->Proxy()->PropertyTransferIDs(buf_aTransferIDs);
    *aTransferIDs = buf_aTransferIDs.Transfer();
}

void CpProxyUpnpOrgContentDirectory1PropertySystemUpdateID(THandle aHandle, uint32_t* aSystemUpdateID)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertySystemUpdateID(*aSystemUpdateID);
}

void CpProxyUpnpOrgContentDirectory1PropertyContainerUpdateIDs(THandle aHandle, char** aContainerUpdateIDs)
{
    CpProxyUpnpOrgContentDirectory1C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory1C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aContainerUpdateIDs;
    proxyC->Proxy()->PropertyContainerUpdateIDs(buf_aContainerUpdateIDs);
    *aContainerUpdateIDs = buf_aContainerUpdateIDs.Transfer();
}

