using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyOpenhomeOrgSubscriptionLongPoll1 : ICpProxy, IDisposable
    {
        void SyncSubscribe(String aClientId, String aUdn, String aService, uint aRequestedDuration, out String aSid, out uint aDuration);
        void BeginSubscribe(String aClientId, String aUdn, String aService, uint aRequestedDuration, CpProxy.CallbackAsyncComplete aCallback);
        void EndSubscribe(IntPtr aAsyncHandle, out String aSid, out uint aDuration);
        void SyncUnsubscribe(String aSid);
        void BeginUnsubscribe(String aSid, CpProxy.CallbackAsyncComplete aCallback);
        void EndUnsubscribe(IntPtr aAsyncHandle);
        void SyncRenew(String aSid, uint aRequestedDuration, out uint aDuration);
        void BeginRenew(String aSid, uint aRequestedDuration, CpProxy.CallbackAsyncComplete aCallback);
        void EndRenew(IntPtr aAsyncHandle, out uint aDuration);
        void SyncGetPropertyUpdates(String aClientId, out String aUpdates);
        void BeginGetPropertyUpdates(String aClientId, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetPropertyUpdates(IntPtr aAsyncHandle, out String aUpdates);
    }

    internal class SyncSubscribeOpenhomeOrgSubscriptionLongPoll1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgSubscriptionLongPoll1 iService;
        private String iSid;
        private uint iDuration;

        public SyncSubscribeOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1 aProxy)
        {
            iService = aProxy;
        }
        public String Sid()
        {
            return iSid;
        }
        public uint Duration()
        {
            return iDuration;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSubscribe(aAsyncHandle, out iSid, out iDuration);
        }
    };

    internal class SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgSubscriptionLongPoll1 iService;

        public SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndUnsubscribe(aAsyncHandle);
        }
    };

    internal class SyncRenewOpenhomeOrgSubscriptionLongPoll1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgSubscriptionLongPoll1 iService;
        private uint iDuration;

        public SyncRenewOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1 aProxy)
        {
            iService = aProxy;
        }
        public uint Duration()
        {
            return iDuration;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndRenew(aAsyncHandle, out iDuration);
        }
    };

    internal class SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1 : SyncProxyAction
    {
        private CpProxyOpenhomeOrgSubscriptionLongPoll1 iService;
        private String iUpdates;

        public SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1(CpProxyOpenhomeOrgSubscriptionLongPoll1 aProxy)
        {
            iService = aProxy;
        }
        public String Updates()
        {
            return iUpdates;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetPropertyUpdates(aAsyncHandle, out iUpdates);
        }
    };

    /// <summary>
    /// Proxy for the openhome.org:SubscriptionLongPoll:1 UPnP service
    /// </summary>
    public class CpProxyOpenhomeOrgSubscriptionLongPoll1 : CpProxy, IDisposable, ICpProxyOpenhomeOrgSubscriptionLongPoll1
    {
        private OpenHome.Net.Core.Action iActionSubscribe;
        private OpenHome.Net.Core.Action iActionUnsubscribe;
        private OpenHome.Net.Core.Action iActionRenew;
        private OpenHome.Net.Core.Action iActionGetPropertyUpdates;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyOpenhomeOrgSubscriptionLongPoll1(ICpDevice aDevice)
            : base("openhome-org", "SubscriptionLongPoll", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionSubscribe = new OpenHome.Net.Core.Action("Subscribe");
            param = new ParameterString("ClientId", allowedValues);
            iActionSubscribe.AddInputParameter(param);
            param = new ParameterString("Udn", allowedValues);
            iActionSubscribe.AddInputParameter(param);
            param = new ParameterString("Service", allowedValues);
            iActionSubscribe.AddInputParameter(param);
            param = new ParameterUint("RequestedDuration");
            iActionSubscribe.AddInputParameter(param);
            param = new ParameterString("Sid", allowedValues);
            iActionSubscribe.AddOutputParameter(param);
            param = new ParameterUint("Duration");
            iActionSubscribe.AddOutputParameter(param);

            iActionUnsubscribe = new OpenHome.Net.Core.Action("Unsubscribe");
            param = new ParameterString("Sid", allowedValues);
            iActionUnsubscribe.AddInputParameter(param);

            iActionRenew = new OpenHome.Net.Core.Action("Renew");
            param = new ParameterString("Sid", allowedValues);
            iActionRenew.AddInputParameter(param);
            param = new ParameterUint("RequestedDuration");
            iActionRenew.AddInputParameter(param);
            param = new ParameterUint("Duration");
            iActionRenew.AddOutputParameter(param);

            iActionGetPropertyUpdates = new OpenHome.Net.Core.Action("GetPropertyUpdates");
            param = new ParameterString("ClientId", allowedValues);
            iActionGetPropertyUpdates.AddInputParameter(param);
            param = new ParameterString("Updates", allowedValues);
            iActionGetPropertyUpdates.AddOutputParameter(param);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aClientId"></param>
        /// <param name="aUdn"></param>
        /// <param name="aService"></param>
        /// <param name="aRequestedDuration"></param>
        /// <param name="aSid"></param>
        /// <param name="aDuration"></param>
        public void SyncSubscribe(String aClientId, String aUdn, String aService, uint aRequestedDuration, out String aSid, out uint aDuration)
        {
            SyncSubscribeOpenhomeOrgSubscriptionLongPoll1 sync = new SyncSubscribeOpenhomeOrgSubscriptionLongPoll1(this);
            BeginSubscribe(aClientId, aUdn, aService, aRequestedDuration, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSid = sync.Sid();
            aDuration = sync.Duration();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSubscribe().</remarks>
        /// <param name="aClientId"></param>
        /// <param name="aUdn"></param>
        /// <param name="aService"></param>
        /// <param name="aRequestedDuration"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSubscribe(String aClientId, String aUdn, String aService, uint aRequestedDuration, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSubscribe, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSubscribe.InputParameter(inIndex++), aClientId));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSubscribe.InputParameter(inIndex++), aUdn));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSubscribe.InputParameter(inIndex++), aService));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSubscribe.InputParameter(inIndex++), aRequestedDuration));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSubscribe.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSubscribe.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSid"></param>
        /// <param name="aDuration"></param>
        public void EndSubscribe(IntPtr aAsyncHandle, out String aSid, out uint aDuration)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aSid = Invocation.OutputString(aAsyncHandle, index++);
            aDuration = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSid"></param>
        public void SyncUnsubscribe(String aSid)
        {
            SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1 sync = new SyncUnsubscribeOpenhomeOrgSubscriptionLongPoll1(this);
            BeginUnsubscribe(aSid, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndUnsubscribe().</remarks>
        /// <param name="aSid"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginUnsubscribe(String aSid, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionUnsubscribe, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionUnsubscribe.InputParameter(inIndex++), aSid));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndUnsubscribe(IntPtr aAsyncHandle)
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
        /// <param name="aSid"></param>
        /// <param name="aRequestedDuration"></param>
        /// <param name="aDuration"></param>
        public void SyncRenew(String aSid, uint aRequestedDuration, out uint aDuration)
        {
            SyncRenewOpenhomeOrgSubscriptionLongPoll1 sync = new SyncRenewOpenhomeOrgSubscriptionLongPoll1(this);
            BeginRenew(aSid, aRequestedDuration, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aDuration = sync.Duration();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRenew().</remarks>
        /// <param name="aSid"></param>
        /// <param name="aRequestedDuration"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginRenew(String aSid, uint aRequestedDuration, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionRenew, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionRenew.InputParameter(inIndex++), aSid));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionRenew.InputParameter(inIndex++), aRequestedDuration));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionRenew.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aDuration"></param>
        public void EndRenew(IntPtr aAsyncHandle, out uint aDuration)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aDuration = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aClientId"></param>
        /// <param name="aUpdates"></param>
        public void SyncGetPropertyUpdates(String aClientId, out String aUpdates)
        {
            SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1 sync = new SyncGetPropertyUpdatesOpenhomeOrgSubscriptionLongPoll1(this);
            BeginGetPropertyUpdates(aClientId, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aUpdates = sync.Updates();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetPropertyUpdates().</remarks>
        /// <param name="aClientId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetPropertyUpdates(String aClientId, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetPropertyUpdates, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetPropertyUpdates.InputParameter(inIndex++), aClientId));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetPropertyUpdates.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aUpdates"></param>
        public void EndGetPropertyUpdates(IntPtr aAsyncHandle, out String aUpdates)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aUpdates = Invocation.OutputString(aAsyncHandle, index++);
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
            iActionSubscribe.Dispose();
            iActionUnsubscribe.Dispose();
            iActionRenew.Dispose();
            iActionGetPropertyUpdates.Dispose();
        }
    }
}

