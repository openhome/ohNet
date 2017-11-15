// Implementation of Os.h APIs for Posix

#undef SET_PTHREAD_NAMES

//#define SET_PTHREAD_NAMES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <assert.h>
#include <sys/time.h> // eScheduleNice only
#include <sys/resource.h> // eScheduleNice only
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD)
# include <linux/netlink.h>
# include <linux/rtnetlink.h>
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_FREEBSD */
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
#define kMaxThreadNameChars 16

#define TEMP_FAILURE_RETRY_2(expression, handle)                            \
    (__extension__                                                          \
    ({ long int __result;                                                   \
    do                                                                      \
        __result = (long int) (expression);                                 \
    while (__result == -1L && errno == EINTR&& !SocketInterrupted(handle)); \
    __result; }))


#if defined(PLATFORM_MACOSX_GNU) || defined(PLATFORM_FREEBSD)
# define TEMP_FAILURE_RETRY(expression)        \
    (__extension__                             \
    ({ long int __result;                      \
    do                                         \
        __result = (long int) (expression);    \
    while (__result == -1L && errno == EINTR); \
    __result; }))
# define MAX_FILE_DESCRIPTOR FD_SETSIZE
# define MSG_NOSIGNAL 0
#else
# define MAX_FILE_DESCRIPTOR __FD_SETSIZE
#endif

struct OsContext {
    struct timeval iStartTime; /* Time OsCreate was called */
    struct timeval iPrevTime; /* Last time OsTimeInUs() was called */
    struct timeval iTimeAdjustment; /* Amount to adjust return for OsTimeInUs() by. 
                                       Will be 0 unless time ever jumps backwards. */
    THandle iMutex;
    OsThreadSchedulePolicy iSchedulerPolicy;
    pthread_key_t iThreadArgKey;
    struct InterfaceChangedObserver* iInterfaceChangedObserver;
    int32_t iThreadPriorityMin;
};

static void DestroyInterfaceChangedObserver(OsContext* aContext);


OsContext* OsCreate(OsThreadSchedulePolicy aSchedulerPolicy)
{
    OsContext* ctx = malloc(sizeof(*ctx));
    gettimeofday(&ctx->iStartTime, NULL);
    ctx->iPrevTime = ctx->iStartTime;
    memset(&ctx->iTimeAdjustment, 0, sizeof(ctx->iTimeAdjustment));
    ctx->iMutex = OsMutexCreate(ctx, "DNSM");
    if (ctx->iMutex == kHandleNull) {
        free(ctx);
        return NULL;
    }
    ctx->iSchedulerPolicy = aSchedulerPolicy;
    if (pthread_key_create(&ctx->iThreadArgKey, NULL) != 0) {
        OsMutexDestroy(ctx->iMutex);
        free(ctx);
        return NULL;
    }
    ctx->iInterfaceChangedObserver = NULL;
    ctx->iThreadPriorityMin = 0;
    return ctx;
}

void OsDestroy(OsContext* aContext)
{
    if (aContext != NULL) {
        DestroyInterfaceChangedObserver(aContext);
        pthread_key_delete(aContext->iThreadArgKey);
        OsMutexDestroy(aContext->iMutex);
        free(aContext);
    }
}

void OsQuit(OsContext* aContext)
{
    abort();
}

#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
# define STACK_TRACE_ENABLE
#else
# undef  STACK_TRACE_ENABLE
#endif

#ifdef STACK_TRACE_ENABLE
# define STACK_TRACE_MAX_DEPTH 64
typedef struct OsStackTrace
{
    void* iStack[STACK_TRACE_MAX_DEPTH];
    int iCount;
    char** iSymbols;
    
} OsStackTrace;
#endif /* STACK_TRACE_ENABLE */


THandle OsStackTraceInitialise(OsContext* aContext)
{
#ifdef STACK_TRACE_ENABLE
    OsStackTrace* stackTrace = (OsStackTrace*)malloc(sizeof(OsStackTrace));
    if (stackTrace == NULL) {
        return kHandleNull;
    }

    stackTrace->iCount = backtrace(stackTrace->iStack, STACK_TRACE_MAX_DEPTH);
    stackTrace->iSymbols = NULL;
    return stackTrace;
#else
    return kHandleNull;
#endif /* STACK_TRACE_ENABLE */
}

