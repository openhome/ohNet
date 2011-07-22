package ohnet;

public class CpDeviceListUpnpUuid extends CpDeviceList
{
	
	public CpDeviceListUpnpUuid(String uuid, IDeviceListListener added,
			IDeviceListListener removed)
	{
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpUuid(uuid);
	}
}