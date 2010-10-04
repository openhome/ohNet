using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkProduct1 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkProduct1")]
        static extern uint CpProxyLinnCoUkProduct1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkProduct1")]
        static extern void CpProxyLinnCoUkProduct1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1SyncRoom(uint aHandle, char** aaRoom);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1BeginRoom(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe int CpProxyLinnCoUkProduct1EndRoom(uint aHandle, uint aAsync, char** aaRoom);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1SyncSetRoom(uint aHandle, char* aaRoom);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1BeginSetRoom(uint aHandle, char* aaRoom, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe int CpProxyLinnCoUkProduct1EndSetRoom(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1SyncStandby(uint aHandle, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1BeginStandby(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe int CpProxyLinnCoUkProduct1EndStandby(uint aHandle, uint aAsync, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1SyncSetStandby(uint aHandle, uint aaStandby);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1BeginSetStandby(uint aHandle, uint aaStandby, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe int CpProxyLinnCoUkProduct1EndSetStandby(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct1")]
        static extern void CpProxyLinnCoUkProduct1SetPropertyRoomChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct1")]
        static extern void CpProxyLinnCoUkProduct1SetPropertyStandbyChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1PropertyRoom(uint aHandle, char** aRoom);
        [DllImport("CpLinnCoUkProduct1")]
        static extern unsafe void CpProxyLinnCoUkProduct1PropertyStandby(uint aHandle, uint* aStandby);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iRoomChanged;
        private CallbackPropertyChanged iStandbyChanged;
        private Callback iCallbackRoomChanged;
        private Callback iCallbackStandbyChanged;

        public CpProxyLinnCoUkProduct1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkProduct1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncRoom(out string aaRoom)
        {
			char* aRoom;
			{
				CpProxyLinnCoUkProduct1SyncRoom(iHandle, &aRoom);
			}
            aaRoom = Marshal.PtrToStringAnsi((IntPtr)aRoom);
            ZappFree(aRoom);
        }

        public unsafe void BeginRoom(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct1BeginRoom(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndRoom(uint aAsyncHandle, out string aaRoom)
        {
			char* aRoom;
			{
				if (0 != CpProxyLinnCoUkProduct1EndRoom(iHandle, aAsyncHandle, &aRoom))
				{
					throw(new ProxyError());
				}
			}
            aaRoom = Marshal.PtrToStringAnsi((IntPtr)aRoom);
            ZappFree(aRoom);
        }

        public unsafe void SyncSetRoom(string aaRoom)
        {
			char* aRoom = (char*)Marshal.StringToHGlobalAnsi(aaRoom);
			{
				CpProxyLinnCoUkProduct1SyncSetRoom(iHandle, aRoom);
			}
			Marshal.FreeHGlobal((IntPtr)aRoom);
        }

        public unsafe void BeginSetRoom(string aaRoom, CallbackAsyncComplete aCallback)
        {
			char* aRoom = (char*)Marshal.StringToHGlobalAnsi(aaRoom);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct1BeginSetRoom(iHandle, aRoom, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aRoom);
        }

        public unsafe void EndSetRoom(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct1EndSetRoom(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStandby(out bool aaStandby)
        {
			uint aStandby;
			{
				CpProxyLinnCoUkProduct1SyncStandby(iHandle, &aStandby);
			}
			aaStandby = (aStandby != 0);
        }

        public unsafe void BeginStandby(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct1BeginStandby(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStandby(uint aAsyncHandle, out bool aaStandby)
        {
			uint aStandby;
			{
				if (0 != CpProxyLinnCoUkProduct1EndStandby(iHandle, aAsyncHandle, &aStandby))
				{
					throw(new ProxyError());
				}
			}
			aaStandby = (aStandby != 0);
        }

        public unsafe void SyncSetStandby(bool aaStandby)
        {
			uint aStandby = (aaStandby? 1u : 0u);
			{
				CpProxyLinnCoUkProduct1SyncSetStandby(iHandle, aStandby);
			}
        }

        public unsafe void BeginSetStandby(bool aaStandby, CallbackAsyncComplete aCallback)
        {
			uint aStandby = (aaStandby? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct1BeginSetStandby(iHandle, aStandby, iActionComplete, ptr);
        }

        public unsafe void EndSetStandby(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct1EndSetStandby(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyRoomChanged(CallbackPropertyChanged aRoomChanged)
        {
            iRoomChanged = aRoomChanged;
            iCallbackRoomChanged = new Callback(PropertyRoomChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct1SetPropertyRoomChanged(iHandle, iCallbackRoomChanged, ptr);
        }

        private void PropertyRoomChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct1 self = (CpProxyLinnCoUkProduct1)gch.Target;
            self.iRoomChanged();
        }

        public void SetPropertyStandbyChanged(CallbackPropertyChanged aStandbyChanged)
        {
            iStandbyChanged = aStandbyChanged;
            iCallbackStandbyChanged = new Callback(PropertyStandbyChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct1SetPropertyStandbyChanged(iHandle, iCallbackStandbyChanged, ptr);
        }

        private void PropertyStandbyChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct1 self = (CpProxyLinnCoUkProduct1)gch.Target;
            self.iStandbyChanged();
        }

        public unsafe void PropertyRoom(out string aRoom)
        {
			char* ptr;
            CpProxyLinnCoUkProduct1PropertyRoom(iHandle, &ptr);
            aRoom = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyStandby(out bool aStandby)
        {
			uint standby;
	        CpProxyLinnCoUkProduct1PropertyStandby(iHandle, &standby);
			aStandby = (standby != 0);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkProduct1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
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
            CpProxyLinnCoUkProduct1Destroy(handle);
            iGch.Free();
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
            else
            {
                DisposeProxy();
            }
        }
    }
}

