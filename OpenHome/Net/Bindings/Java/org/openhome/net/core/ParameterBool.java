package org.openhome.net.core;

/**
 * Boolean type parameter.  Only intended for use by auto-generated proxies and providers.
 */
public class ParameterBool extends Parameter
{
	private static native long ServiceParameterCreateBool(String aName);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor.
	 * 
	 * @param aName	parameter name.
	 */
	public ParameterBool(String aName)
	{
		iHandle = ServiceParameterCreateBool(aName);
	}

}
