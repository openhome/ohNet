package openhome.net.controlpoint;

import java.util.LinkedList;
import java.util.List;

import ohnet.Action;

public class CpService
{

	private native long CpServiceCreate(String aDomain, String aName, int aVersion, long aDevice);
	private native void CpServiceDestroy(long aService);
	private native void CpServiceInvokeAction(long aService, long aInvocation);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle = 0;
	private List<Invocation> iActiveInvocations = null;
	
	public CpService(long aHandle)
	{
		iHandle = aHandle;
		iActiveInvocations = new LinkedList<Invocation>();
	}
	
	protected long getHandle()
	{
		return iHandle;
	}
	
	public void destroy()
	{
		if (iHandle != 0)
		{
			CpServiceDestroy(iHandle);
		}
	}
	
	public Invocation getInvocation(Action aAction, ICpProxyListener aCallback)
	{
		Invocation invocation = new Invocation(this, aAction, aCallback);
		
		synchronized (this)
		{
			iActiveInvocations.add(invocation);
		}
		
		return invocation;
	}

	public void invokeAction(Invocation aInvocation)
	{
		CpServiceInvokeAction(iHandle, aInvocation.getHandle());
	}

	protected void invocationComplete(Invocation aInvocation)
	{
		long handle = aInvocation.getHandle();
		int i = 0;
		synchronized (this)
		{
			for (Invocation invocation : iActiveInvocations)
			{
				if (invocation.getHandle() == handle)
				{
					iActiveInvocations.remove(i);
					break;
				}
				i++;
			}
		}
	}

}
