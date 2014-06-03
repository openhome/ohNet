package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgContentDirectory3.*;
import org.openhome.net.core.*;

    
interface ICpProxyUpnpOrgContentDirectory3 extends ICpProxy
{
    public String syncGetSearchCapabilities();
    public void beginGetSearchCapabilities(ICpProxyListener aCallback);
    public String endGetSearchCapabilities(long aAsyncHandle);
    public String syncGetSortCapabilities();
    public void beginGetSortCapabilities(ICpProxyListener aCallback);
    public String endGetSortCapabilities(long aAsyncHandle);
    public String syncGetSortExtensionCapabilities();
    public void beginGetSortExtensionCapabilities(ICpProxyListener aCallback);
    public String endGetSortExtensionCapabilities(long aAsyncHandle);
    public String syncGetFeatureList();
    public void beginGetFeatureList(ICpProxyListener aCallback);
    public String endGetFeatureList(long aAsyncHandle);
    public long syncGetSystemUpdateID();
    public void beginGetSystemUpdateID(ICpProxyListener aCallback);
    public long endGetSystemUpdateID(long aAsyncHandle);
    public String syncGetServiceResetToken();
    public void beginGetServiceResetToken(ICpProxyListener aCallback);
    public String endGetServiceResetToken(long aAsyncHandle);
    public Browse syncBrowse(String aObjectID, String aBrowseFlag, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria);
    public void beginBrowse(String aObjectID, String aBrowseFlag, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria, ICpProxyListener aCallback);
    public Browse endBrowse(long aAsyncHandle);
    public Search syncSearch(String aContainerID, String aSearchCriteria, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria);
    public void beginSearch(String aContainerID, String aSearchCriteria, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria, ICpProxyListener aCallback);
    public Search endSearch(long aAsyncHandle);
    public CreateObject syncCreateObject(String aContainerID, String aElements);
    public void beginCreateObject(String aContainerID, String aElements, ICpProxyListener aCallback);
    public CreateObject endCreateObject(long aAsyncHandle);
    public void syncDestroyObject(String aObjectID);
    public void beginDestroyObject(String aObjectID, ICpProxyListener aCallback);
    public void endDestroyObject(long aAsyncHandle);
    public void syncUpdateObject(String aObjectID, String aCurrentTagValue, String aNewTagValue);
    public void beginUpdateObject(String aObjectID, String aCurrentTagValue, String aNewTagValue, ICpProxyListener aCallback);
    public void endUpdateObject(long aAsyncHandle);
    public String syncMoveObject(String aObjectID, String aNewParentID);
    public void beginMoveObject(String aObjectID, String aNewParentID, ICpProxyListener aCallback);
    public String endMoveObject(long aAsyncHandle);
    public long syncImportResource(String aSourceURI, String aDestinationURI);
    public void beginImportResource(String aSourceURI, String aDestinationURI, ICpProxyListener aCallback);
    public long endImportResource(long aAsyncHandle);
    public long syncExportResource(String aSourceURI, String aDestinationURI);
    public void beginExportResource(String aSourceURI, String aDestinationURI, ICpProxyListener aCallback);
    public long endExportResource(long aAsyncHandle);
    public void syncDeleteResource(String aResourceURI);
    public void beginDeleteResource(String aResourceURI, ICpProxyListener aCallback);
    public void endDeleteResource(long aAsyncHandle);
    public void syncStopTransferResource(long aTransferID);
    public void beginStopTransferResource(long aTransferID, ICpProxyListener aCallback);
    public void endStopTransferResource(long aAsyncHandle);
    public GetTransferProgress syncGetTransferProgress(long aTransferID);
    public void beginGetTransferProgress(long aTransferID, ICpProxyListener aCallback);
    public GetTransferProgress endGetTransferProgress(long aAsyncHandle);
    public String syncCreateReference(String aContainerID, String aObjectID);
    public void beginCreateReference(String aContainerID, String aObjectID, ICpProxyListener aCallback);
    public String endCreateReference(long aAsyncHandle);
    public FreeFormQuery syncFreeFormQuery(String aContainerID, long aCDSView, String aQueryRequest);
    public void beginFreeFormQuery(String aContainerID, long aCDSView, String aQueryRequest, ICpProxyListener aCallback);
    public FreeFormQuery endFreeFormQuery(long aAsyncHandle);
    public String syncGetFreeFormQueryCapabilities();
    public void beginGetFreeFormQueryCapabilities(ICpProxyListener aCallback);
    public String endGetFreeFormQueryCapabilities(long aAsyncHandle);
    public void setPropertySystemUpdateIDChanged(IPropertyChangeListener aSystemUpdateIDChanged);
    public long getPropertySystemUpdateID();
    public void setPropertyContainerUpdateIDsChanged(IPropertyChangeListener aContainerUpdateIDsChanged);
    public String getPropertyContainerUpdateIDs();
    public void setPropertyLastChangeChanged(IPropertyChangeListener aLastChangeChanged);
    public String getPropertyLastChange();
    public void setPropertyTransferIDsChanged(IPropertyChangeListener aTransferIDsChanged);
    public String getPropertyTransferIDs();
}

class SyncGetSearchCapabilitiesUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iSearchCaps;

    public SyncGetSearchCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getSearchCaps()
    {
        return iSearchCaps;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetSearchCapabilities(aAsyncHandle);
        
        iSearchCaps = result;
    }
}

class SyncGetSortCapabilitiesUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iSortCaps;

    public SyncGetSortCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getSortCaps()
    {
        return iSortCaps;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetSortCapabilities(aAsyncHandle);
        
        iSortCaps = result;
    }
}

class SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iSortExtensionCaps;

    public SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getSortExtensionCaps()
    {
        return iSortExtensionCaps;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetSortExtensionCapabilities(aAsyncHandle);
        
        iSortExtensionCaps = result;
    }
}

class SyncGetFeatureListUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iFeatureList;

    public SyncGetFeatureListUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getFeatureList()
    {
        return iFeatureList;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetFeatureList(aAsyncHandle);
        
        iFeatureList = result;
    }
}

class SyncGetSystemUpdateIDUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private long iId;

    public SyncGetSystemUpdateIDUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public long getId()
    {
        return iId;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetSystemUpdateID(aAsyncHandle);
        
        iId = result;
    }
}

class SyncGetServiceResetTokenUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iResetToken;

    public SyncGetServiceResetTokenUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getResetToken()
    {
        return iResetToken;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetServiceResetToken(aAsyncHandle);
        
        iResetToken = result;
    }
}

class SyncBrowseUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iResult;
    private long iNumberReturned;
    private long iTotalMatches;
    private long iUpdateID;

    public SyncBrowseUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getResult()
    {
        return iResult;
    }
    public long getNumberReturned()
    {
        return iNumberReturned;
    }
    public long getTotalMatches()
    {
        return iTotalMatches;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        Browse result = iService.endBrowse(aAsyncHandle);
        
        iResult = result.getResult();
        iNumberReturned = result.getNumberReturned();
        iTotalMatches = result.getTotalMatches();
        iUpdateID = result.getUpdateID();
    }
}

class SyncSearchUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iResult;
    private long iNumberReturned;
    private long iTotalMatches;
    private long iUpdateID;

    public SyncSearchUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getResult()
    {
        return iResult;
    }
    public long getNumberReturned()
    {
        return iNumberReturned;
    }
    public long getTotalMatches()
    {
        return iTotalMatches;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        Search result = iService.endSearch(aAsyncHandle);
        
        iResult = result.getResult();
        iNumberReturned = result.getNumberReturned();
        iTotalMatches = result.getTotalMatches();
        iUpdateID = result.getUpdateID();
    }
}

class SyncCreateObjectUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iObjectID;
    private String iResult;

    public SyncCreateObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getObjectID()
    {
        return iObjectID;
    }
    public String getResult()
    {
        return iResult;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        CreateObject result = iService.endCreateObject(aAsyncHandle);
        
        iObjectID = result.getObjectID();
        iResult = result.getResult();
    }
}

class SyncDestroyObjectUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;

    public SyncDestroyObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDestroyObject(aAsyncHandle);
        
    }
}

class SyncUpdateObjectUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;

    public SyncUpdateObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endUpdateObject(aAsyncHandle);
        
    }
}

class SyncMoveObjectUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iNewObjectID;

    public SyncMoveObjectUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getNewObjectID()
    {
        return iNewObjectID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endMoveObject(aAsyncHandle);
        
        iNewObjectID = result;
    }
}

class SyncImportResourceUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private long iTransferID;

    public SyncImportResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public long getTransferID()
    {
        return iTransferID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endImportResource(aAsyncHandle);
        
        iTransferID = result;
    }
}

class SyncExportResourceUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private long iTransferID;

    public SyncExportResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public long getTransferID()
    {
        return iTransferID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endExportResource(aAsyncHandle);
        
        iTransferID = result;
    }
}

class SyncDeleteResourceUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;

    public SyncDeleteResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endDeleteResource(aAsyncHandle);
        
    }
}

class SyncStopTransferResourceUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;

    public SyncStopTransferResourceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStopTransferResource(aAsyncHandle);
        
    }
}

class SyncGetTransferProgressUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iTransferStatus;
    private String iTransferLength;
    private String iTransferTotal;

    public SyncGetTransferProgressUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getTransferStatus()
    {
        return iTransferStatus;
    }
    public String getTransferLength()
    {
        return iTransferLength;
    }
    public String getTransferTotal()
    {
        return iTransferTotal;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetTransferProgress result = iService.endGetTransferProgress(aAsyncHandle);
        
        iTransferStatus = result.getTransferStatus();
        iTransferLength = result.getTransferLength();
        iTransferTotal = result.getTransferTotal();
    }
}

class SyncCreateReferenceUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iNewID;

    public SyncCreateReferenceUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getNewID()
    {
        return iNewID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endCreateReference(aAsyncHandle);
        
        iNewID = result;
    }
}

class SyncFreeFormQueryUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iQueryResult;
    private long iUpdateID;

    public SyncFreeFormQueryUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getQueryResult()
    {
        return iQueryResult;
    }
    public long getUpdateID()
    {
        return iUpdateID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        FreeFormQuery result = iService.endFreeFormQuery(aAsyncHandle);
        
        iQueryResult = result.getQueryResult();
        iUpdateID = result.getUpdateID();
    }
}

class SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3 extends SyncProxyAction
{
    private CpProxyUpnpOrgContentDirectory3 iService;
    private String iFFQCapabilities;

    public SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3(CpProxyUpnpOrgContentDirectory3 aProxy)
    {
        iService = aProxy;
    }
    public String getFFQCapabilities()
    {
        return iFFQCapabilities;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetFreeFormQueryCapabilities(aAsyncHandle);
        
        iFFQCapabilities = result;
    }
}

