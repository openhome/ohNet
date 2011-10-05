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
#include <OpenHome/Net/C/OhNet.h> // for OhNetCallbackFreeExternal only

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

/**
 * Represents a single network interface
 * @ingroup Core
 */
class NetworkAdapter : private IStackObject
{
public:
    /**
     * Construct a network interface
     *
     * Not intended for external use
     *
     * @param[in] aAddress  IPv4 address for the interface (in network byte order)
     * @param[in] aNetMask  IPv4 net mask for the interface (in network byte order)
     * @param[in] aName     Name for the interface.  Will be copied inside this function
     *                      so can safely be deleted by the caller when this returns
     */
    NetworkAdapter(TIpAddress aAddress, TIpAddress aNetMask, const char* aName);
    /**
     * Add a reference.  This NetworkAdapter instance won't be deleted until the last reference is removed.
     *
     * Callers must (eventually) call RemoveRef() exactly once for each call to AddRef().
     */
    void AddRef();
    /**
     * Remove a reference previously claimed by the c'tor or by AddRef().
     *
     * This object will be deleted when the reference count reaches zero.
     */
    void RemoveRef();
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
    bool ContainsAddress(TIpAddress aAddress);
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
private:
    ~NetworkAdapter();
private: // from IStackObject
    void ListObjectDetails() const;
private:
    TUint iRefCount;
    TIpAddress iAddress;
    TIpAddress iNetMask;
    Brhz iName;
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
class InitialisationParams
{
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
     * Set the number of threads which will be dedicated to published
     * changes to state variables via WebSockets
     * One thread will be used per active (web browser) connection so a higher
     * number of threads will allow more concurrent clients but will also
     * require more system resources.
     */
    void SetDvNumWebSocketThreads(uint32_t aNumThreads);
    /**
     * Set the tcp port number web socket servers will run on.
     * The default value is 0 (meaning that the OS will assign a port).
     * You should question your design if you need to use this.
     */
    void SetDvWebSocketPort(TUint aPort);
    /**
     * Enable use of Bonjour.
     * All DvDevice instances with an IResourceManager will be published using Bonjour.
     * If a device sets the "Upnp.MdnsHostName" attribute, its presentation will be available via http://[hostname].local.
     * Behaviour when more than one DvDevice sets the "MdnsHostName" attribute is undefined.
     * Note that enabling Bonjour will cause the device stack to run a http server on port 80, requiring root privileges on linux.
     */
    void SetDvEnableBonjour();

    FunctorMsg& LogOutput();
    FunctorMsg& FatalErrorHandler();
    FunctorAsync& AsyncBeginHandler();
    FunctorAsync& AsyncEndHandler();
    FunctorAsync& AsyncErrorHandler();
    Functor& SubnetListChangedListener();
    FunctorNetworkAdapter& SubnetAddedListener();
    FunctorNetworkAdapter& SubnetRemovedListener();
    FunctorNetworkAdapter& NetworkAdapterChangedListener();
    uint32_t TcpConnectTimeoutMs() const;
    uint32_t MsearchTimeSecs() const;
    uint32_t MsearchTtl() const;
    uint32_t NumEventSessionThreads() const;
    uint32_t NumXmlFetcherThreads() const;
    uint32_t NumActionInvokerThreads() const;
    uint32_t NumInvocations() const;
    uint32_t NumSubscriberThreads() const;
    uint32_t PendingSubscriptionTimeoutMs() const;
	OhNetCallbackFreeExternal FreeExternal() const;
    bool UseLoopbackNetworkAdapter() const;
	uint32_t DvMaxUpdateTimeSecs() const;
    uint32_t DvNumServerThreads() const;
    uint32_t DvNumPublisherThreads() const;
    uint32_t DvNumWebSocketThreads() const;
    uint32_t DvWebSocketPort() const;
    bool DvIsBonjourEnabled() const;
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
    uint32_t iTcpConnectTimeoutMs;
    uint32_t iMsearchTimeSecs;
    uint32_t iMsearchTtl;
    uint32_t iNumEventSessionThreads;
    uint32_t iNumXmlFetcherThreads;
    uint32_t iNumActionInvokerThreads;
    uint32_t iNumInvocations;
    uint32_t iNumSubscriberThreads;
    uint32_t iPendingSubscriptionTimeoutMs;
	OhNetCallbackFreeExternal iFreeExternal;
    bool iUseLoopbackNetworkAdapter;
	uint32_t iDvMaxUpdateTimeSecs;
    uint32_t iDvNumServerThreads;
	uint32_t iDvNumPublisherThreads;
    uint32_t iDvNumWebSocketThreads;
    uint32_t iDvWebSocketPort;
    bool iEnableBonjour;
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
    static void Initialise(InitialisationParams* aInitParams);

    /**
     * Lightweight alternative to UpnpLibraryInitialise.
     *
     * Intended for unit tests which are useful to platform porting only.
     * No class APIs other than Close() can be called if this is used.
     *
     * @param aInitParams  Initialisation options.  Only ILogOutput will be used.
     *                     Ownership of these passes to the library.
     */
    static void InitialiseMinimal(InitialisationParams* aInitParams);

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
     * @return  A pointer to the currently selected adapter with a reference claimed.
     *          Or NULL if there is no currently selected adapter.
     */
    static NetworkAdapter* CurrentSubnetAdapter();
};

} // namespace Net
} // namespace OpenHome
#endif // HEADER_UPNP
