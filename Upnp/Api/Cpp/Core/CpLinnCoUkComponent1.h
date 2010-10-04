#ifndef HEADER_LINNCOUKCOMPONENT1
#define HEADER_LINNCOUKCOMPONENT1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Exception.h>
#include <Functor.h>
#include <FunctorAsync.h>
#include <CpProxy.h>

namespace Zapp {

class CpDevice;
class Action;
class PropertyBinary;
class PropertyBool;
class PropertyInt;
class PropertyString;
class PropertyUint;

/**
 * Proxy for linn.co.uk:Component:1
 */
class CpProxyLinnCoUkComponent1 : public CpProxy
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
    CpProxyLinnCoUkComponent1(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyLinnCoUkComponent1();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaEnabled
     */
    void SyncAmplifierEnabled(TBool& aaEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndAmplifierEnabled().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginAmplifierEnabled(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaEnabled
     */
    void EndAmplifierEnabled(IAsync& aAsync, TBool& aaEnabled);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaEnabled
     */
    void SyncSetAmplifierEnabled(TBool aaEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetAmplifierEnabled().
     *
     * @param[in] aaEnabled
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetAmplifierEnabled(TBool aaEnabled, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetAmplifierEnabled(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaAttenuation
     */
    void SyncAmplifierAttenuation(Brh& aaAttenuation);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndAmplifierAttenuation().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginAmplifierAttenuation(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaAttenuation
     */
    void EndAmplifierAttenuation(IAsync& aAsync, Brh& aaAttenuation);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaAttenuation
     */
    void SyncSetAmplifierAttenuation(const Brx& aaAttenuation);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetAmplifierAttenuation().
     *
     * @param[in] aaAttenuation
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetAmplifierAttenuation(const Brx& aaAttenuation, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetAmplifierAttenuation(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaEnabled
     */
    void SyncSetVolumeControlEnabled(TBool aaEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetVolumeControlEnabled().
     *
     * @param[in] aaEnabled
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetVolumeControlEnabled(TBool aaEnabled, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetVolumeControlEnabled(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaEnabled
     */
    void SyncVolumeControlEnabled(TBool& aaEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndVolumeControlEnabled().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginVolumeControlEnabled(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaEnabled
     */
    void EndVolumeControlEnabled(IAsync& aAsync, TBool& aaEnabled);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaRaw
     */
    void SyncSetDigitalAudioOutputRaw(TBool aaRaw);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDigitalAudioOutputRaw().
     *
     * @param[in] aaRaw
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDigitalAudioOutputRaw(TBool aaRaw, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDigitalAudioOutputRaw(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaRaw
     */
    void SyncDigitalAudioOutputRaw(TBool& aaRaw);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDigitalAudioOutputRaw().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDigitalAudioOutputRaw(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaRaw
     */
    void EndDigitalAudioOutputRaw(IAsync& aAsync, TBool& aaRaw);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaOverTemperature
     */
    void SyncAmplifierOverTemperature(TBool& aaOverTemperature);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndAmplifierOverTemperature().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginAmplifierOverTemperature(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaOverTemperature
     */
    void EndAmplifierOverTemperature(IAsync& aAsync, TBool& aaOverTemperature);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaLinkConnected
     */
    void SyncEthernetLinkConnected(TBool& aaLinkConnected);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndEthernetLinkConnected().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginEthernetLinkConnected(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaLinkConnected
     */
    void EndEthernetLinkConnected(IAsync& aAsync, TBool& aaLinkConnected);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     */
    void SyncLocate();
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndLocate().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginLocate(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndLocate(IAsync& aAsync);

    /**
     * Set a callback to be run when the AmplifierEnabled state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkComponent1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyAmplifierEnabledChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the AmplifierAttenuation state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkComponent1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyAmplifierAttenuationChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the VolumeControlEnabled state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkComponent1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyVolumeControlEnabledChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DigitalAudioOutputRaw state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkComponent1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDigitalAudioOutputRawChanged(Functor& aFunctor);

    /**
     * Query the value of the AmplifierEnabled property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aAmplifierEnabled
     */
    void PropertyAmplifierEnabled(TBool& aAmplifierEnabled) const;
    /**
     * Query the value of the AmplifierAttenuation property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aAmplifierAttenuation
     */
    void PropertyAmplifierAttenuation(Brhz& aAmplifierAttenuation) const;
    /**
     * Query the value of the VolumeControlEnabled property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aVolumeControlEnabled
     */
    void PropertyVolumeControlEnabled(TBool& aVolumeControlEnabled) const;
    /**
     * Query the value of the DigitalAudioOutputRaw property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDigitalAudioOutputRaw
     */
    void PropertyDigitalAudioOutputRaw(TBool& aDigitalAudioOutputRaw) const;
private:
    void AmplifierEnabledPropertyChanged();
    void AmplifierAttenuationPropertyChanged();
    void VolumeControlEnabledPropertyChanged();
    void DigitalAudioOutputRawPropertyChanged();
private:
    Action* iActionAmplifierEnabled;
    Action* iActionSetAmplifierEnabled;
    Action* iActionAmplifierAttenuation;
    Action* iActionSetAmplifierAttenuation;
    Action* iActionSetVolumeControlEnabled;
    Action* iActionVolumeControlEnabled;
    Action* iActionSetDigitalAudioOutputRaw;
    Action* iActionDigitalAudioOutputRaw;
    Action* iActionAmplifierOverTemperature;
    Action* iActionEthernetLinkConnected;
    Action* iActionLocate;
    PropertyBool* iAmplifierEnabled;
    PropertyString* iAmplifierAttenuation;
    PropertyBool* iVolumeControlEnabled;
    PropertyBool* iDigitalAudioOutputRaw;
    Functor iAmplifierEnabledChanged;
    Functor iAmplifierAttenuationChanged;
    Functor iVolumeControlEnabledChanged;
    Functor iDigitalAudioOutputRawChanged;
};

} // namespace Zapp

#endif // HEADER_LINNCOUKCOMPONENT1

