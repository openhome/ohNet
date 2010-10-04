#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY2
#define HEADER_DVUPNPORGCONTENTDIRECTORY2

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvService.h>

namespace Zapp {

class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ContentDirectory:2
 */
class DvServiceUpnpOrgContentDirectory2 : public DvService
{
public:
    virtual ~DvServiceUpnpOrgContentDirectory2() {}
    void SetPropertySystemUpdateID(TUint aValue);
    void GetPropertySystemUpdateID(TUint& aValue);
    void SetPropertyContainerUpdateIDs(const Brx& aValue);
    void GetPropertyContainerUpdateIDs(Brhz& aValue);
    void SetPropertyTransferIDs(const Brx& aValue);
    void GetPropertyTransferIDs(Brhz& aValue);
protected:
    DvServiceUpnpOrgContentDirectory2(DvDevice& aDevice);
    void EnableActionGetSearchCapabilities();
    void EnableActionGetSortCapabilities();
    void EnableActionGetSortExtensionCapabilities();
    void EnableActionGetFeatureList();
    void EnableActionGetSystemUpdateID();
    void EnableActionBrowse();
    void EnableActionSearch();
    void EnableActionCreateObject();
    void EnableActionDestroyObject();
    void EnableActionUpdateObject();
    void EnableActionMoveObject();
    void EnableActionImportResource();
    void EnableActionExportResource();
    void EnableActionDeleteResource();
    void EnableActionStopTransferResource();
    void EnableActionGetTransferProgress();
    void EnableActionCreateReference();
private:
    virtual void GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps);
    virtual void GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps);
    virtual void GetSortExtensionCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortExtensionCaps);
    virtual void GetFeatureList(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFeatureList);
    virtual void GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId);
    virtual void Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    virtual void Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    virtual void CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult);
    virtual void DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID);
    virtual void UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue);
    virtual void MoveObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aNewParentID, IInvocationResponseString& aNewObjectID);
    virtual void ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID);
    virtual void ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID);
    virtual void DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI);
    virtual void StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID);
    virtual void GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal);
    virtual void CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID);
private:
    DvServiceUpnpOrgContentDirectory2();
    void DoGetSearchCapabilities(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetSortCapabilities(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetSortExtensionCapabilities(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetFeatureList(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetSystemUpdateID(IDvInvocation& aInvocation, TUint aVersion);
    void DoBrowse(IDvInvocation& aInvocation, TUint aVersion);
    void DoSearch(IDvInvocation& aInvocation, TUint aVersion);
    void DoCreateObject(IDvInvocation& aInvocation, TUint aVersion);
    void DoDestroyObject(IDvInvocation& aInvocation, TUint aVersion);
    void DoUpdateObject(IDvInvocation& aInvocation, TUint aVersion);
    void DoMoveObject(IDvInvocation& aInvocation, TUint aVersion);
    void DoImportResource(IDvInvocation& aInvocation, TUint aVersion);
    void DoExportResource(IDvInvocation& aInvocation, TUint aVersion);
    void DoDeleteResource(IDvInvocation& aInvocation, TUint aVersion);
    void DoStopTransferResource(IDvInvocation& aInvocation, TUint aVersion);
    void DoGetTransferProgress(IDvInvocation& aInvocation, TUint aVersion);
    void DoCreateReference(IDvInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
    PropertyString* iPropertyTransferIDs;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY2

