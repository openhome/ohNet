/**
 * Interface between UPnP library and the underlying Operating System
 *
 * Unless otherwise specified, each function requires a non-trivial implementation.
 * Functions listed here are not permitted to throw exceptions.  Failure should be
 * indicated by returning an error code instead.
 */

#ifndef HEADER_OS_C
#define HEADER_OS_C

#include <OpenHome/OsTypes.h>
#include <OpenHome/Defines.h>

/**
 * 'Null' handle implying no underlying OS object exists
 */
#define kHandleNull  (0)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Big endian representation of a 16-bit integer for little endian builds and vice-versa
 */
static INLINE uint16_t SwapEndian16(uint16_t aValue)
{
    return ((aValue & 0xff00) >> 8)
        |  ((aValue & 0x00ff) << 8);
}

/**
 * Big endian representation of a 32-bit integer for little endian builds and vice-versa
 */
static INLINE uint32_t SwapEndian32(uint32_t aValue)
{
    return ((aValue & 0xff000000) >> 24)
        |  ((aValue & 0x00ff0000) >> 8 )
        |  ((aValue & 0x0000ff00) << 8 )
        |  ((aValue & 0x000000ff) << 24);
}

/**
 * Called when the UPnP library is initialised.
 *
 * This function will be called before any other function defined in this header.
 *
 * @return  Valid OsContext on success; NULL on failure
 */
OsContext* OsCreate();

/**
 * Called when the UPnP library is closed.
 *
 * No other functions defined in this header will be called after this function.
 *
 * @param[in] aContext     Returned from OsCreate().
 */
void OsDestroy(OsContext* aContext);

/**
 * Terminate the process.
 *
 * Will only be called in response to a fatal error.
 * No other functions defined in this header will be called after this function.
 *
 * @param[in] aContext     Returned from OsCreate().
 */
void OsQuit(OsContext* aContext);

/**
 * Initialise a stack trace for the current call stack.
 *
 * Non-trivial implementation of this, and every other OsStackTrace function is entirely optional.
 *
 * This will be called for every exception thrown inside ohNet so it is preferable if
 * it can do minimal work, deferring symbol lookup until OsStackTraceEntry is called.
 *
 * @param[in] aContext     Returned from OsCreate().
 *
 * @return  A valid handle on success; kHandleNull if creation failed.
 */
THandle OsStackTraceInitialise(OsContext* aContext);

/**
 * Create a deep copy of an existing stack trace.
 *
 * Both the original and copy will have OsStackTraceFinalise called.
 *
 * @param[in] aStackTrace  Handle earlier returned from either OsStackTraceInitialise
 *                         or OsStackTraceCopy.  May be kHandleNull.
 *
 * @return  A valid handle on success; kHandleNull if creation failed.
 */
THandle OsStackTraceCopy(THandle aStackTrace);

/**
 * Return the number of entries in a call stack.
 *
 * @param[in] aStackTrace  Handle earlier returned from either OsStackTraceInitialise
 *                         or OsStackTraceCopy.  May be kHandleNull.
 *
 * @return  Number of entries in the call stack.
 */
uint32_t OsStackTraceNumEntries(THandle aStackTrace);

/**
 * Return the name of a function at a given point in a call stack.
 *
 * @param[in] aStackTrace  Handle earlier returned from either OsStackTraceInitialise
 *                         or OsStackTraceCopy.  May be kHandleNull.
 * @param[in] aIndex       Index of the item to lookup the name for.
 *                         Index is zero-based with 0 being the current function.
 *
 * @return  Symbol name.  Will not be freed by the caller.  The name pointer must remain
 *                        valid until the next call to either OsStackTraceEntry or
 *                        OsStackTraceFinalise for this handle.
 *                        Note that implementors are free to include as much or little information
 *                        as they want.  e.g. symbol address can be included or excluded.
 */
const char* OsStackTraceEntry(THandle aStackTrace, uint32_t aIndex);

