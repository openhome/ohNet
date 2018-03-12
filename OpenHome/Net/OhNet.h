/**
 * UPnP library startup / shutdown
 */

#ifndef HEADER_UPNP
#define HEADER_UPNP

#include <OpenHome/Buffer.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Core/FunctorAsync.h>
#include <OpenHome/FunctorMsg.h>
#include <OpenHome/FunctorNetworkAdapter.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/C/OhNet.h> // for OhNetCallbackFreeExternal only
#include <OpenHome/Private/Shell.h> // for Shell::kServerPortDefault only

#include <vector>

namespace OpenHome {

/**
 * For internal use only.
 */
class IStackObject
{
public:
    virtual void ListObjectDetails() const = 0;
};

class Environment;

/**
 * Auto ptr for NetworkAdapter references.
 * @ingroup Core
 */
class DllExportClass AutoNetworkAdapterRef
{
public:
    AutoNetworkAdapterRef(Environment& aEnv, const char* aCookie); // creates ref to stack's current adapter
    AutoNetworkAdapterRef(NetworkAdapter* aAdapter, const char* aCookie);
    ~AutoNetworkAdapterRef();
    NetworkAdapter* Adapter();
    const NetworkAdapter* Adapter() const;
private:
    NetworkAdapter* iAdapter;
    const char* iCookie;
};

/**
 * Represents a single network interface
 * @ingroup Core
 */
class DllExportClass NetworkAdapter : private IStackObject
{
public:
    /**
     * Construct a network interface
     *
     * Not intended for external use
     *
     * @param[in] aEnv      Returned by UpnpLibrary::Initialise().
     * @param[in] aAddress  IPv4 address for the interface (in network byte order)
     * @param[in] aNetMask  IPv4 net mask for the interface (in network byte order)
     * @param[in] aDhcp     IPv4 address for the DHCP server for the interface (in network byte order)
     * @param[in] aGateway  IPv4 address for the Gateway for the interface (in network byte order)
     * @param[in] aName     Name for the interface.  Will be copied inside this function
     *                      so can safely be deleted by the caller when this returns
     * @param[in] aCookie   String identifying the caller.  Needn't be unique although a
     *                      recognisable string will help in debugging the cause of any
     *                      leaked NetworkAdapter references.  The later matching call
     *                      to RemoveRef must use the same cookie.
     */
    NetworkAdapter(Environment& aEnv, TIpAddress aAddress, TIpAddress aNetMask,
                   TIpAddress aDhcp, TIpAddress aGateway,
                   const char* aName, const char* aCookie);
    /**
     * Add a reference.  This NetworkAdapter instance won't be deleted until the last reference is removed.
     *
     * Callers must (eventually) call RemoveRef() exactly once for each call to AddRef().
     *
     * @param[in] aCookie   String identifying the caller.  Needn't be unique although a
     *                      recognisable string will help in debugging the cause of any
     *                      leaked NetworkAdapter references.  The later matching call
     *                      to RemoveRef must use the same cookie.
     */
    void AddRef(const char* aCookie);
    /**
     * Remove a reference previously claimed by the c'tor or by AddRef().
     *
     * This object will be deleted when the reference count reaches zero.
     *
     * @param[in] aCookie   String identifying the caller.
     *                      Must match an earlier cookie used in either the ctor or AddRef().
     */
    void RemoveRef(const char* aCookie);
    /**
     * Query the IP address of the interface
     *
     * @return  IPv4 address for the interface (in network byte order)
     */
    TIpAddress Address() const;
    /**
     * Query the subnet the interface operates on
     *
     * @return  IPv4 address for the subnet (in network byte order)
     */
    TIpAddress Subnet() const;
    /**
     * Query the netmask of the interface
     *
     * @return  netmask for the interface (in network byte order)
     */
    TIpAddress Mask() const;
    /**
     * Query whether the subnet this interface operates on contains a given IP address
     *
     * @param[in] aAddress  IPv4 address being queried
     *
     * @return  true if the address is part of the same subnet as this interface; false otherwise
     */
    bool ContainsAddress(TIpAddress aAddress) const;
    /**
     * Get the name of the network adapter.
     *
     * @return  The subnet name.  Can't be modified; will remain valid until this
     *          NetworkAdapter is deleted
     */
    const char* Name() const;
    /**
     * Get the full name of the network adapter.
     *
     * @return  String in the form a.b.c.d (name).
     *          The caller is responsible for freeing this.
     */
    char* FullName() const;
    /**
     * Query whether the host OS supports reporting DHCP server addresses.
     *
     * @return  true if DhcpServerAddress() will return a valid address; false otherwise
     */
    TBool DhcpServerAddressAvailable() const;
    /**
     * Query the address of the DHCP server for this adapter
     *
     * @return  IP address of the DHCP server for this adapter
     */
    TIpAddress DhcpServerAddress() const;
    /**
    * Query whether the host OS supports reporting Gateway addresses.
    *
    * @return  true if GatewayAddress() will return a valid address; false otherwise
    */
    TBool GatewayAddressAvailable() const;
    /**
     * Query the address of the gateway for this adapter
     *
     * @return  IP address of the gateway for this adapter
     */
    TIpAddress GatewayAddress() const;
private:
    virtual ~NetworkAdapter();
private: // from IStackObject
    void ListObjectDetails() const;
private:
    Environment* iEnv;
    TUint iRefCount;
    TIpAddress iAddress;
    TIpAddress iNetMask;
    TIpAddress iDhcpServer;
    TIpAddress iGateway;
    Brhz iName;
    std::vector<const char*> iCookies;
};

namespace Net {

class DefaultAsyncHandler;
class DefaultLogger;
/**
 * Initialisation options.
 *
 * Most options apply equally to Control Point and Device stacks.  Any functions that are
 * specific to a particular stack include either 'Cp' or 'Dv'
 * @ingroup Core
 */
class DllExportClass InitialisationParams
{
public:
    enum ELoopback
    {
        ELoopbackExclude // exclude loopback from list of available subnets
       ,ELoopbackUse     // exclude everything but loopback from list of available subnets
       ,ELoopbackInclude // include loopback in list of available subnets
    };
    enum EThreadScheduling
    {
        EScheduleDefault
       ,ESchedulePriority
       ,EScheduleNice
       ,EScheduleNone
    };
public:
    /**
     * Create a new InitialisationParams instance.
     * All properties default to sensible values.
     */
    static InitialisationParams* Create();
    ~InitialisationParams();

