package ohnet;

public class ParameterInt extends Parameter
{
	
	public ParameterInt(String aName)
	{
		int defaultMin = Parameter.INT_DEFAULT_MIN;
		int defaultMax = Parameter.INT_DEFAULT_MAX;
		int defaultStep = Parameter.INT_DEFAULT_STEP;
		
		initialiseServiceParameterInt(aName, defaultMin, defaultMax, defaultStep);
	}
	
	public ParameterInt(String aName, int aMinValue, int aMaxValue, int aStep)
	{
		initialiseServiceParameterInt(aName, aMinValue, aMaxValue, aStep);
	}

}
