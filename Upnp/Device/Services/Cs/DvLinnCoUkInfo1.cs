using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkInfo1 : IDisposable
    {

        /// <summary>
        /// Set the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackCount(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyTrackCount();

        /// <summary>
        /// Set the value of the DetailsCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDetailsCount(uint aValue);

        /// <summary>
        /// Get a copy of the value of the DetailsCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyDetailsCount();

        /// <summary>
        /// Set the value of the MetatextCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyMetatextCount(uint aValue);

        /// <summary>
        /// Get a copy of the value of the MetatextCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyMetatextCount();

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyUri(string aValue);

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyUri();

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyMetadata(string aValue);

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyMetadata();

        /// <summary>
        /// Set the value of the Duration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyDuration(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Duration property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyDuration();

        /// <summary>
        /// Set the value of the BitRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyBitRate(uint aValue);

        /// <summary>
        /// Get a copy of the value of the BitRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyBitRate();

        /// <summary>
        /// Set the value of the BitDepth property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyBitDepth(uint aValue);

        /// <summary>
        /// Get a copy of the value of the BitDepth property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyBitDepth();

        /// <summary>
        /// Set the value of the SampleRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySampleRate(uint aValue);

        /// <summary>
        /// Get a copy of the value of the SampleRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertySampleRate();

        /// <summary>
        /// Set the value of the Lossless property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyLossless(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Lossless property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyLossless();

        /// <summary>
        /// Set the value of the CodecName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyCodecName(string aValue);

        /// <summary>
        /// Get a copy of the value of the CodecName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyCodecName();

        /// <summary>
        /// Set the value of the Metatext property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyMetatext(string aValue);

        /// <summary>
        /// Get a copy of the value of the Metatext property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyMetatext();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Info:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkInfo1 : DvProvider, IDisposable, IDvProviderLinnCoUkInfo1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateCounters;
        private ActionDelegate iDelegateTrack;
        private ActionDelegate iDelegateDetails;
        private ActionDelegate iDelegateMetatext;
        private PropertyUint iPropertyTrackCount;
        private PropertyUint iPropertyDetailsCount;
        private PropertyUint iPropertyMetatextCount;
        private PropertyString iPropertyUri;
        private PropertyString iPropertyMetadata;
        private PropertyUint iPropertyDuration;
        private PropertyUint iPropertyBitRate;
        private PropertyUint iPropertyBitDepth;
        private PropertyUint iPropertySampleRate;
        private PropertyBool iPropertyLossless;
        private PropertyString iPropertyCodecName;
        private PropertyString iPropertyMetatext;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkInfo1(DvDevice aDevice)
            : base(aDevice, "linn.co.uk", "Info", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
            AddProperty(iPropertyTrackCount);
            iPropertyDetailsCount = new PropertyUint(new ParameterUint("DetailsCount"));
            AddProperty(iPropertyDetailsCount);
            iPropertyMetatextCount = new PropertyUint(new ParameterUint("MetatextCount"));
            AddProperty(iPropertyMetatextCount);
            iPropertyUri = new PropertyString(new ParameterString("Uri", allowedValues));
            AddProperty(iPropertyUri);
            iPropertyMetadata = new PropertyString(new ParameterString("Metadata", allowedValues));
            AddProperty(iPropertyMetadata);
            iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
            AddProperty(iPropertyDuration);
            iPropertyBitRate = new PropertyUint(new ParameterUint("BitRate"));
            AddProperty(iPropertyBitRate);
            iPropertyBitDepth = new PropertyUint(new ParameterUint("BitDepth"));
            AddProperty(iPropertyBitDepth);
            iPropertySampleRate = new PropertyUint(new ParameterUint("SampleRate"));
            AddProperty(iPropertySampleRate);
            iPropertyLossless = new PropertyBool(new ParameterBool("Lossless"));
            AddProperty(iPropertyLossless);
            iPropertyCodecName = new PropertyString(new ParameterString("CodecName", allowedValues));
            AddProperty(iPropertyCodecName);
            iPropertyMetatext = new PropertyString(new ParameterString("Metatext", allowedValues));
            AddProperty(iPropertyMetatext);
        }

        /// <summary>
        /// Set the value of the TrackCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackCount(uint aValue)
        {
            return SetPropertyUint(iPropertyTrackCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackCount property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTrackCount()
        {
            return iPropertyTrackCount.Value();
        }

        /// <summary>
        /// Set the value of the DetailsCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDetailsCount(uint aValue)
        {
            return SetPropertyUint(iPropertyDetailsCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DetailsCount property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyDetailsCount()
        {
            return iPropertyDetailsCount.Value();
        }

        /// <summary>
        /// Set the value of the MetatextCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetatextCount(uint aValue)
        {
            return SetPropertyUint(iPropertyMetatextCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the MetatextCount property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyMetatextCount()
        {
            return iPropertyMetatextCount.Value();
        }

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyUri(string aValue)
        {
            return SetPropertyString(iPropertyUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyUri()
        {
            return iPropertyUri.Value();
        }

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetadata(string aValue)
        {
            return SetPropertyString(iPropertyMetadata, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyMetadata()
        {
            return iPropertyMetadata.Value();
        }

        /// <summary>
        /// Set the value of the Duration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDuration(uint aValue)
        {
            return SetPropertyUint(iPropertyDuration, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Duration property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyDuration()
        {
            return iPropertyDuration.Value();
        }

        /// <summary>
        /// Set the value of the BitRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyBitRate(uint aValue)
        {
            return SetPropertyUint(iPropertyBitRate, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the BitRate property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyBitRate()
        {
            return iPropertyBitRate.Value();
        }

        /// <summary>
        /// Set the value of the BitDepth property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyBitDepth(uint aValue)
        {
            return SetPropertyUint(iPropertyBitDepth, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the BitDepth property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyBitDepth()
        {
            return iPropertyBitDepth.Value();
        }

        /// <summary>
        /// Set the value of the SampleRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySampleRate(uint aValue)
        {
            return SetPropertyUint(iPropertySampleRate, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SampleRate property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertySampleRate()
        {
            return iPropertySampleRate.Value();
        }

        /// <summary>
        /// Set the value of the Lossless property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLossless(bool aValue)
        {
            return SetPropertyBool(iPropertyLossless, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Lossless property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyLossless()
        {
            return iPropertyLossless.Value();
        }

        /// <summary>
        /// Set the value of the CodecName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyCodecName(string aValue)
        {
            return SetPropertyString(iPropertyCodecName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the CodecName property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyCodecName()
        {
            return iPropertyCodecName.Value();
        }

        /// <summary>
        /// Set the value of the Metatext property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetatext(string aValue)
        {
            return SetPropertyString(iPropertyMetatext, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Metatext property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyMetatext()
        {
            return iPropertyMetatext.Value();
        }

        /// <summary>
        /// Signal that the action Counters is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Counters must be overridden if this is called.</remarks>
        protected void EnableActionCounters()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Counters");
            action.AddOutputParameter(new ParameterRelated("aTrackCount", iPropertyTrackCount));
            action.AddOutputParameter(new ParameterRelated("aDetailsCount", iPropertyDetailsCount));
            action.AddOutputParameter(new ParameterRelated("aMetatextCount", iPropertyMetatextCount));
            iDelegateCounters = new ActionDelegate(DoCounters);
            EnableAction(action, iDelegateCounters, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Track is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Track must be overridden if this is called.</remarks>
        protected void EnableActionTrack()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Track");
            action.AddOutputParameter(new ParameterRelated("aUri", iPropertyUri));
            action.AddOutputParameter(new ParameterRelated("aMetadata", iPropertyMetadata));
            iDelegateTrack = new ActionDelegate(DoTrack);
            EnableAction(action, iDelegateTrack, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Details is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Details must be overridden if this is called.</remarks>
        protected void EnableActionDetails()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Details");
            action.AddOutputParameter(new ParameterRelated("aDuration", iPropertyDuration));
            action.AddOutputParameter(new ParameterRelated("aBitRate", iPropertyBitRate));
            action.AddOutputParameter(new ParameterRelated("aBitDepth", iPropertyBitDepth));
            action.AddOutputParameter(new ParameterRelated("aSampleRate", iPropertySampleRate));
            action.AddOutputParameter(new ParameterRelated("aLossless", iPropertyLossless));
            action.AddOutputParameter(new ParameterRelated("aCodecName", iPropertyCodecName));
            iDelegateDetails = new ActionDelegate(DoDetails);
            EnableAction(action, iDelegateDetails, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Metatext is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Metatext must be overridden if this is called.</remarks>
        protected void EnableActionMetatext()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Metatext");
            action.AddOutputParameter(new ParameterRelated("aMetatext", iPropertyMetatext));
            iDelegateMetatext = new ActionDelegate(DoMetatext);
            EnableAction(action, iDelegateMetatext, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Counters action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Counters action for the owning device.
        ///
        /// Must be implemented iff EnableActionCounters was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDetailsCount"></param>
        /// <param name="aaMetatextCount"></param>
        protected virtual void Counters(uint aVersion, out uint aaTrackCount, out uint aaDetailsCount, out uint aaMetatextCount)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Track action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Track action for the owning device.
        ///
        /// Must be implemented iff EnableActionTrack was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        protected virtual void Track(uint aVersion, out string aaUri, out string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Details action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Details action for the owning device.
        ///
        /// Must be implemented iff EnableActionDetails was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDuration"></param>
        /// <param name="aaBitRate"></param>
        /// <param name="aaBitDepth"></param>
        /// <param name="aaSampleRate"></param>
        /// <param name="aaLossless"></param>
        /// <param name="aaCodecName"></param>
        protected virtual void Details(uint aVersion, out uint aaDuration, out uint aaBitRate, out uint aaBitDepth, out uint aaSampleRate, out bool aaLossless, out string aaCodecName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Metatext action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Metatext action for the owning device.
        ///
        /// Must be implemented iff EnableActionMetatext was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMetatext"></param>
        protected virtual void Metatext(uint aVersion, out string aaMetatext)
        {
            throw (new ActionDisabledError());
        }

        private static int DoCounters(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkInfo1 self = (DvProviderLinnCoUkInfo1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aTrackCount;
            uint aDetailsCount;
            uint aMetatextCount;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Counters(aVersion, out aTrackCount, out aDetailsCount, out aMetatextCount);
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
                invocation.WriteUint("aTrackCount", aTrackCount);
                invocation.WriteUint("aDetailsCount", aDetailsCount);
                invocation.WriteUint("aMetatextCount", aMetatextCount);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoTrack(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkInfo1 self = (DvProviderLinnCoUkInfo1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aUri;
            string aMetadata;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Track(aVersion, out aUri, out aMetadata);
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
                invocation.WriteString("aUri", aUri);
                invocation.WriteString("aMetadata", aMetadata);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDetails(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkInfo1 self = (DvProviderLinnCoUkInfo1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aDuration;
            uint aBitRate;
            uint aBitDepth;
            uint aSampleRate;
            bool aLossless;
            string aCodecName;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Details(aVersion, out aDuration, out aBitRate, out aBitDepth, out aSampleRate, out aLossless, out aCodecName);
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
                invocation.WriteUint("aDuration", aDuration);
                invocation.WriteUint("aBitRate", aBitRate);
                invocation.WriteUint("aBitDepth", aBitDepth);
                invocation.WriteUint("aSampleRate", aSampleRate);
                invocation.WriteBool("aLossless", aLossless);
                invocation.WriteString("aCodecName", aCodecName);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoMetatext(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkInfo1 self = (DvProviderLinnCoUkInfo1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aMetatext;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Metatext(aVersion, out aMetatext);
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
                invocation.WriteString("aMetatext", aMetatext);
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

        ~DvProviderLinnCoUkInfo1()
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

