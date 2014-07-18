#ifndef HEADER_UPNPORGAVTRANSPORT2
#define HEADER_UPNPORGAVTRANSPORT2

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
 * Proxy for upnp.org:AVTransport:2
 * @ingroup Proxies
 */
class CpProxyUpnpOrgAVTransport2 : public CpProxy
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
    CpProxyUpnpOrgAVTransport2(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgAVTransport2();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aCurrentURI
     * @param[in]  aCurrentURIMetaData
     */
    void SyncSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetAVTransportURI().
     *
     * @param[in] aInstanceID
     * @param[in] aCurrentURI
     * @param[in] aCurrentURIMetaData
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetAVTransportURI(TUint aInstanceID, const Brx& aCurrentURI, const Brx& aCurrentURIMetaData, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetAVTransportURI(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aNextURI
     * @param[in]  aNextURIMetaData
     */
    void SyncSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetNextAVTransportURI().
     *
     * @param[in] aInstanceID
     * @param[in] aNextURI
     * @param[in] aNextURIMetaData
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetNextAVTransportURI(TUint aInstanceID, const Brx& aNextURI, const Brx& aNextURIMetaData, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetNextAVTransportURI(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aNrTracks
     * @param[out] aMediaDuration
     * @param[out] aCurrentURI
     * @param[out] aCurrentURIMetaData
     * @param[out] aNextURI
     * @param[out] aNextURIMetaData
     * @param[out] aPlayMedium
     * @param[out] aRecordMedium
     * @param[out] aWriteStatus
     */
    void SyncGetMediaInfo(TUint aInstanceID, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetMediaInfo().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetMediaInfo(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aNrTracks
     * @param[out] aMediaDuration
     * @param[out] aCurrentURI
     * @param[out] aCurrentURIMetaData
     * @param[out] aNextURI
     * @param[out] aNextURIMetaData
     * @param[out] aPlayMedium
     * @param[out] aRecordMedium
     * @param[out] aWriteStatus
     */
    void EndGetMediaInfo(IAsync& aAsync, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentType
     * @param[out] aNrTracks
     * @param[out] aMediaDuration
     * @param[out] aCurrentURI
     * @param[out] aCurrentURIMetaData
     * @param[out] aNextURI
     * @param[out] aNextURIMetaData
     * @param[out] aPlayMedium
     * @param[out] aRecordMedium
     * @param[out] aWriteStatus
     */
    void SyncGetMediaInfo_Ext(TUint aInstanceID, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetMediaInfo_Ext().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetMediaInfo_Ext(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentType
     * @param[out] aNrTracks
     * @param[out] aMediaDuration
     * @param[out] aCurrentURI
     * @param[out] aCurrentURIMetaData
     * @param[out] aNextURI
     * @param[out] aNextURIMetaData
     * @param[out] aPlayMedium
     * @param[out] aRecordMedium
     * @param[out] aWriteStatus
     */
    void EndGetMediaInfo_Ext(IAsync& aAsync, Brh& aCurrentType, TUint& aNrTracks, Brh& aMediaDuration, Brh& aCurrentURI, Brh& aCurrentURIMetaData, Brh& aNextURI, Brh& aNextURIMetaData, Brh& aPlayMedium, Brh& aRecordMedium, Brh& aWriteStatus);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentTransportState
     * @param[out] aCurrentTransportStatus
     * @param[out] aCurrentSpeed
     */
    void SyncGetTransportInfo(TUint aInstanceID, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetTransportInfo().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetTransportInfo(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentTransportState
     * @param[out] aCurrentTransportStatus
     * @param[out] aCurrentSpeed
     */
    void EndGetTransportInfo(IAsync& aAsync, Brh& aCurrentTransportState, Brh& aCurrentTransportStatus, Brh& aCurrentSpeed);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aTrack
     * @param[out] aTrackDuration
     * @param[out] aTrackMetaData
     * @param[out] aTrackURI
     * @param[out] aRelTime
     * @param[out] aAbsTime
     * @param[out] aRelCount
     * @param[out] aAbsCount
     */
    void SyncGetPositionInfo(TUint aInstanceID, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetPositionInfo().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetPositionInfo(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aTrack
     * @param[out] aTrackDuration
     * @param[out] aTrackMetaData
     * @param[out] aTrackURI
     * @param[out] aRelTime
     * @param[out] aAbsTime
     * @param[out] aRelCount
     * @param[out] aAbsCount
     */
    void EndGetPositionInfo(IAsync& aAsync, TUint& aTrack, Brh& aTrackDuration, Brh& aTrackMetaData, Brh& aTrackURI, Brh& aRelTime, Brh& aAbsTime, TInt& aRelCount, TInt& aAbsCount);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aPlayMedia
     * @param[out] aRecMedia
     * @param[out] aRecQualityModes
     */
    void SyncGetDeviceCapabilities(TUint aInstanceID, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetDeviceCapabilities().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetDeviceCapabilities(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aPlayMedia
     * @param[out] aRecMedia
     * @param[out] aRecQualityModes
     */
    void EndGetDeviceCapabilities(IAsync& aAsync, Brh& aPlayMedia, Brh& aRecMedia, Brh& aRecQualityModes);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aPlayMode
     * @param[out] aRecQualityMode
     */
    void SyncGetTransportSettings(TUint aInstanceID, Brh& aPlayMode, Brh& aRecQualityMode);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetTransportSettings().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetTransportSettings(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aPlayMode
     * @param[out] aRecQualityMode
     */
    void EndGetTransportSettings(IAsync& aAsync, Brh& aPlayMode, Brh& aRecQualityMode);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     */
    void SyncStop(TUint aInstanceID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndStop().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginStop(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndStop(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aSpeed
     */
    void SyncPlay(TUint aInstanceID, const Brx& aSpeed);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndPlay().
     *
     * @param[in] aInstanceID
     * @param[in] aSpeed
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginPlay(TUint aInstanceID, const Brx& aSpeed, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndPlay(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     */
    void SyncPause(TUint aInstanceID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndPause().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginPause(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndPause(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     */
    void SyncRecord(TUint aInstanceID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndRecord().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginRecord(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndRecord(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aUnit
     * @param[in]  aTarget
     */
    void SyncSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSeek().
     *
     * @param[in] aInstanceID
     * @param[in] aUnit
     * @param[in] aTarget
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSeek(TUint aInstanceID, const Brx& aUnit, const Brx& aTarget, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSeek(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     */
    void SyncNext(TUint aInstanceID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndNext().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginNext(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndNext(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     */
    void SyncPrevious(TUint aInstanceID);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndPrevious().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginPrevious(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndPrevious(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aNewPlayMode
     */
    void SyncSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetPlayMode().
     *
     * @param[in] aInstanceID
     * @param[in] aNewPlayMode
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetPlayMode(TUint aInstanceID, const Brx& aNewPlayMode, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetPlayMode(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aNewRecordQualityMode
     */
    void SyncSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetRecordQualityMode().
     *
     * @param[in] aInstanceID
     * @param[in] aNewRecordQualityMode
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetRecordQualityMode(TUint aInstanceID, const Brx& aNewRecordQualityMode, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetRecordQualityMode(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aActions
     */
    void SyncGetCurrentTransportActions(TUint aInstanceID, Brh& aActions);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetCurrentTransportActions().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetCurrentTransportActions(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aActions
     */
    void EndGetCurrentTransportActions(IAsync& aAsync, Brh& aActions);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentDRMState
     */
    void SyncGetDRMState(TUint aInstanceID, Brh& aCurrentDRMState);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetDRMState().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetDRMState(TUint aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentDRMState
     */
    void EndGetDRMState(IAsync& aAsync, Brh& aCurrentDRMState);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aStateVariableList
     * @param[out] aStateVariableValuePairs
     */
    void SyncGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, Brh& aStateVariableValuePairs);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetStateVariables().
     *
     * @param[in] aInstanceID
     * @param[in] aStateVariableList
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetStateVariables(TUint aInstanceID, const Brx& aStateVariableList, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aStateVariableValuePairs
     */
    void EndGetStateVariables(IAsync& aAsync, Brh& aStateVariableValuePairs);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aAVTransportUDN
     * @param[in]  aServiceType
     * @param[in]  aServiceId
     * @param[in]  aStateVariableValuePairs
     * @param[out] aStateVariableList
     */
    void SyncSetStateVariables(TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, Brh& aStateVariableList);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetStateVariables().
     *
     * @param[in] aInstanceID
     * @param[in] aAVTransportUDN
     * @param[in] aServiceType
     * @param[in] aServiceId
     * @param[in] aStateVariableValuePairs
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetStateVariables(TUint aInstanceID, const Brx& aAVTransportUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aStateVariableList
     */
    void EndSetStateVariables(IAsync& aAsync, Brh& aStateVariableList);

    /**
     * Set a callback to be run when the LastChange state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgAVTransport2 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyLastChangeChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DRMState state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgAVTransport2 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDRMStateChanged(Functor& aFunctor);

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
     * Query the value of the DRMState property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aDRMState
     */
    void PropertyDRMState(Brhz& aDRMState) const;
private:
    void LastChangePropertyChanged();
    void DRMStatePropertyChanged();
private:
    Action* iActionSetAVTransportURI;
    Action* iActionSetNextAVTransportURI;
    Action* iActionGetMediaInfo;
    Action* iActionGetMediaInfo_Ext;
    Action* iActionGetTransportInfo;
    Action* iActionGetPositionInfo;
    Action* iActionGetDeviceCapabilities;
    Action* iActionGetTransportSettings;
    Action* iActionStop;
    Action* iActionPlay;
    Action* iActionPause;
    Action* iActionRecord;
    Action* iActionSeek;
    Action* iActionNext;
    Action* iActionPrevious;
    Action* iActionSetPlayMode;
    Action* iActionSetRecordQualityMode;
    Action* iActionGetCurrentTransportActions;
    Action* iActionGetDRMState;
    Action* iActionGetStateVariables;
    Action* iActionSetStateVariables;
    PropertyString* iLastChange;
    PropertyString* iDRMState;
    Functor iLastChangeChanged;
    Functor iDRMStateChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_UPNPORGAVTRANSPORT2

