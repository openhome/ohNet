// Implementation of Os.h APIs for Windows

#include <C/Os.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <Winsock2.h>
#include <Windows.h>
#include <Ws2tcpip.h>
#include <Iphlpapi.h>

static const uint32_t kMinStackBytes = 1024 * 16;
static const uint32_t kStackPaddingBytes = 1024 * 16;
static const uint32_t kPriorityMin = 50;
static const uint32_t kPriorityMax = 150;


typedef struct InterfaceChangeObserver
{
    InterfaceListChanged iCallback;
    void*                iArg;
    SOCKET               iSocket;
    WSAEVENT             iEvent;
    WSAEVENT             iShutdownEvent;
    int                  iShutdown;
    HANDLE               iSem;
} InterfaceChangeObserver;

static uint64_t gStartTime;
static DWORD gTlsIndex;
static THandle gMutex = kHandleNull;
static InterfaceChangeObserver* gInterfaceChangeObserver = NULL;
static int32_t gTestInterfaceIndex = -1;

int32_t OsCreate()
{
    FILETIME ft;
    WSADATA wsaData;
    WORD ver = (2<<8)|2; // WinSock v2.2.  Standard on XP and later

    GetSystemTimeAsFileTime(&ft);
    gStartTime = ft.dwHighDateTime;
    gStartTime <<= 32;
    gStartTime |= ft.dwLowDateTime;

    gTlsIndex = TlsAlloc();
    if (TLS_OUT_OF_INDEXES == gTlsIndex) {
        return -1;
    }
    gMutex = OsMutexCreate("");
    if (kHandleNull == gMutex) {
        TlsFree(gTlsIndex);
        return -1;
    }
    if (0 != WSAStartup(ver, &wsaData)) {
        OsMutexDestroy(gMutex);
        TlsFree(gTlsIndex);
        return -1;
    }

    return 0;
}

void OsDestroy()
{
    if (NULL != gInterfaceChangeObserver) {
        gInterfaceChangeObserver->iShutdown = 1;
        (void)WSASetEvent(gInterfaceChangeObserver->iShutdownEvent);
        (void)WaitForSingleObject(gInterfaceChangeObserver->iSem, INFINITE);
        CloseHandle(gInterfaceChangeObserver->iSem);
        WSACloseEvent(gInterfaceChangeObserver->iEvent);
        WSACloseEvent(gInterfaceChangeObserver->iShutdownEvent);
        (void)closesocket(gInterfaceChangeObserver->iSocket);
    }
    (void)WSACleanup();
    OsMutexDestroy(gMutex);
    gMutex = kHandleNull;
    TlsFree(gTlsIndex);
}

void OsQuit()
{
    abort();
}

uint64_t OsTimeInUs()
{
    uint64_t timeNow;
    uint64_t diff;
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    timeNow = ft.dwHighDateTime;
    timeNow <<= 32;
    timeNow |= ft.dwLowDateTime;
    diff = timeNow - gStartTime;
    diff /= 10; // GetSystemTimeAsFileTime has units of 100 nano-secs
    return diff;
}

void OsConsoleWrite(const char* aStr)
{
    fprintf(stderr, "%s", aStr);
    fflush(stderr);
}

void OsGetPlatformNameAndVersion(char** aName, uint32_t* aMajor, uint32_t* aMinor)
{
	OSVERSIONINFO verInfo;
	memset(&verInfo, 0, sizeof(verInfo));
	verInfo.dwOSVersionInfoSize = sizeof(verInfo);
	(void)GetVersionEx(&verInfo);
	*aName = "Windows";
	*aMajor = verInfo.dwMajorVersion;
	*aMinor = verInfo.dwMinorVersion;
}

THandle OsSemaphoreCreate(const char* aName, uint32_t aCount)
{
    aName = aName;
    return (THandle)CreateSemaphore(NULL, aCount, INT32_MAX, NULL);
}

void OsSemaphoreDestroy(THandle aSem)
{
    CloseHandle((HANDLE)aSem);
}

int32_t OsSemaphoreWait(THandle aSem)
{
    DWORD ret = WaitForSingleObject((HANDLE)aSem, INFINITE);
    return (ret==WAIT_OBJECT_0? 0 : -1);
}

