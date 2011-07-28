package ohnet;

import java.util.LinkedList;
import java.util.List;

import openhome.net.controlpoint.CpDevice;


public class CpDeviceList implements ICpDeviceList
{
	private native void CpDeviceListDestroy(long listPtr);
	private native void CpDeviceListRefresh(long listPtr);
	private native long CpDeviceListCreateUpnpAll();
	private native long CpDeviceListCreateUpnpRoot();
	private native long CpDeviceListCreateUpnpUuid(String uuid);
	private native long CpDeviceListCreateUpnpDeviceType(String domName, String devType, int version);
	private native long CpDeviceListCreateUpnpServiceType(String domName, String servType, int version);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long listPtr = 0;
	protected List<ICpDeviceListListener> addedListeners = null;
	protected List<ICpDeviceListListener> removedListeners = null;
	
	/**
	 * Default initialiser.
	 * Must be called prior to retrieving pointer to a native list, so that the
	 * Java object can be passed in to functions which create device lists,
	 * allowing callbacks to be successfully registered with the object.
	 * 
	 * This also allows listeners to be registered with the list prior to
	 * device discovery functions, ensuring all device discovery callbacks are
	 * successfully handled.
	 * 
	 */
	protected CpDeviceList()
	{
		listPtr = 0;
		addedListeners = new LinkedList<ICpDeviceListListener>();
		removedListeners = new LinkedList<ICpDeviceListListener>();
	}
	
	/**
	 * Destroy device list before closing control point stack.
	 */
	public void destroy()
	{
		if (listPtr != 0)
		{
			CpDeviceListDestroy(listPtr);
			listPtr = 0;
		}
	}
	
	/**
	 * Ensures native device list is destroyed when this object is garbage
	 * collected.
	 * Probably redundant, as destroy() MUST be called before CP stack is closed.
	 */
	public void finalize()
	{
		if (listPtr != 0)
		{
			CpDeviceListDestroy(listPtr);
		}
	}
	
	/**
	 * Refresh this device list. Will results in calls to callback methods
	 * deviceAdded() and deviceRemoved().
	 */
	public void refresh()
	{
		if (listPtr != 0)
		{
			CpDeviceListRefresh(listPtr);
		}
	}
	
	public void addDeviceAddedListener(ICpDeviceListListener l)
	{
		addedListeners.add(l);
	}
	
	public void addDeviceRemovedListener(ICpDeviceListListener l)
	{
		removedListeners.add(l);
	}
	
    /**
     * Callback method for native code to use when a device is detected as
     * having been added to the network.
     * 
     * @param devPtr Handle to the added device.
     */
    public void deviceAdded(long devPtr)
    {
    	CpDevice dev = new CpDevice(devPtr);
    	
    	for (ICpDeviceListListener l : addedListeners)
    	{
    		l.deviceAdded(dev);
    	}
    }
    
    /**
     * Callback method for native code to use when a device is detected as
     * having been removed from the network.
     * 
     * @param devPtr Handle to the removed device.
     */
    public void deviceRemoved(long devPtr)
    {
    	CpDevice dev = new CpDevice(devPtr);
    	
    	for (ICpDeviceListListener l : removedListeners)
    	{
    		l.deviceRemoved(dev);
    	}
    }
    
    protected void initialiseDeviceListUpnpAll()
    {
    	listPtr = CpDeviceListCreateUpnpAll();
    }
    
    protected void initialiseDeviceListUpnpRoot()
    {
    	listPtr = CpDeviceListCreateUpnpRoot();
    }
    
    protected void initialiseDeviceListUpnpUuid(String uuid)
    {
    	listPtr = CpDeviceListCreateUpnpUuid(uuid);
    }

    protected void initialiseDeviceListUpnpDeviceType(String domName, String devType, int version)
    {
    	listPtr = CpDeviceListCreateUpnpDeviceType(domName, devType, version);
    }

    /**
     * Create a UPnP service type list of custom type.
     * 
     * @param domainName	Domain name to search for devices.
     * @param serviceType	Type of service to search for.
     * @param version		Version # of services to search for.
     * @return				Handle to service type list.
     */
    protected void initialiseDeviceListUpnpServiceType(String domName, String servType, int version)
    {
    	listPtr = CpDeviceListCreateUpnpServiceType(domName, servType, version);
    }
}
