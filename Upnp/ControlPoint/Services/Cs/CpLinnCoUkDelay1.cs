using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkDelay1 : ICpProxy, IDisposable
    {
        void SyncPresetXml(out String aPresetXml);
        void BeginPresetXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetXml(IntPtr aAsyncHandle, out String aPresetXml);
        void SyncPresetIndex(out uint aIndex);
        void BeginPresetIndex(CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetIndex(IntPtr aAsyncHandle, out uint aIndex);
        void SyncSetPresetIndex(uint aIndex);
        void BeginSetPresetIndex(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetIndex(IntPtr aAsyncHandle);
        void SyncSetPresetDelay(uint aIndex, uint aDelay);
        void BeginSetPresetDelay(uint aIndex, uint aDelay, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetDelay(IntPtr aAsyncHandle);
        void SyncSetPresetVisible(uint aIndex, bool aVisible);
        void BeginSetPresetVisible(uint aIndex, bool aVisible, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetVisible(IntPtr aAsyncHandle);
        void SyncSetPresetName(uint aIndex, String aName);
        void BeginSetPresetName(uint aIndex, String aName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetName(IntPtr aAsyncHandle);
        void SyncDelayMinimum(out uint aDelay);
        void BeginDelayMinimum(CpProxy.CallbackAsyncComplete aCallback);
        void EndDelayMinimum(IntPtr aAsyncHandle, out uint aDelay);
        void SyncDelayMaximum(out uint aDelay);
        void BeginDelayMaximum(CpProxy.CallbackAsyncComplete aCallback);
        void EndDelayMaximum(IntPtr aAsyncHandle, out uint aDelay);
        void SyncPresetCount(out uint aCount);
        void BeginPresetCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetCount(IntPtr aAsyncHandle, out uint aCount);
        void SetPropertyPresetXmlChanged(CpProxy.CallbackPropertyChanged aPresetXmlChanged);
        String PropertyPresetXml();
        void SetPropertyPresetIndexChanged(CpProxy.CallbackPropertyChanged aPresetIndexChanged);
        uint PropertyPresetIndex();
    }

    internal class SyncPresetXmlLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;
        private String iPresetXml;

        public SyncPresetXmlLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        public String PresetXml()
        {
            return iPresetXml;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPresetXml(aAsyncHandle, out iPresetXml);
        }
    };

    internal class SyncPresetIndexLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;
        private uint iIndex;

        public SyncPresetIndexLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        public uint Index()
        {
            return iIndex;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPresetIndex(aAsyncHandle, out iIndex);
        }
    };

    internal class SyncSetPresetIndexLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;

        public SyncSetPresetIndexLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetPresetIndex(aAsyncHandle);
        }
    };

    internal class SyncSetPresetDelayLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;

        public SyncSetPresetDelayLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetPresetDelay(aAsyncHandle);
        }
    };

    internal class SyncSetPresetVisibleLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;

        public SyncSetPresetVisibleLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetPresetVisible(aAsyncHandle);
        }
    };

    internal class SyncSetPresetNameLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;

        public SyncSetPresetNameLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetPresetName(aAsyncHandle);
        }
    };

    internal class SyncDelayMinimumLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;
        private uint iDelay;

        public SyncDelayMinimumLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        public uint Delay()
        {
            return iDelay;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDelayMinimum(aAsyncHandle, out iDelay);
        }
    };

    internal class SyncDelayMaximumLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;
        private uint iDelay;

        public SyncDelayMaximumLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        public uint Delay()
        {
            return iDelay;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDelayMaximum(aAsyncHandle, out iDelay);
        }
    };

    internal class SyncPresetCountLinnCoUkDelay1 : SyncProxyAction
    {
        private CpProxyLinnCoUkDelay1 iService;
        private uint iCount;

        public SyncPresetCountLinnCoUkDelay1(CpProxyLinnCoUkDelay1 aProxy)
        {
            iService = aProxy;
        }
        public uint Count()
        {
            return iCount;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPresetCount(aAsyncHandle, out iCount);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Delay:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkDelay1 : CpProxy, IDisposable, ICpProxyLinnCoUkDelay1
    {
        private Zapp.Core.Action iActionPresetXml;
        private Zapp.Core.Action iActionPresetIndex;
        private Zapp.Core.Action iActionSetPresetIndex;
        private Zapp.Core.Action iActionSetPresetDelay;
        private Zapp.Core.Action iActionSetPresetVisible;
        private Zapp.Core.Action iActionSetPresetName;
        private Zapp.Core.Action iActionDelayMinimum;
        private Zapp.Core.Action iActionDelayMaximum;
        private Zapp.Core.Action iActionPresetCount;
        private PropertyString iPresetXml;
        private PropertyUint iPresetIndex;
        private CallbackPropertyChanged iPresetXmlChanged;
        private CallbackPropertyChanged iPresetIndexChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkDelay1(CpDevice aDevice)
            : base("linn-co-uk", "Delay", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionPresetXml = new Zapp.Core.Action("PresetXml");
            param = new ParameterString("aPresetXml", allowedValues);
            iActionPresetXml.AddOutputParameter(param);

            iActionPresetIndex = new Zapp.Core.Action("PresetIndex");
            param = new ParameterUint("aIndex");
            iActionPresetIndex.AddOutputParameter(param);

            iActionSetPresetIndex = new Zapp.Core.Action("SetPresetIndex");
            param = new ParameterUint("aIndex");
            iActionSetPresetIndex.AddInputParameter(param);

            iActionSetPresetDelay = new Zapp.Core.Action("SetPresetDelay");
            param = new ParameterUint("aIndex");
            iActionSetPresetDelay.AddInputParameter(param);
            param = new ParameterUint("aDelay");
            iActionSetPresetDelay.AddInputParameter(param);

            iActionSetPresetVisible = new Zapp.Core.Action("SetPresetVisible");
            param = new ParameterUint("aIndex");
            iActionSetPresetVisible.AddInputParameter(param);
            param = new ParameterBool("aVisible");
            iActionSetPresetVisible.AddInputParameter(param);

            iActionSetPresetName = new Zapp.Core.Action("SetPresetName");
            param = new ParameterUint("aIndex");
            iActionSetPresetName.AddInputParameter(param);
            param = new ParameterString("aName", allowedValues);
            iActionSetPresetName.AddInputParameter(param);

            iActionDelayMinimum = new Zapp.Core.Action("DelayMinimum");
            param = new ParameterUint("aDelay");
            iActionDelayMinimum.AddOutputParameter(param);

            iActionDelayMaximum = new Zapp.Core.Action("DelayMaximum");
            param = new ParameterUint("aDelay");
            iActionDelayMaximum.AddOutputParameter(param);

            iActionPresetCount = new Zapp.Core.Action("PresetCount");
            param = new ParameterUint("aCount");
            iActionPresetCount.AddOutputParameter(param);

            iPresetXml = new PropertyString("PresetXml", PresetXmlPropertyChanged);
            AddProperty(iPresetXml);
            iPresetIndex = new PropertyUint("PresetIndex", PresetIndexPropertyChanged);
            AddProperty(iPresetIndex);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPresetXml"></param>
        public void SyncPresetXml(out String aPresetXml)
        {
            SyncPresetXmlLinnCoUkDelay1 sync = new SyncPresetXmlLinnCoUkDelay1(this);
            BeginPresetXml(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aPresetXml = sync.PresetXml();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetXml().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPresetXml(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPresetXml, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionPresetXml.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPresetXml"></param>
        public void EndPresetXml(IntPtr aAsyncHandle, out String aPresetXml)
        {
            uint index = 0;
            aPresetXml = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIndex"></param>
        public void SyncPresetIndex(out uint aIndex)
        {
            SyncPresetIndexLinnCoUkDelay1 sync = new SyncPresetIndexLinnCoUkDelay1(this);
            BeginPresetIndex(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aIndex = sync.Index();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetIndex().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPresetIndex(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPresetIndex, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionPresetIndex.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIndex"></param>
        public void EndPresetIndex(IntPtr aAsyncHandle, out uint aIndex)
        {
            uint index = 0;
            aIndex = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIndex"></param>
        public void SyncSetPresetIndex(uint aIndex)
        {
            SyncSetPresetIndexLinnCoUkDelay1 sync = new SyncSetPresetIndexLinnCoUkDelay1(this);
            BeginSetPresetIndex(aIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetIndex().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetPresetIndex(uint aIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetPresetIndex, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetPresetIndex.InputParameter(inIndex++), aIndex));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetPresetIndex(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaDelay"></param>
        public void SyncSetPresetDelay(uint aIndex, uint aDelay)
        {
            SyncSetPresetDelayLinnCoUkDelay1 sync = new SyncSetPresetDelayLinnCoUkDelay1(this);
            BeginSetPresetDelay(aIndex, aDelay, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetDelay().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaDelay"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetPresetDelay(uint aIndex, uint aDelay, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetPresetDelay, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetPresetDelay.InputParameter(inIndex++), aIndex));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetPresetDelay.InputParameter(inIndex++), aDelay));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetPresetDelay(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaVisible"></param>
        public void SyncSetPresetVisible(uint aIndex, bool aVisible)
        {
            SyncSetPresetVisibleLinnCoUkDelay1 sync = new SyncSetPresetVisibleLinnCoUkDelay1(this);
            BeginSetPresetVisible(aIndex, aVisible, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetVisible().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaVisible"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetPresetVisible(uint aIndex, bool aVisible, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetPresetVisible, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetPresetVisible.InputParameter(inIndex++), aIndex));
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetPresetVisible.InputParameter(inIndex++), aVisible));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetPresetVisible(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaName"></param>
        public void SyncSetPresetName(uint aIndex, String aName)
        {
            SyncSetPresetNameLinnCoUkDelay1 sync = new SyncSetPresetNameLinnCoUkDelay1(this);
            BeginSetPresetName(aIndex, aName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetName().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetPresetName(uint aIndex, String aName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetPresetName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetPresetName.InputParameter(inIndex++), aIndex));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetPresetName.InputParameter(inIndex++), aName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetPresetName(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDelay"></param>
        public void SyncDelayMinimum(out uint aDelay)
        {
            SyncDelayMinimumLinnCoUkDelay1 sync = new SyncDelayMinimumLinnCoUkDelay1(this);
            BeginDelayMinimum(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aDelay = sync.Delay();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDelayMinimum().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDelayMinimum(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDelayMinimum, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDelayMinimum.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDelay"></param>
        public void EndDelayMinimum(IntPtr aAsyncHandle, out uint aDelay)
        {
            uint index = 0;
            aDelay = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaDelay"></param>
        public void SyncDelayMaximum(out uint aDelay)
        {
            SyncDelayMaximumLinnCoUkDelay1 sync = new SyncDelayMaximumLinnCoUkDelay1(this);
            BeginDelayMaximum(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aDelay = sync.Delay();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDelayMaximum().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDelayMaximum(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDelayMaximum, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionDelayMaximum.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaDelay"></param>
        public void EndDelayMaximum(IntPtr aAsyncHandle, out uint aDelay)
        {
            uint index = 0;
            aDelay = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaCount"></param>
        public void SyncPresetCount(out uint aCount)
        {
            SyncPresetCountLinnCoUkDelay1 sync = new SyncPresetCountLinnCoUkDelay1(this);
            BeginPresetCount(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCount = sync.Count();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPresetCount(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPresetCount, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionPresetCount.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaCount"></param>
        public void EndPresetCount(IntPtr aAsyncHandle, out uint aCount)
        {
            uint index = 0;
            aCount = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the PresetXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDelay1 instance will not overlap.</remarks>
        /// <param name="aPresetXmlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyPresetXmlChanged(CallbackPropertyChanged aPresetXmlChanged)
        {
            lock (iPropertyLock)
            {
                iPresetXmlChanged = aPresetXmlChanged;
            }
        }

        private void PresetXmlPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iPresetXmlChanged != null)
                {
                    iPresetXmlChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the PresetIndex state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkDelay1 instance will not overlap.</remarks>
        /// <param name="aPresetIndexChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyPresetIndexChanged(CallbackPropertyChanged aPresetIndexChanged)
        {
            lock (iPropertyLock)
            {
                iPresetIndexChanged = aPresetIndexChanged;
            }
        }

        private void PresetIndexPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iPresetIndexChanged != null)
                {
                    iPresetIndexChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the PresetXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aPresetXml">Will be set to the value of the property</param>
        public String PropertyPresetXml()
        {
            return iPresetXml.Value();
        }

        /// <summary>
        /// Query the value of the PresetIndex property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aPresetIndex">Will be set to the value of the property</param>
        public uint PropertyPresetIndex()
        {
            return iPresetIndex.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkDelay1()
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
                iActionPresetXml.Dispose();
                iActionPresetIndex.Dispose();
                iActionSetPresetIndex.Dispose();
                iActionSetPresetDelay.Dispose();
                iActionSetPresetVisible.Dispose();
                iActionSetPresetName.Dispose();
                iActionDelayMinimum.Dispose();
                iActionDelayMaximum.Dispose();
                iActionPresetCount.Dispose();
                iPresetXml.Dispose();
                iPresetIndex.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

