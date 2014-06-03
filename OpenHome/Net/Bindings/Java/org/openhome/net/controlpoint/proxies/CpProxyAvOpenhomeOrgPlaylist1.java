package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgPlaylist1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgPlaylist1 extends ICpProxy
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
    public void syncNext();
    public void beginNext(ICpProxyListener aCallback);
    public void endNext(long aAsyncHandle);
    public void syncPrevious();
    public void beginPrevious(ICpProxyListener aCallback);
    public void endPrevious(long aAsyncHandle);
    public void syncSetRepeat(boolean aValue);
    public void beginSetRepeat(boolean aValue, ICpProxyListener aCallback);
    public void endSetRepeat(long aAsyncHandle);
    public boolean syncRepeat();
    public void beginRepeat(ICpProxyListener aCallback);
    public boolean endRepeat(long aAsyncHandle);
    public void syncSetShuffle(boolean aValue);
    public void beginSetShuffle(boolean aValue, ICpProxyListener aCallback);
    public void endSetShuffle(long aAsyncHandle);
    public boolean syncShuffle();
    public void beginShuffle(ICpProxyListener aCallback);
    public boolean endShuffle(long aAsyncHandle);
    public void syncSeekSecondAbsolute(long aValue);
    public void beginSeekSecondAbsolute(long aValue, ICpProxyListener aCallback);
    public void endSeekSecondAbsolute(long aAsyncHandle);
    public void syncSeekSecondRelative(int aValue);
    public void beginSeekSecondRelative(int aValue, ICpProxyListener aCallback);
    public void endSeekSecondRelative(long aAsyncHandle);
    public void syncSeekId(long aValue);
    public void beginSeekId(long aValue, ICpProxyListener aCallback);
    public void endSeekId(long aAsyncHandle);
    public void syncSeekIndex(long aValue);
    public void beginSeekIndex(long aValue, ICpProxyListener aCallback);
    public void endSeekIndex(long aAsyncHandle);
    public String syncTransportState();
    public void beginTransportState(ICpProxyListener aCallback);
    public String endTransportState(long aAsyncHandle);
    public long syncId();
    public void beginId(ICpProxyListener aCallback);
    public long endId(long aAsyncHandle);
    public Read syncRead(long aId);
    public void beginRead(long aId, ICpProxyListener aCallback);
    public Read endRead(long aAsyncHandle);
    public String syncReadList(String aIdList);
    public void beginReadList(String aIdList, ICpProxyListener aCallback);
    public String endReadList(long aAsyncHandle);
    public long syncInsert(long aAfterId, String aUri, String aMetadata);
    public void beginInsert(long aAfterId, String aUri, String aMetadata, ICpProxyListener aCallback);
    public long endInsert(long aAsyncHandle);
    public void syncDeleteId(long aValue);
    public void beginDeleteId(long aValue, ICpProxyListener aCallback);
    public void endDeleteId(long aAsyncHandle);
    public void syncDeleteAll();
    public void beginDeleteAll(ICpProxyListener aCallback);
    public void endDeleteAll(long aAsyncHandle);
    public long syncTracksMax();
    public void beginTracksMax(ICpProxyListener aCallback);
    public long endTracksMax(long aAsyncHandle);
    public IdArray syncIdArray();
    public void beginIdArray(ICpProxyListener aCallback);
    public IdArray endIdArray(long aAsyncHandle);
    public boolean syncIdArrayChanged(long aToken);
    public void beginIdArrayChanged(long aToken, ICpProxyListener aCallback);
    public boolean endIdArrayChanged(long aAsyncHandle);
    public String syncProtocolInfo();
    public void beginProtocolInfo(ICpProxyListener aCallback);
    public String endProtocolInfo(long aAsyncHandle);
    public void setPropertyTransportStateChanged(IPropertyChangeListener aTransportStateChanged);
    public String getPropertyTransportState();
    public void setPropertyRepeatChanged(IPropertyChangeListener aRepeatChanged);
    public boolean getPropertyRepeat();
    public void setPropertyShuffleChanged(IPropertyChangeListener aShuffleChanged);
    public boolean getPropertyShuffle();
    public void setPropertyIdChanged(IPropertyChangeListener aIdChanged);
    public long getPropertyId();
    public void setPropertyIdArrayChanged(IPropertyChangeListener aIdArrayChanged);
    public byte[] getPropertyIdArray();
    public void setPropertyTracksMaxChanged(IPropertyChangeListener aTracksMaxChanged);
    public long getPropertyTracksMax();
    public void setPropertyProtocolInfoChanged(IPropertyChangeListener aProtocolInfoChanged);
    public String getPropertyProtocolInfo();
}

class SyncPlayAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncPlayAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPlay(aAsyncHandle);
        
    }
}

class SyncPauseAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncPauseAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPause(aAsyncHandle);
        
    }
}

class SyncStopAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncStopAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStop(aAsyncHandle);
        
    }
}

class SyncNextAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncNextAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endNext(aAsyncHandle);
        
    }
}

class SyncPreviousAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncPreviousAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPrevious(aAsyncHandle);
        
    }
}

class SyncSetRepeatAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncSetRepeatAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetRepeat(aAsyncHandle);
        
    }
}

class SyncRepeatAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private boolean iValue;

    public SyncRepeatAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endRepeat(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncSetShuffleAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncSetShuffleAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetShuffle(aAsyncHandle);
        
    }
}

class SyncShuffleAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private boolean iValue;

    public SyncShuffleAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endShuffle(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSeekSecondAbsolute(aAsyncHandle);
        
    }
}

class SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSeekSecondRelative(aAsyncHandle);
        
    }
}

class SyncSeekIdAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncSeekIdAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSeekId(aAsyncHandle);
        
    }
}

class SyncSeekIndexAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncSeekIndexAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSeekIndex(aAsyncHandle);
        
    }
}

class SyncTransportStateAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private String iValue;

    public SyncTransportStateAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
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

class SyncIdAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private long iValue;

    public SyncIdAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
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

class SyncReadAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private String iUri;
    private String iMetadata;

    public SyncReadAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
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
        Read result = iService.endRead(aAsyncHandle);
        
        iUri = result.getUri();
        iMetadata = result.getMetadata();
    }
}

class SyncReadListAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private String iTrackList;

    public SyncReadListAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    public String getTrackList()
    {
        return iTrackList;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endReadList(aAsyncHandle);
        
        iTrackList = result;
    }
}

class SyncInsertAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private long iNewId;

    public SyncInsertAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    public long getNewId()
    {
        return iNewId;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endInsert(aAsyncHandle);
        
        iNewId = result;
    }
}

class SyncDeleteIdAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncDeleteIdAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDeleteId(aAsyncHandle);
        
    }
}

class SyncDeleteAllAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;

    public SyncDeleteAllAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDeleteAll(aAsyncHandle);
        
    }
}

class SyncTracksMaxAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private long iValue;

    public SyncTracksMaxAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endTracksMax(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncIdArrayAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private long iToken;
    private byte[] iArray;

    public SyncIdArrayAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
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

class SyncIdArrayChangedAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private boolean iValue;

    public SyncIdArrayChangedAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
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

class SyncProtocolInfoAvOpenhomeOrgPlaylist1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylist1 iService;
    private String iValue;

    public SyncProtocolInfoAvOpenhomeOrgPlaylist1(CpProxyAvOpenhomeOrgPlaylist1 aProxy)
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
 * Proxy for the av.openhome.org:Playlist:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgPlaylist1 extends CpProxy implements ICpProxyAvOpenhomeOrgPlaylist1
{

    public class Read
    {
        private String iUri;
        private String iMetadata;

        public Read(
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
    private Action iActionNext;
    private Action iActionPrevious;
    private Action iActionSetRepeat;
    private Action iActionRepeat;
    private Action iActionSetShuffle;
    private Action iActionShuffle;
    private Action iActionSeekSecondAbsolute;
    private Action iActionSeekSecondRelative;
    private Action iActionSeekId;
    private Action iActionSeekIndex;
    private Action iActionTransportState;
    private Action iActionId;
    private Action iActionRead;
    private Action iActionReadList;
    private Action iActionInsert;
    private Action iActionDeleteId;
    private Action iActionDeleteAll;
    private Action iActionTracksMax;
    private Action iActionIdArray;
    private Action iActionIdArrayChanged;
    private Action iActionProtocolInfo;
    private PropertyString iTransportState;
    private PropertyBool iRepeat;
    private PropertyBool iShuffle;
    private PropertyUint iId;
    private PropertyBinary iIdArray;
    private PropertyUint iTracksMax;
    private PropertyString iProtocolInfo;
    private IPropertyChangeListener iTransportStateChanged;
    private IPropertyChangeListener iRepeatChanged;
    private IPropertyChangeListener iShuffleChanged;
    private IPropertyChangeListener iIdChanged;
    private IPropertyChangeListener iIdArrayChanged;
    private IPropertyChangeListener iTracksMaxChanged;
    private IPropertyChangeListener iProtocolInfoChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgPlaylist1(CpDevice aDevice)
    {
        super("av-openhome-org", "Playlist", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionPlay = new Action("Play");

        iActionPause = new Action("Pause");

        iActionStop = new Action("Stop");

        iActionNext = new Action("Next");

        iActionPrevious = new Action("Previous");

        iActionSetRepeat = new Action("SetRepeat");
        param = new ParameterBool("Value");
        iActionSetRepeat.addInputParameter(param);

        iActionRepeat = new Action("Repeat");
        param = new ParameterBool("Value");
        iActionRepeat.addOutputParameter(param);

        iActionSetShuffle = new Action("SetShuffle");
        param = new ParameterBool("Value");
        iActionSetShuffle.addInputParameter(param);

        iActionShuffle = new Action("Shuffle");
        param = new ParameterBool("Value");
        iActionShuffle.addOutputParameter(param);

        iActionSeekSecondAbsolute = new Action("SeekSecondAbsolute");
        param = new ParameterUint("Value");
        iActionSeekSecondAbsolute.addInputParameter(param);

        iActionSeekSecondRelative = new Action("SeekSecondRelative");
        param = new ParameterInt("Value");
        iActionSeekSecondRelative.addInputParameter(param);

        iActionSeekId = new Action("SeekId");
        param = new ParameterUint("Value");
        iActionSeekId.addInputParameter(param);

        iActionSeekIndex = new Action("SeekIndex");
        param = new ParameterUint("Value");
        iActionSeekIndex.addInputParameter(param);

        iActionTransportState = new Action("TransportState");
        allowedValues.add("Playing");
        allowedValues.add("Paused");
        allowedValues.add("Stopped");
        allowedValues.add("Buffering");
        param = new ParameterString("Value", allowedValues);
        iActionTransportState.addOutputParameter(param);
        allowedValues.clear();

        iActionId = new Action("Id");
        param = new ParameterUint("Value");
        iActionId.addOutputParameter(param);

        iActionRead = new Action("Read");
        param = new ParameterUint("Id");
        iActionRead.addInputParameter(param);
        param = new ParameterString("Uri", allowedValues);
        iActionRead.addOutputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
        iActionRead.addOutputParameter(param);

        iActionReadList = new Action("ReadList");
        param = new ParameterString("IdList", allowedValues);
        iActionReadList.addInputParameter(param);
        param = new ParameterString("TrackList", allowedValues);
        iActionReadList.addOutputParameter(param);

        iActionInsert = new Action("Insert");
        param = new ParameterUint("AfterId");
        iActionInsert.addInputParameter(param);
        param = new ParameterString("Uri", allowedValues);
        iActionInsert.addInputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
        iActionInsert.addInputParameter(param);
        param = new ParameterUint("NewId");
        iActionInsert.addOutputParameter(param);

        iActionDeleteId = new Action("DeleteId");
        param = new ParameterUint("Value");
        iActionDeleteId.addInputParameter(param);

        iActionDeleteAll = new Action("DeleteAll");

        iActionTracksMax = new Action("TracksMax");
        param = new ParameterUint("Value");
        iActionTracksMax.addOutputParameter(param);

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

        iActionProtocolInfo = new Action("ProtocolInfo");
        param = new ParameterString("Value", allowedValues);
        iActionProtocolInfo.addOutputParameter(param);

        iTransportStateChanged = new PropertyChangeListener();
        iTransportState = new PropertyString("TransportState",
            new PropertyChangeListener() {
                public void notifyChange() {
                    transportStatePropertyChanged();
                }
            }
        );
        addProperty(iTransportState);
        iRepeatChanged = new PropertyChangeListener();
        iRepeat = new PropertyBool("Repeat",
            new PropertyChangeListener() {
                public void notifyChange() {
                    repeatPropertyChanged();
                }
            }
        );
        addProperty(iRepeat);
        iShuffleChanged = new PropertyChangeListener();
        iShuffle = new PropertyBool("Shuffle",
            new PropertyChangeListener() {
                public void notifyChange() {
                    shufflePropertyChanged();
                }
            }
        );
        addProperty(iShuffle);
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
        iTracksMaxChanged = new PropertyChangeListener();
        iTracksMax = new PropertyUint("TracksMax",
            new PropertyChangeListener() {
                public void notifyChange() {
                    tracksMaxPropertyChanged();
                }
            }
        );
        addProperty(iTracksMax);
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
        SyncPlayAvOpenhomeOrgPlaylist1 sync = new SyncPlayAvOpenhomeOrgPlaylist1(this);
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
        SyncPauseAvOpenhomeOrgPlaylist1 sync = new SyncPauseAvOpenhomeOrgPlaylist1(this);
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
        SyncStopAvOpenhomeOrgPlaylist1 sync = new SyncStopAvOpenhomeOrgPlaylist1(this);
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
    public void syncNext()
    {
        SyncNextAvOpenhomeOrgPlaylist1 sync = new SyncNextAvOpenhomeOrgPlaylist1(this);
        beginNext(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endNext}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginNext(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionNext, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginNext} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginNext} method.
     */
    public void endNext(long aAsyncHandle)
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
    public void syncPrevious()
    {
        SyncPreviousAvOpenhomeOrgPlaylist1 sync = new SyncPreviousAvOpenhomeOrgPlaylist1(this);
        beginPrevious(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPrevious}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPrevious(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPrevious, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPrevious} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginPrevious} method.
     */
    public void endPrevious(long aAsyncHandle)
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
    public void syncSetRepeat(boolean aValue)
    {
        SyncSetRepeatAvOpenhomeOrgPlaylist1 sync = new SyncSetRepeatAvOpenhomeOrgPlaylist1(this);
        beginSetRepeat(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetRepeat}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetRepeat(boolean aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetRepeat, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentBool((ParameterBool)iActionSetRepeat.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetRepeat} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetRepeat} method.
     */
    public void endSetRepeat(long aAsyncHandle)
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
    public boolean syncRepeat()
    {
        SyncRepeatAvOpenhomeOrgPlaylist1 sync = new SyncRepeatAvOpenhomeOrgPlaylist1(this);
        beginRepeat(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endRepeat}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginRepeat(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionRepeat, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionRepeat.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginRepeat} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginRepeat} method.
     * @return the result of the previously invoked action.
     */
    public boolean endRepeat(long aAsyncHandle)
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
     */
    public void syncSetShuffle(boolean aValue)
    {
        SyncSetShuffleAvOpenhomeOrgPlaylist1 sync = new SyncSetShuffleAvOpenhomeOrgPlaylist1(this);
        beginSetShuffle(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetShuffle}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetShuffle(boolean aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetShuffle, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentBool((ParameterBool)iActionSetShuffle.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetShuffle} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetShuffle} method.
     */
    public void endSetShuffle(long aAsyncHandle)
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
    public boolean syncShuffle()
    {
        SyncShuffleAvOpenhomeOrgPlaylist1 sync = new SyncShuffleAvOpenhomeOrgPlaylist1(this);
        beginShuffle(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endShuffle}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginShuffle(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionShuffle, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionShuffle.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginShuffle} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginShuffle} method.
     * @return the result of the previously invoked action.
     */
    public boolean endShuffle(long aAsyncHandle)
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
     */
    public void syncSeekSecondAbsolute(long aValue)
    {
        SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1 sync = new SyncSeekSecondAbsoluteAvOpenhomeOrgPlaylist1(this);
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
        SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1 sync = new SyncSeekSecondRelativeAvOpenhomeOrgPlaylist1(this);
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
     */
    public void syncSeekId(long aValue)
    {
        SyncSeekIdAvOpenhomeOrgPlaylist1 sync = new SyncSeekIdAvOpenhomeOrgPlaylist1(this);
        beginSeekId(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSeekId}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSeekId(long aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSeekId, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSeekId.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSeekId} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSeekId} method.
     */
    public void endSeekId(long aAsyncHandle)
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
    public void syncSeekIndex(long aValue)
    {
        SyncSeekIndexAvOpenhomeOrgPlaylist1 sync = new SyncSeekIndexAvOpenhomeOrgPlaylist1(this);
        beginSeekIndex(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSeekIndex}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSeekIndex(long aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSeekIndex, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSeekIndex.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSeekIndex} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSeekIndex} method.
     */
    public void endSeekIndex(long aAsyncHandle)
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
        SyncTransportStateAvOpenhomeOrgPlaylist1 sync = new SyncTransportStateAvOpenhomeOrgPlaylist1(this);
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
        SyncIdAvOpenhomeOrgPlaylist1 sync = new SyncIdAvOpenhomeOrgPlaylist1(this);
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
     *
     * @return the result of the invoked action.
     */
    public Read syncRead(long aId)
    {
        SyncReadAvOpenhomeOrgPlaylist1 sync = new SyncReadAvOpenhomeOrgPlaylist1(this);
        beginRead(aId, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Read(
            sync.getUri(),
            sync.getMetadata()
        );
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
    public Read endRead(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String uri = Invocation.getOutputString(aAsyncHandle, index++);
        String metadata = Invocation.getOutputString(aAsyncHandle, index++);
        return new Read(
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
    public String syncReadList(String aIdList)
    {
        SyncReadListAvOpenhomeOrgPlaylist1 sync = new SyncReadListAvOpenhomeOrgPlaylist1(this);
        beginReadList(aIdList, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getTrackList();
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
        String trackList = Invocation.getOutputString(aAsyncHandle, index++);
        return trackList;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncInsert(long aAfterId, String aUri, String aMetadata)
    {
        SyncInsertAvOpenhomeOrgPlaylist1 sync = new SyncInsertAvOpenhomeOrgPlaylist1(this);
        beginInsert(aAfterId, aUri, aMetadata, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getNewId();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endInsert}.
     * 
     * @param aAfterId
     * @param aUri
     * @param aMetadata
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginInsert(long aAfterId, String aUri, String aMetadata, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionInsert, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionInsert.getInputParameter(inIndex++), aAfterId));
        invocation.addInput(new ArgumentString((ParameterString)iActionInsert.getInputParameter(inIndex++), aUri));
        invocation.addInput(new ArgumentString((ParameterString)iActionInsert.getInputParameter(inIndex++), aMetadata));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionInsert.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginInsert} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginInsert} method.
     * @return the result of the previously invoked action.
     */
    public long endInsert(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long newId = Invocation.getOutputUint(aAsyncHandle, index++);
        return newId;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncDeleteId(long aValue)
    {
        SyncDeleteIdAvOpenhomeOrgPlaylist1 sync = new SyncDeleteIdAvOpenhomeOrgPlaylist1(this);
        beginDeleteId(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDeleteId}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDeleteId(long aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDeleteId, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionDeleteId.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDeleteId} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDeleteId} method.
     */
    public void endDeleteId(long aAsyncHandle)
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
    public void syncDeleteAll()
    {
        SyncDeleteAllAvOpenhomeOrgPlaylist1 sync = new SyncDeleteAllAvOpenhomeOrgPlaylist1(this);
        beginDeleteAll(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDeleteAll}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDeleteAll(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDeleteAll, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDeleteAll} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDeleteAll} method.
     */
    public void endDeleteAll(long aAsyncHandle)
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
    public long syncTracksMax()
    {
        SyncTracksMaxAvOpenhomeOrgPlaylist1 sync = new SyncTracksMaxAvOpenhomeOrgPlaylist1(this);
        beginTracksMax(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endTracksMax}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginTracksMax(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionTracksMax, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionTracksMax.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginTracksMax} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginTracksMax} method.
     * @return the result of the previously invoked action.
     */
    public long endTracksMax(long aAsyncHandle)
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
    public IdArray syncIdArray()
    {
        SyncIdArrayAvOpenhomeOrgPlaylist1 sync = new SyncIdArrayAvOpenhomeOrgPlaylist1(this);
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
        SyncIdArrayChangedAvOpenhomeOrgPlaylist1 sync = new SyncIdArrayChangedAvOpenhomeOrgPlaylist1(this);
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
    public String syncProtocolInfo()
    {
        SyncProtocolInfoAvOpenhomeOrgPlaylist1 sync = new SyncProtocolInfoAvOpenhomeOrgPlaylist1(this);
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
     * Set a delegate to be run when the TransportState state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgPlaylist1 instance will not overlap.
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
     * Set a delegate to be run when the Repeat state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgPlaylist1 instance will not overlap.
     *
     * @param aRepeatChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyRepeatChanged(IPropertyChangeListener aRepeatChanged)
    {
        synchronized (iPropertyLock)
        {
            iRepeatChanged = aRepeatChanged;
        }
    }

    private void repeatPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iRepeatChanged);
        }
    }
    /**
     * Set a delegate to be run when the Shuffle state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgPlaylist1 instance will not overlap.
     *
     * @param aShuffleChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyShuffleChanged(IPropertyChangeListener aShuffleChanged)
    {
        synchronized (iPropertyLock)
        {
            iShuffleChanged = aShuffleChanged;
        }
    }

    private void shufflePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iShuffleChanged);
        }
    }
    /**
     * Set a delegate to be run when the Id state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgPlaylist1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgPlaylist1 instance will not overlap.
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
     * Set a delegate to be run when the TracksMax state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgPlaylist1 instance will not overlap.
     *
     * @param aTracksMaxChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyTracksMaxChanged(IPropertyChangeListener aTracksMaxChanged)
    {
        synchronized (iPropertyLock)
        {
            iTracksMaxChanged = aTracksMaxChanged;
        }
    }

    private void tracksMaxPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iTracksMaxChanged);
        }
    }
    /**
     * Set a delegate to be run when the ProtocolInfo state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgPlaylist1 instance will not overlap.
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
     * Query the value of the Repeat property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Repeat property.
     */
    public boolean getPropertyRepeat()
    {
        propertyReadLock();
        boolean val = iRepeat.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Shuffle property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Shuffle property.
     */
    public boolean getPropertyShuffle()
    {
        propertyReadLock();
        boolean val = iShuffle.getValue();
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
     * Query the value of the TracksMax property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the TracksMax property.
     */
    public long getPropertyTracksMax()
    {
        propertyReadLock();
        long val = iTracksMax.getValue();
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
            iActionNext.destroy();
            iActionPrevious.destroy();
            iActionSetRepeat.destroy();
            iActionRepeat.destroy();
            iActionSetShuffle.destroy();
            iActionShuffle.destroy();
            iActionSeekSecondAbsolute.destroy();
            iActionSeekSecondRelative.destroy();
            iActionSeekId.destroy();
            iActionSeekIndex.destroy();
            iActionTransportState.destroy();
            iActionId.destroy();
            iActionRead.destroy();
            iActionReadList.destroy();
            iActionInsert.destroy();
            iActionDeleteId.destroy();
            iActionDeleteAll.destroy();
            iActionTracksMax.destroy();
            iActionIdArray.destroy();
            iActionIdArrayChanged.destroy();
            iActionProtocolInfo.destroy();
            iTransportState.destroy();
            iRepeat.destroy();
            iShuffle.destroy();
            iId.destroy();
            iIdArray.destroy();
            iTracksMax.destroy();
            iProtocolInfo.destroy();
        }
    }
}

