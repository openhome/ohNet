#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY1CPP
#define HEADER_DVUPNPORGCONTENTDIRECTORY1CPP

#include <ZappTypes.h>
#include <Buffer.h>
#include <Std/DvDevice.h>
#include <DvService.h>

#include <string>

namespace Zapp {

class IDvInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for upnp.org:ContentDirectory:1
 */
class DvServiceUpnpOrgContentDirectory1Cpp : public DvService
{
public:
    virtual ~DvServiceUpnpOrgContentDirectory1Cpp() {}
    void SetPropertyTransferIDs(const std::string& aValue);
    void GetPropertyTransferIDs(std::string& aValue);
    void SetPropertySystemUpdateID(uint32_t aValue);
    void GetPropertySystemUpdateID(uint32_t& aValue);
    void SetPropertyContainerUpdateIDs(const std::string& aValue);
    void GetPropertyContainerUpdateIDs(std::string& aValue);
protected:
    DvServiceUpnpOrgContentDirectory1Cpp(DvDeviceStd& aDevice);
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
    DvServiceUpnpOrgContentDirectory1Cpp();
    void DoGetSearchCapabilities(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetSortCapabilities(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetSystemUpdateID(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoBrowse(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoSearch(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoCreateObject(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDestroyObject(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoUpdateObject(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoImportResource(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoExportResource(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoStopTransferResource(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoGetTransferProgress(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoDeleteResource(IDvInvocation& aInvocation, uint32_t aVersion);
    void DoCreateReference(IDvInvocation& aInvocation, uint32_t aVersion);
private:
    PropertyString* iPropertyTransferIDs;
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY1CPP

