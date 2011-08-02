package org.openhome.net.device;

/**
 * Listener interface to receive notification of when an {@code Action} has
 * been invoked on a {@code DvDevice}.
 */
public interface IDvInvocationListener
{
	/**
	 * Receive notification after an {@code Action} has been invoked on a
	 * {@code DvDevice}.
	 * 
	 * @param aInvocation	pointer to the {@code Invocation}.
	 * @param aVersion		version of thew service.
	 */
	public void actionInvoked(long aInvocation, int aVersion);
}
