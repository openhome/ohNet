package org.openhome.net.core;


/**
 * Related type parameter.  Only intended for use by auto-generated proxies and providers.
 * 
 * <p>A related parameter reads its allowed values from an existing Property.
 * It is normally useful to users of the device stack. Any type of property can
 * be used. However, since only int, uint and string types can have bounds
 * applied, it only makes sense to use these types of property.
 * 
 * <p>Note that no destructor exists. Parameters should be added to an action
 * or property which takes ownership of them.
 */
public class ParameterRelated extends Parameter
{
	private static native long ServiceParameterCreateRelated(String aName, long aProperty);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }

	/**
	 * Constructor.
	 * 
	 * @param aName		parameter name.
	 * @param aProperty	property to read values from.
	 */
	public ParameterRelated(String aName, Property aProperty)
	{
		iHandle = ServiceParameterCreateRelated(aName, aProperty.getHandle());
	}
	
}