    void SetLogOutput(FunctorMsg aLogOutput);
    /**
     * Set a callback which will be run if the library encounters an error it
     * cannot recover from.  Suggested action if this is called is to exit the
     * process and restart the library and its owning application.
     * The string passed to the callback is an error message so would be useful
     * to log.
     */
    void SetFatalErrorHandler(FunctorMsg aFunctor);
    void SetAsyncBeginHandler(FunctorAsync aHandler);
    void SetAsyncEndHandler(FunctorAsync aHandler);
    void SetAsyncErrorHandler(FunctorAsync aHandler);
    void SetSubnetListChangedListener(Functor aFunctor);
    void SetSubnetAddedListener(FunctorNetworkAdapter aFunctor);
    void SetSubnetRemovedListener(FunctorNetworkAdapter aFunctor);
    void SetNetworkAdapterChangedListener(FunctorNetworkAdapter aFunctor);
    void SetThreadExitHandler(Functor aFunctor);
    /**
     * Set a timeout for TCP connections.  Must be greater that zero
     */
    void SetTcpConnectTimeout(uint32_t aTimeoutMs);
    /**
     * Set the time that msearch responses should be spread out over.
     * Must be between 1 and 5 (inclusive).
     */
    void SetMsearchTime(uint32_t aSecs);
    /**
     * Set the time-to-live value for msearches.
     */
    void SetMsearchTtl(uint32_t aTtl);
    /**
     * Set the number of threads which should be dedicated to eventing (handling
     * updates to subscribed state variables)
     * Must be greater than zero.
     */
    void SetNumEventSessionThreads(uint32_t aNumThreads);
    /**
     * Set the number of threads which should be dedicated to fetching
     * device/service XML.
     * A higher number of threads will allow faster population of device lists
     * but will also require more system resources.
     * Must be greater than zero.
     */
    void SetNumXmlFetcherThreads(uint32_t aNumThreads);
    /**
     * Set the number of threads which should be dedicated to invoking actions on devices.
     * A higher number of threads will allow faster population of device lists
     * but will also require more system resources.
     * Must be greater than zero.
     */
    void SetNumActionInvokerThreads(uint32_t aNumThreads);
    /**
     * Set the number of invocations (actions) which should be pre-allocated.
     * If more that this number are pending, the additional attempted invocations
     * will block until a pre-allocated slot becomes clear.
     * A higher number of invocations will decrease the likelihood and duration of
     * any UI-level delays but will also increase the peaks in RAM requirements.
     * Must be greater than zero.
     */
    void SetNumInvocations(uint32_t aNumInvocations);
    /**
     * Set the number of threads which should be dedicated to (un)subscribing
     * to state variables on a service + device.
     * A higher number of threads will allow faster population of device lists
     * but will also require more system resources.
     */
    void SetNumSubscriberThreads(uint32_t aNumThreads);
    /**
     * Set the duration control point subscriptions will request.
     */
    void SetSubscriptionDuration(uint32_t aDurationSecs);
    /**
     * It is possible for initial information on state variables to arrive before
     * a subscription is noted as complete.
     * Set the maximim time to wait before rejecting an event update from an unknown source.
     */
    void SetPendingSubscriptionTimeout(uint32_t aTimeoutMs);
    /**
     * Set a callback which will be used to free memory that is allocated outside the library
     * This is intended for C# wrappers and can be ignored by most (all?) other clients
     */
    void SetFreeExternalCallback(OhNetCallbackFreeExternal aCallback);
    /**
     * Limit the library to using only the loopback network interface.
     * Useful for testing but not expected to be used in production code
     */
    void SetUseLoopbackNetworkAdapter();
    /**
     * Include the loopback network interface in the list of available adapters.
     * Useful for testing but not expected to be used in production code
     */
    void SetIncludeLoopbackNetworkAdapter();
    /**
     * Set the maximum time between device announcements for the device stack
     */
    void SetDvMaxUpdateTime(uint32_t aSecs);
    /**
     * Set the number of threads which should be dedicated to processing
     * control/eventing/presentation requests.
     * A higher number of threads may allow faster response to multiple clients
     * making concurrent requests but will also require more system resources.
     */
    void SetDvNumServerThreads(uint32_t aNumThreads);
    /**
     * Set the number of threads which should be dedicated to publishing
     * changes to state variables on a service + device.
     * A higher number of threads will allow faster publication of changes
     * but will also require more system resources.
     */
    void SetDvNumPublisherThreads(uint32_t aNumThreads);
    /**
     * Set the priority of event publisher threads.
     */
    void SetDvPublisherThreadPriority(uint32_t aPriority);
    /**
     * Set a delay between publishing events from a single thread.
     * A value of 0 implies no delay.
     * Can be used in systems capable of priority-based scheduling to to allow
     * eventing to run at a very high priority without risking it blocking out
     * other high priority tasks.
     * Note that higher moderation times, give lower maximum eventing throughput.
     */
    void SetDvPublisherModerationTime(uint32_t aMillisecs);
    /**
     * Set the number of threads which will be dedicated to published
     * changes to state variables via WebSockets
     * One thread will be used per active (web browser) connection so a higher
     * number of threads will allow more concurrent clients but will also
     * require more system resources.
     */
    void SetDvNumWebSocketThreads(uint32_t aNumThreads);
    /**
     * Set the tcp port number the control point stack's UPnP event server will run on.
     * The default value is 0 (meaning that the OS will assign a port).
     * You should only set this if you know the full set of services (plus their port
     * requirements) running on a device.
     */ 
    void SetCpUpnpEventServerPort(TUint aPort);
    /**
     * Set the tcp port number the device stack's UPnP web server will run on.
     * The default value is 0 (OS-assigned).
     */ 
    void SetDvUpnpServerPort(TUint aPort);
    /**
     * Set the tcp port number the device stack's websocket servers will run on.
     * The default value is 0 (meaning that the OS will assign a port).
     * You should only set this if you know the full set of services (plus their port
     * requirements) running on a device.
     */
    void SetDvWebSocketPort(TUint aPort);
    /**
     * Enable use of Bonjour.
     * All DvDevice instances with an IResourceManager will be published using Bonjour.
     * If a device sets the "Upnp.MdnsHostName" attribute, its presentation will be available via http://[hostname].local.
     * Behaviour when more than one DvDevice sets the "MdnsHostName" attribute is undefined.
     */
    void SetDvEnableBonjour(const TChar* aHostName, TBool aRequiresMdnsCache);
    /**
     * Set the number of threads which will be dedicated LPEC clients.
     * One thread will be used per active connection so a higher number of threads
     * will allow more concurrent clients but will also require more system
     * resources.
     */
    void SetDvNumLpecThreads(uint32_t aNumThreads);
    /**
     * Set the tcp port number the device stack's LPEC servers will run on.
     * The default value is 0 (meaning that the OS will assign a port).
     * You should only set this if you know the full set of services (plus their port
     * requirements) running on a device.
     */
    void SetDvLpecServerPort(uint32_t aPort);
    /**
     * Inform ohNet that UDP will be measurably unreliable on even a local network.
     * (e.g. for an Apple device using wifi)
     * Some control point behaviours will change in this case (e.g. device lists may
     * signal that devices have been removed in fewer circumstances).
     */
    void SetHostUdpIsLowQuality(TBool aLow);
    /**
     * Set TimerManager priority.
     */
    void SetTimerManagerPriority(uint32_t aPriority);
    /**
     * Set UserAgent header to be reported by HTTP clients
     */
    void SetHttpUserAgent(const Brx& aUserAgent);
    /**
     * Enable use of debug shell
     */
    void SetEnableShell(TUint aPort = Shell::kServerPortDefault, TUint aSessionPriority = kPriorityNormal);
    /**
     * Set thread scheduling policy
     * EScheduleDefault is suitable for most OSes.
     * ESchedulePriority is preferable for *nix
     */
    void SetSchedulingPolicy(EThreadScheduling aPolicy);

