package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderUpnpOrgContentDirectory1
{

    /**
     * Set the value of the TransferIDs property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyTransferIDs(String aValue);

    /**
     * Get a copy of the value of the TransferIDs property
     *
     * @return value of the TransferIDs property.
     */
    public String getPropertyTransferIDs();

    /**
     * Set the value of the SystemUpdateID property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertySystemUpdateID(long aValue);

    /**
     * Get a copy of the value of the SystemUpdateID property
     *
     * @return value of the SystemUpdateID property.
     */
    public long getPropertySystemUpdateID();

    /**
     * Set the value of the ContainerUpdateIDs property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyContainerUpdateIDs(String aValue);

    /**
     * Get a copy of the value of the ContainerUpdateIDs property
     *
     * @return value of the ContainerUpdateIDs property.
     */
    public String getPropertyContainerUpdateIDs();
        
}

/**
 * Provider for the upnp.org:ContentDirectory:1 UPnP service.
 */
public class DvProviderUpnpOrgContentDirectory1 extends DvProvider implements IDvProviderUpnpOrgContentDirectory1
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

    private IDvInvocationListener iDelegateGetSearchCapabilities;
    private IDvInvocationListener iDelegateGetSortCapabilities;
    private IDvInvocationListener iDelegateGetSystemUpdateID;
    private IDvInvocationListener iDelegateBrowse;
    private IDvInvocationListener iDelegateSearch;
    private IDvInvocationListener iDelegateCreateObject;
    private IDvInvocationListener iDelegateDestroyObject;
    private IDvInvocationListener iDelegateUpdateObject;
    private IDvInvocationListener iDelegateImportResource;
    private IDvInvocationListener iDelegateExportResource;
    private IDvInvocationListener iDelegateStopTransferResource;
    private IDvInvocationListener iDelegateGetTransferProgress;
    private IDvInvocationListener iDelegateDeleteResource;
    private IDvInvocationListener iDelegateCreateReference;
    private PropertyString iPropertyTransferIDs;
    private PropertyUint iPropertySystemUpdateID;
    private PropertyString iPropertyContainerUpdateIDs;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderUpnpOrgContentDirectory1(DvDevice aDevice)
    {
        super(aDevice, "upnp.org", "ContentDirectory", 1);
    }

    /**
     * Enable the TransferIDs property.
     */
    public void enablePropertyTransferIDs()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs", allowedValues));
        addProperty(iPropertyTransferIDs);
    }

    /**
     * Enable the SystemUpdateID property.
     */
    public void enablePropertySystemUpdateID()
    {
        iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"));
        addProperty(iPropertySystemUpdateID);
    }

    /**
     * Enable the ContainerUpdateIDs property.
     */
    public void enablePropertyContainerUpdateIDs()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs", allowedValues));
        addProperty(iPropertyContainerUpdateIDs);
    }

    /**
     * Set the value of the TransferIDs property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyTransferIDs(String aValue)
    {
        return setPropertyString(iPropertyTransferIDs, aValue);
    }

    /**
     * Get a copy of the value of the TransferIDs property
     *
     * @return  value of the TransferIDs property.
     */
    public String getPropertyTransferIDs()
    {
        return iPropertyTransferIDs.getValue();
    }

    /**
     * Set the value of the SystemUpdateID property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertySystemUpdateID(long aValue)
    {
        return setPropertyUint(iPropertySystemUpdateID, aValue);
    }

    /**
     * Get a copy of the value of the SystemUpdateID property
     *
     * @return  value of the SystemUpdateID property.
     */
    public long getPropertySystemUpdateID()
    {
        return iPropertySystemUpdateID.getValue();
    }

    /**
     * Set the value of the ContainerUpdateIDs property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyContainerUpdateIDs(String aValue)
    {
        return setPropertyString(iPropertyContainerUpdateIDs, aValue);
    }

    /**
     * Get a copy of the value of the ContainerUpdateIDs property
     *
     * @return  value of the ContainerUpdateIDs property.
     */
    public String getPropertyContainerUpdateIDs()
    {
        return iPropertyContainerUpdateIDs.getValue();
    }

    /**
     * Signal that the action GetSearchCapabilities is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetSearchCapabilities must be overridden if this is called.
     */      
    protected void enableActionGetSearchCapabilities()
    {
        Action action = new Action("GetSearchCapabilities");        List<String> allowedValues = new LinkedList<String>();
        action.addOutputParameter(new ParameterString("SearchCaps", allowedValues));
        iDelegateGetSearchCapabilities = new DoGetSearchCapabilities();
        enableAction(action, iDelegateGetSearchCapabilities);
    }

    /**
     * Signal that the action GetSortCapabilities is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetSortCapabilities must be overridden if this is called.
     */      
    protected void enableActionGetSortCapabilities()
    {
        Action action = new Action("GetSortCapabilities");        List<String> allowedValues = new LinkedList<String>();
        action.addOutputParameter(new ParameterString("SortCaps", allowedValues));
        iDelegateGetSortCapabilities = new DoGetSortCapabilities();
        enableAction(action, iDelegateGetSortCapabilities);
    }

    /**
     * Signal that the action GetSystemUpdateID is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetSystemUpdateID must be overridden if this is called.
     */      
    protected void enableActionGetSystemUpdateID()
    {
        Action action = new Action("GetSystemUpdateID");
        action.addOutputParameter(new ParameterRelated("Id", iPropertySystemUpdateID));
        iDelegateGetSystemUpdateID = new DoGetSystemUpdateID();
        enableAction(action, iDelegateGetSystemUpdateID);
    }

    /**
     * Signal that the action Browse is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Browse must be overridden if this is called.
     */      
    protected void enableActionBrowse()
    {
        Action action = new Action("Browse");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ObjectID", allowedValues));
        allowedValues.add("BrowseMetadata");
        allowedValues.add("BrowseDirectChildren");
        action.addInputParameter(new ParameterString("BrowseFlag", allowedValues));
        allowedValues.clear();
        action.addInputParameter(new ParameterString("Filter", allowedValues));
        action.addInputParameter(new ParameterUint("StartingIndex"));
        action.addInputParameter(new ParameterUint("RequestedCount"));
        action.addInputParameter(new ParameterString("SortCriteria", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        action.addOutputParameter(new ParameterUint("NumberReturned"));
        action.addOutputParameter(new ParameterUint("TotalMatches"));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateBrowse = new DoBrowse();
        enableAction(action, iDelegateBrowse);
    }

    /**
     * Signal that the action Search is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Search must be overridden if this is called.
     */      
    protected void enableActionSearch()
    {
        Action action = new Action("Search");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ContainerID", allowedValues));
        action.addInputParameter(new ParameterString("SearchCriteria", allowedValues));
        action.addInputParameter(new ParameterString("Filter", allowedValues));
        action.addInputParameter(new ParameterUint("StartingIndex"));
        action.addInputParameter(new ParameterUint("RequestedCount"));
        action.addInputParameter(new ParameterString("SortCriteria", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        action.addOutputParameter(new ParameterUint("NumberReturned"));
        action.addOutputParameter(new ParameterUint("TotalMatches"));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateSearch = new DoSearch();
        enableAction(action, iDelegateSearch);
    }

    /**
     * Signal that the action CreateObject is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * CreateObject must be overridden if this is called.
     */      
    protected void enableActionCreateObject()
    {
        Action action = new Action("CreateObject");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ContainerID", allowedValues));
        action.addInputParameter(new ParameterString("Elements", allowedValues));
        action.addOutputParameter(new ParameterString("ObjectID", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        iDelegateCreateObject = new DoCreateObject();
        enableAction(action, iDelegateCreateObject);
    }

    /**
     * Signal that the action DestroyObject is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * DestroyObject must be overridden if this is called.
     */      
    protected void enableActionDestroyObject()
    {
        Action action = new Action("DestroyObject");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ObjectID", allowedValues));
        iDelegateDestroyObject = new DoDestroyObject();
        enableAction(action, iDelegateDestroyObject);
    }

    /**
     * Signal that the action UpdateObject is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * UpdateObject must be overridden if this is called.
     */      
    protected void enableActionUpdateObject()
    {
        Action action = new Action("UpdateObject");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ObjectID", allowedValues));
        action.addInputParameter(new ParameterString("CurrentTagValue", allowedValues));
        action.addInputParameter(new ParameterString("NewTagValue", allowedValues));
        iDelegateUpdateObject = new DoUpdateObject();
        enableAction(action, iDelegateUpdateObject);
    }

    /**
     * Signal that the action ImportResource is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ImportResource must be overridden if this is called.
     */      
    protected void enableActionImportResource()
    {
        Action action = new Action("ImportResource");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("SourceURI", allowedValues));
        action.addInputParameter(new ParameterString("DestinationURI", allowedValues));
        action.addOutputParameter(new ParameterUint("TransferID"));
        iDelegateImportResource = new DoImportResource();
        enableAction(action, iDelegateImportResource);
    }

    /**
     * Signal that the action ExportResource is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ExportResource must be overridden if this is called.
     */      
    protected void enableActionExportResource()
    {
        Action action = new Action("ExportResource");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("SourceURI", allowedValues));
        action.addInputParameter(new ParameterString("DestinationURI", allowedValues));
        action.addOutputParameter(new ParameterUint("TransferID"));
        iDelegateExportResource = new DoExportResource();
        enableAction(action, iDelegateExportResource);
    }

    /**
     * Signal that the action StopTransferResource is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * StopTransferResource must be overridden if this is called.
     */      
    protected void enableActionStopTransferResource()
    {
        Action action = new Action("StopTransferResource");
        action.addInputParameter(new ParameterUint("TransferID"));
        iDelegateStopTransferResource = new DoStopTransferResource();
        enableAction(action, iDelegateStopTransferResource);
    }

    /**
     * Signal that the action GetTransferProgress is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetTransferProgress must be overridden if this is called.
     */      
    protected void enableActionGetTransferProgress()
    {
        Action action = new Action("GetTransferProgress");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("TransferID"));
        allowedValues.add("COMPLETED");
        allowedValues.add("ERROR");
        allowedValues.add("IN_PROGRESS");
        allowedValues.add("STOPPED");
        action.addOutputParameter(new ParameterString("TransferStatus", allowedValues));
        allowedValues.clear();
        action.addOutputParameter(new ParameterString("TransferLength", allowedValues));
        action.addOutputParameter(new ParameterString("TransferTotal", allowedValues));
        iDelegateGetTransferProgress = new DoGetTransferProgress();
        enableAction(action, iDelegateGetTransferProgress);
    }

    /**
     * Signal that the action DeleteResource is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * DeleteResource must be overridden if this is called.
     */      
    protected void enableActionDeleteResource()
    {
        Action action = new Action("DeleteResource");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ResourceURI", allowedValues));
        iDelegateDeleteResource = new DoDeleteResource();
        enableAction(action, iDelegateDeleteResource);
    }

    /**
     * Signal that the action CreateReference is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * CreateReference must be overridden if this is called.
     */      
    protected void enableActionCreateReference()
    {
        Action action = new Action("CreateReference");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ContainerID", allowedValues));
        action.addInputParameter(new ParameterString("ObjectID", allowedValues));
        action.addOutputParameter(new ParameterString("NewID", allowedValues));
        iDelegateCreateReference = new DoCreateReference();
        enableAction(action, iDelegateCreateReference);
    }

    /**
     * GetSearchCapabilities action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetSearchCapabilities action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetSearchCapabilities} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String getSearchCapabilities(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetSortCapabilities action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetSortCapabilities action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetSortCapabilities} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String getSortCapabilities(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetSystemUpdateID action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetSystemUpdateID action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetSystemUpdateID} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long getSystemUpdateID(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Browse action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Browse action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionBrowse} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aObjectID
     * @param aBrowseFlag
     * @param aFilter
     * @param aStartingIndex
     * @param aRequestedCount
     * @param aSortCriteria
     */
    protected Browse browse(IDvInvocation aInvocation, String aObjectID, String aBrowseFlag, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Search action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Search action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSearch} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aContainerID
     * @param aSearchCriteria
     * @param aFilter
     * @param aStartingIndex
     * @param aRequestedCount
     * @param aSortCriteria
     */
    protected Search search(IDvInvocation aInvocation, String aContainerID, String aSearchCriteria, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria)
    {
        throw (new ActionDisabledError());
    }

    /**
     * CreateObject action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * CreateObject action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionCreateObject} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aContainerID
     * @param aElements
     */
    protected CreateObject createObject(IDvInvocation aInvocation, String aContainerID, String aElements)
    {
        throw (new ActionDisabledError());
    }

    /**
     * DestroyObject action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * DestroyObject action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDestroyObject} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aObjectID
     */
    protected void destroyObject(IDvInvocation aInvocation, String aObjectID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * UpdateObject action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * UpdateObject action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionUpdateObject} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aObjectID
     * @param aCurrentTagValue
     * @param aNewTagValue
     */
    protected void updateObject(IDvInvocation aInvocation, String aObjectID, String aCurrentTagValue, String aNewTagValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * ImportResource action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ImportResource action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionImportResource} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aSourceURI
     * @param aDestinationURI
     */
    protected long importResource(IDvInvocation aInvocation, String aSourceURI, String aDestinationURI)
    {
        throw (new ActionDisabledError());
    }

    /**
     * ExportResource action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ExportResource action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionExportResource} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aSourceURI
     * @param aDestinationURI
     */
    protected long exportResource(IDvInvocation aInvocation, String aSourceURI, String aDestinationURI)
    {
        throw (new ActionDisabledError());
    }

    /**
     * StopTransferResource action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * StopTransferResource action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStopTransferResource} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aTransferID
     */
    protected void stopTransferResource(IDvInvocation aInvocation, long aTransferID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetTransferProgress action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetTransferProgress action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetTransferProgress} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aTransferID
     */
    protected GetTransferProgress getTransferProgress(IDvInvocation aInvocation, long aTransferID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * DeleteResource action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * DeleteResource action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDeleteResource} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aResourceURI
     */
    protected void deleteResource(IDvInvocation aInvocation, String aResourceURI)
    {
        throw (new ActionDisabledError());
    }

    /**
     * CreateReference action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * CreateReference action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionCreateReference} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aContainerID
     * @param aObjectID
     */
    protected String createReference(IDvInvocation aInvocation, String aContainerID, String aObjectID)
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


    private class DoGetSearchCapabilities implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String searchCaps;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 searchCaps = getSearchCapabilities(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetSearchCapabilities");
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
                invocation.writeString("SearchCaps", searchCaps);
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

    private class DoGetSortCapabilities implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String sortCaps;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 sortCaps = getSortCapabilities(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetSortCapabilities");
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
                invocation.writeString("SortCaps", sortCaps);
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

    private class DoGetSystemUpdateID implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 id = getSystemUpdateID(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetSystemUpdateID");
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
                invocation.writeUint("Id", id);
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

    private class DoBrowse implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String objectID;
            String browseFlag;
            String filter;
            long startingIndex;
            long requestedCount;
            String sortCriteria;
            String result;
            long numberReturned;
            long totalMatches;
            long updateID;
            try
            {
                invocation.readStart();
                objectID = invocation.readString("ObjectID");
                browseFlag = invocation.readString("BrowseFlag");
                filter = invocation.readString("Filter");
                startingIndex = invocation.readUint("StartingIndex");
                requestedCount = invocation.readUint("RequestedCount");
                sortCriteria = invocation.readString("SortCriteria");
                invocation.readEnd();

            Browse outArgs = browse(invocation, objectID, browseFlag, filter, startingIndex, requestedCount, sortCriteria);
            result = outArgs.getResult();
            numberReturned = outArgs.getNumberReturned();
            totalMatches = outArgs.getTotalMatches();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Browse");
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
                invocation.writeString("Result", result);
                invocation.writeUint("NumberReturned", numberReturned);
                invocation.writeUint("TotalMatches", totalMatches);
                invocation.writeUint("UpdateID", updateID);
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

    private class DoSearch implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String containerID;
            String searchCriteria;
            String filter;
            long startingIndex;
            long requestedCount;
            String sortCriteria;
            String result;
            long numberReturned;
            long totalMatches;
            long updateID;
            try
            {
                invocation.readStart();
                containerID = invocation.readString("ContainerID");
                searchCriteria = invocation.readString("SearchCriteria");
                filter = invocation.readString("Filter");
                startingIndex = invocation.readUint("StartingIndex");
                requestedCount = invocation.readUint("RequestedCount");
                sortCriteria = invocation.readString("SortCriteria");
                invocation.readEnd();

            Search outArgs = search(invocation, containerID, searchCriteria, filter, startingIndex, requestedCount, sortCriteria);
            result = outArgs.getResult();
            numberReturned = outArgs.getNumberReturned();
            totalMatches = outArgs.getTotalMatches();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Search");
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
                invocation.writeString("Result", result);
                invocation.writeUint("NumberReturned", numberReturned);
                invocation.writeUint("TotalMatches", totalMatches);
                invocation.writeUint("UpdateID", updateID);
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

    private class DoCreateObject implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String containerID;
            String elements;
            String objectID;
            String result;
            try
            {
                invocation.readStart();
                containerID = invocation.readString("ContainerID");
                elements = invocation.readString("Elements");
                invocation.readEnd();

            CreateObject outArgs = createObject(invocation, containerID, elements);
            objectID = outArgs.getObjectID();
            result = outArgs.getResult();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "CreateObject");
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
                invocation.writeString("ObjectID", objectID);
                invocation.writeString("Result", result);
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

    private class DoDestroyObject implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String objectID;
            try
            {
                invocation.readStart();
                objectID = invocation.readString("ObjectID");
                invocation.readEnd();
                destroyObject(invocation, objectID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "DestroyObject");
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

    private class DoUpdateObject implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String objectID;
            String currentTagValue;
            String newTagValue;
            try
            {
                invocation.readStart();
                objectID = invocation.readString("ObjectID");
                currentTagValue = invocation.readString("CurrentTagValue");
                newTagValue = invocation.readString("NewTagValue");
                invocation.readEnd();
                updateObject(invocation, objectID, currentTagValue, newTagValue);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "UpdateObject");
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

    private class DoImportResource implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String sourceURI;
            String destinationURI;
            long transferID;
            try
            {
                invocation.readStart();
                sourceURI = invocation.readString("SourceURI");
                destinationURI = invocation.readString("DestinationURI");
                invocation.readEnd();
                 transferID = importResource(invocation, sourceURI, destinationURI);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ImportResource");
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
                invocation.writeUint("TransferID", transferID);
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

    private class DoExportResource implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String sourceURI;
            String destinationURI;
            long transferID;
            try
            {
                invocation.readStart();
                sourceURI = invocation.readString("SourceURI");
                destinationURI = invocation.readString("DestinationURI");
                invocation.readEnd();
                 transferID = exportResource(invocation, sourceURI, destinationURI);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ExportResource");
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
                invocation.writeUint("TransferID", transferID);
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

    private class DoStopTransferResource implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long transferID;
            try
            {
                invocation.readStart();
                transferID = invocation.readUint("TransferID");
                invocation.readEnd();
                stopTransferResource(invocation, transferID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "StopTransferResource");
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

    private class DoGetTransferProgress implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long transferID;
            String transferStatus;
            String transferLength;
            String transferTotal;
            try
            {
                invocation.readStart();
                transferID = invocation.readUint("TransferID");
                invocation.readEnd();

            GetTransferProgress outArgs = getTransferProgress(invocation, transferID);
            transferStatus = outArgs.getTransferStatus();
            transferLength = outArgs.getTransferLength();
            transferTotal = outArgs.getTransferTotal();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetTransferProgress");
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
                invocation.writeString("TransferStatus", transferStatus);
                invocation.writeString("TransferLength", transferLength);
                invocation.writeString("TransferTotal", transferTotal);
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

    private class DoDeleteResource implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String resourceURI;
            try
            {
                invocation.readStart();
                resourceURI = invocation.readString("ResourceURI");
                invocation.readEnd();
                deleteResource(invocation, resourceURI);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "DeleteResource");
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

    private class DoCreateReference implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String containerID;
            String objectID;
            String newID;
            try
            {
                invocation.readStart();
                containerID = invocation.readString("ContainerID");
                objectID = invocation.readString("ObjectID");
                invocation.readEnd();
                 newID = createReference(invocation, containerID, objectID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "CreateReference");
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
                invocation.writeString("NewID", newID);
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

