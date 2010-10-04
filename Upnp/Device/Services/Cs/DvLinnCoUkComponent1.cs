using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkComponent1 : IDisposable
    {
        [DllImport("DvLinnCoUkComponent1")]
        static extern uint DvServiceLinnCoUkComponent1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe int DvServiceLinnCoUkComponent1SetPropertyAmplifierEnabled(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe void DvServiceLinnCoUkComponent1GetPropertyAmplifierEnabled(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe int DvServiceLinnCoUkComponent1SetPropertyAmplifierAttenuation(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe void DvServiceLinnCoUkComponent1GetPropertyAmplifierAttenuation(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe int DvServiceLinnCoUkComponent1SetPropertyVolumeControlEnabled(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe void DvServiceLinnCoUkComponent1GetPropertyVolumeControlEnabled(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe int DvServiceLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(uint aHandle, int aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern unsafe void DvServiceLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(uint aHandle, int* aValue);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionAmplifierEnabled(uint aHandle, CallbackAmplifierEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionSetAmplifierEnabled(uint aHandle, CallbackSetAmplifierEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionAmplifierAttenuation(uint aHandle, CallbackAmplifierAttenuation aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionSetAmplifierAttenuation(uint aHandle, CallbackSetAmplifierAttenuation aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionSetVolumeControlEnabled(uint aHandle, CallbackSetVolumeControlEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionVolumeControlEnabled(uint aHandle, CallbackVolumeControlEnabled aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(uint aHandle, CallbackSetDigitalAudioOutputRaw aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(uint aHandle, CallbackDigitalAudioOutputRaw aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionAmplifierOverTemperature(uint aHandle, CallbackAmplifierOverTemperature aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionEthernetLinkConnected(uint aHandle, CallbackEthernetLinkConnected aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkComponent1")]
        static extern void DvServiceLinnCoUkComponent1EnableActionLocate(uint aHandle, CallbackLocate aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackAmplifierEnabled(IntPtr aPtr, uint aVersion, int* aaEnabled);
        private unsafe delegate int CallbackSetAmplifierEnabled(IntPtr aPtr, uint aVersion, int aaEnabled);
        private unsafe delegate int CallbackAmplifierAttenuation(IntPtr aPtr, uint aVersion, char** aaAttenuation);
        private unsafe delegate int CallbackSetAmplifierAttenuation(IntPtr aPtr, uint aVersion, char* aaAttenuation);
        private unsafe delegate int CallbackSetVolumeControlEnabled(IntPtr aPtr, uint aVersion, int aaEnabled);
        private unsafe delegate int CallbackVolumeControlEnabled(IntPtr aPtr, uint aVersion, int* aaEnabled);
        private unsafe delegate int CallbackSetDigitalAudioOutputRaw(IntPtr aPtr, uint aVersion, int aaRaw);
        private unsafe delegate int CallbackDigitalAudioOutputRaw(IntPtr aPtr, uint aVersion, int* aaRaw);
        private unsafe delegate int CallbackAmplifierOverTemperature(IntPtr aPtr, uint aVersion, int* aaOverTemperature);
        private unsafe delegate int CallbackEthernetLinkConnected(IntPtr aPtr, uint aVersion, int* aaLinkConnected);
        private unsafe delegate int CallbackLocate(IntPtr aPtr, uint aVersion);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackAmplifierEnabled iCallbackAmplifierEnabled;
        private CallbackSetAmplifierEnabled iCallbackSetAmplifierEnabled;
        private CallbackAmplifierAttenuation iCallbackAmplifierAttenuation;
        private CallbackSetAmplifierAttenuation iCallbackSetAmplifierAttenuation;
        private CallbackSetVolumeControlEnabled iCallbackSetVolumeControlEnabled;
        private CallbackVolumeControlEnabled iCallbackVolumeControlEnabled;
        private CallbackSetDigitalAudioOutputRaw iCallbackSetDigitalAudioOutputRaw;
        private CallbackDigitalAudioOutputRaw iCallbackDigitalAudioOutputRaw;
        private CallbackAmplifierOverTemperature iCallbackAmplifierOverTemperature;
        private CallbackEthernetLinkConnected iCallbackEthernetLinkConnected;
        private CallbackLocate iCallbackLocate;

        public DvServiceLinnCoUkComponent1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkComponent1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyAmplifierEnabled(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkComponent1SetPropertyAmplifierEnabled(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyAmplifierEnabled(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkComponent1GetPropertyAmplifierEnabled(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyAmplifierAttenuation(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkComponent1SetPropertyAmplifierAttenuation(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyAmplifierAttenuation(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkComponent1GetPropertyAmplifierAttenuation(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyVolumeControlEnabled(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkComponent1SetPropertyVolumeControlEnabled(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyVolumeControlEnabled(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkComponent1GetPropertyVolumeControlEnabled(iHandle, &value);
            aValue = (value != 0);
        }

        public unsafe void SetPropertyDigitalAudioOutputRaw(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceLinnCoUkComponent1SetPropertyDigitalAudioOutputRaw(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDigitalAudioOutputRaw(out bool aValue)
        {
            int value;
            DvServiceLinnCoUkComponent1GetPropertyDigitalAudioOutputRaw(iHandle, &value);
            aValue = (value != 0);
        }

        protected unsafe void EnableActionAmplifierEnabled()
        {
            iCallbackAmplifierEnabled = new CallbackAmplifierEnabled(DoAmplifierEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionAmplifierEnabled(iHandle, iCallbackAmplifierEnabled, ptr);
        }

        protected unsafe void EnableActionSetAmplifierEnabled()
        {
            iCallbackSetAmplifierEnabled = new CallbackSetAmplifierEnabled(DoSetAmplifierEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionSetAmplifierEnabled(iHandle, iCallbackSetAmplifierEnabled, ptr);
        }

        protected unsafe void EnableActionAmplifierAttenuation()
        {
            iCallbackAmplifierAttenuation = new CallbackAmplifierAttenuation(DoAmplifierAttenuation);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionAmplifierAttenuation(iHandle, iCallbackAmplifierAttenuation, ptr);
        }

        protected unsafe void EnableActionSetAmplifierAttenuation()
        {
            iCallbackSetAmplifierAttenuation = new CallbackSetAmplifierAttenuation(DoSetAmplifierAttenuation);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionSetAmplifierAttenuation(iHandle, iCallbackSetAmplifierAttenuation, ptr);
        }

        protected unsafe void EnableActionSetVolumeControlEnabled()
        {
            iCallbackSetVolumeControlEnabled = new CallbackSetVolumeControlEnabled(DoSetVolumeControlEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionSetVolumeControlEnabled(iHandle, iCallbackSetVolumeControlEnabled, ptr);
        }

        protected unsafe void EnableActionVolumeControlEnabled()
        {
            iCallbackVolumeControlEnabled = new CallbackVolumeControlEnabled(DoVolumeControlEnabled);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionVolumeControlEnabled(iHandle, iCallbackVolumeControlEnabled, ptr);
        }

        protected unsafe void EnableActionSetDigitalAudioOutputRaw()
        {
            iCallbackSetDigitalAudioOutputRaw = new CallbackSetDigitalAudioOutputRaw(DoSetDigitalAudioOutputRaw);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionSetDigitalAudioOutputRaw(iHandle, iCallbackSetDigitalAudioOutputRaw, ptr);
        }

        protected unsafe void EnableActionDigitalAudioOutputRaw()
        {
            iCallbackDigitalAudioOutputRaw = new CallbackDigitalAudioOutputRaw(DoDigitalAudioOutputRaw);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionDigitalAudioOutputRaw(iHandle, iCallbackDigitalAudioOutputRaw, ptr);
        }

        protected unsafe void EnableActionAmplifierOverTemperature()
        {
            iCallbackAmplifierOverTemperature = new CallbackAmplifierOverTemperature(DoAmplifierOverTemperature);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionAmplifierOverTemperature(iHandle, iCallbackAmplifierOverTemperature, ptr);
        }

        protected unsafe void EnableActionEthernetLinkConnected()
        {
            iCallbackEthernetLinkConnected = new CallbackEthernetLinkConnected(DoEthernetLinkConnected);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionEthernetLinkConnected(iHandle, iCallbackEthernetLinkConnected, ptr);
        }

        protected unsafe void EnableActionLocate()
        {
            iCallbackLocate = new CallbackLocate(DoLocate);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkComponent1EnableActionLocate(iHandle, iCallbackLocate, ptr);
        }

        protected virtual void AmplifierEnabled(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetAmplifierEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void AmplifierAttenuation(uint aVersion, out string aaAttenuation)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetAmplifierAttenuation(uint aVersion, string aaAttenuation)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetVolumeControlEnabled(uint aVersion, bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void VolumeControlEnabled(uint aVersion, out bool aaEnabled)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetDigitalAudioOutputRaw(uint aVersion, bool aaRaw)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DigitalAudioOutputRaw(uint aVersion, out bool aaRaw)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void AmplifierOverTemperature(uint aVersion, out bool aaOverTemperature)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void EthernetLinkConnected(uint aVersion, out bool aaLinkConnected)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Locate(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoAmplifierEnabled(IntPtr aPtr, uint aVersion, int* aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            bool aEnabled;
            self.AmplifierEnabled(aVersion, out aEnabled);
            *aaEnabled = (aEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetAmplifierEnabled(IntPtr aPtr, uint aVersion, int aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            bool aEnabled = (aaEnabled != 0);
            self.SetAmplifierEnabled(aVersion, aEnabled);
            return 0;
        }

        private static unsafe int DoAmplifierAttenuation(IntPtr aPtr, uint aVersion, char** aaAttenuation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            string aAttenuation;
            self.AmplifierAttenuation(aVersion, out aAttenuation);
            *aaAttenuation = (char*)Marshal.StringToHGlobalAnsi(aAttenuation).ToPointer();
            return 0;
        }

        private static unsafe int DoSetAmplifierAttenuation(IntPtr aPtr, uint aVersion, char* aaAttenuation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            string aAttenuation = Marshal.PtrToStringAnsi((IntPtr)aaAttenuation);
            self.SetAmplifierAttenuation(aVersion, aAttenuation);
            return 0;
        }

        private static unsafe int DoSetVolumeControlEnabled(IntPtr aPtr, uint aVersion, int aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            bool aEnabled = (aaEnabled != 0);
            self.SetVolumeControlEnabled(aVersion, aEnabled);
            return 0;
        }

        private static unsafe int DoVolumeControlEnabled(IntPtr aPtr, uint aVersion, int* aaEnabled)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            bool aEnabled;
            self.VolumeControlEnabled(aVersion, out aEnabled);
            *aaEnabled = (aEnabled ? 1 : 0);
            return 0;
        }

        private static unsafe int DoSetDigitalAudioOutputRaw(IntPtr aPtr, uint aVersion, int aaRaw)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            bool aRaw = (aaRaw != 0);
            self.SetDigitalAudioOutputRaw(aVersion, aRaw);
            return 0;
        }

        private static unsafe int DoDigitalAudioOutputRaw(IntPtr aPtr, uint aVersion, int* aaRaw)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            bool aRaw;
            self.DigitalAudioOutputRaw(aVersion, out aRaw);
            *aaRaw = (aRaw ? 1 : 0);
            return 0;
        }

        private static unsafe int DoAmplifierOverTemperature(IntPtr aPtr, uint aVersion, int* aaOverTemperature)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            bool aOverTemperature;
            self.AmplifierOverTemperature(aVersion, out aOverTemperature);
            *aaOverTemperature = (aOverTemperature ? 1 : 0);
            return 0;
        }

        private static unsafe int DoEthernetLinkConnected(IntPtr aPtr, uint aVersion, int* aaLinkConnected)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            bool aLinkConnected;
            self.EthernetLinkConnected(aVersion, out aLinkConnected);
            *aaLinkConnected = (aLinkConnected ? 1 : 0);
            return 0;
        }

        private static unsafe int DoLocate(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkComponent1 self = (DvServiceLinnCoUkComponent1)gch.Target;
            self.Locate(aVersion);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkComponent1()
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
            DvServiceLinnCoUkComponent1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

