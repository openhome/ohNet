#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY2
#define HEADER_DVUPNPORGCONTENTDIRECTORY2

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the upnp.org:ContentDirectory:2 UPnP service
 */
class DvProviderUpnpOrgContentDirectory2 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgContentDirectory2() {}
    /**
     * Set the value of the SystemUpdateID property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySystemUpdateID(TUint aValue);
    /**
     * Get a copy of the value of the SystemUpdateID property
     */
    void GetPropertySystemUpdateID(TUint& aValue);
    /**
     * Set the value of the ContainerUpdateIDs property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyContainerUpdateIDs(const Brx& aValue);
    /**
     * Get a copy of the value of the ContainerUpdateIDs property
     */
    void GetPropertyContainerUpdateIDs(Brhz& aValue);
    /**
     * Set the value of the TransferIDs property
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTransferIDs(const Brx& aValue);
    /**
     * Get a copy of the value of the TransferIDs property
     */
    void GetPropertyTransferIDs(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgContentDirectory2(DvDevice& aDevice);
    /**
     * Signal that the action GetSearchCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetSearchCapabilities must be overridden if this is called.
     */
    void EnableActionGetSearchCapabilities();
    /**
     * Signal that the action GetSortCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetSortCapabilities must be overridden if this is called.
     */
    void EnableActionGetSortCapabilities();
    /**
     * Signal that the action GetSortExtensionCapabilities is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetSortExtensionCapabilities must be overridden if this is called.
     */
    void EnableActionGetSortExtensionCapabilities();
    /**
     * Signal that the action GetFeatureList is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetFeatureList must be overridden if this is called.
     */
    void EnableActionGetFeatureList();
    /**
     * Signal that the action GetSystemUpdateID is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetSystemUpdateID must be overridden if this is called.
     */
    void EnableActionGetSystemUpdateID();
    /**
     * Signal that the action Browse is supported.
     * The action's availability will be published in the device's service.xml.
     * DoBrowse must be overridden if this is called.
     */
    void EnableActionBrowse();
    /**
     * Signal that the action Search is supported.
     * The action's availability will be published in the device's service.xml.
     * DoSearch must be overridden if this is called.
     */
    void EnableActionSearch();
    /**
     * Signal that the action CreateObject is supported.
     * The action's availability will be published in the device's service.xml.
     * DoCreateObject must be overridden if this is called.
     */
    void EnableActionCreateObject();
    /**
     * Signal that the action DestroyObject is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDestroyObject must be overridden if this is called.
     */
    void EnableActionDestroyObject();
    /**
     * Signal that the action UpdateObject is supported.
     * The action's availability will be published in the device's service.xml.
     * DoUpdateObject must be overridden if this is called.
     */
    void EnableActionUpdateObject();
    /**
     * Signal that the action MoveObject is supported.
     * The action's availability will be published in the device's service.xml.
     * DoMoveObject must be overridden if this is called.
     */
    void EnableActionMoveObject();
    /**
     * Signal that the action ImportResource is supported.
     * The action's availability will be published in the device's service.xml.
     * DoImportResource must be overridden if this is called.
     */
    void EnableActionImportResource();
    /**
     * Signal that the action ExportResource is supported.
     * The action's availability will be published in the device's service.xml.
     * DoExportResource must be overridden if this is called.
     */
    void EnableActionExportResource();
    /**
     * Signal that the action DeleteResource is supported.
     * The action's availability will be published in the device's service.xml.
     * DoDeleteResource must be overridden if this is called.
     */
    void EnableActionDeleteResource();
    /**
     * Signal that the action StopTransferResource is supported.
     * The action's availability will be published in the device's service.xml.
     * DoStopTransferResource must be overridden if this is called.
     */
    void EnableActionStopTransferResource();
    /**
     * Signal that the action GetTransferProgress is supported.
     * The action's availability will be published in the device's service.xml.
     * DoGetTransferProgress must be overridden if this is called.
     */
    void EnableActionGetTransferProgress();
    /**
     * Signal that the action CreateReference is supported.
     * The action's availability will be published in the device's service.xml.
     * DoCreateReference must be overridden if this is called.
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
    virtual void GetSearchCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSearchCaps);
    /**
     * GetSortCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSortCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSortCapabilities was called.
     */
    virtual void GetSortCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortCaps);
    /**
     * GetSortExtensionCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSortExtensionCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSortExtensionCapabilities was called.
     */
    virtual void GetSortExtensionCapabilities(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aSortExtensionCaps);
    /**
     * GetFeatureList action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetFeatureList action for the owning device.
     * Must be implemented iff EnableActionGetFeatureList was called.
     */
    virtual void GetFeatureList(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aFeatureList);
    /**
     * GetSystemUpdateID action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSystemUpdateID action for the owning device.
     * Must be implemented iff EnableActionGetSystemUpdateID was called.
     */
    virtual void GetSystemUpdateID(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aId);
    /**
     * Browse action.
     *
     * Will be called when the device stack receives an invocation of the
     * Browse action for the owning device.
     * Must be implemented iff EnableActionBrowse was called.
     */
    virtual void Browse(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    /**
     * Search action.
     *
     * Will be called when the device stack receives an invocation of the
     * Search action for the owning device.
     * Must be implemented iff EnableActionSearch was called.
     */
    virtual void Search(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IInvocationResponseString& aResult, IInvocationResponseUint& aNumberReturned, IInvocationResponseUint& aTotalMatches, IInvocationResponseUint& aUpdateID);
    /**
     * CreateObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateObject action for the owning device.
     * Must be implemented iff EnableActionCreateObject was called.
     */
    virtual void CreateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aElements, IInvocationResponseString& aObjectID, IInvocationResponseString& aResult);
    /**
     * DestroyObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * DestroyObject action for the owning device.
     * Must be implemented iff EnableActionDestroyObject was called.
     */
    virtual void DestroyObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID);
    /**
     * UpdateObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * UpdateObject action for the owning device.
     * Must be implemented iff EnableActionUpdateObject was called.
     */
    virtual void UpdateObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue);
    /**
     * MoveObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * MoveObject action for the owning device.
     * Must be implemented iff EnableActionMoveObject was called.
     */
    virtual void MoveObject(IInvocationResponse& aResponse, TUint aVersion, const Brx& aObjectID, const Brx& aNewParentID, IInvocationResponseString& aNewObjectID);
    /**
     * ImportResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * ImportResource action for the owning device.
     * Must be implemented iff EnableActionImportResource was called.
     */
    virtual void ImportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID);
    /**
     * ExportResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * ExportResource action for the owning device.
     * Must be implemented iff EnableActionExportResource was called.
     */
    virtual void ExportResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aSourceURI, const Brx& aDestinationURI, IInvocationResponseUint& aTransferID);
    /**
     * DeleteResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteResource action for the owning device.
     * Must be implemented iff EnableActionDeleteResource was called.
     */
    virtual void DeleteResource(IInvocationResponse& aResponse, TUint aVersion, const Brx& aResourceURI);
    /**
     * StopTransferResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * StopTransferResource action for the owning device.
     * Must be implemented iff EnableActionStopTransferResource was called.
     */
    virtual void StopTransferResource(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID);
    /**
     * GetTransferProgress action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransferProgress action for the owning device.
     * Must be implemented iff EnableActionGetTransferProgress was called.
     */
    virtual void GetTransferProgress(IInvocationResponse& aResponse, TUint aVersion, TUint aTransferID, IInvocationResponseString& aTransferStatus, IInvocationResponseString& aTransferLength, IInvocationResponseString& aTransferTotal);
    /**
     * CreateReference action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateReference action for the owning device.
     * Must be implemented iff EnableActionCreateReference was called.
     */
    virtual void CreateReference(IInvocationResponse& aResponse, TUint aVersion, const Brx& aContainerID, const Brx& aObjectID, IInvocationResponseString& aNewID);
private:
    DvProviderUpnpOrgContentDirectory2();
    void DoGetSearchCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSortCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSortExtensionCapabilities(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetFeatureList(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation, TUint aVersion);
    void DoBrowse(IDviInvocation& aInvocation, TUint aVersion);
    void DoSearch(IDviInvocation& aInvocation, TUint aVersion);
    void DoCreateObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoDestroyObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoUpdateObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoMoveObject(IDviInvocation& aInvocation, TUint aVersion);
    void DoImportResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoExportResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoDeleteResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoStopTransferResource(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetTransferProgress(IDviInvocation& aInvocation, TUint aVersion);
    void DoCreateReference(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
    PropertyString* iPropertyTransferIDs;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY2

