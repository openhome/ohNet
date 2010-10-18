using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkProduct3 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkProduct3")]
        static extern IntPtr CpProxyLinnCoUkProduct3Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncType(IntPtr aHandle, char** aaType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginType(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndType(IntPtr aHandle, IntPtr aAsync, char** aaType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncModel(IntPtr aHandle, char** aaModel);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginModel(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndModel(IntPtr aHandle, IntPtr aAsync, char** aaModel);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncName(IntPtr aHandle, char** aaName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginName(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndName(IntPtr aHandle, IntPtr aAsync, char** aaName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetName(IntPtr aHandle, char* aaName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetName(IntPtr aHandle, char* aaName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetName(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncRoom(IntPtr aHandle, char** aaRoom);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginRoom(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndRoom(IntPtr aHandle, IntPtr aAsync, char** aaRoom);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetRoom(IntPtr aHandle, char* aaRoom);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetRoom(IntPtr aHandle, char* aaRoom, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetRoom(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncStandby(IntPtr aHandle, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginStandby(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndStandby(IntPtr aHandle, IntPtr aAsync, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetStandby(IntPtr aHandle, uint aaStandby);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetStandby(IntPtr aHandle, uint aaStandby, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetStandby(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceCount(IntPtr aHandle, uint* aaSourceCount);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceCount(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceCount(IntPtr aHandle, IntPtr aAsync, uint* aaSourceCount);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceXml(IntPtr aHandle, char** aaSourceXml);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceXml(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceXml(IntPtr aHandle, IntPtr aAsync, char** aaSourceXml);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceIndex(IntPtr aHandle, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceIndex(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceIndex(IntPtr aHandle, IntPtr aAsync, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetSourceIndex(IntPtr aHandle, uint aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetSourceIndex(IntPtr aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetSourceIndex(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetSourceIndexByName(IntPtr aHandle, char* aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetSourceIndexByName(IntPtr aHandle, char* aaSourceName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetSourceIndexByName(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndexByName(IntPtr aHandle, char* aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndexByName(IntPtr aHandle, char* aaSourceName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetStartupSourceIndexByName(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncStartupSourceIndex(IntPtr aHandle, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginStartupSourceIndex(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndStartupSourceIndex(IntPtr aHandle, IntPtr aAsync, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndex(IntPtr aHandle, uint aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndex(IntPtr aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetStartupSourceIndex(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncStartupSourceEnabled(IntPtr aHandle, uint* aaStartupSourceEnabled);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginStartupSourceEnabled(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndStartupSourceEnabled(IntPtr aHandle, IntPtr aAsync, uint* aaStartupSourceEnabled);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetStartupSourceEnabled(IntPtr aHandle, uint aaStartupSourceEnabled);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetStartupSourceEnabled(IntPtr aHandle, uint aaStartupSourceEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetStartupSourceEnabled(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceSystemName(IntPtr aHandle, uint aaSourceIndex, char** aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceSystemName(IntPtr aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceSystemName(IntPtr aHandle, IntPtr aAsync, char** aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceName(IntPtr aHandle, uint aaSourceIndex, char** aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceName(IntPtr aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceName(IntPtr aHandle, IntPtr aAsync, char** aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetSourceName(IntPtr aHandle, uint aaSourceIndex, char* aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetSourceName(IntPtr aHandle, uint aaSourceIndex, char* aaSourceName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetSourceName(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceType(IntPtr aHandle, uint aaSourceIndex, char** aaSourceType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceType(IntPtr aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceType(IntPtr aHandle, IntPtr aAsync, char** aaSourceType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceVisible(IntPtr aHandle, uint aaSourceIndex, uint* aaSourceVisible);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceVisible(IntPtr aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceVisible(IntPtr aHandle, IntPtr aAsync, uint* aaSourceVisible);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetSourceVisible(IntPtr aHandle, uint aaSourceIndex, uint aaSourceVisible);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetSourceVisible(IntPtr aHandle, uint aaSourceIndex, uint aaSourceVisible, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetSourceVisible(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductTypeChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductModelChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductNameChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductRoomChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductStandbyChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductSourceIndexChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductSourceCountChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductSourceXmlChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyStartupSourceIndexChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyStartupSourceEnabledChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceNameChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceVisibleChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceTypeChanged(IntPtr aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductType(IntPtr aHandle, char** aProductType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductModel(IntPtr aHandle, char** aProductModel);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductName(IntPtr aHandle, char** aProductName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductRoom(IntPtr aHandle, char** aProductRoom);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductStandby(IntPtr aHandle, uint* aProductStandby);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductSourceIndex(IntPtr aHandle, uint* aProductSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductSourceCount(IntPtr aHandle, uint* aProductSourceCount);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductSourceXml(IntPtr aHandle, char** aProductSourceXml);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyStartupSourceIndex(IntPtr aHandle, uint* aStartupSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyStartupSourceEnabled(IntPtr aHandle, uint* aStartupSourceEnabled);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductAnySourceName(IntPtr aHandle, uint* aProductAnySourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductAnySourceVisible(IntPtr aHandle, uint* aProductAnySourceVisible);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductAnySourceType(IntPtr aHandle, uint* aProductAnySourceType);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iProductTypeChanged;
        private CallbackPropertyChanged iProductModelChanged;
        private CallbackPropertyChanged iProductNameChanged;
        private CallbackPropertyChanged iProductRoomChanged;
        private CallbackPropertyChanged iProductStandbyChanged;
        private CallbackPropertyChanged iProductSourceIndexChanged;
        private CallbackPropertyChanged iProductSourceCountChanged;
        private CallbackPropertyChanged iProductSourceXmlChanged;
        private CallbackPropertyChanged iStartupSourceIndexChanged;
        private CallbackPropertyChanged iStartupSourceEnabledChanged;
        private CallbackPropertyChanged iProductAnySourceNameChanged;
        private CallbackPropertyChanged iProductAnySourceVisibleChanged;
        private CallbackPropertyChanged iProductAnySourceTypeChanged;
        private Callback iCallbackProductTypeChanged;
        private Callback iCallbackProductModelChanged;
        private Callback iCallbackProductNameChanged;
        private Callback iCallbackProductRoomChanged;
        private Callback iCallbackProductStandbyChanged;
        private Callback iCallbackProductSourceIndexChanged;
        private Callback iCallbackProductSourceCountChanged;
        private Callback iCallbackProductSourceXmlChanged;
        private Callback iCallbackStartupSourceIndexChanged;
        private Callback iCallbackStartupSourceEnabledChanged;
        private Callback iCallbackProductAnySourceNameChanged;
        private Callback iCallbackProductAnySourceVisibleChanged;
        private Callback iCallbackProductAnySourceTypeChanged;

        public CpProxyLinnCoUkProduct3(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkProduct3Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncType(out string aaType)
        {
			char* aType;
			{
				CpProxyLinnCoUkProduct3SyncType(iHandle, &aType);
			}
            aaType = Marshal.PtrToStringAnsi((IntPtr)aType);
            ZappFree(aType);
        }

        public unsafe void BeginType(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginType(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndType(IntPtr aAsyncHandle, out string aaType)
        {
			char* aType;
			{
				if (0 != CpProxyLinnCoUkProduct3EndType(iHandle, aAsyncHandle, &aType))
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
				CpProxyLinnCoUkProduct3SyncModel(iHandle, &aModel);
			}
            aaModel = Marshal.PtrToStringAnsi((IntPtr)aModel);
            ZappFree(aModel);
        }

        public unsafe void BeginModel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginModel(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndModel(IntPtr aAsyncHandle, out string aaModel)
        {
			char* aModel;
			{
				if (0 != CpProxyLinnCoUkProduct3EndModel(iHandle, aAsyncHandle, &aModel))
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
				CpProxyLinnCoUkProduct3SyncName(iHandle, &aName);
			}
            aaName = Marshal.PtrToStringAnsi((IntPtr)aName);
            ZappFree(aName);
        }

        public unsafe void BeginName(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginName(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndName(IntPtr aAsyncHandle, out string aaName)
        {
			char* aName;
			{
				if (0 != CpProxyLinnCoUkProduct3EndName(iHandle, aAsyncHandle, &aName))
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
				CpProxyLinnCoUkProduct3SyncSetName(iHandle, aName);
			}
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        public unsafe void BeginSetName(string aaName, CallbackAsyncComplete aCallback)
        {
			char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetName(iHandle, aName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aName);
        }

        public unsafe void EndSetName(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetName(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncRoom(out string aaRoom)
        {
			char* aRoom;
			{
				CpProxyLinnCoUkProduct3SyncRoom(iHandle, &aRoom);
			}
            aaRoom = Marshal.PtrToStringAnsi((IntPtr)aRoom);
            ZappFree(aRoom);
        }

        public unsafe void BeginRoom(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginRoom(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndRoom(IntPtr aAsyncHandle, out string aaRoom)
        {
			char* aRoom;
			{
				if (0 != CpProxyLinnCoUkProduct3EndRoom(iHandle, aAsyncHandle, &aRoom))
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
				CpProxyLinnCoUkProduct3SyncSetRoom(iHandle, aRoom);
			}
			Marshal.FreeHGlobal((IntPtr)aRoom);
        }

        public unsafe void BeginSetRoom(string aaRoom, CallbackAsyncComplete aCallback)
        {
			char* aRoom = (char*)Marshal.StringToHGlobalAnsi(aaRoom);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetRoom(iHandle, aRoom, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aRoom);
        }

        public unsafe void EndSetRoom(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetRoom(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStandby(out bool aaStandby)
        {
			uint aStandby;
			{
				CpProxyLinnCoUkProduct3SyncStandby(iHandle, &aStandby);
			}
			aaStandby = (aStandby != 0);
        }

        public unsafe void BeginStandby(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginStandby(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStandby(IntPtr aAsyncHandle, out bool aaStandby)
        {
			uint aStandby;
			{
				if (0 != CpProxyLinnCoUkProduct3EndStandby(iHandle, aAsyncHandle, &aStandby))
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
				CpProxyLinnCoUkProduct3SyncSetStandby(iHandle, aStandby);
			}
        }

        public unsafe void BeginSetStandby(bool aaStandby, CallbackAsyncComplete aCallback)
        {
			uint aStandby = (aaStandby? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetStandby(iHandle, aStandby, iActionComplete, ptr);
        }

        public unsafe void EndSetStandby(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetStandby(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSourceCount(out uint aaSourceCount)
        {
			fixed (uint* aSourceCount = &aaSourceCount)
			{
				CpProxyLinnCoUkProduct3SyncSourceCount(iHandle, aSourceCount);
			}
        }

        public unsafe void BeginSourceCount(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceCount(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndSourceCount(IntPtr aAsyncHandle, out uint aaSourceCount)
        {
			fixed (uint* aSourceCount = &aaSourceCount)
			{
				if (0 != CpProxyLinnCoUkProduct3EndSourceCount(iHandle, aAsyncHandle, aSourceCount))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSourceXml(out string aaSourceXml)
        {
			char* aSourceXml;
			{
				CpProxyLinnCoUkProduct3SyncSourceXml(iHandle, &aSourceXml);
			}
            aaSourceXml = Marshal.PtrToStringAnsi((IntPtr)aSourceXml);
            ZappFree(aSourceXml);
        }

        public unsafe void BeginSourceXml(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceXml(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndSourceXml(IntPtr aAsyncHandle, out string aaSourceXml)
        {
			char* aSourceXml;
			{
				if (0 != CpProxyLinnCoUkProduct3EndSourceXml(iHandle, aAsyncHandle, &aSourceXml))
				{
					throw(new ProxyError());
				}
			}
            aaSourceXml = Marshal.PtrToStringAnsi((IntPtr)aSourceXml);
            ZappFree(aSourceXml);
        }

        public unsafe void SyncSourceIndex(out uint aaSourceIndex)
        {
			fixed (uint* aSourceIndex = &aaSourceIndex)
			{
				CpProxyLinnCoUkProduct3SyncSourceIndex(iHandle, aSourceIndex);
			}
        }

        public unsafe void BeginSourceIndex(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceIndex(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndSourceIndex(IntPtr aAsyncHandle, out uint aaSourceIndex)
        {
			fixed (uint* aSourceIndex = &aaSourceIndex)
			{
				if (0 != CpProxyLinnCoUkProduct3EndSourceIndex(iHandle, aAsyncHandle, aSourceIndex))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetSourceIndex(uint aaSourceIndex)
        {
			{
				CpProxyLinnCoUkProduct3SyncSetSourceIndex(iHandle, aaSourceIndex);
			}
        }

        public unsafe void BeginSetSourceIndex(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetSourceIndex(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        public unsafe void EndSetSourceIndex(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetSourceIndex(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetSourceIndexByName(string aaSourceName)
        {
			char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
			{
				CpProxyLinnCoUkProduct3SyncSetSourceIndexByName(iHandle, aSourceName);
			}
			Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        public unsafe void BeginSetSourceIndexByName(string aaSourceName, CallbackAsyncComplete aCallback)
        {
			char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetSourceIndexByName(iHandle, aSourceName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        public unsafe void EndSetSourceIndexByName(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetSourceIndexByName(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetStartupSourceIndexByName(string aaSourceName)
        {
			char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
			{
				CpProxyLinnCoUkProduct3SyncSetStartupSourceIndexByName(iHandle, aSourceName);
			}
			Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        public unsafe void BeginSetStartupSourceIndexByName(string aaSourceName, CallbackAsyncComplete aCallback)
        {
			char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetStartupSourceIndexByName(iHandle, aSourceName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        public unsafe void EndSetStartupSourceIndexByName(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetStartupSourceIndexByName(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStartupSourceIndex(out uint aaSourceIndex)
        {
			fixed (uint* aSourceIndex = &aaSourceIndex)
			{
				CpProxyLinnCoUkProduct3SyncStartupSourceIndex(iHandle, aSourceIndex);
			}
        }

        public unsafe void BeginStartupSourceIndex(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginStartupSourceIndex(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStartupSourceIndex(IntPtr aAsyncHandle, out uint aaSourceIndex)
        {
			fixed (uint* aSourceIndex = &aaSourceIndex)
			{
				if (0 != CpProxyLinnCoUkProduct3EndStartupSourceIndex(iHandle, aAsyncHandle, aSourceIndex))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetStartupSourceIndex(uint aaSourceIndex)
        {
			{
				CpProxyLinnCoUkProduct3SyncSetStartupSourceIndex(iHandle, aaSourceIndex);
			}
        }

        public unsafe void BeginSetStartupSourceIndex(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetStartupSourceIndex(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        public unsafe void EndSetStartupSourceIndex(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetStartupSourceIndex(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncStartupSourceEnabled(out bool aaStartupSourceEnabled)
        {
			uint aStartupSourceEnabled;
			{
				CpProxyLinnCoUkProduct3SyncStartupSourceEnabled(iHandle, &aStartupSourceEnabled);
			}
			aaStartupSourceEnabled = (aStartupSourceEnabled != 0);
        }

        public unsafe void BeginStartupSourceEnabled(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginStartupSourceEnabled(iHandle, iActionComplete, ptr);
        }

        public unsafe void EndStartupSourceEnabled(IntPtr aAsyncHandle, out bool aaStartupSourceEnabled)
        {
			uint aStartupSourceEnabled;
			{
				if (0 != CpProxyLinnCoUkProduct3EndStartupSourceEnabled(iHandle, aAsyncHandle, &aStartupSourceEnabled))
				{
					throw(new ProxyError());
				}
			}
			aaStartupSourceEnabled = (aStartupSourceEnabled != 0);
        }

        public unsafe void SyncSetStartupSourceEnabled(bool aaStartupSourceEnabled)
        {
			uint aStartupSourceEnabled = (aaStartupSourceEnabled? 1u : 0u);
			{
				CpProxyLinnCoUkProduct3SyncSetStartupSourceEnabled(iHandle, aStartupSourceEnabled);
			}
        }

        public unsafe void BeginSetStartupSourceEnabled(bool aaStartupSourceEnabled, CallbackAsyncComplete aCallback)
        {
			uint aStartupSourceEnabled = (aaStartupSourceEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetStartupSourceEnabled(iHandle, aStartupSourceEnabled, iActionComplete, ptr);
        }

        public unsafe void EndSetStartupSourceEnabled(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetStartupSourceEnabled(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSourceSystemName(uint aaSourceIndex, out string aaSourceName)
        {
			char* aSourceName;
			{
				CpProxyLinnCoUkProduct3SyncSourceSystemName(iHandle, aaSourceIndex, &aSourceName);
			}
            aaSourceName = Marshal.PtrToStringAnsi((IntPtr)aSourceName);
            ZappFree(aSourceName);
        }

        public unsafe void BeginSourceSystemName(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceSystemName(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        public unsafe void EndSourceSystemName(IntPtr aAsyncHandle, out string aaSourceName)
        {
			char* aSourceName;
			{
				if (0 != CpProxyLinnCoUkProduct3EndSourceSystemName(iHandle, aAsyncHandle, &aSourceName))
				{
					throw(new ProxyError());
				}
			}
            aaSourceName = Marshal.PtrToStringAnsi((IntPtr)aSourceName);
            ZappFree(aSourceName);
        }

        public unsafe void SyncSourceName(uint aaSourceIndex, out string aaSourceName)
        {
			char* aSourceName;
			{
				CpProxyLinnCoUkProduct3SyncSourceName(iHandle, aaSourceIndex, &aSourceName);
			}
            aaSourceName = Marshal.PtrToStringAnsi((IntPtr)aSourceName);
            ZappFree(aSourceName);
        }

        public unsafe void BeginSourceName(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceName(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        public unsafe void EndSourceName(IntPtr aAsyncHandle, out string aaSourceName)
        {
			char* aSourceName;
			{
				if (0 != CpProxyLinnCoUkProduct3EndSourceName(iHandle, aAsyncHandle, &aSourceName))
				{
					throw(new ProxyError());
				}
			}
            aaSourceName = Marshal.PtrToStringAnsi((IntPtr)aSourceName);
            ZappFree(aSourceName);
        }

        public unsafe void SyncSetSourceName(uint aaSourceIndex, string aaSourceName)
        {
			char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
			{
				CpProxyLinnCoUkProduct3SyncSetSourceName(iHandle, aaSourceIndex, aSourceName);
			}
			Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        public unsafe void BeginSetSourceName(uint aaSourceIndex, string aaSourceName, CallbackAsyncComplete aCallback)
        {
			char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetSourceName(iHandle, aaSourceIndex, aSourceName, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        public unsafe void EndSetSourceName(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetSourceName(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSourceType(uint aaSourceIndex, out string aaSourceType)
        {
			char* aSourceType;
			{
				CpProxyLinnCoUkProduct3SyncSourceType(iHandle, aaSourceIndex, &aSourceType);
			}
            aaSourceType = Marshal.PtrToStringAnsi((IntPtr)aSourceType);
            ZappFree(aSourceType);
        }

        public unsafe void BeginSourceType(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceType(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        public unsafe void EndSourceType(IntPtr aAsyncHandle, out string aaSourceType)
        {
			char* aSourceType;
			{
				if (0 != CpProxyLinnCoUkProduct3EndSourceType(iHandle, aAsyncHandle, &aSourceType))
				{
					throw(new ProxyError());
				}
			}
            aaSourceType = Marshal.PtrToStringAnsi((IntPtr)aSourceType);
            ZappFree(aSourceType);
        }

        public unsafe void SyncSourceVisible(uint aaSourceIndex, out bool aaSourceVisible)
        {
			uint aSourceVisible;
			{
				CpProxyLinnCoUkProduct3SyncSourceVisible(iHandle, aaSourceIndex, &aSourceVisible);
			}
			aaSourceVisible = (aSourceVisible != 0);
        }

        public unsafe void BeginSourceVisible(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceVisible(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        public unsafe void EndSourceVisible(IntPtr aAsyncHandle, out bool aaSourceVisible)
        {
			uint aSourceVisible;
			{
				if (0 != CpProxyLinnCoUkProduct3EndSourceVisible(iHandle, aAsyncHandle, &aSourceVisible))
				{
					throw(new ProxyError());
				}
			}
			aaSourceVisible = (aSourceVisible != 0);
        }

        public unsafe void SyncSetSourceVisible(uint aaSourceIndex, bool aaSourceVisible)
        {
			uint aSourceVisible = (aaSourceVisible? 1u : 0u);
			{
				CpProxyLinnCoUkProduct3SyncSetSourceVisible(iHandle, aaSourceIndex, aSourceVisible);
			}
        }

        public unsafe void BeginSetSourceVisible(uint aaSourceIndex, bool aaSourceVisible, CallbackAsyncComplete aCallback)
        {
			uint aSourceVisible = (aaSourceVisible? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetSourceVisible(iHandle, aaSourceIndex, aSourceVisible, iActionComplete, ptr);
        }

        public unsafe void EndSetSourceVisible(IntPtr aAsyncHandle)
        {
			{
				if (0 != CpProxyLinnCoUkProduct3EndSetSourceVisible(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public void SetPropertyProductTypeChanged(CallbackPropertyChanged aProductTypeChanged)
        {
            iProductTypeChanged = aProductTypeChanged;
            iCallbackProductTypeChanged = new Callback(PropertyProductTypeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductTypeChanged(iHandle, iCallbackProductTypeChanged, ptr);
        }

        private void PropertyProductTypeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductTypeChanged();
        }

        public void SetPropertyProductModelChanged(CallbackPropertyChanged aProductModelChanged)
        {
            iProductModelChanged = aProductModelChanged;
            iCallbackProductModelChanged = new Callback(PropertyProductModelChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductModelChanged(iHandle, iCallbackProductModelChanged, ptr);
        }

        private void PropertyProductModelChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductModelChanged();
        }

        public void SetPropertyProductNameChanged(CallbackPropertyChanged aProductNameChanged)
        {
            iProductNameChanged = aProductNameChanged;
            iCallbackProductNameChanged = new Callback(PropertyProductNameChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductNameChanged(iHandle, iCallbackProductNameChanged, ptr);
        }

        private void PropertyProductNameChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductNameChanged();
        }

        public void SetPropertyProductRoomChanged(CallbackPropertyChanged aProductRoomChanged)
        {
            iProductRoomChanged = aProductRoomChanged;
            iCallbackProductRoomChanged = new Callback(PropertyProductRoomChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductRoomChanged(iHandle, iCallbackProductRoomChanged, ptr);
        }

        private void PropertyProductRoomChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductRoomChanged();
        }

        public void SetPropertyProductStandbyChanged(CallbackPropertyChanged aProductStandbyChanged)
        {
            iProductStandbyChanged = aProductStandbyChanged;
            iCallbackProductStandbyChanged = new Callback(PropertyProductStandbyChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductStandbyChanged(iHandle, iCallbackProductStandbyChanged, ptr);
        }

        private void PropertyProductStandbyChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductStandbyChanged();
        }

        public void SetPropertyProductSourceIndexChanged(CallbackPropertyChanged aProductSourceIndexChanged)
        {
            iProductSourceIndexChanged = aProductSourceIndexChanged;
            iCallbackProductSourceIndexChanged = new Callback(PropertyProductSourceIndexChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductSourceIndexChanged(iHandle, iCallbackProductSourceIndexChanged, ptr);
        }

        private void PropertyProductSourceIndexChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductSourceIndexChanged();
        }

        public void SetPropertyProductSourceCountChanged(CallbackPropertyChanged aProductSourceCountChanged)
        {
            iProductSourceCountChanged = aProductSourceCountChanged;
            iCallbackProductSourceCountChanged = new Callback(PropertyProductSourceCountChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductSourceCountChanged(iHandle, iCallbackProductSourceCountChanged, ptr);
        }

        private void PropertyProductSourceCountChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductSourceCountChanged();
        }

        public void SetPropertyProductSourceXmlChanged(CallbackPropertyChanged aProductSourceXmlChanged)
        {
            iProductSourceXmlChanged = aProductSourceXmlChanged;
            iCallbackProductSourceXmlChanged = new Callback(PropertyProductSourceXmlChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductSourceXmlChanged(iHandle, iCallbackProductSourceXmlChanged, ptr);
        }

        private void PropertyProductSourceXmlChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductSourceXmlChanged();
        }

        public void SetPropertyStartupSourceIndexChanged(CallbackPropertyChanged aStartupSourceIndexChanged)
        {
            iStartupSourceIndexChanged = aStartupSourceIndexChanged;
            iCallbackStartupSourceIndexChanged = new Callback(PropertyStartupSourceIndexChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyStartupSourceIndexChanged(iHandle, iCallbackStartupSourceIndexChanged, ptr);
        }

        private void PropertyStartupSourceIndexChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iStartupSourceIndexChanged();
        }

        public void SetPropertyStartupSourceEnabledChanged(CallbackPropertyChanged aStartupSourceEnabledChanged)
        {
            iStartupSourceEnabledChanged = aStartupSourceEnabledChanged;
            iCallbackStartupSourceEnabledChanged = new Callback(PropertyStartupSourceEnabledChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyStartupSourceEnabledChanged(iHandle, iCallbackStartupSourceEnabledChanged, ptr);
        }

        private void PropertyStartupSourceEnabledChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iStartupSourceEnabledChanged();
        }

        public void SetPropertyProductAnySourceNameChanged(CallbackPropertyChanged aProductAnySourceNameChanged)
        {
            iProductAnySourceNameChanged = aProductAnySourceNameChanged;
            iCallbackProductAnySourceNameChanged = new Callback(PropertyProductAnySourceNameChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductAnySourceNameChanged(iHandle, iCallbackProductAnySourceNameChanged, ptr);
        }

        private void PropertyProductAnySourceNameChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductAnySourceNameChanged();
        }

        public void SetPropertyProductAnySourceVisibleChanged(CallbackPropertyChanged aProductAnySourceVisibleChanged)
        {
            iProductAnySourceVisibleChanged = aProductAnySourceVisibleChanged;
            iCallbackProductAnySourceVisibleChanged = new Callback(PropertyProductAnySourceVisibleChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductAnySourceVisibleChanged(iHandle, iCallbackProductAnySourceVisibleChanged, ptr);
        }

        private void PropertyProductAnySourceVisibleChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductAnySourceVisibleChanged();
        }

        public void SetPropertyProductAnySourceTypeChanged(CallbackPropertyChanged aProductAnySourceTypeChanged)
        {
            iProductAnySourceTypeChanged = aProductAnySourceTypeChanged;
            iCallbackProductAnySourceTypeChanged = new Callback(PropertyProductAnySourceTypeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkProduct3SetPropertyProductAnySourceTypeChanged(iHandle, iCallbackProductAnySourceTypeChanged, ptr);
        }

        private void PropertyProductAnySourceTypeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkProduct3 self = (CpProxyLinnCoUkProduct3)gch.Target;
            self.iProductAnySourceTypeChanged();
        }

        public unsafe void PropertyProductType(out string aProductType)
        {
			char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductType(iHandle, &ptr);
            aProductType = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyProductModel(out string aProductModel)
        {
			char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductModel(iHandle, &ptr);
            aProductModel = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyProductName(out string aProductName)
        {
			char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductName(iHandle, &ptr);
            aProductName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyProductRoom(out string aProductRoom)
        {
			char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductRoom(iHandle, &ptr);
            aProductRoom = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyProductStandby(out bool aProductStandby)
        {
			uint productStandby;
	        CpProxyLinnCoUkProduct3PropertyProductStandby(iHandle, &productStandby);
			aProductStandby = (productStandby != 0);
        }

        public unsafe void PropertyProductSourceIndex(out uint aProductSourceIndex)
        {
			fixed (uint* productSourceIndex = &aProductSourceIndex)
			{
	            CpProxyLinnCoUkProduct3PropertyProductSourceIndex(iHandle, productSourceIndex);
			}
        }

        public unsafe void PropertyProductSourceCount(out uint aProductSourceCount)
        {
			fixed (uint* productSourceCount = &aProductSourceCount)
			{
	            CpProxyLinnCoUkProduct3PropertyProductSourceCount(iHandle, productSourceCount);
			}
        }

        public unsafe void PropertyProductSourceXml(out string aProductSourceXml)
        {
			char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductSourceXml(iHandle, &ptr);
            aProductSourceXml = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public unsafe void PropertyStartupSourceIndex(out uint aStartupSourceIndex)
        {
			fixed (uint* startupSourceIndex = &aStartupSourceIndex)
			{
	            CpProxyLinnCoUkProduct3PropertyStartupSourceIndex(iHandle, startupSourceIndex);
			}
        }

        public unsafe void PropertyStartupSourceEnabled(out bool aStartupSourceEnabled)
        {
			uint startupSourceEnabled;
	        CpProxyLinnCoUkProduct3PropertyStartupSourceEnabled(iHandle, &startupSourceEnabled);
			aStartupSourceEnabled = (startupSourceEnabled != 0);
        }

        public unsafe void PropertyProductAnySourceName(out uint aProductAnySourceName)
        {
			fixed (uint* productAnySourceName = &aProductAnySourceName)
			{
	            CpProxyLinnCoUkProduct3PropertyProductAnySourceName(iHandle, productAnySourceName);
			}
        }

        public unsafe void PropertyProductAnySourceVisible(out uint aProductAnySourceVisible)
        {
			fixed (uint* productAnySourceVisible = &aProductAnySourceVisible)
			{
	            CpProxyLinnCoUkProduct3PropertyProductAnySourceVisible(iHandle, productAnySourceVisible);
			}
        }

        public unsafe void PropertyProductAnySourceType(out uint aProductAnySourceType)
        {
			fixed (uint* productAnySourceType = &aProductAnySourceType)
			{
	            CpProxyLinnCoUkProduct3PropertyProductAnySourceType(iHandle, productAnySourceType);
			}
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkProduct3()
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
            CpProxyLinnCoUkProduct3Destroy(handle);
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

