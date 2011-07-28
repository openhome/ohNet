package org.openhome.net.core;

/**
 * Combined control-point and device stacks.
 */
public class CombinedStack
{
	private ControlPointStack iControlPointStack;
	private DeviceStack iDeviceStack;
	
	// Constructor is not public - obtain an instance from Library.
	protected CombinedStack()
	{
		iControlPointStack = new ControlPointStack();
		iDeviceStack = new DeviceStack();
	}
	
	/**
	 * Get the control point stack with this combined stack.
	 * 
	 * @return	the control point stack.
	 */
	public ControlPointStack getControlPointStack()
	{
		return iControlPointStack;
	}
	
	/**
	 * Get the device stack within this combined stack.
	 * 
	 * @return	the device stack.
	 */
	public DeviceStack getDeviceStack()
	{
		return iDeviceStack;
	}
}
