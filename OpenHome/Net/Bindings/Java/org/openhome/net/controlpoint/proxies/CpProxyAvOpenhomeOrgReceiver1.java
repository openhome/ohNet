package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgReceiver1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgReceiver1 extends ICpProxy
{
    public void syncPlay();
    public void beginPlay(ICpProxyListener aCallback);
    public void endPlay(long aAsyncHandle);
    public void syncStop();
    public void beginStop(ICpProxyListener aCallback);
    public void endStop(long aAsyncHandle);
    public void syncSetSender(String aUri, String aMetadata);
    public void beginSetSender(String aUri, String aMetadata, ICpProxyListener aCallback);
    public void endSetSender(long aAsyncHandle);
    public Sender syncSender();
    public void beginSender(ICpProxyListener aCallback);
    public Sender endSender(long aAsyncHandle);
    public String syncProtocolInfo();
    public void beginProtocolInfo(ICpProxyListener aCallback);
    public String endProtocolInfo(long aAsyncHandle);
    public String syncTransportState();
    public void beginTransportState(ICpProxyListener aCallback);
    public String endTransportState(long aAsyncHandle);
    public void setPropertyUriChanged(IPropertyChangeListener aUriChanged);
    public String getPropertyUri();
    public void setPropertyMetadataChanged(IPropertyChangeListener aMetadataChanged);
    public String getPropertyMetadata();
    public void setPropertyTransportStateChanged(IPropertyChangeListener aTransportStateChanged);
    public String getPropertyTransportState();
    public void setPropertyProtocolInfoChanged(IPropertyChangeListener aProtocolInfoChanged);
    public String getPropertyProtocolInfo();
}

class SyncPlayAvOpenhomeOrgReceiver1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgReceiver1 iService;

    public SyncPlayAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPlay(aAsyncHandle);
        
    }
}

class SyncStopAvOpenhomeOrgReceiver1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgReceiver1 iService;

    public SyncStopAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStop(aAsyncHandle);
        
    }
}

class SyncSetSenderAvOpenhomeOrgReceiver1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgReceiver1 iService;

    public SyncSetSenderAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetSender(aAsyncHandle);
        
    }
}

class SyncSenderAvOpenhomeOrgReceiver1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgReceiver1 iService;
    private String iUri;
    private String iMetadata;

    public SyncSenderAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1 aProxy)
    {
        iService = aProxy;
    }
    public String getUri()
    {
        return iUri;
    }
    public String getMetadata()
    {
        return iMetadata;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        Sender result = iService.endSender(aAsyncHandle);
        
        iUri = result.getUri();
        iMetadata = result.getMetadata();
    }
}

class SyncProtocolInfoAvOpenhomeOrgReceiver1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgReceiver1 iService;
    private String iValue;

    public SyncProtocolInfoAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endProtocolInfo(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncTransportStateAvOpenhomeOrgReceiver1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgReceiver1 iService;
    private String iValue;

    public SyncTransportStateAvOpenhomeOrgReceiver1(CpProxyAvOpenhomeOrgReceiver1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endTransportState(aAsyncHandle);
        
        iValue = result;
    }
}

