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
	 * @param aListener		delegate which will be called when a device is detected or removed.
	 * 						Clients who are interested in a newly detected device should call
	 *						<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *						and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *						device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call <tt>CpDevice.removeRef()</tt>.
	 */
	public CpDeviceListUpnpServiceType(String aDomainName, String aServiceType,
			int aVersion, ICpDeviceListListener aListener)
	{
		
		iListener = aListener;
		CpDeviceListInitialised init = CpDeviceListCreateUpnpServiceType(aDomainName, aServiceType, aVersion);
		iHandle = init.getHandle();
		iCallback = init.getCallback();
	}
}