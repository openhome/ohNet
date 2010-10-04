// Implementation of Os.h APIs for Posix

#undef ATTEMPT_THREAD_PRIORITIES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <assert.h>
#ifdef ATTEMPT_THREAD_PRIORITIES
# include <sys/capability.h>
#endif
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <ifaddrs.h>

#include <C/Os.h>

#define kMinStackBytes (1024 * 512)
#define kThreadSchedPolicy (SCHED_RR)

static struct timeval gStartTime;
static THandle gMutex = kHandleNull;


int32_t OsCreate()
{
    gettimeofday(&gStartTime, NULL);
    gMutex = OsMutexCreate("DNSM");
    if (gMutex == kHandleNull)
        return -1;
    return 0;
}

void OsDestroy()
{
    OsMutexDestroy(gMutex);
    gMutex = kHandleNull;
}

void OsQuit()
{
    abort();
}

uint64_t OsTimeInUs()
{
    struct timeval now, diff;
    gettimeofday(&now, NULL);
    diff.tv_sec = now.tv_sec - gStartTime.tv_sec;
    if (now.tv_usec > gStartTime.tv_usec) {
        diff.tv_usec = now.tv_usec - gStartTime.tv_usec;
    }
    else {
        diff.tv_sec--;
        diff.tv_usec = 1000000 - gStartTime.tv_usec + now.tv_usec;
    }

    return (uint64_t)((diff.tv_sec * 1000000) + diff.tv_usec);
}

void OsConsoleWrite(const char* aStr)
{
    fprintf(stderr, "%s", aStr);
    fflush(stderr);
}

void OsGetPlatformNameAndVersion(char** aName, uint32_t* aMajor, uint32_t* aMinor)
{
	*aName = "Posix";
	*aMajor = _POSIX_VERSION;
	*aMinor = 0;
}

static void getAbsTimespec(struct timespec* aTime, uint32_t aMsecs)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    aTime->tv_sec = now.tv_sec + aMsecs/1000;
    aTime->tv_nsec = (now.tv_usec*1000) + ((aMsecs%1000)*1000000);
    if (aTime->tv_nsec >= 1000000000) {
        aTime->tv_sec++;
        aTime->tv_nsec -= 1000000000;
    }
}

typedef struct
{
    pthread_cond_t  iCond;
    pthread_mutex_t iLock;
    uint32_t        iValue;
} SemaphoreData;

THandle OsSemaphoreCreate(const char* aName, uint32_t aCount)
{
    SemaphoreData* data = (SemaphoreData*)calloc(1, sizeof(*data));
    if (data == NULL)
        return kHandleNull;
    int status = pthread_cond_init(&data->iCond, NULL);
    if (status != 0) {
        free(data);
        return kHandleNull;
    }
    status = pthread_mutex_init(&data->iLock, NULL);
    if (status != 0) {
        (void)pthread_cond_destroy(&data->iCond);
        free(data);
        return kHandleNull;
    }
    data->iValue = aCount;
    return (THandle)data;
}

void OsSemaphoreDestroy(THandle aSem)
{
    SemaphoreData* data = (SemaphoreData*)aSem;
    if (data == kHandleNull) {
        return;
    }
    (void)pthread_mutex_destroy(&data->iLock);
    (void)pthread_cond_destroy(&data->iCond);
    free(data);
}

int32_t OsSemaphoreWait(THandle aSem)
{
    SemaphoreData* data = (SemaphoreData*)aSem;
    int status = pthread_mutex_lock(&data->iLock);
    if (status != 0) {
        goto exit;
    }
    while (data->iValue == 0) {
        status = pthread_cond_wait(&data->iCond, &data->iLock);
        if (status != 0) {
            goto exit;
        }
    }
    data->iValue -= 1;
    status = pthread_mutex_unlock(&data->iLock);
exit:
    return status;
}

int32_t OsSemaphoreTimedWait(THandle aSem, uint32_t aTimeoutMs)
{
    SemaphoreData* data = (SemaphoreData*)aSem;
    int32_t timeout = 0;
    struct timespec timeToWait;
    getAbsTimespec(&timeToWait, aTimeoutMs);
    int status = pthread_mutex_lock(&data->iLock);
    if (status != 0) {
        goto exit;
    }
    while (data->iValue == 0 && timeout == 0 && status == 0) {
        status = pthread_cond_timedwait(&data->iCond, &data->iLock, &timeToWait);
        if (status==ETIMEDOUT) {
            timeout = 1;
            status = 0;
        }
    }
    if (timeout == 0 && status == 0) {
        data->iValue--;
    }
    status = status | pthread_mutex_unlock(&data->iLock);
exit:
    return (status!=0? -1 : (timeout==1? 0 : 1));
}

