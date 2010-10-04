#ifndef HEADER_CPISUBSCRIPTION
#define HEADER_CPISUBSCRIPTION

#include <ZappTypes.h>
#include <Buffer.h>
#include <CpiService.h>
#include <Timer.h>
#include <Thread.h>
#include <Fifo.h>
#include <EventUpnp.h>
#include <Functor.h>

#include <list>
#include <map>
#include <vector>

namespace Zapp {

class CpiDevice;

/**
 * Owns a subscription (request for notification of changes in state variables)
 * to a particular service on a paricular device.
 *
 * Reference counted.  Clients will normally release their reference after calling
 * Unsubscribe().  The class will then effectively delete itself when it releases
 * its operation reference after completing the unsubscription.
 */
class Subscription
{
public:
    /**
     * Return the unique subscription identifier
     */
    const Brx& Sid() const;
    
    /**
     * Claim a reference.
     * Callers must be sure anotehr reference is valid before this call and will
     * remain valid during it.  They must also be sure they always (eventually)
     * release their reference.
     */
    void AddRef();

    /**
     * Removes a reference.  Deletes when the final reference is removed.
     */
    void RemoveRef();

    /**
     * Signal that ProcessNotification should not process the notification message
     * or report any updates.
     * Normally used during destruction of a Service (allowing the Subscription to
     * outlast the Service, unsubscribing without delaying Service destruction which
     * may well happen in a UI thread).
     */
    void StopUpdates();
    
    /**
     * Used by the comms thread which receives updates on the state of properties.
     * Assumes that updates are incrementally numbered and returns false if
     * aSequenceNumber suggests that previous updates may have been missed.
     */
    TBool UpdateSequenceNumber(TUint aSequenceNumber);

    /**
     * Passes a notification of update(s) in properties to the (protocol-dependent)
     * device.  Calls the updatesComplete callback after the device has processed
     * the full notification.
     */
    void ProcessNotification(const Brx& aNotification);
    
    /**
     * Inform the subscription of an error in processing an update.
     * Occurence of any error risks one or more properties having the wrong value.
     * This would take an unbounded time to correct itself if ignored so this function
     * attempts to correct things by unsubsribing then creating a new subscription.
     * Successful completion of this new subscription would prompt update callbacks
     * on all properties, giving clients their correct values again.
     * Clients are not notified about any failure of the re-subscription
     */
    void SetNotificationError();
    
    /**
     * Schedule an unsubscribe operation which will happen later in a Subscriber thread.
     * Clients who call this should also release their reference.
     * Clients are not informed about any failure to unsubscribe.
     */
	void Unsubscribe();

    /**
     * Set the handler for interrupting a subscribe/renew/unsubscribe operation
     */
    void SetInterruptHandler(IInterruptHandler* aHandler);
    
    /**
     * Set the sid.  For use by the device only
     */
    void SetSid(Brh& aSid);

    const Zapp::ServiceType& ServiceType() const;

    /**
     * Used by Subscriber threads to process a subscribe/renew/unsubscribe operation
     * Intended for internal use only
     */
    void RunInSubscriber();
private:
    enum EOperation
    {
        eNone
       ,eSubscribe
       ,eRenew
       ,eUnsubscribe
       ,eResubscribe
    };
private:
    /**
     * Constructor.  Schedules a subscription request (which will be processed later
     * in a Subscriber thread)
     * Clients are not notified about any failure of the subscription
     */
    Subscription(CpiDevice& aDevice, const Zapp::ServiceType& aServiceType, PropertyMap& aProperties, Functor& aUpdatesComplete);
    ~Subscription();
    /**
     * Schedule a (subscribe, renew or unsubscribe operation) which will be processed
     * later in a Subscriber thread.  Claims a reference to the subscription, ensuring
     * the class doesn't get deleted before (or, worse, during) that later operation.
     */
    void Schedule(EOperation aOperation);
    void DoSubscribe();
    void Renew();
    void DoRenew();
    void DoUnsubscribe();
private:
    Mutex iLock;
    CpiDevice& iDevice;
    Zapp::ServiceType iServiceType;
    PropertyMap& iProperties;
    Functor& iUpdatesComplete;
    Brh iSid;
    Timer* iTimer;
    TUint iNextSequenceNumber;
    EOperation iPendingOperation;
    TUint iRefCount;
    TBool iStopUpdates;
    IInterruptHandler* iInterruptHandler;

