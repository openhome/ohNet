package ohnet;

import openhome.net.controlpoint.CpDevice;

public interface IDeviceListListener
{
	public void deviceAdded(CpDevice dev);
	public void deviceRemoved(CpDevice dev);
}