int32_t OsSemaphoreTimedWait(THandle aSem, uint32_t aTimeoutMs)
{
    DWORD ret = WaitForSingleObject((HANDLE)aSem, aTimeoutMs);
    if (WAIT_OBJECT_0 == ret) {
        return 1;
    }
    else if (WAIT_TIMEOUT == ret) {
        return 0;
    }
    return -1;
}

uint32_t OsSemaphoreClear(THandle aSem)
{
    uint32_t cleared = 0;
    while (WAIT_OBJECT_0 == WaitForSingleObject((HANDLE)aSem, 0)) {
        cleared = 1;
    }
    return cleared;
}

int32_t OsSemaphoreSignal(THandle aSem)
{
    int32_t ret = 0;
    if (0 == ReleaseSemaphore((HANDLE)aSem, 1, NULL)) {
        ret = -1;
    }
    return ret;
}

typedef struct
{
    CRITICAL_SECTION iCs;
    uint32_t         iCount;
} Mutex;

THandle OsMutexCreate(const char* aName)
{
    Mutex* mutex = calloc(1, sizeof(*mutex));
    aName = aName;
    if (NULL == mutex) {
        return kHandleNull;
    }
    InitializeCriticalSection(&mutex->iCs);
    return (THandle)mutex;
}

void OsMutexDestroy(THandle aMutex)
{
    Mutex* mutex = (Mutex*)aMutex;
    DeleteCriticalSection(&mutex->iCs);
    free(mutex);
}

int32_t OsMutexLock(THandle aMutex)
{
    Mutex* mutex = (Mutex*)aMutex;
    EnterCriticalSection(&mutex->iCs);
    if (0 != mutex->iCount) {
        LeaveCriticalSection(&mutex->iCs);
        return -1;
    }
    mutex->iCount++;
    return 0;
}

int32_t OsMutexUnlock(THandle aMutex)
{
    Mutex* mutex = (Mutex*)aMutex;
    if (1 != mutex->iCount) {
        return -1;
    }
    --mutex->iCount;
    LeaveCriticalSection(&mutex->iCs);
    return 0;
}

typedef struct
{
    HANDLE           iThread;
    ThreadEntryPoint iEntryPoint;
    void*            iArg;
    uint32_t         iPriority;
} ThreadData;


DWORD threadEntrypoint(LPVOID aArg)
{
    ThreadData* data = (ThreadData*)aArg;
    int priority = THREAD_PRIORITY_NORMAL;
    static const int kHostPriorities[] = { THREAD_PRIORITY_IDLE
                                          ,THREAD_PRIORITY_LOWEST
                                          ,THREAD_PRIORITY_BELOW_NORMAL
                                          ,THREAD_PRIORITY_NORMAL
                                          ,THREAD_PRIORITY_ABOVE_NORMAL
                                          ,THREAD_PRIORITY_HIGHEST
                                          ,THREAD_PRIORITY_TIME_CRITICAL };
    static const int kNumHostPriorities = sizeof(kHostPriorities) / sizeof(kHostPriorities[0]);
    int step = (kPriorityMax - kPriorityMin) / kNumHostPriorities;
    int i;

    assert(data != NULL);

    for (i=kNumHostPriorities-1; i>=0; i--) {
        if (kPriorityMin + (i*step) < data->iPriority) {
            priority = kHostPriorities[i];
            break;
        }
    }
    if (!SetThreadPriority(data->iThread, priority)) {
        //fprintf(stderr, "SetPriority failed (err=%d)\n", GetLastError());
        //fflush(stderr);
    }

    (void)TlsSetValue(gTlsIndex, data->iArg);
    data->iEntryPoint(data->iArg);

    return 0;
}

THandle OsThreadCreate(const char* aName, uint32_t aPriority, uint32_t aStackBytes,
                       ThreadEntryPoint aEntryPoint, void* aArg)
{
    ThreadData* data = (ThreadData*)calloc(1, sizeof(ThreadData));
    if (NULL == data) {
        return kHandleNull;
    }
    aName = aName;
    if (aPriority < kPriorityMin || aPriority > kPriorityMax) {
        return kHandleNull;
    }
    if (aStackBytes < kMinStackBytes) {
        aStackBytes = kMinStackBytes;
    }
    aStackBytes += kStackPaddingBytes;
    data->iEntryPoint = aEntryPoint;
    data->iArg        = aArg;
    data->iPriority   = aPriority;

    data->iThread = CreateThread(NULL, aStackBytes, (LPTHREAD_START_ROUTINE)&threadEntrypoint, data, 0, NULL);
    if (0 == data->iThread) {
        free(data);
    }
    return (THandle)data;
}

