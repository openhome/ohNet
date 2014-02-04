package org.openhome.net.core;

/**
 * Listener interface for notification of subnet and adapter changes.
 *
 */
public interface INetworkAdapterListener
{
    /**
     * Receive a subnet or adapter change event.
     */
    public void notifyChange(NetworkAdapter aAdapter);
}
