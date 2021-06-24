// Implementation of Os.h APIs for Windows

#include <OpenHome/Os.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <Windows.h>

#ifdef DEFINE_WINDOWS_UNIVERSAL
#include <Processthreadsapi.h>
#include <Synchapi.h>
#include <algorithm>
#include "collection.h"
using namespace Platform;
using namespace Windows;
using namespace Windows::Networking;
using namespace Windows::Networking::Connectivity;
using namespace Windows::Foundation::Collections;

#define InitializeCriticalSection(arg0) InitializeCriticalSectionEx(arg0, 0, 0)
#define WaitForSingleObject(arg0, arg1) WaitForSingleObjectEx(arg0, arg1, false)
#define M_CreateSemaphore(arg0, arg1, arg2, arg3) CreateSemaphoreEx(arg0, arg1, arg2, arg3, 0, (SYNCHRONIZE | SEMAPHORE_MODIFY_STATE))
#define M_CreateEvent(arg0, arg1, arg2, arg3) CreateEventEx(arg0, arg3, 0 | (arg1 ? CREATE_EVENT_MANUAL_RESET : 0) | (arg2 ? CREATE_EVENT_INITIAL_SET : 0), (SYNCHRONIZE | EVENT_MODIFY_STATE))

#define TlsAlloc() FlsAlloc(NULL)
#define TlsFree(arg0) FlsFree(arg0)
#define TlsSetValue(arg0, arg1) FlsSetValue(arg0, arg1)
#define TlsGetValue(arg0) FlsGetValue(arg0)

#else
#include <Iphlpapi.h>
#include <Dbghelp.h>
#define M_CreateSemaphore(arg0, arg1, arg2, arg3) CreateSemaphore(arg0, arg1, arg2, arg3)
#define M_CreateEvent(arg0, arg1, arg2, arg3) CreateEvent(arg0, arg1, arg2, arg3)
#endif

static const uint32_t kMinStackBytes = 1024 * 16;
static const uint32_t kStackPaddingBytes = 1024 * 16;
static const uint32_t kPriorityMin = 0;
static const uint32_t kPriorityMax = (uint32_t)(THREAD_PRIORITY_TIME_CRITICAL - THREAD_PRIORITY_IDLE);

#define UNUSED(a) (a) = (a)

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

typedef struct OsContext {
    uint64_t iStartTime; /* Time OsCreate was called */
    uint64_t iPrevTime; /* Last time OsTimeInUs() was called */
    uint64_t iTimeAdjustment; /* Amount to adjust return for OsTimeInUs() by. 
                                 Will be 0 unless time ever jumps backwards. */
    DWORD iTlsIndex;
    THandle iMutex;
    InterfaceChangeObserver* iInterfaceChangeObserver;
    int32_t iTestInterfaceIndex;
    HANDLE iDebugSymbolHandle;
} OsContext;


