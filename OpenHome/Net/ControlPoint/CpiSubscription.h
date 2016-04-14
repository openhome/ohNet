#ifndef HEADER_CPISUBSCRIPTION
#define HEADER_CPISUBSCRIPTION

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Net/Private/EventUpnp.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/CpProxy.h> // for IEventProcessor
#include <OpenHome/Net/Core/OhNet.h>

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
class CpiSubscription : public IEventProcessor, private IStackObject, private INonCopyable
{
public:
    /**
     * Return the unique subscription identifier (assigned by the device subscribed to)
     */
    const Brx& Sid() const;

    /**
     * Return the unique subscription identifier (assigned locally).
     * This will be set as the path for the event server and avoids the normal race between
     * subscription completion and initial event.
     */
    TUint Id() const;
    
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
     * Locks subscription iff true is returned.
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

    /**
     * Used by event processing threads to serialise handling of updates to a particular subscription.
     * Intended for internal use only
     */
    void Unlock();
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
    CpiSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType, TUint aId);
    ~CpiSubscription();
    /**
     * Schedule a (subscribe, renew or unsubscribe operation) which will be processed
     * later in a Subscriber thread.  Claims a reference to the subscription, ensuring
     * the class doesn't get deleted before (or, worse, during) that later operation.
     */
    void Schedule(EOperation aOperation, TBool aRejectFutureOperations = false);
    TBool StartSchedule(EOperation aOperation, TBool aRejectFutureOperations);
    void DoSubscribe();
    void Renew();
    void DoRenew();
    void DoUnsubscribe();
    void SetRenewTimer(TUint aMaxSeconds);
    void Resubscribe();
    void NotifySubnetChanged();
    void Suspend();
    TBool RemoveOnSubnetChange() const;
private: // IEventProcessor
    void EventUpdateStart();
    void EventUpdate(const Brx& aName, const Brx& aValue, IOutputProcessor& aProcessor);
    void EventUpdateEnd();
    void EventUpdateError();
    void EventUpdatePrepareForDelete();
private: // from IStackObject
    void ListObjectDetails() const;
private:
    OpenHome::Mutex iLock;
    OpenHome::Mutex iSubscriberLock;
    mutable OpenHome::Mutex iSidLock;
    CpiDevice& iDevice;
    CpStack& iCpStack;
    Environment& iEnv;
    IEventProcessor* iEventProcessor;
    OpenHome::Net::ServiceType iServiceType;
    TUint iId;
    Brh iSid;
    Timer* iTimer;
    TUint iNextSequenceNumber;
    EOperation iPendingOperation;
    TUint iRefCount;
    IInterruptHandler* iInterruptHandler;
    TBool iRejectFutureOperations;
    TBool iSuspended;

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

class PendingSubscription;

/**
 * Singleton which manages the pools of Subscriber and active Subscription instances
 */
class CpiSubscriptionManager : public Thread, private IResumeObserver, private ISuspendObserver
{
public:
    CpiSubscriptionManager(CpStack& aCpStack);
    /**
     * Destructor.  Blocks until all subscriptions have been deleted.
     */
    ~CpiSubscriptionManager();
    CpiSubscription* NewSubscription(CpiDevice& aDevice, IEventProcessor& aEventProcessor, const OpenHome::Net::ServiceType& aServiceType);
    
    /**
     * Returns the subscription with unique id aSid, or NULL if the subscription
     * doesn't exist.  Claims a reference to any subscription returned.  The caller
     * is responsible for releasing this reference.
     */
    CpiSubscription* FindSubscription(TUint aId);
    CpiSubscription* FindSubscription(const Brx& aSid);
    void Remove(CpiSubscription& aSubscription);
    void Schedule(CpiSubscription& aSubscription);
    void ScheduleLocked(CpiSubscription& aSubscription);
    TUint EventServerPort();
    void RenewAll();
private: // from ISuspendObserver
    void NotifySuspended();
private: // from IResumeObserver
    void NotifyResumed();
private:
    class PendingSubscription
    {
    public:
        PendingSubscription(const Brx& aSid);
    public:
        Brn iSid;
        Semaphore iSem;
    };
private:
    void RemoveLocked(CpiSubscription& aSubscription);
    void CurrentNetworkAdapterChanged();
    void SubnetListChanged();
    void HandleInterfaceChange(TBool aNewSubnet);
    TBool ReadyForShutdown() const;
    void ShutdownHasHung();
    void Run();
private:
    CpStack& iCpStack;
    OpenHome::Mutex iLock;
    std::list<CpiSubscription*> iList;
    Fifo<Subscriber*> iFree;
    Subscriber** iSubscribers;
    std::map<TUint,CpiSubscription*> iMap;
    TBool iActive;
    TBool iCleanShutdown;
    Semaphore iWaiter;
    Semaphore iShutdownSem;
    EventServerUpnp* iEventServer;
    TUint iInterfaceListListenerId;
    TUint iInterface;
    TUint iSubnetListenerId;
    TUint iNextSubscriptionId;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPISUBSCRIPTION
