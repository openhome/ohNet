using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceLinnCoUkVolkano1 : IDisposable
    {
        [DllImport("DvLinnCoUkVolkano1")]
        static extern uint DvServiceLinnCoUkVolkano1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionReboot(uint aHandle, CallbackReboot aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionBootMode(uint aHandle, CallbackBootMode aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionSetBootMode(uint aHandle, CallbackSetBootMode aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionBspType(uint aHandle, CallbackBspType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionUglyName(uint aHandle, CallbackUglyName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionMacAddress(uint aHandle, CallbackMacAddress aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionProductId(uint aHandle, CallbackProductId aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionBoardId(uint aHandle, CallbackBoardId aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionBoardType(uint aHandle, CallbackBoardType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionMaxBoards(uint aHandle, CallbackMaxBoards aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvServiceLinnCoUkVolkano1EnableActionSoftwareVersion(uint aHandle, CallbackSoftwareVersion aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackReboot(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackBootMode(IntPtr aPtr, uint aVersion, char** aaMode);
        private unsafe delegate int CallbackSetBootMode(IntPtr aPtr, uint aVersion, char* aaMode);
        private unsafe delegate int CallbackBspType(IntPtr aPtr, uint aVersion, char** aaBspType);
        private unsafe delegate int CallbackUglyName(IntPtr aPtr, uint aVersion, char** aaUglyName);
        private unsafe delegate int CallbackMacAddress(IntPtr aPtr, uint aVersion, char** aaMacAddress);
        private unsafe delegate int CallbackProductId(IntPtr aPtr, uint aVersion, char** aaProductNumber);
        private unsafe delegate int CallbackBoardId(IntPtr aPtr, uint aVersion, uint aaIndex, char** aaBoardNumber);
        private unsafe delegate int CallbackBoardType(IntPtr aPtr, uint aVersion, uint aaIndex, char** aaBoardNumber);
        private unsafe delegate int CallbackMaxBoards(IntPtr aPtr, uint aVersion, uint* aaMaxBoards);
        private unsafe delegate int CallbackSoftwareVersion(IntPtr aPtr, uint aVersion, char** aaSoftwareVersion);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackReboot iCallbackReboot;
        private CallbackBootMode iCallbackBootMode;
        private CallbackSetBootMode iCallbackSetBootMode;
        private CallbackBspType iCallbackBspType;
        private CallbackUglyName iCallbackUglyName;
        private CallbackMacAddress iCallbackMacAddress;
        private CallbackProductId iCallbackProductId;
        private CallbackBoardId iCallbackBoardId;
        private CallbackBoardType iCallbackBoardType;
        private CallbackMaxBoards iCallbackMaxBoards;
        private CallbackSoftwareVersion iCallbackSoftwareVersion;

        public DvServiceLinnCoUkVolkano1(DvDevice aDevice)
        {
            iHandle = DvServiceLinnCoUkVolkano1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        protected unsafe void EnableActionReboot()
        {
            iCallbackReboot = new CallbackReboot(DoReboot);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionReboot(iHandle, iCallbackReboot, ptr);
        }

        protected unsafe void EnableActionBootMode()
        {
            iCallbackBootMode = new CallbackBootMode(DoBootMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionBootMode(iHandle, iCallbackBootMode, ptr);
        }

        protected unsafe void EnableActionSetBootMode()
        {
            iCallbackSetBootMode = new CallbackSetBootMode(DoSetBootMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionSetBootMode(iHandle, iCallbackSetBootMode, ptr);
        }

        protected unsafe void EnableActionBspType()
        {
            iCallbackBspType = new CallbackBspType(DoBspType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionBspType(iHandle, iCallbackBspType, ptr);
        }

        protected unsafe void EnableActionUglyName()
        {
            iCallbackUglyName = new CallbackUglyName(DoUglyName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionUglyName(iHandle, iCallbackUglyName, ptr);
        }

        protected unsafe void EnableActionMacAddress()
        {
            iCallbackMacAddress = new CallbackMacAddress(DoMacAddress);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionMacAddress(iHandle, iCallbackMacAddress, ptr);
        }

        protected unsafe void EnableActionProductId()
        {
            iCallbackProductId = new CallbackProductId(DoProductId);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionProductId(iHandle, iCallbackProductId, ptr);
        }

        protected unsafe void EnableActionBoardId()
        {
            iCallbackBoardId = new CallbackBoardId(DoBoardId);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionBoardId(iHandle, iCallbackBoardId, ptr);
        }

        protected unsafe void EnableActionBoardType()
        {
            iCallbackBoardType = new CallbackBoardType(DoBoardType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionBoardType(iHandle, iCallbackBoardType, ptr);
        }

        protected unsafe void EnableActionMaxBoards()
        {
            iCallbackMaxBoards = new CallbackMaxBoards(DoMaxBoards);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionMaxBoards(iHandle, iCallbackMaxBoards, ptr);
        }

        protected unsafe void EnableActionSoftwareVersion()
        {
            iCallbackSoftwareVersion = new CallbackSoftwareVersion(DoSoftwareVersion);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceLinnCoUkVolkano1EnableActionSoftwareVersion(iHandle, iCallbackSoftwareVersion, ptr);
        }

        protected virtual void Reboot(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void BootMode(uint aVersion, out string aaMode)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetBootMode(uint aVersion, string aaMode)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void BspType(uint aVersion, out string aaBspType)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void UglyName(uint aVersion, out string aaUglyName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void MacAddress(uint aVersion, out string aaMacAddress)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ProductId(uint aVersion, out string aaProductNumber)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void BoardId(uint aVersion, uint aaIndex, out string aaBoardNumber)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void BoardType(uint aVersion, uint aaIndex, out string aaBoardNumber)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void MaxBoards(uint aVersion, out uint aaMaxBoards)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SoftwareVersion(uint aVersion, out string aaSoftwareVersion)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoReboot(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            self.Reboot(aVersion);
            return 0;
        }

        private static unsafe int DoBootMode(IntPtr aPtr, uint aVersion, char** aaMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aMode;
            self.BootMode(aVersion, out aMode);
            *aaMode = (char*)Marshal.StringToHGlobalAnsi(aMode).ToPointer();
            return 0;
        }

        private static unsafe int DoSetBootMode(IntPtr aPtr, uint aVersion, char* aaMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aMode = Marshal.PtrToStringAnsi((IntPtr)aaMode);
            self.SetBootMode(aVersion, aMode);
            return 0;
        }

        private static unsafe int DoBspType(IntPtr aPtr, uint aVersion, char** aaBspType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aBspType;
            self.BspType(aVersion, out aBspType);
            *aaBspType = (char*)Marshal.StringToHGlobalAnsi(aBspType).ToPointer();
            return 0;
        }

        private static unsafe int DoUglyName(IntPtr aPtr, uint aVersion, char** aaUglyName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aUglyName;
            self.UglyName(aVersion, out aUglyName);
            *aaUglyName = (char*)Marshal.StringToHGlobalAnsi(aUglyName).ToPointer();
            return 0;
        }

        private static unsafe int DoMacAddress(IntPtr aPtr, uint aVersion, char** aaMacAddress)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aMacAddress;
            self.MacAddress(aVersion, out aMacAddress);
            *aaMacAddress = (char*)Marshal.StringToHGlobalAnsi(aMacAddress).ToPointer();
            return 0;
        }

        private static unsafe int DoProductId(IntPtr aPtr, uint aVersion, char** aaProductNumber)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aProductNumber;
            self.ProductId(aVersion, out aProductNumber);
            *aaProductNumber = (char*)Marshal.StringToHGlobalAnsi(aProductNumber).ToPointer();
            return 0;
        }

        private static unsafe int DoBoardId(IntPtr aPtr, uint aVersion, uint aaIndex, char** aaBoardNumber)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aBoardNumber;
            self.BoardId(aVersion, aaIndex, out aBoardNumber);
            *aaBoardNumber = (char*)Marshal.StringToHGlobalAnsi(aBoardNumber).ToPointer();
            return 0;
        }

        private static unsafe int DoBoardType(IntPtr aPtr, uint aVersion, uint aaIndex, char** aaBoardNumber)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aBoardNumber;
            self.BoardType(aVersion, aaIndex, out aBoardNumber);
            *aaBoardNumber = (char*)Marshal.StringToHGlobalAnsi(aBoardNumber).ToPointer();
            return 0;
        }

        private static unsafe int DoMaxBoards(IntPtr aPtr, uint aVersion, uint* aaMaxBoards)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            uint aMaxBoards;
            self.MaxBoards(aVersion, out aMaxBoards);
            *aaMaxBoards = aMaxBoards;
            return 0;
        }

        private static unsafe int DoSoftwareVersion(IntPtr aPtr, uint aVersion, char** aaSoftwareVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceLinnCoUkVolkano1 self = (DvServiceLinnCoUkVolkano1)gch.Target;
            string aSoftwareVersion;
            self.SoftwareVersion(aVersion, out aSoftwareVersion);
            *aaSoftwareVersion = (char*)Marshal.StringToHGlobalAnsi(aSoftwareVersion).ToPointer();
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceLinnCoUkVolkano1()
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
            DvServiceLinnCoUkVolkano1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

