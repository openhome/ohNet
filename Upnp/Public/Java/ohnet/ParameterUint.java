package ohnet;

public class ParameterUint extends Parameter
{
	
	public ParameterUint(String aName)
	{
		long defaultMin = Parameter.UINT_DEFAULT_MIN;
		long defaultMax = Parameter.UINT_DEFAULT_MAX;
		long defaultStep = Parameter.UINT_DEFAULT_STEP;
		
		initialiseServiceParameterUint(aName, defaultMin, defaultMax, defaultStep);
	}
	
	public ParameterUint(String aName, long aMinValue, long aMaxValue)
	{
		long defaultStep = Parameter.UINT_DEFAULT_STEP;
		
		initialiseServiceParameterUint(aName, aMinValue, aMaxValue, defaultStep);
	}

	public ParameterUint(String aName, long aMinValue, long aMaxValue, long aStep)
	{
		initialiseServiceParameterUint(aName, aMinValue, aMaxValue, aStep);
	}
	
}
