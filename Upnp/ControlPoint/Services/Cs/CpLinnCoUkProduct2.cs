using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkProduct2 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkProduct2")]
        static extern IntPtr CpProxyLinnCoUkProduct2Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncType(IntPtr aHandle, char** aaType);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginType(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndType(IntPtr aHandle, IntPtr aAsync, char** aaType);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncModel(IntPtr aHandle, char** aaModel);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginModel(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndModel(IntPtr aHandle, IntPtr aAsync, char** aaModel);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncName(IntPtr aHandle, char** aaName);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginName(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndName(IntPtr aHandle, IntPtr aAsync, char** aaName);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSetName(IntPtr aHandle, char* aaName);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSetName(IntPtr aHandle, char* aaName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSetName(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncRoom(IntPtr aHandle, char** aaRoom);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginRoom(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndRoom(IntPtr aHandle, IntPtr aAsync, char** aaRoom);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSetRoom(IntPtr aHandle, char* aaRoom);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSetRoom(IntPtr aHandle, char* aaRoom, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSetRoom(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncStandby(IntPtr aHandle, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginStandby(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndStandby(IntPtr aHandle, IntPtr aAsync, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSetStandby(IntPtr aHandle, uint aaStandby);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSetStandby(IntPtr aHandle, uint aaStandby, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSetStandby(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSourceCount(IntPtr aHandle, uint* aaSourceCount);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSourceCount(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSourceCount(IntPtr aHandle, IntPtr aAsync, uint* aaSourceCount);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSourceIndex(IntPtr aHandle, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSourceIndex(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSourceIndex(IntPtr aHandle, IntPtr aAsync, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSetSourceIndex(IntPtr aHandle, uint aaSourceIndex);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSetSourceIndex(IntPtr aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSetSourceIndex(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2SyncSourceType(IntPtr aHandle, uint aaSourceIndex, char** aaSourceType);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2BeginSourceType(IntPtr aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe int CpProxyLinnCoUkProduct2EndSourceType(IntPtr aHandle, IntPtr aAsync, char** aaSourceType);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2SetPropertyProductNameChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2SetPropertyProductRoomChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2SetPropertyProductStandbyChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern void CpProxyLinnCoUkProduct2SetPropertyProductSourceIndexChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2PropertyProductName(IntPtr aHandle, char** aProductName);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2PropertyProductRoom(IntPtr aHandle, char** aProductRoom);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2PropertyProductStandby(IntPtr aHandle, uint* aProductStandby);
        [DllImport("CpLinnCoUkProduct2")]
        static extern unsafe void CpProxyLinnCoUkProduct2PropertyProductSourceIndex(IntPtr aHandle, uint* aProductSourceIndex);
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

        public unsafe void EndType(IntPtr aAsyncHandle, out string aaType)
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

        public unsafe void EndModel(IntPtr aAsyncHandle, out string aaModel)
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

        public unsafe void EndName(IntPtr aAsyncHandle, out string aaName)
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

        public unsafe void EndSetName(IntPtr aAsyncHandle)
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

        public unsafe void EndRoom(IntPtr aAsyncHandle, out string aaRoom)
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

        public unsafe void EndSetRoom(IntPtr aAsyncHandle)
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

        public unsafe void EndStandby(IntPtr aAsyncHandle, out bool aaStandby)
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

        public unsafe void EndSetStandby(IntPtr aAsyncHandle)
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

        public unsafe void EndSourceCount(IntPtr aAsyncHandle, out uint aaSourceCount)
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

        public unsafe void EndSourceIndex(IntPtr aAsyncHandle, out uint aaSourceIndex)
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

        public unsafe void EndSetSourceIndex(IntPtr aAsyncHandle)
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

        public unsafe void EndSourceType(IntPtr aAsyncHandle, out string aaSourceType)
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
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
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

