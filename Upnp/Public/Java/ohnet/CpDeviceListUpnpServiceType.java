package ohnet;

public class CpDeviceListUpnpServiceType extends CpDeviceList
{
	
	public CpDeviceListUpnpServiceType(String domain, String serviceType,
			int version, IDeviceListListener added, IDeviceListListener removed)
	{
		
		super();
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpServiceType(domain, serviceType, version);
	}
}