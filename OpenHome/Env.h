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

class IStack
{
public:
    virtual ~IStack() {}
};

namespace Net {
    class InitialisationParams;
} // namespace Net

class Environment
{
    friend class Net::CpStack;
    friend class Net::DvStack;
public:
    Environment(OsContext* aOsContext);
    Environment(OsContext* aOsContext, Net::InitialisationParams* aInitParams);
    ~Environment();

    void GetVersion(TUint& aMajor, TUint& aMinor);
    OpenHome::TimerManager& TimerManager();
    /**
     * Intended for /very/ short operations only
     */
    OpenHome::Mutex& Mutex();

    OsContext* OsCtx();
    OpenHome::NetworkAdapterList& NetworkAdapterList();
    Net::SsdpListenerMulticast& MulticastListenerClaim(TIpAddress aInterface);
    void MulticastListenerRelease(TIpAddress aInterface);
    TUint SequenceNumber();
    Net::InitialisationParams& InitParams();
    void AddObject(IStackObject* aObject);
    void RemoveObject(IStackObject* aObject);
    void ListObjects();
    IStack* CpiStack();
    IStack* DviStack();
private:
    void Construct();
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
    Net::InitialisationParams* iInitParams;
    OpenHome::TimerManager* iTimerManager;
    OpenHome::Mutex* iPublicLock;
    OpenHome::NetworkAdapterList* iNetworkAdapterList;
    typedef std::vector<MListener*> MulticastListeners;
    MulticastListeners iMulticastListeners;
    TUint iSequenceNumber;
    IStack* iCpStack;
    IStack* iDvStack;
    typedef std::map<IStackObject*,IStackObject*> ObjectMap;
    ObjectMap iObjectMap;
    OpenHome::Mutex* iPrivateLock;
};

} // namespace OpenHome

#endif // HEADER_STACK