OsContext* OsCreate(OsThreadSchedulePolicy aSchedulerPolicy)
{
    FILETIME ft;
    WSADATA wsaData;
    WORD ver = (2<<8)|2; // WinSock v2.2.  Standard on XP and later

#ifndef DEFINE_WINDOWS_UNIVERSAL
    char* noErrDlgs = getenv("OHNET_NO_ERROR_DIALOGS");
    OsContext* ctx = malloc(sizeof(*ctx));
    if (noErrDlgs != NULL && strcmp(noErrDlgs, "1") == 0) {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
#else
    OsContext* ctx = (OsContext*)malloc(sizeof(*ctx));
#endif
    UNUSED(aSchedulerPolicy);
    if (ctx == NULL) {
        return NULL;
    }

    ctx->iInterfaceChangeObserver = NULL;
    ctx->iTestInterfaceIndex = -1;

    GetSystemTimeAsFileTime(&ft);
    ctx->iStartTime = ft.dwHighDateTime;
    ctx->iStartTime <<= 32;
    ctx->iStartTime |= ft.dwLowDateTime;
    ctx->iPrevTime = 0;
    ctx->iTimeAdjustment = 0;

    ctx->iTlsIndex = TlsAlloc();
    if (TLS_OUT_OF_INDEXES == ctx->iTlsIndex) {
        free(ctx);
        return NULL;
    }
    ctx->iMutex = OsMutexCreate(ctx, "");
    if (kHandleNull == ctx->iMutex) {
        TlsFree(ctx->iTlsIndex);
        free(ctx);
        return NULL;
    }
    if (0 != WSAStartup(ver, &wsaData)) {
        OsMutexDestroy(ctx->iMutex);
        TlsFree(ctx->iTlsIndex);
        free(ctx);
        return NULL;
    }
    {
#ifndef DEFINE_WINDOWS_UNIVERSAL
        HMODULE hModule = GetModuleHandle(NULL);
        CHAR path[MAX_PATH];
        GetModuleFileName(hModule, path, MAX_PATH);
        ctx->iDebugSymbolHandle = GetCurrentProcess();
        SymSetOptions(SYMOPT_FAIL_CRITICAL_ERRORS);
        (void)SymInitialize(ctx->iDebugSymbolHandle, /*NULL*/path, TRUE);
#endif
    }

    return ctx;
}

void OsDestroy(OsContext* aContext)
{
    if (aContext == NULL) {
        return;
    }

#ifndef DEFINE_WINDOWS_UNIVERSAL
    (void)SymCleanup(aContext->iDebugSymbolHandle);
#endif

    if (NULL != aContext->iInterfaceChangeObserver) {
        aContext->iInterfaceChangeObserver->iShutdown = 1;
        (void)WSASetEvent(aContext->iInterfaceChangeObserver->iShutdownEvent);
        (void)WaitForSingleObject(aContext->iInterfaceChangeObserver->iSem, INFINITE);
        CloseHandle(aContext->iInterfaceChangeObserver->iSem);
        WSACloseEvent(aContext->iInterfaceChangeObserver->iEvent);
        WSACloseEvent(aContext->iInterfaceChangeObserver->iShutdownEvent);
        (void)closesocket(aContext->iInterfaceChangeObserver->iSocket);
        free(aContext->iInterfaceChangeObserver);
        aContext->iInterfaceChangeObserver = NULL;
    }
    (void)WSACleanup();
    OsMutexDestroy(aContext->iMutex);
    aContext->iMutex = kHandleNull;
    TlsFree(aContext->iTlsIndex);
    free(aContext);
}

void OsQuit(OsContext* aContext)
{
    UNUSED(aContext);
    abort();
}


#ifdef DEFINE_WINDOWS_UNIVERSAL
typedef struct _SYMBOL_INFO {
  ULONG   SizeOfStruct;
  ULONG   TypeIndex;
  ULONG64 Reserved[2];
  ULONG   Index;
  ULONG   Size;
  ULONG64 ModBase;
  ULONG   Flags;
  ULONG64 Value;
  ULONG64 Address;
  ULONG   Register;
  ULONG   Scope;
  ULONG   Tag;
  ULONG   NameLen;
  ULONG   MaxNameLen;
  TCHAR   Name[1];
} SYMBOL_INFO, *PSYMBOL_INFO;
#endif

#define STACK_TRACE_MAX_DEPTH 32
typedef struct OsStackTrace
{
    void* iStack[STACK_TRACE_MAX_DEPTH];
    USHORT iCount;
    SYMBOL_INFO* iSymbol;
    OsContext* iOsContext;
} OsStackTrace;

#ifndef DEFINE_WINDOWS_UNIVERSAL
#define STACK_TRACE_ENABLE
#endif

THandle OsStackTraceInitialise(OsContext* aContext)
{
    OsStackTrace* stackTrace = (OsStackTrace*)calloc(sizeof(OsStackTrace), 1);
#ifdef STACK_TRACE_ENABLE
    if (stackTrace == NULL) {
        return kHandleNull;
    }
    stackTrace->iCount = CaptureStackBackTrace(4, STACK_TRACE_MAX_DEPTH, stackTrace->iStack, NULL);
#endif /* STACK_TRACE_ENABLE */
    stackTrace->iOsContext = aContext;
    return stackTrace;
}

THandle OsStackTraceCopy(THandle aStackTrace)
{
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    OsStackTrace* copy;
    if (stackTrace == NULL) {
        return kHandleNull;
    }
    copy = (OsStackTrace*)calloc(sizeof(OsStackTrace), 1);
    if (copy == NULL) {
        return kHandleNull;
    }
    (void)memcpy(copy, stackTrace, sizeof(OsStackTrace));
    copy->iSymbol = NULL;
    return copy;
}

uint32_t OsStackTraceNumEntries(THandle aStackTrace)
{
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    if (stackTrace == kHandleNull) {
        return 0;
    }
    return stackTrace->iCount;
}

const char* OsStackTraceEntry(THandle aStackTrace, uint32_t aIndex)
{
#ifndef STACK_TRACE_ENABLE
    aStackTrace = aStackTrace;
    aIndex = aIndex;
    return NULL;
#else
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    OsMutexLock(stackTrace->iOsContext->iMutex);
    if (stackTrace->iSymbol == NULL) {
        stackTrace->iSymbol = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + 256, 1);
        if (stackTrace->iSymbol == NULL) {
            return NULL;
        }
        stackTrace->iSymbol->MaxNameLen = 255;
        stackTrace->iSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    }
    SymFromAddr(stackTrace->iOsContext->iDebugSymbolHandle, (DWORD64)(stackTrace->iStack[aIndex]), 0, stackTrace->iSymbol);
    OsMutexUnlock(stackTrace->iOsContext->iMutex);
    return stackTrace->iSymbol->Name;
#endif
}

