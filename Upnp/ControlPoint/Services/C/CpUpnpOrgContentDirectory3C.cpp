#include <C/CpUpnpOrgContentDirectory3.h>
#include <Core/CpUpnpOrgContentDirectory3.h>
#include <Core/CpDevice.h>
#include <C/CpProxyCPrivate.h>
#include <FunctorAsync.h>

using namespace Zapp;

class CpProxyUpnpOrgContentDirectory3C : public CpProxyC
{
public:
    CpProxyUpnpOrgContentDirectory3C(CpDeviceC aDevice);
    CpProxyUpnpOrgContentDirectory3* Proxy() { return static_cast<CpProxyUpnpOrgContentDirectory3*>(iProxy); }
};

CpProxyUpnpOrgContentDirectory3C::CpProxyUpnpOrgContentDirectory3C(CpDeviceC aDevice)
    : CpProxyC(*reinterpret_cast<CpiDevice*>(aDevice))
{
    iProxy = new CpProxyUpnpOrgContentDirectory3(*iDevice);
}


THandle CpProxyUpnpOrgContentDirectory3Create(CpDeviceC aDevice)
{
    return (THandle)new CpProxyUpnpOrgContentDirectory3C(aDevice);
}

void CpProxyUpnpOrgContentDirectory3Destroy(THandle aHandle)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    delete proxyC;
}

