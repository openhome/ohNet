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
#include <OsWrapper.h>
#include <NetworkInterfaceList.h>
#include <Discovery.h>
#include <Zapp.h>
#include <Printer.h>

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
    Stack();
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
    static void AddObject(void* aPtr, const char* aClassName);
    static void RemoveObject(void* aPtr, const char* aClassName);
    static void ListObjects();
private:
    ~Stack();
    static void SetCpiStack(IStack* aStack);
    static void SetDviStack(IStack* aStack);
    static IStack* CpiStack();
    static IStack* DviStack();
    void DoAddObject(void* aPtr, const char* aClassName);
    void DoRemoveObject(void* aPtr, const char* aClassName);
    void DoListObjects();
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

    typedef std::map<void*,void*> ObjectMap;
    class ObjectType
    {
    public:
        ObjectType(const TChar* aName);
        ~ObjectType();
        const Brx& Name() { return iClassName; }
        ObjectMap& Map() { return iMap; }
    private:
        Brh iClassName;
        ObjectMap iMap;
    };
private:
    InitialisationParams* iInitParams;
    Zapp::TimerManager* iTimerManager;
    Zapp::Mutex iPublicLock;
    Zapp::NetworkInterfaceList* iNetworkInterfaceList;
    typedef std::vector<MListener*> MulticastListeners;
    MulticastListeners iMulticastListeners;
    TUint iSequenceNumber;
    IStack* iCpStack;
    IStack* iDvStack;
    typedef std::map<Brn,ObjectType*,BufferCmp> ObjectTypeMap;
    ObjectTypeMap iObjectMap;
    Zapp::Mutex iPrivateLock;
};

} // namespace Zapp

#endif // HEADER_STACK
