// Implementation of Os.h APIs for Posix

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
#include <netinet/in.h>
#include <netinet/tcp.h>
#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD)
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_FREEBSD */
#if defined(PLATFORM_MACOSX_GNU) || defined(PLATFORM_FREEBSD) || defined(PLATFORM_QNAP)
#include <net/if.h>
#else
#include <linux/wireless.h>
#endif /* PLATFORM_MACOSX_GNU || PLATFORM_FREEBSD || PLATFORM_QNAP */
#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD) && !defined(__ANDROID__)
#include <sys/inotify.h>
#include <arpa/nameser.h>
#include <resolv.h>
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_FREEBSD && !defined(__ANDROID__) */
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <signal.h>

#ifdef PLATFORM_MACOSX_GNU
#include <SystemConfiguration/SystemConfiguration.h>
#include <execinfo.h>

#ifndef PLATFORM_IOS
#include <IOKit/IOMessage.h>
#include <IOKit/pwr_mgt/IOPMLib.h>
#endif /* !PLATFORM_IOS */

#include <mach/mach_init.h>
#include <mach/mach_interface.h>
#include <mach/mach_port.h>
#include <stdarg.h>
#endif

#ifdef POSIX_STACK_TRACE
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

#ifdef PLATFORM_MACOSX_GNU
static void WriteTimeStamp(void)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    int32_t millis = now.tv_usec / 1000;
    int32_t dsec = (int)(now.tv_sec - 1587250800);
    int32_t seconds = dsec % 60;
    int32_t dmin = dsec / 60;
    int32_t minutes = dmin % 60;
    int32_t hours = (dmin / 60) % 24;
    fprintf(stderr, "%02d:%02d:%02d.%03d ", hours, minutes, seconds, millis);
}
#endif

typedef struct OsNetworkHandle
{
    int32_t    iSocket;
    int32_t    iPipe[2];
    int32_t    iInterrupted;
    OsContext* iCtx;
} OsNetworkHandle;

typedef struct DnsRefresher
{
    OsNetworkHandle* iHandle;
    THandle iThread;
    DnsChanged iCallback;
    void* iCallbackArg;
} DnsRefresher;

typedef struct SemaphoreData
{
    pthread_cond_t  iCond;
    pthread_mutex_t iLock;
    int32_t         iValue;
#ifdef PLATFORM_MACOSX_GNU
    int32_t         iSignalled;
    struct SemaphoreData* iNext;
    OsContext*      iCtx;
#endif
} SemaphoreData;

#ifdef PLATFORM_MACOSX_GNU
#ifndef PLATFORM_IOS
typedef struct SleepWake
{
    SemaphoreData* iTimedWaits;
    io_connect_t iRootPort; /* reference to the Root Power Domain IOService */
    IONotificationPortRef iNotifyPortRef; /* allocated by IORegisterForSystemPower */
    io_object_t iNotifierObject; /* notifier object, used to deregister later */
    THandle iThread;
    CFRunLoopRef iRunLoop;
} SleepWake;
#endif /* !PLATFORM_IOS */
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
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
    SleepWake* iSleepWake;
#endif

    DnsRefresher* iDnsRefresh; // linux only
};


static void DestroyInterfaceChangedObserver(OsContext* aContext);
#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD) && !defined(__ANDROID__)
static void DnsRefreshCreate(OsContext* aContext);
static void DnsRefreshDestroy(OsContext* aContext);
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_FREEBSD && !defined(__ANDROID__) */

#ifdef PLATFORM_MACOSX_GNU
#ifndef PLATFORM_IOS
static void SleepWakeCreate(OsContext* aContext);
static void SleepWakeDestroy(OsContext* aContext);
#endif /* !PLATFORM_IOS */
#endif /* PLATFORM_MACOSX */


OsContext* OsCreate(OsThreadSchedulePolicy aSchedulerPolicy)
{
    OsContext* ctx = calloc(1, sizeof(*ctx));
    gettimeofday(&ctx->iStartTime, NULL);
    ctx->iPrevTime = ctx->iStartTime;
    memset(&ctx->iTimeAdjustment, 0, sizeof(ctx->iTimeAdjustment));
    ctx->iSchedulerPolicy = aSchedulerPolicy;
    ctx->iMutex = OsMutexCreate(ctx, "DNSM");
    if (ctx->iMutex == kHandleNull) {
        free(ctx);
        return NULL;
    }
    if (pthread_key_create(&ctx->iThreadArgKey, NULL) != 0) {
        OsMutexDestroy(ctx->iMutex);
        free(ctx);
        return NULL;
    }
    ctx->iInterfaceChangedObserver = NULL;
    ctx->iThreadPriorityMin = 0;

#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD) && !defined(__ANDROID__)
    DnsRefreshCreate(ctx);
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_FREEBSD && !defined(__ANDROID__) */

#ifdef PLATFORM_MACOSX_GNU
#ifndef PLATFORM_IOS
    SleepWakeCreate(ctx);
#endif /* !PLATFORM_IOS */
#endif /* PLATFORM_MACOSX */

    return ctx;
}

