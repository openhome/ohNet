/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_STACK
#define HEADER_STACK

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Private/Discovery.h>

#include <vector>
#include <map>

namespace OpenHome {
class TimerManager;
class Mutex;
class NetworkAdapterList;
class Log;

class IStack
{
public:
    virtual ~IStack() {}
};

class IResumeObserver
{
public:
    virtual void NotifyResumed() = 0; // not allowed to throw
};

namespace Net {
    class InitialisationParams;
} // namespace Net

class Environment
{
    friend class Net::CpStack;
    friend class Net::DvStack;
public:
    Environment(FunctorMsg& aLogOutput);
    Environment(Net::InitialisationParams* aInitParams);
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
    Net::SsdpListenerMulticast& MulticastListenerClaim(TIpAddress aInterface);
    void MulticastListenerRelease(TIpAddress aInterface);
    void AddResumeObserver(IResumeObserver& aObserver);
    void RemoveResumeObserver(IResumeObserver& aObserver);
    void NotifyResumed();
    TUint SequenceNumber();
    TInt Random();
    TUint Random(TUint aMaxValue, TUint aMinValue = 0);
    void SetRandomSeed(TUint aSeed);
    Net::InitialisationParams& InitParams();
    void AddObject(IStackObject* aObject);
    void RemoveObject(IStackObject* aObject);
    void ListObjects();
    IStack* CpiStack();
    IStack* DviStack();
private:
    void Construct(FunctorMsg& aLogOutput);
    void SetCpStack(IStack* aStack);
    void SetDvStack(IStack* aStack);
private:
    class MListener
    {
    public:
        MListener(Environment& aStack, TIpAddress aInterface);
        ~MListener();
        Net::SsdpListenerMulticast& Listener();
        TIpAddress Interface() const;
        void AddRef();
        TBool RemoveRef();
    private:
        Net::SsdpListenerMulticast iListener;
        TInt iRefCount;
    };
private:
    OsContext* iOsContext;
    Log* iLogger;
    Net::InitialisationParams* iInitParams;
    OpenHome::TimerManager* iTimerManager;
    OpenHome::Mutex* iPublicLock;
    OpenHome::NetworkAdapterList* iNetworkAdapterList;
    typedef std::vector<MListener*> MulticastListeners;
    MulticastListeners iMulticastListeners;
    std::vector<IResumeObserver*> iResumeObservers;
    OpenHome::Mutex* iResumeObserverLock;
    TUint iSequenceNumber;
    IStack* iCpStack;
    IStack* iDvStack;
    typedef std::map<IStackObject*,IStackObject*> ObjectMap;
    ObjectMap iObjectMap;
    OpenHome::Mutex* iPrivateLock;
};

} // namespace OpenHome

#endif // HEADER_STACK
