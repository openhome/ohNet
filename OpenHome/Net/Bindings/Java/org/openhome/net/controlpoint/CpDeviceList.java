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
 * <p>{@link #destroy} must be called before <tt>Library.close()</tt>.
 */
public class CpDeviceList implements ICpDeviceList
{
	private static native void CpDeviceListDestroy(long aListHandle, long aCallback);
	private static native void CpDeviceListRefresh(long aListHandle);
	
	protected class CpDeviceListInitialised
	{
		private long iHandle;
		private long iCallback;
		
		public CpDeviceListInitialised(long aHandle, long aCallback)
		{
			iHandle = aHandle;
			iCallback = aCallback;
		}
		public long getHandle()
		{
			return iHandle;
		}
		public long getCallback()
		{
			return iCallback;
		}
	}

	protected long iHandle;
	protected long iCallback;
	protected ICpDeviceListListener iListener;
	
	
	/**
	 * Must be called for each class instance. Must be called before
	 * {@link org.openhome.net.core.Library#close}.
	 */
	public void destroy()
	{
		if (iHandle != 0)
		{
			CpDeviceListDestroy(iHandle, iCallback);
			iHandle = 0;
			iCallback = 0;
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
	 * <tt>org.openhome.net.core.InitParams.getMsearchTimeSecs()</tt> seconds after this call is made.
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
        try
        {
        	iListener.deviceAdded(dev);
        }
        catch (ProxyError pe)
        {
            String desc = pe.getErrorDescription();
            if (desc == null)
                desc = "<unknown>";
            System.out.println("WARNING: ProxyError (" + pe.getErrorCode() + ":" + desc + ") thrown in device list added callback");
        }
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
    	iListener.deviceRemoved(dev);
    }
}
