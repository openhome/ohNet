#include <OpenHome/Os.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// FreeRTOS headers
#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/semphr.h>
#include <FreeRTOS/task.h>

// LWIP headers
#include <lwip/netif.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include <bsp.h>


#define GETHOSTBYNAME_BUFFER_BYTES 128

int32_t OsCreate()
{
    // initialise network stuff.
    BSP_start_network(0);
    return 0;
}

void OsDestroy()
{
}

void OsQuit()
{
}

void OsBreakpoint()
{
    while(1);
}

THandle OsStackTraceInitialise()
{
    return kHandleNull;
}

THandle OsStackTraceCopy(THandle aStackTrace)
{
    aStackTrace = aStackTrace;
    return kHandleNull;
}

uint32_t OsStackTraceNumEntries(THandle aStackTrace)
{
    aStackTrace = aStackTrace;
    return 0;
}

const char* OsStackTraceEntry(THandle aStackTrace, uint32_t aIndex)
{
    aStackTrace = aStackTrace;
    aIndex = aIndex;
    return NULL;
}

void OsStackTraceFinalise(THandle aStackTrace)
{
    aStackTrace = aStackTrace;
}

uint64_t OsTimeInUs()
{
    return xTaskGetTickCount() * portTICK_RATE_MS * 1000;
}

void OsConsoleWrite(const char* aStr)
{
    printf(aStr);
    fflush(stdout);
}

void OsGetPlatformNameAndVersion(char** aName, uint32_t* aMajor, uint32_t* aMinor)
{
    *aName = "FreeRTOS/LWIP";
    *aMajor = 0;
    *aMinor = 1;
}

THandle OsSemaphoreCreate(const char* aName, uint32_t aCount)
{
    xSemaphoreHandle x = xSemaphoreCreateCounting((portBASE_TYPE) (-1), aCount);

    return ( x != NULL ? (THandle) x : kHandleNull );
}

void OsSemaphoreDestroy(THandle aSem)
{
    vQueueDelete(aSem);
}

int32_t OsSemaphoreWait(THandle aSem)
{
    if ( xSemaphoreTake(aSem, portMAX_DELAY) == pdTRUE )
        return 0;
    else
        return -1;
}

int32_t OsSemaphoreTimedWait(THandle aSem, uint32_t aTimeoutMs)
{
    portTickType ticks = portTICK_RATE_MS * aTimeoutMs;

    // Test that the user hasn't inadvertently specified an infinite timeout...
    if ( ticks == portMAX_DELAY )
        return -1;

    if ( xSemaphoreTake(aSem, ticks) == pdTRUE )
        return 1;
    else
        return 0;
}

uint32_t OsSemaphoreClear(THandle aSem)
{
    // Use block time of 0 to poll the semaphore.
    
    // Return 0 if already clear.
    if ( xSemaphoreTake(aSem, 0) == pdFALSE )
        return 0;

    // Take all slots in semaphore.
    while ( xSemaphoreTake(aSem, 0) == pdTRUE );
    
    return 1;
}

// FreeRTOS semaphores are implemented using queues, which means they are of 
// finite length. This means it's possible for the xSemaphoreGive() to block
// while waiting for space on the queue.
//
// The queue size is set to (portBASE_TYPE) (-1) (largest possible unsigned int
// but this may possibly be exhausted and cause weirdness.
//
// OsSemaphoreSignal() might be better implemented using xSemaphoreGiveFromISR()
// which errors out instead of blocking.

int32_t OsSemaphoreSignal(THandle aSem)
{
    if ( xSemaphoreGive(aSem) == pdTRUE )
        return 0;
    else
        return -1;
}

THandle OsMutexCreate(const char* aName)
{
    xSemaphoreHandle x = xSemaphoreCreateMutex();

    return ( x != NULL ? (THandle) x : kHandleNull );
}

void OsMutexDestroy(THandle aMutex)
{
    vQueueDelete(aMutex);
}

int32_t OsMutexLock(THandle aMutex)
{
    if ( xSemaphoreTake(aMutex, portMAX_DELAY) == pdTRUE )
        return 0;
    else
        return -2;
}

int32_t OsMutexUnlock(THandle aMutex)
{
    if ( xSemaphoreGive(aMutex) == pdTRUE )
        return 0;
    else
        return -1;
}

