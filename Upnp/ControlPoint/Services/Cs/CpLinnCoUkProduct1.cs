using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkProduct1 : ICpProxy, IDisposable
    {
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
        void SetPropertyRoomChanged(CpProxy.CallbackPropertyChanged aRoomChanged);
        String PropertyRoom();
        void SetPropertyStandbyChanged(CpProxy.CallbackPropertyChanged aStandbyChanged);
        bool PropertyStandby();
    }

    internal class SyncRoomLinnCoUkProduct1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct1 iService;
        private String iRoom;

        public SyncRoomLinnCoUkProduct1(CpProxyLinnCoUkProduct1 aProxy)
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

    internal class SyncSetRoomLinnCoUkProduct1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct1 iService;

        public SyncSetRoomLinnCoUkProduct1(CpProxyLinnCoUkProduct1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetRoom(aAsyncHandle);
        }
    };

    internal class SyncStandbyLinnCoUkProduct1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct1 iService;
        private bool iStandby;

        public SyncStandbyLinnCoUkProduct1(CpProxyLinnCoUkProduct1 aProxy)
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

    internal class SyncSetStandbyLinnCoUkProduct1 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct1 iService;

        public SyncSetStandbyLinnCoUkProduct1(CpProxyLinnCoUkProduct1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStandby(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Product:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkProduct1 : CpProxy, IDisposable, ICpProxyLinnCoUkProduct1
    {
        private Zapp.Core.Action iActionRoom;
        private Zapp.Core.Action iActionSetRoom;
        private Zapp.Core.Action iActionStandby;
        private Zapp.Core.Action iActionSetStandby;
        private PropertyString iRoom;
        private PropertyBool iStandby;
        private CallbackPropertyChanged iRoomChanged;
        private CallbackPropertyChanged iStandbyChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkProduct1(CpDevice aDevice)
            : base("linn-co-uk", "Product", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

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

            iRoom = new PropertyString("Room", RoomPropertyChanged);
            AddProperty(iRoom);
            iStandby = new PropertyBool("Standby", StandbyPropertyChanged);
            AddProperty(iStandby);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRoom"></param>
        public void SyncRoom(out String aRoom)
        {
            SyncRoomLinnCoUkProduct1 sync = new SyncRoomLinnCoUkProduct1(this);
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
            SyncSetRoomLinnCoUkProduct1 sync = new SyncSetRoomLinnCoUkProduct1(this);
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
            SyncStandbyLinnCoUkProduct1 sync = new SyncStandbyLinnCoUkProduct1(this);
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
            SyncSetStandbyLinnCoUkProduct1 sync = new SyncSetStandbyLinnCoUkProduct1(this);
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
        /// Set a delegate to be run when the Room state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct1 instance will not overlap.</remarks>
        /// <param name="aRoomChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyRoomChanged(CallbackPropertyChanged aRoomChanged)
        {
            lock (iPropertyLock)
            {
                iRoomChanged = aRoomChanged;
            }
        }

        private void RoomPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iRoomChanged != null)
                {
                    iRoomChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Standby state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct1 instance will not overlap.</remarks>
        /// <param name="aStandbyChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStandbyChanged(CallbackPropertyChanged aStandbyChanged)
        {
            lock (iPropertyLock)
            {
                iStandbyChanged = aStandbyChanged;
            }
        }

        private void StandbyPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iStandbyChanged != null)
                {
                    iStandbyChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the Room property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aRoom">Will be set to the value of the property</param>
        public String PropertyRoom()
        {
            PropertyReadLock();
            String val = iRoom.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the Standby property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStandby">Will be set to the value of the property</param>
        public bool PropertyStandby()
        {
            PropertyReadLock();
            bool val = iStandby.Value();
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

        ~CpProxyLinnCoUkProduct1()
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
                iActionRoom.Dispose();
                iActionSetRoom.Dispose();
                iActionStandby.Dispose();
                iActionSetStandby.Dispose();
                iRoom.Dispose();
                iStandby.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

