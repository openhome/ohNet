#ifndef HEADER_OPENHOMEORGTESTBASIC1
#define HEADER_OPENHOMEORGTESTBASIC1

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
class CpProxy;
class ICpProxyOpenhomeOrgTestBasic1 : public ICpProxy
{
public:
    virtual void SyncIncrement(TUint aValue, TUint& aResult) = 0;
    virtual void BeginIncrement(TUint aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndIncrement(IAsync& aAsync, TUint& aResult) = 0;
    virtual void SyncEchoAllowedRangeUint(TUint aValue, TUint& aResult) = 0;
    virtual void BeginEchoAllowedRangeUint(TUint aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndEchoAllowedRangeUint(IAsync& aAsync, TUint& aResult) = 0;
    virtual void SyncDecrement(TInt aValue, TInt& aResult) = 0;
    virtual void BeginDecrement(TInt aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndDecrement(IAsync& aAsync, TInt& aResult) = 0;
    virtual void SyncToggle(TBool aValue, TBool& aResult) = 0;
    virtual void BeginToggle(TBool aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndToggle(IAsync& aAsync, TBool& aResult) = 0;
    virtual void SyncEchoString(const Brx& aValue, Brh& aResult) = 0;
    virtual void BeginEchoString(const Brx& aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndEchoString(IAsync& aAsync, Brh& aResult) = 0;
    virtual void SyncEchoAllowedValueString(const Brx& aValue, Brh& aResult) = 0;
    virtual void BeginEchoAllowedValueString(const Brx& aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndEchoAllowedValueString(IAsync& aAsync, Brh& aResult) = 0;
    virtual void SyncEchoBinary(const Brx& aValue, Brh& aResult) = 0;
    virtual void BeginEchoBinary(const Brx& aValue, FunctorAsync& aFunctor) = 0;
    virtual void EndEchoBinary(IAsync& aAsync, Brh& aResult) = 0;
    virtual void SyncSetUint(TUint aValueUint) = 0;
    virtual void BeginSetUint(TUint aValueUint, FunctorAsync& aFunctor) = 0;
    virtual void EndSetUint(IAsync& aAsync) = 0;
    virtual void SyncGetUint(TUint& aValueUint) = 0;
    virtual void BeginGetUint(FunctorAsync& aFunctor) = 0;
    virtual void EndGetUint(IAsync& aAsync, TUint& aValueUint) = 0;
    virtual void SyncSetInt(TInt aValueInt) = 0;
    virtual void BeginSetInt(TInt aValueInt, FunctorAsync& aFunctor) = 0;
    virtual void EndSetInt(IAsync& aAsync) = 0;
    virtual void SyncGetInt(TInt& aValueInt) = 0;
    virtual void BeginGetInt(FunctorAsync& aFunctor) = 0;
    virtual void EndGetInt(IAsync& aAsync, TInt& aValueInt) = 0;
    virtual void SyncSetBool(TBool aValueBool) = 0;
    virtual void BeginSetBool(TBool aValueBool, FunctorAsync& aFunctor) = 0;
    virtual void EndSetBool(IAsync& aAsync) = 0;
    virtual void SyncGetBool(TBool& aValueBool) = 0;
    virtual void BeginGetBool(FunctorAsync& aFunctor) = 0;
    virtual void EndGetBool(IAsync& aAsync, TBool& aValueBool) = 0;
    virtual void SyncSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool) = 0;
    virtual void BeginSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool, FunctorAsync& aFunctor) = 0;
    virtual void EndSetMultiple(IAsync& aAsync) = 0;
    virtual void SyncGetMultiple(TUint& aValueUint, TInt& aValueInt, TBool& aValueBool) = 0;
    virtual void BeginGetMultiple(FunctorAsync& aFunctor) = 0;
    virtual void EndGetMultiple(IAsync& aAsync, TUint& aValueUint, TInt& aValueInt, TBool& aValueBool) = 0;
    virtual void SyncSetString(const Brx& aValueStr) = 0;
    virtual void BeginSetString(const Brx& aValueStr, FunctorAsync& aFunctor) = 0;
    virtual void EndSetString(IAsync& aAsync) = 0;
    virtual void SyncGetString(Brh& aValueStr) = 0;
    virtual void BeginGetString(FunctorAsync& aFunctor) = 0;
    virtual void EndGetString(IAsync& aAsync, Brh& aValueStr) = 0;
    virtual void SyncSetBinary(const Brx& aValueBin) = 0;
    virtual void BeginSetBinary(const Brx& aValueBin, FunctorAsync& aFunctor) = 0;
    virtual void EndSetBinary(IAsync& aAsync) = 0;
    virtual void SyncGetBinary(Brh& aValueBin) = 0;
    virtual void BeginGetBinary(FunctorAsync& aFunctor) = 0;
    virtual void EndGetBinary(IAsync& aAsync, Brh& aValueBin) = 0;
    virtual void SyncToggleBool() = 0;
    virtual void BeginToggleBool(FunctorAsync& aFunctor) = 0;
    virtual void EndToggleBool(IAsync& aAsync) = 0;
    virtual void SyncWriteFile(const Brx& aData, const Brx& aFileFullName) = 0;
    virtual void BeginWriteFile(const Brx& aData, const Brx& aFileFullName, FunctorAsync& aFunctor) = 0;
    virtual void EndWriteFile(IAsync& aAsync) = 0;
    virtual void SyncShutdown() = 0;
    virtual void BeginShutdown(FunctorAsync& aFunctor) = 0;
    virtual void EndShutdown(IAsync& aAsync) = 0;
    virtual void SetPropertyVarUintChanged(Functor& aVarUintChanged) = 0;
    virtual void PropertyVarUint(TUint& aVarUint) const = 0;
    virtual void SetPropertyVarIntChanged(Functor& aVarIntChanged) = 0;
    virtual void PropertyVarInt(TInt& aVarInt) const = 0;
    virtual void SetPropertyVarBoolChanged(Functor& aVarBoolChanged) = 0;
    virtual void PropertyVarBool(TBool& aVarBool) const = 0;
    virtual void SetPropertyVarStrChanged(Functor& aVarStrChanged) = 0;
    virtual void PropertyVarStr(Brhz& aVarStr) const = 0;
    virtual void SetPropertyVarBinChanged(Functor& aVarBinChanged) = 0;
    virtual void PropertyVarBin(Brh& aVarBin) const = 0;
};

/**
 * Proxy for openhome.org:TestBasic:1
 * @ingroup Proxies
 */
class CpProxyOpenhomeOrgTestBasic1 : public ICpProxyOpenhomeOrgTestBasic1
{
public:
    /**
     * Constructor.
     *
     * Use iCpProxy::[Un]Subscribe() to enable/disable querying of state variable
     * and reporting of their changes.
     *
     * @param[in]  aDevice   The device to use
     */
    CpProxyOpenhomeOrgTestBasic1(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyOpenhomeOrgTestBasic1();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     * @param[out] aResult
     */
    void SyncIncrement(TUint aValue, TUint& aResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndIncrement().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginIncrement(TUint aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     */
    void EndIncrement(IAsync& aAsync, TUint& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     * @param[out] aResult
     */
    void SyncEchoAllowedRangeUint(TUint aValue, TUint& aResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndEchoAllowedRangeUint().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginEchoAllowedRangeUint(TUint aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     */
    void EndEchoAllowedRangeUint(IAsync& aAsync, TUint& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     * @param[out] aResult
     */
    void SyncDecrement(TInt aValue, TInt& aResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDecrement().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDecrement(TInt aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     */
    void EndDecrement(IAsync& aAsync, TInt& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     * @param[out] aResult
     */
    void SyncToggle(TBool aValue, TBool& aResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndToggle().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginToggle(TBool aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     */
    void EndToggle(IAsync& aAsync, TBool& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     * @param[out] aResult
     */
    void SyncEchoString(const Brx& aValue, Brh& aResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndEchoString().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginEchoString(const Brx& aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     */
    void EndEchoString(IAsync& aAsync, Brh& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     * @param[out] aResult
     */
    void SyncEchoAllowedValueString(const Brx& aValue, Brh& aResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndEchoAllowedValueString().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginEchoAllowedValueString(const Brx& aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     */
    void EndEchoAllowedValueString(IAsync& aAsync, Brh& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValue
     * @param[out] aResult
     */
    void SyncEchoBinary(const Brx& aValue, Brh& aResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndEchoBinary().
     *
     * @param[in] aValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginEchoBinary(const Brx& aValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aResult
     */
    void EndEchoBinary(IAsync& aAsync, Brh& aResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValueUint
     */
    void SyncSetUint(TUint aValueUint);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetUint().
     *
     * @param[in] aValueUint
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetUint(TUint aValueUint, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetUint(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValueUint
     */
    void SyncGetUint(TUint& aValueUint);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetUint().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetUint(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValueUint
     */
    void EndGetUint(IAsync& aAsync, TUint& aValueUint);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValueInt
     */
    void SyncSetInt(TInt aValueInt);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetInt().
     *
     * @param[in] aValueInt
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetInt(TInt aValueInt, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetInt(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValueInt
     */
    void SyncGetInt(TInt& aValueInt);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetInt().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetInt(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValueInt
     */
    void EndGetInt(IAsync& aAsync, TInt& aValueInt);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValueBool
     */
    void SyncSetBool(TBool aValueBool);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetBool().
     *
     * @param[in] aValueBool
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetBool(TBool aValueBool, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetBool(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValueBool
     */
    void SyncGetBool(TBool& aValueBool);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetBool().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetBool(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValueBool
     */
    void EndGetBool(IAsync& aAsync, TBool& aValueBool);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValueUint
     * @param[in]  aValueInt
     * @param[in]  aValueBool
     */
    void SyncSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetMultiple().
     *
     * @param[in] aValueUint
     * @param[in] aValueInt
     * @param[in] aValueBool
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetMultiple(TUint aValueUint, TInt aValueInt, TBool aValueBool, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetMultiple(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValueUint
     * @param[out] aValueInt
     * @param[out] aValueBool
     */
    void SyncGetMultiple(TUint& aValueUint, TInt& aValueInt, TBool& aValueBool);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetMultiple().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetMultiple(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValueUint
     * @param[out] aValueInt
     * @param[out] aValueBool
     */
    void EndGetMultiple(IAsync& aAsync, TUint& aValueUint, TInt& aValueInt, TBool& aValueBool);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValueStr
     */
    void SyncSetString(const Brx& aValueStr);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetString().
     *
     * @param[in] aValueStr
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetString(const Brx& aValueStr, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetString(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValueStr
     */
    void SyncGetString(Brh& aValueStr);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetString().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetString(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValueStr
     */
    void EndGetString(IAsync& aAsync, Brh& aValueStr);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aValueBin
     */
    void SyncSetBinary(const Brx& aValueBin);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetBinary().
     *
     * @param[in] aValueBin
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetBinary(const Brx& aValueBin, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetBinary(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aValueBin
     */
    void SyncGetBinary(Brh& aValueBin);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetBinary().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetBinary(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aValueBin
     */
    void EndGetBinary(IAsync& aAsync, Brh& aValueBin);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     */
    void SyncToggleBool();
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndToggleBool().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginToggleBool(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndToggleBool(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aData
     * @param[in]  aFileFullName
     */
    void SyncWriteFile(const Brx& aData, const Brx& aFileFullName);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndWriteFile().
     *
     * @param[in] aData
     * @param[in] aFileFullName
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginWriteFile(const Brx& aData, const Brx& aFileFullName, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndWriteFile(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     */
    void SyncShutdown();
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndShutdown().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginShutdown(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndShutdown(IAsync& aAsync);

    /**
     * Set a callback to be run when the VarUint state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyVarUintChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the VarInt state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyVarIntChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the VarBool state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyVarBoolChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the VarStr state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyVarStrChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the VarBin state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyVarBinChanged(Functor& aFunctor);

    /**
     * Query the value of the VarUint property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aVarUint
     */
    void PropertyVarUint(TUint& aVarUint) const;
    /**
     * Query the value of the VarInt property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aVarInt
     */
    void PropertyVarInt(TInt& aVarInt) const;
    /**
     * Query the value of the VarBool property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aVarBool
     */
    void PropertyVarBool(TBool& aVarBool) const;
    /**
     * Query the value of the VarStr property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aVarStr
     */
    void PropertyVarStr(Brhz& aVarStr) const;
    /**
     * Query the value of the VarBin property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
     * to Unsubscribe().
     *
     * @param[out] aVarBin
     */
    void PropertyVarBin(Brh& aVarBin) const;
    /**
    * This function exposes the Subscribe() function of the iCpProxy member variable
    */
    void Subscribe() override;
    /**
    * This function exposes the Unsubscribe() function of the iCpProxy member variable
    */
    void Unsubscribe() override;
    /**
    * This function exposes the SetPropertyChanged() function of the iCpProxy member variable
    */
    void SetPropertyChanged(Functor& aFunctor) override;
    /**
    * This function exposes the SetPropertyInitialEvent() function of the iCpProxy member variable
    */
    void SetPropertyInitialEvent(Functor& aFunctor) override;
    /**
    * This function exposes the AddProperty() function of the iCpProxy member variable
    */
    void AddProperty(Property* aProperty) override;
    /**
    * This function exposes DestroyService() function of the iCpProxy member variable
    */
    void DestroyService() override;
    /**
    * This function exposes the REportEvent() function of the iCpProxy member variable
    */
    void ReportEvent(Functor aFunctor) override;
    /**
    * This function exposes the Version() function of the iCpProxy member variable
    */
    TUint Version() const override;
private:
    CpProxy iCpProxy;
    void VarUintPropertyChanged();
    void VarIntPropertyChanged();
    void VarBoolPropertyChanged();
    void VarStrPropertyChanged();
    void VarBinPropertyChanged();
private:
    Action* iActionIncrement;
    Action* iActionEchoAllowedRangeUint;
    Action* iActionDecrement;
    Action* iActionToggle;
    Action* iActionEchoString;
    Action* iActionEchoAllowedValueString;
    Action* iActionEchoBinary;
    Action* iActionSetUint;
    Action* iActionGetUint;
    Action* iActionSetInt;
    Action* iActionGetInt;
    Action* iActionSetBool;
    Action* iActionGetBool;
    Action* iActionSetMultiple;
    Action* iActionGetMultiple;
    Action* iActionSetString;
    Action* iActionGetString;
    Action* iActionSetBinary;
    Action* iActionGetBinary;
    Action* iActionToggleBool;
    Action* iActionWriteFile;
    Action* iActionShutdown;
    PropertyUint* iVarUint;
    PropertyInt* iVarInt;
    PropertyBool* iVarBool;
    PropertyString* iVarStr;
    PropertyBinary* iVarBin;
    Functor iVarUintChanged;
    Functor iVarIntChanged;
    Functor iVarBoolChanged;
    Functor iVarStrChanged;
    Functor iVarBinChanged;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_OPENHOMEORGTESTBASIC1

