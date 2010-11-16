#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY1CPP
#define HEADER_DVUPNPORGCONTENTDIRECTORY1CPP

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
 * Base Device for upnp.org:ContentDirectory:1
 */
class DvProviderUpnpOrgContentDirectory1Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgContentDirectory1Cpp() {}
    bool SetPropertyTransferIDs(const std::string& aValue);
    void GetPropertyTransferIDs(std::string& aValue);
    bool SetPropertySystemUpdateID(uint32_t aValue);
    void GetPropertySystemUpdateID(uint32_t& aValue);
    bool SetPropertyContainerUpdateIDs(const std::string& aValue);
    void GetPropertyContainerUpdateIDs(std::string& aValue);
protected:
    DvProviderUpnpOrgContentDirectory1Cpp(DvDeviceStd& aDevice);
    void EnableActionGetSearchCapabilities();
    void EnableActionGetSortCapabilities();
    void EnableActionGetSystemUpdateID();
    void EnableActionBrowse();
    void EnableActionSearch();
    void EnableActionCreateObject();
    void EnableActionDestroyObject();
    void EnableActionUpdateObject();
    void EnableActionImportResource();
    void EnableActionExportResource();
    void EnableActionStopTransferResource();
    void EnableActionGetTransferProgress();
    void EnableActionDeleteResource();
    void EnableActionCreateReference();
private:
    virtual void GetSearchCapabilities(uint32_t aVersion, std::string& aSearchCaps);
    virtual void GetSortCapabilities(uint32_t aVersion, std::string& aSortCaps);
    virtual void GetSystemUpdateID(uint32_t aVersion, uint32_t& aId);
    virtual void Browse(uint32_t aVersion, const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void Search(uint32_t aVersion, const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    virtual void CreateObject(uint32_t aVersion, const std::string& aContainerID, const std::string& aElements, std::string& aObjectID, std::string& aResult);
    virtual void DestroyObject(uint32_t aVersion, const std::string& aObjectID);
    virtual void UpdateObject(uint32_t aVersion, const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue);
    virtual void ImportResource(uint32_t aVersion, const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
    virtual void ExportResource(uint32_t aVersion, const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
    virtual void StopTransferResource(uint32_t aVersion, uint32_t aTransferID);
    virtual void GetTransferProgress(uint32_t aVersion, uint32_t aTransferID, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);
    virtual void DeleteResource(uint32_t aVersion, const std::string& aResourceURI);
    virtual void CreateReference(uint32_t aVersion, const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID);
private:
    DvProviderUpnpOrgContentDirectory1Cpp();
    void DoGetSearchCapabilities(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetSortCapabilities(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoBrowse(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoSearch(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCreateObject(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDestroyObject(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoUpdateObject(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoImportResource(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoExportResource(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoStopTransferResource(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoGetTransferProgress(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteResource(IDviInvocation& aInvocation, uint32_t aVersion);
    void DoCreateReference(IDviInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyTransferIDs;
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY1CPP