void* OsThreadTls()
{
    return TlsGetValue(gTlsIndex);
}

void OsThreadDestroy(THandle aThread)
{
    free((ThreadData*)aThread);
}

int32_t OsThreadSupportsPriorities()
{
    // we do support priorities but can't manage the full range the library expects
    return 0;
}

typedef struct OsNetworkHandle
{
    SOCKET   iSocket;
    WSAEVENT iEvent;
    int32_t  iInterrupted;
}OsNetworkHandle;

static int32_t SocketInterrupted(const OsNetworkHandle* aHandle)
{
    int32_t interrupted;
    OsMutexLock(gMutex);
    interrupted = aHandle->iInterrupted;
    OsMutexUnlock(gMutex);
    return interrupted;
}

static void sockaddrFromEndpoint(struct sockaddr_in* aAddr, TIpAddress aAddress, uint16_t aPort)
{
    memset(aAddr, 0, sizeof(*aAddr));
    aAddr->sin_family = AF_INET;
    aAddr->sin_port = SwapEndian16(aPort);
    aAddr->sin_addr.s_addr = aAddress;
}

static OsNetworkHandle* CreateHandle(SOCKET aSocket)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)malloc(sizeof(OsNetworkHandle));
    if (NULL == handle) {
        (void)closesocket(handle->iSocket);
        return kHandleNull;
    }
    handle->iEvent = WSACreateEvent();
    if (NULL == handle->iEvent) {
        (void)closesocket(handle->iSocket);
        free(handle);
        return kHandleNull;
    }
    handle->iSocket = aSocket;
    handle->iInterrupted = 0;

    return handle;
}

static void SetSocketNonBlocking(SOCKET aSocket)
{
    u_long nonBlocking = 0;
    WSAEventSelect(aSocket, NULL, 0);
    if (-1 == ioctlsocket(aSocket, FIONBIO, &nonBlocking)) {
        fprintf(stdout, "SetSocketNonBlocking failed for socket %u\n", aSocket);
    }
}

THandle OsNetworkCreate(OsNetworkSocketType aSocketType)
{
    int32_t socketH = socket(AF_INET, aSocketType, 0);
    OsNetworkHandle* handle = CreateHandle(socketH);
    return (THandle)handle;
}

int32_t OsNetworkBind(THandle aHandle, TIpAddress aAddress, uint16_t* aPort)
{
    struct sockaddr_in addr;
	int len;
    int err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    sockaddrFromEndpoint(&addr, aAddress, *aPort);
    err = bind(handle->iSocket, (struct sockaddr*)&addr, sizeof(addr));
	if (err != 0) {
		return -1;
	}
	len = sizeof(addr);
	if (0 != getsockname(handle->iSocket, (struct sockaddr*)&addr, &len)) {
		return -1;
	}
	*aPort = SwapEndian16(addr.sin_port);
    return 0;
}

int32_t OsNetworkConnect(THandle aHandle, TIpAddress aAddress, uint16_t aPort, uint32_t aTimeoutMs)
{
    int32_t err = -1;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct sockaddr_in addr;
    WSAEVENT event;
    HANDLE handles[2];
    DWORD ret;

    if (SocketInterrupted(handle)) {
        return -1;
    }

    event = WSACreateEvent();
    if (NULL == event) {
        return -1;
    }
    if (0 != WSAEventSelect(handle->iSocket, event, FD_CONNECT|FD_WRITE)) {
        WSACloseEvent(event);
        return -1;
    }

    sockaddrFromEndpoint(&addr, aAddress, aPort);
    (void)connect(handle->iSocket, (struct sockaddr*)&addr, sizeof(addr));
    handles[0] = event;
    handles[1] = handle->iEvent;
    ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, aTimeoutMs, FALSE);
    if (WAIT_OBJECT_0 == ret) {
        err = 0;
    }

    SetSocketNonBlocking(handle->iSocket);
    WSACloseEvent(event);
    return err;
}

int32_t OsNetworkSend(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes)
{
    int32_t sent;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
#if 0
    {
        char buf[1025];
        size_t len = (aBytes<1025? aBytes : 1024);
        memcpy(buf, aBuffer, len);
        buf[len] = '\0';
        fprintf(stdout, "OsNetworkSend, sending\n%s\n", buf);
    }
#endif
	sent = send(handle->iSocket, (const char*)aBuffer, aBytes, 0);
    return sent;
}

