package org.openhome.net.controlpoint;


import org.openhome.net.core.ParameterBinary;

/**
 * Binary type argument.  Only intended for use by auto-generated proxies.
 */
public class ArgumentBinary extends Argument
{
	
	private static native long ActionArgumentCreateBinaryInput(long aParameter, byte[] aData, int aLen);
	private static native long ActionArgumentCreateBinaryOutput(long aParameter);
	private static native byte[] ActionArgumentGetValueBinary(long aArgument);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor for binary input argument for an action.
	 * 
	 * <p>Intended to be write only (its value is written on construction and not be later read).
	 * 
	 * @param aParameter 	defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using <tt>Action.addInputParameter()</tt>.
	 * @param aValue 		value for the argument.
	 */
	public ArgumentBinary(ParameterBinary aParameter, byte[] aValue)
	{
		iHandle = ActionArgumentCreateBinaryInput(aParameter.getHandle(), aValue, aValue.length);
	}
	
	/**
	 * Constructor for binary output argument for an action
	 * 
	 * <p>Intended to be created without any value.  The value is later set after
	 * {@link CpService#invokeAction} is called but before the invocation's callback is run)
	 * 
	 * @param aParameter 	defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using <tt>Action.addOutputParameter()</tt>.
	 */
	public ArgumentBinary(ParameterBinary aParameter)
	{
		iHandle = ActionArgumentCreateBinaryOutput(aParameter.getHandle());
	}
	
	/**
	 * Read the value of a binary argument.
	 * 
	 * <p>Only intended for use with output arguments inside the invocation completed callback.
	 * 
	 * @return current value of the argument.
	 */
	public byte[] getValue()
	{
		return ActionArgumentGetValueBinary(iHandle);
	}

}