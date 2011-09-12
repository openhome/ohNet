package org.openhome.net.controlpoint;


import org.openhome.net.core.ParameterString;

/**
 * String type argument.  Only intended for use by auto-generated proxies.
 */
public class ArgumentString extends Argument
{
	
	private static native long ActionArgumentCreateStringInput(long aParameter, String aValue);
	private static native long ActionArgumentCreateStringOutput(long aParameter);
	private static native String ActionArgumentValueString(long aArgument);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor for string input argument for an action.
	 * 
	 * <p>Intended to be write only (its value is written on construction and not be later read).
	 * 
	 * @param aParameter 	defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using <tt>Action.addInputParameter()</tt>.
	 * @param aValue 		value for the argument.
	 */
	public ArgumentString(ParameterString aParameter, String aValue)
	{
		if (aValue == null)
		{
			throw new NullPointerException("Value must not be null");
		}
		iHandle = ActionArgumentCreateStringInput(aParameter.getHandle(), aValue);
	}
	
	/**
	 * Constructor for string output argument for an action
	 * 
	 * <p>Intended to be created without any value.  The value is later set after
	 * {@link CpService#invokeAction} is called but before the invocation's callback is run)
	 * 
	 * @param aParameter 	defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using <tt>Action.addOutputParameter()</tt>.
	 */
	public ArgumentString(ParameterString aParameter)
	{
		iHandle = ActionArgumentCreateStringOutput(aParameter.getHandle());
	}
	
	/**
	 * Read the value of an integer argument.
	 * 
	 * <p>Only intended for use with output arguments inside the invocation completed callback.
	 * 
	 * @return current value of the argument.
	 */
	public String getValue()
	{
		return ActionArgumentValueString(iHandle);
	}

}