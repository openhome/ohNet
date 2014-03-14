package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgRadio1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgRadio1 extends ICpProxy
{
    public void syncPlay();
    public void beginPlay(ICpProxyListener aCallback);
    public void endPlay(long aAsyncHandle);
    public void syncPause();
    public void beginPause(ICpProxyListener aCallback);
    public void endPause(long aAsyncHandle);
    public void syncStop();
    public void beginStop(ICpProxyListener aCallback);
    public void endStop(long aAsyncHandle);
    public void syncSeekSecondAbsolute(long aValue);
    public void beginSeekSecondAbsolute(long aValue, ICpProxyListener aCallback);
    public void endSeekSecondAbsolute(long aAsyncHandle);
    public void syncSeekSecondRelative(int aValue);
    public void beginSeekSecondRelative(int aValue, ICpProxyListener aCallback);
    public void endSeekSecondRelative(long aAsyncHandle);
    public Channel syncChannel();
    public void beginChannel(ICpProxyListener aCallback);
    public Channel endChannel(long aAsyncHandle);
    public void syncSetChannel(String aUri, String aMetadata);
    public void beginSetChannel(String aUri, String aMetadata, ICpProxyListener aCallback);
    public void endSetChannel(long aAsyncHandle);
    public String syncTransportState();
    public void beginTransportState(ICpProxyListener aCallback);
    public String endTransportState(long aAsyncHandle);
    public long syncId();
    public void beginId(ICpProxyListener aCallback);
    public long endId(long aAsyncHandle);
    public void syncSetId(long aValue, String aUri);
    public void beginSetId(long aValue, String aUri, ICpProxyListener aCallback);
    public void endSetId(long aAsyncHandle);
    public String syncRead(long aId);
    public void beginRead(long aId, ICpProxyListener aCallback);
    public String endRead(long aAsyncHandle);
    public String syncReadList(String aIdList);
    public void beginReadList(String aIdList, ICpProxyListener aCallback);
    public String endReadList(long aAsyncHandle);
    public IdArray syncIdArray();
    public void beginIdArray(ICpProxyListener aCallback);
    public IdArray endIdArray(long aAsyncHandle);
    public boolean syncIdArrayChanged(long aToken);
    public void beginIdArrayChanged(long aToken, ICpProxyListener aCallback);
    public boolean endIdArrayChanged(long aAsyncHandle);
    public long syncChannelsMax();
    public void beginChannelsMax(ICpProxyListener aCallback);
    public long endChannelsMax(long aAsyncHandle);
    public String syncProtocolInfo();
    public void beginProtocolInfo(ICpProxyListener aCallback);
    public String endProtocolInfo(long aAsyncHandle);
    public void setPropertyUriChanged(IPropertyChangeListener aUriChanged);
    public String getPropertyUri();
    public void setPropertyMetadataChanged(IPropertyChangeListener aMetadataChanged);
    public String getPropertyMetadata();
    public void setPropertyTransportStateChanged(IPropertyChangeListener aTransportStateChanged);
    public String getPropertyTransportState();
    public void setPropertyIdChanged(IPropertyChangeListener aIdChanged);
    public long getPropertyId();
    public void setPropertyIdArrayChanged(IPropertyChangeListener aIdArrayChanged);
    public byte[] getPropertyIdArray();
    public void setPropertyChannelsMaxChanged(IPropertyChangeListener aChannelsMaxChanged);
    public long getPropertyChannelsMax();
    public void setPropertyProtocolInfoChanged(IPropertyChangeListener aProtocolInfoChanged);
    public String getPropertyProtocolInfo();
}

class SyncPlayAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;

    public SyncPlayAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPlay(aAsyncHandle);
        
    }
}

class SyncPauseAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;

    public SyncPauseAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPause(aAsyncHandle);
        
    }
}

class SyncStopAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;

    public SyncStopAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStop(aAsyncHandle);
        
    }
}

class SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;

    public SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSeekSecondAbsolute(aAsyncHandle);
        
    }
}

class SyncSeekSecondRelativeAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;

    public SyncSeekSecondRelativeAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSeekSecondRelative(aAsyncHandle);
        
    }
}

class SyncChannelAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private String iUri;
    private String iMetadata;

    public SyncChannelAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
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
        Channel result = iService.endChannel(aAsyncHandle);
        
        iUri = result.getUri();
        iMetadata = result.getMetadata();
    }
}

class SyncSetChannelAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;

    public SyncSetChannelAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetChannel(aAsyncHandle);
        
    }
}

class SyncTransportStateAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private String iValue;

    public SyncTransportStateAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
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

class SyncIdAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private long iValue;

    public SyncIdAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endId(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncSetIdAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;

    public SyncSetIdAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetId(aAsyncHandle);
        
    }
}

class SyncReadAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private String iMetadata;

    public SyncReadAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    public String getMetadata()
    {
        return iMetadata;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endRead(aAsyncHandle);
        
        iMetadata = result;
    }
}

class SyncReadListAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private String iChannelList;

    public SyncReadListAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    public String getChannelList()
    {
        return iChannelList;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endReadList(aAsyncHandle);
        
        iChannelList = result;
    }
}

class SyncIdArrayAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private long iToken;
    private byte[] iArray;

    public SyncIdArrayAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    public long getToken()
    {
        return iToken;
    }
    public byte[] getArray()
    {
        return iArray;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        IdArray result = iService.endIdArray(aAsyncHandle);
        
        iToken = result.getToken();
        iArray = result.getArray();
    }
}

class SyncIdArrayChangedAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private boolean iValue;

    public SyncIdArrayChangedAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endIdArrayChanged(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncChannelsMaxAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private long iValue;

    public SyncChannelsMaxAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endChannelsMax(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncProtocolInfoAvOpenhomeOrgRadio1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgRadio1 iService;
    private String iValue;

    public SyncProtocolInfoAvOpenhomeOrgRadio1(CpProxyAvOpenhomeOrgRadio1 aProxy)
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

/**
 * Proxy for the av.openhome.org:Radio:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgRadio1 extends CpProxy implements ICpProxyAvOpenhomeOrgRadio1
{

    public class Channel
    {
        private String iUri;
        private String iMetadata;

        public Channel(
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

    public class IdArray
    {
        private long iToken;
        private byte[] iArray;

        public IdArray(
            long aToken,
            byte[] aArray
        )
        {
            iToken = aToken;
            iArray = aArray;
        }
        public long getToken()
        {
            return iToken;
        }
        public byte[] getArray()
        {
            return iArray;
        }
    }

    private Action iActionPlay;
    private Action iActionPause;
    private Action iActionStop;
    private Action iActionSeekSecondAbsolute;
    private Action iActionSeekSecondRelative;
    private Action iActionChannel;
    private Action iActionSetChannel;
    private Action iActionTransportState;
    private Action iActionId;
    private Action iActionSetId;
    private Action iActionRead;
    private Action iActionReadList;
    private Action iActionIdArray;
    private Action iActionIdArrayChanged;
    private Action iActionChannelsMax;
    private Action iActionProtocolInfo;
    private PropertyString iUri;
    private PropertyString iMetadata;
    private PropertyString iTransportState;
    private PropertyUint iId;
    private PropertyBinary iIdArray;
    private PropertyUint iChannelsMax;
    private PropertyString iProtocolInfo;
    private IPropertyChangeListener iUriChanged;
    private IPropertyChangeListener iMetadataChanged;
    private IPropertyChangeListener iTransportStateChanged;
    private IPropertyChangeListener iIdChanged;
    private IPropertyChangeListener iIdArrayChanged;
    private IPropertyChangeListener iChannelsMaxChanged;
    private IPropertyChangeListener iProtocolInfoChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgRadio1(CpDevice aDevice)
    {
        super("av-openhome-org", "Radio", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionPlay = new Action("Play");

        iActionPause = new Action("Pause");

        iActionStop = new Action("Stop");

        iActionSeekSecondAbsolute = new Action("SeekSecondAbsolute");
        param = new ParameterUint("Value");
        iActionSeekSecondAbsolute.addInputParameter(param);

        iActionSeekSecondRelative = new Action("SeekSecondRelative");
        param = new ParameterInt("Value");
        iActionSeekSecondRelative.addInputParameter(param);

        iActionChannel = new Action("Channel");
        param = new ParameterString("Uri", allowedValues);
        iActionChannel.addOutputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
        iActionChannel.addOutputParameter(param);

        iActionSetChannel = new Action("SetChannel");
        param = new ParameterString("Uri", allowedValues);
        iActionSetChannel.addInputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
        iActionSetChannel.addInputParameter(param);

        iActionTransportState = new Action("TransportState");
        allowedValues.add("Stopped");
        allowedValues.add("Playing");
        allowedValues.add("Paused");
        allowedValues.add("Buffering");
        param = new ParameterString("Value", allowedValues);
        iActionTransportState.addOutputParameter(param);
        allowedValues.clear();

        iActionId = new Action("Id");
        param = new ParameterUint("Value");
        iActionId.addOutputParameter(param);

        iActionSetId = new Action("SetId");
        param = new ParameterUint("Value");
        iActionSetId.addInputParameter(param);
        param = new ParameterString("Uri", allowedValues);
        iActionSetId.addInputParameter(param);

        iActionRead = new Action("Read");
        param = new ParameterUint("Id");
        iActionRead.addInputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
        iActionRead.addOutputParameter(param);

        iActionReadList = new Action("ReadList");
        param = new ParameterString("IdList", allowedValues);
        iActionReadList.addInputParameter(param);
        param = new ParameterString("ChannelList", allowedValues);
        iActionReadList.addOutputParameter(param);

        iActionIdArray = new Action("IdArray");
        param = new ParameterUint("Token");
        iActionIdArray.addOutputParameter(param);
        param = new ParameterBinary("Array");
        iActionIdArray.addOutputParameter(param);

        iActionIdArrayChanged = new Action("IdArrayChanged");
        param = new ParameterUint("Token");
        iActionIdArrayChanged.addInputParameter(param);
        param = new ParameterBool("Value");
        iActionIdArrayChanged.addOutputParameter(param);

        iActionChannelsMax = new Action("ChannelsMax");
        param = new ParameterUint("Value");
        iActionChannelsMax.addOutputParameter(param);

        iActionProtocolInfo = new Action("ProtocolInfo");
        param = new ParameterString("Value", allowedValues);
        iActionProtocolInfo.addOutputParameter(param);

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
        iIdChanged = new PropertyChangeListener();
        iId = new PropertyUint("Id",
            new PropertyChangeListener() {
                public void notifyChange() {
                    idPropertyChanged();
                }
            }
        );
        addProperty(iId);
        iIdArrayChanged = new PropertyChangeListener();
        iIdArray = new PropertyBinary("IdArray",
            new PropertyChangeListener() {
                public void notifyChange() {
                    idArrayPropertyChanged();
                }
            }
        );
        addProperty(iIdArray);
        iChannelsMaxChanged = new PropertyChangeListener();
        iChannelsMax = new PropertyUint("ChannelsMax",
            new PropertyChangeListener() {
                public void notifyChange() {
                    channelsMaxPropertyChanged();
                }
            }
        );
        addProperty(iChannelsMax);
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
        SyncPlayAvOpenhomeOrgRadio1 sync = new SyncPlayAvOpenhomeOrgRadio1(this);
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
    public void syncPause()
    {
        SyncPauseAvOpenhomeOrgRadio1 sync = new SyncPauseAvOpenhomeOrgRadio1(this);
        beginPause(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPause}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPause(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPause, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPause} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginPause} method.
     */
    public void endPause(long aAsyncHandle)
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
        SyncStopAvOpenhomeOrgRadio1 sync = new SyncStopAvOpenhomeOrgRadio1(this);
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
    public void syncSeekSecondAbsolute(long aValue)
    {
        SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1 sync = new SyncSeekSecondAbsoluteAvOpenhomeOrgRadio1(this);
        beginSeekSecondAbsolute(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSeekSecondAbsolute}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSeekSecondAbsolute(long aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSeekSecondAbsolute, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSeekSecondAbsolute.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSeekSecondAbsolute} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSeekSecondAbsolute} method.
     */
    public void endSeekSecondAbsolute(long aAsyncHandle)
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
    public void syncSeekSecondRelative(int aValue)
    {
        SyncSeekSecondRelativeAvOpenhomeOrgRadio1 sync = new SyncSeekSecondRelativeAvOpenhomeOrgRadio1(this);
        beginSeekSecondRelative(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSeekSecondRelative}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSeekSecondRelative(int aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSeekSecondRelative, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentInt((ParameterInt)iActionSeekSecondRelative.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSeekSecondRelative} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSeekSecondRelative} method.
     */
    public void endSeekSecondRelative(long aAsyncHandle)
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
    public Channel syncChannel()
    {
        SyncChannelAvOpenhomeOrgRadio1 sync = new SyncChannelAvOpenhomeOrgRadio1(this);
        beginChannel(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Channel(
            sync.getUri(),
            sync.getMetadata()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endChannel}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginChannel(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionChannel, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionChannel.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionChannel.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginChannel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginChannel} method.
     * @return the result of the previously invoked action.
     */
    public Channel endChannel(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String uri = Invocation.getOutputString(aAsyncHandle, index++);
        String metadata = Invocation.getOutputString(aAsyncHandle, index++);
        return new Channel(
            uri,
            metadata
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetChannel(String aUri, String aMetadata)
    {
        SyncSetChannelAvOpenhomeOrgRadio1 sync = new SyncSetChannelAvOpenhomeOrgRadio1(this);
        beginSetChannel(aUri, aMetadata, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetChannel}.
     * 
     * @param aUri
     * @param aMetadata
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetChannel(String aUri, String aMetadata, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetChannel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionSetChannel.getInputParameter(inIndex++), aUri));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetChannel.getInputParameter(inIndex++), aMetadata));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetChannel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetChannel} method.
     */
    public void endSetChannel(long aAsyncHandle)
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
    public String syncTransportState()
    {
        SyncTransportStateAvOpenhomeOrgRadio1 sync = new SyncTransportStateAvOpenhomeOrgRadio1(this);
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
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncId()
    {
        SyncIdAvOpenhomeOrgRadio1 sync = new SyncIdAvOpenhomeOrgRadio1(this);
        beginId(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endId}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginId(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionId, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionId.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginId} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginId} method.
     * @return the result of the previously invoked action.
     */
    public long endId(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long value = Invocation.getOutputUint(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetId(long aValue, String aUri)
    {
        SyncSetIdAvOpenhomeOrgRadio1 sync = new SyncSetIdAvOpenhomeOrgRadio1(this);
        beginSetId(aValue, aUri, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetId}.
     * 
     * @param aValue
     * @param aUri
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetId(long aValue, String aUri, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetId, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetId.getInputParameter(inIndex++), aValue));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetId.getInputParameter(inIndex++), aUri));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetId} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetId} method.
     */
    public void endSetId(long aAsyncHandle)
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
    public String syncRead(long aId)
    {
        SyncReadAvOpenhomeOrgRadio1 sync = new SyncReadAvOpenhomeOrgRadio1(this);
        beginRead(aId, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getMetadata();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endRead}.
     * 
     * @param aId
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginRead(long aId, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionRead, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionRead.getInputParameter(inIndex++), aId));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionRead.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginRead} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginRead} method.
     * @return the result of the previously invoked action.
     */
    public String endRead(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String metadata = Invocation.getOutputString(aAsyncHandle, index++);
        return metadata;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncReadList(String aIdList)
    {
        SyncReadListAvOpenhomeOrgRadio1 sync = new SyncReadListAvOpenhomeOrgRadio1(this);
        beginReadList(aIdList, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getChannelList();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endReadList}.
     * 
     * @param aIdList
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginReadList(String aIdList, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionReadList, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionReadList.getInputParameter(inIndex++), aIdList));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionReadList.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginReadList} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginReadList} method.
     * @return the result of the previously invoked action.
     */
    public String endReadList(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String channelList = Invocation.getOutputString(aAsyncHandle, index++);
        return channelList;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public IdArray syncIdArray()
    {
        SyncIdArrayAvOpenhomeOrgRadio1 sync = new SyncIdArrayAvOpenhomeOrgRadio1(this);
        beginIdArray(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new IdArray(
            sync.getToken(),
            sync.getArray()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endIdArray}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginIdArray(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionIdArray, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionIdArray.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentBinary((ParameterBinary)iActionIdArray.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginIdArray} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginIdArray} method.
     * @return the result of the previously invoked action.
     */
    public IdArray endIdArray(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long token = Invocation.getOutputUint(aAsyncHandle, index++);
        byte[] array = Invocation.getOutputBinary(aAsyncHandle, index++);
        return new IdArray(
            token,
            array
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public boolean syncIdArrayChanged(long aToken)
    {
        SyncIdArrayChangedAvOpenhomeOrgRadio1 sync = new SyncIdArrayChangedAvOpenhomeOrgRadio1(this);
        beginIdArrayChanged(aToken, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endIdArrayChanged}.
     * 
     * @param aToken
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginIdArrayChanged(long aToken, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionIdArrayChanged, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionIdArrayChanged.getInputParameter(inIndex++), aToken));
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionIdArrayChanged.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginIdArrayChanged} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginIdArrayChanged} method.
     * @return the result of the previously invoked action.
     */
    public boolean endIdArrayChanged(long aAsyncHandle)
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
    public long syncChannelsMax()
    {
        SyncChannelsMaxAvOpenhomeOrgRadio1 sync = new SyncChannelsMaxAvOpenhomeOrgRadio1(this);
        beginChannelsMax(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endChannelsMax}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginChannelsMax(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionChannelsMax, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionChannelsMax.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginChannelsMax} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginChannelsMax} method.
     * @return the result of the previously invoked action.
     */
    public long endChannelsMax(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long value = Invocation.getOutputUint(aAsyncHandle, index++);
        return value;
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
        SyncProtocolInfoAvOpenhomeOrgRadio1 sync = new SyncProtocolInfoAvOpenhomeOrgRadio1(this);
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
     * Set a delegate to be run when the Uri state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgRadio1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgRadio1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgRadio1 instance will not overlap.
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
     * Set a delegate to be run when the Id state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgRadio1 instance will not overlap.
     *
     * @param aIdChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyIdChanged(IPropertyChangeListener aIdChanged)
    {
        synchronized (iPropertyLock)
        {
            iIdChanged = aIdChanged;
        }
    }

    private void idPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iIdChanged);
        }
    }
    /**
     * Set a delegate to be run when the IdArray state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgRadio1 instance will not overlap.
     *
     * @param aIdArrayChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyIdArrayChanged(IPropertyChangeListener aIdArrayChanged)
    {
        synchronized (iPropertyLock)
        {
            iIdArrayChanged = aIdArrayChanged;
        }
    }

    private void idArrayPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iIdArrayChanged);
        }
    }
    /**
     * Set a delegate to be run when the ChannelsMax state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgRadio1 instance will not overlap.
     *
     * @param aChannelsMaxChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyChannelsMaxChanged(IPropertyChangeListener aChannelsMaxChanged)
    {
        synchronized (iPropertyLock)
        {
            iChannelsMaxChanged = aChannelsMaxChanged;
        }
    }

    private void channelsMaxPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iChannelsMaxChanged);
        }
    }
    /**
     * Set a delegate to be run when the ProtocolInfo state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgRadio1 instance will not overlap.
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
     * Query the value of the Id property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Id property.
     */
    public long getPropertyId()
    {
        propertyReadLock();
        long val = iId.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the IdArray property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the IdArray property.
     */
    public byte[] getPropertyIdArray()
    {
        propertyReadLock();
        byte[] val = iIdArray.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ChannelsMax property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ChannelsMax property.
     */
    public long getPropertyChannelsMax()
    {
        propertyReadLock();
        long val = iChannelsMax.getValue();
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
            iActionPause.destroy();
            iActionStop.destroy();
            iActionSeekSecondAbsolute.destroy();
            iActionSeekSecondRelative.destroy();
            iActionChannel.destroy();
            iActionSetChannel.destroy();
            iActionTransportState.destroy();
            iActionId.destroy();
            iActionSetId.destroy();
            iActionRead.destroy();
            iActionReadList.destroy();
            iActionIdArray.destroy();
            iActionIdArrayChanged.destroy();
            iActionChannelsMax.destroy();
            iActionProtocolInfo.destroy();
            iUri.destroy();
            iMetadata.destroy();
            iTransportState.destroy();
            iId.destroy();
            iIdArray.destroy();
            iChannelsMax.destroy();
            iProtocolInfo.destroy();
        }
    }
}

