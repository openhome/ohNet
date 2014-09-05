package org.openhome.net.controlpoint.tests;

import java.net.Inet4Address;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

import org.openhome.net.controlpoint.CpAttribute;
import org.openhome.net.controlpoint.CpDevice;
import org.openhome.net.controlpoint.CpDeviceListUpnpServiceType;
import org.openhome.net.controlpoint.ICpDeviceListListener;
import org.openhome.net.controlpoint.ICpProxyListener;
import org.openhome.net.controlpoint.IPropertyChangeListener;
import org.openhome.net.controlpoint.ProxyError;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgConnectionManager1;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgConnectionManager1.GetProtocolInfo;
import org.openhome.net.core.InitParams;
import org.openhome.net.core.Library;
import org.openhome.net.core.NetworkAdapter;
import org.openhome.net.core.SubnetList;



public class TestProxy implements ICpDeviceListListener, ICpProxyListener, IPropertyChangeListener
{
	
	private class PollInvocationTask extends TimerTask
	{
		public void run()
		{
			iActionPollStop.release();
		}
	}

	private List<CpDevice> iDeviceList;
	private int iActionCount;
    private int iSubscriptionCount;
    private CpProxyUpnpOrgConnectionManager1 iConnMgr;
    private String iExpectedSink;
    private Date iActionPollStopTime;
	private Semaphore iActionPollStop;
	private Semaphore iSubscriptionSem;
	private final int kDevicePollMs = 1000;
	private boolean iListFrozen;
	
	
	public TestProxy(int aMsearchTimeSecs)
	{
		iDeviceList = new LinkedList<CpDevice>();
		
		CpDeviceListUpnpServiceType list = new CpDeviceListUpnpServiceType("upnp.org", "ConnectionManager", 1, this);
        
		Semaphore sem = new Semaphore(1);
    	sem.acquireUninterruptibly();
        try {
        	sem.tryAcquire(aMsearchTimeSecs * 1000, TimeUnit.MILLISECONDS);
        } catch (InterruptedException ie) {
            ie.printStackTrace();
        }
        
        iListFrozen = true;

        invokeSync();
        
        // Note that following tests handle the device list changing (i.e. devices being switched on/off) badly.
        System.out.print("\n\n");
        int count = iDeviceList.size();
        Date startTime = new Date();
        pollInvoke();
        Date endTime = new Date();
        int avgActions = 0;
        if (count > 0)
        {
            avgActions = (int)(iActionCount / count);
        }
        double secs = (endTime.getTime() - startTime.getTime())/1000.0;
        System.out.print("\n" + iActionCount + " actions invoked on " + count + " devices (avg " + avgActions + ") in " + secs + " seconds\n\n");
        
        System.out.print("\n\n");
        startTime = new Date();
        pollSubscribe();
        endTime = new Date();
        int avgSubscriptions = 0;
        if (count > 0)
        {
            avgSubscriptions = (int)(iSubscriptionCount / count);
        }
        secs = (endTime.getTime() - startTime.getTime())/1000.0;
        System.out.println("\n" + iSubscriptionCount + " subscriptions on " + count + " devices (avg " + avgSubscriptions + ") in " + secs + " seconds\n");
        
        list.destroy();
        synchronized (this)
        {
        	for (CpDevice c : iDeviceList)
        	{
        		c.removeRef();
        	}
        }
        System.out.println("Tests completed");
        
	}
	
	private void invokeSync()
	{
		// trivial validation of the sync wrappers to all APIs
        // single sync call to whichever device happens to be first in our list
        if (iDeviceList.size() == 0)
        {
            System.out.println("No devices found, so nothing to test");
            return;
        }
        CpDevice device = iDeviceList.get(0);
        System.out.println("\n\nSync call to device " + device.getUdn());
        
        CpProxyUpnpOrgConnectionManager1 connMgr = new CpProxyUpnpOrgConnectionManager1(device);
        try {
            GetProtocolInfo points = connMgr.syncGetProtocolInfo();
            System.out.println("source is " + points.getSource() + "\nsink is " + points.getSink());
        } catch (ProxyError pe) { }
        connMgr.dispose();
	}
	
	private void pollInvoke()
    {
        iActionPollStop = new Semaphore(1);
        iActionPollStop.acquireUninterruptibly();
        Timer timer = new Timer();
        for (int i = 0; i < iDeviceList.size(); i++)
        {
            CpDevice device = iDeviceList.get(i);
            int countBefore = iActionCount;
            System.out.print("Device " + device.getUdn());
            iConnMgr = new CpProxyUpnpOrgConnectionManager1(device);
            iActionPollStopTime = new Date((new Date()).getTime() + kDevicePollMs);
            timer.schedule(new PollInvocationTask(), kDevicePollMs);
            for (int j = 0; j < 4; j ++)
            {
                iConnMgr.beginGetProtocolInfo(this);
            }
            iActionPollStop.acquireUninterruptibly();
            System.out.println("    " + (iActionCount - countBefore));
            iConnMgr.dispose();
            synchronized (this)
            {
                iExpectedSink = null;
            }
        }
        timer.cancel();
    }
	
