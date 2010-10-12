#include <C/CpUpnpOrgContentDirectory2.h>
#include <Core/CpUpnpOrgContentDirectory2.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgContentDirectory2C : public CpProxyC
{
public:
    CpProxyUpnpOrgContentDirectory2C(CpDeviceC aDevice);
    CpProxyUpnpOrgContentDirectory2* Proxy() { return static_cast<CpProxyUpnpOrgContentDirectory2*>(iProxy); }
};

CpProxyUpnpOrgContentDirectory2C::CpProxyUpnpOrgContentDirectory2C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgContentDirectory2(*iDevice);
}


THandle CpProxyUpnpOrgContentDirectory2Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgContentDirectory2C(aDevice);
}

void CpProxyUpnpOrgContentDirectory2Destroy(THandle aHandle)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgContentDirectory2SyncGetSearchCapabilities(THandle aHandle, char** aSearchCaps)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSearchCaps;
    proxyC->Proxy()->SyncGetSearchCapabilities(buf_aSearchCaps);
    *aSearchCaps = buf_aSearchCaps.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginGetSearchCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSearchCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndGetSearchCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSearchCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncGetSortCapabilities(THandle aHandle, char** aSortCaps)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortCaps;
    proxyC->Proxy()->SyncGetSortCapabilities(buf_aSortCaps);
    *aSortCaps = buf_aSortCaps.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginGetSortCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSortCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndGetSortCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncGetSortExtensionCapabilities(THandle aHandle, char** aSortExtensionCaps)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortExtensionCaps;
    proxyC->Proxy()->SyncGetSortExtensionCapabilities(buf_aSortExtensionCaps);
    *aSortExtensionCaps = buf_aSortExtensionCaps.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginGetSortExtensionCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSortExtensionCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndGetSortExtensionCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortExtensionCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aSortExtensionCaps;
    *aSortExtensionCaps = NULL;
    try {
        proxyC->Proxy()->EndGetSortExtensionCapabilities(*async, buf_aSortExtensionCaps);
        *aSortExtensionCaps = buf_aSortExtensionCaps.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory2SyncGetFeatureList(THandle aHandle, char** aFeatureList)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFeatureList;
    proxyC->Proxy()->SyncGetFeatureList(buf_aFeatureList);
    *aFeatureList = buf_aFeatureList.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginGetFeatureList(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetFeatureList(functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndGetFeatureList(THandle aHandle, ZappHandleAsync aAsync, char** aFeatureList)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aFeatureList;
    *aFeatureList = NULL;
    try {
        proxyC->Proxy()->EndGetFeatureList(*async, buf_aFeatureList);
        *aFeatureList = buf_aFeatureList.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory2SyncGetSystemUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetSystemUpdateID(*aId);
}

void CpProxyUpnpOrgContentDirectory2BeginGetSystemUpdateID(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSystemUpdateID(functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndGetSystemUpdateID(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndBrowse(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndSearch(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    Brh buf_aObjectID;
    Brh buf_aResult;
    proxyC->Proxy()->SyncCreateObject(buf_aContainerID, buf_aElements, buf_aObjectID, buf_aResult);
    *aObjectID = buf_aObjectID.Extract();
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateObject(buf_aContainerID, buf_aElements, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndCreateObject(THandle aHandle, ZappHandleAsync aAsync, char** aObjectID, char** aResult)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncDestroyObject(THandle aHandle, const char* aObjectID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    proxyC->Proxy()->SyncDestroyObject(buf_aObjectID);
}

void CpProxyUpnpOrgContentDirectory2BeginDestroyObject(THandle aHandle, const char* aObjectID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDestroyObject(buf_aObjectID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndDestroyObject(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    proxyC->Proxy()->SyncUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue);
}

void CpProxyUpnpOrgContentDirectory2BeginUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndUpdateObject(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncMoveObject(THandle aHandle, const char* aObjectID, const char* aNewParentID, char** aNewObjectID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewParentID(aNewParentID);
    Brh buf_aNewObjectID;
    proxyC->Proxy()->SyncMoveObject(buf_aObjectID, buf_aNewParentID, buf_aNewObjectID);
    *aNewObjectID = buf_aNewObjectID.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginMoveObject(THandle aHandle, const char* aObjectID, const char* aNewParentID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewParentID(aNewParentID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginMoveObject(buf_aObjectID, buf_aNewParentID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndMoveObject(THandle aHandle, ZappHandleAsync aAsync, char** aNewObjectID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aNewObjectID;
    *aNewObjectID = NULL;
    try {
        proxyC->Proxy()->EndMoveObject(*async, buf_aNewObjectID);
        *aNewObjectID = buf_aNewObjectID.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory2SyncImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    proxyC->Proxy()->SyncImportResource(buf_aSourceURI, buf_aDestinationURI, *aTransferID);
}

void CpProxyUpnpOrgContentDirectory2BeginImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginImportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndImportResource(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    proxyC->Proxy()->SyncExportResource(buf_aSourceURI, buf_aDestinationURI, *aTransferID);
}

void CpProxyUpnpOrgContentDirectory2BeginExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginExportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndExportResource(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncDeleteResource(THandle aHandle, const char* aResourceURI)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    proxyC->Proxy()->SyncDeleteResource(buf_aResourceURI);
}

void CpProxyUpnpOrgContentDirectory2BeginDeleteResource(THandle aHandle, const char* aResourceURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDeleteResource(buf_aResourceURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndDeleteResource(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncStopTransferResource(THandle aHandle, uint32_t aTransferID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStopTransferResource(aTransferID);
}

void CpProxyUpnpOrgContentDirectory2BeginStopTransferResource(THandle aHandle, uint32_t aTransferID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStopTransferResource(aTransferID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndStopTransferResource(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncGetTransferProgress(THandle aHandle, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTransferStatus;
    Brh buf_aTransferLength;
    Brh buf_aTransferTotal;
    proxyC->Proxy()->SyncGetTransferProgress(aTransferID, buf_aTransferStatus, buf_aTransferLength, buf_aTransferTotal);
    *aTransferStatus = buf_aTransferStatus.Extract();
    *aTransferLength = buf_aTransferLength.Extract();
    *aTransferTotal = buf_aTransferTotal.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginGetTransferProgress(THandle aHandle, uint32_t aTransferID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetTransferProgress(aTransferID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndGetTransferProgress(THandle aHandle, ZappHandleAsync aAsync, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SyncCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, char** aNewID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewID;
    proxyC->Proxy()->SyncCreateReference(buf_aContainerID, buf_aObjectID, buf_aNewID);
    *aNewID = buf_aNewID.Extract();
}

void CpProxyUpnpOrgContentDirectory2BeginCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateReference(buf_aContainerID, buf_aObjectID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory2EndCreateReference(THandle aHandle, ZappHandleAsync aAsync, char** aNewID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory2SetPropertySystemUpdateIDChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySystemUpdateIDChanged(functor);
}

void CpProxyUpnpOrgContentDirectory2SetPropertyContainerUpdateIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyContainerUpdateIDsChanged(functor);
}

void CpProxyUpnpOrgContentDirectory2SetPropertyTransferIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTransferIDsChanged(functor);
}

void CpProxyUpnpOrgContentDirectory2PropertySystemUpdateID(THandle aHandle, uint32_t* aSystemUpdateID)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertySystemUpdateID(*aSystemUpdateID);
}

void CpProxyUpnpOrgContentDirectory2PropertyContainerUpdateIDs(THandle aHandle, char** aContainerUpdateIDs)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aContainerUpdateIDs;
    proxyC->Proxy()->PropertyContainerUpdateIDs(buf_aContainerUpdateIDs);
    *aContainerUpdateIDs = buf_aContainerUpdateIDs.Transfer();
}

void CpProxyUpnpOrgContentDirectory2PropertyTransferIDs(THandle aHandle, char** aTransferIDs)
{
    CpProxyUpnpOrgContentDirectory2C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory2C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransferIDs;
    proxyC->Proxy()->PropertyTransferIDs(buf_aTransferIDs);
    *aTransferIDs = buf_aTransferIDs.Transfer();
}

