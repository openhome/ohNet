using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestLights1 : ICpProxy, IDisposable
    {
        void SyncGetCount(out uint aCount);
        void BeginGetCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetCount(IntPtr aAsyncHandle, out uint aCount);
        void SyncGetRoom(uint aIndex, out String aRoomName);
        void BeginGetRoom(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRoom(IntPtr aAsyncHandle, out String aRoomName);
        void SyncGetName(uint aIndex, out String aFriendlyName);
        void BeginGetName(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetName(IntPtr aAsyncHandle, out String aFriendlyName);
        void SyncGetPosition(uint aIndex, out uint aX, out uint aY, out uint aZ);
        void BeginGetPosition(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetPosition(IntPtr aAsyncHandle, out uint aX, out uint aY, out uint aZ);
        void SyncSetColor(uint aIndex, uint aColor);
        void BeginSetColor(uint aIndex, uint aColor, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetColor(IntPtr aAsyncHandle);
        void SyncGetColor(uint aIndex, out uint aColor);
        void BeginGetColor(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetColor(IntPtr aAsyncHandle, out uint aColor);
        void SyncGetColorComponents(uint aColor, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue);
        void BeginGetColorComponents(uint aColor, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetColorComponents(IntPtr aAsyncHandle, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue);
    }

    internal class SyncGetCountZappOrgTestLights1 : SyncProxyAction
    {
        private CpProxyZappOrgTestLights1 iService;
        private uint iCount;

        public SyncGetCountZappOrgTestLights1(CpProxyZappOrgTestLights1 aProxy)
        {
            iService = aProxy;
        }
        public uint Count()
        {
            return iCount;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetCount(aAsyncHandle, out iCount);
        }
    };

    internal class SyncGetRoomZappOrgTestLights1 : SyncProxyAction
    {
        private CpProxyZappOrgTestLights1 iService;
        private String iRoomName;

        public SyncGetRoomZappOrgTestLights1(CpProxyZappOrgTestLights1 aProxy)
        {
            iService = aProxy;
        }
        public String RoomName()
        {
            return iRoomName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRoom(aAsyncHandle, out iRoomName);
        }
    };

    internal class SyncGetNameZappOrgTestLights1 : SyncProxyAction
    {
        private CpProxyZappOrgTestLights1 iService;
        private String iFriendlyName;

        public SyncGetNameZappOrgTestLights1(CpProxyZappOrgTestLights1 aProxy)
        {
            iService = aProxy;
        }
        public String FriendlyName()
        {
            return iFriendlyName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetName(aAsyncHandle, out iFriendlyName);
        }
    };

    internal class SyncGetPositionZappOrgTestLights1 : SyncProxyAction
    {
        private CpProxyZappOrgTestLights1 iService;
        private uint iX;
        private uint iY;
        private uint iZ;

        public SyncGetPositionZappOrgTestLights1(CpProxyZappOrgTestLights1 aProxy)
        {
            iService = aProxy;
        }
        public uint X()
        {
            return iX;
        }
        public uint Y()
        {
            return iY;
        }
        public uint Z()
        {
            return iZ;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetPosition(aAsyncHandle, out iX, out iY, out iZ);
        }
    };

    internal class SyncSetColorZappOrgTestLights1 : SyncProxyAction
    {
        private CpProxyZappOrgTestLights1 iService;

        public SyncSetColorZappOrgTestLights1(CpProxyZappOrgTestLights1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetColor(aAsyncHandle);
        }
    };

    internal class SyncGetColorZappOrgTestLights1 : SyncProxyAction
    {
        private CpProxyZappOrgTestLights1 iService;
        private uint iColor;

        public SyncGetColorZappOrgTestLights1(CpProxyZappOrgTestLights1 aProxy)
        {
            iService = aProxy;
        }
        public uint Color()
        {
            return iColor;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetColor(aAsyncHandle, out iColor);
        }
    };

    internal class SyncGetColorComponentsZappOrgTestLights1 : SyncProxyAction
    {
        private CpProxyZappOrgTestLights1 iService;
        private uint iBrightness;
        private uint iRed;
        private uint iGreen;
        private uint iBlue;

        public SyncGetColorComponentsZappOrgTestLights1(CpProxyZappOrgTestLights1 aProxy)
        {
            iService = aProxy;
        }
        public uint Brightness()
        {
            return iBrightness;
        }
        public uint Red()
        {
            return iRed;
        }
        public uint Green()
        {
            return iGreen;
        }
        public uint Blue()
        {
            return iBlue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetColorComponents(aAsyncHandle, out iBrightness, out iRed, out iGreen, out iBlue);
        }
    };

    /// <summary>
    /// Proxy for the zapp.org:TestLights:1 UPnP service
    /// </summary>
    public class CpProxyZappOrgTestLights1 : CpProxy, IDisposable, ICpProxyZappOrgTestLights1
    {
        private Zapp.Core.Action iActionGetCount;
        private Zapp.Core.Action iActionGetRoom;
        private Zapp.Core.Action iActionGetName;
        private Zapp.Core.Action iActionGetPosition;
        private Zapp.Core.Action iActionSetColor;
        private Zapp.Core.Action iActionGetColor;
        private Zapp.Core.Action iActionGetColorComponents;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestLights1(CpDevice aDevice)
            : base("zapp-org", "TestLights", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionGetCount = new Zapp.Core.Action("GetCount");
            param = new ParameterUint("Count");
            iActionGetCount.AddOutputParameter(param);

            iActionGetRoom = new Zapp.Core.Action("GetRoom");
            param = new ParameterUint("Index");
            iActionGetRoom.AddInputParameter(param);
            param = new ParameterString("RoomName", allowedValues);
            iActionGetRoom.AddOutputParameter(param);

            iActionGetName = new Zapp.Core.Action("GetName");
            param = new ParameterUint("Index");
            iActionGetName.AddInputParameter(param);
            param = new ParameterString("FriendlyName", allowedValues);
            iActionGetName.AddOutputParameter(param);

            iActionGetPosition = new Zapp.Core.Action("GetPosition");
            param = new ParameterUint("Index");
            iActionGetPosition.AddInputParameter(param);
            param = new ParameterUint("X");
            iActionGetPosition.AddOutputParameter(param);
            param = new ParameterUint("Y");
            iActionGetPosition.AddOutputParameter(param);
            param = new ParameterUint("Z");
            iActionGetPosition.AddOutputParameter(param);

            iActionSetColor = new Zapp.Core.Action("SetColor");
            param = new ParameterUint("Index");
            iActionSetColor.AddInputParameter(param);
            param = new ParameterUint("Color");
            iActionSetColor.AddInputParameter(param);

            iActionGetColor = new Zapp.Core.Action("GetColor");
            param = new ParameterUint("Index");
            iActionGetColor.AddInputParameter(param);
            param = new ParameterUint("Color");
            iActionGetColor.AddOutputParameter(param);

            iActionGetColorComponents = new Zapp.Core.Action("GetColorComponents");
            param = new ParameterUint("Color");
            iActionGetColorComponents.AddInputParameter(param);
            param = new ParameterUint("Brightness");
            iActionGetColorComponents.AddOutputParameter(param);
            param = new ParameterUint("Red");
            iActionGetColorComponents.AddOutputParameter(param);
            param = new ParameterUint("Green");
            iActionGetColorComponents.AddOutputParameter(param);
            param = new ParameterUint("Blue");
            iActionGetColorComponents.AddOutputParameter(param);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aCount"></param>
        public void SyncGetCount(out uint aCount)
        {
            SyncGetCountZappOrgTestLights1 sync = new SyncGetCountZappOrgTestLights1(this);
            BeginGetCount(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCount = sync.Count();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetCount(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetCount, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetCount.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCount"></param>
        public void EndGetCount(IntPtr aAsyncHandle, out uint aCount)
        {
            uint index = 0;
            aCount = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aRoomName"></param>
        public void SyncGetRoom(uint aIndex, out String aRoomName)
        {
            SyncGetRoomZappOrgTestLights1 sync = new SyncGetRoomZappOrgTestLights1(this);
            BeginGetRoom(aIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRoomName = sync.RoomName();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRoom().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRoom(uint aIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRoom, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetRoom.InputParameter(inIndex++), aIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetRoom.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRoomName"></param>
        public void EndGetRoom(IntPtr aAsyncHandle, out String aRoomName)
        {
            uint index = 0;
            aRoomName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aFriendlyName"></param>
        public void SyncGetName(uint aIndex, out String aFriendlyName)
        {
            SyncGetNameZappOrgTestLights1 sync = new SyncGetNameZappOrgTestLights1(this);
            BeginGetName(aIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aFriendlyName = sync.FriendlyName();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetName().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetName(uint aIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetName.InputParameter(inIndex++), aIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetName.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aFriendlyName"></param>
        public void EndGetName(IntPtr aAsyncHandle, out String aFriendlyName)
        {
            uint index = 0;
            aFriendlyName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aX"></param>
        /// <param name="aY"></param>
        /// <param name="aZ"></param>
        public void SyncGetPosition(uint aIndex, out uint aX, out uint aY, out uint aZ)
        {
            SyncGetPositionZappOrgTestLights1 sync = new SyncGetPositionZappOrgTestLights1(this);
            BeginGetPosition(aIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aX = sync.X();
            aY = sync.Y();
            aZ = sync.Z();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetPosition().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetPosition(uint aIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetPosition, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetPosition.InputParameter(inIndex++), aIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetPosition.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetPosition.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetPosition.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aX"></param>
        /// <param name="aY"></param>
        /// <param name="aZ"></param>
        public void EndGetPosition(IntPtr aAsyncHandle, out uint aX, out uint aY, out uint aZ)
        {
            uint index = 0;
            aX = Invocation.OutputUint(aAsyncHandle, index++);
            aY = Invocation.OutputUint(aAsyncHandle, index++);
            aZ = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aColor"></param>
        public void SyncSetColor(uint aIndex, uint aColor)
        {
            SyncSetColorZappOrgTestLights1 sync = new SyncSetColorZappOrgTestLights1(this);
            BeginSetColor(aIndex, aColor, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetColor().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aColor"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetColor(uint aIndex, uint aColor, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetColor, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetColor.InputParameter(inIndex++), aIndex));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetColor.InputParameter(inIndex++), aColor));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetColor(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aColor"></param>
        public void SyncGetColor(uint aIndex, out uint aColor)
        {
            SyncGetColorZappOrgTestLights1 sync = new SyncGetColorZappOrgTestLights1(this);
            BeginGetColor(aIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aColor = sync.Color();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetColor().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetColor(uint aIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetColor, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetColor.InputParameter(inIndex++), aIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColor.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aColor"></param>
        public void EndGetColor(IntPtr aAsyncHandle, out uint aColor)
        {
            uint index = 0;
            aColor = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aColor"></param>
        /// <param name="aBrightness"></param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        public void SyncGetColorComponents(uint aColor, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue)
        {
            SyncGetColorComponentsZappOrgTestLights1 sync = new SyncGetColorComponentsZappOrgTestLights1(this);
            BeginGetColorComponents(aColor, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aBrightness = sync.Brightness();
            aRed = sync.Red();
            aGreen = sync.Green();
            aBlue = sync.Blue();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetColorComponents().</remarks>
        /// <param name="aColor"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetColorComponents(uint aColor, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetColorComponents, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetColorComponents.InputParameter(inIndex++), aColor));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColorComponents.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColorComponents.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColorComponents.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColorComponents.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aBrightness"></param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        public void EndGetColorComponents(IntPtr aAsyncHandle, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue)
        {
            uint index = 0;
            aBrightness = Invocation.OutputUint(aAsyncHandle, index++);
            aRed = Invocation.OutputUint(aAsyncHandle, index++);
            aGreen = Invocation.OutputUint(aAsyncHandle, index++);
            aBlue = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestLights1()
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
                iActionGetCount.Dispose();
                iActionGetRoom.Dispose();
                iActionGetName.Dispose();
                iActionGetPosition.Dispose();
                iActionSetColor.Dispose();
                iActionGetColor.Dispose();
                iActionGetColorComponents.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

