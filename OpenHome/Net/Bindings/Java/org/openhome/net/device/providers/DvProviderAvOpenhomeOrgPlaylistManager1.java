package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderAvOpenhomeOrgPlaylistManager1
{

    /**
     * Set the value of the Metadata property
     *
     * @param aValue	new value for the property.
     * @return 		<tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
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
     * Set the value of the ImagesXml property
     *
     * @param aValue	new value for the property.
     * @return 		<tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyImagesXml(String aValue);

    /**
     * Get a copy of the value of the ImagesXml property
     *
     * @return value of the ImagesXml property.
     */
    public String getPropertyImagesXml();

    /**
     * Set the value of the IdArray property
     *
     * @param aValue	new value for the property.
     * @return 		<tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
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
     * Set the value of the TokenArray property
     *
     * @param aValue	new value for the property.
     * @return 		<tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyTokenArray(byte[] aValue);

    /**
     * Get a copy of the value of the TokenArray property
     *
     * @return value of the TokenArray property.
     */
    public byte[] getPropertyTokenArray();

    /**
     * Set the value of the PlaylistsMax property
     *
     * @param aValue	new value for the property.
     * @return 		<tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyPlaylistsMax(long aValue);

    /**
     * Get a copy of the value of the PlaylistsMax property
     *
     * @return value of the PlaylistsMax property.
     */
    public long getPropertyPlaylistsMax();

    /**
     * Set the value of the TracksMax property
     *
     * @param aValue	new value for the property.
     * @return 		<tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyTracksMax(long aValue);

    /**
     * Get a copy of the value of the TracksMax property
     *
     * @return value of the TracksMax property.
     */
    public long getPropertyTracksMax();
        
}

/**
 * Provider for the av.openhome.org:PlaylistManager:1 UPnP service.
 */
public class DvProviderAvOpenhomeOrgPlaylistManager1 extends DvProvider implements IDvProviderAvOpenhomeOrgPlaylistManager1
{

    public class PlaylistRead
    {
        private String iName;
        private String iDescription;
        private long iImageId;

        public PlaylistRead(
            String aName,
            String aDescription,
            long aImageId
        )
        {
            iName = aName;
            iDescription = aDescription;
            iImageId = aImageId;
        }
        public String getName()
        {
            return iName;
        }
        public String getDescription()
        {
            return iDescription;
        }
        public long getImageId()
        {
            return iImageId;
        }
    }

    public class PlaylistArrays
    {
        private long iToken;
        private byte[] iIdArray;
        private byte[] iTokenArray;

        public PlaylistArrays(
            long aToken,
            byte[] aIdArray,
            byte[] aTokenArray
        )
        {
            iToken = aToken;
            iIdArray = aIdArray;
            iTokenArray = aTokenArray;
        }
        public long getToken()
        {
            return iToken;
        }
        public byte[] getIdArray()
        {
            return iIdArray;
        }
        public byte[] getTokenArray()
        {
            return iTokenArray;
        }
    }

    private IDvInvocationListener iDelegateMetadata;
    private IDvInvocationListener iDelegateImagesXml;
    private IDvInvocationListener iDelegatePlaylistReadArray;
    private IDvInvocationListener iDelegatePlaylistReadMetadata;
    private IDvInvocationListener iDelegatePlaylistRead;
    private IDvInvocationListener iDelegatePlaylistUpdate;
    private IDvInvocationListener iDelegatePlaylistInsert;
    private IDvInvocationListener iDelegatePlaylistDeleteId;
    private IDvInvocationListener iDelegatePlaylistsMax;
    private IDvInvocationListener iDelegateTracksMax;
    private IDvInvocationListener iDelegatePlaylistArrays;
    private IDvInvocationListener iDelegatePlaylistArraysChanged;
    private IDvInvocationListener iDelegateRead;
    private IDvInvocationListener iDelegateReadList;
    private IDvInvocationListener iDelegateInsert;
    private IDvInvocationListener iDelegateDeleteId;
    private IDvInvocationListener iDelegateDeleteAll;
    private PropertyString iPropertyMetadata;
    private PropertyString iPropertyImagesXml;
    private PropertyBinary iPropertyIdArray;
    private PropertyBinary iPropertyTokenArray;
    private PropertyUint iPropertyPlaylistsMax;
    private PropertyUint iPropertyTracksMax;

