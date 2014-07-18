#ifndef HEADER_UPNPORGRENDERINGCONTROL1CPP
#define HEADER_UPNPORGRENDERINGCONTROL1CPP

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
 * Proxy for upnp.org:RenderingControl:1
 * @ingroup Proxies
 */
class CpProxyUpnpOrgRenderingControl1Cpp : public CpProxy
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
    CpProxyUpnpOrgRenderingControl1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyUpnpOrgRenderingControl1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentPresetNameList
     */
    void SyncListPresets(uint32_t aInstanceID, std::string& aCurrentPresetNameList);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndListPresets().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginListPresets(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentPresetNameList
     */
    void EndListPresets(IAsync& aAsync, std::string& aCurrentPresetNameList);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aPresetName
     */
    void SyncSelectPreset(uint32_t aInstanceID, const std::string& aPresetName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSelectPreset().
     *
     * @param[in] aInstanceID
     * @param[in] aPresetName
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSelectPreset(uint32_t aInstanceID, const std::string& aPresetName, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSelectPreset(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentBrightness
     */
    void SyncGetBrightness(uint32_t aInstanceID, uint32_t& aCurrentBrightness);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetBrightness().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetBrightness(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentBrightness
     */
    void EndGetBrightness(IAsync& aAsync, uint32_t& aCurrentBrightness);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredBrightness
     */
    void SyncSetBrightness(uint32_t aInstanceID, uint32_t aDesiredBrightness);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetBrightness().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredBrightness
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetBrightness(uint32_t aInstanceID, uint32_t aDesiredBrightness, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetBrightness(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentContrast
     */
    void SyncGetContrast(uint32_t aInstanceID, uint32_t& aCurrentContrast);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetContrast().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetContrast(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentContrast
     */
    void EndGetContrast(IAsync& aAsync, uint32_t& aCurrentContrast);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredContrast
     */
    void SyncSetContrast(uint32_t aInstanceID, uint32_t aDesiredContrast);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetContrast().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredContrast
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetContrast(uint32_t aInstanceID, uint32_t aDesiredContrast, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetContrast(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentSharpness
     */
    void SyncGetSharpness(uint32_t aInstanceID, uint32_t& aCurrentSharpness);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetSharpness().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetSharpness(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentSharpness
     */
    void EndGetSharpness(IAsync& aAsync, uint32_t& aCurrentSharpness);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredSharpness
     */
    void SyncSetSharpness(uint32_t aInstanceID, uint32_t aDesiredSharpness);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetSharpness().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredSharpness
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetSharpness(uint32_t aInstanceID, uint32_t aDesiredSharpness, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetSharpness(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentRedVideoGain
     */
    void SyncGetRedVideoGain(uint32_t aInstanceID, uint32_t& aCurrentRedVideoGain);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetRedVideoGain().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetRedVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentRedVideoGain
     */
    void EndGetRedVideoGain(IAsync& aAsync, uint32_t& aCurrentRedVideoGain);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredRedVideoGain
     */
    void SyncSetRedVideoGain(uint32_t aInstanceID, uint32_t aDesiredRedVideoGain);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetRedVideoGain().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredRedVideoGain
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetRedVideoGain(uint32_t aInstanceID, uint32_t aDesiredRedVideoGain, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetRedVideoGain(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentGreenVideoGain
     */
    void SyncGetGreenVideoGain(uint32_t aInstanceID, uint32_t& aCurrentGreenVideoGain);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetGreenVideoGain().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetGreenVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentGreenVideoGain
     */
    void EndGetGreenVideoGain(IAsync& aAsync, uint32_t& aCurrentGreenVideoGain);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredGreenVideoGain
     */
    void SyncSetGreenVideoGain(uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetGreenVideoGain().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredGreenVideoGain
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetGreenVideoGain(uint32_t aInstanceID, uint32_t aDesiredGreenVideoGain, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetGreenVideoGain(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentBlueVideoGain
     */
    void SyncGetBlueVideoGain(uint32_t aInstanceID, uint32_t& aCurrentBlueVideoGain);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetBlueVideoGain().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetBlueVideoGain(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentBlueVideoGain
     */
    void EndGetBlueVideoGain(IAsync& aAsync, uint32_t& aCurrentBlueVideoGain);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredBlueVideoGain
     */
    void SyncSetBlueVideoGain(uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetBlueVideoGain().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredBlueVideoGain
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetBlueVideoGain(uint32_t aInstanceID, uint32_t aDesiredBlueVideoGain, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetBlueVideoGain(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentRedVideoBlackLevel
     */
    void SyncGetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentRedVideoBlackLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetRedVideoBlackLevel().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetRedVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentRedVideoBlackLevel
     */
    void EndGetRedVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentRedVideoBlackLevel);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredRedVideoBlackLevel
     */
    void SyncSetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetRedVideoBlackLevel().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredRedVideoBlackLevel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetRedVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredRedVideoBlackLevel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetRedVideoBlackLevel(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentGreenVideoBlackLevel
     */
    void SyncGetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentGreenVideoBlackLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetGreenVideoBlackLevel().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetGreenVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentGreenVideoBlackLevel
     */
    void EndGetGreenVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentGreenVideoBlackLevel);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredGreenVideoBlackLevel
     */
    void SyncSetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetGreenVideoBlackLevel().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredGreenVideoBlackLevel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetGreenVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredGreenVideoBlackLevel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetGreenVideoBlackLevel(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentBlueVideoBlackLevel
     */
    void SyncGetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t& aCurrentBlueVideoBlackLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetBlueVideoBlackLevel().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetBlueVideoBlackLevel(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentBlueVideoBlackLevel
     */
    void EndGetBlueVideoBlackLevel(IAsync& aAsync, uint32_t& aCurrentBlueVideoBlackLevel);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredBlueVideoBlackLevel
     */
    void SyncSetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetBlueVideoBlackLevel().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredBlueVideoBlackLevel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetBlueVideoBlackLevel(uint32_t aInstanceID, uint32_t aDesiredBlueVideoBlackLevel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetBlueVideoBlackLevel(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentColorTemperature
     */
    void SyncGetColorTemperature(uint32_t aInstanceID, uint32_t& aCurrentColorTemperature);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetColorTemperature().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetColorTemperature(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentColorTemperature
     */
    void EndGetColorTemperature(IAsync& aAsync, uint32_t& aCurrentColorTemperature);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredColorTemperature
     */
    void SyncSetColorTemperature(uint32_t aInstanceID, uint32_t aDesiredColorTemperature);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetColorTemperature().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredColorTemperature
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetColorTemperature(uint32_t aInstanceID, uint32_t aDesiredColorTemperature, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetColorTemperature(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentHorizontalKeystone
     */
    void SyncGetHorizontalKeystone(uint32_t aInstanceID, int32_t& aCurrentHorizontalKeystone);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetHorizontalKeystone().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetHorizontalKeystone(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentHorizontalKeystone
     */
    void EndGetHorizontalKeystone(IAsync& aAsync, int32_t& aCurrentHorizontalKeystone);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredHorizontalKeystone
     */
    void SyncSetHorizontalKeystone(uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetHorizontalKeystone().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredHorizontalKeystone
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetHorizontalKeystone(uint32_t aInstanceID, int32_t aDesiredHorizontalKeystone, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetHorizontalKeystone(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[out] aCurrentVerticalKeystone
     */
    void SyncGetVerticalKeystone(uint32_t aInstanceID, int32_t& aCurrentVerticalKeystone);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetVerticalKeystone().
     *
     * @param[in] aInstanceID
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetVerticalKeystone(uint32_t aInstanceID, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentVerticalKeystone
     */
    void EndGetVerticalKeystone(IAsync& aAsync, int32_t& aCurrentVerticalKeystone);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aDesiredVerticalKeystone
     */
    void SyncSetVerticalKeystone(uint32_t aInstanceID, int32_t aDesiredVerticalKeystone);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetVerticalKeystone().
     *
     * @param[in] aInstanceID
     * @param[in] aDesiredVerticalKeystone
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetVerticalKeystone(uint32_t aInstanceID, int32_t aDesiredVerticalKeystone, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetVerticalKeystone(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[out] aCurrentMute
     */
    void SyncGetMute(uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentMute);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetMute().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetMute(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentMute
     */
    void EndGetMute(IAsync& aAsync, bool& aCurrentMute);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[in]  aDesiredMute
     */
    void SyncSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetMute().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aDesiredMute
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetMute(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredMute, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetMute(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[out] aCurrentVolume
     */
    void SyncGetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t& aCurrentVolume);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetVolume().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetVolume(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentVolume
     */
    void EndGetVolume(IAsync& aAsync, uint32_t& aCurrentVolume);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[in]  aDesiredVolume
     */
    void SyncSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetVolume().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aDesiredVolume
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetVolume(uint32_t aInstanceID, const std::string& aChannel, uint32_t aDesiredVolume, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetVolume(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[out] aCurrentVolume
     */
    void SyncGetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t& aCurrentVolume);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetVolumeDB().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentVolume
     */
    void EndGetVolumeDB(IAsync& aAsync, int32_t& aCurrentVolume);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[in]  aDesiredVolume
     */
    void SyncSetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetVolumeDB().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aDesiredVolume
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetVolumeDB(uint32_t aInstanceID, const std::string& aChannel, int32_t aDesiredVolume, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetVolumeDB(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[out] aMinValue
     * @param[out] aMaxValue
     */
    void SyncGetVolumeDBRange(uint32_t aInstanceID, const std::string& aChannel, int32_t& aMinValue, int32_t& aMaxValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetVolumeDBRange().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetVolumeDBRange(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aMinValue
     * @param[out] aMaxValue
     */
    void EndGetVolumeDBRange(IAsync& aAsync, int32_t& aMinValue, int32_t& aMaxValue);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[out] aCurrentLoudness
     */
    void SyncGetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool& aCurrentLoudness);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetLoudness().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetLoudness(uint32_t aInstanceID, const std::string& aChannel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aCurrentLoudness
     */
    void EndGetLoudness(IAsync& aAsync, bool& aCurrentLoudness);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aInstanceID
     * @param[in]  aChannel
     * @param[in]  aDesiredLoudness
     */
    void SyncSetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetLoudness().
     *
     * @param[in] aInstanceID
     * @param[in] aChannel
     * @param[in] aDesiredLoudness
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetLoudness(uint32_t aInstanceID, const std::string& aChannel, bool aDesiredLoudness, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetLoudness(IAsync& aAsync);

    /**
     * Set a callback to be run when the LastChange state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgRenderingControl1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyLastChangeChanged(Functor& aFunctor);

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
private:
    void LastChangePropertyChanged();
private:
    Action* iActionListPresets;
    Action* iActionSelectPreset;
    Action* iActionGetBrightness;
    Action* iActionSetBrightness;
    Action* iActionGetContrast;
    Action* iActionSetContrast;
    Action* iActionGetSharpness;
    Action* iActionSetSharpness;
    Action* iActionGetRedVideoGain;
    Action* iActionSetRedVideoGain;
    Action* iActionGetGreenVideoGain;
    Action* iActionSetGreenVideoGain;
    Action* iActionGetBlueVideoGain;
    Action* iActionSetBlueVideoGain;
    Action* iActionGetRedVideoBlackLevel;
    Action* iActionSetRedVideoBlackLevel;
    Action* iActionGetGreenVideoBlackLevel;
    Action* iActionSetGreenVideoBlackLevel;
    Action* iActionGetBlueVideoBlackLevel;
    Action* iActionSetBlueVideoBlackLevel;
    Action* iActionGetColorTemperature;
    Action* iActionSetColorTemperature;
    Action* iActionGetHorizontalKeystone;
    Action* iActionSetHorizontalKeystone;
    Action* iActionGetVerticalKeystone;
    Action* iActionSetVerticalKeystone;
    Action* iActionGetMute;
    Action* iActionSetMute;
    Action* iActionGetVolume;
    Action* iActionSetVolume;
    Action* iActionGetVolumeDB;
    Action* iActionSetVolumeDB;
    Action* iActionGetVolumeDBRange;
    Action* iActionGetLoudness;
    Action* iActionSetLoudness;
    PropertyString* iLastChange;
    Functor iLastChangeChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_UPNPORGRENDERINGCONTROL1CPP

