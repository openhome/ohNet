using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkDebug2 : ICpProxy, IDisposable
    {
        void SyncSetDebugLevel(uint aDebugLevel);
        void BeginSetDebugLevel(uint aDebugLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDebugLevel(IntPtr aAsyncHandle);
        void SyncDebugLevel(out uint aDebugLevel);
        void BeginDebugLevel(CpProxy.CallbackAsyncComplete aCallback);
        void EndDebugLevel(IntPtr aAsyncHandle, out uint aDebugLevel);
        void SyncMemWrite(uint aMemAddress, byte[] aMemData);
        void BeginMemWrite(uint aMemAddress, byte[] aMemData, CpProxy.CallbackAsyncComplete aCallback);
        void EndMemWrite(IntPtr aAsyncHandle);
    }

    internal class SyncSetDebugLevelLinnCoUkDebug2 : SyncProxyAction
    {
        private CpProxyLinnCoUkDebug2 iService;

        public SyncSetDebugLevelLinnCoUkDebug2(CpProxyLinnCoUkDebug2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetDebugLevel(aAsyncHandle);
        }
    };

    internal class SyncDebugLevelLinnCoUkDebug2 : SyncProxyAction
    {
        private CpProxyLinnCoUkDebug2 iService;
        private uint iDebugLevel;

        public SyncDebugLevelLinnCoUkDebug2(CpProxyLinnCoUkDebug2 aProxy)
        {
            iService = aProxy;
        }
        public uint DebugLevel()
        {
            return iDebugLevel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDebugLevel(aAsyncHandle, out iDebugLevel);
        }
    };

    internal class SyncMemWriteLinnCoUkDebug2 : SyncProxyAction
    {
        private CpProxyLinnCoUkDebug2 iService;

        public SyncMemWriteLinnCoUkDebug2(CpProxyLinnCoUkDebug2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndMemWrite(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Debug:2 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkDebug2 : CpProxy, IDisposable, ICpProxyLinnCoUkDebug2
    {
        private Zapp.Core.Action iActionSetDebugLevel;
        private Zapp.Core.Action iActionDebugLevel;
        private Zapp.Core.Action iActionMemWrite;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkDebug2(CpDevice aDevice)
            : base("linn-co-uk", "Debug", 2, aDevice)
        {
            Zapp.Core.Parameter param;

            iActionSetDebugLevel = new Zapp.Core.Action("SetDebugLevel");
            param = new ParameterUint("aDebugLevel");
            iActionSetDebugLevel.AddInputParameter(param);

            iActionDebugLevel = new Zapp.Core.Action("DebugLevel");
            param = new ParameterUint("aDebugLevel");
            iActionDebugLevel.AddOutputParameter(param);

            iActionMemWrite = new Zapp.Core.Action("MemWrite");
            param = new ParameterUint("aMemAddress");
            iActionMemWrite.AddInputParameter(param);
            param = new ParameterBinary("aMemData");
            iActionMemWrite.AddInputParameter(param);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDebugLevel"></param>
        public void SyncSetDebugLevel(uint aDebugLevel)
        {
            SyncSetDebugLevelLinnCoUkDebug2 sync = new SyncSetDebugLevelLinnCoUkDebug2(this);
            BeginSetDebugLevel(aDebugLevel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDebugLevel().</remarks>
        /// <param name="aaDebugLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetDebugLevel(uint aDebugLevel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetDebugLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetDebugLevel.InputParameter(inIndex++), aDebugLevel));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetDebugLevel(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDebugLevel"></param>
        public void SyncDebugLevel(out uint aDebugLevel)
        {
            SyncDebugLevelLinnCoUkDebug2 sync = new SyncDebugLevelLinnCoUkDebug2(this);
            BeginDebugLevel(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aDebugLevel = sync.DebugLevel();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDebugLevel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDebugLevel(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDebugLevel, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDebugLevel.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDebugLevel"></param>
        public void EndDebugLevel(IntPtr aAsyncHandle, out uint aDebugLevel)
        {
            uint index = 0;
            aDebugLevel = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaMemAddress"></param>
        /// <param name="aaMemData"></param>
        public void SyncMemWrite(uint aMemAddress, byte[] aMemData)
        {
            SyncMemWriteLinnCoUkDebug2 sync = new SyncMemWriteLinnCoUkDebug2(this);
            BeginMemWrite(aMemAddress, aMemData, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMemWrite().</remarks>
        /// <param name="aaMemAddress"></param>
        /// <param name="aaMemData"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginMemWrite(uint aMemAddress, byte[] aMemData, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionMemWrite, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionMemWrite.InputParameter(inIndex++), aMemAddress));
            invocation.AddInput(new ArgumentBinary((ParameterBinary)iActionMemWrite.InputParameter(inIndex++), aMemData));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndMemWrite(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDebug2()
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
                iActionSetDebugLevel.Dispose();
                iActionDebugLevel.Dispose();
                iActionMemWrite.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

