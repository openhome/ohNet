/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_STACK
#define HEADER_STACK

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

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
class Shell;
class IInfoAggregator;
class ShellCommandDebug;
class IWriter;
class DnsChangeNotifier;
class IDnsChangeNotifier;

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
    class IMdnsProvider;
} // namespace Net

class Environment
{
    friend class Net::CpStack;
    friend class Net::DvStack;
public:
    enum ELoopback
    {
        ELoopbackExclude, // exclude loopback from list of available subnets
        ELoopbackUse,     // exclude everything but loopback from list of available subnets
        ELoopbackInclude  // include loopback in list of available subnets
    };
    enum EThreadScheduling
    {
        EScheduleDefault,
        ESchedulePriority,
        EScheduleNice,
        EScheduleNone
    };
private:
    static const TBool kIPv6SupportedDefault = false;
public:
    static Environment* Create(FunctorMsg& aLogOutput);
    static Environment* Create(FunctorMsg& aLogOutput,
                               TUint aTimerManagerPriority,
                               EThreadScheduling aSchedulerPolicy,
                               ELoopback aLoopbackPolicy);
    static Environment* Create(Net::InitialisationParams* aInitParams);
    ~Environment();

    void GetVersion(TUint& aMajor, TUint& aMinor);
    OpenHome::TimerManager& TimerManager();

    OsContext* OsCtx();
    Log& Logger();
    OpenHome::NetworkAdapterList& NetworkAdapterList();
    ThreadPriorityArbitrator& PriorityArbitrator();
    OpenHome::Shell* Shell();
    IInfoAggregator* InfoAggregator();
    OpenHome::ShellCommandDebug* ShellCommandDebug();
    Net::SsdpListenerMulticast& MulticastListenerClaim(const TIpAddress& aInterface);
    void MulticastListenerRelease(const TIpAddress& aInterface);
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
    void SetHttpUserAgent(const Brx& aUserAgent);
    TBool HasHttpUserAgent() const;
    void WriteHttpUserAgent(IWriter& aWriter);
    void AddObject(IStackObject* aObject);
    void RemoveObject(IStackObject* aObject);
    void ListObjects();
    IStack* CpiStack();
    IStack* DviStack();
    void CreateMdnsProvider();
    Net::IMdnsProvider* MdnsProvider();
    IDnsChangeNotifier* DnsChangeNotifier();
    void SetInitParams(Net::InitialisationParams* aInitParams);
private:
    Environment(FunctorMsg& aLogOutput);
    Environment(FunctorMsg& aLogOutput,
                TUint aTimerManagerPriority,
                EThreadScheduling aSchedulerPolicy,
                ELoopback aLoopbackPolicy);
    Environment(Net::InitialisationParams* aInitParams);
    void Construct(FunctorMsg& aLogOutput, EThreadScheduling aSchedulerPolicy);
    void DoSetInitParams(Net::InitialisationParams* aInitParams);
    void CreateShell();
    void SetCpStack(IStack* aStack);
    void SetDvStack(IStack* aStack);
    static void DnsChanged(void* aSelf);
private:
    OsContext* iOsContext;
    Log* iLogger;
    Net::InitialisationParams* iInitParams;
    OpenHome::TimerManager* iTimerManager;
    OpenHome::Mutex* iPublicLock;
    OpenHome::NetworkAdapterList* iNetworkAdapterList;
    ThreadPriorityArbitrator* iThreadPriorityArbitrator;
    OpenHome::Shell* iShell;
    IInfoAggregator* iInfoAggregator;
    OpenHome::ShellCommandDebug* iShellCommandDebug;
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
    Bws<128> iHttpUserAgent;
    Net::IMdnsProvider* iMdns;
    OpenHome::DnsChangeNotifier* iDnsChangeNotifier;
};

} // namespace OpenHome

#endif // HEADER_STACK
