#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY3CPP
#define HEADER_DVUPNPORGCONTENTDIRECTORY3CPP

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Cpp/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/Net/Cpp/DvInvocation.h>

#include <string>

namespace OpenHome {
namespace Net {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the upnp.org:ContentDirectory:3 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgContentDirectory3Cpp : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgContentDirectory3Cpp() {}
    /**
     * Set the value of the SystemUpdateID property
     *
     * Can only be called if EnablePropertySystemUpdateID has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertySystemUpdateID(uint32_t aValue);
    /**
     * Get a copy of the value of the SystemUpdateID property
     *
     * Can only be called if EnablePropertySystemUpdateID has previously been called.
     */
    void GetPropertySystemUpdateID(uint32_t& aValue);
    /**
     * Set the value of the ContainerUpdateIDs property
     *
     * Can only be called if EnablePropertyContainerUpdateIDs has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyContainerUpdateIDs(const std::string& aValue);
    /**
     * Get a copy of the value of the ContainerUpdateIDs property
     *
     * Can only be called if EnablePropertyContainerUpdateIDs has previously been called.
     */
    void GetPropertyContainerUpdateIDs(std::string& aValue);
    /**
     * Set the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyLastChange(const std::string& aValue);
    /**
     * Get a copy of the value of the LastChange property
     *
     * Can only be called if EnablePropertyLastChange has previously been called.
     */
    void GetPropertyLastChange(std::string& aValue);
    /**
     * Set the value of the TransferIDs property
     *
     * Can only be called if EnablePropertyTransferIDs has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    bool SetPropertyTransferIDs(const std::string& aValue);
    /**
     * Get a copy of the value of the TransferIDs property
     *
     * Can only be called if EnablePropertyTransferIDs has previously been called.
     */
    void GetPropertyTransferIDs(std::string& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgContentDirectory3Cpp(DvDeviceStd& aDevice);
    /**
     * Enable the SystemUpdateID property.
     */
    void EnablePropertySystemUpdateID();
    /**
     * Enable the ContainerUpdateIDs property.
     */
    void EnablePropertyContainerUpdateIDs();
    /**
     * Enable the LastChange property.
     */
    void EnablePropertyLastChange();
    /**
     * Enable the TransferIDs property.
     */
    void EnablePropertyTransferIDs();
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
     * Signal that the action GetServiceResetToken is supported.
     * The action's availability will be published in the device's service.xml.
     * GetServiceResetToken must be overridden if this is called.
     */
    void EnableActionGetServiceResetToken();
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
    /**
     * Signal that the action FreeFormQuery is supported.
     * The action's availability will be published in the device's service.xml.
     * FreeFormQuery must be overridden if this is called.
     */
    void EnableActionFreeFormQuery();
    /**
     * Signal that the action GetFreeFormQueryCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * GetFreeFormQueryCapabilities must be overridden if this is called.
     */
    void EnableActionGetFreeFormQueryCapabilities();
private:
    /**
     * GetSearchCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSearchCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSearchCapabilities was called.
     */
    virtual void GetSearchCapabilities(IDvInvocationStd& aInvocation, std::string& aSearchCaps);
    /**
     * GetSortCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSortCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSortCapabilities was called.
     */
    virtual void GetSortCapabilities(IDvInvocationStd& aInvocation, std::string& aSortCaps);
    /**
     * GetSortExtensionCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSortExtensionCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSortExtensionCapabilities was called.
     */
    virtual void GetSortExtensionCapabilities(IDvInvocationStd& aInvocation, std::string& aSortExtensionCaps);
    /**
     * GetFeatureList action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetFeatureList action for the owning device.
     * Must be implemented iff EnableActionGetFeatureList was called.
     */
    virtual void GetFeatureList(IDvInvocationStd& aInvocation, std::string& aFeatureList);
    /**
     * GetSystemUpdateID action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSystemUpdateID action for the owning device.
     * Must be implemented iff EnableActionGetSystemUpdateID was called.
     */
    virtual void GetSystemUpdateID(IDvInvocationStd& aInvocation, uint32_t& aId);
    /**
     * GetServiceResetToken action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetServiceResetToken action for the owning device.
     * Must be implemented iff EnableActionGetServiceResetToken was called.
     */
    virtual void GetServiceResetToken(IDvInvocationStd& aInvocation, std::string& aResetToken);
    /**
     * Browse action.
     *
     * Will be called when the device stack receives an invocation of the
     * Browse action for the owning device.
     * Must be implemented iff EnableActionBrowse was called.
     */
    virtual void Browse(IDvInvocationStd& aInvocation, const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * Search action.
     *
     * Will be called when the device stack receives an invocation of the
     * Search action for the owning device.
     * Must be implemented iff EnableActionSearch was called.
     */
    virtual void Search(IDvInvocationStd& aInvocation, const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
    /**
     * CreateObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateObject action for the owning device.
     * Must be implemented iff EnableActionCreateObject was called.
     */
    virtual void CreateObject(IDvInvocationStd& aInvocation, const std::string& aContainerID, const std::string& aElements, std::string& aObjectID, std::string& aResult);
    /**
     * DestroyObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * DestroyObject action for the owning device.
     * Must be implemented iff EnableActionDestroyObject was called.
     */
    virtual void DestroyObject(IDvInvocationStd& aInvocation, const std::string& aObjectID);
    /**
     * UpdateObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * UpdateObject action for the owning device.
     * Must be implemented iff EnableActionUpdateObject was called.
     */
    virtual void UpdateObject(IDvInvocationStd& aInvocation, const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue);
    /**
     * MoveObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * MoveObject action for the owning device.
     * Must be implemented iff EnableActionMoveObject was called.
     */
    virtual void MoveObject(IDvInvocationStd& aInvocation, const std::string& aObjectID, const std::string& aNewParentID, std::string& aNewObjectID);
    /**
     * ImportResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * ImportResource action for the owning device.
     * Must be implemented iff EnableActionImportResource was called.
     */
    virtual void ImportResource(IDvInvocationStd& aInvocation, const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
    /**
     * ExportResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * ExportResource action for the owning device.
     * Must be implemented iff EnableActionExportResource was called.
     */
    virtual void ExportResource(IDvInvocationStd& aInvocation, const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
    /**
     * DeleteResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteResource action for the owning device.
     * Must be implemented iff EnableActionDeleteResource was called.
     */
    virtual void DeleteResource(IDvInvocationStd& aInvocation, const std::string& aResourceURI);
    /**
     * StopTransferResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * StopTransferResource action for the owning device.
     * Must be implemented iff EnableActionStopTransferResource was called.
     */
    virtual void StopTransferResource(IDvInvocationStd& aInvocation, uint32_t aTransferID);
    /**
     * GetTransferProgress action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransferProgress action for the owning device.
     * Must be implemented iff EnableActionGetTransferProgress was called.
     */
    virtual void GetTransferProgress(IDvInvocationStd& aInvocation, uint32_t aTransferID, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);
    /**
     * CreateReference action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateReference action for the owning device.
     * Must be implemented iff EnableActionCreateReference was called.
     */
    virtual void CreateReference(IDvInvocationStd& aInvocation, const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID);
    /**
     * FreeFormQuery action.
     *
     * Will be called when the device stack receives an invocation of the
     * FreeFormQuery action for the owning device.
     * Must be implemented iff EnableActionFreeFormQuery was called.
     */
    virtual void FreeFormQuery(IDvInvocationStd& aInvocation, const std::string& aContainerID, uint32_t aCDSView, const std::string& aQueryRequest, std::string& aQueryResult, uint32_t& aUpdateID);
    /**
     * GetFreeFormQueryCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetFreeFormQueryCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetFreeFormQueryCapabilities was called.
     */
    virtual void GetFreeFormQueryCapabilities(IDvInvocationStd& aInvocation, std::string& aFFQCapabilities);
private:
    DvProviderUpnpOrgContentDirectory3Cpp();
    void DoGetSearchCapabilities(IDviInvocation& aInvocation);
    void DoGetSortCapabilities(IDviInvocation& aInvocation);
    void DoGetSortExtensionCapabilities(IDviInvocation& aInvocation);
    void DoGetFeatureList(IDviInvocation& aInvocation);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation);
    void DoGetServiceResetToken(IDviInvocation& aInvocation);
    void DoBrowse(IDviInvocation& aInvocation);
    void DoSearch(IDviInvocation& aInvocation);
    void DoCreateObject(IDviInvocation& aInvocation);
    void DoDestroyObject(IDviInvocation& aInvocation);
    void DoUpdateObject(IDviInvocation& aInvocation);
    void DoMoveObject(IDviInvocation& aInvocation);
    void DoImportResource(IDviInvocation& aInvocation);
    void DoExportResource(IDviInvocation& aInvocation);
    void DoDeleteResource(IDviInvocation& aInvocation);
    void DoStopTransferResource(IDviInvocation& aInvocation);
    void DoGetTransferProgress(IDviInvocation& aInvocation);
    void DoCreateReference(IDviInvocation& aInvocation);
    void DoFreeFormQuery(IDviInvocation& aInvocation);
    void DoGetFreeFormQueryCapabilities(IDviInvocation& aInvocation);
private:
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
    PropertyString* iPropertyLastChange;
    PropertyString* iPropertyTransferIDs;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY3CPP