    friend class SubscriptionManager;
};

/**
 * Dedicated thread which processes subscription events
 *
 * Subscribe, renew (subscription) and unsubscribe are handled in these threads.
 * Notification of state variable changes are handled separately (e.g. EventSessionUpnp for UPnP)
 *
 * Intended for internal use only
 */
class Subscriber : public Thread
{
public:
    Subscriber(const TChar* aName, Fifo<Subscriber*>& aFree);
    ~Subscriber();
    void Subscribe(Subscription* aSubscription);
private:
    void Error(const TChar* aErr);
    void Run();
private:
    Fifo<Subscriber*>& iFree;
    Subscription* iSubscription;
};

/**
 * Singleton which manages the pools of Subscriber and active Subscription instances
 */
class SubscriptionManager : public Thread
{
public:
    SubscriptionManager();
    /**
     * Destructor.  Blocks until all subscriptions have been deleted.
     */
    ~SubscriptionManager();
    static Subscription* NewSubscription(CpiDevice& aDevice, const ServiceType& aServiceType, PropertyMap& aProperties, Functor& aUpdatesComplete);
    static void NotifyAddPending(Subscription& aSubscription);
    static void NotifyAddAborted(Subscription& aSubscription);
    
    /**
     * The UPnP specification contains a race condition where it is possible to
     * attempt to process initial notification of property state before processing
     * the response from the subscription request.  Since this response contains
     * the unique subscription id used to identify which subscription the notification
     * applies to, this causes obvious problems...
     *
     * Handlers of notification messages who find that FindSubscription() returns
     * NULL should try calling this function.  WaitForPendingAdds() blocks until all
     * pending subscriptions have completed.  (It also times out after a reasonable
     * delay to avoid being block indefinitely by any badly behaved client which issues
     * streams of (un)subscribe requests.)  After this completes, FindSubscription()
     * should be tried again before treating the notification as an error.
     */
    static void WaitForPendingAdds();
    static void Add(Subscription& aSubscription);

    /**
     * Returns the subscription with unique id aSid, or NULL if the subscription
     * doesn't exist.  Claims a reference to any subscription returned.  The caller
     * is responsible for releasing this reference.
     *
     * See also WaitForPendingAdds()
     */
    static Zapp::Subscription* FindSubscription(const Brx& aSid);
    static void Remove(Zapp::Subscription& aSubscription);
    static void Schedule(Zapp::Subscription& aSubscription);
    static EventServerUpnp* EventServer();
private:
    static SubscriptionManager* Self();
    void RemovePendingAdd(Subscription& aSubscription);
    void CurrentNetworkInterfaceChanged();
    void SubnetChanged();
    void HandleInterfaceChange(TBool aNewSubnet);
    void Run();
private:
    Mutex iLock;
    std::list<Zapp::Subscription*> iList;
    Fifo<Subscriber*> iFree;
    Subscriber** iSubscribers;
    typedef std::map<Brn,Subscription*,BufferCmp> Map;
    Map iMap;
    TBool iActive;
    Semaphore iWaiter;
    TUint iWaiters;
    Semaphore iShutdownSem;
    EventServerUpnp* iEventServer;
    typedef std::vector<Zapp::Subscription*> VectorSubscriptions;
    VectorSubscriptions iPendingSubscriptions;
    TUint iInterfaceListListenerId;
    TUint iSubnetListenerId;
};

} // namespace Zapp

#endif // HEADER_CPISUBSCRIPTION
