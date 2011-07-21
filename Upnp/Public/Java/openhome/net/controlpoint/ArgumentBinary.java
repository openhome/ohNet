package openhome.net.controlpoint;

import ohnet.ParameterBinary;


public class ArgumentBinary extends Argument
{
	
	private native long ActionArgumentCreateBinaryInput(long parameterPtr, byte[] aData, int aLen);
	private native long ActionArgumentCreateBinaryOutput(long parameterPtr);
	private native byte[] ActionArgumentGetValueBinary(long argumentPtr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	public ArgumentBinary(ParameterBinary aParameter, byte[] aValue)
	{
		iHandle = ActionArgumentCreateBinaryInput(aParameter.getHandle(), aValue, aValue.length);
	}
	
	public ArgumentBinary(ParameterBinary aParameter)
	{
		iHandle = ActionArgumentCreateBinaryOutput(aParameter.getHandle());
	}
	
	public byte[] value()
	{
		return ActionArgumentGetValueBinary(iHandle);
	}

}