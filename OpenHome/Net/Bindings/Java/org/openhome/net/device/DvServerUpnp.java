package org.openhome.net.device;

/**
 * UPnP device server.
 * 
 * <p>Publishes DvDevices as UPnP devices, serves UIs (depending on device
 * configuration) and manages subscriptions.  This works automatically across
 * all active network interfaces. One of these servers is setup automatically
 * by the device stack. This default instance will be used automatically by all
 * devices.
 * 
 * <p>Additional servers should not be required for normal use of the device
 * stack. They may however be necessary for unusual * cases where a provider is
 * required to make blocking calls to a proxy.
 */
public class DvServerUpnp
{
	private static native long DvServerUpnpCreate();
	private static native void DvServerUpnpDestroy(long aServer);
	private static native void DvServerUpnpAddDevice(long aServer, long aDevice);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle;
	
	/**
	 * Create a UPnP device server.
	 */
	public DvServerUpnp()
	{
		iHandle = DvServerUpnpCreate();
	}
	
	/**
	 * Destroy the underlying native instance of this server.
	 */
	public void dispose()
	{
		DvServerUpnpDestroy(iHandle);
		iHandle = 0;
	}
	
	/**
	 * Instruct a device to publish itself using (only) this server.
	 * 
	 * @param aDevice	the <tt>DvDevice</tt> to be published.
	 */
	public void addDevice(DvDevice aDevice)
	{
		DvServerUpnpAddDevice(iHandle, aDevice.getHandle());
	}
}
