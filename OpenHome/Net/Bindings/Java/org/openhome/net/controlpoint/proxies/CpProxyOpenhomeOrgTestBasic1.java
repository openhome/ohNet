package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyOpenhomeOrgTestBasic1.*;
import org.openhome.net.core.*;

	
interface ICpProxyOpenhomeOrgTestBasic1 extends ICpProxy
{
    public long syncIncrement(long aValue);
    public void beginIncrement(long aValue, ICpProxyListener aCallback);
    public long endIncrement(long aAsyncHandle);
    public int syncDecrement(int aValue);
    public void beginDecrement(int aValue, ICpProxyListener aCallback);
    public int endDecrement(long aAsyncHandle);
    public boolean syncToggle(boolean aValue);
    public void beginToggle(boolean aValue, ICpProxyListener aCallback);
    public boolean endToggle(long aAsyncHandle);
    public String syncEchoString(String aValue);
    public void beginEchoString(String aValue, ICpProxyListener aCallback);
    public String endEchoString(long aAsyncHandle);
    public byte[] syncEchoBinary(byte[] aValue);
    public void beginEchoBinary(byte[] aValue, ICpProxyListener aCallback);
    public byte[] endEchoBinary(long aAsyncHandle);
    public void syncSetUint(long aValueUint);
    public void beginSetUint(long aValueUint, ICpProxyListener aCallback);
    public void endSetUint(long aAsyncHandle);
    public long syncGetUint();
    public void beginGetUint(ICpProxyListener aCallback);
    public long endGetUint(long aAsyncHandle);
    public void syncSetInt(int aValueInt);
    public void beginSetInt(int aValueInt, ICpProxyListener aCallback);
    public void endSetInt(long aAsyncHandle);
    public int syncGetInt();
    public void beginGetInt(ICpProxyListener aCallback);
    public int endGetInt(long aAsyncHandle);
    public void syncSetBool(boolean aValueBool);
    public void beginSetBool(boolean aValueBool, ICpProxyListener aCallback);
    public void endSetBool(long aAsyncHandle);
    public boolean syncGetBool();
    public void beginGetBool(ICpProxyListener aCallback);
    public boolean endGetBool(long aAsyncHandle);
    public void syncSetMultiple(long aValueUint, int aValueInt, boolean aValueBool);
    public void beginSetMultiple(long aValueUint, int aValueInt, boolean aValueBool, ICpProxyListener aCallback);
    public void endSetMultiple(long aAsyncHandle);
    public void syncSetString(String aValueStr);
    public void beginSetString(String aValueStr, ICpProxyListener aCallback);
    public void endSetString(long aAsyncHandle);
    public String syncGetString();
    public void beginGetString(ICpProxyListener aCallback);
    public String endGetString(long aAsyncHandle);
    public void syncSetBinary(byte[] aValueBin);
    public void beginSetBinary(byte[] aValueBin, ICpProxyListener aCallback);
    public void endSetBinary(long aAsyncHandle);
    public byte[] syncGetBinary();
    public void beginGetBinary(ICpProxyListener aCallback);
    public byte[] endGetBinary(long aAsyncHandle);
    public void syncToggleBool();
    public void beginToggleBool(ICpProxyListener aCallback);
    public void endToggleBool(long aAsyncHandle);
    public void syncWriteFile(String aData, String aFileFullName);
    public void beginWriteFile(String aData, String aFileFullName, ICpProxyListener aCallback);
    public void endWriteFile(long aAsyncHandle);
    public void syncShutdown();
    public void beginShutdown(ICpProxyListener aCallback);
    public void endShutdown(long aAsyncHandle);
    public void setPropertyVarUintChanged(IPropertyChangeListener aVarUintChanged);
    public long getPropertyVarUint();
    public void setPropertyVarIntChanged(IPropertyChangeListener aVarIntChanged);
    public int getPropertyVarInt();
    public void setPropertyVarBoolChanged(IPropertyChangeListener aVarBoolChanged);
    public boolean getPropertyVarBool();
    public void setPropertyVarStrChanged(IPropertyChangeListener aVarStrChanged);
    public String getPropertyVarStr();
    public void setPropertyVarBinChanged(IPropertyChangeListener aVarBinChanged);
    public byte[] getPropertyVarBin();
}

class SyncIncrementOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private long iResult;

    public SyncIncrementOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public long getResult()
    {
        return iResult;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endIncrement(aAsyncHandle);
		
        iResult = result;
    }
}

class SyncDecrementOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private int iResult;

    public SyncDecrementOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public int getResult()
    {
        return iResult;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        int result = iService.endDecrement(aAsyncHandle);
		
        iResult = result;
    }
}

class SyncToggleOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private boolean iResult;

    public SyncToggleOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getResult()
    {
        return iResult;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endToggle(aAsyncHandle);
		
        iResult = result;
    }
}

class SyncEchoStringOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private String iResult;

    public SyncEchoStringOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public String getResult()
    {
        return iResult;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endEchoString(aAsyncHandle);
		
        iResult = result;
    }
}

class SyncEchoBinaryOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private byte[] iResult;

    public SyncEchoBinaryOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public byte[] getResult()
    {
        return iResult;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        byte[] result = iService.endEchoBinary(aAsyncHandle);
		
        iResult = result;
    }
}

class SyncSetUintOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncSetUintOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetUint(aAsyncHandle);
		
    }
}

class SyncGetUintOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private long iValueUint;

    public SyncGetUintOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public long getValueUint()
    {
        return iValueUint;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetUint(aAsyncHandle);
		
        iValueUint = result;
    }
}

class SyncSetIntOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncSetIntOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetInt(aAsyncHandle);
		
    }
}

class SyncGetIntOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private int iValueInt;

    public SyncGetIntOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public int getValueInt()
    {
        return iValueInt;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        int result = iService.endGetInt(aAsyncHandle);
		
        iValueInt = result;
    }
}

class SyncSetBoolOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncSetBoolOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetBool(aAsyncHandle);
		
    }
}

class SyncGetBoolOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private boolean iValueBool;

    public SyncGetBoolOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getValueBool()
    {
        return iValueBool;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endGetBool(aAsyncHandle);
		
        iValueBool = result;
    }
}

class SyncSetMultipleOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncSetMultipleOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetMultiple(aAsyncHandle);
		
    }
}

class SyncSetStringOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncSetStringOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetString(aAsyncHandle);
		
    }
}

class SyncGetStringOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private String iValueStr;

    public SyncGetStringOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public String getValueStr()
    {
        return iValueStr;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetString(aAsyncHandle);
		
        iValueStr = result;
    }
}

class SyncSetBinaryOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncSetBinaryOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetBinary(aAsyncHandle);
		
    }
}

class SyncGetBinaryOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;
    private byte[] iValueBin;

    public SyncGetBinaryOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    public byte[] getValueBin()
    {
        return iValueBin;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        byte[] result = iService.endGetBinary(aAsyncHandle);
		
        iValueBin = result;
    }
}

class SyncToggleBoolOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncToggleBoolOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endToggleBool(aAsyncHandle);
		
    }
}

class SyncWriteFileOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncWriteFileOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endWriteFile(aAsyncHandle);
		
    }
}

class SyncShutdownOpenhomeOrgTestBasic1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestBasic1 iService;

    public SyncShutdownOpenhomeOrgTestBasic1(CpProxyOpenhomeOrgTestBasic1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endShutdown(aAsyncHandle);
		
    }
}

/**
 * Proxy for the openhome.org:TestBasic:1 UPnP service
 */
public class CpProxyOpenhomeOrgTestBasic1 extends CpProxy implements ICpProxyOpenhomeOrgTestBasic1
{

    private Action iActionIncrement;
    private Action iActionDecrement;
    private Action iActionToggle;
    private Action iActionEchoString;
    private Action iActionEchoBinary;
    private Action iActionSetUint;
    private Action iActionGetUint;
    private Action iActionSetInt;
    private Action iActionGetInt;
    private Action iActionSetBool;
    private Action iActionGetBool;
    private Action iActionSetMultiple;
    private Action iActionSetString;
    private Action iActionGetString;
    private Action iActionSetBinary;
    private Action iActionGetBinary;
    private Action iActionToggleBool;
    private Action iActionWriteFile;
    private Action iActionShutdown;
    private PropertyUint iVarUint;
    private PropertyInt iVarInt;
    private PropertyBool iVarBool;
    private PropertyString iVarStr;
    private PropertyBinary iVarBin;
    private IPropertyChangeListener iVarUintChanged;
    private IPropertyChangeListener iVarIntChanged;
    private IPropertyChangeListener iVarBoolChanged;
    private IPropertyChangeListener iVarStrChanged;
    private IPropertyChangeListener iVarBinChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@code #subscribe}/{@code #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice	the device to use.
     */

