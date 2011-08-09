package org.openhome.net.core;

import org.openhome.net.controlpoint.IPropertyChangeListener;

/**
 * Integer type property.  Only intended for use by auto-generated proxies and providers.
 */
public class PropertyInt extends Property
{
	private native PropertyInitialised ServicePropertyCreateIntCp(String aName, IPropertyChangeListener aListener);
	private static native long ServicePropertyCreateIntDv(long aParameter);
	private static native int ServicePropertyValueInt(long aProperty);
	private static native int ServicePropertySetValueInt(long aProperty, int aValue);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }

	
	/**
	 * Constructor suitable for use by clients of the control point stack.
	 * 
	 * @param aName		property name.
	 * @param aListener listener to call when the property's value changes.
	 */
	public PropertyInt(String aName, IPropertyChangeListener aListener)
	{
		super(aListener);
		PropertyInitialised init = ServicePropertyCreateIntCp(aName, aListener);
		iHandle = init.getHandle();
		iCallback = init.getCallback();
	}
	
	/**
	 * Constructor suitable for use by clients of the device stack.
	 * Assumes the managed property does not own the underlying native property.
	 * 
	 * @param aParameter	parameter defining the name and any value bounds for the property.
	 */
	public PropertyInt(Parameter aParameter)
	{
		super(false);
		iHandle = ServicePropertyCreateIntDv(aParameter.getHandle());
	}
	
	/**
	 * Constructor suitable for use by clients of the device stack.
	 * 
	 * @param aParameter			parameter defining the name and any value bounds for the property.
	 * @param aOwnsNativeProperty	whether the managed property owns the underlying native property.
	 */
	public PropertyInt(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		super(aOwnsNativeProperty);
		iHandle = ServicePropertyCreateIntDv(aParameter.getHandle());
	}
	
	/**
	 * Query the value of the property.
	 * 
	 * @return	integer property value.
	 */
	public int getValue()
	{
		return ServicePropertyValueInt(iHandle);
	}
	
	/**
	 * Set the value of the property.
	 * 
	 * @param aValue	new value for the property.
	 * @return			<tt>true</tt> if the property's value was changed;
	 * 					<tt>false</tt> otherwise.
	 */
	public boolean setValue(int aValue)
	{
		int changed = ServicePropertySetValueInt(iHandle, aValue);
		
		return (changed != 0);
	}
}
