package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgSwitchPower1.*;
import org.openhome.net.core.*;

    
interface ICpProxyUpnpOrgSwitchPower1 extends ICpProxy
{
    public void syncSetTarget(boolean aNewTargetValue);
    public void beginSetTarget(boolean aNewTargetValue, ICpProxyListener aCallback);
    public void endSetTarget(long aAsyncHandle);
    public boolean syncGetTarget();
    public void beginGetTarget(ICpProxyListener aCallback);
    public boolean endGetTarget(long aAsyncHandle);
    public boolean syncGetStatus();
    public void beginGetStatus(ICpProxyListener aCallback);
    public boolean endGetStatus(long aAsyncHandle);
    public void setPropertyStatusChanged(IPropertyChangeListener aStatusChanged);
    public boolean getPropertyStatus();
}

class SyncSetTargetUpnpOrgSwitchPower1 extends SyncProxyAction
{
    private CpProxyUpnpOrgSwitchPower1 iService;

    public SyncSetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetTarget(aAsyncHandle);
        
    }
}

class SyncGetTargetUpnpOrgSwitchPower1 extends SyncProxyAction
{
    private CpProxyUpnpOrgSwitchPower1 iService;
    private boolean iRetTargetValue;

    public SyncGetTargetUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getRetTargetValue()
    {
        return iRetTargetValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endGetTarget(aAsyncHandle);
        
        iRetTargetValue = result;
    }
}

class SyncGetStatusUpnpOrgSwitchPower1 extends SyncProxyAction
{
    private CpProxyUpnpOrgSwitchPower1 iService;
    private boolean iResultStatus;

    public SyncGetStatusUpnpOrgSwitchPower1(CpProxyUpnpOrgSwitchPower1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getResultStatus()
    {
        return iResultStatus;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endGetStatus(aAsyncHandle);
        
        iResultStatus = result;
    }
}

/**
 * Proxy for the upnp.org:SwitchPower:1 UPnP service
 */
public class CpProxyUpnpOrgSwitchPower1 extends CpProxy implements ICpProxyUpnpOrgSwitchPower1
{

    private Action iActionSetTarget;
    private Action iActionGetTarget;
    private Action iActionGetStatus;
    private PropertyBool iStatus;
    private IPropertyChangeListener iStatusChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyUpnpOrgSwitchPower1(CpDevice aDevice)
    {
        super("schemas-upnp-org", "SwitchPower", 1, aDevice);
        Parameter param;
        

        iActionSetTarget = new Action("SetTarget");
        param = new ParameterBool("newTargetValue");
        iActionSetTarget.addInputParameter(param);

        iActionGetTarget = new Action("GetTarget");
        param = new ParameterBool("RetTargetValue");
        iActionGetTarget.addOutputParameter(param);

        iActionGetStatus = new Action("GetStatus");
        param = new ParameterBool("ResultStatus");
        iActionGetStatus.addOutputParameter(param);

        iStatusChanged = new PropertyChangeListener();
        iStatus = new PropertyBool("Status",
            new PropertyChangeListener() {
                public void notifyChange() {
                    statusPropertyChanged();
                }
            }
        );
        addProperty(iStatus);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetTarget(boolean aNewTargetValue)
    {
        SyncSetTargetUpnpOrgSwitchPower1 sync = new SyncSetTargetUpnpOrgSwitchPower1(this);
        beginSetTarget(aNewTargetValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetTarget}.
     * 
     * @param aNewTargetValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetTarget(boolean aNewTargetValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetTarget, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentBool((ParameterBool)iActionSetTarget.getInputParameter(inIndex++), aNewTargetValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetTarget} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetTarget} method.
     */
    public void endSetTarget(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public boolean syncGetTarget()
    {
        SyncGetTargetUpnpOrgSwitchPower1 sync = new SyncGetTargetUpnpOrgSwitchPower1(this);
        beginGetTarget(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getRetTargetValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetTarget}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetTarget(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetTarget, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionGetTarget.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetTarget} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetTarget} method.
     * @return the result of the previously invoked action.
     */
    public boolean endGetTarget(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        boolean retTargetValue = Invocation.getOutputBool(aAsyncHandle, index++);
        return retTargetValue;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public boolean syncGetStatus()
    {
        SyncGetStatusUpnpOrgSwitchPower1 sync = new SyncGetStatusUpnpOrgSwitchPower1(this);
        beginGetStatus(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getResultStatus();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetStatus}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetStatus(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetStatus, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionGetStatus.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetStatus} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetStatus} method.
     * @return the result of the previously invoked action.
     */
    public boolean endGetStatus(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        boolean resultStatus = Invocation.getOutputBool(aAsyncHandle, index++);
        return resultStatus;
    }
        
    /**
     * Set a delegate to be run when the Status state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgSwitchPower1 instance will not overlap.
     *
     * @param aStatusChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyStatusChanged(IPropertyChangeListener aStatusChanged)
    {
        synchronized (iPropertyLock)
        {
            iStatusChanged = aStatusChanged;
        }
    }

    private void statusPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iStatusChanged);
        }
    }

    /**
     * Query the value of the Status property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Status property.
     */
    public boolean getPropertyStatus()
    {
        propertyReadLock();
        boolean val = iStatus.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Dispose of this control point proxy.
     * Must be called for each class instance.
     * Must be called before <tt>Library.close()</tt>.
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
            iActionSetTarget.destroy();
            iActionGetTarget.destroy();
            iActionGetStatus.destroy();
            iStatus.destroy();
        }
    }
}

