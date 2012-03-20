/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_STACK
#define HEADER_STACK

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Printer.h>

#include <vector>

namespace OpenHome {
namespace Net {

class IStack
{
public:
    virtual ~IStack() {}
};

class Stack
{
    friend class CpiStack;
    friend class DviStack;
public:
    Stack();
    Stack(InitialisationParams* aInitParams);
    static void Destroy();
    static TBool IsInitialised();
    static void GetVersion(TUint& aMajor, TUint& aMinor);
    static OpenHome::TimerManager& TimerManager();
    /**
     * Intended for /very/ short operations only
     */
    static OpenHome::Mutex& Mutex();

    static OpenHome::NetworkAdapterList& NetworkAdapterList();
    static SsdpListenerMulticast& MulticastListenerClaim(TIpAddress aInterface);
    static void MulticastListenerRelease(TIpAddress aInterface);
    static TUint SequenceNumber();
    static InitialisationParams& InitParams();
    static void AddObject(IStackObject* aObject);
    static void RemoveObject(IStackObject* aObject);
    static void ListObjects();
private:
    ~Stack();
    static void SetCpiStack(IStack* aStack);
    static void SetDviStack(IStack* aStack);
    static IStack* CpiStack();
    static IStack* DviStack();
    void DoAddObject(IStackObject* aObject);
    void DoRemoveObject(IStackObject* aObject);
    void DoListObjects();
private:
    class MListener
    {
    public:
        MListener(TIpAddress aInterface);
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
    InitialisationParams* iInitParams;
    OpenHome::TimerManager* iTimerManager;
    OpenHome::Mutex iPublicLock;
    OpenHome::NetworkAdapterList* iNetworkAdapterList;
    typedef std::vector<MListener*> MulticastListeners;
    MulticastListeners iMulticastListeners;
    TUint iSequenceNumber;
    IStack* iCpStack;
    IStack* iDvStack;
    typedef std::map<IStackObject*,IStackObject*> ObjectMap;
    ObjectMap iObjectMap;
    OpenHome::Mutex iPrivateLock;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_STACK
