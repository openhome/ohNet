#ifndef HEADER_LINNCOUKMEDIATIME1CPP
#define HEADER_LINNCOUKMEDIATIME1CPP

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
 * Proxy for linn.co.uk:MediaTime:1
 */
class CpProxyLinnCoUkMediaTime1Cpp : public CpProxy
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
    CpProxyLinnCoUkMediaTime1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyLinnCoUkMediaTime1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaSeconds
     */
    void SyncSeconds(uint32_t& aaSeconds);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSeconds().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSeconds(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaSeconds
     */
    void EndSeconds(IAsync& aAsync, uint32_t& aaSeconds);

    /**
     * Set a callback to be run when the Seconds state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkMediaTime1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertySecondsChanged(Functor& aFunctor);

    /**
     * Query the value of the Seconds property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aSeconds
     */
    void PropertySeconds(uint32_t& aSeconds) const;
private:
    void SecondsPropertyChanged();
private:
    Action* iActionSeconds;
    PropertyUint* iSeconds;
    Functor iSecondsChanged;
};

} // namespace Zapp

#endif // HEADER_LINNCOUKMEDIATIME1CPP