THandle OsThreadCreate(const char* aName, uint32_t aPriority, uint32_t aStackBytes, ThreadEntryPoint aEntryPoint, void* aArg)
{
    portBASE_TYPE result;
    xTaskHandle task;

    /* The task application tag is used to hold a pointer to the containing Thread object.
       If the child task is higher priority than it's parent, it'll run before the tag is 
       set. Bad. So we set the initial priority as slightly lower than parent thread, set
       the tag, then promote the child task to it's rightful priority. */

    result =  xTaskCreate(  aEntryPoint,                          // pdTASK_CODE pvTaskCode, 
                            (const signed char * const) aName,    // const portCHAR * const pcName, 
                            (aStackBytes != 0 ? aStackBytes : 1024 * 32) / sizeof( portSTACK_TYPE ),
                                                                  // unsigned portSHORT usStackDepth, 
                            aArg,                                 // void *pvParameters, 
                            uxTaskPriorityGet(NULL) - 1,          // unsigned portBASE_TYPE uxPriority, 
                            &task                                 // xTaskHandle *pvCreatedTask 
                          );

    if ( result != pdPASS )
        return kHandleNull;

    vTaskSetApplicationTaskTag(task, aArg);
    vTaskPrioritySet(task, aPriority);
    
    return (THandle) task;
}

void* OsThreadTls()
{
    return xTaskGetApplicationTaskTag(NULL);
}

void OsThreadDestroy(THandle aThread)
{
    vTaskDelete((xTaskHandle) aThread);
}

int32_t OsThreadSupportsPriorities()
{
    return 1;
}

typedef struct
{
    THandle iMutex;
    int     iSocket;
    int     iIntSocket;
    int     iFlagInterrupted;
} OsNetworkHandle;

#define HANDLE_TO_SOCKET(x)     (((OsNetworkHandle*) (x))->iSocket)

#define INT_ENABLED             1

#if 0

#define LOGFUNC()     LOG("%s\n", __FUNCTION__)

#define LOGFUNCIN()   do { printf("ENTER %s %d\n", __FUNCTION__, HANDLE_TO_SOCKET(aHandle)); fflush(stdout); } while(0)
#define LOGFUNCOUT()  do { printf("EXIT  %s %d\n", __FUNCTION__, HANDLE_TO_SOCKET(aHandle)); fflush(stdout); } while(0)
#define LOG(x, args... )    do { printf((x), ## args); fflush(stdout); } while(0)

#else

#define LOGFUNC()

#define LOGFUNCIN()
#define LOGFUNCOUT()
#define LOG(x, args...)

#endif

static OsNetworkHandle* OsNetworkHandle_Create()
{
    LOGFUNC();

    OsNetworkHandle* handle = (OsNetworkHandle*) malloc(sizeof(OsNetworkHandle));
    
    if ( handle == NULL )
        return NULL;
    
    THandle mtx = OsMutexCreate("");
    
    if ( mtx == kHandleNull )
    {
        free(handle);
        return NULL;
    }
    
    handle->iMutex              = mtx;
    handle->iSocket             = -1;
    handle->iIntSocket          = -1;
    handle->iFlagInterrupted    =  0;
    
    LOG("Allocted OsNetworkHandle %08x\n", handle);
    
    return handle;
}

static int OsNetworkHandle_Initialise(OsNetworkHandle* aHandle, int aSocket)
{
    LOGFUNC();

    aHandle->iSocket = aSocket;
    
#if INT_ENABLED
    
    int ih = lwip_socket(AF_INET, SOCK_DGRAM, 0);
    
    if ( ih < 0 )
    {
        LOG("%s failed with %d\n", __FUNCTION__, errno);
        return -1;
    }
    
    struct sockaddr_in s;
    
    s.sin_family        = AF_INET;
    s.sin_port          = htons( 10000 + (short) aSocket );  // relate port to fd
    s.sin_addr.s_addr   = IPADDR_LOOPBACK;                   // localhost
    
    int err = lwip_bind ( ih, (struct sockaddr*) &s, sizeof(s) );
    
    if ( err < 0 )
    {
        lwip_close(ih);
        return -1;
    }
    
    aHandle->iIntSocket = ih;
    
#endif
    
    LOG("Created OsNetworkHandle %d:%d\n", aHandle->iSocket, aHandle->iIntSocket);
    
    return 0;
}

