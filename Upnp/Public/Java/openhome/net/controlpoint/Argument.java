package openhome.net.controlpoint;

/**
 * (Action) Argument.  Only intended for use by auto-generated proxies.
 * 
 * One Argument will be created per [in/out]put Parameter for the Action.
 * Input parameters should construct arguments using the (Parameter, Val) constructor.
 * Output parameters should construct arguments using only the parameter and should
 * read the value when the invocation completes.
 */
public class Argument
{

	protected long iHandle = 0;
	
	/**
	 * 
	 */
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
