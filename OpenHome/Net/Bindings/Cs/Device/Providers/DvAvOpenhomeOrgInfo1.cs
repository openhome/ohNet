using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgInfo1 : IDisposable
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
        /// <returns>Value of the TrackCount property.</param>
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
        /// <returns>Value of the DetailsCount property.</param>
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
        /// <returns>Value of the MetatextCount property.</param>
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
        /// <returns>Value of the Uri property.</param>
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
        /// <returns>Value of the Metadata property.</param>
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
        /// <returns>Value of the Duration property.</param>
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
        /// <returns>Value of the BitRate property.</param>
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
        /// <returns>Value of the BitDepth property.</param>
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
        /// <returns>Value of the SampleRate property.</param>
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
        /// <returns>Value of the Lossless property.</param>
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
        /// <returns>Value of the CodecName property.</param>
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
        /// <returns>Value of the Metatext property.</param>
        string PropertyMetatext();
        
    }
    /// <summary>
    /// Provider for the av.openhome.org:Info:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgInfo1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgInfo1
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
        protected DvProviderAvOpenhomeOrgInfo1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "Info", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the TrackCount property.
        /// </summary>
        public void EnablePropertyTrackCount()
        {
            iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
            AddProperty(iPropertyTrackCount);
        }

        /// <summary>
        /// Enable the DetailsCount property.
        /// </summary>
        public void EnablePropertyDetailsCount()
        {
            iPropertyDetailsCount = new PropertyUint(new ParameterUint("DetailsCount"));
            AddProperty(iPropertyDetailsCount);
        }

        /// <summary>
        /// Enable the MetatextCount property.
        /// </summary>
        public void EnablePropertyMetatextCount()
        {
            iPropertyMetatextCount = new PropertyUint(new ParameterUint("MetatextCount"));
            AddProperty(iPropertyMetatextCount);
        }

        /// <summary>
        /// Enable the Uri property.
        /// </summary>
        public void EnablePropertyUri()
        {
            List<String> allowedValues = new List<String>();
            iPropertyUri = new PropertyString(new ParameterString("Uri", allowedValues));
            AddProperty(iPropertyUri);
        }

        /// <summary>
        /// Enable the Metadata property.
        /// </summary>
        public void EnablePropertyMetadata()
        {
            List<String> allowedValues = new List<String>();
            iPropertyMetadata = new PropertyString(new ParameterString("Metadata", allowedValues));
            AddProperty(iPropertyMetadata);
        }

        /// <summary>
        /// Enable the Duration property.
        /// </summary>
        public void EnablePropertyDuration()
        {
            iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
            AddProperty(iPropertyDuration);
        }

        /// <summary>
        /// Enable the BitRate property.
        /// </summary>
        public void EnablePropertyBitRate()
        {
            iPropertyBitRate = new PropertyUint(new ParameterUint("BitRate"));
            AddProperty(iPropertyBitRate);
        }

        /// <summary>
        /// Enable the BitDepth property.
        /// </summary>
        public void EnablePropertyBitDepth()
        {
            iPropertyBitDepth = new PropertyUint(new ParameterUint("BitDepth"));
            AddProperty(iPropertyBitDepth);
        }

        /// <summary>
        /// Enable the SampleRate property.
        /// </summary>
        public void EnablePropertySampleRate()
        {
            iPropertySampleRate = new PropertyUint(new ParameterUint("SampleRate"));
            AddProperty(iPropertySampleRate);
        }

        /// <summary>
        /// Enable the Lossless property.
        /// </summary>
        public void EnablePropertyLossless()
        {
            iPropertyLossless = new PropertyBool(new ParameterBool("Lossless"));
            AddProperty(iPropertyLossless);
        }

        /// <summary>
        /// Enable the CodecName property.
        /// </summary>
        public void EnablePropertyCodecName()
        {
            List<String> allowedValues = new List<String>();
            iPropertyCodecName = new PropertyString(new ParameterString("CodecName", allowedValues));
            AddProperty(iPropertyCodecName);
        }

        /// <summary>
        /// Enable the Metatext property.
        /// </summary>
        public void EnablePropertyMetatext()
        {
            List<String> allowedValues = new List<String>();
            iPropertyMetatext = new PropertyString(new ParameterString("Metatext", allowedValues));
            AddProperty(iPropertyMetatext);
        }

        /// <summary>
        /// Set the value of the TrackCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTrackCount has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackCount(uint aValue)
        {
            if (iPropertyTrackCount == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyTrackCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyTrackCount has previously been called.</remarks>
        /// <returns>Value of the TrackCount property.</returns>
        public uint PropertyTrackCount()
        {
            if (iPropertyTrackCount == null)
                throw new PropertyDisabledError();
            return iPropertyTrackCount.Value();
        }

        /// <summary>
        /// Set the value of the DetailsCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyDetailsCount has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDetailsCount(uint aValue)
        {
            if (iPropertyDetailsCount == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyDetailsCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the DetailsCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyDetailsCount has previously been called.</remarks>
        /// <returns>Value of the DetailsCount property.</returns>
        public uint PropertyDetailsCount()
        {
            if (iPropertyDetailsCount == null)
                throw new PropertyDisabledError();
            return iPropertyDetailsCount.Value();
        }

        /// <summary>
        /// Set the value of the MetatextCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetatextCount has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetatextCount(uint aValue)
        {
            if (iPropertyMetatextCount == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyMetatextCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the MetatextCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetatextCount has previously been called.</remarks>
        /// <returns>Value of the MetatextCount property.</returns>
        public uint PropertyMetatextCount()
        {
            if (iPropertyMetatextCount == null)
                throw new PropertyDisabledError();
            return iPropertyMetatextCount.Value();
        }

        /// <summary>
        /// Set the value of the Uri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyUri has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyUri(string aValue)
        {
            if (iPropertyUri == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Uri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyUri has previously been called.</remarks>
        /// <returns>Value of the Uri property.</returns>
        public string PropertyUri()
        {
            if (iPropertyUri == null)
                throw new PropertyDisabledError();
            return iPropertyUri.Value();
        }

        /// <summary>
        /// Set the value of the Metadata property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetadata has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetadata(string aValue)
        {
            if (iPropertyMetadata == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyMetadata, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Metadata property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetadata has previously been called.</remarks>
        /// <returns>Value of the Metadata property.</returns>
        public string PropertyMetadata()
        {
            if (iPropertyMetadata == null)
                throw new PropertyDisabledError();
            return iPropertyMetadata.Value();
        }

        /// <summary>
        /// Set the value of the Duration property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyDuration has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyDuration(uint aValue)
        {
            if (iPropertyDuration == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyDuration, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Duration property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyDuration has previously been called.</remarks>
        /// <returns>Value of the Duration property.</returns>
        public uint PropertyDuration()
        {
            if (iPropertyDuration == null)
                throw new PropertyDisabledError();
            return iPropertyDuration.Value();
        }

        /// <summary>
        /// Set the value of the BitRate property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyBitRate has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyBitRate(uint aValue)
        {
            if (iPropertyBitRate == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyBitRate, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the BitRate property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyBitRate has previously been called.</remarks>
        /// <returns>Value of the BitRate property.</returns>
        public uint PropertyBitRate()
        {
            if (iPropertyBitRate == null)
                throw new PropertyDisabledError();
            return iPropertyBitRate.Value();
        }

        /// <summary>
        /// Set the value of the BitDepth property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyBitDepth has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyBitDepth(uint aValue)
        {
            if (iPropertyBitDepth == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyBitDepth, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the BitDepth property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyBitDepth has previously been called.</remarks>
        /// <returns>Value of the BitDepth property.</returns>
        public uint PropertyBitDepth()
        {
            if (iPropertyBitDepth == null)
                throw new PropertyDisabledError();
            return iPropertyBitDepth.Value();
        }

        /// <summary>
        /// Set the value of the SampleRate property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySampleRate has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySampleRate(uint aValue)
        {
            if (iPropertySampleRate == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertySampleRate, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SampleRate property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySampleRate has previously been called.</remarks>
        /// <returns>Value of the SampleRate property.</returns>
        public uint PropertySampleRate()
        {
            if (iPropertySampleRate == null)
                throw new PropertyDisabledError();
            return iPropertySampleRate.Value();
        }

        /// <summary>
        /// Set the value of the Lossless property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyLossless has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyLossless(bool aValue)
        {
            if (iPropertyLossless == null)
                throw new PropertyDisabledError();
            return SetPropertyBool(iPropertyLossless, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Lossless property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyLossless has previously been called.</remarks>
        /// <returns>Value of the Lossless property.</returns>
        public bool PropertyLossless()
        {
            if (iPropertyLossless == null)
                throw new PropertyDisabledError();
            return iPropertyLossless.Value();
        }

        /// <summary>
        /// Set the value of the CodecName property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyCodecName has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyCodecName(string aValue)
        {
            if (iPropertyCodecName == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyCodecName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the CodecName property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyCodecName has previously been called.</remarks>
        /// <returns>Value of the CodecName property.</returns>
        public string PropertyCodecName()
        {
            if (iPropertyCodecName == null)
                throw new PropertyDisabledError();
            return iPropertyCodecName.Value();
        }

        /// <summary>
        /// Set the value of the Metatext property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetatext has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyMetatext(string aValue)
        {
            if (iPropertyMetatext == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyMetatext, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Metatext property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyMetatext has previously been called.</remarks>
        /// <returns>Value of the Metatext property.</returns>
        public string PropertyMetatext()
        {
            if (iPropertyMetatext == null)
                throw new PropertyDisabledError();
            return iPropertyMetatext.Value();
        }

        /// <summary>
        /// Signal that the action Counters is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Counters must be overridden if this is called.</remarks>
        protected void EnableActionCounters()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Counters");
            action.AddOutputParameter(new ParameterRelated("TrackCount", iPropertyTrackCount));
            action.AddOutputParameter(new ParameterRelated("DetailsCount", iPropertyDetailsCount));
            action.AddOutputParameter(new ParameterRelated("MetatextCount", iPropertyMetatextCount));
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Track");
            action.AddOutputParameter(new ParameterRelated("Uri", iPropertyUri));
            action.AddOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Details");
            action.AddOutputParameter(new ParameterRelated("Duration", iPropertyDuration));
            action.AddOutputParameter(new ParameterRelated("BitRate", iPropertyBitRate));
            action.AddOutputParameter(new ParameterRelated("BitDepth", iPropertyBitDepth));
            action.AddOutputParameter(new ParameterRelated("SampleRate", iPropertySampleRate));
            action.AddOutputParameter(new ParameterRelated("Lossless", iPropertyLossless));
            action.AddOutputParameter(new ParameterRelated("CodecName", iPropertyCodecName));
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Metatext");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyMetatext));
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aTrackCount"></param>
        /// <param name="aDetailsCount"></param>
        /// <param name="aMetatextCount"></param>
        protected virtual void Counters(IDvInvocation aInvocation, out uint aTrackCount, out uint aDetailsCount, out uint aMetatextCount)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        protected virtual void Track(IDvInvocation aInvocation, out string aUri, out string aMetadata)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aDuration"></param>
        /// <param name="aBitRate"></param>
        /// <param name="aBitDepth"></param>
        /// <param name="aSampleRate"></param>
        /// <param name="aLossless"></param>
        /// <param name="aCodecName"></param>
        protected virtual void Details(IDvInvocation aInvocation, out uint aDuration, out uint aBitRate, out uint aBitDepth, out uint aSampleRate, out bool aLossless, out string aCodecName)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Metatext(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        private static int DoCounters(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgInfo1 self = (DvProviderAvOpenhomeOrgInfo1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint trackCount;
            uint detailsCount;
            uint metatextCount;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Counters(invocation, out trackCount, out detailsCount, out metatextCount);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Counters");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Counters"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Counters", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("TrackCount", trackCount);
                invocation.WriteUint("DetailsCount", detailsCount);
                invocation.WriteUint("MetatextCount", metatextCount);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Counters", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoTrack(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgInfo1 self = (DvProviderAvOpenhomeOrgInfo1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string uri;
            string metadata;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Track(invocation, out uri, out metadata);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Track");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Track"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Track", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Uri", uri);
                invocation.WriteString("Metadata", metadata);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Track", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoDetails(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgInfo1 self = (DvProviderAvOpenhomeOrgInfo1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint duration;
            uint bitRate;
            uint bitDepth;
            uint sampleRate;
            bool lossless;
            string codecName;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Details(invocation, out duration, out bitRate, out bitDepth, out sampleRate, out lossless, out codecName);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Details");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Details"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Details", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Duration", duration);
                invocation.WriteUint("BitRate", bitRate);
                invocation.WriteUint("BitDepth", bitDepth);
                invocation.WriteUint("SampleRate", sampleRate);
                invocation.WriteBool("Lossless", lossless);
                invocation.WriteString("CodecName", codecName);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Details", e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoMetatext(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgInfo1 self = (DvProviderAvOpenhomeOrgInfo1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Metatext(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Metatext");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", "Metatext"));
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Metatext", e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2} in {3}", e.GetType(), e.Message, "Metatext", e.TargetSite.Name);
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

