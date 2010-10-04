// C++ wrapper to the C interfaces to the OS porting layer
// UPnP library code should call this rather than the C APIs

#ifndef HEADER_LINN_OS_CPP
#define HEADER_LINN_OS_CPP

#include <C/Os.h>
#include <ZappTypes.h>
#include <Standard.h>
#include <Network.h>
#include <Zapp.h>

#include <vector>

namespace Zapp {

class Os
{
public:
    inline static TInt Create();
    inline static void Destroy();
    inline static void Quit();
    inline static TUint TimeInMs();
    inline static TUint64 TimeInUs();
    inline static void ConsoleWrite(const TChar* aStr);
	static Brn GetPlatformNameAndVersion(TUint& aMajor, TUint& aMinor);
    inline static THandle SemaphoreCreate(const TChar* aName, TUint aCount);
    inline static void SemaphoreDestroy(THandle aSem);
    inline static void SemaphoreWait(THandle aSem);
    inline static TBool  SemaphoreTimedWait(THandle aSem, TUint aTimeoutMs);
    inline static TBool SemaphoreClear(THandle aSem);
    inline static void SemaphoreSignal(THandle aSem);
    inline static THandle MutexCreate(const TChar* aName);
    inline static void MutexDestroy(THandle aMutex);
    inline static void MutexLock(THandle aMutex);
    inline static void MutexUnlock(THandle aMutex);
    inline static THandle ThreadCreate(const TChar* aName, TUint aPriority, TUint aStackBytes,
                                       ThreadEntryPoint aEntryPoint, void* aArg);
    inline static void* ThreadTls();
    inline static void ThreadDestroy(THandle aThread);
    inline static TBool ThreadSupportsPriorities();
    static THandle NetworkCreate(ESocketType aSocketType);
    static TInt NetworkBind(THandle aHandle, Endpoint& aEndpoint);
    static void NetworkConnect(THandle aHandle, const Endpoint& aEndpoint, TUint aTimeoutMs);
    inline static TInt NetworkSend(THandle aHandle, const Brx& aBuffer);
    inline static TInt NetworkSendTo(THandle aHandle, const Brx& aBuffer, const Endpoint& aEndpoint);
    inline static TInt NetworkReceive(THandle aHandle, Bwx& aBuffer);
    static TInt NetworkReceiveFrom(THandle aHandle, Bwx& aBuffer, Endpoint& aEndpoint);
    inline static TInt NetworkInterrupt(THandle aHandle, TBool aInterrupt);
    inline static TInt NetworkClose(THandle aHandle);
    inline static TInt NetworkListen(THandle aHandle, TUint aSlots);
    inline static THandle NetworkAccept(THandle aHandle);
    static TIpAddress NetworkGetHostByName(const Brx& aAddress);
    static void NetworkSocketSetSendBufBytes(THandle aHandle, TUint aBytes);
    static void NetworkSocketSetReceiveTimeout(THandle aHandle, TUint aMilliSeconds);
    static void NetworkTcpSetNoDelay(THandle aHandle);
    static void NetworkSocketSetReuseAddress(THandle aHandle);
    static void NetworkSocketSetMulticastTtl(THandle aHandle, TUint8 aTtl);
    static void NetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aAddress, TIpAddress aInterface);
    static void NetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aAddress, TIpAddress aInterface);
    static std::vector<NetworkInterface*>* NetworkListInterfaces();
    inline static void NetworkSetInterfaceChangedObserver(InterfaceListChanged aCallback, void* aArg);
};

#include <Os.inl>

} // namespace Zapp
#endif // HEADER_LINN_OS_C
