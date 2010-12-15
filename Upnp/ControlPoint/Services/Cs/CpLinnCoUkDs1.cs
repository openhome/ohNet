using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkDs1 : ICpProxy, IDisposable
    {
        void SyncPlay();
        void BeginPlay(CpProxy.CallbackAsyncComplete aCallback);
        void EndPlay(IntPtr aAsyncHandle);
        void SyncPause();
        void BeginPause(CpProxy.CallbackAsyncComplete aCallback);
        void EndPause(IntPtr aAsyncHandle);
        void SyncStop();
        void BeginStop(CpProxy.CallbackAsyncComplete aCallback);
        void EndStop(IntPtr aAsyncHandle);
        void SyncSeekSecondAbsolute(uint aaSecond);
        void BeginSeekSecondAbsolute(uint aaSecond, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekSecondAbsolute(IntPtr aAsyncHandle);
        void SyncSeekSecondRelative(int aaSecond);
        void BeginSeekSecondRelative(int aaSecond, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekSecondRelative(IntPtr aAsyncHandle);
        void SyncSeekTrackId(uint aaTrackId);
        void BeginSeekTrackId(uint aaTrackId, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekTrackId(IntPtr aAsyncHandle);
        void SyncSeekTrackAbsolute(uint aaTrack);
        void BeginSeekTrackAbsolute(uint aaTrack, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekTrackAbsolute(IntPtr aAsyncHandle);
        void SyncSeekTrackRelative(int aaTrack);
        void BeginSeekTrackRelative(int aaTrack, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekTrackRelative(IntPtr aAsyncHandle);
        void SyncState(out String aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out String aaTrackCodecName, out uint aaTrackId);
        void BeginState(CpProxy.CallbackAsyncComplete aCallback);
        void EndState(IntPtr aAsyncHandle, out String aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out String aaTrackCodecName, out uint aaTrackId);
        void SyncProtocolInfo(out String aaSupportedProtocols);
        void BeginProtocolInfo(CpProxy.CallbackAsyncComplete aCallback);
        void EndProtocolInfo(IntPtr aAsyncHandle, out String aaSupportedProtocols);
        void SetPropertySupportedProtocolsChanged(CpProxy.CallbackPropertyChanged aSupportedProtocolsChanged);
        String PropertySupportedProtocols();
        void SetPropertyTrackDurationChanged(CpProxy.CallbackPropertyChanged aTrackDurationChanged);
        uint PropertyTrackDuration();
        void SetPropertyTrackBitRateChanged(CpProxy.CallbackPropertyChanged aTrackBitRateChanged);
        uint PropertyTrackBitRate();
        void SetPropertyTrackLosslessChanged(CpProxy.CallbackPropertyChanged aTrackLosslessChanged);
        bool PropertyTrackLossless();
        void SetPropertyTrackBitDepthChanged(CpProxy.CallbackPropertyChanged aTrackBitDepthChanged);
        uint PropertyTrackBitDepth();
        void SetPropertyTrackSampleRateChanged(CpProxy.CallbackPropertyChanged aTrackSampleRateChanged);
        uint PropertyTrackSampleRate();
        void SetPropertyTrackCodecNameChanged(CpProxy.CallbackPropertyChanged aTrackCodecNameChanged);
        String PropertyTrackCodecName();
        void SetPropertyTrackIdChanged(CpProxy.CallbackPropertyChanged aTrackIdChanged);
        uint PropertyTrackId();
        void SetPropertyTransportStateChanged(CpProxy.CallbackPropertyChanged aTransportStateChanged);
        String PropertyTransportState();
    }

    internal class SyncPlayLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;

        public SyncPlayLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPlay(aAsyncHandle);
        }
    };

    internal class SyncPauseLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;

        public SyncPauseLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPause(aAsyncHandle);
        }
    };

    internal class SyncStopLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;

        public SyncStopLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStop(aAsyncHandle);
        }
    };

    internal class SyncSeekSecondAbsoluteLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;

        public SyncSeekSecondAbsoluteLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSeekSecondAbsolute(aAsyncHandle);
        }
    };

    internal class SyncSeekSecondRelativeLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;

        public SyncSeekSecondRelativeLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSeekSecondRelative(aAsyncHandle);
        }
    };

    internal class SyncSeekTrackIdLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;

        public SyncSeekTrackIdLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSeekTrackId(aAsyncHandle);
        }
    };

    internal class SyncSeekTrackAbsoluteLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;

        public SyncSeekTrackAbsoluteLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSeekTrackAbsolute(aAsyncHandle);
        }
    };

    internal class SyncSeekTrackRelativeLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;

        public SyncSeekTrackRelativeLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSeekTrackRelative(aAsyncHandle);
        }
    };

    internal class SyncStateLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;
        private String iTransportState;
        private uint iTrackDuration;
        private uint iTrackBitRate;
        private bool iTrackLossless;
        private uint iTrackBitDepth;
        private uint iTrackSampleRate;
        private String iTrackCodecName;
        private uint iTrackId;

        public SyncStateLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        public String TransportState()
        {
            return iTransportState;
        }
        public uint TrackDuration()
        {
            return iTrackDuration;
        }
        public uint TrackBitRate()
        {
            return iTrackBitRate;
        }
        public bool TrackLossless()
        {
            return iTrackLossless;
        }
        public uint TrackBitDepth()
        {
            return iTrackBitDepth;
        }
        public uint TrackSampleRate()
        {
            return iTrackSampleRate;
        }
        public String TrackCodecName()
        {
            return iTrackCodecName;
        }
        public uint TrackId()
        {
            return iTrackId;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndState(aAsyncHandle, out iTransportState, out iTrackDuration, out iTrackBitRate, out iTrackLossless, out iTrackBitDepth, out iTrackSampleRate, out iTrackCodecName, out iTrackId);
        }
    };

    internal class SyncProtocolInfoLinnCoUkDs1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDs1 iService;
        private String iSupportedProtocols;

        public SyncProtocolInfoLinnCoUkDs1(CpProxyLinnCoUkDs1 aProxy)
        {
            iService = aProxy;
        }
        public String SupportedProtocols()
        {
            return iSupportedProtocols;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndProtocolInfo(aAsyncHandle, out iSupportedProtocols);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Ds:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkDs1 : CpProxy, IDisposable, ICpProxyLinnCoUkDs1
    {
        private Zapp.Core.Action iActionPlay;
        private Zapp.Core.Action iActionPause;
        private Zapp.Core.Action iActionStop;
        private Zapp.Core.Action iActionSeekSecondAbsolute;
        private Zapp.Core.Action iActionSeekSecondRelative;
        private Zapp.Core.Action iActionSeekTrackId;
        private Zapp.Core.Action iActionSeekTrackAbsolute;
        private Zapp.Core.Action iActionSeekTrackRelative;
        private Zapp.Core.Action iActionState;
        private Zapp.Core.Action iActionProtocolInfo;
        private PropertyString iSupportedProtocols;
        private PropertyUint iTrackDuration;
        private PropertyUint iTrackBitRate;
        private PropertyBool iTrackLossless;
        private PropertyUint iTrackBitDepth;
        private PropertyUint iTrackSampleRate;
        private PropertyString iTrackCodecName;
        private PropertyUint iTrackId;
        private PropertyString iTransportState;
        private CallbackPropertyChanged iSupportedProtocolsChanged;
        private CallbackPropertyChanged iTrackDurationChanged;
        private CallbackPropertyChanged iTrackBitRateChanged;
        private CallbackPropertyChanged iTrackLosslessChanged;
        private CallbackPropertyChanged iTrackBitDepthChanged;
        private CallbackPropertyChanged iTrackSampleRateChanged;
        private CallbackPropertyChanged iTrackCodecNameChanged;
        private CallbackPropertyChanged iTrackIdChanged;
        private CallbackPropertyChanged iTransportStateChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkDs1(CpDevice aDevice)
            : base("linn-co-uk", "Ds", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionPlay = new Zapp.Core.Action("Play");

            iActionPause = new Zapp.Core.Action("Pause");

            iActionStop = new Zapp.Core.Action("Stop");

            iActionSeekSecondAbsolute = new Zapp.Core.Action("SeekSecondAbsolute");
            param = new ParameterUint("aSecond");
            iActionSeekSecondAbsolute.AddInputParameter(param);

            iActionSeekSecondRelative = new Zapp.Core.Action("SeekSecondRelative");
            param = new ParameterInt("aSecond");
            iActionSeekSecondRelative.AddInputParameter(param);

            iActionSeekTrackId = new Zapp.Core.Action("SeekTrackId");
            param = new ParameterUint("aTrackId");
            iActionSeekTrackId.AddInputParameter(param);

            iActionSeekTrackAbsolute = new Zapp.Core.Action("SeekTrackAbsolute");
            param = new ParameterUint("aTrack");
            iActionSeekTrackAbsolute.AddInputParameter(param);

            iActionSeekTrackRelative = new Zapp.Core.Action("SeekTrackRelative");
            param = new ParameterInt("aTrack");
            iActionSeekTrackRelative.AddInputParameter(param);

            iActionState = new Zapp.Core.Action("State");
            allowedValues.Add("Playing");
            allowedValues.Add("Paused");
            allowedValues.Add("Stopped");
            allowedValues.Add("Buffering");
            param = new ParameterString("aTransportState", allowedValues);
            iActionState.AddOutputParameter(param);
            allowedValues.Clear();
            param = new ParameterUint("aTrackDuration");
            iActionState.AddOutputParameter(param);
            param = new ParameterUint("aTrackBitRate");
            iActionState.AddOutputParameter(param);
            param = new ParameterBool("aTrackLossless");
            iActionState.AddOutputParameter(param);
            param = new ParameterUint("aTrackBitDepth");
            iActionState.AddOutputParameter(param);
            param = new ParameterUint("aTrackSampleRate");
            iActionState.AddOutputParameter(param);
            param = new ParameterString("aTrackCodecName", allowedValues);
            iActionState.AddOutputParameter(param);
            param = new ParameterUint("aTrackId");
            iActionState.AddOutputParameter(param);

            iActionProtocolInfo = new Zapp.Core.Action("ProtocolInfo");
            param = new ParameterString("aSupportedProtocols", allowedValues);
            iActionProtocolInfo.AddOutputParameter(param);

            iSupportedProtocols = new PropertyString("SupportedProtocols", SupportedProtocolsPropertyChanged);
            AddProperty(iSupportedProtocols);
            iTrackDuration = new PropertyUint("TrackDuration", TrackDurationPropertyChanged);
            AddProperty(iTrackDuration);
            iTrackBitRate = new PropertyUint("TrackBitRate", TrackBitRatePropertyChanged);
            AddProperty(iTrackBitRate);
            iTrackLossless = new PropertyBool("TrackLossless", TrackLosslessPropertyChanged);
            AddProperty(iTrackLossless);
            iTrackBitDepth = new PropertyUint("TrackBitDepth", TrackBitDepthPropertyChanged);
            AddProperty(iTrackBitDepth);
            iTrackSampleRate = new PropertyUint("TrackSampleRate", TrackSampleRatePropertyChanged);
            AddProperty(iTrackSampleRate);
            iTrackCodecName = new PropertyString("TrackCodecName", TrackCodecNamePropertyChanged);
            AddProperty(iTrackCodecName);
            iTrackId = new PropertyUint("TrackId", TrackIdPropertyChanged);
            AddProperty(iTrackId);
            iTransportState = new PropertyString("TransportState", TransportStatePropertyChanged);
            AddProperty(iTransportState);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncPlay()
        {
            SyncPlayLinnCoUkDs1 sync = new SyncPlayLinnCoUkDs1(this);
            BeginPlay(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPlay().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPlay(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPlay, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndPlay(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncPause()
        {
            SyncPauseLinnCoUkDs1 sync = new SyncPauseLinnCoUkDs1(this);
            BeginPause(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPause().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPause(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPause, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndPause(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncStop()
        {
            SyncStopLinnCoUkDs1 sync = new SyncStopLinnCoUkDs1(this);
            BeginStop(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStop().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStop(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStop, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStop(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSecond"></param>
        public void SyncSeekSecondAbsolute(uint aaSecond)
        {
            SyncSeekSecondAbsoluteLinnCoUkDs1 sync = new SyncSeekSecondAbsoluteLinnCoUkDs1(this);
            BeginSeekSecondAbsolute(aSecond, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekSecondAbsolute().</remarks>
        /// <param name="aaSecond"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSeekSecondAbsolute(uint aaSecond, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSeekSecondAbsolute, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSeekSecondAbsolute.InputParameter(inIndex++), aSecond));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSeekSecondAbsolute(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSecond"></param>
        public void SyncSeekSecondRelative(int aaSecond)
        {
            SyncSeekSecondRelativeLinnCoUkDs1 sync = new SyncSeekSecondRelativeLinnCoUkDs1(this);
            BeginSeekSecondRelative(aSecond, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekSecondRelative().</remarks>
        /// <param name="aaSecond"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSeekSecondRelative(int aaSecond, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSeekSecondRelative, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSeekSecondRelative.InputParameter(inIndex++), aSecond));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSeekSecondRelative(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTrackId"></param>
        public void SyncSeekTrackId(uint aaTrackId)
        {
            SyncSeekTrackIdLinnCoUkDs1 sync = new SyncSeekTrackIdLinnCoUkDs1(this);
            BeginSeekTrackId(aTrackId, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekTrackId().</remarks>
        /// <param name="aaTrackId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSeekTrackId(uint aaTrackId, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSeekTrackId, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSeekTrackId.InputParameter(inIndex++), aTrackId));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSeekTrackId(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTrack"></param>
        public void SyncSeekTrackAbsolute(uint aaTrack)
        {
            SyncSeekTrackAbsoluteLinnCoUkDs1 sync = new SyncSeekTrackAbsoluteLinnCoUkDs1(this);
            BeginSeekTrackAbsolute(aTrack, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekTrackAbsolute().</remarks>
        /// <param name="aaTrack"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSeekTrackAbsolute(uint aaTrack, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSeekTrackAbsolute, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSeekTrackAbsolute.InputParameter(inIndex++), aTrack));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSeekTrackAbsolute(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTrack"></param>
        public void SyncSeekTrackRelative(int aaTrack)
        {
            SyncSeekTrackRelativeLinnCoUkDs1 sync = new SyncSeekTrackRelativeLinnCoUkDs1(this);
            BeginSeekTrackRelative(aTrack, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekTrackRelative().</remarks>
        /// <param name="aaTrack"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSeekTrackRelative(int aaTrack, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSeekTrackRelative, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSeekTrackRelative.InputParameter(inIndex++), aTrack));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSeekTrackRelative(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTransportState"></param>
        /// <param name="aaTrackDuration"></param>
        /// <param name="aaTrackBitRate"></param>
        /// <param name="aaTrackLossless"></param>
        /// <param name="aaTrackBitDepth"></param>
        /// <param name="aaTrackSampleRate"></param>
        /// <param name="aaTrackCodecName"></param>
        /// <param name="aaTrackId"></param>
        public void SyncState(out String aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out String aaTrackCodecName, out uint aaTrackId)
        {
            SyncStateLinnCoUkDs1 sync = new SyncStateLinnCoUkDs1(this);
            BeginState(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aTransportState = sync.TransportState();
            aTrackDuration = sync.TrackDuration();
            aTrackBitRate = sync.TrackBitRate();
            aTrackLossless = sync.TrackLossless();
            aTrackBitDepth = sync.TrackBitDepth();
            aTrackSampleRate = sync.TrackSampleRate();
            aTrackCodecName = sync.TrackCodecName();
            aTrackId = sync.TrackId();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndState().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginState(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionState, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionState.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionState.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionState.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionState.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionState.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionState.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionState.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionState.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaTransportState"></param>
        /// <param name="aaTrackDuration"></param>
        /// <param name="aaTrackBitRate"></param>
        /// <param name="aaTrackLossless"></param>
        /// <param name="aaTrackBitDepth"></param>
        /// <param name="aaTrackSampleRate"></param>
        /// <param name="aaTrackCodecName"></param>
        /// <param name="aaTrackId"></param>
        public void EndState(IntPtr aAsyncHandle, out String aaTransportState, out uint aaTrackDuration, out uint aaTrackBitRate, out bool aaTrackLossless, out uint aaTrackBitDepth, out uint aaTrackSampleRate, out String aaTrackCodecName, out uint aaTrackId)
        {
            uint index = 0;
            aTransportState = Invocation.OutputString(aAsyncHandle, index++);
            aTrackDuration = Invocation.OutputUint(aAsyncHandle, index++);
            aTrackBitRate = Invocation.OutputUint(aAsyncHandle, index++);
            aTrackLossless = Invocation.OutputBool(aAsyncHandle, index++);
            aTrackBitDepth = Invocation.OutputUint(aAsyncHandle, index++);
            aTrackSampleRate = Invocation.OutputUint(aAsyncHandle, index++);
            aTrackCodecName = Invocation.OutputString(aAsyncHandle, index++);
            aTrackId = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSupportedProtocols"></param>
        public void SyncProtocolInfo(out String aaSupportedProtocols)
        {
            SyncProtocolInfoLinnCoUkDs1 sync = new SyncProtocolInfoLinnCoUkDs1(this);
            BeginProtocolInfo(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSupportedProtocols = sync.SupportedProtocols();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndProtocolInfo().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginProtocolInfo(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionProtocolInfo, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionProtocolInfo.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSupportedProtocols"></param>
        public void EndProtocolInfo(IntPtr aAsyncHandle, out String aaSupportedProtocols)
        {
            uint index = 0;
            aSupportedProtocols = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the SupportedProtocols state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aSupportedProtocolsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySupportedProtocolsChanged(CallbackPropertyChanged aSupportedProtocolsChanged)
        {
            lock (this)
            {
                iSupportedProtocolsChanged = aSupportedProtocolsChanged;
            }
        }

        private void SupportedProtocolsPropertyChanged()
        {
            lock (this)
            {
                if (iSupportedProtocolsChanged != null)
                {
                    iSupportedProtocolsChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TrackDuration state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackDurationChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackDurationChanged(CallbackPropertyChanged aTrackDurationChanged)
        {
            lock (this)
            {
                iTrackDurationChanged = aTrackDurationChanged;
            }
        }

        private void TrackDurationPropertyChanged()
        {
            lock (this)
            {
                if (iTrackDurationChanged != null)
                {
                    iTrackDurationChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TrackBitRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackBitRateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackBitRateChanged(CallbackPropertyChanged aTrackBitRateChanged)
        {
            lock (this)
            {
                iTrackBitRateChanged = aTrackBitRateChanged;
            }
        }

        private void TrackBitRatePropertyChanged()
        {
            lock (this)
            {
                if (iTrackBitRateChanged != null)
                {
                    iTrackBitRateChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TrackLossless state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackLosslessChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackLosslessChanged(CallbackPropertyChanged aTrackLosslessChanged)
        {
            lock (this)
            {
                iTrackLosslessChanged = aTrackLosslessChanged;
            }
        }

        private void TrackLosslessPropertyChanged()
        {
            lock (this)
            {
                if (iTrackLosslessChanged != null)
                {
                    iTrackLosslessChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TrackBitDepth state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackBitDepthChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackBitDepthChanged(CallbackPropertyChanged aTrackBitDepthChanged)
        {
            lock (this)
            {
                iTrackBitDepthChanged = aTrackBitDepthChanged;
            }
        }

        private void TrackBitDepthPropertyChanged()
        {
            lock (this)
            {
                if (iTrackBitDepthChanged != null)
                {
                    iTrackBitDepthChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TrackSampleRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackSampleRateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackSampleRateChanged(CallbackPropertyChanged aTrackSampleRateChanged)
        {
            lock (this)
            {
                iTrackSampleRateChanged = aTrackSampleRateChanged;
            }
        }

        private void TrackSampleRatePropertyChanged()
        {
            lock (this)
            {
                if (iTrackSampleRateChanged != null)
                {
                    iTrackSampleRateChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TrackCodecName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackCodecNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackCodecNameChanged(CallbackPropertyChanged aTrackCodecNameChanged)
        {
            lock (this)
            {
                iTrackCodecNameChanged = aTrackCodecNameChanged;
            }
        }

        private void TrackCodecNamePropertyChanged()
        {
            lock (this)
            {
                if (iTrackCodecNameChanged != null)
                {
                    iTrackCodecNameChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TrackId state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTrackIdChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackIdChanged(CallbackPropertyChanged aTrackIdChanged)
        {
            lock (this)
            {
                iTrackIdChanged = aTrackIdChanged;
            }
        }

        private void TrackIdPropertyChanged()
        {
            lock (this)
            {
                if (iTrackIdChanged != null)
                {
                    iTrackIdChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TransportState state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDs1 instance will not overlap.</remarks>
        /// <param name="aTransportStateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTransportStateChanged(CallbackPropertyChanged aTransportStateChanged)
        {
            lock (this)
            {
                iTransportStateChanged = aTransportStateChanged;
            }
        }

        private void TransportStatePropertyChanged()
        {
            lock (this)
            {
                if (iTransportStateChanged != null)
                {
                    iTransportStateChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the SupportedProtocols property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aSupportedProtocols">Will be set to the value of the property</param>
        public String PropertySupportedProtocols()
        {
            return iSupportedProtocols.Value();
        }

        /// <summary>
        /// Query the value of the TrackDuration property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackDuration">Will be set to the value of the property</param>
        public uint PropertyTrackDuration()
        {
            return iTrackDuration.Value();
        }

        /// <summary>
        /// Query the value of the TrackBitRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackBitRate">Will be set to the value of the property</param>
        public uint PropertyTrackBitRate()
        {
            return iTrackBitRate.Value();
        }

        /// <summary>
        /// Query the value of the TrackLossless property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackLossless">Will be set to the value of the property</param>
        public bool PropertyTrackLossless()
        {
            return iTrackLossless.Value();
        }

        /// <summary>
        /// Query the value of the TrackBitDepth property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackBitDepth">Will be set to the value of the property</param>
        public uint PropertyTrackBitDepth()
        {
            return iTrackBitDepth.Value();
        }

        /// <summary>
        /// Query the value of the TrackSampleRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackSampleRate">Will be set to the value of the property</param>
        public uint PropertyTrackSampleRate()
        {
            return iTrackSampleRate.Value();
        }

        /// <summary>
        /// Query the value of the TrackCodecName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackCodecName">Will be set to the value of the property</param>
        public String PropertyTrackCodecName()
        {
            return iTrackCodecName.Value();
        }

        /// <summary>
        /// Query the value of the TrackId property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackId">Will be set to the value of the property</param>
        public uint PropertyTrackId()
        {
            return iTrackId.Value();
        }

        /// <summary>
        /// Query the value of the TransportState property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTransportState">Will be set to the value of the property</param>
        public String PropertyTransportState()
        {
            return iTransportState.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDs1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProxy();
                iHandle = IntPtr.Zero;
                iActionPlay.Dispose();
                iActionPause.Dispose();
                iActionStop.Dispose();
                iActionSeekSecondAbsolute.Dispose();
                iActionSeekSecondRelative.Dispose();
                iActionSeekTrackId.Dispose();
                iActionSeekTrackAbsolute.Dispose();
                iActionSeekTrackRelative.Dispose();
                iActionState.Dispose();
                iActionProtocolInfo.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

