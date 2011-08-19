package org.openhome.net.controlpoint;


/**
 * List of all UPnP devices of a given service type on the current subnet.
 */
public class CpDeviceListUpnpServiceType extends CpDeviceList
{
	private native CpDeviceListInitialised CpDeviceListCreateUpnpServiceType(String aDomainName, String aServiceType, int aVersion);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor.
	 * 
	 * @param aDomainName	vendor domain for the target service (e.g. <tt>upnp.org</tt>).
	 * @param aServiceType	name of the target service.
	 * @param aVersion		version number for the target service.
	 * @param aAdded		delegate which will be run when a new device is detected.
	 * 						Clients who are interested this new device should call
	 *						<tt>CpDevice.addRef()</tt> on it and add it to some local collection.
	 * 						This callback will never be run for a device that is already in the list.
	 * @param aRemoved		delegate which will be run when a device is removed from the network.
	 * 						Clients who had previously stored a reference to the device
	 * 						in their <tt>aAdded</tt> callback should call
	 * 						<tt>CpDevice.removeRef()</tt> and remove the device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call <tt>CpDevice.removeRef()</tt>.
	 */
	public CpDeviceListUpnpServiceType(String aDomainName, String aServiceType,
			int aVersion, ICpDeviceListListener aAdded, ICpDeviceListListener aRemoved)
	{
		
		iAdded = aAdded;
		iRemoved = aRemoved;
		CpDeviceListInitialised init = CpDeviceListCreateUpnpServiceType(aDomainName, aServiceType, aVersion);
		iHandle = init.getHandle();
		iCallback = init.getCallback();
	}
}