int32_t OsNetworkSendTo(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes, TIpAddress aAddress, uint16_t aPort)
{
    int32_t sent;
    struct sockaddr_in addr;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    sockaddrFromEndpoint(&addr, aAddress, aPort);
#if 0
    {
        char buf[1025];
        size_t len = (aBytes<1025? aBytes : 1024);
        memcpy(buf, aBuffer, len);
        buf[len] = '\0';
        fprintf(stdout, "OsNetworkSendTo, sending\n%s\n", buf);
    }
#endif
    sent = sendto(handle->iSocket, (const char*)aBuffer, aBytes, 0, (struct sockaddr*)&addr, sizeof(addr));
    return sent;
}

int32_t OsNetworkReceive(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes)
{
    int32_t received;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    WSAEVENT event;
    HANDLE handles[2];
    DWORD ret;

    if (SocketInterrupted(handle)) {
        return -1;
    }

    event = WSACreateEvent();
    if (NULL == event) {
        return -1;
    }
    if (0 != WSAEventSelect(handle->iSocket, event, FD_READ|FD_CLOSE)) {
        WSACloseEvent(event);
        return -1;
    }

    received = recv(handle->iSocket, (char*)aBuffer, aBytes, 0);
    if (SOCKET_ERROR==received && WSAEWOULDBLOCK==WSAGetLastError()) {
        handles[0] = event;
        handles[1] = handle->iEvent;
        ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
        if (WAIT_OBJECT_0 == ret) {
            received = recv(handle->iSocket, (char*)aBuffer, aBytes, 0);
        }
    }

    SetSocketNonBlocking(handle->iSocket);
    WSACloseEvent(event);
    return received;
}

int32_t OsNetworkReceiveFrom(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes, TIpAddress* aAddress, uint16_t* aPort)
{
    int32_t received;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct sockaddr_in addr;
    int len = sizeof(addr);
    WSAEVENT event;
    HANDLE handles[2];
    DWORD ret;

    if (SocketInterrupted(handle)) {
        return -1;
    }

    sockaddrFromEndpoint(&addr, 0, 0);

    event = WSACreateEvent();
    if (NULL == event) {
        return -1;
    }
    if (0 != WSAEventSelect(handle->iSocket, event, FD_READ|FD_CLOSE)) {
        WSACloseEvent(event);
        return -1;
    }

    received = recvfrom(handle->iSocket, (char*)aBuffer, aBytes, 0, (struct sockaddr*)&addr, &len);
    if (SOCKET_ERROR==received && WSAEWOULDBLOCK==WSAGetLastError()) {
        handles[0] = event;
        handles[1] = handle->iEvent;
        ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
        if (WAIT_OBJECT_0 == ret) {
            received = recvfrom(handle->iSocket, (char*)aBuffer, aBytes, 0, (struct sockaddr*)&addr, &len);
        }
    }

    SetSocketNonBlocking(handle->iSocket);
    WSACloseEvent(event);
    *aAddress = addr.sin_addr.s_addr;
    *aPort = SwapEndian16(addr.sin_port);
    return received;
}

int32_t OsNetworkInterrupt(THandle aHandle, int32_t aInterrupt)
{
    int32_t err = 0;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    OsMutexLock(gMutex);
    handle->iInterrupted = aInterrupt;
    if (aInterrupt != 0) {
        (void)WSASetEvent(handle->iEvent);
    }
    else {
        (void)WSAResetEvent(handle->iEvent);
    }
    OsMutexUnlock(gMutex);
    return err;
}

int32_t OsNetworkClose(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = closesocket(handle->iSocket);
    if (0 == err) {
        WSACloseEvent(handle->iEvent);
        free(handle);
    }
    return err;
}

int32_t OsNetworkListen(THandle aHandle, uint32_t aSlots)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    err = listen(handle->iSocket, aSlots);
    return err;
}