static int OsNetworkHandle_IsInterrupted(OsNetworkHandle* aHandle)
{
    int state;
    OsMutexLock(aHandle->iMutex);
    state = aHandle->iFlagInterrupted;
    OsMutexUnlock(aHandle->iMutex);
    return state;
}

static void post_int(OsNetworkHandle* aHandle)
{
    // Send byte to interrupt socket
    int sender = lwip_socket ( AF_INET, SOCK_DGRAM, 0 );
    struct sockaddr_in s;
    s.sin_family        = AF_INET;
    s.sin_port          = htons( 10000 + HANDLE_TO_SOCKET(aHandle) );   // relate port to fd
    s.sin_addr.s_addr   = IPADDR_LOOPBACK;                              // localhost

    char buffer[] = { 0xaa };

    int bytes = lwip_sendto ( sender, buffer, 1, 0, (struct sockaddr*) &s, sizeof(s) );
    
    if ( bytes != sizeof(buffer) )
        exit(-1);
    
    lwip_close(sender);
}

static void clear_int(OsNetworkHandle* aHandle)
{
    char buffer[1];
    int bytes = lwip_recv(aHandle->iIntSocket, buffer, 1, 0);
    if ( bytes != 1 )
        exit(-1);
}

static void OsNetworkHandle_SetInterrupted(OsNetworkHandle* aHandle, int aNewInterruptState)
{
    OsMutexLock(aHandle->iMutex);

    if ( aNewInterruptState != (int) aHandle->iFlagInterrupted )
    {
        aHandle->iFlagInterrupted = aNewInterruptState;
        
#if INT_ENABLED
        if ( aHandle->iFlagInterrupted )
            post_int(aHandle);
        else
            clear_int(aHandle);
#endif
    }
    
    OsMutexUnlock(aHandle->iMutex);
}

static void OsNetworkHandle_Destroy(OsNetworkHandle* aHandle)
{
    LOGFUNC();

#if INT_ENABLED
    if ( aHandle->iIntSocket >= 0 )
    {
        lwip_close(aHandle->iIntSocket);
    }
#endif
    
    OsMutexDestroy(aHandle->iMutex);
    
    aHandle->iSocket            = -1;
    aHandle->iIntSocket         = -1;
    aHandle->iFlagInterrupted   =  1;
    
    free(aHandle);
    
    LOG("Destroyd OsNetworkHandle %08x\n", aHandle);
}

/* Returns
 (-1) if interrupted
 (-2) if timed out
 (fd) if socket is ready
*/
#define LS_READ         1
#define LS_WRITE        0
#define LS_FOREVER      0

static int local_select(THandle aHandle, int aMode, uint32_t aTimeoutMs)
{
    OsNetworkHandle* h = (OsNetworkHandle*) aHandle;
    
    LOGFUNCIN();
    
    fd_set read_set;
    fd_set write_set;
    
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    
    if ( aMode == LS_READ )
        FD_SET(h->iSocket, &read_set);
    else
        FD_SET(h->iSocket, &write_set);
    
#if INT_ENABLED
    FD_SET(h->iIntSocket, &read_set);
#endif
    
    struct timeval t, *t_ptr = NULL;
    
    if ( aTimeoutMs != LS_FOREVER )
    {
        t.tv_sec  = aTimeoutMs / 1000;
        t.tv_usec = 1000 * (aTimeoutMs % 1000);
        t_ptr = &t;
    }
    
    int nfds = 1 + ( h->iSocket > h->iIntSocket ? h->iSocket : h->iIntSocket );

    int fd = lwip_select(nfds, &read_set, &write_set, NULL, t_ptr);

    if ( fd == 0 )
        return -2;

    if ( fd == -1 )
        exit(-1);
    
#if INT_ENABLED
    if ( FD_ISSET(h->iIntSocket, &read_set) )
    {
        LOG("local_select - interrupted %d", h->iSocket);
        return -1;
    }
#endif

    if ( (aMode == LS_READ) && FD_ISSET(h->iSocket, &read_set) )
    {
        LOGFUNCOUT();
        return h->iSocket;
    }
    
    if ( (aMode != LS_READ) && FD_ISSET(h->iSocket, &write_set) )
    {
        LOGFUNCOUT();
        return h->iSocket;
    }
    
    exit(-1);
}

