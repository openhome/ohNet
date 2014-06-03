using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyAvOpenhomeOrgTime1 : ICpProxy, IDisposable
    {
        void SyncTime(out uint aTrackCount, out uint aDuration, out uint aSeconds);
        void BeginTime(CpProxy.CallbackAsyncComplete aCallback);
        void EndTime(IntPtr aAsyncHandle, out uint aTrackCount, out uint aDuration, out uint aSeconds);
        void SetPropertyTrackCountChanged(System.Action aTrackCountChanged);
        uint PropertyTrackCount();
        void SetPropertyDurationChanged(System.Action aDurationChanged);
        uint PropertyDuration();
        void SetPropertySecondsChanged(System.Action aSecondsChanged);
        uint PropertySeconds();
    }

    internal class SyncTimeAvOpenhomeOrgTime1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgTime1 iService;
        private uint iTrackCount;
        private uint iDuration;
        private uint iSeconds;

        public SyncTimeAvOpenhomeOrgTime1(CpProxyAvOpenhomeOrgTime1 aProxy)
        {
            iService = aProxy;
        }
        public uint TrackCount()
        {
            return iTrackCount;
        }
        public uint Duration()
        {
            return iDuration;
        }
        public uint Seconds()
        {
            return iSeconds;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndTime(aAsyncHandle, out iTrackCount, out iDuration, out iSeconds);
        }
    };

    /// <summary>
    /// Proxy for the av.openhome.org:Time:1 UPnP service
    /// </summary>
    public class CpProxyAvOpenhomeOrgTime1 : CpProxy, IDisposable, ICpProxyAvOpenhomeOrgTime1
    {
        private OpenHome.Net.Core.Action iActionTime;
        private PropertyUint iTrackCount;
        private PropertyUint iDuration;
        private PropertyUint iSeconds;
        private System.Action iTrackCountChanged;
        private System.Action iDurationChanged;
        private System.Action iSecondsChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyAvOpenhomeOrgTime1(CpDevice aDevice)
            : base("av-openhome-org", "Time", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            

            iActionTime = new OpenHome.Net.Core.Action("Time");
            param = new ParameterUint("TrackCount");
            iActionTime.AddOutputParameter(param);
            param = new ParameterUint("Duration");
            iActionTime.AddOutputParameter(param);
            param = new ParameterUint("Seconds");
            iActionTime.AddOutputParameter(param);

            iTrackCount = new PropertyUint("TrackCount", TrackCountPropertyChanged);
            AddProperty(iTrackCount);
            iDuration = new PropertyUint("Duration", DurationPropertyChanged);
            AddProperty(iDuration);
            iSeconds = new PropertyUint("Seconds", SecondsPropertyChanged);
            AddProperty(iSeconds);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aTrackCount"></param>
        /// <param name="aDuration"></param>
        /// <param name="aSeconds"></param>
        public void SyncTime(out uint aTrackCount, out uint aDuration, out uint aSeconds)
        {
            SyncTimeAvOpenhomeOrgTime1 sync = new SyncTimeAvOpenhomeOrgTime1(this);
            BeginTime(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aTrackCount = sync.TrackCount();
            aDuration = sync.Duration();
            aSeconds = sync.Seconds();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTime().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginTime(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionTime, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionTime.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionTime.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionTime.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aTrackCount"></param>
        /// <param name="aDuration"></param>
        /// <param name="aSeconds"></param>
        public void EndTime(IntPtr aAsyncHandle, out uint aTrackCount, out uint aDuration, out uint aSeconds)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aTrackCount = Invocation.OutputUint(aAsyncHandle, index++);
            aDuration = Invocation.OutputUint(aAsyncHandle, index++);
            aSeconds = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the TrackCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgTime1 instance will not overlap.</remarks>
        /// <param name="aTrackCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackCountChanged(System.Action aTrackCountChanged)
        {
            lock (iPropertyLock)
            {
                iTrackCountChanged = aTrackCountChanged;
            }
        }

        private void TrackCountPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iTrackCountChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Duration state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgTime1 instance will not overlap.</remarks>
        /// <param name="aDurationChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDurationChanged(System.Action aDurationChanged)
        {
            lock (iPropertyLock)
            {
                iDurationChanged = aDurationChanged;
            }
        }

        private void DurationPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iDurationChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Seconds state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgTime1 instance will not overlap.</remarks>
        /// <param name="aSecondsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySecondsChanged(System.Action aSecondsChanged)
        {
            lock (iPropertyLock)
            {
                iSecondsChanged = aSecondsChanged;
            }
        }

        private void SecondsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSecondsChanged);
            }
        }

        /// <summary>
        /// Query the value of the TrackCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the TrackCount property</returns>
        public uint PropertyTrackCount()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iTrackCount.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Duration property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Duration property</returns>
        public uint PropertyDuration()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iDuration.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Seconds property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Seconds property</returns>
        public uint PropertySeconds()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iSeconds.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
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
            iActionTime.Dispose();
            iTrackCount.Dispose();
            iDuration.Dispose();
            iSeconds.Dispose();
        }
    }
}