void OsDestroy(OsContext* aContext)
{
    if (aContext != NULL) {

#ifdef PLATFORM_MACOSX_GNU
#ifndef PLATFORM_IOS
        SleepWakeDestroy(aContext);
#endif /* !PLATFORM_IOS */
#endif /* PLATFORM_MACOSX */ 

#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD) && !defined(__ANDROID__)
        DnsRefreshDestroy(aContext);
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_FREEBSD && !defined(__ANDROID__) */
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

#if (defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)) || defined(POSIX_STACK_TRACE)
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
#ifdef PLATFORM_MACOSX_GNU
    data->iCtx = aContext;
#endif
    return (THandle)data;
}

#ifdef PLATFORM_MACOSX_GNU
#ifndef PLATFORM_IOS
static void Debug(char* message, ...)
{
    va_list args;
    int enableDebug = 0; // 1 enables, 0 disables debug output
    if (enableDebug) {
        WriteTimeStamp();
        va_start(args, message);
        vfprintf(stderr, message, args);
        va_end(args);
        fflush(stderr);
    }
}

void removeTimedWait(SemaphoreData* data, char* function)
{
    // remove this semaphore from the timed waiting list, if present
    SleepWake *sleepWake = data->iCtx->iSleepWake;
    OsMutexLock(data->iCtx->iMutex);
    if (sleepWake->iTimedWaits == data) {
        Debug("%s: removing semaphore %p from timed wait list\n", function, data);
        sleepWake->iTimedWaits = data->iNext;
    }
    else {
        for (SemaphoreData* sem = sleepWake->iTimedWaits; sem != NULL; sem = sem->iNext) {
            if (sem->iNext == data) {
                Debug("%s: removing semaphore %p from timed wait list\n", function, data);
                sem->iNext = data->iNext;
                break;
            }
        }
    }
    OsMutexUnlock(data->iCtx->iMutex);
}
#endif /* !PLATFORM_IOS */
#endif /* PLATFORM_MACOSX_GNU */

void OsSemaphoreDestroy(THandle aSem)
{
    SemaphoreData* data = (SemaphoreData*)aSem;
    if (data == kHandleNull) {
        return;
    }
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
    removeTimedWait(data, "OsSemaphoreDestroy");
#endif
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
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
        // add this semaphore to the timed waiting list
        Debug("OsSemaphoreTimedWait: adding semaphore %p to timed wait list\n", data);
        OsContext* ctx = data->iCtx;
        SleepWake* sleepWake = ctx->iSleepWake;
        OsMutexLock(ctx->iMutex);
        data->iNext = sleepWake->iTimedWaits;
        sleepWake->iTimedWaits = data;
        data->iSignalled = 0;
        OsMutexUnlock(ctx->iMutex);
        int32_t millis = timeToWait.tv_nsec / 1000000;
        int32_t dsec = (int)(timeToWait.tv_sec - 1587250800);
        int32_t seconds = dsec % 60;
        int32_t dmin = dsec / 60;
        int32_t minutes = dmin % 60;
        int32_t hours = (dmin / 60) % 24;
        while (true) {
            Debug("OsSemaphoreTimedWait: handle=%p timeout=%d timeToWait=%02d:%02d:%02d.%03d\n",
                  aSem, aTimeoutMs, hours, minutes, seconds, millis);
#endif /* PLATFORM_MACOSX_GNU && !PLATFORM_IOS */
            status = TEMP_FAILURE_RETRY(pthread_cond_timedwait(&data->iCond, &data->iLock, &timeToWait));
#if defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_IOS)
            if (status == 0 && !data->iSignalled) {
                // signalled by SleepWakeCallback
                struct timeval now;
                gettimeofday(&now, NULL);
                if (now.tv_sec < timeToWait.tv_sec ||
                    (now.tv_sec == timeToWait.tv_sec && now.tv_usec * 1000 < timeToWait.tv_nsec)) {
                    // original wait deadline has not yet passed
                    continue;
                } else {
                    status = ETIMEDOUT;
                }
            }
            break;
        }
        Debug("OsSemaphoreTimedWait: handle=%p timeout=%d timeToWait=%02d:%02d:%02d.%03d status=%d\n",
              aSem, aTimeoutMs, hours, minutes, seconds, millis, status);
        data->iSignalled = 0;
        removeTimedWait(data, "OsSemaphoreTimedWait");
#endif
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
#ifdef PLATFORM_MACOSX_GNU
    data->iSignalled = 1;
#endif
    status = pthread_cond_signal(&data->iCond);
    pthread_mutex_unlock(&data->iLock);
    return (status==0? 0 : -1);
}

THandle OsMutexCreate(OsContext* aContext, const char* aName)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    (void)pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
#ifndef __ANDROID__
    if (aContext->iSchedulerPolicy == eSchedulePriorityEnable) {
        int err = pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
        if (err != 0) {
            fprintf(stderr, "OsMutexCreate - failed to set PTHREAD_PRIO_INHERIT - error=%d\n", err);
            return kHandleNull;
        }
    }
#endif /* !__ANDROID__ */
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

static TIpAddress TIpAddressFromSockAddr(const struct sockaddr* aAddr)
{
    TIpAddress addr;

    // Check for IPv6, default to IPv4
    if (aAddr->sa_family == AF_INET6) {
        addr.iFamily = kFamilyV6;
        for (uint8_t i = 0; i < 16; i++) {
            addr.iV6[i] = ((const struct sockaddr_in6*)aAddr)->sin6_addr.s6_addr[i];
        }
    }
    else {
        addr.iFamily = kFamilyV4;
        addr.iV4 = ((const struct sockaddr_in*)aAddr)->sin_addr.s_addr;
    }

    return addr;
}

static uint16_t PortFromSockAddr(const struct sockaddr* aAddr)
{
    return (aAddr->sa_family == AF_INET6) ? ntohs(((const struct sockaddr_in6*)aAddr)->sin6_port) : ntohs(((const struct sockaddr_in*)aAddr)->sin_port);
}

static void in6AddrFromTIpAddress(struct in6_addr* aAddr, const TIpAddress* aAddress)
{
    for (uint8_t i = 0; i < 16; i++) {
        aAddr->s6_addr[i] = aAddress->iV6[i];
    }
}

uint32_t sockaddrFromEndpoint(struct sockaddr* aAddr, const TIpAddress* aAddress, uint16_t aPort)
{
    memset(aAddr, 0, sizeof(struct sockaddr_in6));
    // Check for IPv6 default to IPv4
    if (aAddress->iFamily == kFamilyV6) {
        struct sockaddr_in6 addr;
        addr.sin6_family = 10; // AF_INET6
        addr.sin6_port = htons(aPort);
        in6AddrFromTIpAddress(&addr.sin6_addr, aAddress);
        memcpy(aAddr, &addr, sizeof(addr));
        return sizeof(addr);
    }
    else {
        struct sockaddr_in addr;
        addr.sin_family = 2; // AF_INET
        addr.sin_port = htons(aPort);
        addr.sin_addr.s_addr = aAddress->iV4;
        memcpy(aAddr, &addr, sizeof(addr));
        return sizeof(addr);
    }
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

THandle OsNetworkCreate(OsContext* aContext, OsNetworkSocketType aSocketType, OsNetworkSocketFamily aSocketFamily)
{
    int32_t socketH;
    int32_t type = (aSocketType == eOsNetworkSocketStream) ? SOCK_STREAM : SOCK_DGRAM;
    int32_t family = (aSocketFamily == eOsNetworkSocketV4) ? AF_INET : AF_INET6;

    socketH = socket(family, type, 0);
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

    // Create storage for the larger of the two structs (sockaddr_in/sockaddr_in6)
    // Helper function will setup sockaddr for IPv4/v6
    struct sockaddr_in6 addr;
    int32_t len = sockaddrFromEndpoint((struct sockaddr*)&addr, &aAddress, (uint16_t)aPort);

    err = bind(handle->iSocket, (struct sockaddr*)&addr, len);

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
    struct sockaddr addr;
    socklen_t len = sizeof(addr);
    err = getsockname(handle->iSocket, &addr, &len);
    if (err == 0) {
        // PortFromSockAddr handles IPv4 and v6 sockets
        uint16_t port = PortFromSockAddr(&addr);
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

    // Create storage for the larger of the two structs (sockaddr_in/sockaddr_in6)
    // Helper function will setup sockaddr for IPv4/v6
    struct sockaddr_in6 addr;
    sockaddrFromEndpoint((struct sockaddr*)&addr, &aAddress, aPort);
    /* ignore err as we expect this to fail due to EINPROGRESS */
    (void)connect(handle->iSocket, (struct sockaddr*)&addr, sizeof(addr));

    fd_set read;
    fd_set write;
    fd_set error;
    int32_t selectErr;

    struct timeval tv;
    tv.tv_sec = aTimeoutMs / 1000;
    tv.tv_usec = (aTimeoutMs % 1000) * 1000;

    do {
        FD_ZERO(&read);
        FD_SET(handle->iPipe[0], &read);
        FD_ZERO(&write);
        FD_SET(handle->iSocket, &write);
        FD_ZERO(&error);
        FD_SET(handle->iSocket, &error);
        selectErr = (long int) select(nfds(handle), &read, &write, &error, &tv);
    } while(selectErr == -1L && errno == EINTR && !SocketInterrupted(handle));
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
    // Create storage for the larger of the two structs (sockaddr_in/sockaddr_in6)
    // Helper function will setup sockaddr for IPv4/v6
    struct sockaddr_in6 addr;
    sockaddrFromEndpoint((struct sockaddr*)&addr, &aAddress, aPort);

    int32_t sent = 0;
    int32_t bytes = 0;
    do {
        bytes = TEMP_FAILURE_RETRY_2(sendto(handle->iSocket, &aBuffer[sent], aBytes-sent, MSG_NOSIGNAL, &addr, sizeof(addr)), handle);
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

    fd_set read;
    fd_set error;
    int32_t selectErr;

    while(1) 
    {
        FD_ZERO(&read);
        FD_SET(handle->iPipe[0], &read);
        FD_SET(handle->iSocket, &read);
        FD_ZERO(&error);
        FD_SET(handle->iSocket, &error);

        selectErr = (long int) select(nfds(handle), &read, NULL, &error, NULL);

        if (selectErr < 0) {
            // We've been interupted or something has gone wrong with select()
            // Don't continue trying and exit our loop. 
            if (errno != EINTR || SocketInterrupted(handle)) {
                break;
            }
        }
        else {
            // By now we either have a data ready to read, the socket itself
            // has errors, or we've been interupted. 
            break;
        }
    }


    int32_t received = -1;
    if (selectErr != -1) {
        received = FD_ISSET(handle->iSocket, &read) ? TEMP_FAILURE_RETRY_2(recv(handle->iSocket, aBuffer, aBytes, MSG_NOSIGNAL), handle)
                                                    : -1; //Assuming it was the pipe or an error
    }

    return received;
}

int32_t OsNetworkReceiveFrom(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes, TIpAddress* aAddress, uint16_t* aPort)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (SocketInterrupted(handle)) {
        return -1;
    }
    struct sockaddr addr;
    socklen_t addrLen = sizeof(addr);

    fd_set read;
    fd_set error;
    int32_t selectErr;

    while(1) 
    {
        FD_ZERO(&read);
        FD_SET(handle->iPipe[0], &read);
        FD_SET(handle->iSocket, &read);
        FD_ZERO(&error);
        FD_SET(handle->iSocket, &error);

        selectErr = (long int) select(nfds(handle), &read, NULL, &error, NULL);

        if (selectErr < 0) {
            // We've been interupted or something has gone wrong with select()
            // Don't continue trying and exit our loop. 
            if (errno != EINTR || SocketInterrupted(handle)) {
                break;
            }
        }
        else {
            // By now we either have data ready to read, the socket itself
            // has errors, or we've been interupted. 
            break;
        }
    }


    int32_t received = -1;
    if (selectErr != -1) {
        received = FD_ISSET(handle->iSocket, &read) ? TEMP_FAILURE_RETRY_2(recvfrom(handle->iSocket, aBuffer, aBytes, MSG_NOSIGNAL, (struct sockaddr*)&addr, &addrLen), handle)
                                                    : -1; //Assuming it was the pipe or an error 
    }

    *aAddress = TIpAddressFromSockAddr(&addr);
    *aPort = PortFromSockAddr(&addr);
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
    *aClientAddress = kIpAddressV4AllAdapters;
    *aClientPort = 0;
    if (SocketInterrupted(handle)) {
        return kHandleNull;
    }
    struct sockaddr addr;
    socklen_t len = sizeof(addr);

    /* accept() in O_NONBLOCK mode will constantly return an error of
     * EWOULDBLOCK / EAGAIN until there is a pending connection in the
     * queue. Calling select() on an O_NONBLOCK socket will also return
     * instantly with EWOULDBLOCK / EAGAIN.
     * More details can be found in accept() man pages.
     *
     * It is therefore more efficient to use a standard blocking call
     * to select() to wait until work is ready. This can be either:
     *  - A client is ready to connect, calling accept() would be good
     *  - We've been interupted and should return.
     *
     * Otherwise, we end up looping around and eating CPU time until
     * there is a client ready to connect. */
    fd_set read;
    fd_set error;
    int32_t h = 0;

    while(1) 
    {
        FD_ZERO(&read);
        FD_SET(handle->iPipe[0], &read);
        FD_SET(handle->iSocket, &read);
        FD_ZERO(&error);
        FD_SET(handle->iSocket, &error);

        // NOTE: If select() returns an error we should not assume that
        //       any fd_set is left in a valid state (even with EINTR)
        h = (long int) select(nfds(handle), &read, NULL, &error, NULL);

        if (h < 0) {
            // We've been interupted or something has gone wrong with select()
            // Don't continue trying and exit our loop. 
            if (errno != EINTR || SocketInterrupted(handle)) {
                break;
            }
        }
        else {
            // By now we either have a pending connection, the socket itself
            // has errors, or we've been interupted. 
            break;
        }
    }


    // If all is well and the socket is ready to read, we can assume that
    // a client is waiting to connect. Otherwise, we were interupted and
    // so shouldn't call accept().
    if (h != -1) {
        h = FD_ISSET(handle->iSocket, &read) ? TEMP_FAILURE_RETRY_2(accept(handle->iSocket, &addr, &len), handle)
                                             : -1; //Assuming it was the pipe or an error, so use indicate this here. 
    }

    // If select() has failed, our socket wasn't readable or something
    // has gone wrong with accept()...
    if (h == -1) {
        return kHandleNull;
    }

    OsNetworkHandle* newHandle = CreateHandle(handle->iCtx, h);
    if (newHandle == NULL) {
        close(h);
        return kHandleNull;
    }

    // Helper functions determine protocol family (IPv4/v6)
    *aClientAddress = TIpAddressFromSockAddr(&addr);
    *aClientPort = PortFromSockAddr(&addr);
    return (THandle)newHandle;
}

int32_t OsNetworkGetHostByName(const char* aAddress, TIpAddress* aHost)
{
    struct addrinfo *res;
    if (getaddrinfo(aAddress, NULL, NULL, &res) == 0) {
        // Helper function determines protocol family (IPv4/v6)
        *aHost = TIpAddressFromSockAddr(res->ai_addr);
        freeaddrinfo(res);
        return 0;
    }

#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD) && !defined(__ANDROID__)
    // getaddrinfo() failed, possibly because configuration is stale and configuration files need to be re-read.
    // Try re-read configuration files.
    if (res_init() == 0) {
        // Configuration files were re-read. Try getaddrinfo() again.
        if (getaddrinfo(aAddress, NULL, NULL, &res) == 0) {
            // Helper function determines protocol family (IPv4/v6)
            *aHost = TIpAddressFromSockAddr(res->ai_addr);
            freeaddrinfo(res);
            return 0;
        }
    }
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_FREEBSD && !defined(__ANDROID__) */

    *aHost = kIpAddressV4AllAdapters;
    return -1;
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
#ifndef SO_REUSEPORT
# define SO_REUSEPORT 15
#endif
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t reuseaddr = 1;
    int32_t err = setsockopt(handle->iSocket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
    if (err == 0) {
        /* ignore errors from SO_REUSEPORT - some platforms don't support it */
        (void)setsockopt(handle->iSocket, SOL_SOCKET, SO_REUSEPORT, &reuseaddr, sizeof(reuseaddr));
    }
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

    // Check for IPv6, default to IPv4
    if (aInterface.iFamily == kFamilyV6) {
        struct ipv6_mreq mreq;
        in6AddrFromTIpAddress((struct in6_addr*)&mreq.ipv6mr_multiaddr, &aAddress);
        in6AddrFromTIpAddress((struct in6_addr*)&mreq.ipv6mr_interface, &aInterface);
        err = setsockopt(handle->iSocket, IPPROTO_IPV6, IP_ADD_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));
    }
    else {
        struct ip_mreq mreq;
        mreq.imr_multiaddr.s_addr = aAddress.iV4;
        mreq.imr_interface.s_addr = aInterface.iV4;
        err = setsockopt(handle->iSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));
    }

    if (err != 0) {
        return err;
    }
    
    loop = 0;
    int level = (aInterface.iFamily == kFamilyV6) ? IPPROTO_IPV6 : IPPROTO_IP;
    err = setsockopt(handle->iSocket, level, IP_MULTICAST_LOOP, &loop, sizeof(loop));
    
    return err;
}

int32_t OsNetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;

    // Check for IPv6, default to IPv4
    if (aInterface.iFamily == kFamilyV6) {
        struct ipv6_mreq mreq;
        in6AddrFromTIpAddress((struct in6_addr*)&mreq.ipv6mr_multiaddr, &aAddress);
        in6AddrFromTIpAddress((struct in6_addr*)&mreq.ipv6mr_interface, &aInterface);
        err = setsockopt(handle->iSocket, IPPROTO_IPV6, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    }
    else {
        struct ip_mreq mreq;
        mreq.imr_multiaddr.s_addr = aAddress.iV4;
        mreq.imr_interface.s_addr = aInterface.iV4;
        err = setsockopt(handle->iSocket, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    }
    return err;
}
 
int32_t OsNetworkSocketSetMulticastIf(THandle aHandle, TIpAddress aInterface)
{
#if defined(PLATFORM_MACOSX_GNU) || defined(PLATFORM_FREEBSD)
    int err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;

    if (aInterface.iFamily == kFamilyV6) {
        err = setsockopt(handle->iSocket, IPPROTO_IPV6, IP_MULTICAST_IF, &aInterface.iV6, sizeof(aInterface));
    }
    else {
        err = setsockopt(handle->iSocket, IPPROTO_IP, IP_MULTICAST_IF, &aInterface.iV4, sizeof(aInterface));
    }
    return err;
#else
    return 0;
#endif
}

static int32_t isWireless(const char* ifname, int domain)
{
#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_QNAP)
    int sock = -1;
    int err;
    struct iwreq pwrq;
    memset(&pwrq, 0, sizeof(pwrq));
    strncpy(pwrq.ifr_name, ifname, IFNAMSIZ);

    if ((sock = socket(domain, SOCK_STREAM, 0)) == -1) {
        return 0;
    }

    err = ioctl(sock, SIOCGIWNAME, &pwrq);
    close(sock);
    return err == 0 ? 1 : 0;
#else
    return 0;
#endif /* !PLATFORM_MACOSX_GNU && !PLATFORM_QNAP */
}

static int32_t TIpAddressesAreEqual(const TIpAddress* aAddr1, const TIpAddress* aAddr2)
{
    if ((aAddr1->iFamily == aAddr2->iFamily) &&
       ((aAddr1->iFamily == kFamilyV6 && (aAddr1->iV6 == aAddr2->iV6)) ||
        (aAddr1->iFamily == kFamilyV4 && (aAddr1->iV4 == aAddr2->iV4)))) {
        return 1;
    }
    return 0;
}

static int32_t NetMasksAreEqual(const TIpAddress* aAddr1, const TIpAddress* aAddr2)
{
    if (aAddr1->iFamily != aAddr2->iFamily) {
        return 0;
    }

    if (aAddr1->iFamily == kFamilyV6) {
        for (uint8_t i = 0; i < 16; i++) {
            if ((aAddr1->iV6[i] & aAddr2->iV6[i]) != aAddr1->iV6[i]) {
                return 0;
            }
        }
        return 1;
    }
    else {
        return ((aAddr1->iV4 & aAddr2->iV4) == aAddr1->iV4);
    }
    return 0;
}

static int32_t isLoopback(struct sockaddr* aInterface)
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

    uint32_t loopbackAddrV4 = MakeIpAddress(127, 0, 0, 1);

    if (aInterface->sa_family == AF_INET6) {
        return IN6_IS_ADDR_LOOPBACK(&((struct sockaddr_in6*)aInterface)->sin6_addr);
    }
    else {
        return (((struct sockaddr_in*)aInterface)->sin_addr.s_addr == loopbackAddrV4);
    }
}

static void append(OsNetworkAdapter* aAdapter, OsNetworkAdapter** aHead, OsNetworkAdapter** aTail)
{
    if (*aHead == NULL) {
        *aHead = aAdapter;
    }
    else {
        (*aTail)->iNext = aAdapter;
    }
    *aTail = aAdapter;
}

int32_t OsNetworkListAdapters(OsContext* aContext, OsNetworkAdapter** aAdapters, uint32_t aUseLoopback)
{
    int32_t ret = -1;
    struct ifaddrs* networkIf;
    struct ifaddrs* iter;
    int32_t includeLoopback = 1;
    *aAdapters = NULL;
    if (TEMP_FAILURE_RETRY(getifaddrs(&networkIf)) == -1) {
        return -1;
    }

    /* first check whether we have any suitable interfaces other than loopback */
    if (aUseLoopback == 0) {
        iter = networkIf;
        while (iter != NULL) {
            if (iter->ifa_addr != NULL &&
                (iter->ifa_flags & IFF_RUNNING) != 0) {
                
                // isLoopback determines protocol family (v4/v6)
                if (iter->ifa_addr->sa_family == AF_INET && !isLoopback(iter->ifa_addr)) {
                    includeLoopback = 0;
                    break;
                }
#if !defined(PLATFORM_MACOSX_GNU)
                else if (iter->ifa_addr->sa_family == AF_INET6 && !isLoopback(iter->ifa_addr)) {
                    includeLoopback = 0;
                    break;
                }
#endif
            }
            iter = iter->ifa_next;
        }
    }

    OsNetworkAdapter* head = NULL;
    OsNetworkAdapter* wiredHead = NULL;
    OsNetworkAdapter* wiredTail = NULL;
    OsNetworkAdapter* wirelessHead = NULL;
    OsNetworkAdapter* wirelessTail = NULL;
    OsNetworkAdapter* loopHead = NULL;      /* List of loopback adapters */
    OsNetworkAdapter* loopTail = NULL;

    for (iter = networkIf; iter != NULL; iter = iter->ifa_next) {

        if (iter->ifa_addr == NULL) {
            continue;
        }
        const int ifaceIsWireless = isWireless(iter->ifa_name, iter->ifa_addr->sa_family);
        const int ifaceIsLoopback = isLoopback(iter->ifa_addr);

#if !defined(PLATFORM_MACOSX_GNU)
        const uint8_t familyIsValid = (iter->ifa_addr->sa_family == AF_INET || iter->ifa_addr->sa_family == AF_INET6);
#else
        // Omit IPv6 adapters on macOS platforms
        const uint8_t familyIsValid = (iter->ifa_addr->sa_family == AF_INET);
#endif
        if (!familyIsValid ||
            (iter->ifa_flags & IFF_RUNNING) == 0 ||
            (includeLoopback == 0 && ifaceIsLoopback == 1) ||
            (aUseLoopback == 1    && ifaceIsLoopback == 0)) {

#if !defined(PLATFORM_MACOSX_GNU)
            if (iter->ifa_addr->sa_family != AF_INET6) {
                continue;
            }
#endif
            continue;
        }

        OsNetworkAdapter* iface = (OsNetworkAdapter*)calloc(1, sizeof(*iface));
        if (iface != NULL) {
            iface->iName = (char*)malloc(strlen(iter->ifa_name) + 1);
        }
        if (iface == NULL || iface->iName == NULL) {
            OsNetworkFreeInterfaces(wiredHead);
            OsNetworkFreeInterfaces(wirelessHead);
            OsNetworkFreeInterfaces(loopHead);
            goto exit;
        }

        if (ifaceIsLoopback) {
            append(iface, &loopHead, &loopTail);
        }
        else if (ifaceIsWireless) {
            append(iface, &wirelessHead, &wirelessTail);
        }
        else { // wired, non-loopback
            append(iface, &wiredHead, &wiredTail);
        }

        (void)strcpy(iface->iName, iter->ifa_name);
        // Helper functions handle Ipv4 and v6 addresses
        iface->iAddress = TIpAddressFromSockAddr(iter->ifa_addr);
        iface->iNetMask = TIpAddressFromSockAddr(iter->ifa_netmask);
        iface->iReserved = ifaceIsWireless;
    }

    // List wired before wireless, wireless before loopback
    OsNetworkAdapter* tail = NULL;
    head = wiredHead;
    tail = wiredTail;
    if (head == NULL) {
        head = wirelessHead;
        tail = wirelessTail;
    }
    else if (wirelessHead != NULL) {
        tail->iNext = wirelessHead;
        tail = wirelessTail;
    }
    if (head == NULL) {
        head = loopHead;
        tail = loopTail;
    }
    else if (loopHead != NULL) {
        tail->iNext = loopHead;
        tail = loopTail;
    }

    // Check for multiple entries with same address and different netmasks and
    // remove all these except for the least specific (largest superset) netmask.
    // This code would also work if there are repeated identical address/netmask pairs.
    OsNetworkAdapter* ifacePrevious = NULL;
    // outer loop: for each adapter, remove it if another adapter takes priority
    OsNetworkAdapter* ifaceIter = head;
    while (ifaceIter != NULL) {
        int removeIface = 1; // false
        // inner loop: check other adapters (not ifaceIter) for priority
        OsNetworkAdapter* addrsIter = head;
        while (addrsIter != NULL) {
            // Helper functions distinguish between IPv4 and v6
            if (addrsIter != ifaceIter &&
                TIpAddressesAreEqual(&addrsIter->iAddress, &ifaceIter->iAddress) &&
                NetMasksAreEqual(&addrsIter->iNetMask, &ifaceIter->iNetMask)) { // Order of arguments is important here

                removeIface = 0; // true
                break;
            }
            addrsIter = addrsIter->iNext;
        }
        if (removeIface == 0) {
            OsNetworkAdapter* ifaceNext = ifaceIter->iNext;
            if (ifaceIter == head) {
                head = ifaceNext;
            }
            else {
                ifacePrevious->iNext = ifaceNext;
            }
            free(ifaceIter->iName);
            free(ifaceIter);
            ifaceIter = ifaceNext;
            // don't update ifacePrevious
        }
        else {
            ifacePrevious = ifaceIter;
            ifaceIter = ifaceIter->iNext;
        }
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

#if !defined(PLATFORM_FREEBSD)

static int32_t ThreadJoin(THandle aThread)
{
    ThreadData* data = (ThreadData*) aThread;
    int status = pthread_join(data->iThread, NULL);
    return (status==0 ? 0 : -1);
}

#endif /* !PLATFORM_FREEBSD */

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

        do {
            FD_ZERO(&rfds);
            FD_SET(handle->iPipe[0], &rfds);
            FD_SET(handle->iSocket, &rfds);
            FD_ZERO(&errfds);
            FD_SET(handle->iSocket, &errfds);
            ret = (long int) select(nfds(handle), &rfds, NULL, &errfds, NULL);
        } while(ret == -1L && errno == EINTR && !SocketInterrupted(handle));

        if ((ret > 0) && FD_ISSET(handle->iSocket, &rfds)) {
            nlh = (struct nlmsghdr *) buffer;
            if ((len = recv(handle->iSocket, nlh, 4096, 0)) > 0) {
                while (NLMSG_OK(nlh, len) && (nlh->nlmsg_type != NLMSG_DONE)) {
                    if (nlh->nlmsg_type == RTM_NEWADDR || 
                        nlh->nlmsg_type == RTM_DELADDR || 
                        nlh->nlmsg_type == RTM_NEWLINK) {

#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD) && !defined(__ANDROID__)
                        // Adapter change; speculatively attempt to reload resolver configuration.
                        (void)res_init();
#endif /* !PLATFORM_MACOSX_GNU  && !PLATFORM_FREEBSD && !defined(__ANDROID__) */

                        observer->iCallback(observer->iArg);
                    }

                    nlh = NLMSG_NEXT(nlh, len);
                }
            }
        }
    }
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


#if !defined(PLATFORM_MACOSX_GNU) && !defined(PLATFORM_FREEBSD) && !defined(__ANDROID__)

void DnsRefreshThread(void* aPtr)
{
    /*
     * glibc prior to 2.26 only reads in resolv.conf at startup.
     *
     * The result is that a resolv.conf which does not contain suitable entries
     * for ohNet's use may be read in and will persist for the lifetime of the
     * ohNet stack.
     *
     * This will manifest itself as calls to getaddrinfo() failing.
     *
     * To work around the above issue, manually watch for changes in
     * resolv.conf and trigger res_init() to force glibc to reload resolv.conf.
     */
    OsContext* ctx = (OsContext*)aPtr;
    DnsRefresher* dnsRefresh = ctx->iDnsRefresh;
    OsNetworkHandle* handle = (OsNetworkHandle*)dnsRefresh->iHandle;
    const int watchDesc = inotify_add_watch(handle->iSocket, "/etc/resolv.conf", IN_CLOSE_WRITE);

    if (watchDesc != -1) {
        // Watch descriptor was successfully created; start reading events.
        const size_t bytesToRead = sizeof(struct inotify_event) + NAME_MAX + 1;
        int32_t ret;
        fd_set rfds, errfds;

        for (;;) {
            if (SocketInterrupted(handle)) {
                // Quitting. Remove watcher.
                (void)inotify_rm_watch(handle->iSocket, watchDesc);
                return;
            }

            do {
                FD_ZERO(&rfds);
                FD_SET(handle->iPipe[0], &rfds);
                FD_SET(handle->iSocket, &rfds);
                FD_ZERO(&errfds);
                FD_SET(handle->iSocket, &errfds);
                ret = (long int) select(nfds(handle), &rfds, NULL, &errfds, NULL);
            } while(ret == -1L && errno == EINTR && !SocketInterrupted(handle));

            if ((ret > 0) && FD_ISSET(handle->iSocket, &rfds)) {
                char* buffer[bytesToRead];
                int32_t len = read(handle->iSocket, buffer, bytesToRead);
                if (len > 0) {
                    // Only one watcher. If len > 0, assume message is from that single watcher.
                    res_init();
                    OsMutexLock(ctx->iMutex);
                    if (dnsRefresh->iCallback != NULL) {
                        dnsRefresh->iCallback(dnsRefresh->iCallbackArg);
                    }
                    OsMutexUnlock(ctx->iMutex);
                }
            }
        }
    }
}

static void DnsRefreshCreate(OsContext* aContext)
{
    assert(aContext != NULL);
    uint32_t minPrio, maxPrio;
    OsThreadGetPriorityRange(aContext, &minPrio, &maxPrio);

    assert(aContext->iDnsRefresh == NULL);
    aContext->iDnsRefresh = calloc(1, sizeof *aContext->iDnsRefresh);

    const int32_t fd = inotify_init();
    if (fd != -1) {
        OsNetworkHandle* handle = CreateHandle(aContext, fd);
        if (handle != NULL) {
            aContext->iDnsRefresh->iHandle = handle;
            aContext->iDnsRefresh->iThread = DoThreadCreate(aContext,
                                                            "DnsRefreshThread",
                                                            (maxPrio - minPrio) / 2,   // Same as adapterChangeObserverThread
                                                            16 * 1024,                 // Same as adapterChangeObserverThread
                                                            1,                         // Joinable
                                                            DnsRefreshThread,
                                                            aContext);
        }
        else {
            close(fd);
        }
    }
}

static void DnsRefreshDestroy(OsContext* aContext)
{
    assert(aContext != NULL);
    if (aContext->iDnsRefresh == NULL) {
        return;
    }
    if (aContext->iDnsRefresh->iThread != NULL) {
        OsNetworkInterrupt(aContext->iDnsRefresh->iHandle, 1);
        ThreadJoin(aContext->iDnsRefresh->iThread);
        OsThreadDestroy(aContext->iDnsRefresh->iThread);
    }
    OsNetworkClose(aContext->iDnsRefresh->iHandle);
    free(aContext->iDnsRefresh);
}

#endif /* !PLATFORM_MACOSX_GNU  && !PLATFORM_FREEBSD && !defined(__ANDROID__) */

#ifdef PLATFORM_MACOSX_GNU
#ifndef PLATFORM_IOS

// macOS doesn't handle timed waits correctly after sleep/wake.
// Work around this problem by registering for wake notifications and signalling
// all semaphores that are currently in a timed wait.

void SleepWakeCallback(void* aPtr, io_service_t service, natural_t messageType, void* messageArgument)
{
    OsContext* ctx = (OsContext*)aPtr;
    SleepWake* sleepWake = ctx->iSleepWake;

    switch (messageType) {

        case kIOMessageCanSystemSleep:
            Debug("SleepWakeCallback: received kIOMessageCanSystemSleep\n");

            /* Idle sleep is about to kick in. This message will not be sent for forced sleep.
                Applications have a chance to prevent sleep by calling IOCancelPowerChange.
                Most applications should not prevent idle sleep.

                Power Management waits up to 30 seconds for you to either allow or deny idle
                sleep. If you don't acknowledge this power change by calling either
                IOAllowPowerChange or IOCancelPowerChange, the system will wait 30
                seconds then go to sleep.
            */

            //Uncomment to cancel idle sleep
            //IOCancelPowerChange(sleepWake->iRootPort, (long)messageArgument);

            // we will allow idle sleep
            IOAllowPowerChange(sleepWake->iRootPort, (long)messageArgument);
            break;

        case kIOMessageSystemWillSleep:
            Debug("SleepWakeCallback: received kIOMessageSystemWillSleep\n");

            /* The system WILL go to sleep. If you do not call IOAllowPowerChange or
                IOCancelPowerChange to acknowledge this message, sleep will be
                delayed by 30 seconds.

                NOTE: If you call IOCancelPowerChange to deny sleep it returns
                kIOReturnSuccess, however the system WILL still go to sleep.
            */

            IOAllowPowerChange(sleepWake->iRootPort, (long)messageArgument);
            break;

        case kIOMessageSystemWillPowerOn:
            // System has started the wake up process...
            Debug("SleepWakeCallback: received kIOMessageSystemWillPowerOn\n");
            break;

        case kIOMessageSystemHasPoweredOn:
            // System has finished waking up...
            Debug("SleepWakeCallback: received kIOMessageSystemHasPoweredOn\n");

            // signal all semaphores on the timed wait list
            // OsSemaphoreTimedWait will start a new wait if the deadline has not yet passed 
            OsMutexLock(ctx->iMutex);
            for (SemaphoreData* data = sleepWake->iTimedWaits; data != NULL; data = data->iNext) {
                Debug("SleepWakeCallback: signalling semaphore %p on timed wait list\n", data);
                pthread_mutex_lock(&data->iLock);
                pthread_cond_signal(&data->iCond);
                pthread_mutex_unlock(&data->iLock);
            }
            OsMutexUnlock(ctx->iMutex);
            break;

        default:
            Debug("SleepWakeCallback: messageType %08lx, arg %08lx\n",
                  (long unsigned int)messageType,
                  (long unsigned int)messageArgument);
            break;
    }
}

static void SleepWakeThread(void* aPtr)
{
    Debug("SleepWakeThread: starting\n");
    OsContext* ctx = (OsContext*)aPtr;
    SleepWake* sleepWake = ctx->iSleepWake;
    sleepWake->iRunLoop = CFRunLoopGetCurrent();

    // register to receive system sleep notifications
    sleepWake->iRootPort = IORegisterForSystemPower(aPtr, &sleepWake->iNotifyPortRef, SleepWakeCallback, &sleepWake->iNotifierObject);
    if (sleepWake->iRootPort == MACH_PORT_NULL) {
        Debug("SleepWakeThread: IORegisterForSystemPower error\n");
        return;
    }

    // add the notification port to the application RunLoop
    CFRunLoopAddSource(sleepWake->iRunLoop, IONotificationPortGetRunLoopSource(sleepWake->iNotifyPortRef), kCFRunLoopCommonModes);

    // start the RunLoop to receive sleep notifications
    CFRunLoopRun();

    // CFRunLoopRun doesn't return until CFRunLoopStop is called
}

static void SleepWakeCreate(OsContext* aContext)
{
    Debug("SleepWakeCreate: starting\n");
    assert(aContext != NULL);
    uint32_t minPrio, maxPrio;
    OsThreadGetPriorityRange(aContext, &minPrio, &maxPrio);

    assert(aContext->iSleepWake == NULL);
    aContext->iSleepWake = calloc(1, sizeof *aContext->iSleepWake);

    aContext->iSleepWake->iThread = DoThreadCreate(aContext,
                                                    "SleepWakeThread",
                                                    (maxPrio - minPrio) / 2,   // Same as adapterChangeObserverThread
                                                    16 * 1024,                 // Same as adapterChangeObserverThread
                                                    1,                         // Joinable
                                                    SleepWakeThread,
                                                    aContext);
}

static void SleepWakeDestroy(OsContext* aContext)
{
    Debug("SleepWakeDestroy: starting\n");
    assert(aContext != NULL);
    if (aContext->iSleepWake == NULL) {
        return;
    }
    SleepWake* sleepWake = aContext->iSleepWake;

    /* When testing, the startup and teardown of this context
     * can happen very quickly and the CFRunLoop doesn't have
     * a suitable amount of time to get started and populate
     * our 'iNotifyPortRef' value.
     *
     * Under normal operation this should never spin, but in 
     * order to allow tests to run correctly we'll spinwait 
     * a short while to let things get going in the runloop.
     *
     * If by the of the spinwait we still don't have a notify
     * port ref we'll just cleanup as much as possible and
     * assume the OS will tidyup the rest once the program
     * exists! */
    for(int i = 0; i < 50; ++i)
    {
        if (sleepWake->iNotifyPortRef != NULL)
            break;

        sleep(0.75);
    }

    Debug("SleepWakeDestory [WARN]: iNotifyPortRef is still NULL after spinwait. Certain teardown operations wont be run.\n");

    if (sleepWake->iNotifyPortRef != NULL)
    {
        // remove the sleep notification port from the application runloop
        Debug("SleepWakeDestroy: calling CFRunLoopRemoveSource\n");
        CFRunLoopRemoveSource(sleepWake->iRunLoop,
                              IONotificationPortGetRunLoopSource(sleepWake->iNotifyPortRef),
                              kCFRunLoopCommonModes);
    }
    else
    {
        Debug("SleepWakeDestroy: [WARN] Skipping CFRunLoopRemoveSource\n");
    }

    // deregister for system sleep notifications
    Debug("SleepWakeDestroy: calling IODeregisterForSystemPower\n");
    IOReturn ioStatus = IODeregisterForSystemPower(&sleepWake->iNotifierObject);
    if (ioStatus != kIOReturnSuccess) {
        Debug("SleepWakeDestroy: IODeregisterForSystemPower error return %d\n", ioStatus);
    }

    // IORegisterForSystemPower implicitly opens the Root Power Domain IOService
    // so we close it here
    Debug("SleepWakeDestroy: calling IOServiceClose\n");
    kern_return_t kernStatus = IOServiceClose(sleepWake->iRootPort);
    if (ioStatus != KERN_SUCCESS) {
        Debug("SleepWakeDestroy: IOServiceClose error return %d\n", kernStatus);
    }

    if (sleepWake->iNotifyPortRef != NULL)
    {
        // destroy the notification port allocated by IORegisterForSystemPower
        Debug("SleepWakeDestroy: calling IONotificationPortDestroy\n");
        IONotificationPortDestroy(sleepWake->iNotifyPortRef);
    }
    else
    {
        Debug("SleepWakeDestroy: [WARN] Skipping IONotificationPortDestroy\n");
    }


    if (sleepWake->iThread != NULL) {
        Debug("SleepWakeDestroy: calling CFRunLoopStop\n");
        CFRunLoopStop(sleepWake->iRunLoop);
        Debug("SleepWakeDestroy: calling ThreadJoin\n");
        ThreadJoin(sleepWake->iThread);
        Debug("SleepWakeDestroy: calling OsThreadDestroy\n");
        OsThreadDestroy(sleepWake->iThread);
    }
    free(aContext->iSleepWake);
}

#endif /* !PLATFORM_IOS */
#endif /* PLATFORM_MACOSX_GNU */

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
#else /* !PLATFORM_MACOSX_GNU */
    SetInterfaceChangedObserver_Linux(aContext, aCallback, aArg);
#endif /* PLATFORM_MACOSX_GNU */
}

void OsNetworkSetDnsChangedObserver(OsContext* aContext, DnsChanged aCallback, void* aArg)
{
    assert(aContext != NULL);
    if (aContext->iDnsRefresh == NULL) {
        return;
    }
    OsMutexLock(aContext->iMutex);
    aContext->iDnsRefresh->iCallback = aCallback;
    aContext->iDnsRefresh->iCallbackArg = aArg;
    OsMutexUnlock(aContext->iMutex);
}
