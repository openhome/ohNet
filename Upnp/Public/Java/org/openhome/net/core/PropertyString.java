package org.openhome.net.core;


import org.openhome.net.controlpoint.IPropertyChangeListener;

/**
 * String type property.  Only intended for use by auto-generated proxies and providers.
 */
public class PropertyString extends Property
{
	private static native long ServicePropertyCreateStringCp(String aName, IPropertyChangeListener aListener);
	private static native long ServicePropertyCreateStringDv(long aParameter);
	private static native String ServicePropertyValueString(long aProperty);
	private static native int ServicePropertySetValueString(long aProperty, String aValue);
	
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
	public PropertyString(String aName, IPropertyChangeListener aListener)
	{
		super(aListener);
		iHandle = ServicePropertyCreateStringCp(aName, aListener);
	}
	
	/**
	 * Constructor suitable for use by clients of the device stack.
	 * Assumes the managed property does not own the underlying native property.
	 * 
	 * @param aParameter	parameter defining the name and any set of allowed values for the property.
	 */
	public PropertyString(Parameter aParameter)
	{
		super(false);
		iHandle = ServicePropertyCreateStringDv(aParameter.getHandle());
	}
	
	/**
	 * Constructor suitable for use by clients of the device stack.
	 * 
	 * @param aParameter			parameter defining the name and any set of allowed values for the property.
	 * @param aOwnsNativeProperty	whether the managed property owns the underlying native property.
	 */
	public PropertyString(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		super(aOwnsNativeProperty);
		iHandle = ServicePropertyCreateStringDv(aParameter.getHandle());
	}
	
	/**
	 * Query the value of the property.
	 * 
	 * @return	string property value.
	 */
	public String getValue()
	{
		return ServicePropertyValueString(iHandle);
	}
	
	/**
	 * Set the value of the property.
	 * 
	 * @param aValue	new value for the property.
	 * @return			{@code true} if the property's value was changed;
	 * 					{@code false} otherwise.
	 */
	public boolean setValue(String aValue)
	{
		int changed = ServicePropertySetValueString(iHandle, aValue);
		
		return (changed != 0);
	}
}