THandle OsStackTraceCopy(THandle aStackTrace)
{
#ifdef STACK_TRACE_ENABLE
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
    (void)aStackTrace;
    return kHandleNull;
#endif /* STACK_TRACE_ENABLE */
}

uint32_t OsStackTraceNumEntries(THandle aStackTrace)
{
#ifdef STACK_TRACE_ENABLE
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    if (stackTrace == kHandleNull) {
        return 0;
    }

    return stackTrace->iCount;
#else
    (void)aStackTrace;
    return 0;
#endif /* STACK_TRACE_ENABLE */
}

const char* OsStackTraceEntry(THandle aStackTrace, uint32_t aIndex)
{
#ifdef STACK_TRACE_ENABLE
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
    (void)aStackTrace;
    (void)aIndex;
    return NULL;
#endif /* STACK_TRACE_ENABLE */
}

void OsStackTraceFinalise(THandle aStackTrace)
{
#ifdef STACK_TRACE_ENABLE
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    if (stackTrace != kHandleNull) {
        if (stackTrace->iSymbols != NULL) {
            free(stackTrace->iSymbols);
        }
        free(stackTrace);
    }
#else
    (void)aStackTrace;
#endif /* STACK_TRACE_ENABLE */
}

static struct timeval subtractTimeval(struct timeval* aT1, struct timeval* aT2)
{
    struct timeval diff;
    diff.tv_sec = aT1->tv_sec - aT2->tv_sec;
    if (aT1->tv_usec > aT2->tv_usec) {
        diff.tv_usec = aT1->tv_usec - aT2->tv_usec;
    }
    else {
        diff.tv_sec--;
        diff.tv_usec = 1000000 - aT2->tv_usec + aT1->tv_usec;
    }
    return diff;
}

static struct timeval addTimeval(struct timeval* aT1, struct timeval* aT2)
{
    struct timeval result;
    result.tv_sec = aT1->tv_sec + aT2->tv_sec;
    int32_t usec = aT1->tv_usec + aT2->tv_usec;
    if (usec < 1000000) {
        result.tv_usec = usec;
    }
    else {
        result.tv_sec++;
        result.tv_usec = usec - 1000000;
    }
    return result;
}

uint64_t OsTimeInUs(OsContext* aContext)
{
    struct timeval now, diff, adjustedNow;
    OsMutexLock(aContext->iMutex);
    gettimeofday(&now, NULL);
    
    /* if time has moved backwards, calculate by how much and add this to aContext->iTimeAdjustment */
    if (now.tv_sec < aContext->iPrevTime.tv_sec ||
        (now.tv_sec == aContext->iPrevTime.tv_sec && now.tv_usec < aContext->iPrevTime.tv_usec)) {
        diff = subtractTimeval(&aContext->iPrevTime, &now);
        fprintf(stderr, "WARNING: clock moved backwards by %llu.%03llusecs\n", (unsigned long long)diff.tv_sec, (unsigned long long)(diff.tv_usec/1000));
        aContext->iTimeAdjustment = addTimeval(&aContext->iTimeAdjustment, &diff);
    }
    aContext->iPrevTime = now; /* stash current time to allow the next call to spot any backwards move */
    adjustedNow = addTimeval(&now, &aContext->iTimeAdjustment); /* add any previous backwards moves to the time */
    diff = subtractTimeval(&adjustedNow, &aContext->iStartTime); /* how long since we started, ignoring any backwards moves */
    OsMutexUnlock(aContext->iMutex);

    return (uint64_t)diff.tv_sec * 1000000 + diff.tv_usec;
}

void OsConsoleWrite(const char* aStr)
{
    fprintf(stderr, "%s", aStr);
    fflush(stderr);
}

void OsGetPlatformNameAndVersion(OsContext* aContext, char** aName, uint32_t* aMajor, uint32_t* aMinor)
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
    int32_t         iValue;
} SemaphoreData;