/**
 * Finalise a stack trace, freeing all resources associated with it.
 *
 * @param[in] aStackTrace  Handle earlier returned from either OsStackTraceInitialise
 *                         or OsStackTraceCopy.  May be kHandleNull.
 */
void OsStackTraceFinalise(THandle aStackTrace);

/**
 * Return the current time in microseconds.
 *
 * This is only used to determine relative time rather than absolute time, so the returned time
 * can be relative anything approriate for this implementation.
 *
 * @param[in] aContext     Returned from OsCreate().
 */
uint64_t OsTimeInUs(OsContext* aContext);

/**
 * Write text to a console
 *
 * Used by unit tests only
 *
 * @param[in] aStr        Nul terminated string to be written
 */
void OsConsoleWrite(const char* aStr);

/**
 * Return the platform name and version number
 *
 * @param[in] aContext    Returned from OsCreate().
 * @param[out] aName      Must be set to the platform name.  The caller will not take
 *                        ownership of the string so it should either be const or freed
 *                        in OsDestroy
 * @param[out] aMajor     Must be set to the major version number of the platform
 * @param[out] aMinor     Must be set to the minor version number of the platform
 */
void OsGetPlatformNameAndVersion(OsContext* aContext, char** aName, uint32_t* aMajor, uint32_t* aMinor);

/**
 * Create a semaphore.
 *
 * @param[in] aContext    Returned from OsCreate().
 * @param[in] aName       Name for this semaphore.  May not be unique.
 *                        Maximum length is 4 characters.
 * @param[in] aCount      Initial count.  If this is greater than zero, the first aCount
 *                        calls to Wait() will complete immediately
 *
 * @return  a valid handle on success; kHandleNull if creation failed.
 */
THandle OsSemaphoreCreate(OsContext* aContext, const char* aName, uint32_t aCount);

/**
 * Destroy a semaphore.
 *
 * Guaranteed to be called for each handle returned by SemaphoreCreate().  May be
 * called when the semaphore has a non-zero count.  No further operations will be
 * attempted using this handle.
 *
 * @param[in] aSem        Semaphore handle returned from SemaphoreCreate()
 */
void OsSemaphoreDestroy(THandle aSem);

/**
 * Wait on the semaphore.
 *
 * Will complete immediately if the semaphore has a non-zero count;
 * blocks indefinitely otherwise.
 *
 * @param[in] aSem        Semaphore handle returned from SemaphoreCreate()
 *
 * @return  0 on success; <0 on failure
 *          Note that a failure will be treated as a fatal error by the caller
 */
int32_t OsSemaphoreWait(THandle aSem);

/**
 * Wait on a semaphore but don't allow it to block indefinately.
 *
 * @param[in] aSem        Semaphore handle returned from SemaphoreCreate()
 * @param[in] aTimeoutMs  The maximum time (in milliseconds) to wait for a signal
 *
 * @return  >0 if the semaphore was signalled; zero if it timed out; <0 on failure
 *          The semaphore's count must only be decremented if true is returned
 *          Note that a failure will be treated as a fatal error by the caller
 */
int32_t OsSemaphoreTimedWait(THandle aSem, uint32_t aTimeoutMs);

/**
 * Clear any pending signals on a semaphore
 *
 * This is equivalent to repeated calls to Wait() until the next one would block
 *
 * @param[in] aSem        Semaphore handle returned from SemaphoreCreate()
 *
 * @return  1 if pending signal(s) were cleared; 0 if the semaphore was already clear
 */
uint32_t OsSemaphoreClear(THandle aSem);

/**
 * Signal a semaphore.
 *
 * Each call should either unblock a single thread which is already waiting or unblock
 * the next thread which waits.
 *
 * @param[in] aSem        Semaphore handle returned from SemaphoreCreate()
 *
 * @return  0 on success; <0 on failure
 *          Note that a failure will be treated as a fatal error by the caller
 */
