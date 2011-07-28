package ohnet;

public interface ICpUpnpDeviceListFactory
{

	public ICpDeviceList createListAll(ICpDeviceListListener added, ICpDeviceListListener removed);
	public ICpDeviceList createListRoot(ICpDeviceListListener added, ICpDeviceListListener removed);
	public ICpDeviceList createListUuid(String Uuid, ICpDeviceListListener added, ICpDeviceListListener removed);
	public ICpDeviceList createListDeviceType(String domain, String deviceType, int version,
            ICpDeviceListListener added, ICpDeviceListListener removed);
	public ICpDeviceList createListServiceType(String domain, String serviceType, int version,
			ICpDeviceListListener added, ICpDeviceListListener removed);
	
}
