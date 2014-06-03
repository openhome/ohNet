using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyAvOpenhomeOrgInfo1 : ICpProxy, IDisposable
    {
        void SyncCounters(out uint aTrackCount, out uint aDetailsCount, out uint aMetatextCount);
        void BeginCounters(CpProxy.CallbackAsyncComplete aCallback);
        void EndCounters(IntPtr aAsyncHandle, out uint aTrackCount, out uint aDetailsCount, out uint aMetatextCount);
        void SyncTrack(out String aUri, out String aMetadata);
        void BeginTrack(CpProxy.CallbackAsyncComplete aCallback);
        void EndTrack(IntPtr aAsyncHandle, out String aUri, out String aMetadata);
        void SyncDetails(out uint aDuration, out uint aBitRate, out uint aBitDepth, out uint aSampleRate, out bool aLossless, out String aCodecName);
        void BeginDetails(CpProxy.CallbackAsyncComplete aCallback);
        void EndDetails(IntPtr aAsyncHandle, out uint aDuration, out uint aBitRate, out uint aBitDepth, out uint aSampleRate, out bool aLossless, out String aCodecName);
        void SyncMetatext(out String aValue);
        void BeginMetatext(CpProxy.CallbackAsyncComplete aCallback);
        void EndMetatext(IntPtr aAsyncHandle, out String aValue);
        void SetPropertyTrackCountChanged(System.Action aTrackCountChanged);
        uint PropertyTrackCount();
        void SetPropertyDetailsCountChanged(System.Action aDetailsCountChanged);
        uint PropertyDetailsCount();
        void SetPropertyMetatextCountChanged(System.Action aMetatextCountChanged);
        uint PropertyMetatextCount();
        void SetPropertyUriChanged(System.Action aUriChanged);
        String PropertyUri();
        void SetPropertyMetadataChanged(System.Action aMetadataChanged);
        String PropertyMetadata();
        void SetPropertyDurationChanged(System.Action aDurationChanged);
        uint PropertyDuration();
        void SetPropertyBitRateChanged(System.Action aBitRateChanged);
        uint PropertyBitRate();
        void SetPropertyBitDepthChanged(System.Action aBitDepthChanged);
        uint PropertyBitDepth();
        void SetPropertySampleRateChanged(System.Action aSampleRateChanged);
        uint PropertySampleRate();
        void SetPropertyLosslessChanged(System.Action aLosslessChanged);
        bool PropertyLossless();
        void SetPropertyCodecNameChanged(System.Action aCodecNameChanged);
        String PropertyCodecName();
        void SetPropertyMetatextChanged(System.Action aMetatextChanged);
        String PropertyMetatext();
    }

    internal class SyncCountersAvOpenhomeOrgInfo1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgInfo1 iService;
        private uint iTrackCount;
        private uint iDetailsCount;
        private uint iMetatextCount;

        public SyncCountersAvOpenhomeOrgInfo1(CpProxyAvOpenhomeOrgInfo1 aProxy)
        {
            iService = aProxy;
        }
        public uint TrackCount()
        {
            return iTrackCount;
        }
        public uint DetailsCount()
        {
            return iDetailsCount;
        }
        public uint MetatextCount()
        {
            return iMetatextCount;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCounters(aAsyncHandle, out iTrackCount, out iDetailsCount, out iMetatextCount);
        }
    };

    internal class SyncTrackAvOpenhomeOrgInfo1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgInfo1 iService;
        private String iUri;
        private String iMetadata;

        public SyncTrackAvOpenhomeOrgInfo1(CpProxyAvOpenhomeOrgInfo1 aProxy)
        {
            iService = aProxy;
        }
        public String Uri()
        {
            return iUri;
        }
        public String Metadata()
        {
            return iMetadata;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndTrack(aAsyncHandle, out iUri, out iMetadata);
        }
    };

    internal class SyncDetailsAvOpenhomeOrgInfo1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgInfo1 iService;
        private uint iDuration;
        private uint iBitRate;
        private uint iBitDepth;
        private uint iSampleRate;
        private bool iLossless;
        private String iCodecName;

        public SyncDetailsAvOpenhomeOrgInfo1(CpProxyAvOpenhomeOrgInfo1 aProxy)
        {
            iService = aProxy;
        }
        public uint Duration()
        {
            return iDuration;
        }
        public uint BitRate()
        {
            return iBitRate;
        }
        public uint BitDepth()
        {
            return iBitDepth;
        }
        public uint SampleRate()
        {
            return iSampleRate;
        }
        public bool Lossless()
        {
            return iLossless;
        }
        public String CodecName()
        {
            return iCodecName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDetails(aAsyncHandle, out iDuration, out iBitRate, out iBitDepth, out iSampleRate, out iLossless, out iCodecName);
        }
    };

    internal class SyncMetatextAvOpenhomeOrgInfo1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgInfo1 iService;
        private String iValue;

        public SyncMetatextAvOpenhomeOrgInfo1(CpProxyAvOpenhomeOrgInfo1 aProxy)
        {
            iService = aProxy;
        }
        public String Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndMetatext(aAsyncHandle, out iValue);
        }
    };

    /// <summary>
    /// Proxy for the av.openhome.org:Info:1 UPnP service
    /// </summary>
    public class CpProxyAvOpenhomeOrgInfo1 : CpProxy, IDisposable, ICpProxyAvOpenhomeOrgInfo1
    {
        private OpenHome.Net.Core.Action iActionCounters;
        private OpenHome.Net.Core.Action iActionTrack;
        private OpenHome.Net.Core.Action iActionDetails;
        private OpenHome.Net.Core.Action iActionMetatext;
        private PropertyUint iTrackCount;
        private PropertyUint iDetailsCount;
        private PropertyUint iMetatextCount;
        private PropertyString iUri;
        private PropertyString iMetadata;
        private PropertyUint iDuration;
        private PropertyUint iBitRate;
        private PropertyUint iBitDepth;
        private PropertyUint iSampleRate;
        private PropertyBool iLossless;
        private PropertyString iCodecName;
        private PropertyString iMetatext;
        private System.Action iTrackCountChanged;
        private System.Action iDetailsCountChanged;
        private System.Action iMetatextCountChanged;
        private System.Action iUriChanged;
        private System.Action iMetadataChanged;
        private System.Action iDurationChanged;
        private System.Action iBitRateChanged;
        private System.Action iBitDepthChanged;
        private System.Action iSampleRateChanged;
        private System.Action iLosslessChanged;
        private System.Action iCodecNameChanged;
        private System.Action iMetatextChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyAvOpenhomeOrgInfo1(CpDevice aDevice)
            : base("av-openhome-org", "Info", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionCounters = new OpenHome.Net.Core.Action("Counters");
            param = new ParameterUint("TrackCount");
            iActionCounters.AddOutputParameter(param);
            param = new ParameterUint("DetailsCount");
            iActionCounters.AddOutputParameter(param);
            param = new ParameterUint("MetatextCount");
            iActionCounters.AddOutputParameter(param);

            iActionTrack = new OpenHome.Net.Core.Action("Track");
            param = new ParameterString("Uri", allowedValues);
            iActionTrack.AddOutputParameter(param);
            param = new ParameterString("Metadata", allowedValues);
            iActionTrack.AddOutputParameter(param);

            iActionDetails = new OpenHome.Net.Core.Action("Details");
            param = new ParameterUint("Duration");
            iActionDetails.AddOutputParameter(param);
            param = new ParameterUint("BitRate");
            iActionDetails.AddOutputParameter(param);
            param = new ParameterUint("BitDepth");
            iActionDetails.AddOutputParameter(param);
            param = new ParameterUint("SampleRate");
            iActionDetails.AddOutputParameter(param);
            param = new ParameterBool("Lossless");
            iActionDetails.AddOutputParameter(param);
            param = new ParameterString("CodecName", allowedValues);
            iActionDetails.AddOutputParameter(param);

            iActionMetatext = new OpenHome.Net.Core.Action("Metatext");
            param = new ParameterString("Value", allowedValues);
            iActionMetatext.AddOutputParameter(param);

            iTrackCount = new PropertyUint("TrackCount", TrackCountPropertyChanged);
            AddProperty(iTrackCount);
            iDetailsCount = new PropertyUint("DetailsCount", DetailsCountPropertyChanged);
            AddProperty(iDetailsCount);
            iMetatextCount = new PropertyUint("MetatextCount", MetatextCountPropertyChanged);
            AddProperty(iMetatextCount);
            iUri = new PropertyString("Uri", UriPropertyChanged);
            AddProperty(iUri);
            iMetadata = new PropertyString("Metadata", MetadataPropertyChanged);
            AddProperty(iMetadata);
            iDuration = new PropertyUint("Duration", DurationPropertyChanged);
            AddProperty(iDuration);
            iBitRate = new PropertyUint("BitRate", BitRatePropertyChanged);
            AddProperty(iBitRate);
            iBitDepth = new PropertyUint("BitDepth", BitDepthPropertyChanged);
            AddProperty(iBitDepth);
            iSampleRate = new PropertyUint("SampleRate", SampleRatePropertyChanged);
            AddProperty(iSampleRate);
            iLossless = new PropertyBool("Lossless", LosslessPropertyChanged);
            AddProperty(iLossless);
            iCodecName = new PropertyString("CodecName", CodecNamePropertyChanged);
            AddProperty(iCodecName);
            iMetatext = new PropertyString("Metatext", MetatextPropertyChanged);
            AddProperty(iMetatext);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aTrackCount"></param>
        /// <param name="aDetailsCount"></param>
        /// <param name="aMetatextCount"></param>
        public void SyncCounters(out uint aTrackCount, out uint aDetailsCount, out uint aMetatextCount)
        {
            SyncCountersAvOpenhomeOrgInfo1 sync = new SyncCountersAvOpenhomeOrgInfo1(this);
            BeginCounters(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aTrackCount = sync.TrackCount();
            aDetailsCount = sync.DetailsCount();
            aMetatextCount = sync.MetatextCount();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCounters().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCounters(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCounters, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCounters.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCounters.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCounters.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aTrackCount"></param>
        /// <param name="aDetailsCount"></param>
        /// <param name="aMetatextCount"></param>
        public void EndCounters(IntPtr aAsyncHandle, out uint aTrackCount, out uint aDetailsCount, out uint aMetatextCount)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aTrackCount = Invocation.OutputUint(aAsyncHandle, index++);
            aDetailsCount = Invocation.OutputUint(aAsyncHandle, index++);
            aMetatextCount = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        public void SyncTrack(out String aUri, out String aMetadata)
        {
            SyncTrackAvOpenhomeOrgInfo1 sync = new SyncTrackAvOpenhomeOrgInfo1(this);
            BeginTrack(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aUri = sync.Uri();
            aMetadata = sync.Metadata();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTrack().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginTrack(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionTrack, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionTrack.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionTrack.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aUri"></param>
        /// <param name="aMetadata"></param>
        public void EndTrack(IntPtr aAsyncHandle, out String aUri, out String aMetadata)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aUri = Invocation.OutputString(aAsyncHandle, index++);
            aMetadata = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aDuration"></param>
        /// <param name="aBitRate"></param>
        /// <param name="aBitDepth"></param>
        /// <param name="aSampleRate"></param>
        /// <param name="aLossless"></param>
        /// <param name="aCodecName"></param>
        public void SyncDetails(out uint aDuration, out uint aBitRate, out uint aBitDepth, out uint aSampleRate, out bool aLossless, out String aCodecName)
        {
            SyncDetailsAvOpenhomeOrgInfo1 sync = new SyncDetailsAvOpenhomeOrgInfo1(this);
            BeginDetails(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aDuration = sync.Duration();
            aBitRate = sync.BitRate();
            aBitDepth = sync.BitDepth();
            aSampleRate = sync.SampleRate();
            aLossless = sync.Lossless();
            aCodecName = sync.CodecName();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDetails().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDetails(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDetails, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDetails.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDetails.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDetails.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDetails.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionDetails.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionDetails.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aDuration"></param>
        /// <param name="aBitRate"></param>
        /// <param name="aBitDepth"></param>
        /// <param name="aSampleRate"></param>
        /// <param name="aLossless"></param>
        /// <param name="aCodecName"></param>
        public void EndDetails(IntPtr aAsyncHandle, out uint aDuration, out uint aBitRate, out uint aBitDepth, out uint aSampleRate, out bool aLossless, out String aCodecName)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aDuration = Invocation.OutputUint(aAsyncHandle, index++);
            aBitRate = Invocation.OutputUint(aAsyncHandle, index++);
            aBitDepth = Invocation.OutputUint(aAsyncHandle, index++);
            aSampleRate = Invocation.OutputUint(aAsyncHandle, index++);
            aLossless = Invocation.OutputBool(aAsyncHandle, index++);
            aCodecName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncMetatext(out String aValue)
        {
            SyncMetatextAvOpenhomeOrgInfo1 sync = new SyncMetatextAvOpenhomeOrgInfo1(this);
            BeginMetatext(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMetatext().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginMetatext(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionMetatext, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionMetatext.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndMetatext(IntPtr aAsyncHandle, out String aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the TrackCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aTrackCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackCountChanged(System.Action aTrackCountChanged)
        {
            lock (iPropertyLock)
            {
                iTrackCountChanged = aTrackCountChanged;
            }
        }

        private void TrackCountPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iTrackCountChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the DetailsCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aDetailsCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDetailsCountChanged(System.Action aDetailsCountChanged)
        {
            lock (iPropertyLock)
            {
                iDetailsCountChanged = aDetailsCountChanged;
            }
        }

        private void DetailsCountPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iDetailsCountChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the MetatextCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aMetatextCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyMetatextCountChanged(System.Action aMetatextCountChanged)
        {
            lock (iPropertyLock)
            {
                iMetatextCountChanged = aMetatextCountChanged;
            }
        }

        private void MetatextCountPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iMetatextCountChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Uri state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aUriChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyUriChanged(System.Action aUriChanged)
        {
            lock (iPropertyLock)
            {
                iUriChanged = aUriChanged;
            }
        }

        private void UriPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iUriChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Metadata state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aMetadataChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyMetadataChanged(System.Action aMetadataChanged)
        {
            lock (iPropertyLock)
            {
                iMetadataChanged = aMetadataChanged;
            }
        }

        private void MetadataPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iMetadataChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Duration state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aDurationChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDurationChanged(System.Action aDurationChanged)
        {
            lock (iPropertyLock)
            {
                iDurationChanged = aDurationChanged;
            }
        }

        private void DurationPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iDurationChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the BitRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aBitRateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyBitRateChanged(System.Action aBitRateChanged)
        {
            lock (iPropertyLock)
            {
                iBitRateChanged = aBitRateChanged;
            }
        }

        private void BitRatePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iBitRateChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the BitDepth state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aBitDepthChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyBitDepthChanged(System.Action aBitDepthChanged)
        {
            lock (iPropertyLock)
            {
                iBitDepthChanged = aBitDepthChanged;
            }
        }

        private void BitDepthPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iBitDepthChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the SampleRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aSampleRateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySampleRateChanged(System.Action aSampleRateChanged)
        {
            lock (iPropertyLock)
            {
                iSampleRateChanged = aSampleRateChanged;
            }
        }

        private void SampleRatePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSampleRateChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Lossless state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aLosslessChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyLosslessChanged(System.Action aLosslessChanged)
        {
            lock (iPropertyLock)
            {
                iLosslessChanged = aLosslessChanged;
            }
        }

        private void LosslessPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iLosslessChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the CodecName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aCodecNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyCodecNameChanged(System.Action aCodecNameChanged)
        {
            lock (iPropertyLock)
            {
                iCodecNameChanged = aCodecNameChanged;
            }
        }

        private void CodecNamePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iCodecNameChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Metatext state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgInfo1 instance will not overlap.</remarks>
        /// <param name="aMetatextChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyMetatextChanged(System.Action aMetatextChanged)
        {
            lock (iPropertyLock)
            {
                iMetatextChanged = aMetatextChanged;
            }
        }

        private void MetatextPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iMetatextChanged);
            }
        }

        /// <summary>
        /// Query the value of the TrackCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the TrackCount property</returns>
        public uint PropertyTrackCount()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iTrackCount.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the DetailsCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the DetailsCount property</returns>
        public uint PropertyDetailsCount()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iDetailsCount.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the MetatextCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the MetatextCount property</returns>
        public uint PropertyMetatextCount()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iMetatextCount.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Uri property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Uri property</returns>
        public String PropertyUri()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iUri.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Metadata property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Metadata property</returns>
        public String PropertyMetadata()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iMetadata.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Duration property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Duration property</returns>
        public uint PropertyDuration()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iDuration.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the BitRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the BitRate property</returns>
        public uint PropertyBitRate()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iBitRate.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the BitDepth property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the BitDepth property</returns>
        public uint PropertyBitDepth()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iBitDepth.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the SampleRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the SampleRate property</returns>
        public uint PropertySampleRate()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iSampleRate.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Lossless property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Lossless property</returns>
        public bool PropertyLossless()
        {
            PropertyReadLock();
            bool val;
            try
            {
                val = iLossless.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the CodecName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the CodecName property</returns>
        public String PropertyCodecName()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iCodecName.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Metatext property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Metatext property</returns>
        public String PropertyMetatext()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iMetatext.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DisposeProxy();
                iHandle = IntPtr.Zero;
            }
            iActionCounters.Dispose();
            iActionTrack.Dispose();
            iActionDetails.Dispose();
            iActionMetatext.Dispose();
            iTrackCount.Dispose();
            iDetailsCount.Dispose();
            iMetatextCount.Dispose();
            iUri.Dispose();
            iMetadata.Dispose();
            iDuration.Dispose();
            iBitRate.Dispose();
            iBitDepth.Dispose();
            iSampleRate.Dispose();
            iLossless.Dispose();
            iCodecName.Dispose();
            iMetatext.Dispose();
        }
    }
}