int32_t OsSemaphoreSignal(THandle aSem);

/**
 * Create a mutex.
 *
 * @param[in] aContext    Returned from OsCreate().
 * @param[in] aName       Name for this mutex.  May not be unique.
 *                        Maximum length is 4 characters.
 *
 * @return  a valid handle on success; kHandleNull if creation failed.
 */
THandle OsMutexCreate(OsContext* aContext, const char* aName);

/**
 * Destroy a mutex.  No further operations will be attempted using this handle.
 *
 * Guaranteed to be called for each handle returned by MutexCreate().  Will not be
 * called for locked mutexes.  No further operations will be attempted using this handle.
 *
 * @param[in] aMutex  Mutex handle returned from MutexCreate()
 */
void OsMutexDestroy(THandle aMutex);

/**
 * Lock a mutex.
 *
 * Will block indefinitely if another thread has the mutex locked.
 *
 * @param[in] aMutex  Mutex handle returned from MutexCreate()
 *
 * @return  0 on success
 *          -1 if called by a thread which already holds the lock
 *          -2 on any other error
 *          Note that a failure will be treated as a fatal error by the caller
 */
int32_t OsMutexLock(THandle aMutex);

/**
 * Unlock a mutex
 *
 * Will not be called if the current thread does not have the mutex locked.
 *
 * @param[in] aMutex  Mutex handle returned from MutexCreate()
 *
 * @return  0 on success; <0 on failure
 *          Note that a failure will be treated as a fatal error by the caller
 */
int32_t OsMutexUnlock(THandle aMutex);

/**
 * Pointer to a function which must be called from the native thread entrypoint
 *
 * Note that the function pointed to sets up exception handlers used by the ASSERT
 * macro so native thread entrypoints must not use ASSERT.
 *
 * @param[in] aArg         Argument passed to ThreadCreate()
 */
typedef void(*ThreadEntryPoint)(void*);

/**
 * Create a thread.
 *
 * @param[in] aContext    Returned from OsCreate().
 * @param[in] aName        Name for this thread.  May not be unique.
 *                         Maximum length is 4 characters.
 * @param[in] aPriority    Priority the thread should run at.  Will be in the range
 *                         (50 - 150) which may need to be mapped onto a suitable native
 *                         range.  If thread priorities are not supported, this value
 *                         should be stored and returned by calls to ThreadPriority()
 * @param[in] aStackBytes  Size of the thread stack in bytes.  If this is 0 a sensible
 *                         default value should be used.
 * @param[in] aEntryPoint  Pointer to a function which must be called from the native
 *                         thread entrypoint
 * @param[in] aArg         Pointer to pass to aEntryPoint.  This should be stored in
 *                         thread local storage of the created thread for later retrieval
 *                         by OsThreadTls().
 *
 * @return  a valid handle on success; kHandleNull if creation failed.
 */
THandle OsThreadCreate(OsContext* aContext, const char* aName, uint32_t aPriority,
                       uint32_t aStackBytes, ThreadEntryPoint aEntryPoint, void* aArg);

/**
 * Allow platform code to install any per-thread signal handlers or equivalent.
 *
 * Called once per call to OsThreadCreate().  Is called in the context of the
 * newly created thread.
 */
void OsThreadInstallSignalHandlers();

/**
 * Return the 'aArg' value passed to the entrypoint for the current thread
 *
 * @param[in] aContext    Returned from OsCreate().
 */
void* OsThreadTls(OsContext* aContext);

/**
 * Destroy a thread.
 *
 * This function will only be called when the native thread has exited.
 *
 * @param[in] aThread      Thread handle returned from ThreadCreate()
 */
void OsThreadDestroy(THandle aThread);

/**
 * Query whether the threading system supports setting different priorities.
 *
 * @param[in] aContext    Returned from OsCreate().
 *
 * @return  non-zero if priorities (at least the range passed to OsThreadCreate)
 *          are supported; zero otherwise
 */