uint32_t OsSemaphoreClear(THandle aSem)
{
    uint32_t ret;
    SemaphoreData* data = (SemaphoreData*)aSem;
    pthread_mutex_lock(&data->iLock);
    ret = (data->iValue>0? 1 : 0);
    data->iValue = 0;
    pthread_mutex_unlock(&data->iLock);
    return ret;
}

int32_t OsSemaphoreSignal(THandle aSem)
{
    int status;
    SemaphoreData* data = (SemaphoreData*)aSem;
    pthread_mutex_lock(&data->iLock);
    data->iValue += 1;
    pthread_mutex_unlock(&data->iLock);
    status = pthread_cond_signal(&data->iCond);
    return (status==0? 0 : -1);
}

THandle OsMutexCreate(const char* aName)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    (void)pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_t* mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    if (mutex == NULL) {
        return kHandleNull;
    }
    int status = pthread_mutex_init(mutex, &attr);
    if (status != 0) {
        free(mutex);
        return kHandleNull;
    }
    return (THandle)mutex;
}

void OsMutexDestroy(THandle aMutex)
{
    if (aMutex == kHandleNull) {
        return;
    }
    pthread_mutex_t* mutex = (pthread_mutex_t*)aMutex;
    (void)pthread_mutex_destroy(mutex);
    free(mutex);
}

int32_t OsMutexLock(THandle aMutex)
{
    int status = pthread_mutex_lock((pthread_mutex_t*)aMutex);
    return (status==0? 0 : -1);
}

int32_t OsMutexUnlock(THandle aMutex)
{
    int status = pthread_mutex_unlock((pthread_mutex_t*)aMutex);
    return (status==0? 0 : -1);
}

typedef struct
{
    pthread_t        iThread;
    ThreadEntryPoint iEntryPoint;
    void*            iArg;
    uint32_t         iPriority;
} ThreadData;

__thread void* tlsThreadArg;

static void* threadEntrypoint(void* aArg)
{
    int oldState;
    int status;
    ThreadData* data = (ThreadData*)aArg;
    assert(data != NULL);

#ifdef ATTEMPT_THREAD_PRIORITIES
    {
        TInt platMin = sched_get_priority_min(kThreadSchedPolicy);
        TInt platMax = sched_get_priority_max(kThreadSchedPolicy);
        // convert the UPnP library's 50 - 150 priority range into
        // an equivalent posix priority
        // ...calculate priority as percentage of library range
        int32_t percent = (((int32_t )data->iPriority - 50) * 100) / (150 - 50);
        // ...calculate native priority as 'percent' through the dest range
        int32_t priority = platMin + ((percent * (platMax - platMin))/100);
        sched_param param;
        param.sched_priority = priority;
        int status = pthread_setschedparam(data->iThread, kThreadSchedPolicy, &param);
        assert(status == 0);
    }
#endif // ATTEMPT_THREAD_PRIORITIES

    // Disable cancellation - we're in a C++ environment, and
    // don't want to rely on pthreads to mess things up for us.
    status = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldState);
    assert(status == 0);

    tlsThreadArg = data->iArg;
    data->iEntryPoint(data->iArg);

    return NULL;
}

THandle OsThreadCreate(const char* aName, uint32_t aPriority, uint32_t aStackBytes, ThreadEntryPoint aEntryPoint, void* aArg)
{
    ThreadData* data = (ThreadData*)calloc(1, sizeof(ThreadData));
    if (data == NULL) {
        return kHandleNull;
    }
    if (aStackBytes < kMinStackBytes)
        aStackBytes = kMinStackBytes;
    data->iEntryPoint = aEntryPoint;
    data->iArg        = aArg;
    data->iPriority   = aPriority;

    pthread_attr_t attr;
    (void)pthread_attr_init(&attr);
    (void)pthread_attr_setstacksize(&attr, aStackBytes);
    (void)pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
    (void)pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    int status = pthread_create(&data->iThread, &attr, threadEntrypoint, data);
    if (status != 0) {
        free(data);
        return kHandleNull;
    }
    (void)pthread_attr_destroy(&attr);
    return (THandle)data;
}

