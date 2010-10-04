using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkProduct2 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkProduct2")]
        static extern uint CpProxyLinnCoUkProduct2Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2Destroy(uint aHandle);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncType(uint aHandle, char** aaType);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginType(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndType(uint aHandle, uint aAsync, char** aaType);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncModel(uint aHandle, char** aaModel);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginModel(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndModel(uint aHandle, uint aAsync, char** aaModel);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncName(uint aHandle, char** aaName);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginName(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndName(uint aHandle, uint aAsync, char** aaName);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSetName(uint aHandle, char* aaName);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSetName(uint aHandle, char* aaName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSetName(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncRoom(uint aHandle, char** aaRoom);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginRoom(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndRoom(uint aHandle, uint aAsync, char** aaRoom);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSetRoom(uint aHandle, char* aaRoom);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSetRoom(uint aHandle, char* aaRoom, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSetRoom(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncStandby(uint aHandle, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginStandby(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndStandby(uint aHandle, uint aAsync, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSetStandby(uint aHandle, uint aaStandby);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSetStandby(uint aHandle, uint aaStandby, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSetStandby(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSourceCount(uint aHandle, uint* aaSourceCount);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSourceCount(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSourceCount(uint aHandle, uint aAsync, uint* aaSourceCount);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSourceIndex(uint aHandle, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSourceIndex(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSourceIndex(uint aHandle, uint aAsync, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSetSourceIndex(uint aHandle, uint aaSourceIndex);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSetSourceIndex(uint aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSetSourceIndex(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSourceType(uint aHandle, uint aaSourceIndex, char** aaSourceType);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSourceType(uint aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSourceType(uint aHandle, uint aAsync, char** aaSourceType);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2SetPropertyProductNameChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2SetPropertyProductRoomChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2SetPropertyProductStandbyChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2SetPropertyProductSourceIndexChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2PropertyProductName(uint aHandle, char** aProductName);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2PropertyProductRoom(uint aHandle, char** aProductRoom);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2PropertyProductStandby(uint aHandle, uint* aProductStandby);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2PropertyProductSourceIndex(uint aHandle, uint* aProductSourceIndex);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iProductNameChanged;
        private CallbackPropertyChanged iProductRoomChanged;
        private CallbackPropertyChanged iProductStandbyChanged;
        private CallbackPropertyChanged iProductSourceIndexChanged;
        private Callback iCallbackProductNameChanged;
        private Callback iCallbackProductRoomChanged;
        private Callback iCallbackProductStandbyChanged;
        private Callback iCallbackProductSourceIndexChanged;

        public CpProxyLinnCoUkProduct2(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkProduct2Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncType(out string aaType)
        {
			char* aType;
			{
				CpProxyLinnCoUkProduct2SyncType(iHandle, &aType);
			}
            aaType = Marshal.PtrToStringAnsi((IntPtr)aType);
            ZappFree(aType);
        }

        public unsafe void BeginType(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginType(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndType(uint aAsyncHandle, out string aaType)
        {
			char* aType;
			{
				if (0 != CpProxyLinnCoUkProduct2EndType(iHandle, aAsyncHandle, &aType))
				{
					throw(new ProxyError());
				}
			}
            aaType = Marshal.PtrToStringAnsi((IntPtr)aType);
            ZappFree(aType);
        }

        public unsafe void SyncModel(out string aaModel)
        {
			char* aModel;
			{
				CpProxyLinnCoUkProduct2SyncModel(iHandle, &aModel);
			}
            aaModel = Marshal.PtrToStringAnsi((IntPtr)aModel);
            ZappFree(aModel);
        }

        public unsafe void BeginModel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginModel(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndModel(uint aAsyncHandle, out string aaModel)
        {
			char* aModel;
			{
				if (0 != CpProxyLinnCoUkProduct2EndModel(iHandle, aAsyncHandle, &aModel))
				{
					throw(new ProxyError());
				}
			}
            aaModel = Marshal.PtrToStringAnsi((IntPtr)aModel);
            ZappFree(aModel);
        }

        public unsafe void SyncName(out string aaName)
        {
			char* aName;
			{
				CpProxyLinnCoUkProduct2SyncName(iHandle, &aName);
			}
            aaName = Marshal.PtrToStringAnsi((IntPtr)aName);
            ZappFree(aName);
        }

        public unsafe void BeginName(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginName(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndName(uint aAsyncHandle, out string aaName)
        {
			char* aName;
			{
				if (0 != CpProxyLinnCoUkProduct2EndName(iHandle, aAsyncHandle, &aName))
				{
					throw(new ProxyError());
				}
			}
            aaName = Marshal.PtrToStringAnsi((IntPtr)aName);
            ZappFree(aName);
        }

        public unsafe void SyncSetName(string aaName)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
			{
				CpProxyLinnCoUkProduct2SyncSetName(iHandle, aName);
			}
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        public unsafe void BeginSetName(string aaName, CallbackAsyncComplete aCallback)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginSetName(iHandle, aName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        public unsafe void EndSetName(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct2EndSetName(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncRoom(out string aaRoom)
        {
			char* aRoom;
			{
				CpProxyLinnCoUkProduct2SyncRoom(iHandle, &aRoom);
			}
            aaRoom = Marshal.PtrToStringAnsi((IntPtr)aRoom);
            ZappFree(aRoom);
        }

        public unsafe void BeginRoom(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginRoom(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndRoom(uint aAsyncHandle, out string aaRoom)
        {
			char* aRoom;
			{
				if (0 != CpProxyLinnCoUkProduct2EndRoom(iHandle, aAsyncHandle, &aRoom))
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
				CpProxyLinnCoUkProduct2SyncSetRoom(iHandle, aRoom);
			}
			Marshal.FreeHGlobal((IntPtr)aRoom);
        }

        public unsafe void BeginSetRoom(string aaRoom, CallbackAsyncComplete aCallback)
        {
			char* aRoom = (char*)Marshal.StringToHGlobalAnsi(aaRoom);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginSetRoom(iHandle, aRoom, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aRoom);
        }

        public unsafe void EndSetRoom(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct2EndSetRoom(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStandby(out bool aaStandby)
        {
			uint aStandby;
			{
				CpProxyLinnCoUkProduct2SyncStandby(iHandle, &aStandby);
			}
			aaStandby = (aStandby != 0);
        }

        public unsafe void BeginStandby(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginStandby(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStandby(uint aAsyncHandle, out bool aaStandby)
        {
			uint aStandby;
			{
				if (0 != CpProxyLinnCoUkProduct2EndStandby(iHandle, aAsyncHandle, &aStandby))
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
				CpProxyLinnCoUkProduct2SyncSetStandby(iHandle, aStandby);
			}
        }

        public unsafe void BeginSetStandby(bool aaStandby, CallbackAsyncComplete aCallback)
        {
			uint aStandby = (aaStandby? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginSetStandby(iHandle, aStandby, iActionComplete, ptr);
        }

        public unsafe void EndSetStandby(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct2EndSetStandby(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSourceCount(out uint aaSourceCount)
        {
			fixed (uint* aSourceCount = &aaSourceCount)
			{
				CpProxyLinnCoUkProduct2SyncSourceCount(iHandle, aSourceCount);
			}
        }

        public unsafe void BeginSourceCount(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginSourceCount(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndSourceCount(uint aAsyncHandle, out uint aaSourceCount)
        {
			fixed (uint* aSourceCount = &aaSourceCount)
			{
				if (0 != CpProxyLinnCoUkProduct2EndSourceCount(iHandle, aAsyncHandle, aSourceCount))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSourceIndex(out uint aaSourceIndex)
        {
			fixed (uint* aSourceIndex = &aaSourceIndex)
			{
				CpProxyLinnCoUkProduct2SyncSourceIndex(iHandle, aSourceIndex);
			}
        }

        public unsafe void BeginSourceIndex(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginSourceIndex(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndSourceIndex(uint aAsyncHandle, out uint aaSourceIndex)
        {
			fixed (uint* aSourceIndex = &aaSourceIndex)
			{
				if (0 != CpProxyLinnCoUkProduct2EndSourceIndex(iHandle, aAsyncHandle, aSourceIndex))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetSourceIndex(uint aaSourceIndex)
        {
			{
				CpProxyLinnCoUkProduct2SyncSetSourceIndex(iHandle, aaSourceIndex);
			}
        }

        public unsafe void BeginSetSourceIndex(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginSetSourceIndex(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        public unsafe void EndSetSourceIndex(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct2EndSetSourceIndex(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSourceType(uint aaSourceIndex, out string aaSourceType)
        {
			char* aSourceType;
			{
				CpProxyLinnCoUkProduct2SyncSourceType(iHandle, aaSourceIndex, &aSourceType);
			}
            aaSourceType = Marshal.PtrToStringAnsi((IntPtr)aSourceType);
            ZappFree(aSourceType);
        }

        public unsafe void BeginSourceType(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct2BeginSourceType(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        public unsafe void EndSourceType(uint aAsyncHandle, out string aaSourceType)
        {
			char* aSourceType;
			{
				if (0 != CpProxyLinnCoUkProduct2EndSourceType(iHandle, aAsyncHandle, &aSourceType))
				{
					throw(new ProxyError());
				}
			}
            aaSourceType = Marshal.PtrToStringAnsi((IntPtr)aSourceType);
            ZappFree(aSourceType);
        }

        public void SetPropertyProductNameChanged(CallbackPropertyChanged aProductNameChanged)
        {
            iProductNameChanged = aProductNameChanged;
            iCallbackProductNameChanged = new Callback(PropertyProductNameChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct2SetPropertyProductNameChanged(iHandle, iCallbackProductNameChanged, ptr);
        }

        private void PropertyProductNameChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct2 self = (CpProxyLinnCoUkProduct2)gch.Target;
            self.iProductNameChanged();
        }

        public void SetPropertyProductRoomChanged(CallbackPropertyChanged aProductRoomChanged)
        {
            iProductRoomChanged = aProductRoomChanged;
            iCallbackProductRoomChanged = new Callback(PropertyProductRoomChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct2SetPropertyProductRoomChanged(iHandle, iCallbackProductRoomChanged, ptr);
        }

        private void PropertyProductRoomChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct2 self = (CpProxyLinnCoUkProduct2)gch.Target;
            self.iProductRoomChanged();
        }

        public void SetPropertyProductStandbyChanged(CallbackPropertyChanged aProductStandbyChanged)
        {
            iProductStandbyChanged = aProductStandbyChanged;
            iCallbackProductStandbyChanged = new Callback(PropertyProductStandbyChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct2SetPropertyProductStandbyChanged(iHandle, iCallbackProductStandbyChanged, ptr);
        }

        private void PropertyProductStandbyChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct2 self = (CpProxyLinnCoUkProduct2)gch.Target;
            self.iProductStandbyChanged();
        }

        public void SetPropertyProductSourceIndexChanged(CallbackPropertyChanged aProductSourceIndexChanged)
        {
            iProductSourceIndexChanged = aProductSourceIndexChanged;
            iCallbackProductSourceIndexChanged = new Callback(PropertyProductSourceIndexChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct2SetPropertyProductSourceIndexChanged(iHandle, iCallbackProductSourceIndexChanged, ptr);
        }

        private void PropertyProductSourceIndexChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct2 self = (CpProxyLinnCoUkProduct2)gch.Target;
            self.iProductSourceIndexChanged();
        }

        public unsafe void PropertyProductName(out string aProductName)
        {
			char* ptr;
            CpProxyLinnCoUkProduct2PropertyProductName(iHandle, &ptr);
            aProductName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyProductRoom(out string aProductRoom)
        {
			char* ptr;
            CpProxyLinnCoUkProduct2PropertyProductRoom(iHandle, &ptr);
            aProductRoom = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyProductStandby(out bool aProductStandby)
        {
			uint productStandby;
	        CpProxyLinnCoUkProduct2PropertyProductStandby(iHandle, &productStandby);
			aProductStandby = (productStandby != 0);
        }

        public unsafe void PropertyProductSourceIndex(out uint aProductSourceIndex)
        {
			fixed (uint* productSourceIndex = &aProductSourceIndex)
			{
	            CpProxyLinnCoUkProduct2PropertyProductSourceIndex(iHandle, productSourceIndex);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkProduct2()
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
            CpProxyLinnCoUkProduct2Destroy(handle);
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

