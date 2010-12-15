using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkJukebox1 : IDisposable
    {

        /// <summary>
        /// Set the value of the CurrentPreset property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyCurrentPreset(uint aValue);

        /// <summary>
        /// Get a copy of the value of the CurrentPreset property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyCurrentPreset();

        /// <summary>
        /// Set the value of the PresetPrefix property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyPresetPrefix(string aValue);

        /// <summary>
        /// Get a copy of the value of the PresetPrefix property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyPresetPrefix();

        /// <summary>
        /// Set the value of the AlbumArtFileName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyAlbumArtFileName(string aValue);

        /// <summary>
        /// Get a copy of the value of the AlbumArtFileName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyAlbumArtFileName();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Jukebox:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkJukebox1 : DvProvider, IDisposable, IDvProviderLinnCoUkJukebox1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSetPresetPrefix;
        private ActionDelegate iDelegatePresetPrefix;
        private ActionDelegate iDelegateSetAlbumArtFileName;
        private ActionDelegate iDelegateAlbumArtFileName;
        private ActionDelegate iDelegateSetCurrentPreset;
        private ActionDelegate iDelegateCurrentPreset;
        private ActionDelegate iDelegatePresetMetaData;
        private ActionDelegate iDelegateLoadManifest;
        private PropertyUint iPropertyCurrentPreset;
        private PropertyString iPropertyPresetPrefix;
        private PropertyString iPropertyAlbumArtFileName;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkJukebox1(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Jukebox", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyCurrentPreset = new PropertyUint(new ParameterUint("CurrentPreset"));
            AddProperty(iPropertyCurrentPreset);
            iPropertyPresetPrefix = new PropertyString(new ParameterString("PresetPrefix", allowedValues));
            AddProperty(iPropertyPresetPrefix);
            iPropertyAlbumArtFileName = new PropertyString(new ParameterString("AlbumArtFileName", allowedValues));
            AddProperty(iPropertyAlbumArtFileName);
        }

        /// <summary>
        /// Set the value of the CurrentPreset property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyCurrentPreset(uint aValue)
        {
            return SetPropertyUint(iPropertyCurrentPreset, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the CurrentPreset property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyCurrentPreset()
        {
            return iPropertyCurrentPreset.Value();
        }

        /// <summary>
        /// Set the value of the PresetPrefix property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyPresetPrefix(string aValue)
        {
            return SetPropertyString(iPropertyPresetPrefix, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the PresetPrefix property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyPresetPrefix()
        {
            return iPropertyPresetPrefix.Value();
        }

        /// <summary>
        /// Set the value of the AlbumArtFileName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyAlbumArtFileName(string aValue)
        {
            return SetPropertyString(iPropertyAlbumArtFileName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the AlbumArtFileName property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyAlbumArtFileName()
        {
            return iPropertyAlbumArtFileName.Value();
        }

        /// <summary>
        /// Signal that the action SetPresetPrefix is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetPresetPrefix must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetPresetPrefix()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetPresetPrefix");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aUri", iPropertyPresetPrefix));
            iDelegateSetPresetPrefix = new ActionDelegate(DoSetPresetPrefix);
            EnableAction(action, iDelegateSetPresetPrefix, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PresetPrefix is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPresetPrefix must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPresetPrefix()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("PresetPrefix");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterRelated("aUri", iPropertyPresetPrefix));
            iDelegatePresetPrefix = new ActionDelegate(DoPresetPrefix);
            EnableAction(action, iDelegatePresetPrefix, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetAlbumArtFileName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetAlbumArtFileName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetAlbumArtFileName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetAlbumArtFileName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aName", iPropertyAlbumArtFileName));
            iDelegateSetAlbumArtFileName = new ActionDelegate(DoSetAlbumArtFileName);
            EnableAction(action, iDelegateSetAlbumArtFileName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action AlbumArtFileName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoAlbumArtFileName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionAlbumArtFileName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("AlbumArtFileName");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterRelated("aName", iPropertyAlbumArtFileName));
            iDelegateAlbumArtFileName = new ActionDelegate(DoAlbumArtFileName);
            EnableAction(action, iDelegateAlbumArtFileName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetCurrentPreset is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetCurrentPreset must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetCurrentPreset()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetCurrentPreset");
            action.AddInputParameter(new ParameterRelated("aPreset", iPropertyCurrentPreset));
            iDelegateSetCurrentPreset = new ActionDelegate(DoSetCurrentPreset);
            EnableAction(action, iDelegateSetCurrentPreset, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action CurrentPreset is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoCurrentPreset must be overridden if this is called.</remarks>
        protected unsafe void EnableActionCurrentPreset()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("CurrentPreset");
            action.AddOutputParameter(new ParameterRelated("aPreset", iPropertyCurrentPreset));
            iDelegateCurrentPreset = new ActionDelegate(DoCurrentPreset);
            EnableAction(action, iDelegateCurrentPreset, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action PresetMetaData is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPresetMetaData must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPresetMetaData()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("PresetMetaData");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aPreset", iPropertyCurrentPreset));
            action.AddOutputParameter(new ParameterString("aMetaData", allowedValues));
            iDelegatePresetMetaData = new ActionDelegate(DoPresetMetaData);
            EnableAction(action, iDelegatePresetMetaData, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action LoadManifest is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoLoadManifest must be overridden if this is called.</remarks>
        protected unsafe void EnableActionLoadManifest()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("LoadManifest");
            action.AddOutputParameter(new ParameterRelated("aTotalPresets", iPropertyCurrentPreset));
            iDelegateLoadManifest = new ActionDelegate(DoLoadManifest);
            EnableAction(action, iDelegateLoadManifest, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// SetPresetPrefix action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetPresetPrefix action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetPresetPrefix was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        protected virtual void SetPresetPrefix(uint aVersion, string aaUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PresetPrefix action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PresetPrefix action for the owning device.
        ///
        /// Must be implemented iff EnableActionPresetPrefix was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        protected virtual void PresetPrefix(uint aVersion, out string aaUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetAlbumArtFileName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetAlbumArtFileName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetAlbumArtFileName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaName"></param>
        protected virtual void SetAlbumArtFileName(uint aVersion, string aaName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// AlbumArtFileName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// AlbumArtFileName action for the owning device.
        ///
        /// Must be implemented iff EnableActionAlbumArtFileName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaName"></param>
        protected virtual void AlbumArtFileName(uint aVersion, out string aaName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetCurrentPreset action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetCurrentPreset action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetCurrentPreset was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPreset"></param>
        protected virtual void SetCurrentPreset(uint aVersion, uint aaPreset)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// CurrentPreset action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// CurrentPreset action for the owning device.
        ///
        /// Must be implemented iff EnableActionCurrentPreset was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPreset"></param>
        protected virtual void CurrentPreset(uint aVersion, out uint aaPreset)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// PresetMetaData action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// PresetMetaData action for the owning device.
        ///
        /// Must be implemented iff EnableActionPresetMetaData was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPreset"></param>
        /// <param name="aaMetaData"></param>
        protected virtual void PresetMetaData(uint aVersion, uint aaPreset, out string aaMetaData)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// LoadManifest action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// LoadManifest action for the owning device.
        ///
        /// Must be implemented iff EnableActionLoadManifest was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTotalPresets"></param>
        protected virtual void LoadManifest(uint aVersion, out uint aaTotalPresets)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetPresetPrefix(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aUri = invocation.ReadString("aUri");
            self.SetPresetPrefix(aVersion, aUri);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoPresetPrefix(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aUri;
            self.PresetPrefix(aVersion, out aUri);
            invocation.WriteStart();
            invocation.WriteString("aUri", aUri);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetAlbumArtFileName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aName = invocation.ReadString("aName");
            self.SetAlbumArtFileName(aVersion, aName);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoAlbumArtFileName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aName;
            self.AlbumArtFileName(aVersion, out aName);
            invocation.WriteStart();
            invocation.WriteString("aName", aName);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetCurrentPreset(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aPreset = invocation.ReadUint("aPreset");
            self.SetCurrentPreset(aVersion, aPreset);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoCurrentPreset(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aPreset;
            self.CurrentPreset(aVersion, out aPreset);
            invocation.WriteStart();
            invocation.WriteUint("aPreset", aPreset);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoPresetMetaData(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aPreset = invocation.ReadUint("aPreset");
            string aMetaData;
            self.PresetMetaData(aVersion, aPreset, out aMetaData);
            invocation.WriteStart();
            invocation.WriteString("aMetaData", aMetaData);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoLoadManifest(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkJukebox1 self = (DvProviderLinnCoUkJukebox1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aTotalPresets;
            self.LoadManifest(aVersion, out aTotalPresets);
            invocation.WriteStart();
            invocation.WriteUint("aTotalPresets", aTotalPresets);
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

        ~DvProviderLinnCoUkJukebox1()
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

