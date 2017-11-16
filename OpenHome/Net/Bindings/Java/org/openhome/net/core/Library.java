package org.openhome.net.core;

import java.net.Inet4Address;



public class Library
{
    private static native long OhNetLibraryInitialise(long aInitParams); 
    private static native long OhNetLibraryInitialiseMinimal(long aInitParams);
    private static native int OhNetLibraryStartCp(int aSubnet);
    private static native int OhNetLibraryStartDv();
    private static native int OhNetLibraryStartCombined(int aSubnet);
    private static native void OhNetLibraryClose();
    private static native void OhNetSetCurrentSubnet(long aSubnet);
    private static native long OhNetCurrentSubnetAdapter();
    private static native void OhNetRefreshNetworkAdapterList();
    private static native void OhNetLibraryNotifySuspended();
    private static native void OhNetLibraryNotifyResumed();
    private static native void OhNetDebugSetLevel(long aLevel);
    private static native void OhNetDebugSetSeverity(int aSeverity);
    private static native void OhNetAbortProcess();

    static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }

    private InitParams iInitParams;
    
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
    	if (0 != OhNetLibraryInitialise(aInitParams.getHandle()))
        {
            throw new LibraryException();
        }
        iInitParams = aInitParams;
    }
    
    /**
     * Create a library.
     * @param aInitParams	initialisation options.  Ownership of these passes to
     * 						the library
     * @return				the instantiated library.
     */
    public static Library create(InitParams aInitParams)
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
        int err = OhNetLibraryStartCp(ipv4Addr);
        checkStartupError(err);
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
        int err = OhNetLibraryStartCombined(ipv4Addr);
        checkStartupError(err);
        return new CombinedStack();
    }
    
    /**
     * Start the library as a UPnP device stack.
     * 
     * @return a device stack. Can be used to create device factories.
     */
    public DeviceStack startDv()
    {
    	int err = OhNetLibraryStartDv();
    	checkStartupError(err);
    	return new DeviceStack();
    }
    
    private void checkStartupError(int aError)
    {
        switch (aError)
        {
            case 0:
            default:
                break;
            case 1:
                throw new ErrorNoMemory();
            case 2:
                throw new ErrorGeneral();
            case 3:
                throw new ErrorNetworkAddressInUse();
        }
    }
    
    /**
     * Close the ohNet library. Must be called sometime after calling startCp()
     * to allow stack to be shutdown.
     */
    public void close() {
        OhNetLibraryClose();
        if (iInitParams != null) {
            iInitParams.disposeCallbacks();
        }
    }
    
    /**
     * Set which subnet the library should use.
     * 
     * <p>Device lists and subscriptions will be automatically updated.
     * No other subnet will be selected if aSubnet is not available.
     * 
     * @param aSubnet	handle returned by <tt>NetworkAdapterList.subnetAt()</tt>.
     */
    public void setCurrentSubnet(NetworkAdapter aSubnet)
    {
    	OhNetSetCurrentSubnet(aSubnet.getHandle());
    }
    
    /**
     * Query which network adapter is currently selected.
     *
     * <p>The {@link NetworkAdapter#removeRef()} method must be called on the returned
     * {@link NetworkAdapter} object when the {@link NetworkAdapter} object is no longer required.
     * 
     * @return the currently selected adapter.
     */
    public NetworkAdapter getCurrentSubnet()
    {
    	return new NetworkAdapter(OhNetCurrentSubnetAdapter(), true);
    }

    /**
     * Force a refresh of the library's list of available network adapters
     *
     * This should only be required on platforms that are not capable of
     * automatically detecting adapter changes.
     */
    public void refreshNetworkAdapterList()
    {
        OhNetRefreshNetworkAdapterList();
    }

    /**
     * Inform the library that the application has been suspended.
     *
     * This is necessary if the application may be paused while other processes on
     * a device continued to be executed (e.g. when an app moves to background on iOS).
     * It is typically not necessary to call this when the host device hibernates.
     */
     public void notifySuspended()
     {
         OhNetLibraryNotifySuspended();
     }

    /**
     * Inform the library that the application has been resumed.
     *
     * This is necessary if the application may have been paused while other processes on
     * a device continued to be executed (e.g. when an app moves to background on iOS).
     * It is typically not necessary to call this when the host device resumes from hibernation.
     */
     public void notifyResumed()
     {
         OhNetLibraryNotifyResumed();
     }

    /**
+     * Set debug logging level.
     * 
     * <p>Log messages can optionally be passed to a callback registered by {@link InitParams#setLogOutput}.
     * 
     * @param aLevel    bit(s) specifying debug level.  The debug level can be any
     *                  combination of bit-mask values returned by {@link DebugLevel#longValue}.
     *                  See {@link DebugLevel} for details.
     */
    public void setDebugLevel(long aLevel)
    {
        OhNetDebugSetLevel(aLevel);
    }

    /**
     * Set debug logging severity.
     * 
     * <p>Log messages can optionally be passed to a callback registered by {@link InitParams#setLogOutput}.
     * 
     * @param aLevel    enum constant specifying debug severity.  The debug severity can be any
     *                  of the values defined by the {@link DebugSeverity} enum.
     */
    public void setDebugSeverity(DebugSeverity aSeverity)
    {
        OhNetDebugSetSeverity(aSeverity.intValue());
    }

    /**
     * Terminate the ohNet process after a fatal error. On some platforms, this call
     * may invoke a debugger or produce a crash dump.
     */
    public void abortProcess()
    {
        OhNetAbortProcess();
    }
    
    /**
     * Convert an <tt>Inet4Address</tt> into an integer representation in
     * network byte order.
     * 
     * @param aAddress	the IPv4 address object to convert.
     * @return			the integer representation in network byte order.
     */
    private int getIpv4Int(Inet4Address aAddress)
    {
        byte[] ipv4Bytes = aAddress.getAddress();
        int ipv4Addr = (ipv4Bytes[0] & 0xff) << 24;
        ipv4Addr |= (ipv4Bytes[1] & 0xff) << 16;
        ipv4Addr |= (ipv4Bytes[2] & 0xff) << 8;
        ipv4Addr |= ipv4Bytes[3] & 0xff;
        return ipv4Addr;
    }
}
