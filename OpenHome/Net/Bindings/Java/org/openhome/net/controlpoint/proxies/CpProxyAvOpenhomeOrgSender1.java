package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgSender1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgSender1 extends ICpProxy
{
    public String syncPresentationUrl();
    public void beginPresentationUrl(ICpProxyListener aCallback);
    public String endPresentationUrl(long aAsyncHandle);
    public String syncMetadata();
    public void beginMetadata(ICpProxyListener aCallback);
    public String endMetadata(long aAsyncHandle);
    public boolean syncAudio();
    public void beginAudio(ICpProxyListener aCallback);
    public boolean endAudio(long aAsyncHandle);
    public String syncStatus();
    public void beginStatus(ICpProxyListener aCallback);
    public String endStatus(long aAsyncHandle);
    public String syncAttributes();
    public void beginAttributes(ICpProxyListener aCallback);
    public String endAttributes(long aAsyncHandle);
    public void setPropertyPresentationUrlChanged(IPropertyChangeListener aPresentationUrlChanged);
    public String getPropertyPresentationUrl();
    public void setPropertyMetadataChanged(IPropertyChangeListener aMetadataChanged);
    public String getPropertyMetadata();
    public void setPropertyAudioChanged(IPropertyChangeListener aAudioChanged);
    public boolean getPropertyAudio();
    public void setPropertyStatusChanged(IPropertyChangeListener aStatusChanged);
    public String getPropertyStatus();
    public void setPropertyAttributesChanged(IPropertyChangeListener aAttributesChanged);
    public String getPropertyAttributes();
}

