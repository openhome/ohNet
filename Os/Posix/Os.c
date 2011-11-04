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
#include <signal.h>

#ifdef PLATFORM_MACOSX_GNU
#include <SystemConfiguration/SystemConfiguration.h>
#include <execinfo.h>
#endif

#include <OpenHome/Os.h>

#define kMinStackBytes (1024 * 512)
#define kThreadSchedPolicy (SCHED_RR)

#ifdef PLATFORM_MACOSX_GNU
# define TEMP_FAILURE_RETRY(expression) \
(__extension__ \
({ long int __result; \
do __result = (long int) (expression); \
while (__result == -1L && errno == EINTR); \
__result; }))
# define MAX_FILE_DESCRIPTOR FD_SETSIZE
#else
# define MAX_FILE_DESCRIPTOR __FD_SETSIZE
#endif



#ifdef PLATFORM_MACOSX_GNU

typedef struct InterfaceChangedObserver
{
    InterfaceListChanged iCallback;
    void* iArg;
    SCDynamicStoreRef iStore;
    CFRunLoopSourceRef iRunLoopSource;

} InterfaceChangedObserver;

static InterfaceChangedObserver* gInterfaceChangedObserver = NULL;

#endif /* PLATFOTM_MACOSX_GNU */



static struct timeval gStartTime;
static THandle gMutex = kHandleNull;
static pthread_key_t gThreadArgKey;

int32_t OsCreate()
{
    int errnum;
    gettimeofday(&gStartTime, NULL);
    gMutex = OsMutexCreate("DNSM");
    if (gMutex == kHandleNull)
        return -1;
    errnum = pthread_key_create(&gThreadArgKey, NULL);
    if (errnum != 0)
    {
        OsMutexDestroy(gMutex);
        gMutex = kHandleNull;
        return -1;
    }
    return 0;
}

void OsDestroy()
{
    pthread_key_delete(gThreadArgKey);
    OsMutexDestroy(gMutex);
    gMutex = kHandleNull;

#ifdef PLATFORM_MACOSX_GNU
    if (NULL != gInterfaceChangedObserver)
    {
        CFRunLoopRef runLoop = CFRunLoopGetMain();
        CFRunLoopRemoveSource(runLoop, gInterfaceChangedObserver->iRunLoopSource, kCFRunLoopCommonModes);
        CFRelease(gInterfaceChangedObserver->iStore);
        CFRelease(gInterfaceChangedObserver->iRunLoopSource);
        free(gInterfaceChangedObserver);
        gInterfaceChangedObserver = NULL;
    }
#endif /* PLATFOTM_MACOSX_GNU */
}

void OsQuit()
{
    abort();
}

void OsBreakpoint()
{
    raise(SIGTRAP);
}


#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
#define STACK_TRACE_MAX_DEPTH 64
typedef struct OsStackTrace
{
    void* iStack[STACK_TRACE_MAX_DEPTH];
    int iCount;
    char** iSymbols;
    
} OsStackTrace;
#endif /* defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS) */


THandle OsStackTraceInitialise()
{
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
    OsStackTrace* stackTrace = (OsStackTrace*)malloc(sizeof(OsStackTrace));
    if (stackTrace == NULL) {
        return kHandleNull;
    }

    stackTrace->iCount = backtrace(stackTrace->iStack, STACK_TRACE_MAX_DEPTH);
    stackTrace->iSymbols = NULL;
    return stackTrace;
#else
    return kHandleNull;
#endif /* defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS) */
}

THandle OsStackTraceCopy(THandle aStackTrace)
{
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    OsStackTrace* copy = NULL;
    if (stackTrace == NULL) {
        return kHandleNull;
    }

    copy = (OsStackTrace*)malloc(sizeof(OsStackTrace));
    if (copy == NULL) {
        return kHandleNull;
    }

    memcpy(copy, stackTrace, sizeof(OsStackTrace));
    copy->iSymbols = NULL;
    return copy;
#else
    aStackTrace = aStackTrace;
    return kHandleNull;
#endif /* defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS) */
}

uint32_t OsStackTraceNumEntries(THandle aStackTrace)
{
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    if (stackTrace == kHandleNull) {
        return 0;
    }

    return stackTrace->iCount;
#else
    aStackTrace = aStackTrace;
    return 0;
#endif /* defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS) */
}

