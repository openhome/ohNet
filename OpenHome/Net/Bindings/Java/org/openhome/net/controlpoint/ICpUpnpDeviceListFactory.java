package org.openhome.net.controlpoint;


/**
 * Factory interface for creating any sort of Upnp device list.
 */
public interface ICpUpnpDeviceListFactory
{
	/**
	 * Create a device list that detects all UPnP devices.
	 * 
	 * @param aAdded	delegate which will be run when a new device is detected.
	 * 					Clients who are interested this new device should call
	 *					{@code CpDevice.addRef()} on it and add it to some local collection.
	 * 					This callback will never be run for a device that is already in the list.
	 * @param aRemoved	delegate which will be run when a device is removed from the network.
	 * 					Clients who had previously stored a reference to the device
	 * 					in their {@code aAdded} callback should call
	 * 					{@code CpDevice.removeRef()} and remove the device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call {@code CpDevice.removeRef()}.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListAll(ICpDeviceListListener aAdded, ICpDeviceListListener aRemoved);
	
	/**
	 * Create a device list that detects all UPnP root devices.
	 * 
	 * @param aAdded	delegate which will be run when a new device is detected.
	 * 					Clients who are interested this new device should call
	 *					{@code CpDevice.addRef()} on it and add it to some local collection.
	 * 					This callback will never be run for a device that is already in the list.
	 * @param aRemoved	delegate which will be run when a device is removed from the network.
	 * 					Clients who had previously stored a reference to the device
	 * 					in their {@code aAdded} callback should call
	 * 					{@code CpDevice.removeRef()} and remove the device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call {@code CpDevice.removeRef()}.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListRoot(ICpDeviceListListener aAdded, ICpDeviceListListener aRemoved);
	
	/**
	 * Create a device list that detects a UPnP devices with a specific Udn.
	 * 
	 * @param aUuid		unique identifier for the target device.	
	 * @param aAdded	delegate which will be run when a new device is detected.
	 * 					Clients who are interested this new device should call
	 *					{@code CpDevice.addRef()} on it and add it to some local collection.
	 * 					This callback will never be run for a device that is already in the list.
	 * @param aRemoved	delegate which will be run when a device is removed from the network.
	 * 					Clients who had previously stored a reference to the device
	 * 					in their {@code aAdded} callback should call
	 * 					{@code CpDevice.removeRef()} and remove the device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call {@code CpDevice.removeRef()}.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListUuid(String aUuid, ICpDeviceListListener aAdded, ICpDeviceListListener aRemoved);
	
	/**
	 * Create a device list that detects UPnP devices of a specific type.
	 * 
	 * @param aDomainName	vendor domain for the target device.
	 * @param aDeviceType	name of the target device.
	 * @param aVersion		version number for the target device.
	 * @param aAdded		delegate which will be run when a new device is detected.
	 * 						Clients who are interested this new device should call
	 *						{@code CpDevice.addRef()} on it and add it to some local collection.
	 * 						This callback will never be run for a device that is already in the list.
	 * @param aRemoved		delegate which will be run when a device is removed from the network.
	 * 						Clients who had previously stored a reference to the device
	 * 						in their {@code aAdded} callback should call
	 * 						{@code CpDevice.removeRef()} and remove the device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call {@code CpDevice.removeRef()}.
	 * @return				handle to an underlying native device list.
	 */
	public ICpDeviceList createListDeviceType(String aDomainName, String aDeviceType, int aVersion,
            ICpDeviceListListener aAdded, ICpDeviceListListener aRemoved);
	
	/**
	 * Create a device list that detects UPnP devices bearing a specific type of service.
	 * 
	 * @param aDomain		vendor domain for the target service (e.g. {@code upnp.org}).
	 * @param aServiceType	name of the target service.
	 * @param aVersion		version number for the target service.
	 * @param aAdded		delegate which will be run when a new device is detected.
	 * 						Clients who are interested this new device should call
	 *						{@code CpDevice.addRef()} on it and add it to some local collection.
	 * 						This callback will never be run for a device that is already in the list.
	 * @param aRemoved		delegate which will be run when a device is removed from the network.
	 * 						Clients who had previously stored a reference to the device
	 * 						in their {@code aAdded} callback should call
	 * 						{@code CpDevice.removeRef()} and remove the device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call {@code CpDevice.removeRef()}.
	 * @return				handle to an underlying native device list.
	 */
	public ICpDeviceList createListServiceType(String aDomain, String aServiceType, int aVersion,
			ICpDeviceListListener aAdded, ICpDeviceListListener aRemoved);
}
