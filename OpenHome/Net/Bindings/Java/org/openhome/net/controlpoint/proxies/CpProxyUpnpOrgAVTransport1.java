package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgAVTransport1.*;
import org.openhome.net.core.*;

    
interface ICpProxyUpnpOrgAVTransport1 extends ICpProxy
{
    public void syncSetAVTransportURI(long aInstanceID, String aCurrentURI, String aCurrentURIMetaData);
    public void beginSetAVTransportURI(long aInstanceID, String aCurrentURI, String aCurrentURIMetaData, ICpProxyListener aCallback);
    public void endSetAVTransportURI(long aAsyncHandle);
    public void syncSetNextAVTransportURI(long aInstanceID, String aNextURI, String aNextURIMetaData);
    public void beginSetNextAVTransportURI(long aInstanceID, String aNextURI, String aNextURIMetaData, ICpProxyListener aCallback);
    public void endSetNextAVTransportURI(long aAsyncHandle);
    public GetMediaInfo syncGetMediaInfo(long aInstanceID);
    public void beginGetMediaInfo(long aInstanceID, ICpProxyListener aCallback);
    public GetMediaInfo endGetMediaInfo(long aAsyncHandle);
    public GetTransportInfo syncGetTransportInfo(long aInstanceID);
    public void beginGetTransportInfo(long aInstanceID, ICpProxyListener aCallback);
    public GetTransportInfo endGetTransportInfo(long aAsyncHandle);
    public GetPositionInfo syncGetPositionInfo(long aInstanceID);
    public void beginGetPositionInfo(long aInstanceID, ICpProxyListener aCallback);
    public GetPositionInfo endGetPositionInfo(long aAsyncHandle);
    public GetDeviceCapabilities syncGetDeviceCapabilities(long aInstanceID);
    public void beginGetDeviceCapabilities(long aInstanceID, ICpProxyListener aCallback);
    public GetDeviceCapabilities endGetDeviceCapabilities(long aAsyncHandle);
    public GetTransportSettings syncGetTransportSettings(long aInstanceID);
    public void beginGetTransportSettings(long aInstanceID, ICpProxyListener aCallback);
    public GetTransportSettings endGetTransportSettings(long aAsyncHandle);
    public void syncStop(long aInstanceID);
    public void beginStop(long aInstanceID, ICpProxyListener aCallback);
    public void endStop(long aAsyncHandle);
    public void syncPlay(long aInstanceID, String aSpeed);
    public void beginPlay(long aInstanceID, String aSpeed, ICpProxyListener aCallback);
    public void endPlay(long aAsyncHandle);
    public void syncPause(long aInstanceID);
    public void beginPause(long aInstanceID, ICpProxyListener aCallback);
    public void endPause(long aAsyncHandle);
    public void syncRecord(long aInstanceID);
    public void beginRecord(long aInstanceID, ICpProxyListener aCallback);
    public void endRecord(long aAsyncHandle);
    public void syncSeek(long aInstanceID, String aUnit, String aTarget);
    public void beginSeek(long aInstanceID, String aUnit, String aTarget, ICpProxyListener aCallback);
    public void endSeek(long aAsyncHandle);
    public void syncNext(long aInstanceID);
    public void beginNext(long aInstanceID, ICpProxyListener aCallback);
    public void endNext(long aAsyncHandle);
    public void syncPrevious(long aInstanceID);
    public void beginPrevious(long aInstanceID, ICpProxyListener aCallback);
    public void endPrevious(long aAsyncHandle);
    public void syncSetPlayMode(long aInstanceID, String aNewPlayMode);
    public void beginSetPlayMode(long aInstanceID, String aNewPlayMode, ICpProxyListener aCallback);
    public void endSetPlayMode(long aAsyncHandle);
    public void syncSetRecordQualityMode(long aInstanceID, String aNewRecordQualityMode);
    public void beginSetRecordQualityMode(long aInstanceID, String aNewRecordQualityMode, ICpProxyListener aCallback);
    public void endSetRecordQualityMode(long aAsyncHandle);
    public String syncGetCurrentTransportActions(long aInstanceID);
    public void beginGetCurrentTransportActions(long aInstanceID, ICpProxyListener aCallback);
    public String endGetCurrentTransportActions(long aAsyncHandle);
    public void setPropertyLastChangeChanged(IPropertyChangeListener aLastChangeChanged);
    public String getPropertyLastChange();
}

class SyncSetAVTransportURIUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncSetAVTransportURIUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetAVTransportURI(aAsyncHandle);
        
    }
}

class SyncSetNextAVTransportURIUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncSetNextAVTransportURIUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetNextAVTransportURI(aAsyncHandle);
        
    }
}

class SyncGetMediaInfoUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;
    private long iNrTracks;
    private String iMediaDuration;
    private String iCurrentURI;
    private String iCurrentURIMetaData;
    private String iNextURI;
    private String iNextURIMetaData;
    private String iPlayMedium;
    private String iRecordMedium;
    private String iWriteStatus;

    public SyncGetMediaInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    public long getNrTracks()
    {
        return iNrTracks;
    }
    public String getMediaDuration()
    {
        return iMediaDuration;
    }
    public String getCurrentURI()
    {
        return iCurrentURI;
    }
    public String getCurrentURIMetaData()
    {
        return iCurrentURIMetaData;
    }
    public String getNextURI()
    {
        return iNextURI;
    }
    public String getNextURIMetaData()
    {
        return iNextURIMetaData;
    }
    public String getPlayMedium()
    {
        return iPlayMedium;
    }
    public String getRecordMedium()
    {
        return iRecordMedium;
    }
    public String getWriteStatus()
    {
        return iWriteStatus;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetMediaInfo result = iService.endGetMediaInfo(aAsyncHandle);
        
        iNrTracks = result.getNrTracks();
        iMediaDuration = result.getMediaDuration();
        iCurrentURI = result.getCurrentURI();
        iCurrentURIMetaData = result.getCurrentURIMetaData();
        iNextURI = result.getNextURI();
        iNextURIMetaData = result.getNextURIMetaData();
        iPlayMedium = result.getPlayMedium();
        iRecordMedium = result.getRecordMedium();
        iWriteStatus = result.getWriteStatus();
    }
}

class SyncGetTransportInfoUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;
    private String iCurrentTransportState;
    private String iCurrentTransportStatus;
    private String iCurrentSpeed;

    public SyncGetTransportInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    public String getCurrentTransportState()
    {
        return iCurrentTransportState;
    }
    public String getCurrentTransportStatus()
    {
        return iCurrentTransportStatus;
    }
    public String getCurrentSpeed()
    {
        return iCurrentSpeed;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetTransportInfo result = iService.endGetTransportInfo(aAsyncHandle);
        
        iCurrentTransportState = result.getCurrentTransportState();
        iCurrentTransportStatus = result.getCurrentTransportStatus();
        iCurrentSpeed = result.getCurrentSpeed();
    }
}

class SyncGetPositionInfoUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;
    private long iTrack;
    private String iTrackDuration;
    private String iTrackMetaData;
    private String iTrackURI;
    private String iRelTime;
    private String iAbsTime;
    private int iRelCount;
    private int iAbsCount;

    public SyncGetPositionInfoUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    public long getTrack()
    {
        return iTrack;
    }
    public String getTrackDuration()
    {
        return iTrackDuration;
    }
    public String getTrackMetaData()
    {
        return iTrackMetaData;
    }
    public String getTrackURI()
    {
        return iTrackURI;
    }
    public String getRelTime()
    {
        return iRelTime;
    }
    public String getAbsTime()
    {
        return iAbsTime;
    }
    public int getRelCount()
    {
        return iRelCount;
    }
    public int getAbsCount()
    {
        return iAbsCount;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetPositionInfo result = iService.endGetPositionInfo(aAsyncHandle);
        
        iTrack = result.getTrack();
        iTrackDuration = result.getTrackDuration();
        iTrackMetaData = result.getTrackMetaData();
        iTrackURI = result.getTrackURI();
        iRelTime = result.getRelTime();
        iAbsTime = result.getAbsTime();
        iRelCount = result.getRelCount();
        iAbsCount = result.getAbsCount();
    }
}

class SyncGetDeviceCapabilitiesUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;
    private String iPlayMedia;
    private String iRecMedia;
    private String iRecQualityModes;

    public SyncGetDeviceCapabilitiesUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    public String getPlayMedia()
    {
        return iPlayMedia;
    }
    public String getRecMedia()
    {
        return iRecMedia;
    }
    public String getRecQualityModes()
    {
        return iRecQualityModes;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetDeviceCapabilities result = iService.endGetDeviceCapabilities(aAsyncHandle);
        
        iPlayMedia = result.getPlayMedia();
        iRecMedia = result.getRecMedia();
        iRecQualityModes = result.getRecQualityModes();
    }
}

class SyncGetTransportSettingsUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;
    private String iPlayMode;
    private String iRecQualityMode;

    public SyncGetTransportSettingsUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    public String getPlayMode()
    {
        return iPlayMode;
    }
    public String getRecQualityMode()
    {
        return iRecQualityMode;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetTransportSettings result = iService.endGetTransportSettings(aAsyncHandle);
        
        iPlayMode = result.getPlayMode();
        iRecQualityMode = result.getRecQualityMode();
    }
}

class SyncStopUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncStopUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStop(aAsyncHandle);
        
    }
}

class SyncPlayUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncPlayUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPlay(aAsyncHandle);
        
    }
}

class SyncPauseUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncPauseUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPause(aAsyncHandle);
        
    }
}

class SyncRecordUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncRecordUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endRecord(aAsyncHandle);
        
    }
}

class SyncSeekUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncSeekUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSeek(aAsyncHandle);
        
    }
}

class SyncNextUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncNextUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endNext(aAsyncHandle);
        
    }
}

class SyncPreviousUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncPreviousUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPrevious(aAsyncHandle);
        
    }
}

class SyncSetPlayModeUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncSetPlayModeUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetPlayMode(aAsyncHandle);
        
    }
}

class SyncSetRecordQualityModeUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;

    public SyncSetRecordQualityModeUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetRecordQualityMode(aAsyncHandle);
        
    }
}

class SyncGetCurrentTransportActionsUpnpOrgAVTransport1 extends SyncProxyAction
{
    private CpProxyUpnpOrgAVTransport1 iService;
    private String iActions;

    public SyncGetCurrentTransportActionsUpnpOrgAVTransport1(CpProxyUpnpOrgAVTransport1 aProxy)
    {
        iService = aProxy;
    }
    public String getActions()
    {
        return iActions;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetCurrentTransportActions(aAsyncHandle);
        
        iActions = result;
    }
}

/**
 * Proxy for the upnp.org:AVTransport:1 UPnP service
 */
public class CpProxyUpnpOrgAVTransport1 extends CpProxy implements ICpProxyUpnpOrgAVTransport1
{

    public class GetMediaInfo
    {
        private long iNrTracks;
        private String iMediaDuration;
        private String iCurrentURI;
        private String iCurrentURIMetaData;
        private String iNextURI;
        private String iNextURIMetaData;
        private String iPlayMedium;
        private String iRecordMedium;
        private String iWriteStatus;

        public GetMediaInfo(
            long aNrTracks,
            String aMediaDuration,
            String aCurrentURI,
            String aCurrentURIMetaData,
            String aNextURI,
            String aNextURIMetaData,
            String aPlayMedium,
            String aRecordMedium,
            String aWriteStatus
        )
        {
            iNrTracks = aNrTracks;
            iMediaDuration = aMediaDuration;
            iCurrentURI = aCurrentURI;
            iCurrentURIMetaData = aCurrentURIMetaData;
            iNextURI = aNextURI;
            iNextURIMetaData = aNextURIMetaData;
            iPlayMedium = aPlayMedium;
            iRecordMedium = aRecordMedium;
            iWriteStatus = aWriteStatus;
        }
        public long getNrTracks()
        {
            return iNrTracks;
        }
        public String getMediaDuration()
        {
            return iMediaDuration;
        }
        public String getCurrentURI()
        {
            return iCurrentURI;
        }
        public String getCurrentURIMetaData()
        {
            return iCurrentURIMetaData;
        }
        public String getNextURI()
        {
            return iNextURI;
        }
        public String getNextURIMetaData()
        {
            return iNextURIMetaData;
        }
        public String getPlayMedium()
        {
            return iPlayMedium;
        }
        public String getRecordMedium()
        {
            return iRecordMedium;
        }
        public String getWriteStatus()
        {
            return iWriteStatus;
        }
    }

    public class GetTransportInfo
    {
        private String iCurrentTransportState;
        private String iCurrentTransportStatus;
        private String iCurrentSpeed;

        public GetTransportInfo(
            String aCurrentTransportState,
            String aCurrentTransportStatus,
            String aCurrentSpeed
        )
        {
            iCurrentTransportState = aCurrentTransportState;
            iCurrentTransportStatus = aCurrentTransportStatus;
            iCurrentSpeed = aCurrentSpeed;
        }
        public String getCurrentTransportState()
        {
            return iCurrentTransportState;
        }
        public String getCurrentTransportStatus()
        {
            return iCurrentTransportStatus;
        }
        public String getCurrentSpeed()
        {
            return iCurrentSpeed;
        }
    }

    public class GetPositionInfo
    {
        private long iTrack;
        private String iTrackDuration;
        private String iTrackMetaData;
        private String iTrackURI;
        private String iRelTime;
        private String iAbsTime;
        private int iRelCount;
        private int iAbsCount;

        public GetPositionInfo(
            long aTrack,
            String aTrackDuration,
            String aTrackMetaData,
            String aTrackURI,
            String aRelTime,
            String aAbsTime,
            int aRelCount,
            int aAbsCount
        )
        {
            iTrack = aTrack;
            iTrackDuration = aTrackDuration;
            iTrackMetaData = aTrackMetaData;
            iTrackURI = aTrackURI;
            iRelTime = aRelTime;
            iAbsTime = aAbsTime;
            iRelCount = aRelCount;
            iAbsCount = aAbsCount;
        }
        public long getTrack()
        {
            return iTrack;
        }
        public String getTrackDuration()
        {
            return iTrackDuration;
        }
        public String getTrackMetaData()
        {
            return iTrackMetaData;
        }
        public String getTrackURI()
        {
            return iTrackURI;
        }
        public String getRelTime()
        {
            return iRelTime;
        }
        public String getAbsTime()
        {
            return iAbsTime;
        }
        public int getRelCount()
        {
            return iRelCount;
        }
        public int getAbsCount()
        {
            return iAbsCount;
        }
    }

    public class GetDeviceCapabilities
    {
        private String iPlayMedia;
        private String iRecMedia;
        private String iRecQualityModes;

