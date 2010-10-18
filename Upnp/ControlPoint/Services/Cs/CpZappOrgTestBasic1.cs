using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyZappOrgTestBasic1 : CpProxy, IDisposable
    {
        [DllImport("CpZappOrgTestBasic1")]
        static extern IntPtr CpProxyZappOrgTestBasic1Create(IntPtr aDeviceHandle);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1Destroy(IntPtr aHandle);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncIncrement(IntPtr aHandle, uint aValue, uint* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginIncrement(IntPtr aHandle, uint aValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndIncrement(IntPtr aHandle, IntPtr aAsync, uint* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncDecrement(IntPtr aHandle, int aValue, int* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginDecrement(IntPtr aHandle, int aValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndDecrement(IntPtr aHandle, IntPtr aAsync, int* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncToggle(IntPtr aHandle, uint aValue, uint* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginToggle(IntPtr aHandle, uint aValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndToggle(IntPtr aHandle, IntPtr aAsync, uint* aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncEchoString(IntPtr aHandle, char* aValue, char** aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginEchoString(IntPtr aHandle, char* aValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndEchoString(IntPtr aHandle, IntPtr aAsync, char** aResult);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncEchoBinary(IntPtr aHandle, char* aValue, uint aValueLen, char** aResult, uint* aResultLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginEchoBinary(IntPtr aHandle, char* aValue, uint aValueLen, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndEchoBinary(IntPtr aHandle, IntPtr aAsync, char** aResult, uint* aResultLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetUint(IntPtr aHandle, uint aValueUint);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetUint(IntPtr aHandle, uint aValueUint, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetUint(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetUint(IntPtr aHandle, uint* aValueUint);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetUint(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetUint(IntPtr aHandle, IntPtr aAsync, uint* aValueUint);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetInt(IntPtr aHandle, int aValueInt);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetInt(IntPtr aHandle, int aValueInt, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetInt(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetInt(IntPtr aHandle, int* aValueInt);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetInt(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetInt(IntPtr aHandle, IntPtr aAsync, int* aValueInt);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetBool(IntPtr aHandle, uint aValueBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetBool(IntPtr aHandle, uint aValueBool, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetBool(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetBool(IntPtr aHandle, uint* aValueBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetBool(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetBool(IntPtr aHandle, IntPtr aAsync, uint* aValueBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetMultiple(IntPtr aHandle, uint aValueUint, int aValueInt, uint aValueBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetMultiple(IntPtr aHandle, uint aValueUint, int aValueInt, uint aValueBool, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetMultiple(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetString(IntPtr aHandle, char* aValueStr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetString(IntPtr aHandle, char* aValueStr, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetString(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetString(IntPtr aHandle, char** aValueStr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetString(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetString(IntPtr aHandle, IntPtr aAsync, char** aValueStr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncSetBinary(IntPtr aHandle, char* aValueBin, uint aValueBinLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginSetBinary(IntPtr aHandle, char* aValueBin, uint aValueBinLen, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndSetBinary(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1SyncGetBinary(IntPtr aHandle, char** aValueBin, uint* aValueBinLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1BeginGetBinary(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe int CpProxyZappOrgTestBasic1EndGetBinary(IntPtr aHandle, IntPtr aAsync, char** aValueBin, uint* aValueBinLen);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarUintChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarIntChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarBoolChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarStrChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern void CpProxyZappOrgTestBasic1SetPropertyVarBinChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarUint(IntPtr aHandle, uint* aVarUint);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarInt(IntPtr aHandle, int* aVarInt);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarBool(IntPtr aHandle, uint* aVarBool);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarStr(IntPtr aHandle, char** aVarStr);
        [DllImport("CpZappOrgTestBasic1")]
        static extern unsafe void CpProxyZappOrgTestBasic1PropertyVarBin(IntPtr aHandle, char** aVarBin, uint* aLen);
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

        public CpProxyZappOrgTestBasic1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestBasic1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncIncrement(uint aValue, out uint aResult)
        {
			fixed (uint* result = &aResult)
			{
				CpProxyZappOrgTestBasic1SyncIncrement(iHandle, aValue, result);
			}
        }

        public unsafe void BeginIncrement(uint aValue, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginIncrement(iHandle, aValue, iActionComplete, ptr);
        }

        public unsafe void EndIncrement(IntPtr aAsyncHandle, out uint aResult)
        {
			fixed (uint* result = &aResult)
			{
				if (0 != CpProxyZappOrgTestBasic1EndIncrement(iHandle, aAsyncHandle, result))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncDecrement(int aValue, out int aResult)
        {
			fixed (int* result = &aResult)
			{
				CpProxyZappOrgTestBasic1SyncDecrement(iHandle, aValue, result);
			}
        }

        public unsafe void BeginDecrement(int aValue, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginDecrement(iHandle, aValue, iActionComplete, ptr);
        }

        public unsafe void EndDecrement(IntPtr aAsyncHandle, out int aResult)
        {
			fixed (int* result = &aResult)
			{
				if (0 != CpProxyZappOrgTestBasic1EndDecrement(iHandle, aAsyncHandle, result))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncToggle(bool aValue, out bool aResult)
        {
			uint value = (aValue? 1u : 0u);
			uint result;
			{
				CpProxyZappOrgTestBasic1SyncToggle(iHandle, value, &result);
			}
			aResult = (result != 0);
        }

        public unsafe void BeginToggle(bool aValue, CallbackAsyncComplete aCallback)
        {
			uint value = (aValue? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginToggle(iHandle, value, iActionComplete, ptr);
        }

        public unsafe void EndToggle(IntPtr aAsyncHandle, out bool aResult)
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

        public unsafe void BeginEchoString(string aValue, CallbackAsyncComplete aCallback)
        {
			char* value = (char*)Marshal.StringToHGlobalAnsi(aValue);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginEchoString(iHandle, value, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)value);
        }

        public unsafe void EndEchoString(IntPtr aAsyncHandle, out string aResult)
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

        public unsafe void BeginEchoBinary(string aValue, CallbackAsyncComplete aCallback)
        {
			char* value = (char*)Marshal.StringToHGlobalAnsi(aValue);
			uint valueLen = (uint)aValue.Length;
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginEchoBinary(iHandle, value, valueLen, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)value);
        }

        public unsafe void EndEchoBinary(IntPtr aAsyncHandle, out string aResult)
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

        public unsafe void SyncSetUint(uint aValueUint)
        {
			{
				CpProxyZappOrgTestBasic1SyncSetUint(iHandle, aValueUint);
			}
        }

        public unsafe void BeginSetUint(uint aValueUint, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetUint(iHandle, aValueUint, iActionComplete, ptr);
        }

        public unsafe void EndSetUint(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetUint(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetUint(out uint aValueUint)
        {
			fixed (uint* valueUint = &aValueUint)
			{
				CpProxyZappOrgTestBasic1SyncGetUint(iHandle, valueUint);
			}
        }

        public unsafe void BeginGetUint(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetUint(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetUint(IntPtr aAsyncHandle, out uint aValueUint)
        {
			fixed (uint* valueUint = &aValueUint)
			{
				if (0 != CpProxyZappOrgTestBasic1EndGetUint(iHandle, aAsyncHandle, valueUint))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetInt(int aValueInt)
        {
			{
				CpProxyZappOrgTestBasic1SyncSetInt(iHandle, aValueInt);
			}
        }

        public unsafe void BeginSetInt(int aValueInt, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetInt(iHandle, aValueInt, iActionComplete, ptr);
        }

        public unsafe void EndSetInt(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetInt(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetInt(out int aValueInt)
        {
			fixed (int* valueInt = &aValueInt)
			{
				CpProxyZappOrgTestBasic1SyncGetInt(iHandle, valueInt);
			}
        }

        public unsafe void BeginGetInt(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetInt(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetInt(IntPtr aAsyncHandle, out int aValueInt)
        {
			fixed (int* valueInt = &aValueInt)
			{
				if (0 != CpProxyZappOrgTestBasic1EndGetInt(iHandle, aAsyncHandle, valueInt))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetBool(bool aValueBool)
        {
			uint valueBool = (aValueBool? 1u : 0u);
			{
				CpProxyZappOrgTestBasic1SyncSetBool(iHandle, valueBool);
			}
        }

        public unsafe void BeginSetBool(bool aValueBool, CallbackAsyncComplete aCallback)
        {
			uint valueBool = (aValueBool? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetBool(iHandle, valueBool, iActionComplete, ptr);
        }

        public unsafe void EndSetBool(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetBool(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetBool(out bool aValueBool)
        {
			uint valueBool;
			{
				CpProxyZappOrgTestBasic1SyncGetBool(iHandle, &valueBool);
			}
			aValueBool = (valueBool != 0);
        }

        public unsafe void BeginGetBool(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetBool(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetBool(IntPtr aAsyncHandle, out bool aValueBool)
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

        public unsafe void SyncSetMultiple(uint aValueUint, int aValueInt, bool aValueBool)
        {
			uint valueBool = (aValueBool? 1u : 0u);
			{
				CpProxyZappOrgTestBasic1SyncSetMultiple(iHandle, aValueUint, aValueInt, valueBool);
			}
        }

        public unsafe void BeginSetMultiple(uint aValueUint, int aValueInt, bool aValueBool, CallbackAsyncComplete aCallback)
        {
			uint valueBool = (aValueBool? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetMultiple(iHandle, aValueUint, aValueInt, valueBool, iActionComplete, ptr);
        }

        public unsafe void EndSetMultiple(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetMultiple(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetString(string aValueStr)
        {
			char* valueStr = (char*)Marshal.StringToHGlobalAnsi(aValueStr);
			{
				CpProxyZappOrgTestBasic1SyncSetString(iHandle, valueStr);
			}
			Marshal.FreeHGlobal((IntPtr)valueStr);
        }

        public unsafe void BeginSetString(string aValueStr, CallbackAsyncComplete aCallback)
        {
			char* valueStr = (char*)Marshal.StringToHGlobalAnsi(aValueStr);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetString(iHandle, valueStr, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)valueStr);
        }

        public unsafe void EndSetString(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetString(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetString(out string aValueStr)
        {
			char* valueStr;
			{
				CpProxyZappOrgTestBasic1SyncGetString(iHandle, &valueStr);
			}
            aValueStr = Marshal.PtrToStringAnsi((IntPtr)valueStr);
            ZappFree(valueStr);
        }

        public unsafe void BeginGetString(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetString(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetString(IntPtr aAsyncHandle, out string aValueStr)
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

        public unsafe void SyncSetBinary(string aValueBin)
        {
			char* valueBin = (char*)Marshal.StringToHGlobalAnsi(aValueBin);
			uint valueBinLen = (uint)aValueBin.Length;
			{
				CpProxyZappOrgTestBasic1SyncSetBinary(iHandle, valueBin, valueBinLen);
			}
			Marshal.FreeHGlobal((IntPtr)valueBin);
        }

        public unsafe void BeginSetBinary(string aValueBin, CallbackAsyncComplete aCallback)
        {
			char* valueBin = (char*)Marshal.StringToHGlobalAnsi(aValueBin);
			uint valueBinLen = (uint)aValueBin.Length;
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginSetBinary(iHandle, valueBin, valueBinLen, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)valueBin);
        }

        public unsafe void EndSetBinary(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestBasic1EndSetBinary(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

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

        public unsafe void BeginGetBinary(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestBasic1BeginGetBinary(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndGetBinary(IntPtr aAsyncHandle, out string aValueBin)
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

        public unsafe void PropertyVarUint(out uint aVarUint)
        {
			fixed (uint* varUint = &aVarUint)
			{
	            CpProxyZappOrgTestBasic1PropertyVarUint(iHandle, varUint);
			}
        }

        public unsafe void PropertyVarInt(out int aVarInt)
        {
			fixed (int* varInt = &aVarInt)
			{
	            CpProxyZappOrgTestBasic1PropertyVarInt(iHandle, varInt);
			}
        }

        public unsafe void PropertyVarBool(out bool aVarBool)
        {
			uint varBool;
	        CpProxyZappOrgTestBasic1PropertyVarBool(iHandle, &varBool);
			aVarBool = (varBool != 0);
        }

        public unsafe void PropertyVarStr(out string aVarStr)
        {
			char* ptr;
            CpProxyZappOrgTestBasic1PropertyVarStr(iHandle, &ptr);
            aVarStr = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyVarBin(out string aVarBin)
        {
			char* ptr;
			uint len;
	        CpProxyZappOrgTestBasic1PropertyVarBin(iHandle, &ptr, &len);
            aVarBin = Marshal.PtrToStringAnsi((IntPtr)ptr, (int)len);
            ZappFree(ptr);
        }

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
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            CpProxyZappOrgTestBasic1Destroy(handle);
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

