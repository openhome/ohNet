package ohnet;

public interface ICpUpnpDeviceListFactory
{

	public ICpDeviceList createListAll(IDeviceListListener added, IDeviceListListener removed);
	public ICpDeviceList createListRoot(IDeviceListListener added, IDeviceListListener removed);
	public ICpDeviceList createListUuid(String Uuid, IDeviceListListener added, IDeviceListListener removed);
	public ICpDeviceList createListDeviceType(String domain, String deviceType, int version,
            IDeviceListListener added, IDeviceListListener removed);
	public ICpDeviceList createListServiceType(String domain, String serviceType, int version,
			IDeviceListListener added, IDeviceListListener removed);
	
}
