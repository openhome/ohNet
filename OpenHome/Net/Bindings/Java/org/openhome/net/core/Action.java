package org.openhome.net.core;

import java.util.ArrayList;
import java.util.List;


/**
 * (Service) Action.
 * 
 * <p>Each service has <tt>0..n</tt> of these.  Each action has <tt>0..n</tt> input parameters and
 * <tt>0..m</tt> output parameters.  Each parameter must be either input or output.
 */
public class Action
{
	private static native long ServiceActionCreate(String aName);
	private static native void ServiceActionDestroy(long aAction);
	private static native void ServiceActionAddInputParameter(long aAction, long aParameter);
	private static native void ServiceActionAddOutputParameter(long aAction, long aParameter);
	private static native String ServiceActionName(long aAction);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle;
	private List<Parameter> iInputParameters;
    private List<Parameter> iOutputParameters;

    /**
     * Constructor.
     * 
     * @param aName	action Name.
     */
	public Action(String aName)
	{
		iHandle = ServiceActionCreate(aName);
		iInputParameters = new ArrayList<Parameter>();
		iOutputParameters = new ArrayList<Parameter>();
	}
	
	/**
	 * Get a handle to the underlying native action.
	 * 
	 * @return	handle to the native action.
	 */
	public long getHandle()
	{
		return iHandle;
	}
	
	/**
	 * Dispose of this action.
	 */
	public void destroy()
	{
		synchronized(this)
		{
			if (iHandle == 0)
			{
				return;
			}
			iHandle = 0;
		}
		ServiceActionDestroy(iHandle);
	}
	
	/**
	 * Add an input parameter.
	 * 
	 * @param aParameter	input parameter.  Ownership is passed to the action.
	 */
	public void addInputParameter(Parameter aParameter)
	{
		iInputParameters.add(aParameter);
		ServiceActionAddInputParameter(iHandle, aParameter.getHandle());
	}
	
	/**
	 * Add an output parameter.
	 * 
	 * @param aParameter	output parameter.  Ownership is passed to the action.
	 */
	public void addOutputParameter(Parameter aParameter)
	{
		iOutputParameters.add(aParameter);
		ServiceActionAddOutputParameter(iHandle, aParameter.getHandle());
	}
	
	/**
	 * Retrieve an input parameter.
	 * 
	 * @param aIndex	(zero-based) index of the parameter.
	 * @return			the relevant input parameter.
	 */
	public Parameter getInputParameter(int aIndex)
    {
        return iInputParameters.get(aIndex);
    }
	
	/**
	 * Retrieve an output parameter.
	 * 
	 * @param aIndex	(zero-based) index of the parameter.
	 * @return			the relevant output parameter.
	 */
	public Parameter getOutputParameter(int aIndex)
    {
        return iOutputParameters.get(aIndex);
    }
	
	/**
	 * Query the name of the action.
	 * 
	 * @return	action name.
	 */
	public String getName()
	{
		return ServiceActionName(iHandle);
	}
}
