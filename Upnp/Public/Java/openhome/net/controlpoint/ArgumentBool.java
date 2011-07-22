package openhome.net.controlpoint;

import ohnet.ParameterBool;


public class ArgumentBool extends Argument
{
	
	private native long ActionArgumentCreateBoolInput(long parameterPtr, int aValue);
	private native long ActionArgumentCreateBoolOutput(long parameterPtr);
	private native int ActionArgumentValueBool(long argumentPtr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	public ArgumentBool(ParameterBool aParameter, boolean aValue)
	{
		iHandle = ActionArgumentCreateBoolInput(aParameter.getHandle(), (aValue ? 1 : 0));
	}
	
	public ArgumentBool(ParameterBool aParameter)
	{
		iHandle = ActionArgumentCreateBoolOutput(aParameter.getHandle());
	}
	
	public boolean value()
	{
		int val = ActionArgumentValueBool(iHandle);
		
		return (val != 0);
	}

}