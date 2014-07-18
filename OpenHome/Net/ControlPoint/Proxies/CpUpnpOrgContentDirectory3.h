#ifndef HEADER_UPNPORGCONTENTDIRECTORY3
#define HEADER_UPNPORGCONTENTDIRECTORY3

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Net/Core/CpProxy.h>

namespace OpenHome {
namespace Net {

class CpDevice;
class Action;
class PropertyBinary;
class PropertyBool;
class PropertyInt;
class PropertyString;
class PropertyUint;

/**
 * Proxy for upnp.org:ContentDirectory:3
 * @ingroup Proxies
 */
class CpProxyUpnpOrgContentDirectory3 : public CpProxy
{
public:
    /**
     * Constructor.
     *
     * Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable
     * and reporting of their changes.
     *
     * @param[in]  aDevice   The device to use
     */
    CpProxyUpnpOrgContentDirectory3(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgContentDirectory3();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSearchCaps
     */
    void SyncGetSearchCapabilities(Brh& aSearchCaps);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSearchCapabilities().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSearchCapabilities(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aSearchCaps
     */
    void EndGetSearchCapabilities(IAsync& aAsync, Brh& aSearchCaps);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSortCaps
     */
    void SyncGetSortCapabilities(Brh& aSortCaps);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSortCapabilities().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSortCapabilities(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aSortCaps
     */
    void EndGetSortCapabilities(IAsync& aAsync, Brh& aSortCaps);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSortExtensionCaps
     */
    void SyncGetSortExtensionCapabilities(Brh& aSortExtensionCaps);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSortExtensionCapabilities().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSortExtensionCapabilities(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aSortExtensionCaps
     */
    void EndGetSortExtensionCapabilities(IAsync& aAsync, Brh& aSortExtensionCaps);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aFeatureList
     */
    void SyncGetFeatureList(Brh& aFeatureList);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetFeatureList().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetFeatureList(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aFeatureList
     */
    void EndGetFeatureList(IAsync& aAsync, Brh& aFeatureList);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aId
     */
    void SyncGetSystemUpdateID(TUint& aId);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSystemUpdateID().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSystemUpdateID(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aId
     */
    void EndGetSystemUpdateID(IAsync& aAsync, TUint& aId);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aResetToken
     */
    void SyncGetServiceResetToken(Brh& aResetToken);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetServiceResetToken().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetServiceResetToken(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResetToken
     */
    void EndGetServiceResetToken(IAsync& aAsync, Brh& aResetToken);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aObjectID
     * @param[in]  aBrowseFlag
     * @param[in]  aFilter
     * @param[in]  aStartingIndex
     * @param[in]  aRequestedCount
     * @param[in]  aSortCriteria
     * @param[out] aResult
     * @param[out] aNumberReturned
     * @param[out] aTotalMatches
     * @param[out] aUpdateID
     */
    void SyncBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndBrowse().
     *
     * @param[in] aObjectID
     * @param[in] aBrowseFlag
     * @param[in] aFilter
     * @param[in] aStartingIndex
     * @param[in] aRequestedCount
     * @param[in] aSortCriteria
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginBrowse(const Brx& aObjectID, const Brx& aBrowseFlag, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     * @param[out] aNumberReturned
     * @param[out] aTotalMatches
     * @param[out] aUpdateID
     */
    void EndBrowse(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aSearchCriteria
     * @param[in]  aFilter
     * @param[in]  aStartingIndex
     * @param[in]  aRequestedCount
     * @param[in]  aSortCriteria
     * @param[out] aResult
     * @param[out] aNumberReturned
     * @param[out] aTotalMatches
     * @param[out] aUpdateID
     */
    void SyncSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSearch().
     *
     * @param[in] aContainerID
     * @param[in] aSearchCriteria
     * @param[in] aFilter
     * @param[in] aStartingIndex
     * @param[in] aRequestedCount
     * @param[in] aSortCriteria
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSearch(const Brx& aContainerID, const Brx& aSearchCriteria, const Brx& aFilter, TUint aStartingIndex, TUint aRequestedCount, const Brx& aSortCriteria, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     * @param[out] aNumberReturned
     * @param[out] aTotalMatches
     * @param[out] aUpdateID
     */
    void EndSearch(IAsync& aAsync, Brh& aResult, TUint& aNumberReturned, TUint& aTotalMatches, TUint& aUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aElements
     * @param[out] aObjectID
     * @param[out] aResult
     */
    void SyncCreateObject(const Brx& aContainerID, const Brx& aElements, Brh& aObjectID, Brh& aResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndCreateObject().
     *
     * @param[in] aContainerID
     * @param[in] aElements
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginCreateObject(const Brx& aContainerID, const Brx& aElements, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aObjectID
     * @param[out] aResult
     */
    void EndCreateObject(IAsync& aAsync, Brh& aObjectID, Brh& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aObjectID
     */
    void SyncDestroyObject(const Brx& aObjectID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDestroyObject().
     *
     * @param[in] aObjectID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDestroyObject(const Brx& aObjectID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndDestroyObject(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aObjectID
     * @param[in]  aCurrentTagValue
     * @param[in]  aNewTagValue
     */
    void SyncUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndUpdateObject().
     *
     * @param[in] aObjectID
     * @param[in] aCurrentTagValue
     * @param[in] aNewTagValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginUpdateObject(const Brx& aObjectID, const Brx& aCurrentTagValue, const Brx& aNewTagValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndUpdateObject(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aObjectID
     * @param[in]  aNewParentID
     * @param[out] aNewObjectID
     */
    void SyncMoveObject(const Brx& aObjectID, const Brx& aNewParentID, Brh& aNewObjectID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndMoveObject().
     *
     * @param[in] aObjectID
     * @param[in] aNewParentID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginMoveObject(const Brx& aObjectID, const Brx& aNewParentID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aNewObjectID
     */
    void EndMoveObject(IAsync& aAsync, Brh& aNewObjectID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aSourceURI
     * @param[in]  aDestinationURI
     * @param[out] aTransferID
     */
    void SyncImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndImportResource().
     *
     * @param[in] aSourceURI
     * @param[in] aDestinationURI
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginImportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aTransferID
     */
    void EndImportResource(IAsync& aAsync, TUint& aTransferID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aSourceURI
     * @param[in]  aDestinationURI
     * @param[out] aTransferID
     */
    void SyncExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, TUint& aTransferID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndExportResource().
     *
     * @param[in] aSourceURI
     * @param[in] aDestinationURI
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginExportResource(const Brx& aSourceURI, const Brx& aDestinationURI, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aTransferID
     */
    void EndExportResource(IAsync& aAsync, TUint& aTransferID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aResourceURI
     */
    void SyncDeleteResource(const Brx& aResourceURI);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDeleteResource().
     *
     * @param[in] aResourceURI
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDeleteResource(const Brx& aResourceURI, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndDeleteResource(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aTransferID
     */
    void SyncStopTransferResource(TUint aTransferID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndStopTransferResource().
     *
     * @param[in] aTransferID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginStopTransferResource(TUint aTransferID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndStopTransferResource(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aTransferID
     * @param[out] aTransferStatus
     * @param[out] aTransferLength
     * @param[out] aTransferTotal
     */
    void SyncGetTransferProgress(TUint aTransferID, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetTransferProgress().
     *
     * @param[in] aTransferID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetTransferProgress(TUint aTransferID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aTransferStatus
     * @param[out] aTransferLength
     * @param[out] aTransferTotal
     */
    void EndGetTransferProgress(IAsync& aAsync, Brh& aTransferStatus, Brh& aTransferLength, Brh& aTransferTotal);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aObjectID
     * @param[out] aNewID
     */
    void SyncCreateReference(const Brx& aContainerID, const Brx& aObjectID, Brh& aNewID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndCreateReference().
     *
     * @param[in] aContainerID
     * @param[in] aObjectID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginCreateReference(const Brx& aContainerID, const Brx& aObjectID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aNewID
     */
    void EndCreateReference(IAsync& aAsync, Brh& aNewID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aCDSView
     * @param[in]  aQueryRequest
     * @param[out] aQueryResult
     * @param[out] aUpdateID
     */
    void SyncFreeFormQuery(const Brx& aContainerID, TUint aCDSView, const Brx& aQueryRequest, Brh& aQueryResult, TUint& aUpdateID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndFreeFormQuery().
     *
     * @param[in] aContainerID
     * @param[in] aCDSView
     * @param[in] aQueryRequest
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginFreeFormQuery(const Brx& aContainerID, TUint aCDSView, const Brx& aQueryRequest, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aQueryResult
     * @param[out] aUpdateID
     */
    void EndFreeFormQuery(IAsync& aAsync, Brh& aQueryResult, TUint& aUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aFFQCapabilities
     */
    void SyncGetFreeFormQueryCapabilities(Brh& aFFQCapabilities);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetFreeFormQueryCapabilities().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetFreeFormQueryCapabilities(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aFFQCapabilities
     */
    void EndGetFreeFormQueryCapabilities(IAsync& aAsync, Brh& aFFQCapabilities);

    /**
     * Set a callback to be run when the SystemUpdateID state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySystemUpdateIDChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ContainerUpdateIDs state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyContainerUpdateIDsChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the LastChange state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyLastChangeChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TransferIDs state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTransferIDsChanged(Functor& aFunctor);

    /**
     * Query the value of the SystemUpdateID property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aSystemUpdateID
     */
    void PropertySystemUpdateID(TUint& aSystemUpdateID) const;
    /**
     * Query the value of the ContainerUpdateIDs property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aContainerUpdateIDs
     */
    void PropertyContainerUpdateIDs(Brhz& aContainerUpdateIDs) const;
    /**
     * Query the value of the LastChange property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aLastChange
     */
    void PropertyLastChange(Brhz& aLastChange) const;
    /**
     * Query the value of the TransferIDs property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aTransferIDs
     */
    void PropertyTransferIDs(Brhz& aTransferIDs) const;
private:
    void SystemUpdateIDPropertyChanged();
    void ContainerUpdateIDsPropertyChanged();
    void LastChangePropertyChanged();
    void TransferIDsPropertyChanged();
private:
    Action* iActionGetSearchCapabilities;
    Action* iActionGetSortCapabilities;
    Action* iActionGetSortExtensionCapabilities;
    Action* iActionGetFeatureList;
    Action* iActionGetSystemUpdateID;
    Action* iActionGetServiceResetToken;
    Action* iActionBrowse;
    Action* iActionSearch;
    Action* iActionCreateObject;
    Action* iActionDestroyObject;
    Action* iActionUpdateObject;
    Action* iActionMoveObject;
    Action* iActionImportResource;
    Action* iActionExportResource;
    Action* iActionDeleteResource;
    Action* iActionStopTransferResource;
    Action* iActionGetTransferProgress;
    Action* iActionCreateReference;
    Action* iActionFreeFormQuery;
    Action* iActionGetFreeFormQueryCapabilities;
    PropertyUint* iSystemUpdateID;
    PropertyString* iContainerUpdateIDs;
    PropertyString* iLastChange;
    PropertyString* iTransferIDs;
    Functor iSystemUpdateIDChanged;
    Functor iContainerUpdateIDsChanged;
    Functor iLastChangeChanged;
    Functor iTransferIDsChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_UPNPORGCONTENTDIRECTORY3

