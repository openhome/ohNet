#ifndef HEADER_LINNCOUKUI2CPP
#define HEADER_LINNCOUKUI2CPP

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
 * Proxy for linn.co.uk:Ui:2
 */
class CpProxyLinnCoUkUi2Cpp : public CpProxy
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
    CpProxyLinnCoUkUi2Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyLinnCoUkUi2Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaTestPattern
     */
    void SyncDisplayTestPattern(int32_t aaTestPattern);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplayTestPattern().
     *
     * @param[in] aaTestPattern
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplayTestPattern(int32_t aaTestPattern, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndDisplayTestPattern(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     */
    void SyncDisplayFill();
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplayFill().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplayFill(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndDisplayFill(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     */
    void SyncDisplayClear();
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplayClear().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplayClear(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndDisplayClear(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaEnabled
     */
    void SyncSetTestModeEnabled(bool aaEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetTestModeEnabled().
     *
     * @param[in] aaEnabled
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetTestModeEnabled(bool aaEnabled, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetTestModeEnabled(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaCode
     */
    void SyncSimulateInfraredInput(uint32_t aaCode);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSimulateInfraredInput().
     *
     * @param[in] aaCode
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSimulateInfraredInput(uint32_t aaCode, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSimulateInfraredInput(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaCode
     */
    void SyncSimulateButtonInput(uint32_t aaCode);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSimulateButtonInput().
     *
     * @param[in] aaCode
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSimulateButtonInput(uint32_t aaCode, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSimulateButtonInput(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaLightLevel
     */
    void SyncSimulateLightSensor(uint32_t aaLightLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSimulateLightSensor().
     *
     * @param[in] aaLightLevel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSimulateLightSensor(uint32_t aaLightLevel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSimulateLightSensor(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaLightLevel
     */
    void SyncGetLightSensorData(uint32_t& aaLightLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetLightSensorData().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetLightSensorData(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaLightLevel
     */
    void EndGetLightSensorData(IAsync& aAsync, uint32_t& aaLightLevel);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaBrightness
     */
    void SyncSetDisplayBrightness(uint32_t aaBrightness);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDisplayBrightness().
     *
     * @param[in] aaBrightness
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDisplayBrightness(uint32_t aaBrightness, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDisplayBrightness(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaBrightnessAuto
     */
    void SyncSetDisplayBrightnessAuto(bool aaBrightnessAuto);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDisplayBrightnessAuto().
     *
     * @param[in] aaBrightnessAuto
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDisplayBrightnessAuto(bool aaBrightnessAuto, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDisplayBrightnessAuto(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaCommands
     */
    void SyncSetInfraredCommands(const std::string& aaCommands);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetInfraredCommands().
     *
     * @param[in] aaCommands
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetInfraredCommands(const std::string& aaCommands, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetInfraredCommands(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaCommands
     */
    void SyncInfraredCommands(std::string& aaCommands);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndInfraredCommands().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginInfraredCommands(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaCommands
     */
    void EndInfraredCommands(IAsync& aAsync, std::string& aaCommands);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaCommands
     */
    void SyncSetInfraredTerminalCommands(const std::string& aaCommands);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetInfraredTerminalCommands().
     *
     * @param[in] aaCommands
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetInfraredTerminalCommands(const std::string& aaCommands, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetInfraredTerminalCommands(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaCommands
     */
    void SyncInfraredTerminalCommands(std::string& aaCommands);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndInfraredTerminalCommands().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginInfraredTerminalCommands(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaCommands
     */
    void EndInfraredTerminalCommands(IAsync& aAsync, std::string& aaCommands);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaBrightness
     */
    void SyncDisplayBrightness(uint32_t& aaBrightness);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplayBrightness().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplayBrightness(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaBrightness
     */
    void EndDisplayBrightness(IAsync& aAsync, uint32_t& aaBrightness);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaBrightnessAuto
     */
    void SyncDisplayBrightnessAuto(bool& aaBrightnessAuto);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplayBrightnessAuto().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplayBrightnessAuto(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaBrightnessAuto
     */
    void EndDisplayBrightnessAuto(IAsync& aAsync, bool& aaBrightnessAuto);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaUpsideDown
     */
    void SyncDisplayUpsideDown(bool& aaUpsideDown);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplayUpsideDown().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplayUpsideDown(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaUpsideDown
     */
    void EndDisplayUpsideDown(IAsync& aAsync, bool& aaUpsideDown);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaUpsideDown
     */
    void SyncSetDisplayUpsideDown(bool aaUpsideDown);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDisplayUpsideDown().
     *
     * @param[in] aaUpsideDown
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDisplayUpsideDown(bool aaUpsideDown, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDisplayUpsideDown(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaDisplayScrollText
     */
    void SyncSetDisplayScrollText(bool aaDisplayScrollText);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDisplayScrollText().
     *
     * @param[in] aaDisplayScrollText
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDisplayScrollText(bool aaDisplayScrollText, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDisplayScrollText(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaDisplayScrollTextEnabled
     */
    void SyncDisplayScrollText(bool& aaDisplayScrollTextEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplayScrollText().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplayScrollText(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaDisplayScrollTextEnabled
     */
    void EndDisplayScrollText(IAsync& aAsync, bool& aaDisplayScrollTextEnabled);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaEnabled
     */
    void SyncSetDisplaySleep(bool aaEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDisplaySleep().
     *
     * @param[in] aaEnabled
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDisplaySleep(bool aaEnabled, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDisplaySleep(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaEnabled
     */
    void SyncDisplaySleep(bool& aaEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplaySleep().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplaySleep(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaEnabled
     */
    void EndDisplaySleep(IAsync& aAsync, bool& aaEnabled);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaOff
     */
    void SyncSetDisplayLedOff(bool aaOff);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDisplayLedOff().
     *
     * @param[in] aaOff
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDisplayLedOff(bool aaOff, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDisplayLedOff(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaOff
     */
    void SyncDisplayLedOff(bool& aaOff);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDisplayLedOff().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDisplayLedOff(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaOff
     */
    void EndDisplayLedOff(IAsync& aAsync, bool& aaOff);

    /**
     * Set a callback to be run when the DisplayBrightness state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDisplayBrightnessChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DisplayBrightnessAuto state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDisplayBrightnessAutoChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the InfraredCommands state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyInfraredCommandsChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the InfraredTerminalCommands state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyInfraredTerminalCommandsChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DisplayUpsideDown state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDisplayUpsideDownChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DisplayScrollText state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDisplayScrollTextChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DisplaySleep state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDisplaySleepChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DisplayLedOff state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDisplayLedOffChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TerminalInputCode state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTerminalInputCodeChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the TerminalInputName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyTerminalInputNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DisplayPixels state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkUi2Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDisplayPixelsChanged(Functor& aFunctor);

    /**
     * Query the value of the DisplayBrightness property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDisplayBrightness
     */
    void PropertyDisplayBrightness(uint32_t& aDisplayBrightness) const;
    /**
     * Query the value of the DisplayBrightnessAuto property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDisplayBrightnessAuto
     */
    void PropertyDisplayBrightnessAuto(bool& aDisplayBrightnessAuto) const;
    /**
     * Query the value of the InfraredCommands property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aInfraredCommands
     */
    void PropertyInfraredCommands(std::string& aInfraredCommands) const;
    /**
     * Query the value of the InfraredTerminalCommands property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aInfraredTerminalCommands
     */
    void PropertyInfraredTerminalCommands(std::string& aInfraredTerminalCommands) const;
    /**
     * Query the value of the DisplayUpsideDown property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDisplayUpsideDown
     */
    void PropertyDisplayUpsideDown(bool& aDisplayUpsideDown) const;
    /**
     * Query the value of the DisplayScrollText property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDisplayScrollText
     */
    void PropertyDisplayScrollText(bool& aDisplayScrollText) const;
    /**
     * Query the value of the DisplaySleep property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDisplaySleep
     */
    void PropertyDisplaySleep(bool& aDisplaySleep) const;
    /**
     * Query the value of the DisplayLedOff property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDisplayLedOff
     */
    void PropertyDisplayLedOff(bool& aDisplayLedOff) const;
    /**
     * Query the value of the TerminalInputCode property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTerminalInputCode
     */
    void PropertyTerminalInputCode(uint32_t& aTerminalInputCode) const;
    /**
     * Query the value of the TerminalInputName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aTerminalInputName
     */
    void PropertyTerminalInputName(std::string& aTerminalInputName) const;
    /**
     * Query the value of the DisplayPixels property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDisplayPixels
     */
    void PropertyDisplayPixels(std::string& aDisplayPixels) const;
private:
    void DisplayBrightnessPropertyChanged();
    void DisplayBrightnessAutoPropertyChanged();
    void InfraredCommandsPropertyChanged();
    void InfraredTerminalCommandsPropertyChanged();
    void DisplayUpsideDownPropertyChanged();
    void DisplayScrollTextPropertyChanged();
    void DisplaySleepPropertyChanged();
    void DisplayLedOffPropertyChanged();
    void TerminalInputCodePropertyChanged();
    void TerminalInputNamePropertyChanged();
    void DisplayPixelsPropertyChanged();
private:
    Action* iActionDisplayTestPattern;
    Action* iActionDisplayFill;
    Action* iActionDisplayClear;
    Action* iActionSetTestModeEnabled;
    Action* iActionSimulateInfraredInput;
    Action* iActionSimulateButtonInput;
    Action* iActionSimulateLightSensor;
    Action* iActionGetLightSensorData;
    Action* iActionSetDisplayBrightness;
    Action* iActionSetDisplayBrightnessAuto;
    Action* iActionSetInfraredCommands;
    Action* iActionInfraredCommands;
    Action* iActionSetInfraredTerminalCommands;
    Action* iActionInfraredTerminalCommands;
    Action* iActionDisplayBrightness;
    Action* iActionDisplayBrightnessAuto;
    Action* iActionDisplayUpsideDown;
    Action* iActionSetDisplayUpsideDown;
    Action* iActionSetDisplayScrollText;
    Action* iActionDisplayScrollText;
    Action* iActionSetDisplaySleep;
    Action* iActionDisplaySleep;
    Action* iActionSetDisplayLedOff;
    Action* iActionDisplayLedOff;
    PropertyUint* iDisplayBrightness;
    PropertyBool* iDisplayBrightnessAuto;
    PropertyString* iInfraredCommands;
    PropertyString* iInfraredTerminalCommands;
    PropertyBool* iDisplayUpsideDown;
    PropertyBool* iDisplayScrollText;
    PropertyBool* iDisplaySleep;
    PropertyBool* iDisplayLedOff;
    PropertyUint* iTerminalInputCode;
    PropertyString* iTerminalInputName;
    PropertyBinary* iDisplayPixels;
    Functor iDisplayBrightnessChanged;
    Functor iDisplayBrightnessAutoChanged;
    Functor iInfraredCommandsChanged;
    Functor iInfraredTerminalCommandsChanged;
    Functor iDisplayUpsideDownChanged;
    Functor iDisplayScrollTextChanged;
    Functor iDisplaySleepChanged;
    Functor iDisplayLedOffChanged;
    Functor iTerminalInputCodeChanged;
    Functor iTerminalInputNameChanged;
    Functor iDisplayPixelsChanged;
};

} // namespace Zapp

#endif // HEADER_LINNCOUKUI2CPP