    FunctorMsg& LogOutput();
    FunctorMsg& FatalErrorHandler();
    FunctorAsync& AsyncBeginHandler();
    FunctorAsync& AsyncEndHandler();
    FunctorAsync& AsyncErrorHandler();
    Functor& SubnetListChangedListener();
    FunctorNetworkAdapter& SubnetAddedListener();
    FunctorNetworkAdapter& SubnetRemovedListener();
    FunctorNetworkAdapter& NetworkAdapterChangedListener();
    Functor& ThreadExitHandler();
    uint32_t TcpConnectTimeoutMs() const;
    uint32_t MsearchTimeSecs() const;
    uint32_t MsearchTtl() const;
    uint32_t NumEventSessionThreads() const;
    uint32_t NumXmlFetcherThreads() const;
    uint32_t NumActionInvokerThreads() const;
    uint32_t NumInvocations() const;
    uint32_t NumSubscriberThreads() const;
    uint32_t SubscriptionDurationSecs() const;
    uint32_t PendingSubscriptionTimeoutMs() const;
    OhNetCallbackFreeExternal FreeExternal() const;
    ELoopback LoopbackNetworkAdapter() const;
    uint32_t DvMaxUpdateTimeSecs() const;
    uint32_t DvNumServerThreads() const;
    uint32_t DvNumPublisherThreads() const;
    uint32_t DvPublisherThreadPriority() const;
    uint32_t DvPublisherModerationTimeMs() const;
    uint32_t DvNumWebSocketThreads() const;
    uint32_t CpUpnpEventServerPort() const;
    uint32_t DvUpnpServerPort() const;
    uint32_t DvWebSocketPort() const;
    bool DvIsBonjourEnabled(const TChar*& aHostName, TBool& aRequiresMdnsCache) const;
    uint32_t DvNumLpecThreads();
    uint32_t DvLpecServerPort();
    bool IsHostUdpLowQuality();
    uint32_t TimerManagerPriority() const;
    const Brx& HttpUserAgent() const;
    TBool IsShellEnabled(TUint& aPort, TUint& aSessionPriority) const;
    EThreadScheduling SchedulingPolicy() const;
private:
    InitialisationParams();
    void FatalErrorHandlerDefault(const char* aMsg);
private:
    FunctorMsg iLogOutput;
    DefaultLogger* iDefaultLogger;
    FunctorMsg iFatalErrorHandler;
    FunctorAsync iAsyncBeginHandler;
    FunctorAsync iAsyncEndHandler;
    FunctorAsync iAsyncErrorHandler;
    DefaultAsyncHandler* iDefaultAsyncHandler;
    Functor iSubnetListChangedListener;
    FunctorNetworkAdapter iSubnetAddedListener;
    FunctorNetworkAdapter iSubnetRemovedListener;
    FunctorNetworkAdapter iNetworkAdapterChangedListener;
    Functor iThreadExitHandler;
    uint32_t iTcpConnectTimeoutMs;
    uint32_t iMsearchTimeSecs;
    uint32_t iMsearchTtl;
    uint32_t iNumEventSessionThreads;
    uint32_t iNumXmlFetcherThreads;
    uint32_t iNumActionInvokerThreads;
    uint32_t iNumInvocations;
    uint32_t iNumSubscriberThreads;
    uint32_t iSubscriptionDurationSecs;
    uint32_t iPendingSubscriptionTimeoutMs;
    OhNetCallbackFreeExternal iFreeExternal;
    ELoopback iUseLoopbackNetworkAdapter;
    uint32_t iDvMaxUpdateTimeSecs;
    uint32_t iDvNumServerThreads;
    uint32_t iDvNumPublisherThreads;
    uint32_t iDvPublisherModerationTimeMs;
    uint32_t iDvPublisherThreadPriority;
    uint32_t iDvNumWebSocketThreads;
    uint32_t iCpUpnpEventServerPort;
    uint32_t iDvUpnpWebServerPort;
    uint32_t iDvWebSocketPort;
    bool iHostUdpLowQuality;
    bool iEnableBonjour;
    bool iRequiresMdnsCache;
    Brhz iDvBonjourHostName;
    uint32_t iDvNumLpecThreads;
    uint32_t iDvLpecServerPort;
    uint32_t iTimerManagerThreadPriority;
    Brh iUserAgent;
    TBool iEnableShell;
    TUint iShellPort;
    TUint iShellSessionPriority;
    EThreadScheduling iSchedulingPolicy;
};

class CpStack;
class DvStack;

/**
 * Initialisation and finalisation of this library
 * @ingroup Core
 */
class DllExportClass Library
{
public:
    /**
     * Constructor.
     *
     * @param aInitParams  Initialisation options.  Ownership of these passes to the library.
     */
    Library(InitialisationParams* aInitParams);

