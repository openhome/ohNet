package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgNetworkMonitor1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgNetworkMonitor1 extends ICpProxy
{
    public String syncName();
    public void beginName(ICpProxyListener aCallback);
    public String endName(long aAsyncHandle);
    public Ports syncPorts();
    public void beginPorts(ICpProxyListener aCallback);
    public Ports endPorts(long aAsyncHandle);
    public void setPropertyNameChanged(IPropertyChangeListener aNameChanged);
    public String getPropertyName();
    public void setPropertySenderChanged(IPropertyChangeListener aSenderChanged);
    public long getPropertySender();
    public void setPropertyReceiverChanged(IPropertyChangeListener aReceiverChanged);
    public long getPropertyReceiver();
    public void setPropertyResultsChanged(IPropertyChangeListener aResultsChanged);
    public long getPropertyResults();
}

class SyncNameAvOpenhomeOrgNetworkMonitor1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgNetworkMonitor1 iService;
    private String iName;

    public SyncNameAvOpenhomeOrgNetworkMonitor1(CpProxyAvOpenhomeOrgNetworkMonitor1 aProxy)
    {
        iService = aProxy;
    }
    public String getName()
    {
        return iName;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endName(aAsyncHandle);
        
        iName = result;
    }
}

class SyncPortsAvOpenhomeOrgNetworkMonitor1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgNetworkMonitor1 iService;
    private long iSender;
    private long iReceiver;
    private long iResults;

    public SyncPortsAvOpenhomeOrgNetworkMonitor1(CpProxyAvOpenhomeOrgNetworkMonitor1 aProxy)
    {
        iService = aProxy;
    }
    public long getSender()
    {
        return iSender;
    }
    public long getReceiver()
    {
        return iReceiver;
    }
    public long getResults()
    {
        return iResults;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        Ports result = iService.endPorts(aAsyncHandle);
        
        iSender = result.getSender();
        iReceiver = result.getReceiver();
        iResults = result.getResults();
    }
}

