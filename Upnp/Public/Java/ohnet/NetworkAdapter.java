package ohnet;

import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class NetworkAdapter
{
	private static native int OhNetNetworkAdapterAddress(long ptr);
	private static native int OhNetNetworkAdapterSubnet(long ptr);
	private static native String OhNetNetworkAdapterName(long ptr);
	private static native String OhNetNetworkAdapterFullName(long ptr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle;
	
	/**
	 * Create a network adapter
	 * @param aSubnet
	 */
	public NetworkAdapter(long aSubnet)
	{
		if (aSubnet != 0)
		{
			iHandle = aSubnet;
		}
		else
		{
			throw new NullPointerException("No currently selected network adapter.");
		}
	}
	
	/**
	 * Get the handle to the underlying native network adapter.
	 * 
	 * @return	handle to the underlying network adapter.
	 */
	public long getHandle()
	{
		return iHandle;
	}
	
	private byte[] ipv4IntToByteArray(int ipv4)
	{
		byte[] addr = new byte[4];

		for (int i = 3; i >= 0; i--) {
			addr[i] = (byte) (ipv4 >> i*8);
		}
		
		return addr;
	}
	
	/**
	 * Get the IP address for a given network interface.
	 * 
	 * @return	IPv4 address.
	 */
	public Inet4Address getAddress()
	{
		int intAddr = OhNetNetworkAdapterAddress(iHandle);
		
		byte[] addr = ipv4IntToByteArray(intAddr);

		try {
			return (Inet4Address) InetAddress.getByAddress(addr);
		}
		catch (UnknownHostException uhe)
		{
			return null;
		}
	}
	
	/**
	 * Get the subnet address for a given network interface.
	 * 
	 * @return	IPv4 address
	 */
	public Inet4Address getSubnet()
	{
		int intAddr = OhNetNetworkAdapterSubnet(iHandle);

		byte[] addr = ipv4IntToByteArray(intAddr);
		
		try
		{
			return (Inet4Address) InetAddress.getByAddress(addr);
		}
		catch (UnknownHostException uhe)
		{
			return null;
		}
	}
	
	/**
	 * Get the name for the network interface.
	 * 
	 * @return	the name of the network interface.
	 */
	public String getName()
	{
		return OhNetNetworkAdapterName(iHandle);
	}
	
	/**
	 * Get the full name for a given network interface.
	 * 
	 * @return	{@link #String} in the form {@code a.b.c.d (name)}.
	 */
	public String getFullName()
	{
		return OhNetNetworkAdapterFullName(iHandle);
	}
	
	public String toString()
	{
		return getName();
	}

}
