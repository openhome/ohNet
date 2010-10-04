#ifndef HEADER_LINNCOUKPROXYMANAGER1CPP
#define HEADER_LINNCOUKPROXYMANAGER1CPP

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
 * Proxy for linn.co.uk:ProxyManager:1
 */
class CpProxyLinnCoUkProxyManager1Cpp : public CpProxy
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
    CpProxyLinnCoUkProxyManager1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyLinnCoUkProxyManager1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaConnected
     */
    void SyncKontrolProductConnected(std::string& aaConnected);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndKontrolProductConnected().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginKontrolProductConnected(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaConnected
     */
    void EndKontrolProductConnected(IAsync& aAsync, std::string& aaConnected);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaConnected
     */
    void SyncSetKontrolProductConnected(const std::string& aaConnected);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetKontrolProductConnected().
     *
     * @param[in] aaConnected
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetKontrolProductConnected(const std::string& aaConnected, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetKontrolProductConnected(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaPort
     */
    void SyncKontrolProductComPort(uint32_t& aaPort);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndKontrolProductComPort().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginKontrolProductComPort(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaPort
     */
    void EndKontrolProductComPort(IAsync& aAsync, uint32_t& aaPort);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaConnected
     */
    void SyncSetKontrolProductComPort(uint32_t aaConnected);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetKontrolProductComPort().
     *
     * @param[in] aaConnected
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetKontrolProductComPort(uint32_t aaConnected, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetKontrolProductComPort(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaConnected
     */
    void SyncDiscPlayerConnected(std::string& aaConnected);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDiscPlayerConnected().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDiscPlayerConnected(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaConnected
     */
    void EndDiscPlayerConnected(IAsync& aAsync, std::string& aaConnected);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaConnected
     */
    void SyncSetDiscPlayerConnected(const std::string& aaConnected);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDiscPlayerConnected().
     *
     * @param[in] aaConnected
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDiscPlayerConnected(const std::string& aaConnected, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDiscPlayerConnected(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaPort
     */
    void SyncDiscPlayerComPort(uint32_t& aaPort);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndDiscPlayerComPort().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginDiscPlayerComPort(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaPort
     */
    void EndDiscPlayerComPort(IAsync& aAsync, uint32_t& aaPort);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aaConnected
     */
    void SyncSetDiscPlayerComPort(uint32_t aaConnected);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetDiscPlayerComPort().
     *
     * @param[in] aaConnected
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetDiscPlayerComPort(uint32_t aaConnected, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetDiscPlayerComPort(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaResult
     */
    void SyncTestKontrolProductConnection(bool& aaResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndTestKontrolProductConnection().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginTestKontrolProductConnection(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaResult
     */
    void EndTestKontrolProductConnection(IAsync& aAsync, bool& aaResult);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[out] aaResult
     */
    void SyncTestDiscPlayerConnection(bool& aaResult);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndTestDiscPlayerConnection().
     *
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginTestDiscPlayerConnection(FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aaResult
     */
    void EndTestDiscPlayerConnection(IAsync& aAsync, bool& aaResult);

    /**
     * Set a callback to be run when the KontrolProductConnected state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProxyManager1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyKontrolProductConnectedChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the KontrolProductComPort state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProxyManager1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyKontrolProductComPortChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DiscPlayerConnected state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProxyManager1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDiscPlayerConnectedChanged(Functor& aFunctor);
    /**
     * Set a callback to be run when the DiscPlayerComPort state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyLinnCoUkProxyManager1Cpp instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyDiscPlayerComPortChanged(Functor& aFunctor);

    /**
     * Query the value of the KontrolProductConnected property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aKontrolProductConnected
     */
    void PropertyKontrolProductConnected(std::string& aKontrolProductConnected) const;
    /**
     * Query the value of the KontrolProductComPort property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aKontrolProductComPort
     */
    void PropertyKontrolProductComPort(uint32_t& aKontrolProductComPort) const;
    /**
     * Query the value of the DiscPlayerConnected property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDiscPlayerConnected
     */
    void PropertyDiscPlayerConnected(std::string& aDiscPlayerConnected) const;
    /**
     * Query the value of the DiscPlayerComPort property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aDiscPlayerComPort
     */
    void PropertyDiscPlayerComPort(uint32_t& aDiscPlayerComPort) const;
private:
    void KontrolProductConnectedPropertyChanged();
    void KontrolProductComPortPropertyChanged();
    void DiscPlayerConnectedPropertyChanged();
    void DiscPlayerComPortPropertyChanged();
private:
    Action* iActionKontrolProductConnected;
    Action* iActionSetKontrolProductConnected;
    Action* iActionKontrolProductComPort;
    Action* iActionSetKontrolProductComPort;
    Action* iActionDiscPlayerConnected;
    Action* iActionSetDiscPlayerConnected;
    Action* iActionDiscPlayerComPort;
    Action* iActionSetDiscPlayerComPort;
    Action* iActionTestKontrolProductConnection;
    Action* iActionTestDiscPlayerConnection;
    PropertyString* iKontrolProductConnected;
    PropertyUint* iKontrolProductComPort;
    PropertyString* iDiscPlayerConnected;
    PropertyUint* iDiscPlayerComPort;
    Functor iKontrolProductConnectedChanged;
    Functor iKontrolProductComPortChanged;
    Functor iDiscPlayerConnectedChanged;
    Functor iDiscPlayerComPortChanged;
};

} // namespace Zapp

#endif // HEADER_LINNCOUKPROXYMANAGER1CPP

