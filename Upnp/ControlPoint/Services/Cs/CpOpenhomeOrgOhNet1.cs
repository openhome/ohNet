using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyOpenhomeOrgOhNet1 : ICpProxy, IDisposable
    {
        void SyncGetWebSocketPort(out uint aPort);
        void BeginGetWebSocketPort(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetWebSocketPort(IntPtr aAsyncHandle, out uint aPort);
    }

    internal class SyncGetWebSocketPortOpenhomeOrgOhNet1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgOhNet1 iService;
        private uint iPort;

        public SyncGetWebSocketPortOpenhomeOrgOhNet1(CpProxyOpenhomeOrgOhNet1 aProxy)
        {
            iService = aProxy;
        }
        public uint Port()
        {
            return iPort;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetWebSocketPort(aAsyncHandle, out iPort);
        }
    };

    /// <summary>
    /// Proxy for the openhome.org:OhNet:1 UPnP service
    /// </summary>
    public class CpProxyOpenhomeOrgOhNet1 : CpProxy, IDisposable, ICpProxyOpenhomeOrgOhNet1
    {
        private Zapp.Core.Action iActionGetWebSocketPort;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyOpenhomeOrgOhNet1(CpDevice aDevice)
            : base("openhome-org", "OhNet", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            

            iActionGetWebSocketPort = new Zapp.Core.Action("GetWebSocketPort");
            param = new ParameterUint("Port");
            iActionGetWebSocketPort.AddOutputParameter(param);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aPort"></param>
        public void SyncGetWebSocketPort(out uint aPort)
        {
            SyncGetWebSocketPortOpenhomeOrgOhNet1 sync = new SyncGetWebSocketPortOpenhomeOrgOhNet1(this);
            BeginGetWebSocketPort(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aPort = sync.Port();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetWebSocketPort().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetWebSocketPort(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetWebSocketPort, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetWebSocketPort.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aPort"></param>
        public void EndGetWebSocketPort(IntPtr aAsyncHandle, out uint aPort)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aPort = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyOpenhomeOrgOhNet1()
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
                iActionGetWebSocketPort.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