void CpProxyUpnpOrgContentDirectory3SyncGetSearchCapabilities(THandle aHandle, char** aSearchCaps)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSearchCaps;
    proxyC->Proxy()->SyncGetSearchCapabilities(buf_aSearchCaps);
    *aSearchCaps = buf_aSearchCaps.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginGetSearchCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSearchCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndGetSearchCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSearchCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncGetSortCapabilities(THandle aHandle, char** aSortCaps)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortCaps;
    proxyC->Proxy()->SyncGetSortCapabilities(buf_aSortCaps);
    *aSortCaps = buf_aSortCaps.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginGetSortCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSortCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndGetSortCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncGetSortExtensionCapabilities(THandle aHandle, char** aSortExtensionCaps)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSortExtensionCaps;
    proxyC->Proxy()->SyncGetSortExtensionCapabilities(buf_aSortExtensionCaps);
    *aSortExtensionCaps = buf_aSortExtensionCaps.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginGetSortExtensionCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSortExtensionCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndGetSortExtensionCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aSortExtensionCaps)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncGetFeatureList(THandle aHandle, char** aFeatureList)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFeatureList;
    proxyC->Proxy()->SyncGetFeatureList(buf_aFeatureList);
    *aFeatureList = buf_aFeatureList.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginGetFeatureList(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetFeatureList(functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndGetFeatureList(THandle aHandle, ZappHandleAsync aAsync, char** aFeatureList)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncGetSystemUpdateID(THandle aHandle, uint32_t* aId)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncGetSystemUpdateID(*aId);
}

void CpProxyUpnpOrgContentDirectory3BeginGetSystemUpdateID(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetSystemUpdateID(functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndGetSystemUpdateID(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aId)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncGetServiceResetToken(THandle aHandle, char** aResetToken)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResetToken;
    proxyC->Proxy()->SyncGetServiceResetToken(buf_aResetToken);
    *aResetToken = buf_aResetToken.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginGetServiceResetToken(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetServiceResetToken(functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndGetServiceResetToken(THandle aHandle, ZappHandleAsync aAsync, char** aResetToken)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aResetToken;
    *aResetToken = NULL;
    try {
        proxyC->Proxy()->EndGetServiceResetToken(*async, buf_aResetToken);
        *aResetToken = buf_aResetToken.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory3SyncBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginBrowse(THandle aHandle, const char* aObjectID, const char* aBrowseFlag, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aBrowseFlag(aBrowseFlag);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginBrowse(buf_aObjectID, buf_aBrowseFlag, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndBrowse(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    Brh buf_aResult;
    proxyC->Proxy()->SyncSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, buf_aResult, *aNumberReturned, *aTotalMatches, *aUpdateID);
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginSearch(THandle aHandle, const char* aContainerID, const char* aSearchCriteria, const char* aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const char* aSortCriteria, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aSearchCriteria(aSearchCriteria);
    Brh buf_aFilter(aFilter);
    Brh buf_aSortCriteria(aSortCriteria);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginSearch(buf_aContainerID, buf_aSearchCriteria, buf_aFilter, aStartingIndex, aRequestedCount, buf_aSortCriteria, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndSearch(THandle aHandle, ZappHandleAsync aAsync, char** aResult, uint32_t* aNumberReturned, uint32_t* aTotalMatches, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, char** aObjectID, char** aResult)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    Brh buf_aObjectID;
    Brh buf_aResult;
    proxyC->Proxy()->SyncCreateObject(buf_aContainerID, buf_aElements, buf_aObjectID, buf_aResult);
    *aObjectID = buf_aObjectID.Extract();
    *aResult = buf_aResult.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginCreateObject(THandle aHandle, const char* aContainerID, const char* aElements, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aElements(aElements);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateObject(buf_aContainerID, buf_aElements, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndCreateObject(THandle aHandle, ZappHandleAsync aAsync, char** aObjectID, char** aResult)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncDestroyObject(THandle aHandle, const char* aObjectID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    proxyC->Proxy()->SyncDestroyObject(buf_aObjectID);
}

void CpProxyUpnpOrgContentDirectory3BeginDestroyObject(THandle aHandle, const char* aObjectID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDestroyObject(buf_aObjectID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndDestroyObject(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    proxyC->Proxy()->SyncUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue);
}

void CpProxyUpnpOrgContentDirectory3BeginUpdateObject(THandle aHandle, const char* aObjectID, const char* aCurrentTagValue, const char* aNewTagValue, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aCurrentTagValue(aCurrentTagValue);
    Brh buf_aNewTagValue(aNewTagValue);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginUpdateObject(buf_aObjectID, buf_aCurrentTagValue, buf_aNewTagValue, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndUpdateObject(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncMoveObject(THandle aHandle, const char* aObjectID, const char* aNewParentID, char** aNewObjectID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewParentID(aNewParentID);
    Brh buf_aNewObjectID;
    proxyC->Proxy()->SyncMoveObject(buf_aObjectID, buf_aNewParentID, buf_aNewObjectID);
    *aNewObjectID = buf_aNewObjectID.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginMoveObject(THandle aHandle, const char* aObjectID, const char* aNewParentID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewParentID(aNewParentID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginMoveObject(buf_aObjectID, buf_aNewParentID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndMoveObject(THandle aHandle, ZappHandleAsync aAsync, char** aNewObjectID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    proxyC->Proxy()->SyncImportResource(buf_aSourceURI, buf_aDestinationURI, *aTransferID);
}

void CpProxyUpnpOrgContentDirectory3BeginImportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginImportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndImportResource(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, uint32_t* aTransferID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    proxyC->Proxy()->SyncExportResource(buf_aSourceURI, buf_aDestinationURI, *aTransferID);
}

void CpProxyUpnpOrgContentDirectory3BeginExportResource(THandle aHandle, const char* aSourceURI, const char* aDestinationURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aSourceURI(aSourceURI);
    Brh buf_aDestinationURI(aDestinationURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginExportResource(buf_aSourceURI, buf_aDestinationURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndExportResource(THandle aHandle, ZappHandleAsync aAsync, uint32_t* aTransferID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncDeleteResource(THandle aHandle, const char* aResourceURI)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    proxyC->Proxy()->SyncDeleteResource(buf_aResourceURI);
}

void CpProxyUpnpOrgContentDirectory3BeginDeleteResource(THandle aHandle, const char* aResourceURI, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aResourceURI(aResourceURI);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginDeleteResource(buf_aResourceURI, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndDeleteResource(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncStopTransferResource(THandle aHandle, uint32_t aTransferID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->SyncStopTransferResource(aTransferID);
}

void CpProxyUpnpOrgContentDirectory3BeginStopTransferResource(THandle aHandle, uint32_t aTransferID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginStopTransferResource(aTransferID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndStopTransferResource(THandle aHandle, ZappHandleAsync aAsync)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncGetTransferProgress(THandle aHandle, uint32_t aTransferID, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aTransferStatus;
    Brh buf_aTransferLength;
    Brh buf_aTransferTotal;
    proxyC->Proxy()->SyncGetTransferProgress(aTransferID, buf_aTransferStatus, buf_aTransferLength, buf_aTransferTotal);
    *aTransferStatus = buf_aTransferStatus.Extract();
    *aTransferLength = buf_aTransferLength.Extract();
    *aTransferTotal = buf_aTransferTotal.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginGetTransferProgress(THandle aHandle, uint32_t aTransferID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetTransferProgress(aTransferID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndGetTransferProgress(THandle aHandle, ZappHandleAsync aAsync, char** aTransferStatus, char** aTransferLength, char** aTransferTotal)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, char** aNewID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    Brh buf_aNewID;
    proxyC->Proxy()->SyncCreateReference(buf_aContainerID, buf_aObjectID, buf_aNewID);
    *aNewID = buf_aNewID.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginCreateReference(THandle aHandle, const char* aContainerID, const char* aObjectID, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aObjectID(aObjectID);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginCreateReference(buf_aContainerID, buf_aObjectID, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndCreateReference(THandle aHandle, ZappHandleAsync aAsync, char** aNewID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
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

void CpProxyUpnpOrgContentDirectory3SyncFreeFormQuery(THandle aHandle, const char* aContainerID, uint32_t aCDSView, const char* aQueryRequest, char** aQueryResult, uint32_t* aUpdateID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aQueryRequest(aQueryRequest);
    Brh buf_aQueryResult;
    proxyC->Proxy()->SyncFreeFormQuery(buf_aContainerID, aCDSView, buf_aQueryRequest, buf_aQueryResult, *aUpdateID);
    *aQueryResult = buf_aQueryResult.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginFreeFormQuery(THandle aHandle, const char* aContainerID, uint32_t aCDSView, const char* aQueryRequest, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aContainerID(aContainerID);
    Brh buf_aQueryRequest(aQueryRequest);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginFreeFormQuery(buf_aContainerID, aCDSView, buf_aQueryRequest, functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndFreeFormQuery(THandle aHandle, ZappHandleAsync aAsync, char** aQueryResult, uint32_t* aUpdateID)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aQueryResult;
    *aQueryResult = NULL;
    try {
        proxyC->Proxy()->EndFreeFormQuery(*async, buf_aQueryResult, *aUpdateID);
        *aQueryResult = buf_aQueryResult.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory3SyncGetFreeFormQueryCapabilities(THandle aHandle, char** aFFQCapabilities)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brh buf_aFFQCapabilities;
    proxyC->Proxy()->SyncGetFreeFormQueryCapabilities(buf_aFFQCapabilities);
    *aFFQCapabilities = buf_aFFQCapabilities.Extract();
}

void CpProxyUpnpOrgContentDirectory3BeginGetFreeFormQueryCapabilities(THandle aHandle, ZappCallbackAsync aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    FunctorAsync functor = MakeFunctorAsync(aPtr, (ZappFunctorAsync)aCallback);
    proxyC->Proxy()->BeginGetFreeFormQueryCapabilities(functor);
}

int32_t CpProxyUpnpOrgContentDirectory3EndGetFreeFormQueryCapabilities(THandle aHandle, ZappHandleAsync aAsync, char** aFFQCapabilities)
{
    int32_t err = 0;
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    IAsync* async = reinterpret_cast<IAsync*>(aAsync);
    ASSERT(async != NULL);
    Brh buf_aFFQCapabilities;
    *aFFQCapabilities = NULL;
    try {
        proxyC->Proxy()->EndGetFreeFormQueryCapabilities(*async, buf_aFFQCapabilities);
        *aFFQCapabilities = buf_aFFQCapabilities.Extract();
    }
    catch(...) {
        err = -1;
    }
    return err;
}

void CpProxyUpnpOrgContentDirectory3SetPropertySystemUpdateIDChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertySystemUpdateIDChanged(functor);
}

void CpProxyUpnpOrgContentDirectory3SetPropertyContainerUpdateIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyContainerUpdateIDsChanged(functor);
}

void CpProxyUpnpOrgContentDirectory3SetPropertyLastChangeChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyLastChangeChanged(functor);
}

void CpProxyUpnpOrgContentDirectory3SetPropertyTransferIDsChanged(THandle aHandle, ZappCallback aCallback, void* aPtr)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Functor functor = MakeFunctor(aPtr, aCallback);
    proxyC->Proxy()->SetPropertyTransferIDsChanged(functor);
}

void CpProxyUpnpOrgContentDirectory3PropertySystemUpdateID(THandle aHandle, uint32_t* aSystemUpdateID)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    proxyC->Proxy()->PropertySystemUpdateID(*aSystemUpdateID);
}

void CpProxyUpnpOrgContentDirectory3PropertyContainerUpdateIDs(THandle aHandle, char** aContainerUpdateIDs)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aContainerUpdateIDs;
    proxyC->Proxy()->PropertyContainerUpdateIDs(buf_aContainerUpdateIDs);
    *aContainerUpdateIDs = buf_aContainerUpdateIDs.Transfer();
}

void CpProxyUpnpOrgContentDirectory3PropertyLastChange(THandle aHandle, char** aLastChange)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aLastChange;
    proxyC->Proxy()->PropertyLastChange(buf_aLastChange);
    *aLastChange = buf_aLastChange.Transfer();
}

void CpProxyUpnpOrgContentDirectory3PropertyTransferIDs(THandle aHandle, char** aTransferIDs)
{
    CpProxyUpnpOrgContentDirectory3C* proxyC = reinterpret_cast<CpProxyUpnpOrgContentDirectory3C*>(aHandle);
    ASSERT(proxyC != NULL);
    Brhz buf_aTransferIDs;
    proxyC->Proxy()->PropertyTransferIDs(buf_aTransferIDs);
    *aTransferIDs = buf_aTransferIDs.Transfer();
}

