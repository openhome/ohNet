using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkConfiguration1 : IDisposable
    {
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern uint DvServiceLinnCoUkConfiguration1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvServiceLinnCoUkConfiguration1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe int DvServiceLinnCoUkConfiguration1SetPropertyConfigurationXml(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe void DvServiceLinnCoUkConfiguration1GetPropertyConfigurationXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe int DvServiceLinnCoUkConfiguration1SetPropertyParameterXml(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern unsafe void DvServiceLinnCoUkConfiguration1GetPropertyParameterXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvServiceLinnCoUkConfiguration1EnableActionConfigurationXml(uint aHandle, CallbackConfigurationXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvServiceLinnCoUkConfiguration1EnableActionParameterXml(uint aHandle, CallbackParameterXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkConfiguration1")]
        static extern void DvServiceLinnCoUkConfiguration1EnableActionSetParameter(uint aHandle, CallbackSetParameter aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackConfigurationXml(IntPtr aPtr, uint aVersion, char** aaConfigurationXml);
        private unsafe delegate int CallbackParameterXml(IntPtr aPtr, uint aVersion, char** aaParameterXml);
        private unsafe delegate int CallbackSetParameter(IntPtr aPtr, uint aVersion, char* aaTarget, char* aaName, char* aaValue);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackConfigurationXml iCallbackConfigurationXml;
        private CallbackParameterXml iCallbackParameterXml;
        private CallbackSetParameter iCallbackSetParameter;

        public DvServiceLinnCoUkConfiguration1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkConfiguration1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyConfigurationXml(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkConfiguration1SetPropertyConfigurationXml(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyConfigurationXml(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkConfiguration1GetPropertyConfigurationXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyParameterXml(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkConfiguration1SetPropertyParameterXml(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyParameterXml(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkConfiguration1GetPropertyParameterXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionConfigurationXml()
        {
            iCallbackConfigurationXml = new CallbackConfigurationXml(DoConfigurationXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkConfiguration1EnableActionConfigurationXml(iHandle, iCallbackConfigurationXml, ptr);
        }

        protected unsafe void EnableActionParameterXml()
        {
            iCallbackParameterXml = new CallbackParameterXml(DoParameterXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkConfiguration1EnableActionParameterXml(iHandle, iCallbackParameterXml, ptr);
        }

        protected unsafe void EnableActionSetParameter()
        {
            iCallbackSetParameter = new CallbackSetParameter(DoSetParameter);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkConfiguration1EnableActionSetParameter(iHandle, iCallbackSetParameter, ptr);
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
            DvServiceLinnCoUkConfiguration1 self = (DvServiceLinnCoUkConfiguration1)gch.Target;
            string aConfigurationXml;
            self.ConfigurationXml(aVersion, out aConfigurationXml);
            *aaConfigurationXml = (char*)Marshal.StringToHGlobalAnsi(aConfigurationXml).ToPointer();
            return 0;
        }

        private static unsafe int DoParameterXml(IntPtr aPtr, uint aVersion, char** aaParameterXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkConfiguration1 self = (DvServiceLinnCoUkConfiguration1)gch.Target;
            string aParameterXml;
            self.ParameterXml(aVersion, out aParameterXml);
            *aaParameterXml = (char*)Marshal.StringToHGlobalAnsi(aParameterXml).ToPointer();
            return 0;
        }

        private static unsafe int DoSetParameter(IntPtr aPtr, uint aVersion, char* aaTarget, char* aaName, char* aaValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkConfiguration1 self = (DvServiceLinnCoUkConfiguration1)gch.Target;
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

        ~DvServiceLinnCoUkConfiguration1()
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
            DvServiceLinnCoUkConfiguration1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

