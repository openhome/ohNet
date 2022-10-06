package org.openhome.net.device;

/**
 * Utility class used by providers to read input and write output arguments.
 * 
 * <p>Only intended for use by auto-generated providers.
 */
public class DvInvocation implements IDvInvocation
{
	private class InvocationStatus
	{
		private boolean iSucceeded;
		
		public InvocationStatus(int aSucceeded)
		{
			iSucceeded = (aSucceeded == 0);
		}
		public boolean succeeded()
		{
			return iSucceeded;
		}
	}

	private class InvocationStatusInt extends InvocationStatus
	{
		private int iValue;
		
		public InvocationStatusInt(int aValue, int aSucceeded)
		{
			super(aSucceeded);
			iValue = aValue;
		}
		public int getValue()
		{
			return iValue;
		}
	}

	private class InvocationStatusUint extends InvocationStatus
	{
		private long iValue;
		
		public InvocationStatusUint(long aValue, int aSucceeded)
		{
			super(aSucceeded);
			iValue = aValue;
		}
		public long getValue()
		{
			return iValue;
		}
	}

	private class InvocationStatusBool extends InvocationStatus
	{
		private boolean iValue;
		
		public InvocationStatusBool(int aValue, int aSucceeded)
		{
			super(aSucceeded);
			iValue = (aValue != 0);
		}
		public boolean getValue()
		{
			return iValue;
		}
	}

	private class InvocationStatusString extends InvocationStatus
	{
		private String iValue;
		
		public InvocationStatusString(String aValue, int aSucceeded)
		{
			super(aSucceeded);
			iValue = aValue;
		}
		public String getValue()
		{
			return iValue;
		}
	}

	private class InvocationStatusBinary extends InvocationStatus
	{
		private byte[] iValue;
		
		public InvocationStatusBinary(byte[] aValue, int aSucceeded)
		{
			super(aSucceeded);
			iValue = aValue;
		}
		public byte[] getValue()
		{
			return iValue;
		}
	}
	
    private static native int DvInvocationGetVersion(long aInvocation);
    private static native int DvInvocationGetAdapter(long aInvocation);
    private static native String DvInvocationGetResourceUriPrefix(long aInvocation);
    private static native int DvInvocationGetClientAddress(long aInvocation);
    private static native int DvInvocationGetClientPort(long aInvocation);
    private static native String DvInvocationGetClientUserAgent(long aInvocation);
	private static native int DvInvocationReadStart(long aInvocation);
	private native InvocationStatusInt DvInvocationReadInt(long aInvocation, String aName);
	private native InvocationStatusUint DvInvocationReadUint(long aInvocation, String aName);
	private native InvocationStatusBool DvInvocationReadBool(long aInvocation, String aName);
	private native InvocationStatusString DvInvocationReadString(long aInvocation, String aName);
	private native InvocationStatusBinary DvInvocationReadBinary(long aInvocation, String aName);
	private static native int DvInvocationReadEnd(long aInvocation);
	private static native int DvInvocationReportError(long aInvocation, long aCode, String aDescription);
	private static native int DvInvocationWriteStart(long aInvocation);
	private static native int DvInvocationWriteInt(long aInvocation, String aName, int aValue);
	private static native int DvInvocationWriteUint(long aInvocation, String aName, long aValue);
	private static native int DvInvocationWriteBool(long aInvocation, String aName, int aValue);
	private static native int DvInvocationWriteStringStart(long aInvocation, String aName);
	private static native int DvInvocationWriteString(long aInvocation, String aValue);
	private static native int DvInvocationWriteStringEnd(long aInvocation, String aName);
	private static native int DvInvocationWriteBinaryStart(long aInvocation, String aName);
	private static native int DvInvocationWriteBinary(long aInvocation, byte[] aData, int aLen);
	private static native int DvInvocationWriteBinaryEnd(long aInvocation, String aName);
	private static native int DvInvocationWriteEnd(long aInvocation);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
//	 This isn't used here but MUST be called by the native code.
//	private static native void OhNetFree(long aPtr);
	
	protected long iHandle;
	
	/**
	 * Create a DvInvocation.
	 * 
	 * @param aHandle	<tt>aInvocation</tt> argument passed to <tt>IDvDeviceListener</tt>.
	 */
	public DvInvocation(long aHandle)
	{
		iHandle = aHandle;
	}
	
