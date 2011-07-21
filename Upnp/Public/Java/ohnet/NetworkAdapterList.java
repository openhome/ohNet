package ohnet;

public class NetworkAdapterList
{
	private native int OhNetSubnetListSize(long ptr);
	private native int OhNetSubnetAt(long ptr, int index);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	public long iHandle = 0;
	
	public NetworkAdapterList(long ptr)
	{
		iHandle = ptr;
	}
	
	public long getHandle()
	{
		return iHandle;
	}
	
	public int size()
	{
		return OhNetSubnetListSize(iHandle);
	}
	
	public NetworkAdapter subnetAt(int i)
	{
		return new NetworkAdapter(OhNetSubnetAt(iHandle, i));
	}
	
	public void finalize()
	{
		
	}
}
