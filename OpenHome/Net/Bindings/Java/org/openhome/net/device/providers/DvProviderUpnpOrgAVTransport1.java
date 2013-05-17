package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderUpnpOrgAVTransport1
{

    /**
     * Set the value of the LastChange property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyLastChange(String aValue);

    /**
     * Get a copy of the value of the LastChange property
     *
     * @return value of the LastChange property.
     */
    public String getPropertyLastChange();
        
}

/**
 * Provider for the upnp.org:AVTransport:1 UPnP service.
 */
public class DvProviderUpnpOrgAVTransport1 extends DvProvider implements IDvProviderUpnpOrgAVTransport1
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

    private IDvInvocationListener iDelegateSetAVTransportURI;
    private IDvInvocationListener iDelegateSetNextAVTransportURI;
    private IDvInvocationListener iDelegateGetMediaInfo;
    private IDvInvocationListener iDelegateGetTransportInfo;
    private IDvInvocationListener iDelegateGetPositionInfo;
    private IDvInvocationListener iDelegateGetDeviceCapabilities;
    private IDvInvocationListener iDelegateGetTransportSettings;
    private IDvInvocationListener iDelegateStop;
    private IDvInvocationListener iDelegatePlay;
    private IDvInvocationListener iDelegatePause;
    private IDvInvocationListener iDelegateRecord;
    private IDvInvocationListener iDelegateSeek;
    private IDvInvocationListener iDelegateNext;
    private IDvInvocationListener iDelegatePrevious;
    private IDvInvocationListener iDelegateSetPlayMode;
    private IDvInvocationListener iDelegateSetRecordQualityMode;
    private IDvInvocationListener iDelegateGetCurrentTransportActions;
    private PropertyString iPropertyLastChange;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderUpnpOrgAVTransport1(DvDevice aDevice)
    {
        super(aDevice, "upnp.org", "AVTransport", 1);
    }

    /**
     * Enable the LastChange property.
     */
    public void enablePropertyLastChange()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
        addProperty(iPropertyLastChange);
    }

    /**
     * Set the value of the LastChange property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyLastChange(String aValue)
    {
        return setPropertyString(iPropertyLastChange, aValue);
    }

    /**
     * Get a copy of the value of the LastChange property
     *
     * @return  value of the LastChange property.
     */
    public String getPropertyLastChange()
    {
        return iPropertyLastChange.getValue();
    }

    /**
     * Signal that the action SetAVTransportURI is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetAVTransportURI must be overridden if this is called.
     */      
    protected void enableActionSetAVTransportURI()
    {
        Action action = new Action("SetAVTransportURI");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("CurrentURI", allowedValues));
        action.addInputParameter(new ParameterString("CurrentURIMetaData", allowedValues));
        iDelegateSetAVTransportURI = new DoSetAVTransportURI();
        enableAction(action, iDelegateSetAVTransportURI);
    }

    /**
     * Signal that the action SetNextAVTransportURI is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetNextAVTransportURI must be overridden if this is called.
     */      
    protected void enableActionSetNextAVTransportURI()
    {
        Action action = new Action("SetNextAVTransportURI");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("NextURI", allowedValues));
        action.addInputParameter(new ParameterString("NextURIMetaData", allowedValues));
        iDelegateSetNextAVTransportURI = new DoSetNextAVTransportURI();
        enableAction(action, iDelegateSetNextAVTransportURI);
    }

    /**
     * Signal that the action GetMediaInfo is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetMediaInfo must be overridden if this is called.
     */      
    protected void enableActionGetMediaInfo()
    {
        Action action = new Action("GetMediaInfo");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("NrTracks", 0, 2147483647));
        action.addOutputParameter(new ParameterString("MediaDuration", allowedValues));
        action.addOutputParameter(new ParameterString("CurrentURI", allowedValues));
        action.addOutputParameter(new ParameterString("CurrentURIMetaData", allowedValues));
        action.addOutputParameter(new ParameterString("NextURI", allowedValues));
        action.addOutputParameter(new ParameterString("NextURIMetaData", allowedValues));
        action.addOutputParameter(new ParameterString("PlayMedium", allowedValues));
        action.addOutputParameter(new ParameterString("RecordMedium", allowedValues));
        allowedValues.add("WRITABLE");
        allowedValues.add("PROTECTED");
        allowedValues.add("NOT_WRITABLE");
        allowedValues.add("UNKNOWN");
        allowedValues.add("NOT_IMPLEMENTED");
        action.addOutputParameter(new ParameterString("WriteStatus", allowedValues));
        allowedValues.clear();
        iDelegateGetMediaInfo = new DoGetMediaInfo();
        enableAction(action, iDelegateGetMediaInfo);
    }

    /**
     * Signal that the action GetTransportInfo is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetTransportInfo must be overridden if this is called.
     */      
    protected void enableActionGetTransportInfo()
    {
        Action action = new Action("GetTransportInfo");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        allowedValues.add("STOPPED");
        allowedValues.add("PLAYING");
        allowedValues.add("TRANSITIONING");
        allowedValues.add("PAUSED_PLAYBACK");
        allowedValues.add("PAUSED_RECORDING");
        allowedValues.add("RECORDING");
        allowedValues.add("NO_MEDIA_PRESENT");
        action.addOutputParameter(new ParameterString("CurrentTransportState", allowedValues));
        allowedValues.clear();
        allowedValues.add("OK");
        allowedValues.add("ERROR_OCCURRED");
        action.addOutputParameter(new ParameterString("CurrentTransportStatus", allowedValues));
        allowedValues.clear();
        action.addOutputParameter(new ParameterString("CurrentSpeed", allowedValues));
        iDelegateGetTransportInfo = new DoGetTransportInfo();
        enableAction(action, iDelegateGetTransportInfo);
    }

    /**
     * Signal that the action GetPositionInfo is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetPositionInfo must be overridden if this is called.
     */      
    protected void enableActionGetPositionInfo()
    {
        Action action = new Action("GetPositionInfo");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("Track", 0, 2147483647, 1));
        action.addOutputParameter(new ParameterString("TrackDuration", allowedValues));
        action.addOutputParameter(new ParameterString("TrackMetaData", allowedValues));
        action.addOutputParameter(new ParameterString("TrackURI", allowedValues));
        action.addOutputParameter(new ParameterString("RelTime", allowedValues));
        action.addOutputParameter(new ParameterString("AbsTime", allowedValues));
        action.addOutputParameter(new ParameterInt("RelCount"));
        action.addOutputParameter(new ParameterInt("AbsCount"));
        iDelegateGetPositionInfo = new DoGetPositionInfo();
        enableAction(action, iDelegateGetPositionInfo);
    }

    /**
     * Signal that the action GetDeviceCapabilities is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetDeviceCapabilities must be overridden if this is called.
     */      
    protected void enableActionGetDeviceCapabilities()
    {
        Action action = new Action("GetDeviceCapabilities");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterString("PlayMedia", allowedValues));
        action.addOutputParameter(new ParameterString("RecMedia", allowedValues));
        action.addOutputParameter(new ParameterString("RecQualityModes", allowedValues));
        iDelegateGetDeviceCapabilities = new DoGetDeviceCapabilities();
        enableAction(action, iDelegateGetDeviceCapabilities);
    }

    /**
     * Signal that the action GetTransportSettings is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetTransportSettings must be overridden if this is called.
     */      
    protected void enableActionGetTransportSettings()
    {
        Action action = new Action("GetTransportSettings");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        allowedValues.add("NORMAL");
        action.addOutputParameter(new ParameterString("PlayMode", allowedValues));
        allowedValues.clear();
        action.addOutputParameter(new ParameterString("RecQualityMode", allowedValues));
        iDelegateGetTransportSettings = new DoGetTransportSettings();
        enableAction(action, iDelegateGetTransportSettings);
    }

    /**
     * Signal that the action Stop is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Stop must be overridden if this is called.
     */      
    protected void enableActionStop()
    {
        Action action = new Action("Stop");
        action.addInputParameter(new ParameterUint("InstanceID"));
        iDelegateStop = new DoStop();
        enableAction(action, iDelegateStop);
    }

    /**
     * Signal that the action Play is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Play must be overridden if this is called.
     */      
    protected void enableActionPlay()
    {
        Action action = new Action("Play");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Speed", allowedValues));
        iDelegatePlay = new DoPlay();
        enableAction(action, iDelegatePlay);
    }

    /**
     * Signal that the action Pause is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Pause must be overridden if this is called.
     */      
    protected void enableActionPause()
    {
        Action action = new Action("Pause");
        action.addInputParameter(new ParameterUint("InstanceID"));
        iDelegatePause = new DoPause();
        enableAction(action, iDelegatePause);
    }

    /**
     * Signal that the action Record is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Record must be overridden if this is called.
     */      
    protected void enableActionRecord()
    {
        Action action = new Action("Record");
        action.addInputParameter(new ParameterUint("InstanceID"));
        iDelegateRecord = new DoRecord();
        enableAction(action, iDelegateRecord);
    }

    /**
     * Signal that the action Seek is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Seek must be overridden if this is called.
     */      
    protected void enableActionSeek()
    {
        Action action = new Action("Seek");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        allowedValues.add("TRACK_NR");
        allowedValues.add("ABS_TIME");
        allowedValues.add("REL_TIME");
        allowedValues.add("ABS_COUNT");
        allowedValues.add("REL_COUNT");
        allowedValues.add("CHANNEL_FREQ");
        allowedValues.add("TAPE-INDEX");
        allowedValues.add("FRAME");
        action.addInputParameter(new ParameterString("Unit", allowedValues));
        allowedValues.clear();
        action.addInputParameter(new ParameterString("Target", allowedValues));
        iDelegateSeek = new DoSeek();
        enableAction(action, iDelegateSeek);
    }

    /**
     * Signal that the action Next is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Next must be overridden if this is called.
     */      
    protected void enableActionNext()
    {
        Action action = new Action("Next");
        action.addInputParameter(new ParameterUint("InstanceID"));
        iDelegateNext = new DoNext();
        enableAction(action, iDelegateNext);
    }

    /**
     * Signal that the action Previous is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Previous must be overridden if this is called.
     */      
    protected void enableActionPrevious()
    {
        Action action = new Action("Previous");
        action.addInputParameter(new ParameterUint("InstanceID"));
        iDelegatePrevious = new DoPrevious();
        enableAction(action, iDelegatePrevious);
    }

    /**
     * Signal that the action SetPlayMode is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetPlayMode must be overridden if this is called.
     */      
    protected void enableActionSetPlayMode()
    {
        Action action = new Action("SetPlayMode");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        allowedValues.add("NORMAL");
        action.addInputParameter(new ParameterString("NewPlayMode", allowedValues));
        allowedValues.clear();
        iDelegateSetPlayMode = new DoSetPlayMode();
        enableAction(action, iDelegateSetPlayMode);
    }

    /**
     * Signal that the action SetRecordQualityMode is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetRecordQualityMode must be overridden if this is called.
     */      
    protected void enableActionSetRecordQualityMode()
    {
        Action action = new Action("SetRecordQualityMode");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("NewRecordQualityMode", allowedValues));
        iDelegateSetRecordQualityMode = new DoSetRecordQualityMode();
        enableAction(action, iDelegateSetRecordQualityMode);
    }

    /**
     * Signal that the action GetCurrentTransportActions is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetCurrentTransportActions must be overridden if this is called.
     */      
    protected void enableActionGetCurrentTransportActions()
    {
        Action action = new Action("GetCurrentTransportActions");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterString("Actions", allowedValues));
        iDelegateGetCurrentTransportActions = new DoGetCurrentTransportActions();
        enableAction(action, iDelegateGetCurrentTransportActions);
    }

    /**
     * SetAVTransportURI action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetAVTransportURI action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetAVTransportURI} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aCurrentURI
     * @param aCurrentURIMetaData
     */
    protected void setAVTransportURI(IDvInvocation aInvocation, long aInstanceID, String aCurrentURI, String aCurrentURIMetaData)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetNextAVTransportURI action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetNextAVTransportURI action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetNextAVTransportURI} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aNextURI
     * @param aNextURIMetaData
     */
    protected void setNextAVTransportURI(IDvInvocation aInvocation, long aInstanceID, String aNextURI, String aNextURIMetaData)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetMediaInfo action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetMediaInfo action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetMediaInfo} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected GetMediaInfo getMediaInfo(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetTransportInfo action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetTransportInfo action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetTransportInfo} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected GetTransportInfo getTransportInfo(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetPositionInfo action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetPositionInfo action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetPositionInfo} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected GetPositionInfo getPositionInfo(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetDeviceCapabilities action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetDeviceCapabilities action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetDeviceCapabilities} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected GetDeviceCapabilities getDeviceCapabilities(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetTransportSettings action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetTransportSettings action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetTransportSettings} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected GetTransportSettings getTransportSettings(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Stop action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Stop action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStop} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected void stop(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Play action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Play action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlay} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aSpeed
     */
    protected void play(IDvInvocation aInvocation, long aInstanceID, String aSpeed)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Pause action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Pause action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPause} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected void pause(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Record action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Record action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionRecord} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected void record(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Seek action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Seek action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSeek} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aUnit
     * @param aTarget
     */
    protected void seek(IDvInvocation aInvocation, long aInstanceID, String aUnit, String aTarget)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Next action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Next action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionNext} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected void next(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Previous action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Previous action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPrevious} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected void previous(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetPlayMode action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetPlayMode action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetPlayMode} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aNewPlayMode
     */
    protected void setPlayMode(IDvInvocation aInvocation, long aInstanceID, String aNewPlayMode)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetRecordQualityMode action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetRecordQualityMode action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetRecordQualityMode} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aNewRecordQualityMode
     */
    protected void setRecordQualityMode(IDvInvocation aInvocation, long aInstanceID, String aNewRecordQualityMode)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetCurrentTransportActions action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetCurrentTransportActions action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetCurrentTransportActions} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected String getCurrentTransportActions(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Must be called for each class instance.  Must be called before Core.Library.Close().
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            super.dispose();
            iHandle = 0;
        }
    }


    private class DoSetAVTransportURI implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String currentURI;
            String currentURIMetaData;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                currentURI = invocation.readString("CurrentURI");
                currentURIMetaData = invocation.readString("CurrentURIMetaData");
                invocation.readEnd();
                setAVTransportURI(invocation, instanceID, currentURI, currentURIMetaData);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetAVTransportURI");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetNextAVTransportURI implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String nextURI;
            String nextURIMetaData;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                nextURI = invocation.readString("NextURI");
                nextURIMetaData = invocation.readString("NextURIMetaData");
                invocation.readEnd();
                setNextAVTransportURI(invocation, instanceID, nextURI, nextURIMetaData);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetNextAVTransportURI");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetMediaInfo implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long nrTracks;
            String mediaDuration;
            String currentURI;
            String currentURIMetaData;
            String nextURI;
            String nextURIMetaData;
            String playMedium;
            String recordMedium;
            String writeStatus;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();

            GetMediaInfo outArgs = getMediaInfo(invocation, instanceID);
            nrTracks = outArgs.getNrTracks();
            mediaDuration = outArgs.getMediaDuration();
            currentURI = outArgs.getCurrentURI();
            currentURIMetaData = outArgs.getCurrentURIMetaData();
            nextURI = outArgs.getNextURI();
            nextURIMetaData = outArgs.getNextURIMetaData();
            playMedium = outArgs.getPlayMedium();
            recordMedium = outArgs.getRecordMedium();
            writeStatus = outArgs.getWriteStatus();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetMediaInfo");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("NrTracks", nrTracks);
                invocation.writeString("MediaDuration", mediaDuration);
                invocation.writeString("CurrentURI", currentURI);
                invocation.writeString("CurrentURIMetaData", currentURIMetaData);
                invocation.writeString("NextURI", nextURI);
                invocation.writeString("NextURIMetaData", nextURIMetaData);
                invocation.writeString("PlayMedium", playMedium);
                invocation.writeString("RecordMedium", recordMedium);
                invocation.writeString("WriteStatus", writeStatus);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetTransportInfo implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String currentTransportState;
            String currentTransportStatus;
            String currentSpeed;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();

            GetTransportInfo outArgs = getTransportInfo(invocation, instanceID);
            currentTransportState = outArgs.getCurrentTransportState();
            currentTransportStatus = outArgs.getCurrentTransportStatus();
            currentSpeed = outArgs.getCurrentSpeed();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetTransportInfo");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("CurrentTransportState", currentTransportState);
                invocation.writeString("CurrentTransportStatus", currentTransportStatus);
                invocation.writeString("CurrentSpeed", currentSpeed);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetPositionInfo implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long track;
            String trackDuration;
            String trackMetaData;
            String trackURI;
            String relTime;
            String absTime;
            int relCount;
            int absCount;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();

            GetPositionInfo outArgs = getPositionInfo(invocation, instanceID);
            track = outArgs.getTrack();
            trackDuration = outArgs.getTrackDuration();
            trackMetaData = outArgs.getTrackMetaData();
            trackURI = outArgs.getTrackURI();
            relTime = outArgs.getRelTime();
            absTime = outArgs.getAbsTime();
            relCount = outArgs.getRelCount();
            absCount = outArgs.getAbsCount();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetPositionInfo");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("Track", track);
                invocation.writeString("TrackDuration", trackDuration);
                invocation.writeString("TrackMetaData", trackMetaData);
                invocation.writeString("TrackURI", trackURI);
                invocation.writeString("RelTime", relTime);
                invocation.writeString("AbsTime", absTime);
                invocation.writeInt("RelCount", relCount);
                invocation.writeInt("AbsCount", absCount);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetDeviceCapabilities implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String playMedia;
            String recMedia;
            String recQualityModes;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();

            GetDeviceCapabilities outArgs = getDeviceCapabilities(invocation, instanceID);
            playMedia = outArgs.getPlayMedia();
            recMedia = outArgs.getRecMedia();
            recQualityModes = outArgs.getRecQualityModes();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetDeviceCapabilities");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("PlayMedia", playMedia);
                invocation.writeString("RecMedia", recMedia);
                invocation.writeString("RecQualityModes", recQualityModes);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetTransportSettings implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String playMode;
            String recQualityMode;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();

            GetTransportSettings outArgs = getTransportSettings(invocation, instanceID);
            playMode = outArgs.getPlayMode();
            recQualityMode = outArgs.getRecQualityMode();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetTransportSettings");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("PlayMode", playMode);
                invocation.writeString("RecQualityMode", recQualityMode);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoStop implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                stop(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Stop");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoPlay implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String speed;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                speed = invocation.readString("Speed");
                invocation.readEnd();
                play(invocation, instanceID, speed);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Play");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoPause implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                pause(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Pause");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoRecord implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                record(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Record");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSeek implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String unit;
            String target;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                unit = invocation.readString("Unit");
                target = invocation.readString("Target");
                invocation.readEnd();
                seek(invocation, instanceID, unit, target);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Seek");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoNext implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                next(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Next");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoPrevious implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                previous(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Previous");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetPlayMode implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String newPlayMode;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                newPlayMode = invocation.readString("NewPlayMode");
                invocation.readEnd();
                setPlayMode(invocation, instanceID, newPlayMode);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetPlayMode");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetRecordQualityMode implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String newRecordQualityMode;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                newRecordQualityMode = invocation.readString("NewRecordQualityMode");
                invocation.readEnd();
                setRecordQualityMode(invocation, instanceID, newRecordQualityMode);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetRecordQualityMode");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetCurrentTransportActions implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String actions;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 actions = getCurrentTransportActions(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetCurrentTransportActions");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("Actions", actions);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }
}

