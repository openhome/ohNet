using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceUpnpOrgSwitchPower1 : IDisposable
    {
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern uint DvServiceUpnpOrgSwitchPower1Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern void DvServiceUpnpOrgSwitchPower1Destroy(uint aHandle);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern unsafe int DvServiceUpnpOrgSwitchPower1SetPropertyStatus(uint aHandle, int aValue);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern unsafe void DvServiceUpnpOrgSwitchPower1GetPropertyStatus(uint aHandle, int* aValue);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern void DvServiceUpnpOrgSwitchPower1EnableActionSetTarget(uint aHandle, CallbackSetTarget aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern void DvServiceUpnpOrgSwitchPower1EnableActionGetTarget(uint aHandle, CallbackGetTarget aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgSwitchPower1")]
        static extern void DvServiceUpnpOrgSwitchPower1EnableActionGetStatus(uint aHandle, CallbackGetStatus aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetTarget(IntPtr aPtr, uint aVersion, int anewTargetValue);
        private unsafe delegate int CallbackGetTarget(IntPtr aPtr, uint aVersion, int* aRetTargetValue);
        private unsafe delegate int CallbackGetStatus(IntPtr aPtr, uint aVersion, int* aResultStatus);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackSetTarget iCallbackSetTarget;
        private CallbackGetTarget iCallbackGetTarget;
        private CallbackGetStatus iCallbackGetStatus;

        public DvServiceUpnpOrgSwitchPower1(DvDevice aDevice)
        {
            iHandle = DvServiceUpnpOrgSwitchPower1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyStatus(bool aValue)
        {
            int value = (aValue ? 1 : 0);
            if (0 != DvServiceUpnpOrgSwitchPower1SetPropertyStatus(iHandle, value))
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyStatus(out bool aValue)
        {
            int value;
            DvServiceUpnpOrgSwitchPower1GetPropertyStatus(iHandle, &value);
            aValue = (value != 0);
        }

        protected unsafe void EnableActionSetTarget()
        {
            iCallbackSetTarget = new CallbackSetTarget(DoSetTarget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgSwitchPower1EnableActionSetTarget(iHandle, iCallbackSetTarget, ptr);
        }

        protected unsafe void EnableActionGetTarget()
        {
            iCallbackGetTarget = new CallbackGetTarget(DoGetTarget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgSwitchPower1EnableActionGetTarget(iHandle, iCallbackGetTarget, ptr);
        }

        protected unsafe void EnableActionGetStatus()
        {
            iCallbackGetStatus = new CallbackGetStatus(DoGetStatus);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgSwitchPower1EnableActionGetStatus(iHandle, iCallbackGetStatus, ptr);
        }

        protected virtual void SetTarget(uint aVersion, bool anewTargetValue)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetTarget(uint aVersion, out bool aRetTargetValue)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetStatus(uint aVersion, out bool aResultStatus)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetTarget(IntPtr aPtr, uint aVersion, int anewTargetValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgSwitchPower1 self = (DvServiceUpnpOrgSwitchPower1)gch.Target;
            bool newTargetValue = (anewTargetValue != 0);
            self.SetTarget(aVersion, newTargetValue);
            return 0;
        }

        private static unsafe int DoGetTarget(IntPtr aPtr, uint aVersion, int* aRetTargetValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgSwitchPower1 self = (DvServiceUpnpOrgSwitchPower1)gch.Target;
            bool retTargetValue;
            self.GetTarget(aVersion, out retTargetValue);
            *aRetTargetValue = (retTargetValue ? 1 : 0);
            return 0;
        }

        private static unsafe int DoGetStatus(IntPtr aPtr, uint aVersion, int* aResultStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgSwitchPower1 self = (DvServiceUpnpOrgSwitchPower1)gch.Target;
            bool resultStatus;
            self.GetStatus(aVersion, out resultStatus);
            *aResultStatus = (resultStatus ? 1 : 0);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceUpnpOrgSwitchPower1()
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
            DvServiceUpnpOrgSwitchPower1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

