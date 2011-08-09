package org.openhome.net.device;

public interface IDvDeviceFactory
{
	/**
	 * Creates a device without support for any protocol but capable of adding
	 * services or attributes. This should only be used with <tt>CpDeviceDv</tt>.
	 * 
	 * @param aUdn	universally unique identifier.
	 * @return		a <tt>DvDevice</tt>.
	 */
	public DvDevice createDevice(String aUdn);

	/**
	 * Creates a device capable of operating on any of the protocols the device
	 * stack supports as standard but with no services or attributes as yet.
	 * 
	 * @param aUdn	universally unique identifier.
	 * @return		a <tt>DvDevice</tt>.
	 */
	public DvDevice createDeviceStandard(String aUdn);

	/**
	 * Creates a device capable of serving UI files and of operating on any of
	 * the protocols the device stack supports as standard but with no services
	 * or attributes as yet.
	 * 
	 * @param aUdn				universally unique identifier.
	 * @param aResourceManager	allows the owner of a device to serve UI files.
	 * @return					a <tt>DvDevice</tt>.
	 */
	public DvDevice createDeviceStandard(String aUdn, IResourceManager aResourceManager);
}