void* OsThreadTls()
{
    return tlsThreadArg;
}

void OsThreadDestroy(THandle aThread)
{
    // no call to pthread_exit as it will have been implicitly called when the thread exited
    free((ThreadData*)aThread);
}

int32_t OsThreadSupportsPriorities()
{
#ifdef ATTEMPT_THREAD_PRIORITIES
    return 1;
#else
    return 0;
#endif
}

typedef struct OsNetworkHandle
{
    int32_t iSocket;
    int32_t iPipe[2];
    int32_t iInterrupted;
}OsNetworkHandle;

static int nfds(const OsNetworkHandle* aHandle)
{
    int nfds = aHandle->iPipe[1];
    if (aHandle->iPipe[0] > nfds) {
        nfds = aHandle->iPipe[0];
    }
    if (aHandle->iSocket > nfds) {
        nfds = aHandle->iSocket;
    }
    return nfds+1;
}

static void SetFdBlocking(int32_t aSocket)
{
    uint32_t state = fcntl(aSocket, F_GETFL, 0);
    state &= ~O_NONBLOCK;
    fcntl(aSocket, F_SETFL, state);
}

static void SetFdNonBlocking(int32_t aSocket)
{
    uint32_t state = fcntl(aSocket, F_GETFL, 0);
    state |= O_NONBLOCK;
    fcntl(aSocket, F_SETFL, state);
}

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
    aAddr->sin_family = 2;
    aAddr->sin_port = SwapEndian16(aPort);
    aAddr->sin_addr.s_addr = aAddress;
}

static OsNetworkHandle* CreateHandle(int32_t aSocket)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)malloc(sizeof(OsNetworkHandle));
    if (handle == NULL) {
        return kHandleNull;
    }
    if (pipe(handle->iPipe) == -1) {
        free(handle);
        return kHandleNull;
    }
    SetFdNonBlocking(handle->iPipe[0]);
    handle->iSocket = aSocket;
    assert(aSocket >= 0 && aSocket < __FD_SETSIZE);
    handle->iInterrupted = 0;

    return handle;
}

THandle OsNetworkCreate(OsNetworkSocketType aSocketType)
{
    int32_t socketH = socket(2, aSocketType, 0);
    OsNetworkHandle* handle = CreateHandle(socketH);
    if (handle == kHandleNull) {
        close(socketH);
    }
    return (THandle)handle;
}

int32_t OsNetworkBind(THandle aHandle, TIpAddress aAddress, uint16_t* aPort)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    struct sockaddr_in addr;
    sockaddrFromEndpoint(&addr, aAddress, *aPort);
    int err = bind(handle->iSocket, (struct sockaddr*)&addr, sizeof(addr));
    if (err == 0) {
        socklen_t len = sizeof(addr);
        if (0 != getsockname(handle->iSocket, (struct sockaddr*)&addr, &len)) {
            err = -1;
            }
        else {
            *aPort = SwapEndian16(addr.sin_port);
        }
    }
    return err;
}

int32_t OsNetworkConnect(THandle aHandle, TIpAddress aAddress, uint16_t aPort, uint32_t aTimeoutMs)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    int32_t err = -1;

    SetFdNonBlocking(handle->iSocket);

    struct sockaddr_in addr;
    sockaddrFromEndpoint(&addr, aAddress, aPort);
    /* ignore err as we expect this to fail due to EINPROGRESS */
    (void)connect(handle->iSocket, (struct sockaddr*)&addr, sizeof(addr));

    fd_set read;
    FD_ZERO(&read);
    FD_SET(handle->iPipe[0], &read);
    fd_set write;
    FD_ZERO(&write);
    FD_SET(handle->iSocket, &write);
    fd_set error;
    FD_ZERO(&error);
    FD_SET(handle->iSocket, &error);

    struct timeval tv;
    tv.tv_sec = aTimeoutMs / 1000;
    tv.tv_usec = (aTimeoutMs % 1000) * 1000;

    if (select(nfds(handle), &read, &write, &error, &tv) > 0 && FD_ISSET(handle->iSocket, &write)) {
        err = 0;
    }
    SetFdBlocking(handle->iSocket);
    return err;
}

