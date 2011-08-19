package org.openhome.net.controlpoint;

/**
 * (Action) Argument.  Only intended for use by auto-generated proxies.
 * 
 * <p>One Argument will be created per [in/out]put Parameter for the Action.
 * Input parameters should construct arguments using the <tt>(Parameter, Val)</tt>
 * constructor.
 * Output parameters should construct arguments using only the parameter and should
 * read the value when the invocation completes.
 */
public class Argument
{

	protected long iHandle;

	protected Argument() {}
	
	/**
	 * Get the pointer to the underlying native data structure.
	 * @return	the underlying pointer.
	 */
	protected long getHandle()
	{
		return iHandle;
	}
	
}
