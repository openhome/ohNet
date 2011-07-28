package openhome.net.controlpoint;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.ICpProxyListener;
import org.openhome.net.controlpoint.ProxyError;

import ohnet.Action;

public class Invocation
{
	
	private native long CpServiceInvocation(long aService, long aAction);
	private native void CpInvocationAddInput(long aInvocation, long aArgument);
	private native void CpInvocationAddOutput(long aInvocation, long aArgument);
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
	
	private ICpProxyListener iAsyncComplete = null;
	private CpService iService = null;
	private long iHandle = 0;
	private List<Argument> iInputArgs = null;
	private List<Argument> iOutputArgs = null;
	
	public Invocation(CpService aService, Action aAction, ICpProxyListener aCallback)
	{
		iService = aService;
		iInputArgs = new LinkedList<Argument>();
		iOutputArgs = new LinkedList<Argument>();
		iAsyncComplete = aCallback;
		
		iHandle = CpServiceInvocation(aService.getHandle(), aAction.getHandle());
	}
	
	protected long getHandle()
	{
		return iHandle;
	}
	
	public void addInput(Argument aArgument)
    {
        iInputArgs.add(aArgument);
        CpInvocationAddInput(iHandle, aArgument.getHandle());
    }
	
	public void addOutput(Argument aArgument)
    {
        iOutputArgs.add(aArgument);
        CpInvocationAddOutput(iHandle, aArgument.getHandle());
    }
	
	public static boolean error(long aHandle)
    {
        int err = CpInvocationError(aHandle);
        return (err != 0);
    }
	
	public static int getOutputInt(long aHandle, int aIndex)
    {
        return CpInvocationOutputInt(aHandle, aIndex);
    }
	
	public static long getOutputUint(long aHandle, int aIndex)
    {
        return CpInvocationOutputUint(aHandle, aIndex);
    }
	
	public static boolean getOutputBool(long aHandle, int aIndex)
    {
        int val = CpInvocationOutputBool(aHandle, aIndex);
        
        return (val != 0);
    }
	
	public static String getOutputString(long aHandle, int aIndex)
	{
		return CpInvocationOutputString(aHandle, aIndex);
	}

	public static byte[] getOutputBinary(long aHandle, int aIndex)
	{
		return CpInvocationGetOutputBinary(aHandle, aIndex);
	}
	
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
