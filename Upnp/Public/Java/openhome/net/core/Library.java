package openhome.net.core;

import java.net.Inet4Address;

import ohnet.NetworkAdapter;
import ohnet.NetworkAdapterList;

public class Library
{
    private native long OhNetLibraryInitialise(long paramsPtr);    
    private native long OhNetSubnetListCreate();
    private native int OhNetSubnetAt(long netIntListPtr, int index);
    private native int OhNetNetworkAdapterAddress(long netIntPtr);
    private native int OhNetNetworkAdapterSubnet(long netIntPtr);
    private native long OhNetCurrentSubnetAdapter();
    private native void OhNetSubnetListDestroy(long netIntListPtr);
    private native void OhNetLibraryStartCp(int ipv4Addr);
    private native void OhNetLibraryClose();

    static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
    
    public Library() {}
    
    /**
     * Initialise UPnP library.
     * Must be called before any other library function.
     * 
     * @return zero upon success, non-zero otherwise.
     */
    public void initialise(InitParams p) {
    	OhNetLibraryInitialise(p.getHandle());
    }
    
    public static Library Create(InitParams aParams)
    {
        Library instance = new Library();
        instance.initialise(aParams);
        
        return instance;
    }
    
    /**
     * Lightweight alternative to {@code initialise()}.
     * Intended for unit tests which are useful to platform porting only.
     * 
     * No class APIs other than {@code close()} can be called if this is used.
     * @param aInitParams	Initialisation options. Ownership of these passes to the library.
     */
//    public void InitialiseMinimal(IntPtr aInitParams)
//    {
//        if (0 != OhNetLibraryInitialiseMinimal(aInitParams))
//        {
//            throw new LibraryException();
//        }
//    }
    
    /**
     * Create a list of subnets. Currently stores an internal pointer to the list.
     * 
     * @param ptr Handle to a subnet list object.
     */
    public NetworkAdapterList subnetListCreate() {
        return new NetworkAdapterList(OhNetSubnetListCreate());
    }
    
    /**
     * Get the subnet at the given position within the internally stored subnet
     * list gained by calling createSubnetList.
     * 
     * @param ptr Handle to subnet list.
     * @param i Index of subnet to access.
     * @return Handle to network adapter.
     */
    public NetworkAdapter getSubnet(int ptr, int i) {
        return new NetworkAdapter(OhNetSubnetAt(ptr, i));
    }
    
    /**
     * Get the network interface address address of the given adapter.
     * 
     * @param ptr Handle to a network adapter.
     * @return Internet address of the given subnet.
     */
//    public int getNetworkAdapterAddress(int ptr) {
//        int intAddr = OhNetNetworkAdapterAddress(ptr);
////        byte[] addr = new byte[4];
////        
////        for (int i = 3; i >= 0; i--) {
////            addr[i] = (byte) (intAddr >> i*8);
////        }
////        
////        try {
////            return InetAddress.getByAddress(addr);
////        } catch (UnknownHostException uhe) {
////            return null;
////        }
//        
//        return intAddr;
//    }
    
//    /**
//     * Get the subnet address of the given network adapter.
//     * 
//     * @param ptr	Handle to a network adapter.
//     * @return		Subnet address of the given subnet.
//     */
//    public int getNetworkAdapterSubnet(int ptr) {
//        int intAddr = OhNetNetworkAdapterSubnet(ptr);
////        byte[] addr = new byte[4];
////        
////        for (int i = 3; i >= 0; i--) {
////            addr[i] = (byte) (intAddr >> i*8);
////        }
////        
////        try {
////            return InetAddress.getByAddress(addr);
////        } catch (UnknownHostException uhe) {
////            return null;
////        }
//        
//        return intAddr;
//    }
    
    /**
     * Destroy a subnet list.
     * 
     * @param ptr Handle to subnet list.
     */
    public void subnetListDestroy(long ptr) {
        OhNetSubnetListDestroy(ptr);
    }
    
    /**
     * Start the stack for the control point at a given address.
     * 
     * @param ipv4 The address at which to start a control point.
     */
    public void startCp(Inet4Address ipv4) {
        byte[] ipv4Bytes = ipv4.getAddress();
        int ipv4Addr = ipv4Bytes[0];
        
        for (int i = 1; i < 4; i++) {
            ipv4Addr +=  ipv4Bytes[i] << i*8;
        }
        
        OhNetLibraryStartCp(ipv4Addr);
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
    
    public static void main(String[] args) {
        Library lib = new Library();
        InitParams params = new InitParams();
        lib.initialise(params);
        
        System.out.println("Params TCP timeout:\t\t\t" + params.getTcpConnectTimeoutMs() + " ms");
        System.out.println("Params search time:\t\t\t" + params.getMsearchTimeSecs() + " secs");
        
        NetworkAdapterList netList = lib.subnetListCreate();
        //NetworkAdapter netAdptr = on.getSubnet((int) netList.listPtr, 0);
        NetworkAdapter netAdptr = netList.subnetAt(0);
        
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
        lib.subnetListDestroy((int) netList.iHandle);
        lib.close();
    }
}
