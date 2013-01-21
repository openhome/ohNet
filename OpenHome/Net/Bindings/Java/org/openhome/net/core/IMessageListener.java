package org.openhome.net.core;

/**
 * Listener interface to receive log messages and fatal error messages.
 *
 */
public interface IMessageListener
{
	/**
	 * Receive a message.
     *
     * @param aMessage      the message.
	 */
	public void message(String aMessage);
}
