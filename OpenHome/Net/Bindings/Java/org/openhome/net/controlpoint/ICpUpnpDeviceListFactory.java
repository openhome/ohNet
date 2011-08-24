package org.openhome.net.controlpoint;


/**
 * Factory interface for creating any sort of Upnp device list.
 */
public interface ICpUpnpDeviceListFactory
{
	/**
	 * Create a device list that detects all UPnP devices.
	 * 
	 * @param aListener	delegate which will be called when a device is detected or removed.
	 * 					Clients who are interested in a newly detected device should call
	 *					<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *					and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *					device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call <tt>CpDevice.removeRef()</tt>.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListAll(ICpDeviceListListener aListener);
	
	/**
	 * Create a device list that detects all UPnP root devices.
	 * 
	 * @param aListener	delegate which will be called when a device is detected or removed.
	 * 					Clients who are interested in a newly detected device should call
	 *					<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *					and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *					device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call <tt>CpDevice.removeRef()</tt>.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListRoot(ICpDeviceListListener aListener);
	
	/**
	 * Create a device list that detects a UPnP devices with a specific Udn.
	 * 
	 * @param aUuid		unique identifier for the target device.	
	 * @param aListener	delegate which will be called when a device is detected or removed.
	 * 					Clients who are interested in a newly detected device should call
	 *					<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *					and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *					device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call <tt>CpDevice.removeRef()</tt>.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListUuid(String aUuid, ICpDeviceListListener aListener);
	
	/**
	 * Create a device list that detects UPnP devices of a specific type.
	 * 
	 * @param aDomainName	vendor domain for the target device.
	 * @param aDeviceType	name of the target device.
	 * @param aVersion		version number for the target device.
	 * @param aListener		delegate which will be called when a device is detected or removed.
	 * 						Clients who are interested in a newly detected device should call
	 *						<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *						and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *						device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call <tt>CpDevice.removeRef()</tt>.
	 * @return				handle to an underlying native device list.
	 */
	public ICpDeviceList createListDeviceType(String aDomainName, String aDeviceType, int aVersion,
			ICpDeviceListListener aListener);
	
	/**
	 * Create a device list that detects UPnP devices bearing a specific type of service.
	 * 
	 * @param aDomain		vendor domain for the target service (e.g. <tt>upnp.org</tt>).
	 * @param aServiceType	name of the target service.
	 * @param aVersion		version number for the target service.
	 * @param aListener		delegate which will be called when a device is detected or removed.
	 * 						Clients who are interested in a newly detected device should call
	 *						<tt>CpDevice.addRef()</tt> on it and add it to some local collection
	 *						and must later call <tt>CpDevice.removeRef()</tt> to remove the
	 *						device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call <tt>CpDevice.removeRef()</tt>.
	 * @return				handle to an underlying native device list.
	 */
	public ICpDeviceList createListServiceType(String aDomain, String aServiceType, int aVersion,
			ICpDeviceListListener aListener);
}
