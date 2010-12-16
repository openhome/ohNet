using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkMediaTime1 : ICpProxy, IDisposable
    {
        void SyncSeconds(out uint aaSeconds);
        void BeginSeconds(CpProxy.CallbackAsyncComplete aCallback);
        void EndSeconds(IntPtr aAsyncHandle, out uint aaSeconds);
        void SetPropertySecondsChanged(CpProxy.CallbackPropertyChanged aSecondsChanged);
        uint PropertySeconds();
    }

    internal class SyncSecondsLinnCoUkMediaTime1 : SyncProxyAction
    {
        private CpProxyLinnCoUkMediaTime1 iService;
        private uint iSeconds;

        public SyncSecondsLinnCoUkMediaTime1(CpProxyLinnCoUkMediaTime1 aProxy)
        {
            iService = aProxy;
        }
        public uint Seconds()
        {
            return iSeconds;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSeconds(aAsyncHandle, out iSeconds);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:MediaTime:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkMediaTime1 : CpProxy, IDisposable, ICpProxyLinnCoUkMediaTime1
    {
        private Zapp.Core.Action iActionSeconds;
        private PropertyUint iSeconds;
        private CallbackPropertyChanged iSecondsChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkMediaTime1(CpDevice aDevice)
            : base("linn-co-uk", "MediaTime", 1, aDevice)
        {
            Zapp.Core.Parameter param;

            iActionSeconds = new Zapp.Core.Action("Seconds");
            param = new ParameterUint("aSeconds");
            iActionSeconds.AddOutputParameter(param);

            iSeconds = new PropertyUint("Seconds", SecondsPropertyChanged);
            AddProperty(iSeconds);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSeconds"></param>
        public void SyncSeconds(out uint aaSeconds)
        {
            SyncSecondsLinnCoUkMediaTime1 sync = new SyncSecondsLinnCoUkMediaTime1(this);
            BeginSeconds(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSeconds = sync.Seconds();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeconds().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSeconds(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSeconds, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSeconds.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSeconds"></param>
        public void EndSeconds(IntPtr aAsyncHandle, out uint aaSeconds)
        {
            uint index = 0;
            aSeconds = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the Seconds state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkMediaTime1 instance will not overlap.</remarks>
        /// <param name="aSecondsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySecondsChanged(CallbackPropertyChanged aSecondsChanged)
        {
            lock (this)
            {
                iSecondsChanged = aSecondsChanged;
            }
        }

        private void SecondsPropertyChanged()
        {
            lock (this)
            {
                if (iSecondsChanged != null)
                {
                    iSecondsChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the Seconds property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aSeconds">Will be set to the value of the property</param>
        public uint PropertySeconds()
        {
            return iSeconds.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkMediaTime1()
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
                iActionSeconds.Dispose();
                iSeconds.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

