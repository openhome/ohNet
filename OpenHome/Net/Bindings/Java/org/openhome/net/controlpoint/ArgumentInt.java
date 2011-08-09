package org.openhome.net.controlpoint;


import org.openhome.net.core.ParameterInt;

/**
 * Integer type argument.  Only intended for use by auto-generated proxies.
 */
public class ArgumentInt extends Argument
{
	
	private static native long ActionArgumentCreateIntInput(long aParameter, int aValue);
	private static native long ActionArgumentCreateIntOutput(long aParameter);
	private static native int ActionArgumentValueInt(long aArgument);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor for integer input argument for an action.
	 * 
	 * <p>Intended to be write only (its value is written on construction and not be later read).
	 * 
	 * @param aParameter 	defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using <tt>Action.addInputParameter()</tt>.
	 * @param aValue 		value for the argument.
	 */
	public ArgumentInt(ParameterInt aParameter, int aValue)
	{
		iHandle = ActionArgumentCreateIntInput(aParameter.getHandle(), aValue);
	}
	
	/**
	 * Constructor for integer output argument for an action
	 * 
	 * <p>Intended to be created without any value.  The value is later set after
	 * {@link CpService#invokeAction} is called but before the invocation's callback is run)
	 * 
	 * @param aParameter 	defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using <tt>Action.addOutputParameter()</tt>.
	 */
	public ArgumentInt(ParameterInt aParameter)
	{
		iHandle = ActionArgumentCreateIntOutput(aParameter.getHandle());
	}
	
	/**
	 * Read the value of an integer argument.
	 * 
	 * <p>Only intended for use with output arguments inside the invocation completed callback.
	 * 
	 * @return current value of the argument.
	 */
	public int getValue()
	{
		return ActionArgumentValueInt(iHandle);
	}

}