const char* OsStackTraceEntry(THandle aStackTrace, uint32_t aIndex)
{
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    if (stackTrace == kHandleNull) {
        return NULL;
    }

    if (stackTrace->iSymbols == NULL) {
        stackTrace->iSymbols = backtrace_symbols(stackTrace->iStack, stackTrace->iCount);
    }

    if (stackTrace->iSymbols != NULL && aIndex < stackTrace->iCount) {
        return stackTrace->iSymbols[aIndex];
    }
    else {
        return NULL;
    }
#else
    aStackTrace = aStackTrace;
    aIndex = aIndex;
    return NULL;
#endif /* defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS) */
}

void OsStackTraceFinalise(THandle aStackTrace)
{
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    if (stackTrace != kHandleNull) {
        if (stackTrace->iSymbols != NULL) {
            free(stackTrace->iSymbols);
        }
        free(stackTrace);
    }
#else
    aStackTrace = aStackTrace;
#endif /* defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS) */
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
    (void)TEMP_FAILURE_RETRY(pthread_cond_destroy(&data->iCond));
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
        status = TEMP_FAILURE_RETRY(pthread_cond_timedwait(&data->iCond, &data->iLock, &timeToWait));
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
    if (status == 0)
        return 0;
    else if (status == EDEADLK)
        return -1;
    return -2;
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

/* __thread void* tlsThreadArg; */

static void* threadEntrypoint(void* aArg)
{
#ifndef __ANDROID__
    int oldState;
    int status;
#endif
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
#ifndef __ANDROID__
    status = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldState);
    assert(status == 0);
#endif

    //tlsThreadArg = data->iArg;
    pthread_setspecific(gThreadArgKey, data->iArg);
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
#ifndef __ANDROID__
    (void)pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
#endif
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
    return pthread_getspecific(gThreadArgKey);
    //return tlsThreadArg;
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
    assert(aSocket >= 0 && aSocket < MAX_FILE_DESCRIPTOR);
    handle->iInterrupted = 0;

    return handle;
}

THandle OsNetworkCreate(OsNetworkSocketType aSocketType)
{
    int32_t socketH = socket(2, aSocketType, 0);
    OsNetworkHandle* handle = CreateHandle(socketH);
    if (handle == kHandleNull) {
        TEMP_FAILURE_RETRY(close(socketH));
    }
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
    if (err == -1 && errno == EADDRINUSE) {
        err = -2;
    }
    return err;
}

int32_t OsNetworkBindMulticast(THandle aHandle, TIpAddress aAdapter, TIpAddress aMulticast, uint32_t aPort)
{
    return OsNetworkBind(aHandle, aMulticast, aPort);
}

int32_t OsNetworkPort(THandle aHandle, uint32_t* aPort)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
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

    int32_t selectErr = TEMP_FAILURE_RETRY(select(nfds(handle), &read, &write, &error, &tv));
    if (selectErr > 0 && FD_ISSET(handle->iSocket, &write)) {
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

    int32_t sent = 0;
    int32_t bytes = 0;
    do {
        bytes = TEMP_FAILURE_RETRY(send(handle->iSocket, &aBuffer[sent], aBytes-sent, 0));
        if (bytes != -1) {
            sent += bytes;
        }
    } while(bytes != -1 && sent < aBytes);    
    return sent;
}

