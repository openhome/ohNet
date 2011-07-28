package org.openhome.net.core;

import java.net.Inet4Address;


import ohnet.NetworkAdapter;

public class Library
{
    private static native long OhNetLibraryInitialise(long aInitParams); 
    private static native long OhNetLibraryInitialiseMinimal(long aInitParams);
    private static native void OhNetLibraryStartCp(int aSubnet);
    private static native void OhNetLibraryStartDv();
    private static native void OhNetLibraryStartCombined(int aSubnet);
    private static native void OhNetLibraryClose();
    private static native void OhNetSetCurrentSubnet(long aSubnet);
    private static native long OhNetCurrentSubnetAdapter();

    static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
    
    public Library() {}
    
    /**
     * Initialise the library.
     * 
     * <p>Must be called before any other library function.
     * 
     * @param aInitParams	initialisation options.  Ownership of these passes to
     * 						the library
     */
    public void initialise(InitParams aInitParams) {
    	OhNetLibraryInitialise(aInitParams.getHandle());
    }
    
    /**
     * Create a library.
     * @param aInitParams	initialisation options.  Ownership of these passes to
     * 						the library
     * @return				the instantiated library.
     */
    public static Library Create(InitParams aInitParams)
    {
        Library instance = new Library();
        instance.initialise(aInitParams);
        
        return instance;
    }
    
    /**
     * Lightweight alternative to {@link #initialise}.
     * 
     * <p>Intended for unit tests which are useful to platform porting only.
     * 
     * <p>No class APIs other than {@link #close} can be called if this is used.
     * 
     * @param aInitParams	initialisation options. Ownership of these passes
     * 						to the library.
     */
    public void InitialiseMinimal(InitParams aInitParams)
    {
        if (0 != OhNetLibraryInitialiseMinimal(aInitParams.getHandle()))
        {
            throw new LibraryException();
        }
    }
    
    /**
     * Start the library as a UPnP control point stack.
     * 
     * @param aSubnet	subnet address of the network adapter to use.
     * @return			a control-point stack. Can be used to create device
     * 					list factories.
     */
    public ControlPointStack startCp(Inet4Address aSubnet)
    {
        int ipv4Addr = getIpv4Int(aSubnet);
        OhNetLibraryStartCp(ipv4Addr);
        return new ControlPointStack();
    }
    
    /**
     * Start the library as both UPnP control point and device stacks.
     * 
     * @param aSubnet	subnet address of the network adapter for the control
     * 					point stack to use. (The device stack operates on all
     * 					adapters.)
     * @return			a combined control-point and device stack.
     */
    public CombinedStack startCombined(Inet4Address aSubnet)
    {
    	int ipv4Addr = getIpv4Int(aSubnet);
        OhNetLibraryStartCombined(ipv4Addr);
        return new CombinedStack();
    }
    
    /**
     * Start the library as a UPnP device stack.
     * 
     * @return a device stack. Can be used to create device factories.
     */
    public DeviceStack startDv()
    {
    	OhNetLibraryStartDv();
    	return new DeviceStack();
    }
    
    public NetworkAdapter getCurrentSubnetAdapter() {
    	long ptr = OhNetCurrentSubnetAdapter();
    	
    	if (ptr == 0) {
    		return null;
    	} else {
    		return new NetworkAdapter(ptr);
    	}
    }
    
    /**
     * Close the ohNet library. Must be called sometime after calling startCp()
     * to allow stack to be shutdown.
     */
    public void close() {
        OhNetLibraryClose();
    }
    
    /**
     * Create a vector of the available subnets.
     * 
     * @return	a list of the available subnets.
     */
    public NetworkAdapterList subnetListCreate()
    {
        return new NetworkAdapterList();
    }
    
    /**
     * Set which subnet the library should use.
     * 
     * <p>Device lists and subscriptions will be automatically updated.
     * No other subnet will be selected if aSubnet is not available.
     * 
     * @param aSubnet	handle returned by {@link #NetworkAdapterList.subnetAt}.
     */
    public void setCurrentSubnet(NetworkAdapter aSubnet)
    {
    	OhNetSetCurrentSubnet(aSubnet.getHandle());
    }
    
    /**
     * Query which network adapter is currently selected.
     * 
     * @return the currently selected adapter.
     */
    public NetworkAdapter getCurrentSubnet()
    {
    	return new NetworkAdapter(OhNetCurrentSubnetAdapter());
    }
    
    /**
     * Convert an {@code Inet4Address} into an integer representation in
     * network byte order.
     * 
     * @param aAddress	the IPv4 address object to convert.
     * @return			the integer representation in network byte order.
     */
    private int getIpv4Int(Inet4Address aAddress)
    {
    	byte[] ipv4Bytes = aAddress.getAddress();
        int ipv4Addr = ipv4Bytes[0];
        
        for (int i = 1; i < 4; i++) {
            ipv4Addr +=  ipv4Bytes[i] << i*8;
        }
        
        return ipv4Addr;
    }
    
    public static void main(String[] args) {
        Library lib = new Library();
        InitParams params = new InitParams();
        lib.initialise(params);
        
        System.out.println("Params TCP timeout:\t\t\t" + params.getTcpConnectTimeoutMs() + " ms");
        System.out.println("Params search time:\t\t\t" + params.getMsearchTimeSecs() + " secs");
        
        NetworkAdapterList netList = lib.subnetListCreate();
        //NetworkAdapter netAdptr = on.getSubnet((int) netList.listPtr, 0);
        NetworkAdapter netAdptr = netList.getSubnet(0);
        
        System.out.println("Size of network adapter list: " + netList.size());
        
//        NetworkAdapter adptr = on.getCurrentSubnetAdapter();
//        if (adptr == null) {
//        	System.out.println("No adapter currently selected.");
//        } else {
//        	System.out.println(on.getCurrentSubnetAdapter());
//        }
        
        System.out.println("Current subnet adapter name:\t\t" + netAdptr.getName());
        System.out.println("Current subnet adapter full name:\t" + netAdptr.getFullName());
        System.out.println("Current subnet adapter address:\t\t" + netAdptr.getAddress().getHostAddress());
        System.out.println("Current subnet adapter hostname:\t" + netAdptr.getAddress().getHostName());
        System.out.println("Current subnet adapter subnet:\t\t" + netAdptr.getSubnet().getHostAddress());
        
        System.out.println("First adapter address in subnet list:");
        System.out.println(netAdptr.getAddress().getHostAddress());
        
        System.out.println("First adapter subnet in subnet list:");
        System.out.println(netAdptr.getSubnet().getHostAddress());
//        on.getSubnet(1);
//        System.out.println("Second subnet in subnet list:");
//        System.out.println(on.getNetworkInterfaceAddress());
        netList.destroy();
        lib.close();
    }
}
