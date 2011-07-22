package ohnet;

public class CpDeviceListUpnpRoot extends CpDeviceList
{

	public CpDeviceListUpnpRoot(IDeviceListListener added,
			IDeviceListListener removed)
	{

		super();
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpRoot();
	}

}