package org.openhome.net.controlpoint;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.Action;



/**
 * Used by CpProxy to represent a service offered by a remote device.
 * Only intended for use by auto-generated proxies.
 */
public class CpService
{

	private static native long CpServiceCreate(String aDomain, String aName, int aVersion, long aDevice);
	private static native void CpServiceDestroy(long aService);
	private static native void CpServiceInvokeAction(long aService, long aInvocation);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle;
	private List<Invocation> iActiveInvocations;
	
	/**
	 * Constructor.  Only intended for use by CpProxy.
	 * 
	 * @param aHandle	Handle to native CpService structure.
	 */
	protected CpService(long aHandle)
	{
		iHandle = aHandle;
		iActiveInvocations = new LinkedList<Invocation>();
	}
	
	/**
	 * Get a handle to the underlying native service.
	 * 
	 * @return	Handle to the underlying native service.
	 */
	protected long getHandle()
	{
		return iHandle;
	}
	
	/**
	 * Destroy the underlying native service.
	 */
	public void destroy()
	{
		if (iHandle != 0)
		{
			CpServiceDestroy(iHandle);
		}
		iHandle = 0;
	}
	
	/**
	 * Request an invocation object prior to setting input/output arguments.
	 * 
	 * @param aAction		action which will be invoked.
	 * @param aCallback		listener to call when the action completes.
	 * @return				invocation object, ready to receive input and output arguments.
	 */
	public Invocation getInvocation(Action aAction, ICpProxyListener aCallback)
	{
		Invocation invocation = new Invocation(this, aAction, aCallback);
		
		synchronized (this)
		{
			iActiveInvocations.add(invocation);
		}
		
		return invocation;
	}

	/**
	 * Invoke an action.
	 * 
	 * @param aInvocation	invocation object, with all input and output arguments added.
	 */
	public void invokeAction(Invocation aInvocation)
	{
		CpServiceInvokeAction(iHandle, aInvocation.getHandle());
	}

	/**
	 * Inform the service that invocation of an action has completed.
	 *
	 * @param aInvocation	the invocation that has completed.
	 */
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
