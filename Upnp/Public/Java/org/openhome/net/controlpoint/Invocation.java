package org.openhome.net.controlpoint;

import java.util.LinkedList;
import java.util.List;


import ohnet.Action;

/**
 * Utility class used to execute a single action. Only intended for use by
 * auto-generated proxies.
 */
public class Invocation
{
	
	private native long CpServiceInvocation(long aService, long aAction);
	private static native void CpInvocationAddInput(long aInvocation, long aArgument);
	private static native void CpInvocationAddOutput(long aInvocation, long aArgument);
	private static native int CpInvocationError(long aInvocation);
	private static native int CpInvocationOutputInt(long aInvocation, int aIndex);
	private static native long CpInvocationOutputUint(long aInvocation, int aIndex);
	private static native int CpInvocationOutputBool(long aInvocation, int aIndex);
	private static native String CpInvocationOutputString(long aInvocation, int aIndex);
	private static native byte[] CpInvocationGetOutputBinary(long aInvocation, int aIndex);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private ICpProxyListener iAsyncComplete;
	private CpService iService;
	private long iHandle;
	private List<Argument> iInputArgs;
	private List<Argument> iOutputArgs;
	
	/**
	 * Constructor.  Not intended for external use (use {@link #CpService.Invocation}
	 * instead).
	 *
	 * @param aService		service the action is being invoked on.
	 * @param aAction		handle to the action being invoked.
	 * @param aCallback		callback to run when the action completes.
	 */
	public Invocation(CpService aService, Action aAction, ICpProxyListener aCallback)
	{
		iService = aService;
		iInputArgs = new LinkedList<Argument>();
		iOutputArgs = new LinkedList<Argument>();
		iAsyncComplete = aCallback;
		
		iHandle = CpServiceInvocation(aService.getHandle(), aAction.getHandle());
	}
	
	/**
	 * Get the handle to the underlying native invocation.
	 *
	 * @return	handle to the native invocation.
	 */
	protected long getHandle()
	{
		return iHandle;
	}
	
	/**
	 * Add an input argument to an invocation.
	 * 
	 * @param aArgument	input argument being added. Ownership passes to the invocation.
	 */
	public void addInput(Argument aArgument)
    {
        iInputArgs.add(aArgument);
        CpInvocationAddInput(iHandle, aArgument.getHandle());
    }
	
	/**
	 * Add an output argument to an invocation.
	 *
	 * @param aArgument	output argument being added. Ownership passes to the invocation.
	 */
	public void addOutput(Argument aArgument)
    {
        iOutputArgs.add(aArgument);
        CpInvocationAddOutput(iHandle, aArgument.getHandle());
    }
	
	/**
	 * Check whether the invocation failed.
	 * 
	 * <p>Only intended for use in the invocation complete callback.
	 *
	 * @param aHandle	invocation to check for errors.
	 * @return			{@code true} if the invocation failed; {@code false} if it succeeded.
	 */
	public static boolean error(long aHandle)
    {
        int err = CpInvocationError(aHandle);
        return (err != 0);
    }
	
	/**
	 * Utility to retrieve the value of an integer type output argument.
	 * 
	 * @param aHandle	invocation handle.
	 * @param aIndex	zero-based index into array of output arguments.
	 * 					Must refer to an {@link #ArgumentInt}.
	 * @return			value of the integer output argument.
	 */
	public static int getOutputInt(long aHandle, int aIndex)
    {
        return CpInvocationOutputInt(aHandle, aIndex);
    }
	
	/**
	 * Utility to retrieve the value of an unsigned integer type output argument.
	 * 
	 * @param aHandle	invocation handle.
	 * @param aIndex	zero-based index into array of output arguments.
	 * 					Must refer to an {@link #ArgumentUint}.
	 * @return			value of the unsigned integer output argument.
	 */
	public static long getOutputUint(long aHandle, int aIndex)
    {
        return CpInvocationOutputUint(aHandle, aIndex);
    }
	
	/**
	 * Utility to retrieve the value of a boolean type output argument.
	 * 
	 * @param aHandle	invocation handle.
	 * @param aIndex	zero-based index into array of output arguments.
	 * 					Must refer to an {@link #ArgumentBool}.
	 * @return			value of the boolean output argument.
	 */
	public static boolean getOutputBool(long aHandle, int aIndex)
    {
        int val = CpInvocationOutputBool(aHandle, aIndex);
        
        return (val != 0);
    }
	
	/**
	 * Utility to retrieve the value of a string type output argument.
	 * 
	 * <p>Must only be called once per output argument. (The first call
	 * extracts the string data from the underlying native object so later
	 * calls would return an empty string.)
	 *
	 * @param aHandle	invocation handle.
	 * @param aIndex	zero-based index into array of output arguments.
	 * 					Must refer to an {@link #ArgumentString}.
	 * @return			value of the string output argument.
	 */
	public static String getOutputString(long aHandle, int aIndex)
	{
		return CpInvocationOutputString(aHandle, aIndex);
	}

	/**
	 * Utility to retrieve the value of a binary type output argument.
	 * 
	 * <p>Must only be called once per output argument.  (The first call
	 * extracts the binary data from the underlying native object so later
	 * calls would return an empty string.)
	 * 
	 * @param aHandle	invocation handle.
	 * @param aIndex	zero-based index into array of output arguments.
	 * 					Must refer to an {@link #ArgumentBinary}.
	 * @return			value of the string output argument.
	 */
	public static byte[] getOutputBinary(long aHandle, int aIndex)
	{
		return CpInvocationGetOutputBinary(aHandle, aIndex);
	}
	
	/**
	 * Asynchronous callback used for notification that an invocation has
	 * successfully completed.
	 * 
	 * @param aPtr			custom data used for callback purposes.
	 * @param aAsyncHandle	asynchronous handle.
	 */
	public void asyncComplete(long aPtr, long aAsyncHandle)
    {
        try
        {
//		iAsyncComplete.callbackActionComplete(aPtr, aAsyncHandle);
		iAsyncComplete.callbackAsyncComplete(aAsyncHandle);
        }
        catch (ProxyError pe)
        {
        }
        catch (Exception e)
        {
        	System.out.println("ERROR: unexpected exception thrown: " + e.getMessage() + "\nStack trace: " + e.getStackTrace());
			System.out.println("       Only ProxyError can be thrown by action complete delegates");
        }
		iService.invocationComplete(this);
    }
}
