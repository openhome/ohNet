using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderUpnpOrgContentDirectory3 : IDisposable
    {

        /// <summary>
        /// Set the value of the SystemUpdateID property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySystemUpdateID(uint aValue);

        /// <summary>
        /// Get a copy of the value of the SystemUpdateID property
        /// </summary>
        /// <returns>Value of the SystemUpdateID property.</param>
        uint PropertySystemUpdateID();

        /// <summary>
        /// Set the value of the ContainerUpdateIDs property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyContainerUpdateIDs(string aValue);

        /// <summary>
        /// Get a copy of the value of the ContainerUpdateIDs property
        /// </summary>
        /// <returns>Value of the ContainerUpdateIDs property.</param>
        string PropertyContainerUpdateIDs();

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyLastChange(string aValue);

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <returns>Value of the LastChange property.</param>
        string PropertyLastChange();

        /// <summary>
        /// Set the value of the TransferIDs property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTransferIDs(string aValue);

        /// <summary>
        /// Get a copy of the value of the TransferIDs property
        /// </summary>
        /// <returns>Value of the TransferIDs property.</param>
        string PropertyTransferIDs();
        
    }
    /// <summary>
    /// Provider for the upnp.org:ContentDirectory:3 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgContentDirectory3 : DvProvider, IDisposable, IDvProviderUpnpOrgContentDirectory3
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateGetSearchCapabilities;
        private ActionDelegate iDelegateGetSortCapabilities;
        private ActionDelegate iDelegateGetSortExtensionCapabilities;
        private ActionDelegate iDelegateGetFeatureList;
        private ActionDelegate iDelegateGetSystemUpdateID;
        private ActionDelegate iDelegateGetServiceResetToken;
        private ActionDelegate iDelegateBrowse;
        private ActionDelegate iDelegateSearch;
        private ActionDelegate iDelegateCreateObject;
        private ActionDelegate iDelegateDestroyObject;
        private ActionDelegate iDelegateUpdateObject;
        private ActionDelegate iDelegateMoveObject;
        private ActionDelegate iDelegateImportResource;
        private ActionDelegate iDelegateExportResource;
        private ActionDelegate iDelegateDeleteResource;
        private ActionDelegate iDelegateStopTransferResource;
        private ActionDelegate iDelegateGetTransferProgress;
        private ActionDelegate iDelegateCreateReference;
        private ActionDelegate iDelegateFreeFormQuery;
        private ActionDelegate iDelegateGetFreeFormQueryCapabilities;
        private PropertyUint iPropertySystemUpdateID;
        private PropertyString iPropertyContainerUpdateIDs;
        private PropertyString iPropertyLastChange;
        private PropertyString iPropertyTransferIDs;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgContentDirectory3(DvDevice aDevice)
            : base(aDevice, "upnp.org", "ContentDirectory", 3)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the SystemUpdateID property.
        /// </summary>
        public void EnablePropertySystemUpdateID()
        {
            iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"));
            AddProperty(iPropertySystemUpdateID);
        }

        /// <summary>
        /// Enable the ContainerUpdateIDs property.
        /// </summary>
        public void EnablePropertyContainerUpdateIDs()
        {
            List<String> allowedValues = new List<String>();
            iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs", allowedValues));
            AddProperty(iPropertyContainerUpdateIDs);
        }

        /// <summary>
        /// Enable the LastChange property.
        /// </summary>
        public void EnablePropertyLastChange()
        {
            List<String> allowedValues = new List<String>();
            iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
            AddProperty(iPropertyLastChange);
        }

        /// <summary>
        /// Enable the TransferIDs property.
        /// </summary>
        public void EnablePropertyTransferIDs()
        {
            List<String> allowedValues = new List<String>();
            iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs", allowedValues));
            AddProperty(iPropertyTransferIDs);
        }

        /// <summary>
        /// Set the value of the SystemUpdateID property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySystemUpdateID has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySystemUpdateID(uint aValue)
        {
            if (iPropertySystemUpdateID == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertySystemUpdateID, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SystemUpdateID property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySystemUpdateID has previously been called.</remarks>
        /// <returns>Value of the SystemUpdateID property.</returns>
        public uint PropertySystemUpdateID()
        {
            if (iPropertySystemUpdateID == null)
                throw new PropertyDisabledError();
            return iPropertySystemUpdateID.Value();
        }

        /// <summary>
        /// Set the value of the ContainerUpdateIDs property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyContainerUpdateIDs has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyContainerUpdateIDs(string aValue)
        {
            if (iPropertyContainerUpdateIDs == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyContainerUpdateIDs, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ContainerUpdateIDs property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyContainerUpdateIDs has previously been called.</remarks>
        /// <returns>Value of the ContainerUpdateIDs property.</returns>
        public string PropertyContainerUpdateIDs()
        {
            if (iPropertyContainerUpdateIDs == null)
                throw new PropertyDisabledError();
            return iPropertyContainerUpdateIDs.Value();
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyLastChange has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLastChange(string aValue)
        {
            if (iPropertyLastChange == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyLastChange, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyLastChange has previously been called.</remarks>
        /// <returns>Value of the LastChange property.</returns>
        public string PropertyLastChange()
        {
            if (iPropertyLastChange == null)
                throw new PropertyDisabledError();
            return iPropertyLastChange.Value();
        }

        /// <summary>
        /// Set the value of the TransferIDs property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTransferIDs has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTransferIDs(string aValue)
        {
            if (iPropertyTransferIDs == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyTransferIDs, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TransferIDs property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTransferIDs has previously been called.</remarks>
        /// <returns>Value of the TransferIDs property.</returns>
        public string PropertyTransferIDs()
        {
            if (iPropertyTransferIDs == null)
                throw new PropertyDisabledError();
            return iPropertyTransferIDs.Value();
        }

        /// <summary>
        /// Signal that the action GetSearchCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetSearchCapabilities must be overridden if this is called.</remarks>
        protected void EnableActionGetSearchCapabilities()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetSearchCapabilities");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("SearchCaps", allowedValues));
            iDelegateGetSearchCapabilities = new ActionDelegate(DoGetSearchCapabilities);
            EnableAction(action, iDelegateGetSearchCapabilities, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetSortCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetSortCapabilities must be overridden if this is called.</remarks>
        protected void EnableActionGetSortCapabilities()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetSortCapabilities");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("SortCaps", allowedValues));
            iDelegateGetSortCapabilities = new ActionDelegate(DoGetSortCapabilities);
            EnableAction(action, iDelegateGetSortCapabilities, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetSortExtensionCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetSortExtensionCapabilities must be overridden if this is called.</remarks>
        protected void EnableActionGetSortExtensionCapabilities()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetSortExtensionCapabilities");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("SortExtensionCaps", allowedValues));
            iDelegateGetSortExtensionCapabilities = new ActionDelegate(DoGetSortExtensionCapabilities);
            EnableAction(action, iDelegateGetSortExtensionCapabilities, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetFeatureList is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetFeatureList must be overridden if this is called.</remarks>
        protected void EnableActionGetFeatureList()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetFeatureList");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("FeatureList", allowedValues));
            iDelegateGetFeatureList = new ActionDelegate(DoGetFeatureList);
            EnableAction(action, iDelegateGetFeatureList, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetSystemUpdateID is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetSystemUpdateID must be overridden if this is called.</remarks>
        protected void EnableActionGetSystemUpdateID()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetSystemUpdateID");
            action.AddOutputParameter(new ParameterRelated("Id", iPropertySystemUpdateID));
            iDelegateGetSystemUpdateID = new ActionDelegate(DoGetSystemUpdateID);
            EnableAction(action, iDelegateGetSystemUpdateID, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetServiceResetToken is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetServiceResetToken must be overridden if this is called.</remarks>
        protected void EnableActionGetServiceResetToken()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetServiceResetToken");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("ResetToken", allowedValues));
            iDelegateGetServiceResetToken = new ActionDelegate(DoGetServiceResetToken);
            EnableAction(action, iDelegateGetServiceResetToken, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Browse is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Browse must be overridden if this is called.</remarks>
        protected void EnableActionBrowse()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Browse");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ObjectID", allowedValues));
            allowedValues.Add("BrowseMetadata");
            allowedValues.Add("BrowseDirectChildren");
            action.AddInputParameter(new ParameterString("BrowseFlag", allowedValues));
            allowedValues.Clear();
            action.AddInputParameter(new ParameterString("Filter", allowedValues));
            action.AddInputParameter(new ParameterUint("StartingIndex"));
            action.AddInputParameter(new ParameterUint("RequestedCount"));
            action.AddInputParameter(new ParameterString("SortCriteria", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            action.AddOutputParameter(new ParameterUint("NumberReturned"));
            action.AddOutputParameter(new ParameterUint("TotalMatches"));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateBrowse = new ActionDelegate(DoBrowse);
            EnableAction(action, iDelegateBrowse, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Search is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Search must be overridden if this is called.</remarks>
        protected void EnableActionSearch()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Search");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ContainerID", allowedValues));
            action.AddInputParameter(new ParameterString("SearchCriteria", allowedValues));
            action.AddInputParameter(new ParameterString("Filter", allowedValues));
            action.AddInputParameter(new ParameterUint("StartingIndex"));
            action.AddInputParameter(new ParameterUint("RequestedCount"));
            action.AddInputParameter(new ParameterString("SortCriteria", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            action.AddOutputParameter(new ParameterUint("NumberReturned"));
            action.AddOutputParameter(new ParameterUint("TotalMatches"));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateSearch = new ActionDelegate(DoSearch);
            EnableAction(action, iDelegateSearch, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action CreateObject is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// CreateObject must be overridden if this is called.</remarks>
        protected void EnableActionCreateObject()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("CreateObject");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ContainerID", allowedValues));
            action.AddInputParameter(new ParameterString("Elements", allowedValues));
            action.AddOutputParameter(new ParameterString("ObjectID", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            iDelegateCreateObject = new ActionDelegate(DoCreateObject);
            EnableAction(action, iDelegateCreateObject, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DestroyObject is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DestroyObject must be overridden if this is called.</remarks>
        protected void EnableActionDestroyObject()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("DestroyObject");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ObjectID", allowedValues));
            iDelegateDestroyObject = new ActionDelegate(DoDestroyObject);
            EnableAction(action, iDelegateDestroyObject, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action UpdateObject is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// UpdateObject must be overridden if this is called.</remarks>
        protected void EnableActionUpdateObject()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("UpdateObject");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ObjectID", allowedValues));
            action.AddInputParameter(new ParameterString("CurrentTagValue", allowedValues));
            action.AddInputParameter(new ParameterString("NewTagValue", allowedValues));
            iDelegateUpdateObject = new ActionDelegate(DoUpdateObject);
            EnableAction(action, iDelegateUpdateObject, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action MoveObject is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// MoveObject must be overridden if this is called.</remarks>
        protected void EnableActionMoveObject()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("MoveObject");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ObjectID", allowedValues));
            action.AddInputParameter(new ParameterString("NewParentID", allowedValues));
            action.AddOutputParameter(new ParameterString("NewObjectID", allowedValues));
            iDelegateMoveObject = new ActionDelegate(DoMoveObject);
            EnableAction(action, iDelegateMoveObject, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ImportResource is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ImportResource must be overridden if this is called.</remarks>
        protected void EnableActionImportResource()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ImportResource");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("SourceURI", allowedValues));
            action.AddInputParameter(new ParameterString("DestinationURI", allowedValues));
            action.AddOutputParameter(new ParameterUint("TransferID"));
            iDelegateImportResource = new ActionDelegate(DoImportResource);
            EnableAction(action, iDelegateImportResource, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ExportResource is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ExportResource must be overridden if this is called.</remarks>
        protected void EnableActionExportResource()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ExportResource");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("SourceURI", allowedValues));
            action.AddInputParameter(new ParameterString("DestinationURI", allowedValues));
            action.AddOutputParameter(new ParameterUint("TransferID"));
            iDelegateExportResource = new ActionDelegate(DoExportResource);
            EnableAction(action, iDelegateExportResource, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DeleteResource is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DeleteResource must be overridden if this is called.</remarks>
        protected void EnableActionDeleteResource()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("DeleteResource");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ResourceURI", allowedValues));
            iDelegateDeleteResource = new ActionDelegate(DoDeleteResource);
            EnableAction(action, iDelegateDeleteResource, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StopTransferResource is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// StopTransferResource must be overridden if this is called.</remarks>
        protected void EnableActionStopTransferResource()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("StopTransferResource");
            action.AddInputParameter(new ParameterUint("TransferID"));
            iDelegateStopTransferResource = new ActionDelegate(DoStopTransferResource);
            EnableAction(action, iDelegateStopTransferResource, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetTransferProgress is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetTransferProgress must be overridden if this is called.</remarks>
        protected void EnableActionGetTransferProgress()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetTransferProgress");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("TransferID"));
            allowedValues.Add("COMPLETED");
            allowedValues.Add("ERROR");
            allowedValues.Add("IN_PROGRESS");
            allowedValues.Add("STOPPED");
            action.AddOutputParameter(new ParameterString("TransferStatus", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterString("TransferLength", allowedValues));
            action.AddOutputParameter(new ParameterString("TransferTotal", allowedValues));
            iDelegateGetTransferProgress = new ActionDelegate(DoGetTransferProgress);
            EnableAction(action, iDelegateGetTransferProgress, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action CreateReference is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// CreateReference must be overridden if this is called.</remarks>
        protected void EnableActionCreateReference()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("CreateReference");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ContainerID", allowedValues));
            action.AddInputParameter(new ParameterString("ObjectID", allowedValues));
            action.AddOutputParameter(new ParameterString("NewID", allowedValues));
            iDelegateCreateReference = new ActionDelegate(DoCreateReference);
            EnableAction(action, iDelegateCreateReference, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action FreeFormQuery is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// FreeFormQuery must be overridden if this is called.</remarks>
        protected void EnableActionFreeFormQuery()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("FreeFormQuery");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ContainerID", allowedValues));
            action.AddInputParameter(new ParameterUint("CDSView"));
            action.AddInputParameter(new ParameterString("QueryRequest", allowedValues));
            action.AddOutputParameter(new ParameterString("QueryResult", allowedValues));
            action.AddOutputParameter(new ParameterUint("UpdateID"));
            iDelegateFreeFormQuery = new ActionDelegate(DoFreeFormQuery);
            EnableAction(action, iDelegateFreeFormQuery, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetFreeFormQueryCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetFreeFormQueryCapabilities must be overridden if this is called.</remarks>
        protected void EnableActionGetFreeFormQueryCapabilities()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetFreeFormQueryCapabilities");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("FFQCapabilities", allowedValues));
            iDelegateGetFreeFormQueryCapabilities = new ActionDelegate(DoGetFreeFormQueryCapabilities);
            EnableAction(action, iDelegateGetFreeFormQueryCapabilities, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// GetSearchCapabilities action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetSearchCapabilities action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetSearchCapabilities was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aSearchCaps"></param>
        protected virtual void GetSearchCapabilities(IDvInvocation aInvocation, out string aSearchCaps)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetSortCapabilities action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetSortCapabilities action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetSortCapabilities was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aSortCaps"></param>
        protected virtual void GetSortCapabilities(IDvInvocation aInvocation, out string aSortCaps)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetSortExtensionCapabilities action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetSortExtensionCapabilities action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetSortExtensionCapabilities was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aSortExtensionCaps"></param>
        protected virtual void GetSortExtensionCapabilities(IDvInvocation aInvocation, out string aSortExtensionCaps)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetFeatureList action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetFeatureList action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetFeatureList was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aFeatureList"></param>
        protected virtual void GetFeatureList(IDvInvocation aInvocation, out string aFeatureList)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetSystemUpdateID action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetSystemUpdateID action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetSystemUpdateID was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aId"></param>
        protected virtual void GetSystemUpdateID(IDvInvocation aInvocation, out uint aId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetServiceResetToken action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetServiceResetToken action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetServiceResetToken was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aResetToken"></param>
        protected virtual void GetServiceResetToken(IDvInvocation aInvocation, out string aResetToken)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Browse action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Browse action for the owning device.
        ///
        /// Must be implemented iff EnableActionBrowse was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aObjectID"></param>
        /// <param name="aBrowseFlag"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void Browse(IDvInvocation aInvocation, string aObjectID, string aBrowseFlag, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Search action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Search action for the owning device.
        ///
        /// Must be implemented iff EnableActionSearch was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aContainerID"></param>
        /// <param name="aSearchCriteria"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void Search(IDvInvocation aInvocation, string aContainerID, string aSearchCriteria, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// CreateObject action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CreateObject action for the owning device.
        ///
        /// Must be implemented iff EnableActionCreateObject was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aContainerID"></param>
        /// <param name="aElements"></param>
        /// <param name="aObjectID"></param>
        /// <param name="aResult"></param>
        protected virtual void CreateObject(IDvInvocation aInvocation, string aContainerID, string aElements, out string aObjectID, out string aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DestroyObject action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DestroyObject action for the owning device.
        ///
        /// Must be implemented iff EnableActionDestroyObject was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aObjectID"></param>
        protected virtual void DestroyObject(IDvInvocation aInvocation, string aObjectID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// UpdateObject action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// UpdateObject action for the owning device.
        ///
        /// Must be implemented iff EnableActionUpdateObject was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aObjectID"></param>
        /// <param name="aCurrentTagValue"></param>
        /// <param name="aNewTagValue"></param>
        protected virtual void UpdateObject(IDvInvocation aInvocation, string aObjectID, string aCurrentTagValue, string aNewTagValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// MoveObject action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// MoveObject action for the owning device.
        ///
        /// Must be implemented iff EnableActionMoveObject was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aObjectID"></param>
        /// <param name="aNewParentID"></param>
        /// <param name="aNewObjectID"></param>
        protected virtual void MoveObject(IDvInvocation aInvocation, string aObjectID, string aNewParentID, out string aNewObjectID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ImportResource action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ImportResource action for the owning device.
        ///
        /// Must be implemented iff EnableActionImportResource was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aSourceURI"></param>
        /// <param name="aDestinationURI"></param>
        /// <param name="aTransferID"></param>
        protected virtual void ImportResource(IDvInvocation aInvocation, string aSourceURI, string aDestinationURI, out uint aTransferID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ExportResource action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ExportResource action for the owning device.
        ///
        /// Must be implemented iff EnableActionExportResource was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aSourceURI"></param>
        /// <param name="aDestinationURI"></param>
        /// <param name="aTransferID"></param>
        protected virtual void ExportResource(IDvInvocation aInvocation, string aSourceURI, string aDestinationURI, out uint aTransferID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DeleteResource action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DeleteResource action for the owning device.
        ///
        /// Must be implemented iff EnableActionDeleteResource was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aResourceURI"></param>
        protected virtual void DeleteResource(IDvInvocation aInvocation, string aResourceURI)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StopTransferResource action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StopTransferResource action for the owning device.
        ///
        /// Must be implemented iff EnableActionStopTransferResource was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aTransferID"></param>
        protected virtual void StopTransferResource(IDvInvocation aInvocation, uint aTransferID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetTransferProgress action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetTransferProgress action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetTransferProgress was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aTransferID"></param>
        /// <param name="aTransferStatus"></param>
        /// <param name="aTransferLength"></param>
        /// <param name="aTransferTotal"></param>
        protected virtual void GetTransferProgress(IDvInvocation aInvocation, uint aTransferID, out string aTransferStatus, out string aTransferLength, out string aTransferTotal)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// CreateReference action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CreateReference action for the owning device.
        ///
        /// Must be implemented iff EnableActionCreateReference was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aContainerID"></param>
        /// <param name="aObjectID"></param>
        /// <param name="aNewID"></param>
        protected virtual void CreateReference(IDvInvocation aInvocation, string aContainerID, string aObjectID, out string aNewID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// FreeFormQuery action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// FreeFormQuery action for the owning device.
        ///
        /// Must be implemented iff EnableActionFreeFormQuery was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aContainerID"></param>
        /// <param name="aCDSView"></param>
        /// <param name="aQueryRequest"></param>
        /// <param name="aQueryResult"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void FreeFormQuery(IDvInvocation aInvocation, string aContainerID, uint aCDSView, string aQueryRequest, out string aQueryResult, out uint aUpdateID)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetFreeFormQueryCapabilities action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetFreeFormQueryCapabilities action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetFreeFormQueryCapabilities was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aFFQCapabilities"></param>
        protected virtual void GetFreeFormQueryCapabilities(IDvInvocation aInvocation, out string aFFQCapabilities)
        {
            throw (new ActionDisabledError());
        }

        private static int DoGetSearchCapabilities(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string searchCaps;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSearchCapabilities(invocation, out searchCaps);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetSearchCapabilities");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetSearchCapabilities"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetSearchCapabilities", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("SearchCaps", searchCaps);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetSearchCapabilities", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetSortCapabilities(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sortCaps;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSortCapabilities(invocation, out sortCaps);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetSortCapabilities");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetSortCapabilities"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetSortCapabilities", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("SortCaps", sortCaps);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetSortCapabilities", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetSortExtensionCapabilities(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sortExtensionCaps;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSortExtensionCapabilities(invocation, out sortExtensionCaps);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetSortExtensionCapabilities");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetSortExtensionCapabilities"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetSortExtensionCapabilities", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("SortExtensionCaps", sortExtensionCaps);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetSortExtensionCapabilities", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetFeatureList(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string featureList;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetFeatureList(invocation, out featureList);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetFeatureList");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetFeatureList"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetFeatureList", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("FeatureList", featureList);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetFeatureList", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetSystemUpdateID(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSystemUpdateID(invocation, out id);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetSystemUpdateID");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetSystemUpdateID"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetSystemUpdateID", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Id", id);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetSystemUpdateID", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetServiceResetToken(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string resetToken;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetServiceResetToken(invocation, out resetToken);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetServiceResetToken");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetServiceResetToken"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetServiceResetToken", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("ResetToken", resetToken);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetServiceResetToken", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoBrowse(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string objectID;
            string browseFlag;
            string filter;
            uint startingIndex;
            uint requestedCount;
            string sortCriteria;
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            try
            {
                invocation.ReadStart();
                objectID = invocation.ReadString("ObjectID");
                browseFlag = invocation.ReadString("BrowseFlag");
                filter = invocation.ReadString("Filter");
                startingIndex = invocation.ReadUint("StartingIndex");
                requestedCount = invocation.ReadUint("RequestedCount");
                sortCriteria = invocation.ReadString("SortCriteria");
                invocation.ReadEnd();
                self.Browse(invocation, objectID, browseFlag, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Browse");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Browse"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Browse", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteUint("NumberReturned", numberReturned);
                invocation.WriteUint("TotalMatches", totalMatches);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Browse", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSearch(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string containerID;
            string searchCriteria;
            string filter;
            uint startingIndex;
            uint requestedCount;
            string sortCriteria;
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            try
            {
                invocation.ReadStart();
                containerID = invocation.ReadString("ContainerID");
                searchCriteria = invocation.ReadString("SearchCriteria");
                filter = invocation.ReadString("Filter");
                startingIndex = invocation.ReadUint("StartingIndex");
                requestedCount = invocation.ReadUint("RequestedCount");
                sortCriteria = invocation.ReadString("SortCriteria");
                invocation.ReadEnd();
                self.Search(invocation, containerID, searchCriteria, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Search");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Search"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Search", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteUint("NumberReturned", numberReturned);
                invocation.WriteUint("TotalMatches", totalMatches);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Search", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoCreateObject(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string containerID;
            string elements;
            string objectID;
            string result;
            try
            {
                invocation.ReadStart();
                containerID = invocation.ReadString("ContainerID");
                elements = invocation.ReadString("Elements");
                invocation.ReadEnd();
                self.CreateObject(invocation, containerID, elements, out objectID, out result);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "CreateObject");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "CreateObject"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "CreateObject", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("ObjectID", objectID);
                invocation.WriteString("Result", result);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "CreateObject", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoDestroyObject(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string objectID;
            try
            {
                invocation.ReadStart();
                objectID = invocation.ReadString("ObjectID");
                invocation.ReadEnd();
                self.DestroyObject(invocation, objectID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "DestroyObject");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "DestroyObject"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "DestroyObject", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "DestroyObject", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoUpdateObject(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string objectID;
            string currentTagValue;
            string newTagValue;
            try
            {
                invocation.ReadStart();
                objectID = invocation.ReadString("ObjectID");
                currentTagValue = invocation.ReadString("CurrentTagValue");
                newTagValue = invocation.ReadString("NewTagValue");
                invocation.ReadEnd();
                self.UpdateObject(invocation, objectID, currentTagValue, newTagValue);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "UpdateObject");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "UpdateObject"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "UpdateObject", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "UpdateObject", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoMoveObject(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string objectID;
            string newParentID;
            string newObjectID;
            try
            {
                invocation.ReadStart();
                objectID = invocation.ReadString("ObjectID");
                newParentID = invocation.ReadString("NewParentID");
                invocation.ReadEnd();
                self.MoveObject(invocation, objectID, newParentID, out newObjectID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "MoveObject");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "MoveObject"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "MoveObject", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("NewObjectID", newObjectID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "MoveObject", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoImportResource(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sourceURI;
            string destinationURI;
            uint transferID;
            try
            {
                invocation.ReadStart();
                sourceURI = invocation.ReadString("SourceURI");
                destinationURI = invocation.ReadString("DestinationURI");
                invocation.ReadEnd();
                self.ImportResource(invocation, sourceURI, destinationURI, out transferID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ImportResource");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "ImportResource"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ImportResource", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("TransferID", transferID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ImportResource", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoExportResource(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sourceURI;
            string destinationURI;
            uint transferID;
            try
            {
                invocation.ReadStart();
                sourceURI = invocation.ReadString("SourceURI");
                destinationURI = invocation.ReadString("DestinationURI");
                invocation.ReadEnd();
                self.ExportResource(invocation, sourceURI, destinationURI, out transferID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ExportResource");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "ExportResource"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ExportResource", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("TransferID", transferID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "ExportResource", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoDeleteResource(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string resourceURI;
            try
            {
                invocation.ReadStart();
                resourceURI = invocation.ReadString("ResourceURI");
                invocation.ReadEnd();
                self.DeleteResource(invocation, resourceURI);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "DeleteResource");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "DeleteResource"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "DeleteResource", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "DeleteResource", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStopTransferResource(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint transferID;
            try
            {
                invocation.ReadStart();
                transferID = invocation.ReadUint("TransferID");
                invocation.ReadEnd();
                self.StopTransferResource(invocation, transferID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "StopTransferResource");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "StopTransferResource"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StopTransferResource", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "StopTransferResource", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetTransferProgress(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint transferID;
            string transferStatus;
            string transferLength;
            string transferTotal;
            try
            {
                invocation.ReadStart();
                transferID = invocation.ReadUint("TransferID");
                invocation.ReadEnd();
                self.GetTransferProgress(invocation, transferID, out transferStatus, out transferLength, out transferTotal);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetTransferProgress");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetTransferProgress"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetTransferProgress", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("TransferStatus", transferStatus);
                invocation.WriteString("TransferLength", transferLength);
                invocation.WriteString("TransferTotal", transferTotal);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetTransferProgress", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoCreateReference(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string containerID;
            string objectID;
            string newID;
            try
            {
                invocation.ReadStart();
                containerID = invocation.ReadString("ContainerID");
                objectID = invocation.ReadString("ObjectID");
                invocation.ReadEnd();
                self.CreateReference(invocation, containerID, objectID, out newID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "CreateReference");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "CreateReference"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "CreateReference", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("NewID", newID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "CreateReference", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoFreeFormQuery(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string containerID;
            uint cDSView;
            string queryRequest;
            string queryResult;
            uint updateID;
            try
            {
                invocation.ReadStart();
                containerID = invocation.ReadString("ContainerID");
                cDSView = invocation.ReadUint("CDSView");
                queryRequest = invocation.ReadString("QueryRequest");
                invocation.ReadEnd();
                self.FreeFormQuery(invocation, containerID, cDSView, queryRequest, out queryResult, out updateID);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "FreeFormQuery");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "FreeFormQuery"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "FreeFormQuery", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("QueryResult", queryResult);
                invocation.WriteUint("UpdateID", updateID);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "FreeFormQuery", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetFreeFormQueryCapabilities(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string fFQCapabilities;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetFreeFormQueryCapabilities(invocation, out fFQCapabilities);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetFreeFormQueryCapabilities");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "GetFreeFormQueryCapabilities"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetFreeFormQueryCapabilities", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("FFQCapabilities", fFQCapabilities);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "GetFreeFormQueryCapabilities", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            if (DisposeProvider())
                iGch.Free();
        }
    }
}

