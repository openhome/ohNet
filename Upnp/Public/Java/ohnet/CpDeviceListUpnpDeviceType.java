package ohnet;

public class CpDeviceListUpnpDeviceType extends CpDeviceList
{
	
	public CpDeviceListUpnpDeviceType(String domain, String deviceType,
		int version, ICpDeviceListListener added, ICpDeviceListListener removed)
	{
		
		super();
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpDeviceType(domain, deviceType, version);
	}
	
}