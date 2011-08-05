package org.openhome.net.controlpoint;

/**
 * Protocol-independent device.
 *
 * <p>Instance of this class are reference counted and are automatically deleted
 * when the reference count falls to zero.
 * All references to class instances must have been removed before
 * {@code Library.close()} is called.
 */
public class CpDevice
{
	
	private long iHandle;
    
    private static native String CpDeviceCUdn(long aDevice);
    private static native void CpDeviceCAddRef(long aDevice);
    private static native void CpDeviceCRemoveRef(long aDevice);
    private static native int CpDeviceCGetAttribute(long aDevice, String aKey, String[] aValue);
    
    static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
    
    /**
     * Constructor. Not intended for external use.
     * 
     * <p>Devices should be constructed via {@link #CpDevice} or
     * {@code CpDeviceList} subclasses.
     * 
     * @param aHandle	handle to the underlying native device.
     */
    public CpDevice(long aHandle)
    {
    	iHandle = aHandle;
    }
    
    /**
     * Get the handle to the underlying native device.
     * 
     * @return	handle to the underlying native device.
     */
    protected long getHandle()
    {
    	return iHandle;
    }
    
    /**
     * Query the unique identifier associated with a device.
     * @return	device's (universally unique) name
     */
    public String getUdn()
    {
        return CpDeviceCUdn(iHandle);
    }
    
    /**
     * Claim a reference to a device.
     * 
     * <p>Can only be called from code that can guarantee another reference is
     * already held. Each call to {@link #addRef()} must later have exactly one
     * matching call to {@link #removeRef()}.
     */
    public void addRef()
    {
    	CpDeviceCAddRef(iHandle);
    }
    
    /**
     * Remove a reference to a device.
     * 
     * <p>Removing the final reference causes a device to be deleted.
     */
    public void removeRef()
    {
    	CpDeviceCRemoveRef(iHandle);
    }
    
    /**
     * Query the value of one of the device's attributes.
     * 
     * @param aKey		the name of the attribute being queried. Available
     * 					attributes will be listed in a protocol-specific header.
     * @param aValue	empty String array of size 1.
     * 					First and only element will be replaced with attribute matching key.
     * @return			{@code true} if the attribute was available on the device;
     * 					{@code false} otherwise. {@code aValue} will not have been set if
     * 					false is returned
     */
    public boolean getAttribute(String aKey, String[] aValue) {
    	int result = CpDeviceCGetAttribute(iHandle, aKey, aValue);
    	
    	return (result != 0);
    }
}
