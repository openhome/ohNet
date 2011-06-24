#ifndef HEADER_CPISUBSCRIPTION
#define HEADER_CPISUBSCRIPTION

#include <OhNetTypes.h>
#include <Buffer.h>
#include <CpiService.h>
#include <Timer.h>
#include <Thread.h>
#include <Fifo.h>
#include <EventUpnp.h>
#include <Functor.h>
#include <CpProxy.h> // for IEventProcessor

#include <list>
#include <map>
#include <vector>

namespace OpenHome {
namespace Net {

/**
 * Owns a subscription (request for notification of changes in state variables)
 * to a particular service on a paricular device.
 *
 * Reference counted.  Clients will normally release their reference after calling
 * Unsubscribe().  The class will then effectively delete itself when it releases
 * its operation reference after completing the unsubscription.
 */
class CpiSubscription : public IEventProcessor
{
public:
    static const TUint kDefaultDurationSecs = 30 * 60; // 30 minutes
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
     * Used by the comms thread which receives updates on the state of properties.
     * Assumes that updates are incrementally numbered and returns false if
     * aSequenceNumber suggests that previous updates may have been missed.
     */
    TBool UpdateSequenceNumber(TUint aSequenceNumber);

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
	 * No property update events will be delivered once this returns.
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

    const OpenHome::Net::ServiceType& ServiceType() const;

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
    CpiSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType);
    ~CpiSubscription();
    /**
     * Schedule a (subscribe, renew or unsubscribe operation) which will be processed
     * later in a Subscriber thread.  Claims a reference to the subscription, ensuring
     * the class doesn't get deleted before (or, worse, during) that later operation.
     */
    void Schedule(EOperation aOperation);
    void RunInSubscriber(EOperation aOperation);
    void DoSubscribe();
    void Renew();
    void DoRenew();
    void DoUnsubscribe();
    void NotifyAddAborted();
private: // IEventProcessor
    void EventUpdateStart();
    void EventUpdate(const Brx& aName, const Brx& aValue, IOutputProcessor& aProcessor);
    void EventUpdateEnd();
private:
    OpenHome::Mutex iLock;
    OpenHome::Mutex iSubscriberLock;
    CpiDevice& iDevice;
    IEventProcessor* iEventProcessor;
    OpenHome::Net::ServiceType iServiceType;
    Brh iSid;
    Timer* iTimer;
    TUint iNextSequenceNumber;
    EOperation iPendingOperation;
    TUint iRefCount;
    IInterruptHandler* iInterruptHandler;
    Semaphore iSubscribeCompleted;

    friend class CpiSubscriptionManager;
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
    void Subscribe(CpiSubscription* aSubscription);
private:
    void Error(const TChar* aErr);
    void Run();
private:
    Fifo<Subscriber*>& iFree;
    CpiSubscription* iSubscription;
};

/**
 * Singleton which manages the pools of Subscriber and active Subscription instances
 */
class CpiSubscriptionManager : public Thread
{
public:
    CpiSubscriptionManager();
    /**
     * Destructor.  Blocks until all subscriptions have been deleted.
     */
    ~CpiSubscriptionManager();
    static CpiSubscription* NewSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType);
    static void NotifyAddPending(CpiSubscription& aSubscription);
    static void NotifyAddAborted(CpiSubscription& aSubscription);
    
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
    static void Add(CpiSubscription& aSubscription);

    /**
     * Returns the subscription with unique id aSid, or NULL if the subscription
     * doesn't exist.  Claims a reference to any subscription returned.  The caller
     * is responsible for releasing this reference.
     *
     * See also WaitForPendingAdds()
     */
    static CpiSubscription* FindSubscription(const Brx& aSid);
    static void Remove(CpiSubscription& aSubscription);
    static void Schedule(CpiSubscription& aSubscription);
    static EventServerUpnp* EventServer();
private:
    static CpiSubscriptionManager* Self();
    void RemovePendingAdd(CpiSubscription& aSubscription);
    void CurrentNetworkInterfaceChanged();
    void SubnetChanged();
    void HandleInterfaceChange(TBool aNewSubnet);
    void Run();
private:
    OpenHome::Mutex iLock;
    std::list<CpiSubscription*> iList;
    Fifo<Subscriber*> iFree;
    Subscriber** iSubscribers;
    typedef std::map<Brn,CpiSubscription*,BufferCmp> Map;
    Map iMap;
    TBool iActive;
    Semaphore iWaiter;
    TUint iWaiters;
    Semaphore iShutdownSem;
    EventServerUpnp* iEventServer;
    typedef std::vector<CpiSubscription*> VectorSubscriptions;
    VectorSubscriptions iPendingSubscriptions;
    TUint iInterfaceListListenerId;
    TUint iSubnetListenerId;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPISUBSCRIPTION
