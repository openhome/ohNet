using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProviderLinnCoUkConfiguration1 : DvProvider, IDisposable
    {
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern uint DvProviderLinnCoUkConfiguration1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvProviderLinnCoUkConfiguration1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe int DvProviderLinnCoUkConfiguration1SetPropertyConfigurationXml(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe void DvProviderLinnCoUkConfiguration1GetPropertyConfigurationXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe int DvProviderLinnCoUkConfiguration1SetPropertyParameterXml(uint aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe void DvProviderLinnCoUkConfiguration1GetPropertyParameterXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvProviderLinnCoUkConfiguration1EnableActionConfigurationXml(uint aHandle, CallbackConfigurationXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvProviderLinnCoUkConfiguration1EnableActionParameterXml(uint aHandle, CallbackParameterXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvProviderLinnCoUkConfiguration1EnableActionSetParameter(uint aHandle, CallbackSetParameter aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackConfigurationXml(IntPtr aPtr, uint aVersion, char** aaConfigurationXml);
        private unsafe delegate int CallbackParameterXml(IntPtr aPtr, uint aVersion, char** aaParameterXml);
        private unsafe delegate int CallbackSetParameter(IntPtr aPtr, uint aVersion, char* aaTarget, char* aaName, char* aaValue);

        private GCHandle iGch;
        private CallbackConfigurationXml iCallbackConfigurationXml;
        private CallbackParameterXml iCallbackParameterXml;
        private CallbackSetParameter iCallbackSetParameter;

        public DvProviderLinnCoUkConfiguration1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkConfiguration1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe bool SetPropertyConfigurationXml(string aValue)
        {
        uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkConfiguration1SetPropertyConfigurationXml(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyConfigurationXml(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkConfiguration1GetPropertyConfigurationXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe bool SetPropertyParameterXml(string aValue)
        {
        uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkConfiguration1SetPropertyParameterXml(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        public unsafe void GetPropertyParameterXml(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkConfiguration1GetPropertyParameterXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionConfigurationXml()
        {
            iCallbackConfigurationXml = new CallbackConfigurationXml(DoConfigurationXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkConfiguration1EnableActionConfigurationXml(iHandle, iCallbackConfigurationXml, ptr);
        }

        protected unsafe void EnableActionParameterXml()
        {
            iCallbackParameterXml = new CallbackParameterXml(DoParameterXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkConfiguration1EnableActionParameterXml(iHandle, iCallbackParameterXml, ptr);
        }

        protected unsafe void EnableActionSetParameter()
        {
            iCallbackSetParameter = new CallbackSetParameter(DoSetParameter);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkConfiguration1EnableActionSetParameter(iHandle, iCallbackSetParameter, ptr);
        }

        protected virtual void ConfigurationXml(uint aVersion, out string aaConfigurationXml)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ParameterXml(uint aVersion, out string aaParameterXml)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetParameter(uint aVersion, string aaTarget, string aaName, string aaValue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoConfigurationXml(IntPtr aPtr, uint aVersion, char** aaConfigurationXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            string aConfigurationXml;
            self.ConfigurationXml(aVersion, out aConfigurationXml);
            *aaConfigurationXml = (char*)Marshal.StringToHGlobalAnsi(aConfigurationXml).ToPointer();
            return 0;
        }

        private static unsafe int DoParameterXml(IntPtr aPtr, uint aVersion, char** aaParameterXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            string aParameterXml;
            self.ParameterXml(aVersion, out aParameterXml);
            *aaParameterXml = (char*)Marshal.StringToHGlobalAnsi(aParameterXml).ToPointer();
            return 0;
        }

        private static unsafe int DoSetParameter(IntPtr aPtr, uint aVersion, char* aaTarget, char* aaName, char* aaValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkConfiguration1 self = (DvProviderLinnCoUkConfiguration1)gch.Target;
            string aTarget = Marshal.PtrToStringAnsi((IntPtr)aaTarget);
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            string aValue = Marshal.PtrToStringAnsi((IntPtr)aaValue);
            self.SetParameter(aVersion, aTarget, aName, aValue);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkConfiguration1()
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
            DvProviderLinnCoUkConfiguration1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