int32_t OsNetworkSendTo(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes, TIpAddress aAddress, uint16_t aPort)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    struct sockaddr_in addr;
    sockaddrFromEndpoint(&addr, aAddress, aPort);
    int32_t sent = 0;
    int32_t bytes = 0;
    do {
        bytes = TEMP_FAILURE_RETRY(sendto(handle->iSocket, &aBuffer[sent], aBytes-sent, 0, (struct sockaddr*)&addr, sizeof(addr)));
        if (bytes != -1) {
            sent += bytes;
        }
    } while(bytes != -1 && sent < aBytes);    
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

    int32_t received = TEMP_FAILURE_RETRY(recv(handle->iSocket, aBuffer, aBytes, 0));
    if (received==-1 && errno==EWOULDBLOCK) {
        int32_t selectErr = TEMP_FAILURE_RETRY(select(nfds(handle), &read, NULL, &error, NULL));
        if (selectErr > 0 && FD_ISSET(handle->iSocket, &read)) {
            received = TEMP_FAILURE_RETRY(recv(handle->iSocket, aBuffer, aBytes, 0));
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

    int32_t received = TEMP_FAILURE_RETRY(recvfrom(handle->iSocket, aBuffer, aBytes, 0, (struct sockaddr*)&addr, &addrLen));
    if (received==-1 && errno==EWOULDBLOCK) {
        int32_t selectErr = TEMP_FAILURE_RETRY(select(nfds(handle), &read, NULL, &error, NULL));
        if (selectErr > 0 && FD_ISSET(handle->iSocket, &read)) {
            received = TEMP_FAILURE_RETRY(recvfrom(handle->iSocket, aBuffer, aBytes, 0, (struct sockaddr*)&addr, &addrLen));
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
        while (TEMP_FAILURE_RETRY(read(handle->iPipe[0], &val, sizeof(val))) > 0) {
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
        err  = TEMP_FAILURE_RETRY(close(handle->iSocket));
        err |= TEMP_FAILURE_RETRY(close(handle->iPipe[0]));
        err |= TEMP_FAILURE_RETRY(close(handle->iPipe[1]));
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

    int32_t h = TEMP_FAILURE_RETRY(accept(handle->iSocket, (struct sockaddr*)&addr, &len));
    if (h==-1 && errno==EWOULDBLOCK) {
        int32_t selectErr = TEMP_FAILURE_RETRY(select(nfds(handle), &read, NULL, &error, NULL));
        if (selectErr > 0 && FD_ISSET(handle->iSocket, &read)) {
            h = TEMP_FAILURE_RETRY(accept(handle->iSocket, (struct sockaddr*)&addr, &len));
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
    struct addrinfo *res;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    if (0 != getaddrinfo(aAddress, NULL, &hints, &res)) {
        ret = -1;
        *aHost = 0;
    }
    else {
        struct sockaddr_in* s = (struct sockaddr_in*)res->ai_addr;
        *aHost = s->sin_addr.s_addr;
        freeaddrinfo(res);
    }    
    return ret;
}

int32_t OsNetworkSocketSetSendBufBytes(THandle aHandle, uint32_t aBytes)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_SNDBUF, &aBytes, sizeof(aBytes));
    return err;
}

int32_t OsNetworkSocketSetRecvBufBytes(THandle aHandle, uint32_t aBytes)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_RCVBUF, &aBytes, sizeof(aBytes));
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
#ifdef PLATFORM_MACOSX_GNU
    if (err == 0) {
        err = setsockopt(handle->iSocket, SOL_SOCKET, SO_REUSEPORT, &reuseaddr, sizeof(reuseaddr));
    }
#endif /* PLATFOTM_MACOSX_GNU */
    return err;
}

int32_t OsNetworkSocketSetMulticastTtl(THandle aHandle, uint8_t aTtl)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    uint8_t err = setsockopt(handle->iSocket, IPPROTO_IP, IP_MULTICAST_TTL, &aTtl, sizeof(aTtl));
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
    
    loop = 0;
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
    err = setsockopt(handle->iSocket, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    return err;
}

int32_t OsNetworkListAdapters(OsNetworkAdapter** aAdapters, uint32_t aUseLoopback)
{
#define MakeIpAddress(aByte1, aByte2, aByte3, aByte4) \
        (aByte1 | (aByte2<<8) | (aByte3<<16) | (aByte4<<24))

    int32_t ret = -1;
    struct ifaddrs* networkIf;
    struct ifaddrs* iter;
    int32_t includeLoopback = 1;
#ifdef PLATFORM_MACOSX_GNU
    aUseLoopback = 0;
#endif
    *aAdapters = NULL;
    if (TEMP_FAILURE_RETRY(getifaddrs(&networkIf)) == -1) {
        return -1;
    }
    TIpAddress loopbackAddr = MakeIpAddress(127, 0, 0, 1);
    /* first check whether we have any suitable interfaces other than loopback */
    if (aUseLoopback == 0) {
        iter = networkIf;
        while (iter != NULL) {
            if (iter->ifa_addr != NULL &&
                iter->ifa_addr->sa_family == AF_INET &&
                ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr != loopbackAddr) {
                includeLoopback = 0;
                break;
            }
            iter = iter->ifa_next;
        }
    }
    /* ...then allocate/populate the list */
    iter = networkIf;
    OsNetworkAdapter* head = NULL;
    OsNetworkAdapter* tail = NULL;
    while (iter != NULL) {
        if (iter->ifa_addr == NULL || iter->ifa_addr->sa_family != AF_INET ||
            (includeLoopback == 0 && ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr == loopbackAddr) ||
            (aUseLoopback == 1 && ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr != loopbackAddr)) {
            iter = iter->ifa_next;
            continue;
        }

        OsNetworkAdapter* iface = (OsNetworkAdapter*)calloc(1, sizeof(*iface));
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
        iter = iter->ifa_next;
    }
    ret = 0;
    *aAdapters = head;
exit:
    freeifaddrs(networkIf);
    return ret;
}

void OsNetworkFreeInterfaces(OsNetworkAdapter* aAdapters)
{
    OsNetworkAdapter* tmp;
    while (aAdapters != NULL) {
        tmp = aAdapters;
        aAdapters = aAdapters->iNext;
        free(tmp->iName);
        free(tmp);
    }
}


#ifdef PLATFORM_MACOSX_GNU

static void InterfaceChangedDynamicStoreCallback(SCDynamicStoreRef aStore, CFArrayRef aChangedKeys, void* aInfo)
{
    if (aInfo != NULL)
    {
        InterfaceChangedObserver* obs = (InterfaceChangedObserver*)aInfo;
        obs->iCallback(obs->iArg);
    }
}

#endif /* PLATFOTM_MACOSX_GNU */


void OsNetworkSetInterfaceChangedObserver(InterfaceListChanged aCallback, void* aArg)
{
    // not supported yet on anything other than Mac OS X

#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)

    SCDynamicStoreContext context = {0, NULL, NULL, NULL, NULL};
    CFStringRef pattern = NULL;
    CFArrayRef patternList = NULL;
    CFRunLoopRef runLoop = NULL;

    if (NULL != gInterfaceChangedObserver) {
        return;
    }

    gInterfaceChangedObserver = (InterfaceChangedObserver*)malloc(sizeof(*gInterfaceChangedObserver));
    if (NULL == gInterfaceChangedObserver) {
        goto Error;
    }

    gInterfaceChangedObserver->iCallback = aCallback;
    gInterfaceChangedObserver->iArg = aArg;
    gInterfaceChangedObserver->iStore = NULL;
    gInterfaceChangedObserver->iRunLoopSource = NULL;

    context.info = gInterfaceChangedObserver;

    gInterfaceChangedObserver->iStore = SCDynamicStoreCreate(NULL, CFSTR("AddIPAddressListChangeCallbackSCF"), &InterfaceChangedDynamicStoreCallback, &context);
    if (NULL == gInterfaceChangedObserver->iStore) {
        goto Error;
    }

    pattern = SCDynamicStoreKeyCreateNetworkServiceEntity(NULL, kSCDynamicStoreDomainState, kSCCompAnyRegex, kSCEntNetIPv4);
    if (NULL == pattern) {
        goto Error;
    }

    patternList = CFArrayCreate(NULL, (const void **)&pattern, 1, &kCFTypeArrayCallBacks);
    if (NULL == patternList) {
        goto Error;
    }

    if (false == SCDynamicStoreSetNotificationKeys(gInterfaceChangedObserver->iStore, NULL, patternList)) {
        goto Error;
    }

    gInterfaceChangedObserver->iRunLoopSource = SCDynamicStoreCreateRunLoopSource(NULL, gInterfaceChangedObserver->iStore, 0);
    if (NULL == gInterfaceChangedObserver->iRunLoopSource) {
        goto Error;
    }

    runLoop = CFRunLoopGetMain();
    if (NULL == runLoop) {
        goto Error;
    }

    CFRunLoopAddSource(runLoop, gInterfaceChangedObserver->iRunLoopSource, kCFRunLoopCommonModes);
    CFRelease(pattern);
    CFRelease(patternList);
    return;

Error:
    if (NULL != pattern) {
        CFRelease(pattern);
    }
    if (NULL != patternList) {
        CFRelease(patternList);
    }
    if (NULL != gInterfaceChangedObserver)
    {
        if (gInterfaceChangedObserver->iStore != NULL) {
            CFRelease(gInterfaceChangedObserver->iStore);
        }
        if (gInterfaceChangedObserver->iRunLoopSource != NULL) {
            CFRelease(gInterfaceChangedObserver->iRunLoopSource);
        }
        free(gInterfaceChangedObserver);
        gInterfaceChangedObserver = NULL;
    }

#endif /* PLATFOTM_MACOSX_GNU && ! PLATFORM_IOS */
}



