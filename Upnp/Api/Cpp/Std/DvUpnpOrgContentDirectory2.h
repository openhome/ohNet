#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY2CPP
#define HEADER_DVUPNPORGCONTENTDIRECTORY2CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvProvider.h>

#include <string>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ContentDirectory:2
 */
class DvProviderUpnpOrgContentDirectory2Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgContentDirectory2Cpp() {}
    bool SetPropertySystemUpdateID(uint32_t aValue);
    void GetPropertySystemUpdateID(uint32_t& aValue);
    bool SetPropertyContainerUpdateIDs(const std::string& aValue);
    void GetPropertyContainerUpdateIDs(std::string& aValue);
    bool SetPropertyTransferIDs(const std::string& aValue);
    void GetPropertyTransferIDs(std::string& aValue);
protected:
    DvProviderUpnpOrgContentDirectory2Cpp(DvDeviceStd& aDevice);
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
    virtual void GetSearchCapabilities(uint32_t aVersion, std::string& aSearchCaps);
    virtual void GetSortCapabilities(uint32_t aVersion, std::string& aSortCaps);
    virtual void GetSortExtensionCapabilities(uint32_t aVersion, std::string& aSortExtensionCaps);
    virtual void GetFeatureList(uint32_t aVersion, std::string& aFeatureList);
    virtual void GetSystemUpdateID(uint32_t aVersion, uint32_t& aId);
    virtual void Browse(uint32_t aVersion, const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void Search(uint32_t aVersion, const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CreateObject(uint32_t aVersion, const std::string& aContainerID, const std::string& aElements, std::string& aObjectID, std::string& aResult);
    virtual void DestroyObject(uint32_t aVersion, const std::string& aObjectID);
    virtual void UpdateObject(uint32_t aVersion, const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue);
    virtual void MoveObject(uint32_t aVersion, const std::string& aObjectID, const std::string& aNewParentID, std::string& aNewObjectID);
    virtual void ImportResource(uint32_t aVersion, const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
    virtual void ExportResource(uint32_t aVersion, const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
    virtual void DeleteResource(uint32_t aVersion, const std::string& aResourceURI);
    virtual void StopTransferResource(uint32_t aVersion, uint32_t aTransferID);
    virtual void GetTransferProgress(uint32_t aVersion, uint32_t aTransferID, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);
    virtual void CreateReference(uint32_t aVersion, const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID);
private:
    DvProviderUpnpOrgContentDirectory2Cpp();
    void DoGetSearchCapabilities(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetSortCapabilities(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetSortExtensionCapabilities(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetFeatureList(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBrowse(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSearch(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCreateObject(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDestroyObject(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoUpdateObject(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoMoveObject(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoImportResource(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoExportResource(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteResource(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStopTransferResource(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetTransferProgress(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCreateReference(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
    PropertyString* iPropertyTransferIDs;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY2CPP

