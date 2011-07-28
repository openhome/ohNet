package ohnet;

public class CpDeviceListUpnpRoot extends CpDeviceList
{

	public CpDeviceListUpnpRoot(ICpDeviceListListener added,
			ICpDeviceListListener removed)
	{

		super();
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpRoot();
	}

}