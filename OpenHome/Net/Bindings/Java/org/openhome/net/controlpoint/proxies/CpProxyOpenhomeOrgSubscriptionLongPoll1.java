package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyOpenhomeOrgSubscriptionLongPoll1.*;
import org.openhome.net.core.*;

    
interface ICpProxyOpenhomeOrgSubscriptionLongPoll1 extends ICpProxy
{
    public Subscribe syncSubscribe(String aClientId, String aUdn, String aService, long aRequestedDuration);
    public void beginSubscribe(String aClientId, String aUdn, String aService, long aRequestedDuration, ICpProxyListener aCallback);
    public Subscribe endSubscribe(long aAsyncHandle);
    public void syncUnsubscribe(String aSid);
    public void beginUnsubscribe(String aSid, ICpProxyListener aCallback);
    public void endUnsubscribe(long aAsyncHandle);
    public long syncRenew(String aSid, long aRequestedDuration);
    public void beginRenew(String aSid, long aRequestedDuration, ICpProxyListener aCallback);
    public long endRenew(long aAsyncHandle);
    public String syncGetPropertyUpdates(String aClientId);
    public void beginGetPropertyUpdates(String aClientId, ICpProxyListener aCallback);
    public String endGetPropertyUpdates(long aAsyncHandle);
}

class SyncSubscribeOpenhomeOrgSubscriptionLongPoll1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgSubscriptionLongPoll1 iService;
    private String iSid;
    private long iDuration;

    public SyncSubscribeOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1 aProxy)
    {
        iService = aProxy;
    }
    public String getSid()
    {
        return iSid;
    }
    public long getDuration()
    {
        return iDuration;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        Subscribe result = iService.endSubscribe(aAsyncHandle);
        
        iSid = result.getSid();
        iDuration = result.getDuration();
    }
}

class SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgSubscriptionLongPoll1 iService;

    public SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endUnsubscribe(aAsyncHandle);
        
    }
}

class SyncRenewOpenhomeOrgSubscriptionLongPoll1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgSubscriptionLongPoll1 iService;
    private long iDuration;

    public SyncRenewOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1 aProxy)
    {
        iService = aProxy;
    }
    public long getDuration()
    {
        return iDuration;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endRenew(aAsyncHandle);
        
        iDuration = result;
    }
}

class SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgSubscriptionLongPoll1 iService;
    private String iUpdates;

    public SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1 aProxy)
    {
        iService = aProxy;
    }
    public String getUpdates()
    {
        return iUpdates;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetPropertyUpdates(aAsyncHandle);
        
        iUpdates = result;
    }
}

/**
 * Proxy for the openhome.org:SubscriptionLongPoll:1 UPnP service
 */
public class CpProxyOpenhomeOrgSubscriptionLongPoll1 extends CpProxy implements ICpProxyOpenhomeOrgSubscriptionLongPoll1
{

    public class Subscribe
    {
        private String iSid;
        private long iDuration;

        public Subscribe(
            String aSid,
            long aDuration
        )
        {
            iSid = aSid;
            iDuration = aDuration;
        }
        public String getSid()
        {
            return iSid;
        }
        public long getDuration()
        {
            return iDuration;
        }
    }

