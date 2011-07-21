package openhome.net.controlpoint;

import ohnet.ParameterString;


public class ArgumentString extends Argument
{
	
	private native long ActionArgumentCreateStringInput(long parameterPtr, String aValue);
	private native long ActionArgumentCreateStringOutput(long parameterPtr);
	private native String ActionArgumentValueString(long argumentPtr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	public ArgumentString(ParameterString aParameter, String aValue)
	{
		iHandle = ActionArgumentCreateStringInput(aParameter.getHandle(), aValue);
	}
	
	public ArgumentString(ParameterString aParameter)
	{
		iHandle = ActionArgumentCreateStringOutput(aParameter.getHandle());
	}
	
	public String value()
	{
		return ActionArgumentValueString(iHandle);
	}

}