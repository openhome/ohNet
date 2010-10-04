using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkDelay1 : IDisposable
    {
        [DllImport("DvLinnCoUkDelay1")]
        static extern uint DvServiceLinnCoUkDelay1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkDelay1")]
        static extern unsafe int DvServiceLinnCoUkDelay1SetPropertyPresetXml(uint aHandle, char* aValue);
        [DllImport("DvLinnCoUkDelay1")]
        static extern unsafe void DvServiceLinnCoUkDelay1GetPropertyPresetXml(uint aHandle, char** aValue);
        [DllImport("DvLinnCoUkDelay1")]
        static extern unsafe int DvServiceLinnCoUkDelay1SetPropertyPresetIndex(uint aHandle, uint aValue);
        [DllImport("DvLinnCoUkDelay1")]
        static extern unsafe void DvServiceLinnCoUkDelay1GetPropertyPresetIndex(uint aHandle, uint* aValue);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionPresetXml(uint aHandle, CallbackPresetXml aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionPresetIndex(uint aHandle, CallbackPresetIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionSetPresetIndex(uint aHandle, CallbackSetPresetIndex aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionSetPresetDelay(uint aHandle, CallbackSetPresetDelay aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionSetPresetVisible(uint aHandle, CallbackSetPresetVisible aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionSetPresetName(uint aHandle, CallbackSetPresetName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionDelayMinimum(uint aHandle, CallbackDelayMinimum aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionDelayMaximum(uint aHandle, CallbackDelayMaximum aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkDelay1")]
        static extern void DvServiceLinnCoUkDelay1EnableActionPresetCount(uint aHandle, CallbackPresetCount aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackPresetXml(IntPtr aPtr, uint aVersion, char** aaPresetXml);
        private unsafe delegate int CallbackPresetIndex(IntPtr aPtr, uint aVersion, uint* aaIndex);
        private unsafe delegate int CallbackSetPresetIndex(IntPtr aPtr, uint aVersion, uint aaIndex);
        private unsafe delegate int CallbackSetPresetDelay(IntPtr aPtr, uint aVersion, uint aaIndex, uint aaDelay);
        private unsafe delegate int CallbackSetPresetVisible(IntPtr aPtr, uint aVersion, uint aaIndex, int aaVisible);
        private unsafe delegate int CallbackSetPresetName(IntPtr aPtr, uint aVersion, uint aaIndex, char* aaName);
        private unsafe delegate int CallbackDelayMinimum(IntPtr aPtr, uint aVersion, uint* aaDelay);
        private unsafe delegate int CallbackDelayMaximum(IntPtr aPtr, uint aVersion, uint* aaDelay);
        private unsafe delegate int CallbackPresetCount(IntPtr aPtr, uint aVersion, uint* aaCount);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackPresetXml iCallbackPresetXml;
        private CallbackPresetIndex iCallbackPresetIndex;
        private CallbackSetPresetIndex iCallbackSetPresetIndex;
        private CallbackSetPresetDelay iCallbackSetPresetDelay;
        private CallbackSetPresetVisible iCallbackSetPresetVisible;
        private CallbackSetPresetName iCallbackSetPresetName;
        private CallbackDelayMinimum iCallbackDelayMinimum;
        private CallbackDelayMaximum iCallbackDelayMaximum;
        private CallbackPresetCount iCallbackPresetCount;

        public DvServiceLinnCoUkDelay1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkDelay1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyPresetXml(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceLinnCoUkDelay1SetPropertyPresetXml(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyPresetXml(out string aValue)
        {
            char* value;
            DvServiceLinnCoUkDelay1GetPropertyPresetXml(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyPresetIndex(uint aValue)
        {
            if (0 != DvServiceLinnCoUkDelay1SetPropertyPresetIndex(iHandle, aValue))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyPresetIndex(out uint aValue)
        {
            fixed (uint* value = &aValue)
			{
                DvServiceLinnCoUkDelay1GetPropertyPresetIndex(iHandle, value);
            }
        }

        protected unsafe void EnableActionPresetXml()
        {
            iCallbackPresetXml = new CallbackPresetXml(DoPresetXml);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionPresetXml(iHandle, iCallbackPresetXml, ptr);
        }

        protected unsafe void EnableActionPresetIndex()
        {
            iCallbackPresetIndex = new CallbackPresetIndex(DoPresetIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionPresetIndex(iHandle, iCallbackPresetIndex, ptr);
        }

        protected unsafe void EnableActionSetPresetIndex()
        {
            iCallbackSetPresetIndex = new CallbackSetPresetIndex(DoSetPresetIndex);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionSetPresetIndex(iHandle, iCallbackSetPresetIndex, ptr);
        }

        protected unsafe void EnableActionSetPresetDelay()
        {
            iCallbackSetPresetDelay = new CallbackSetPresetDelay(DoSetPresetDelay);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionSetPresetDelay(iHandle, iCallbackSetPresetDelay, ptr);
        }

        protected unsafe void EnableActionSetPresetVisible()
        {
            iCallbackSetPresetVisible = new CallbackSetPresetVisible(DoSetPresetVisible);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionSetPresetVisible(iHandle, iCallbackSetPresetVisible, ptr);
        }

        protected unsafe void EnableActionSetPresetName()
        {
            iCallbackSetPresetName = new CallbackSetPresetName(DoSetPresetName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionSetPresetName(iHandle, iCallbackSetPresetName, ptr);
        }

        protected unsafe void EnableActionDelayMinimum()
        {
            iCallbackDelayMinimum = new CallbackDelayMinimum(DoDelayMinimum);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionDelayMinimum(iHandle, iCallbackDelayMinimum, ptr);
        }

        protected unsafe void EnableActionDelayMaximum()
        {
            iCallbackDelayMaximum = new CallbackDelayMaximum(DoDelayMaximum);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionDelayMaximum(iHandle, iCallbackDelayMaximum, ptr);
        }

        protected unsafe void EnableActionPresetCount()
        {
            iCallbackPresetCount = new CallbackPresetCount(DoPresetCount);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkDelay1EnableActionPresetCount(iHandle, iCallbackPresetCount, ptr);
        }

        protected virtual void PresetXml(uint aVersion, out string aaPresetXml)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void PresetIndex(uint aVersion, out uint aaIndex)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetPresetIndex(uint aVersion, uint aaIndex)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetPresetDelay(uint aVersion, uint aaIndex, uint aaDelay)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetPresetVisible(uint aVersion, uint aaIndex, bool aaVisible)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetPresetName(uint aVersion, uint aaIndex, string aaName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DelayMinimum(uint aVersion, out uint aaDelay)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void DelayMaximum(uint aVersion, out uint aaDelay)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void PresetCount(uint aVersion, out uint aaCount)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoPresetXml(IntPtr aPtr, uint aVersion, char** aaPresetXml)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            string aPresetXml;
            self.PresetXml(aVersion, out aPresetXml);
            *aaPresetXml = (char*)Marshal.StringToHGlobalAnsi(aPresetXml).ToPointer();
            return 0;
        }

        private static unsafe int DoPresetIndex(IntPtr aPtr, uint aVersion, uint* aaIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            uint aIndex;
            self.PresetIndex(aVersion, out aIndex);
            *aaIndex = aIndex;
            return 0;
        }

        private static unsafe int DoSetPresetIndex(IntPtr aPtr, uint aVersion, uint aaIndex)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            self.SetPresetIndex(aVersion, aaIndex);
            return 0;
        }

        private static unsafe int DoSetPresetDelay(IntPtr aPtr, uint aVersion, uint aaIndex, uint aaDelay)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            self.SetPresetDelay(aVersion, aaIndex, aaDelay);
            return 0;
        }

        private static unsafe int DoSetPresetVisible(IntPtr aPtr, uint aVersion, uint aaIndex, int aaVisible)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            bool aVisible = (aaVisible != 0);
            self.SetPresetVisible(aVersion, aaIndex, aVisible);
            return 0;
        }

        private static unsafe int DoSetPresetName(IntPtr aPtr, uint aVersion, uint aaIndex, char* aaName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            string aName = Marshal.PtrToStringAnsi((IntPtr)aaName);
            self.SetPresetName(aVersion, aaIndex, aName);
            return 0;
        }

        private static unsafe int DoDelayMinimum(IntPtr aPtr, uint aVersion, uint* aaDelay)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            uint aDelay;
            self.DelayMinimum(aVersion, out aDelay);
            *aaDelay = aDelay;
            return 0;
        }

        private static unsafe int DoDelayMaximum(IntPtr aPtr, uint aVersion, uint* aaDelay)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            uint aDelay;
            self.DelayMaximum(aVersion, out aDelay);
            *aaDelay = aDelay;
            return 0;
        }

        private static unsafe int DoPresetCount(IntPtr aPtr, uint aVersion, uint* aaCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkDelay1 self = (DvServiceLinnCoUkDelay1)gch.Target;
            uint aCount;
            self.PresetCount(aVersion, out aCount);
            *aaCount = aCount;
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkDelay1()
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
            DvServiceLinnCoUkDelay1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