	private void pollSubscribe()
    {
        iSubscriptionSem = new Semaphore(1);
        iSubscriptionSem.acquireUninterruptibly();
        for (int i = 0; i < iDeviceList.size(); i++)
        {
            CpDevice device = iDeviceList.get(i);
            String udn = device.getUdn();
            if (udn.equals("896659847466-a4badbeaacbc-737837") ||
                udn.equals("541d0cb5-3b34-4264-8ff0-d8653acf6425"))
                continue;
            int countBefore = iSubscriptionCount;
            System.out.print("Device " + device.getUdn());
            CpProxyUpnpOrgConnectionManager1 connMgr = new CpProxyUpnpOrgConnectionManager1(device);
            long version = connMgr.version();
            if (version < 1 || version > 4)
                System.out.println("\tWARNING: implausible version for service - " + version);
            connMgr.setPropertyChanged(this);
            Date startTime = new Date();
            while(true)
            {
                connMgr.subscribe();
                try {
                	iSubscriptionSem.tryAcquire((int)(2 * kDevicePollMs), TimeUnit.MILLISECONDS);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
                connMgr.unsubscribe();
                Date now = new Date();
                if ((now.getTime() - startTime.getTime()) > kDevicePollMs)
                {
                    break;
                }
                iSubscriptionCount++;
            }
            System.out.println("    " + (iSubscriptionCount - countBefore));
            connMgr.dispose();
        }
    }

	public void callbackAsyncComplete(long aAsyncHandle) {
		synchronized (this)
        {
			Date timeNow = new Date();
            if (timeNow.equals(iActionPollStopTime)
            		|| timeNow.after(iActionPollStopTime))
            {
                return;
            }
            
            iConnMgr.beginGetProtocolInfo(this);
            
            try
            {
                String source;
                String sink;
                GetProtocolInfo points = iConnMgr.endGetProtocolInfo(aAsyncHandle);
                source = points.getSource();
                sink = points.getSink();
                iActionCount++;
                if (sink == null && iExpectedSink != null)
                {
                    System.out.println("Expected " + iExpectedSink + "\n...got (null)");
                }
                else
                {
                    if (iExpectedSink == null)
                    {
                        iExpectedSink = sink;
                    }
                    else if (!sink.equals(iExpectedSink))
                    {
                        System.out.println("Expected " + iExpectedSink + "\n...got " + sink);
                    }
                }
            }
            catch (ProxyError pe) { }
        }
	}

	public void callbackActionComplete(long aPtr, long aAsyncHandle) {}
	public void callback(long aPtr) {}

	public void notifyChange() {
		iSubscriptionSem.release();
	}

	public void deviceAdded(CpDevice aDevice)
	{
		synchronized (this)
		{
			if (!iListFrozen)
			{
				printDeviceInfo("Added", aDevice);
                aDevice.addRef();
				iDeviceList.add(aDevice);
			}
		}
		
	}

	public void deviceRemoved(CpDevice aDevice)
	{
        synchronized (this)
        {
            if (!iListFrozen)
            {
                printDeviceInfo("Removed", aDevice);
                String udn = aDevice.getUdn();
                int i = 0;
                for (CpDevice n : iDeviceList)
                {
                    if (n.getUdn() == udn)
                    {
                        n.removeRef();
                        iDeviceList.remove(i);
                        break;
                    }
                    i++;
                }
            }
        }
	}
	
	private static void printDeviceInfo(String aPrologue, CpDevice aDevice)
	{
        CpAttribute location = aDevice.getAttribute("Upnp.Location");
        CpAttribute friendlyName = aDevice.getAttribute("Upnp.FriendlyName");
        System.out.println(aPrologue +
                      "\n    udn = " + aDevice.getUdn() + 
                      "\n    location = " + location.getValue() +
                      "\n    name = " + friendlyName.getValue());
	}
	
	public static void main(String[] args)
	{
		InitParams initParams = new InitParams();
		Library lib = new Library();
		lib.initialise(initParams);
		SubnetList subnetList = new SubnetList();
		NetworkAdapter nif = subnetList.getSubnet(0);
		Inet4Address subnet = nif.getSubnet();
		subnetList.destroy();
		lib.startCp(subnet);
		new TestProxy(initParams.getMsearchTimeSecs());
		lib.close();
	}
	
}
