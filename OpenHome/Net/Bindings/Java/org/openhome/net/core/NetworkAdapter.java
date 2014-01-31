package org.openhome.net.core;

import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 * Class representing a network adapter.
 */
public class NetworkAdapter
{
	private static native int OhNetNetworkAdapterAddress(long aNif);
	private static native int OhNetNetworkAdapterSubnet(long aNif);
	private static native int OhNetNetworkAdapterMask(long aNif);
	private static native String OhNetNetworkAdapterName(long aNif);
	private static native String OhNetNetworkAdapterFullName(long aNif);
    private static native void OhNetNetworkAdapterRemoveRef(long aNif);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle;
    private boolean iHasRef;
	
	/**
	 * Create a network adapter
	 * @param aSubnet
     * @param aHasRef flag indicating whether a removeRef call is needed
	 */
	public NetworkAdapter(long aSubnet, boolean aHasRef)
	{
		if (aSubnet != 0)
		{
			iHandle = aSubnet;
		}
		else
		{
			throw new NullPointerException("No currently selected network adapter.");
		}
        this.iHasRef = aHasRef;
	}
    
    /**
     * Remove a reference to a network adapter.
     *
     * <p>Must be called if this object was obtained by calling
     * {@link Library#getCurrentSubnet()}.
     */
    public synchronized void removeRef()
    {
        // ensure NetworkAdapter::RemoveRef isn't called without a valid cookie
        if (iHasRef) {
            OhNetNetworkAdapterRemoveRef(iHandle);
            iHasRef = false;
        }
    }
	
	/**
	 * Get the handle to the underlying native network adapter.
	 * 
	 * @return	handle to the underlying network adapter.
	 */
	protected long getHandle()
	{
		return iHandle;
	}
	
	/**
	 * Convert an IPv4 address in integer format to a byte array.
	 * 
	 * @param ipv4	network order integer representation of an IPv4 address.
	 * @return		IPv4 address contained within a byte array.
	 */
	private byte[] ipv4IntToByteArray(int ipv4)
	{
		byte[] addr = new byte[4];

        addr[0] = (byte) (ipv4 >> 24);
        addr[1] = (byte) (ipv4 >> 16);
        addr[2] = (byte) (ipv4 >> 8);
        addr[3] = (byte) ipv4;		
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
	 * Get the netmask for a given network interface.
	 * 
	 * @return	IPv4 address
	 */
	public Inet4Address getMask()
	{
		int intAddr = OhNetNetworkAdapterMask(iHandle);

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
	 * @return	<tt>String</tt> in the form <tt>a.b.c.d (name)</tt>.
	 */
	public String getFullName()
	{
		return OhNetNetworkAdapterFullName(iHandle);
	}
}
