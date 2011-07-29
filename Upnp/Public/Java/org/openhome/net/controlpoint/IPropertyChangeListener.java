package org.openhome.net.controlpoint;

/**
 * Listener interface for notification of when a property has changed.
 */
public interface IPropertyChangeListener
{
	/**
	 * Be notified that the property that this listener is registered with has
	 * changed.
	 */
	public void notifyChange();
}
