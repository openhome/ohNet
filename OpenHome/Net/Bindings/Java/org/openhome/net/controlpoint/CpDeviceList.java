package org.openhome.net.controlpoint;


/**
 * List of devices available on the current subnet.
 * 
 * <p>Runs callbacks when a device is detected on or removed from a network.
 * Clients can't iterate the list's contents so must take note of the device in
 * their 'added' callback and remove the device in their 'removed' callback.
 * Since CpDevice instances are reference counted, a reference must be claimed
 * inside the 'added' callback and removed inside the 'removed' callback.
 * 
 * <p>This class can't be directly instantiated.  Clients should instead use
 * subclasses which will define policy on how to detect devices etc.
 * 
 * <p>{@link destroy} must be called before {@link org.openhome.net.core.Library#close}.
 */
public class CpDeviceList implements ICpDeviceList
{
	private static native void CpDeviceListDestroy(long aListHandle);
	private static native void CpDeviceListRefresh(long aListHandle);

	protected long iHandle;
	protected ICpDeviceListListener iAdded;
	protected ICpDeviceListListener iRemoved;
	
	
	/**
	 * Must be called for each class instance. Must be called before
	 * {@link org.openhome.net.core.Library#close}.
	 */
	public void destroy()
	{
		if (iHandle != 0)
		{
			CpDeviceListDestroy(iHandle);
			iHandle = 0;
		}
	}
	
	/**
	 * Refresh the contents of the list.
	 * 
	 * <p>This may be a useful way to quickly update a list after a device has
	 * been removed abruptly from the network (without announcing its removal).
	 * 
	 * <p>The 'added' callback may run any time after this is called to notify new devices.
	 * Any removed devices will be notified by a burst of calls to the 'removed' callback
	 * {@code org.openhome.net.core.InitParams.getMsearchTimeSecs()} seconds after this call is made.
	 * There is no notification that a refresh has completed. Existing CpDevice instances
	 * can be used as normal throughout the refresh.
	 */
	public void refresh()
	{
		CpDeviceListRefresh(iHandle);
	}
	
    /**
     * Callback method for native code to use when a device is detected as
     * having been added to the network.
     * 
     * @param aDevice	handle to the added device.
     */
    public void deviceAdded(long aDevice)
    {
    	CpDevice dev = new CpDevice(aDevice);
    	iAdded.deviceAdded(dev);
    }
    
    /**
     * Callback method for native code to use when a device is detected as
     * having been removed from the network.
     * 
     * @param aDevice	handle to the removed device.
     */
    public void deviceRemoved(long aDevice)
    {
    	CpDevice dev = new CpDevice(aDevice);
    	iRemoved.deviceRemoved(dev);
    }
}
