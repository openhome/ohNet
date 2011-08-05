package org.openhome.net.core;

public class InitParams
{

	private long iHandle = 0;
	
	// Initialisation and destruction functions.
	private static native long OhNetInitParamsCreate();
	private static native void OhNetInitParamsDestroy(long aParams);

	// Getter functions.
	private static native int OhNetInitParamsTcpConnectTimeoutMs(long aParams);
	private static native int OhNetInitParamsMsearchTimeSecs(long aParams);
	private static native int OhNetInitParamsMsearchTtl(long aParams);
	private static native int OhNetInitParamsNumEventSessionThreads(long aParams);
	private static native int OhNetInitParamsNumXmlFetcherThreads(long aParams);
	private static native int OhNetInitParamsNumActionInvokerThreads(long aParams);
	private static native int OhNetInitParamsNumInvocations(long aParams);
	private static native int OhNetInitParamsNumSubscriberThreads(long aParams);
	private static native int OhNetInitParamsPendingSubscriptionTimeoutMs(long aParams);
	private static native int OhNetInitParamsDvMaxUpdateTimeSecs(long aParams);
	private static native int OhNetInitParamsDvNumServerThreads(long aParams);
	private static native int OhNetInitParamsDvNumPublisherThreads(long aParams);
	private static native int OhNetInitParamsDvNumWebSocketThreads(long aParams);
	private static native int OhNetInitParamsDvWebSocketPort(long aParams);
	private static native int OhNetInitParamsDvIsBonjourEnabled(long aParams);
	
	// Setter functions.
	private static native void OhNetInitParamsSetMsearchTime(long aParams, int aSecs);
	private static native void OhNetInitParamsSetUseLoopbackNetworkAdapter(long aParams);

	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }

	public InitParams()
	{
		iHandle = OhNetInitParamsCreate();
	}
	
	public void destroy()
	{
		OhNetInitParamsDestroy(iHandle);
	}
	
	protected long getHandle()
	{
		return iHandle;
	}
	
	public int getTcpConnectTimeoutMs()
	{
		return OhNetInitParamsTcpConnectTimeoutMs(iHandle);
	}
	
	public int getMsearchTimeSecs()
	{
		return OhNetInitParamsMsearchTimeSecs(iHandle);
	}
	
	public int getMsearchTtl()
	{
		return OhNetInitParamsMsearchTtl(iHandle);
	}
	
	public int getNumEventSessionThreads()
	{
		return OhNetInitParamsNumEventSessionThreads(iHandle);
	}
	
	public int getNumXmlFetcherThreads()
	{
		return OhNetInitParamsNumXmlFetcherThreads(iHandle);
	}
	
	public int getNumActionInvokerThreads()
	{
		return OhNetInitParamsNumActionInvokerThreads(iHandle);
	}
	
	public int getNumInvocations()
	{
		return OhNetInitParamsNumInvocations(iHandle);
	}
	
	public int getNumSubscriberThreads()
	{
		return OhNetInitParamsNumSubscriberThreads(iHandle);
	}
	
	/**
	 * Set a custom time that msearch responses should be spread out over.
	 * 
	 * @param aSecs	time in seconds.  Must be between 1 and 5 (inclusive).
	 */
	public void setMsearchTimeSecs(int aSecs)
	{
		OhNetInitParamsSetMsearchTime(iHandle, aSecs);
	}
	
	/**
	 * Limit the library to using only the loopback network interface.
	 * Useful for testing but not expected to be used in production code.
	 */
	public void setUseLoopbackNetworkAdapter()
	{
		OhNetInitParamsSetUseLoopbackNetworkAdapter(iHandle);
	}
	
	public static void main(String[] args)
	{
		InitParams params = new InitParams();
		
		System.out.println("Params TCP timeout:\t\t\t" + params.getTcpConnectTimeoutMs() + " ms");
        System.out.println("Params search time:\t\t\t" + params.getMsearchTimeSecs() + " secs");
        System.out.println("Params search TTL:\t\t\t" + params.getMsearchTtl());
        System.out.println("Params num event session threads:\t" + params.getNumEventSessionThreads());
        System.out.println("Params num XML fetcher threads:\t\t" + params.getNumXmlFetcherThreads());
        System.out.println("Params num action invoker threads:\t" + params.getNumActionInvokerThreads());
        System.out.println("Params num invocations:\t\t\t" + params.getNumInvocations());
        System.out.println("Params num subscriber threads:\t\t" + params.getNumSubscriberThreads());
        
	}
	
}
