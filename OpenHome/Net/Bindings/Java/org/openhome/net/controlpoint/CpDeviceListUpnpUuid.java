package org.openhome.net.controlpoint;


/**
 * List of all UPnP devices with a given uuid (udn) on the current subnet.
 */
public class CpDeviceListUpnpUuid extends CpDeviceList
{
	private native CpDeviceListInitialised CpDeviceListCreateUpnpUuid(String aUuid);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor.
	 * 
	 * @param aUuid		unique identifier for the target device.	
	 * @param aListener	delegate which will be called when a device is detected or removed.
	 * 					Clients who are interested in a newly detected device should call
	 *					<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *					and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *					device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call <tt>CpDevice.removeRef()</tt>.
	 */
	public CpDeviceListUpnpUuid(String aUuid, ICpDeviceListListener aListener)
	{
		iListener = aListener;
		CpDeviceListInitialised init = CpDeviceListCreateUpnpUuid(aUuid);
		iHandle = init.getHandle();
		iCallback = init.getCallback();
	}
}