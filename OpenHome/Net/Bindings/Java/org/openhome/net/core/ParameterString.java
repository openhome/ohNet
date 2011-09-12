package org.openhome.net.core;

import java.util.List;

/**
 * String type parameter.  Only intended for use by auto-generated proxies and providers.
 */
public class ParameterString extends Parameter
{
	private static native long ServiceParameterCreateString(String aName, String[] aAllowedValues, int aCount);

	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor.
	 * 
	 * @param aName				parameter name.
	 * @param aAllowedValues	list of allowed values for the string.
	 */
	public ParameterString(String aName, List<String> aAllowedValues)
	{
		if (aName == null)
		{
			throw new NullPointerException("Name must not be null");
		}
		if (aAllowedValues == null)
		{
			throw new NullPointerException("Allowed values list must not be null");
		}
		// Check for null strings in aAllowedValues is made within native
		// ServiceParameterCreateString code.
		String[] allowedValues = new String[aAllowedValues.size()];
		allowedValues = aAllowedValues.toArray(allowedValues);
		iHandle = ServiceParameterCreateString(aName, allowedValues, allowedValues.length);
	}
}