    /**
     * Destructor.  No library function may be called after this.
     */
    ~Library();

    /**
     * Start the library as a UPnP control point stack
     *
     * @param aSubnet    The subnet to use.  Likely to be the Subnet() from a
     *                   NetworkAdapter returned by SubnetList.
     *
     * @return  Opaque pointer required by various other library functions.
     */
    CpStack* StartCp(TIpAddress aSubnet);

    /**
     * Start the library as a UPnP device stack
     *
     * @return  Opaque pointer required by various other library functions.
     */
    DvStack* StartDv();

    /**
     * Start the library as both UPnP control point and device stacks
     *
     * @param aSubnet    The subnet to use for both control point and device stacks.
     *                   Likely to be the Subnet() from a NetworkAdapter returned by SubnetList.
     * @param aCpStack   Opaque pointer required by various other library functions.
     * @param aDvStack   Opaque pointer required by various other library functions.
     */
    void StartCombined(TIpAddress aSubnet, CpStack*& aCpStack, DvStack*& aDvStack);

    /**
     * For internal use only
     *
     * @return  Environment instance
     */
    Environment& Env();

    /**
     * Create a vector of the available subnets.
     *
     * The returned vector and all its pointers are allocated.  Use DestroySubnetList
     * to later free this memory.
     *
     * @return  A newly allocated vector containing the adapter judged most suitable for
     *          each available subnet.
     */
    std::vector<NetworkAdapter*>* CreateSubnetList();