    /**
     * Constructor
     *
     * @param aDevice	device which owns this provider.
     */
    protected DvProviderAvOpenhomeOrgPlaylistManager1(DvDevice aDevice)
    {
	    super(aDevice, "av.openhome.org", "PlaylistManager", 1);
        List<String> allowedValues = new LinkedList<String>();
        iPropertyMetadata = new PropertyString(new ParameterString("Metadata", allowedValues));
        addProperty(iPropertyMetadata);
        iPropertyImagesXml = new PropertyString(new ParameterString("ImagesXml", allowedValues));
        addProperty(iPropertyImagesXml);
        iPropertyIdArray = new PropertyBinary(new ParameterBinary("IdArray"));
        addProperty(iPropertyIdArray);
        iPropertyTokenArray = new PropertyBinary(new ParameterBinary("TokenArray"));
        addProperty(iPropertyTokenArray);
        iPropertyPlaylistsMax = new PropertyUint(new ParameterUint("PlaylistsMax"));
        addProperty(iPropertyPlaylistsMax);
        iPropertyTracksMax = new PropertyUint(new ParameterUint("TracksMax"));
        addProperty(iPropertyTracksMax);
    }

    /**
     * Set the value of the Metadata property
     *
     * @param aValue	new value for the property.
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
     * @return	value of the Metadata property.
     */
    public String getPropertyMetadata()
    {
        return iPropertyMetadata.getValue();
    }

    /**
     * Set the value of the ImagesXml property
     *
     * @param aValue	new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyImagesXml(String aValue)
    {
        return setPropertyString(iPropertyImagesXml, aValue);
    }

    /**
     * Get a copy of the value of the ImagesXml property
     *
     * @return	value of the ImagesXml property.
     */
    public String getPropertyImagesXml()
    {
        return iPropertyImagesXml.getValue();
    }

    /**
     * Set the value of the IdArray property
     *
     * @param aValue	new value for the property.
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
     * @return	value of the IdArray property.
     */
    public byte[] getPropertyIdArray()
    {
        return iPropertyIdArray.getValue();
    }

    /**
     * Set the value of the TokenArray property
     *
     * @param aValue	new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyTokenArray(byte[] aValue)
    {
        return setPropertyBinary(iPropertyTokenArray, aValue);
    }

    /**
     * Get a copy of the value of the TokenArray property
     *
     * @return	value of the TokenArray property.
     */
    public byte[] getPropertyTokenArray()
    {
        return iPropertyTokenArray.getValue();
    }

    /**
     * Set the value of the PlaylistsMax property
     *
     * @param aValue	new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyPlaylistsMax(long aValue)
    {
        return setPropertyUint(iPropertyPlaylistsMax, aValue);
    }

    /**
     * Get a copy of the value of the PlaylistsMax property
     *
     * @return	value of the PlaylistsMax property.
     */
    public long getPropertyPlaylistsMax()
    {
        return iPropertyPlaylistsMax.getValue();
    }

    /**
     * Set the value of the TracksMax property
     *
     * @param aValue	new value for the property.
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
     * @return	value of the TracksMax property.
     */
    public long getPropertyTracksMax()
    {
        return iPropertyTracksMax.getValue();
    }

    /**
     * Signal that the action Metadata is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Metadata must be overridden if this is called.
     */		 
    protected void enableActionMetadata()
    {
        Action action = new Action("Metadata");
        action.addOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
        iDelegateMetadata = new DoMetadata();
        enableAction(action, iDelegateMetadata);
    }

    /**
     * Signal that the action ImagesXml is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ImagesXml must be overridden if this is called.
     */		 
    protected void enableActionImagesXml()
    {
        Action action = new Action("ImagesXml");
        action.addOutputParameter(new ParameterRelated("ImagesXml", iPropertyImagesXml));
        iDelegateImagesXml = new DoImagesXml();
        enableAction(action, iDelegateImagesXml);
    }

