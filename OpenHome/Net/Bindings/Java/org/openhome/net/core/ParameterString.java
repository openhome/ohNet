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
		String[] allowedValues = new String[aAllowedValues.size()];
		allowedValues = aAllowedValues.toArray(allowedValues);
		iHandle = ServiceParameterCreateString(aName, allowedValues, allowedValues.length);
	}
}
