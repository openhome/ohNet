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

	public ICpDeviceList createListAll(IDeviceListListener added,
			IDeviceListListener removed)
	{
		return new CpDeviceListUpnpAll(added, removed);
	}

	public ICpDeviceList createListRoot(IDeviceListListener added,
			IDeviceListListener removed)
	{
		return new CpDeviceListUpnpRoot(added, removed);
	}

	public ICpDeviceList createListUuid(String uuid, IDeviceListListener added,
			IDeviceListListener removed)
	{
		return new CpDeviceListUpnpUuid(uuid, added, removed);
	}

	public ICpDeviceList createListDeviceType(String domain, String deviceType,
			int version, IDeviceListListener added, IDeviceListListener removed)
	{
		return new CpDeviceListUpnpDeviceType(domain, deviceType, version,
				added, removed);
	}

	public ICpDeviceList createListServiceType(String domain,
			String serviceType, int version, IDeviceListListener added,
			IDeviceListListener removed)
	{
		return new CpDeviceListUpnpServiceType(domain, serviceType, version, added, removed);
	}
}
