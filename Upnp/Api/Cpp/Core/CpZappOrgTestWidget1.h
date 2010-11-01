#ifndef HEADER_ZAPPORGTESTWIDGET1
#define HEADER_ZAPPORGTESTWIDGET1

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
 * Proxy for zapp.org:TestWidget:1
 */
class CpProxyZappOrgTestWidget1 : public CpProxy
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
    CpProxyZappOrgTestWidget1(CpDevice& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyZappOrgTestWidget1();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aRegisterIndex
     * @param[in]  aRegisterValue
     */
    void SyncSetReadWriteRegister(TUint aRegisterIndex, TUint aRegisterValue);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSetReadWriteRegister().
     *
     * @param[in] aRegisterIndex
     * @param[in] aRegisterValue
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSetReadWriteRegister(TUint aRegisterIndex, TUint aRegisterValue, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndSetReadWriteRegister(IAsync& aAsync);

    /**
     * Set a callback to be run when the ReadWriteRegister0 state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestWidget1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyReadWriteRegister0Changed(Functor& aFunctor);
    /**
     * Set a callback to be run when the ReadWriteRegister1 state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestWidget1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyReadWriteRegister1Changed(Functor& aFunctor);
    /**
     * Set a callback to be run when the ReadWriteRegister2 state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestWidget1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyReadWriteRegister2Changed(Functor& aFunctor);
    /**
     * Set a callback to be run when the ReadWriteRegister3 state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestWidget1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyReadWriteRegister3Changed(Functor& aFunctor);
    /**
     * Set a callback to be run when the ReadOnlyRegister4 state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestWidget1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyReadOnlyRegister4Changed(Functor& aFunctor);
    /**
     * Set a callback to be run when the ReadOnlyRegister5 state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestWidget1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyReadOnlyRegister5Changed(Functor& aFunctor);
    /**
     * Set a callback to be run when the ReadOnlyRegister6 state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestWidget1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyReadOnlyRegister6Changed(Functor& aFunctor);
    /**
     * Set a callback to be run when the ReadOnlyRegister7 state variable changes.
     *
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyZappOrgTestWidget1 instance will not overlap.
     *
     * @param[in]  aFunctor  The callback to run when the state variable changes
     */
    void SetPropertyReadOnlyRegister7Changed(Functor& aFunctor);

    /**
     * Query the value of the ReadWriteRegister0 property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aReadWriteRegister0
     */
    void PropertyReadWriteRegister0(TUint& aReadWriteRegister0) const;
    /**
     * Query the value of the ReadWriteRegister1 property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aReadWriteRegister1
     */
    void PropertyReadWriteRegister1(TUint& aReadWriteRegister1) const;
    /**
     * Query the value of the ReadWriteRegister2 property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aReadWriteRegister2
     */
    void PropertyReadWriteRegister2(TUint& aReadWriteRegister2) const;
    /**
     * Query the value of the ReadWriteRegister3 property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aReadWriteRegister3
     */
    void PropertyReadWriteRegister3(TUint& aReadWriteRegister3) const;
    /**
     * Query the value of the ReadOnlyRegister4 property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aReadOnlyRegister4
     */
    void PropertyReadOnlyRegister4(TUint& aReadOnlyRegister4) const;
    /**
     * Query the value of the ReadOnlyRegister5 property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aReadOnlyRegister5
     */
    void PropertyReadOnlyRegister5(TUint& aReadOnlyRegister5) const;
    /**
     * Query the value of the ReadOnlyRegister6 property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aReadOnlyRegister6
     */
    void PropertyReadOnlyRegister6(TUint& aReadOnlyRegister6) const;
    /**
     * Query the value of the ReadOnlyRegister7 property.
     *
     * This function is threadsafe and can only be called if Subscribe() has been
     * called and a first eventing callback received more recently than any call
	 * to Unsubscribe().
     *
     * @param[out] aReadOnlyRegister7
     */
    void PropertyReadOnlyRegister7(TUint& aReadOnlyRegister7) const;
private:
    void ReadWriteRegister0PropertyChanged();
    void ReadWriteRegister1PropertyChanged();
    void ReadWriteRegister2PropertyChanged();
    void ReadWriteRegister3PropertyChanged();
    void ReadOnlyRegister4PropertyChanged();
    void ReadOnlyRegister5PropertyChanged();
    void ReadOnlyRegister6PropertyChanged();
    void ReadOnlyRegister7PropertyChanged();
private:
    Action* iActionSetReadWriteRegister;
    PropertyUint* iReadWriteRegister0;
    PropertyUint* iReadWriteRegister1;
    PropertyUint* iReadWriteRegister2;
    PropertyUint* iReadWriteRegister3;
    PropertyUint* iReadOnlyRegister4;
    PropertyUint* iReadOnlyRegister5;
    PropertyUint* iReadOnlyRegister6;
    PropertyUint* iReadOnlyRegister7;
    Functor iReadWriteRegister0Changed;
    Functor iReadWriteRegister1Changed;
    Functor iReadWriteRegister2Changed;
    Functor iReadWriteRegister3Changed;
    Functor iReadOnlyRegister4Changed;
    Functor iReadOnlyRegister5Changed;
    Functor iReadOnlyRegister6Changed;
    Functor iReadOnlyRegister7Changed;
};

} // namespace Zapp

#endif // HEADER_ZAPPORGTESTWIDGET1

