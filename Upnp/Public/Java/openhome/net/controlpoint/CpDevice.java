/**
 * Class wrapping around native calls for control point devices in OhNet.
 */
package openhome.net.controlpoint;

import ohnet.CpDeviceListListener;
import ohnet.CpUpnpDeviceListFactory;
import ohnet.ICpDeviceList;
import ohnet.NetworkAdapter;
import ohnet.NetworkAdapterList;
import openhome.net.core.InitParams;
import openhome.net.core.Library;

public class CpDevice
{
	
	private long iHandle = 0;
    
    private native String CpDeviceCUdn(long devPtr);
    private native void CpDeviceCAddRef(long devPtr);
    private native void CpDeviceCRemoveRef(long devPtr);
    private native int CpDeviceCGetAttribute(long devPtr, String aKey, String[] aValue);
    
    static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
    
    public CpDevice(long aHandle)
    {
    	iHandle = aHandle;
    }
    
    public long getHandle()
    {
    	return iHandle;
    }
    
    /**
     * Get the unique device identifier of the given device.
     * @return			Unique identifier of device.
     */
    public String getUdn()
    {
        return CpDeviceCUdn(iHandle);
    }
    
    public void addReference()
    {
    	CpDeviceCAddRef(iHandle);
    }
    
    public void removeRef()
    {
    	CpDeviceCRemoveRef(iHandle);
    }
    
    /**
     * Read an attribute of device.
     * @param key	Key from protocol-specific list.
     * @param val	Empty String array of size 1.
     * First and only element will be replaced with attribute matching key.
     * @return	1 if attribute was available, 0 otherwise.
     */
    public boolean getAttribute(String aKey, String[] aValue) {
    	// TODO: Check for null pointer to array.
    	int result = CpDeviceCGetAttribute(iHandle, aKey, aValue);
    	
    	return (result != 0);
    }
    
    public static void main(String[] args)
    {
        Library on = new Library();
        //CpDevice cd = new CpDevice();
        
        InitParams params = new InitParams();
        
        on.initialise(params);
        NetworkAdapterList netList = on.subnetListCreate();
        NetworkAdapter netAdptr = on.getSubnet((int) netList.iHandle, 0);
        System.out.println("First adapter address in subnet list:");
        System.out.println(netAdptr.getAddress().getHostAddress());
        System.out.println("First adapter subnet in subnet list:");
        System.out.println(netAdptr.getSubnet().getHostAddress());
        on.startCp(netAdptr.getSubnet());
        
//        int devListPtr = cd.createUpnpServiceTypeList("av.openhome.org", "Radio", 1);
        
        //CpDeviceList devList = new CpDeviceList();
        CpDeviceListListener listener = new CpDeviceListListener();
        CpUpnpDeviceListFactory devListFactory = new CpUpnpDeviceListFactory();
        ICpDeviceList devList = devListFactory.createListAll(listener, listener);
        
        //devList.addDeviceAddedListener(listener);
        //devList.initialiseDeviceListUpnpServiceType("av.openhome.org", "Radio", 1);
        //devList.initialiseDeviceListUpnpAll();
        //devList.initialiseDeviceListUpnpRoot();
        //devList.initialiseDeviceListUpnpUuid("chrisc");
//        
        try {
            Thread.sleep(5000);
        } catch (InterruptedException ie) {
            
        }
        
        System.out.println("Refreshing list...");
        devList.refresh();
        
        try {
            Thread.sleep(5000);
        } catch (InterruptedException ie) {
            
        }
//        
////        cd.destroyDeviceList(devListPtr);
        
        devList.destroy();
        on.subnetListDestroy((int) netList.iHandle);
        on.close();

        
        System.out.println("OhNet stack closed.");
    }
    
}
