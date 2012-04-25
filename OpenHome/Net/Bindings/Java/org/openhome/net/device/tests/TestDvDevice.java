package org.openhome.net.device.tests;

import java.net.Inet4Address;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

import org.openhome.net.controlpoint.CpDevice;
import org.openhome.net.controlpoint.CpDeviceListUpnpServiceType;
import org.openhome.net.controlpoint.ICpDeviceListListener;
import org.openhome.net.controlpoint.tests.TestBasicCp;
import org.openhome.net.core.InitParams;
import org.openhome.net.core.Library;
import org.openhome.net.core.NetworkAdapter;
import org.openhome.net.core.SubnetList;


public class TestDvDevice implements ICpDeviceListListener
{
	private List<CpDevice> iDeviceList;
	private DeviceBasic iDevice;
	private Semaphore iSem;
	
	public TestDvDevice()
	{
		System.out.println("TestDvDeviceJava - starting");
		iDevice = new DeviceBasic();
		iDeviceList = new ArrayList<CpDevice>();
		CpDeviceListUpnpServiceType list = new CpDeviceListUpnpServiceType("openhome.org", "TestBasic", 1, this);
		iSem = new Semaphore(1);
		iSem.acquireUninterruptibly();
		try {
			iSem.tryAcquire(30*1000, TimeUnit.MILLISECONDS);
		}
		catch (InterruptedException ie)
		{
			ie.printStackTrace();
		}
		assert(iDeviceList.size() == 1);
		System.out.println("iDeviceList size: " + iDeviceList.size());
		TestBasicCp cp = new TestBasicCp(iDeviceList.get(0));
		cp.testActions();
		cp.testSubscriptions();
		list.destroy();
		synchronized (this)
		{
			for (CpDevice d : iDeviceList)
			{
				d.removeRef();
			}
		}
		iDevice.dispose();
		
		System.out.println("TestDvDeviceJava - completed");
	}
	
	public void deviceAdded(CpDevice aDevice)
	{
		synchronized (this)
		{
			if (aDevice.getUdn().equals(iDevice.getUdn()))
			{
                aDevice.addRef();
				iDeviceList.add(aDevice);
				iSem.release();
			}
		}
		
	}

	public void deviceRemoved(CpDevice aDevice)
	{
		synchronized (this)
		{
			String udn = aDevice.getUdn();
			int i = 0;
			for (CpDevice n : iDeviceList)
			{
				if (n.getUdn() == udn)
				{
					n.removeRef();
					iDeviceList.remove(i);
				}
				i++;
			}
		}
	}
	
	public static void main(String[] args)
	{
		InitParams initParams = new InitParams();
		initParams.setMsearchTimeSecs(1);
		initParams.setUseLoopbackNetworkAdapter();
        initParams.setDvServerPort(0);
		Library lib = new Library();
		lib.initialise(initParams);
		SubnetList subnetList = new SubnetList();
		NetworkAdapter nif = subnetList.getSubnet(0);
		Inet4Address subnet = nif.getSubnet();
		subnetList.destroy();
		lib.startCombined(subnet);
		new TestDvDevice();
		lib.close();
	}
}
