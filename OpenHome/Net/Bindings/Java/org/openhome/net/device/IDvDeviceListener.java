package org.openhome.net.device;

/**
 * Listener interface to receive notification of when a <tt>DvDevice</tt> has
 * been disabled.
 *
 */
public interface IDvDeviceListener
{
	/**
	 * Receive notification after a <tt>DvDevice</tt> has been disabled.
	 */
	public void deviceDisabled();
}
