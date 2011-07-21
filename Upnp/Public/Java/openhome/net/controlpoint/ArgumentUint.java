package openhome.net.controlpoint;

import ohnet.ParameterUint;


public class ArgumentUint extends Argument
{
	
	private native long ActionArgumentCreateUintInput(long parameterPtr, long aValue);
	private native long ActionArgumentCreateUintOutput(long parameterPtr);
	private native long ActionArgumentValueUint(long argumentPtr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	public ArgumentUint(ParameterUint aParameter, long aValue)
	{
		iHandle = ActionArgumentCreateUintInput(aParameter.getHandle(), aValue);
	}
	
	public ArgumentUint(ParameterUint aParameter)
	{
		iHandle = ActionArgumentCreateUintOutput(aParameter.getHandle());
	}
	
	public long value()
	{
		return ActionArgumentValueUint(iHandle);
	}

}