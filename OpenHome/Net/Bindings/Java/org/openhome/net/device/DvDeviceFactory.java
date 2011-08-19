package org.openhome.net.device;

import org.openhome.net.core.DeviceStack;

/**
 * The default factory for DvDevices. Creates devices normally.
 */
public class DvDeviceFactory implements IDvDeviceFactory
{
	
	private DeviceStack iDeviceStack;
	
	/**
	 * Create a new device factory. Requires a running device stack.
	 * 
	 * @param aDeviceStack	a running device stack.
	 */
	public DvDeviceFactory(DeviceStack aDeviceStack)
	{
		iDeviceStack = aDeviceStack;
		if (iDeviceStack == null)
		{
			throw new NullPointerException("aDeviceStack");
		}
	}

	/**
	 * Creates a device without support for any protocol but capable of adding
	 * services or attributes. This should only be used with <tt>CpDeviceDv</tt>.
	 * 
	 * @param aUdn	universally unique identifier.
	 * @return		a <tt>DvDevice</tt>.
	 */
	public DvDevice createDevice(String aUdn)
	{
		return new DvDevice(aUdn);
	}

	/**
	 * Creates a device capable of operating on any of the protocols the device
	 * stack supports as standard but with no services or attributes as yet.
	 * 
	 * @param aUdn	universally unique identifier.
	 * @return		a <tt>DvDevice</tt>.
	 */
	public DvDevice createDeviceStandard(String aUdn)
	{
		return new DvDeviceStandard(aUdn);
	}

	/**
	 * Creates a device capable of serving UI files and of operating on any of
	 * the protocols the device stack supports as standard but with no services
	 * or attributes as yet.
	 * 
	 * @param aUdn				universally unique identifier.
	 * @param aResourceManager	allows the owner of a device to serve UI files.
	 * @return					a <tt>DvDevice</tt>.
	 */
	public DvDevice createDeviceStandard(String aUdn,
			IResourceManager aResourceManager)
	{
		return new DvDeviceStandard(aUdn, aResourceManager);
	}

}