    private Action iActionSubscribe;
    private Action iActionUnsubscribe;
    private Action iActionRenew;
    private Action iActionGetPropertyUpdates;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyOpenhomeOrgSubscriptionLongPoll1(CpDevice aDevice)
    {
        super("openhome-org", "SubscriptionLongPoll", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionSubscribe = new Action("Subscribe");
        param = new ParameterString("ClientId", allowedValues);
        iActionSubscribe.addInputParameter(param);
        param = new ParameterString("Udn", allowedValues);
        iActionSubscribe.addInputParameter(param);
        param = new ParameterString("Service", allowedValues);
        iActionSubscribe.addInputParameter(param);
        param = new ParameterUint("RequestedDuration");
        iActionSubscribe.addInputParameter(param);
        param = new ParameterString("Sid", allowedValues);
        iActionSubscribe.addOutputParameter(param);
        param = new ParameterUint("Duration");
        iActionSubscribe.addOutputParameter(param);

        iActionUnsubscribe = new Action("Unsubscribe");
        param = new ParameterString("Sid", allowedValues);
        iActionUnsubscribe.addInputParameter(param);

        iActionRenew = new Action("Renew");
        param = new ParameterString("Sid", allowedValues);
        iActionRenew.addInputParameter(param);
        param = new ParameterUint("RequestedDuration");
        iActionRenew.addInputParameter(param);
        param = new ParameterUint("Duration");
        iActionRenew.addOutputParameter(param);

        iActionGetPropertyUpdates = new Action("GetPropertyUpdates");
        param = new ParameterString("ClientId", allowedValues);
        iActionGetPropertyUpdates.addInputParameter(param);
        param = new ParameterString("Updates", allowedValues);
        iActionGetPropertyUpdates.addOutputParameter(param);
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Subscribe syncSubscribe(String aClientId, String aUdn, String aService, long aRequestedDuration)
    {
        SyncSubscribeOpenhomeOrgSubscriptionLongPoll1 sync = new SyncSubscribeOpenhomeOrgSubscriptionLongPoll1(this);
        beginSubscribe(aClientId, aUdn, aService, aRequestedDuration, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Subscribe(
            sync.getSid(),
            sync.getDuration()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSubscribe}.
     * 
     * @param aClientId
     * @param aUdn
     * @param aService
     * @param aRequestedDuration
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSubscribe(String aClientId, String aUdn, String aService, long aRequestedDuration, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSubscribe, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionSubscribe.getInputParameter(inIndex++), aClientId));
        invocation.addInput(new ArgumentString((ParameterString)iActionSubscribe.getInputParameter(inIndex++), aUdn));
        invocation.addInput(new ArgumentString((ParameterString)iActionSubscribe.getInputParameter(inIndex++), aService));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSubscribe.getInputParameter(inIndex++), aRequestedDuration));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionSubscribe.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionSubscribe.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSubscribe} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSubscribe} method.
     * @return the result of the previously invoked action.
     */
    public Subscribe endSubscribe(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String sid = Invocation.getOutputString(aAsyncHandle, index++);
        long duration = Invocation.getOutputUint(aAsyncHandle, index++);
        return new Subscribe(
            sid,
            duration
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncUnsubscribe(String aSid)
    {
        SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1 sync = new SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1(this);
        beginUnsubscribe(aSid, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endUnsubscribe}.
     * 
     * @param aSid
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginUnsubscribe(String aSid, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionUnsubscribe, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionUnsubscribe.getInputParameter(inIndex++), aSid));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginUnsubscribe} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginUnsubscribe} method.
     */
    public void endUnsubscribe(long aAsyncHandle)
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
    public long syncRenew(String aSid, long aRequestedDuration)
    {
        SyncRenewOpenhomeOrgSubscriptionLongPoll1 sync = new SyncRenewOpenhomeOrgSubscriptionLongPoll1(this);
        beginRenew(aSid, aRequestedDuration, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getDuration();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endRenew}.
     * 
     * @param aSid
     * @param aRequestedDuration
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginRenew(String aSid, long aRequestedDuration, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionRenew, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionRenew.getInputParameter(inIndex++), aSid));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionRenew.getInputParameter(inIndex++), aRequestedDuration));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionRenew.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginRenew} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginRenew} method.
     * @return the result of the previously invoked action.
     */
    public long endRenew(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long duration = Invocation.getOutputUint(aAsyncHandle, index++);
        return duration;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetPropertyUpdates(String aClientId)
    {
        SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1 sync = new SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1(this);
        beginGetPropertyUpdates(aClientId, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getUpdates();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetPropertyUpdates}.
     * 
     * @param aClientId
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetPropertyUpdates(String aClientId, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetPropertyUpdates, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionGetPropertyUpdates.getInputParameter(inIndex++), aClientId));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetPropertyUpdates.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetPropertyUpdates} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetPropertyUpdates} method.
     * @return the result of the previously invoked action.
     */
    public String endGetPropertyUpdates(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String updates = Invocation.getOutputString(aAsyncHandle, index++);
        return updates;
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
            iActionSubscribe.destroy();
            iActionUnsubscribe.destroy();
            iActionRenew.destroy();
            iActionGetPropertyUpdates.destroy();
        }
    }
}

