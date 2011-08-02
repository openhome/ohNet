package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgPlaylistManager1.*;
import org.openhome.net.core.*;

	
interface ICpProxyAvOpenhomeOrgPlaylistManager1 extends ICpProxy
{
    public String syncMetadata();
    public void beginMetadata(ICpProxyListener aCallback);
    public String endMetadata(long aAsyncHandle);
    public String syncImagesXml();
    public void beginImagesXml(ICpProxyListener aCallback);
    public String endImagesXml(long aAsyncHandle);
    public byte[] syncPlaylistReadArray(long aId);
    public void beginPlaylistReadArray(long aId, ICpProxyListener aCallback);
    public byte[] endPlaylistReadArray(long aAsyncHandle);
    public String syncPlaylistReadMetadata(String aIdList);
    public void beginPlaylistReadMetadata(String aIdList, ICpProxyListener aCallback);
    public String endPlaylistReadMetadata(long aAsyncHandle);
    public PlaylistRead syncPlaylistRead(long aId);
    public void beginPlaylistRead(long aId, ICpProxyListener aCallback);
    public PlaylistRead endPlaylistRead(long aAsyncHandle);
    public void syncPlaylistUpdate(long aId, String aName, String aDescription, long aImageId);
    public void beginPlaylistUpdate(long aId, String aName, String aDescription, long aImageId, ICpProxyListener aCallback);
    public void endPlaylistUpdate(long aAsyncHandle);
    public long syncPlaylistInsert(long aAfterId, String aName, String aDescription, long aImageId);
    public void beginPlaylistInsert(long aAfterId, String aName, String aDescription, long aImageId, ICpProxyListener aCallback);
    public long endPlaylistInsert(long aAsyncHandle);
    public void syncPlaylistDeleteId(long aValue);
    public void beginPlaylistDeleteId(long aValue, ICpProxyListener aCallback);
    public void endPlaylistDeleteId(long aAsyncHandle);
    public long syncPlaylistsMax();
    public void beginPlaylistsMax(ICpProxyListener aCallback);
    public long endPlaylistsMax(long aAsyncHandle);
    public long syncTracksMax();
    public void beginTracksMax(ICpProxyListener aCallback);
    public long endTracksMax(long aAsyncHandle);
    public PlaylistArrays syncPlaylistArrays();
    public void beginPlaylistArrays(ICpProxyListener aCallback);
    public PlaylistArrays endPlaylistArrays(long aAsyncHandle);
    public boolean syncPlaylistArraysChanged(long aToken);
    public void beginPlaylistArraysChanged(long aToken, ICpProxyListener aCallback);
    public boolean endPlaylistArraysChanged(long aAsyncHandle);
    public String syncRead(long aId, long aTrackId);
    public void beginRead(long aId, long aTrackId, ICpProxyListener aCallback);
    public String endRead(long aAsyncHandle);
    public String syncReadList(long aId, String aTrackIdList);
    public void beginReadList(long aId, String aTrackIdList, ICpProxyListener aCallback);
    public String endReadList(long aAsyncHandle);
    public long syncInsert(long aId, long aAfterTrackId, String aUdn, String aMetadataId);
    public void beginInsert(long aId, long aAfterTrackId, String aUdn, String aMetadataId, ICpProxyListener aCallback);
    public long endInsert(long aAsyncHandle);
    public void syncDeleteId(long aTrackId, long aValue);
    public void beginDeleteId(long aTrackId, long aValue, ICpProxyListener aCallback);
    public void endDeleteId(long aAsyncHandle);
    public void syncDeleteAll(long aTrackId);
    public void beginDeleteAll(long aTrackId, ICpProxyListener aCallback);
    public void endDeleteAll(long aAsyncHandle);
    public void setPropertyMetadataChanged(IPropertyChangeListener aMetadataChanged);
    public String getPropertyMetadata();
    public void setPropertyImagesXmlChanged(IPropertyChangeListener aImagesXmlChanged);
    public String getPropertyImagesXml();
    public void setPropertyIdArrayChanged(IPropertyChangeListener aIdArrayChanged);
    public byte[] getPropertyIdArray();
    public void setPropertyTokenArrayChanged(IPropertyChangeListener aTokenArrayChanged);
    public byte[] getPropertyTokenArray();
    public void setPropertyPlaylistsMaxChanged(IPropertyChangeListener aPlaylistsMaxChanged);
    public long getPropertyPlaylistsMax();
    public void setPropertyTracksMaxChanged(IPropertyChangeListener aTracksMaxChanged);
    public long getPropertyTracksMax();
}

class SyncMetadataAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private String iMetadata;

    public SyncMetadataAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    public String getMetadata()
    {
        return iMetadata;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endMetadata(aAsyncHandle);
		
        iMetadata = result;
    }
}

class SyncImagesXmlAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private String iImagesXml;

    public SyncImagesXmlAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    public String getImagesXml()
    {
        return iImagesXml;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endImagesXml(aAsyncHandle);
		
        iImagesXml = result;
    }
}

class SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private byte[] iArray;

    public SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    public byte[] getArray()
    {
        return iArray;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        byte[] result = iService.endPlaylistReadArray(aAsyncHandle);
		
        iArray = result;
    }
}

class SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private String iMetadata;

    public SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    public String getMetadata()
    {
        return iMetadata;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endPlaylistReadMetadata(aAsyncHandle);
		
        iMetadata = result;
    }
}

class SyncPlaylistReadAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private String iName;
    private String iDescription;
    private long iImageId;

    public SyncPlaylistReadAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
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
    protected void completeRequest(long aAsyncHandle)
    {
        PlaylistRead result = iService.endPlaylistRead(aAsyncHandle);
		
        iName = result.getName();
        iDescription = result.getDescription();
        iImageId = result.getImageId();
    }
}

class SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;

    public SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPlaylistUpdate(aAsyncHandle);
		
    }
}

class SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private long iNewId;

    public SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    public long getNewId()
    {
        return iNewId;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endPlaylistInsert(aAsyncHandle);
		
        iNewId = result;
    }
}

class SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;

    public SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPlaylistDeleteId(aAsyncHandle);
		
    }
}

class SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private long iValue;

    public SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endPlaylistsMax(aAsyncHandle);
		
        iValue = result;
    }
}

class SyncTracksMaxAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private long iValue;

    public SyncTracksMaxAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
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

class SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private long iToken;
    private byte[] iIdArray;
    private byte[] iTokenArray;

    public SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
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
    protected void completeRequest(long aAsyncHandle)
    {
        PlaylistArrays result = iService.endPlaylistArrays(aAsyncHandle);
		
        iToken = result.getToken();
        iIdArray = result.getIdArray();
        iTokenArray = result.getTokenArray();
    }
}

class SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private boolean iValue;

    public SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endPlaylistArraysChanged(aAsyncHandle);
		
        iValue = result;
    }
}

class SyncReadAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private String iMetadata;

    public SyncReadAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
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

class SyncReadListAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private String iTrackList;

    public SyncReadListAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
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

class SyncInsertAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;
    private long iNewTrackId;

    public SyncInsertAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    public long getNewTrackId()
    {
        return iNewTrackId;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endInsert(aAsyncHandle);
		
        iNewTrackId = result;
    }
}

class SyncDeleteIdAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;

    public SyncDeleteIdAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDeleteId(aAsyncHandle);
		
    }
}

class SyncDeleteAllAvOpenhomeOrgPlaylistManager1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgPlaylistManager1 iService;

    public SyncDeleteAllAvOpenhomeOrgPlaylistManager1(CpProxyAvOpenhomeOrgPlaylistManager1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDeleteAll(aAsyncHandle);
		
    }
}

