using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkRadio1 : ICpProxy, IDisposable
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
        void SyncSeekSecondAbsolute(uint aSecond);
        void BeginSeekSecondAbsolute(uint aSecond, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekSecondAbsolute(IntPtr aAsyncHandle);
        void SyncSeekSecondRelative(int aSecond);
        void BeginSeekSecondRelative(int aSecond, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekSecondRelative(IntPtr aAsyncHandle);
        void SyncChannel(out String aUri, out String aMetadata);
        void BeginChannel(CpProxy.CallbackAsyncComplete aCallback);
        void EndChannel(IntPtr aAsyncHandle, out String aUri, out String aMetadata);
        void SyncSetChannel(String aUri, String aMetadata);
        void BeginSetChannel(String aUri, String aMetadata, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetChannel(IntPtr aAsyncHandle);
        void SyncProtocolInfo(out String aInfo);
        void BeginProtocolInfo(CpProxy.CallbackAsyncComplete aCallback);
        void EndProtocolInfo(IntPtr aAsyncHandle, out String aInfo);
        void SyncTransportState(out String aState);
        void BeginTransportState(CpProxy.CallbackAsyncComplete aCallback);
        void EndTransportState(IntPtr aAsyncHandle, out String aState);
        void SyncId(out uint aId);
        void BeginId(CpProxy.CallbackAsyncComplete aCallback);
        void EndId(IntPtr aAsyncHandle, out uint aId);
        void SyncSetId(uint aId, String aUri);
        void BeginSetId(uint aId, String aUri, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetId(IntPtr aAsyncHandle);
        void SyncRead(uint aId, out String aMetadata);
        void BeginRead(uint aId, CpProxy.CallbackAsyncComplete aCallback);
        void EndRead(IntPtr aAsyncHandle, out String aMetadata);
        void SyncReadList(String aIdList, out String aMetadataList);
        void BeginReadList(String aIdList, CpProxy.CallbackAsyncComplete aCallback);
        void EndReadList(IntPtr aAsyncHandle, out String aMetadataList);
        void SyncIdArray(out uint aIdArrayToken, out byte[] aIdArray);
        void BeginIdArray(CpProxy.CallbackAsyncComplete aCallback);
        void EndIdArray(IntPtr aAsyncHandle, out uint aIdArrayToken, out byte[] aIdArray);
        void SyncIdArrayChanged(uint aIdArrayToken, out bool aIdArrayChanged);
        void BeginIdArrayChanged(uint aIdArrayToken, CpProxy.CallbackAsyncComplete aCallback);
        void EndIdArrayChanged(IntPtr aAsyncHandle, out bool aIdArrayChanged);
        void SyncIdsMax(out uint aIdsMax);
        void BeginIdsMax(CpProxy.CallbackAsyncComplete aCallback);
        void EndIdsMax(IntPtr aAsyncHandle, out uint aIdsMax);
        void SetPropertyChannelUriChanged(CpProxy.CallbackPropertyChanged aChannelUriChanged);
        String PropertyChannelUri();
        void SetPropertyChannelMetadataChanged(CpProxy.CallbackPropertyChanged aChannelMetadataChanged);
        String PropertyChannelMetadata();
        void SetPropertyTransportStateChanged(CpProxy.CallbackPropertyChanged aTransportStateChanged);
        String PropertyTransportState();
        void SetPropertyProtocolInfoChanged(CpProxy.CallbackPropertyChanged aProtocolInfoChanged);
        String PropertyProtocolInfo();
        void SetPropertyIdChanged(CpProxy.CallbackPropertyChanged aIdChanged);
        uint PropertyId();
        void SetPropertyIdArrayChanged(CpProxy.CallbackPropertyChanged aIdArrayChanged);
        byte[] PropertyIdArray();
        void SetPropertyIdsMaxChanged(CpProxy.CallbackPropertyChanged aIdsMaxChanged);
        uint PropertyIdsMax();
    }

    internal class SyncPlayLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;

        public SyncPlayLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPlay(aAsyncHandle);
        }
    };

    internal class SyncPauseLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;

        public SyncPauseLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPause(aAsyncHandle);
        }
    };

    internal class SyncStopLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;

        public SyncStopLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStop(aAsyncHandle);
        }
    };

    internal class SyncSeekSecondAbsoluteLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;

        public SyncSeekSecondAbsoluteLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSeekSecondAbsolute(aAsyncHandle);
        }
    };

    internal class SyncSeekSecondRelativeLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;

        public SyncSeekSecondRelativeLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSeekSecondRelative(aAsyncHandle);
        }
    };

    internal class SyncChannelLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private String iUri;
        private String iMetadata;

        public SyncChannelLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
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
            iService.EndChannel(aAsyncHandle, out iUri, out iMetadata);
        }
    };

    internal class SyncSetChannelLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;

        public SyncSetChannelLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetChannel(aAsyncHandle);
        }
    };

    internal class SyncProtocolInfoLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private String iInfo;

        public SyncProtocolInfoLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        public String Info()
        {
            return iInfo;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndProtocolInfo(aAsyncHandle, out iInfo);
        }
    };

    internal class SyncTransportStateLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private String iState;

        public SyncTransportStateLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        public String State()
        {
            return iState;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndTransportState(aAsyncHandle, out iState);
        }
    };

    internal class SyncIdLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private uint iId;

        public SyncIdLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        public uint Id()
        {
            return iId;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndId(aAsyncHandle, out iId);
        }
    };

    internal class SyncSetIdLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;

        public SyncSetIdLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetId(aAsyncHandle);
        }
    };

    internal class SyncReadLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private String iMetadata;

        public SyncReadLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        public String Metadata()
        {
            return iMetadata;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndRead(aAsyncHandle, out iMetadata);
        }
    };

    internal class SyncReadListLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private String iMetadataList;

        public SyncReadListLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        public String MetadataList()
        {
            return iMetadataList;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndReadList(aAsyncHandle, out iMetadataList);
        }
    };

    internal class SyncIdArrayLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private uint iIdArrayToken;
        private byte[] iIdArray;

        public SyncIdArrayLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        public uint IdArrayToken()
        {
            return iIdArrayToken;
        }
        public byte[] IdArray()
        {
            return iIdArray;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndIdArray(aAsyncHandle, out iIdArrayToken, out iIdArray);
        }
    };

    internal class SyncIdArrayChangedLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private bool iIdArrayChanged;

        public SyncIdArrayChangedLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        public bool IdArrayChanged()
        {
            return iIdArrayChanged;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndIdArrayChanged(aAsyncHandle, out iIdArrayChanged);
        }
    };

    internal class SyncIdsMaxLinnCoUkRadio1 : SyncProxyAction
    {
        private CpProxyLinnCoUkRadio1 iService;
        private uint iIdsMax;

        public SyncIdsMaxLinnCoUkRadio1(CpProxyLinnCoUkRadio1 aProxy)
        {
            iService = aProxy;
        }
        public uint IdsMax()
        {
            return iIdsMax;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndIdsMax(aAsyncHandle, out iIdsMax);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Radio:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkRadio1 : CpProxy, IDisposable, ICpProxyLinnCoUkRadio1
    {
        private Zapp.Core.Action iActionPlay;
        private Zapp.Core.Action iActionPause;
        private Zapp.Core.Action iActionStop;
        private Zapp.Core.Action iActionSeekSecondAbsolute;
        private Zapp.Core.Action iActionSeekSecondRelative;
        private Zapp.Core.Action iActionChannel;
        private Zapp.Core.Action iActionSetChannel;
        private Zapp.Core.Action iActionProtocolInfo;
        private Zapp.Core.Action iActionTransportState;
        private Zapp.Core.Action iActionId;
        private Zapp.Core.Action iActionSetId;
        private Zapp.Core.Action iActionRead;
        private Zapp.Core.Action iActionReadList;
        private Zapp.Core.Action iActionIdArray;
        private Zapp.Core.Action iActionIdArrayChanged;
        private Zapp.Core.Action iActionIdsMax;
        private PropertyString iChannelUri;
        private PropertyString iChannelMetadata;
        private PropertyString iTransportState;
        private PropertyString iProtocolInfo;
        private PropertyUint iId;
        private PropertyBinary iIdArray;
        private PropertyUint iIdsMax;
        private CallbackPropertyChanged iChannelUriChanged;
        private CallbackPropertyChanged iChannelMetadataChanged;
        private CallbackPropertyChanged iTransportStateChanged;
        private CallbackPropertyChanged iProtocolInfoChanged;
        private CallbackPropertyChanged iIdChanged;
        private CallbackPropertyChanged iIdArrayChanged;
        private CallbackPropertyChanged iIdsMaxChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkRadio1(CpDevice aDevice)
            : base("linn-co-uk", "Radio", 1, aDevice)
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

            iActionChannel = new Zapp.Core.Action("Channel");
            param = new ParameterString("aUri", allowedValues);
            iActionChannel.AddOutputParameter(param);
            param = new ParameterString("aMetadata", allowedValues);
            iActionChannel.AddOutputParameter(param);

            iActionSetChannel = new Zapp.Core.Action("SetChannel");
            param = new ParameterString("aUri", allowedValues);
            iActionSetChannel.AddInputParameter(param);
            param = new ParameterString("aMetadata", allowedValues);
            iActionSetChannel.AddInputParameter(param);

            iActionProtocolInfo = new Zapp.Core.Action("ProtocolInfo");
            param = new ParameterString("aInfo", allowedValues);
            iActionProtocolInfo.AddOutputParameter(param);

            iActionTransportState = new Zapp.Core.Action("TransportState");
            allowedValues.Add("Stopped");
            allowedValues.Add("Playing");
            allowedValues.Add("Paused");
            allowedValues.Add("Buffering");
            param = new ParameterString("aState", allowedValues);
            iActionTransportState.AddOutputParameter(param);
            allowedValues.Clear();

            iActionId = new Zapp.Core.Action("Id");
            param = new ParameterUint("aId");
            iActionId.AddOutputParameter(param);

            iActionSetId = new Zapp.Core.Action("SetId");
            param = new ParameterUint("aId");
            iActionSetId.AddInputParameter(param);
            param = new ParameterString("aUri", allowedValues);
            iActionSetId.AddInputParameter(param);

            iActionRead = new Zapp.Core.Action("Read");
            param = new ParameterUint("aId");
            iActionRead.AddInputParameter(param);
            param = new ParameterString("aMetadata", allowedValues);
            iActionRead.AddOutputParameter(param);

            iActionReadList = new Zapp.Core.Action("ReadList");
            param = new ParameterString("aIdList", allowedValues);
            iActionReadList.AddInputParameter(param);
            param = new ParameterString("aMetadataList", allowedValues);
            iActionReadList.AddOutputParameter(param);

            iActionIdArray = new Zapp.Core.Action("IdArray");
            param = new ParameterUint("aIdArrayToken");
            iActionIdArray.AddOutputParameter(param);
            param = new ParameterBinary("aIdArray");
            iActionIdArray.AddOutputParameter(param);

            iActionIdArrayChanged = new Zapp.Core.Action("IdArrayChanged");
            param = new ParameterUint("aIdArrayToken");
            iActionIdArrayChanged.AddInputParameter(param);
            param = new ParameterBool("aIdArrayChanged");
            iActionIdArrayChanged.AddOutputParameter(param);

            iActionIdsMax = new Zapp.Core.Action("IdsMax");
            param = new ParameterUint("aIdsMax");
            iActionIdsMax.AddOutputParameter(param);

            iChannelUri = new PropertyString("ChannelUri", ChannelUriPropertyChanged);
            AddProperty(iChannelUri);
            iChannelMetadata = new PropertyString("ChannelMetadata", ChannelMetadataPropertyChanged);
            AddProperty(iChannelMetadata);
            iTransportState = new PropertyString("TransportState", TransportStatePropertyChanged);
            AddProperty(iTransportState);
            iProtocolInfo = new PropertyString("ProtocolInfo", ProtocolInfoPropertyChanged);
            AddProperty(iProtocolInfo);
            iId = new PropertyUint("Id", IdPropertyChanged);
            AddProperty(iId);
            iIdArray = new PropertyBinary("IdArray", IdArrayPropertyChanged);
            AddProperty(iIdArray);
            iIdsMax = new PropertyUint("IdsMax", IdsMaxPropertyChanged);
            AddProperty(iIdsMax);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncPlay()
        {
            SyncPlayLinnCoUkRadio1 sync = new SyncPlayLinnCoUkRadio1(this);
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
            SyncPauseLinnCoUkRadio1 sync = new SyncPauseLinnCoUkRadio1(this);
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
            SyncStopLinnCoUkRadio1 sync = new SyncStopLinnCoUkRadio1(this);
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
        public void SyncSeekSecondAbsolute(uint aSecond)
        {
            SyncSeekSecondAbsoluteLinnCoUkRadio1 sync = new SyncSeekSecondAbsoluteLinnCoUkRadio1(this);
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
        public void BeginSeekSecondAbsolute(uint aSecond, CallbackAsyncComplete aCallback)
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
        public void SyncSeekSecondRelative(int aSecond)
        {
            SyncSeekSecondRelativeLinnCoUkRadio1 sync = new SyncSeekSecondRelativeLinnCoUkRadio1(this);
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
        public void BeginSeekSecondRelative(int aSecond, CallbackAsyncComplete aCallback)
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
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        public void SyncChannel(out String aUri, out String aMetadata)
        {
            SyncChannelLinnCoUkRadio1 sync = new SyncChannelLinnCoUkRadio1(this);
            BeginChannel(sync.AsyncComplete());
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
        /// EndChannel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginChannel(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionChannel, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionChannel.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionChannel.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        public void EndChannel(IntPtr aAsyncHandle, out String aUri, out String aMetadata)
        {
            uint index = 0;
            aUri = Invocation.OutputString(aAsyncHandle, index++);
            aMetadata = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        public void SyncSetChannel(String aUri, String aMetadata)
        {
            SyncSetChannelLinnCoUkRadio1 sync = new SyncSetChannelLinnCoUkRadio1(this);
            BeginSetChannel(aUri, aMetadata, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetChannel().</remarks>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetChannel(String aUri, String aMetadata, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetChannel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetChannel.InputParameter(inIndex++), aUri));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetChannel.InputParameter(inIndex++), aMetadata));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetChannel(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaInfo"></param>
        public void SyncProtocolInfo(out String aInfo)
        {
            SyncProtocolInfoLinnCoUkRadio1 sync = new SyncProtocolInfoLinnCoUkRadio1(this);
            BeginProtocolInfo(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aInfo = sync.Info();
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
        /// <param name="aaInfo"></param>
        public void EndProtocolInfo(IntPtr aAsyncHandle, out String aInfo)
        {
            uint index = 0;
            aInfo = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaState"></param>
        public void SyncTransportState(out String aState)
        {
            SyncTransportStateLinnCoUkRadio1 sync = new SyncTransportStateLinnCoUkRadio1(this);
            BeginTransportState(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aState = sync.State();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTransportState().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginTransportState(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionTransportState, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionTransportState.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaState"></param>
        public void EndTransportState(IntPtr aAsyncHandle, out String aState)
        {
            uint index = 0;
            aState = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaId"></param>
        public void SyncId(out uint aId)
        {
            SyncIdLinnCoUkRadio1 sync = new SyncIdLinnCoUkRadio1(this);
            BeginId(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aId = sync.Id();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndId().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginId(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionId, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionId.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaId"></param>
        public void EndId(IntPtr aAsyncHandle, out uint aId)
        {
            uint index = 0;
            aId = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaId"></param>
        /// <param name="aaUri"></param>
        public void SyncSetId(uint aId, String aUri)
        {
            SyncSetIdLinnCoUkRadio1 sync = new SyncSetIdLinnCoUkRadio1(this);
            BeginSetId(aId, aUri, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetId().</remarks>
        /// <param name="aaId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetId(uint aId, String aUri, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetId, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetId.InputParameter(inIndex++), aId));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetId.InputParameter(inIndex++), aUri));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetId(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaId"></param>
        /// <param name="aaMetadata"></param>
        public void SyncRead(uint aId, out String aMetadata)
        {
            SyncReadLinnCoUkRadio1 sync = new SyncReadLinnCoUkRadio1(this);
            BeginRead(aId, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aMetadata = sync.Metadata();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRead().</remarks>
        /// <param name="aaId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginRead(uint aId, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionRead, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionRead.InputParameter(inIndex++), aId));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionRead.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetadata"></param>
        public void EndRead(IntPtr aAsyncHandle, out String aMetadata)
        {
            uint index = 0;
            aMetadata = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdList"></param>
        /// <param name="aaMetadataList"></param>
        public void SyncReadList(String aIdList, out String aMetadataList)
        {
            SyncReadListLinnCoUkRadio1 sync = new SyncReadListLinnCoUkRadio1(this);
            BeginReadList(aIdList, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aMetadataList = sync.MetadataList();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndReadList().</remarks>
        /// <param name="aaIdList"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginReadList(String aIdList, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionReadList, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionReadList.InputParameter(inIndex++), aIdList));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionReadList.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetadataList"></param>
        public void EndReadList(IntPtr aAsyncHandle, out String aMetadataList)
        {
            uint index = 0;
            aMetadataList = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        public void SyncIdArray(out uint aIdArrayToken, out byte[] aIdArray)
        {
            SyncIdArrayLinnCoUkRadio1 sync = new SyncIdArrayLinnCoUkRadio1(this);
            BeginIdArray(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aIdArrayToken = sync.IdArrayToken();
            aIdArray = sync.IdArray();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdArray().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginIdArray(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionIdArray, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionIdArray.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentBinary((ParameterBinary)iActionIdArray.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        public void EndIdArray(IntPtr aAsyncHandle, out uint aIdArrayToken, out byte[] aIdArray)
        {
            uint index = 0;
            aIdArrayToken = Invocation.OutputUint(aAsyncHandle, index++);
            aIdArray = Invocation.OutputBinary(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArrayChanged"></param>
        public void SyncIdArrayChanged(uint aIdArrayToken, out bool aIdArrayChanged)
        {
            SyncIdArrayChangedLinnCoUkRadio1 sync = new SyncIdArrayChangedLinnCoUkRadio1(this);
            BeginIdArrayChanged(aIdArrayToken, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aIdArrayChanged = sync.IdArrayChanged();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdArrayChanged().</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginIdArrayChanged(uint aIdArrayToken, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionIdArrayChanged, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionIdArrayChanged.InputParameter(inIndex++), aIdArrayToken));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionIdArrayChanged.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdArrayChanged"></param>
        public void EndIdArrayChanged(IntPtr aAsyncHandle, out bool aIdArrayChanged)
        {
            uint index = 0;
            aIdArrayChanged = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdsMax"></param>
        public void SyncIdsMax(out uint aIdsMax)
        {
            SyncIdsMaxLinnCoUkRadio1 sync = new SyncIdsMaxLinnCoUkRadio1(this);
            BeginIdsMax(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aIdsMax = sync.IdsMax();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdsMax().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginIdsMax(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionIdsMax, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionIdsMax.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdsMax"></param>
        public void EndIdsMax(IntPtr aAsyncHandle, out uint aIdsMax)
        {
            uint index = 0;
            aIdsMax = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the ChannelUri state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aChannelUriChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyChannelUriChanged(CallbackPropertyChanged aChannelUriChanged)
        {
            lock (iPropertyLock)
            {
                iChannelUriChanged = aChannelUriChanged;
            }
        }

        private void ChannelUriPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iChannelUriChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ChannelMetadata state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aChannelMetadataChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyChannelMetadataChanged(CallbackPropertyChanged aChannelMetadataChanged)
        {
            lock (iPropertyLock)
            {
                iChannelMetadataChanged = aChannelMetadataChanged;
            }
        }

        private void ChannelMetadataPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iChannelMetadataChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TransportState state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aTransportStateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTransportStateChanged(CallbackPropertyChanged aTransportStateChanged)
        {
            lock (iPropertyLock)
            {
                iTransportStateChanged = aTransportStateChanged;
            }
        }

        private void TransportStatePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iTransportStateChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProtocolInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aProtocolInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProtocolInfoChanged(CallbackPropertyChanged aProtocolInfoChanged)
        {
            lock (iPropertyLock)
            {
                iProtocolInfoChanged = aProtocolInfoChanged;
            }
        }

        private void ProtocolInfoPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProtocolInfoChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Id state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aIdChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIdChanged(CallbackPropertyChanged aIdChanged)
        {
            lock (iPropertyLock)
            {
                iIdChanged = aIdChanged;
            }
        }

        private void IdPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iIdChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the IdArray state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aIdArrayChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIdArrayChanged(CallbackPropertyChanged aIdArrayChanged)
        {
            lock (iPropertyLock)
            {
                iIdArrayChanged = aIdArrayChanged;
            }
        }

        private void IdArrayPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iIdArrayChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the IdsMax state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aIdsMaxChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIdsMaxChanged(CallbackPropertyChanged aIdsMaxChanged)
        {
            lock (iPropertyLock)
            {
                iIdsMaxChanged = aIdsMaxChanged;
            }
        }

        private void IdsMaxPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iIdsMaxChanged);
            }
        }

        /// <summary>
        /// Query the value of the ChannelUri property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aChannelUri">Will be set to the value of the property</param>
        public String PropertyChannelUri()
        {
            PropertyReadLock();
            String val = iChannelUri.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ChannelMetadata property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aChannelMetadata">Will be set to the value of the property</param>
        public String PropertyChannelMetadata()
        {
            PropertyReadLock();
            String val = iChannelMetadata.Value();
            PropertyReadUnlock();
            return val;
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
            PropertyReadLock();
            String val = iTransportState.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProtocolInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProtocolInfo">Will be set to the value of the property</param>
        public String PropertyProtocolInfo()
        {
            PropertyReadLock();
            String val = iProtocolInfo.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the Id property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aId">Will be set to the value of the property</param>
        public uint PropertyId()
        {
            PropertyReadLock();
            uint val = iId.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the IdArray property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aIdArray">Will be set to the value of the property</param>
        public byte[] PropertyIdArray()
        {
            PropertyReadLock();
            byte[] val = iIdArray.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the IdsMax property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aIdsMax">Will be set to the value of the property</param>
        public uint PropertyIdsMax()
        {
            PropertyReadLock();
            uint val = iIdsMax.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkRadio1()
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
                iActionChannel.Dispose();
                iActionSetChannel.Dispose();
                iActionProtocolInfo.Dispose();
                iActionTransportState.Dispose();
                iActionId.Dispose();
                iActionSetId.Dispose();
                iActionRead.Dispose();
                iActionReadList.Dispose();
                iActionIdArray.Dispose();
                iActionIdArrayChanged.Dispose();
                iActionIdsMax.Dispose();
                iChannelUri.Dispose();
                iChannelMetadata.Dispose();
                iTransportState.Dispose();
                iProtocolInfo.Dispose();
                iId.Dispose();
                iIdArray.Dispose();
                iIdsMax.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