	/**
	 * Get the version number of the service requested by the caller.
	 *
	 * @return	The version number of the service the caller expects.
	 */
	public int getVersion()
	{
		return DvInvocationGetVersion(iHandle);
	}
	
	/**
	 * Get the network adapter an action was invoked using.
	 *
	 * @return	The network adapter used to invoke this action.
	 */
	public int getAdapter()
	{
		return DvInvocationGetAdapter(iHandle);
	}
	
	/**
	 * Get the prefix to use on any URIs to resources offered by the provider.
	 *
	 * @return	The prefix to resource URIs.
	 */
	public String getResourceUriPrefix()
	{
		String result = DvInvocationGetResourceUriPrefix(iHandle);
		if (result == null)
		{
			result = "";
		}
		return result;
	}
   
   /**
    * Get the client address for this invocation.
    *
    * @return  The client address that invoked this action.
    */
   public int getClientAddress()
   {
       return DvInvocationGetClientAddress(iHandle);
   }
   
   /**
    * Get the client port for this invocation.
    *
    * @return  The client port that invoked this action.
    */
   public int getClientPort()
   {
       return DvInvocationGetClientPort(iHandle);
   }
	
	/**
     * Get the client user agent string for this invocation.
     *
     * @return  The user agent string sent by the client, or null if no user agent string was sent.
     */
    public String getClientUserAgent()
    {
        return DvInvocationGetClientUserAgent(iHandle);
    }
    
    /**
	 * Begin reading (input arguments for) an invocation.
	 * 
	 * <p>Must be called before the values of any input arguments are read.
	 * Must be called for invocations with no input arguments.
	 */
	public void readStart()
	{
		checkError(DvInvocationReadStart(iHandle));
	}
	
	/**
	 * Read the value of an integer input argument for an invocation.
	 * 
	 * @param aName	name of the parameter associated with this input argument.
	 * @return		value of the input argument.
	 */
	public int readInt(String aName)
	{
		InvocationStatusInt status = DvInvocationReadInt(iHandle, aName);
		checkError(status.succeeded());
		return status.getValue();
	}
	
	/**
	 * Read the value of an unsigned integer input argument for an invocation.
	 * 
	 * @param aName	name of the parameter associated with this input argument.
	 * @return		value of the input argument.
	 */
	public long readUint(String aName)
	{
		InvocationStatusUint status = DvInvocationReadUint(iHandle, aName);
		checkError(status.succeeded());
		return status.getValue();
	}
	
	/**
	 * Read the value of a boolean input argument for an invocation.
	 * 
	 * @param aName	name of the parameter associated with this input argument.
	 * @return		value of the input argument.
	 */
	public boolean readBool(String aName)
	{
		InvocationStatusBool status = DvInvocationReadBool(iHandle, aName);
		checkError(status.succeeded());
		return status.getValue();
	}
	
	/**
	 * Read the value of a string input argument for an invocation.
	 * 
	 * @param aName	name of the parameter associated with this input argument.
	 * @return		value of the input argument.
	 */
	public String readString(String aName)
	{
		InvocationStatusString status = DvInvocationReadString(iHandle, aName);
		checkError(status.succeeded());
		return status.getValue();
	}
	
	/**
	 * Read the value of a binary input argument for an invocation.
	 * 
	 * @param aName	name of the parameter associated with this input argument.
	 * @return		value of the input argument.
	 */
	public byte[] readBinary(String aName)
	{
		InvocationStatusBinary status = DvInvocationReadBinary(iHandle, aName);
		checkError(status.succeeded());
		return status.getValue();
	}
	
	/**
	 * Complete reading (input arguments for) an invocation.
	 * 
	 * <p>Must be called after the values of all input arguments are read.
	 * Must be called for invocations with no input arguments.
	 */
	public void readEnd()
	{
		int err = DvInvocationReadEnd(iHandle);
		checkError(err);
	}
	