    /**
     * Signal that the action PlaylistReadArray is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistReadArray must be overridden if this is called.
     */		 
    protected void enableActionPlaylistReadArray()
    {
        Action action = new Action("PlaylistReadArray");
        action.addInputParameter(new ParameterUint("Id"));
        action.addOutputParameter(new ParameterRelated("Array", iPropertyIdArray));
        iDelegatePlaylistReadArray = new DoPlaylistReadArray();
        enableAction(action, iDelegatePlaylistReadArray);
    }

    /**
     * Signal that the action PlaylistReadMetadata is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistReadMetadata must be overridden if this is called.
     */		 
    protected void enableActionPlaylistReadMetadata()
    {
        Action action = new Action("PlaylistReadMetadata");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("IdList", allowedValues));
        action.addOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
        iDelegatePlaylistReadMetadata = new DoPlaylistReadMetadata();
        enableAction(action, iDelegatePlaylistReadMetadata);
    }

    /**
     * Signal that the action PlaylistRead is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistRead must be overridden if this is called.
     */		 
    protected void enableActionPlaylistRead()
    {
        Action action = new Action("PlaylistRead");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("Id"));
        action.addOutputParameter(new ParameterString("Name", allowedValues));
        action.addOutputParameter(new ParameterString("Description", allowedValues));
        action.addOutputParameter(new ParameterUint("ImageId"));
        iDelegatePlaylistRead = new DoPlaylistRead();
        enableAction(action, iDelegatePlaylistRead);
    }

    /**
     * Signal that the action PlaylistUpdate is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistUpdate must be overridden if this is called.
     */		 
    protected void enableActionPlaylistUpdate()
    {
        Action action = new Action("PlaylistUpdate");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("Id"));
        action.addInputParameter(new ParameterString("Name", allowedValues));
        action.addInputParameter(new ParameterString("Description", allowedValues));
        action.addInputParameter(new ParameterUint("ImageId"));
        iDelegatePlaylistUpdate = new DoPlaylistUpdate();
        enableAction(action, iDelegatePlaylistUpdate);
    }

    /**
     * Signal that the action PlaylistInsert is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistInsert must be overridden if this is called.
     */		 
    protected void enableActionPlaylistInsert()
    {
        Action action = new Action("PlaylistInsert");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("AfterId"));
        action.addInputParameter(new ParameterString("Name", allowedValues));
        action.addInputParameter(new ParameterString("Description", allowedValues));
        action.addInputParameter(new ParameterUint("ImageId"));
        action.addOutputParameter(new ParameterUint("NewId"));
        iDelegatePlaylistInsert = new DoPlaylistInsert();
        enableAction(action, iDelegatePlaylistInsert);
    }

    /**
     * Signal that the action PlaylistDeleteId is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistDeleteId must be overridden if this is called.
     */		 
    protected void enableActionPlaylistDeleteId()
    {
        Action action = new Action("PlaylistDeleteId");
        action.addInputParameter(new ParameterUint("Value"));
        iDelegatePlaylistDeleteId = new DoPlaylistDeleteId();
        enableAction(action, iDelegatePlaylistDeleteId);
    }

    /**
     * Signal that the action PlaylistsMax is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistsMax must be overridden if this is called.
     */		 
    protected void enableActionPlaylistsMax()
    {
        Action action = new Action("PlaylistsMax");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyPlaylistsMax));
        iDelegatePlaylistsMax = new DoPlaylistsMax();
        enableAction(action, iDelegatePlaylistsMax);
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
     * Signal that the action PlaylistArrays is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistArrays must be overridden if this is called.
     */		 
    protected void enableActionPlaylistArrays()
    {
        Action action = new Action("PlaylistArrays");
        action.addOutputParameter(new ParameterUint("Token"));
        action.addOutputParameter(new ParameterRelated("IdArray", iPropertyIdArray));
        action.addOutputParameter(new ParameterRelated("TokenArray", iPropertyTokenArray));
        iDelegatePlaylistArrays = new DoPlaylistArrays();
        enableAction(action, iDelegatePlaylistArrays);
    }

    /**
     * Signal that the action PlaylistArraysChanged is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PlaylistArraysChanged must be overridden if this is called.
     */		 
    protected void enableActionPlaylistArraysChanged()
    {
        Action action = new Action("PlaylistArraysChanged");
        action.addInputParameter(new ParameterUint("Token"));
        action.addOutputParameter(new ParameterBool("Value"));
        iDelegatePlaylistArraysChanged = new DoPlaylistArraysChanged();
        enableAction(action, iDelegatePlaylistArraysChanged);
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
        action.addInputParameter(new ParameterUint("Id"));
        action.addInputParameter(new ParameterUint("TrackId"));
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
        action.addInputParameter(new ParameterUint("Id"));
        action.addInputParameter(new ParameterString("TrackIdList", allowedValues));
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
        action.addInputParameter(new ParameterUint("Id"));
        action.addInputParameter(new ParameterUint("AfterTrackId"));
        action.addInputParameter(new ParameterString("Udn", allowedValues));
        action.addInputParameter(new ParameterString("MetadataId", allowedValues));
        action.addOutputParameter(new ParameterUint("NewTrackId"));
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
        action.addInputParameter(new ParameterUint("TrackId"));
        action.addInputParameter(new ParameterUint("Value"));
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
        action.addInputParameter(new ParameterUint("TrackId"));
        iDelegateDeleteAll = new DoDeleteAll();
        enableAction(action, iDelegateDeleteAll);
    }

    /**
     * Metadata action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Metadata action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionMetadata} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     */
    protected String metadata(int aVersion)
    {
        throw (new ActionDisabledError());
    }

    /**
     * ImagesXml action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ImagesXml action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionImagesXml} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     */
    protected String imagesXml(int aVersion)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistReadArray action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistReadArray action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistReadArray} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aId
     */
    protected byte[] playlistReadArray(int aVersion, long aId)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistReadMetadata action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistReadMetadata action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistReadMetadata} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aIdList
     */
    protected String playlistReadMetadata(int aVersion, String aIdList)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistRead action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistRead action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistRead} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aId
     */
    protected PlaylistRead playlistRead(int aVersion, long aId)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistUpdate action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistUpdate action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistUpdate} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aId
     * @param aName
     * @param aDescription
     * @param aImageId
     */
    protected void playlistUpdate(int aVersion, long aId, String aName, String aDescription, long aImageId)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistInsert action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistInsert action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistInsert} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aAfterId
     * @param aName
     * @param aDescription
     * @param aImageId
     */
    protected long playlistInsert(int aVersion, long aAfterId, String aName, String aDescription, long aImageId)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistDeleteId action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistDeleteId action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistDeleteId} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aValue
     */
    protected void playlistDeleteId(int aVersion, long aValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistsMax action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistsMax action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistsMax} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     */
    protected long playlistsMax(int aVersion)
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
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     */
    protected long tracksMax(int aVersion)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistArrays action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistArrays action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistArrays} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     */
    protected PlaylistArrays playlistArrays(int aVersion)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PlaylistArraysChanged action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PlaylistArraysChanged action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPlaylistArraysChanged} was called.</remarks>
     *
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aToken
     */
    protected boolean playlistArraysChanged(int aVersion, long aToken)
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
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aId
     * @param aTrackId
     */
    protected String read(int aVersion, long aId, long aTrackId)
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
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aId
     * @param aTrackIdList
     */
    protected String readList(int aVersion, long aId, String aTrackIdList)
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
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aId
     * @param aAfterTrackId
     * @param aUdn
     * @param aMetadataId
     */
    protected long insert(int aVersion, long aId, long aAfterTrackId, String aUdn, String aMetadataId)
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
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aTrackId
     * @param aValue
     */
    protected void deleteId(int aVersion, long aTrackId, long aValue)
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
     * @param aVersion	version of the service being requested (will be <= the version advertised)</param>
     * @param aTrackId
     */
    protected void deleteAll(int aVersion, long aTrackId)
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


    private class DoMetadata implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String metadata;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 metadata = metadata(aVersion);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoImagesXml implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String imagesXml;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 imagesXml = imagesXml(aVersion);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeString("ImagesXml", imagesXml);
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

    private class DoPlaylistReadArray implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            byte[] array;
            try
            {
                invocation.readStart();
                id = invocation.readUint("Id");
                invocation.readEnd();
                 array = playlistReadArray(aVersion, id);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoPlaylistReadMetadata implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String idList;
            String metadata;
            try
            {
                invocation.readStart();
                idList = invocation.readString("IdList");
                invocation.readEnd();
                 metadata = playlistReadMetadata(aVersion, idList);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoPlaylistRead implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            String name;
            String description;
            long imageId;
            try
            {
                invocation.readStart();
                id = invocation.readUint("Id");
                invocation.readEnd();

            PlaylistRead outArgs = playlistRead(aVersion, id);
            name = outArgs.getName();
            description = outArgs.getDescription();
            imageId = outArgs.getImageId();
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeString("Name", name);
                invocation.writeString("Description", description);
                invocation.writeUint("ImageId", imageId);
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

    private class DoPlaylistUpdate implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            String name;
            String description;
            long imageId;
            try
            {
                invocation.readStart();
                id = invocation.readUint("Id");
                name = invocation.readString("Name");
                description = invocation.readString("Description");
                imageId = invocation.readUint("ImageId");
                invocation.readEnd();
                playlistUpdate(aVersion, id, name, description, imageId);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoPlaylistInsert implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long afterId;
            String name;
            String description;
            long imageId;
            long newId;
            try
            {
                invocation.readStart();
                afterId = invocation.readUint("AfterId");
                name = invocation.readString("Name");
                description = invocation.readString("Description");
                imageId = invocation.readUint("ImageId");
                invocation.readEnd();
                 newId = playlistInsert(aVersion, afterId, name, description, imageId);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoPlaylistDeleteId implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                value = invocation.readUint("Value");
                invocation.readEnd();
                playlistDeleteId(aVersion, value);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoPlaylistsMax implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = playlistsMax(aVersion);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoTracksMax implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = tracksMax(aVersion);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoPlaylistArrays implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long token;
            byte[] idArray;
            byte[] tokenArray;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            PlaylistArrays outArgs = playlistArrays(aVersion);
            token = outArgs.getToken();
            idArray = outArgs.getIdArray();
            tokenArray = outArgs.getTokenArray();
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeBinary("IdArray", idArray);
                invocation.writeBinary("TokenArray", tokenArray);
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

    private class DoPlaylistArraysChanged implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long token;
            boolean value;
            try
            {
                invocation.readStart();
                token = invocation.readUint("Token");
                invocation.readEnd();
                 value = playlistArraysChanged(aVersion, token);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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

    private class DoRead implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            long trackId;
            String metadata;
            try
            {
                invocation.readStart();
                id = invocation.readUint("Id");
                trackId = invocation.readUint("TrackId");
                invocation.readEnd();
                 metadata = read(aVersion, id, trackId);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            String trackIdList;
            String trackList;
            try
            {
                invocation.readStart();
                id = invocation.readUint("Id");
                trackIdList = invocation.readString("TrackIdList");
                invocation.readEnd();
                 trackList = readList(aVersion, id, trackIdList);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            long afterTrackId;
            String udn;
            String metadataId;
            long newTrackId;
            try
            {
                invocation.readStart();
                id = invocation.readUint("Id");
                afterTrackId = invocation.readUint("AfterTrackId");
                udn = invocation.readString("Udn");
                metadataId = invocation.readString("MetadataId");
                invocation.readEnd();
                 newTrackId = insert(aVersion, id, afterTrackId, udn, metadataId);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeUint("NewTrackId", newTrackId);
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
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long trackId;
            long value;
            try
            {
                invocation.readStart();
                trackId = invocation.readUint("TrackId");
                value = invocation.readUint("Value");
                invocation.readEnd();
                deleteId(aVersion, trackId, value);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
        public void actionInvoked(long aInvocation, int aVersion)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long trackId;
            try
            {
                invocation.readStart();
                trackId = invocation.readUint("TrackId");
                invocation.readEnd();
                deleteAll(aVersion, trackId);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
}