void OsStackTraceFinalise(THandle aStackTrace)
{
    OsStackTrace* stackTrace = (OsStackTrace*)aStackTrace;
    if (stackTrace != kHandleNull) {
        free(stackTrace->iSymbol);
        free(stackTrace);
    }
}

uint64_t OsTimeInUs(OsContext* aContext)
{
    uint64_t now, diff, adjustedNow;
    FILETIME ft;
    OsMutexLock(aContext->iMutex);
    GetSystemTimeAsFileTime(&ft);
    now = ft.dwHighDateTime;
    now <<= 32;
    now |= ft.dwLowDateTime;
    
    /* if time has moved backwards, calculate by how much and add this to aContext->iTimeAdjustment */
    if (now < aContext->iPrevTime) {
        diff = aContext->iPrevTime - now;
#ifndef DEFINE_WINDOWS_UNIVERSAL
        fprintf(stderr, "WARNING: clock moved backwards by %3llums\n", now / 10000);
#endif
        aContext->iTimeAdjustment += diff;
    }
    aContext->iPrevTime = now; /* stash current time to allow the next call to spot any backwards move */
    adjustedNow = now + aContext->iTimeAdjustment; /* add any previous backwards moves to the time */
    diff = adjustedNow - aContext->iStartTime; /* how long since we started, ignoring any backwards moves */
    diff /= 10; // GetSystemTimeAsFileTime has units of 100 nano-secs
    OsMutexUnlock(aContext->iMutex);

    return diff;
}

#ifdef DEFINE_WINDOWS_UNIVERSAL
void OsConsoleWrite(const char* /*aStr*/)
{
}
#else
void OsConsoleWrite(const char* aStr)
{
    fprintf(stderr, "%s", aStr);
    fflush(stderr);
}
#endif

void OsGetPlatformNameAndVersion(OsContext* aContext, char** aName, uint32_t* aMajor, uint32_t* aMinor)
{
#if NTDDI_VERSION <= 0x06010000 /* Windows 7 and below */
    OSVERSIONINFO verInfo;
    UNUSED(aContext);
    memset(&verInfo, 0, sizeof(verInfo));
    verInfo.dwOSVersionInfoSize = sizeof(verInfo);
    (void)GetVersionEx(&verInfo);
    *aName = "Windows";
    *aMajor = verInfo.dwMajorVersion;
    *aMinor = verInfo.dwMinorVersion;
#else
    /* There doesn't seem to be any reliable way to determine version info on Windows 8.1 and beyond
       The recommended route appears to be to add ever more IsWindowsXxx tests as new OS versions are released... */
    /* The recommended route doesn't appear to always work.
       Reporting host OS version has questionable benefit anyway so just hard-code something credible. */
    UNUSED(aContext);
    *aName = "Windows";
    *aMajor = 6;
    *aMinor = 3;
#endif
}

