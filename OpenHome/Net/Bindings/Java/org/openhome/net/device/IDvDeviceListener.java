package org.openhome.net.device;

/**
 * Listener interface to receive notification of when a {@link #DvDevice} has
 * been disabled.
 *
 */
public interface IDvDeviceListener
{
	/**
	 * Receive notification after a {@link #DvDevice} has been disabled.
	 */
	public void deviceDisabled();
}
