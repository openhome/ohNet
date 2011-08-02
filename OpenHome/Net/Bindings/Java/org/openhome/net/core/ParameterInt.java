package org.openhome.net.core;

/**
 * Integer type parameter.  Only intended for use by auto-generated proxies and providers.
 */
public class ParameterInt extends Parameter
{
	private static native long ServiceParameterCreateInt(String aName, int aMinValue, int aMaxValue, int aStep);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	public static final int INT_DEFAULT_MIN = Integer.MIN_VALUE;
	public static final int INT_DEFAULT_MAX = Integer.MAX_VALUE;
	public static final int INT_DEFAULT_STEP = 1;
	
	/**
	 * Constructor. Constructs a parameter with the default value range.
	 * 
	 * @param aName	parameter name.
	 */
	public ParameterInt(String aName)
	{
		iHandle = ServiceParameterCreateInt(aName, INT_DEFAULT_MIN, INT_DEFAULT_MAX, INT_DEFAULT_STEP);
	}
	
	/**
	 * Constructor. Constructs a parameter with the given range and default
	 * gap between values.
	 * 
	 * @param aName		parameter name.
	 * @param aMinValue	minimum allowed value.
	 * @param aMaxValue	maximum allowed value.
	 */
	public ParameterInt(String aName, int aMinValue, int aMaxValue)
	{
		iHandle = ServiceParameterCreateInt(aName, aMinValue, aMaxValue, INT_DEFAULT_STEP);
	}
	
	/**
	 * Constructor.
	 * 
	 * @param aName		parameter name.
	 * @param aMinValue	minimum allowed value.
	 * @param aMaxValue	maximum allowed value.
	 * @param aStep		gap between allowed values.
	 */
	public ParameterInt(String aName, int aMinValue, int aMaxValue, int aStep)
	{
		iHandle = ServiceParameterCreateInt(aName, aMinValue, aMaxValue, aStep);
	}
}
