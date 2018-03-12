package org.openhome.net.core;

public class InitParams
{

	private long iHandle = 0;
    private long iCallbackThreadExit = 0;
    private long iCallbackLogOutput = 0;
    private long iCallbackFatalError = 0;
    private long iCallbackSubnetListChanged = 0;
    private long iCallbackSubnetAdded = 0;
    private long iCallbackSubnetRemoved = 0;
    private long iCallbackNetworkAdapterChanged = 0;
	
	// Initialisation and destruction functions.
	private static native long OhNetInitParamsCreate();
    private static native long OhNetInitParamsCreateThreadExitCallback(long aParams);
	private static native void OhNetInitParamsDestroy(long aParams);
    private static native void OhNetInitParamsDisposeCallback(long aCallback);
	
	// Callbacks.
//	private static native void OhNetInitParamsSetAsyncBeginHandler(long aParams, OhNetCallbackAsync aCallback, void* aPtr);
//	private static native void OhNetInitParamsSetAsyncEndHandler(long aParams, OhNetCallbackAsync aCallback, void* aPtr);
//	private static native void OhNetInitParamsSetAsyncErrorHandler(long aParams, OhNetCallbackAsync aCallback, void* aPtr);
//	private static native void OhNetInitParamsSetFreeExternalCallback(long aParams, OhNetCallbackFreeExternal aCallback);

	// Getter functions.
	private static native int OhNetInitParamsTcpConnectTimeoutMs(long aParams);
	private static native int OhNetInitParamsMsearchTimeSecs(long aParams);
	private static native int OhNetInitParamsMsearchTtl(long aParams);
	private static native int OhNetInitParamsNumEventSessionThreads(long aParams);
	private static native int OhNetInitParamsNumXmlFetcherThreads(long aParams);
	private static native int OhNetInitParamsNumActionInvokerThreads(long aParams);
	private static native int OhNetInitParamsNumInvocations(long aParams);
	private static native int OhNetInitParamsNumSubscriberThreads(long aParams);
	private static native int OhNetInitParamsSubscriptionDurationSecs(long aParams);
	private static native int OhNetInitParamsPendingSubscriptionTimeoutMs(long aParams);
	private static native int OhNetInitParamsDvMaxUpdateTimeSecs(long aParams);
	private static native int OhNetInitParamsDvNumServerThreads(long aParams);
	private static native int OhNetInitParamsDvNumPublisherThreads(long aParams);
	private static native int OhNetInitParamsDvNumWebSocketThreads(long aParams);
	private static native int OhNetInitParamsDvUpnpServerPort(long aParams);
	private static native int OhNetInitParamsDvWebSocketPort(long aParams);
	private static native int OhNetInitParamsDvIsBonjourEnabled(long aParams);
	