	/**
	 * Report an error reading or writing an invocation.
	 * 
	 * <p>Must be called if {@link #readEnd} isn't reached.
	 * May be called if {@link #writeStart} or later have been called.
	 * 
	 * @param aCode			error code.
	 * @param aDescription	error description.
	 */
	public void reportError(long aCode, String aDescription)
	{
		// no point in propogating any error - client code can't cope with error reporting failing
		DvInvocationReportError(iHandle, aCode, aDescription);
	}
	
	/**
	 * Begin writing (output arguments for) an invocation.
	 * 
	 * <p>Must be called before the values of any output arguments are written.
	 * Must be called for invocations with no output arguments.
	 */
	public void writeStart()
	{
		checkError(DvInvocationWriteStart(iHandle));
	}
	
	/**
	 * Set the value of an integer output argument for an invocation.
	 * 
	 * @param aName		name of the parameter associated with this output argument.
	 * @param aValue	value of the output argument.
	 */
	public void writeInt(String aName, int aValue)
	{
		int err = DvInvocationWriteInt(iHandle, aName, aValue);
		checkError(err);
	}
	
	/**
	 * Set the value of an unsigned integer output argument for an invocation.
	 * 
	 * @param aName		name of the parameter associated with this output argument.
	 * @param aValue	value of the output argument.
	 */
	public void writeUint(String aName, long aValue)
	{
		int err = DvInvocationWriteUint(iHandle, aName, aValue);
		checkError(err);
	}
	
	/**
	 * Set the value of a boolean output argument for an invocation.
	 * 
	 * @param aName		name of the parameter associated with this output argument.
	 * @param aValue	value of the output argument.
	 */
	public void writeBool(String aName, boolean aValue)
	{
		int val = (aValue ? 1 : 0);
		int err = DvInvocationWriteBool(iHandle, aName, val);
		checkError(err);
	}
	
	/**
	 * Set the value of a string output argument for an invocation.
	 * 
	 * @param aName		name of the parameter associated with this output argument.
	 * @param aValue	value of the output argument.
	 */
	public void writeString(String aName, String aValue)
	{
		int err = DvInvocationWriteStringStart(iHandle, aName);
		if (err == 0)
		{
			err = DvInvocationWriteString(iHandle, aValue);
		}
		if (err == 0)
		{
			err = DvInvocationWriteStringEnd(iHandle, aName);
		}
		checkError(err);
	}
	
	/**
	 * Set the value of a binary output argument for an invocation.
	 * 
	 * @param aName	name of the parameter associated with this output argument.
	 * @param aData	value of the output argument.
	 */
	public void writeBinary(String aName, byte[] aData)
	{
		int err = DvInvocationWriteBinaryStart(iHandle, aName);
		if (err == 0)
		{
			err = DvInvocationWriteBinary(iHandle, aData, aData.length);
		}
		if (err == 0)
		{
			err = DvInvocationWriteBinaryEnd(iHandle, aName);
		}
		checkError(err);
	}
	
	/**
	 * Complete writing (output arguments for) an invocation.
	 * 
	 * <p>Must be called after the values of all output arguments are written.
	 * Must be called for invocations with no output arguments.
	 */
	public void writeEnd()
	{
		checkError(DvInvocationWriteEnd(iHandle));
	}
	
	/**
     * Report an error from action processing in provider code.
     * 
     * @param aError       the {@link #ActionError} exception object.
     * @param aActionName  the action name.
     */
    public void reportActionError(ActionError aError, String aActionName)
    {
        String msg = aError.getMessage();
        if (msg == null)
            msg = String.format("Action %s failed", aActionName);

        int errCode = aError.getErrorCode();
        if (errCode == 0)
            errCode = 501;

        reportError(errCode, msg);
    }

	/**
	 * Check if an error has been encountered during a read or write process.
	 * 
	 * @param aSuccess	the error status to be checked.
	 * @throws {@link #ActionError} if <tt>aSuccess</tt> is non-zero.
	 */
	private void checkError(boolean aSuccess)
	{
		if (!aSuccess)
		{
			throw (new ActionError());
		}
	}
	
	/**
	 * Check if an error has been encountered during a read or write process.
	 * 
	 * @param aError	the error status to be checked.
	 * @throws {@link #ActionError} if <tt>aError</tt> is non-zero.
	 */
	private void checkError(int aError)
	{
		if (aError != 0)
		{
			throw (new ActionError());
		}
	}
}
