package org.openhome.net.device;

public interface IDvInvocation
{
	/**
	 * Get the version number of the service requested by the caller.
	 *
	 * @return	The version number of the service the caller expects.
	 */
	public int getVersion();
	
	/**
	 * Get the network adapter an action was invoked using.
	 *
	 * @return	The network adapter used to invoke this action.
	 */
	public int getAdapter();
	
	/**
	 * Get the prefix to use on any URIs to resources offered by the provider.
	 *
	 * @return	The prefix to resource URIs.
	 */
	public String getResourceUriPrefix();
    
    /**
     * Get the client address for this invocation.
     *
     * @return  The client address that invoked this action.
     */
    public int getClientAddress();
    
    /**
     * Get the client port for this invocation.
     *
     * @return  The client port that invoked this action.
     */
    public int getClientPort();
    
    /**
     * Get the client user agent string for this invocation.
     *
     * @return  The user agent string sent by the client, or null if no user agent string was sent.
     */
    public String getClientUserAgent();
}
