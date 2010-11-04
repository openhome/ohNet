using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProviderZappOrgTestWidgetController1 : IDisposable
    {
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern uint DvProviderZappOrgTestWidgetController1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1EnableActionCreateWidget(uint aHandle, CallbackCreateWidget aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1EnableActionRemoveWidget(uint aHandle, CallbackRemoveWidget aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestWidgetController1")]
        static extern void DvProviderZappOrgTestWidgetController1EnableActionSetWidgetRegister(uint aHandle, CallbackSetWidgetRegister aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackCreateWidget(IntPtr aPtr, uint aVersion, char* aWidgetUdn);
        private unsafe delegate int CallbackRemoveWidget(IntPtr aPtr, uint aVersion, char* aWidgetUdn);
        private unsafe delegate int CallbackSetWidgetRegister(IntPtr aPtr, uint aVersion, char* aWidgetUdn, uint aRegisterIndex, uint aRegisterValue);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackCreateWidget iCallbackCreateWidget;
        private CallbackRemoveWidget iCallbackRemoveWidget;
        private CallbackSetWidgetRegister iCallbackSetWidgetRegister;

        public DvProviderZappOrgTestWidgetController1(DvDevice aDevice)
        {
            iHandle = DvProviderZappOrgTestWidgetController1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        protected unsafe void EnableActionCreateWidget()
        {
            iCallbackCreateWidget = new CallbackCreateWidget(DoCreateWidget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidgetController1EnableActionCreateWidget(iHandle, iCallbackCreateWidget, ptr);
        }

        protected unsafe void EnableActionRemoveWidget()
        {
            iCallbackRemoveWidget = new CallbackRemoveWidget(DoRemoveWidget);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidgetController1EnableActionRemoveWidget(iHandle, iCallbackRemoveWidget, ptr);
        }

        protected unsafe void EnableActionSetWidgetRegister()
        {
            iCallbackSetWidgetRegister = new CallbackSetWidgetRegister(DoSetWidgetRegister);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestWidgetController1EnableActionSetWidgetRegister(iHandle, iCallbackSetWidgetRegister, ptr);
        }

        protected virtual void CreateWidget(uint aVersion, string aWidgetUdn)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void RemoveWidget(uint aVersion, string aWidgetUdn)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetWidgetRegister(uint aVersion, string aWidgetUdn, uint aRegisterIndex, uint aRegisterValue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoCreateWidget(IntPtr aPtr, uint aVersion, char* aWidgetUdn)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            string widgetUdn = Marshal.PtrToStringAnsi((IntPtr)aWidgetUdn);
            self.CreateWidget(aVersion, widgetUdn);
            return 0;
        }

        private static unsafe int DoRemoveWidget(IntPtr aPtr, uint aVersion, char* aWidgetUdn)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            string widgetUdn = Marshal.PtrToStringAnsi((IntPtr)aWidgetUdn);
            self.RemoveWidget(aVersion, widgetUdn);
            return 0;
        }

        private static unsafe int DoSetWidgetRegister(IntPtr aPtr, uint aVersion, char* aWidgetUdn, uint aRegisterIndex, uint aRegisterValue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestWidgetController1 self = (DvProviderZappOrgTestWidgetController1)gch.Target;
            string widgetUdn = Marshal.PtrToStringAnsi((IntPtr)aWidgetUdn);
            self.SetWidgetRegister(aVersion, widgetUdn, aRegisterIndex, aRegisterValue);
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderZappOrgTestWidgetController1()
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
            DvProviderZappOrgTestWidgetController1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

