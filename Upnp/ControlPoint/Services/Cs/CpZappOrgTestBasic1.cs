using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestBasic1 : ICpProxy, IDisposable
    {
        void SyncIncrement(uint aValue, out uint aResult);
        void BeginIncrement(uint aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndIncrement(uint aAsyncHandle, out uint aResult);
        void SyncDecrement(int aValue, out int aResult);
        void BeginDecrement(int aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndDecrement(uint aAsyncHandle, out int aResult);
        void SyncToggle(bool aValue, out bool aResult);
        void BeginToggle(bool aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndToggle(uint aAsyncHandle, out bool aResult);
        void SyncEchoString(string aValue, out string aResult);
        void BeginEchoString(string aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndEchoString(uint aAsyncHandle, out string aResult);
        void SyncEchoBinary(string aValue, out string aResult);
        void BeginEchoBinary(string aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndEchoBinary(uint aAsyncHandle, out string aResult);
        void SyncSetUint(uint aValueUint);
        void BeginSetUint(uint aValueUint, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetUint(uint aAsyncHandle);
        void SyncGetUint(out uint aValueUint);
        void BeginGetUint(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetUint(uint aAsyncHandle, out uint aValueUint);
        void SyncSetInt(int aValueInt);
        void BeginSetInt(int aValueInt, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetInt(uint aAsyncHandle);
        void SyncGetInt(out int aValueInt);
        void BeginGetInt(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetInt(uint aAsyncHandle, out int aValueInt);
        void SyncSetBool(bool aValueBool);
        void BeginSetBool(bool aValueBool, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBool(uint aAsyncHandle);
        void SyncGetBool(out bool aValueBool);
        void BeginGetBool(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetBool(uint aAsyncHandle, out bool aValueBool);
        void SyncSetMultiple(uint aValueUint, int aValueInt, bool aValueBool);
        void BeginSetMultiple(uint aValueUint, int aValueInt, bool aValueBool, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetMultiple(uint aAsyncHandle);
        void SyncSetString(string aValueStr);
        void BeginSetString(string aValueStr, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetString(uint aAsyncHandle);
        void SyncGetString(out string aValueStr);
        void BeginGetString(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetString(uint aAsyncHandle, out string aValueStr);
        void SyncSetBinary(string aValueBin);
        void BeginSetBinary(string aValueBin, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBinary(uint aAsyncHandle);
        void SyncGetBinary(out string aValueBin);
        void BeginGetBinary(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetBinary(uint aAsyncHandle, out string aValueBin);
        void SyncToggleBool();
        void BeginToggleBool(CpProxy.CallbackAsyncComplete aCallback);
        void EndToggleBool(uint aAsyncHandle);
        void SyncWriteFile(string aData, string aFileFullName);
        void BeginWriteFile(string aData, string aFileFullName, CpProxy.CallbackAsyncComplete aCallback);
        void EndWriteFile(uint aAsyncHandle);
        void SyncShutdown();
        void BeginShutdown(CpProxy.CallbackAsyncComplete aCallback);
        void EndShutdown(uint aAsyncHandle);

        void SetPropertyVarUintChanged(CpProxy.CallbackPropertyChanged aVarUintChanged);
        void PropertyVarUint(out uint aVarUint);
        void SetPropertyVarIntChanged(CpProxy.CallbackPropertyChanged aVarIntChanged);
        void PropertyVarInt(out int aVarInt);
        void SetPropertyVarBoolChanged(CpProxy.CallbackPropertyChanged aVarBoolChanged);
        void PropertyVarBool(out bool aVarBool);
        void SetPropertyVarStrChanged(CpProxy.CallbackPropertyChanged aVarStrChanged);
        void PropertyVarStr(out string aVarStr);
        void SetPropertyVarBinChanged(CpProxy.CallbackPropertyChanged aVarBinChanged);
        void PropertyVarBin(out string aVarBin);
    }

    public class CpProxyZappOrgTestBasic1 : CpProxy, IDisposable, ICpProxyZappOrgTestBasic1
    {
        [DllImport("CpZappOrgTestBasic1")]
        static extern uint CpProxyZappOrgTestBasic1Create(uint aDeviceHandle);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1Destroy(uint aHandle);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncIncrement(uint aHandle, uint aValue, uint* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginIncrement(uint aHandle, uint aValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndIncrement(uint aHandle, uint aAsync, uint* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncDecrement(uint aHandle, int aValue, int* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginDecrement(uint aHandle, int aValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndDecrement(uint aHandle, uint aAsync, int* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncToggle(uint aHandle, uint aValue, uint* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginToggle(uint aHandle, uint aValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndToggle(uint aHandle, uint aAsync, uint* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncEchoString(uint aHandle, char* aValue, char** aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginEchoString(uint aHandle, char* aValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndEchoString(uint aHandle, uint aAsync, char** aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncEchoBinary(uint aHandle, char* aValue, uint aValueLen, char** aResult, uint* aResultLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginEchoBinary(uint aHandle, char* aValue, uint aValueLen, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndEchoBinary(uint aHandle, uint aAsync, char** aResult, uint* aResultLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetUint(uint aHandle, uint aValueUint);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetUint(uint aHandle, uint aValueUint, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetUint(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetUint(uint aHandle, uint* aValueUint);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetUint(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetUint(uint aHandle, uint aAsync, uint* aValueUint);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetInt(uint aHandle, int aValueInt);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetInt(uint aHandle, int aValueInt, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetInt(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetInt(uint aHandle, int* aValueInt);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetInt(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetInt(uint aHandle, uint aAsync, int* aValueInt);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetBool(uint aHandle, uint aValueBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetBool(uint aHandle, uint aValueBool, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetBool(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetBool(uint aHandle, uint* aValueBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetBool(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetBool(uint aHandle, uint aAsync, uint* aValueBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetMultiple(uint aHandle, uint aValueUint, int aValueInt, uint aValueBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetMultiple(uint aHandle, uint aValueUint, int aValueInt, uint aValueBool, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetMultiple(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetString(uint aHandle, char* aValueStr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetString(uint aHandle, char* aValueStr, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetString(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetString(uint aHandle, char** aValueStr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetString(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetString(uint aHandle, uint aAsync, char** aValueStr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetBinary(uint aHandle, char* aValueBin, uint aValueBinLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetBinary(uint aHandle, char* aValueBin, uint aValueBinLen, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetBinary(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetBinary(uint aHandle, char** aValueBin, uint* aValueBinLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetBinary(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetBinary(uint aHandle, uint aAsync, char** aValueBin, uint* aValueBinLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncToggleBool(uint aHandle);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginToggleBool(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndToggleBool(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncWriteFile(uint aHandle, char* aData, char* aFileFullName);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginWriteFile(uint aHandle, char* aData, char* aFileFullName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndWriteFile(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncShutdown(uint aHandle);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginShutdown(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndShutdown(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarUintChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarIntChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarBoolChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarStrChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarBinChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarUint(uint aHandle, uint* aVarUint);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarInt(uint aHandle, int* aVarInt);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarBool(uint aHandle, uint* aVarBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarStr(uint aHandle, char** aVarStr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarBin(uint aHandle, char** aVarBin, uint* aLen);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iVarUintChanged;
        private CallbackPropertyChanged iVarIntChanged;
        private CallbackPropertyChanged iVarBoolChanged;
        private CallbackPropertyChanged iVarStrChanged;
        private CallbackPropertyChanged iVarBinChanged;
        private Callback iCallbackVarUintChanged;
        private Callback iCallbackVarIntChanged;
        private Callback iCallbackVarBoolChanged;
        private Callback iCallbackVarStrChanged;
        private Callback iCallbackVarBinChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestBasic1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestBasic1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public unsafe void SyncIncrement(uint aValue, out uint aResult)
        {
			fixed (uint* result = &aResult)
			{
				CpProxyZappOrgTestBasic1SyncIncrement(iHandle, aValue, result);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIncrement().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginIncrement(uint aValue, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginIncrement(iHandle, aValue, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public unsafe void EndIncrement(uint aAsyncHandle, out uint aResult)
        {
			fixed (uint* result = &aResult)
			{
				if (0 != CpProxyZappOrgTestBasic1EndIncrement(iHandle, aAsyncHandle, result))
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
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public unsafe void SyncDecrement(int aValue, out int aResult)
        {
			fixed (int* result = &aResult)
			{
				CpProxyZappOrgTestBasic1SyncDecrement(iHandle, aValue, result);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDecrement().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginDecrement(int aValue, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginDecrement(iHandle, aValue, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public unsafe void EndDecrement(uint aAsyncHandle, out int aResult)
        {
			fixed (int* result = &aResult)
			{
				if (0 != CpProxyZappOrgTestBasic1EndDecrement(iHandle, aAsyncHandle, result))
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
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public unsafe void SyncToggle(bool aValue, out bool aResult)
        {
			uint value = (aValue? 1u : 0u);
			uint result;
			{
				CpProxyZappOrgTestBasic1SyncToggle(iHandle, value, &result);
			}
			aResult = (result != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndToggle().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginToggle(bool aValue, CallbackAsyncComplete aCallback)
        {
			uint value = (aValue? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginToggle(iHandle, value, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public unsafe void EndToggle(uint aAsyncHandle, out bool aResult)
        {
			uint result;
			{
				if (0 != CpProxyZappOrgTestBasic1EndToggle(iHandle, aAsyncHandle, &result))
				{
					throw(new ProxyError());
				}
			}
			aResult = (result != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public unsafe void SyncEchoString(string aValue, out string aResult)
        {
			char* value = (char*)Marshal.StringToHGlobalAnsi(aValue);
			char* result;
			{
				CpProxyZappOrgTestBasic1SyncEchoString(iHandle, value, &result);
			}
			Marshal.FreeHGlobal((IntPtr)value);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEchoString().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginEchoString(string aValue, CallbackAsyncComplete aCallback)
        {
			char* value = (char*)Marshal.StringToHGlobalAnsi(aValue);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginEchoString(iHandle, value, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)value);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public unsafe void EndEchoString(uint aAsyncHandle, out string aResult)
        {
			char* result;
			{
				if (0 != CpProxyZappOrgTestBasic1EndEchoString(iHandle, aAsyncHandle, &result))
				{
					throw(new ProxyError());
				}
			}
            aResult = Marshal.PtrToStringAnsi((IntPtr)result);
            ZappFree(result);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        public unsafe void SyncEchoBinary(string aValue, out string aResult)
        {
			char* value = (char*)Marshal.StringToHGlobalAnsi(aValue);
			uint valueLen = (uint)aValue.Length;
			char* result;
			uint resultLen;
			{
				CpProxyZappOrgTestBasic1SyncEchoBinary(iHandle, value, valueLen, &result, &resultLen);
			}
			Marshal.FreeHGlobal((IntPtr)value);
            aResult = Marshal.PtrToStringAnsi((IntPtr)result, (int)resultLen);
            ZappFree(result);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndEchoBinary().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginEchoBinary(string aValue, CallbackAsyncComplete aCallback)
        {
			char* value = (char*)Marshal.StringToHGlobalAnsi(aValue);
			uint valueLen = (uint)aValue.Length;
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginEchoBinary(iHandle, value, valueLen, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)value);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        public unsafe void EndEchoBinary(uint aAsyncHandle, out string aResult)
        {
			char* result;
			uint resultLen;
			{
				if (0 != CpProxyZappOrgTestBasic1EndEchoBinary(iHandle, aAsyncHandle, &result, &resultLen))
				{
					throw(new ProxyError());
				}
			}
            aResult = Marshal.PtrToStringAnsi((IntPtr)result, (int)resultLen);
            ZappFree(result);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueUint"></param>
        public unsafe void SyncSetUint(uint aValueUint)
        {
			{
				CpProxyZappOrgTestBasic1SyncSetUint(iHandle, aValueUint);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetUint().</remarks>
        /// <param name="aValueUint"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetUint(uint aValueUint, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetUint(iHandle, aValueUint, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetUint(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetUint(iHandle, aAsyncHandle))
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
        /// <param name="aValueUint"></param>
        public unsafe void SyncGetUint(out uint aValueUint)
        {
			fixed (uint* valueUint = &aValueUint)
			{
				CpProxyZappOrgTestBasic1SyncGetUint(iHandle, valueUint);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetUint().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetUint(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetUint(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueUint"></param>
        public unsafe void EndGetUint(uint aAsyncHandle, out uint aValueUint)
        {
			fixed (uint* valueUint = &aValueUint)
			{
				if (0 != CpProxyZappOrgTestBasic1EndGetUint(iHandle, aAsyncHandle, valueUint))
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
        /// <param name="aValueInt"></param>
        public unsafe void SyncSetInt(int aValueInt)
        {
			{
				CpProxyZappOrgTestBasic1SyncSetInt(iHandle, aValueInt);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetInt().</remarks>
        /// <param name="aValueInt"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetInt(int aValueInt, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetInt(iHandle, aValueInt, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetInt(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetInt(iHandle, aAsyncHandle))
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
        /// <param name="aValueInt"></param>
        public unsafe void SyncGetInt(out int aValueInt)
        {
			fixed (int* valueInt = &aValueInt)
			{
				CpProxyZappOrgTestBasic1SyncGetInt(iHandle, valueInt);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetInt().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetInt(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetInt(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueInt"></param>
        public unsafe void EndGetInt(uint aAsyncHandle, out int aValueInt)
        {
			fixed (int* valueInt = &aValueInt)
			{
				if (0 != CpProxyZappOrgTestBasic1EndGetInt(iHandle, aAsyncHandle, valueInt))
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
        /// <param name="aValueBool"></param>
        public unsafe void SyncSetBool(bool aValueBool)
        {
			uint valueBool = (aValueBool? 1u : 0u);
			{
				CpProxyZappOrgTestBasic1SyncSetBool(iHandle, valueBool);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBool().</remarks>
        /// <param name="aValueBool"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetBool(bool aValueBool, CallbackAsyncComplete aCallback)
        {
			uint valueBool = (aValueBool? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetBool(iHandle, valueBool, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetBool(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetBool(iHandle, aAsyncHandle))
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
        /// <param name="aValueBool"></param>
        public unsafe void SyncGetBool(out bool aValueBool)
        {
			uint valueBool;
			{
				CpProxyZappOrgTestBasic1SyncGetBool(iHandle, &valueBool);
			}
			aValueBool = (valueBool != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetBool().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetBool(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetBool(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueBool"></param>
        public unsafe void EndGetBool(uint aAsyncHandle, out bool aValueBool)
        {
			uint valueBool;
			{
				if (0 != CpProxyZappOrgTestBasic1EndGetBool(iHandle, aAsyncHandle, &valueBool))
				{
					throw(new ProxyError());
				}
			}
			aValueBool = (valueBool != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        public unsafe void SyncSetMultiple(uint aValueUint, int aValueInt, bool aValueBool)
        {
			uint valueBool = (aValueBool? 1u : 0u);
			{
				CpProxyZappOrgTestBasic1SyncSetMultiple(iHandle, aValueUint, aValueInt, valueBool);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetMultiple().</remarks>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetMultiple(uint aValueUint, int aValueInt, bool aValueBool, CallbackAsyncComplete aCallback)
        {
			uint valueBool = (aValueBool? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetMultiple(iHandle, aValueUint, aValueInt, valueBool, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetMultiple(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetMultiple(iHandle, aAsyncHandle))
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
        /// <param name="aValueStr"></param>
        public unsafe void SyncSetString(string aValueStr)
        {
			char* valueStr = (char*)Marshal.StringToHGlobalAnsi(aValueStr);
			{
				CpProxyZappOrgTestBasic1SyncSetString(iHandle, valueStr);
			}
			Marshal.FreeHGlobal((IntPtr)valueStr);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetString().</remarks>
        /// <param name="aValueStr"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetString(string aValueStr, CallbackAsyncComplete aCallback)
        {
			char* valueStr = (char*)Marshal.StringToHGlobalAnsi(aValueStr);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetString(iHandle, valueStr, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)valueStr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetString(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetString(iHandle, aAsyncHandle))
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
        /// <param name="aValueStr"></param>
        public unsafe void SyncGetString(out string aValueStr)
        {
			char* valueStr;
			{
				CpProxyZappOrgTestBasic1SyncGetString(iHandle, &valueStr);
			}
            aValueStr = Marshal.PtrToStringAnsi((IntPtr)valueStr);
            ZappFree(valueStr);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetString().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetString(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetString(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueStr"></param>
        public unsafe void EndGetString(uint aAsyncHandle, out string aValueStr)
        {
			char* valueStr;
			{
				if (0 != CpProxyZappOrgTestBasic1EndGetString(iHandle, aAsyncHandle, &valueStr))
				{
					throw(new ProxyError());
				}
			}
            aValueStr = Marshal.PtrToStringAnsi((IntPtr)valueStr);
            ZappFree(valueStr);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValueBin"></param>
        public unsafe void SyncSetBinary(string aValueBin)
        {
			char* valueBin = (char*)Marshal.StringToHGlobalAnsi(aValueBin);
			uint valueBinLen = (uint)aValueBin.Length;
			{
				CpProxyZappOrgTestBasic1SyncSetBinary(iHandle, valueBin, valueBinLen);
			}
			Marshal.FreeHGlobal((IntPtr)valueBin);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBinary().</remarks>
        /// <param name="aValueBin"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetBinary(string aValueBin, CallbackAsyncComplete aCallback)
        {
			char* valueBin = (char*)Marshal.StringToHGlobalAnsi(aValueBin);
			uint valueBinLen = (uint)aValueBin.Length;
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetBinary(iHandle, valueBin, valueBinLen, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)valueBin);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetBinary(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetBinary(iHandle, aAsyncHandle))
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
        /// <param name="aValueBin"></param>
        public unsafe void SyncGetBinary(out string aValueBin)
        {
			char* valueBin;
			uint valueBinLen;
			{
				CpProxyZappOrgTestBasic1SyncGetBinary(iHandle, &valueBin, &valueBinLen);
			}
            aValueBin = Marshal.PtrToStringAnsi((IntPtr)valueBin, (int)valueBinLen);
            ZappFree(valueBin);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetBinary().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetBinary(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetBinary(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValueBin"></param>
        public unsafe void EndGetBinary(uint aAsyncHandle, out string aValueBin)
        {
			char* valueBin;
			uint valueBinLen;
			{
				if (0 != CpProxyZappOrgTestBasic1EndGetBinary(iHandle, aAsyncHandle, &valueBin, &valueBinLen))
				{
					throw(new ProxyError());
				}
			}
            aValueBin = Marshal.PtrToStringAnsi((IntPtr)valueBin, (int)valueBinLen);
            ZappFree(valueBin);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncToggleBool()
        {
			{
				CpProxyZappOrgTestBasic1SyncToggleBool(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndToggleBool().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginToggleBool(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginToggleBool(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndToggleBool(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndToggleBool(iHandle, aAsyncHandle))
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
        /// <param name="aData"></param>
        /// <param name="aFileFullName"></param>
        public unsafe void SyncWriteFile(string aData, string aFileFullName)
        {
			char* data = (char*)Marshal.StringToHGlobalAnsi(aData);
			char* fileFullName = (char*)Marshal.StringToHGlobalAnsi(aFileFullName);
			{
				CpProxyZappOrgTestBasic1SyncWriteFile(iHandle, data, fileFullName);
			}
			Marshal.FreeHGlobal((IntPtr)data);
			Marshal.FreeHGlobal((IntPtr)fileFullName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndWriteFile().</remarks>
        /// <param name="aData"></param>
        /// <param name="aFileFullName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginWriteFile(string aData, string aFileFullName, CallbackAsyncComplete aCallback)
        {
			char* data = (char*)Marshal.StringToHGlobalAnsi(aData);
			char* fileFullName = (char*)Marshal.StringToHGlobalAnsi(aFileFullName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginWriteFile(iHandle, data, fileFullName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)data);
			Marshal.FreeHGlobal((IntPtr)fileFullName);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndWriteFile(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndWriteFile(iHandle, aAsyncHandle))
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
        public unsafe void SyncShutdown()
        {
			{
				CpProxyZappOrgTestBasic1SyncShutdown(iHandle);
			}
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndShutdown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginShutdown(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginShutdown(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndShutdown(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndShutdown(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Set a delegate to be run when the VarUint state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarUintChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarUintChanged(CallbackPropertyChanged aVarUintChanged)
        {
            iVarUintChanged = aVarUintChanged;
            iCallbackVarUintChanged = new Callback(PropertyVarUintChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestBasic1SetPropertyVarUintChanged(iHandle, iCallbackVarUintChanged, ptr);
        }

        private void PropertyVarUintChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestBasic1 self = (CpProxyZappOrgTestBasic1)gch.Target;
            self.iVarUintChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the VarInt state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarIntChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarIntChanged(CallbackPropertyChanged aVarIntChanged)
        {
            iVarIntChanged = aVarIntChanged;
            iCallbackVarIntChanged = new Callback(PropertyVarIntChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestBasic1SetPropertyVarIntChanged(iHandle, iCallbackVarIntChanged, ptr);
        }

        private void PropertyVarIntChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestBasic1 self = (CpProxyZappOrgTestBasic1)gch.Target;
            self.iVarIntChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the VarBool state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarBoolChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarBoolChanged(CallbackPropertyChanged aVarBoolChanged)
        {
            iVarBoolChanged = aVarBoolChanged;
            iCallbackVarBoolChanged = new Callback(PropertyVarBoolChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestBasic1SetPropertyVarBoolChanged(iHandle, iCallbackVarBoolChanged, ptr);
        }

        private void PropertyVarBoolChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestBasic1 self = (CpProxyZappOrgTestBasic1)gch.Target;
            self.iVarBoolChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the VarStr state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarStrChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarStrChanged(CallbackPropertyChanged aVarStrChanged)
        {
            iVarStrChanged = aVarStrChanged;
            iCallbackVarStrChanged = new Callback(PropertyVarStrChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestBasic1SetPropertyVarStrChanged(iHandle, iCallbackVarStrChanged, ptr);
        }

        private void PropertyVarStrChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestBasic1 self = (CpProxyZappOrgTestBasic1)gch.Target;
            self.iVarStrChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the VarBin state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestBasic1 instance will not overlap.</remarks>
        /// <param name="aVarBinChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyVarBinChanged(CallbackPropertyChanged aVarBinChanged)
        {
            iVarBinChanged = aVarBinChanged;
            iCallbackVarBinChanged = new Callback(PropertyVarBinChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyZappOrgTestBasic1SetPropertyVarBinChanged(iHandle, iCallbackVarBinChanged, ptr);
        }

        private void PropertyVarBinChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyZappOrgTestBasic1 self = (CpProxyZappOrgTestBasic1)gch.Target;
            self.iVarBinChanged();
        }

        /// <summary>
        /// Query the value of the VarUint property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aVarUint">Will be set to the value of the property</param>
        public unsafe void PropertyVarUint(out uint aVarUint)
        {
			fixed (uint* varUint = &aVarUint)
			{
	            CpProxyZappOrgTestBasic1PropertyVarUint(iHandle, varUint);
			}
        }

        /// <summary>
        /// Query the value of the VarInt property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aVarInt">Will be set to the value of the property</param>
        public unsafe void PropertyVarInt(out int aVarInt)
        {
			fixed (int* varInt = &aVarInt)
			{
	            CpProxyZappOrgTestBasic1PropertyVarInt(iHandle, varInt);
			}
        }

        /// <summary>
        /// Query the value of the VarBool property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aVarBool">Will be set to the value of the property</param>
        public unsafe void PropertyVarBool(out bool aVarBool)
        {
			uint varBool;
	        CpProxyZappOrgTestBasic1PropertyVarBool(iHandle, &varBool);
			aVarBool = (varBool != 0);
        }

        /// <summary>
        /// Query the value of the VarStr property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aVarStr">Will be set to the value of the property</param>
        public unsafe void PropertyVarStr(out string aVarStr)
        {
			char* ptr;
            CpProxyZappOrgTestBasic1PropertyVarStr(iHandle, &ptr);
            aVarStr = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the VarBin property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
	    /// to Unsubscribe().</remarks>
        /// <param name="aVarBin">Will be set to the value of the property</param>
        public unsafe void PropertyVarBin(out string aVarBin)
        {
			char* ptr;
			uint len;
	        CpProxyZappOrgTestBasic1PropertyVarBin(iHandle, &ptr, &len);
            aVarBin = Marshal.PtrToStringAnsi((IntPtr)ptr, (int)len);
            ZappFree(ptr);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestBasic1()
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
                CpProxyZappOrgTestBasic1Destroy(iHandle);
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

