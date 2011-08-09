package org.openhome.net.core;

import org.openhome.net.controlpoint.IPropertyChangeListener;

/**
 * Boolean type property.  Only intended for use by auto-generated proxies and providers.
 */
public class PropertyBool extends Property
{
	private native PropertyInitialised ServicePropertyCreateBoolCp(String aName, IPropertyChangeListener aListener);
	private static native long ServicePropertyCreateBoolDv(long aParameter);
	private static native int ServicePropertyValueBool(long aProperty);
	private static native int ServicePropertySetValueBool(long aProperty, int aValue);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }


	/**
	 * Constructor suitable for use by clients of the control point stack.
	 * 
	 * @param aName		property name.
	 * @param aListener	action to run when the property's value changes.
	 */
	public PropertyBool(String aName, IPropertyChangeListener aListener)
	{
		super(aListener);
		PropertyInitialised init = ServicePropertyCreateBoolCp(aName, aListener);
		iHandle = init.getHandle();
		iCallback = init.getCallback();
	}
	
	/**
	 * Constructor suitable for use by clients of the device stack.
	 * Assumes the managed property does not own the underlying native property.
	 * 
	 * @param aParameter	parameter defining the name for the property.
	 */
	public PropertyBool(Parameter aParameter)
	{
		super(false);
		iHandle = ServicePropertyCreateBoolDv(aParameter.getHandle());
	}
	
	/**
	 * Constructor suitable for use by clients of the device stack.
	 * 
	 * @param aParameter			parameter defining the name for the property.
	 * @param aOwnsNativeProperty	whether the managed property owns the underlying native property.
	 */
	public PropertyBool(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		super(aOwnsNativeProperty);
		iHandle = ServicePropertyCreateBoolDv(aParameter.getHandle());
	}
	
	/**
	 * Query the value of the property.
	 * 
	 * @return boolean property value.
	 */
	public boolean getValue()
	{
		int result = ServicePropertyValueBool(iHandle);
		
		return (result != 0);
	}
	
	/**
	 * Set the value of the property.
	 * 
	 * @param aValue	new value for the property.
	 * @return			<tt>true</tt> if the property's value was changed;
	 * 					<tt>false</tt> otherwise.
	 */
	public boolean setValue(boolean aValue)
	{
		int value = (aValue ? 1 : 0);
		int changed = ServicePropertySetValueBool(iHandle, value);
		
		return (changed != 0);
	}
}