static void setNonBlocking(THandle aHandle, int aNewState)
{
    lwip_fcntl(HANDLE_TO_SOCKET(aHandle), F_SETFL, (aNewState ? O_NONBLOCK : 0));
}

THandle OsNetworkCreate(OsNetworkSocketType aSocketType)
{
    int s;
    int type;
    OsNetworkHandle* h;

    //LOG(__FUNCTION__);

    switch ( aSocketType )
    {
        case eOsNetworkSocketStream:
            type = SOCK_STREAM;
            break;
        
        case eOsNetworkSocketDatagram:
            type = SOCK_DGRAM;
            break;
        
        default:
            return kHandleNull;
    }

    h = OsNetworkHandle_Create();

    //LOG("  Created %d\n", HANDLE_TO_SOCKET(h));

    if ( h == kHandleNull )
        return kHandleNull;

    s = lwip_socket(AF_INET, type, 0);

    if ( s < 0 )
    {
        OsNetworkHandle_Destroy(h);
        return kHandleNull;
    }

    if ( type == SOCK_DGRAM )
    {
        char loop = 1;
        if (lwip_setsockopt(s, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0)
        {
            OsNetworkHandle_Destroy(h);
            return kHandleNull;
        }
    }

    if ( OsNetworkHandle_Initialise(h, s) < 0 )
    {
        OsNetworkHandle_Destroy(h);
        return kHandleNull;
    }
    
    return (THandle) h;
}

int32_t OsNetworkBind(THandle aHandle, TIpAddress aAddress, uint32_t aPort)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;
    LOGFUNCIN();

    struct sockaddr_in s;

    s.sin_family        = AF_INET;
    s.sin_port          = htons(aPort);
    s.sin_addr.s_addr   = aAddress;        // this is already stored in network order

    int err = lwip_bind ( HANDLE_TO_SOCKET(aHandle), (struct sockaddr*) &s, sizeof(s) );
    
    if ( err == EADDRINUSE )
        return -2;
    
    LOGFUNCOUT();
    return err;
}

int32_t OsNetworkBindMulticast(THandle aHandle, TIpAddress aAdapter, TIpAddress aMulticast, uint32_t aPort)
{
    return OsNetworkBind(aHandle, aAdapter, aPort);
}

int32_t OsNetworkPort(THandle aHandle, uint32_t* aPort)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;
    LOGFUNCIN();

    struct sockaddr_in s;
    socklen_t len = sizeof(s);
    
    int err = lwip_getsockname ( HANDLE_TO_SOCKET(aHandle), (struct sockaddr*) &s, &len );

    if ( err < 0 )
        return -1;

    if (s.sin_family != AF_INET )
        return -1;
    
    *aPort = (uint32_t) (ntohs(s.sin_port));


    LOGFUNCOUT();
    return 0;
}

int32_t OsNetworkConnect(THandle aHandle, TIpAddress aAddress, uint16_t aPort, uint32_t aTimeoutMs)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;
    
    LOGFUNCIN();

    struct sockaddr_in s;
    
    s.sin_family        = AF_INET;
    s.sin_port          = htons(aPort);
    s.sin_addr.s_addr   = aAddress;
    
    int err;
    
    setNonBlocking(aHandle, 1);
    
    err = lwip_connect ( HANDLE_TO_SOCKET(aHandle), (struct sockaddr*) &s, sizeof(s) );
    
    setNonBlocking(aHandle, 0);
    
    if ( err == 0 )
        return 0;
    
    if ( errno != EINPROGRESS )
    {
        // error!
        return -1;
    }
    
    if ( local_select(aHandle, LS_WRITE, aTimeoutMs) < 0 )
    {
        return -1;
    }
    
    LOGFUNCOUT();
    return 0;
}

int32_t OsNetworkSend(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;

    LOGFUNCIN();
    
    int bytes = lwip_send ( HANDLE_TO_SOCKET(aHandle), (const void *) aBuffer, (size_t) aBytes, 0);
    
    LOGFUNCOUT();
    return bytes;
}