/**
 * Proxy for the av.openhome.org:PlaylistManager:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgPlaylistManager1 extends CpProxy implements ICpProxyAvOpenhomeOrgPlaylistManager1
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

    private Action iActionMetadata;
    private Action iActionImagesXml;
    private Action iActionPlaylistReadArray;
    private Action iActionPlaylistReadMetadata;
    private Action iActionPlaylistRead;
    private Action iActionPlaylistUpdate;
    private Action iActionPlaylistInsert;
    private Action iActionPlaylistDeleteId;
    private Action iActionPlaylistsMax;
    private Action iActionTracksMax;
    private Action iActionPlaylistArrays;
    private Action iActionPlaylistArraysChanged;
    private Action iActionRead;
    private Action iActionReadList;
    private Action iActionInsert;
    private Action iActionDeleteId;
    private Action iActionDeleteAll;
    private PropertyString iMetadata;
    private PropertyString iImagesXml;
    private PropertyBinary iIdArray;
    private PropertyBinary iTokenArray;
    private PropertyUint iPlaylistsMax;
    private PropertyUint iTracksMax;
    private IPropertyChangeListener iMetadataChanged;
    private IPropertyChangeListener iImagesXmlChanged;
    private IPropertyChangeListener iIdArrayChanged;
    private IPropertyChangeListener iTokenArrayChanged;
    private IPropertyChangeListener iPlaylistsMaxChanged;
    private IPropertyChangeListener iTracksMaxChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@code #subscribe}/{@code #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice	the device to use.
     */

    public CpProxyAvOpenhomeOrgPlaylistManager1(CpDevice aDevice)
    {
        super("av-openhome-org", "PlaylistManager", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionMetadata = new Action("Metadata");
        param = new ParameterString("Metadata", allowedValues);
		iActionMetadata.addOutputParameter(param);

        iActionImagesXml = new Action("ImagesXml");
        param = new ParameterString("ImagesXml", allowedValues);
		iActionImagesXml.addOutputParameter(param);

        iActionPlaylistReadArray = new Action("PlaylistReadArray");
        param = new ParameterUint("Id");
		iActionPlaylistReadArray.addInputParameter(param);
        param = new ParameterBinary("Array");
		iActionPlaylistReadArray.addOutputParameter(param);

        iActionPlaylistReadMetadata = new Action("PlaylistReadMetadata");
        param = new ParameterString("IdList", allowedValues);
		iActionPlaylistReadMetadata.addInputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
		iActionPlaylistReadMetadata.addOutputParameter(param);

        iActionPlaylistRead = new Action("PlaylistRead");
        param = new ParameterUint("Id");
		iActionPlaylistRead.addInputParameter(param);
        param = new ParameterString("Name", allowedValues);
		iActionPlaylistRead.addOutputParameter(param);
        param = new ParameterString("Description", allowedValues);
		iActionPlaylistRead.addOutputParameter(param);
        param = new ParameterUint("ImageId");
		iActionPlaylistRead.addOutputParameter(param);

        iActionPlaylistUpdate = new Action("PlaylistUpdate");
        param = new ParameterUint("Id");
		iActionPlaylistUpdate.addInputParameter(param);
        param = new ParameterString("Name", allowedValues);
		iActionPlaylistUpdate.addInputParameter(param);
        param = new ParameterString("Description", allowedValues);
		iActionPlaylistUpdate.addInputParameter(param);
        param = new ParameterUint("ImageId");
		iActionPlaylistUpdate.addInputParameter(param);

        iActionPlaylistInsert = new Action("PlaylistInsert");
        param = new ParameterUint("AfterId");
		iActionPlaylistInsert.addInputParameter(param);
        param = new ParameterString("Name", allowedValues);
		iActionPlaylistInsert.addInputParameter(param);
        param = new ParameterString("Description", allowedValues);
		iActionPlaylistInsert.addInputParameter(param);
        param = new ParameterUint("ImageId");
		iActionPlaylistInsert.addInputParameter(param);
        param = new ParameterUint("NewId");
		iActionPlaylistInsert.addOutputParameter(param);

        iActionPlaylistDeleteId = new Action("PlaylistDeleteId");
        param = new ParameterUint("Value");
		iActionPlaylistDeleteId.addInputParameter(param);

        iActionPlaylistsMax = new Action("PlaylistsMax");
        param = new ParameterUint("Value");
		iActionPlaylistsMax.addOutputParameter(param);

        iActionTracksMax = new Action("TracksMax");
        param = new ParameterUint("Value");
		iActionTracksMax.addOutputParameter(param);

        iActionPlaylistArrays = new Action("PlaylistArrays");
        param = new ParameterUint("Token");
		iActionPlaylistArrays.addOutputParameter(param);
        param = new ParameterBinary("IdArray");
		iActionPlaylistArrays.addOutputParameter(param);
        param = new ParameterBinary("TokenArray");
		iActionPlaylistArrays.addOutputParameter(param);

        iActionPlaylistArraysChanged = new Action("PlaylistArraysChanged");
        param = new ParameterUint("Token");
		iActionPlaylistArraysChanged.addInputParameter(param);
        param = new ParameterBool("Value");
		iActionPlaylistArraysChanged.addOutputParameter(param);

        iActionRead = new Action("Read");
        param = new ParameterUint("Id");
		iActionRead.addInputParameter(param);
        param = new ParameterUint("TrackId");
		iActionRead.addInputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
		iActionRead.addOutputParameter(param);

        iActionReadList = new Action("ReadList");
        param = new ParameterUint("Id");
		iActionReadList.addInputParameter(param);
        param = new ParameterString("TrackIdList", allowedValues);
		iActionReadList.addInputParameter(param);
        param = new ParameterString("TrackList", allowedValues);
		iActionReadList.addOutputParameter(param);

        iActionInsert = new Action("Insert");
        param = new ParameterUint("Id");
		iActionInsert.addInputParameter(param);
        param = new ParameterUint("AfterTrackId");
		iActionInsert.addInputParameter(param);
        param = new ParameterString("Udn", allowedValues);
		iActionInsert.addInputParameter(param);
        param = new ParameterString("MetadataId", allowedValues);
		iActionInsert.addInputParameter(param);
        param = new ParameterUint("NewTrackId");
		iActionInsert.addOutputParameter(param);

        iActionDeleteId = new Action("DeleteId");
        param = new ParameterUint("TrackId");
		iActionDeleteId.addInputParameter(param);
        param = new ParameterUint("Value");
		iActionDeleteId.addInputParameter(param);

        iActionDeleteAll = new Action("DeleteAll");
        param = new ParameterUint("TrackId");
		iActionDeleteAll.addInputParameter(param);

        iMetadataChanged = new PropertyChangeListener();
        iMetadata = new PropertyString("Metadata", iMetadataChanged);
		addProperty(iMetadata);
        iImagesXmlChanged = new PropertyChangeListener();
        iImagesXml = new PropertyString("ImagesXml", iImagesXmlChanged);
		addProperty(iImagesXml);
        iIdArrayChanged = new PropertyChangeListener();
        iIdArray = new PropertyBinary("IdArray", iIdArrayChanged);
		addProperty(iIdArray);
        iTokenArrayChanged = new PropertyChangeListener();
        iTokenArray = new PropertyBinary("TokenArray", iTokenArrayChanged);
		addProperty(iTokenArray);
        iPlaylistsMaxChanged = new PropertyChangeListener();
        iPlaylistsMax = new PropertyUint("PlaylistsMax", iPlaylistsMaxChanged);
		addProperty(iPlaylistsMax);
        iTracksMaxChanged = new PropertyChangeListener();
        iTracksMax = new PropertyUint("TracksMax", iTracksMaxChanged);
		addProperty(iTracksMax);
        iPropertyLock = new Object();
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
	    SyncMetadataAvOpenhomeOrgPlaylistManager1 sync = new SyncMetadataAvOpenhomeOrgPlaylistManager1(this);
	    beginMetadata(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getMetadata();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endMetadata}.
	 * 
	 * @param aCallback	listener to call back when action completes.
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
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginMetadata} method.
     * @return the result of the previously invoked action.
     */
	public String endMetadata(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
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
	public String syncImagesXml()
	{
	    SyncImagesXmlAvOpenhomeOrgPlaylistManager1 sync = new SyncImagesXmlAvOpenhomeOrgPlaylistManager1(this);
	    beginImagesXml(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getImagesXml();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endImagesXml}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginImagesXml(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionImagesXml, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionImagesXml.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginImagesXml} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginImagesXml} method.
     * @return the result of the previously invoked action.
     */
	public String endImagesXml(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        String imagesXml = Invocation.getOutputString(aAsyncHandle, index++);
        return imagesXml;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public byte[] syncPlaylistReadArray(long aId)
	{
	    SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistReadArrayAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistReadArray(aId, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getArray();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistReadArray}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistReadArray(long aId, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistReadArray, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlaylistReadArray.getInputParameter(inIndex++), aId));
        int outIndex = 0;
        invocation.addOutput(new ArgumentBinary((ParameterBinary)iActionPlaylistReadArray.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistReadArray} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistReadArray} method.
     * @return the result of the previously invoked action.
     */
	public byte[] endPlaylistReadArray(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        byte[] array = Invocation.getOutputBinary(aAsyncHandle, index++);
        return array;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public String syncPlaylistReadMetadata(String aIdList)
	{
	    SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistReadMetadataAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistReadMetadata(aIdList, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getMetadata();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistReadMetadata}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistReadMetadata(String aIdList, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistReadMetadata, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionPlaylistReadMetadata.getInputParameter(inIndex++), aIdList));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionPlaylistReadMetadata.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistReadMetadata} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistReadMetadata} method.
     * @return the result of the previously invoked action.
     */
	public String endPlaylistReadMetadata(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
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
	public PlaylistRead syncPlaylistRead(long aId)
	{
	    SyncPlaylistReadAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistReadAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistRead(aId, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return new PlaylistRead(
            sync.getName(),
            sync.getDescription(),
            sync.getImageId()
		);
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistRead}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistRead(long aId, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistRead, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlaylistRead.getInputParameter(inIndex++), aId));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionPlaylistRead.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionPlaylistRead.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionPlaylistRead.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistRead} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistRead} method.
     * @return the result of the previously invoked action.
     */
	public PlaylistRead endPlaylistRead(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        String name = Invocation.getOutputString(aAsyncHandle, index++);
        String description = Invocation.getOutputString(aAsyncHandle, index++);
        long imageId = Invocation.getOutputUint(aAsyncHandle, index++);
        return new PlaylistRead(
            name,
            description,
            imageId
		);
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncPlaylistUpdate(long aId, String aName, String aDescription, long aImageId)
	{
	    SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistUpdateAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistUpdate(aId, aName, aDescription, aImageId, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistUpdate}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistUpdate(long aId, String aName, String aDescription, long aImageId, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistUpdate, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlaylistUpdate.getInputParameter(inIndex++), aId));
        invocation.addInput(new ArgumentString((ParameterString)iActionPlaylistUpdate.getInputParameter(inIndex++), aName));
        invocation.addInput(new ArgumentString((ParameterString)iActionPlaylistUpdate.getInputParameter(inIndex++), aDescription));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlaylistUpdate.getInputParameter(inIndex++), aImageId));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistUpdate} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistUpdate} method.
     */
	public void endPlaylistUpdate(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public long syncPlaylistInsert(long aAfterId, String aName, String aDescription, long aImageId)
	{
	    SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistInsertAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistInsert(aAfterId, aName, aDescription, aImageId, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getNewId();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistInsert}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistInsert(long aAfterId, String aName, String aDescription, long aImageId, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistInsert, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlaylistInsert.getInputParameter(inIndex++), aAfterId));
        invocation.addInput(new ArgumentString((ParameterString)iActionPlaylistInsert.getInputParameter(inIndex++), aName));
        invocation.addInput(new ArgumentString((ParameterString)iActionPlaylistInsert.getInputParameter(inIndex++), aDescription));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlaylistInsert.getInputParameter(inIndex++), aImageId));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionPlaylistInsert.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistInsert} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistInsert} method.
     * @return the result of the previously invoked action.
     */
	public long endPlaylistInsert(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
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
	public void syncPlaylistDeleteId(long aValue)
	{
	    SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistDeleteIdAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistDeleteId(aValue, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistDeleteId}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistDeleteId(long aValue, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistDeleteId, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlaylistDeleteId.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistDeleteId} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistDeleteId} method.
     */
	public void endPlaylistDeleteId(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public long syncPlaylistsMax()
	{
	    SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistsMaxAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistsMax(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getValue();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistsMax}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistsMax(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistsMax, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionPlaylistsMax.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistsMax} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistsMax} method.
     * @return the result of the previously invoked action.
     */
	public long endPlaylistsMax(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
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
	public long syncTracksMax()
	{
	    SyncTracksMaxAvOpenhomeOrgPlaylistManager1 sync = new SyncTracksMaxAvOpenhomeOrgPlaylistManager1(this);
	    beginTracksMax(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getValue();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endTracksMax}.
	 * 
	 * @param aCallback	listener to call back when action completes.
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
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginTracksMax} method.
     * @return the result of the previously invoked action.
     */
	public long endTracksMax(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
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
	public PlaylistArrays syncPlaylistArrays()
	{
	    SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistArraysAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistArrays(sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return new PlaylistArrays(
            sync.getToken(),
            sync.getIdArray(),
            sync.getTokenArray()
		);
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistArrays}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistArrays(ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistArrays, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionPlaylistArrays.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentBinary((ParameterBinary)iActionPlaylistArrays.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentBinary((ParameterBinary)iActionPlaylistArrays.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistArrays} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistArrays} method.
     * @return the result of the previously invoked action.
     */
	public PlaylistArrays endPlaylistArrays(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        long token = Invocation.getOutputUint(aAsyncHandle, index++);
        byte[] idArray = Invocation.getOutputBinary(aAsyncHandle, index++);
        byte[] tokenArray = Invocation.getOutputBinary(aAsyncHandle, index++);
        return new PlaylistArrays(
            token,
            idArray,
            tokenArray
		);
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
	public boolean syncPlaylistArraysChanged(long aToken)
	{
	    SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1 sync = new SyncPlaylistArraysChangedAvOpenhomeOrgPlaylistManager1(this);
	    beginPlaylistArraysChanged(aToken, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getValue();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endPlaylistArraysChanged}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginPlaylistArraysChanged(long aToken, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionPlaylistArraysChanged, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionPlaylistArraysChanged.getInputParameter(inIndex++), aToken));
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionPlaylistArraysChanged.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPlaylistArraysChanged} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginPlaylistArraysChanged} method.
     * @return the result of the previously invoked action.
     */
	public boolean endPlaylistArraysChanged(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
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
	public String syncRead(long aId, long aTrackId)
	{
	    SyncReadAvOpenhomeOrgPlaylistManager1 sync = new SyncReadAvOpenhomeOrgPlaylistManager1(this);
	    beginRead(aId, aTrackId, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getMetadata();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endRead}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginRead(long aId, long aTrackId, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionRead, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionRead.getInputParameter(inIndex++), aId));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionRead.getInputParameter(inIndex++), aTrackId));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionRead.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginRead} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginRead} method.
     * @return the result of the previously invoked action.
     */
	public String endRead(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
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
	public String syncReadList(long aId, String aTrackIdList)
	{
	    SyncReadListAvOpenhomeOrgPlaylistManager1 sync = new SyncReadListAvOpenhomeOrgPlaylistManager1(this);
	    beginReadList(aId, aTrackIdList, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getTrackList();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endReadList}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginReadList(long aId, String aTrackIdList, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionReadList, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionReadList.getInputParameter(inIndex++), aId));
        invocation.addInput(new ArgumentString((ParameterString)iActionReadList.getInputParameter(inIndex++), aTrackIdList));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionReadList.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginReadList} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginReadList} method.
     * @return the result of the previously invoked action.
     */
	public String endReadList(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
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
	public long syncInsert(long aId, long aAfterTrackId, String aUdn, String aMetadataId)
	{
	    SyncInsertAvOpenhomeOrgPlaylistManager1 sync = new SyncInsertAvOpenhomeOrgPlaylistManager1(this);
	    beginInsert(aId, aAfterTrackId, aUdn, aMetadataId, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }

        return sync.getNewTrackId();
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endInsert}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginInsert(long aId, long aAfterTrackId, String aUdn, String aMetadataId, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionInsert, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionInsert.getInputParameter(inIndex++), aId));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionInsert.getInputParameter(inIndex++), aAfterTrackId));
        invocation.addInput(new ArgumentString((ParameterString)iActionInsert.getInputParameter(inIndex++), aUdn));
        invocation.addInput(new ArgumentString((ParameterString)iActionInsert.getInputParameter(inIndex++), aMetadataId));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionInsert.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginInsert} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginInsert} method.
     * @return the result of the previously invoked action.
     */
	public long endInsert(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
        int index = 0;
        long newTrackId = Invocation.getOutputUint(aAsyncHandle, index++);
        return newTrackId;
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncDeleteId(long aTrackId, long aValue)
	{
	    SyncDeleteIdAvOpenhomeOrgPlaylistManager1 sync = new SyncDeleteIdAvOpenhomeOrgPlaylistManager1(this);
	    beginDeleteId(aTrackId, aValue, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endDeleteId}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginDeleteId(long aTrackId, long aValue, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionDeleteId, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionDeleteId.getInputParameter(inIndex++), aTrackId));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionDeleteId.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDeleteId} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginDeleteId} method.
     */
	public void endDeleteId(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
	public void syncDeleteAll(long aTrackId)
	{
	    SyncDeleteAllAvOpenhomeOrgPlaylistManager1 sync = new SyncDeleteAllAvOpenhomeOrgPlaylistManager1(this);
	    beginDeleteAll(aTrackId, sync.getListener());
	    sync.waitToComplete();

        try
        {
            sync.reportError();
        }
        catch (ProxyError pe) { }
	}
	
	/**
	 * Invoke the action asynchronously.
	 * Returns immediately and will run the client-specified callback when the
	 * action later completes.  Any output arguments can then be retrieved by
	 * calling {@link #endDeleteAll}.
	 * 
	 * @param aCallback	listener to call back when action completes.
	 */
	public void beginDeleteAll(long aTrackId, ICpProxyListener aCallback)
	{
        Invocation invocation = iService.getInvocation(iActionDeleteAll, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionDeleteAll.getInputParameter(inIndex++), aTrackId));
        iService.invokeAction(invocation);
    }

	/**
	 * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDeleteAll} method.
     *
     * @param aAsyncHandle	argument passed to the delegate set in the
	 *			{@link #beginDeleteAll} method.
     */
	public void endDeleteAll(long aAsyncHandle)
    {
        if (Invocation.error(aAsyncHandle))
        {
            throw new ProxyError();
        }
    }
		
    /**
     * Set a delegate to be run when the Metadata state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyAvOpenhomeOrgPlaylistManager1 instance will not overlap.
     *
     * @param aMetadataChanged	the listener to call back when the state
	 * 			variable changes.
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
     * Set a delegate to be run when the ImagesXml state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyAvOpenhomeOrgPlaylistManager1 instance will not overlap.
     *
     * @param aImagesXmlChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyImagesXmlChanged(IPropertyChangeListener aImagesXmlChanged)
    {
        synchronized (iPropertyLock)
        {
            iImagesXmlChanged = aImagesXmlChanged;
        }
    }

    private void imagesXmlPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iImagesXmlChanged);
        }
    }
    /**
     * Set a delegate to be run when the IdArray state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyAvOpenhomeOrgPlaylistManager1 instance will not overlap.
     *
     * @param aIdArrayChanged	the listener to call back when the state
	 * 			variable changes.
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
     * Set a delegate to be run when the TokenArray state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyAvOpenhomeOrgPlaylistManager1 instance will not overlap.
     *
     * @param aTokenArrayChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyTokenArrayChanged(IPropertyChangeListener aTokenArrayChanged)
    {
        synchronized (iPropertyLock)
        {
            iTokenArrayChanged = aTokenArrayChanged;
        }
    }

    private void tokenArrayPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iTokenArrayChanged);
        }
    }
    /**
     * Set a delegate to be run when the PlaylistsMax state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyAvOpenhomeOrgPlaylistManager1 instance will not overlap.
     *
     * @param aPlaylistsMaxChanged	the listener to call back when the state
	 * 			variable changes.
     */
    public void setPropertyPlaylistsMaxChanged(IPropertyChangeListener aPlaylistsMaxChanged)
    {
        synchronized (iPropertyLock)
        {
            iPlaylistsMaxChanged = aPlaylistsMaxChanged;
        }
    }

    private void playlistsMaxPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iPlaylistsMaxChanged);
        }
    }
    /**
     * Set a delegate to be run when the TracksMax state variable changes.
     * Callbacks may be run in different threads but callbacks for a
	 * CpProxyAvOpenhomeOrgPlaylistManager1 instance will not overlap.
     *
     * @param aTracksMaxChanged	the listener to call back when the state
	 * 			variable changes.
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
     * Query the value of the Metadata property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the Metadata property.
     */
    public String getPropertyMetadata()
    {
        propertyReadLock();
        String val = iMetadata.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the ImagesXml property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the ImagesXml property.
     */
    public String getPropertyImagesXml()
    {
        propertyReadLock();
        String val = iImagesXml.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the IdArray property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the IdArray property.
     */
    public byte[] getPropertyIdArray()
    {
        propertyReadLock();
        byte[] val = iIdArray.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the TokenArray property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the TokenArray property.
     */
    public byte[] getPropertyTokenArray()
    {
        propertyReadLock();
        byte[] val = iTokenArray.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the PlaylistsMax property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the PlaylistsMax property.
     */
    public long getPropertyPlaylistsMax()
    {
        propertyReadLock();
        long val = iPlaylistsMax.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Query the value of the TracksMax property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
	 * @return	value of the TracksMax property.
     */
    public long getPropertyTracksMax()
    {
        propertyReadLock();
        long val = iTracksMax.getValue();
        propertyReadUnlock();
        return val;
    }
	
    /**
     * Dispose of this control point proxy.
     * Must be called for each class instance.  Must be called before {@code
     * Library.close()}.
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
            iActionMetadata.destroy();
            iActionImagesXml.destroy();
            iActionPlaylistReadArray.destroy();
            iActionPlaylistReadMetadata.destroy();
            iActionPlaylistRead.destroy();
            iActionPlaylistUpdate.destroy();
            iActionPlaylistInsert.destroy();
            iActionPlaylistDeleteId.destroy();
            iActionPlaylistsMax.destroy();
            iActionTracksMax.destroy();
            iActionPlaylistArrays.destroy();
            iActionPlaylistArraysChanged.destroy();
            iActionRead.destroy();
            iActionReadList.destroy();
            iActionInsert.destroy();
            iActionDeleteId.destroy();
            iActionDeleteAll.destroy();
            iMetadata.destroy();
            iImagesXml.destroy();
            iIdArray.destroy();
            iTokenArray.destroy();
            iPlaylistsMax.destroy();
            iTracksMax.destroy();
        }
    }
}

