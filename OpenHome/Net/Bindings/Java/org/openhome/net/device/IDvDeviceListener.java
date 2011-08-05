package org.openhome.net.device;

/**
 * Listener interface to receive notification of when a {@code DvDevice} has
 * been disabled.
 *
 */
public interface IDvDeviceListener
{
	/**
	 * Receive notification after a {@code DvDevice} has been disabled.
	 */
	public void deviceDisabled();
}