THandle OsSemaphoreCreate(OsContext* aContext, const char* aName, uint32_t aCount)
{
    UNUSED(aContext);
    UNUSED(aName);
    return (THandle)M_CreateSemaphore(NULL, aCount, INT32_MAX, NULL);
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

THandle OsMutexCreate(OsContext* aContext, const char* aName)
{
    Mutex* mutex = (Mutex*)calloc(1, sizeof(*mutex));
    UNUSED(aContext);
    UNUSED(aName);
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
    char*            iName;
    ThreadEntryPoint iEntryPoint;
    void*            iArg;
    uint32_t         iPriority;
    OsContext*       iCtx;
    THandle          iSemaHandle;
} ThreadData;

void OsThreadGetPriorityRange(OsContext* aContext, uint32_t* aHostMin, uint32_t* aHostMax)
{
    UNUSED(aContext);
    *aHostMin = kPriorityMin;
    *aHostMax = kPriorityMax;
}

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
   DWORD dwType;     // Must be 0x1000.
   LPCSTR szName;    // Pointer to name (in user addr space).
   DWORD dwThreadID; // Thread ID (-1=caller thread).
   DWORD dwFlags;    // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

static void SetCurrentThreadName(const char* threadName)
{
    static const DWORD MS_VC_EXCEPTION=0x406D1388;

    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = threadName;
    info.dwThreadID = GetCurrentThreadId();
    info.dwFlags = 0;

    __try {
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {}
}

DWORD threadEntrypoint(LPVOID aArg)
{
    ThreadData* data = (ThreadData*)aArg;
    int priority = data->iPriority;
    priority += THREAD_PRIORITY_IDLE;
    if (!SetThreadPriority(data->iThread, priority)) {
        //fprintf(stderr, "SetPriority failed (err=%d)\n", GetLastError());
        //fflush(stderr);
    }

    (void)TlsSetValue(data->iCtx->iTlsIndex, data->iArg);
    SetCurrentThreadName(data->iName);
    data->iEntryPoint(data->iArg);

    return 0;
}

THandle OsThreadCreate(OsContext* aContext, const char* aName, uint32_t aPriority,
                       uint32_t aStackBytes, ThreadEntryPoint aEntryPoint, void* aArg)
{
    ThreadData* data = (ThreadData*)calloc(1, sizeof(ThreadData));
    if (NULL == data) {
        return kHandleNull;
    }
#ifndef DEFINE_WINDOWS_UNIVERSAL
    data->iName = _strdup(aName);
#else
     size_t length = strlen(aName);
     data->iName = new char[length + 1];
     memcpy_s(data->iName, length + 1, aName, length + 1);
#endif

    if (data->iName == NULL) {
        free(data);
        return kHandleNull;
    }

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
    data->iCtx        = aContext;
    data->iSemaHandle = OsSemaphoreCreate(aContext, "tls_sem", 0);

    if (data->iSemaHandle == kHandleNull) {
        free(data->iName);
        free(data);
        return kHandleNull;
    }

    data->iThread = CreateThread(NULL, aStackBytes, (LPTHREAD_START_ROUTINE)&threadEntrypoint, data, 0, NULL);
    if (0 == data->iThread) {
        OsSemaphoreDestroy(data->iSemaHandle);
        free(data->iName);
        free(data);
	return kHandleNull;
    }
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

void* OsThreadTls(OsContext* aContext)
{
    return TlsGetValue(aContext->iTlsIndex);
}

void OsThreadDestroy(THandle aThread)
{
    ThreadData* data = (ThreadData*)aThread;
    if (data != NULL) {
        OsSemaphoreDestroy(data->iSemaHandle);
        free(data->iName);
        free(data);
    }
}

int32_t OsThreadSupportsPriorities(OsContext* aContext)
{
    UNUSED(aContext);
    // we do support priorities but can't manage the full range the library expects
    return 0;
}

typedef struct OsNetworkHandle
{
    SOCKET     iSocket;
    WSAEVENT   iEventSocket;
    WSAEVENT   iEventInterrupt;
    int32_t    iInterrupted;
    OsContext* iCtx;
}OsNetworkHandle;

static int32_t SocketInterrupted(const OsNetworkHandle* aHandle)
{
    int32_t interrupted;
    OsMutexLock(aHandle->iCtx->iMutex);
    interrupted = aHandle->iInterrupted;
    OsMutexUnlock(aHandle->iCtx->iMutex);
    return interrupted;
}

static void sockaddrFromEndpoint(struct sockaddr_in* aAddr, const TIpAddress* aAddress, uint16_t aPort)
{
    memset(aAddr, 0, sizeof(*aAddr));
    aAddr->sin_family = AF_INET;
    aAddr->sin_port = SwapEndian16(aPort);
    aAddr->sin_addr.s_addr = aAddress->iV4;
}

static OsNetworkHandle* CreateHandle(OsContext* aContext, SOCKET aSocket)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)malloc(sizeof(OsNetworkHandle));
    if (NULL == handle) {
        (void)closesocket(handle->iSocket);
        return kHandleNull;
    }
    handle->iEventSocket = WSACreateEvent();
    if (NULL == handle->iEventSocket) {
        (void)closesocket(aSocket);
        free(handle);
        return kHandleNull;
    }
    handle->iEventInterrupt = WSACreateEvent();
    if (NULL == handle->iEventInterrupt) {
        WSACloseEvent(handle->iEventSocket);
        (void)closesocket(aSocket);
        free(handle);
        return kHandleNull;
    }
    if (0 != WSAEventSelect(aSocket, handle->iEventSocket, FD_READ | FD_WRITE | FD_ACCEPT | FD_CONNECT | FD_CLOSE)) {
        WSACloseEvent(handle->iEventInterrupt);
        WSACloseEvent(handle->iEventSocket);
        (void)closesocket(aSocket);
        free(handle);
        return kHandleNull;
    }
    handle->iSocket = aSocket;
    handle->iInterrupted = 0;
    handle->iCtx = aContext;

    return handle;
}

static void SetSocketBlocking(SOCKET aSocket)
{
    u_long nonBlocking = 0;
    WSAEventSelect(aSocket, NULL, 0);
    if (-1 == ioctlsocket(aSocket, FIONBIO, &nonBlocking)) {
#ifndef DEFINE_WINDOWS_UNIVERSAL
        fprintf(stdout, "SetSocketBlocking failed for socket %u\n", aSocket);
#endif
    }
}

THandle OsNetworkCreate(OsContext* aContext, OsNetworkSocketType aSocketType, OsNetworkSocketFamily aSocketFamily)
{
    if (aSocketFamily != eOsNetworkSocketV4)
        return NULL;
    SOCKET socketH = socket(AF_INET, aSocketType, 0);
    OsNetworkHandle* handle = CreateHandle(aContext, socketH);
    return (THandle)handle;
}

int32_t OsNetworkBind(THandle aHandle, TIpAddress aAddress, uint32_t aPort)
{
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct sockaddr_in addr;
    uint16_t port = (uint16_t)aPort;
    sockaddrFromEndpoint(&addr, &aAddress, port);
    err = bind(handle->iSocket, (struct sockaddr*)&addr, sizeof(addr));
    if (err == SOCKET_ERROR) {
        if (WSAGetLastError() == WSAEADDRINUSE) {
            err = -2;
        }
        else {
            err = -1;
        }
    }
    return err;
}

int32_t OsNetworkBindMulticast(THandle aHandle, TIpAddress aAdapter, TIpAddress aMulticast, uint32_t aPort)
{
    aMulticast = aMulticast; // suppress warning C2055
    return OsNetworkBind(aHandle, aAdapter, aPort);
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
    HANDLE handles[2];
    DWORD ret;

    if (aAddress.iFamily != kFamilyV4) {
        return -1;
    }
    if (SocketInterrupted(handle)) {
        return -1;
    }

    handles[0] = handle->iEventSocket;
    handles[1] = handle->iEventInterrupt;

    sockaddrFromEndpoint(&addr, &aAddress, aPort);
    (void)connect(handle->iSocket, (struct sockaddr*)&addr, sizeof(addr));
    ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, aTimeoutMs, FALSE);
    if (WAIT_OBJECT_0 == ret) {
        // Need to check socket status using getsockopt. See msdn page for select:
        //  https://msdn.microsoft.com/en-us/library/windows/desktop/ms740141%28v=vs.85%29.aspx
        int sock_error;
        int opt_len = sizeof(sock_error);
        if (getsockopt(handle->iSocket, SOL_SOCKET, SO_ERROR, (char*) &sock_error, &opt_len) == 0) {
            err = ((opt_len == sizeof(sock_error)) && (sock_error == 0)) ? 0 : -2;
        }
    }

    return err;
}