THandle OsNetworkAccept(THandle aHandle)
{
    SOCKET h;
    OsNetworkHandle* newHandle;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    WSAEVENT event;
    HANDLE handles[2];
    DWORD ret;

    if (SocketInterrupted(handle)) {
        return kHandleNull;
    }
    event = WSACreateEvent();
    if (NULL == event) {
        return kHandleNull;
    }
    if (0 != WSAEventSelect(handle->iSocket, event, FD_ACCEPT|FD_CLOSE)) {
        WSACloseEvent(event);
        return kHandleNull;
    }

    h = accept(handle->iSocket, NULL, NULL);
    if (INVALID_SOCKET==h && WSAEWOULDBLOCK==WSAGetLastError()) {
        handles[0] = event;
        handles[1] = handle->iEvent;
        ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
        if (WAIT_OBJECT_0 == ret) {
            h = accept(handle->iSocket, NULL, NULL);
        }
    }
    SetSocketNonBlocking(handle->iSocket);
    WSACloseEvent(event);
    if (INVALID_SOCKET == h) {
        return kHandleNull;
    }

    newHandle = CreateHandle(h);
    if (NULL == newHandle) {
        return kHandleNull;
    }

    return (THandle)newHandle;
}

int32_t OsNetworkGetHostByName(const char* aAddress, TIpAddress* aHost)
{
    int32_t ret = 0;
    struct hostent* dns = gethostbyname(aAddress);
    if (NULL == dns) {
        ret = -1;
    }
    else {
        *aHost = *((uint32_t*)(dns->h_addr_list[0]));
    }

    return ret;
}

int32_t OsNetworkSocketSetSendBufBytes(THandle aHandle, uint32_t aBytes)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&aBytes, sizeof(aBytes));
    return err;
}

int32_t OsNetworkSocketSetReceiveTimeout(THandle aHandle, uint32_t aMilliSeconds)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct timeval tv;
    tv.tv_sec = aMilliSeconds/1000;
    tv.tv_usec = (aMilliSeconds%1000)*1000;
    err = setsockopt(handle->iSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    return err;
}

int32_t OsNetworkTcpSetNoDelay(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    uint32_t nodelay = 1;
    int32_t err = setsockopt(handle->iSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&nodelay, sizeof(nodelay));
    return err;
}

int32_t OsNetworkSocketSetReuseAddress(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t reuseaddr = 1;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuseaddr, sizeof(reuseaddr));
    return err;
}

int32_t OsNetworkSocketSetMulticastTtl(THandle aHandle, uint8_t aTtl)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = setsockopt(handle->iSocket, IPPROTO_IP, IP_MULTICAST_TTL, (const char*)&aTtl, sizeof(aTtl));
    return err;
}

int32_t OsNetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aAddress, TIpAddress aInterface)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = aAddress;
    mreq.imr_interface.s_addr = aInterface;
    err = setsockopt(handle->iSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));
    return err;
}

int32_t OsNetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aAddress, TIpAddress aInterface)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = aAddress;
    mreq.imr_interface.s_addr = aInterface;
    err = setsockopt(handle->iSocket, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));
    return err;
}

int32_t OsNetworkListInterfaces(OsNetworkInterface** aInterfaces)
{
    IP_ADAPTER_INFO* info;
    ULONG bytes;
    OsNetworkInterface* head = NULL;
    int32_t index = 0;

    if (ERROR_BUFFER_OVERFLOW != GetAdaptersInfo(NULL, &bytes)) {
        return -1;
    }
    info = (IP_ADAPTER_INFO*)malloc(bytes);
    if (ERROR_SUCCESS == GetAdaptersInfo(info, &bytes)) {
        IP_ADAPTER_INFO* ptr = info;
        int32_t includeLoopback = 1;

        // Only include loopback if there are no non-loopback adapters
        while (NULL != ptr && includeLoopback) {
            if (ptr->Type != MIB_IF_TYPE_LOOPBACK) {
                includeLoopback = 0;
            }
            ptr = ptr->Next;
        }

        ptr = info;
        while (NULL != ptr) {
            OsNetworkInterface* nif;
            if (ptr->Type == MIB_IF_TYPE_LOOPBACK && !includeLoopback) {
                ptr = ptr->Next;
                continue;
            }
            if (-1 != gTestInterfaceIndex && index++ != gTestInterfaceIndex) {
                ptr = ptr->Next;
                continue;
            }
            nif = (OsNetworkInterface*)calloc(1, sizeof(*nif));
            if (nif == NULL) {
                goto failure;
            }
            nif->iReserved = ptr->Type;
            if (0 != OsNetworkGetHostByName(ptr->IpAddressList.IpAddress.String, &nif->iAddress)) {
                free(nif);
                goto failure;
            }
            if (0 != OsNetworkGetHostByName(ptr->IpAddressList.IpMask.String, &nif->iNetMask)) {
                free(nif);
                goto failure;
            }
			
			/* discard nifs with unusable zero'd address or mask */

			if (nif->iAddress==0 || nif->iNetMask==0) {
			    free(nif);
                ptr = ptr->Next;
				continue;
			}
            
			if (head == NULL) {
                head = nif;
            }
            else {
                TIpAddress subnet = (nif->iAddress & nif->iNetMask);
                OsNetworkInterface* p1 = head;
                OsNetworkInterface* prev = NULL;
                while (NULL != p1) {
                    if ((p1->iAddress & p1->iNetMask) == subnet) {
                        while (NULL != p1 && IF_TYPE_ETHERNET_CSMACD == p1->iReserved) {
                            prev = p1;
                            p1 = p1->iNext;
                        }
                        break;
                    }
                    prev = p1;
                    p1 = p1->iNext;
                }
                if (NULL == prev) {
                    nif->iNext = head;
                    head = nif;
                }
                else {
                    nif->iNext = prev->iNext;
                    prev->iNext = nif;
                }
            }
            nif->iName = (char*)malloc(strlen(ptr->Description)+1);
            if (NULL == nif->iName) {
                goto failure;
            }
            (void)strcpy(nif->iName, ptr->Description);
            ptr = ptr->Next;
        }
    }

    *aInterfaces = head;
    return 0;

failure:
    OsNetworkFreeInterfaces(head);
    return -1;
}

