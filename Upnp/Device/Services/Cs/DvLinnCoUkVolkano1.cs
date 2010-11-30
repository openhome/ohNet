using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkVolkano1 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Volkano:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkVolkano1 : DvProvider, IDisposable, IDvProviderLinnCoUkVolkano1
    {
        [DllImport("DvLinnCoUkVolkano1")]
        static extern uint DvProviderLinnCoUkVolkano1Create(uint aDeviceHandle);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1Destroy(uint aHandle);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionReboot(uint aHandle, CallbackReboot aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionBootMode(uint aHandle, CallbackBootMode aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionSetBootMode(uint aHandle, CallbackSetBootMode aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionBspType(uint aHandle, CallbackBspType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionUglyName(uint aHandle, CallbackUglyName aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionMacAddress(uint aHandle, CallbackMacAddress aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionProductId(uint aHandle, CallbackProductId aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionBoardId(uint aHandle, CallbackBoardId aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionBoardType(uint aHandle, CallbackBoardType aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionMaxBoards(uint aHandle, CallbackMaxBoards aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkVolkano1")]
        static extern void DvProviderLinnCoUkVolkano1EnableActionSoftwareVersion(uint aHandle, CallbackSoftwareVersion aCallback, IntPtr aPtr);
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkVolkano1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkVolkano1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action Reboot is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoReboot must be overridden if this is called.</remarks>
        protected unsafe void EnableActionReboot()
        {
            iCallbackReboot = new CallbackReboot(DoReboot);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionReboot(iHandle, iCallbackReboot, ptr);
        }

        /// <summary>
        /// Signal that the action BootMode is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBootMode must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBootMode()
        {
            iCallbackBootMode = new CallbackBootMode(DoBootMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionBootMode(iHandle, iCallbackBootMode, ptr);
        }

        /// <summary>
        /// Signal that the action SetBootMode is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetBootMode must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetBootMode()
        {
            iCallbackSetBootMode = new CallbackSetBootMode(DoSetBootMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionSetBootMode(iHandle, iCallbackSetBootMode, ptr);
        }

        /// <summary>
        /// Signal that the action BspType is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBspType must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBspType()
        {
            iCallbackBspType = new CallbackBspType(DoBspType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionBspType(iHandle, iCallbackBspType, ptr);
        }

        /// <summary>
        /// Signal that the action UglyName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoUglyName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionUglyName()
        {
            iCallbackUglyName = new CallbackUglyName(DoUglyName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionUglyName(iHandle, iCallbackUglyName, ptr);
        }

        /// <summary>
        /// Signal that the action MacAddress is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoMacAddress must be overridden if this is called.</remarks>
        protected unsafe void EnableActionMacAddress()
        {
            iCallbackMacAddress = new CallbackMacAddress(DoMacAddress);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionMacAddress(iHandle, iCallbackMacAddress, ptr);
        }

        /// <summary>
        /// Signal that the action ProductId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoProductId must be overridden if this is called.</remarks>
        protected unsafe void EnableActionProductId()
        {
            iCallbackProductId = new CallbackProductId(DoProductId);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionProductId(iHandle, iCallbackProductId, ptr);
        }

        /// <summary>
        /// Signal that the action BoardId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBoardId must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBoardId()
        {
            iCallbackBoardId = new CallbackBoardId(DoBoardId);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionBoardId(iHandle, iCallbackBoardId, ptr);
        }

        /// <summary>
        /// Signal that the action BoardType is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoBoardType must be overridden if this is called.</remarks>
        protected unsafe void EnableActionBoardType()
        {
            iCallbackBoardType = new CallbackBoardType(DoBoardType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionBoardType(iHandle, iCallbackBoardType, ptr);
        }

        /// <summary>
        /// Signal that the action MaxBoards is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoMaxBoards must be overridden if this is called.</remarks>
        protected unsafe void EnableActionMaxBoards()
        {
            iCallbackMaxBoards = new CallbackMaxBoards(DoMaxBoards);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionMaxBoards(iHandle, iCallbackMaxBoards, ptr);
        }

        /// <summary>
        /// Signal that the action SoftwareVersion is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSoftwareVersion must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSoftwareVersion()
        {
            iCallbackSoftwareVersion = new CallbackSoftwareVersion(DoSoftwareVersion);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkVolkano1EnableActionSoftwareVersion(iHandle, iCallbackSoftwareVersion, ptr);
        }

        /// <summary>
        /// Reboot action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Reboot action for the owning device.
        ///
        /// Must be implemented iff EnableActionReboot was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Reboot(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BootMode action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BootMode action for the owning device.
        ///
        /// Must be implemented iff EnableActionBootMode was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMode"></param>
        protected virtual void BootMode(uint aVersion, out string aaMode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBootMode action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBootMode action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBootMode was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMode"></param>
        protected virtual void SetBootMode(uint aVersion, string aaMode)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BspType action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BspType action for the owning device.
        ///
        /// Must be implemented iff EnableActionBspType was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaBspType"></param>
        protected virtual void BspType(uint aVersion, out string aaBspType)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// UglyName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// UglyName action for the owning device.
        ///
        /// Must be implemented iff EnableActionUglyName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUglyName"></param>
        protected virtual void UglyName(uint aVersion, out string aaUglyName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// MacAddress action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// MacAddress action for the owning device.
        ///
        /// Must be implemented iff EnableActionMacAddress was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMacAddress"></param>
        protected virtual void MacAddress(uint aVersion, out string aaMacAddress)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ProductId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ProductId action for the owning device.
        ///
        /// Must be implemented iff EnableActionProductId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaProductNumber"></param>
        protected virtual void ProductId(uint aVersion, out string aaProductNumber)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BoardId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BoardId action for the owning device.
        ///
        /// Must be implemented iff EnableActionBoardId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        /// <param name="aaBoardNumber"></param>
        protected virtual void BoardId(uint aVersion, uint aaIndex, out string aaBoardNumber)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// BoardType action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// BoardType action for the owning device.
        ///
        /// Must be implemented iff EnableActionBoardType was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIndex"></param>
        /// <param name="aaBoardNumber"></param>
        protected virtual void BoardType(uint aVersion, uint aaIndex, out string aaBoardNumber)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// MaxBoards action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// MaxBoards action for the owning device.
        ///
        /// Must be implemented iff EnableActionMaxBoards was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMaxBoards"></param>
        protected virtual void MaxBoards(uint aVersion, out uint aaMaxBoards)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SoftwareVersion action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SoftwareVersion action for the owning device.
        ///
        /// Must be implemented iff EnableActionSoftwareVersion was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSoftwareVersion"></param>
        protected virtual void SoftwareVersion(uint aVersion, out string aaSoftwareVersion)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoReboot(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            self.Reboot(aVersion);
            return 0;
        }

        private static unsafe int DoBootMode(IntPtr aPtr, uint aVersion, char** aaMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aMode;
            self.BootMode(aVersion, out aMode);
            *aaMode = (char*)Marshal.StringToHGlobalAnsi(aMode).ToPointer();
            return 0;
        }

        private static unsafe int DoSetBootMode(IntPtr aPtr, uint aVersion, char* aaMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aMode = Marshal.PtrToStringAnsi((IntPtr)aaMode);
            self.SetBootMode(aVersion, aMode);
            return 0;
        }

        private static unsafe int DoBspType(IntPtr aPtr, uint aVersion, char** aaBspType)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aBspType;
            self.BspType(aVersion, out aBspType);
            *aaBspType = (char*)Marshal.StringToHGlobalAnsi(aBspType).ToPointer();
            return 0;
        }

        private static unsafe int DoUglyName(IntPtr aPtr, uint aVersion, char** aaUglyName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aUglyName;
            self.UglyName(aVersion, out aUglyName);
            *aaUglyName = (char*)Marshal.StringToHGlobalAnsi(aUglyName).ToPointer();
            return 0;
        }

        private static unsafe int DoMacAddress(IntPtr aPtr, uint aVersion, char** aaMacAddress)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aMacAddress;
            self.MacAddress(aVersion, out aMacAddress);
            *aaMacAddress = (char*)Marshal.StringToHGlobalAnsi(aMacAddress).ToPointer();
            return 0;
        }

        private static unsafe int DoProductId(IntPtr aPtr, uint aVersion, char** aaProductNumber)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aProductNumber;
            self.ProductId(aVersion, out aProductNumber);
            *aaProductNumber = (char*)Marshal.StringToHGlobalAnsi(aProductNumber).ToPointer();
            return 0;
        }

        private static unsafe int DoBoardId(IntPtr aPtr, uint aVersion, uint aaIndex, char** aaBoardNumber)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aBoardNumber;
            self.BoardId(aVersion, aaIndex, out aBoardNumber);
            *aaBoardNumber = (char*)Marshal.StringToHGlobalAnsi(aBoardNumber).ToPointer();
            return 0;
        }

        private static unsafe int DoBoardType(IntPtr aPtr, uint aVersion, uint aaIndex, char** aaBoardNumber)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aBoardNumber;
            self.BoardType(aVersion, aaIndex, out aBoardNumber);
            *aaBoardNumber = (char*)Marshal.StringToHGlobalAnsi(aBoardNumber).ToPointer();
            return 0;
        }

        private static unsafe int DoMaxBoards(IntPtr aPtr, uint aVersion, uint* aaMaxBoards)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            uint aMaxBoards;
            self.MaxBoards(aVersion, out aMaxBoards);
            *aaMaxBoards = aMaxBoards;
            return 0;
        }

        private static unsafe int DoSoftwareVersion(IntPtr aPtr, uint aVersion, char** aaSoftwareVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkVolkano1 self = (DvProviderLinnCoUkVolkano1)gch.Target;
            string aSoftwareVersion;
            self.SoftwareVersion(aVersion, out aSoftwareVersion);
            *aaSoftwareVersion = (char*)Marshal.StringToHGlobalAnsi(aSoftwareVersion).ToPointer();
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

        ~DvProviderLinnCoUkVolkano1()
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
            DvProviderLinnCoUkVolkano1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

