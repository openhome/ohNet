#ifndef HEADER_DVUPNPORGCONTENTDIRECTORY1
#define HEADER_DVUPNPORGCONTENTDIRECTORY1

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Core/DvDevice.h>
#include <OpenHome/Net/Core/DvProvider.h>

namespace OpenHome {
namespace Net {

class DviDevice;
class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Provider for the upnp.org:ContentDirectory:1 UPnP service
 * @ingroup Providers
 */
class DvProviderUpnpOrgContentDirectory1 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgContentDirectory1() {}
    /**
     * Set the value of the TransferIDs property
     *
     * Can only be called if EnablePropertyTransferIDs has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyTransferIDs(const Brx& aValue);
    /**
     * Get a copy of the value of the TransferIDs property
     *
     * Can only be called if EnablePropertyTransferIDs has previously been called.
     */
    void GetPropertyTransferIDs(Brhz& aValue);
    /**
     * Set the value of the SystemUpdateID property
     *
     * Can only be called if EnablePropertySystemUpdateID has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertySystemUpdateID(TUint aValue);
    /**
     * Get a copy of the value of the SystemUpdateID property
     *
     * Can only be called if EnablePropertySystemUpdateID has previously been called.
     */
    void GetPropertySystemUpdateID(TUint& aValue);
    /**
     * Set the value of the ContainerUpdateIDs property
     *
     * Can only be called if EnablePropertyContainerUpdateIDs has previously been called.
     *
     * @return  true if the value has been updated; false if aValue was the same as the previous value
     */
    TBool SetPropertyContainerUpdateIDs(const Brx& aValue);
    /**
     * Get a copy of the value of the ContainerUpdateIDs property
     *
     * Can only be called if EnablePropertyContainerUpdateIDs has previously been called.
     */
    void GetPropertyContainerUpdateIDs(Brhz& aValue);
protected:
    /**
     * Constructor
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgContentDirectory1(DvDevice& aDevice);
    /**
     * Constructor.  Not for external use.
     *
     * @param[in] aDevice  Device which owns this provider
     */
    DvProviderUpnpOrgContentDirectory1(DviDevice& aDevice);
    /**
     * Enable the TransferIDs property.
     */
    void EnablePropertyTransferIDs();
    /**
     * Enable the SystemUpdateID property.
     */
    void EnablePropertySystemUpdateID();
    /**
     * Enable the ContainerUpdateIDs property.
     */
    void EnablePropertyContainerUpdateIDs();
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
     * Signal that the action DeleteResource is supported.
     * The action's availability will be published in the device's service.xml.
     * DeleteResource must be overridden if this is called.
     */
    void EnableActionDeleteResource();
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
    virtual void GetSearchCapabilities(IDvInvocation& aInvocation, IDvInvocationResponseString& aSearchCaps);
    /**
     * GetSortCapabilities action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSortCapabilities action for the owning device.
     * Must be implemented iff EnableActionGetSortCapabilities was called.
     */
    virtual void GetSortCapabilities(IDvInvocation& aInvocation, IDvInvocationResponseString& aSortCaps);
    /**
     * GetSystemUpdateID action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetSystemUpdateID action for the owning device.
     * Must be implemented iff EnableActionGetSystemUpdateID was called.
     */
    virtual void GetSystemUpdateID(IDvInvocation& aInvocation, IDvInvocationResponseUint& aId);
    /**
     * Browse action.
     *
     * Will be called when the device stack receives an invocation of the
     * Browse action for the owning device.
     * Must be implemented iff EnableActionBrowse was called.
     */
    virtual void Browse(IDvInvocation& aInvocation, const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IDvInvocationResponseString& aResult, IDvInvocationResponseUint& aNumberReturned, IDvInvocationResponseUint& aTotalMatches, IDvInvocationResponseUint& aUpdateID);
    /**
     * Search action.
     *
     * Will be called when the device stack receives an invocation of the
     * Search action for the owning device.
     * Must be implemented iff EnableActionSearch was called.
     */
    virtual void Search(IDvInvocation& aInvocation, const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, IDvInvocationResponseString& aResult, IDvInvocationResponseUint& aNumberReturned, IDvInvocationResponseUint& aTotalMatches, IDvInvocationResponseUint& aUpdateID);
    /**
     * CreateObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateObject action for the owning device.
     * Must be implemented iff EnableActionCreateObject was called.
     */
    virtual void CreateObject(IDvInvocation& aInvocation, const Brx& aContainerID, const Brx& aElements, IDvInvocationResponseString& aObjectID, IDvInvocationResponseString& aResult);
    /**
     * DestroyObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * DestroyObject action for the owning device.
     * Must be implemented iff EnableActionDestroyObject was called.
     */
    virtual void DestroyObject(IDvInvocation& aInvocation, const Brx& aObjectID);
    /**
     * UpdateObject action.
     *
     * Will be called when the device stack receives an invocation of the
     * UpdateObject action for the owning device.
     * Must be implemented iff EnableActionUpdateObject was called.
     */
    virtual void UpdateObject(IDvInvocation& aInvocation, const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue);
    /**
     * ImportResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * ImportResource action for the owning device.
     * Must be implemented iff EnableActionImportResource was called.
     */
    virtual void ImportResource(IDvInvocation& aInvocation, const Brx& aSourceURI, const Brx& aDestinationURI, IDvInvocationResponseUint& aTransferID);
    /**
     * ExportResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * ExportResource action for the owning device.
     * Must be implemented iff EnableActionExportResource was called.
     */
    virtual void ExportResource(IDvInvocation& aInvocation, const Brx& aSourceURI, const Brx& aDestinationURI, IDvInvocationResponseUint& aTransferID);
    /**
     * StopTransferResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * StopTransferResource action for the owning device.
     * Must be implemented iff EnableActionStopTransferResource was called.
     */
    virtual void StopTransferResource(IDvInvocation& aInvocation, TUint aTransferID);
    /**
     * GetTransferProgress action.
     *
     * Will be called when the device stack receives an invocation of the
     * GetTransferProgress action for the owning device.
     * Must be implemented iff EnableActionGetTransferProgress was called.
     */
    virtual void GetTransferProgress(IDvInvocation& aInvocation, TUint aTransferID, IDvInvocationResponseString& aTransferStatus, IDvInvocationResponseString& aTransferLength, IDvInvocationResponseString& aTransferTotal);
    /**
     * DeleteResource action.
     *
     * Will be called when the device stack receives an invocation of the
     * DeleteResource action for the owning device.
     * Must be implemented iff EnableActionDeleteResource was called.
     */
    virtual void DeleteResource(IDvInvocation& aInvocation, const Brx& aResourceURI);
    /**
     * CreateReference action.
     *
     * Will be called when the device stack receives an invocation of the
     * CreateReference action for the owning device.
     * Must be implemented iff EnableActionCreateReference was called.
     */
    virtual void CreateReference(IDvInvocation& aInvocation, const Brx& aContainerID, const Brx& aObjectID, IDvInvocationResponseString& aNewID);
private:
    DvProviderUpnpOrgContentDirectory1();
    void Construct();
    void DoGetSearchCapabilities(IDviInvocation& aInvocation);
    void DoGetSortCapabilities(IDviInvocation& aInvocation);
    void DoGetSystemUpdateID(IDviInvocation& aInvocation);
    void DoBrowse(IDviInvocation& aInvocation);
    void DoSearch(IDviInvocation& aInvocation);
    void DoCreateObject(IDviInvocation& aInvocation);
    void DoDestroyObject(IDviInvocation& aInvocation);
    void DoUpdateObject(IDviInvocation& aInvocation);
    void DoImportResource(IDviInvocation& aInvocation);
    void DoExportResource(IDviInvocation& aInvocation);
    void DoStopTransferResource(IDviInvocation& aInvocation);
    void DoGetTransferProgress(IDviInvocation& aInvocation);
    void DoDeleteResource(IDviInvocation& aInvocation);
    void DoCreateReference(IDviInvocation& aInvocation);
private:
    PropertyString* iPropertyTransferIDs;
    PropertyUint* iPropertySystemUpdateID;
    PropertyString* iPropertyContainerUpdateIDs;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVUPNPORGCONTENTDIRECTORY1

