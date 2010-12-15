using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderUpnpOrgContentDirectory1 : IDisposable
    {

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
        
    }
    /// <summary>
    /// Provider for the upnp.org:ContentDirectory:1 UPnP service
    /// </summary>
    public class DvProviderUpnpOrgContentDirectory1 : DvProvider, IDisposable, IDvProviderUpnpOrgContentDirectory1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateGetSearchCapabilities;
        private ActionDelegate iDelegateGetSortCapabilities;
        private ActionDelegate iDelegateGetSystemUpdateID;
        private ActionDelegate iDelegateBrowse;
        private ActionDelegate iDelegateSearch;
        private ActionDelegate iDelegateCreateObject;
        private ActionDelegate iDelegateDestroyObject;
        private ActionDelegate iDelegateUpdateObject;
        private ActionDelegate iDelegateImportResource;
        private ActionDelegate iDelegateExportResource;
        private ActionDelegate iDelegateStopTransferResource;
        private ActionDelegate iDelegateGetTransferProgress;
        private ActionDelegate iDelegateDeleteResource;
        private ActionDelegate iDelegateCreateReference;
        private PropertyString iPropertyTransferIDs;
        private PropertyUint iPropertySystemUpdateID;
        private PropertyString iPropertyContainerUpdateIDs;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderUpnpOrgContentDirectory1(DvDevice aDevice)
            : base(aDevice, "schemas-upnp-org", "ContentDirectory", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyTransferIDs = new PropertyString(new ParameterString("TransferIDs", allowedValues));
            AddProperty(iPropertyTransferIDs);
            iPropertySystemUpdateID = new PropertyUint(new ParameterUint("SystemUpdateID"));
            AddProperty(iPropertySystemUpdateID);
            iPropertyContainerUpdateIDs = new PropertyString(new ParameterString("ContainerUpdateIDs", allowedValues));
            AddProperty(iPropertyContainerUpdateIDs);
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
        /// Signal that the action GetSearchCapabilities is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetSearchCapabilities must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetSearchCapabilities()
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
        /// DoGetSortCapabilities must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetSortCapabilities()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetSortCapabilities");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("SortCaps", allowedValues));
            iDelegateGetSortCapabilities = new ActionDelegate(DoGetSortCapabilities);
            EnableAction(action, iDelegateGetSortCapabilities, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetSystemUpdateID is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetSystemUpdateID must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetSystemUpdateID()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetSystemUpdateID");
            action.AddOutputParameter(new ParameterRelated("Id", iPropertySystemUpdateID));
            iDelegateGetSystemUpdateID = new ActionDelegate(DoGetSystemUpdateID);
            EnableAction(action, iDelegateGetSystemUpdateID, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Browse is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBrowse must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBrowse()
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
        /// DoSearch must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSearch()
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
        /// DoCreateObject must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCreateObject()
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
        /// DoDestroyObject must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDestroyObject()
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
        /// DoUpdateObject must be overridden if this is called.</remarks>
        protected unsafe void EnableActionUpdateObject()
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
        /// Signal that the action ImportResource is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoImportResource must be overridden if this is called.</remarks>
        protected unsafe void EnableActionImportResource()
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
        /// DoExportResource must be overridden if this is called.</remarks>
        protected unsafe void EnableActionExportResource()
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
        /// Signal that the action StopTransferResource is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStopTransferResource must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStopTransferResource()
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
        /// DoGetTransferProgress must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetTransferProgress()
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
        /// Signal that the action DeleteResource is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDeleteResource must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDeleteResource()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DeleteResource");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("ResourceURI", allowedValues));
            iDelegateDeleteResource = new ActionDelegate(DoDeleteResource);
            EnableAction(action, iDelegateDeleteResource, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action CreateReference is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCreateReference must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCreateReference()
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

        private static unsafe int DoGetSearchCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string searchCaps;
            self.GetSearchCapabilities(aVersion, out searchCaps);
            invocation.WriteStart();
            invocation.WriteString("SearchCaps", searchCaps);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoGetSortCapabilities(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sortCaps;
            self.GetSortCapabilities(aVersion, out sortCaps);
            invocation.WriteStart();
            invocation.WriteString("SortCaps", sortCaps);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoGetSystemUpdateID(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint id;
            self.GetSystemUpdateID(aVersion, out id);
            invocation.WriteStart();
            invocation.WriteUint("Id", id);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoBrowse(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string objectID = invocation.ReadString("ObjectID");
            string browseFlag = invocation.ReadString("BrowseFlag");
            string filter = invocation.ReadString("Filter");
            uint startingIndex = invocation.ReadUint("StartingIndex");
            uint requestedCount = invocation.ReadUint("RequestedCount");
            string sortCriteria = invocation.ReadString("SortCriteria");
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            self.Browse(aVersion, objectID, browseFlag, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            invocation.WriteStart();
            invocation.WriteString("Result", result);
            invocation.WriteUint("NumberReturned", numberReturned);
            invocation.WriteUint("TotalMatches", totalMatches);
            invocation.WriteUint("UpdateID", updateID);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSearch(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string containerID = invocation.ReadString("ContainerID");
            string searchCriteria = invocation.ReadString("SearchCriteria");
            string filter = invocation.ReadString("Filter");
            uint startingIndex = invocation.ReadUint("StartingIndex");
            uint requestedCount = invocation.ReadUint("RequestedCount");
            string sortCriteria = invocation.ReadString("SortCriteria");
            string result;
            uint numberReturned;
            uint totalMatches;
            uint updateID;
            self.Search(aVersion, containerID, searchCriteria, filter, startingIndex, requestedCount, sortCriteria, out result, out numberReturned, out totalMatches, out updateID);
            invocation.WriteStart();
            invocation.WriteString("Result", result);
            invocation.WriteUint("NumberReturned", numberReturned);
            invocation.WriteUint("TotalMatches", totalMatches);
            invocation.WriteUint("UpdateID", updateID);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoCreateObject(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string containerID = invocation.ReadString("ContainerID");
            string elements = invocation.ReadString("Elements");
            string objectID;
            string result;
            self.CreateObject(aVersion, containerID, elements, out objectID, out result);
            invocation.WriteStart();
            invocation.WriteString("ObjectID", objectID);
            invocation.WriteString("Result", result);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoDestroyObject(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string objectID = invocation.ReadString("ObjectID");
            self.DestroyObject(aVersion, objectID);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoUpdateObject(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string objectID = invocation.ReadString("ObjectID");
            string currentTagValue = invocation.ReadString("CurrentTagValue");
            string newTagValue = invocation.ReadString("NewTagValue");
            self.UpdateObject(aVersion, objectID, currentTagValue, newTagValue);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoImportResource(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sourceURI = invocation.ReadString("SourceURI");
            string destinationURI = invocation.ReadString("DestinationURI");
            uint transferID;
            self.ImportResource(aVersion, sourceURI, destinationURI, out transferID);
            invocation.WriteStart();
            invocation.WriteUint("TransferID", transferID);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoExportResource(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string sourceURI = invocation.ReadString("SourceURI");
            string destinationURI = invocation.ReadString("DestinationURI");
            uint transferID;
            self.ExportResource(aVersion, sourceURI, destinationURI, out transferID);
            invocation.WriteStart();
            invocation.WriteUint("TransferID", transferID);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoStopTransferResource(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint transferID = invocation.ReadUint("TransferID");
            self.StopTransferResource(aVersion, transferID);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoGetTransferProgress(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint transferID = invocation.ReadUint("TransferID");
            string transferStatus;
            string transferLength;
            string transferTotal;
            self.GetTransferProgress(aVersion, transferID, out transferStatus, out transferLength, out transferTotal);
            invocation.WriteStart();
            invocation.WriteString("TransferStatus", transferStatus);
            invocation.WriteString("TransferLength", transferLength);
            invocation.WriteString("TransferTotal", transferTotal);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoDeleteResource(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string resourceURI = invocation.ReadString("ResourceURI");
            self.DeleteResource(aVersion, resourceURI);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoCreateReference(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderUpnpOrgContentDirectory1 self = (DvProviderUpnpOrgContentDirectory1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string containerID = invocation.ReadString("ContainerID");
            string objectID = invocation.ReadString("ObjectID");
            string newID;
            self.CreateReference(aVersion, containerID, objectID, out newID);
            invocation.WriteStart();
            invocation.WriteString("NewID", newID);
            invocation.WriteEnd();
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

        ~DvProviderUpnpOrgContentDirectory1()
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