THandle OsSemaphoreCreate(OsContext* aContext, const char* aName, uint32_t aCount)
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
    if (data->iValue < 0) {
        status = -1;
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
    if (data->iValue < 0) {
        status = -1;
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
    status = pthread_cond_signal(&data->iCond);
    pthread_mutex_unlock(&data->iLock);
    return (status==0? 0 : -1);
}

THandle OsMutexCreate(OsContext* aContext, const char* aName)
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

void OsThreadGetPriorityRange(OsContext* aContext, uint32_t* aHostMin, uint32_t* aHostMax)
{
    if (aContext->iSchedulerPolicy == eSchedulePriorityEnable) {
        const int32_t platMin = sched_get_priority_min(kThreadSchedPolicy);
        const int32_t platMax = sched_get_priority_max(kThreadSchedPolicy);
        aContext->iThreadPriorityMin = platMin;
        *aHostMin = 0;
        *aHostMax = platMax - platMin;
    }
    else if (aContext->iSchedulerPolicy == eScheduleNice) {
        // FIXME - 50/150 copied from previous expectations of threadEntrypoint
        *aHostMin = 50;
        *aHostMax = 150;
    }
    else {
        *aHostMin = 1;
        *aHostMax = 100;
    }
}

typedef struct
{
    pthread_t        iThread;
    ThreadEntryPoint iEntryPoint;
    void*            iArg;
    uint32_t         iPriority;
    OsContext*       iCtx;
    THandle          iSemaHandle;
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

    if (data->iCtx->iSchedulerPolicy == eSchedulePriorityEnable) {
        int32_t priority = ((int32_t)data->iPriority) + data->iCtx->iThreadPriorityMin;
        struct sched_param param;
        memset(&param, 0, sizeof(param));
        //printf("thread priority %u mapped to %d\n", data->iPriority, priority);
        param.sched_priority = priority;
        int status = pthread_setschedparam(data->iThread, kThreadSchedPolicy, &param);
        if (status != 0) {
            char name[kMaxThreadNameChars] = {0};
#if defined(SET_PTHREAD_NAMES)
            pthread_getname_np(data->iThread, name, sizeof(name));
#else
            strncpy(name, "UNKNOWN", kMaxThreadNameChars-1);
#endif
            printf("Attempt to set thread priority for '%s' to %d failed with %d(%d)\n", name, priority, status, errno);
        }
    }
    else if (data->iCtx->iSchedulerPolicy == eScheduleNice) {
        static const int kMinimumNice = 5; // set MIN
        // Map all prios > 105 -> nice 0 (default), anything else to MIN
        //int nice_value = (data->iPriority > 105 ? 0 : kMinimumNice);
        // Map prio=[50,150]-> nice=[MIN,0]
        int nice_value = -1 * (((((int) data->iPriority-50) * kMinimumNice) / (150-50)) - kMinimumNice);
        if ( nice_value < 0 )
            nice_value = 0;
        //printf("Thread of priority %d asking for niceness %d (current niceness is %d)\n", data->iPriority, nice_value, getpriority(PRIO_PROCESS, 0));
        /*int result = */setpriority(PRIO_PROCESS, 0, nice_value);
        //if ( result == -1 )
        //    perror("Warning: Could not renice this thread");
    }

    // Disable cancellation - we're in a C++ environment, and
    // don't want to rely on pthreads to mess things up for us.
#ifndef __ANDROID__
    status = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldState);
    assert(status == 0);
#endif

    //tlsThreadArg = data->iArg;
    pthread_setspecific(data->iCtx->iThreadArgKey, data->iArg);
    data->iEntryPoint(data->iArg);

    return NULL;
}

static THandle DoThreadCreate(OsContext* aContext, const char* aName, uint32_t aPriority, uint32_t aStackBytes, int isJoinable, ThreadEntryPoint aEntryPoint, void* aArg)
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
    data->iCtx        = aContext;
    data->iSemaHandle = OsSemaphoreCreate(aContext, "tls_sem", 0);

    if (data->iSemaHandle == kHandleNull) {
        free(data);
        return kHandleNull;
    }

    pthread_attr_t attr;
    (void)pthread_attr_init(&attr);
    (void)pthread_attr_setstacksize(&attr, aStackBytes);
#ifndef __ANDROID__
    (void)pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
#endif
    (void)pthread_attr_setdetachstate(&attr, isJoinable ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED);
    int status = pthread_create(&data->iThread, &attr, threadEntrypoint, data);
    if (status != 0) {
        free(data);
        return kHandleNull;
    }
    (void)pthread_attr_destroy(&attr);

