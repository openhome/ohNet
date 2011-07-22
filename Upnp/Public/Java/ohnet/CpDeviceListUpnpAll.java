package ohnet;

public class CpDeviceListUpnpAll extends CpDeviceList
{
	
	public CpDeviceListUpnpAll(IDeviceListListener added, 
			IDeviceListListener removed) 
	{
		
		super();
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpAll();
	}
	
}