int32_t OsNetworkSendTo(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes, TIpAddress aAddress, uint16_t aPort )
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;

    LOGFUNCIN();

    struct sockaddr_in s;
    
    s.sin_family        = AF_INET;
    s.sin_port          = htons(aPort);
    s.sin_addr.s_addr   = aAddress;

    int bytes = lwip_sendto ( HANDLE_TO_SOCKET(aHandle), (const void *) aBuffer, (size_t) aBytes, 0, (struct sockaddr*) &s, sizeof(s) );
    
    LOGFUNCOUT();
    
    return bytes;
}

THandle OsNetworkAccept(THandle aHandle)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return kHandleNull;
    
    LOGFUNCIN();

    OsNetworkHandle* h = OsNetworkHandle_Create();
    
    if ( h == NULL )
        return kHandleNull;

    int fd;
    
    if ( local_select(aHandle, LS_READ, LS_FOREVER) == -1 )
        goto cleanup;
    
    fd = lwip_accept ( HANDLE_TO_SOCKET(aHandle), NULL, NULL);
    
    int err = OsNetworkHandle_Initialise(h, fd);
    
    if ( err < 0 )
        goto cleanup;
    
    LOGFUNCOUT();
    return (THandle) h;

cleanup:
    LOGFUNCOUT();
    OsNetworkHandle_Destroy(h);
    return kHandleNull;
}

int32_t OsNetworkReceive(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;

    LOGFUNCIN();

    if ( local_select(aHandle, LS_READ, LS_FOREVER) == -1 )
        return -1;

    size_t bytes = lwip_recv ( HANDLE_TO_SOCKET(aHandle), (void*) aBuffer, (size_t) aBytes, 0);

    LOGFUNCOUT();
    return bytes;
}

int32_t OsNetworkReceiveFrom(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes, TIpAddress* aAddress, uint16_t* aPort )
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;

    LOGFUNCIN();

    struct sockaddr_in s;
    socklen_t len = sizeof(s);

    if ( local_select(aHandle, LS_READ, LS_FOREVER) == -1 )
        return -1;

    int bytes = lwip_recvfrom ( HANDLE_TO_SOCKET(aHandle), (void*) aBuffer, (size_t) aBytes, 0, (struct sockaddr*) &s, &len );

    if ( bytes == -1 )
        return -1;
    
    if ( s.sin_family != AF_INET )
        return -1;
    
    *aAddress   = s.sin_addr.s_addr;
    *aPort      = ntohs(s.sin_port);
    
    LOGFUNCOUT();
    return bytes;
}

int32_t OsNetworkInterrupt(THandle aHandle, int32_t aInterrupt)
{
    LOGFUNCIN();
    OsNetworkHandle_SetInterrupted(aHandle, aInterrupt);
    LOGFUNCOUT();
    return 0;
}

int32_t OsNetworkClose(THandle aHandle)
{
    LOGFUNCIN();

    int err = lwip_close ( HANDLE_TO_SOCKET(aHandle) );

    if ( err )
    {
        LOG("THINGS\n");
        LOGFUNCOUT();
        return -1;
    }
    LOGFUNCOUT();
    OsNetworkHandle_Destroy(aHandle);
    return 0;
}

int32_t OsNetworkListen(THandle aHandle, uint32_t aSlots)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;

    LOGFUNCIN();

    int result = lwip_listen ( HANDLE_TO_SOCKET(aHandle), (int) aSlots );
    
    LOGFUNCOUT();
    return result;
}

int32_t OsNetworkGetHostByName(const char* aAddress, TIpAddress* aHost)
{
    struct hostent ret;
    struct hostent* result;
    int errnop, err;
    char buffer[GETHOSTBYNAME_BUFFER_BYTES];

    do
    {
        err = lwip_gethostbyname_r(aAddress, &ret, buffer, sizeof(buffer), &result, &errnop);
    
    } while ( err && (errnop == TRY_AGAIN) );
    
    if ( err )
        return -1;

    if ( result == NULL )
        return -1;

    memcpy(aHost, *(result->h_addr_list), sizeof(TIpAddress));

    return 0;
}