/**
 * Proxy for the av.openhome.org:Receiver:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgReceiver1 extends CpProxy implements ICpProxyAvOpenhomeOrgReceiver1
{

    public class Sender
    {
        private String iUri;
        private String iMetadata;

        public Sender(
            String aUri,
            String aMetadata
        )
        {
            iUri = aUri;
            iMetadata = aMetadata;
        }
        public String getUri()
        {
            return iUri;
        }
        public String getMetadata()
        {
            return iMetadata;
        }
    }

    private Action iActionPlay;
    private Action iActionStop;
    private Action iActionSetSender;
    private Action iActionSender;
    private Action iActionProtocolInfo;
    private Action iActionTransportState;
    private PropertyString iUri;
    private PropertyString iMetadata;
    private PropertyString iTransportState;
    private PropertyString iProtocolInfo;
    private IPropertyChangeListener iUriChanged;
    private IPropertyChangeListener iMetadataChanged;
    private IPropertyChangeListener iTransportStateChanged;
    private IPropertyChangeListener iProtocolInfoChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgReceiver1(CpDevice aDevice)
    {
        super("av-openhome-org", "Receiver", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionPlay = new Action("Play");

        iActionStop = new Action("Stop");

        iActionSetSender = new Action("SetSender");
        param = new ParameterString("Uri", allowedValues);
        iActionSetSender.addInputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
        iActionSetSender.addInputParameter(param);

        iActionSender = new Action("Sender");
        param = new ParameterString("Uri", allowedValues);
        iActionSender.addOutputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
        iActionSender.addOutputParameter(param);

        iActionProtocolInfo = new Action("ProtocolInfo");
        param = new ParameterString("Value", allowedValues);
        iActionProtocolInfo.addOutputParameter(param);

        iActionTransportState = new Action("TransportState");
        allowedValues.add("Stopped");
        allowedValues.add("Playing");
        allowedValues.add("Waiting");
        allowedValues.add("Buffering");
        param = new ParameterString("Value", allowedValues);
        iActionTransportState.addOutputParameter(param);
        allowedValues.clear();

        iUriChanged = new PropertyChangeListener();
        iUri = new PropertyString("Uri",
            new PropertyChangeListener() {
                public void notifyChange() {
                    uriPropertyChanged();
                }
            }
        );
        addProperty(iUri);
        iMetadataChanged = new PropertyChangeListener();
        iMetadata = new PropertyString("Metadata",
            new PropertyChangeListener() {
                public void notifyChange() {
                    metadataPropertyChanged();
                }
            }
        );
        addProperty(iMetadata);
        iTransportStateChanged = new PropertyChangeListener();
        iTransportState = new PropertyString("TransportState",
            new PropertyChangeListener() {
                public void notifyChange() {
                    transportStatePropertyChanged();
                }
            }
        );
        addProperty(iTransportState);
        iProtocolInfoChanged = new PropertyChangeListener();
        iProtocolInfo = new PropertyString("ProtocolInfo",
            new PropertyChangeListener() {
                public void notifyChange() {
                    protocolInfoPropertyChanged();
                }
            }
        );
        addProperty(iProtocolInfo);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncPlay()
    {
        SyncPlayAvOpenhomeOrgReceiver1 sync = new SyncPlayAvOpenhomeOrgReceiver1(this);
        beginPlay(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPlay}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPlay(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPlay, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlay} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginPlay} method.
     */
    public void endPlay(long aAsyncHandle)
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
     */
    public void syncStop()
    {
        SyncStopAvOpenhomeOrgReceiver1 sync = new SyncStopAvOpenhomeOrgReceiver1(this);
        beginStop(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStop}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStop(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStop, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStop} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStop} method.
     */
    public void endStop(long aAsyncHandle)
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
     */
    public void syncSetSender(String aUri, String aMetadata)
    {
        SyncSetSenderAvOpenhomeOrgReceiver1 sync = new SyncSetSenderAvOpenhomeOrgReceiver1(this);
        beginSetSender(aUri, aMetadata, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetSender}.
     * 
     * @param aUri
     * @param aMetadata
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetSender(String aUri, String aMetadata, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetSender, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionSetSender.getInputParameter(inIndex++), aUri));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetSender.getInputParameter(inIndex++), aMetadata));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetSender} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetSender} method.
     */
    public void endSetSender(long aAsyncHandle)
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
    public Sender syncSender()
    {
        SyncSenderAvOpenhomeOrgReceiver1 sync = new SyncSenderAvOpenhomeOrgReceiver1(this);
        beginSender(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Sender(
            sync.getUri(),
            sync.getMetadata()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSender}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSender(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSender, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionSender.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionSender.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSender} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSender} method.
     * @return the result of the previously invoked action.
     */
    public Sender endSender(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String uri = Invocation.getOutputString(aAsyncHandle, index++);
        String metadata = Invocation.getOutputString(aAsyncHandle, index++);
        return new Sender(
            uri,
            metadata
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncProtocolInfo()
    {
        SyncProtocolInfoAvOpenhomeOrgReceiver1 sync = new SyncProtocolInfoAvOpenhomeOrgReceiver1(this);
        beginProtocolInfo(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endProtocolInfo}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginProtocolInfo(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionProtocolInfo, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionProtocolInfo.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginProtocolInfo} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginProtocolInfo} method.
     * @return the result of the previously invoked action.
     */
    public String endProtocolInfo(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String value = Invocation.getOutputString(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncTransportState()
    {
        SyncTransportStateAvOpenhomeOrgReceiver1 sync = new SyncTransportStateAvOpenhomeOrgReceiver1(this);
        beginTransportState(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endTransportState}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginTransportState(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionTransportState, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionTransportState.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginTransportState} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginTransportState} method.
     * @return the result of the previously invoked action.
     */
    public String endTransportState(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String value = Invocation.getOutputString(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Set a delegate to be run when the Uri state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgReceiver1 instance will not overlap.
     *
     * @param aUriChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyUriChanged(IPropertyChangeListener aUriChanged)
    {
        synchronized (iPropertyLock)
        {
            iUriChanged = aUriChanged;
        }
    }

    private void uriPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iUriChanged);
        }
    }
    /**
     * Set a delegate to be run when the Metadata state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgReceiver1 instance will not overlap.
     *
     * @param aMetadataChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyMetadataChanged(IPropertyChangeListener aMetadataChanged)
    {
        synchronized (iPropertyLock)
        {
            iMetadataChanged = aMetadataChanged;
        }
    }

    private void metadataPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iMetadataChanged);
        }
    }
    /**
     * Set a delegate to be run when the TransportState state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgReceiver1 instance will not overlap.
     *
     * @param aTransportStateChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyTransportStateChanged(IPropertyChangeListener aTransportStateChanged)
    {
        synchronized (iPropertyLock)
        {
            iTransportStateChanged = aTransportStateChanged;
        }
    }

    private void transportStatePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iTransportStateChanged);
        }
    }
    /**
     * Set a delegate to be run when the ProtocolInfo state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgReceiver1 instance will not overlap.
     *
     * @param aProtocolInfoChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyProtocolInfoChanged(IPropertyChangeListener aProtocolInfoChanged)
    {
        synchronized (iPropertyLock)
        {
            iProtocolInfoChanged = aProtocolInfoChanged;
        }
    }

    private void protocolInfoPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iProtocolInfoChanged);
        }
    }

    /**
     * Query the value of the Uri property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Uri property.
     */
    public String getPropertyUri()
    {
        propertyReadLock();
        String val = iUri.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Metadata property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Metadata property.
     */
    public String getPropertyMetadata()
    {
        propertyReadLock();
        String val = iMetadata.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the TransportState property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the TransportState property.
     */
    public String getPropertyTransportState()
    {
        propertyReadLock();
        String val = iTransportState.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ProtocolInfo property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ProtocolInfo property.
     */
    public String getPropertyProtocolInfo()
    {
        propertyReadLock();
        String val = iProtocolInfo.getValue();
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
            iActionPlay.destroy();
            iActionStop.destroy();
            iActionSetSender.destroy();
            iActionSender.destroy();
            iActionProtocolInfo.destroy();
            iActionTransportState.destroy();
            iUri.destroy();
            iMetadata.destroy();
            iTransportState.destroy();
            iProtocolInfo.destroy();
        }
    }
}

