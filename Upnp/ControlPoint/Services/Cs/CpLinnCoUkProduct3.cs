using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyLinnCoUkProduct3 : CpProxy, IDisposable
    {
        [DllImport("CpLinnCoUkProduct3")]
        static extern uint CpProxyLinnCoUkProduct3Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3Destroy(uint aHandle);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncType(uint aHandle, char** aaType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginType(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndType(uint aHandle, uint aAsync, char** aaType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncModel(uint aHandle, char** aaModel);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginModel(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndModel(uint aHandle, uint aAsync, char** aaModel);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncName(uint aHandle, char** aaName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginName(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndName(uint aHandle, uint aAsync, char** aaName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetName(uint aHandle, char* aaName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetName(uint aHandle, char* aaName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetName(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncRoom(uint aHandle, char** aaRoom);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginRoom(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndRoom(uint aHandle, uint aAsync, char** aaRoom);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetRoom(uint aHandle, char* aaRoom);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetRoom(uint aHandle, char* aaRoom, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetRoom(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncStandby(uint aHandle, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginStandby(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndStandby(uint aHandle, uint aAsync, uint* aaStandby);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetStandby(uint aHandle, uint aaStandby);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetStandby(uint aHandle, uint aaStandby, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetStandby(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceCount(uint aHandle, uint* aaSourceCount);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceCount(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceCount(uint aHandle, uint aAsync, uint* aaSourceCount);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceXml(uint aHandle, char** aaSourceXml);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceXml(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceXml(uint aHandle, uint aAsync, char** aaSourceXml);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceIndex(uint aHandle, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceIndex(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceIndex(uint aHandle, uint aAsync, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetSourceIndex(uint aHandle, uint aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetSourceIndex(uint aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetSourceIndex(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetSourceIndexByName(uint aHandle, char* aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetSourceIndexByName(uint aHandle, char* aaSourceName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetSourceIndexByName(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndexByName(uint aHandle, char* aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndexByName(uint aHandle, char* aaSourceName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetStartupSourceIndexByName(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncStartupSourceIndex(uint aHandle, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginStartupSourceIndex(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndStartupSourceIndex(uint aHandle, uint aAsync, uint* aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetStartupSourceIndex(uint aHandle, uint aaSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetStartupSourceIndex(uint aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetStartupSourceIndex(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncStartupSourceEnabled(uint aHandle, uint* aaStartupSourceEnabled);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginStartupSourceEnabled(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndStartupSourceEnabled(uint aHandle, uint aAsync, uint* aaStartupSourceEnabled);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetStartupSourceEnabled(uint aHandle, uint aaStartupSourceEnabled);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetStartupSourceEnabled(uint aHandle, uint aaStartupSourceEnabled, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetStartupSourceEnabled(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceSystemName(uint aHandle, uint aaSourceIndex, char** aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceSystemName(uint aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceSystemName(uint aHandle, uint aAsync, char** aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceName(uint aHandle, uint aaSourceIndex, char** aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceName(uint aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceName(uint aHandle, uint aAsync, char** aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetSourceName(uint aHandle, uint aaSourceIndex, char* aaSourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetSourceName(uint aHandle, uint aaSourceIndex, char* aaSourceName, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetSourceName(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceType(uint aHandle, uint aaSourceIndex, char** aaSourceType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceType(uint aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceType(uint aHandle, uint aAsync, char** aaSourceType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSourceVisible(uint aHandle, uint aaSourceIndex, uint* aaSourceVisible);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSourceVisible(uint aHandle, uint aaSourceIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSourceVisible(uint aHandle, uint aAsync, uint* aaSourceVisible);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3SyncSetSourceVisible(uint aHandle, uint aaSourceIndex, uint aaSourceVisible);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3BeginSetSourceVisible(uint aHandle, uint aaSourceIndex, uint aaSourceVisible, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe int CpProxyLinnCoUkProduct3EndSetSourceVisible(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductTypeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductModelChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductNameChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductRoomChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductStandbyChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductSourceIndexChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductSourceCountChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductSourceXmlChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyStartupSourceIndexChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyStartupSourceEnabledChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceNameChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceVisibleChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern void CpProxyLinnCoUkProduct3SetPropertyProductAnySourceTypeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductType(uint aHandle, char** aProductType);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductModel(uint aHandle, char** aProductModel);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductName(uint aHandle, char** aProductName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductRoom(uint aHandle, char** aProductRoom);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductStandby(uint aHandle, uint* aProductStandby);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductSourceIndex(uint aHandle, uint* aProductSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductSourceCount(uint aHandle, uint* aProductSourceCount);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductSourceXml(uint aHandle, char** aProductSourceXml);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyStartupSourceIndex(uint aHandle, uint* aStartupSourceIndex);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyStartupSourceEnabled(uint aHandle, uint* aStartupSourceEnabled);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductAnySourceName(uint aHandle, uint* aProductAnySourceName);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductAnySourceVisible(uint aHandle, uint* aProductAnySourceVisible);
        [DllImport("CpLinnCoUkProduct3")]
        static extern unsafe void CpProxyLinnCoUkProduct3PropertyProductAnySourceType(uint aHandle, uint* aProductAnySourceType);
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

        public unsafe void EndType(uint aAsyncHandle, out string aaType)
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

        public unsafe void EndModel(uint aAsyncHandle, out string aaModel)
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

        public unsafe void EndName(uint aAsyncHandle, out string aaName)
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

        public unsafe void EndSetName(uint aAsyncHandle)
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

        public unsafe void EndRoom(uint aAsyncHandle, out string aaRoom)
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

        public unsafe void EndSetRoom(uint aAsyncHandle)
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

        public unsafe void EndStandby(uint aAsyncHandle, out bool aaStandby)
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

        public unsafe void EndSetStandby(uint aAsyncHandle)
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

        public unsafe void EndSourceCount(uint aAsyncHandle, out uint aaSourceCount)
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

        public unsafe void EndSourceXml(uint aAsyncHandle, out string aaSourceXml)
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

        public unsafe void EndSourceIndex(uint aAsyncHandle, out uint aaSourceIndex)
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

        public unsafe void EndSetSourceIndex(uint aAsyncHandle)
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

        public unsafe void EndSetSourceIndexByName(uint aAsyncHandle)
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

        public unsafe void EndSetStartupSourceIndexByName(uint aAsyncHandle)
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

        public unsafe void EndStartupSourceIndex(uint aAsyncHandle, out uint aaSourceIndex)
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

        public unsafe void EndSetStartupSourceIndex(uint aAsyncHandle)
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

        public unsafe void EndStartupSourceEnabled(uint aAsyncHandle, out bool aaStartupSourceEnabled)
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

        public unsafe void EndSetStartupSourceEnabled(uint aAsyncHandle)
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

        public unsafe void EndSourceSystemName(uint aAsyncHandle, out string aaSourceName)
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

        public unsafe void EndSourceName(uint aAsyncHandle, out string aaSourceName)
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

        public unsafe void EndSetSourceName(uint aAsyncHandle)
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

        public unsafe void EndSourceType(uint aAsyncHandle, out string aaSourceType)
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

        public unsafe void EndSourceVisible(uint aAsyncHandle, out bool aaSourceVisible)
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

        public unsafe void EndSetSourceVisible(uint aAsyncHandle)
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

