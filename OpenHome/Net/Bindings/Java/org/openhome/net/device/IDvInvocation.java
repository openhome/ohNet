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
}