    public CpProxyOpenhomeOrgTestBasic1(CpDevice aDevice)
    {
        super("openhome-org", "TestBasic", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionIncrement = new Action("Increment");
        param = new ParameterUint("Value");
		iActionIncrement.addInputParameter(param);
        param = new ParameterUint("Result");
		iActionIncrement.addOutputParameter(param);

        iActionDecrement = new Action("Decrement");
        param = new ParameterInt("Value");
		iActionDecrement.addInputParameter(param);
        param = new ParameterInt("Result");
		iActionDecrement.addOutputParameter(param);

        iActionToggle = new Action("Toggle");
        param = new ParameterBool("Value");
		iActionToggle.addInputParameter(param);
        param = new ParameterBool("Result");
		iActionToggle.addOutputParameter(param);

        iActionEchoString = new Action("EchoString");
        param = new ParameterString("Value", allowedValues);
		iActionEchoString.addInputParameter(param);
        param = new ParameterString("Result", allowedValues);
		iActionEchoString.addOutputParameter(param);

        iActionEchoBinary = new Action("EchoBinary");
        param = new ParameterBinary("Value");
		iActionEchoBinary.addInputParameter(param);
        param = new ParameterBinary("Result");
		iActionEchoBinary.addOutputParameter(param);

        iActionSetUint = new Action("SetUint");
        param = new ParameterUint("ValueUint");
		iActionSetUint.addInputParameter(param);

        iActionGetUint = new Action("GetUint");
        param = new ParameterUint("ValueUint");
		iActionGetUint.addOutputParameter(param);

        iActionSetInt = new Action("SetInt");
        param = new ParameterInt("ValueInt");
		iActionSetInt.addInputParameter(param);

        iActionGetInt = new Action("GetInt");
        param = new ParameterInt("ValueInt");
		iActionGetInt.addOutputParameter(param);

        iActionSetBool = new Action("SetBool");
        param = new ParameterBool("ValueBool");
		iActionSetBool.addInputParameter(param);

        iActionGetBool = new Action("GetBool");
        param = new ParameterBool("ValueBool");
		iActionGetBool.addOutputParameter(param);

        iActionSetMultiple = new Action("SetMultiple");
        param = new ParameterUint("ValueUint");
		iActionSetMultiple.addInputParameter(param);
        param = new ParameterInt("ValueInt");
		iActionSetMultiple.addInputParameter(param);
        param = new ParameterBool("ValueBool");
		iActionSetMultiple.addInputParameter(param);

        iActionSetString = new Action("SetString");
        param = new ParameterString("ValueStr", allowedValues);
		iActionSetString.addInputParameter(param);

        iActionGetString = new Action("GetString");
        param = new ParameterString("ValueStr", allowedValues);
		iActionGetString.addOutputParameter(param);

        iActionSetBinary = new Action("SetBinary");
        param = new ParameterBinary("ValueBin");
		iActionSetBinary.addInputParameter(param);

        iActionGetBinary = new Action("GetBinary");
        param = new ParameterBinary("ValueBin");
		iActionGetBinary.addOutputParameter(param);

        iActionToggleBool = new Action("ToggleBool");

        iActionWriteFile = new Action("WriteFile");
        param = new ParameterString("Data", allowedValues);
		iActionWriteFile.addInputParameter(param);
        param = new ParameterString("FileFullName", allowedValues);
		iActionWriteFile.addInputParameter(param);

        iActionShutdown = new Action("Shutdown");

        iVarUintChanged = new PropertyChangeListener();
        iVarUint = new PropertyUint("VarUint", iVarUintChanged);
		addProperty(iVarUint);
        iVarIntChanged = new PropertyChangeListener();
        iVarInt = new PropertyInt("VarInt", iVarIntChanged);
		addProperty(iVarInt);
        iVarBoolChanged = new PropertyChangeListener();
        iVarBool = new PropertyBool("VarBool", iVarBoolChanged);
		addProperty(iVarBool);
        iVarStrChanged = new PropertyChangeListener();
        iVarStr = new PropertyString("VarStr", iVarStrChanged);
		addProperty(iVarStr);
        iVarBinChanged = new PropertyChangeListener();
        iVarBin = new PropertyBinary("VarBin", iVarBinChanged);
		addProperty(iVarBin);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public long syncIncrement(long aValue)
	{
	    SyncIncrementOpenhomeOrgTestBasic1 sync = new SyncIncrementOpenhomeOrgTestBasic1(this);
	    beginIncrement(aValue, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getResult();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endIncrement}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginIncrement(long aValue, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionIncrement, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionIncrement.getInputParameter(inIndex++), aValue));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionIncrement.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginIncrement} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginIncrement} method.
     * @return the result of the previously invoked action.
     */
	public long endIncrement(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        long result = Invocation.getOutputUint(aAsyncHandle, index++);
        return result;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public int syncDecrement(int aValue)
	{
	    SyncDecrementOpenhomeOrgTestBasic1 sync = new SyncDecrementOpenhomeOrgTestBasic1(this);
	    beginDecrement(aValue, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getResult();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endDecrement}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginDecrement(int aValue, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionDecrement, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentInt((ParameterInt)iActionDecrement.getInputParameter(inIndex++), aValue));
        int outIndex = 0;
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionDecrement.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDecrement} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginDecrement} method.
     * @return the result of the previously invoked action.
     */
	public int endDecrement(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        int result = Invocation.getOutputInt(aAsyncHandle, index++);
        return result;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public boolean syncToggle(boolean aValue)
	{
	    SyncToggleOpenhomeOrgTestBasic1 sync = new SyncToggleOpenhomeOrgTestBasic1(this);
	    beginToggle(aValue, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getResult();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endToggle}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginToggle(boolean aValue, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionToggle, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentBool((ParameterBool)iActionToggle.getInputParameter(inIndex++), aValue));
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionToggle.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginToggle} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginToggle} method.
     * @return the result of the previously invoked action.
     */
	public boolean endToggle(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        boolean result = Invocation.getOutputBool(aAsyncHandle, index++);
        return result;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public String syncEchoString(String aValue)
	{
	    SyncEchoStringOpenhomeOrgTestBasic1 sync = new SyncEchoStringOpenhomeOrgTestBasic1(this);
	    beginEchoString(aValue, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getResult();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endEchoString}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginEchoString(String aValue, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionEchoString, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionEchoString.getInputParameter(inIndex++), aValue));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionEchoString.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginEchoString} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginEchoString} method.
     * @return the result of the previously invoked action.
     */
	public String endEchoString(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        return result;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public byte[] syncEchoBinary(byte[] aValue)
	{
	    SyncEchoBinaryOpenhomeOrgTestBasic1 sync = new SyncEchoBinaryOpenhomeOrgTestBasic1(this);
	    beginEchoBinary(aValue, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getResult();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endEchoBinary}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginEchoBinary(byte[] aValue, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionEchoBinary, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentBinary((ParameterBinary)iActionEchoBinary.getInputParameter(inIndex++), aValue));
        int outIndex = 0;
        invocation.addOutput(new ArgumentBinary((ParameterBinary)iActionEchoBinary.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginEchoBinary} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginEchoBinary} method.
     * @return the result of the previously invoked action.
     */
	public byte[] endEchoBinary(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        byte[] result = Invocation.getOutputBinary(aAsyncHandle, index++);
        return result;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncSetUint(long aValueUint)
	{
	    SyncSetUintOpenhomeOrgTestBasic1 sync = new SyncSetUintOpenhomeOrgTestBasic1(this);
	    beginSetUint(aValueUint, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endSetUint}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginSetUint(long aValueUint, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionSetUint, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetUint.getInputParameter(inIndex++), aValueUint));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetUint} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginSetUint} method.
     */
	public void endSetUint(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public long syncGetUint()
	{
	    SyncGetUintOpenhomeOrgTestBasic1 sync = new SyncGetUintOpenhomeOrgTestBasic1(this);
	    beginGetUint(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getValueUint();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endGetUint}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginGetUint(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionGetUint, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetUint.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetUint} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginGetUint} method.
     * @return the result of the previously invoked action.
     */
	public long endGetUint(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        long valueUint = Invocation.getOutputUint(aAsyncHandle, index++);
        return valueUint;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncSetInt(int aValueInt)
	{
	    SyncSetIntOpenhomeOrgTestBasic1 sync = new SyncSetIntOpenhomeOrgTestBasic1(this);
	    beginSetInt(aValueInt, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endSetInt}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginSetInt(int aValueInt, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionSetInt, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentInt((ParameterInt)iActionSetInt.getInputParameter(inIndex++), aValueInt));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetInt} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginSetInt} method.
     */
	public void endSetInt(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public int syncGetInt()
	{
	    SyncGetIntOpenhomeOrgTestBasic1 sync = new SyncGetIntOpenhomeOrgTestBasic1(this);
	    beginGetInt(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getValueInt();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endGetInt}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginGetInt(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionGetInt, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetInt.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetInt} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginGetInt} method.
     * @return the result of the previously invoked action.
     */
	public int endGetInt(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        int valueInt = Invocation.getOutputInt(aAsyncHandle, index++);
        return valueInt;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncSetBool(boolean aValueBool)
	{
	    SyncSetBoolOpenhomeOrgTestBasic1 sync = new SyncSetBoolOpenhomeOrgTestBasic1(this);
	    beginSetBool(aValueBool, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endSetBool}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginSetBool(boolean aValueBool, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionSetBool, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentBool((ParameterBool)iActionSetBool.getInputParameter(inIndex++), aValueBool));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetBool} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginSetBool} method.
     */
	public void endSetBool(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public boolean syncGetBool()
	{
	    SyncGetBoolOpenhomeOrgTestBasic1 sync = new SyncGetBoolOpenhomeOrgTestBasic1(this);
	    beginGetBool(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getValueBool();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endGetBool}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginGetBool(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionGetBool, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionGetBool.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetBool} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginGetBool} method.
     * @return the result of the previously invoked action.
     */
	public boolean endGetBool(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        boolean valueBool = Invocation.getOutputBool(aAsyncHandle, index++);
        return valueBool;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncSetMultiple(long aValueUint, int aValueInt, boolean aValueBool)
	{
	    SyncSetMultipleOpenhomeOrgTestBasic1 sync = new SyncSetMultipleOpenhomeOrgTestBasic1(this);
	    beginSetMultiple(aValueUint, aValueInt, aValueBool, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endSetMultiple}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginSetMultiple(long aValueUint, int aValueInt, boolean aValueBool, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionSetMultiple, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetMultiple.getInputParameter(inIndex++), aValueUint));
        invocation.addInput(new ArgumentInt((ParameterInt)iActionSetMultiple.getInputParameter(inIndex++), aValueInt));
        invocation.addInput(new ArgumentBool((ParameterBool)iActionSetMultiple.getInputParameter(inIndex++), aValueBool));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetMultiple} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginSetMultiple} method.
     */
	public void endSetMultiple(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncSetString(String aValueStr)
	{
	    SyncSetStringOpenhomeOrgTestBasic1 sync = new SyncSetStringOpenhomeOrgTestBasic1(this);
	    beginSetString(aValueStr, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endSetString}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginSetString(String aValueStr, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionSetString, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionSetString.getInputParameter(inIndex++), aValueStr));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetString} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginSetString} method.
     */
	public void endSetString(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public String syncGetString()
	{
	    SyncGetStringOpenhomeOrgTestBasic1 sync = new SyncGetStringOpenhomeOrgTestBasic1(this);
	    beginGetString(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getValueStr();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endGetString}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginGetString(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionGetString, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetString.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetString} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginGetString} method.
     * @return the result of the previously invoked action.
     */
	public String endGetString(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        String valueStr = Invocation.getOutputString(aAsyncHandle, index++);
        return valueStr;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncSetBinary(byte[] aValueBin)
	{
	    SyncSetBinaryOpenhomeOrgTestBasic1 sync = new SyncSetBinaryOpenhomeOrgTestBasic1(this);
	    beginSetBinary(aValueBin, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endSetBinary}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginSetBinary(byte[] aValueBin, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionSetBinary, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentBinary((ParameterBinary)iActionSetBinary.getInputParameter(inIndex++), aValueBin));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetBinary} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginSetBinary} method.
     */
	public void endSetBinary(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public byte[] syncGetBinary()
	{
	    SyncGetBinaryOpenhomeOrgTestBasic1 sync = new SyncGetBinaryOpenhomeOrgTestBasic1(this);
	    beginGetBinary(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getValueBin();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endGetBinary}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginGetBinary(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionGetBinary, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBinary((ParameterBinary)iActionGetBinary.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetBinary} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginGetBinary} method.
     * @return the result of the previously invoked action.
     */
	public byte[] endGetBinary(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        byte[] valueBin = Invocation.getOutputBinary(aAsyncHandle, index++);
        return valueBin;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncToggleBool()
	{
	    SyncToggleBoolOpenhomeOrgTestBasic1 sync = new SyncToggleBoolOpenhomeOrgTestBasic1(this);
	    beginToggleBool(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endToggleBool}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginToggleBool(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionToggleBool, aCallback);
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginToggleBool} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginToggleBool} method.
     */
	public void endToggleBool(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncWriteFile(String aData, String aFileFullName)
	{
	    SyncWriteFileOpenhomeOrgTestBasic1 sync = new SyncWriteFileOpenhomeOrgTestBasic1(this);
	    beginWriteFile(aData, aFileFullName, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endWriteFile}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginWriteFile(String aData, String aFileFullName, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionWriteFile, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionWriteFile.getInputParameter(inIndex++), aData));
        invocation.addInput(new ArgumentString((ParameterString)iActionWriteFile.getInputParameter(inIndex++), aFileFullName));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginWriteFile} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginWriteFile} method.
     */
	public void endWriteFile(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncShutdown()
	{
	    SyncShutdownOpenhomeOrgTestBasic1 sync = new SyncShutdownOpenhomeOrgTestBasic1(this);
	    beginShutdown(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endShutdown}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginShutdown(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionShutdown, aCallback);
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginShutdown} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginShutdown} method.
     */
	public void endShutdown(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Set a delegate to be run when the VarUint state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param aVarUintChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyVarUintChanged(IPropertyChangeListener aVarUintChanged)
    {
        synchronized (iPropertyLock)
        {
            iVarUintChanged = aVarUintChanged;
        }
    }

    private void varUintPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iVarUintChanged);
        }
    }
    /**
     * Set a delegate to be run when the VarInt state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param aVarIntChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyVarIntChanged(IPropertyChangeListener aVarIntChanged)
    {
        synchronized (iPropertyLock)
        {
            iVarIntChanged = aVarIntChanged;
        }
    }

    private void varIntPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iVarIntChanged);
        }
    }
    /**
     * Set a delegate to be run when the VarBool state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param aVarBoolChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyVarBoolChanged(IPropertyChangeListener aVarBoolChanged)
    {
        synchronized (iPropertyLock)
        {
            iVarBoolChanged = aVarBoolChanged;
        }
    }

    private void varBoolPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iVarBoolChanged);
        }
    }
    /**
     * Set a delegate to be run when the VarStr state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param aVarStrChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyVarStrChanged(IPropertyChangeListener aVarStrChanged)
    {
        synchronized (iPropertyLock)
        {
            iVarStrChanged = aVarStrChanged;
        }
    }

    private void varStrPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iVarStrChanged);
        }
    }
    /**
     * Set a delegate to be run when the VarBin state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyOpenhomeOrgTestBasic1 instance will not overlap.
     *
     * @param aVarBinChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyVarBinChanged(IPropertyChangeListener aVarBinChanged)
    {
        synchronized (iPropertyLock)
        {
            iVarBinChanged = aVarBinChanged;
        }
    }

    private void varBinPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iVarBinChanged);
        }
    }

    /**
     * Query the value of the VarUint property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the VarUint property.
     */
    public long getPropertyVarUint()
    {
        propertyReadLock();
        long val = iVarUint.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the VarInt property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the VarInt property.
     */
    public int getPropertyVarInt()
    {
        propertyReadLock();
        int val = iVarInt.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the VarBool property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the VarBool property.
     */
    public boolean getPropertyVarBool()
    {
        propertyReadLock();
        boolean val = iVarBool.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the VarStr property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the VarStr property.
     */
    public String getPropertyVarStr()
    {
        propertyReadLock();
        String val = iVarStr.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the VarBin property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the VarBin property.
     */
    public byte[] getPropertyVarBin()
    {
        propertyReadLock();
        byte[] val = iVarBin.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Dispose of this control point proxy.
     * Must be called for each class instance.  Must be called before {@code
     * Library.close()}.
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            disposeProxy();
            iHandle = 0;
            iActionIncrement.destroy();
            iActionDecrement.destroy();
            iActionToggle.destroy();
            iActionEchoString.destroy();
            iActionEchoBinary.destroy();
            iActionSetUint.destroy();
            iActionGetUint.destroy();
            iActionSetInt.destroy();
            iActionGetInt.destroy();
            iActionSetBool.destroy();
            iActionGetBool.destroy();
            iActionSetMultiple.destroy();
            iActionSetString.destroy();
            iActionGetString.destroy();
            iActionSetBinary.destroy();
            iActionGetBinary.destroy();
            iActionToggleBool.destroy();
            iActionWriteFile.destroy();
            iActionShutdown.destroy();
            iVarUint.destroy();
            iVarInt.destroy();
            iVarBool.destroy();
            iVarStr.destroy();
            iVarBin.destroy();
        }
    }
}

