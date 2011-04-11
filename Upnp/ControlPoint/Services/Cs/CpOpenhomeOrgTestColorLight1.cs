using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyOpenhomeOrgTestColorLight1 : ICpProxy, IDisposable
    {
        void SyncGetName(out String aFriendlyName);
        void BeginGetName(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetName(IntPtr aAsyncHandle, out String aFriendlyName);
        void SyncSetColor(uint aRed, uint aGreen, uint aBlue);
        void BeginSetColor(uint aRed, uint aGreen, uint aBlue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetColor(IntPtr aAsyncHandle);
        void SyncGetColor(out uint aRed, out uint aGreen, out uint aBlue);
        void BeginGetColor(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetColor(IntPtr aAsyncHandle, out uint aRed, out uint aGreen, out uint aBlue);
        void SyncGetMaxColors(out uint aRed, out uint aGreen, out uint aBlue);
        void BeginGetMaxColors(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetMaxColors(IntPtr aAsyncHandle, out uint aRed, out uint aGreen, out uint aBlue);
    }

    internal class SyncGetNameOpenhomeOrgTestColorLight1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestColorLight1 iService;
        private String iFriendlyName;

        public SyncGetNameOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1 aProxy)
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

    internal class SyncSetColorOpenhomeOrgTestColorLight1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestColorLight1 iService;

        public SyncSetColorOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetColor(aAsyncHandle);
        }
    };

    internal class SyncGetColorOpenhomeOrgTestColorLight1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestColorLight1 iService;
        private uint iRed;
        private uint iGreen;
        private uint iBlue;

        public SyncGetColorOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1 aProxy)
        {
            iService = aProxy;
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
            iService.EndGetColor(aAsyncHandle, out iRed, out iGreen, out iBlue);
        }
    };

    internal class SyncGetMaxColorsOpenhomeOrgTestColorLight1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgTestColorLight1 iService;
        private uint iRed;
        private uint iGreen;
        private uint iBlue;

        public SyncGetMaxColorsOpenhomeOrgTestColorLight1(CpProxyOpenhomeOrgTestColorLight1 aProxy)
        {
            iService = aProxy;
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
            iService.EndGetMaxColors(aAsyncHandle, out iRed, out iGreen, out iBlue);
        }
    };

    /// <summary>
    /// Proxy for the openhome.org:TestColorLight:1 UPnP service
    /// </summary>
    public class CpProxyOpenhomeOrgTestColorLight1 : CpProxy, IDisposable, ICpProxyOpenhomeOrgTestColorLight1
    {
        private Zapp.Core.Action iActionGetName;
        private Zapp.Core.Action iActionSetColor;
        private Zapp.Core.Action iActionGetColor;
        private Zapp.Core.Action iActionGetMaxColors;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyOpenhomeOrgTestColorLight1(CpDevice aDevice)
            : base("openhome-org", "TestColorLight", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionGetName = new Zapp.Core.Action("GetName");
            param = new ParameterString("FriendlyName", allowedValues);
            iActionGetName.AddOutputParameter(param);

            iActionSetColor = new Zapp.Core.Action("SetColor");
            param = new ParameterUint("Red");
            iActionSetColor.AddInputParameter(param);
            param = new ParameterUint("Green");
            iActionSetColor.AddInputParameter(param);
            param = new ParameterUint("Blue");
            iActionSetColor.AddInputParameter(param);

            iActionGetColor = new Zapp.Core.Action("GetColor");
            param = new ParameterUint("Red");
            iActionGetColor.AddOutputParameter(param);
            param = new ParameterUint("Green");
            iActionGetColor.AddOutputParameter(param);
            param = new ParameterUint("Blue");
            iActionGetColor.AddOutputParameter(param);

            iActionGetMaxColors = new Zapp.Core.Action("GetMaxColors");
            param = new ParameterUint("Red");
            iActionGetMaxColors.AddOutputParameter(param);
            param = new ParameterUint("Green");
            iActionGetMaxColors.AddOutputParameter(param);
            param = new ParameterUint("Blue");
            iActionGetMaxColors.AddOutputParameter(param);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aFriendlyName"></param>
        public void SyncGetName(out String aFriendlyName)
        {
            SyncGetNameOpenhomeOrgTestColorLight1 sync = new SyncGetNameOpenhomeOrgTestColorLight1(this);
            BeginGetName(sync.AsyncComplete());
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
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetName(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetName, aCallback);
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
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aFriendlyName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        public void SyncSetColor(uint aRed, uint aGreen, uint aBlue)
        {
            SyncSetColorOpenhomeOrgTestColorLight1 sync = new SyncSetColorOpenhomeOrgTestColorLight1(this);
            BeginSetColor(aRed, aGreen, aBlue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetColor().</remarks>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetColor(uint aRed, uint aGreen, uint aBlue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetColor, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetColor.InputParameter(inIndex++), aRed));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetColor.InputParameter(inIndex++), aGreen));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetColor.InputParameter(inIndex++), aBlue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetColor(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        public void SyncGetColor(out uint aRed, out uint aGreen, out uint aBlue)
        {
            SyncGetColorOpenhomeOrgTestColorLight1 sync = new SyncGetColorOpenhomeOrgTestColorLight1(this);
            BeginGetColor(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRed = sync.Red();
            aGreen = sync.Green();
            aBlue = sync.Blue();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetColor().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetColor(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetColor, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColor.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColor.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColor.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        public void EndGetColor(IntPtr aAsyncHandle, out uint aRed, out uint aGreen, out uint aBlue)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aRed = Invocation.OutputUint(aAsyncHandle, index++);
            aGreen = Invocation.OutputUint(aAsyncHandle, index++);
            aBlue = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        public void SyncGetMaxColors(out uint aRed, out uint aGreen, out uint aBlue)
        {
            SyncGetMaxColorsOpenhomeOrgTestColorLight1 sync = new SyncGetMaxColorsOpenhomeOrgTestColorLight1(this);
            BeginGetMaxColors(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRed = sync.Red();
            aGreen = sync.Green();
            aBlue = sync.Blue();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetMaxColors().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetMaxColors(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetMaxColors, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetMaxColors.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetMaxColors.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetMaxColors.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        public void EndGetMaxColors(IntPtr aAsyncHandle, out uint aRed, out uint aGreen, out uint aBlue)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
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

        ~CpProxyOpenhomeOrgTestColorLight1()
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
                iActionGetName.Dispose();
                iActionSetColor.Dispose();
                iActionGetColor.Dispose();
                iActionGetMaxColors.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