int32_t OsNetworkSend(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    int32_t sent = send(handle->iSocket, aBuffer, aBytes, 0);
    return sent;
}

int32_t OsNetworkSendTo(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes, TIpAddress aAddress, uint16_t aPort)
{
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
        fprintf(stdout, "OsNetworkSendTo, sending\n%s\n", buf);
    }
#endif
    struct sockaddr_in addr;
    sockaddrFromEndpoint(&addr, aAddress, aPort);
    int32_t sent = sendto(handle->iSocket, aBuffer, aBytes, 0, (struct sockaddr*)&addr, sizeof(addr));
    return sent;
}

int32_t OsNetworkReceive(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    SetFdNonBlocking(handle->iSocket);

    fd_set read;
    FD_ZERO(&read);
    FD_SET(handle->iPipe[0], &read);
    FD_SET(handle->iSocket, &read);
    fd_set error;
    FD_ZERO(&error);
    FD_SET(handle->iSocket, &error);

    int32_t received = recv(handle->iSocket, aBuffer, aBytes, 0);
    if (received==-1 && errno==EWOULDBLOCK) {
        if (select(nfds(handle), &read, NULL, &error, NULL) > 0 &&
            FD_ISSET(handle->iSocket, &read)) {
            received = recv(handle->iSocket, aBuffer, aBytes, 0);
        }
    }

    SetFdBlocking(handle->iSocket);
    return received;
}

int32_t OsNetworkReceiveFrom(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes, TIpAddress* aAddress, uint16_t* aPort)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    struct sockaddr_in addr;
    sockaddrFromEndpoint(&addr, 0, 0);
    socklen_t addrLen = sizeof(addr);

    SetFdNonBlocking(handle->iSocket);

    fd_set read;
    FD_ZERO(&read);
    FD_SET(handle->iPipe[0], &read);
    FD_SET(handle->iSocket, &read);
    fd_set error;
    FD_ZERO(&error);
    FD_SET(handle->iSocket, &error);

    int32_t received = recvfrom(handle->iSocket, aBuffer, aBytes, 0, (struct sockaddr*)&addr, &addrLen);
    if (received==-1 && errno==EWOULDBLOCK) {
        if (select(nfds(handle), &read, NULL, &error, NULL) > 0 &&
            FD_ISSET(handle->iSocket, &read)) {
            received = recvfrom(handle->iSocket, aBuffer, aBytes, 0, (struct sockaddr*)&addr, &addrLen);
        }
    }
    SetFdBlocking(handle->iSocket);
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
    int32_t val = 1;
    if (aInterrupt != 0) {
        if (write(handle->iPipe[1], &val, sizeof(val)) == -1) {
            err = -1;
        }
    }
    else {
        while (read(handle->iPipe[0], &val, sizeof(val)) > 0) {
            ;
        }
    }
    OsMutexUnlock(gMutex);
    return err;
}

int32_t OsNetworkClose(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = 0;
    if (handle != NULL) {
        err = close(handle->iSocket);
        err |= close(handle->iPipe[0]);
        err |= close(handle->iPipe[1]);
        free(handle);
    }
    return err;
}

int32_t OsNetworkListen(THandle aHandle, uint32_t aSlots)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    int32_t err = listen(handle->iSocket, aSlots);
    return err;
}

THandle OsNetworkAccept(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return kHandleNull;
    }
    struct sockaddr_in addr;
    sockaddrFromEndpoint(&addr, 0, 0);
    socklen_t len = sizeof(addr);

    SetFdNonBlocking(handle->iSocket);

    fd_set read;
    FD_ZERO(&read);
    FD_SET(handle->iPipe[0], &read);
    FD_SET(handle->iSocket, &read);
    fd_set error;
    FD_ZERO(&error);
    FD_SET(handle->iSocket, &error);

    int32_t h = accept(handle->iSocket, (struct sockaddr*)&addr, &len);
    if (h==-1 && errno==EWOULDBLOCK) {
        if (select(nfds(handle), &read, NULL, &error, NULL) > 0 &&
            FD_ISSET(handle->iSocket, &read)) {
            h = accept(handle->iSocket, (struct sockaddr*)&addr, &len);
        }
    }
    SetFdBlocking(handle->iSocket);
    if (h == -1) {
        return kHandleNull;
    }

    OsNetworkHandle* newHandle = CreateHandle(h);
    if (newHandle == NULL) {
        close(h);
        return kHandleNull;
    }

    return (THandle)newHandle;
}

