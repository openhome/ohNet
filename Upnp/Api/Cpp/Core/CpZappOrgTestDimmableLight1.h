#ifndef HEADER_ZAPPORGTESTDIMMABLELIGHT1
#define HEADER_ZAPPORGTESTDIMMABLELIGHT1

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
 * Proxy for zapp.org:TestDimmableLight:1
 */
class CpProxyZappOrgTestDimmableLight1 : public CpProxy
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
    CpProxyZappOrgTestDimmableLight1(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyZappOrgTestDimmableLight1();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aLevel
     */
    void SyncGetLevel(TUint& aLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetLevel().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetLevel(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aLevel
     */
    void EndGetLevel(IAsync& aAsync, TUint& aLevel);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aLevel
     */
    void SyncSetLevel(TUint aLevel);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetLevel().
     *
     * @param[in] aLevel
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetLevel(TUint aLevel, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetLevel(IAsync& aAsync);

    /**
     * Set a callback to be run when the A_ARG_Level state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestDimmableLight1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyA_ARG_LevelChanged(Functor& aFunctor);

    /**
     * Query the value of the A_ARG_Level property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aA_ARG_Level
     */
    void PropertyA_ARG_Level(TUint& aA_ARG_Level) const;
private:
    void A_ARG_LevelPropertyChanged();
private:
    Action* iActionGetLevel;
    Action* iActionSetLevel;
    PropertyUint* iA_ARG_Level;
    Functor iA_ARG_LevelChanged;
};

} // namespace Zapp

#endif // HEADER_ZAPPORGTESTDIMMABLELIGHT1