void OsNetworkFreeInterfaces(OsNetworkInterface* aInterfaces)
{
    OsNetworkInterface* tmp;
    while (aInterfaces != NULL) {
        tmp = aInterfaces;
        aInterfaces = aInterfaces->iNext;
        free(tmp->iName);
        free(tmp);
    }
}

DWORD interfaceChangeThread(LPVOID aArg)
{
    InterfaceChangeObserver* obs = (InterfaceChangeObserver*)aArg;
    while (obs->iShutdown == 0) {
        DWORD ret = WAIT_FAILED;
        DWORD bytes;
        if (SOCKET_ERROR == WSAIoctl(obs->iSocket, SIO_ADDRESS_LIST_CHANGE,
                                       NULL, 0, NULL, 0, &bytes, NULL, NULL)
            && WSAEWOULDBLOCK == WSAGetLastError()) {
            HANDLE handles[2];
            handles[0] = obs->iEvent;
            handles[1] = obs->iShutdownEvent;
            ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
        }
        if (WAIT_OBJECT_0 == ret) {
            (obs->iCallback)(obs->iArg);
            (void)WSAResetEvent(obs->iEvent);
        }
    }
    (void)ReleaseSemaphore(obs->iSem, 1, NULL);
    return 0;
}

void OsNetworkSetInterfaceChangedObserver(InterfaceListChanged aCallback, void* aArg)
{
    if (NULL != gInterfaceChangeObserver) {
        return;
    }

    gInterfaceChangeObserver = (InterfaceChangeObserver*)malloc(sizeof(*gInterfaceChangeObserver));
    if (NULL == gInterfaceChangeObserver) {
        return;
    }

    gInterfaceChangeObserver->iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    gInterfaceChangeObserver->iEvent = WSACreateEvent();
    gInterfaceChangeObserver->iShutdownEvent = WSACreateEvent();
    gInterfaceChangeObserver->iCallback = aCallback;
    gInterfaceChangeObserver->iArg = aArg;
    gInterfaceChangeObserver->iShutdown = 0;
    gInterfaceChangeObserver->iSem = CreateSemaphore(NULL, 0, INT32_MAX, NULL);
    (void)WSAEventSelect(gInterfaceChangeObserver->iSocket, gInterfaceChangeObserver->iEvent, FD_ADDRESS_LIST_CHANGE);
    (void)CreateThread(NULL, 16*1024, (LPTHREAD_START_ROUTINE)&interfaceChangeThread, gInterfaceChangeObserver, 0, NULL);
}

/**
 * Test function.  Restrict OsNetworkListInterfaces to just item aIndex from its normal list
 * Not advertised in Os.h and not guaranteed to be available on all platforms
 */
extern void OsNetworkSetTestInterfaceIndex(int32_t aIndex);
void OsNetworkSetTestInterfaceIndex(int32_t aIndex)
{
    gTestInterfaceIndex = aIndex;
    if (NULL != gInterfaceChangeObserver) {
        (void)WSASetEvent(gInterfaceChangeObserver->iEvent);
    }
}
