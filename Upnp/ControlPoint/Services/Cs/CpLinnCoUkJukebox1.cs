using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkJukebox1 : ICpProxy, IDisposable
    {
        void SyncSetPresetPrefix(String aUri);
        void BeginSetPresetPrefix(String aUri, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetPresetPrefix(IntPtr aAsyncHandle);
        void SyncPresetPrefix(out String aUri);
        void BeginPresetPrefix(CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetPrefix(IntPtr aAsyncHandle, out String aUri);
        void SyncSetAlbumArtFileName(String aName);
        void BeginSetAlbumArtFileName(String aName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetAlbumArtFileName(IntPtr aAsyncHandle);
        void SyncAlbumArtFileName(out String aName);
        void BeginAlbumArtFileName(CpProxy.CallbackAsyncComplete aCallback);
        void EndAlbumArtFileName(IntPtr aAsyncHandle, out String aName);
        void SyncSetCurrentPreset(uint aPreset);
        void BeginSetCurrentPreset(uint aPreset, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetCurrentPreset(IntPtr aAsyncHandle);
        void SyncCurrentPreset(out uint aPreset);
        void BeginCurrentPreset(CpProxy.CallbackAsyncComplete aCallback);
        void EndCurrentPreset(IntPtr aAsyncHandle, out uint aPreset);
        void SyncPresetMetaData(uint aPreset, out String aMetaData);
        void BeginPresetMetaData(uint aPreset, CpProxy.CallbackAsyncComplete aCallback);
        void EndPresetMetaData(IntPtr aAsyncHandle, out String aMetaData);
        void SyncLoadManifest(out uint aTotalPresets);
        void BeginLoadManifest(CpProxy.CallbackAsyncComplete aCallback);
        void EndLoadManifest(IntPtr aAsyncHandle, out uint aTotalPresets);
        void SetPropertyCurrentPresetChanged(CpProxy.CallbackPropertyChanged aCurrentPresetChanged);
        uint PropertyCurrentPreset();
        void SetPropertyPresetPrefixChanged(CpProxy.CallbackPropertyChanged aPresetPrefixChanged);
        String PropertyPresetPrefix();
        void SetPropertyAlbumArtFileNameChanged(CpProxy.CallbackPropertyChanged aAlbumArtFileNameChanged);
        String PropertyAlbumArtFileName();
    }

    internal class SyncSetPresetPrefixLinnCoUkJukebox1 : SyncProxyAction
    {
        private CpProxyLinnCoUkJukebox1 iService;

        public SyncSetPresetPrefixLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetPresetPrefix(aAsyncHandle);
        }
    };

    internal class SyncPresetPrefixLinnCoUkJukebox1 : SyncProxyAction
    {
        private CpProxyLinnCoUkJukebox1 iService;
        private String iUri;

        public SyncPresetPrefixLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1 aProxy)
        {
            iService = aProxy;
        }
        public String Uri()
        {
            return iUri;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPresetPrefix(aAsyncHandle, out iUri);
        }
    };

    internal class SyncSetAlbumArtFileNameLinnCoUkJukebox1 : SyncProxyAction
    {
        private CpProxyLinnCoUkJukebox1 iService;

        public SyncSetAlbumArtFileNameLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetAlbumArtFileName(aAsyncHandle);
        }
    };

    internal class SyncAlbumArtFileNameLinnCoUkJukebox1 : SyncProxyAction
    {
        private CpProxyLinnCoUkJukebox1 iService;
        private String iName;

        public SyncAlbumArtFileNameLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1 aProxy)
        {
            iService = aProxy;
        }
        public String Name()
        {
            return iName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndAlbumArtFileName(aAsyncHandle, out iName);
        }
    };

    internal class SyncSetCurrentPresetLinnCoUkJukebox1 : SyncProxyAction
    {
        private CpProxyLinnCoUkJukebox1 iService;

        public SyncSetCurrentPresetLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetCurrentPreset(aAsyncHandle);
        }
    };

    internal class SyncCurrentPresetLinnCoUkJukebox1 : SyncProxyAction
    {
        private CpProxyLinnCoUkJukebox1 iService;
        private uint iPreset;

        public SyncCurrentPresetLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1 aProxy)
        {
            iService = aProxy;
        }
        public uint Preset()
        {
            return iPreset;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCurrentPreset(aAsyncHandle, out iPreset);
        }
    };

    internal class SyncPresetMetaDataLinnCoUkJukebox1 : SyncProxyAction
    {
        private CpProxyLinnCoUkJukebox1 iService;
        private String iMetaData;

        public SyncPresetMetaDataLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1 aProxy)
        {
            iService = aProxy;
        }
        public String MetaData()
        {
            return iMetaData;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPresetMetaData(aAsyncHandle, out iMetaData);
        }
    };

    internal class SyncLoadManifestLinnCoUkJukebox1 : SyncProxyAction
    {
        private CpProxyLinnCoUkJukebox1 iService;
        private uint iTotalPresets;

        public SyncLoadManifestLinnCoUkJukebox1(CpProxyLinnCoUkJukebox1 aProxy)
        {
            iService = aProxy;
        }
        public uint TotalPresets()
        {
            return iTotalPresets;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndLoadManifest(aAsyncHandle, out iTotalPresets);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Jukebox:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkJukebox1 : CpProxy, IDisposable, ICpProxyLinnCoUkJukebox1
    {
        private Zapp.Core.Action iActionSetPresetPrefix;
        private Zapp.Core.Action iActionPresetPrefix;
        private Zapp.Core.Action iActionSetAlbumArtFileName;
        private Zapp.Core.Action iActionAlbumArtFileName;
        private Zapp.Core.Action iActionSetCurrentPreset;
        private Zapp.Core.Action iActionCurrentPreset;
        private Zapp.Core.Action iActionPresetMetaData;
        private Zapp.Core.Action iActionLoadManifest;
        private PropertyUint iCurrentPreset;
        private PropertyString iPresetPrefix;
        private PropertyString iAlbumArtFileName;
        private CallbackPropertyChanged iCurrentPresetChanged;
        private CallbackPropertyChanged iPresetPrefixChanged;
        private CallbackPropertyChanged iAlbumArtFileNameChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkJukebox1(CpDevice aDevice)
            : base("linn-co-uk", "Jukebox", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionSetPresetPrefix = new Zapp.Core.Action("SetPresetPrefix");
            param = new ParameterString("aUri", allowedValues);
            iActionSetPresetPrefix.AddInputParameter(param);

            iActionPresetPrefix = new Zapp.Core.Action("PresetPrefix");
            param = new ParameterString("aUri", allowedValues);
            iActionPresetPrefix.AddOutputParameter(param);

            iActionSetAlbumArtFileName = new Zapp.Core.Action("SetAlbumArtFileName");
            param = new ParameterString("aName", allowedValues);
            iActionSetAlbumArtFileName.AddInputParameter(param);

            iActionAlbumArtFileName = new Zapp.Core.Action("AlbumArtFileName");
            param = new ParameterString("aName", allowedValues);
            iActionAlbumArtFileName.AddOutputParameter(param);

            iActionSetCurrentPreset = new Zapp.Core.Action("SetCurrentPreset");
            param = new ParameterUint("aPreset");
            iActionSetCurrentPreset.AddInputParameter(param);

            iActionCurrentPreset = new Zapp.Core.Action("CurrentPreset");
            param = new ParameterUint("aPreset");
            iActionCurrentPreset.AddOutputParameter(param);

            iActionPresetMetaData = new Zapp.Core.Action("PresetMetaData");
            param = new ParameterUint("aPreset");
            iActionPresetMetaData.AddInputParameter(param);
            param = new ParameterString("aMetaData", allowedValues);
            iActionPresetMetaData.AddOutputParameter(param);

            iActionLoadManifest = new Zapp.Core.Action("LoadManifest");
            param = new ParameterUint("aTotalPresets");
            iActionLoadManifest.AddOutputParameter(param);

            iCurrentPreset = new PropertyUint("CurrentPreset", CurrentPresetPropertyChanged);
            AddProperty(iCurrentPreset);
            iPresetPrefix = new PropertyString("PresetPrefix", PresetPrefixPropertyChanged);
            AddProperty(iPresetPrefix);
            iAlbumArtFileName = new PropertyString("AlbumArtFileName", AlbumArtFileNamePropertyChanged);
            AddProperty(iAlbumArtFileName);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUri"></param>
        public void SyncSetPresetPrefix(String aUri)
        {
            SyncSetPresetPrefixLinnCoUkJukebox1 sync = new SyncSetPresetPrefixLinnCoUkJukebox1(this);
            BeginSetPresetPrefix(aUri, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetPresetPrefix().</remarks>
        /// <param name="aaUri"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetPresetPrefix(String aUri, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetPresetPrefix, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetPresetPrefix.InputParameter(inIndex++), aUri));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetPresetPrefix(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUri"></param>
        public void SyncPresetPrefix(out String aUri)
        {
            SyncPresetPrefixLinnCoUkJukebox1 sync = new SyncPresetPrefixLinnCoUkJukebox1(this);
            BeginPresetPrefix(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aUri = sync.Uri();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetPrefix().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPresetPrefix(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPresetPrefix, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionPresetPrefix.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUri"></param>
        public void EndPresetPrefix(IntPtr aAsyncHandle, out String aUri)
        {
            uint index = 0;
            aUri = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public void SyncSetAlbumArtFileName(String aName)
        {
            SyncSetAlbumArtFileNameLinnCoUkJukebox1 sync = new SyncSetAlbumArtFileNameLinnCoUkJukebox1(this);
            BeginSetAlbumArtFileName(aName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetAlbumArtFileName().</remarks>
        /// <param name="aaName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetAlbumArtFileName(String aName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetAlbumArtFileName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetAlbumArtFileName.InputParameter(inIndex++), aName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetAlbumArtFileName(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public void SyncAlbumArtFileName(out String aName)
        {
            SyncAlbumArtFileNameLinnCoUkJukebox1 sync = new SyncAlbumArtFileNameLinnCoUkJukebox1(this);
            BeginAlbumArtFileName(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aName = sync.Name();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAlbumArtFileName().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginAlbumArtFileName(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionAlbumArtFileName, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionAlbumArtFileName.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaName"></param>
        public void EndAlbumArtFileName(IntPtr aAsyncHandle, out String aName)
        {
            uint index = 0;
            aName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPreset"></param>
        public void SyncSetCurrentPreset(uint aPreset)
        {
            SyncSetCurrentPresetLinnCoUkJukebox1 sync = new SyncSetCurrentPresetLinnCoUkJukebox1(this);
            BeginSetCurrentPreset(aPreset, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetCurrentPreset().</remarks>
        /// <param name="aaPreset"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetCurrentPreset(uint aPreset, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetCurrentPreset, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetCurrentPreset.InputParameter(inIndex++), aPreset));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetCurrentPreset(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPreset"></param>
        public void SyncCurrentPreset(out uint aPreset)
        {
            SyncCurrentPresetLinnCoUkJukebox1 sync = new SyncCurrentPresetLinnCoUkJukebox1(this);
            BeginCurrentPreset(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aPreset = sync.Preset();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCurrentPreset().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCurrentPreset(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCurrentPreset, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionCurrentPreset.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaPreset"></param>
        public void EndCurrentPreset(IntPtr aAsyncHandle, out uint aPreset)
        {
            uint index = 0;
            aPreset = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaPreset"></param>
        /// <param name="aaMetaData"></param>
        public void SyncPresetMetaData(uint aPreset, out String aMetaData)
        {
            SyncPresetMetaDataLinnCoUkJukebox1 sync = new SyncPresetMetaDataLinnCoUkJukebox1(this);
            BeginPresetMetaData(aPreset, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aMetaData = sync.MetaData();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPresetMetaData().</remarks>
        /// <param name="aaPreset"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPresetMetaData(uint aPreset, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPresetMetaData, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionPresetMetaData.InputParameter(inIndex++), aPreset));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionPresetMetaData.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetaData"></param>
        public void EndPresetMetaData(IntPtr aAsyncHandle, out String aMetaData)
        {
            uint index = 0;
            aMetaData = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTotalPresets"></param>
        public void SyncLoadManifest(out uint aTotalPresets)
        {
            SyncLoadManifestLinnCoUkJukebox1 sync = new SyncLoadManifestLinnCoUkJukebox1(this);
            BeginLoadManifest(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aTotalPresets = sync.TotalPresets();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndLoadManifest().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginLoadManifest(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionLoadManifest, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionLoadManifest.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaTotalPresets"></param>
        public void EndLoadManifest(IntPtr aAsyncHandle, out uint aTotalPresets)
        {
            uint index = 0;
            aTotalPresets = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the CurrentPreset state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkJukebox1 instance will not overlap.</remarks>
        /// <param name="aCurrentPresetChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyCurrentPresetChanged(CallbackPropertyChanged aCurrentPresetChanged)
        {
            lock (iPropertyLock)
            {
                iCurrentPresetChanged = aCurrentPresetChanged;
            }
        }

        private void CurrentPresetPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iCurrentPresetChanged != null)
                {
                    iCurrentPresetChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the PresetPrefix state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkJukebox1 instance will not overlap.</remarks>
        /// <param name="aPresetPrefixChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyPresetPrefixChanged(CallbackPropertyChanged aPresetPrefixChanged)
        {
            lock (iPropertyLock)
            {
                iPresetPrefixChanged = aPresetPrefixChanged;
            }
        }

        private void PresetPrefixPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iPresetPrefixChanged != null)
                {
                    iPresetPrefixChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the AlbumArtFileName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkJukebox1 instance will not overlap.</remarks>
        /// <param name="aAlbumArtFileNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyAlbumArtFileNameChanged(CallbackPropertyChanged aAlbumArtFileNameChanged)
        {
            lock (iPropertyLock)
            {
                iAlbumArtFileNameChanged = aAlbumArtFileNameChanged;
            }
        }

        private void AlbumArtFileNamePropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iAlbumArtFileNameChanged != null)
                {
                    iAlbumArtFileNameChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the CurrentPreset property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aCurrentPreset">Will be set to the value of the property</param>
        public uint PropertyCurrentPreset()
        {
            return iCurrentPreset.Value();
        }

        /// <summary>
        /// Query the value of the PresetPrefix property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aPresetPrefix">Will be set to the value of the property</param>
        public String PropertyPresetPrefix()
        {
            return iPresetPrefix.Value();
        }

        /// <summary>
        /// Query the value of the AlbumArtFileName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aAlbumArtFileName">Will be set to the value of the property</param>
        public String PropertyAlbumArtFileName()
        {
            return iAlbumArtFileName.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkJukebox1()
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
                iActionSetPresetPrefix.Dispose();
                iActionPresetPrefix.Dispose();
                iActionSetAlbumArtFileName.Dispose();
                iActionAlbumArtFileName.Dispose();
                iActionSetCurrentPreset.Dispose();
                iActionCurrentPreset.Dispose();
                iActionPresetMetaData.Dispose();
                iActionLoadManifest.Dispose();
                iCurrentPreset.Dispose();
                iPresetPrefix.Dispose();
                iAlbumArtFileName.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