int32_t OsThreadSupportsPriorities(OsContext* aContext);

/**
 * Types of network socket
 */
typedef enum
{
    eOsNetworkSocketStream   = 1 /**< used by TCP sockets */
   ,eOsNetworkSocketDatagram = 2 /**< used by UDP sockets */
} OsNetworkSocketType;


/**
 * Create a socket.
 *
 * This is equivalent to the BSD socket() function with two of its parameters assumed
 * to be constant - 'af' should always be 2 (IpV4) and 'protocol' should always be 0.
 *
 * @param[in] aContext     Returned from OsCreate().
 * @param[in] aSocketType  The type of socket to create
 *
 * @return  a valid handle on success; kHandleNull if creation failed.
 */
THandle OsNetworkCreate(OsContext* aContext, OsNetworkSocketType aSocketType);

/**
 * Assign a name to a socket.
 *
 * This is equivalent to the BSD bind() function
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aAddress     IpV4 address (in network byte order)
 * @param[in] aPort        Port [0..65535].  If 0 is passed, this will be set to the port the OS selects
 *
 * @return  0 on success; -2 if the name is already in use; -1 on any other failure
 */
int32_t OsNetworkBind(THandle aHandle, TIpAddress aAddress, uint32_t aPort);

/**
 * Assign a name to a multicast socket.
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aAddress     IpV4 address (in network byte order)
 * @param[in] aMulticast   IpV4 address (in network byte order)
 * @param[in] aPort        Port [0..65535].  If 0 is passed, this will be set to the port the OS selects
 *
 * @return  0 on success; -2 if the name is already in use; -1 on any other failure
 */
int32_t OsNetworkBindMulticast(THandle aHandle, TIpAddress aAdapter, TIpAddress aMulticast, uint32_t aPort);

/**
 * Get the socket port.
 *
 * This is equivalent to the BSD bind() function
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aPort        Port set to the port of the socket
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkPort(THandle aHandle, uint32_t* aPort);

/**
 * Connect to a (possibly remote) socket, specifying a timeout to fail after
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aAddress     IpV4 address (in network byte order) to connect to
 * @param[in] aPort        Port [0..65535] to connect to
 * @param[in] aTimeoutMs   Number of milliseconds to wait.  An error will be returned
 *                         if the connection did not complete or fail before this.
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkConnect(THandle aHandle, TIpAddress aAddress, uint16_t aPort, uint32_t aTimeoutMs);

/**
 * Send data to the endpoint we're OsNetworkConnect()ed to
 *
 * This is equivalent to the BSD send() function
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aBuffer      Data to send
 * @param[in] aBytes       Number of bytes of 'aBuffer' to send
 *
 * @return  number of bytes sent (>0) on success; -1 on failure
 */
int32_t OsNetworkSend(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes);

/**
 * Send data to the specified endpoint
 *
 * This is equivalent to the BSD sendto() function
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aBuffer      Data to send
 * @param[in] aBytes       Number of bytes of 'aBuffer' to send
 * @param[in] aAddress     IpV4 address (in network byte order) to send to
 * @param[in] aPort        Port [0..65535] to send to
 *
 * @return  number of bytes sent (>0) on success; -1 on failure
 */
int32_t OsNetworkSendTo(THandle aHandle, const uint8_t* aBuffer, uint32_t aBytes, TIpAddress aAddress, uint16_t aPort);

/**
 * Receive 0..aBytes of data from the endpoint we're OsNetworkConnect()ed to
 *
 * This is equivalent to the BSD recv() function
 *
 * @param[in]  aHandle     Socket handle returned from OsNetworkCreate()
 * @param[out] aBuffer     Buffer to receive data into.  Must have been allocated by the caller
 * @param[in]  aBytes      Maximum number of bytes of data 'aBuffer' can hold
 *
 * @return  number of bytes received (0..aBytes) on success; -1 on failure
 */
