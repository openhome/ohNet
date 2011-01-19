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
 * Provider for the upnp.org:ContentDirectory:2 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgContentDirectory2Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgContentDirectory2Cpp() {}
    /**
     * Set the value of the SystemUpdateID property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySystemUpdateID(uint32_t aValue);
    /**
     * Get a copy of the value of the SystemUpdateID property
     */
    void GetPropertySystemUpdateID(uint32_t& aValue);
    /**
     * Set the value of the ContainerUpdateIDs property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyContainerUpdateIDs(const std::string& aValue);
    /**
     * Get a copy of the value of the ContainerUpdateIDs property
     */
    void GetPropertyContainerUpdateIDs(std::string& aValue);
    /**
     * Set the value of the TransferIDs property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTransferIDs(const std::string& aValue);
    /**
     * Get a copy of the value of the TransferIDs property
     */
    void GetPropertyTransferIDs(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgContentDirectory2Cpp(DvDeviceStd& aDevice);
    /**
     * Signal that the action GetSearchCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * GetSearchCapabilities must be overridden if this is called.
     */
    void EnableActionGetSearchCapabilities();
    /**
     * Signal that the action GetSortCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * GetSortCapabilities must be overridden if this is called.
     */
    void EnableActionGetSortCapabilities();
    /**
     * Signal that the action GetSortExtensionCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * GetSortExtensionCapabilities must be overridden if this is called.
     */
    void EnableActionGetSortExtensionCapabilities();
    /**
     * Signal that the action GetFeatureList is supported.
     * The action's availability will be published in the device's service.xml.
     * GetFeatureList must be overridden if this is called.
     */
    void EnableActionGetFeatureList();
    /**
     * Signal that the action GetSystemUpdateID is supported.
     * The action's availability will be published in the device's service.xml.
     * GetSystemUpdateID must be overridden if this is called.
     */
    void EnableActionGetSystemUpdateID();
    /**
     * Signal that the action Browse is supported.
     * The action's availability will be published in the device's service.xml.
     * Browse must be overridden if this is called.
     */
    void EnableActionBrowse();
    /**
     * Signal that the action Search is supported.
     * The action's availability will be published in the device's service.xml.
     * Search must be overridden if this is called.
     */
    void EnableActionSearch();
    /**
     * Signal that the action CreateObject is supported.
     * The action's availability will be published in the device's service.xml.
     * CreateObject must be overridden if this is called.
     */
    void EnableActionCreateObject();
    /**
     * Signal that the action DestroyObject is supported.
     * The action's availability will be published in the device's service.xml.
     * DestroyObject must be overridden if this is called.
     */
    void EnableActionDestroyObject();
    /**
     * Signal that the action UpdateObject is supported.
     * The action's availability will be published in the device's service.xml.
     * UpdateObject must be overridden if this is called.
     */
    void EnableActionUpdateObject();
    /**
     * Signal that the action MoveObject is supported.
     * The action's availability will be published in the device's service.xml.
     * MoveObject must be overridden if this is called.
     */
    void EnableActionMoveObject();
    /**
     * Signal that the action ImportResource is supported.
     * The action's availability will be published in the device's service.xml.
     * ImportResource must be overridden if this is called.
     */
    void EnableActionImportResource();
    /**
     * Signal that the action ExportResource is supported.
     * The action's availability will be published in the device's service.xml.
     * ExportResource must be overridden if this is called.
     */
    void EnableActionExportResource();
    /**
     * Signal that the action DeleteResource is supported.
     * The action's availability will be published in the device's service.xml.
     * DeleteResource must be overridden if this is called.
     */
    void EnableActionDeleteResource();
    /**
     * Signal that the action StopTransferResource is supported.
     * The action's availability will be published in the device's service.xml.
     * StopTransferResource must be overridden if this is called.
     */
    void EnableActionStopTransferResource();
    /**
     * Signal that the action GetTransferProgress is supported.
     * The action's availability will be published in the device's service.xml.
     * GetTransferProgress must be overridden if this is called.
     */
    void EnableActionGetTransferProgress();
    /**
     * Signal that the action CreateReference is supported.
     * The action's availability will be published in the device's service.xml.
     * CreateReference must be overridden if this is called.
     */
    void EnableActionCreateReference();
private:
    /**
     * GetSearchCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSearchCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSearchCapabilities was called.
     */
    virtual void GetSearchCapabilities(uint32_t aVersion, std::string& aSearchCaps);
    /**
     * GetSortCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSortCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSortCapabilities was called.
     */
    virtual void GetSortCapabilities(uint32_t aVersion, std::string& aSortCaps);
    /**
     * GetSortExtensionCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSortExtensionCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSortExtensionCapabilities was called.
     */
    virtual void GetSortExtensionCapabilities(uint32_t aVersion, std::string& aSortExtensionCaps);
    /**
     * GetFeatureList action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetFeatureList action for the owning device.
     * Must be implemented iff EnableActionGetFeatureList was called.
     */
    virtual void GetFeatureList(uint32_t aVersion, std::string& aFeatureList);
    /**
     * GetSystemUpdateID action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSystemUpdateID action for the owning device.
     * Must be implemented iff EnableActionGetSystemUpdateID was called.
     */
    virtual void GetSystemUpdateID(uint32_t aVersion, uint32_t& aId);
    /**
     * Browse action.
     *
     * Will be called when the device stack receives an invocation of the
     * Browse action for the owning device.
     * Must be implemented iff EnableActionBrowse was called.
     */
    virtual void Browse(uint32_t aVersion, const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * Search action.
     *
     * Will be called when the device stack receives an invocation of the
     * Search action for the owning device.
     * Must be implemented iff EnableActionSearch was called.
     */
    virtual void Search(uint32_t aVersion, const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * CreateObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateObject action for the owning device.
     * Must be implemented iff EnableActionCreateObject was called.
     */
    virtual void CreateObject(uint32_t aVersion, const std::string& aContainerID, const std::string& aElements, std::string& aObjectID, std::string& aResult);
    /**
     * DestroyObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * DestroyObject action for the owning device.
     * Must be implemented iff EnableActionDestroyObject was called.
     */
    virtual void DestroyObject(uint32_t aVersion, const std::string& aObjectID);
    /**
     * UpdateObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * UpdateObject action for the owning device.
     * Must be implemented iff EnableActionUpdateObject was called.
     */
    virtual void UpdateObject(uint32_t aVersion, const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue);
    /**
     * MoveObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * MoveObject action for the owning device.
     * Must be implemented iff EnableActionMoveObject was called.
     */
    virtual void MoveObject(uint32_t aVersion, const std::string& aObjectID, const std::string& aNewParentID, std::string& aNewObjectID);
    /**
     * ImportResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * ImportResource action for the owning device.
     * Must be implemented iff EnableActionImportResource was called.
     */
    virtual void ImportResource(uint32_t aVersion, const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
    /**
     * ExportResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * ExportResource action for the owning device.
     * Must be implemented iff EnableActionExportResource was called.
     */
    virtual void ExportResource(uint32_t aVersion, const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
    /**
     * DeleteResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteResource action for the owning device.
     * Must be implemented iff EnableActionDeleteResource was called.
     */
    virtual void DeleteResource(uint32_t aVersion, const std::string& aResourceURI);
    /**
     * StopTransferResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * StopTransferResource action for the owning device.
     * Must be implemented iff EnableActionStopTransferResource was called.
     */
    virtual void StopTransferResource(uint32_t aVersion, uint32_t aTransferID);
    /**
     * GetTransferProgress action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransferProgress action for the owning device.
     * Must be implemented iff EnableActionGetTransferProgress was called.
     */
    virtual void GetTransferProgress(uint32_t aVersion, uint32_t aTransferID, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);
    /**
     * CreateReference action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateReference action for the owning device.
     * Must be implemented iff EnableActionCreateReference was called.
     */
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