int32_t OsNetworkSend(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes)
{
    int32_t bytes = 0;
    uint32_t remaining = aBytes;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    HANDLE handles[2];
    DWORD ret;

    if (SocketInterrupted(handle)) {
        return -1;
    }

    handles[0] = handle->iEventSocket;
    handles[1] = handle->iEventInterrupt;
    do {
        bytes = send(handle->iSocket, (const char*)aBuffer, remaining, 0);
        if (bytes != -1) {
            aBuffer += bytes;
            remaining -= bytes;
        }
        else if (WSAEWOULDBLOCK == WSAGetLastError()) {
            ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
            if (WAIT_OBJECT_0 == ret) {
                bytes = 0; // space to write - reset bytes to allow for another iteration
            }
            (void)WSAResetEvent(handle->iEventSocket);
        }
        else {
            break;
        }
    } while(bytes != -1 && remaining > 0);

    return (int32_t)aBytes - remaining;
}

int32_t OsNetworkSendTo(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes, TIpAddress aAddress, uint16_t aPort)
{
    int32_t sent = 0;
    int32_t bytes = 0;
    struct sockaddr_in addr;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    if (aAddress.iFamily != kFamilyV4) {
        return -1;
    }
    if (SocketInterrupted(handle)) {
        return -1;
    }
    sockaddrFromEndpoint(&addr, &aAddress, aPort);
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
    HANDLE handles[2];
    DWORD ret;

    if (SocketInterrupted(handle)) {
        return -1;
    }

    handles[0] = handle->iEventSocket;
    handles[1] = handle->iEventInterrupt;

    received = recv(handle->iSocket, (char*)aBuffer, aBytes, 0);
    while (SOCKET_ERROR==received && WSAEWOULDBLOCK==WSAGetLastError()) {
        ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
        if (SocketInterrupted(handle)) {
            break;
        }
        (void)WSAResetEvent(handle->iEventSocket);
        received = recv(handle->iSocket, (char*)aBuffer, aBytes, 0);
    }

    return received;
}