        public GetDeviceCapabilities(
            String aPlayMedia,
            String aRecMedia,
            String aRecQualityModes
        )
        {
            iPlayMedia = aPlayMedia;
            iRecMedia = aRecMedia;
            iRecQualityModes = aRecQualityModes;
        }
        public String getPlayMedia()
        {
            return iPlayMedia;
        }
        public String getRecMedia()
        {
            return iRecMedia;
        }
        public String getRecQualityModes()
        {
            return iRecQualityModes;
        }
    }

    public class GetTransportSettings
    {
        private String iPlayMode;
        private String iRecQualityMode;

        public GetTransportSettings(
            String aPlayMode,
            String aRecQualityMode
        )
        {
            iPlayMode = aPlayMode;
            iRecQualityMode = aRecQualityMode;
        }
        public String getPlayMode()
        {
            return iPlayMode;
        }
        public String getRecQualityMode()
        {
            return iRecQualityMode;
        }
    }

    private Action iActionSetAVTransportURI;
    private Action iActionSetNextAVTransportURI;
    private Action iActionGetMediaInfo;
    private Action iActionGetTransportInfo;
    private Action iActionGetPositionInfo;
    private Action iActionGetDeviceCapabilities;
    private Action iActionGetTransportSettings;
    private Action iActionStop;
    private Action iActionPlay;
    private Action iActionPause;
    private Action iActionRecord;
    private Action iActionSeek;
    private Action iActionNext;
    private Action iActionPrevious;
    private Action iActionSetPlayMode;
    private Action iActionSetRecordQualityMode;
    private Action iActionGetCurrentTransportActions;
    private PropertyString iLastChange;
    private IPropertyChangeListener iLastChangeChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyUpnpOrgAVTransport1(CpDevice aDevice)
    {
        super("schemas-upnp-org", "AVTransport", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionSetAVTransportURI = new Action("SetAVTransportURI");
        param = new ParameterUint("InstanceID");
        iActionSetAVTransportURI.addInputParameter(param);
        param = new ParameterString("CurrentURI", allowedValues);
        iActionSetAVTransportURI.addInputParameter(param);
        param = new ParameterString("CurrentURIMetaData", allowedValues);
        iActionSetAVTransportURI.addInputParameter(param);

        iActionSetNextAVTransportURI = new Action("SetNextAVTransportURI");
        param = new ParameterUint("InstanceID");
        iActionSetNextAVTransportURI.addInputParameter(param);
        param = new ParameterString("NextURI", allowedValues);
        iActionSetNextAVTransportURI.addInputParameter(param);
        param = new ParameterString("NextURIMetaData", allowedValues);
        iActionSetNextAVTransportURI.addInputParameter(param);

        iActionGetMediaInfo = new Action("GetMediaInfo");
        param = new ParameterUint("InstanceID");
        iActionGetMediaInfo.addInputParameter(param);
        param = new ParameterUint("NrTracks", 0, 2147483647);
        iActionGetMediaInfo.addOutputParameter(param);
        param = new ParameterString("MediaDuration", allowedValues);
        iActionGetMediaInfo.addOutputParameter(param);
        param = new ParameterString("CurrentURI", allowedValues);
        iActionGetMediaInfo.addOutputParameter(param);
        param = new ParameterString("CurrentURIMetaData", allowedValues);
        iActionGetMediaInfo.addOutputParameter(param);
        param = new ParameterString("NextURI", allowedValues);
        iActionGetMediaInfo.addOutputParameter(param);
        param = new ParameterString("NextURIMetaData", allowedValues);
        iActionGetMediaInfo.addOutputParameter(param);
        param = new ParameterString("PlayMedium", allowedValues);
        iActionGetMediaInfo.addOutputParameter(param);
        param = new ParameterString("RecordMedium", allowedValues);
        iActionGetMediaInfo.addOutputParameter(param);
        allowedValues.add("WRITABLE");
        allowedValues.add("PROTECTED");
        allowedValues.add("NOT_WRITABLE");
        allowedValues.add("UNKNOWN");
        allowedValues.add("NOT_IMPLEMENTED");
        param = new ParameterString("WriteStatus", allowedValues);
        iActionGetMediaInfo.addOutputParameter(param);
        allowedValues.clear();

        iActionGetTransportInfo = new Action("GetTransportInfo");
        param = new ParameterUint("InstanceID");
        iActionGetTransportInfo.addInputParameter(param);
        allowedValues.add("STOPPED");
        allowedValues.add("PLAYING");
        allowedValues.add("TRANSITIONING");
        allowedValues.add("PAUSED_PLAYBACK");
        allowedValues.add("PAUSED_RECORDING");
        allowedValues.add("RECORDING");
        allowedValues.add("NO_MEDIA_PRESENT");
        param = new ParameterString("CurrentTransportState", allowedValues);
        iActionGetTransportInfo.addOutputParameter(param);
        allowedValues.clear();
        allowedValues.add("OK");
        allowedValues.add("ERROR_OCCURRED");
        param = new ParameterString("CurrentTransportStatus", allowedValues);
        iActionGetTransportInfo.addOutputParameter(param);
        allowedValues.clear();
        param = new ParameterString("CurrentSpeed", allowedValues);
        iActionGetTransportInfo.addOutputParameter(param);

        iActionGetPositionInfo = new Action("GetPositionInfo");
        param = new ParameterUint("InstanceID");
        iActionGetPositionInfo.addInputParameter(param);
        param = new ParameterUint("Track", 0, 2147483647, 1);
        iActionGetPositionInfo.addOutputParameter(param);
        param = new ParameterString("TrackDuration", allowedValues);
        iActionGetPositionInfo.addOutputParameter(param);
        param = new ParameterString("TrackMetaData", allowedValues);
        iActionGetPositionInfo.addOutputParameter(param);
        param = new ParameterString("TrackURI", allowedValues);
        iActionGetPositionInfo.addOutputParameter(param);
        param = new ParameterString("RelTime", allowedValues);
        iActionGetPositionInfo.addOutputParameter(param);
        param = new ParameterString("AbsTime", allowedValues);
        iActionGetPositionInfo.addOutputParameter(param);
        param = new ParameterInt("RelCount");
        iActionGetPositionInfo.addOutputParameter(param);
        param = new ParameterInt("AbsCount");
        iActionGetPositionInfo.addOutputParameter(param);

        iActionGetDeviceCapabilities = new Action("GetDeviceCapabilities");
        param = new ParameterUint("InstanceID");
        iActionGetDeviceCapabilities.addInputParameter(param);
        param = new ParameterString("PlayMedia", allowedValues);
        iActionGetDeviceCapabilities.addOutputParameter(param);
        param = new ParameterString("RecMedia", allowedValues);
        iActionGetDeviceCapabilities.addOutputParameter(param);
        param = new ParameterString("RecQualityModes", allowedValues);
        iActionGetDeviceCapabilities.addOutputParameter(param);

        iActionGetTransportSettings = new Action("GetTransportSettings");
        param = new ParameterUint("InstanceID");
        iActionGetTransportSettings.addInputParameter(param);
        allowedValues.add("NORMAL");
        param = new ParameterString("PlayMode", allowedValues);
        iActionGetTransportSettings.addOutputParameter(param);
        allowedValues.clear();
        param = new ParameterString("RecQualityMode", allowedValues);
        iActionGetTransportSettings.addOutputParameter(param);

        iActionStop = new Action("Stop");
        param = new ParameterUint("InstanceID");
        iActionStop.addInputParameter(param);

        iActionPlay = new Action("Play");
        param = new ParameterUint("InstanceID");
        iActionPlay.addInputParameter(param);
        param = new ParameterString("Speed", allowedValues);
        iActionPlay.addInputParameter(param);

        iActionPause = new Action("Pause");
        param = new ParameterUint("InstanceID");
        iActionPause.addInputParameter(param);

        iActionRecord = new Action("Record");
        param = new ParameterUint("InstanceID");
        iActionRecord.addInputParameter(param);

        iActionSeek = new Action("Seek");
        param = new ParameterUint("InstanceID");
        iActionSeek.addInputParameter(param);
        allowedValues.add("TRACK_NR");
        allowedValues.add("ABS_TIME");
        allowedValues.add("REL_TIME");
        allowedValues.add("ABS_COUNT");
        allowedValues.add("REL_COUNT");
        allowedValues.add("CHANNEL_FREQ");
        allowedValues.add("TAPE-INDEX");
        allowedValues.add("FRAME");
        param = new ParameterString("Unit", allowedValues);
        iActionSeek.addInputParameter(param);
        allowedValues.clear();
        param = new ParameterString("Target", allowedValues);
        iActionSeek.addInputParameter(param);

        iActionNext = new Action("Next");
        param = new ParameterUint("InstanceID");
        iActionNext.addInputParameter(param);

        iActionPrevious = new Action("Previous");
        param = new ParameterUint("InstanceID");
        iActionPrevious.addInputParameter(param);

        iActionSetPlayMode = new Action("SetPlayMode");
        param = new ParameterUint("InstanceID");
        iActionSetPlayMode.addInputParameter(param);
        allowedValues.add("NORMAL");
        param = new ParameterString("NewPlayMode", allowedValues);
        iActionSetPlayMode.addInputParameter(param);
        allowedValues.clear();

        iActionSetRecordQualityMode = new Action("SetRecordQualityMode");
        param = new ParameterUint("InstanceID");
        iActionSetRecordQualityMode.addInputParameter(param);
        param = new ParameterString("NewRecordQualityMode", allowedValues);
        iActionSetRecordQualityMode.addInputParameter(param);

        iActionGetCurrentTransportActions = new Action("GetCurrentTransportActions");
        param = new ParameterUint("InstanceID");
        iActionGetCurrentTransportActions.addInputParameter(param);
        param = new ParameterString("Actions", allowedValues);
        iActionGetCurrentTransportActions.addOutputParameter(param);

        iLastChangeChanged = new PropertyChangeListener();
        iLastChange = new PropertyString("LastChange",
            new PropertyChangeListener() {
                public void notifyChange() {
                    lastChangePropertyChanged();
                }
            }
        );
        addProperty(iLastChange);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetAVTransportURI(long aInstanceID, String aCurrentURI, String aCurrentURIMetaData)
    {
        SyncSetAVTransportURIUpnpOrgAVTransport1 sync = new SyncSetAVTransportURIUpnpOrgAVTransport1(this);
        beginSetAVTransportURI(aInstanceID, aCurrentURI, aCurrentURIMetaData, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetAVTransportURI}.
     * 
     * @param aInstanceID
     * @param aCurrentURI
     * @param aCurrentURIMetaData
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetAVTransportURI(long aInstanceID, String aCurrentURI, String aCurrentURIMetaData, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetAVTransportURI, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetAVTransportURI.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetAVTransportURI.getInputParameter(inIndex++), aCurrentURI));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetAVTransportURI.getInputParameter(inIndex++), aCurrentURIMetaData));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetAVTransportURI} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetAVTransportURI} method.
     */
    public void endSetAVTransportURI(long aAsyncHandle)
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
    public void syncSetNextAVTransportURI(long aInstanceID, String aNextURI, String aNextURIMetaData)
    {
        SyncSetNextAVTransportURIUpnpOrgAVTransport1 sync = new SyncSetNextAVTransportURIUpnpOrgAVTransport1(this);
        beginSetNextAVTransportURI(aInstanceID, aNextURI, aNextURIMetaData, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetNextAVTransportURI}.
     * 
     * @param aInstanceID
     * @param aNextURI
     * @param aNextURIMetaData
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetNextAVTransportURI(long aInstanceID, String aNextURI, String aNextURIMetaData, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetNextAVTransportURI, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetNextAVTransportURI.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetNextAVTransportURI.getInputParameter(inIndex++), aNextURI));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetNextAVTransportURI.getInputParameter(inIndex++), aNextURIMetaData));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetNextAVTransportURI} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetNextAVTransportURI} method.
     */
    public void endSetNextAVTransportURI(long aAsyncHandle)
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
    public GetMediaInfo syncGetMediaInfo(long aInstanceID)
    {
        SyncGetMediaInfoUpnpOrgAVTransport1 sync = new SyncGetMediaInfoUpnpOrgAVTransport1(this);
        beginGetMediaInfo(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetMediaInfo(
            sync.getNrTracks(),
            sync.getMediaDuration(),
            sync.getCurrentURI(),
            sync.getCurrentURIMetaData(),
            sync.getNextURI(),
            sync.getNextURIMetaData(),
            sync.getPlayMedium(),
            sync.getRecordMedium(),
            sync.getWriteStatus()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetMediaInfo}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetMediaInfo(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetMediaInfo, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetMediaInfo.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetMediaInfo.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetMediaInfo} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetMediaInfo} method.
     * @return the result of the previously invoked action.
     */
    public GetMediaInfo endGetMediaInfo(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long nrTracks = Invocation.getOutputUint(aAsyncHandle, index++);
        String mediaDuration = Invocation.getOutputString(aAsyncHandle, index++);
        String currentURI = Invocation.getOutputString(aAsyncHandle, index++);
        String currentURIMetaData = Invocation.getOutputString(aAsyncHandle, index++);
        String nextURI = Invocation.getOutputString(aAsyncHandle, index++);
        String nextURIMetaData = Invocation.getOutputString(aAsyncHandle, index++);
        String playMedium = Invocation.getOutputString(aAsyncHandle, index++);
        String recordMedium = Invocation.getOutputString(aAsyncHandle, index++);
        String writeStatus = Invocation.getOutputString(aAsyncHandle, index++);
        return new GetMediaInfo(
            nrTracks,
            mediaDuration,
            currentURI,
            currentURIMetaData,
            nextURI,
            nextURIMetaData,
            playMedium,
            recordMedium,
            writeStatus
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetTransportInfo syncGetTransportInfo(long aInstanceID)
    {
        SyncGetTransportInfoUpnpOrgAVTransport1 sync = new SyncGetTransportInfoUpnpOrgAVTransport1(this);
        beginGetTransportInfo(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetTransportInfo(
            sync.getCurrentTransportState(),
            sync.getCurrentTransportStatus(),
            sync.getCurrentSpeed()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetTransportInfo}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetTransportInfo(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetTransportInfo, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetTransportInfo.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetTransportInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetTransportInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetTransportInfo.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetTransportInfo} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetTransportInfo} method.
     * @return the result of the previously invoked action.
     */
    public GetTransportInfo endGetTransportInfo(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String currentTransportState = Invocation.getOutputString(aAsyncHandle, index++);
        String currentTransportStatus = Invocation.getOutputString(aAsyncHandle, index++);
        String currentSpeed = Invocation.getOutputString(aAsyncHandle, index++);
        return new GetTransportInfo(
            currentTransportState,
            currentTransportStatus,
            currentSpeed
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetPositionInfo syncGetPositionInfo(long aInstanceID)
    {
        SyncGetPositionInfoUpnpOrgAVTransport1 sync = new SyncGetPositionInfoUpnpOrgAVTransport1(this);
        beginGetPositionInfo(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetPositionInfo(
            sync.getTrack(),
            sync.getTrackDuration(),
            sync.getTrackMetaData(),
            sync.getTrackURI(),
            sync.getRelTime(),
            sync.getAbsTime(),
            sync.getRelCount(),
            sync.getAbsCount()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetPositionInfo}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetPositionInfo(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetPositionInfo, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetPositionInfo.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetPositionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetPositionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetPositionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetPositionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetPositionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetPositionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetPositionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetPositionInfo.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetPositionInfo} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetPositionInfo} method.
     * @return the result of the previously invoked action.
     */
    public GetPositionInfo endGetPositionInfo(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long track = Invocation.getOutputUint(aAsyncHandle, index++);
        String trackDuration = Invocation.getOutputString(aAsyncHandle, index++);
        String trackMetaData = Invocation.getOutputString(aAsyncHandle, index++);
        String trackURI = Invocation.getOutputString(aAsyncHandle, index++);
        String relTime = Invocation.getOutputString(aAsyncHandle, index++);
        String absTime = Invocation.getOutputString(aAsyncHandle, index++);
        int relCount = Invocation.getOutputInt(aAsyncHandle, index++);
        int absCount = Invocation.getOutputInt(aAsyncHandle, index++);
        return new GetPositionInfo(
            track,
            trackDuration,
            trackMetaData,
            trackURI,
            relTime,
            absTime,
            relCount,
            absCount
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetDeviceCapabilities syncGetDeviceCapabilities(long aInstanceID)
    {
        SyncGetDeviceCapabilitiesUpnpOrgAVTransport1 sync = new SyncGetDeviceCapabilitiesUpnpOrgAVTransport1(this);
        beginGetDeviceCapabilities(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetDeviceCapabilities(
            sync.getPlayMedia(),
            sync.getRecMedia(),
            sync.getRecQualityModes()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetDeviceCapabilities}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetDeviceCapabilities(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetDeviceCapabilities, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetDeviceCapabilities.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetDeviceCapabilities.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetDeviceCapabilities.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetDeviceCapabilities.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetDeviceCapabilities} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetDeviceCapabilities} method.
     * @return the result of the previously invoked action.
     */
    public GetDeviceCapabilities endGetDeviceCapabilities(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String playMedia = Invocation.getOutputString(aAsyncHandle, index++);
        String recMedia = Invocation.getOutputString(aAsyncHandle, index++);
        String recQualityModes = Invocation.getOutputString(aAsyncHandle, index++);
        return new GetDeviceCapabilities(
            playMedia,
            recMedia,
            recQualityModes
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetTransportSettings syncGetTransportSettings(long aInstanceID)
    {
        SyncGetTransportSettingsUpnpOrgAVTransport1 sync = new SyncGetTransportSettingsUpnpOrgAVTransport1(this);
        beginGetTransportSettings(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetTransportSettings(
            sync.getPlayMode(),
            sync.getRecQualityMode()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetTransportSettings}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetTransportSettings(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetTransportSettings, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetTransportSettings.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetTransportSettings.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetTransportSettings.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetTransportSettings} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetTransportSettings} method.
     * @return the result of the previously invoked action.
     */
    public GetTransportSettings endGetTransportSettings(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String playMode = Invocation.getOutputString(aAsyncHandle, index++);
        String recQualityMode = Invocation.getOutputString(aAsyncHandle, index++);
        return new GetTransportSettings(
            playMode,
            recQualityMode
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncStop(long aInstanceID)
    {
        SyncStopUpnpOrgAVTransport1 sync = new SyncStopUpnpOrgAVTransport1(this);
        beginStop(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStop}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStop(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStop, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionStop.getInputParameter(inIndex++), aInstanceID));
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
    public void syncPlay(long aInstanceID, String aSpeed)
    {
        SyncPlayUpnpOrgAVTransport1 sync = new SyncPlayUpnpOrgAVTransport1(this);
        beginPlay(aInstanceID, aSpeed, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPlay}.
     * 
     * @param aInstanceID
     * @param aSpeed
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPlay(long aInstanceID, String aSpeed, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPlay, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlay.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionPlay.getInputParameter(inIndex++), aSpeed));
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
    public void syncPause(long aInstanceID)
    {
        SyncPauseUpnpOrgAVTransport1 sync = new SyncPauseUpnpOrgAVTransport1(this);
        beginPause(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPause}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPause(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPause, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPause.getInputParameter(inIndex++), aInstanceID));
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
    public void syncRecord(long aInstanceID)
    {
        SyncRecordUpnpOrgAVTransport1 sync = new SyncRecordUpnpOrgAVTransport1(this);
        beginRecord(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endRecord}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginRecord(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionRecord, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionRecord.getInputParameter(inIndex++), aInstanceID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginRecord} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginRecord} method.
     */
    public void endRecord(long aAsyncHandle)
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
    public void syncSeek(long aInstanceID, String aUnit, String aTarget)
    {
        SyncSeekUpnpOrgAVTransport1 sync = new SyncSeekUpnpOrgAVTransport1(this);
        beginSeek(aInstanceID, aUnit, aTarget, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSeek}.
     * 
     * @param aInstanceID
     * @param aUnit
     * @param aTarget
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSeek(long aInstanceID, String aUnit, String aTarget, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSeek, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSeek.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSeek.getInputParameter(inIndex++), aUnit));
        invocation.addInput(new ArgumentString((ParameterString)iActionSeek.getInputParameter(inIndex++), aTarget));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSeek} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSeek} method.
     */
    public void endSeek(long aAsyncHandle)
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
    public void syncNext(long aInstanceID)
    {
        SyncNextUpnpOrgAVTransport1 sync = new SyncNextUpnpOrgAVTransport1(this);
        beginNext(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endNext}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginNext(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionNext, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionNext.getInputParameter(inIndex++), aInstanceID));
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
    public void syncPrevious(long aInstanceID)
    {
        SyncPreviousUpnpOrgAVTransport1 sync = new SyncPreviousUpnpOrgAVTransport1(this);
        beginPrevious(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPrevious}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPrevious(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPrevious, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPrevious.getInputParameter(inIndex++), aInstanceID));
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
    public void syncSetPlayMode(long aInstanceID, String aNewPlayMode)
    {
        SyncSetPlayModeUpnpOrgAVTransport1 sync = new SyncSetPlayModeUpnpOrgAVTransport1(this);
        beginSetPlayMode(aInstanceID, aNewPlayMode, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetPlayMode}.
     * 
     * @param aInstanceID
     * @param aNewPlayMode
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetPlayMode(long aInstanceID, String aNewPlayMode, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetPlayMode, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetPlayMode.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetPlayMode.getInputParameter(inIndex++), aNewPlayMode));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetPlayMode} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetPlayMode} method.
     */
    public void endSetPlayMode(long aAsyncHandle)
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
    public void syncSetRecordQualityMode(long aInstanceID, String aNewRecordQualityMode)
    {
        SyncSetRecordQualityModeUpnpOrgAVTransport1 sync = new SyncSetRecordQualityModeUpnpOrgAVTransport1(this);
        beginSetRecordQualityMode(aInstanceID, aNewRecordQualityMode, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetRecordQualityMode}.
     * 
     * @param aInstanceID
     * @param aNewRecordQualityMode
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetRecordQualityMode(long aInstanceID, String aNewRecordQualityMode, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetRecordQualityMode, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetRecordQualityMode.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetRecordQualityMode.getInputParameter(inIndex++), aNewRecordQualityMode));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetRecordQualityMode} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetRecordQualityMode} method.
     */
    public void endSetRecordQualityMode(long aAsyncHandle)
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
    public String syncGetCurrentTransportActions(long aInstanceID)
    {
        SyncGetCurrentTransportActionsUpnpOrgAVTransport1 sync = new SyncGetCurrentTransportActionsUpnpOrgAVTransport1(this);
        beginGetCurrentTransportActions(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getActions();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetCurrentTransportActions}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetCurrentTransportActions(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetCurrentTransportActions, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetCurrentTransportActions.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetCurrentTransportActions.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetCurrentTransportActions} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetCurrentTransportActions} method.
     * @return the result of the previously invoked action.
     */
    public String endGetCurrentTransportActions(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String actions = Invocation.getOutputString(aAsyncHandle, index++);
        return actions;
    }
        
    /**
     * Set a delegate to be run when the LastChange state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgAVTransport1 instance will not overlap.
     *
     * @param aLastChangeChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyLastChangeChanged(IPropertyChangeListener aLastChangeChanged)
    {
        synchronized (iPropertyLock)
        {
            iLastChangeChanged = aLastChangeChanged;
        }
    }

    private void lastChangePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iLastChangeChanged);
        }
    }

    /**
     * Query the value of the LastChange property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the LastChange property.
     */
    public String getPropertyLastChange()
    {
        propertyReadLock();
        String val = iLastChange.getValue();
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
            iActionSetAVTransportURI.destroy();
            iActionSetNextAVTransportURI.destroy();
            iActionGetMediaInfo.destroy();
            iActionGetTransportInfo.destroy();
            iActionGetPositionInfo.destroy();
            iActionGetDeviceCapabilities.destroy();
            iActionGetTransportSettings.destroy();
            iActionStop.destroy();
            iActionPlay.destroy();
            iActionPause.destroy();
            iActionRecord.destroy();
            iActionSeek.destroy();
            iActionNext.destroy();
            iActionPrevious.destroy();
            iActionSetPlayMode.destroy();
            iActionSetRecordQualityMode.destroy();
            iActionGetCurrentTransportActions.destroy();
            iLastChange.destroy();
        }
    }
}