int32_t OsNetworkReceive(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes);

/**
 * Receive 0..aBytes of data, setting the sender's endpoint if the transport permits
 *
 * This is equivalent to the BSD recvfrom() function
 *
 * @param[in]  aHandle     Socket handle returned from OsNetworkCreate()
 * @param[out] aBuffer     Buffer to receive data into.  Must have been allocated by the caller
 * @param[in]  aBytes      Maximum number of bytes of data 'aBuffer' can hold
 * @param[in]  aAddress    IpV4 address (in network byte order) to receive from
 * @param[in]  aPort       Port [0..65535] to receive from
 *
 * @return  number of bytes received (0..aBytes) on success; -1 on failure
 */
int32_t OsNetworkReceiveFrom(THandle aHandle, uint8_t* aBuffer, uint32_t aBytes, TIpAddress* aAddress, uint16_t* aPort);

/**
 * Stop a socket's send/receive operations, interrupting any pending request.
 *
 * All subsequent operations other than OsNetworkClose() must fail when a socket
 * is in an interrupted state.  Normal operation should resume when this is called
 * with aInterrupt set to 0.
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aInterrupt   1 if the socket should be interrupted (fail pending and
 *                         subsequent operations other than close); 0 if normal
 *                         behaviour should be resumed.
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkInterrupt(THandle aHandle, int32_t aInterrupt);

/**
 * Close a socket.
 *
 * This is equivalent to the BSD close() function.
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkClose(THandle aHandle);

/**
 * Treat a socket as a passive endpoint of a connection.  The socket can later
 * receive but not send data
 *
 * This is equivalent to the BSD listen() function
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aSlots       Maximum number of messages which will be queued
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkListen(THandle aHandle, uint32_t aSlots);

/**
 * Establish a client-server connection on the server side
 *
 * This is equivalent to the BSD accept() function
 *
 * @param[in]  aHandle         Socket handle returned from OsNetworkCreate()
 * @param[out] aClientAddress  IPv4 address of client.  0 on error.
 * @param[out] aClientPort     Port [1..65535] of client.  0 on error
 *
 * @return  a valid handle on success; kHandleNull if creation failed.
 */
THandle OsNetworkAccept(THandle aHandle, TIpAddress* aClientAddress, uint32_t* aClientPort);

/**
 * Convert a string into a IpV4 address
 *
 * This is equivalent to the BSD gethostbyname() function
 *
 * @param[in] aAddress     Address as a string (e.g. www.abcd.org)
 * @param[out] aHost       IpV4 equivalent of 'aAddress'.  Must not be NULL.
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkGetHostByName(const char* aAddress, TIpAddress* aHost);

/**
 * Set the size of a socket's send buffer
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aBytes       New size for the send buffer
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkSocketSetSendBufBytes(THandle aHandle, uint32_t aBytes);

/**
 * Set the size of a socket's receive (recv) buffer
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aBytes       New size for the recv buffer
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkSocketSetRecvBufBytes(THandle aHandle, uint32_t aBytes);

/**
 * Modify the socket's receive timeout
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aTimeoutMs   New timeout value in milliseconds
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkSocketSetReceiveTimeout(THandle aHandle, uint32_t aTimeoutMs);

/**
 * Do not delay transmission of data.
 * Note that this can increase performance but also increases network congestion
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkTcpSetNoDelay(THandle aHandle);

/**
 * Allow a socket to bind to a port that is already in use by another socket
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkSocketSetReuseAddress(THandle aHandle);

/**
 * Set the ttl (time to live) value, affecting whether multicast datagrams are
 * forwarded beyond the local network
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aTtl         New ttl value
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkSocketSetMulticastTtl(THandle aHandle, uint8_t aTtl);

/**
 * Add a socket to a given multicast group
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aInterface   IpV4 address (in network byte order) specifying the network
 *                         interface on which the multicast group should be joined.
 *                         If this is 0, the default multicast interface will be used.
 * @param[in] aAddress     IpV4 address (in network byte order) specifying the multicast group
 * @param[in] aPort        Port [0..65535].  If 0 is passed, this will be set to the port the OS selects
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkSocketMulticastAddMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress);

/**
 * Remove a socket from a given mukticast group
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aAddress     IpV4 address (in network byte order) specifying the multicast group
 * @param[in] aInterface   IpV4 address (in network byte order) specifying the network
 *                         interface on which the multicast group should be dropped.
 *                         If this is 0, the default multicast interface will be used.
 * @param[in] aPort        Port [0..65535]
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkSocketMulticastDropMembership(THandle aHandle, TIpAddress aInterface, TIpAddress aAddress);

/**
 * Set the interface for sending multicast requests from this socket
 *
 * @param[in] aHandle      Socket handle returned from OsNetworkCreate()
 * @param[in] aInterface   IpV4 address (in network byte order) specifying the network
 *                         interface on which the multicast group should be joined.
 *                         If this is 0, the default multicast interface will be used.
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkSocketSetMulticastIf(THandle aHandle, TIpAddress aInterface);

/**
 * Representation of a network interface
 */