int32_t OsNetworkReceiveFrom(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes, TIpAddress* aAddress, uint16_t* aPort)
{
    int32_t received;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct sockaddr_in addr;
    int len = sizeof(addr);
    HANDLE handles[2];
    DWORD ret = 0;

    if (SocketInterrupted(handle)) {
        return -1;
    }

    sockaddrFromEndpoint(&addr, &kIpAddressV4AllAdapters, 0);

    handles[0] = handle->iEventSocket;
    handles[1] = handle->iEventInterrupt;

    received = recvfrom(handle->iSocket, (char*)aBuffer, aBytes, 0, (struct sockaddr*)&addr, &len);
    while (SOCKET_ERROR == received) {
        int err = WSAGetLastError();
        if (WSAECONNRESET != err && WSAEWOULDBLOCK != err) {
            break;
        }
        ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
        if (SocketInterrupted(handle)) {
            break;
        }
        (void)WSAResetEvent(handle->iEventSocket);
        received = recvfrom(handle->iSocket, (char*)aBuffer, aBytes, 0, (struct sockaddr*)&addr, &len);
    }

    aAddress->iFamily = kFamilyV4;
    aAddress->iV4 = addr.sin_addr.s_addr;
    *aPort = SwapEndian16(addr.sin_port);
    return received;
}

int32_t OsNetworkInterrupt(THandle aHandle, int32_t aInterrupt)
{
    int32_t err = 0;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    OsMutexLock(handle->iCtx->iMutex);
    handle->iInterrupted = aInterrupt;
    if (aInterrupt != 0) {
        (void)WSASetEvent(handle->iEventInterrupt);
    }
    else {
        (void)WSAResetEvent(handle->iEventInterrupt);
    }
    OsMutexUnlock(handle->iCtx->iMutex);
    return err;
}

