/**
 * UPnP library startup / shutdown
 */

#ifndef HEADER_UPNP
#define HEADER_UPNP

#include <Buffer.h>
#include <Functor.h>
#include <FunctorAsync.h>
#include <FunctorMsg.h>
#include <C/Zapp.h> // for ZappCallbackFreeExternal only

#include <vector>

namespace Zapp {

class NetworkInterface
{
public:
    NetworkInterface(TIpAddress aAddress, TIpAddress aNetMask, const char* aName);
    NetworkInterface* Clone() const;
    TIpAddress Address() const;
    TIpAddress Subnet() const;
    bool ContainsAddress(TIpAddress aAddress);
    const char* Name() const;
private:
    TIpAddress iAddress;
    TIpAddress iNetMask;
    Brhz iName;
};

class DefaultAsyncHandler;
class DefaultLogger;
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
    void SetDefaultSubnet(TIpAddress aSubnet);
    void SetSubnetChangedListener(Functor aFunctor);
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
	void SetFreeExternalCallback(ZappCallbackFreeExternal aCallback);
	/**
	 * Set the maximum time between device announcements for the device stack
	 */
	void SetDvMaxUpdateTime(uint32_t aSecs);
    /**
     * Set the number of threads which should be dedicated to publishing
     * changes to state variables on a service + device.
     * A higher number of threads will allow faster publication of changes
     * but will also require more system resources.
     */
    void SetDvNumPublisherThreads(uint32_t aNumThreads);

    FunctorMsg& LogOutput();
    FunctorMsg& FatalErrorHandler();
    FunctorAsync& AsyncBeginHandler();
    FunctorAsync& AsyncEndHandler();
    FunctorAsync& AsyncErrorHandler();
    TIpAddress DefaultSubnet() const;
    Functor& SubnetChangedListener();
    uint32_t TcpConnectTimeoutMs() const;
    uint32_t MsearchTimeSecs() const;
    uint32_t MsearchTtl() const;
    uint32_t NumEventSessionThreads() const;
    uint32_t NumXmlFetcherThreads() const;
    uint32_t NumActionInvokerThreads() const;
    uint32_t NumInvocations() const;
    uint32_t NumSubscriberThreads() const;
    uint32_t PendingSubscriptionTimeoutMs() const;
	ZappCallbackFreeExternal FreeExternal() const;
	uint32_t DvMaxUpdateTimeSecs() const;
    uint32_t DvNumPublisherThreads() const;
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
    TIpAddress iDefaultSubnet;
    Functor iSubnetChangedListener;
    uint32_t iTcpConnectTimeoutMs;
    uint32_t iMsearchTimeSecs;
    uint32_t iMsearchTtl;
    uint32_t iNumEventSessionThreads;
    uint32_t iNumXmlFetcherThreads;
    uint32_t iNumActionInvokerThreads;
    uint32_t iNumInvocations;
    uint32_t iNumSubscriberThreads;
    uint32_t iPendingSubscriptionTimeoutMs;
	ZappCallbackFreeExternal iFreeExternal;
	uint32_t iDvMaxUpdateTimeSecs;
	uint32_t iDvNumPublisherThreads;
};

class UpnpLibrary
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
     */
    static void StartCp();

    /**
     * Start the library as a UPnP device stack
     */
    static void StartDv();

    /**
     * Start the library as both UPnP control point and device stacks
     */
    static void StartCombined();

    /**
     * Close the UPnP library.
     *
     * Will not fail.  No more library functions should be called after this.
     */
    static void Close();

    /**
     * Create a vector of the available subnets.
     *
     * The returned vector and all its pointers are allocated.  Ownership is
     * transferred to the caller who is responsible for later deleting each
     * NetworkInterface* then the vector.
     *
     * @return  A newly allocated vector of newly allocated interfaces
     */
    static std::vector<NetworkInterface*>* SubnetList();

    /**
     * Set which subnet the library should use.
     * Override any value set via InitialisationParams::SetDefaultSubnet.
     * Device lists and subscriptions will be automatically updated.
     * No other subnet will be selected if aSubnet is not available
     *
     * @param aSubnet    The subnet to use.  Likely to be a reference to a
     *                   NetworkInterface returned by SubnetList
     */
    static void SetCurrentSubnet(const NetworkInterface& aSubnet);

    /**
     * Clear any subnet previously specified using SetCurrentSubnet() or
     * InitialisationParams::SetDefaultSubnet().  OS-specified defaults will be
     * used instead.
     * Device lists and subscriptions will be automatically updated if necessary.
     */
    static void SetDefaultSubnet();
};

} // namespace Zapp
#endif // HEADER_UPNP
