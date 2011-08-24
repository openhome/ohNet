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
	 * <p>Clients who are interested this new device should call
	 * <tt>CpDevice.addRef()</tt> on it and add it to some local collection.
	 * This callback will never be run for a device that is already in the list.
	 * 
	 * @param aDevice	the device that has been added to the list.
	 */
	public void deviceAdded(CpDevice aDevice);
	
	/**
	 * Called when a device is removed from a device list.
	 * 
	 * <p>Clients who had previously stored a reference to the device in the
	 * <tt>deviceAdded()</tt> method should call <tt>CpDevice.removeRef()</tt>
	 * and remove the device from their local collection.
	 * Clients who had not previously claimed a reference to a device must not
	 * call <tt>CpDevice.removeRef()</tt>.
	 * 
	 * @param aDevice	the device that has been removed from the list.
	 */
	public void deviceRemoved(CpDevice aDevice);
}
