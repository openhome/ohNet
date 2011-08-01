package ohnet;

import java.util.List;

import org.openhome.net.core.Property;


public class Parameter
{
	
	public static final int INT_DEFAULT_MIN = Integer.MIN_VALUE;
	public static final int INT_DEFAULT_MAX = Integer.MAX_VALUE;
	public static final int INT_DEFAULT_STEP = 1;
	public static final long UINT_DEFAULT_MIN = 0;
	public static final long UINT_DEFAULT_MAX = Long.MAX_VALUE;
	public static final long UINT_DEFAULT_STEP = 1;
	
	private native long ServiceParameterCreateInt(String aName, int aMinValue, int aMaxValue, int aStep);
	private native long ServiceParameterCreateUint(String aName, long aMinValue, long aMaxValue, long aStep);
	private native long ServiceParameterCreateBool(String aName);
	private native long ServiceParameterCreateString(String aName, String[] aAllowedValues, int aCount);
	private native long ServiceParameterCreateBinary(String aName);
	private native long ServiceParameterCreateRelated(String aName, long aProperty);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }

	private long iHandle = 0;
	
	protected Parameter() {};

	public long getHandle()
	{
		return iHandle;
	}
	
	protected void initialiseServiceParameterInt(String aName, int aMinValue, int aMaxValue, int aStep)
	{
		iHandle = ServiceParameterCreateInt(aName, aMinValue, aMaxValue, aStep);
	}
	
	protected void initialiseServiceParameterUint(String aName, long aMinValue, long aMaxValue, long aStep)
	{
		iHandle = ServiceParameterCreateUint(aName, aMinValue, aMaxValue, aStep);
	}
	
	protected void initialiseServiceParameterBool(String aName)
	{
		iHandle = ServiceParameterCreateBool(aName);
	}
	
	protected void initialiseServiceParameterString(String aName, List<String> aAllowedValues)
	{
		String[] allowedValues = new String[aAllowedValues.size()];
		allowedValues = aAllowedValues.toArray(allowedValues);
		iHandle = ServiceParameterCreateString(aName, allowedValues, allowedValues.length);
	}
	
	protected void initialiseServiceParameterBinary(String aName)
	{
		iHandle = ServiceParameterCreateBinary(aName);
	}
	
	protected void initialiseServiceParameterRelated(String aName, Property aProperty)
	{
		iHandle = ServiceParameterCreateRelated(aName, aProperty.getHandle());
	}
	
}
