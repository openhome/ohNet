package org.openhome.net.core;

/**
 * Unsigned integer type parameter.  Only intended for use by auto-generated proxies and providers.
 */
public class ParameterUint extends Parameter
{
	private static native long ServiceParameterCreateUint(String aName, long aMinValue, long aMaxValue, long aStep);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	public static final long UINT_DEFAULT_MIN = 0;
	public static final long UINT_DEFAULT_MAX = Long.MAX_VALUE;
	public static final long UINT_DEFAULT_STEP = 1;
	
	/**
	 * Constructor. Constructs a parameter with the default value range.
	 * 
	 * @param aName	parameter name.
	 */
	public ParameterUint(String aName)
	{
		iHandle = ServiceParameterCreateUint(aName, UINT_DEFAULT_MIN, UINT_DEFAULT_MAX, UINT_DEFAULT_STEP);
	}
	
	/**
	 * Constructor. Constructs a parameter with the given range and default
	 * gap between values.
	 * 
	 * @param aName		parameter name.
	 * @param aMinValue	minimum allowed value.
	 * @param aMaxValue	maximum allowed value.
	 */
	public ParameterUint(String aName, long aMinValue, long aMaxValue)
	{
		iHandle = ServiceParameterCreateUint(aName, aMinValue, aMaxValue, UINT_DEFAULT_STEP);
	}

	/**
	 * Constructor.
	 *
	 * @param aName		parameter name.
	 * @param aMinValue	minimum allowed value.
	 * @param aMaxValue	maximum allowed value.
	 * @param aStep		gap between allowed values
	 */
	public ParameterUint(String aName, long aMinValue, long aMaxValue, long aStep)
	{
		iHandle = ServiceParameterCreateUint(aName, aMinValue, aMaxValue, aStep);
	}
}
