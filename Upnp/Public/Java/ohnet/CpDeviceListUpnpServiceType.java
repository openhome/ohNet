package ohnet;

public class CpDeviceListUpnpServiceType extends CpDeviceList
{
	
	public CpDeviceListUpnpServiceType(String domain, String serviceType,
			int version, ICpDeviceListListener added, ICpDeviceListListener removed)
	{
		
		super();
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpServiceType(domain, serviceType, version);
	}
}