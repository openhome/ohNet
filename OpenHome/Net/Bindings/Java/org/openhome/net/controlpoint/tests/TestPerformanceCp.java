package org.openhome.net.controlpoint.tests;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Inet4Address;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.concurrent.Semaphore;

import org.openhome.net.controlpoint.CpDevice;
import org.openhome.net.controlpoint.CpUpnpDeviceListFactory;
import org.openhome.net.controlpoint.ICpDeviceList;
import org.openhome.net.controlpoint.ICpDeviceListListener;
import org.openhome.net.controlpoint.ICpUpnpDeviceListFactory;
import org.openhome.net.controlpoint.IPropertyChangeListener;
import org.openhome.net.controlpoint.proxies.CpProxyOpenhomeOrgTestBasic1;
import org.openhome.net.core.InitParams;
import org.openhome.net.core.Library;
import org.openhome.net.core.NetworkAdapter;
import org.openhome.net.core.SubnetList;

public class TestPerformanceCp implements ICpDeviceListListener
{
	public static final int TEST_DURATION_MS = 1000;
	
	private class ThreadArgs
    {
        private CpDevice iDevice;
        private int iCount;
        private Date iStopTime;

        public ThreadArgs(CpDevice aDevice, long aDurationMs)
        {
            iDevice = aDevice;
            iStopTime = new Date((new Date()).getTime() + aDurationMs);
        }
        public CpDevice getDevice()
        {
        	return iDevice;
        }
        public int getCount()
        {
        	synchronized (this)
        	{
        		return iCount;
        	}
        }
        public boolean incrementCount()
        {
            synchronized (this)
            {
            	Date timeNow = new Date();
                if (timeNow.before(iStopTime) || timeNow.equals(iStopTime))
                {
                    iCount++;
                    return true;
                }
                return false;
            }
        }
    }
	
	private class ActionThread extends Thread
    {
		private ThreadArgs iArgs;
		private CpProxyOpenhomeOrgTestBasic1 iProxy;
		
		public ActionThread(ThreadArgs aArgs)
		{
			iArgs = aArgs;
			iProxy = new CpProxyOpenhomeOrgTestBasic1(aArgs.getDevice());
		}

		public void run()
		{
            long val;
            do
            {
            	val = iProxy.syncGetUint();
            } while (iArgs.incrementCount());
		}
    }
    private class SubscriptionThread extends Thread implements IPropertyChangeListener
    {
        ThreadArgs iArgs;
        Semaphore iSem;
        
        public SubscriptionThread(ThreadArgs aArgs)
        {
        	iArgs = aArgs;
        	iSem = new Semaphore(1);
        	iSem.acquireUninterruptibly();
        }

        public void run()
        {
	        do
	        {
	        	CpProxyOpenhomeOrgTestBasic1 proxy = new CpProxyOpenhomeOrgTestBasic1(iArgs.getDevice());
	        	proxy.setPropertyChanged(this);
	            proxy.subscribe();
	            iSem.acquireUninterruptibly();
	            proxy.dispose();
	        } while (iArgs.incrementCount());
        }

		public void notifyChange() {
			iSem.release();
		}
    }
	
	private CpDevice iDevice;
	private Semaphore iSem;
	
	private TestPerformanceCp()
	{
		System.out.println("TestPerformanceCpJava - starting");
		InitParams initParams = new InitParams();
        Library lib = Library.create(initParams);
        SubnetList subnetList = new SubnetList();
        NetworkAdapter nif = subnetList.getSubnet(0);
        Inet4Address subnet = nif.getSubnet();
        subnetList.destroy();
        ICpUpnpDeviceListFactory deviceListFactory = new CpUpnpDeviceListFactory(lib.startCp(subnet));
        iDevice = null;
        iSem = new Semaphore(1);
    	iSem.acquireUninterruptibly();
        ICpDeviceList deviceList = deviceListFactory.createListServiceType("openhome.org", "TestBasic", 1, this);
        iSem.acquireUninterruptibly();
        
        // actions
        System.out.println("");
        int[] threadCounts = { 1, 2, 4 };
        for (int threadCount : threadCounts)
        {
            List<Thread> threads = new ArrayList<Thread>();
            ThreadArgs threadArgs = new ThreadArgs(iDevice, TEST_DURATION_MS);
            for (int i = 0; i < threadCount; i++)
            {
                threads.add(new ActionThread(threadArgs));
            }
            for (int i = 0; i < threadCount; i++)
            {
                threads.get(i).start();
            }
            for (int i = 0; i < threadCount; i++)
            {
            	try
            	{
            		threads.get(i).join();
            	}
            	catch (InterruptedException ie)
            	{
            		ie.printStackTrace();
            	}
            }
            System.out.printf("Invoked %d actions in %dms using %d threads\n", threadArgs.getCount(), TEST_DURATION_MS, threadCount);
        }

        // subscriptions
        ThreadArgs args = new ThreadArgs(iDevice, TEST_DURATION_MS);
        Thread thread = new SubscriptionThread(args);
        thread.start();
        try {
        	thread.join();
        }
        catch (InterruptedException ie)
        {
        	ie.printStackTrace();
        }
        System.out.printf("\nCompleted %d subscriptions in %dms\n", args.getCount(), TEST_DURATION_MS);

        iDevice.removeRef();
        deviceList.destroy();
        System.out.println("\nTests complete.  Press 'q' to exit.");
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        try
        {
        	while(in.read() != 'q') ;
        }
        catch (IOException io)
        {
        	System.err.println("ERROR: Exiting abnormally");
        }
	}

	public void deviceAdded(CpDevice aDevice) {
		if (iDevice != null)
        {
            throw new RuntimeException("Found more than one device.  Giving up as test results will probably be invalid.");
        }
        iDevice = aDevice;
        iDevice.addRef();
        iSem.release();
	}

	public void deviceRemoved(CpDevice aDevice) {
		throw new RuntimeException("ERROR: Device removed while test is running.");
	}
	
	public static void main(String[] args)
	{
        TestPerformanceCp testPerf = new TestPerformanceCp();
	}
}