class SyncPresentationUrlAvOpenhomeOrgSender1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgSender1 iService;
    private String iValue;

    public SyncPresentationUrlAvOpenhomeOrgSender1(CpProxyAvOpenhomeOrgSender1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endPresentationUrl(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncMetadataAvOpenhomeOrgSender1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgSender1 iService;
    private String iValue;

    public SyncMetadataAvOpenhomeOrgSender1(CpProxyAvOpenhomeOrgSender1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endMetadata(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncAudioAvOpenhomeOrgSender1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgSender1 iService;
    private boolean iValue;

    public SyncAudioAvOpenhomeOrgSender1(CpProxyAvOpenhomeOrgSender1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endAudio(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncStatusAvOpenhomeOrgSender1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgSender1 iService;
    private String iValue;

    public SyncStatusAvOpenhomeOrgSender1(CpProxyAvOpenhomeOrgSender1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endStatus(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncAttributesAvOpenhomeOrgSender1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgSender1 iService;
    private String iValue;

    public SyncAttributesAvOpenhomeOrgSender1(CpProxyAvOpenhomeOrgSender1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endAttributes(aAsyncHandle);
        
        iValue = result;
    }
}

/**
 * Proxy for the av.openhome.org:Sender:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgSender1 extends CpProxy implements ICpProxyAvOpenhomeOrgSender1
{

    private Action iActionPresentationUrl;
    private Action iActionMetadata;
    private Action iActionAudio;
    private Action iActionStatus;
    private Action iActionAttributes;
    private PropertyString iPresentationUrl;
    private PropertyString iMetadata;
    private PropertyBool iAudio;
    private PropertyString iStatus;
    private PropertyString iAttributes;
    private IPropertyChangeListener iPresentationUrlChanged;
    private IPropertyChangeListener iMetadataChanged;
    private IPropertyChangeListener iAudioChanged;
    private IPropertyChangeListener iStatusChanged;
    private IPropertyChangeListener iAttributesChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgSender1(CpDevice aDevice)
    {
        super("av-openhome-org", "Sender", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionPresentationUrl = new Action("PresentationUrl");
        param = new ParameterString("Value", allowedValues);
        iActionPresentationUrl.addOutputParameter(param);

        iActionMetadata = new Action("Metadata");
        param = new ParameterString("Value", allowedValues);
        iActionMetadata.addOutputParameter(param);

        iActionAudio = new Action("Audio");
        param = new ParameterBool("Value");
        iActionAudio.addOutputParameter(param);

        iActionStatus = new Action("Status");
        allowedValues.add("Enabled");
        allowedValues.add("Disabled");
        allowedValues.add("Blocked");
        param = new ParameterString("Value", allowedValues);
        iActionStatus.addOutputParameter(param);
        allowedValues.clear();

        iActionAttributes = new Action("Attributes");
        param = new ParameterString("Value", allowedValues);
        iActionAttributes.addOutputParameter(param);

        iPresentationUrlChanged = new PropertyChangeListener();
        iPresentationUrl = new PropertyString("PresentationUrl",
            new PropertyChangeListener() {
                public void notifyChange() {
                    presentationUrlPropertyChanged();
                }
            }
        );
        addProperty(iPresentationUrl);
        iMetadataChanged = new PropertyChangeListener();
        iMetadata = new PropertyString("Metadata",
            new PropertyChangeListener() {
                public void notifyChange() {
                    metadataPropertyChanged();
                }
            }
        );
        addProperty(iMetadata);
        iAudioChanged = new PropertyChangeListener();
        iAudio = new PropertyBool("Audio",
            new PropertyChangeListener() {
                public void notifyChange() {
                    audioPropertyChanged();
                }
            }
        );
        addProperty(iAudio);
        iStatusChanged = new PropertyChangeListener();
        iStatus = new PropertyString("Status",
            new PropertyChangeListener() {
                public void notifyChange() {
                    statusPropertyChanged();
                }
            }
        );
        addProperty(iStatus);
        iAttributesChanged = new PropertyChangeListener();
        iAttributes = new PropertyString("Attributes",
            new PropertyChangeListener() {
                public void notifyChange() {
                    attributesPropertyChanged();
                }
            }
        );
        addProperty(iAttributes);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncPresentationUrl()
    {
        SyncPresentationUrlAvOpenhomeOrgSender1 sync = new SyncPresentationUrlAvOpenhomeOrgSender1(this);
        beginPresentationUrl(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPresentationUrl}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPresentationUrl(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPresentationUrl, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionPresentationUrl.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPresentationUrl} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginPresentationUrl} method.
     * @return the result of the previously invoked action.
     */
    public String endPresentationUrl(long aAsyncHandle)
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
    public String syncMetadata()
    {
        SyncMetadataAvOpenhomeOrgSender1 sync = new SyncMetadataAvOpenhomeOrgSender1(this);
        beginMetadata(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endMetadata}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginMetadata(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionMetadata, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionMetadata.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginMetadata} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginMetadata} method.
     * @return the result of the previously invoked action.
     */
    public String endMetadata(long aAsyncHandle)
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
    public boolean syncAudio()
    {
        SyncAudioAvOpenhomeOrgSender1 sync = new SyncAudioAvOpenhomeOrgSender1(this);
        beginAudio(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endAudio}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginAudio(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionAudio, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionAudio.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginAudio} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginAudio} method.
     * @return the result of the previously invoked action.
     */
    public boolean endAudio(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        boolean value = Invocation.getOutputBool(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncStatus()
    {
        SyncStatusAvOpenhomeOrgSender1 sync = new SyncStatusAvOpenhomeOrgSender1(this);
        beginStatus(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStatus}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStatus(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStatus, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionStatus.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStatus} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStatus} method.
     * @return the result of the previously invoked action.
     */
    public String endStatus(long aAsyncHandle)
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
    public String syncAttributes()
    {
        SyncAttributesAvOpenhomeOrgSender1 sync = new SyncAttributesAvOpenhomeOrgSender1(this);
        beginAttributes(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endAttributes}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginAttributes(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionAttributes, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionAttributes.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginAttributes} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginAttributes} method.
     * @return the result of the previously invoked action.
     */
    public String endAttributes(long aAsyncHandle)
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
     * Set a delegate to be run when the PresentationUrl state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgSender1 instance will not overlap.
     *
     * @param aPresentationUrlChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyPresentationUrlChanged(IPropertyChangeListener aPresentationUrlChanged)
    {
        synchronized (iPropertyLock)
        {
            iPresentationUrlChanged = aPresentationUrlChanged;
        }
    }

    private void presentationUrlPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iPresentationUrlChanged);
        }
    }
    /**
     * Set a delegate to be run when the Metadata state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgSender1 instance will not overlap.
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
     * Set a delegate to be run when the Audio state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgSender1 instance will not overlap.
     *
     * @param aAudioChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyAudioChanged(IPropertyChangeListener aAudioChanged)
    {
        synchronized (iPropertyLock)
        {
            iAudioChanged = aAudioChanged;
        }
    }

    private void audioPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iAudioChanged);
        }
    }
    /**
     * Set a delegate to be run when the Status state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgSender1 instance will not overlap.
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
     * Set a delegate to be run when the Attributes state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgSender1 instance will not overlap.
     *
     * @param aAttributesChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyAttributesChanged(IPropertyChangeListener aAttributesChanged)
    {
        synchronized (iPropertyLock)
        {
            iAttributesChanged = aAttributesChanged;
        }
    }

    private void attributesPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iAttributesChanged);
        }
    }

    /**
     * Query the value of the PresentationUrl property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the PresentationUrl property.
     */
    public String getPropertyPresentationUrl()
    {
        propertyReadLock();
        String val = iPresentationUrl.getValue();
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
     * Query the value of the Audio property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Audio property.
     */
    public boolean getPropertyAudio()
    {
        propertyReadLock();
        boolean val = iAudio.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Status property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Status property.
     */
    public String getPropertyStatus()
    {
        propertyReadLock();
        String val = iStatus.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Attributes property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Attributes property.
     */
    public String getPropertyAttributes()
    {
        propertyReadLock();
        String val = iAttributes.getValue();
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
            iActionPresentationUrl.destroy();
            iActionMetadata.destroy();
            iActionAudio.destroy();
            iActionStatus.destroy();
            iActionAttributes.destroy();
            iPresentationUrl.destroy();
            iMetadata.destroy();
            iAudio.destroy();
            iStatus.destroy();
            iAttributes.destroy();
        }
    }
}

