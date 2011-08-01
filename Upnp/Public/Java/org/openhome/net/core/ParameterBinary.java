package org.openhome.net.core;

/**
 * Binary type parameter.  Only intended for use by auto-generated proxies and providers.
 */
public class ParameterBinary extends Parameter
{
	private static native long ServiceParameterCreateBinary(String aName);
	
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
	public ParameterBinary(String aName)
	{
		iHandle = ServiceParameterCreateBinary(aName);
	}

}
