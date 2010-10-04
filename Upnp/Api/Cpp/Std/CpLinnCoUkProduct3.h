#ifndef HEADER_LINNCOUKPRODUCT3CPP
#define HEADER_LINNCOUKPRODUCT3CPP

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
 * Proxy for linn.co.uk:Product:3
 */
class CpProxyLinnCoUkProduct3Cpp : public CpProxy
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
    CpProxyLinnCoUkProduct3Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyLinnCoUkProduct3Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaType
     */
    void SyncType(std::string& aaType);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndType().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginType(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaType
     */
    void EndType(IAsync& aAsync, std::string& aaType);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaModel
     */
    void SyncModel(std::string& aaModel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndModel().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginModel(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaModel
     */
    void EndModel(IAsync& aAsync, std::string& aaModel);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaName
     */
    void SyncName(std::string& aaName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndName().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginName(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaName
     */
    void EndName(IAsync& aAsync, std::string& aaName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaName
     */
    void SyncSetName(const std::string& aaName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetName().
     *
     * @param[in] aaName
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetName(const std::string& aaName, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetName(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaRoom
     */
    void SyncRoom(std::string& aaRoom);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndRoom().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginRoom(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaRoom
     */
    void EndRoom(IAsync& aAsync, std::string& aaRoom);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaRoom
     */
    void SyncSetRoom(const std::string& aaRoom);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetRoom().
     *
     * @param[in] aaRoom
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetRoom(const std::string& aaRoom, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetRoom(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaStandby
     */
    void SyncStandby(bool& aaStandby);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndStandby().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginStandby(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaStandby
     */
    void EndStandby(IAsync& aAsync, bool& aaStandby);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaStandby
     */
    void SyncSetStandby(bool aaStandby);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetStandby().
     *
     * @param[in] aaStandby
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetStandby(bool aaStandby, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetStandby(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaSourceCount
     */
    void SyncSourceCount(uint32_t& aaSourceCount);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceCount().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceCount(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceCount
     */
    void EndSourceCount(IAsync& aAsync, uint32_t& aaSourceCount);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaSourceXml
     */
    void SyncSourceXml(std::string& aaSourceXml);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceXml().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceXml(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceXml
     */
    void EndSourceXml(IAsync& aAsync, std::string& aaSourceXml);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaSourceIndex
     */
    void SyncSourceIndex(uint32_t& aaSourceIndex);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceIndex().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceIndex(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceIndex
     */
    void EndSourceIndex(IAsync& aAsync, uint32_t& aaSourceIndex);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     */
    void SyncSetSourceIndex(uint32_t aaSourceIndex);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetSourceIndex().
     *
     * @param[in] aaSourceIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetSourceIndex(uint32_t aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetSourceIndex(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceName
     */
    void SyncSetSourceIndexByName(const std::string& aaSourceName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetSourceIndexByName().
     *
     * @param[in] aaSourceName
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetSourceIndexByName(const std::string& aaSourceName, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetSourceIndexByName(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceName
     */
    void SyncSetStartupSourceIndexByName(const std::string& aaSourceName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetStartupSourceIndexByName().
     *
     * @param[in] aaSourceName
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetStartupSourceIndexByName(const std::string& aaSourceName, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetStartupSourceIndexByName(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaSourceIndex
     */
    void SyncStartupSourceIndex(uint32_t& aaSourceIndex);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndStartupSourceIndex().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginStartupSourceIndex(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceIndex
     */
    void EndStartupSourceIndex(IAsync& aAsync, uint32_t& aaSourceIndex);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     */
    void SyncSetStartupSourceIndex(uint32_t aaSourceIndex);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetStartupSourceIndex().
     *
     * @param[in] aaSourceIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetStartupSourceIndex(uint32_t aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetStartupSourceIndex(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaStartupSourceEnabled
     */
    void SyncStartupSourceEnabled(bool& aaStartupSourceEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndStartupSourceEnabled().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginStartupSourceEnabled(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaStartupSourceEnabled
     */
    void EndStartupSourceEnabled(IAsync& aAsync, bool& aaStartupSourceEnabled);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaStartupSourceEnabled
     */
    void SyncSetStartupSourceEnabled(bool aaStartupSourceEnabled);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetStartupSourceEnabled().
     *
     * @param[in] aaStartupSourceEnabled
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetStartupSourceEnabled(bool aaStartupSourceEnabled, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetStartupSourceEnabled(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[out] aaSourceName
     */
    void SyncSourceSystemName(uint32_t aaSourceIndex, std::string& aaSourceName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceSystemName().
     *
     * @param[in] aaSourceIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceSystemName(uint32_t aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceName
     */
    void EndSourceSystemName(IAsync& aAsync, std::string& aaSourceName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[out] aaSourceName
     */
    void SyncSourceName(uint32_t aaSourceIndex, std::string& aaSourceName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceName().
     *
     * @param[in] aaSourceIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceName(uint32_t aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceName
     */
    void EndSourceName(IAsync& aAsync, std::string& aaSourceName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[in]  aaSourceName
     */
    void SyncSetSourceName(uint32_t aaSourceIndex, const std::string& aaSourceName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetSourceName().
     *
     * @param[in] aaSourceIndex
     * @param[in] aaSourceName
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetSourceName(uint32_t aaSourceIndex, const std::string& aaSourceName, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetSourceName(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[out] aaSourceType
     */
    void SyncSourceType(uint32_t aaSourceIndex, std::string& aaSourceType);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceType().
     *
     * @param[in] aaSourceIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceType(uint32_t aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceType
     */
    void EndSourceType(IAsync& aAsync, std::string& aaSourceType);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[out] aaSourceVisible
     */
    void SyncSourceVisible(uint32_t aaSourceIndex, bool& aaSourceVisible);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSourceVisible().
     *
     * @param[in] aaSourceIndex
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSourceVisible(uint32_t aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceVisible
     */
    void EndSourceVisible(IAsync& aAsync, bool& aaSourceVisible);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[in]  aaSourceVisible
     */
    void SyncSetSourceVisible(uint32_t aaSourceIndex, bool aaSourceVisible);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetSourceVisible().
     *
     * @param[in] aaSourceIndex
     * @param[in] aaSourceVisible
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetSourceVisible(uint32_t aaSourceIndex, bool aaSourceVisible, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetSourceVisible(IAsync& aAsync);

    /**
     * Set a callback to be run when the ProductType state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductTypeChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductModel state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductModelChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductRoom state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductRoomChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductStandby state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductStandbyChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductSourceIndex state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductSourceIndexChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductSourceCount state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductSourceCountChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductSourceXml state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductSourceXmlChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the StartupSourceIndex state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyStartupSourceIndexChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the StartupSourceEnabled state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyStartupSourceEnabledChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductAnySourceName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductAnySourceNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductAnySourceVisible state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductAnySourceVisibleChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductAnySourceType state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductAnySourceTypeChanged(Functor& aFunctor);

    /**
     * Query the value of the ProductType property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductType
     */
    void PropertyProductType(std::string& aProductType) const;
    /**
     * Query the value of the ProductModel property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductModel
     */
    void PropertyProductModel(std::string& aProductModel) const;
    /**
     * Query the value of the ProductName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductName
     */
    void PropertyProductName(std::string& aProductName) const;
    /**
     * Query the value of the ProductRoom property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductRoom
     */
    void PropertyProductRoom(std::string& aProductRoom) const;
    /**
     * Query the value of the ProductStandby property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductStandby
     */
    void PropertyProductStandby(bool& aProductStandby) const;
    /**
     * Query the value of the ProductSourceIndex property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductSourceIndex
     */
    void PropertyProductSourceIndex(uint32_t& aProductSourceIndex) const;
    /**
     * Query the value of the ProductSourceCount property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductSourceCount
     */
    void PropertyProductSourceCount(uint32_t& aProductSourceCount) const;
    /**
     * Query the value of the ProductSourceXml property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductSourceXml
     */
    void PropertyProductSourceXml(std::string& aProductSourceXml) const;
    /**
     * Query the value of the StartupSourceIndex property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aStartupSourceIndex
     */
    void PropertyStartupSourceIndex(uint32_t& aStartupSourceIndex) const;
    /**
     * Query the value of the StartupSourceEnabled property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aStartupSourceEnabled
     */
    void PropertyStartupSourceEnabled(bool& aStartupSourceEnabled) const;
    /**
     * Query the value of the ProductAnySourceName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductAnySourceName
     */
    void PropertyProductAnySourceName(uint32_t& aProductAnySourceName) const;
    /**
     * Query the value of the ProductAnySourceVisible property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductAnySourceVisible
     */
    void PropertyProductAnySourceVisible(uint32_t& aProductAnySourceVisible) const;
    /**
     * Query the value of the ProductAnySourceType property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductAnySourceType
     */
    void PropertyProductAnySourceType(uint32_t& aProductAnySourceType) const;
private:
    void ProductTypePropertyChanged();
    void ProductModelPropertyChanged();
    void ProductNamePropertyChanged();
    void ProductRoomPropertyChanged();
    void ProductStandbyPropertyChanged();
    void ProductSourceIndexPropertyChanged();
    void ProductSourceCountPropertyChanged();
    void ProductSourceXmlPropertyChanged();
    void StartupSourceIndexPropertyChanged();
    void StartupSourceEnabledPropertyChanged();
    void ProductAnySourceNamePropertyChanged();
    void ProductAnySourceVisiblePropertyChanged();
    void ProductAnySourceTypePropertyChanged();
private:
    Action* iActionType;
    Action* iActionModel;
    Action* iActionName;
    Action* iActionSetName;
    Action* iActionRoom;
    Action* iActionSetRoom;
    Action* iActionStandby;
    Action* iActionSetStandby;
    Action* iActionSourceCount;
    Action* iActionSourceXml;
    Action* iActionSourceIndex;
    Action* iActionSetSourceIndex;
    Action* iActionSetSourceIndexByName;
    Action* iActionSetStartupSourceIndexByName;
    Action* iActionStartupSourceIndex;
    Action* iActionSetStartupSourceIndex;
    Action* iActionStartupSourceEnabled;
    Action* iActionSetStartupSourceEnabled;
    Action* iActionSourceSystemName;
    Action* iActionSourceName;
    Action* iActionSetSourceName;
    Action* iActionSourceType;
    Action* iActionSourceVisible;
    Action* iActionSetSourceVisible;
    PropertyString* iProductType;
    PropertyString* iProductModel;
    PropertyString* iProductName;
    PropertyString* iProductRoom;
    PropertyBool* iProductStandby;
    PropertyUint* iProductSourceIndex;
    PropertyUint* iProductSourceCount;
    PropertyString* iProductSourceXml;
    PropertyUint* iStartupSourceIndex;
    PropertyBool* iStartupSourceEnabled;
    PropertyUint* iProductAnySourceName;
    PropertyUint* iProductAnySourceVisible;
    PropertyUint* iProductAnySourceType;
    Functor iProductTypeChanged;
    Functor iProductModelChanged;
    Functor iProductNameChanged;
    Functor iProductRoomChanged;
    Functor iProductStandbyChanged;
    Functor iProductSourceIndexChanged;
    Functor iProductSourceCountChanged;
    Functor iProductSourceXmlChanged;
    Functor iStartupSourceIndexChanged;
    Functor iStartupSourceEnabledChanged;
    Functor iProductAnySourceNameChanged;
    Functor iProductAnySourceVisibleChanged;
    Functor iProductAnySourceTypeChanged;
};

} // namespace Zapp

#endif // HEADER_LINNCOUKPRODUCT3CPP

