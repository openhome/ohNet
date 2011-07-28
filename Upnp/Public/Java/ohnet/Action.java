package ohnet;

import java.util.ArrayList;
import java.util.List;


public class Action
{
	private native long ServiceActionCreate(String aName);
	private native void ServiceActionDestroy(long actionPtr);
	private native void ServiceActionAddInputParameter(long actionPtr, long paramPtr);
	private native void ServiceActionAddOutputParameter(long actionPtr, long paramPtr);
	private native String ServiceActionName(long actionPtr);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle = 0;
	private List<Parameter> iInputParameters;
    private List<Parameter> iOutputParameters;

	public Action(String aName)
	{
		iHandle = ServiceActionCreate(aName);
		iInputParameters = new ArrayList<Parameter>();
		iOutputParameters = new ArrayList<Parameter>();
	}
	
	public long getHandle()
	{
		return iHandle;
	}
	
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
	
	public void addInputParameter(Parameter aParameter)
	{
		iInputParameters.add(aParameter);
		ServiceActionAddInputParameter(iHandle, aParameter.getHandle());
	}
	
	public void addOutputParameter(Parameter aParameter)
	{
		iOutputParameters.add(aParameter);
		ServiceActionAddOutputParameter(iHandle, aParameter.getHandle());
	}
	
	public Parameter getInputParameter(int aIndex)
    {
        return iInputParameters.get(aIndex);
    }
	
	public Parameter getOutputParameter(int aIndex)
    {
        return iOutputParameters.get(aIndex);
    }
	
	public String getName()
	{
		return ServiceActionName(iHandle);
	}
}
