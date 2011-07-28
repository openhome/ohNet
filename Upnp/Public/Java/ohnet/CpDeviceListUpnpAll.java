package ohnet;

public class CpDeviceListUpnpAll extends CpDeviceList
{
	
	public CpDeviceListUpnpAll(ICpDeviceListListener added, 
			ICpDeviceListListener removed) 
	{
		
		super();
		addedListeners.add(added);
		removedListeners.add(removed);
		initialiseDeviceListUpnpAll();
	}
	
}