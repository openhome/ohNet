// Implementation of Os.h APIs for Windows

#include <OpenHome/Os.h>

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

    char* noErrDlgs = getenv("OHNET_NO_ERROR_DIALOGS");
    if (noErrDlgs != NULL && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }

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
        free(gInterfaceChangeObserver);
        gInterfaceChangeObserver = NULL;
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

void OsBreakpoint()
{
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
    SOCKET socketH = socket(AF_INET, aSocketType, 0);
    OsNetworkHandle* handle = CreateHandle(socketH);
    return (THandle)handle;
}

int32_t OsNetworkBind(THandle aHandle, TIpAddress aAddress, uint32_t aPort)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct sockaddr_in addr;
    uint16_t port = (uint16_t)aPort;
    sockaddrFromEndpoint(&addr, aAddress, port);
    err = bind(handle->iSocket, (struct sockaddr*)&addr, sizeof(addr));
    return err;
}

int32_t OsNetworkPort(THandle aHandle, uint32_t* aPort)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    err = getsockname(handle->iSocket, (struct sockaddr*)&addr, &len);
    
    if (err == 0) {
        uint16_t port = SwapEndian16(addr.sin_port);
        *aPort = port;
    }
    return err;
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
    int32_t sent = 0;
    int32_t bytes = 0;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        fprintf(stdout, "--OsNetworkSend: error, SocketInterrupted\n");
        return -1;
    }
    do {
        bytes = send(handle->iSocket, (const char*)aBuffer, aBytes, 0);
        if (bytes != -1) {
            sent += bytes;
        }
        else {
            fprintf(stdout, "--OsNetworkSend: error from send - %d\n", WSAGetLastError());
        }
    } while(bytes != -1 && sent < (int32_t)aBytes);
    if (sent < (int32_t)aBytes) {
        fprintf(stdout, "--OsNetworkSend: error sent %d of %u bytes; last error was %d\n", sent, aBytes, WSAGetLastError());
    }
    return sent;
}

int32_t OsNetworkSendTo(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes, TIpAddress aAddress, uint16_t aPort)
{
    int32_t sent = 0;
    int32_t bytes = 0;
    struct sockaddr_in addr;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    sockaddrFromEndpoint(&addr, aAddress, aPort);
    do {
        bytes = sendto(handle->iSocket, (const char*)aBuffer, aBytes, 0, (struct sockaddr*)&addr, sizeof(addr));
        if (bytes != -1) {
            sent += bytes;
        }
    } while(bytes != -1 && sent < (int32_t)aBytes);    
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

int32_t OsNetworkSocketSetRecvBufBytes(THandle aHandle, uint32_t aBytes)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&aBytes, sizeof(aBytes));
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

int32_t OsNetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    int32_t err;
    char loop;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = aAddress;
    mreq.imr_interface.s_addr = aInterface;
    err = setsockopt(handle->iSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));

    if (err != 0) {
        return err;
    }
    
    loop = 1;
    err = setsockopt(handle->iSocket, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
    
    return err;
}

int32_t OsNetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = aAddress;
    mreq.imr_interface.s_addr = aInterface;
    err = setsockopt(handle->iSocket, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));
    return err;
}

int32_t OsNetworkListAdapters(OsNetworkAdapter** aInterfaces, uint32_t aUseLoopback)
{
#define MakeIpAddress(aByte1, aByte2, aByte3, aByte4) \
        (aByte1 | (aByte2<<8) | (aByte3<<16) | (aByte4<<24))

    MIB_IFTABLE* ifTable          = NULL;
    MIB_IPADDRTABLE* addrTable    = NULL;
    ULONG bytes                   = 0;
    OsNetworkAdapter* head      = NULL;
    int32_t index                 = 0;
    const TIpAddress loopbackAddr = MakeIpAddress(127, 0, 0, 1);
    int32_t includeLoopback       = 1;
    uint32_t i;

    if (ERROR_INSUFFICIENT_BUFFER != GetIpAddrTable(NULL, &bytes, FALSE)) {
        return -1;
    }
    addrTable = (MIB_IPADDRTABLE*)malloc(bytes);
    if (NO_ERROR != GetIpAddrTable(addrTable, &bytes, FALSE)) {
        goto failure;
    }
    bytes = 0;
    if (ERROR_INSUFFICIENT_BUFFER != GetIfTable(NULL, &bytes, FALSE)) {
        goto failure;
    }
    ifTable = (MIB_IFTABLE*)malloc(bytes);
    if (NO_ERROR != GetIfTable(ifTable, &bytes, FALSE)) {
        goto failure;
    }

    if (aUseLoopback == 0) {
        // Only include loopback if there are no non-loopback adapters
        for (i=0; i<addrTable->dwNumEntries; i++) {
            MIB_IPADDRROW* addrRow = &(addrTable->table[i]);
            if (addrRow->dwAddr != loopbackAddr) {
                includeLoopback = 0;
                break;
            }
        }
    }

    for (i=0; i<addrTable->dwNumEntries; i++) {
        MIB_IPADDRROW* addrRow = &(addrTable->table[i]);
        MIB_IFROW* ifRow = NULL;
        OsNetworkAdapter* nif;
        size_t len;
		DWORD j = 0;

		for (; j< ifTable->dwNumEntries; j++) {
			MIB_IFROW* tmp = &ifTable->table[j];
			if (tmp->dwIndex == addrRow->dwIndex) {
				ifRow = tmp;
				break;
			}
		}
		if (ifRow == NULL) {
			fprintf(stderr, "Unable to match ifRow to addrRow\n");
			continue;
		}

        if ((addrRow->dwAddr == loopbackAddr && !includeLoopback) ||
            (addrRow->dwAddr != loopbackAddr && aUseLoopback)) {
            continue;
        }
        if (-1 != gTestInterfaceIndex && index++ != gTestInterfaceIndex) {
            continue;
        }
        if (addrRow->dwAddr == 0 || addrRow->dwMask == 0) {
            continue;
        }

        nif = (OsNetworkAdapter*)calloc(1, sizeof(*nif));
        if (nif == NULL) {
            goto failure;
        }
        nif->iReserved = ifRow->dwType;
        nif->iAddress = addrRow->dwAddr;
        nif->iNetMask = addrRow->dwMask;
        len = ifRow->dwDescrLen;
        nif->iName = (char*)malloc(len+1);
        if (NULL == nif->iName) {
            free(nif);
            goto failure;
        }
        for (j=0; j<len; j++) {
            nif->iName[j] = (char)ifRow->bDescr[j];
        }
        nif->iName[len] = '\0';

        if (head == NULL) {
            head = nif;
        }
        else {
            TIpAddress subnet = (nif->iAddress & nif->iNetMask);
            OsNetworkAdapter* p1 = head;
            OsNetworkAdapter* prev = NULL;
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
    }

    free(addrTable);
    free(ifTable);
    *aInterfaces = head;
    return 0;

failure:
    free(addrTable);
    free(ifTable);
    OsNetworkFreeInterfaces(head);
    return -1;
}

void OsNetworkFreeInterfaces(OsNetworkAdapter* aInterfaces)
{
    OsNetworkAdapter* tmp;
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
 * Test function.  Restrict OsNetworkListAdapters to just item aIndex from its normal list
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
