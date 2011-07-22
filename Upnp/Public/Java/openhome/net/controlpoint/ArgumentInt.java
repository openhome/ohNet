package openhome.net.controlpoint;

import ohnet.ParameterInt;

/**
 * Integer type argument.  Only intended for use by auto-generated proxies.
 */
public class ArgumentInt extends Argument
{
	
	private native long ActionArgumentCreateIntInput(long parameterPtr, int aValue);
	private native long ActionArgumentCreateIntOutput(long parameterPtr);
	private native int ActionArgumentValueInt(long argumentPtr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	/**
	 * Constructor for integer input argument for an action.
	 * Intended to be write only (its value is written on construction and not be later read).
	 * 
	 * @param aParameter Defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using {@link ohnet.Action#addInputParameter}.
	 * @param aValue value for the argument.
	 */
	public ArgumentInt(ParameterInt aParameter, int aValue)
	{
		iHandle = ActionArgumentCreateIntInput(aParameter.getHandle(), aValue);
	}
	
	/**
	 * Constructor for integer output argument for an action
	 * Intended to be created without any value.  The value is later set after
	 * CpService.InvokeAction is called but before the invocation's callback is run)
	 * @param aParameter Defines the name plus any bounds to the value for the argument.
	 * Must have been previously added to the action using Action.AddOutputParameter
	 */
	public ArgumentInt(ParameterInt aParameter)
	{
		iHandle = ActionArgumentCreateIntOutput(aParameter.getHandle());
	}
	
	/**
	 * Read the value of an integer argument.
	 * Only intended for use with output arguments inside the invocation completed callback.
	 * @return current value of the argument.
	 */
	public int value()
	{
		return ActionArgumentValueInt(iHandle);
	}

}
