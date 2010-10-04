#ifndef HEADER_LINNCOUKPRODUCT3
#define HEADER_LINNCOUKPRODUCT3

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
 * Proxy for linn.co.uk:Product:3
 */
class CpProxyLinnCoUkProduct3 : public CpProxy
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
    CpProxyLinnCoUkProduct3(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyLinnCoUkProduct3();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaType
     */
    void SyncType(Brh& aaType);
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
    void EndType(IAsync& aAsync, Brh& aaType);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaModel
     */
    void SyncModel(Brh& aaModel);
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
    void EndModel(IAsync& aAsync, Brh& aaModel);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaName
     */
    void SyncName(Brh& aaName);
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
    void EndName(IAsync& aAsync, Brh& aaName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaName
     */
    void SyncSetName(const Brx& aaName);
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
    void BeginSetName(const Brx& aaName, FunctorAsync& aFunctor);
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
    void SyncRoom(Brh& aaRoom);
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
    void EndRoom(IAsync& aAsync, Brh& aaRoom);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaRoom
     */
    void SyncSetRoom(const Brx& aaRoom);
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
    void BeginSetRoom(const Brx& aaRoom, FunctorAsync& aFunctor);
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
    void SyncStandby(TBool& aaStandby);
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
    void EndStandby(IAsync& aAsync, TBool& aaStandby);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaStandby
     */
    void SyncSetStandby(TBool aaStandby);
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
    void BeginSetStandby(TBool aaStandby, FunctorAsync& aFunctor);
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
    void SyncSourceCount(TUint& aaSourceCount);
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
    void EndSourceCount(IAsync& aAsync, TUint& aaSourceCount);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaSourceXml
     */
    void SyncSourceXml(Brh& aaSourceXml);
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
    void EndSourceXml(IAsync& aAsync, Brh& aaSourceXml);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaSourceIndex
     */
    void SyncSourceIndex(TUint& aaSourceIndex);
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
    void EndSourceIndex(IAsync& aAsync, TUint& aaSourceIndex);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     */
    void SyncSetSourceIndex(TUint aaSourceIndex);
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
    void BeginSetSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor);
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
    void SyncSetSourceIndexByName(const Brx& aaSourceName);
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
    void BeginSetSourceIndexByName(const Brx& aaSourceName, FunctorAsync& aFunctor);
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
    void SyncSetStartupSourceIndexByName(const Brx& aaSourceName);
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
    void BeginSetStartupSourceIndexByName(const Brx& aaSourceName, FunctorAsync& aFunctor);
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
    void SyncStartupSourceIndex(TUint& aaSourceIndex);
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
    void EndStartupSourceIndex(IAsync& aAsync, TUint& aaSourceIndex);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     */
    void SyncSetStartupSourceIndex(TUint aaSourceIndex);
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
    void BeginSetStartupSourceIndex(TUint aaSourceIndex, FunctorAsync& aFunctor);
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
    void SyncStartupSourceEnabled(TBool& aaStartupSourceEnabled);
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
    void EndStartupSourceEnabled(IAsync& aAsync, TBool& aaStartupSourceEnabled);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaStartupSourceEnabled
     */
    void SyncSetStartupSourceEnabled(TBool aaStartupSourceEnabled);
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
    void BeginSetStartupSourceEnabled(TBool aaStartupSourceEnabled, FunctorAsync& aFunctor);
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
    void SyncSourceSystemName(TUint aaSourceIndex, Brh& aaSourceName);
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
    void BeginSourceSystemName(TUint aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceName
     */
    void EndSourceSystemName(IAsync& aAsync, Brh& aaSourceName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[out] aaSourceName
     */
    void SyncSourceName(TUint aaSourceIndex, Brh& aaSourceName);
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
    void BeginSourceName(TUint aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceName
     */
    void EndSourceName(IAsync& aAsync, Brh& aaSourceName);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[in]  aaSourceName
     */
    void SyncSetSourceName(TUint aaSourceIndex, const Brx& aaSourceName);
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
    void BeginSetSourceName(TUint aaSourceIndex, const Brx& aaSourceName, FunctorAsync& aFunctor);
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
    void SyncSourceType(TUint aaSourceIndex, Brh& aaSourceType);
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
    void BeginSourceType(TUint aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceType
     */
    void EndSourceType(IAsync& aAsync, Brh& aaSourceType);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[out] aaSourceVisible
     */
    void SyncSourceVisible(TUint aaSourceIndex, TBool& aaSourceVisible);
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
    void BeginSourceVisible(TUint aaSourceIndex, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSourceVisible
     */
    void EndSourceVisible(IAsync& aAsync, TBool& aaSourceVisible);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaSourceIndex
     * @param[in]  aaSourceVisible
     */
    void SyncSetSourceVisible(TUint aaSourceIndex, TBool aaSourceVisible);
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
    void BeginSetSourceVisible(TUint aaSourceIndex, TBool aaSourceVisible, FunctorAsync& aFunctor);
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
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductTypeChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductModel state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductModelChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductRoom state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductRoomChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductStandby state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductStandbyChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductSourceIndex state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductSourceIndexChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductSourceCount state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductSourceCountChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductSourceXml state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductSourceXmlChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the StartupSourceIndex state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyStartupSourceIndexChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the StartupSourceEnabled state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyStartupSourceEnabledChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductAnySourceName state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductAnySourceNameChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductAnySourceVisible state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyProductAnySourceVisibleChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the ProductAnySourceType state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProduct3 instance will not overlap.
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
    void PropertyProductType(Brhz& aProductType) const;
    /**
     * Query the value of the ProductModel property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductModel
     */
    void PropertyProductModel(Brhz& aProductModel) const;
    /**
     * Query the value of the ProductName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductName
     */
    void PropertyProductName(Brhz& aProductName) const;
    /**
     * Query the value of the ProductRoom property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductRoom
     */
    void PropertyProductRoom(Brhz& aProductRoom) const;
    /**
     * Query the value of the ProductStandby property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductStandby
     */
    void PropertyProductStandby(TBool& aProductStandby) const;
    /**
     * Query the value of the ProductSourceIndex property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductSourceIndex
     */
    void PropertyProductSourceIndex(TUint& aProductSourceIndex) const;
    /**
     * Query the value of the ProductSourceCount property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductSourceCount
     */
    void PropertyProductSourceCount(TUint& aProductSourceCount) const;
    /**
     * Query the value of the ProductSourceXml property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductSourceXml
     */
    void PropertyProductSourceXml(Brhz& aProductSourceXml) const;
    /**
     * Query the value of the StartupSourceIndex property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aStartupSourceIndex
     */
    void PropertyStartupSourceIndex(TUint& aStartupSourceIndex) const;
    /**
     * Query the value of the StartupSourceEnabled property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aStartupSourceEnabled
     */
    void PropertyStartupSourceEnabled(TBool& aStartupSourceEnabled) const;
    /**
     * Query the value of the ProductAnySourceName property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductAnySourceName
     */
    void PropertyProductAnySourceName(TUint& aProductAnySourceName) const;
    /**
     * Query the value of the ProductAnySourceVisible property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductAnySourceVisible
     */
    void PropertyProductAnySourceVisible(TUint& aProductAnySourceVisible) const;
    /**
     * Query the value of the ProductAnySourceType property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aProductAnySourceType
     */
    void PropertyProductAnySourceType(TUint& aProductAnySourceType) const;
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

#endif // HEADER_LINNCOUKPRODUCT3