int32_t OsNetworkClose(THandle aHandle)
{
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = closesocket(handle->iSocket);
    if (0 == err) {
        WSACloseEvent(handle->iEventInterrupt);
        WSACloseEvent(handle->iEventSocket);
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

THandle OsNetworkAccept(THandle aHandle, TIpAddress* aClientAddress, uint32_t* aClientPort)
{
    SOCKET h;
    OsNetworkHandle* newHandle;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    HANDLE handles[2];
    DWORD ret;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    aClientAddress->iFamily = kFamilyV4;
    aClientAddress->iV4 = 0;
    *aClientPort = 0;
    if (SocketInterrupted(handle)) {
        return kHandleNull;
    }
    sockaddrFromEndpoint(&addr, &kIpAddressV4AllAdapters, 0);
    handles[0] = handle->iEventSocket;
    handles[1] = handle->iEventInterrupt;

    h = accept(handle->iSocket, (struct sockaddr*)&addr, &len);
    while (INVALID_SOCKET==h && WSAEWOULDBLOCK==WSAGetLastError()) {
        ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
        (void)WSAResetEvent(handle->iEventSocket);
        if (SocketInterrupted(handle)) {
            break;
        }
        h = accept(handle->iSocket, (struct sockaddr*)&addr, &len);
    }
    if (INVALID_SOCKET == h) {
        return kHandleNull;
    }

    newHandle = CreateHandle(handle->iCtx, h);
    if (NULL == newHandle) {
        return kHandleNull;
    }

    aClientAddress->iV4 = addr.sin_addr.s_addr;
    *aClientPort = SwapEndian16(addr.sin_port);
    return (THandle)newHandle;
}

int32_t OsNetworkGetHostByName(const char* aAddress, TIpAddress* aHost)
{
    int32_t ret = -1;
    struct addrinfo *results = NULL;
    (void)getaddrinfo(aAddress, "", NULL, &results);
    if (results != NULL) {
        struct addrinfo *res = results;
        while (res != NULL) {
            if (res->ai_family == AF_INET) {
                aHost->iFamily = kFamilyV4;
                aHost->iV4 = ((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr;
                ret = 0;
                break;
            }
            res = res->ai_next;
        }
        freeaddrinfo(results);
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
    if (aInterface.iFamily != kFamilyV4)
        return -1;
    int32_t err;
    char loop;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = aAddress.iV4;
    mreq.imr_interface.s_addr = aInterface.iV4;
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
    if (aInterface.iFamily != kFamilyV4 || aAddress.iFamily != kFamilyV4)
        return -1;
    int32_t err;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = aAddress.iV4;
    mreq.imr_interface.s_addr = aInterface.iV4;
    err = setsockopt(handle->iSocket, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));
    return err;
}

int32_t OsNetworkSocketSetMulticastIf(THandle aHandle,  TIpAddress aInterface)
{
    if (aInterface.iFamily != kFamilyV4)
        return -1;
    OsNetworkHandle* handle = (OsNetworkHandle*)aHandle;
    int32_t err = setsockopt(handle->iSocket, IPPROTO_IP, IP_MULTICAST_IF, (const char*)&aInterface, sizeof(aInterface));
    return err;
}


#define MakeIpAddress(aByte1, aByte2, aByte3, aByte4) \
        (aByte1 | (aByte2<<8) | (aByte3<<16) | (aByte4<<24))



#ifndef DEFINE_WINDOWS_UNIVERSAL

int32_t OsNetworkListAdapters(OsContext* aContext, OsNetworkAdapter** aInterfaces, uint32_t aUseLoopback, uint32_t aIpVersion)
{
    UNUSED(aIpVersion);

    MIB_IFTABLE* ifTable          = NULL;
    MIB_IPADDRTABLE* addrTable    = NULL;
    ULONG bytes                   = 0;
    OsNetworkAdapter* head      = NULL;
    int32_t index                 = 0;
    int32_t includeLoopback       = 1;
    uint32_t i;
    TIpAddress loopbackAddr;
    loopbackAddr.iFamily = kFamilyV4;
    loopbackAddr.iV4 = MakeIpAddress(127, 0, 0, 1);


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

    if (aUseLoopback == LOOPBACK_EXCLUDE) {
        // Only include loopback if there are no non-loopback adapters
        for (i=0; i<addrTable->dwNumEntries; i++) {
            MIB_IPADDRROW* addrRow = &(addrTable->table[i]);
            if (addrRow->dwAddr != loopbackAddr.iV4) {
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

        if ((addrRow->dwAddr == loopbackAddr.iV4 && includeLoopback == 0) ||
            (addrRow->dwAddr != loopbackAddr.iV4 && aUseLoopback == LOOPBACK_USE)) {
            continue;
        }
        if (-1 != aContext->iTestInterfaceIndex && index++ != aContext->iTestInterfaceIndex) {
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
        nif->iAddress.iFamily = kFamilyV4;
        nif->iAddress.iV4 = addrRow->dwAddr;
        nif->iNetMask.iFamily = kFamilyV4;
        nif->iNetMask.iV4 = addrRow->dwMask;
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
            TIpAddress subnet;
            subnet.iFamily = kFamilyV4;
            subnet.iV4 = (nif->iAddress.iV4 & nif->iNetMask.iV4);
            OsNetworkAdapter* p1 = head;
            OsNetworkAdapter* prev = NULL;
            while (NULL != p1) {
                if ((p1->iAddress.iV4 & p1->iNetMask.iV4) == subnet.iV4) {
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

#else
#define IF_TYPE_ETHERNET_CSMACD 6

  int32_t OsNetworkListAdapters(OsContext* aContext, OsNetworkAdapter** aInterfaces, uint32_t aUseLoopback, uint32_t aIpVersion)
  {
    UNUSED(aContext);
    UNUSED(aUseLoopback);
    UNUSED(aIpVersion);

    OsNetworkAdapter* head = NULL;

    try
    {
        auto hostNames = NetworkInformation::GetHostNames();

        for each (auto iter in hostNames)
        {
            HostName^ hostName = (HostName^)iter;
            if (hostName != nullptr && hostName->Type == HostNameType::Ipv4 && hostName->IPInformation != nullptr)
            {
                TIpAddress address;

                IPInformation^ ipInfo = hostName->IPInformation;                
                int prefixLength = ipInfo->PrefixLength->Value;
                String^ ipAddressString = hostName->CanonicalName;

                // convert String ipAddressString to char*
                auto wideData = ipAddressString->Data();                
                int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideData, -1, nullptr, 0, NULL, NULL);
                auto utf8 = std::make_unique<char[]>(bufferSize);
                if (0 == WideCharToMultiByte(CP_UTF8, 0, wideData, -1, utf8.get(), bufferSize, NULL, NULL))
                {
                    OsNetworkFreeInterfaces(head);
                    return -1;
                }
                std::string ipAddrStdStr = std::string(utf8.get());
                const char* ipAddressChars = ipAddrStdStr.c_str();
                
                if (0 != OsNetworkGetHostByName(ipAddressChars, &address))
                {
                    OsNetworkFreeInterfaces(head);
                    return -1;
                }

                TIpAddress netmask;
                netmask.iFamily = kFamilyV4;
                netmask.iV4 = 0xFFFFFFFF;
                netmask.iV4 <<= 32 - prefixLength;
                netmask.iV4 = htonl(netmask.iV4);

                OsNetworkAdapter* nif;
                nif = (OsNetworkAdapter*)calloc(1, sizeof(*nif));
                if (nif == NULL) {
                    return -1;
                }
                nif->iReserved = IF_TYPE_ETHERNET_CSMACD;
                nif->iAddress = address;
                nif->iNetMask = netmask;
                nif->iName = (char*)malloc(1);
                nif->iName[0] = '\0';
                if (head == NULL) 
                {
                    head = nif;
                }
                else 
                {
                    TIpAddress subnet;
                    subnet.iFamily = kFamilyV4;
                    subnet.iV4 = (nif->iAddress.iV4 & nif->iNetMask.iV4);
                    OsNetworkAdapter* p1 = head;
                    OsNetworkAdapter* prev = NULL;
                    while (NULL != p1) 
                    {
                        if ((p1->iAddress.iV4 & p1->iNetMask.iV4) == subnet.iV4) 
                        {
                            while (NULL != p1 && IF_TYPE_ETHERNET_CSMACD == p1->iReserved) 
                            {
                                prev = p1;
                                p1 = p1->iNext;
                            }
                            break;
                        }
                        prev = p1;
                        p1 = p1->iNext;
                    }
                    if (NULL == prev) 
                    {
                        nif->iNext = head;
                        head = nif;
                    }
                    else 
                    {
                        nif->iNext = prev->iNext;
                        prev->iNext = nif;
                    }
                }
            }
        }
    }
    catch (Exception^ ex)
    {
        OsNetworkFreeInterfaces(head);
        return -1;
    }

    *aInterfaces = head;

    return 0;
  }

#endif


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
    DWORD callback = 0;

    while (obs->iShutdown == 0) {
        DWORD ret = WAIT_FAILED;
        DWORD bytes;
        if (SOCKET_ERROR == WSAIoctl(obs->iSocket, SIO_ADDRESS_LIST_CHANGE,
                                       NULL, 0, NULL, 0, &bytes, NULL, NULL)
            && WSAEWOULDBLOCK == WSAGetLastError()) {
            HANDLE handles[2];
            handles[0] = obs->iEvent;
            handles[1] = obs->iShutdownEvent;

            if (callback)
            {
                (obs->iCallback)(obs->iArg);
                callback = 0;
            }

            ret = WSAWaitForMultipleEvents(2, &handles[0], FALSE, INFINITE, FALSE);
        }
        if (WAIT_OBJECT_0 == ret) {
            callback = 1;
        }
    }
    (void)ReleaseSemaphore(obs->iSem, 1, NULL);
    return 0;
}

void OsNetworkSetInterfaceChangedObserver(OsContext* aContext, InterfaceListChanged aCallback, void* aArg)
{
    InterfaceChangeObserver* icobs;
    if (NULL != aContext->iInterfaceChangeObserver) {
        return;
    }

    icobs = (InterfaceChangeObserver*)malloc(sizeof(InterfaceChangeObserver));
    if (NULL == icobs) {
        return;
    }

    icobs->iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    SetSocketBlocking(icobs->iSocket);
    icobs->iEvent = M_CreateEvent(NULL, FALSE, FALSE, NULL);
    icobs->iShutdownEvent = M_CreateEvent(NULL, FALSE, FALSE, NULL);
    icobs->iCallback = aCallback;
    icobs->iArg = aArg;
    icobs->iShutdown = 0;
    icobs->iSem = M_CreateSemaphore(NULL, 0, INT32_MAX, NULL);
    (void)WSAEventSelect(icobs->iSocket, icobs->iEvent, FD_ADDRESS_LIST_CHANGE);
    (void)CreateThread(NULL, 16*1024, (LPTHREAD_START_ROUTINE)&interfaceChangeThread, icobs, 0, NULL);
    aContext->iInterfaceChangeObserver = icobs;
}

/**
 * Test function.  Restrict OsNetworkListAdapters to just item aIndex from its normal list
 * Not advertised in Os.h and not guaranteed to be available on all platforms
 */
extern void OsNetworkSetTestInterfaceIndex(OsContext* aContext, int32_t aIndex);
void OsNetworkSetTestInterfaceIndex(OsContext* aContext, int32_t aIndex)
{
    aContext->iTestInterfaceIndex = aIndex;
    if (NULL != aContext->iInterfaceChangeObserver) {
        (void)WSASetEvent(aContext->iInterfaceChangeObserver->iEvent);
    }
}

void OsNetworkSetDnsChangedObserver(OsContext* aContext, DnsChanged aCallback, void* aArg)
{
    UNUSED(aContext);
    UNUSED(aCallback);
    UNUSED(aArg);
}
