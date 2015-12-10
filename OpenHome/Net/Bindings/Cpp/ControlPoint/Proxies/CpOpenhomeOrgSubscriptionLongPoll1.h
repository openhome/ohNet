#ifndef HEADER_OPENHOMEORGSUBSCRIPTIONLONGPOLL1CPP
#define HEADER_OPENHOMEORGSUBSCRIPTIONLONGPOLL1CPP

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
class CpProxy;
class ICpProxyOpenhomeOrgSubscriptionLongPoll1Cpp : public ICpProxy
{
public:
    virtual ~ICpProxyOpenhomeOrgSubscriptionLongPoll1Cpp() {}
    virtual void SyncSubscribe(const std::string& aClientId, const std::string& aUdn, const std::string& aService, uint32_t aRequestedDuration, std::string& aSid, uint32_t& aDuration) = 0;
    virtual void BeginSubscribe(const std::string& aClientId, const std::string& aUdn, const std::string& aService, uint32_t aRequestedDuration, FunctorAsync& aFunctor) = 0;
    virtual void EndSubscribe(IAsync& aAsync, std::string& aSid, uint32_t& aDuration) = 0;
    virtual void SyncUnsubscribe(const std::string& aSid) = 0;
    virtual void BeginUnsubscribe(const std::string& aSid, FunctorAsync& aFunctor) = 0;
    virtual void EndUnsubscribe(IAsync& aAsync) = 0;
    virtual void SyncRenew(const std::string& aSid, uint32_t aRequestedDuration, uint32_t& aDuration) = 0;
    virtual void BeginRenew(const std::string& aSid, uint32_t aRequestedDuration, FunctorAsync& aFunctor) = 0;
    virtual void EndRenew(IAsync& aAsync, uint32_t& aDuration) = 0;
    virtual void SyncGetPropertyUpdates(const std::string& aClientId, std::string& aUpdates) = 0;
    virtual void BeginGetPropertyUpdates(const std::string& aClientId, FunctorAsync& aFunctor) = 0;
    virtual void EndGetPropertyUpdates(IAsync& aAsync, std::string& aUpdates) = 0;
};

/**
 * Proxy for openhome.org:SubscriptionLongPoll:1
 * @ingroup Proxies
 */
class CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp : public ICpProxyOpenhomeOrgSubscriptionLongPoll1Cpp
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
    CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp(CpDeviceCpp& aDevice);
    /**
     * Destructor.
     * If any asynchronous method is in progress, this will block until they complete.
     * [Note that any methods still in progress are likely to complete with an error.]
     * Clients who have called Subscribe() do not need to call Unsubscribe() before
     * calling delete.  An unsubscribe will be triggered automatically when required.
     */
    ~CpProxyOpenhomeOrgSubscriptionLongPoll1Cpp();

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aClientId
     * @param[in]  aUdn
     * @param[in]  aService
     * @param[in]  aRequestedDuration
     * @param[out] aSid
     * @param[out] aDuration
     */
    void SyncSubscribe(const std::string& aClientId, const std::string& aUdn, const std::string& aService, uint32_t aRequestedDuration, std::string& aSid, uint32_t& aDuration);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndSubscribe().
     *
     * @param[in] aClientId
     * @param[in] aUdn
     * @param[in] aService
     * @param[in] aRequestedDuration
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginSubscribe(const std::string& aClientId, const std::string& aUdn, const std::string& aService, uint32_t aRequestedDuration, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aSid
     * @param[out] aDuration
     */
    void EndSubscribe(IAsync& aAsync, std::string& aSid, uint32_t& aDuration);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aSid
     */
    void SyncUnsubscribe(const std::string& aSid);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndUnsubscribe().
     *
     * @param[in] aSid
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginUnsubscribe(const std::string& aSid, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     */
    void EndUnsubscribe(IAsync& aAsync);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aSid
     * @param[in]  aRequestedDuration
     * @param[out] aDuration
     */
    void SyncRenew(const std::string& aSid, uint32_t aRequestedDuration, uint32_t& aDuration);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndRenew().
     *
     * @param[in] aSid
     * @param[in] aRequestedDuration
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginRenew(const std::string& aSid, uint32_t aRequestedDuration, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aDuration
     */
    void EndRenew(IAsync& aAsync, uint32_t& aDuration);

    /**
     * Invoke the action synchronously.  Blocks until the action has been processed
     * on the device and sets any output arguments.
     *
     * @param[in]  aClientId
     * @param[out] aUpdates
     */
    void SyncGetPropertyUpdates(const std::string& aClientId, std::string& aUpdates);
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the action
     * later completes.  Any output arguments can then be retrieved by calling
     * EndGetPropertyUpdates().
     *
     * @param[in] aClientId
     * @param[in] aFunctor   Callback to run when the action completes.
     *                       This is guaranteed to be run but may indicate an error
     */
    void BeginGetPropertyUpdates(const std::string& aClientId, FunctorAsync& aFunctor);
    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the above Begin function.
     *
     * @param[in]  aAsync  Argument passed to the callback set in the above Begin function
     * @param[out] aUpdates
     */
    void EndGetPropertyUpdates(IAsync& aAsync, std::string& aUpdates);


    /**
    * This function exposes the Subscribe() function of the iCpProxy member variable
    */
    void Subscribe();
    /**
    * This function exposes the Unsubscribe() function of the iCpProxy member variable
    */
    void Unsubscribe();
    /**
    * This function exposes the SetPropertyChanged() function of the iCpProxy member variable
    */
    void SetPropertyChanged(Functor& aFunctor);
    /**
    * This function exposes the SetPropertyInitialEvent() function of the iCpProxy member variable
    */
    void SetPropertyInitialEvent(Functor& aFunctor);
    /**
    * This function exposes the AddProperty() function of the iCpProxy member variable
    */
    void AddProperty(Property* aProperty);
    /**
    * This function exposes DestroyService() function of the iCpProxy member variable
    */
    void DestroyService();
    /**
    * This function exposes the REportEvent() function of the iCpProxy member variable
    */
    void ReportEvent(Functor aFunctor);
    /**
    * This function exposes the Version() function of the iCpProxy member variable
    */
    TUint Version() const;
private:
    CpProxy iCpProxy;
private:
    Action* iActionSubscribe;
    Action* iActionUnsubscribe;
    Action* iActionRenew;
    Action* iActionGetPropertyUpdates;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_OPENHOMEORGSUBSCRIPTIONLONGPOLL1CPP

