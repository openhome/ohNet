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
namespace Net {

class IStack
{
public:
    virtual ~IStack() {}
};

class InitialisationParams;

class Stack
{
    friend class CpStack;
    friend class DvStack;
public:
    Stack(OsContext* aOsContext);
    Stack(OsContext* aOsContext, InitialisationParams* aInitParams);
    ~Stack();

    void GetVersion(TUint& aMajor, TUint& aMinor);
    OpenHome::TimerManager& TimerManager();
    /**
     * Intended for /very/ short operations only
     */
    OpenHome::Mutex& Mutex();

    OsContext* OsCtx();
    OpenHome::NetworkAdapterList& NetworkAdapterList();
    SsdpListenerMulticast& MulticastListenerClaim(TIpAddress aInterface);
    void MulticastListenerRelease(TIpAddress aInterface);
    TUint SequenceNumber();
    InitialisationParams& InitParams();
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
        MListener(Stack& aStack, TIpAddress aInterface);
        ~MListener();
        SsdpListenerMulticast& Listener();
        TIpAddress Interface() const;
        void AddRef();
        TBool RemoveRef();
    private:
        SsdpListenerMulticast iListener;
        TInt iRefCount;
    };
private:
    OsContext* iOsContext;
    InitialisationParams* iInitParams;
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

} // namespace Net
} // namespace OpenHome

#endif // HEADER_STACK
