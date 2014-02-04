package org.openhome.net.core;


public class SubnetList
{
	private static native long OhNetSubnetListCreate();
	private static native int OhNetSubnetListSize(long aList);
	private static native long OhNetSubnetAt(long aList, int aIndex);
	private static native void OhNetSubnetListDestroy(long aList);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle;
	
	/**
	 * Create a vector of the available subnets
	 * 
	 * <p>Caller must later call {@link #destroy}.
	 */
	public SubnetList()
	{
		iHandle = OhNetSubnetListCreate();
	}
	
	/**
	 * Get the handle to the underlying native subnet list.
	 * 
	 * @return	handle to the underlying subnet list.
	 */
	public long getHandle()
	{
		return iHandle;
	}
	
	/**
	 * Query the number of items in a subnet list.
	 * 
	 * @return	the number of items in the subnet.
	 */
	public int size()
	{
		return OhNetSubnetListSize(iHandle);
	}
	
    /**
     * Get a handle to a particular subnet from a subnet list.
     *
     * @param aIndex	index of the list item to get a handle to <tt>(0..size()-1)</tt>.
     * @return			handle to the subnet.
     */
    public NetworkAdapter getSubnet(int aIndex)
    {
        return new NetworkAdapter(OhNetSubnetAt(iHandle, aIndex), false);
    }
	
    /**
     * Destroy this subnet list.
     */
    public void destroy()
    {
    	OhNetSubnetListDestroy(iHandle);
    }
}