#if defined(SET_PTHREAD_NAMES)
#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS) && !defined(__ANDROID__)
    char name[kMaxThreadNameChars] = {0};
    strncpy(name, aName, kMaxThreadNameChars-1); // leave trailing \0
    (void)pthread_setname_np(data->iThread, name);
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_IOS && !__ANDROID__ */
#endif

    return (THandle)data;
}

void OsThreadWait(THandle aThread, uint32_t aConsumePolicy)
{
    THandle sema = ((ThreadData*) aThread)->iSemaHandle;

    OsSemaphoreWait(sema);

    if (aConsumePolicy == eConsumeAll) {
        OsSemaphoreClear(sema);
    }
}

void OsThreadSignal(THandle aThread)
{
    THandle sema = ((ThreadData*) aThread)->iSemaHandle;

    OsSemaphoreSignal(sema);
}

THandle OsThreadCreate(OsContext* aContext, const char* aName, uint32_t aPriority, uint32_t aStackBytes, ThreadEntryPoint aEntryPoint, void* aArg)
{
    return DoThreadCreate(aContext, aName, aPriority, aStackBytes, 0, aEntryPoint, aArg);
}

void* OsThreadTls(OsContext* aContext)
{
    return pthread_getspecific(aContext->iThreadArgKey);
    //return tlsThreadArg;
}

void OsThreadDestroy(THandle aThread)
{
    ThreadData* data = (ThreadData*) aThread;
    OsSemaphoreDestroy(data->iSemaHandle);
    // no call to pthread_exit as it will have been implicitly called when the thread exited
    free(data);
}

int32_t OsThreadSupportsPriorities(OsContext* aContext)
{
    if (aContext->iSchedulerPolicy == eSchedulePriorityEnable) {
        return 1;
    }
    return 0;
}

typedef struct OsNetworkHandle
{
    int32_t    iSocket;
    int32_t    iPipe[2];
    int32_t    iInterrupted;
    OsContext* iCtx;
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
    OsMutexLock(aHandle->iCtx->iMutex);
    interrupted = aHandle->iInterrupted;
    OsMutexUnlock(aHandle->iCtx->iMutex);
    return interrupted;
}

static void sockaddrFromEndpoint(struct sockaddr_in* aAddr, TIpAddress aAddress, uint16_t aPort)
{
    memset(aAddr, 0, sizeof(*aAddr));
    aAddr->sin_family = 2;
    aAddr->sin_port = htons(aPort);
    aAddr->sin_addr.s_addr = aAddress;
}

static OsNetworkHandle* CreateHandle(OsContext* aContext, int32_t aSocket)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)malloc(sizeof(OsNetworkHandle));
#ifdef PLATFORM_MACOSX_GNU
    int set = 1;
    setsockopt(aSocket, SOL_SOCKET, SO_NOSIGPIPE, (void*)&set, sizeof(int));
#endif /* PLATFORM_MACOSX_GNU */
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
    handle->iCtx = aContext;

    return handle;
}

