package ohnet;

import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class NetworkAdapter
{
	private native int OhNetNetworkAdapterAddress(long ptr);
	private native int OhNetNetworkAdapterSubnet(long ptr);
	private native String OhNetNetworkAdapterName(long ptr);
	private native String OhNetNetworkAdapterFullName(long ptr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	public long adptrPtr = 0;
	
	public NetworkAdapter(long ptr)
	{
		adptrPtr = ptr;
	}
	
	private byte[] ipv4IntToByteArray(int ipv4)
	{
		byte[] addr = new byte[4];

		for (int i = 3; i >= 0; i--) {
			addr[i] = (byte) (ipv4 >> i*8);
		}
		
		return addr;
	}
	
	public Inet4Address getAddress()
	{
		int intAddr = OhNetNetworkAdapterAddress(adptrPtr);
		
		byte[] addr = ipv4IntToByteArray(intAddr);

		try {
			return (Inet4Address) InetAddress.getByAddress(addr);
		}
		catch (UnknownHostException uhe)
		{
			return null;
		}
	}
	
	public Inet4Address getSubnet()
	{
		int intAddr = OhNetNetworkAdapterSubnet(adptrPtr);

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
	
	public String getName()
	{
		return OhNetNetworkAdapterName(adptrPtr);
	}
	
	public String getFullName()
	{
		return OhNetNetworkAdapterFullName(adptrPtr);
	}
	
	public String toString()
	{
		return getName();
	}

}
