package org.openhome.net.controlpoint;


/**
 * Default implementation of a device list listener. Prints the udn of a
 * given device when it is added or removed from the list.
 *
 */
public class CpDeviceListListener implements ICpDeviceListListener
{
	/**
	 * Called when a device is added to a device list. Prints a line of the
	 * form: <tt>Device added: \<device udn\></tt>.
	 */
	public void deviceAdded(CpDevice aDevice)
	{
		System.out.println("Device added: " + aDevice.getUdn());
	}
	
	/**
	 * Called when a device is removed from a device list. Prints a line of the
	 * form: <tt>Device removed: \<device udn\></tt>.
	 */
	public void deviceRemoved(CpDevice aDevice)
	{
		System.out.println("Device removed: " + aDevice.getUdn());
	}
	
}
