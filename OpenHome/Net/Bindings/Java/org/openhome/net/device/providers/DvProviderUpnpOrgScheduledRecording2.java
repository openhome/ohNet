package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderUpnpOrgScheduledRecording2
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
 * Provider for the upnp.org:ScheduledRecording:2 UPnP service.
 */
public class DvProviderUpnpOrgScheduledRecording2 extends DvProvider implements IDvProviderUpnpOrgScheduledRecording2
{

    public class GetSortCapabilities
    {
        private String iSortCaps;
        private long iSortLevelCap;

        public GetSortCapabilities(
            String aSortCaps,
            long aSortLevelCap
        )
        {
            iSortCaps = aSortCaps;
            iSortLevelCap = aSortLevelCap;
        }
        public String getSortCaps()
        {
            return iSortCaps;
        }
        public long getSortLevelCap()
        {
            return iSortLevelCap;
        }
    }

    public class BrowseRecordSchedules
    {
        private String iResult;
        private long iNumberReturned;
        private long iTotalMatches;
        private long iUpdateID;

        public BrowseRecordSchedules(
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

    public class BrowseRecordTasks
    {
        private String iResult;
        private long iNumberReturned;
        private long iTotalMatches;
        private long iUpdateID;

        public BrowseRecordTasks(
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

    public class CreateRecordSchedule
    {
        private String iRecordScheduleID;
        private String iResult;
        private long iUpdateID;

        public CreateRecordSchedule(
            String aRecordScheduleID,
            String aResult,
            long aUpdateID
        )
        {
            iRecordScheduleID = aRecordScheduleID;
            iResult = aResult;
            iUpdateID = aUpdateID;
        }
        public String getRecordScheduleID()
        {
            return iRecordScheduleID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class GetRecordSchedule
    {
        private String iResult;
        private long iUpdateID;

        public GetRecordSchedule(
            String aResult,
            long aUpdateID
        )
        {
            iResult = aResult;
            iUpdateID = aUpdateID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class GetRecordTask
    {
        private String iResult;
        private long iUpdateID;

        public GetRecordTask(
            String aResult,
            long aUpdateID
        )
        {
            iResult = aResult;
            iUpdateID = aUpdateID;
        }
        public String getResult()
        {
            return iResult;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class GetRecordScheduleConflicts
    {
        private String iRecordScheduleConflictIDList;
        private long iUpdateID;

        public GetRecordScheduleConflicts(
            String aRecordScheduleConflictIDList,
            long aUpdateID
        )
        {
            iRecordScheduleConflictIDList = aRecordScheduleConflictIDList;
            iUpdateID = aUpdateID;
        }
        public String getRecordScheduleConflictIDList()
        {
            return iRecordScheduleConflictIDList;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    public class GetRecordTaskConflicts
    {
        private String iRecordTaskConflictIDList;
        private long iUpdateID;

        public GetRecordTaskConflicts(
            String aRecordTaskConflictIDList,
            long aUpdateID
        )
        {
            iRecordTaskConflictIDList = aRecordTaskConflictIDList;
            iUpdateID = aUpdateID;
        }
        public String getRecordTaskConflictIDList()
        {
            return iRecordTaskConflictIDList;
        }
        public long getUpdateID()
        {
            return iUpdateID;
        }
    }

    private IDvInvocationListener iDelegateGetSortCapabilities;
    private IDvInvocationListener iDelegateGetPropertyList;
    private IDvInvocationListener iDelegateGetAllowedValues;
    private IDvInvocationListener iDelegateGetStateUpdateID;
    private IDvInvocationListener iDelegateBrowseRecordSchedules;
    private IDvInvocationListener iDelegateBrowseRecordTasks;
    private IDvInvocationListener iDelegateCreateRecordSchedule;
    private IDvInvocationListener iDelegateDeleteRecordSchedule;
    private IDvInvocationListener iDelegateGetRecordSchedule;
    private IDvInvocationListener iDelegateEnableRecordSchedule;
    private IDvInvocationListener iDelegateDisableRecordSchedule;
    private IDvInvocationListener iDelegateDeleteRecordTask;
    private IDvInvocationListener iDelegateGetRecordTask;
    private IDvInvocationListener iDelegateEnableRecordTask;
    private IDvInvocationListener iDelegateDisableRecordTask;
    private IDvInvocationListener iDelegateResetRecordTask;
    private IDvInvocationListener iDelegateGetRecordScheduleConflicts;
    private IDvInvocationListener iDelegateGetRecordTaskConflicts;
    private PropertyString iPropertyLastChange;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderUpnpOrgScheduledRecording2(DvDevice aDevice)
    {
        super(aDevice, "upnp.org", "ScheduledRecording", 2);
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
     * Signal that the action GetSortCapabilities is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetSortCapabilities must be overridden if this is called.
     */      
    protected void enableActionGetSortCapabilities()
    {
        Action action = new Action("GetSortCapabilities");        List<String> allowedValues = new LinkedList<String>();
        action.addOutputParameter(new ParameterString("SortCaps", allowedValues));
        action.addOutputParameter(new ParameterUint("SortLevelCap"));
        iDelegateGetSortCapabilities = new DoGetSortCapabilities();
        enableAction(action, iDelegateGetSortCapabilities);
    }

    /**
     * Signal that the action GetPropertyList is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetPropertyList must be overridden if this is called.
     */      
    protected void enableActionGetPropertyList()
    {
        Action action = new Action("GetPropertyList");        List<String> allowedValues = new LinkedList<String>();
        allowedValues.add("A_ARG_TYPE_RecordSchedule");
        allowedValues.add("A_ARG_TYPE_RecordTask");
        allowedValues.add("A_ARG_TYPE_RecordScheduleParts");
        action.addInputParameter(new ParameterString("DataTypeID", allowedValues));
        allowedValues.clear();
        action.addOutputParameter(new ParameterString("PropertyList", allowedValues));
        iDelegateGetPropertyList = new DoGetPropertyList();
        enableAction(action, iDelegateGetPropertyList);
    }

    /**
     * Signal that the action GetAllowedValues is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetAllowedValues must be overridden if this is called.
     */      
    protected void enableActionGetAllowedValues()
    {
        Action action = new Action("GetAllowedValues");        List<String> allowedValues = new LinkedList<String>();
        allowedValues.add("A_ARG_TYPE_RecordSchedule");
        allowedValues.add("A_ARG_TYPE_RecordTask");
        allowedValues.add("A_ARG_TYPE_RecordScheduleParts");
        action.addInputParameter(new ParameterString("DataTypeID", allowedValues));
        allowedValues.clear();
        action.addInputParameter(new ParameterString("Filter", allowedValues));
        action.addOutputParameter(new ParameterString("PropertyInfo", allowedValues));
        iDelegateGetAllowedValues = new DoGetAllowedValues();
        enableAction(action, iDelegateGetAllowedValues);
    }

    /**
     * Signal that the action GetStateUpdateID is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetStateUpdateID must be overridden if this is called.
     */      
    protected void enableActionGetStateUpdateID()
    {
        Action action = new Action("GetStateUpdateID");
        action.addOutputParameter(new ParameterUint("Id"));
        iDelegateGetStateUpdateID = new DoGetStateUpdateID();
        enableAction(action, iDelegateGetStateUpdateID);
    }

    /**
     * Signal that the action BrowseRecordSchedules is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * BrowseRecordSchedules must be overridden if this is called.
     */      
    protected void enableActionBrowseRecordSchedules()
    {
        Action action = new Action("BrowseRecordSchedules");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("Filter", allowedValues));
        action.addInputParameter(new ParameterUint("StartingIndex"));
        action.addInputParameter(new ParameterUint("RequestedCount"));
        action.addInputParameter(new ParameterString("SortCriteria", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        action.addOutputParameter(new ParameterUint("NumberReturned"));
        action.addOutputParameter(new ParameterUint("TotalMatches"));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateBrowseRecordSchedules = new DoBrowseRecordSchedules();
        enableAction(action, iDelegateBrowseRecordSchedules);
    }

    /**
     * Signal that the action BrowseRecordTasks is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * BrowseRecordTasks must be overridden if this is called.
     */      
    protected void enableActionBrowseRecordTasks()
    {
        Action action = new Action("BrowseRecordTasks");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordScheduleID", allowedValues));
        action.addInputParameter(new ParameterString("Filter", allowedValues));
        action.addInputParameter(new ParameterUint("StartingIndex"));
        action.addInputParameter(new ParameterUint("RequestedCount"));
        action.addInputParameter(new ParameterString("SortCriteria", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        action.addOutputParameter(new ParameterUint("NumberReturned"));
        action.addOutputParameter(new ParameterUint("TotalMatches"));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateBrowseRecordTasks = new DoBrowseRecordTasks();
        enableAction(action, iDelegateBrowseRecordTasks);
    }

    /**
     * Signal that the action CreateRecordSchedule is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * CreateRecordSchedule must be overridden if this is called.
     */      
    protected void enableActionCreateRecordSchedule()
    {
        Action action = new Action("CreateRecordSchedule");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("Elements", allowedValues));
        action.addOutputParameter(new ParameterString("RecordScheduleID", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateCreateRecordSchedule = new DoCreateRecordSchedule();
        enableAction(action, iDelegateCreateRecordSchedule);
    }

    /**
     * Signal that the action DeleteRecordSchedule is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * DeleteRecordSchedule must be overridden if this is called.
     */      
    protected void enableActionDeleteRecordSchedule()
    {
        Action action = new Action("DeleteRecordSchedule");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordScheduleID", allowedValues));
        iDelegateDeleteRecordSchedule = new DoDeleteRecordSchedule();
        enableAction(action, iDelegateDeleteRecordSchedule);
    }

    /**
     * Signal that the action GetRecordSchedule is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRecordSchedule must be overridden if this is called.
     */      
    protected void enableActionGetRecordSchedule()
    {
        Action action = new Action("GetRecordSchedule");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordScheduleID", allowedValues));
        action.addInputParameter(new ParameterString("Filter", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateGetRecordSchedule = new DoGetRecordSchedule();
        enableAction(action, iDelegateGetRecordSchedule);
    }

    /**
     * Signal that the action EnableRecordSchedule is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * EnableRecordSchedule must be overridden if this is called.
     */      
    protected void enableActionEnableRecordSchedule()
    {
        Action action = new Action("EnableRecordSchedule");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordScheduleID", allowedValues));
        iDelegateEnableRecordSchedule = new DoEnableRecordSchedule();
        enableAction(action, iDelegateEnableRecordSchedule);
    }

    /**
     * Signal that the action DisableRecordSchedule is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * DisableRecordSchedule must be overridden if this is called.
     */      
    protected void enableActionDisableRecordSchedule()
    {
        Action action = new Action("DisableRecordSchedule");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordScheduleID", allowedValues));
        iDelegateDisableRecordSchedule = new DoDisableRecordSchedule();
        enableAction(action, iDelegateDisableRecordSchedule);
    }

    /**
     * Signal that the action DeleteRecordTask is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * DeleteRecordTask must be overridden if this is called.
     */      
    protected void enableActionDeleteRecordTask()
    {
        Action action = new Action("DeleteRecordTask");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordTaskID", allowedValues));
        iDelegateDeleteRecordTask = new DoDeleteRecordTask();
        enableAction(action, iDelegateDeleteRecordTask);
    }

    /**
     * Signal that the action GetRecordTask is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRecordTask must be overridden if this is called.
     */      
    protected void enableActionGetRecordTask()
    {
        Action action = new Action("GetRecordTask");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordTaskID", allowedValues));
        action.addInputParameter(new ParameterString("Filter", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateGetRecordTask = new DoGetRecordTask();
        enableAction(action, iDelegateGetRecordTask);
    }

    /**
     * Signal that the action EnableRecordTask is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * EnableRecordTask must be overridden if this is called.
     */      
    protected void enableActionEnableRecordTask()
    {
        Action action = new Action("EnableRecordTask");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordTaskID", allowedValues));
        iDelegateEnableRecordTask = new DoEnableRecordTask();
        enableAction(action, iDelegateEnableRecordTask);
    }

    /**
     * Signal that the action DisableRecordTask is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * DisableRecordTask must be overridden if this is called.
     */      
    protected void enableActionDisableRecordTask()
    {
        Action action = new Action("DisableRecordTask");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordTaskID", allowedValues));
        iDelegateDisableRecordTask = new DoDisableRecordTask();
        enableAction(action, iDelegateDisableRecordTask);
    }

    /**
     * Signal that the action ResetRecordTask is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ResetRecordTask must be overridden if this is called.
     */      
    protected void enableActionResetRecordTask()
    {
        Action action = new Action("ResetRecordTask");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordTaskID", allowedValues));
        iDelegateResetRecordTask = new DoResetRecordTask();
        enableAction(action, iDelegateResetRecordTask);
    }

    /**
     * Signal that the action GetRecordScheduleConflicts is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRecordScheduleConflicts must be overridden if this is called.
     */      
    protected void enableActionGetRecordScheduleConflicts()
    {
        Action action = new Action("GetRecordScheduleConflicts");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordScheduleID", allowedValues));
        action.addOutputParameter(new ParameterString("RecordScheduleConflictIDList", allowedValues));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateGetRecordScheduleConflicts = new DoGetRecordScheduleConflicts();
        enableAction(action, iDelegateGetRecordScheduleConflicts);
    }

    /**
     * Signal that the action GetRecordTaskConflicts is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRecordTaskConflicts must be overridden if this is called.
     */      
    protected void enableActionGetRecordTaskConflicts()
    {
        Action action = new Action("GetRecordTaskConflicts");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RecordTaskID", allowedValues));
        action.addOutputParameter(new ParameterString("RecordTaskConflictIDList", allowedValues));
        action.addOutputParameter(new ParameterUint("UpdateID"));
        iDelegateGetRecordTaskConflicts = new DoGetRecordTaskConflicts();
        enableAction(action, iDelegateGetRecordTaskConflicts);
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
    protected GetSortCapabilities getSortCapabilities(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetPropertyList action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetPropertyList action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetPropertyList} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aDataTypeID
     */
    protected String getPropertyList(IDvInvocation aInvocation, String aDataTypeID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetAllowedValues action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetAllowedValues action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetAllowedValues} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aDataTypeID
     * @param aFilter
     */
    protected String getAllowedValues(IDvInvocation aInvocation, String aDataTypeID, String aFilter)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetStateUpdateID action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetStateUpdateID action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetStateUpdateID} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long getStateUpdateID(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * BrowseRecordSchedules action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * BrowseRecordSchedules action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionBrowseRecordSchedules} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aFilter
     * @param aStartingIndex
     * @param aRequestedCount
     * @param aSortCriteria
     */
    protected BrowseRecordSchedules browseRecordSchedules(IDvInvocation aInvocation, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria)
    {
        throw (new ActionDisabledError());
    }

    /**
     * BrowseRecordTasks action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * BrowseRecordTasks action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionBrowseRecordTasks} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordScheduleID
     * @param aFilter
     * @param aStartingIndex
     * @param aRequestedCount
     * @param aSortCriteria
     */
    protected BrowseRecordTasks browseRecordTasks(IDvInvocation aInvocation, String aRecordScheduleID, String aFilter, long aStartingIndex, long aRequestedCount, String aSortCriteria)
    {
        throw (new ActionDisabledError());
    }

    /**
     * CreateRecordSchedule action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * CreateRecordSchedule action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionCreateRecordSchedule} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aElements
     */
    protected CreateRecordSchedule createRecordSchedule(IDvInvocation aInvocation, String aElements)
    {
        throw (new ActionDisabledError());
    }

    /**
     * DeleteRecordSchedule action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * DeleteRecordSchedule action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDeleteRecordSchedule} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordScheduleID
     */
    protected void deleteRecordSchedule(IDvInvocation aInvocation, String aRecordScheduleID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRecordSchedule action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRecordSchedule action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRecordSchedule} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordScheduleID
     * @param aFilter
     */
    protected GetRecordSchedule getRecordSchedule(IDvInvocation aInvocation, String aRecordScheduleID, String aFilter)
    {
        throw (new ActionDisabledError());
    }

    /**
     * EnableRecordSchedule action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * EnableRecordSchedule action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionEnableRecordSchedule} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordScheduleID
     */
    protected void enableRecordSchedule(IDvInvocation aInvocation, String aRecordScheduleID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * DisableRecordSchedule action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * DisableRecordSchedule action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDisableRecordSchedule} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordScheduleID
     */
    protected void disableRecordSchedule(IDvInvocation aInvocation, String aRecordScheduleID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * DeleteRecordTask action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * DeleteRecordTask action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDeleteRecordTask} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordTaskID
     */
    protected void deleteRecordTask(IDvInvocation aInvocation, String aRecordTaskID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRecordTask action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRecordTask action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRecordTask} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordTaskID
     * @param aFilter
     */
    protected GetRecordTask getRecordTask(IDvInvocation aInvocation, String aRecordTaskID, String aFilter)
    {
        throw (new ActionDisabledError());
    }

    /**
     * EnableRecordTask action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * EnableRecordTask action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionEnableRecordTask} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordTaskID
     */
    protected void enableRecordTask(IDvInvocation aInvocation, String aRecordTaskID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * DisableRecordTask action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * DisableRecordTask action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDisableRecordTask} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordTaskID
     */
    protected void disableRecordTask(IDvInvocation aInvocation, String aRecordTaskID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * ResetRecordTask action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ResetRecordTask action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionResetRecordTask} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordTaskID
     */
    protected void resetRecordTask(IDvInvocation aInvocation, String aRecordTaskID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRecordScheduleConflicts action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRecordScheduleConflicts action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRecordScheduleConflicts} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordScheduleID
     */
    protected GetRecordScheduleConflicts getRecordScheduleConflicts(IDvInvocation aInvocation, String aRecordScheduleID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRecordTaskConflicts action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRecordTaskConflicts action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRecordTaskConflicts} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRecordTaskID
     */
    protected GetRecordTaskConflicts getRecordTaskConflicts(IDvInvocation aInvocation, String aRecordTaskID)
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


    private class DoGetSortCapabilities implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String sortCaps;
            long sortLevelCap;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            GetSortCapabilities outArgs = getSortCapabilities(invocation);
            sortCaps = outArgs.getSortCaps();
            sortLevelCap = outArgs.getSortLevelCap();
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
                invocation.writeUint("SortLevelCap", sortLevelCap);
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

    private class DoGetPropertyList implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String dataTypeID;
            String propertyList;
            try
            {
                invocation.readStart();
                dataTypeID = invocation.readString("DataTypeID");
                invocation.readEnd();
                 propertyList = getPropertyList(invocation, dataTypeID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetPropertyList");
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
                invocation.writeString("PropertyList", propertyList);
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

    private class DoGetAllowedValues implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String dataTypeID;
            String filter;
            String propertyInfo;
            try
            {
                invocation.readStart();
                dataTypeID = invocation.readString("DataTypeID");
                filter = invocation.readString("Filter");
                invocation.readEnd();
                 propertyInfo = getAllowedValues(invocation, dataTypeID, filter);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetAllowedValues");
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
                invocation.writeString("PropertyInfo", propertyInfo);
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

    private class DoGetStateUpdateID implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long id;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 id = getStateUpdateID(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetStateUpdateID");
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

    private class DoBrowseRecordSchedules implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
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
                filter = invocation.readString("Filter");
                startingIndex = invocation.readUint("StartingIndex");
                requestedCount = invocation.readUint("RequestedCount");
                sortCriteria = invocation.readString("SortCriteria");
                invocation.readEnd();

            BrowseRecordSchedules outArgs = browseRecordSchedules(invocation, filter, startingIndex, requestedCount, sortCriteria);
            result = outArgs.getResult();
            numberReturned = outArgs.getNumberReturned();
            totalMatches = outArgs.getTotalMatches();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "BrowseRecordSchedules");
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

    private class DoBrowseRecordTasks implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordScheduleID;
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
                recordScheduleID = invocation.readString("RecordScheduleID");
                filter = invocation.readString("Filter");
                startingIndex = invocation.readUint("StartingIndex");
                requestedCount = invocation.readUint("RequestedCount");
                sortCriteria = invocation.readString("SortCriteria");
                invocation.readEnd();

            BrowseRecordTasks outArgs = browseRecordTasks(invocation, recordScheduleID, filter, startingIndex, requestedCount, sortCriteria);
            result = outArgs.getResult();
            numberReturned = outArgs.getNumberReturned();
            totalMatches = outArgs.getTotalMatches();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "BrowseRecordTasks");
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

    private class DoCreateRecordSchedule implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String elements;
            String recordScheduleID;
            String result;
            long updateID;
            try
            {
                invocation.readStart();
                elements = invocation.readString("Elements");
                invocation.readEnd();

            CreateRecordSchedule outArgs = createRecordSchedule(invocation, elements);
            recordScheduleID = outArgs.getRecordScheduleID();
            result = outArgs.getResult();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "CreateRecordSchedule");
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
                invocation.writeString("RecordScheduleID", recordScheduleID);
                invocation.writeString("Result", result);
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

    private class DoDeleteRecordSchedule implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordScheduleID;
            try
            {
                invocation.readStart();
                recordScheduleID = invocation.readString("RecordScheduleID");
                invocation.readEnd();
                deleteRecordSchedule(invocation, recordScheduleID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "DeleteRecordSchedule");
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

    private class DoGetRecordSchedule implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordScheduleID;
            String filter;
            String result;
            long updateID;
            try
            {
                invocation.readStart();
                recordScheduleID = invocation.readString("RecordScheduleID");
                filter = invocation.readString("Filter");
                invocation.readEnd();

            GetRecordSchedule outArgs = getRecordSchedule(invocation, recordScheduleID, filter);
            result = outArgs.getResult();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRecordSchedule");
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

    private class DoEnableRecordSchedule implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordScheduleID;
            try
            {
                invocation.readStart();
                recordScheduleID = invocation.readString("RecordScheduleID");
                invocation.readEnd();
                enableRecordSchedule(invocation, recordScheduleID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "EnableRecordSchedule");
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

    private class DoDisableRecordSchedule implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordScheduleID;
            try
            {
                invocation.readStart();
                recordScheduleID = invocation.readString("RecordScheduleID");
                invocation.readEnd();
                disableRecordSchedule(invocation, recordScheduleID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "DisableRecordSchedule");
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

    private class DoDeleteRecordTask implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordTaskID;
            try
            {
                invocation.readStart();
                recordTaskID = invocation.readString("RecordTaskID");
                invocation.readEnd();
                deleteRecordTask(invocation, recordTaskID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "DeleteRecordTask");
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

    private class DoGetRecordTask implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordTaskID;
            String filter;
            String result;
            long updateID;
            try
            {
                invocation.readStart();
                recordTaskID = invocation.readString("RecordTaskID");
                filter = invocation.readString("Filter");
                invocation.readEnd();

            GetRecordTask outArgs = getRecordTask(invocation, recordTaskID, filter);
            result = outArgs.getResult();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRecordTask");
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

    private class DoEnableRecordTask implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordTaskID;
            try
            {
                invocation.readStart();
                recordTaskID = invocation.readString("RecordTaskID");
                invocation.readEnd();
                enableRecordTask(invocation, recordTaskID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "EnableRecordTask");
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

    private class DoDisableRecordTask implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordTaskID;
            try
            {
                invocation.readStart();
                recordTaskID = invocation.readString("RecordTaskID");
                invocation.readEnd();
                disableRecordTask(invocation, recordTaskID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "DisableRecordTask");
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

    private class DoResetRecordTask implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordTaskID;
            try
            {
                invocation.readStart();
                recordTaskID = invocation.readString("RecordTaskID");
                invocation.readEnd();
                resetRecordTask(invocation, recordTaskID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ResetRecordTask");
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

    private class DoGetRecordScheduleConflicts implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordScheduleID;
            String recordScheduleConflictIDList;
            long updateID;
            try
            {
                invocation.readStart();
                recordScheduleID = invocation.readString("RecordScheduleID");
                invocation.readEnd();

            GetRecordScheduleConflicts outArgs = getRecordScheduleConflicts(invocation, recordScheduleID);
            recordScheduleConflictIDList = outArgs.getRecordScheduleConflictIDList();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRecordScheduleConflicts");
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
                invocation.writeString("RecordScheduleConflictIDList", recordScheduleConflictIDList);
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

    private class DoGetRecordTaskConflicts implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String recordTaskID;
            String recordTaskConflictIDList;
            long updateID;
            try
            {
                invocation.readStart();
                recordTaskID = invocation.readString("RecordTaskID");
                invocation.readEnd();

            GetRecordTaskConflicts outArgs = getRecordTaskConflicts(invocation, recordTaskID);
            recordTaskConflictIDList = outArgs.getRecordTaskConflictIDList();
            updateID = outArgs.getUpdateID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRecordTaskConflicts");
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
                invocation.writeString("RecordTaskConflictIDList", recordTaskConflictIDList);
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
}

