#ifndef HEADER_UPNPORGCONTENTDIRECTORY3CPP
#define HEADER_UPNPORGCONTENTDIRECTORY3CPP

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/Net/Core/CpProxy.h>

#include <string>

namespace OpenHome {
namespace Net {

class CpDeviceCpp;
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
class CpProxyUpnpOrgContentDirectory3Cpp : public CpProxy
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
    CpProxyUpnpOrgContentDirectory3Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgContentDirectory3Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSearchCaps
     */
    void SyncGetSearchCapabilities(std::string& aSearchCaps);
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
    void EndGetSearchCapabilities(IAsync& aAsync, std::string& aSearchCaps);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSortCaps
     */
    void SyncGetSortCapabilities(std::string& aSortCaps);
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
    void EndGetSortCapabilities(IAsync& aAsync, std::string& aSortCaps);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aSortExtensionCaps
     */
    void SyncGetSortExtensionCapabilities(std::string& aSortExtensionCaps);
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
    void EndGetSortExtensionCapabilities(IAsync& aAsync, std::string& aSortExtensionCaps);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aFeatureList
     */
    void SyncGetFeatureList(std::string& aFeatureList);
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
    void EndGetFeatureList(IAsync& aAsync, std::string& aFeatureList);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aId
     */
    void SyncGetSystemUpdateID(uint32_t& aId);
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
    void EndGetSystemUpdateID(IAsync& aAsync, uint32_t& aId);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aResetToken
     */
    void SyncGetServiceResetToken(std::string& aResetToken);
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
    void EndGetServiceResetToken(IAsync& aAsync, std::string& aResetToken);

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
    void SyncBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
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
    void BeginBrowse(const std::string& aObjectID, const std::string& aBrowseFlag, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor);
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
    void EndBrowse(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);

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
    void SyncSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);
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
    void BeginSearch(const std::string& aContainerID, const std::string& aSearchCriteria, const std::string& aFilter, uint32_t aStartingIndex, uint32_t aRequestedCount, const std::string& aSortCriteria, FunctorAsync& aFunctor);
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
    void EndSearch(IAsync& aAsync, std::string& aResult, uint32_t& aNumberReturned, uint32_t& aTotalMatches, uint32_t& aUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aElements
     * @param[out] aObjectID
     * @param[out] aResult
     */
    void SyncCreateObject(const std::string& aContainerID, const std::string& aElements, std::string& aObjectID, std::string& aResult);
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
    void BeginCreateObject(const std::string& aContainerID, const std::string& aElements, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aObjectID
     * @param[out] aResult
     */
    void EndCreateObject(IAsync& aAsync, std::string& aObjectID, std::string& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aObjectID
     */
    void SyncDestroyObject(const std::string& aObjectID);
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
    void BeginDestroyObject(const std::string& aObjectID, FunctorAsync& aFunctor);
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
    void SyncUpdateObject(const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue);
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
    void BeginUpdateObject(const std::string& aObjectID, const std::string& aCurrentTagValue, const std::string& aNewTagValue, FunctorAsync& aFunctor);
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
    void SyncMoveObject(const std::string& aObjectID, const std::string& aNewParentID, std::string& aNewObjectID);
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
    void BeginMoveObject(const std::string& aObjectID, const std::string& aNewParentID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aNewObjectID
     */
    void EndMoveObject(IAsync& aAsync, std::string& aNewObjectID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aSourceURI
     * @param[in]  aDestinationURI
     * @param[out] aTransferID
     */
    void SyncImportResource(const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
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
    void BeginImportResource(const std::string& aSourceURI, const std::string& aDestinationURI, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aTransferID
     */
    void EndImportResource(IAsync& aAsync, uint32_t& aTransferID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aSourceURI
     * @param[in]  aDestinationURI
     * @param[out] aTransferID
     */
    void SyncExportResource(const std::string& aSourceURI, const std::string& aDestinationURI, uint32_t& aTransferID);
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
    void BeginExportResource(const std::string& aSourceURI, const std::string& aDestinationURI, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aTransferID
     */
    void EndExportResource(IAsync& aAsync, uint32_t& aTransferID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aResourceURI
     */
    void SyncDeleteResource(const std::string& aResourceURI);
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
    void BeginDeleteResource(const std::string& aResourceURI, FunctorAsync& aFunctor);
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
    void SyncStopTransferResource(uint32_t aTransferID);
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
    void BeginStopTransferResource(uint32_t aTransferID, FunctorAsync& aFunctor);
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
    void SyncGetTransferProgress(uint32_t aTransferID, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);
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
    void BeginGetTransferProgress(uint32_t aTransferID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aTransferStatus
     * @param[out] aTransferLength
     * @param[out] aTransferTotal
     */
    void EndGetTransferProgress(IAsync& aAsync, std::string& aTransferStatus, std::string& aTransferLength, std::string& aTransferTotal);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aContainerID
     * @param[in]  aObjectID
     * @param[out] aNewID
     */
    void SyncCreateReference(const std::string& aContainerID, const std::string& aObjectID, std::string& aNewID);
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
    void BeginCreateReference(const std::string& aContainerID, const std::string& aObjectID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aNewID
     */
    void EndCreateReference(IAsync& aAsync, std::string& aNewID);

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
    void SyncFreeFormQuery(const std::string& aContainerID, uint32_t aCDSView, const std::string& aQueryRequest, std::string& aQueryResult, uint32_t& aUpdateID);
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
    void BeginFreeFormQuery(const std::string& aContainerID, uint32_t aCDSView, const std::string& aQueryRequest, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aQueryResult
     * @param[out] aUpdateID
     */
    void EndFreeFormQuery(IAsync& aAsync, std::string& aQueryResult, uint32_t& aUpdateID);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aFFQCapabilities
     */
    void SyncGetFreeFormQueryCapabilities(std::string& aFFQCapabilities);
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
    void EndGetFreeFormQueryCapabilities(IAsync& aAsync, std::string& aFFQCapabilities);

    /**
     * Set a callback to be run when the SystemUpdateID state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySystemUpdateIDChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ContainerUpdateIDs state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyContainerUpdateIDsChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the LastChange state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyLastChangeChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TransferIDs state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3Cpp instance will not overlap.
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
    void PropertySystemUpdateID(uint32_t& aSystemUpdateID) const;
    /**
     * Query the value of the ContainerUpdateIDs property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aContainerUpdateIDs
     */
    void PropertyContainerUpdateIDs(std::string& aContainerUpdateIDs) const;
    /**
     * Query the value of the LastChange property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aLastChange
     */
    void PropertyLastChange(std::string& aLastChange) const;
    /**
     * Query the value of the TransferIDs property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aTransferIDs
     */
    void PropertyTransferIDs(std::string& aTransferIDs) const;
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

#endif // HEADER_UPNPORGCONTENTDIRECTORY3CPP

