package org.openhome.net.controlpoint;


import org.openhome.net.core.ParameterUint;

/**
 * Unsigned integer type argument.  Only intended for use by auto-generated proxies.
 */
public class ArgumentUint extends Argument
{
	
	private static native long ActionArgumentCreateUintInput(long aParameter, long aValue);
	private static native long ActionArgumentCreateUintOutput(long aParameter);
	private static native long ActionArgumentValueUint(long aArgument);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor for unsigned integer input argument for an action.
	 * 
	 * <p>Intended to be write only (its value is written on construction and not be later read).
	 * 
	 * @param aParameter 	defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using <tt>Action.addInputParameter()</tt>.
	 * @param aValue 		value for the argument.
	 */
	public ArgumentUint(ParameterUint aParameter, long aValue)
	{
		iHandle = ActionArgumentCreateUintInput(aParameter.getHandle(), aValue);
	}
	
	/**
	 * Constructor for unsigned integer output argument for an action
	 * 
	 * <p>Intended to be created without any value.  The value is later set after
	 * {@link CpService#invokeAction} is called but before the invocation's callback is run)
	 * 
	 * @param aParameter 	defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using <tt>Action.addOutputParameter()</tt>.
	 */
	public ArgumentUint(ParameterUint aParameter)
	{
		iHandle = ActionArgumentCreateUintOutput(aParameter.getHandle());
	}
	
	/**
	 * Read the value of an integer argument.
	 * 
	 * <p>Only intended for use with output arguments inside the invocation completed callback.
	 * 
	 * @return current value of the argument.
	 */
	public long getValue()
	{
		return ActionArgumentValueUint(iHandle);
	}

}