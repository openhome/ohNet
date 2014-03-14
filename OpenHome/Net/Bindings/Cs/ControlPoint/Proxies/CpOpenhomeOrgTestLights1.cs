using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyOpenhomeOrgTestLights1 : ICpProxy, IDisposable
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

    internal class SyncGetCountOpenhomeOrgTestLights1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestLights1 iService;
        private uint iCount;

        public SyncGetCountOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
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

    internal class SyncGetRoomOpenhomeOrgTestLights1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestLights1 iService;
        private String iRoomName;

        public SyncGetRoomOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
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

    internal class SyncGetNameOpenhomeOrgTestLights1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestLights1 iService;
        private String iFriendlyName;

        public SyncGetNameOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
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

    internal class SyncGetPositionOpenhomeOrgTestLights1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestLights1 iService;
        private uint iX;
        private uint iY;
        private uint iZ;

        public SyncGetPositionOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
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

    internal class SyncSetColorOpenhomeOrgTestLights1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestLights1 iService;

        public SyncSetColorOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetColor(aAsyncHandle);
        }
    };

    internal class SyncGetColorOpenhomeOrgTestLights1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestLights1 iService;
        private uint iColor;

        public SyncGetColorOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
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

    internal class SyncGetColorComponentsOpenhomeOrgTestLights1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestLights1 iService;
        private uint iBrightness;
        private uint iRed;
        private uint iGreen;
        private uint iBlue;

        public SyncGetColorComponentsOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
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
    /// Proxy for the openhome.org:TestLights:1 UPnP service
    /// </summary>
    public class CpProxyOpenhomeOrgTestLights1 : CpProxy, IDisposable, ICpProxyOpenhomeOrgTestLights1
    {
        private OpenHome.Net.Core.Action iActionGetCount;
        private OpenHome.Net.Core.Action iActionGetRoom;
        private OpenHome.Net.Core.Action iActionGetName;
        private OpenHome.Net.Core.Action iActionGetPosition;
        private OpenHome.Net.Core.Action iActionSetColor;
        private OpenHome.Net.Core.Action iActionGetColor;
        private OpenHome.Net.Core.Action iActionGetColorComponents;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyOpenhomeOrgTestLights1(CpDevice aDevice)
            : base("openhome-org", "TestLights", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionGetCount = new OpenHome.Net.Core.Action("GetCount");
            param = new ParameterUint("Count");
            iActionGetCount.AddOutputParameter(param);

            iActionGetRoom = new OpenHome.Net.Core.Action("GetRoom");
            param = new ParameterUint("Index");
            iActionGetRoom.AddInputParameter(param);
            param = new ParameterString("RoomName", allowedValues);
            iActionGetRoom.AddOutputParameter(param);

            iActionGetName = new OpenHome.Net.Core.Action("GetName");
            param = new ParameterUint("Index");
            iActionGetName.AddInputParameter(param);
            param = new ParameterString("FriendlyName", allowedValues);
            iActionGetName.AddOutputParameter(param);

            iActionGetPosition = new OpenHome.Net.Core.Action("GetPosition");
            param = new ParameterUint("Index");
            iActionGetPosition.AddInputParameter(param);
            param = new ParameterUint("X");
            iActionGetPosition.AddOutputParameter(param);
            param = new ParameterUint("Y");
            iActionGetPosition.AddOutputParameter(param);
            param = new ParameterUint("Z");
            iActionGetPosition.AddOutputParameter(param);

            iActionSetColor = new OpenHome.Net.Core.Action("SetColor");
            param = new ParameterUint("Index");
            iActionSetColor.AddInputParameter(param);
            param = new ParameterUint("Color");
            iActionSetColor.AddInputParameter(param);

            iActionGetColor = new OpenHome.Net.Core.Action("GetColor");
            param = new ParameterUint("Index");
            iActionGetColor.AddInputParameter(param);
            param = new ParameterUint("Color");
            iActionGetColor.AddOutputParameter(param);

            iActionGetColorComponents = new OpenHome.Net.Core.Action("GetColorComponents");
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
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aCount"></param>
        public void SyncGetCount(out uint aCount)
        {
            SyncGetCountOpenhomeOrgTestLights1 sync = new SyncGetCountOpenhomeOrgTestLights1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncGetRoomOpenhomeOrgTestLights1 sync = new SyncGetRoomOpenhomeOrgTestLights1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncGetNameOpenhomeOrgTestLights1 sync = new SyncGetNameOpenhomeOrgTestLights1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncGetPositionOpenhomeOrgTestLights1 sync = new SyncGetPositionOpenhomeOrgTestLights1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncSetColorOpenhomeOrgTestLights1 sync = new SyncSetColorOpenhomeOrgTestLights1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncGetColorOpenhomeOrgTestLights1 sync = new SyncGetColorOpenhomeOrgTestLights1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            SyncGetColorComponentsOpenhomeOrgTestLights1 sync = new SyncGetColorComponentsOpenhomeOrgTestLights1(this);
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
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DisposeProxy();
                iHandle = IntPtr.Zero;
            }
            iActionGetCount.Dispose();
            iActionGetRoom.Dispose();
            iActionGetName.Dispose();
            iActionGetPosition.Dispose();
            iActionSetColor.Dispose();
            iActionGetColor.Dispose();
            iActionGetColorComponents.Dispose();
        }
    }
}

