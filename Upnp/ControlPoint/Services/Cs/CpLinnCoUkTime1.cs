using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkTime1 : ICpProxy, IDisposable
    {
        void SyncTime(out uint aTrackCount, out uint aDuration, out uint aSeconds);
        void BeginTime(CpProxy.CallbackAsyncComplete aCallback);
        void EndTime(IntPtr aAsyncHandle, out uint aTrackCount, out uint aDuration, out uint aSeconds);
        void SetPropertyTrackCountChanged(CpProxy.CallbackPropertyChanged aTrackCountChanged);
        uint PropertyTrackCount();
        void SetPropertyDurationChanged(CpProxy.CallbackPropertyChanged aDurationChanged);
        uint PropertyDuration();
        void SetPropertySecondsChanged(CpProxy.CallbackPropertyChanged aSecondsChanged);
        uint PropertySeconds();
    }

    internal class SyncTimeLinnCoUkTime1 : SyncProxyAction
    {
        private CpProxyLinnCoUkTime1 iService;
        private uint iTrackCount;
        private uint iDuration;
        private uint iSeconds;

        public SyncTimeLinnCoUkTime1(CpProxyLinnCoUkTime1 aProxy)
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
    /// Proxy for the linn.co.uk:Time:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkTime1 : CpProxy, IDisposable, ICpProxyLinnCoUkTime1
    {
        private Zapp.Core.Action iActionTime;
        private PropertyUint iTrackCount;
        private PropertyUint iDuration;
        private PropertyUint iSeconds;
        private CallbackPropertyChanged iTrackCountChanged;
        private CallbackPropertyChanged iDurationChanged;
        private CallbackPropertyChanged iSecondsChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkTime1(CpDevice aDevice)
            : base("linn-co-uk", "Time", 1, aDevice)
        {
            Zapp.Core.Parameter param;

            iActionTime = new Zapp.Core.Action("Time");
            param = new ParameterUint("aTrackCount");
            iActionTime.AddOutputParameter(param);
            param = new ParameterUint("aDuration");
            iActionTime.AddOutputParameter(param);
            param = new ParameterUint("aSeconds");
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
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDuration"></param>
        /// <param name="aaSeconds"></param>
        public void SyncTime(out uint aTrackCount, out uint aDuration, out uint aSeconds)
        {
            SyncTimeLinnCoUkTime1 sync = new SyncTimeLinnCoUkTime1(this);
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
        /// <param name="aaTrackCount"></param>
        /// <param name="aaDuration"></param>
        /// <param name="aaSeconds"></param>
        public void EndTime(IntPtr aAsyncHandle, out uint aTrackCount, out uint aDuration, out uint aSeconds)
        {
            uint index = 0;
            aTrackCount = Invocation.OutputUint(aAsyncHandle, index++);
            aDuration = Invocation.OutputUint(aAsyncHandle, index++);
            aSeconds = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the TrackCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkTime1 instance will not overlap.</remarks>
        /// <param name="aTrackCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTrackCountChanged(CallbackPropertyChanged aTrackCountChanged)
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
                if (iTrackCountChanged != null)
                {
                    iTrackCountChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Duration state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkTime1 instance will not overlap.</remarks>
        /// <param name="aDurationChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDurationChanged(CallbackPropertyChanged aDurationChanged)
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
                if (iDurationChanged != null)
                {
                    iDurationChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Seconds state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkTime1 instance will not overlap.</remarks>
        /// <param name="aSecondsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySecondsChanged(CallbackPropertyChanged aSecondsChanged)
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
                if (iSecondsChanged != null)
                {
                    iSecondsChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the TrackCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTrackCount">Will be set to the value of the property</param>
        public uint PropertyTrackCount()
        {
            PropertyReadLock();
            uint val = iTrackCount.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the Duration property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aDuration">Will be set to the value of the property</param>
        public uint PropertyDuration()
        {
            PropertyReadLock();
            uint val = iDuration.Value();
            PropertyReadUnlock();
            return val;
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
            PropertyReadLock();
            uint val = iSeconds.Value();
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

        ~CpProxyLinnCoUkTime1()
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
                iActionTime.Dispose();
                iTrackCount.Dispose();
                iDuration.Dispose();
                iSeconds.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

