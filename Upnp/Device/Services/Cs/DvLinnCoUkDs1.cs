using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkDs1 : IDisposable
    {

        /// <summary>
        /// Set the value of the SupportedProtocols property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySupportedProtocols(string aValue);

        /// <summary>
        /// Get a copy of the value of the SupportedProtocols property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertySupportedProtocols();

        /// <summary>
        /// Set the value of the TrackDuration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackDuration(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TrackDuration property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyTrackDuration();

        /// <summary>
        /// Set the value of the TrackBitRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackBitRate(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TrackBitRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyTrackBitRate();

        /// <summary>
        /// Set the value of the TrackLossless property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackLossless(bool aValue);

        /// <summary>
        /// Get a copy of the value of the TrackLossless property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyTrackLossless();

        /// <summary>
        /// Set the value of the TrackBitDepth property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackBitDepth(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TrackBitDepth property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyTrackBitDepth();

        /// <summary>
        /// Set the value of the TrackSampleRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackSampleRate(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TrackSampleRate property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyTrackSampleRate();

        /// <summary>
        /// Set the value of the TrackCodecName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackCodecName(string aValue);

        /// <summary>
        /// Get a copy of the value of the TrackCodecName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyTrackCodecName();

        /// <summary>
        /// Set the value of the TrackId property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTrackId(uint aValue);

        /// <summary>
        /// Get a copy of the value of the TrackId property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyTrackId();

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTransportState(string aValue);

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyTransportState();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Ds:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkDs1 : DvProvider, IDisposable, IDvProviderLinnCoUkDs1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegatePlay;
        private ActionDelegate iDelegatePause;
        private ActionDelegate iDelegateStop;
        private ActionDelegate iDelegateSeekSecondAbsolute;
        private ActionDelegate iDelegateSeekSecondRelative;
        private ActionDelegate iDelegateSeekTrackId;
        private ActionDelegate iDelegateSeekTrackAbsolute;
        private ActionDelegate iDelegateSeekTrackRelative;
        private ActionDelegate iDelegateState;
        private ActionDelegate iDelegateProtocolInfo;
        private PropertyString iPropertySupportedProtocols;
        private PropertyUint iPropertyTrackDuration;
        private PropertyUint iPropertyTrackBitRate;
        private PropertyBool iPropertyTrackLossless;
        private PropertyUint iPropertyTrackBitDepth;
        private PropertyUint iPropertyTrackSampleRate;
        private PropertyString iPropertyTrackCodecName;
        private PropertyUint iPropertyTrackId;
        private PropertyString iPropertyTransportState;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkDs1(DvDevice aDevice)
            : base(aDevice, "linn.co.uk", "Ds", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertySupportedProtocols = new PropertyString(new ParameterString("SupportedProtocols", allowedValues));
            AddProperty(iPropertySupportedProtocols);
            iPropertyTrackDuration = new PropertyUint(new ParameterUint("TrackDuration"));
            AddProperty(iPropertyTrackDuration);
            iPropertyTrackBitRate = new PropertyUint(new ParameterUint("TrackBitRate"));
            AddProperty(iPropertyTrackBitRate);
            iPropertyTrackLossless = new PropertyBool(new ParameterBool("TrackLossless"));
            AddProperty(iPropertyTrackLossless);
            iPropertyTrackBitDepth = new PropertyUint(new ParameterUint("TrackBitDepth"));
            AddProperty(iPropertyTrackBitDepth);
            iPropertyTrackSampleRate = new PropertyUint(new ParameterUint("TrackSampleRate"));
            AddProperty(iPropertyTrackSampleRate);
            iPropertyTrackCodecName = new PropertyString(new ParameterString("TrackCodecName", allowedValues));
            AddProperty(iPropertyTrackCodecName);
            iPropertyTrackId = new PropertyUint(new ParameterUint("TrackId"));
            AddProperty(iPropertyTrackId);
            allowedValues.Add("Playing");
            allowedValues.Add("Paused");
            allowedValues.Add("Stopped");
            allowedValues.Add("Buffering");
            iPropertyTransportState = new PropertyString(new ParameterString("TransportState", allowedValues));
            AddProperty(iPropertyTransportState);
            allowedValues.Clear();
        }

        /// <summary>
        /// Set the value of the SupportedProtocols property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySupportedProtocols(string aValue)
        {
            return SetPropertyString(iPropertySupportedProtocols, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SupportedProtocols property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertySupportedProtocols()
        {
            return iPropertySupportedProtocols.Value();
        }

        /// <summary>
        /// Set the value of the TrackDuration property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackDuration(uint aValue)
        {
            return SetPropertyUint(iPropertyTrackDuration, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackDuration property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTrackDuration()
        {
            return iPropertyTrackDuration.Value();
        }

        /// <summary>
        /// Set the value of the TrackBitRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackBitRate(uint aValue)
        {
            return SetPropertyUint(iPropertyTrackBitRate, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackBitRate property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTrackBitRate()
        {
            return iPropertyTrackBitRate.Value();
        }

        /// <summary>
        /// Set the value of the TrackLossless property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackLossless(bool aValue)
        {
            return SetPropertyBool(iPropertyTrackLossless, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackLossless property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyTrackLossless()
        {
            return iPropertyTrackLossless.Value();
        }

        /// <summary>
        /// Set the value of the TrackBitDepth property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackBitDepth(uint aValue)
        {
            return SetPropertyUint(iPropertyTrackBitDepth, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackBitDepth property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTrackBitDepth()
        {
            return iPropertyTrackBitDepth.Value();
        }

        /// <summary>
        /// Set the value of the TrackSampleRate property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackSampleRate(uint aValue)
        {
            return SetPropertyUint(iPropertyTrackSampleRate, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackSampleRate property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTrackSampleRate()
        {
            return iPropertyTrackSampleRate.Value();
        }

        /// <summary>
        /// Set the value of the TrackCodecName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackCodecName(string aValue)
        {
            return SetPropertyString(iPropertyTrackCodecName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackCodecName property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyTrackCodecName()
        {
            return iPropertyTrackCodecName.Value();
        }

        /// <summary>
        /// Set the value of the TrackId property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTrackId(uint aValue)
        {
            return SetPropertyUint(iPropertyTrackId, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TrackId property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyTrackId()
        {
            return iPropertyTrackId.Value();
        }

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyTransportState(string aValue)
        {
            return SetPropertyString(iPropertyTransportState, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyTransportState()
        {
            return iPropertyTransportState.Value();
        }

        /// <summary>
        /// Signal that the action Play is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Play must be overridden if this is called.</remarks>
        protected void EnableActionPlay()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Play");
            iDelegatePlay = new ActionDelegate(DoPlay);
            EnableAction(action, iDelegatePlay, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Pause is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Pause must be overridden if this is called.</remarks>
        protected void EnableActionPause()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Pause");
            iDelegatePause = new ActionDelegate(DoPause);
            EnableAction(action, iDelegatePause, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Stop is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Stop must be overridden if this is called.</remarks>
        protected void EnableActionStop()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Stop");
            iDelegateStop = new ActionDelegate(DoStop);
            EnableAction(action, iDelegateStop, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekSecondAbsolute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SeekSecondAbsolute must be overridden if this is called.</remarks>
        protected void EnableActionSeekSecondAbsolute()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SeekSecondAbsolute");
            action.AddInputParameter(new ParameterUint("aSecond"));
            iDelegateSeekSecondAbsolute = new ActionDelegate(DoSeekSecondAbsolute);
            EnableAction(action, iDelegateSeekSecondAbsolute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekSecondRelative is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SeekSecondRelative must be overridden if this is called.</remarks>
        protected void EnableActionSeekSecondRelative()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SeekSecondRelative");
            action.AddInputParameter(new ParameterInt("aSecond"));
            iDelegateSeekSecondRelative = new ActionDelegate(DoSeekSecondRelative);
            EnableAction(action, iDelegateSeekSecondRelative, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekTrackId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SeekTrackId must be overridden if this is called.</remarks>
        protected void EnableActionSeekTrackId()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SeekTrackId");
            action.AddInputParameter(new ParameterRelated("aTrackId", iPropertyTrackId));
            iDelegateSeekTrackId = new ActionDelegate(DoSeekTrackId);
            EnableAction(action, iDelegateSeekTrackId, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekTrackAbsolute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SeekTrackAbsolute must be overridden if this is called.</remarks>
        protected void EnableActionSeekTrackAbsolute()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SeekTrackAbsolute");
            action.AddInputParameter(new ParameterUint("aTrack"));
            iDelegateSeekTrackAbsolute = new ActionDelegate(DoSeekTrackAbsolute);
            EnableAction(action, iDelegateSeekTrackAbsolute, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SeekTrackRelative is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SeekTrackRelative must be overridden if this is called.</remarks>
        protected void EnableActionSeekTrackRelative()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SeekTrackRelative");
            action.AddInputParameter(new ParameterInt("aTrack"));
            iDelegateSeekTrackRelative = new ActionDelegate(DoSeekTrackRelative);
            EnableAction(action, iDelegateSeekTrackRelative, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action State is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// State must be overridden if this is called.</remarks>
        protected void EnableActionState()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("State");
            action.AddOutputParameter(new ParameterRelated("aTransportState", iPropertyTransportState));
            action.AddOutputParameter(new ParameterRelated("aTrackDuration", iPropertyTrackDuration));
            action.AddOutputParameter(new ParameterRelated("aTrackBitRate", iPropertyTrackBitRate));
            action.AddOutputParameter(new ParameterRelated("aTrackLossless", iPropertyTrackLossless));
            action.AddOutputParameter(new ParameterRelated("aTrackBitDepth", iPropertyTrackBitDepth));
            action.AddOutputParameter(new ParameterRelated("aTrackSampleRate", iPropertyTrackSampleRate));
            action.AddOutputParameter(new ParameterRelated("aTrackCodecName", iPropertyTrackCodecName));
            action.AddOutputParameter(new ParameterRelated("aTrackId", iPropertyTrackId));
            iDelegateState = new ActionDelegate(DoState);
            EnableAction(action, iDelegateState, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ProtocolInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ProtocolInfo must be overridden if this is called.</remarks>
        protected void EnableActionProtocolInfo()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ProtocolInfo");
            action.AddOutputParameter(new ParameterRelated("aSupportedProtocols", iPropertySupportedProtocols));
            iDelegateProtocolInfo = new ActionDelegate(DoProtocolInfo);
            EnableAction(action, iDelegateProtocolInfo, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Play action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Play action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlay was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Play(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Pause action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Pause action for the owning device.
        ///
        /// Must be implemented iff EnableActionPause was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Pause(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Stop action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Stop action for the owning device.
        ///
        /// Must be implemented iff EnableActionStop was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Stop(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekSecondAbsolute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekSecondAbsolute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekSecondAbsolute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSecond"></param>
        protected virtual void SeekSecondAbsolute(uint aVersion, uint aaSecond)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekSecondRelative action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekSecondRelative action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekSecondRelative was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSecond"></param>
        protected virtual void SeekSecondRelative(uint aVersion, int aaSecond)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekTrackId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekTrackId action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekTrackId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrackId"></param>
        protected virtual void SeekTrackId(uint aVersion, uint aaTrackId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekTrackAbsolute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekTrackAbsolute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekTrackAbsolute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrack"></param>
        protected virtual void SeekTrackAbsolute(uint aVersion, uint aaTrack)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekTrackRelative action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekTrackRelative action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekTrackRelative was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTrack"></param>
        protected virtual void SeekTrackRelative(uint aVersion, int aaTrack)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// State action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// State action for the owning device.
        ///
        /// Must be implemented iff EnableActionState was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaTransportState"></param>
        /// <param name="aaTrackDuration"></param>
        /// <param name="aaTrackBitRate"></param>
        /// <param name="aaTrackLossless"></param>
        /// <param name="aaTrackBitDepth"></param>
        /// <param name="aaTrackSampleRate"></param>
        /// <param name="aaTrackCodecName"></param>
        /// <param name="aaTrackId"></param>
        protected virtual void State(uint aVersion, out string aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out string aaTrackCodecName, out uint aaTrackId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ProtocolInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ProtocolInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionProtocolInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSupportedProtocols"></param>
        protected virtual void ProtocolInfo(uint aVersion, out string aaSupportedProtocols)
        {
            throw (new ActionDisabledError());
        }

        private static int DoPlay(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Play(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoPause(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Pause(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoStop(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Stop(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSeekSecondAbsolute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aSecond;
            try
            {
                invocation.ReadStart();
                aSecond = invocation.ReadUint("aSecond");
                invocation.ReadEnd();
                self.SeekSecondAbsolute(aVersion, aSecond);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSeekSecondRelative(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int aSecond;
            try
            {
                invocation.ReadStart();
                aSecond = invocation.ReadInt("aSecond");
                invocation.ReadEnd();
                self.SeekSecondRelative(aVersion, aSecond);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSeekTrackId(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aTrackId;
            try
            {
                invocation.ReadStart();
                aTrackId = invocation.ReadUint("aTrackId");
                invocation.ReadEnd();
                self.SeekTrackId(aVersion, aTrackId);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSeekTrackAbsolute(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aTrack;
            try
            {
                invocation.ReadStart();
                aTrack = invocation.ReadUint("aTrack");
                invocation.ReadEnd();
                self.SeekTrackAbsolute(aVersion, aTrack);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSeekTrackRelative(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int aTrack;
            try
            {
                invocation.ReadStart();
                aTrack = invocation.ReadInt("aTrack");
                invocation.ReadEnd();
                self.SeekTrackRelative(aVersion, aTrack);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
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
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoState(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aTransportState;
            uint aTrackDuration;
            uint aTrackBitRate;
            bool aTrackLossless;
            uint aTrackBitDepth;
            uint aTrackSampleRate;
            string aTrackCodecName;
            uint aTrackId;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.State(aVersion, out aTransportState, out aTrackDuration, out aTrackBitRate, out aTrackLossless, out aTrackBitDepth, out aTrackSampleRate, out aTrackCodecName, out aTrackId);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aTransportState", aTransportState);
                invocation.WriteUint("aTrackDuration", aTrackDuration);
                invocation.WriteUint("aTrackBitRate", aTrackBitRate);
                invocation.WriteBool("aTrackLossless", aTrackLossless);
                invocation.WriteUint("aTrackBitDepth", aTrackBitDepth);
                invocation.WriteUint("aTrackSampleRate", aTrackSampleRate);
                invocation.WriteString("aTrackCodecName", aTrackCodecName);
                invocation.WriteUint("aTrackId", aTrackId);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoProtocolInfo(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDs1 self = (DvProviderLinnCoUkDs1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string aSupportedProtocols;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ProtocolInfo(aVersion, out aSupportedProtocols);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("aSupportedProtocols", aSupportedProtocols);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkDs1()
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

