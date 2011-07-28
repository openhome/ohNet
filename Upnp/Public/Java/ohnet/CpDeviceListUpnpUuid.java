package ohnet;

public class CpDeviceListUpnpUuid extends CpDeviceList
{
	
	public CpDeviceListUpnpUuid(String uuid, ICpDeviceListListener added,
			ICpDeviceListListener removed)
	{
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpUuid(uuid);
	}
}