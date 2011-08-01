package org.openhome.net.core;

import ohnet.Parameter;

import org.openhome.net.controlpoint.IPropertyChangeListener;

/**
 * Unsigned integer type property.  Only intended for use by auto-generated proxies and providers.
 */
public class PropertyUint extends Property
{
	
	private static native long ServicePropertyCreateUintCp(String aName, IPropertyChangeListener aListener);
	private static native long ServicePropertyCreateUintDv(long aParameter);
	private static native long ServicePropertyValueUint(long aProperty);
	private static native int ServicePropertySetValueUint(long aProperty, long aValue);
	
	/**
	 * Constructor suitable for use by clients of the control point stack.
	 * 
	 * @param aName		property name.
	 * @param aListener action to run when the property's value changes.
	 */
	public PropertyUint(String aName, IPropertyChangeListener aListener)
	{
		super(aListener);
		iHandle = ServicePropertyCreateUintCp(aName, aListener);
	}
	
	/**
	 * Constructor suitable for use by clients of the device stack.
	 * Assumes the managed property does not own the underlying native property.
	 * 
	 * @param aParameter	parameter defining the name and any value bounds for the property.
	 */
	public PropertyUint(Parameter aParameter)
	{
		super(false);
		iHandle = ServicePropertyCreateUintDv(aParameter.getHandle());
	}
	
	/**
	 * Constructor suitable for use by clients of the device stack.
	 * 
	 * @param aParameter			parameter defining the name and any value bounds for the property.
	 * @param aOwnsNativeProperty	whether the managed property owns the underlying native property.
	 */
	public PropertyUint(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		super(aOwnsNativeProperty);
		iHandle = ServicePropertyCreateUintDv(aParameter.getHandle());
	}
	
	/**
	 * Query the value of the property.
	 * 
	 * @return unsigned integer property value.
	 */
	public long getValue()
	{
		return ServicePropertyValueUint(iHandle);
	}
	
	/**
	 * Set the value of the property.
	 * 
	 * @param aValue	new value for the property.
	 * @return			{@code true} if the property's value was changed;
	 * 					{@code false} otherwise.
	 */
	public boolean setValue(long aValue)
	{
		int changed = ServicePropertySetValueUint(iHandle, aValue);
		
		return (changed != 0);
	}
}