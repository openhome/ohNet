using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkComponent1 : ICpProxy, IDisposable
    {
        void SyncAmplifierEnabled(out bool aaEnabled);
        void BeginAmplifierEnabled(CpProxy.CallbackAsyncComplete aCallback);
        void EndAmplifierEnabled(uint aAsyncHandle, out bool aaEnabled);
        void SyncSetAmplifierEnabled(bool aaEnabled);
        void BeginSetAmplifierEnabled(bool aaEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetAmplifierEnabled(uint aAsyncHandle);
        void SyncAmplifierAttenuation(out string aaAttenuation);
        void BeginAmplifierAttenuation(CpProxy.CallbackAsyncComplete aCallback);
        void EndAmplifierAttenuation(uint aAsyncHandle, out string aaAttenuation);
        void SyncSetAmplifierAttenuation(string aaAttenuation);
        void BeginSetAmplifierAttenuation(string aaAttenuation, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetAmplifierAttenuation(uint aAsyncHandle);
        void SyncSetVolumeControlEnabled(bool aaEnabled);
        void BeginSetVolumeControlEnabled(bool aaEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolumeControlEnabled(uint aAsyncHandle);
        void SyncVolumeControlEnabled(out bool aaEnabled);
        void BeginVolumeControlEnabled(CpProxy.CallbackAsyncComplete aCallback);
        void EndVolumeControlEnabled(uint aAsyncHandle, out bool aaEnabled);
        void SyncSetDigitalAudioOutputRaw(bool aaRaw);
        void BeginSetDigitalAudioOutputRaw(bool aaRaw, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetDigitalAudioOutputRaw(uint aAsyncHandle);
        void SyncDigitalAudioOutputRaw(out bool aaRaw);
        void BeginDigitalAudioOutputRaw(CpProxy.CallbackAsyncComplete aCallback);
        void EndDigitalAudioOutputRaw(uint aAsyncHandle, out bool aaRaw);
        void SyncAmplifierOverTemperature(out bool aaOverTemperature);
        void BeginAmplifierOverTemperature(CpProxy.CallbackAsyncComplete aCallback);
        void EndAmplifierOverTemperature(uint aAsyncHandle, out bool aaOverTemperature);
        void SyncEthernetLinkConnected(out bool aaLinkConnected);
        void BeginEthernetLinkConnected(CpProxy.CallbackAsyncComplete aCallback);
        void EndEthernetLinkConnected(uint aAsyncHandle, out bool aaLinkConnected);
        void SyncLocate();
        void BeginLocate(CpProxy.CallbackAsyncComplete aCallback);
        void EndLocate(uint aAsyncHandle);

        void SetPropertyAmplifierEnabledChanged(CpProxy.CallbackPropertyChanged aAmplifierEnabledChanged);
        void PropertyAmplifierEnabled(out bool aAmplifierEnabled);
        void SetPropertyAmplifierAttenuationChanged(CpProxy.CallbackPropertyChanged aAmplifierAttenuationChanged);
        void PropertyAmplifierAttenuation(out string aAmplifierAttenuation);
        void SetPropertyVolumeControlEnabledChanged(CpProxy.CallbackPropertyChanged aVolumeControlEnabledChanged);
        void PropertyVolumeControlEnabled(out bool aVolumeControlEnabled);
        void SetPropertyDigitalAudioOutputRawChanged(CpProxy.CallbackPropertyChanged aDigitalAudioOutputRawChanged);
        void PropertyDigitalAudioOutputRaw(out bool aDigitalAudioOutputRaw);
    }

    public class CpProxyLinnCoUkComponent1 : CpProxy, IDisposable, ICpProxyLinnCoUkComponent1
    {
        [DllImport("CpLinnCoUkComponent1")]
        static extern uint CpProxyLinnCoUkComponent1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkComponent1")]
        static extern void CpProxyLinnCoUkComponent1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncAmplifierEnabled(uint aHandle, uint* aaEnabled);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginAmplifierEnabled(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndAmplifierEnabled(uint aHandle, uint aAsync, uint* aaEnabled);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncSetAmplifierEnabled(uint aHandle, uint aaEnabled);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginSetAmplifierEnabled(uint aHandle, uint aaEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndSetAmplifierEnabled(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncAmplifierAttenuation(uint aHandle, char** aaAttenuation);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginAmplifierAttenuation(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndAmplifierAttenuation(uint aHandle, uint aAsync, char** aaAttenuation);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncSetAmplifierAttenuation(uint aHandle, char* aaAttenuation);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginSetAmplifierAttenuation(uint aHandle, char* aaAttenuation, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndSetAmplifierAttenuation(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncSetVolumeControlEnabled(uint aHandle, uint aaEnabled);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginSetVolumeControlEnabled(uint aHandle, uint aaEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndSetVolumeControlEnabled(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncVolumeControlEnabled(uint aHandle, uint* aaEnabled);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginVolumeControlEnabled(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndVolumeControlEnabled(uint aHandle, uint aAsync, uint* aaEnabled);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncSetDigitalAudioOutputRaw(uint aHandle, uint aaRaw);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginSetDigitalAudioOutputRaw(uint aHandle, uint aaRaw, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndSetDigitalAudioOutputRaw(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncDigitalAudioOutputRaw(uint aHandle, uint* aaRaw);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginDigitalAudioOutputRaw(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndDigitalAudioOutputRaw(uint aHandle, uint aAsync, uint* aaRaw);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncAmplifierOverTemperature(uint aHandle, uint* aaOverTemperature);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginAmplifierOverTemperature(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndAmplifierOverTemperature(uint aHandle, uint aAsync, uint* aaOverTemperature);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncEthernetLinkConnected(uint aHandle, uint* aaLinkConnected);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginEthernetLinkConnected(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndEthernetLinkConnected(uint aHandle, uint aAsync, uint* aaLinkConnected);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1SyncLocate(uint aHandle);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1BeginLocate(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe int CpProxyLinnCoUkComponent1EndLocate(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkComponent1")]
        static extern void CpProxyLinnCoUkComponent1SetPropertyAmplifierEnabledChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern void CpProxyLinnCoUkComponent1SetPropertyAmplifierAttenuationChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern void CpProxyLinnCoUkComponent1SetPropertyVolumeControlEnabledChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern void CpProxyLinnCoUkComponent1SetPropertyDigitalAudioOutputRawChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1PropertyAmplifierEnabled(uint aHandle, uint* aAmplifierEnabled);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1PropertyAmplifierAttenuation(uint aHandle, char** aAmplifierAttenuation);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1PropertyVolumeControlEnabled(uint aHandle, uint* aVolumeControlEnabled);
        [DllImport("CpLinnCoUkComponent1")]
        static extern unsafe void CpProxyLinnCoUkComponent1PropertyDigitalAudioOutputRaw(uint aHandle, uint* aDigitalAudioOutputRaw);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iAmplifierEnabledChanged;
        private CallbackPropertyChanged iAmplifierAttenuationChanged;
        private CallbackPropertyChanged iVolumeControlEnabledChanged;
        private CallbackPropertyChanged iDigitalAudioOutputRawChanged;
        private Callback iCallbackAmplifierEnabledChanged;
        private Callback iCallbackAmplifierAttenuationChanged;
        private Callback iCallbackVolumeControlEnabledChanged;
        private Callback iCallbackDigitalAudioOutputRawChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkComponent1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkComponent1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public unsafe void SyncAmplifierEnabled(out bool aaEnabled)
        {
			uint aEnabled;
			{
				CpProxyLinnCoUkComponent1SyncAmplifierEnabled(iHandle, &aEnabled);
			}
			aaEnabled = (aEnabled != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAmplifierEnabled().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginAmplifierEnabled(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginAmplifierEnabled(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaEnabled"></param>
        public unsafe void EndAmplifierEnabled(uint aAsyncHandle, out bool aaEnabled)
        {
			uint aEnabled;
			{
				if (0 != CpProxyLinnCoUkComponent1EndAmplifierEnabled(iHandle, aAsyncHandle, &aEnabled))
				{
					throw(new ProxyError());
				}
			}
			aaEnabled = (aEnabled != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public unsafe void SyncSetAmplifierEnabled(bool aaEnabled)
        {
			uint aEnabled = (aaEnabled? 1u : 0u);
			{
				CpProxyLinnCoUkComponent1SyncSetAmplifierEnabled(iHandle, aEnabled);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetAmplifierEnabled().</remarks>
        /// <param name="aaEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetAmplifierEnabled(bool aaEnabled, CallbackAsyncComplete aCallback)
        {
			uint aEnabled = (aaEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginSetAmplifierEnabled(iHandle, aEnabled, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetAmplifierEnabled(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkComponent1EndSetAmplifierEnabled(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaAttenuation"></param>
        public unsafe void SyncAmplifierAttenuation(out string aaAttenuation)
        {
			char* aAttenuation;
			{
				CpProxyLinnCoUkComponent1SyncAmplifierAttenuation(iHandle, &aAttenuation);
			}
            aaAttenuation = Marshal.PtrToStringAnsi((IntPtr)aAttenuation);
            ZappFree(aAttenuation);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAmplifierAttenuation().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginAmplifierAttenuation(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginAmplifierAttenuation(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaAttenuation"></param>
        public unsafe void EndAmplifierAttenuation(uint aAsyncHandle, out string aaAttenuation)
        {
			char* aAttenuation;
			{
				if (0 != CpProxyLinnCoUkComponent1EndAmplifierAttenuation(iHandle, aAsyncHandle, &aAttenuation))
				{
					throw(new ProxyError());
				}
			}
            aaAttenuation = Marshal.PtrToStringAnsi((IntPtr)aAttenuation);
            ZappFree(aAttenuation);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaAttenuation"></param>
        public unsafe void SyncSetAmplifierAttenuation(string aaAttenuation)
        {
			char* aAttenuation = (char*)Marshal.StringToHGlobalAnsi(aaAttenuation);
			{
				CpProxyLinnCoUkComponent1SyncSetAmplifierAttenuation(iHandle, aAttenuation);
			}
			Marshal.FreeHGlobal((IntPtr)aAttenuation);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetAmplifierAttenuation().</remarks>
        /// <param name="aaAttenuation"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetAmplifierAttenuation(string aaAttenuation, CallbackAsyncComplete aCallback)
        {
			char* aAttenuation = (char*)Marshal.StringToHGlobalAnsi(aaAttenuation);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginSetAmplifierAttenuation(iHandle, aAttenuation, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aAttenuation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetAmplifierAttenuation(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkComponent1EndSetAmplifierAttenuation(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public unsafe void SyncSetVolumeControlEnabled(bool aaEnabled)
        {
			uint aEnabled = (aaEnabled? 1u : 0u);
			{
				CpProxyLinnCoUkComponent1SyncSetVolumeControlEnabled(iHandle, aEnabled);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolumeControlEnabled().</remarks>
        /// <param name="aaEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetVolumeControlEnabled(bool aaEnabled, CallbackAsyncComplete aCallback)
        {
			uint aEnabled = (aaEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginSetVolumeControlEnabled(iHandle, aEnabled, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetVolumeControlEnabled(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkComponent1EndSetVolumeControlEnabled(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaEnabled"></param>
        public unsafe void SyncVolumeControlEnabled(out bool aaEnabled)
        {
			uint aEnabled;
			{
				CpProxyLinnCoUkComponent1SyncVolumeControlEnabled(iHandle, &aEnabled);
			}
			aaEnabled = (aEnabled != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndVolumeControlEnabled().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginVolumeControlEnabled(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginVolumeControlEnabled(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaEnabled"></param>
        public unsafe void EndVolumeControlEnabled(uint aAsyncHandle, out bool aaEnabled)
        {
			uint aEnabled;
			{
				if (0 != CpProxyLinnCoUkComponent1EndVolumeControlEnabled(iHandle, aAsyncHandle, &aEnabled))
				{
					throw(new ProxyError());
				}
			}
			aaEnabled = (aEnabled != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRaw"></param>
        public unsafe void SyncSetDigitalAudioOutputRaw(bool aaRaw)
        {
			uint aRaw = (aaRaw? 1u : 0u);
			{
				CpProxyLinnCoUkComponent1SyncSetDigitalAudioOutputRaw(iHandle, aRaw);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetDigitalAudioOutputRaw().</remarks>
        /// <param name="aaRaw"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetDigitalAudioOutputRaw(bool aaRaw, CallbackAsyncComplete aCallback)
        {
			uint aRaw = (aaRaw? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginSetDigitalAudioOutputRaw(iHandle, aRaw, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetDigitalAudioOutputRaw(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkComponent1EndSetDigitalAudioOutputRaw(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRaw"></param>
        public unsafe void SyncDigitalAudioOutputRaw(out bool aaRaw)
        {
			uint aRaw;
			{
				CpProxyLinnCoUkComponent1SyncDigitalAudioOutputRaw(iHandle, &aRaw);
			}
			aaRaw = (aRaw != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDigitalAudioOutputRaw().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDigitalAudioOutputRaw(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginDigitalAudioOutputRaw(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaRaw"></param>
        public unsafe void EndDigitalAudioOutputRaw(uint aAsyncHandle, out bool aaRaw)
        {
			uint aRaw;
			{
				if (0 != CpProxyLinnCoUkComponent1EndDigitalAudioOutputRaw(iHandle, aAsyncHandle, &aRaw))
				{
					throw(new ProxyError());
				}
			}
			aaRaw = (aRaw != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaOverTemperature"></param>
        public unsafe void SyncAmplifierOverTemperature(out bool aaOverTemperature)
        {
			uint aOverTemperature;
			{
				CpProxyLinnCoUkComponent1SyncAmplifierOverTemperature(iHandle, &aOverTemperature);
			}
			aaOverTemperature = (aOverTemperature != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAmplifierOverTemperature().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginAmplifierOverTemperature(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginAmplifierOverTemperature(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaOverTemperature"></param>
        public unsafe void EndAmplifierOverTemperature(uint aAsyncHandle, out bool aaOverTemperature)
        {
			uint aOverTemperature;
			{
				if (0 != CpProxyLinnCoUkComponent1EndAmplifierOverTemperature(iHandle, aAsyncHandle, &aOverTemperature))
				{
					throw(new ProxyError());
				}
			}
			aaOverTemperature = (aOverTemperature != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaLinkConnected"></param>
        public unsafe void SyncEthernetLinkConnected(out bool aaLinkConnected)
        {
			uint aLinkConnected;
			{
				CpProxyLinnCoUkComponent1SyncEthernetLinkConnected(iHandle, &aLinkConnected);
			}
			aaLinkConnected = (aLinkConnected != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEthernetLinkConnected().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginEthernetLinkConnected(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginEthernetLinkConnected(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaLinkConnected"></param>
        public unsafe void EndEthernetLinkConnected(uint aAsyncHandle, out bool aaLinkConnected)
        {
			uint aLinkConnected;
			{
				if (0 != CpProxyLinnCoUkComponent1EndEthernetLinkConnected(iHandle, aAsyncHandle, &aLinkConnected))
				{
					throw(new ProxyError());
				}
			}
			aaLinkConnected = (aLinkConnected != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncLocate()
        {
			{
				CpProxyLinnCoUkComponent1SyncLocate(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndLocate().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginLocate(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkComponent1BeginLocate(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndLocate(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkComponent1EndLocate(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Set a delegate to be run when the AmplifierEnabled state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkComponent1 instance will not overlap.</remarks>
        /// <param name="aAmplifierEnabledChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyAmplifierEnabledChanged(CallbackPropertyChanged aAmplifierEnabledChanged)
        {
            iAmplifierEnabledChanged = aAmplifierEnabledChanged;
            iCallbackAmplifierEnabledChanged = new Callback(PropertyAmplifierEnabledChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkComponent1SetPropertyAmplifierEnabledChanged(iHandle, iCallbackAmplifierEnabledChanged, ptr);
        }

        private void PropertyAmplifierEnabledChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkComponent1 self = (CpProxyLinnCoUkComponent1)gch.Target;
            self.iAmplifierEnabledChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the AmplifierAttenuation state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkComponent1 instance will not overlap.</remarks>
        /// <param name="aAmplifierAttenuationChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyAmplifierAttenuationChanged(CallbackPropertyChanged aAmplifierAttenuationChanged)
        {
            iAmplifierAttenuationChanged = aAmplifierAttenuationChanged;
            iCallbackAmplifierAttenuationChanged = new Callback(PropertyAmplifierAttenuationChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkComponent1SetPropertyAmplifierAttenuationChanged(iHandle, iCallbackAmplifierAttenuationChanged, ptr);
        }

        private void PropertyAmplifierAttenuationChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkComponent1 self = (CpProxyLinnCoUkComponent1)gch.Target;
            self.iAmplifierAttenuationChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the VolumeControlEnabled state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkComponent1 instance will not overlap.</remarks>
        /// <param name="aVolumeControlEnabledChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVolumeControlEnabledChanged(CallbackPropertyChanged aVolumeControlEnabledChanged)
        {
            iVolumeControlEnabledChanged = aVolumeControlEnabledChanged;
            iCallbackVolumeControlEnabledChanged = new Callback(PropertyVolumeControlEnabledChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkComponent1SetPropertyVolumeControlEnabledChanged(iHandle, iCallbackVolumeControlEnabledChanged, ptr);
        }

        private void PropertyVolumeControlEnabledChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkComponent1 self = (CpProxyLinnCoUkComponent1)gch.Target;
            self.iVolumeControlEnabledChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the DigitalAudioOutputRaw state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkComponent1 instance will not overlap.</remarks>
        /// <param name="aDigitalAudioOutputRawChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyDigitalAudioOutputRawChanged(CallbackPropertyChanged aDigitalAudioOutputRawChanged)
        {
            iDigitalAudioOutputRawChanged = aDigitalAudioOutputRawChanged;
            iCallbackDigitalAudioOutputRawChanged = new Callback(PropertyDigitalAudioOutputRawChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkComponent1SetPropertyDigitalAudioOutputRawChanged(iHandle, iCallbackDigitalAudioOutputRawChanged, ptr);
        }

        private void PropertyDigitalAudioOutputRawChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkComponent1 self = (CpProxyLinnCoUkComponent1)gch.Target;
            self.iDigitalAudioOutputRawChanged();
        }

        /// <summary>
        /// Query the value of the AmplifierEnabled property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aAmplifierEnabled">Will be set to the value of the property</param>
        public unsafe void PropertyAmplifierEnabled(out bool aAmplifierEnabled)
        {
			uint amplifierEnabled;
	        CpProxyLinnCoUkComponent1PropertyAmplifierEnabled(iHandle, &amplifierEnabled);
			aAmplifierEnabled = (amplifierEnabled != 0);
        }

        /// <summary>
        /// Query the value of the AmplifierAttenuation property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aAmplifierAttenuation">Will be set to the value of the property</param>
        public unsafe void PropertyAmplifierAttenuation(out string aAmplifierAttenuation)
        {
			char* ptr;
            CpProxyLinnCoUkComponent1PropertyAmplifierAttenuation(iHandle, &ptr);
            aAmplifierAttenuation = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the VolumeControlEnabled property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aVolumeControlEnabled">Will be set to the value of the property</param>
        public unsafe void PropertyVolumeControlEnabled(out bool aVolumeControlEnabled)
        {
			uint volumeControlEnabled;
	        CpProxyLinnCoUkComponent1PropertyVolumeControlEnabled(iHandle, &volumeControlEnabled);
			aVolumeControlEnabled = (volumeControlEnabled != 0);
        }

        /// <summary>
        /// Query the value of the DigitalAudioOutputRaw property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aDigitalAudioOutputRaw">Will be set to the value of the property</param>
        public unsafe void PropertyDigitalAudioOutputRaw(out bool aDigitalAudioOutputRaw)
        {
			uint digitalAudioOutputRaw;
	        CpProxyLinnCoUkComponent1PropertyDigitalAudioOutputRaw(iHandle, &digitalAudioOutputRaw);
			aDigitalAudioOutputRaw = (digitalAudioOutputRaw != 0);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkComponent1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                CpProxyLinnCoUkComponent1Destroy(iHandle);
                iHandle = 0;
            }
            iGch.Free();
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
            else
            {
                DisposeProxy();
            }
        }
    }
}