    /**
     * Destroy a subnet list created using CreateSubnetList().
     *
     * @param aSubnetList  Returned by CreateSubnetList().
     */
    static void DestroySubnetList(std::vector<NetworkAdapter*>* aSubnetList);

    /**
     * Create a vector of the available network adapters.
     *
     * The returned vector and all its pointers are allocated.  Use DestroyNetworkAdapterList
     * to later free this memory.
     *
     * @return  A newly allocated vector containing the list of available network adapters.
     */
    std::vector<NetworkAdapter*>* CreateNetworkAdapterList();

    /**
     * Destroy a network adapter list created using CreateNetworkAdapterList().
     *
     * @param aNetworkAdapterList  Returned by CreateNetworkAdapterList().
     */
    static void DestroyNetworkAdapterList(std::vector<NetworkAdapter*>* aNetworkAdapterList);

    /**
     * Set which subnet the library should use.
     * Device lists and subscriptions will be automatically updated.
     * No other subnet will be selected if aSubnet is not available
     *
     * @param aSubnet    The subnet to use.  Likely to be the Subnet() from a
     *                   NetworkAdapter returned by CreateSubnetList.
     */
    void SetCurrentSubnet(TIpAddress aSubnet);

    /**
     * Query which network adapter is currently selected.
     *
     * @param[in] aCookie   String identifying the caller.  Needn't be unique although a
     *                      recognisable string will help in debugging the cause of any
     *                      leaked NetworkAdapter references.  The later matching call
     *                      to RemoveRef must use the same cookie.
     *
     * @return  A pointer to the currently selected adapter with a reference claimed.
     *          Or NULL if there is no currently selected adapter.
     */
    NetworkAdapter* CurrentSubnetAdapter(const char* aCookie);

