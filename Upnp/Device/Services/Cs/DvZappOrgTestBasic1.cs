using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    /// <summary>
    /// Provider for the zapp.org:TestBasic:1 UPnP service
    /// </summary>
    public class DvProviderZappOrgTestBasic1 : DvProvider, IDisposable
    {
        [DllImport("DvZappOrgTestBasic1")]
        static extern uint DvProviderZappOrgTestBasic1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvProviderZappOrgTestBasic1SetPropertyVarUint(uint aHandle, uint aValue, uint* aChanged);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvProviderZappOrgTestBasic1GetPropertyVarUint(uint aHandle, uint* aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvProviderZappOrgTestBasic1SetPropertyVarInt(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvProviderZappOrgTestBasic1GetPropertyVarInt(uint aHandle, int* aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvProviderZappOrgTestBasic1SetPropertyVarBool(uint aHandle, int aValue, uint* aChanged);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvProviderZappOrgTestBasic1GetPropertyVarBool(uint aHandle, int* aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvProviderZappOrgTestBasic1SetPropertyVarStr(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvProviderZappOrgTestBasic1GetPropertyVarStr(uint aHandle, char** aValue);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe int DvProviderZappOrgTestBasic1SetPropertyVarBin(uint aHandle, char* aValue, int aValueLen, uint* aChanged);
        [DllImport("DvZappOrgTestBasic1")]
        static extern unsafe void DvProviderZappOrgTestBasic1GetPropertyVarBin(uint aHandle, char** aValue, int* aValueLen);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionIncrement(uint aHandle, CallbackIncrement aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionDecrement(uint aHandle, CallbackDecrement aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionToggle(uint aHandle, CallbackToggle aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionEchoString(uint aHandle, CallbackEchoString aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionEchoBinary(uint aHandle, CallbackEchoBinary aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionSetUint(uint aHandle, CallbackSetUint aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionGetUint(uint aHandle, CallbackGetUint aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionSetInt(uint aHandle, CallbackSetInt aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionGetInt(uint aHandle, CallbackGetInt aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionSetBool(uint aHandle, CallbackSetBool aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionGetBool(uint aHandle, CallbackGetBool aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionSetMultiple(uint aHandle, CallbackSetMultiple aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionSetString(uint aHandle, CallbackSetString aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionGetString(uint aHandle, CallbackGetString aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionSetBinary(uint aHandle, CallbackSetBinary aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionGetBinary(uint aHandle, CallbackGetBinary aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionToggleBool(uint aHandle, CallbackToggleBool aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionWriteFile(uint aHandle, CallbackWriteFile aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestBasic1")]
        static extern void DvProviderZappOrgTestBasic1EnableActionShutdown(uint aHandle, CallbackShutdown aCallback, IntPtr aPtr);
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
        private unsafe delegate int CallbackToggleBool(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackWriteFile(IntPtr aPtr, uint aVersion, char* aData, char* aFileFullName);
        private unsafe delegate int CallbackShutdown(IntPtr aPtr, uint aVersion);

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
        private CallbackToggleBool iCallbackToggleBool;
        private CallbackWriteFile iCallbackWriteFile;
        private CallbackShutdown iCallbackShutdown;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderZappOrgTestBasic1(DvDevice aDevice)
        {
            iHandle = DvProviderZappOrgTestBasic1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the VarUint property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyVarUint(uint aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestBasic1SetPropertyVarUint(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the VarUint property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyVarUint(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderZappOrgTestBasic1GetPropertyVarUint(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the VarInt property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyVarInt(int aValue)
        {
            uint changed;
            if (0 != DvProviderZappOrgTestBasic1SetPropertyVarInt(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the VarInt property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyVarInt(out int aValue)
        {
            fixed (int* value = &aValue)
            {
                DvProviderZappOrgTestBasic1GetPropertyVarInt(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the VarBool property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyVarBool(bool aValue)
        {
            uint changed;
            int value = (aValue ? 1 : 0);
            if (0 != DvProviderZappOrgTestBasic1SetPropertyVarBool(iHandle, value, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the VarBool property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyVarBool(out bool aValue)
        {
            int value;
            DvProviderZappOrgTestBasic1GetPropertyVarBool(iHandle, &value);
            aValue = (value != 0);
        }

        /// <summary>
        /// Set the value of the VarStr property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyVarStr(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderZappOrgTestBasic1SetPropertyVarStr(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the VarStr property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyVarStr(out string aValue)
        {
            char* value;
            DvProviderZappOrgTestBasic1GetPropertyVarStr(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the VarBin property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyVarBin(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int valueLen = aValue.Length;
            int err = DvProviderZappOrgTestBasic1SetPropertyVarBin(iHandle, value, valueLen, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the VarBin property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyVarBin(out string aValue)
        {
            char* value;
            int valueLen;
             DvProviderZappOrgTestBasic1GetPropertyVarBin(iHandle, &value, &valueLen);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value, valueLen);
            ZappFree(value);
        }

        /// <summary>
        /// Signal that the action Increment is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIncrement must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIncrement()
        {
            iCallbackIncrement = new CallbackIncrement(DoIncrement);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionIncrement(iHandle, iCallbackIncrement, ptr);
        }

        /// <summary>
        /// Signal that the action Decrement is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDecrement must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDecrement()
        {
            iCallbackDecrement = new CallbackDecrement(DoDecrement);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionDecrement(iHandle, iCallbackDecrement, ptr);
        }

        /// <summary>
        /// Signal that the action Toggle is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoToggle must be overridden if this is called.</remarks>
        protected unsafe void EnableActionToggle()
        {
            iCallbackToggle = new CallbackToggle(DoToggle);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionToggle(iHandle, iCallbackToggle, ptr);
        }

        /// <summary>
        /// Signal that the action EchoString is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoEchoString must be overridden if this is called.</remarks>
        protected unsafe void EnableActionEchoString()
        {
            iCallbackEchoString = new CallbackEchoString(DoEchoString);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionEchoString(iHandle, iCallbackEchoString, ptr);
        }

        /// <summary>
        /// Signal that the action EchoBinary is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoEchoBinary must be overridden if this is called.</remarks>
        protected unsafe void EnableActionEchoBinary()
        {
            iCallbackEchoBinary = new CallbackEchoBinary(DoEchoBinary);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionEchoBinary(iHandle, iCallbackEchoBinary, ptr);
        }

        /// <summary>
        /// Signal that the action SetUint is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetUint must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetUint()
        {
            iCallbackSetUint = new CallbackSetUint(DoSetUint);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionSetUint(iHandle, iCallbackSetUint, ptr);
        }

        /// <summary>
        /// Signal that the action GetUint is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetUint must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetUint()
        {
            iCallbackGetUint = new CallbackGetUint(DoGetUint);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionGetUint(iHandle, iCallbackGetUint, ptr);
        }

        /// <summary>
        /// Signal that the action SetInt is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetInt must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetInt()
        {
            iCallbackSetInt = new CallbackSetInt(DoSetInt);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionSetInt(iHandle, iCallbackSetInt, ptr);
        }

        /// <summary>
        /// Signal that the action GetInt is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetInt must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetInt()
        {
            iCallbackGetInt = new CallbackGetInt(DoGetInt);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionGetInt(iHandle, iCallbackGetInt, ptr);
        }

        /// <summary>
        /// Signal that the action SetBool is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBool must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBool()
        {
            iCallbackSetBool = new CallbackSetBool(DoSetBool);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionSetBool(iHandle, iCallbackSetBool, ptr);
        }

        /// <summary>
        /// Signal that the action GetBool is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetBool must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetBool()
        {
            iCallbackGetBool = new CallbackGetBool(DoGetBool);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionGetBool(iHandle, iCallbackGetBool, ptr);
        }

        /// <summary>
        /// Signal that the action SetMultiple is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetMultiple must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetMultiple()
        {
            iCallbackSetMultiple = new CallbackSetMultiple(DoSetMultiple);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionSetMultiple(iHandle, iCallbackSetMultiple, ptr);
        }

        /// <summary>
        /// Signal that the action SetString is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetString must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetString()
        {
            iCallbackSetString = new CallbackSetString(DoSetString);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionSetString(iHandle, iCallbackSetString, ptr);
        }

        /// <summary>
        /// Signal that the action GetString is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetString must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetString()
        {
            iCallbackGetString = new CallbackGetString(DoGetString);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionGetString(iHandle, iCallbackGetString, ptr);
        }

        /// <summary>
        /// Signal that the action SetBinary is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBinary must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBinary()
        {
            iCallbackSetBinary = new CallbackSetBinary(DoSetBinary);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionSetBinary(iHandle, iCallbackSetBinary, ptr);
        }

        /// <summary>
        /// Signal that the action GetBinary is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetBinary must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetBinary()
        {
            iCallbackGetBinary = new CallbackGetBinary(DoGetBinary);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionGetBinary(iHandle, iCallbackGetBinary, ptr);
        }

        /// <summary>
        /// Signal that the action ToggleBool is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoToggleBool must be overridden if this is called.</remarks>
        protected unsafe void EnableActionToggleBool()
        {
            iCallbackToggleBool = new CallbackToggleBool(DoToggleBool);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionToggleBool(iHandle, iCallbackToggleBool, ptr);
        }

        /// <summary>
        /// Signal that the action WriteFile is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoWriteFile must be overridden if this is called.</remarks>
        protected unsafe void EnableActionWriteFile()
        {
            iCallbackWriteFile = new CallbackWriteFile(DoWriteFile);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionWriteFile(iHandle, iCallbackWriteFile, ptr);
        }

        /// <summary>
        /// Signal that the action Shutdown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoShutdown must be overridden if this is called.</remarks>
        protected unsafe void EnableActionShutdown()
        {
            iCallbackShutdown = new CallbackShutdown(DoShutdown);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestBasic1EnableActionShutdown(iHandle, iCallbackShutdown, ptr);
        }

        /// <summary>
        /// Increment action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Increment action for the owning device.
        ///
        /// Must be implemented iff EnableActionIncrement was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Increment(uint aVersion, uint aValue, out uint aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Decrement action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Decrement action for the owning device.
        ///
        /// Must be implemented iff EnableActionDecrement was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Decrement(uint aVersion, int aValue, out int aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Toggle action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Toggle action for the owning device.
        ///
        /// Must be implemented iff EnableActionToggle was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Toggle(uint aVersion, bool aValue, out bool aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EchoString action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EchoString action for the owning device.
        ///
        /// Must be implemented iff EnableActionEchoString was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void EchoString(uint aVersion, string aValue, out string aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EchoBinary action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EchoBinary action for the owning device.
        ///
        /// Must be implemented iff EnableActionEchoBinary was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void EchoBinary(uint aVersion, string aValue, out string aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetUint action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetUint action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetUint was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueUint"></param>
        protected virtual void SetUint(uint aVersion, uint aValueUint)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetUint action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetUint action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetUint was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueUint"></param>
        protected virtual void GetUint(uint aVersion, out uint aValueUint)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetInt action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetInt action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetInt was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueInt"></param>
        protected virtual void SetInt(uint aVersion, int aValueInt)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetInt action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetInt action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetInt was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueInt"></param>
        protected virtual void GetInt(uint aVersion, out int aValueInt)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBool action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBool action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBool was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueBool"></param>
        protected virtual void SetBool(uint aVersion, bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBool action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBool action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBool was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueBool"></param>
        protected virtual void GetBool(uint aVersion, out bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetMultiple action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetMultiple action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetMultiple was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        protected virtual void SetMultiple(uint aVersion, uint aValueUint, int aValueInt, bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetString action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetString action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetString was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueStr"></param>
        protected virtual void SetString(uint aVersion, string aValueStr)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetString action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetString action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetString was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueStr"></param>
        protected virtual void GetString(uint aVersion, out string aValueStr)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBinary action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBinary action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBinary was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueBin"></param>
        protected virtual void SetBinary(uint aVersion, string aValueBin)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBinary action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBinary action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBinary was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueBin"></param>
        protected virtual void GetBinary(uint aVersion, out string aValueBin)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ToggleBool action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ToggleBool action for the owning device.
        ///
        /// Must be implemented iff EnableActionToggleBool was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void ToggleBool(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// WriteFile action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// WriteFile action for the owning device.
        ///
        /// Must be implemented iff EnableActionWriteFile was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aData"></param>
        /// <param name="aFileFullName"></param>
        protected virtual void WriteFile(uint aVersion, string aData, string aFileFullName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Shutdown action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Shutdown action for the owning device.
        ///
        /// Must be implemented iff EnableActionShutdown was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Shutdown(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoIncrement(IntPtr aPtr, uint aVersion, uint aValue, uint* aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            uint result;
            self.Increment(aVersion, aValue, out result);
            *aResult = result;
            return 0;
        }

        private static unsafe int DoDecrement(IntPtr aPtr, uint aVersion, int aValue, int* aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            int result;
            self.Decrement(aVersion, aValue, out result);
            *aResult = result;
            return 0;
        }

        private static unsafe int DoToggle(IntPtr aPtr, uint aVersion, int aValue, int* aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            bool value = (aValue != 0);
            bool result;
            self.Toggle(aVersion, value, out result);
            *aResult = (result ? 1 : 0);
            return 0;
        }

        private static unsafe int DoEchoString(IntPtr aPtr, uint aVersion, char* aValue, char** aResult)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            string value = Marshal.PtrToStringAnsi((IntPtr)aValue);
            string result;
            self.EchoString(aVersion, value, out result);
            *aResult = (char*)Marshal.StringToHGlobalAnsi(result).ToPointer();
            return 0;
        }

        private static unsafe int DoEchoBinary(IntPtr aPtr, uint aVersion, char* aValue, int aValueLen, char** aResult, int* aResultLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
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
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            self.SetUint(aVersion, aValueUint);
            return 0;
        }

        private static unsafe int DoGetUint(IntPtr aPtr, uint aVersion, uint* aValueUint)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            uint valueUint;
            self.GetUint(aVersion, out valueUint);
            *aValueUint = valueUint;
            return 0;
        }

        private static unsafe int DoSetInt(IntPtr aPtr, uint aVersion, int aValueInt)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            self.SetInt(aVersion, aValueInt);
            return 0;
        }

        private static unsafe int DoGetInt(IntPtr aPtr, uint aVersion, int* aValueInt)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            int valueInt;
            self.GetInt(aVersion, out valueInt);
            *aValueInt = valueInt;
            return 0;
        }

        private static unsafe int DoSetBool(IntPtr aPtr, uint aVersion, int aValueBool)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            bool valueBool = (aValueBool != 0);
            self.SetBool(aVersion, valueBool);
            return 0;
        }

        private static unsafe int DoGetBool(IntPtr aPtr, uint aVersion, int* aValueBool)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            bool valueBool;
            self.GetBool(aVersion, out valueBool);
            *aValueBool = (valueBool ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetMultiple(IntPtr aPtr, uint aVersion, uint aValueUint, int aValueInt, int aValueBool)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            bool valueBool = (aValueBool != 0);
            self.SetMultiple(aVersion, aValueUint, aValueInt, valueBool);
            return 0;
        }

        private static unsafe int DoSetString(IntPtr aPtr, uint aVersion, char* aValueStr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            string valueStr = Marshal.PtrToStringAnsi((IntPtr)aValueStr);
            self.SetString(aVersion, valueStr);
            return 0;
        }

        private static unsafe int DoGetString(IntPtr aPtr, uint aVersion, char** aValueStr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            string valueStr;
            self.GetString(aVersion, out valueStr);
            *aValueStr = (char*)Marshal.StringToHGlobalAnsi(valueStr).ToPointer();
            return 0;
        }

        private static unsafe int DoSetBinary(IntPtr aPtr, uint aVersion, char* aValueBin, int aValueBinLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            string valueBin = Marshal.PtrToStringAnsi((IntPtr)aValueBin, aValueBinLen);
            self.SetBinary(aVersion, valueBin);
            return 0;
        }

        private static unsafe int DoGetBinary(IntPtr aPtr, uint aVersion, char** aValueBin, int* aValueBinLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            string valueBin;
            self.GetBinary(aVersion, out valueBin);
            *aValueBin = (char*)Marshal.StringToHGlobalAnsi(valueBin).ToPointer();
            *aValueBinLen = valueBin.Length;
            return 0;
        }

        private static unsafe int DoToggleBool(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            self.ToggleBool(aVersion);
            return 0;
        }

        private static unsafe int DoWriteFile(IntPtr aPtr, uint aVersion, char* aData, char* aFileFullName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            string data = Marshal.PtrToStringAnsi((IntPtr)aData);
            string fileFullName = Marshal.PtrToStringAnsi((IntPtr)aFileFullName);
            self.WriteFile(aVersion, data, fileFullName);
            return 0;
        }

        private static unsafe int DoShutdown(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            self.Shutdown(aVersion);
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderZappOrgTestBasic1()
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
            DvProviderZappOrgTestBasic1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

