package org.openhome.net.controlpoint;


/**
 * List of all root UPnP devices on the current subnet.
 */
public class CpDeviceListUpnpRoot extends CpDeviceList
{
	private native CpDeviceListInitialised CpDeviceListCreateUpnpRoot();
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor.
	 * @param aListener		delegate which will be called when a device is detected or removed.
	 * 						Clients who are interested in a newly detected device should call
	 *						<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *						and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *						device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call <tt>CpDevice.removeRef()</tt>.
	 */
	public CpDeviceListUpnpRoot(ICpDeviceListListener aListener)
	{
		iListener = aListener;
		CpDeviceListInitialised init = CpDeviceListCreateUpnpRoot();
		iHandle = init.getHandle();
		iCallback = init.getCallback();
	}
}