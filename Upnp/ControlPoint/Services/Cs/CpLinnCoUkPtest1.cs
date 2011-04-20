using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkPtest1 : ICpProxy, IDisposable
    {
        void SyncTestComPort(uint aPort, out bool aResult);
        void BeginTestComPort(uint aPort, CpProxy.CallbackAsyncComplete aCallback);
        void EndTestComPort(IntPtr aAsyncHandle, out bool aResult);
        void SyncLedsOn();
        void BeginLedsOn(CpProxy.CallbackAsyncComplete aCallback);
        void EndLedsOn(IntPtr aAsyncHandle);
        void SyncLedsOff();
        void BeginLedsOff(CpProxy.CallbackAsyncComplete aCallback);
        void EndLedsOff(IntPtr aAsyncHandle);
    }

    internal class SyncTestComPortLinnCoUkPtest1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPtest1 iService;
        private bool iResult;

        public SyncTestComPortLinnCoUkPtest1(CpProxyLinnCoUkPtest1 aProxy)
        {
            iService = aProxy;
        }
        public bool Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndTestComPort(aAsyncHandle, out iResult);
        }
    };

    internal class SyncLedsOnLinnCoUkPtest1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPtest1 iService;

        public SyncLedsOnLinnCoUkPtest1(CpProxyLinnCoUkPtest1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndLedsOn(aAsyncHandle);
        }
    };

    internal class SyncLedsOffLinnCoUkPtest1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPtest1 iService;

        public SyncLedsOffLinnCoUkPtest1(CpProxyLinnCoUkPtest1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndLedsOff(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Ptest:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkPtest1 : CpProxy, IDisposable, ICpProxyLinnCoUkPtest1
    {
        private Zapp.Core.Action iActionTestComPort;
        private Zapp.Core.Action iActionLedsOn;
        private Zapp.Core.Action iActionLedsOff;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkPtest1(CpDevice aDevice)
            : base("linn-co-uk", "Ptest", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            

            iActionTestComPort = new Zapp.Core.Action("TestComPort");
            param = new ParameterUint("aPort");
            iActionTestComPort.AddInputParameter(param);
            param = new ParameterBool("aResult");
            iActionTestComPort.AddOutputParameter(param);

            iActionLedsOn = new Zapp.Core.Action("LedsOn");

            iActionLedsOff = new Zapp.Core.Action("LedsOff");
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPort"></param>
        /// <param name="aaResult"></param>
        public void SyncTestComPort(uint aPort, out bool aResult)
        {
            SyncTestComPortLinnCoUkPtest1 sync = new SyncTestComPortLinnCoUkPtest1(this);
            BeginTestComPort(aPort, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTestComPort().</remarks>
        /// <param name="aaPort"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginTestComPort(uint aPort, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionTestComPort, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionTestComPort.InputParameter(inIndex++), aPort));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionTestComPort.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaResult"></param>
        public void EndTestComPort(IntPtr aAsyncHandle, out bool aResult)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aResult = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncLedsOn()
        {
            SyncLedsOnLinnCoUkPtest1 sync = new SyncLedsOnLinnCoUkPtest1(this);
            BeginLedsOn(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndLedsOn().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginLedsOn(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionLedsOn, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndLedsOn(IntPtr aAsyncHandle)
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
        public void SyncLedsOff()
        {
            SyncLedsOffLinnCoUkPtest1 sync = new SyncLedsOffLinnCoUkPtest1(this);
            BeginLedsOff(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndLedsOff().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginLedsOff(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionLedsOff, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndLedsOff(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkPtest1()
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
                iActionTestComPort.Dispose();
                iActionLedsOn.Dispose();
                iActionLedsOff.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