/**
 * Proxy for the av.openhome.org:NetworkMonitor:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgNetworkMonitor1 extends CpProxy implements ICpProxyAvOpenhomeOrgNetworkMonitor1
{

    public class Ports
    {
        private long iSender;
        private long iReceiver;
        private long iResults;

        public Ports(
            long aSender,
            long aReceiver,
            long aResults
        )
        {
            iSender = aSender;
            iReceiver = aReceiver;
            iResults = aResults;
        }
        public long getSender()
        {
            return iSender;
        }
        public long getReceiver()
        {
            return iReceiver;
        }
        public long getResults()
        {
            return iResults;
        }
    }

    private Action iActionName;
    private Action iActionPorts;
    private PropertyString iName;
    private PropertyUint iSender;
    private PropertyUint iReceiver;
    private PropertyUint iResults;
    private IPropertyChangeListener iNameChanged;
    private IPropertyChangeListener iSenderChanged;
    private IPropertyChangeListener iReceiverChanged;
    private IPropertyChangeListener iResultsChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgNetworkMonitor1(CpDevice aDevice)
    {
        super("av-openhome-org", "NetworkMonitor", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionName = new Action("Name");
        param = new ParameterString("Name", allowedValues);
        iActionName.addOutputParameter(param);

        iActionPorts = new Action("Ports");
        param = new ParameterUint("Sender");
        iActionPorts.addOutputParameter(param);
        param = new ParameterUint("Receiver");
        iActionPorts.addOutputParameter(param);
        param = new ParameterUint("Results");
        iActionPorts.addOutputParameter(param);

        iNameChanged = new PropertyChangeListener();
        iName = new PropertyString("Name",
            new PropertyChangeListener() {
                public void notifyChange() {
                    namePropertyChanged();
                }
            }
        );
        addProperty(iName);
        iSenderChanged = new PropertyChangeListener();
        iSender = new PropertyUint("Sender",
            new PropertyChangeListener() {
                public void notifyChange() {
                    senderPropertyChanged();
                }
            }
        );
        addProperty(iSender);
        iReceiverChanged = new PropertyChangeListener();
        iReceiver = new PropertyUint("Receiver",
            new PropertyChangeListener() {
                public void notifyChange() {
                    receiverPropertyChanged();
                }
            }
        );
        addProperty(iReceiver);
        iResultsChanged = new PropertyChangeListener();
        iResults = new PropertyUint("Results",
            new PropertyChangeListener() {
                public void notifyChange() {
                    resultsPropertyChanged();
                }
            }
        );
        addProperty(iResults);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncName()
    {
        SyncNameAvOpenhomeOrgNetworkMonitor1 sync = new SyncNameAvOpenhomeOrgNetworkMonitor1(this);
        beginName(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getName();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endName}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginName(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionName, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionName.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginName} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginName} method.
     * @return the result of the previously invoked action.
     */
    public String endName(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String name = Invocation.getOutputString(aAsyncHandle, index++);
        return name;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Ports syncPorts()
    {
        SyncPortsAvOpenhomeOrgNetworkMonitor1 sync = new SyncPortsAvOpenhomeOrgNetworkMonitor1(this);
        beginPorts(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Ports(
            sync.getSender(),
            sync.getReceiver(),
            sync.getResults()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPorts}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPorts(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPorts, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionPorts.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionPorts.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionPorts.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPorts} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginPorts} method.
     * @return the result of the previously invoked action.
     */
    public Ports endPorts(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long sender = Invocation.getOutputUint(aAsyncHandle, index++);
        long receiver = Invocation.getOutputUint(aAsyncHandle, index++);
        long results = Invocation.getOutputUint(aAsyncHandle, index++);
        return new Ports(
            sender,
            receiver,
            results
        );
    }
        
    /**
     * Set a delegate to be run when the Name state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.
     *
     * @param aNameChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyNameChanged(IPropertyChangeListener aNameChanged)
    {
        synchronized (iPropertyLock)
        {
            iNameChanged = aNameChanged;
        }
    }

    private void namePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iNameChanged);
        }
    }
    /**
     * Set a delegate to be run when the Sender state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.
     *
     * @param aSenderChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySenderChanged(IPropertyChangeListener aSenderChanged)
    {
        synchronized (iPropertyLock)
        {
            iSenderChanged = aSenderChanged;
        }
    }

    private void senderPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSenderChanged);
        }
    }
    /**
     * Set a delegate to be run when the Receiver state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.
     *
     * @param aReceiverChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyReceiverChanged(IPropertyChangeListener aReceiverChanged)
    {
        synchronized (iPropertyLock)
        {
            iReceiverChanged = aReceiverChanged;
        }
    }

    private void receiverPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iReceiverChanged);
        }
    }
    /**
     * Set a delegate to be run when the Results state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgNetworkMonitor1 instance will not overlap.
     *
     * @param aResultsChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyResultsChanged(IPropertyChangeListener aResultsChanged)
    {
        synchronized (iPropertyLock)
        {
            iResultsChanged = aResultsChanged;
        }
    }

    private void resultsPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iResultsChanged);
        }
    }

    /**
     * Query the value of the Name property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Name property.
     */
    public String getPropertyName()
    {
        propertyReadLock();
        String val = iName.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Sender property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Sender property.
     */
    public long getPropertySender()
    {
        propertyReadLock();
        long val = iSender.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Receiver property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Receiver property.
     */
    public long getPropertyReceiver()
    {
        propertyReadLock();
        long val = iReceiver.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Results property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Results property.
     */
    public long getPropertyResults()
    {
        propertyReadLock();
        long val = iResults.getValue();
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
            iActionName.destroy();
            iActionPorts.destroy();
            iName.destroy();
            iSender.destroy();
            iReceiver.destroy();
            iResults.destroy();
        }
    }
}

