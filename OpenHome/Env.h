/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_STACK
#define HEADER_STACK

#include <OpenHome/Types.h>

#include <vector>
#include <map>

namespace OpenHome {
class FunctorMsg;
class TimerManager;
class Mutex;
class NetworkAdapterList;
class ThreadPriorityArbitrator;
class Log;
class MListener;
class IStackObject;

class IStack
{
public:
    virtual ~IStack() {}
};

class ISuspendObserver
{
public:
    virtual void NotifySuspended() = 0; // not allowed to throw
};

class IResumeObserver
{
public:
    virtual void NotifyResumed() = 0; // not allowed to throw
};

namespace Net {
    class InitialisationParams;
    class CpStack;
    class DvStack;
    class SsdpListenerMulticast;
} // namespace Net

class Environment
{
    friend class Net::CpStack;
    friend class Net::DvStack;
public:
    static Environment* Create(FunctorMsg& aLogOutput);
    static Environment* Create(Net::InitialisationParams* aInitParams);
    ~Environment();

    void GetVersion(TUint& aMajor, TUint& aMinor);
    OpenHome::TimerManager& TimerManager();
    /**
     * Intended for /very/ short operations only
     */
    OpenHome::Mutex& Mutex();

    OsContext* OsCtx();
    Log& Logger();
    OpenHome::NetworkAdapterList& NetworkAdapterList();
    ThreadPriorityArbitrator& PriorityArbitrator();
    Net::SsdpListenerMulticast& MulticastListenerClaim(TIpAddress aInterface);
    void MulticastListenerRelease(TIpAddress aInterface);
    void AddSuspendObserver(ISuspendObserver& aObserver);
    void AddResumeObserver(IResumeObserver& aObserver);
    void RemoveSuspendObserver(ISuspendObserver& aObserver);
    void RemoveResumeObserver(IResumeObserver& aObserver);
    void NotifySuspended();
    void NotifyResumed();
    TUint SequenceNumber();
    TInt Random();
    TUint Random(TUint aMaxValue, TUint aMinValue = 0);
    void SetRandomSeed(TUint aSeed);
    Net::InitialisationParams* InitParams();
    void AddObject(IStackObject* aObject);
    void RemoveObject(IStackObject* aObject);
    void ListObjects();
    IStack* CpiStack();
    IStack* DviStack();
    void SetInitParams(Net::InitialisationParams* aInitParams);
private:
    Environment(FunctorMsg& aLogOutput);
    Environment(Net::InitialisationParams* aInitParams);
    void Construct(FunctorMsg& aLogOutput);
    void SetCpStack(IStack* aStack);
    void SetDvStack(IStack* aStack);
private:
    OsContext* iOsContext;
    Log* iLogger;
    Net::InitialisationParams* iInitParams;
    OpenHome::TimerManager* iTimerManager;
    OpenHome::Mutex* iPublicLock;
    OpenHome::NetworkAdapterList* iNetworkAdapterList;
    ThreadPriorityArbitrator* iThreadPriorityArbitrator;
    std::vector<MListener*> iMulticastListeners;
    std::vector<ISuspendObserver*> iSuspendObservers;
    std::vector<IResumeObserver*> iResumeObservers;
    OpenHome::Mutex* iSuspendResumeObserverLock;
    TUint iSequenceNumber;
    IStack* iCpStack;
    IStack* iDvStack;
    typedef std::map<IStackObject*,IStackObject*> ObjectMap;
    ObjectMap iObjectMap;
    OpenHome::Mutex* iPrivateLock;
};

} // namespace OpenHome

#endif // HEADER_STACK
