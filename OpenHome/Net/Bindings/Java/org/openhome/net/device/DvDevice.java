package org.openhome.net.device;

public class DvDevice
{
	private static native long DvDeviceCreate(String aUdn);
	private static native void DvDeviceDestroy(long aDevice);
	private static native String DvDeviceUdn(long aDevice);
	private static native int DvDeviceEnabled(long aDevice);
	private static native void DvDeviceSetEnabled(long aDevice);
	private static native void DvDeviceSetDisabled(long aDevice, IDvDeviceListener aCompleted);
	private static native String DvDeviceGetAttribute(long aDevice, String aKey);
	private static native void DvDeviceSetAttribute(long aDevice, String aKey, String aValue);
//	private static native void OhNetFree(long aPtr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	protected long iHandle;
	
	protected DvDevice() { }
	
	/**
	 * Constructor. Creates a device without support for any protocol but
	 * capable of adding services or attributes. This should only be used with
	 * CpDeviceDv.
	 * 
	 * @param aUdn 	universally unique identifier.  The caller is responsible
	 * 				for calculating/assigning this.
	 */
	public DvDevice(String aUdn)
    {
        iHandle = DvDeviceCreate(aUdn);
    }
	
	/**
	 * Destroy the underlying native instance. Must be called for each class instance.
	 * Must be called before <tt>Library.close()</tt>.
	 */
	public void destroy()
	{
		DvDeviceDestroy(iHandle);
	}
	
	/**
	 * Get the handle to the underlying native device.
	 * 
	 * @return	handle to the underlying native device.
	 */
	public long getHandle()
	{
		return iHandle;
	}
	
	/**
	 * Query the (client-specified) unique device name.
	 * 
	 * @return	the name passed to {@link #DvDevice}.
	 */
	public String getUdn()
    {
		return DvDeviceUdn(iHandle);
    }
	
	/**
	 * Query whether the device is enabled.
	 * 
	 * @return	<tt>true</tt> if the device is enabled; <tt>false</tt> otherwise.
	 */
	public boolean enabled()
	{
		int enabled = DvDeviceEnabled(iHandle);
		if (enabled != 0)
		{
			return true;
		}
		return false;
	}
	
	/**
	 * Set the device ready for external use.
	 * 
	 * <p>When this returns, the device will be available for use using any of the
	 * protocols the device stack supports. Services must not be added
	 * (<tt>DvProvider</tt>-derived classes created using this device) and attributes
	 * must not be set while a device is enabled. If these need to change in
	 * future, the device must first be disabled.
	 */
	public void setEnabled()
    {
        DvDeviceSetEnabled(iHandle);
    }
	
	/**
	 * Disable the device, withdrawing its availability for external use.
	 * 
	 * <p>Services can be added and attributes can be set once a device is disabled.
	 * The device will not be available for use again until {@link #setEnabled}
	 * is called again.
	 * 
	 * <p>This call is asynchronous so returns before the device is fully disabled.
	 * Wait for the <tt>aCompleted</tt> callback before adding services or setting
	 * attributes.
	 * 
	 * @param aCompleted	Listener which is called when the device is fully disabled. 
	 * 						Until this runs, the device should be considered to still
	 * 						be enabled.
	 */
	public void setDisabled(IDvDeviceListener aCompleted)
    {
		if (aCompleted == null)
		{
			throw new NullPointerException("DvDevice.setDisabled: aCompleted param is null");
		}
        DvDeviceSetDisabled(iHandle, aCompleted);
    }
	
	/**
	 * Query the value of an atrribute.
	 * 
	 * @param aKey	string of the form <tt>protocol_name.protocol_specific_key</tt>.
	 * @return		the attribute or null if the attribute has not been set.
	 */
	public String getAttribute(String aKey)
    {
		return DvDeviceGetAttribute(iHandle, aKey);
    }
	
	/**
	 * Set the value of an attribute.
	 * 
	 * @param aKey		<tt>String</tt> of the form <tt>protocol_name.protocol_specific_key</tt>.
	 * @param aValue	attribute will be set to a copy of this <tt>String</tt>.
	 */
	public void setAttribute(String aKey, String aValue)
    {
        DvDeviceSetAttribute(iHandle, aKey, aValue);
    }
	
}
