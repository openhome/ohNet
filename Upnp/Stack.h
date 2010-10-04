/**
 * UPnP library internal APIs
 *
 * NOT intended for use by clients of the library
 */

#ifndef HEADER_STACK
#define HEADER_STACK

#include <ZappTypes.h>
#include <Thread.h>
#include <Timer.h>
#include <Os.h>
#include <NetworkInterfaceList.h>
#include <Discovery.h>
#include <Zapp.h>

#include <vector>

namespace Zapp {

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
    Stack(InitialisationParams* aInitParams);
    static void Destroy();
    static TBool IsInitialised();
	static void GetVersion(TUint& aMajor, TUint& aMinor);
    static Zapp::TimerManager& TimerManager();
    /**
     * Intended for /very/ short operations only
     */
    static Zapp::Mutex& Mutex();

    static Zapp::NetworkInterfaceList& NetworkInterfaceList();
    static SsdpListenerMulticast& MulticastListenerClaim(TIpAddress aInterface);
    static void MulticastListenerRelease(TIpAddress aInterface);
    static TUint SequenceNumber();
    static InitialisationParams& InitParams();
private:
    ~Stack();
    static void SetCpiStack(IStack* aStack);
    static void SetDviStack(IStack* aStack);
    static IStack* CpiStack();
    static IStack* DviStack();
private:
    class MListener
    {
    public:
        MListener(TIpAddress aInterface);
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
    Zapp::TimerManager iTimerManager;
    Zapp::Mutex iLock;
    Zapp::NetworkInterfaceList* iNetworkInterfaceList;
    typedef std::vector<MListener*> MulticastListeners;
    MulticastListeners iMulticastListeners;
    TUint iSequenceNumber;
    IStack* iCpStack;
    IStack* iDvStack;
};

} // namespace Zapp

#endif // HEADER_STACK
