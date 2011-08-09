package org.openhome.net.controlpoint;


import org.openhome.net.core.ControlPointStack;

/**
 * Default implementation of device list factory interface.
 */
public class CpUpnpDeviceListFactory implements ICpUpnpDeviceListFactory
{
	
	private ControlPointStack iControlPointStack;
	
	public CpUpnpDeviceListFactory(ControlPointStack aControlPointStack)
	{
		iControlPointStack = aControlPointStack;
		if (iControlPointStack == null)
		{
			throw new IllegalArgumentException("aControlPointStack");
		}
	}

	/**
	 * Create a device list that detects all UPnP devices.
	 * 
	 * @param aAdded	delegate which will be run when a new device is detected.
	 * 					Clients who are interested this new device should call
	 *					<tt>CpDevice.addRef()</tt> on it and add it to some local collection.
	 * 					This callback will never be run for a device that is already in the list.
	 * @param aRemoved	delegate which will be run when a device is removed from the network.
	 * 					Clients who had previously stored a reference to the device
	 * 					in their <tt>aAdded</tt> callback should call
	 * 					<tt>CpDevice.removeRef()</tt> and remove the device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call <tt>CpDevice.removeRef()</tt>.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListAll(ICpDeviceListListener aAdded,
			ICpDeviceListListener aRemoved)
	{
		return new CpDeviceListUpnpAll(aAdded, aRemoved);
	}

	/**
	 * Create a device list that detects all UPnP root devices.
	 * 
	 * @param aAdded	delegate which will be run when a new device is detected.
	 * 					Clients who are interested this new device should call
	 *					<tt>CpDevice.addRef()</tt> on it and add it to some local collection.
	 * 					This callback will never be run for a device that is already in the list.
	 * @param aRemoved	delegate which will be run when a device is removed from the network.
	 * 					Clients who had previously stored a reference to the device
	 * 					in their <tt>aAdded</tt> callback should call
	 * 					<tt>CpDevice.removeRef()</tt> and remove the device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call <tt>CpDevice.removeRef()</tt>.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListRoot(ICpDeviceListListener aAdded,
			ICpDeviceListListener aRemoved)
	{
		return new CpDeviceListUpnpRoot(aAdded, aRemoved);
	}

	/**
	 * Create a device list that detects a UPnP devices with a specific Udn.
	 * 
	 * @param aUuid		unique identifier for the target device.	
	 * @param aAdded	delegate which will be run when a new device is detected.
	 * 					Clients who are interested this new device should call
	 *					<tt>CpDevice.addRef()</tt> on it and add it to some local collection.
	 * 					This callback will never be run for a device that is already in the list.
	 * @param aRemoved	delegate which will be run when a device is removed from the network.
	 * 					Clients who had previously stored a reference to the device
	 * 					in their <tt>aAdded</tt> callback should call
	 * 					<tt>CpDevice.removeRef()</tt> and remove the device from their local collection.
	 * 					Clients who had not previously claimed a reference to a device must
	 * 					not call <tt>CpDevice.removeRef()</tt>.
	 * @return			handle to an underlying native device list.
	 */
	public ICpDeviceList createListUuid(String aUuid, ICpDeviceListListener aAdded,
			ICpDeviceListListener aRemoved)
	{
		return new CpDeviceListUpnpUuid(aUuid, aAdded, aRemoved);
	}

	/**
	 * Create a device list that detects UPnP devices of a specific type.
	 * 
	 * @param aDomainName	vendor domain for the target device.
	 * @param aDeviceType	name of the target device.
	 * @param aVersion		version number for the target device.
	 * @param aAdded		delegate which will be run when a new device is detected.
	 * 						Clients who are interested this new device should call
	 *						<tt>CpDevice.addRef()</tt> on it and add it to some local collection.
	 * 						This callback will never be run for a device that is already in the list.
	 * @param aRemoved		delegate which will be run when a device is removed from the network.
	 * 						Clients who had previously stored a reference to the device
	 * 						in their <tt>aAdded</tt> callback should call
	 * 						<tt>CpDevice.removeRef()</tt> and remove the device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call <tt>CpDevice.removeRef()</tt>.
	 * @return				handle to an underlying native device list.
	 */
	public ICpDeviceList createListDeviceType(String aDomainName, String aDeviceType,
			int aVersion, ICpDeviceListListener aAdded,
			ICpDeviceListListener aRemoved)
	{
		return new CpDeviceListUpnpDeviceType(aDomainName, aDeviceType, aVersion,
				aAdded, aRemoved);
	}

	/**
	 * Create a device list that detects UPnP devices bearing a specific type of service.
	 * 
	 * @param aDomainName	vendor domain for the target service (e.g. <tt>upnp.org</tt>).
	 * @param aServiceType	name of the target service.
	 * @param aVersion		version number for the target service.
	 * @param aAdded		delegate which will be run when a new device is detected.
	 * 						Clients who are interested this new device should call
	 *						<tt>CpDevice.addRef()</tt> on it and add it to some local collection.
	 * 						This callback will never be run for a device that is already in the list.
	 * @param aRemoved		delegate which will be run when a device is removed from the network.
	 * 						Clients who had previously stored a reference to the device
	 * 						in their <tt>aAdded</tt> callback should call
	 * 						<tt>CpDevice.removeRef()</tt> and remove the device from their local collection.
	 * 						Clients who had not previously claimed a reference to a device must
	 * 						not call <tt>CpDevice.removeRef()</tt>.
	 * @return				handle to an underlying native device list.
	 */
	public ICpDeviceList createListServiceType(String aDomainName,
			String aServiceType, int aVersion, ICpDeviceListListener aAdded,
			ICpDeviceListListener aRemoved)
	{
		return new CpDeviceListUpnpServiceType(aDomainName, aServiceType, aVersion, aAdded, aRemoved);
	}
}