/**
 * Proxy for the upnp.org:ContentDirectory:3 UPnP service
 */
public class CpProxyUpnpOrgContentDirectory3 extends CpProxy implements ICpProxyUpnpOrgContentDirectory3
{

    public class Browse
    {
        private String iResult;
        private long iNumberReturned;
        private long iTotalMatches;
        private long iUpdateID;

        public Browse(
            String aResult,
            long aNumberReturned,
            long aTotalMatches,
            long aUpdateID
        )
        {
            iResult = aResult;
            iNumberReturned = aNumberReturned;
            iTotalMatches = aTotalMatches;
            iUpdateID = aUpdateID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getNumberReturned()
        {
            return iNumberReturned;
        }
        public long getTotalMatches()
        {
            return iTotalMatches;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class Search
    {
        private String iResult;
        private long iNumberReturned;
        private long iTotalMatches;
        private long iUpdateID;

        public Search(
            String aResult,
            long aNumberReturned,
            long aTotalMatches,
            long aUpdateID
        )
        {
            iResult = aResult;
            iNumberReturned = aNumberReturned;
            iTotalMatches = aTotalMatches;
            iUpdateID = aUpdateID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getNumberReturned()
        {
            return iNumberReturned;
        }
        public long getTotalMatches()
        {
            return iTotalMatches;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class CreateObject
    {
        private String iObjectID;
        private String iResult;

        public CreateObject(
            String aObjectID,
            String aResult
        )
        {
            iObjectID = aObjectID;
            iResult = aResult;
        }
        public String getObjectID()
        {
            return iObjectID;
        }
        public String getResult()
        {
            return iResult;
        }
    }

    public class GetTransferProgress
    {
        private String iTransferStatus;
        private String iTransferLength;
        private String iTransferTotal;

        public GetTransferProgress(
            String aTransferStatus,
            String aTransferLength,
            String aTransferTotal
        )
        {
            iTransferStatus = aTransferStatus;
            iTransferLength = aTransferLength;
            iTransferTotal = aTransferTotal;
        }
        public String getTransferStatus()
        {
            return iTransferStatus;
        }
        public String getTransferLength()
        {
            return iTransferLength;
        }
        public String getTransferTotal()
        {
            return iTransferTotal;
        }
    }

    public class FreeFormQuery
    {
        private String iQueryResult;
        private long iUpdateID;

        public FreeFormQuery(
            String aQueryResult,
            long aUpdateID
        )
        {
            iQueryResult = aQueryResult;
            iUpdateID = aUpdateID;
        }
        public String getQueryResult()
        {
            return iQueryResult;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    private Action iActionGetSearchCapabilities;
    private Action iActionGetSortCapabilities;
    private Action iActionGetSortExtensionCapabilities;
    private Action iActionGetFeatureList;
    private Action iActionGetSystemUpdateID;
    private Action iActionGetServiceResetToken;
    private Action iActionBrowse;
    private Action iActionSearch;
    private Action iActionCreateObject;
    private Action iActionDestroyObject;
    private Action iActionUpdateObject;
    private Action iActionMoveObject;
    private Action iActionImportResource;
    private Action iActionExportResource;
    private Action iActionDeleteResource;
    private Action iActionStopTransferResource;
    private Action iActionGetTransferProgress;
    private Action iActionCreateReference;
    private Action iActionFreeFormQuery;
    private Action iActionGetFreeFormQueryCapabilities;
    private PropertyUint iSystemUpdateID;
    private PropertyString iContainerUpdateIDs;
    private PropertyString iLastChange;
    private PropertyString iTransferIDs;
    private IPropertyChangeListener iSystemUpdateIDChanged;
    private IPropertyChangeListener iContainerUpdateIDsChanged;
    private IPropertyChangeListener iLastChangeChanged;
    private IPropertyChangeListener iTransferIDsChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyUpnpOrgContentDirectory3(CpDevice aDevice)
    {
        super("schemas-upnp-org", "ContentDirectory", 3, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionGetSearchCapabilities = new Action("GetSearchCapabilities");
        param = new ParameterString("SearchCaps", allowedValues);
        iActionGetSearchCapabilities.addOutputParameter(param);

        iActionGetSortCapabilities = new Action("GetSortCapabilities");
        param = new ParameterString("SortCaps", allowedValues);
        iActionGetSortCapabilities.addOutputParameter(param);

        iActionGetSortExtensionCapabilities = new Action("GetSortExtensionCapabilities");
        param = new ParameterString("SortExtensionCaps", allowedValues);
        iActionGetSortExtensionCapabilities.addOutputParameter(param);

        iActionGetFeatureList = new Action("GetFeatureList");
        param = new ParameterString("FeatureList", allowedValues);
        iActionGetFeatureList.addOutputParameter(param);

        iActionGetSystemUpdateID = new Action("GetSystemUpdateID");
        param = new ParameterUint("Id");
        iActionGetSystemUpdateID.addOutputParameter(param);

        iActionGetServiceResetToken = new Action("GetServiceResetToken");
        param = new ParameterString("ResetToken", allowedValues);
        iActionGetServiceResetToken.addOutputParameter(param);

        iActionBrowse = new Action("Browse");
        param = new ParameterString("ObjectID", allowedValues);
        iActionBrowse.addInputParameter(param);
        allowedValues.add("BrowseMetadata");
        allowedValues.add("BrowseDirectChildren");
        param = new ParameterString("BrowseFlag", allowedValues);
        iActionBrowse.addInputParameter(param);
        allowedValues.clear();
        param = new ParameterString("Filter", allowedValues);
        iActionBrowse.addInputParameter(param);
        param = new ParameterUint("StartingIndex");
        iActionBrowse.addInputParameter(param);
        param = new ParameterUint("RequestedCount");
        iActionBrowse.addInputParameter(param);
        param = new ParameterString("SortCriteria", allowedValues);
        iActionBrowse.addInputParameter(param);
        param = new ParameterString("Result", allowedValues);
        iActionBrowse.addOutputParameter(param);
        param = new ParameterUint("NumberReturned");
        iActionBrowse.addOutputParameter(param);
        param = new ParameterUint("TotalMatches");
        iActionBrowse.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionBrowse.addOutputParameter(param);

        iActionSearch = new Action("Search");
        param = new ParameterString("ContainerID", allowedValues);
        iActionSearch.addInputParameter(param);
        param = new ParameterString("SearchCriteria", allowedValues);
        iActionSearch.addInputParameter(param);
        param = new ParameterString("Filter", allowedValues);
        iActionSearch.addInputParameter(param);
        param = new ParameterUint("StartingIndex");
        iActionSearch.addInputParameter(param);
        param = new ParameterUint("RequestedCount");
        iActionSearch.addInputParameter(param);
        param = new ParameterString("SortCriteria", allowedValues);
        iActionSearch.addInputParameter(param);
        param = new ParameterString("Result", allowedValues);
        iActionSearch.addOutputParameter(param);
        param = new ParameterUint("NumberReturned");
        iActionSearch.addOutputParameter(param);
        param = new ParameterUint("TotalMatches");
        iActionSearch.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionSearch.addOutputParameter(param);

        iActionCreateObject = new Action("CreateObject");
        param = new ParameterString("ContainerID", allowedValues);
        iActionCreateObject.addInputParameter(param);
        param = new ParameterString("Elements", allowedValues);
        iActionCreateObject.addInputParameter(param);
        param = new ParameterString("ObjectID", allowedValues);
        iActionCreateObject.addOutputParameter(param);
        param = new ParameterString("Result", allowedValues);
        iActionCreateObject.addOutputParameter(param);

        iActionDestroyObject = new Action("DestroyObject");
        param = new ParameterString("ObjectID", allowedValues);
        iActionDestroyObject.addInputParameter(param);

        iActionUpdateObject = new Action("UpdateObject");
        param = new ParameterString("ObjectID", allowedValues);
        iActionUpdateObject.addInputParameter(param);
        param = new ParameterString("CurrentTagValue", allowedValues);
        iActionUpdateObject.addInputParameter(param);
        param = new ParameterString("NewTagValue", allowedValues);
        iActionUpdateObject.addInputParameter(param);

        iActionMoveObject = new Action("MoveObject");
        param = new ParameterString("ObjectID", allowedValues);
        iActionMoveObject.addInputParameter(param);
        param = new ParameterString("NewParentID", allowedValues);
        iActionMoveObject.addInputParameter(param);
        param = new ParameterString("NewObjectID", allowedValues);
        iActionMoveObject.addOutputParameter(param);

        iActionImportResource = new Action("ImportResource");
        param = new ParameterString("SourceURI", allowedValues);
        iActionImportResource.addInputParameter(param);
        param = new ParameterString("DestinationURI", allowedValues);
        iActionImportResource.addInputParameter(param);
        param = new ParameterUint("TransferID");
        iActionImportResource.addOutputParameter(param);

        iActionExportResource = new Action("ExportResource");
        param = new ParameterString("SourceURI", allowedValues);
        iActionExportResource.addInputParameter(param);
        param = new ParameterString("DestinationURI", allowedValues);
        iActionExportResource.addInputParameter(param);
        param = new ParameterUint("TransferID");
        iActionExportResource.addOutputParameter(param);

        iActionDeleteResource = new Action("DeleteResource");
        param = new ParameterString("ResourceURI", allowedValues);
        iActionDeleteResource.addInputParameter(param);

        iActionStopTransferResource = new Action("StopTransferResource");
        param = new ParameterUint("TransferID");
        iActionStopTransferResource.addInputParameter(param);

        iActionGetTransferProgress = new Action("GetTransferProgress");
        param = new ParameterUint("TransferID");
        iActionGetTransferProgress.addInputParameter(param);
        allowedValues.add("COMPLETED");
        allowedValues.add("ERROR");
        allowedValues.add("IN_PROGRESS");
        allowedValues.add("STOPPED");
        param = new ParameterString("TransferStatus", allowedValues);
        iActionGetTransferProgress.addOutputParameter(param);
        allowedValues.clear();
        param = new ParameterString("TransferLength", allowedValues);
        iActionGetTransferProgress.addOutputParameter(param);
        param = new ParameterString("TransferTotal", allowedValues);
        iActionGetTransferProgress.addOutputParameter(param);

        iActionCreateReference = new Action("CreateReference");
        param = new ParameterString("ContainerID", allowedValues);
        iActionCreateReference.addInputParameter(param);
        param = new ParameterString("ObjectID", allowedValues);
        iActionCreateReference.addInputParameter(param);
        param = new ParameterString("NewID", allowedValues);
        iActionCreateReference.addOutputParameter(param);

        iActionFreeFormQuery = new Action("FreeFormQuery");
        param = new ParameterString("ContainerID", allowedValues);
        iActionFreeFormQuery.addInputParameter(param);
        param = new ParameterUint("CDSView");
        iActionFreeFormQuery.addInputParameter(param);
        param = new ParameterString("QueryRequest", allowedValues);
        iActionFreeFormQuery.addInputParameter(param);
        param = new ParameterString("QueryResult", allowedValues);
        iActionFreeFormQuery.addOutputParameter(param);
        param = new ParameterUint("UpdateID");
        iActionFreeFormQuery.addOutputParameter(param);

        iActionGetFreeFormQueryCapabilities = new Action("GetFreeFormQueryCapabilities");
        param = new ParameterString("FFQCapabilities", allowedValues);
        iActionGetFreeFormQueryCapabilities.addOutputParameter(param);

        iSystemUpdateIDChanged = new PropertyChangeListener();
        iSystemUpdateID = new PropertyUint("SystemUpdateID",
            new PropertyChangeListener() {
                public void notifyChange() {
                    systemUpdateIDPropertyChanged();
                }
            }
        );
        addProperty(iSystemUpdateID);
        iContainerUpdateIDsChanged = new PropertyChangeListener();
        iContainerUpdateIDs = new PropertyString("ContainerUpdateIDs",
            new PropertyChangeListener() {
                public void notifyChange() {
                    containerUpdateIDsPropertyChanged();
                }
            }
        );
        addProperty(iContainerUpdateIDs);
        iLastChangeChanged = new PropertyChangeListener();
        iLastChange = new PropertyString("LastChange",
            new PropertyChangeListener() {
                public void notifyChange() {
                    lastChangePropertyChanged();
                }
            }
        );
        addProperty(iLastChange);
        iTransferIDsChanged = new PropertyChangeListener();
        iTransferIDs = new PropertyString("TransferIDs",
            new PropertyChangeListener() {
                public void notifyChange() {
                    transferIDsPropertyChanged();
                }
            }
        );
        addProperty(iTransferIDs);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetSearchCapabilities()
    {
        SyncGetSearchCapabilitiesUpnpOrgContentDirectory3 sync = new SyncGetSearchCapabilitiesUpnpOrgContentDirectory3(this);
        beginGetSearchCapabilities(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getSearchCaps();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetSearchCapabilities}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetSearchCapabilities(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetSearchCapabilities, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetSearchCapabilities.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetSearchCapabilities} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetSearchCapabilities} method.
     * @return the result of the previously invoked action.
     */
    public String endGetSearchCapabilities(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String searchCaps = Invocation.getOutputString(aAsyncHandle, index++);
        return searchCaps;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetSortCapabilities()
    {
        SyncGetSortCapabilitiesUpnpOrgContentDirectory3 sync = new SyncGetSortCapabilitiesUpnpOrgContentDirectory3(this);
        beginGetSortCapabilities(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getSortCaps();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetSortCapabilities}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetSortCapabilities(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetSortCapabilities, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetSortCapabilities.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetSortCapabilities} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetSortCapabilities} method.
     * @return the result of the previously invoked action.
     */
    public String endGetSortCapabilities(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String sortCaps = Invocation.getOutputString(aAsyncHandle, index++);
        return sortCaps;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetSortExtensionCapabilities()
    {
        SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3 sync = new SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory3(this);
        beginGetSortExtensionCapabilities(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getSortExtensionCaps();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetSortExtensionCapabilities}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetSortExtensionCapabilities(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetSortExtensionCapabilities, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetSortExtensionCapabilities.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetSortExtensionCapabilities} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetSortExtensionCapabilities} method.
     * @return the result of the previously invoked action.
     */
    public String endGetSortExtensionCapabilities(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String sortExtensionCaps = Invocation.getOutputString(aAsyncHandle, index++);
        return sortExtensionCaps;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetFeatureList()
    {
        SyncGetFeatureListUpnpOrgContentDirectory3 sync = new SyncGetFeatureListUpnpOrgContentDirectory3(this);
        beginGetFeatureList(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getFeatureList();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetFeatureList}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetFeatureList(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetFeatureList, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetFeatureList.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetFeatureList} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetFeatureList} method.
     * @return the result of the previously invoked action.
     */
    public String endGetFeatureList(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String featureList = Invocation.getOutputString(aAsyncHandle, index++);
        return featureList;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetSystemUpdateID()
    {
        SyncGetSystemUpdateIDUpnpOrgContentDirectory3 sync = new SyncGetSystemUpdateIDUpnpOrgContentDirectory3(this);
        beginGetSystemUpdateID(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getId();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetSystemUpdateID}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetSystemUpdateID(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetSystemUpdateID, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetSystemUpdateID.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetSystemUpdateID} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetSystemUpdateID} method.
     * @return the result of the previously invoked action.
     */
    public long endGetSystemUpdateID(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long id = Invocation.getOutputUint(aAsyncHandle, index++);
        return id;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetServiceResetToken()
    {
        SyncGetServiceResetTokenUpnpOrgContentDirectory3 sync = new SyncGetServiceResetTokenUpnpOrgContentDirectory3(this);
        beginGetServiceResetToken(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getResetToken();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetServiceResetToken}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetServiceResetToken(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetServiceResetToken, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetServiceResetToken.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetServiceResetToken} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetServiceResetToken} method.
     * @return the result of the previously invoked action.
     */
    public String endGetServiceResetToken(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String resetToken = Invocation.getOutputString(aAsyncHandle, index++);
        return resetToken;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Browse syncBrowse(String aObjectID, String aBrowseFlag, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria)
    {
        SyncBrowseUpnpOrgContentDirectory3 sync = new SyncBrowseUpnpOrgContentDirectory3(this);
        beginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Browse(
            sync.getResult(),
            sync.getNumberReturned(),
            sync.getTotalMatches(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endBrowse}.
     * 
     * @param aObjectID
     * @param aBrowseFlag
     * @param aFilter
     * @param aStartingIndex
     * @param aRequestedCount
     * @param aSortCriteria
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginBrowse(String aObjectID, String aBrowseFlag, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionBrowse, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowse.getInputParameter(inIndex++), aObjectID));
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowse.getInputParameter(inIndex++), aBrowseFlag));
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowse.getInputParameter(inIndex++), aFilter));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionBrowse.getInputParameter(inIndex++), aStartingIndex));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionBrowse.getInputParameter(inIndex++), aRequestedCount));
        invocation.addInput(new ArgumentString((ParameterString)iActionBrowse.getInputParameter(inIndex++), aSortCriteria));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionBrowse.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowse.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowse.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowse.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginBrowse} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginBrowse} method.
     * @return the result of the previously invoked action.
     */
    public Browse endBrowse(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        long numberReturned = Invocation.getOutputUint(aAsyncHandle, index++);
        long totalMatches = Invocation.getOutputUint(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new Browse(
            result,
            numberReturned,
            totalMatches,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Search syncSearch(String aContainerID, String aSearchCriteria, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria)
    {
        SyncSearchUpnpOrgContentDirectory3 sync = new SyncSearchUpnpOrgContentDirectory3(this);
        beginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Search(
            sync.getResult(),
            sync.getNumberReturned(),
            sync.getTotalMatches(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSearch}.
     * 
     * @param aContainerID
     * @param aSearchCriteria
     * @param aFilter
     * @param aStartingIndex
     * @param aRequestedCount
     * @param aSortCriteria
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSearch(String aContainerID, String aSearchCriteria, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSearch, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionSearch.getInputParameter(inIndex++), aContainerID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSearch.getInputParameter(inIndex++), aSearchCriteria));
        invocation.addInput(new ArgumentString((ParameterString)iActionSearch.getInputParameter(inIndex++), aFilter));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSearch.getInputParameter(inIndex++), aStartingIndex));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSearch.getInputParameter(inIndex++), aRequestedCount));
        invocation.addInput(new ArgumentString((ParameterString)iActionSearch.getInputParameter(inIndex++), aSortCriteria));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionSearch.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionSearch.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionSearch.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionSearch.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSearch} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSearch} method.
     * @return the result of the previously invoked action.
     */
    public Search endSearch(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        long numberReturned = Invocation.getOutputUint(aAsyncHandle, index++);
        long totalMatches = Invocation.getOutputUint(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new Search(
            result,
            numberReturned,
            totalMatches,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public CreateObject syncCreateObject(String aContainerID, String aElements)
    {
        SyncCreateObjectUpnpOrgContentDirectory3 sync = new SyncCreateObjectUpnpOrgContentDirectory3(this);
        beginCreateObject(aContainerID, aElements, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new CreateObject(
            sync.getObjectID(),
            sync.getResult()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endCreateObject}.
     * 
     * @param aContainerID
     * @param aElements
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginCreateObject(String aContainerID, String aElements, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionCreateObject, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionCreateObject.getInputParameter(inIndex++), aContainerID));
        invocation.addInput(new ArgumentString((ParameterString)iActionCreateObject.getInputParameter(inIndex++), aElements));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionCreateObject.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionCreateObject.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginCreateObject} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginCreateObject} method.
     * @return the result of the previously invoked action.
     */
    public CreateObject endCreateObject(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String objectID = Invocation.getOutputString(aAsyncHandle, index++);
        String result = Invocation.getOutputString(aAsyncHandle, index++);
        return new CreateObject(
            objectID,
            result
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncDestroyObject(String aObjectID)
    {
        SyncDestroyObjectUpnpOrgContentDirectory3 sync = new SyncDestroyObjectUpnpOrgContentDirectory3(this);
        beginDestroyObject(aObjectID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDestroyObject}.
     * 
     * @param aObjectID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDestroyObject(String aObjectID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDestroyObject, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionDestroyObject.getInputParameter(inIndex++), aObjectID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDestroyObject} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDestroyObject} method.
     */
    public void endDestroyObject(long aAsyncHandle)
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
    public void syncUpdateObject(String aObjectID, String aCurrentTagValue, String aNewTagValue)
    {
        SyncUpdateObjectUpnpOrgContentDirectory3 sync = new SyncUpdateObjectUpnpOrgContentDirectory3(this);
        beginUpdateObject(aObjectID, aCurrentTagValue, aNewTagValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endUpdateObject}.
     * 
     * @param aObjectID
     * @param aCurrentTagValue
     * @param aNewTagValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginUpdateObject(String aObjectID, String aCurrentTagValue, String aNewTagValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionUpdateObject, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionUpdateObject.getInputParameter(inIndex++), aObjectID));
        invocation.addInput(new ArgumentString((ParameterString)iActionUpdateObject.getInputParameter(inIndex++), aCurrentTagValue));
        invocation.addInput(new ArgumentString((ParameterString)iActionUpdateObject.getInputParameter(inIndex++), aNewTagValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginUpdateObject} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginUpdateObject} method.
     */
    public void endUpdateObject(long aAsyncHandle)
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
    public String syncMoveObject(String aObjectID, String aNewParentID)
    {
        SyncMoveObjectUpnpOrgContentDirectory3 sync = new SyncMoveObjectUpnpOrgContentDirectory3(this);
        beginMoveObject(aObjectID, aNewParentID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getNewObjectID();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endMoveObject}.
     * 
     * @param aObjectID
     * @param aNewParentID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginMoveObject(String aObjectID, String aNewParentID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionMoveObject, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionMoveObject.getInputParameter(inIndex++), aObjectID));
        invocation.addInput(new ArgumentString((ParameterString)iActionMoveObject.getInputParameter(inIndex++), aNewParentID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionMoveObject.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginMoveObject} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginMoveObject} method.
     * @return the result of the previously invoked action.
     */
    public String endMoveObject(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String newObjectID = Invocation.getOutputString(aAsyncHandle, index++);
        return newObjectID;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncImportResource(String aSourceURI, String aDestinationURI)
    {
        SyncImportResourceUpnpOrgContentDirectory3 sync = new SyncImportResourceUpnpOrgContentDirectory3(this);
        beginImportResource(aSourceURI, aDestinationURI, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getTransferID();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endImportResource}.
     * 
     * @param aSourceURI
     * @param aDestinationURI
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginImportResource(String aSourceURI, String aDestinationURI, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionImportResource, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionImportResource.getInputParameter(inIndex++), aSourceURI));
        invocation.addInput(new ArgumentString((ParameterString)iActionImportResource.getInputParameter(inIndex++), aDestinationURI));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionImportResource.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginImportResource} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginImportResource} method.
     * @return the result of the previously invoked action.
     */
    public long endImportResource(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long transferID = Invocation.getOutputUint(aAsyncHandle, index++);
        return transferID;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncExportResource(String aSourceURI, String aDestinationURI)
    {
        SyncExportResourceUpnpOrgContentDirectory3 sync = new SyncExportResourceUpnpOrgContentDirectory3(this);
        beginExportResource(aSourceURI, aDestinationURI, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getTransferID();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endExportResource}.
     * 
     * @param aSourceURI
     * @param aDestinationURI
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginExportResource(String aSourceURI, String aDestinationURI, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionExportResource, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionExportResource.getInputParameter(inIndex++), aSourceURI));
        invocation.addInput(new ArgumentString((ParameterString)iActionExportResource.getInputParameter(inIndex++), aDestinationURI));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionExportResource.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginExportResource} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginExportResource} method.
     * @return the result of the previously invoked action.
     */
    public long endExportResource(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long transferID = Invocation.getOutputUint(aAsyncHandle, index++);
        return transferID;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncDeleteResource(String aResourceURI)
    {
        SyncDeleteResourceUpnpOrgContentDirectory3 sync = new SyncDeleteResourceUpnpOrgContentDirectory3(this);
        beginDeleteResource(aResourceURI, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDeleteResource}.
     * 
     * @param aResourceURI
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDeleteResource(String aResourceURI, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDeleteResource, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionDeleteResource.getInputParameter(inIndex++), aResourceURI));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDeleteResource} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDeleteResource} method.
     */
    public void endDeleteResource(long aAsyncHandle)
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
    public void syncStopTransferResource(long aTransferID)
    {
        SyncStopTransferResourceUpnpOrgContentDirectory3 sync = new SyncStopTransferResourceUpnpOrgContentDirectory3(this);
        beginStopTransferResource(aTransferID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStopTransferResource}.
     * 
     * @param aTransferID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStopTransferResource(long aTransferID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStopTransferResource, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionStopTransferResource.getInputParameter(inIndex++), aTransferID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStopTransferResource} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStopTransferResource} method.
     */
    public void endStopTransferResource(long aAsyncHandle)
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
    public GetTransferProgress syncGetTransferProgress(long aTransferID)
    {
        SyncGetTransferProgressUpnpOrgContentDirectory3 sync = new SyncGetTransferProgressUpnpOrgContentDirectory3(this);
        beginGetTransferProgress(aTransferID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetTransferProgress(
            sync.getTransferStatus(),
            sync.getTransferLength(),
            sync.getTransferTotal()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetTransferProgress}.
     * 
     * @param aTransferID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetTransferProgress(long aTransferID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetTransferProgress, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetTransferProgress.getInputParameter(inIndex++), aTransferID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetTransferProgress.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetTransferProgress.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetTransferProgress.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetTransferProgress} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetTransferProgress} method.
     * @return the result of the previously invoked action.
     */
    public GetTransferProgress endGetTransferProgress(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String transferStatus = Invocation.getOutputString(aAsyncHandle, index++);
        String transferLength = Invocation.getOutputString(aAsyncHandle, index++);
        String transferTotal = Invocation.getOutputString(aAsyncHandle, index++);
        return new GetTransferProgress(
            transferStatus,
            transferLength,
            transferTotal
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncCreateReference(String aContainerID, String aObjectID)
    {
        SyncCreateReferenceUpnpOrgContentDirectory3 sync = new SyncCreateReferenceUpnpOrgContentDirectory3(this);
        beginCreateReference(aContainerID, aObjectID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getNewID();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endCreateReference}.
     * 
     * @param aContainerID
     * @param aObjectID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginCreateReference(String aContainerID, String aObjectID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionCreateReference, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionCreateReference.getInputParameter(inIndex++), aContainerID));
        invocation.addInput(new ArgumentString((ParameterString)iActionCreateReference.getInputParameter(inIndex++), aObjectID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionCreateReference.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginCreateReference} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginCreateReference} method.
     * @return the result of the previously invoked action.
     */
    public String endCreateReference(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String newID = Invocation.getOutputString(aAsyncHandle, index++);
        return newID;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public FreeFormQuery syncFreeFormQuery(String aContainerID, long aCDSView, String aQueryRequest)
    {
        SyncFreeFormQueryUpnpOrgContentDirectory3 sync = new SyncFreeFormQueryUpnpOrgContentDirectory3(this);
        beginFreeFormQuery(aContainerID, aCDSView, aQueryRequest, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new FreeFormQuery(
            sync.getQueryResult(),
            sync.getUpdateID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endFreeFormQuery}.
     * 
     * @param aContainerID
     * @param aCDSView
     * @param aQueryRequest
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginFreeFormQuery(String aContainerID, long aCDSView, String aQueryRequest, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionFreeFormQuery, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionFreeFormQuery.getInputParameter(inIndex++), aContainerID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionFreeFormQuery.getInputParameter(inIndex++), aCDSView));
        invocation.addInput(new ArgumentString((ParameterString)iActionFreeFormQuery.getInputParameter(inIndex++), aQueryRequest));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionFreeFormQuery.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionFreeFormQuery.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginFreeFormQuery} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginFreeFormQuery} method.
     * @return the result of the previously invoked action.
     */
    public FreeFormQuery endFreeFormQuery(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String queryResult = Invocation.getOutputString(aAsyncHandle, index++);
        long updateID = Invocation.getOutputUint(aAsyncHandle, index++);
        return new FreeFormQuery(
            queryResult,
            updateID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetFreeFormQueryCapabilities()
    {
        SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3 sync = new SyncGetFreeFormQueryCapabilitiesUpnpOrgContentDirectory3(this);
        beginGetFreeFormQueryCapabilities(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getFFQCapabilities();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetFreeFormQueryCapabilities}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetFreeFormQueryCapabilities(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetFreeFormQueryCapabilities, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetFreeFormQueryCapabilities.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetFreeFormQueryCapabilities} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetFreeFormQueryCapabilities} method.
     * @return the result of the previously invoked action.
     */
    public String endGetFreeFormQueryCapabilities(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String fFQCapabilities = Invocation.getOutputString(aAsyncHandle, index++);
        return fFQCapabilities;
    }
        
    /**
     * Set a delegate to be run when the SystemUpdateID state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3 instance will not overlap.
     *
     * @param aSystemUpdateIDChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySystemUpdateIDChanged(IPropertyChangeListener aSystemUpdateIDChanged)
    {
        synchronized (iPropertyLock)
        {
            iSystemUpdateIDChanged = aSystemUpdateIDChanged;
        }
    }

    private void systemUpdateIDPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSystemUpdateIDChanged);
        }
    }
    /**
     * Set a delegate to be run when the ContainerUpdateIDs state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3 instance will not overlap.
     *
     * @param aContainerUpdateIDsChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyContainerUpdateIDsChanged(IPropertyChangeListener aContainerUpdateIDsChanged)
    {
        synchronized (iPropertyLock)
        {
            iContainerUpdateIDsChanged = aContainerUpdateIDsChanged;
        }
    }

    private void containerUpdateIDsPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iContainerUpdateIDsChanged);
        }
    }
    /**
     * Set a delegate to be run when the LastChange state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3 instance will not overlap.
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
     * Set a delegate to be run when the TransferIDs state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgContentDirectory3 instance will not overlap.
     *
     * @param aTransferIDsChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyTransferIDsChanged(IPropertyChangeListener aTransferIDsChanged)
    {
        synchronized (iPropertyLock)
        {
            iTransferIDsChanged = aTransferIDsChanged;
        }
    }

    private void transferIDsPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iTransferIDsChanged);
        }
    }

    /**
     * Query the value of the SystemUpdateID property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the SystemUpdateID property.
     */
    public long getPropertySystemUpdateID()
    {
        propertyReadLock();
        long val = iSystemUpdateID.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ContainerUpdateIDs property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ContainerUpdateIDs property.
     */
    public String getPropertyContainerUpdateIDs()
    {
        propertyReadLock();
        String val = iContainerUpdateIDs.getValue();
        propertyReadUnlock();
        return val;
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
     * Query the value of the TransferIDs property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the TransferIDs property.
     */
    public String getPropertyTransferIDs()
    {
        propertyReadLock();
        String val = iTransferIDs.getValue();
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
            iActionGetSearchCapabilities.destroy();
            iActionGetSortCapabilities.destroy();
            iActionGetSortExtensionCapabilities.destroy();
            iActionGetFeatureList.destroy();
            iActionGetSystemUpdateID.destroy();
            iActionGetServiceResetToken.destroy();
            iActionBrowse.destroy();
            iActionSearch.destroy();
            iActionCreateObject.destroy();
            iActionDestroyObject.destroy();
            iActionUpdateObject.destroy();
            iActionMoveObject.destroy();
            iActionImportResource.destroy();
            iActionExportResource.destroy();
            iActionDeleteResource.destroy();
            iActionStopTransferResource.destroy();
            iActionGetTransferProgress.destroy();
            iActionCreateReference.destroy();
            iActionFreeFormQuery.destroy();
            iActionGetFreeFormQueryCapabilities.destroy();
            iSystemUpdateID.destroy();
            iContainerUpdateIDs.destroy();
            iLastChange.destroy();
            iTransferIDs.destroy();
        }
    }
}

