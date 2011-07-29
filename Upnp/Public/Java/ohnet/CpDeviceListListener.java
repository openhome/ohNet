package ohnet;

import org.openhome.net.controlpoint.CpDevice;

public class CpDeviceListListener implements ICpDeviceListListener
{

	public CpDeviceListListener() {}
	
	public void deviceAdded(CpDevice dev)
	{
		System.out.println("Device added: " + dev.getUdn());
	}
	
	public void deviceRemoved(CpDevice dev)
	{
		System.out.println("Device removed: " + dev.getUdn());
	}
	
}
