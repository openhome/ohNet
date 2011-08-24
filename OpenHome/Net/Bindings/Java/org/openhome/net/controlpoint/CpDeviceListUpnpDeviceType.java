package org.openhome.net.controlpoint;


/**
 * List of all UPnP devices of a given device type on the current subnet.
 */
public class CpDeviceListUpnpDeviceType extends CpDeviceList
{
	private native CpDeviceListInitialised CpDeviceListCreateUpnpDeviceType(String aDomainName, String aDeviceType, int aVersion);
	
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
	 * @param aListener		delegate which will be called when a device is detected or removed.
	 * 						Clients who are interested in a newly detected device should call
	 *						<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *						and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *						device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call <tt>CpDevice.removeRef()</tt>.
	 */
	public CpDeviceListUpnpDeviceType(String aDomainName, String aDeviceType,
		int aVersion, ICpDeviceListListener aListener)
	{
		
		iListener = aListener;
		CpDeviceListInitialised init = CpDeviceListCreateUpnpDeviceType(aDomainName, aDeviceType, aVersion);
		iHandle = init.getHandle();
		iCallback = init.getCallback();
	}
}