using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkProduct2 : ICpProxy, IDisposable
    {
        void SyncType(out String aType);
        void BeginType(CpProxy.CallbackAsyncComplete aCallback);
        void EndType(IntPtr aAsyncHandle, out String aType);
        void SyncModel(out String aModel);
        void BeginModel(CpProxy.CallbackAsyncComplete aCallback);
        void EndModel(IntPtr aAsyncHandle, out String aModel);
        void SyncName(out String aName);
        void BeginName(CpProxy.CallbackAsyncComplete aCallback);
        void EndName(IntPtr aAsyncHandle, out String aName);
        void SyncSetName(String aName);
        void BeginSetName(String aName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetName(IntPtr aAsyncHandle);
        void SyncRoom(out String aRoom);
        void BeginRoom(CpProxy.CallbackAsyncComplete aCallback);
        void EndRoom(IntPtr aAsyncHandle, out String aRoom);
        void SyncSetRoom(String aRoom);
        void BeginSetRoom(String aRoom, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRoom(IntPtr aAsyncHandle);
        void SyncStandby(out bool aStandby);
        void BeginStandby(CpProxy.CallbackAsyncComplete aCallback);
        void EndStandby(IntPtr aAsyncHandle, out bool aStandby);
        void SyncSetStandby(bool aStandby);
        void BeginSetStandby(bool aStandby, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStandby(IntPtr aAsyncHandle);
        void SyncSourceCount(out uint aSourceCount);
        void BeginSourceCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceCount(IntPtr aAsyncHandle, out uint aSourceCount);
        void SyncSourceIndex(out uint aSourceIndex);
        void BeginSourceIndex(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceIndex(IntPtr aAsyncHandle, out uint aSourceIndex);
        void SyncSetSourceIndex(uint aSourceIndex);
        void BeginSetSourceIndex(uint aSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceIndex(IntPtr aAsyncHandle);
        void SyncSourceType(uint aSourceIndex, out String aSourceType);
        void BeginSourceType(uint aSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceType(IntPtr aAsyncHandle, out String aSourceType);
        void SetPropertyProductNameChanged(CpProxy.CallbackPropertyChanged aProductNameChanged);
        String PropertyProductName();
        void SetPropertyProductRoomChanged(CpProxy.CallbackPropertyChanged aProductRoomChanged);
        String PropertyProductRoom();
        void SetPropertyProductStandbyChanged(CpProxy.CallbackPropertyChanged aProductStandbyChanged);
        bool PropertyProductStandby();
        void SetPropertyProductSourceIndexChanged(CpProxy.CallbackPropertyChanged aProductSourceIndexChanged);
        uint PropertyProductSourceIndex();
    }

    internal class SyncTypeLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;
        private String iType;

        public SyncTypeLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        public String Type()
        {
            return iType;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndType(aAsyncHandle, out iType);
        }
    };

    internal class SyncModelLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;
        private String iModel;

        public SyncModelLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        public String Model()
        {
            return iModel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndModel(aAsyncHandle, out iModel);
        }
    };

    internal class SyncNameLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;
        private String iName;

        public SyncNameLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        public String Name()
        {
            return iName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndName(aAsyncHandle, out iName);
        }
    };

    internal class SyncSetNameLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;

        public SyncSetNameLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetName(aAsyncHandle);
        }
    };

    internal class SyncRoomLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;
        private String iRoom;

        public SyncRoomLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        public String Room()
        {
            return iRoom;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndRoom(aAsyncHandle, out iRoom);
        }
    };

    internal class SyncSetRoomLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;

        public SyncSetRoomLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetRoom(aAsyncHandle);
        }
    };

    internal class SyncStandbyLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;
        private bool iStandby;

        public SyncStandbyLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        public bool Standby()
        {
            return iStandby;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStandby(aAsyncHandle, out iStandby);
        }
    };

    internal class SyncSetStandbyLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;

        public SyncSetStandbyLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStandby(aAsyncHandle);
        }
    };

    internal class SyncSourceCountLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;
        private uint iSourceCount;

        public SyncSourceCountLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        public uint SourceCount()
        {
            return iSourceCount;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceCount(aAsyncHandle, out iSourceCount);
        }
    };

    internal class SyncSourceIndexLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;
        private uint iSourceIndex;

        public SyncSourceIndexLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        public uint SourceIndex()
        {
            return iSourceIndex;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceIndex(aAsyncHandle, out iSourceIndex);
        }
    };

    internal class SyncSetSourceIndexLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;

        public SyncSetSourceIndexLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetSourceIndex(aAsyncHandle);
        }
    };

    internal class SyncSourceTypeLinnCoUkProduct2 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct2 iService;
        private String iSourceType;

        public SyncSourceTypeLinnCoUkProduct2(CpProxyLinnCoUkProduct2 aProxy)
        {
            iService = aProxy;
        }
        public String SourceType()
        {
            return iSourceType;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceType(aAsyncHandle, out iSourceType);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Product:2 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkProduct2 : CpProxy, IDisposable, ICpProxyLinnCoUkProduct2
    {
        private Zapp.Core.Action iActionType;
        private Zapp.Core.Action iActionModel;
        private Zapp.Core.Action iActionName;
        private Zapp.Core.Action iActionSetName;
        private Zapp.Core.Action iActionRoom;
        private Zapp.Core.Action iActionSetRoom;
        private Zapp.Core.Action iActionStandby;
        private Zapp.Core.Action iActionSetStandby;
        private Zapp.Core.Action iActionSourceCount;
        private Zapp.Core.Action iActionSourceIndex;
        private Zapp.Core.Action iActionSetSourceIndex;
        private Zapp.Core.Action iActionSourceType;
        private PropertyString iProductName;
        private PropertyString iProductRoom;
        private PropertyBool iProductStandby;
        private PropertyUint iProductSourceIndex;
        private CallbackPropertyChanged iProductNameChanged;
        private CallbackPropertyChanged iProductRoomChanged;
        private CallbackPropertyChanged iProductStandbyChanged;
        private CallbackPropertyChanged iProductSourceIndexChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkProduct2(CpDevice aDevice)
            : base("linn-co-uk", "Product", 2, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionType = new Zapp.Core.Action("Type");
            param = new ParameterString("aType", allowedValues);
            iActionType.AddOutputParameter(param);

            iActionModel = new Zapp.Core.Action("Model");
            param = new ParameterString("aModel", allowedValues);
            iActionModel.AddOutputParameter(param);

            iActionName = new Zapp.Core.Action("Name");
            param = new ParameterString("aName", allowedValues);
            iActionName.AddOutputParameter(param);

            iActionSetName = new Zapp.Core.Action("SetName");
            param = new ParameterString("aName", allowedValues);
            iActionSetName.AddInputParameter(param);

            iActionRoom = new Zapp.Core.Action("Room");
            param = new ParameterString("aRoom", allowedValues);
            iActionRoom.AddOutputParameter(param);

            iActionSetRoom = new Zapp.Core.Action("SetRoom");
            param = new ParameterString("aRoom", allowedValues);
            iActionSetRoom.AddInputParameter(param);

            iActionStandby = new Zapp.Core.Action("Standby");
            param = new ParameterBool("aStandby");
            iActionStandby.AddOutputParameter(param);

            iActionSetStandby = new Zapp.Core.Action("SetStandby");
            param = new ParameterBool("aStandby");
            iActionSetStandby.AddInputParameter(param);

            iActionSourceCount = new Zapp.Core.Action("SourceCount");
            param = new ParameterUint("aSourceCount");
            iActionSourceCount.AddOutputParameter(param);

            iActionSourceIndex = new Zapp.Core.Action("SourceIndex");
            param = new ParameterUint("aSourceIndex");
            iActionSourceIndex.AddOutputParameter(param);

            iActionSetSourceIndex = new Zapp.Core.Action("SetSourceIndex");
            param = new ParameterUint("aSourceIndex");
            iActionSetSourceIndex.AddInputParameter(param);

            iActionSourceType = new Zapp.Core.Action("SourceType");
            param = new ParameterUint("aSourceIndex");
            iActionSourceType.AddInputParameter(param);
            param = new ParameterString("aSourceType", allowedValues);
            iActionSourceType.AddOutputParameter(param);

            iProductName = new PropertyString("ProductName", ProductNamePropertyChanged);
            AddProperty(iProductName);
            iProductRoom = new PropertyString("ProductRoom", ProductRoomPropertyChanged);
            AddProperty(iProductRoom);
            iProductStandby = new PropertyBool("ProductStandby", ProductStandbyPropertyChanged);
            AddProperty(iProductStandby);
            iProductSourceIndex = new PropertyUint("ProductSourceIndex", ProductSourceIndexPropertyChanged);
            AddProperty(iProductSourceIndex);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaType"></param>
        public void SyncType(out String aType)
        {
            SyncTypeLinnCoUkProduct2 sync = new SyncTypeLinnCoUkProduct2(this);
            BeginType(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aType = sync.Type();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndType().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginType(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionType, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionType.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaType"></param>
        public void EndType(IntPtr aAsyncHandle, out String aType)
        {
            uint index = 0;
            aType = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaModel"></param>
        public void SyncModel(out String aModel)
        {
            SyncModelLinnCoUkProduct2 sync = new SyncModelLinnCoUkProduct2(this);
            BeginModel(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aModel = sync.Model();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndModel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginModel(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionModel, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionModel.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaModel"></param>
        public void EndModel(IntPtr aAsyncHandle, out String aModel)
        {
            uint index = 0;
            aModel = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public void SyncName(out String aName)
        {
            SyncNameLinnCoUkProduct2 sync = new SyncNameLinnCoUkProduct2(this);
            BeginName(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aName = sync.Name();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndName().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginName(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionName, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionName.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaName"></param>
        public void EndName(IntPtr aAsyncHandle, out String aName)
        {
            uint index = 0;
            aName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public void SyncSetName(String aName)
        {
            SyncSetNameLinnCoUkProduct2 sync = new SyncSetNameLinnCoUkProduct2(this);
            BeginSetName(aName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetName().</remarks>
        /// <param name="aaName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetName(String aName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetName.InputParameter(inIndex++), aName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetName(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRoom"></param>
        public void SyncRoom(out String aRoom)
        {
            SyncRoomLinnCoUkProduct2 sync = new SyncRoomLinnCoUkProduct2(this);
            BeginRoom(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRoom = sync.Room();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRoom().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginRoom(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionRoom, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionRoom.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaRoom"></param>
        public void EndRoom(IntPtr aAsyncHandle, out String aRoom)
        {
            uint index = 0;
            aRoom = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRoom"></param>
        public void SyncSetRoom(String aRoom)
        {
            SyncSetRoomLinnCoUkProduct2 sync = new SyncSetRoomLinnCoUkProduct2(this);
            BeginSetRoom(aRoom, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRoom().</remarks>
        /// <param name="aaRoom"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetRoom(String aRoom, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetRoom, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetRoom.InputParameter(inIndex++), aRoom));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetRoom(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStandby"></param>
        public void SyncStandby(out bool aStandby)
        {
            SyncStandbyLinnCoUkProduct2 sync = new SyncStandbyLinnCoUkProduct2(this);
            BeginStandby(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aStandby = sync.Standby();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStandby().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStandby(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStandby, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionStandby.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStandby"></param>
        public void EndStandby(IntPtr aAsyncHandle, out bool aStandby)
        {
            uint index = 0;
            aStandby = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStandby"></param>
        public void SyncSetStandby(bool aStandby)
        {
            SyncSetStandbyLinnCoUkProduct2 sync = new SyncSetStandbyLinnCoUkProduct2(this);
            BeginSetStandby(aStandby, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStandby().</remarks>
        /// <param name="aaStandby"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStandby(bool aStandby, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStandby, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetStandby.InputParameter(inIndex++), aStandby));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStandby(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceCount"></param>
        public void SyncSourceCount(out uint aSourceCount)
        {
            SyncSourceCountLinnCoUkProduct2 sync = new SyncSourceCountLinnCoUkProduct2(this);
            BeginSourceCount(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceCount = sync.SourceCount();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceCount(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceCount, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSourceCount.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceCount"></param>
        public void EndSourceCount(IntPtr aAsyncHandle, out uint aSourceCount)
        {
            uint index = 0;
            aSourceCount = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public void SyncSourceIndex(out uint aSourceIndex)
        {
            SyncSourceIndexLinnCoUkProduct2 sync = new SyncSourceIndexLinnCoUkProduct2(this);
            BeginSourceIndex(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceIndex = sync.SourceIndex();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceIndex().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceIndex(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceIndex, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSourceIndex.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceIndex"></param>
        public void EndSourceIndex(IntPtr aAsyncHandle, out uint aSourceIndex)
        {
            uint index = 0;
            aSourceIndex = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public void SyncSetSourceIndex(uint aSourceIndex)
        {
            SyncSetSourceIndexLinnCoUkProduct2 sync = new SyncSetSourceIndexLinnCoUkProduct2(this);
            BeginSetSourceIndex(aSourceIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceIndex().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetSourceIndex(uint aSourceIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetSourceIndex, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetSourceIndex.InputParameter(inIndex++), aSourceIndex));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetSourceIndex(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceType"></param>
        public void SyncSourceType(uint aSourceIndex, out String aSourceType)
        {
            SyncSourceTypeLinnCoUkProduct2 sync = new SyncSourceTypeLinnCoUkProduct2(this);
            BeginSourceType(aSourceIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceType = sync.SourceType();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceType().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceType(uint aSourceIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceType, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSourceType.InputParameter(inIndex++), aSourceIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSourceType.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceType"></param>
        public void EndSourceType(IntPtr aAsyncHandle, out String aSourceType)
        {
            uint index = 0;
            aSourceType = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the ProductName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct2 instance will not overlap.</remarks>
        /// <param name="aProductNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductNameChanged(CallbackPropertyChanged aProductNameChanged)
        {
            lock (this)
            {
                iProductNameChanged = aProductNameChanged;
            }
        }

        private void ProductNamePropertyChanged()
        {
            lock (this)
            {
                if (iProductNameChanged != null)
                {
                    iProductNameChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductRoom state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct2 instance will not overlap.</remarks>
        /// <param name="aProductRoomChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductRoomChanged(CallbackPropertyChanged aProductRoomChanged)
        {
            lock (this)
            {
                iProductRoomChanged = aProductRoomChanged;
            }
        }

        private void ProductRoomPropertyChanged()
        {
            lock (this)
            {
                if (iProductRoomChanged != null)
                {
                    iProductRoomChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductStandby state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct2 instance will not overlap.</remarks>
        /// <param name="aProductStandbyChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductStandbyChanged(CallbackPropertyChanged aProductStandbyChanged)
        {
            lock (this)
            {
                iProductStandbyChanged = aProductStandbyChanged;
            }
        }

        private void ProductStandbyPropertyChanged()
        {
            lock (this)
            {
                if (iProductStandbyChanged != null)
                {
                    iProductStandbyChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductSourceIndex state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct2 instance will not overlap.</remarks>
        /// <param name="aProductSourceIndexChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductSourceIndexChanged(CallbackPropertyChanged aProductSourceIndexChanged)
        {
            lock (this)
            {
                iProductSourceIndexChanged = aProductSourceIndexChanged;
            }
        }

        private void ProductSourceIndexPropertyChanged()
        {
            lock (this)
            {
                if (iProductSourceIndexChanged != null)
                {
                    iProductSourceIndexChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the ProductName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductName">Will be set to the value of the property</param>
        public String PropertyProductName()
        {
            return iProductName.Value();
        }

        /// <summary>
        /// Query the value of the ProductRoom property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductRoom">Will be set to the value of the property</param>
        public String PropertyProductRoom()
        {
            return iProductRoom.Value();
        }

        /// <summary>
        /// Query the value of the ProductStandby property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductStandby">Will be set to the value of the property</param>
        public bool PropertyProductStandby()
        {
            return iProductStandby.Value();
        }

        /// <summary>
        /// Query the value of the ProductSourceIndex property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductSourceIndex">Will be set to the value of the property</param>
        public uint PropertyProductSourceIndex()
        {
            return iProductSourceIndex.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkProduct2()
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
                iActionType.Dispose();
                iActionModel.Dispose();
                iActionName.Dispose();
                iActionSetName.Dispose();
                iActionRoom.Dispose();
                iActionSetRoom.Dispose();
                iActionStandby.Dispose();
                iActionSetStandby.Dispose();
                iActionSourceCount.Dispose();
                iActionSourceIndex.Dispose();
                iActionSetSourceIndex.Dispose();
                iActionSourceType.Dispose();
                iProductName.Dispose();
                iProductRoom.Dispose();
                iProductStandby.Dispose();
                iProductSourceIndex.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

