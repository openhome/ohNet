package org.openhome.net.controlpoint;


/**
 * Interface defining methods that may be called when a device is added or
 * removed from a UPnP device list.
 */
public interface ICpDeviceListListener
{
	/**
	 * Called when a device is added from a device list.
	 * 
	 * @param aDevice	the device that has been added to the list.
	 */
	public void deviceAdded(CpDevice aDevice);
	
	/**
	 * Called when a device is removed from a device list.
	 * 
	 * @param aDevice	the device that has been removed from the list.
	 */
	public void deviceRemoved(CpDevice aDevice);
}