    /**
     * Force a refresh of the library's list of available network adapters
     *
     * This should only be required on platforms that are not capable of
     * automatically detecting adapter changes.
     */
    void RefreshNetworkAdapterList();

    /**
     * Inform the library that the application has been suspended.
     *
     * This is necessary if the application may be paused while other processes on
     * a device continued to be executed (e.g. when an app moves to background on iOS).
     * It is typically not necessary to call this when the host device hibernates.
     */
    void NotifySuspended();

    /**
     * Inform the library that the application has been resumed.
     *
     * This is necessary if the application may have been paused while other processes on
     * a device continued to be executed (e.g. when an app moves to background on iOS).
     * It is typically not necessary to call this when the host device resumes from hibernation.
     */
    void NotifyResumed();
private:
    OpenHome::Environment* iEnv;
    OpenHome::TBool iEnvOwner;
};


/**
 * Initialisation and finalisation of this library
 * @ingroup Core
 */
class DllExportClass UpnpLibrary
{
public:
    /**
     * Initialise the UPnP library.
     *
     * Must be called before any other library function.
     * Throws an exception in error cases.
     *
     * @param aInitParams  Initialisation options.  Ownership of these passes to the library.
     */
    static Environment* Initialise(InitialisationParams* aInitParams);

    /**
     * Lightweight alternative to UpnpLibraryInitialise.
     *
     * Intended for unit tests which are useful to platform porting only.
     * No class APIs other than Close() can be called if this is used.
     *
     * @param aInitParams  Initialisation options.  Only ILogOutput will be used.
     *                     Ownership of these passes to the library.
     */
    static Environment* InitialiseMinimal(InitialisationParams* aInitParams);

