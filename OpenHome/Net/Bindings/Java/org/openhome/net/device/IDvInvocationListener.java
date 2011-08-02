package org.openhome.net.device;

/**
 * Listener interface to receive notification of when an {@link #Action} has
 * been invoked on a {@link #DvDevice}.
 */
public interface IDvInvocationListener
{
	/**
	 * Receive notification after an {@link #Action} has been invoked on a
	 * {@link #DvDevice}.
	 * 
	 * @param aInvocation	pointer to the {@link Invocation}.
	 * @param aVersion		version of thew service.
	 */
	public void actionInvoked(long aInvocation, int aVersion);
}
