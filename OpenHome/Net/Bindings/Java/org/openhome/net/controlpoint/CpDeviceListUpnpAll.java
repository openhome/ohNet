package org.openhome.net.controlpoint;


/**
 * List of all UPnP devices on the current subnet.
 */
public class CpDeviceListUpnpAll extends CpDeviceList
{
	private native CpDeviceListInitialised CpDeviceListCreateUpnpAll();
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor.
	 * 
	 * @param added		delegate which will be run when a new device is detected.
	 * 					Clients who are interested this new device should call
	 *					{@link org.openhome.net.controlpoint.device#addRef} on it
	 *					and add it to some local collection.
	 * 					This callback will never be run for a device that is already in the list.
	 * @param removed	delegate which will be run when a device is removed from the network.
	 * 					Clients who had previously stored a reference to the device
	 * 					in their {@code aAdded} callback should call
	 * 					{@link org.openhome.net.controlpoint.device#removeRef} and remove the
	 * 					device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call {@link org.openhome.net.controlpoint.device#removeRef}.
	 */
	public CpDeviceListUpnpAll(ICpDeviceListListener aAdded, 
			ICpDeviceListListener aRemoved) 
	{
		iAdded = aAdded;
		iRemoved = aRemoved;
		CpDeviceListInitialised init = CpDeviceListCreateUpnpAll();
		iHandle = init.getHandle();
		iCallback = init.getCallback();
	}
}