typedef struct OsNetworkAdapter
{
    TIpAddress iAddress;  /**< Address of the interface */
    char*      iName;     /**< Nul-terminated name of the interface */
    TIpAddress iNetMask;  /**< netmask for the interface */
    int32_t    iReserved; /**< for OS-internal use */
    struct OsNetworkAdapter* iNext; /**< Pointer to next interface or NULL */
} OsNetworkAdapter;

#define LOOPBACK_EXCLUDE (0) /* exclude loopback from list of available subnets */
#define LOOPBACK_USE     (1) /* exclude everything but loopback from list of available subnets */
#define LOOPBACK_INCLUDE (2) /* include loopback in list of available subnets */

/**
 * Return a list of all available network interfaces (aka adaptors).
 *
 * The first interface listed for each subnet will be preferred.  Wired interfaces
 * for a subnet should be listed before wireless ones.
 * A loopback interface should only be reported if no other interfaces are present.
 *
 * @param[in] aContext          Returned from OsCreate().
 * @param[out] aInterfaces      List of available interfaces.  Allocated inside this function;
 *                              the caller should use OsNetworkFreeInterfaces to free it
 * @param[out] aUseLoopback     2 if all interfaces, including loopback, should be returned;
 *                              1 if only the loopback interface should be returned;
 *                              0 (default) if normal behaviour is required
 *
 * @return  0 on success; -1 on failure
 */
int32_t OsNetworkListAdapters(OsContext* aContext, OsNetworkAdapter** aInterfaces, uint32_t aUseLoopback);

/**
 * Destroy list returned by OsNetworkListAdapters.
 *
 * @param[in] aInterfaces       Returned by OsNetworkListAdapters
 * @param[in] aInterfaceCount   Returned by OsNetworkListAdapters
 */
void OsNetworkFreeInterfaces(OsNetworkAdapter* aInterfaces);

/**
 * Pointer to a function which will be called if the list of available network interfaces changes
 *
 * @param[in] aArg         Argument passed to OsNetworkSetInterfaceChangedObserver()
 */
typedef void(*InterfaceListChanged)(void*);

/**
 * Register a callback to be run if the list of available network interfaces changes
 *
 * Only a single observer can be set.  The UPnP library will function correctly if
 * this function has a trivial implementation (i.e. does not generate callbacks when
 * interfaces change).  Note however that the library may sometimes have to be manually
 * stopped then restarted after some changes in interfaces.
 *
 * @param[in] aContext     Returned from OsCreate().
 * @param[in] aCallback    Callback to run if the interface list changes
 * @param[in] aArg         Argument to pass to the callback
 */
void OsNetworkSetInterfaceChangedObserver(OsContext* aContext, InterfaceListChanged aCallback, void* aArg);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HEADER_OS_C
