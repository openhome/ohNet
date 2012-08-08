package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderAvOpenhomeOrgPlaylist1
{

    /**
     * Set the value of the TransportState property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyTransportState(String aValue);

    /**
     * Get a copy of the value of the TransportState property
     *
     * @return value of the TransportState property.
     */
    public String getPropertyTransportState();

    /**
     * Set the value of the Repeat property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyRepeat(boolean aValue);

    /**
     * Get a copy of the value of the Repeat property
     *
     * @return value of the Repeat property.
     */
    public boolean getPropertyRepeat();

    /**
     * Set the value of the Shuffle property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyShuffle(boolean aValue);

    /**
     * Get a copy of the value of the Shuffle property
     *
     * @return value of the Shuffle property.
     */
    public boolean getPropertyShuffle();

    /**
     * Set the value of the Id property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyId(long aValue);

    /**
     * Get a copy of the value of the Id property
     *
     * @return value of the Id property.
     */
    public long getPropertyId();

    /**
     * Set the value of the IdArray property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyIdArray(byte[] aValue);

    /**
     * Get a copy of the value of the IdArray property
     *
     * @return value of the IdArray property.
     */
    public byte[] getPropertyIdArray();

    /**
     * Set the value of the TracksMax property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyTracksMax(long aValue);

    /**
     * Get a copy of the value of the TracksMax property
     *
     * @return value of the TracksMax property.
     */
    public long getPropertyTracksMax();

    /**
     * Set the value of the ProtocolInfo property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyProtocolInfo(String aValue);

    /**
     * Get a copy of the value of the ProtocolInfo property
     *
     * @return value of the ProtocolInfo property.
     */
    public String getPropertyProtocolInfo();
        
}

/**
 * Provider for the av.openhome.org:Playlist:1 UPnP service.
 */
