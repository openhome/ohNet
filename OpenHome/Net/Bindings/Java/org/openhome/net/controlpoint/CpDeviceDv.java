package org.openhome.net.controlpoint;

import org.openhome.net.device.DvDevice;


/**
 * Control point device which communicates directly with a device stack's device.
 */
public class CpDeviceDv extends CpDevice {
	
	private static native long CpDeviceDvCreate(long aDevice);
	
	/**
	 * Create a control point device which communicates directly with the given
	 * device stack's device.
	 * 
	 * @param aDevice	a device stack's device.
	 */
	public CpDeviceDv(DvDevice aDevice)
	{
		super(CpDeviceDvCreate(aDevice.getHandle()));
	}

}
