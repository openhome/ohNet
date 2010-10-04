#ifndef HEADER_LINNCOUKDS1CPP
#define HEADER_LINNCOUKDS1CPP

#include <ZappTypes.h>
#include <Exception.h>
#include <Functor.h>
#include <FunctorAsync.h>
#include <CpProxy.h>

#include <string>

namespace Zapp {

class CpDeviceCpp;
class Action;
class PropertyBinary;
class PropertyBool;
class PropertyInt;
class PropertyString;
class PropertyUint;

/**
 * Proxy for linn.co.uk:Ds:1
 */
class CpProxyLinnCoUkDs1Cpp : public CpProxy
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
    CpProxyLinnCoUkDs1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyLinnCoUkDs1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     */
    void SyncPlay();
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndPlay().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginPlay(FunctorAsync& aFunctor);
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
     */
    void SyncPause();
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndPause().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginPause(FunctorAsync& aFunctor);
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
     */
    void SyncStop();
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndStop().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginStop(FunctorAsync& aFunctor);
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
     * @param[in]  aaSecond
     */
    void SyncSeekSecondAbsolute(uint32_t aaSecond);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSeekSecondAbsolute().
     *
     * @param[in] aaSecond
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSeekSecondAbsolute(uint32_t aaSecond, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSeekSecondAbsolute(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSecond
     */
    void SyncSeekSecondRelative(int32_t aaSecond);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSeekSecondRelative().
     *
     * @param[in] aaSecond
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSeekSecondRelative(int32_t aaSecond, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSeekSecondRelative(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaTrackId
     */
    void SyncSeekTrackId(uint32_t aaTrackId);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSeekTrackId().
     *
     * @param[in] aaTrackId
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSeekTrackId(uint32_t aaTrackId, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSeekTrackId(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaTrack
     */
    void SyncSeekTrackAbsolute(uint32_t aaTrack);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSeekTrackAbsolute().
     *
     * @param[in] aaTrack
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSeekTrackAbsolute(uint32_t aaTrack, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSeekTrackAbsolute(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaTrack
     */
    void SyncSeekTrackRelative(int32_t aaTrack);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSeekTrackRelative().
     *
     * @param[in] aaTrack
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSeekTrackRelative(int32_t aaTrack, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSeekTrackRelative(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaTransportState
     * @param[out] aaTrackDuration
     * @param[out] aaTrackBitRate
     * @param[out] aaTrackLossless
     * @param[out] aaTrackBitDepth
     * @param[out] aaTrackSampleRate
     * @param[out] aaTrackCodecName
     * @param[out] aaTrackId
     */
    void SyncState(std::string& aaTransportState, uint32_t& aaTrackDuration, uint32_t& aaTrackBitRate, bool& aaTrackLossless, uint32_t& aaTrackBitDepth, uint32_t& aaTrackSampleRate, std::string& aaTrackCodecName, uint32_t& aaTrackId);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndState().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginState(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaTransportState
     * @param[out] aaTrackDuration
     * @param[out] aaTrackBitRate
     * @param[out] aaTrackLossless
     * @param[out] aaTrackBitDepth
     * @param[out] aaTrackSampleRate
     * @param[out] aaTrackCodecName
     * @param[out] aaTrackId
     */
    void EndState(IAsync& aAsync, std::string& aaTransportState, uint32_t& aaTrackDuration, uint32_t& aaTrackBitRate, bool& aaTrackLossless, uint32_t& aaTrackBitDepth, uint32_t& aaTrackSampleRate, std::string& aaTrackCodecName, uint32_t& aaTrackId);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaSupportedProtocols
     */
    void SyncProtocolInfo(std::string& aaSupportedProtocols);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndProtocolInfo().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginProtocolInfo(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSupportedProtocols
     */
    void EndProtocolInfo(IAsync& aAsync, std::string& aaSupportedProtocols);

    /**
     * Set a callback to be run when the SupportedProtocols state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySupportedProtocolsChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TrackDuration state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTrackDurationChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TrackBitRate state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTrackBitRateChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TrackLossless state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTrackLosslessChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TrackBitDepth state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTrackBitDepthChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TrackSampleRate state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTrackSampleRateChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TrackCodecName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTrackCodecNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TrackId state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTrackIdChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TransportState state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkDs1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTransportStateChanged(Functor& aFunctor);

    /**
     * Query the value of the SupportedProtocols property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aSupportedProtocols
     */
    void PropertySupportedProtocols(std::string& aSupportedProtocols) const;
    /**
     * Query the value of the TrackDuration property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTrackDuration
     */
    void PropertyTrackDuration(uint32_t& aTrackDuration) const;
    /**
     * Query the value of the TrackBitRate property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTrackBitRate
     */
    void PropertyTrackBitRate(uint32_t& aTrackBitRate) const;
    /**
     * Query the value of the TrackLossless property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTrackLossless
     */
    void PropertyTrackLossless(bool& aTrackLossless) const;
    /**
     * Query the value of the TrackBitDepth property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTrackBitDepth
     */
    void PropertyTrackBitDepth(uint32_t& aTrackBitDepth) const;
    /**
     * Query the value of the TrackSampleRate property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTrackSampleRate
     */
    void PropertyTrackSampleRate(uint32_t& aTrackSampleRate) const;
    /**
     * Query the value of the TrackCodecName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTrackCodecName
     */
    void PropertyTrackCodecName(std::string& aTrackCodecName) const;
    /**
     * Query the value of the TrackId property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTrackId
     */
    void PropertyTrackId(uint32_t& aTrackId) const;
    /**
     * Query the value of the TransportState property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTransportState
     */
    void PropertyTransportState(std::string& aTransportState) const;
private:
    void SupportedProtocolsPropertyChanged();
    void TrackDurationPropertyChanged();
    void TrackBitRatePropertyChanged();
    void TrackLosslessPropertyChanged();
    void TrackBitDepthPropertyChanged();
    void TrackSampleRatePropertyChanged();
    void TrackCodecNamePropertyChanged();
    void TrackIdPropertyChanged();
    void TransportStatePropertyChanged();
private:
    Action* iActionPlay;
    Action* iActionPause;
    Action* iActionStop;
    Action* iActionSeekSecondAbsolute;
    Action* iActionSeekSecondRelative;
    Action* iActionSeekTrackId;
    Action* iActionSeekTrackAbsolute;
    Action* iActionSeekTrackRelative;
    Action* iActionState;
    Action* iActionProtocolInfo;
    PropertyString* iSupportedProtocols;
    PropertyUint* iTrackDuration;
    PropertyUint* iTrackBitRate;
    PropertyBool* iTrackLossless;
    PropertyUint* iTrackBitDepth;
    PropertyUint* iTrackSampleRate;
    PropertyString* iTrackCodecName;
    PropertyUint* iTrackId;
    PropertyString* iTransportState;
    Functor iSupportedProtocolsChanged;
    Functor iTrackDurationChanged;
    Functor iTrackBitRateChanged;
    Functor iTrackLosslessChanged;
    Functor iTrackBitDepthChanged;
    Functor iTrackSampleRateChanged;
    Functor iTrackCodecNameChanged;
    Functor iTrackIdChanged;
    Functor iTransportStateChanged;
};

} // namespace Zapp

#endif // HEADER_LINNCOUKDS1CPP

