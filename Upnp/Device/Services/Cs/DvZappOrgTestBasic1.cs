using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceZappOrgTestBasic1 : IDisposable
    {
        [DllImport("DvZappOrgTestBasic1")]
        static extern uint DvServiceZappOrgTestBasic1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvServiceZappOrgTestBasic1SetPropertyVarUint(uint aHandle, uint aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvServiceZappOrgTestBasic1GetPropertyVarUint(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvServiceZappOrgTestBasic1SetPropertyVarInt(uint aHandle, int aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvServiceZappOrgTestBasic1GetPropertyVarInt(uint aHandle, int* aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvServiceZappOrgTestBasic1SetPropertyVarBool(uint aHandle, int aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvServiceZappOrgTestBasic1GetPropertyVarBool(uint aHandle, int* aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvServiceZappOrgTestBasic1SetPropertyVarStr(uint aHandle, char* aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvServiceZappOrgTestBasic1GetPropertyVarStr(uint aHandle, char** aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvServiceZappOrgTestBasic1SetPropertyVarBin(uint aHandle, char* aValue, int aValueLen);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvServiceZappOrgTestBasic1GetPropertyVarBin(uint aHandle, char** aValue, int* aValueLen);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionIncrement(uint aHandle, CallbackIncrement aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionDecrement(uint aHandle, CallbackDecrement aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionToggle(uint aHandle, CallbackToggle aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionEchoString(uint aHandle, CallbackEchoString aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionEchoBinary(uint aHandle, CallbackEchoBinary aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionSetUint(uint aHandle, CallbackSetUint aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionGetUint(uint aHandle, CallbackGetUint aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionSetInt(uint aHandle, CallbackSetInt aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionGetInt(uint aHandle, CallbackGetInt aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionSetBool(uint aHandle, CallbackSetBool aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionGetBool(uint aHandle, CallbackGetBool aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionSetMultiple(uint aHandle, CallbackSetMultiple aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionSetString(uint aHandle, CallbackSetString aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionGetString(uint aHandle, CallbackGetString aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionSetBinary(uint aHandle, CallbackSetBinary aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvServiceZappOrgTestBasic1EnableActionGetBinary(uint aHandle, CallbackGetBinary aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackIncrement(IntPtr aPtr, uint aVersion, uint aValue, uint* aResult);
        private unsafe delegate int CallbackDecrement(IntPtr aPtr, uint aVersion, int aValue, int* aResult);
        private unsafe delegate int CallbackToggle(IntPtr aPtr, uint aVersion, int aValue, int* aResult);
        private unsafe delegate int CallbackEchoString(IntPtr aPtr, uint aVersion, char* aValue, char** aResult);
        private unsafe delegate int CallbackEchoBinary(IntPtr aPtr, uint aVersion, char* aValue, int aValueLen, char** aResult, int* aResultLen);
        private unsafe delegate int CallbackSetUint(IntPtr aPtr, uint aVersion, uint aValueUint);
        private unsafe delegate int CallbackGetUint(IntPtr aPtr, uint aVersion, uint* aValueUint);
        private unsafe delegate int CallbackSetInt(IntPtr aPtr, uint aVersion, int aValueInt);
        private unsafe delegate int CallbackGetInt(IntPtr aPtr, uint aVersion, int* aValueInt);
        private unsafe delegate int CallbackSetBool(IntPtr aPtr, uint aVersion, int aValueBool);
        private unsafe delegate int CallbackGetBool(IntPtr aPtr, uint aVersion, int* aValueBool);
        private unsafe delegate int CallbackSetMultiple(IntPtr aPtr, uint aVersion, uint aValueUint, int aValueInt, int aValueBool);
        private unsafe delegate int CallbackSetString(IntPtr aPtr, uint aVersion, char* aValueStr);
        private unsafe delegate int CallbackGetString(IntPtr aPtr, uint aVersion, char** aValueStr);
        private unsafe delegate int CallbackSetBinary(IntPtr aPtr, uint aVersion, char* aValueBin, int aValueBinLen);
        private unsafe delegate int CallbackGetBinary(IntPtr aPtr, uint aVersion, char** aValueBin, int* aValueBinLen);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackIncrement iCallbackIncrement;
        private CallbackDecrement iCallbackDecrement;
        private CallbackToggle iCallbackToggle;
        private CallbackEchoString iCallbackEchoString;
        private CallbackEchoBinary iCallbackEchoBinary;
        private CallbackSetUint iCallbackSetUint;
        private CallbackGetUint iCallbackGetUint;
        private CallbackSetInt iCallbackSetInt;
        private CallbackGetInt iCallbackGetInt;
        private CallbackSetBool iCallbackSetBool;
        private CallbackGetBool iCallbackGetBool;
        private CallbackSetMultiple iCallbackSetMultiple;
        private CallbackSetString iCallbackSetString;
        private CallbackGetString iCallbackGetString;
        private CallbackSetBinary iCallbackSetBinary;
        private CallbackGetBinary iCallbackGetBinary;

        public DvServiceZappOrgTestBasic1(DvDevice aDevice)
        {
            iHandle = DvServiceZappOrgTestBasic1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyVarUint(uint aValue)
        {
            if (0 != DvServiceZappOrgTestBasic1SetPropertyVarUint(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyVarUint(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceZappOrgTestBasic1GetPropertyVarUint(iHandle, value);
            }
        }

        public unsafe void SetPropertyVarInt(int aValue)
        {
            if (0 != DvServiceZappOrgTestBasic1SetPropertyVarInt(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyVarInt(out int aValue)
        {
            fixed (int* value = &aValue)
			{
                DvServiceZappOrgTestBasic1GetPropertyVarInt(iHandle, value);
            }
        }

        public unsafe void SetPropertyVarBool(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceZappOrgTestBasic1SetPropertyVarBool(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyVarBool(out bool aValue)
        {
            int value;
            DvServiceZappOrgTestBasic1GetPropertyVarBool(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyVarStr(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceZappOrgTestBasic1SetPropertyVarStr(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyVarStr(out string aValue)
        {
            char* value;
            DvServiceZappOrgTestBasic1GetPropertyVarStr(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyVarBin(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int valueLen = aValue.Length;
            int err = DvServiceZappOrgTestBasic1SetPropertyVarBin(iHandle, value, valueLen);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyVarBin(out string aValue)
        {
            char* value;
            int valueLen;
             DvServiceZappOrgTestBasic1GetPropertyVarBin(iHandle, &value, &valueLen);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value, valueLen);
            ZappFree(value);
        }

        protected unsafe void EnableActionIncrement()
        {
            iCallbackIncrement = new CallbackIncrement(DoIncrement);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionIncrement(iHandle, iCallbackIncrement, ptr);
        }

        protected unsafe void EnableActionDecrement()
        {
            iCallbackDecrement = new CallbackDecrement(DoDecrement);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionDecrement(iHandle, iCallbackDecrement, ptr);
        }

        protected unsafe void EnableActionToggle()
        {
            iCallbackToggle = new CallbackToggle(DoToggle);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionToggle(iHandle, iCallbackToggle, ptr);
        }

        protected unsafe void EnableActionEchoString()
        {
            iCallbackEchoString = new CallbackEchoString(DoEchoString);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionEchoString(iHandle, iCallbackEchoString, ptr);
        }

        protected unsafe void EnableActionEchoBinary()
        {
            iCallbackEchoBinary = new CallbackEchoBinary(DoEchoBinary);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionEchoBinary(iHandle, iCallbackEchoBinary, ptr);
        }

        protected unsafe void EnableActionSetUint()
        {
            iCallbackSetUint = new CallbackSetUint(DoSetUint);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionSetUint(iHandle, iCallbackSetUint, ptr);
        }

        protected unsafe void EnableActionGetUint()
        {
            iCallbackGetUint = new CallbackGetUint(DoGetUint);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionGetUint(iHandle, iCallbackGetUint, ptr);
        }

        protected unsafe void EnableActionSetInt()
        {
            iCallbackSetInt = new CallbackSetInt(DoSetInt);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionSetInt(iHandle, iCallbackSetInt, ptr);
        }

        protected unsafe void EnableActionGetInt()
        {
            iCallbackGetInt = new CallbackGetInt(DoGetInt);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionGetInt(iHandle, iCallbackGetInt, ptr);
        }

        protected unsafe void EnableActionSetBool()
        {
            iCallbackSetBool = new CallbackSetBool(DoSetBool);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionSetBool(iHandle, iCallbackSetBool, ptr);
        }

        protected unsafe void EnableActionGetBool()
        {
            iCallbackGetBool = new CallbackGetBool(DoGetBool);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionGetBool(iHandle, iCallbackGetBool, ptr);
        }

        protected unsafe void EnableActionSetMultiple()
        {
            iCallbackSetMultiple = new CallbackSetMultiple(DoSetMultiple);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionSetMultiple(iHandle, iCallbackSetMultiple, ptr);
        }

        protected unsafe void EnableActionSetString()
        {
            iCallbackSetString = new CallbackSetString(DoSetString);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionSetString(iHandle, iCallbackSetString, ptr);
        }

        protected unsafe void EnableActionGetString()
        {
            iCallbackGetString = new CallbackGetString(DoGetString);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionGetString(iHandle, iCallbackGetString, ptr);
        }

        protected unsafe void EnableActionSetBinary()
        {
            iCallbackSetBinary = new CallbackSetBinary(DoSetBinary);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionSetBinary(iHandle, iCallbackSetBinary, ptr);
        }

        protected unsafe void EnableActionGetBinary()
        {
            iCallbackGetBinary = new CallbackGetBinary(DoGetBinary);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestBasic1EnableActionGetBinary(iHandle, iCallbackGetBinary, ptr);
        }

        protected virtual void Increment(uint aVersion, uint aValue, out uint aResult)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Decrement(uint aVersion, int aValue, out int aResult)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Toggle(uint aVersion, bool aValue, out bool aResult)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void EchoString(uint aVersion, string aValue, out string aResult)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void EchoBinary(uint aVersion, string aValue, out string aResult)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetUint(uint aVersion, uint aValueUint)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetUint(uint aVersion, out uint aValueUint)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetInt(uint aVersion, int aValueInt)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetInt(uint aVersion, out int aValueInt)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetBool(uint aVersion, bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetBool(uint aVersion, out bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetMultiple(uint aVersion, uint aValueUint, int aValueInt, bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetString(uint aVersion, string aValueStr)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetString(uint aVersion, out string aValueStr)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetBinary(uint aVersion, string aValueBin)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetBinary(uint aVersion, out string aValueBin)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoIncrement(IntPtr aPtr, uint aVersion, uint aValue, uint* aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            uint result;
            self.Increment(aVersion, aValue, out result);
            *aResult = result;
            return 0;
        }

        private static unsafe int DoDecrement(IntPtr aPtr, uint aVersion, int aValue, int* aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            int result;
            self.Decrement(aVersion, aValue, out result);
            *aResult = result;
            return 0;
        }

        private static unsafe int DoToggle(IntPtr aPtr, uint aVersion, int aValue, int* aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            bool value = (aValue != 0);
            bool result;
            self.Toggle(aVersion, value, out result);
            *aResult = (result ? 1 : 0);
            return 0;
        }

        private static unsafe int DoEchoString(IntPtr aPtr, uint aVersion, char* aValue, char** aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            string value = Marshal.PtrToStringAnsi((IntPtr)aValue);
            string result;
            self.EchoString(aVersion, value, out result);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            return 0;
        }

        private static unsafe int DoEchoBinary(IntPtr aPtr, uint aVersion, char* aValue, int aValueLen, char** aResult, int* aResultLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            string value = Marshal.PtrToStringAnsi((IntPtr)aValue, aValueLen);
            string result;
            self.EchoBinary(aVersion, value, out result);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            *aResultLen = result.Length;
            return 0;
        }

        private static unsafe int DoSetUint(IntPtr aPtr, uint aVersion, uint aValueUint)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            self.SetUint(aVersion, aValueUint);
            return 0;
        }

        private static unsafe int DoGetUint(IntPtr aPtr, uint aVersion, uint* aValueUint)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            uint valueUint;
            self.GetUint(aVersion, out valueUint);
            *aValueUint = valueUint;
            return 0;
        }

        private static unsafe int DoSetInt(IntPtr aPtr, uint aVersion, int aValueInt)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            self.SetInt(aVersion, aValueInt);
            return 0;
        }

        private static unsafe int DoGetInt(IntPtr aPtr, uint aVersion, int* aValueInt)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            int valueInt;
            self.GetInt(aVersion, out valueInt);
            *aValueInt = valueInt;
            return 0;
        }

        private static unsafe int DoSetBool(IntPtr aPtr, uint aVersion, int aValueBool)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            bool valueBool = (aValueBool != 0);
            self.SetBool(aVersion, valueBool);
            return 0;
        }

        private static unsafe int DoGetBool(IntPtr aPtr, uint aVersion, int* aValueBool)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            bool valueBool;
            self.GetBool(aVersion, out valueBool);
            *aValueBool = (valueBool ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetMultiple(IntPtr aPtr, uint aVersion, uint aValueUint, int aValueInt, int aValueBool)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            bool valueBool = (aValueBool != 0);
            self.SetMultiple(aVersion, aValueUint, aValueInt, valueBool);
            return 0;
        }

        private static unsafe int DoSetString(IntPtr aPtr, uint aVersion, char* aValueStr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            string valueStr = Marshal.PtrToStringAnsi((IntPtr)aValueStr);
            self.SetString(aVersion, valueStr);
            return 0;
        }

        private static unsafe int DoGetString(IntPtr aPtr, uint aVersion, char** aValueStr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            string valueStr;
            self.GetString(aVersion, out valueStr);
            *aValueStr = (char*)Marshal.StringToHGlobalAnsi(valueStr).ToPointer();
            return 0;
        }

        private static unsafe int DoSetBinary(IntPtr aPtr, uint aVersion, char* aValueBin, int aValueBinLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            string valueBin = Marshal.PtrToStringAnsi((IntPtr)aValueBin, aValueBinLen);
            self.SetBinary(aVersion, valueBin);
            return 0;
        }

        private static unsafe int DoGetBinary(IntPtr aPtr, uint aVersion, char** aValueBin, int* aValueBinLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestBasic1 self = (DvServiceZappOrgTestBasic1)gch.Target;
            string valueBin;
            self.GetBinary(aVersion, out valueBin);
            *aValueBin = (char*)Marshal.StringToHGlobalAnsi(valueBin).ToPointer();
            *aValueBinLen = valueBin.Length;
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceZappOrgTestBasic1()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            uint handle;
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                handle = iHandle;
                iHandle = 0;
            }
            DvServiceZappOrgTestBasic1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

