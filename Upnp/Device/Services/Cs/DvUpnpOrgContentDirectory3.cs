using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
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
        /// <param name="aValue">Property's value will be copied here</param>
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
            List<String> allowedValues = new List<String>();
            iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"));
            AddProperty(iPropertySystemUpdateID);
            iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs", allowedValues));
            AddProperty(iPropertyContainerUpdateIDs);
            iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
            AddProperty(iPropertyLastChange);
            iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs", allowedValues));
            AddProperty(iPropertyTransferIDs);
        }

        /// <summary>
        /// Set the value of the SystemUpdateID property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySystemUpdateID(uint aValue)
        {
            return SetPropertyUint(iPropertySystemUpdateID, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SystemUpdateID property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertySystemUpdateID()
        {
            return iPropertySystemUpdateID.Value();
        }

        /// <summary>
        /// Set the value of the ContainerUpdateIDs property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyContainerUpdateIDs(string aValue)
        {
            return SetPropertyString(iPropertyContainerUpdateIDs, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ContainerUpdateIDs property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyContainerUpdateIDs()
        {
            return iPropertyContainerUpdateIDs.Value();
        }

        /// <summary>
        /// Set the value of the LastChange property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLastChange(string aValue)
        {
            return SetPropertyString(iPropertyLastChange, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the LastChange property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyLastChange()
        {
            return iPropertyLastChange.Value();
        }

        /// <summary>
        /// Set the value of the TransferIDs property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTransferIDs(string aValue)
        {
            return SetPropertyString(iPropertyTransferIDs, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TransferIDs property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyTransferIDs()
        {
            return iPropertyTransferIDs.Value();
        }

        /// <summary>
        /// Signal that the action GetSearchCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetSearchCapabilities must be overridden if this is called.</remarks>
        protected void EnableActionGetSearchCapabilities()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetSearchCapabilities");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetSortCapabilities");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetSortExtensionCapabilities");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetFeatureList");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetSystemUpdateID");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetServiceResetToken");
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
            Zapp.Core.Action action = new Zapp.Core.Action("Browse");
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
            Zapp.Core.Action action = new Zapp.Core.Action("Search");
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
            Zapp.Core.Action action = new Zapp.Core.Action("CreateObject");
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
            Zapp.Core.Action action = new Zapp.Core.Action("DestroyObject");
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
            Zapp.Core.Action action = new Zapp.Core.Action("UpdateObject");
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
            Zapp.Core.Action action = new Zapp.Core.Action("MoveObject");
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
            Zapp.Core.Action action = new Zapp.Core.Action("ImportResource");
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
            Zapp.Core.Action action = new Zapp.Core.Action("ExportResource");
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
            Zapp.Core.Action action = new Zapp.Core.Action("DeleteResource");
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
            Zapp.Core.Action action = new Zapp.Core.Action("StopTransferResource");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetTransferProgress");
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
            Zapp.Core.Action action = new Zapp.Core.Action("CreateReference");
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
            Zapp.Core.Action action = new Zapp.Core.Action("FreeFormQuery");
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
            Zapp.Core.Action action = new Zapp.Core.Action("GetFreeFormQueryCapabilities");
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aSearchCaps"></param>
        protected virtual void GetSearchCapabilities(uint aVersion, out string aSearchCaps)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aSortCaps"></param>
        protected virtual void GetSortCapabilities(uint aVersion, out string aSortCaps)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aSortExtensionCaps"></param>
        protected virtual void GetSortExtensionCapabilities(uint aVersion, out string aSortExtensionCaps)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aFeatureList"></param>
        protected virtual void GetFeatureList(uint aVersion, out string aFeatureList)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aId"></param>
        protected virtual void GetSystemUpdateID(uint aVersion, out uint aId)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aResetToken"></param>
        protected virtual void GetServiceResetToken(uint aVersion, out string aResetToken)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
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
        protected virtual void Browse(uint aVersion, string aObjectID, string aBrowseFlag, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
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
        protected virtual void Search(uint aVersion, string aContainerID, string aSearchCriteria, string aFilter, uint aStartingIndex, uint aRequestedCount, string aSortCriteria, out string aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aContainerID"></param>
        /// <param name="aElements"></param>
        /// <param name="aObjectID"></param>
        /// <param name="aResult"></param>
        protected virtual void CreateObject(uint aVersion, string aContainerID, string aElements, out string aObjectID, out string aResult)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aObjectID"></param>
        protected virtual void DestroyObject(uint aVersion, string aObjectID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aObjectID"></param>
        /// <param name="aCurrentTagValue"></param>
        /// <param name="aNewTagValue"></param>
        protected virtual void UpdateObject(uint aVersion, string aObjectID, string aCurrentTagValue, string aNewTagValue)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aObjectID"></param>
        /// <param name="aNewParentID"></param>
        /// <param name="aNewObjectID"></param>
        protected virtual void MoveObject(uint aVersion, string aObjectID, string aNewParentID, out string aNewObjectID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aSourceURI"></param>
        /// <param name="aDestinationURI"></param>
        /// <param name="aTransferID"></param>
        protected virtual void ImportResource(uint aVersion, string aSourceURI, string aDestinationURI, out uint aTransferID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aSourceURI"></param>
        /// <param name="aDestinationURI"></param>
        /// <param name="aTransferID"></param>
        protected virtual void ExportResource(uint aVersion, string aSourceURI, string aDestinationURI, out uint aTransferID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aResourceURI"></param>
        protected virtual void DeleteResource(uint aVersion, string aResourceURI)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aTransferID"></param>
        protected virtual void StopTransferResource(uint aVersion, uint aTransferID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aTransferID"></param>
        /// <param name="aTransferStatus"></param>
        /// <param name="aTransferLength"></param>
        /// <param name="aTransferTotal"></param>
        protected virtual void GetTransferProgress(uint aVersion, uint aTransferID, out string aTransferStatus, out string aTransferLength, out string aTransferTotal)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aContainerID"></param>
        /// <param name="aObjectID"></param>
        /// <param name="aNewID"></param>
        protected virtual void CreateReference(uint aVersion, string aContainerID, string aObjectID, out string aNewID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aContainerID"></param>
        /// <param name="aCDSView"></param>
        /// <param name="aQueryRequest"></param>
        /// <param name="aQueryResult"></param>
        /// <param name="aUpdateID"></param>
        protected virtual void FreeFormQuery(uint aVersion, string aContainerID, uint aCDSView, string aQueryRequest, out string aQueryResult, out uint aUpdateID)
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
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aFFQCapabilities"></param>
        protected virtual void GetFreeFormQueryCapabilities(uint aVersion, out string aFFQCapabilities)
        {
            throw (new ActionDisabledError());
        }

        private static int DoGetSearchCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string searchCaps;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSearchCapabilities(aVersion, out searchCaps);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoGetSortCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sortCaps;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSortCapabilities(aVersion, out sortCaps);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoGetSortExtensionCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sortExtensionCaps;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSortExtensionCapabilities(aVersion, out sortExtensionCaps);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoGetFeatureList(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string featureList;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetFeatureList(aVersion, out featureList);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoGetSystemUpdateID(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetSystemUpdateID(aVersion, out id);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoGetServiceResetToken(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string resetToken;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetServiceResetToken(aVersion, out resetToken);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoBrowse(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.Browse(aVersion, objectID, browseFlag, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoSearch(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.Search(aVersion, containerID, searchCriteria, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoCreateObject(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.CreateObject(aVersion, containerID, elements, out objectID, out result);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoDestroyObject(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.DestroyObject(aVersion, objectID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoUpdateObject(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.UpdateObject(aVersion, objectID, currentTagValue, newTagValue);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoMoveObject(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.MoveObject(aVersion, objectID, newParentID, out newObjectID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoImportResource(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.ImportResource(aVersion, sourceURI, destinationURI, out transferID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoExportResource(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.ExportResource(aVersion, sourceURI, destinationURI, out transferID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoDeleteResource(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.DeleteResource(aVersion, resourceURI);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoStopTransferResource(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.StopTransferResource(aVersion, transferID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoGetTransferProgress(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.GetTransferProgress(aVersion, transferID, out transferStatus, out transferLength, out transferTotal);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoCreateReference(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.CreateReference(aVersion, containerID, objectID, out newID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoFreeFormQuery(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
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
                self.FreeFormQuery(aVersion, containerID, cDSView, queryRequest, out queryResult, out updateID);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoGetFreeFormQueryCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory3 self = (DvProviderUpnpOrgContentDirectory3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string fFQCapabilities;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetFreeFormQueryCapabilities(aVersion, out fFQCapabilities);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderUpnpOrgContentDirectory3()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProvider();
                iHandle = IntPtr.Zero;
            }
            iGch.Free();
        }
    }
}

