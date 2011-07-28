package ohnet;

public class CpUpnpDeviceListFactory implements ICpUpnpDeviceListFactory
{
	
//	private ControlPointStack controlPointStack;
	
//	public CpUpnpDeviceListFactory(ControlPointStack controlPointStack)
//	{
//		this.controlPointStack = controlPointStack;
//		if (controlPointStack == null)
//		{
//			throw new NullArgumentException("controlPointStack");
//		}
//	}

	public ICpDeviceList createListAll(ICpDeviceListListener added,
			ICpDeviceListListener removed)
	{
		return new CpDeviceListUpnpAll(added, removed);
	}

	public ICpDeviceList createListRoot(ICpDeviceListListener added,
			ICpDeviceListListener removed)
	{
		return new CpDeviceListUpnpRoot(added, removed);
	}

	public ICpDeviceList createListUuid(String uuid, ICpDeviceListListener added,
			ICpDeviceListListener removed)
	{
		return new CpDeviceListUpnpUuid(uuid, added, removed);
	}

	public ICpDeviceList createListDeviceType(String domain, String deviceType,
			int version, ICpDeviceListListener added, ICpDeviceListListener removed)
	{
		return new CpDeviceListUpnpDeviceType(domain, deviceType, version,
				added, removed);
	}

	public ICpDeviceList createListServiceType(String domain,
			String serviceType, int version, ICpDeviceListListener added,
			ICpDeviceListListener removed)
	{
		return new CpDeviceListUpnpServiceType(domain, serviceType, version, added, removed);
	}
}