    /**
     * Start the library as a UPnP control point stack
     *
     * @param aSubnet    The subnet to use.  Likely to be the Subnet() from a
     *                   NetworkAdapter returned by SubnetList.
     */
    static void StartCp(TIpAddress aSubnet);

    /**
     * Start the library as a UPnP device stack
     */
    static void StartDv();

    /**
     * Start the library as both UPnP control point and device stacks
     *
     * @param aSubnet    The subnet to use for both control point and device stacks.
     *                   Likely to be the Subnet() from a NetworkAdapter returned by SubnetList.
     */
    static void StartCombined(TIpAddress aSubnet);

    /**
     * Close the UPnP library.
     *
     * Will not fail.  No more library functions should be called after this.
     */
    static void Close();

    /**
     * Create a vector of the available subnets.
     *
     * The returned vector and all its pointers are allocated.  Use DestroySubnetList
     * to later free this memory.
     *
     * @return  A newly allocated vector containing the adapter judged most suitable for
     *          each available subnet.
     */
    static std::vector<NetworkAdapter*>* CreateSubnetList();

    /**
     * Destroy a subnet list created using CreateSubnetList().
     *
     * @param aSubnetList  Returned by CreateSubnetList().
     */
    static void DestroySubnetList(std::vector<NetworkAdapter*>* aSubnetList);

    /**
     * Create a vector of the available network adapters.
     *
     * The returned vector and all its pointers are allocated.  Use DestroyNetworkAdapterList
     * to later free this memory.
     *
     * @return  A newly allocated vector containing the list of available network adapters.
     */
    static std::vector<NetworkAdapter*>* CreateNetworkAdapterList();

    /**
     * Destroy a network adapter list created using CreateNetworkAdapterList().
     *
     * @param aNetworkAdapterList  Returned by CreateNetworkAdapterList().
     */
    static void DestroyNetworkAdapterList(std::vector<NetworkAdapter*>* aNetworkAdapterList);

    /**
     * Set which subnet the library should use.
     * Device lists and subscriptions will be automatically updated.
     * No other subnet will be selected if aSubnet is not available
     *
     * @param aSubnet    The subnet to use.  Likely to be the Subnet() from a
     *                   NetworkAdapter returned by CreateSubnetList.
     */
    static void SetCurrentSubnet(TIpAddress aSubnet);

    /**
     * Query which network adapter is currently selected.
     *
     * @param[in] aCookie   String identifying the caller.  Needn't be unique although a
     *                      recognisable string will help in debugging the cause of any
     *                      leaked NetworkAdapter references.  The later matching call
     *                      to RemoveRef must use the same cookie.
     *
     * @return  A pointer to the currently selected adapter with a reference claimed.
     *          Or NULL if there is no currently selected adapter.
     */
    static NetworkAdapter* CurrentSubnetAdapter(const char* aCookie);

    /**
     * Force a refresh of the library's list of available network adapters
     *
     * This should only be required on platforms that are not capable of
     * automatically detecting adapter changes.
     */
    static void RefreshNetworkAdapterList();

    /**
     * Inform the library that the application has been suspended.
     *
     * This is necessary if the application may be paused while other processes on
     * a device continued to be executed (e.g. when an app moves to background on iOS).
     * It is typically not necessary to call this when the host device hibernates.
     */
    static void NotifySuspended();

    /**
     * Inform the library that the application has been resumed
     *
     * This is necessary if the application may have been paused while other processes on
     * a device continued to be executed (e.g. when an app moves to background on iOS).
     * It is typically not necessary to call this when the host device resumes from hibernation.
     */
    static void NotifyResumed();
};

} // namespace Net
} // namespace OpenHome
#endif // HEADER_UPNP
