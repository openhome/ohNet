package org.openhome.net.controlpoint;


/**
 * List of all UPnP devices of a given device type on the current subnet.
 */
public class CpDeviceListUpnpDeviceType extends CpDeviceList
{
	private native long CpDeviceListCreateUpnpDeviceType(String aDomainName, String aDeviceType, int aVersion);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor.
	 * 
	 * @param aDomainName	vendor domain for the target device.
	 * @param aDeviceType	name of the target device.
	 * @param aVersion		version number for the target device.
	 * @param added			delegate which will be run when a new device is detected.
	 * 						Clients who are interested this new device should call
	 *						{@link org.openhome.net.controlpoint.device#addRef} on it
	 *						and add it to some local collection.
	 * 						This callback will never be run for a device that is already in the list.
	 * @param removed		delegate which will be run when a device is removed from the network.
	 * 						Clients who had previously stored a reference to the device
	 * 						in their {@code aAdded} callback should call
	 * 						{@link org.openhome.net.controlpoint.device#removeRef} and remove the
	 * 						device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call {@link org.openhome.net.controlpoint.device#removeRef}.
	 */
	public CpDeviceListUpnpDeviceType(String aDomainName, String aDeviceType,
		int aVersion, ICpDeviceListListener aAdded, ICpDeviceListListener aRemoved)
	{
		
		iAdded = aAdded;
		iRemoved = aRemoved;
		iHandle = CpDeviceListCreateUpnpDeviceType(aDomainName, aDeviceType, aVersion);
	}
}