static int set_socket_option_int(THandle aHandle, int aOptName, int aVal)
{
    return lwip_setsockopt ( HANDLE_TO_SOCKET(aHandle), SOL_SOCKET, aOptName, &aVal, sizeof(int));
}

int32_t OsNetworkSocketSetSendBufBytes(THandle aHandle, uint32_t aBytes)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;
    
    return set_socket_option_int(aHandle, SO_SNDBUF, (int) aBytes);
}

int32_t OsNetworkSocketSetRecvBufBytes(THandle aHandle, uint32_t aBytes)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;

    return set_socket_option_int(aHandle, SO_RCVBUF, (int) aBytes);
}

int32_t OsNetworkSocketSetReceiveTimeout(THandle aHandle, uint32_t aMilliSeconds)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;

    struct timeval t;
    t.tv_sec = aMilliSeconds / 1000;
    t.tv_usec = (aMilliSeconds % 1000) * 1000;

    return lwip_setsockopt ( HANDLE_TO_SOCKET(aHandle), SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(struct timeval));
}

int32_t OsNetworkTcpSetNoDelay(THandle aHandle)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;

    return set_socket_option_int(aHandle, IPPROTO_TCP, TCP_NODELAY);
}

int32_t OsNetworkSocketSetReuseAddress(THandle aHandle)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;
        
    return set_socket_option_int(aHandle, SO_REUSEADDR, 1);
}

int32_t OsNetworkSocketSetMulticastTtl(THandle aHandle, uint8_t aTtl)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;
        
    return lwip_setsockopt ( HANDLE_TO_SOCKET(aHandle), IPPROTO_IP, IP_MULTICAST_TTL, &aTtl, sizeof(uint8_t));
}

int32_t OsNetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;
        
    struct ip_mreq m = {
        .imr_multiaddr.s_addr = aAddress,
        .imr_interface.s_addr = aInterface
    };

    return lwip_setsockopt ( HANDLE_TO_SOCKET(aHandle), IPPROTO_IP, IP_ADD_MEMBERSHIP, &m, sizeof(m) );
}

int32_t OsNetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress)
{
    if ( OsNetworkHandle_IsInterrupted(aHandle) )
        return -1;
        
    struct ip_mreq m = {
        .imr_multiaddr.s_addr = aAddress,
        .imr_interface.s_addr = aInterface
    };

    return lwip_setsockopt ( HANDLE_TO_SOCKET(aHandle), IPPROTO_IP, IP_DROP_MEMBERSHIP, &m, sizeof(m));
}

int32_t OsNetworkListAdapters(OsNetworkAdapter** aAdapters, uint32_t aUseLoopback)
{
    struct netif* n;
    OsNetworkAdapter* start = NULL;
    OsNetworkAdapter* end = NULL;
    
    for ( n = netif_list ; n != NULL ; n = n->next )
    {
        if ( aUseLoopback )
            if ( n->name[0] != 'l' || n->name[1] != 'o' )
                continue;
        
        if ( !netif_is_up(n) )
            continue;
        
        OsNetworkAdapter *a = (OsNetworkAdapter*) malloc(sizeof(OsNetworkAdapter));

        if ( a == NULL )
        {
            OsNetworkFreeInterfaces(start);
            return -1;
        }

        // Stash lwip interface name (2 chars, no termination) in iReserved
        char* name_reserved = (char*) &(a->iReserved);
        name_reserved[0] = n->name[0];
        name_reserved[1] = n->name[1];
        name_reserved[2] = '\0';

        // Copy info
        a->iAddress = (TIpAddress) n->ip_addr.addr;
        a->iNetMask = (TIpAddress) n->netmask.addr;
        a->iName    = name_reserved;
        a->iNext    = NULL;

        // Push on to end of list. We reverse netif_list as loopback is first.
        if ( start == NULL )
            start = end = a;
        else
        {
            end->iNext = a;
            end = a;
        }
    }
    
    *aAdapters = start;
    
    return 0;
}

void OsNetworkFreeInterfaces(OsNetworkAdapter* aAdapters)
{
    while ( aAdapters != NULL )
    {
        OsNetworkAdapter* n = aAdapters;
        aAdapters = aAdapters->iNext;
        free(n);
    }
}

void OsNetworkSetInterfaceChangedObserver(InterfaceListChanged aCallback, void* aArg)
{
}