public class DvProviderAvOpenhomeOrgPlaylist1 extends DvProvider implements IDvProviderAvOpenhomeOrgPlaylist1
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

    private IDvInvocationListener iDelegatePlay;
    private IDvInvocationListener iDelegatePause;
    private IDvInvocationListener iDelegateStop;
    private IDvInvocationListener iDelegateNext;
    private IDvInvocationListener iDelegatePrevious;
    private IDvInvocationListener iDelegateSetRepeat;
    private IDvInvocationListener iDelegateRepeat;
    private IDvInvocationListener iDelegateSetShuffle;
    private IDvInvocationListener iDelegateShuffle;
    private IDvInvocationListener iDelegateSeekSecondAbsolute;
    private IDvInvocationListener iDelegateSeekSecondRelative;
    private IDvInvocationListener iDelegateSeekId;
    private IDvInvocationListener iDelegateSeekIndex;
    private IDvInvocationListener iDelegateTransportState;
    private IDvInvocationListener iDelegateId;
    private IDvInvocationListener iDelegateRead;
    private IDvInvocationListener iDelegateReadList;
    private IDvInvocationListener iDelegateInsert;
    private IDvInvocationListener iDelegateDeleteId;
    private IDvInvocationListener iDelegateDeleteAll;
    private IDvInvocationListener iDelegateTracksMax;
    private IDvInvocationListener iDelegateIdArray;
    private IDvInvocationListener iDelegateIdArrayChanged;
    private IDvInvocationListener iDelegateProtocolInfo;
    private PropertyString iPropertyTransportState;
    private PropertyBool iPropertyRepeat;
    private PropertyBool iPropertyShuffle;
    private PropertyUint iPropertyId;
    private PropertyBinary iPropertyIdArray;
    private PropertyUint iPropertyTracksMax;
    private PropertyString iPropertyProtocolInfo;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderAvOpenhomeOrgPlaylist1(DvDevice aDevice)
    {
        super(aDevice, "av.openhome.org", "Playlist", 1);
    }

    /**
     * Enable the TransportState property.
     */
    public void enablePropertyTransportState()
    {
        List<String> allowedValues = new LinkedList<String>();
        allowedValues.add("Playing");
        allowedValues.add("Paused");
        allowedValues.add("Stopped");
        allowedValues.add("Buffering");
        iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues));
        addProperty(iPropertyTransportState);
            allowedValues.clear();
    }

    /**
     * Enable the Repeat property.
     */
    public void enablePropertyRepeat()
    {
        iPropertyRepeat = new PropertyBool(new ParameterBool("Repeat"));
        addProperty(iPropertyRepeat);
    }

    /**
     * Enable the Shuffle property.
     */
    public void enablePropertyShuffle()
    {
        iPropertyShuffle = new PropertyBool(new ParameterBool("Shuffle"));
        addProperty(iPropertyShuffle);
    }

    /**
     * Enable the Id property.
     */
    public void enablePropertyId()
    {
        iPropertyId = new PropertyUint(new ParameterUint("Id"));
        addProperty(iPropertyId);
    }

    /**
     * Enable the IdArray property.
     */
    public void enablePropertyIdArray()
    {
        iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
        addProperty(iPropertyIdArray);
    }

    /**
     * Enable the TracksMax property.
     */
    public void enablePropertyTracksMax()
    {
        iPropertyTracksMax = new PropertyUint(new ParameterUint("TracksMax"));
        addProperty(iPropertyTracksMax);
    }

    /**
     * Enable the ProtocolInfo property.
     */
    public void enablePropertyProtocolInfo()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyProtocolInfo = new PropertyString(new ParameterString("ProtocolInfo", allowedValues));
        addProperty(iPropertyProtocolInfo);
    }

    /**
     * Set the value of the TransportState property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyTransportState(String aValue)
    {
        return setPropertyString(iPropertyTransportState, aValue);
    }

    /**
     * Get a copy of the value of the TransportState property
     *
     * @return  value of the TransportState property.
     */
    public String getPropertyTransportState()
    {
        return iPropertyTransportState.getValue();
    }

    /**
     * Set the value of the Repeat property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyRepeat(boolean aValue)
    {
        return setPropertyBool(iPropertyRepeat, aValue);
    }

    /**
     * Get a copy of the value of the Repeat property
     *
     * @return  value of the Repeat property.
     */
    public boolean getPropertyRepeat()
    {
        return iPropertyRepeat.getValue();
    }

    /**
     * Set the value of the Shuffle property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyShuffle(boolean aValue)
    {
        return setPropertyBool(iPropertyShuffle, aValue);
    }

    /**
     * Get a copy of the value of the Shuffle property
     *
     * @return  value of the Shuffle property.
     */
    public boolean getPropertyShuffle()
    {
        return iPropertyShuffle.getValue();
    }

    /**
     * Set the value of the Id property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyId(long aValue)
    {
        return setPropertyUint(iPropertyId, aValue);
    }

    /**
     * Get a copy of the value of the Id property
     *
     * @return  value of the Id property.
     */
    public long getPropertyId()
    {
        return iPropertyId.getValue();
    }

    /**
     * Set the value of the IdArray property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyIdArray(byte[] aValue)
    {
        return setPropertyBinary(iPropertyIdArray, aValue);
    }

    /**
     * Get a copy of the value of the IdArray property
     *
     * @return  value of the IdArray property.
     */
    public byte[] getPropertyIdArray()
    {
        return iPropertyIdArray.getValue();
    }

    /**
     * Set the value of the TracksMax property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyTracksMax(long aValue)
    {
        return setPropertyUint(iPropertyTracksMax, aValue);
    }

    /**
     * Get a copy of the value of the TracksMax property
     *
     * @return  value of the TracksMax property.
     */
    public long getPropertyTracksMax()
    {
        return iPropertyTracksMax.getValue();
    }

    /**
     * Set the value of the ProtocolInfo property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyProtocolInfo(String aValue)
    {
        return setPropertyString(iPropertyProtocolInfo, aValue);
    }

    /**
     * Get a copy of the value of the ProtocolInfo property
     *
     * @return  value of the ProtocolInfo property.
     */
    public String getPropertyProtocolInfo()
    {
        return iPropertyProtocolInfo.getValue();
    }

    /**
     * Signal that the action Play is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Play must be overridden if this is called.
     */      
    protected void enableActionPlay()
    {
        Action action = new Action("Play");
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
        iDelegatePause = new DoPause();
        enableAction(action, iDelegatePause);
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
        iDelegateStop = new DoStop();
        enableAction(action, iDelegateStop);
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
        iDelegatePrevious = new DoPrevious();
        enableAction(action, iDelegatePrevious);
    }

    /**
     * Signal that the action SetRepeat is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetRepeat must be overridden if this is called.
     */      
    protected void enableActionSetRepeat()
    {
        Action action = new Action("SetRepeat");
        action.addInputParameter(new ParameterRelated("Value", iPropertyRepeat));
        iDelegateSetRepeat = new DoSetRepeat();
        enableAction(action, iDelegateSetRepeat);
    }

    /**
     * Signal that the action Repeat is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Repeat must be overridden if this is called.
     */      
    protected void enableActionRepeat()
    {
        Action action = new Action("Repeat");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyRepeat));
        iDelegateRepeat = new DoRepeat();
        enableAction(action, iDelegateRepeat);
    }

    /**
     * Signal that the action SetShuffle is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetShuffle must be overridden if this is called.
     */      
    protected void enableActionSetShuffle()
    {
        Action action = new Action("SetShuffle");
        action.addInputParameter(new ParameterRelated("Value", iPropertyShuffle));
        iDelegateSetShuffle = new DoSetShuffle();
        enableAction(action, iDelegateSetShuffle);
    }

    /**
     * Signal that the action Shuffle is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Shuffle must be overridden if this is called.
     */      
    protected void enableActionShuffle()
    {
        Action action = new Action("Shuffle");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyShuffle));
        iDelegateShuffle = new DoShuffle();
        enableAction(action, iDelegateShuffle);
    }

    /**
     * Signal that the action SeekSecondAbsolute is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SeekSecondAbsolute must be overridden if this is called.
     */      
    protected void enableActionSeekSecondAbsolute()
    {
        Action action = new Action("SeekSecondAbsolute");
        action.addInputParameter(new ParameterUint("Value"));
        iDelegateSeekSecondAbsolute = new DoSeekSecondAbsolute();
        enableAction(action, iDelegateSeekSecondAbsolute);
    }

    /**
     * Signal that the action SeekSecondRelative is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SeekSecondRelative must be overridden if this is called.
     */      
    protected void enableActionSeekSecondRelative()
    {
        Action action = new Action("SeekSecondRelative");
        action.addInputParameter(new ParameterInt("Value"));
        iDelegateSeekSecondRelative = new DoSeekSecondRelative();
        enableAction(action, iDelegateSeekSecondRelative);
    }

    /**
     * Signal that the action SeekId is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SeekId must be overridden if this is called.
     */      
    protected void enableActionSeekId()
    {
        Action action = new Action("SeekId");
        action.addInputParameter(new ParameterRelated("Value", iPropertyId));
        iDelegateSeekId = new DoSeekId();
        enableAction(action, iDelegateSeekId);
    }

    /**
     * Signal that the action SeekIndex is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SeekIndex must be overridden if this is called.
     */      
    protected void enableActionSeekIndex()
    {
        Action action = new Action("SeekIndex");
        action.addInputParameter(new ParameterUint("Value"));
        iDelegateSeekIndex = new DoSeekIndex();
        enableAction(action, iDelegateSeekIndex);
    }

    /**
     * Signal that the action TransportState is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * TransportState must be overridden if this is called.
     */      
    protected void enableActionTransportState()
    {
        Action action = new Action("TransportState");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyTransportState));
        iDelegateTransportState = new DoTransportState();
        enableAction(action, iDelegateTransportState);
    }

    /**
     * Signal that the action Id is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Id must be overridden if this is called.
     */      
    protected void enableActionId()
    {
        Action action = new Action("Id");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyId));
        iDelegateId = new DoId();
        enableAction(action, iDelegateId);
    }

    /**
     * Signal that the action Read is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Read must be overridden if this is called.
     */      
    protected void enableActionRead()
    {
        Action action = new Action("Read");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterRelated("Id", iPropertyId));
        action.addOutputParameter(new ParameterString("Uri", allowedValues));
        action.addOutputParameter(new ParameterString("Metadata", allowedValues));
        iDelegateRead = new DoRead();
        enableAction(action, iDelegateRead);
    }

    /**
     * Signal that the action ReadList is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ReadList must be overridden if this is called.
     */      
    protected void enableActionReadList()
    {
        Action action = new Action("ReadList");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("IdList", allowedValues));
        action.addOutputParameter(new ParameterString("TrackList", allowedValues));
        iDelegateReadList = new DoReadList();
        enableAction(action, iDelegateReadList);
    }

    /**
     * Signal that the action Insert is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Insert must be overridden if this is called.
     */      
    protected void enableActionInsert()
    {
        Action action = new Action("Insert");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterRelated("AfterId", iPropertyId));
        action.addInputParameter(new ParameterString("Uri", allowedValues));
        action.addInputParameter(new ParameterString("Metadata", allowedValues));
        action.addOutputParameter(new ParameterRelated("NewId", iPropertyId));
        iDelegateInsert = new DoInsert();
        enableAction(action, iDelegateInsert);
    }

    /**
     * Signal that the action DeleteId is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * DeleteId must be overridden if this is called.
     */      
    protected void enableActionDeleteId()
    {
        Action action = new Action("DeleteId");
        action.addInputParameter(new ParameterRelated("Value", iPropertyId));
        iDelegateDeleteId = new DoDeleteId();
        enableAction(action, iDelegateDeleteId);
    }

    /**
     * Signal that the action DeleteAll is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * DeleteAll must be overridden if this is called.
     */      
    protected void enableActionDeleteAll()
    {
        Action action = new Action("DeleteAll");
        iDelegateDeleteAll = new DoDeleteAll();
        enableAction(action, iDelegateDeleteAll);
    }

    /**
     * Signal that the action TracksMax is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * TracksMax must be overridden if this is called.
     */      
    protected void enableActionTracksMax()
    {
        Action action = new Action("TracksMax");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyTracksMax));
        iDelegateTracksMax = new DoTracksMax();
        enableAction(action, iDelegateTracksMax);
    }

    /**
     * Signal that the action IdArray is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * IdArray must be overridden if this is called.
     */      
    protected void enableActionIdArray()
    {
        Action action = new Action("IdArray");
        action.addOutputParameter(new ParameterUint("Token"));
        action.addOutputParameter(new ParameterRelated("Array", iPropertyIdArray));
        iDelegateIdArray = new DoIdArray();
        enableAction(action, iDelegateIdArray);
    }

    /**
     * Signal that the action IdArrayChanged is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * IdArrayChanged must be overridden if this is called.
     */      
    protected void enableActionIdArrayChanged()
    {
        Action action = new Action("IdArrayChanged");
        action.addInputParameter(new ParameterUint("Token"));
        action.addOutputParameter(new ParameterBool("Value"));
        iDelegateIdArrayChanged = new DoIdArrayChanged();
        enableAction(action, iDelegateIdArrayChanged);
    }

    /**
     * Signal that the action ProtocolInfo is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ProtocolInfo must be overridden if this is called.
     */      
    protected void enableActionProtocolInfo()
    {
        Action action = new Action("ProtocolInfo");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyProtocolInfo));
        iDelegateProtocolInfo = new DoProtocolInfo();
        enableAction(action, iDelegateProtocolInfo);
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
     */
    protected void play(IDvInvocation aInvocation)
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
     */
    protected void pause(IDvInvocation aInvocation)
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
     */
    protected void stop(IDvInvocation aInvocation)
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
     */
    protected void next(IDvInvocation aInvocation)
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
     */
    protected void previous(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetRepeat action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetRepeat action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetRepeat} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aValue
     */
    protected void setRepeat(IDvInvocation aInvocation, boolean aValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Repeat action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Repeat action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionRepeat} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected boolean repeat(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetShuffle action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetShuffle action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetShuffle} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aValue
     */
    protected void setShuffle(IDvInvocation aInvocation, boolean aValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Shuffle action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Shuffle action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionShuffle} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected boolean shuffle(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SeekSecondAbsolute action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SeekSecondAbsolute action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSeekSecondAbsolute} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aValue
     */
    protected void seekSecondAbsolute(IDvInvocation aInvocation, long aValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SeekSecondRelative action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SeekSecondRelative action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSeekSecondRelative} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aValue
     */
    protected void seekSecondRelative(IDvInvocation aInvocation, int aValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SeekId action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SeekId action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSeekId} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aValue
     */
    protected void seekId(IDvInvocation aInvocation, long aValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SeekIndex action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SeekIndex action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSeekIndex} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aValue
     */
    protected void seekIndex(IDvInvocation aInvocation, long aValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * TransportState action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * TransportState action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionTransportState} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String transportState(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Id action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Id action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionId} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long id(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Read action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Read action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionRead} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aId
     */
    protected Read read(IDvInvocation aInvocation, long aId)
    {
        throw (new ActionDisabledError());
    }

    /**
     * ReadList action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ReadList action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionReadList} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aIdList
     */
    protected String readList(IDvInvocation aInvocation, String aIdList)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Insert action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Insert action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionInsert} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aAfterId
     * @param aUri
     * @param aMetadata
     */
    protected long insert(IDvInvocation aInvocation, long aAfterId, String aUri, String aMetadata)
    {
        throw (new ActionDisabledError());
    }

    /**
     * DeleteId action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * DeleteId action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDeleteId} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aValue
     */
    protected void deleteId(IDvInvocation aInvocation, long aValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * DeleteAll action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * DeleteAll action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDeleteAll} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected void deleteAll(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * TracksMax action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * TracksMax action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionTracksMax} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long tracksMax(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * IdArray action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * IdArray action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionIdArray} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected IdArray idArray(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * IdArrayChanged action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * IdArrayChanged action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionIdArrayChanged} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aToken
     */
    protected boolean idArrayChanged(IDvInvocation aInvocation, long aToken)
    {
        throw (new ActionDisabledError());
    }

    /**
     * ProtocolInfo action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ProtocolInfo action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionProtocolInfo} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String protocolInfo(IDvInvocation aInvocation)
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


    private class DoPlay implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                play(invocation);
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
            try
            {
                invocation.readStart();
                invocation.readEnd();
                pause(invocation);
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

    private class DoStop implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                stop(invocation);
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

    private class DoNext implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                next(invocation);
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
            try
            {
                invocation.readStart();
                invocation.readEnd();
                previous(invocation);
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

    private class DoSetRepeat implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean value;
            try
            {
                invocation.readStart();
                value = invocation.readBool("Value");
                invocation.readEnd();
                setRepeat(invocation, value);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetRepeat");
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

    private class DoRepeat implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = repeat(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Repeat");
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
                invocation.writeBool("Value", value);
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

    private class DoSetShuffle implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean value;
            try
            {
                invocation.readStart();
                value = invocation.readBool("Value");
                invocation.readEnd();
                setShuffle(invocation, value);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetShuffle");
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

    private class DoShuffle implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = shuffle(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Shuffle");
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
                invocation.writeBool("Value", value);
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

    private class DoSeekSecondAbsolute implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                value = invocation.readUint("Value");
                invocation.readEnd();
                seekSecondAbsolute(invocation, value);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SeekSecondAbsolute");
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

    private class DoSeekSecondRelative implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            int value;
            try
            {
                invocation.readStart();
                value = invocation.readInt("Value");
                invocation.readEnd();
                seekSecondRelative(invocation, value);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SeekSecondRelative");
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

    private class DoSeekId implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                value = invocation.readUint("Value");
                invocation.readEnd();
                seekId(invocation, value);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SeekId");
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

    private class DoSeekIndex implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                value = invocation.readUint("Value");
                invocation.readEnd();
                seekIndex(invocation, value);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SeekIndex");
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

    private class DoTransportState implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = transportState(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "TransportState");
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
                invocation.writeString("Value", value);
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

    private class DoId implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = id(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Id");
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
                invocation.writeUint("Value", value);
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

    private class DoRead implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            String uri;
            String metadata;
            try
            {
                invocation.readStart();
                id = invocation.readUint("Id");
                invocation.readEnd();

            Read outArgs = read(invocation, id);
            uri = outArgs.getUri();
            metadata = outArgs.getMetadata();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Read");
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
                invocation.writeString("Uri", uri);
                invocation.writeString("Metadata", metadata);
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

    private class DoReadList implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String idList;
            String trackList;
            try
            {
                invocation.readStart();
                idList = invocation.readString("IdList");
                invocation.readEnd();
                 trackList = readList(invocation, idList);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ReadList");
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
                invocation.writeString("TrackList", trackList);
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

    private class DoInsert implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long afterId;
            String uri;
            String metadata;
            long newId;
            try
            {
                invocation.readStart();
                afterId = invocation.readUint("AfterId");
                uri = invocation.readString("Uri");
                metadata = invocation.readString("Metadata");
                invocation.readEnd();
                 newId = insert(invocation, afterId, uri, metadata);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Insert");
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
                invocation.writeUint("NewId", newId);
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

    private class DoDeleteId implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                value = invocation.readUint("Value");
                invocation.readEnd();
                deleteId(invocation, value);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "DeleteId");
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

    private class DoDeleteAll implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                deleteAll(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "DeleteAll");
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

    private class DoTracksMax implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = tracksMax(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "TracksMax");
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
                invocation.writeUint("Value", value);
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

    private class DoIdArray implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long token;
            byte[] array;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            IdArray outArgs = idArray(invocation);
            token = outArgs.getToken();
            array = outArgs.getArray();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "IdArray");
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
                invocation.writeUint("Token", token);
                invocation.writeBinary("Array", array);
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

    private class DoIdArrayChanged implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long token;
            boolean value;
            try
            {
                invocation.readStart();
                token = invocation.readUint("Token");
                invocation.readEnd();
                 value = idArrayChanged(invocation, token);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "IdArrayChanged");
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
                invocation.writeBool("Value", value);
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

    private class DoProtocolInfo implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = protocolInfo(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ProtocolInfo");
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
                invocation.writeString("Value", value);
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