int32_t OsNetworkGetHostByName(const char* aAddress, TIpAddress* aHost)
{
    int32_t ret = 0;
    (void)OsMutexLock(gMutex);
    struct hostent* dns = gethostbyname(aAddress);
    if (dns == NULL) {
        ret = -1;
    }
    else {
        *aHost = *((uint32_t*)(dns->h_addr_list[0]));
    }
    (void)OsMutexUnlock(gMutex);

    return ret;
}

int32_t OsNetworkSocketSetSendBufBytes(THandle aHandle, uint32_t aBytes)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_SNDBUF, &aBytes, sizeof(aBytes));
    return err;
}

int32_t OsNetworkSocketSetReceiveTimeout(THandle aHandle, uint32_t aMilliSeconds)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct timeval tv;
    tv.tv_sec = aMilliSeconds/1000;
    tv.tv_usec = (aMilliSeconds%1000)*1000;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    return err;
}

int32_t OsNetworkTcpSetNoDelay(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    uint32_t nodelay = 1;
    int32_t err = setsockopt(handle->iSocket, IPPROTO_TCP, TCP_NODELAY, &nodelay, sizeof(nodelay));
    return err;
}

int32_t OsNetworkSocketSetReuseAddress(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t reuseaddr = 1;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
    return err;
}

int32_t OsNetworkSocketSetMulticastTtl(THandle aHandle, uint8_t aTtl)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    uint8_t err = setsockopt(handle->iSocket, IPPROTO_IP, IP_MULTICAST_TTL, &aTtl, sizeof(aTtl));
    return err;
}

int32_t OsNetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aAddress, TIpAddress aInterface)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = aAddress;
    mreq.imr_interface.s_addr = aInterface;
    int32_t err = setsockopt(handle->iSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    return err;
}

int32_t OsNetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aAddress, TIpAddress aInterface)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = aAddress;
    mreq.imr_interface.s_addr = aInterface;
    int32_t err = setsockopt(handle->iSocket, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    return err;
}

int32_t OsNetworkListInterfaces(OsNetworkInterface** aInterfaces)
{
#define MakeIpAddress(aByte1, aByte2, aByte3, aByte4) \
        (aByte1 | (aByte2<<8) | (aByte3<<16) | (aByte4<<24))

    int32_t ret = -1;
    struct ifaddrs* networkIf;
    struct ifaddrs* iter;
    int32_t includeLoopback = 1;
    *aInterfaces = NULL;
    if (getifaddrs(&networkIf) == -1) {
        return -1;
    }
    TIpAddress loopbackAddr = MakeIpAddress(127, 0, 0, 1);
    /* first check whether we have any suitable interfaces other than loopback*/
    iter = networkIf;
    while (iter != NULL) {
        if (iter->ifa_addr->sa_family == AF_INET &&
            ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr != loopbackAddr) {
            includeLoopback = 0;
            break;
        }
        iter = iter->ifa_next;
    }
    /* ...then allocate/populate the list */
    iter = networkIf;
    OsNetworkInterface* head = NULL;
    OsNetworkInterface* tail = NULL;
    while (iter != NULL) {
        if (iter->ifa_addr->sa_family == AF_INET && (includeLoopback ||
            ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr != loopbackAddr)) {
            OsNetworkInterface* iface = (OsNetworkInterface*)calloc(1, sizeof(*iface));
            if (iface == NULL) {
                OsNetworkFreeInterfaces(head);
                goto exit;
            }
            if (head == NULL) {
                head = iface;
            }
            iface->iName = (char*)malloc(strlen(iter->ifa_name) + 1);
            if (iface->iName == NULL) {
                OsNetworkFreeInterfaces(head);
                goto exit;
            }
            (void)strcpy(iface->iName, iter->ifa_name);
            iface->iAddress = ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr;
            iface->iNetMask = ((struct sockaddr_in*)iter->ifa_netmask)->sin_addr.s_addr;
            if (tail != NULL) {
                tail->iNext = iface;
            }
            tail = iface;
        }
        iter = iter->ifa_next;
    }
    ret = 0;
    *aInterfaces = head;
exit:
    freeifaddrs(networkIf);
    return ret;
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

void OsNetworkSetInterfaceChangedObserver(InterfaceListChanged aCallback, void* aArg)
{
    // not supported yet
}
