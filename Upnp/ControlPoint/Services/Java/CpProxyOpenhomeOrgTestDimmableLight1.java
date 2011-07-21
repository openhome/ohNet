package openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import ohnet.*;
import openhome.net.controlpoint.*;
import openhome.net.controlpoint.proxies.*;
import openhome.net.controlpoint.proxies.CpProxyOpenhomeOrgTestDimmableLight1.*;
import openhome.net.core.*;

	
interface ICpProxyOpenhomeOrgTestDimmableLight1 extends ICpProxy
{
    public long syncGetLevel();
    public void beginGetLevel(ICpProxyListener aCallback);
    public long endGetLevel(long aAsyncHandle);
    public void syncSetLevel(long aLevel);
    public void beginSetLevel(long aLevel, ICpProxyListener aCallback);
    public void endSetLevel(long aAsyncHandle);
    public void setPropertyA_ARG_LevelChanged(IPropertyChangeListener aA_ARG_LevelChanged);
    public long getPropertyA_ARG_Level();
}

class SyncGetLevelOpenhomeOrgTestDimmableLight1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestDimmableLight1 iService;
    private long iLevel;

    public SyncGetLevelOpenhomeOrgTestDimmableLight1(CpProxyOpenhomeOrgTestDimmableLight1 aProxy)
    {
        iService = aProxy;
    }
    public long getLevel()
    {
        return iLevel;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetLevel(aAsyncHandle);
		
        iLevel = result;
    }
}

class SyncSetLevelOpenhomeOrgTestDimmableLight1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestDimmableLight1 iService;

    public SyncSetLevelOpenhomeOrgTestDimmableLight1(CpProxyOpenhomeOrgTestDimmableLight1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetLevel(aAsyncHandle);
		
    }
}

/**
 * Proxy for the openhome.org:TestDimmableLight:1 UPnP service
 */
public class CpProxyOpenhomeOrgTestDimmableLight1 extends CpProxy implements ICpProxyOpenhomeOrgTestDimmableLight1
{

    private Action iActionGetLevel;
    private Action iActionSetLevel;
    private PropertyUint iA_ARG_Level;
    private IPropertyChangeListener iA_ARG_LevelChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@code #subscribe}/{@code #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice	the device to use.
     */

    public CpProxyOpenhomeOrgTestDimmableLight1(CpDevice aDevice)
    {
        super("openhome-org", "TestDimmableLight", 1, aDevice);
        Parameter param;
        

        iActionGetLevel = new Action("GetLevel");
        param = new ParameterUint("Level");
		iActionGetLevel.addOutputParameter(param);

        iActionSetLevel = new Action("SetLevel");
        param = new ParameterUint("Level");
		iActionSetLevel.addInputParameter(param);

        iA_ARG_LevelChanged = new PropertyChangeListener();
        iA_ARG_Level = new PropertyUint("A_ARG_Level", iA_ARG_LevelChanged);
		addProperty(iA_ARG_Level);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public long syncGetLevel()
	{
	    SyncGetLevelOpenhomeOrgTestDimmableLight1 sync = new SyncGetLevelOpenhomeOrgTestDimmableLight1(this);
	    beginGetLevel(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getLevel();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endGetLevel}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginGetLevel(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionGetLevel, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetLevel.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetLevel} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginGetLevel} method.
     * @return the result of the previously invoked action.
     */
	public long endGetLevel(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        long level = Invocation.getOutputUint(aAsyncHandle, index++);
        return level;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncSetLevel(long aLevel)
	{
	    SyncSetLevelOpenhomeOrgTestDimmableLight1 sync = new SyncSetLevelOpenhomeOrgTestDimmableLight1(this);
	    beginSetLevel(aLevel, sync.getListener());
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
	 * calling {@link #endSetLevel}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginSetLevel(long aLevel, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionSetLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetLevel.getInputParameter(inIndex++), aLevel));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetLevel} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginSetLevel} method.
     */
	public void endSetLevel(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Set a delegate to be run when the A_ARG_Level state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyOpenhomeOrgTestDimmableLight1 instance will not overlap.
     *
     * @param aA_ARG_LevelChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyA_ARG_LevelChanged(IPropertyChangeListener aA_ARG_LevelChanged)
    {
        synchronized (iPropertyLock)
        {
            iA_ARG_LevelChanged = aA_ARG_LevelChanged;
        }
    }

    private void a_ARG_LevelPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iA_ARG_LevelChanged);
        }
    }

    /**
     * Query the value of the A_ARG_Level property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the A_ARG_Level property.
     */
    public long getPropertyA_ARG_Level()
    {
        propertyReadLock();
        long val = iA_ARG_Level.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Dispose of this control point proxy.
     * Must be called for each class instance.  Must be called before {@link
     * #openhome.net.core.library.close}.
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
            iActionGetLevel.destroy();
            iActionSetLevel.destroy();
            iA_ARG_Level.destroy();
        }
    }
}