	// Setter functions.
	private static native void OhNetInitParamsSetTcpConnectTimeout(long aParams, int aTimeoutMs);
	private static native void OhNetInitParamsSetMsearchTime(long aParams, int aSecs);
	private static native void OhNetInitParamsSetMsearchTtl(long aParams, int aTtl);
	private static native void OhNetInitParamsSetNumEventSessionThreads(long aParams, int aNumThreads);
	private static native void OhNetInitParamsSetNumXmlFetcherThreads(long aParams, int aNumThreads);
	private static native void OhNetInitParamsSetNumActionInvokerThreads(long aParams, int aNumThreads);
	private static native void OhNetInitParamsSetNumInvocations(long aParams, int aNumInvocations);
	private static native void OhNetInitParamsSetNumSubscriberThreads(long aParams, int aNumThreads);
	private static native void OhNetInitParamsSetSubscriptionDuration(long aParams, int aDurationSecs);
	private static native void OhNetInitParamsSetPendingSubscriptionTimeout(long aParams, int aTimeoutMs);
	private static native void OhNetInitParamsSetUseLoopbackNetworkAdapter(long aParams);
	private static native void OhNetInitParamsSetIncludeLoopbackNetworkAdapter(long aParams);
	private static native void OhNetInitParamsSetDvMaxUpdateTime(long aParams, int aSecs);
	private static native void OhNetInitParamsSetDvNumServerThreads(long aParams, int aNumThreads);
	private static native void OhNetInitParamsSetDvNumPublisherThreads(long aParams, int aNumThreads);
	private static native void OhNetInitParamsSetDvNumWebSocketThreads(long aParams, int aNumThreads);
	private static native void OhNetInitParamsSetDvUpnpServerPort(long aParams, int aPort);
	private static native void OhNetInitParamsSetDvWebSocketPort(long aParams, int aPort);
	private static native void OhNetInitParamsSetDvEnableBonjour(long aParams, String aHostName, Bool aRequiresMdnsCache);
    private static native long OhNetInitParamsSetLogOutput(long aParams, IMessageListener aListener);
    private static native long OhNetInitParamsSetFatalErrorHandler(long aParams, IMessageListener aListener);
    private static native void OhNetInitParamsSetThreadExitHandler(long aParams, IThreadExitListener aListener);
    private static native long OhNetInitParamsSetSubnetListChangedListener(long aParams, IChangeListener aListener);
    private static native long OhNetInitParamsSetSubnetAddedListener(long aParams, NetworkAdapterCallback aCallback);
    private static native long OhNetInitParamsSetSubnetRemovedListener(long aParams, NetworkAdapterCallback aCallback);
    private static native long OhNetInitParamsSetNetworkAdapterChangedListener(long aParams, NetworkAdapterCallback aCallback);


	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }

	public InitParams()
	{
		iHandle = OhNetInitParamsCreate();
        iCallbackThreadExit = OhNetInitParamsCreateThreadExitCallback(iHandle);
	}
	
	public void destroy()
	{
		OhNetInitParamsDestroy(iHandle);
        disposeCallbacks();
	}
    
    public void disposeCallbacks()
    {
        if (iCallbackThreadExit != 0) {
            OhNetInitParamsDisposeCallback(iCallbackThreadExit);
        }
        if (iCallbackLogOutput != 0) {
            OhNetInitParamsDisposeCallback(iCallbackLogOutput);
        }
        if (iCallbackFatalError != 0) {
            OhNetInitParamsDisposeCallback(iCallbackFatalError);
        }
        if (iCallbackSubnetListChanged != 0) {
            OhNetInitParamsDisposeCallback(iCallbackSubnetListChanged);
        }
        if (iCallbackSubnetAdded != 0) {
            OhNetInitParamsDisposeCallback(iCallbackSubnetAdded);
        }
        if (iCallbackSubnetRemoved != 0) {
            OhNetInitParamsDisposeCallback(iCallbackSubnetRemoved);
        }
        if (iCallbackNetworkAdapterChanged != 0) {
            OhNetInitParamsDisposeCallback(iCallbackNetworkAdapterChanged);
        }
    }
	
	protected long getHandle()
	{
		return iHandle;
	}
	
	/**
	 * Get the timeout for TCP connections in milliseconds.
	 *
	 * @return	timeout in milliseconds.
	 */
	public int getTcpConnectTimeoutMs()
	{
		return OhNetInitParamsTcpConnectTimeoutMs(iHandle);
	}
	
	/**
	 * Get the time in seconds that msearch responses should be spread out over.
	 *
	 * @return	msearch time in seconds.
	 */
	public int getMsearchTimeSecs()
	{
		return OhNetInitParamsMsearchTimeSecs(iHandle);
	}
	
	/**
	 * Get the time-to-live value for msearches.
	 *
	 * @return	time-to-live value for msearches.
	 */
	public int getMsearchTtl()
	{
		return OhNetInitParamsMsearchTtl(iHandle);
	}
	
	/**
	 * Get the number of threads which should be dedicated to eventing
	 * (handling updates to subscribed state variables).
	 *
	 * @return	the number of eventing threads.
	 */
	public int getNumEventSessionThreads()
	{
		return OhNetInitParamsNumEventSessionThreads(iHandle);
	}
	
	/**
	 * Get the number of threads which should be dedicated to fetching
	 * device/service XML.
	 * 
	 * <p>A higher number of threads will allow faster population of device
	 * lists but will also require more system resources.
	 *
	 * @return	the number of XML fetcher threads.
	 */
	public int getNumXmlFetcherThreads()
	{
		return OhNetInitParamsNumXmlFetcherThreads(iHandle);
	}
	
	/**
	 * Get the number of threads which should be dedicated to invoking actions
	 * on devices.
	 * 
	 * <p>A higher number of threads will allow faster population of device
	 * lists but will also require more system resources.
	 * 
	 * @return	the number of action invoker threads.
	 */
	public int getNumActionInvokerThreads()
	{
		return OhNetInitParamsNumActionInvokerThreads(iHandle);
	}
	
	/**
	 * Get the number of invocations (actions) which should be pre-allocated.
	 * 
	 * <p>If more that this number are pending, the additional attempted invocations 
	 * will block until a pre-allocated slot becomes clear.
	 * 
	 * <p>A higher number of invocations will decrease the likelihood and duration of
	 * any UI-level delays but will also increase the peaks in RAM requirements.
	 * 
	 * @return	the number of pre-allocated invocations.
	 */
	public int getNumInvocations()
	{
		return OhNetInitParamsNumInvocations(iHandle);
	}
	
	/**
	 * Get the number of threads which should be dedicated to (un)subscribing
	 * to state variables on a service + device.
	 * 
	 * <p>A higher number of threads will allow faster population of device
	 * lists but will also require more system resources.
	 * 
	 * @return	the number of subscriber threads.
	 */
	public int getNumSubscriberThreads()
	{
		return OhNetInitParamsNumSubscriberThreads(iHandle);
	}
	
	/**
	 * Get the duration (in seconds) control points will request for subscriptions.
	 * 
	 * @return	requested subscription duration in seconds.
	 */
	public int getSubscriptionDurationSecs()
	{
		return OhNetInitParamsSubscriptionDurationSecs(iHandle);
	}
	
	/**
	 * Get the maximum time in milliseconds to wait before rejecting an event
	 * update from an unknown source.
	 * 
	 * <p>It is possible for initial information on state variables to arrive
	 * before a subscription is noted as complete. Waiting a short while before
	 * rejecting events from unknown sources decreases the chances of missing
	 * the initial event from a subscription.
	 * 
	 * @return	maximum time before rejecting an event update.
	 */
	public int getPendingSubscriptionTimeoutMs()
	{
		return OhNetInitParamsPendingSubscriptionTimeoutMs(iHandle);
	}
	
	/**
	 * Get the maximum time in seconds between device announcements for the
	 * device stack.
	 * 
	 * <p>This value will appear in the maxage header for UPnP advertisements.
	 * 
	 * @return	the maximum time between device announcements.
	 */
	public int getDvMaxUpdateTimeSecs()
	{
		return OhNetInitParamsDvMaxUpdateTimeSecs(iHandle);
	}
	
	/**
	 * Get the number of threads which should be dedicated to processing
	 * control/eventing/presentation requests.
	 * 
	 * <p>A higher number of threads may allow faster response to multiple
	 * clients making concurrent requests but will also require more system
	 * resources.
	 * 
	 * @return	the number of threads dedicated to processing requests.
	 */
	public int getDvNumServerThreads()
	{
		return OhNetInitParamsDvNumServerThreads(iHandle);
	}
	
	/**
	 * Get the number of threads which should be dedicated to publishing
	 * changes to state variables on a service + device.
	 * 
	 * <p>A higher number of threads will allow faster publication of changes
	 * but will also require more system resources.
	 * 
	 * @return	the number of publishing threads.
	 */
	public int getDvNumPublisherThreads()
	{
		return OhNetInitParamsDvNumPublisherThreads(iHandle);
	}
	
	/**
	 * Get the number of threads which will be dedicated to published changes
	 * to state variables via WebSockets.
	 * 
	 * <p>One thread will be used per active (web browser) connection so a
	 * higher number of threads will allow more concurrent clients but will
	 * also require more system resources. Can be 0 for clients who do not
	 * require HTML5 support.
	 * 
	 * @return	the number of WebSocket threads.
	 */
	public int getDvNumWebSocketThreads()
	{
		return OhNetInitParamsDvNumWebSocketThreads(iHandle);
	}
	
	/**
	 * Get the TCP port number the device stack server will run on.
	 * 
	 * @return	the TCP port number the device stack server will run on.
	 */
	public int getDvServerPort()
	{
		return OhNetInitParamsDvUpnpServerPort(iHandle);
	}
	
	/**
	 * Get the TCP port number the WebSocket server will run on.
	 * 
	 * @return	the TCP port number the WebSocket server will run on.
	 */
	public int getDvWebSocketPort()
	{
		return OhNetInitParamsDvWebSocketPort(iHandle);
	}
	
	/**
	 * Check if use of Bonjour is enabled
	 * 
	 * <p>All <tt>DvDevice</tt> instances with an <tt>IResourceManager</tt>
	 * will be published using Bonjour. 
	 * 
	 * <p>If a device sets the "Upnp.MdnsHostName" attribute, its presentation
	 * will be available via http://[hostname].local.
	 * 
	 * <p>Behaviour when more than one DvDevice sets the "MdnsHostName" attribute
	 * is undefined.
	 * 
	 * <p>Note that enabling Bonjour will cause the device stack to run a HTTP
	 * server on port 80, requiring root privileges on Linux.
	 * 
	 * @return	<tt>true</tt> if Bonjour is enabled; <tt>false</tt> otherwise.
	 */
	public boolean getDvIsBonjourEnabled()
	{
		return OhNetInitParamsDvIsBonjourEnabled(iHandle) == 1;
	}

	/**
	 * Set the timeout for TCP connections in milliseconds. Must be >0.
	 *
	 * @param aTimeoutMs	timeout in milliseconds.
	 */
	public void setTcpConnectTimeoutMs(int aTimeoutMs)
	{
		OhNetInitParamsSetTcpConnectTimeout(iHandle, aTimeoutMs);
	}
	
	/**
	 * Set the time in seconds that msearch responses should be spread out over.
	 * Should be between 1 and 5 (inclusive).
	 *
	 * @param aSecs		msearch time in seconds.
	 */
	public void setMsearchTimeSecs(int aSecs)
	{
		OhNetInitParamsSetMsearchTime(iHandle, aSecs);
	}
	
	/**
	 * Set the time-to-live value for msearches.
	 *
	 * @param aTtl	time-to-live value for msearches.
	 */
	public void setMsearchTtl(int aTtl)
	{
		OhNetInitParamsSetMsearchTtl(iHandle, aTtl);
	}
	
	/**
	 * Set the number of threads which should be dedicated to eventing
	 * (handling updates to subscribed state variables).
	 *
	 * @param aNumThreads	the number of eventing threads.
	 */
	public void setNumEventSessionThreads(int aNumThreads)
	{
		OhNetInitParamsSetNumEventSessionThreads(iHandle, aNumThreads);
	}
	
	/**
	 * Set the number of threads which should be dedicated to fetching
	 * device/service XML.
	 * 
	 * <p>A higher number of threads will allow faster population of device
	 * lists but will also require more system resources.
	 *
	 * @param aNumThreads	the number of XML fetcher threads.
	 */
	public void setNumXmlFetcherThreads(int aNumThreads)
	{
		OhNetInitParamsSetNumXmlFetcherThreads(iHandle, aNumThreads);
	}
	
	/**
	 * Set the number of threads which should be dedicated to invoking actions
	 * on devices.
	 * 
	 * <p>A higher number of threads will allow faster population of device
	 * lists but will also require more system resources.
	 * 
	 * @param aNumThreads	the number of action invoker threads.
	 */
	public void setNumActionInvokerThreads(int aNumThreads)
	{
		OhNetInitParamsSetNumActionInvokerThreads(iHandle, aNumThreads);
	}
	
	/**
	 * Set the number of invocations (actions) which should be pre-allocated.
	 * 
	 * <p>If more that this number are pending, the additional attempted invocations 
	 * will block until a pre-allocated slot becomes clear.
	 * 
	 * <p>A higher number of invocations will decrease the likelihood and duration of
	 * any UI-level delays but will also increase the peaks in RAM requirements.
	 * 
	 * @param aNumInvocations	the number of pre-allocated invocations.
	 */
	public void setNumInvocations(int aNumInvocations)
	{
		OhNetInitParamsSetNumInvocations(iHandle, aNumInvocations);
	}
	
	/**
	 * Set the number of threads which should be dedicated to (un)subscribing
	 * to state variables on a service + device.
	 * 
	 * <p>A higher number of threads will allow faster population of device
	 * lists but will also require more system resources.
	 * 
	 * @param aNumThreads	the number of subscriber threads.
	 */
	public void setNumSubscriberThreads(int aNumThreads)
	{
		OhNetInitParamsSetNumSubscriberThreads(iHandle, aNumThreads);
	}
	
	/**
	 * Set the duration control point subscriptions will request.
	 * 
	 * @param aDurationSecs	 maximum time before rejecting an event update.
	 */
	public void setSubscriptionDuration(int aDurationSecs)
	{
		OhNetInitParamsSetSubscriptionDuration(iHandle, aDurationSecs);
	}
	
	/**
	 * Set the maximum time in milliseconds to wait before rejecting an event
	 * update from an unknown source.
	 * 
	 * <p>It is possible for initial information on state variables to arrive
	 * before a subscription is noted as complete. Waiting a short while before
	 * rejecting events from unknown sources decreases the chances of missing
	 * the initial event from a subscription.
	 * 
	 * @param aTimeoutMs	maximum time before rejecting an event update.
	 */
	public void setPendingSubscriptionTimeoutMs(int aTimeoutMs)
	{
		OhNetInitParamsSetPendingSubscriptionTimeout(iHandle, aTimeoutMs);
	}
	
	/**
	 * Limit the library to using only the loopback network interface.
	 * 
	 * <p>Useful for testing but not expected to be used in production code.
	 */
	public void setUseLoopbackNetworkAdapter()
	{
		OhNetInitParamsSetUseLoopbackNetworkAdapter(iHandle);
	}
	
	/**
	 * Include the loopback network interface in the list of available adapters.
	 *
	 * <p>Useful for testing but not expected to be used in production code.
	 */
	public void setIncludeLoopbackNetworkAdapter()
	{
		OhNetInitParamsSetIncludeLoopbackNetworkAdapter(iHandle);
	}

	/**
	 * Set the maximum time in seconds between device announcements for the
	 * device stack.
	 * 
	 * <p>This value will appear in the maxage header for UPnP advertisements.
	 * 
	 * @param aSecs		the maximum time between device announcements.
	 */
	public void setDvMaxUpdateTimeSecs(int aSecs)
	{
		OhNetInitParamsSetDvMaxUpdateTime(iHandle, aSecs);
	}
	
	/**
	 * Set the number of threads which should be dedicated to processing
	 * control/eventing/presentation requests.
	 * 
	 * <p>A higher number of threads may allow faster response to multiple
	 * clients making concurrent requests but will also require more system
	 * resources.
	 * 
	 * @param aNumThreads	the number of threads dedicated to processing requests.
	 */
	public void setDvNumServerThreads(int aNumThreads)
	{
		OhNetInitParamsSetDvNumServerThreads(iHandle, aNumThreads);
	}
	
	/**
	 * Set the number of threads which should be dedicated to publishing
	 * changes to state variables on a service + device.
	 * 
	 * <p>A higher number of threads will allow faster publication of changes
	 * but will also require more system resources.
	 * 
	 * @param aNumThreads	the number of publishing threads.
	 */
	public void setDvNumPublisherThreads(int aNumThreads)
	{
		OhNetInitParamsSetDvNumPublisherThreads(iHandle, aNumThreads);
	}
	
	/**
	 * Set the number of threads which will be dedicated to published changes
	 * to state variables via WebSockets.
	 * 
	 * <p>One thread will be used per active (web browser) connection so a
	 * higher number of threads will allow more concurrent clients but will
	 * also require more system resources. Can be 0 for clients who do not
	 * require HTML5 support.
	 * 
	 * @param aNumThreads	the number of WebSocket threads.
	 */
	public void setDvNumWebSocketThreads(int aNumThreads)
	{
		OhNetInitParamsSetDvNumWebSocketThreads(iHandle, aNumThreads);
	}
	
	/**
	 * Set the TCP port number the device stack server will run on.
	 * 
	 * <p>The default value is 0 (OS-assigned).
	 *
	 * @param aPort		the TCP port number the device stack server will run on.
	 */
	public void setDvServerPort(int aPort)
	{
		OhNetInitParamsSetDvUpnpServerPort(iHandle, aPort);
	}

	/**
	 * Set the TCP port number the WebSocket server will run on.
	 * 
	 * <p>The default value is 0 (meaning that the OS will assign a port).
	 *
	 * @param aPort		the TCP port number the WebSocket server will run on.
	 */
	public void setDvWebSocketPort(int aPort)
	{
		OhNetInitParamsSetDvWebSocketPort(iHandle, aPort);
	}
	
	/**
	 * Enable the use of Bonjour.
	 * 
	 * <p>All <tt>DvDevice</tt> instances with an <tt>IResourceManager</tt>
	 * will be published using Bonjour. 
	 * 
	 * <p>If a device sets the "Upnp.MdnsHostName" attribute, its presentation
	 * will be available via http://[hostname].local.
	 * 
	 * <p>Behaviour when more than one DvDevice sets the "MdnsHostName" attribute
	 * is undefined.
	 * 
	 * <p>Note that enabling Bonjour will cause the device stack to run a HTTP
	 * server on port 80, requiring root privileges on Linux.
	 */
	public void setDvEnableBonjour(String aHostName, Bool aRequiresMdnsCache)
	{
		OhNetInitParamsSetDvEnableBonjour(iHandle, aHostName, aRequiresMdnsCache);
	}
    
    /**
     * Set the listener callback for log messages.
     * 
     * @param aListener     the listener callback for log messages.
     */
    public synchronized void setLogOutput(IMessageListener aListener)
    {
        long prevCallbackLogOutput = iCallbackLogOutput; 
         iCallbackLogOutput = OhNetInitParamsSetLogOutput(iHandle, aListener);
        if (prevCallbackLogOutput != 0) {
            OhNetInitParamsDisposeCallback(prevCallbackLogOutput);
        }
    }
    
    /**
     * Set the fatal error handler.
     * 
     * @param aListener     the handler for fatal error messages.
     */
    public synchronized void setFatalErrorHandler(IMessageListener aListener)
    {
        long prevCallbackFatalError = iCallbackFatalError; 
        iCallbackFatalError = OhNetInitParamsSetFatalErrorHandler(iHandle, aListener);
        if (prevCallbackFatalError != 0) {
            OhNetInitParamsDisposeCallback(prevCallbackFatalError);
        }
    }

    /**
     * Set the thread exit handler.
     * 
     * @param aListener     the handler for thread exit events.
     */
    public synchronized void setThreadExitHandler(IThreadExitListener aListener)
    {
        OhNetInitParamsSetThreadExitHandler(iCallbackThreadExit, aListener);
    }

    /**
     * Set the listener callback for subnet list changes.
     * 
     * @param aListener     the listener callback for subnet list changes.
     */
    public synchronized void setSubnetListChangedListener(IChangeListener aListener)
    {
        long prevCallbackSubnetListChanged = iCallbackSubnetListChanged; 
        iCallbackSubnetListChanged = OhNetInitParamsSetSubnetListChangedListener(iHandle, aListener);
        if (prevCallbackSubnetListChanged != 0) {
            OhNetInitParamsDisposeCallback(prevCallbackSubnetListChanged);
        }
    }

    /**
     * Set the listener callback for subnet added events.
     * 
     * @param aListener     the listener callback for subnet added events.
     */
    public synchronized void setSubnetAddedListener(INetworkAdapterListener aListener)
    {
        long prevCallbackSubnetAdded = iCallbackSubnetAdded; 
        iCallbackSubnetAdded = OhNetInitParamsSetSubnetAddedListener(iHandle,
                                   new NetworkAdapterCallback(aListener));
        if (prevCallbackSubnetAdded != 0) {
            OhNetInitParamsDisposeCallback(prevCallbackSubnetAdded);
        }
    }

    /**
     * Set the listener callback for subnet removed events.
     * 
     * @param aListener     the listener callback for subnet removed events.
     */
    public synchronized void setSubnetRemovedListener(INetworkAdapterListener aListener)
    {
        long prevCallbackSubnetRemoved = iCallbackSubnetRemoved; 
        iCallbackSubnetRemoved = OhNetInitParamsSetSubnetRemovedListener(iHandle,
                                     new NetworkAdapterCallback(aListener));
        if (prevCallbackSubnetRemoved != 0) {
            OhNetInitParamsDisposeCallback(prevCallbackSubnetRemoved);
        }
    }

    /**
     * Set the listener callback for network adapter changed events.
     * 
     * @param aListener     the listener callback for network adapter changed events.
     */
    public synchronized void setNetworkAdapterChangedListener(INetworkAdapterListener aListener)
    {
        long prevCallbackNetworkAdapterChanged = iCallbackNetworkAdapterChanged; 
        iCallbackNetworkAdapterChanged = OhNetInitParamsSetNetworkAdapterChangedListener(iHandle,
                                             new NetworkAdapterCallback(aListener));
        if (prevCallbackNetworkAdapterChanged != 0) {
            OhNetInitParamsDisposeCallback(prevCallbackNetworkAdapterChanged);
        }
    }
	
	public static void main(String[] args)
	{
		InitParams params = new InitParams();
		
		int tcpTimeout 				= params.getTcpConnectTimeoutMs();
		int msearchTime 			= params.getMsearchTimeSecs();
		int msearchTtl				= params.getMsearchTtl();
		int numEventThreads			= params.getNumEventSessionThreads();
		int numFetcherThreads		= params.getNumXmlFetcherThreads();
		int numInvokerThreads		= params.getNumActionInvokerThreads();
		int numInvocations			= params.getNumInvocations();
		int numSubscriberThreads	= params.getNumSubscriberThreads();
		int pendingSubsTimeout 		= params.getPendingSubscriptionTimeoutMs();
		int maxUpdateTime			= params.getDvMaxUpdateTimeSecs();
		int numServerThreads		= params.getDvNumServerThreads();
		int numPublisherThreads		= params.getDvNumPublisherThreads();
		int numWebSocketThreads		= params.getDvNumWebSocketThreads();
		int webSocketPort			= params.getDvWebSocketPort();
		boolean bonjourEnabled		= params.getDvIsBonjourEnabled();
		
		System.out.println("Params TCP timeout:\t\t\t" + params.getTcpConnectTimeoutMs() + " ms");
        System.out.println("Params search time:\t\t\t" + params.getMsearchTimeSecs() + " secs");
        System.out.println("Params search TTL:\t\t\t" + params.getMsearchTtl());
        System.out.println("Params num event session threads:\t" + params.getNumEventSessionThreads());
        System.out.println("Params num XML fetcher threads:\t\t" + params.getNumXmlFetcherThreads());
        System.out.println("Params num action invoker threads:\t" + params.getNumActionInvokerThreads());
        System.out.println("Params num invocations:\t\t\t" + params.getNumInvocations());
        System.out.println("Params num subscriber threads:\t\t" + params.getNumSubscriberThreads());
        System.out.println("Params pending subscription timeout:\t" + params.getPendingSubscriptionTimeoutMs());
        System.out.println("Params device max update time:\t\t" + params.getDvMaxUpdateTimeSecs() + " secs");
        System.out.println("Params num server threads:\t\t" + params.getDvNumServerThreads());
        System.out.println("Params num publisher threads:\t\t" + params.getDvNumPublisherThreads());
        System.out.println("Params num WebSocket threads:\t\t" + params.getDvNumWebSocketThreads());
        System.out.println("Params WebSocket port:\t\t\t" + params.getDvWebSocketPort());
        System.out.println("Params Bonjour enabled:\t\t\t" + params.getDvIsBonjourEnabled());
        
		params.setTcpConnectTimeoutMs(tcpTimeout + 1);
		params.setMsearchTimeSecs(msearchTime + 1);
		params.setMsearchTtl(msearchTtl + 1);
		params.setNumEventSessionThreads(numEventThreads + 1);
		params.setNumXmlFetcherThreads(numFetcherThreads + 1);
		params.setNumActionInvokerThreads(numInvokerThreads + 1);
		params.setNumInvocations(numInvocations + 1);
		params.setNumSubscriberThreads(numSubscriberThreads + 1);
		params.setPendingSubscriptionTimeoutMs(pendingSubsTimeout + 1);
		params.setDvMaxUpdateTimeSecs(maxUpdateTime + 1);
		params.setDvNumServerThreads(numServerThreads + 1);
		params.setDvNumPublisherThreads(numPublisherThreads + 1);
		params.setDvNumWebSocketThreads(numWebSocketThreads + 1);
		params.setDvWebSocketPort(webSocketPort + 1);
		params.setDvEnableBonjour("");
		
		System.out.println();
		System.out.println("Params TCP timeout:\t\t\t" + params.getTcpConnectTimeoutMs() + " ms");
        System.out.println("Params search time:\t\t\t" + params.getMsearchTimeSecs() + " secs");
        System.out.println("Params search TTL:\t\t\t" + params.getMsearchTtl());
        System.out.println("Params num event session threads:\t" + params.getNumEventSessionThreads());
        System.out.println("Params num XML fetcher threads:\t\t" + params.getNumXmlFetcherThreads());
        System.out.println("Params num action invoker threads:\t" + params.getNumActionInvokerThreads());
        System.out.println("Params num invocations:\t\t\t" + params.getNumInvocations());
        System.out.println("Params num subscriber threads:\t\t" + params.getNumSubscriberThreads());
        System.out.println("Params pending subscription timeout:\t" + params.getPendingSubscriptionTimeoutMs());
        System.out.println("Params device max update time:\t\t" + params.getDvMaxUpdateTimeSecs() + " secs");
        System.out.println("Params num server threads:\t\t" + params.getDvNumServerThreads());
        System.out.println("Params num publisher threads:\t\t" + params.getDvNumPublisherThreads());
        System.out.println("Params num WebSocket threads:\t\t" + params.getDvNumWebSocketThreads());
        System.out.println("Params WebSocket port:\t\t\t" + params.getDvWebSocketPort());
        System.out.println("Params Bonjour enabled:\t\t\t" + params.getDvIsBonjourEnabled());
	}

    private static class NetworkAdapterCallback
    {
        private INetworkAdapterListener iListener;

        private NetworkAdapterCallback(INetworkAdapterListener aListener) {
            iListener = aListener;
        }

        /**
         * Callback method for native code to use for a subnet or adapter change event.
         * 
         * @param aAdapter   handle to the network adapter.
         */
        public void notifyChange(long aAdapter)
        {
            // ohNet will call removeRef for the adapter when this callback returns
            NetworkAdapter adapter = new NetworkAdapter(aAdapter, false);
            iListener.notifyChange(adapter);
        }
    }
}
