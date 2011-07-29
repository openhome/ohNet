package ohnet;

import org.openhome.net.controlpoint.CpDevice;

public interface ICpDeviceListListener
{
	public void deviceAdded(CpDevice dev);
	public void deviceRemoved(CpDevice dev);
}
