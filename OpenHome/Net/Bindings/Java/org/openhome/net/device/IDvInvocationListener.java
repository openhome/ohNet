package org.openhome.net.device;

/**
 * Listener interface to receive notification of when an <tt>Action</tt> has
 * been invoked on a <tt>DvDevice</tt>.
 */
public interface IDvInvocationListener
{
	/**
	 * Receive notification after an <tt>Action</tt> has been invoked on a
	 * <tt>DvDevice</tt>.
	 * 
	 * @param aInvocation	pointer to the <tt>Invocation</tt>.
	 * @param aVersion		version of thew service.
	 */
	public void actionInvoked(long aInvocation, int aVersion);
}
