package openhome.net.core;

public class InitParams
{

	private long iHandle = 0;
	
	// Initialisation and destruction functions.
	private native long OhNetInitParamsCreate();
	private native void OhNetInitParamsDestroy(long ptr);
	
	// Setter functions.

	// Getter functions.
	private native int OhNetInitParamsTcpConnectTimeoutMs(long ptr);
	private native int OhNetInitParamsMsearchTimeSecs(long ptr);
	private native int OhNetInitParamsMsearchTtl(long ptr);
	private native int OhNetInitParamsNumEventSessionThreads(long ptr);
	private native int OhNetInitParamsNumXmlFetcherThreads(long ptr);
	private native int OhNetInitParamsNumActionInvokerThreads(long ptr);
	private native int OhNetInitParamsNumInvocations(long ptr);
	private native int OhNetInitParamsNumSubscriberThreads(long ptr);
	private native int OhNetInitParamsPendingSubscriptionTimeoutMs(long ptr);
	private native int OhNetInitParamsDvMaxUpdateTimeSecs(long ptr);
	private native int OhNetInitParamsDvNumServerThreads(long ptr);
	private native int OhNetInitParamsDvNumPublisherThreads(long ptr);
	private native int OhNetInitParamsDvNumWebSocketThreads(long ptr);
	private native int OhNetInitParamsDvWebSocketPort(long ptr);
	private native int OhNetInitParamsDvIsBonjourEnabled(long ptr);

	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }

	public InitParams()
	{
		iHandle = OhNetInitParamsCreate();
	}
	
	public void finalize()
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
