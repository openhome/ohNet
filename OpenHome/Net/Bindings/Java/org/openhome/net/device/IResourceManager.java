package org.openhome.net.device;

import java.util.List;

/**
 * Interface used by devices to publish data (typically files).
 */
public interface IResourceManager
{
	/**
	 * Write resources.
	 * 
	 * @param aUriTail			file being requested
	 * @param aIpAddress		network interface the file request was made on.
	 * @param aLanguageList		prioritised list of the languages accepted in
	 * 							the resources to be written. 
	 * @param aWriter			pointer to be passed to all 3 <tt>writeResource</tt> callbacks.
	 */
	public void writeResource(String aUriTail, int aIpAddress, List<String> aLanguageList, IResourceWriter aWriter);
}
