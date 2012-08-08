package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderAvOpenhomeOrgRadio1
{

    /**
     * Set the value of the Uri property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyUri(String aValue);

    /**
     * Get a copy of the value of the Uri property
     *
     * @return value of the Uri property.
     */
    public String getPropertyUri();

    /**
     * Set the value of the Metadata property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyMetadata(String aValue);

    /**
     * Get a copy of the value of the Metadata property
     *
     * @return value of the Metadata property.
     */
    public String getPropertyMetadata();

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
     * Set the value of the ChannelsMax property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyChannelsMax(long aValue);

    /**
     * Get a copy of the value of the ChannelsMax property
     *
     * @return value of the ChannelsMax property.
     */
    public long getPropertyChannelsMax();

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
 * Provider for the av.openhome.org:Radio:1 UPnP service.
 */
public class DvProviderAvOpenhomeOrgRadio1 extends DvProvider implements IDvProviderAvOpenhomeOrgRadio1
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

    private IDvInvocationListener iDelegatePlay;
    private IDvInvocationListener iDelegatePause;
    private IDvInvocationListener iDelegateStop;
    private IDvInvocationListener iDelegateSeekSecondAbsolute;
    private IDvInvocationListener iDelegateSeekSecondRelative;
    private IDvInvocationListener iDelegateChannel;
    private IDvInvocationListener iDelegateSetChannel;
    private IDvInvocationListener iDelegateTransportState;
    private IDvInvocationListener iDelegateId;
    private IDvInvocationListener iDelegateSetId;
    private IDvInvocationListener iDelegateRead;
    private IDvInvocationListener iDelegateReadList;
    private IDvInvocationListener iDelegateIdArray;
    private IDvInvocationListener iDelegateIdArrayChanged;
    private IDvInvocationListener iDelegateChannelsMax;
    private IDvInvocationListener iDelegateProtocolInfo;
    private PropertyString iPropertyUri;
    private PropertyString iPropertyMetadata;
    private PropertyString iPropertyTransportState;
    private PropertyUint iPropertyId;
    private PropertyBinary iPropertyIdArray;
    private PropertyUint iPropertyChannelsMax;
    private PropertyString iPropertyProtocolInfo;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderAvOpenhomeOrgRadio1(DvDevice aDevice)
    {
        super(aDevice, "av.openhome.org", "Radio", 1);
    }

    /**
     * Enable the Uri property.
     */
    public void enablePropertyUri()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyUri = new PropertyString(new ParameterString("Uri", allowedValues));
        addProperty(iPropertyUri);
    }

    /**
     * Enable the Metadata property.
     */
    public void enablePropertyMetadata()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyMetadata = new PropertyString(new ParameterString("Metadata", allowedValues));
        addProperty(iPropertyMetadata);
    }

    /**
     * Enable the TransportState property.
     */
    public void enablePropertyTransportState()
    {
        List<String> allowedValues = new LinkedList<String>();
        allowedValues.add("Stopped");
        allowedValues.add("Playing");
        allowedValues.add("Paused");
        allowedValues.add("Buffering");
        iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues));
        addProperty(iPropertyTransportState);
            allowedValues.clear();
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
     * Enable the ChannelsMax property.
     */
    public void enablePropertyChannelsMax()
    {
        iPropertyChannelsMax = new PropertyUint(new ParameterUint("ChannelsMax"));
        addProperty(iPropertyChannelsMax);
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
     * Set the value of the Uri property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyUri(String aValue)
    {
        return setPropertyString(iPropertyUri, aValue);
    }

    /**
     * Get a copy of the value of the Uri property
     *
     * @return  value of the Uri property.
     */
    public String getPropertyUri()
    {
        return iPropertyUri.getValue();
    }

    /**
     * Set the value of the Metadata property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyMetadata(String aValue)
    {
        return setPropertyString(iPropertyMetadata, aValue);
    }

    /**
     * Get a copy of the value of the Metadata property
     *
     * @return  value of the Metadata property.
     */
    public String getPropertyMetadata()
    {
        return iPropertyMetadata.getValue();
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
     * Set the value of the ChannelsMax property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyChannelsMax(long aValue)
    {
        return setPropertyUint(iPropertyChannelsMax, aValue);
    }

    /**
     * Get a copy of the value of the ChannelsMax property
     *
     * @return  value of the ChannelsMax property.
     */
    public long getPropertyChannelsMax()
    {
        return iPropertyChannelsMax.getValue();
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
     * Signal that the action Channel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Channel must be overridden if this is called.
     */      
    protected void enableActionChannel()
    {
        Action action = new Action("Channel");
        action.addOutputParameter(new ParameterRelated("Uri", iPropertyUri));
        action.addOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
        iDelegateChannel = new DoChannel();
        enableAction(action, iDelegateChannel);
    }

    /**
     * Signal that the action SetChannel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetChannel must be overridden if this is called.
     */      
    protected void enableActionSetChannel()
    {
        Action action = new Action("SetChannel");
        action.addInputParameter(new ParameterRelated("Uri", iPropertyUri));
        action.addInputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
        iDelegateSetChannel = new DoSetChannel();
        enableAction(action, iDelegateSetChannel);
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
     * Signal that the action SetId is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetId must be overridden if this is called.
     */      
    protected void enableActionSetId()
    {
        Action action = new Action("SetId");
        action.addInputParameter(new ParameterRelated("Value", iPropertyId));
        action.addInputParameter(new ParameterRelated("Uri", iPropertyUri));
        iDelegateSetId = new DoSetId();
        enableAction(action, iDelegateSetId);
    }

    /**
     * Signal that the action Read is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Read must be overridden if this is called.
     */      
    protected void enableActionRead()
    {
        Action action = new Action("Read");
        action.addInputParameter(new ParameterRelated("Id", iPropertyId));
        action.addOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
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
        action.addOutputParameter(new ParameterString("ChannelList", allowedValues));
        iDelegateReadList = new DoReadList();
        enableAction(action, iDelegateReadList);
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
     * Signal that the action ChannelsMax is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ChannelsMax must be overridden if this is called.
     */      
    protected void enableActionChannelsMax()
    {
        Action action = new Action("ChannelsMax");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyChannelsMax));
        iDelegateChannelsMax = new DoChannelsMax();
        enableAction(action, iDelegateChannelsMax);
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
     * Channel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Channel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionChannel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Channel channel(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetChannel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetChannel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetChannel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aUri
     * @param aMetadata
     */
    protected void setChannel(IDvInvocation aInvocation, String aUri, String aMetadata)
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
     * SetId action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetId action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetId} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aValue
     * @param aUri
     */
    protected void setId(IDvInvocation aInvocation, long aValue, String aUri)
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
    protected String read(IDvInvocation aInvocation, long aId)
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
     * ChannelsMax action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ChannelsMax action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionChannelsMax} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long channelsMax(IDvInvocation aInvocation)
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

    private class DoChannel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String uri;
            String metadata;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Channel outArgs = channel(invocation);
            uri = outArgs.getUri();
            metadata = outArgs.getMetadata();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Channel");
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

    private class DoSetChannel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String uri;
            String metadata;
            try
            {
                invocation.readStart();
                uri = invocation.readString("Uri");
                metadata = invocation.readString("Metadata");
                invocation.readEnd();
                setChannel(invocation, uri, metadata);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetChannel");
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

    private class DoSetId implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            String uri;
            try
            {
                invocation.readStart();
                value = invocation.readUint("Value");
                uri = invocation.readString("Uri");
                invocation.readEnd();
                setId(invocation, value, uri);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetId");
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

    private class DoRead implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            String metadata;
            try
            {
                invocation.readStart();
                id = invocation.readUint("Id");
                invocation.readEnd();
                 metadata = read(invocation, id);
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
            String channelList;
            try
            {
                invocation.readStart();
                idList = invocation.readString("IdList");
                invocation.readEnd();
                 channelList = readList(invocation, idList);
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
                invocation.writeString("ChannelList", channelList);
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

    private class DoChannelsMax implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = channelsMax(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ChannelsMax");
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

