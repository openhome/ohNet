package org.openhome.net.core;

/**
 * Listener interface to receive thread exit notifications.
 *
 */
public interface IThreadExitListener
{
	/**
	 * Receive a thread exit notification.
     *
	 */
	public void threadExit();
}