THandle OsNetworkCreate(OsContext* aContext, OsNetworkSocketType aSocketType)
{
    int32_t socketH;
    int32_t type = (aSocketType == eOsNetworkSocketStream) ? SOCK_STREAM : SOCK_DGRAM;

    socketH = socket(2, type, 0);
    OsNetworkHandle* handle = CreateHandle(aContext, socketH);
    if (handle == kHandleNull) {
        /* close is the one networking call that is exempt from being wrapped by TEMP_FAILURE_RETRY.  See
        https://sites.google.com/site/michaelsafyan/software-engineering/checkforeintrwheninvokingclosethinkagain */
        close(socketH);
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
        uint16_t port = ntohs(addr.sin_port);
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

    int32_t selectErr = TEMP_FAILURE_RETRY_2(select(nfds(handle), &read, &write, &error, &tv), handle);
    if (selectErr > 0 && FD_ISSET(handle->iSocket, &write)) {
        // Need to check socket status using getsockopt. See man page for connect, EINPROGRESS
        int sock_error;
        socklen_t err_len = sizeof(sock_error);
        if (getsockopt(handle->iSocket, SOL_SOCKET, SO_ERROR, &sock_error, &err_len) == 0) {
            err = ((err_len == sizeof(sock_error)) && (sock_error == 0)) ? 0 : -2;
        }
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
        bytes = TEMP_FAILURE_RETRY_2(send(handle->iSocket, &aBuffer[sent], aBytes-sent, MSG_NOSIGNAL), handle);
        if (bytes != -1) {
            sent += bytes;
        }
    } while(bytes != -1 && sent < (int32_t)aBytes);
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
        bytes = TEMP_FAILURE_RETRY_2(sendto(handle->iSocket, &aBuffer[sent], aBytes-sent, MSG_NOSIGNAL, (struct sockaddr*)&addr, sizeof(addr)), handle);
        if (bytes != -1) {
            sent += bytes;
        }
    } while(bytes != -1 && sent < (int32_t)aBytes);    
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

    int32_t received = TEMP_FAILURE_RETRY_2(recv(handle->iSocket, aBuffer, aBytes, MSG_NOSIGNAL), handle);
    if (received==-1 && errno==EWOULDBLOCK) {
        int32_t selectErr = TEMP_FAILURE_RETRY_2(select(nfds(handle), &read, NULL, &error, NULL), handle);
        if (selectErr > 0 && FD_ISSET(handle->iSocket, &read)) {
            received = TEMP_FAILURE_RETRY_2(recv(handle->iSocket, aBuffer, aBytes, MSG_NOSIGNAL), handle);
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

    int32_t received = TEMP_FAILURE_RETRY_2(recvfrom(handle->iSocket, aBuffer, aBytes, MSG_NOSIGNAL, (struct sockaddr*)&addr, &addrLen), handle);
    if (received==-1 && errno==EWOULDBLOCK) {
        int32_t selectErr = TEMP_FAILURE_RETRY_2(select(nfds(handle), &read, NULL, &error, NULL), handle);
        if (selectErr > 0 && FD_ISSET(handle->iSocket, &read)) {
            received = TEMP_FAILURE_RETRY_2(recvfrom(handle->iSocket, aBuffer, aBytes, MSG_NOSIGNAL, (struct sockaddr*)&addr, &addrLen), handle);
        }
    }
    SetFdBlocking(handle->iSocket);
    *aAddress = addr.sin_addr.s_addr;
    *aPort = ntohs(addr.sin_port);
    return received;
}

int32_t OsNetworkInterrupt(THandle aHandle, int32_t aInterrupt)
{
    int32_t err = 0;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    OsContext* ctx = handle->iCtx;
    OsMutexLock(ctx->iMutex);
    handle->iInterrupted = aInterrupt;
    int32_t val = 1;
    if (aInterrupt != 0) {
        if (TEMP_FAILURE_RETRY(write(handle->iPipe[1], &val, sizeof(val))) == -1) {
            err = -1;
        }
    }
    else {
        while (TEMP_FAILURE_RETRY(read(handle->iPipe[0], &val, sizeof(val))) > 0) {
            ;
        }
    }
    OsMutexUnlock(ctx->iMutex);
    return err;
}

int32_t OsNetworkClose(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = 0;
    if (handle != NULL) {
        err  = close(handle->iSocket);
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

THandle OsNetworkAccept(THandle aHandle, TIpAddress* aClientAddress, uint32_t* aClientPort)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    *aClientAddress = 0;
    *aClientPort = 0;
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

    int32_t h = TEMP_FAILURE_RETRY_2(accept(handle->iSocket, (struct sockaddr*)&addr, &len), handle);
    if (h==-1 && errno==EWOULDBLOCK) {
        int32_t selectErr = TEMP_FAILURE_RETRY_2(select(nfds(handle), &read, NULL, &error, NULL), handle);
        if (selectErr > 0 && FD_ISSET(handle->iSocket, &read)) {
            h = TEMP_FAILURE_RETRY_2(accept(handle->iSocket, (struct sockaddr*)&addr, &len), handle);
        }
    }
    SetFdBlocking(handle->iSocket);
    if (h == -1) {
        return kHandleNull;
    }

    OsNetworkHandle* newHandle = CreateHandle(handle->iCtx, h);
    if (newHandle == NULL) {
        close(h);
        return kHandleNull;
    }

    *aClientAddress = addr.sin_addr.s_addr;
    *aClientPort = ntohs(addr.sin_port);
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
 
int32_t OsNetworkSocketSetMulticastIf(THandle aHandle,  TIpAddress aInterface)
{
#if defined(PLATFORM_MACOSX_GNU) || defined(PLATFORM_FREEBSD)
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = setsockopt(handle->iSocket, IPPROTO_IP, IP_MULTICAST_IF, &aInterface, sizeof(aInterface));
    return err;
#else
    return 0;
#endif
}

int32_t OsNetworkListAdapters(OsContext* aContext, OsNetworkAdapter** aAdapters, uint32_t aUseLoopback)
{
#ifdef DEFINE_BIG_ENDIAN
#define MakeIpAddress(aByte1, aByte2, aByte3, aByte4) \
        (aByte4 | (aByte3<<8) | (aByte2<<16) | (aByte1<<24))
#elif defined(DEFINE_LITTLE_ENDIAN)
#define MakeIpAddress(aByte1, aByte2, aByte3, aByte4) \
        (aByte1 | (aByte2<<8) | (aByte3<<16) | (aByte4<<24))
#else
#error "Endianness must be defined."
#endif

    int32_t ret = -1;
    struct ifaddrs* networkIf;
    struct ifaddrs* iter;
    int32_t includeLoopback = 1;
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
                (iter->ifa_flags & IFF_RUNNING) != 0 &&
                ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr != loopbackAddr) {
                includeLoopback = 0;
                break;
            }
            iter = iter->ifa_next;
        }
    }
    /* ...then allocate/populate the list */
    OsNetworkAdapter* head = NULL;
    OsNetworkAdapter* tail = NULL;
    for (iter = networkIf; iter != NULL; iter = iter->ifa_next) {
        if (iter->ifa_addr == NULL || iter->ifa_addr->sa_family != AF_INET ||
            (iter->ifa_flags & IFF_RUNNING) == 0 ||
            (includeLoopback == 0 && ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr == loopbackAddr) ||
            (aUseLoopback == 1 && ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr != loopbackAddr)) {
            continue;
        }

        // Check for multiple entries with same address and different subnets and
        // ensure that only the least specific (largest superset) subnet is added.
        // This code would also work if there are repeated identical address/subnet pairs.

        // first check the entries already added to see if any of them is a superset subnet 
        TIpAddress address = ((struct sockaddr_in*)iter->ifa_addr)->sin_addr.s_addr;
        TIpAddress netMask = ((struct sockaddr_in*)iter->ifa_netmask)->sin_addr.s_addr;
        OsNetworkAdapter* ifaceIter = head;
        while (ifaceIter != NULL) {
            if (ifaceIter->iAddress == address && (ifaceIter->iNetMask & netMask) == ifaceIter->iNetMask) {
                break; // superset subnet has been added already
            }
            ifaceIter = ifaceIter->iNext;
        }
        if (ifaceIter != NULL) {
            continue; // superset subnet has been added already
        }

        // now check the entries not yet added to see if any of them is a superset subnet 
        struct ifaddrs* addrsIter = iter->ifa_next;
        while (addrsIter != NULL) {
            TIpAddress iterAddress = ((struct sockaddr_in*)addrsIter->ifa_addr)->sin_addr.s_addr;
            TIpAddress iterNetMask = ((struct sockaddr_in*)addrsIter->ifa_netmask)->sin_addr.s_addr;
            if (iterAddress == address && (iterNetMask & netMask) == iterNetMask) {
                break; // superset subnet will be added later
            }
            addrsIter = addrsIter->ifa_next;
        }
        if (addrsIter != NULL) {
            continue; // superset subnet will be added later
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
        iface->iAddress = address;
        iface->iNetMask = netMask;
        if (tail != NULL) {
            tail->iNext = iface;
        }
        tail = iface;
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

typedef struct InterfaceChangedObserver
{
    InterfaceListChanged iCallback;
    void* iArg;
    SCDynamicStoreRef iStore;
    CFRunLoopSourceRef iRunLoopSource;

} InterfaceChangedObserver;

#else

typedef struct InterfaceChangedObserver
{
    OsNetworkHandle *netHnd;
    InterfaceListChanged iCallback;
    void* iArg;
    THandle iThread;
} InterfaceChangedObserver;

#endif /* PLATFOTM_MACOSX_GNU */

#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)

static void InterfaceChangedDynamicStoreCallback(SCDynamicStoreRef aStore, CFArrayRef aChangedKeys, void* aInfo)
{
    if (aInfo != NULL)
    {
        InterfaceChangedObserver* obs = (InterfaceChangedObserver*)aInfo;
        obs->iCallback(obs->iArg);
    }
}

static void SetInterfaceChangedObserver_MacDesktop(OsContext* aContext, InterfaceListChanged aCallback, void* aArg)
{
    SCDynamicStoreContext context = {0, NULL, NULL, NULL, NULL};
    CFStringRef pattern = NULL;
    CFArrayRef patternList = NULL;
    CFRunLoopRef runLoop = NULL;

    if (NULL != aContext->iInterfaceChangedObserver) {
        return;
    }

    aContext->iInterfaceChangedObserver = (InterfaceChangedObserver*)malloc(sizeof(*(aContext->iInterfaceChangedObserver)));
    if (NULL == aContext->iInterfaceChangedObserver) {
        goto Error;
    }

    aContext->iInterfaceChangedObserver->iCallback = aCallback;
    aContext->iInterfaceChangedObserver->iArg = aArg;
    aContext->iInterfaceChangedObserver->iStore = NULL;
    aContext->iInterfaceChangedObserver->iRunLoopSource = NULL;

    context.info = aContext->iInterfaceChangedObserver;

    aContext->iInterfaceChangedObserver->iStore = SCDynamicStoreCreate(NULL, CFSTR("AddIPAddressListChangeCallbackSCF"), &InterfaceChangedDynamicStoreCallback, &context);
    if (NULL == aContext->iInterfaceChangedObserver->iStore) {
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

    if (false == SCDynamicStoreSetNotificationKeys(aContext->iInterfaceChangedObserver->iStore, NULL, patternList)) {
        goto Error;
    }

    aContext->iInterfaceChangedObserver->iRunLoopSource = SCDynamicStoreCreateRunLoopSource(NULL, aContext->iInterfaceChangedObserver->iStore, 0);
    if (NULL == aContext->iInterfaceChangedObserver->iRunLoopSource) {
        goto Error;
    }

    runLoop = CFRunLoopGetMain();
    if (NULL == runLoop) {
        goto Error;
    }

    CFRunLoopAddSource(runLoop, aContext->iInterfaceChangedObserver->iRunLoopSource, kCFRunLoopCommonModes);
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
    if (NULL != aContext->iInterfaceChangedObserver)
    {
        if (aContext->iInterfaceChangedObserver->iStore != NULL) {
            CFRelease(aContext->iInterfaceChangedObserver->iStore);
        }
        if (aContext->iInterfaceChangedObserver->iRunLoopSource != NULL) {
            CFRelease(aContext->iInterfaceChangedObserver->iRunLoopSource);
        }
        free(aContext->iInterfaceChangedObserver);
        aContext->iInterfaceChangedObserver = NULL;
    }
}

static void DestroyInterfaceChangedObserver_MacDesktop(OsContext* aContext)
{
    if (NULL != aContext->iInterfaceChangedObserver)
    {
        CFRunLoopRef runLoop = CFRunLoopGetMain();
        CFRunLoopRemoveSource(runLoop, aContext->iInterfaceChangedObserver->iRunLoopSource, kCFRunLoopCommonModes);
        CFRelease(aContext->iInterfaceChangedObserver->iStore);
        CFRelease(aContext->iInterfaceChangedObserver->iRunLoopSource);
        free(aContext->iInterfaceChangedObserver);
        aContext->iInterfaceChangedObserver = NULL;
    }
}

#endif /* PLATFOTM_MACOSX_GNU && ! PLATFORM_IOS */

#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD)

void adapterChangeObserverThread(void* aPtr)
{
    InterfaceChangedObserver* observer = (InterfaceChangedObserver*) aPtr;
    OsNetworkHandle *handle = observer->netHnd;
    char buffer[4096];
    struct nlmsghdr *nlh;
    int32_t len, ret;
    fd_set rfds,errfds;

    while (1) {
        if (SocketInterrupted(handle)) {
            return;
        }

        FD_ZERO(&rfds);
        FD_SET(handle->iPipe[0], &rfds);
        FD_SET(handle->iSocket, &rfds);

        FD_ZERO(&errfds);
        FD_SET(handle->iSocket, &errfds);

        ret = TEMP_FAILURE_RETRY_2(select(nfds(handle), &rfds, NULL, &errfds, NULL), handle);
        if ((ret > 0) && FD_ISSET(handle->iSocket, &rfds)) {
            nlh = (struct nlmsghdr *) buffer;
            if ((len = recv(handle->iSocket, nlh, 4096, 0)) > 0) {
                while (NLMSG_OK(nlh, len) && (nlh->nlmsg_type != NLMSG_DONE)) {
                    if (nlh->nlmsg_type == RTM_NEWADDR || 
                        nlh->nlmsg_type == RTM_DELADDR || 
                        nlh->nlmsg_type == RTM_NEWLINK) {              
                        observer->iCallback(observer->iArg);
                    }
                    nlh = NLMSG_NEXT(nlh, len);
                }
            }
        }
    }
}

static int32_t ThreadJoin(THandle aThread)
{
    ThreadData* data = (ThreadData*) aThread;
    int status = pthread_join(data->iThread, NULL);
    return (status==0 ? 0 : -1);
}

static void DestroyInterfaceChangedObserver_Linux(OsContext* aContext)
{
    if (aContext->iInterfaceChangedObserver != NULL) {
        if (aContext->iInterfaceChangedObserver->iThread != NULL) {
            OsNetworkInterrupt(aContext->iInterfaceChangedObserver->netHnd, 1);
            ThreadJoin(aContext->iInterfaceChangedObserver->iThread);
            OsThreadDestroy(aContext->iInterfaceChangedObserver->iThread);
        }
                   
        OsNetworkClose(aContext->iInterfaceChangedObserver->netHnd);

        free(aContext->iInterfaceChangedObserver);
        aContext->iInterfaceChangedObserver = NULL;
    }
}

static void SetInterfaceChangedObserver_Linux(OsContext* aContext, InterfaceListChanged aCallback, void* aArg)
{
    struct sockaddr_nl addr;
    int sock = 0;
    uint32_t minPrio, maxPrio;

    aContext->iInterfaceChangedObserver = (InterfaceChangedObserver*) calloc(1, sizeof(InterfaceChangedObserver));
    if (aContext->iInterfaceChangedObserver == NULL) {
        goto Error;
    }

    if ((sock = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE)) == -1) {
        goto Error;
    }

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR;
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(sock);
        goto Error;
    }

    if ((aContext->iInterfaceChangedObserver->netHnd = CreateHandle(aContext, sock)) == NULL) {
        close(sock);
        goto Error;
    }

    OsThreadGetPriorityRange(aContext, &minPrio, &maxPrio);

    aContext->iInterfaceChangedObserver->iCallback = aCallback;
    aContext->iInterfaceChangedObserver->iArg = aArg;
    if ((aContext->iInterfaceChangedObserver->iThread = DoThreadCreate(aContext,
                                                            "AdapterChangeObserverThread",
                                                            (maxPrio - minPrio) / 2, 16 * 1024, 1,
                                                            adapterChangeObserverThread,
                                                            aContext->iInterfaceChangedObserver)) == NULL) {
        goto Error;
    }
    
    return;

Error:
    DestroyInterfaceChangedObserver_Linux(aContext);
}

#endif /* !PLATFORM_MACOSX_GNU  && !PLATFORM_FREEBSD */

static void DestroyInterfaceChangedObserver(OsContext* aContext)
{
#ifdef PLATFORM_MACOSX_GNU
# ifndef PLATFORM_IOS
    DestroyInterfaceChangedObserver_MacDesktop(aContext);
# endif /* !PLATFORM_IOS */
#elif defined(PLATFORM_FREEBSD)
#else /* !PLATFOTM_MACOSX_GNU */
    DestroyInterfaceChangedObserver_Linux(aContext);
#endif /* PLATFOTM_MACOSX_GNU */
}


void OsNetworkSetInterfaceChangedObserver(OsContext* aContext, InterfaceListChanged aCallback, void* aArg)
{
#ifdef PLATFORM_MACOSX_GNU
# ifndef PLATFORM_IOS
    SetInterfaceChangedObserver_MacDesktop(aContext, aCallback, aArg);
# endif /* !PLATFORM_IOS */
#elif defined(PLATFORM_FREEBSD)
#else /* !PLATFOTM_MACOSX_GNU */
    SetInterfaceChangedObserver_Linux(aContext, aCallback, aArg);
#endif /* PLATFOTM_MACOSX_GNU */
}



