using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkProduct3 : ICpProxy, IDisposable
    {
        void SyncType(out string aaType);
        void BeginType(CpProxy.CallbackAsyncComplete aCallback);
        void EndType(IntPtr aAsyncHandle, out string aaType);
        void SyncModel(out string aaModel);
        void BeginModel(CpProxy.CallbackAsyncComplete aCallback);
        void EndModel(IntPtr aAsyncHandle, out string aaModel);
        void SyncName(out string aaName);
        void BeginName(CpProxy.CallbackAsyncComplete aCallback);
        void EndName(IntPtr aAsyncHandle, out string aaName);
        void SyncSetName(string aaName);
        void BeginSetName(string aaName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetName(IntPtr aAsyncHandle);
        void SyncRoom(out string aaRoom);
        void BeginRoom(CpProxy.CallbackAsyncComplete aCallback);
        void EndRoom(IntPtr aAsyncHandle, out string aaRoom);
        void SyncSetRoom(string aaRoom);
        void BeginSetRoom(string aaRoom, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRoom(IntPtr aAsyncHandle);
        void SyncStandby(out bool aaStandby);
        void BeginStandby(CpProxy.CallbackAsyncComplete aCallback);
        void EndStandby(IntPtr aAsyncHandle, out bool aaStandby);
        void SyncSetStandby(bool aaStandby);
        void BeginSetStandby(bool aaStandby, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStandby(IntPtr aAsyncHandle);
        void SyncSourceCount(out uint aaSourceCount);
        void BeginSourceCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceCount(IntPtr aAsyncHandle, out uint aaSourceCount);
        void SyncSourceXml(out string aaSourceXml);
        void BeginSourceXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceXml(IntPtr aAsyncHandle, out string aaSourceXml);
        void SyncSourceIndex(out uint aaSourceIndex);
        void BeginSourceIndex(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceIndex(IntPtr aAsyncHandle, out uint aaSourceIndex);
        void SyncSetSourceIndex(uint aaSourceIndex);
        void BeginSetSourceIndex(uint aaSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceIndex(IntPtr aAsyncHandle);
        void SyncSetSourceIndexByName(string aaSourceName);
        void BeginSetSourceIndexByName(string aaSourceName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceIndexByName(IntPtr aAsyncHandle);
        void SyncSetStartupSourceIndexByName(string aaSourceName);
        void BeginSetStartupSourceIndexByName(string aaSourceName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupSourceIndexByName(IntPtr aAsyncHandle);
        void SyncStartupSourceIndex(out uint aaSourceIndex);
        void BeginStartupSourceIndex(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartupSourceIndex(IntPtr aAsyncHandle, out uint aaSourceIndex);
        void SyncSetStartupSourceIndex(uint aaSourceIndex);
        void BeginSetStartupSourceIndex(uint aaSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupSourceIndex(IntPtr aAsyncHandle);
        void SyncStartupSourceEnabled(out bool aaStartupSourceEnabled);
        void BeginStartupSourceEnabled(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartupSourceEnabled(IntPtr aAsyncHandle, out bool aaStartupSourceEnabled);
        void SyncSetStartupSourceEnabled(bool aaStartupSourceEnabled);
        void BeginSetStartupSourceEnabled(bool aaStartupSourceEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupSourceEnabled(IntPtr aAsyncHandle);
        void SyncSourceSystemName(uint aaSourceIndex, out string aaSourceName);
        void BeginSourceSystemName(uint aaSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceSystemName(IntPtr aAsyncHandle, out string aaSourceName);
        void SyncSourceName(uint aaSourceIndex, out string aaSourceName);
        void BeginSourceName(uint aaSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceName(IntPtr aAsyncHandle, out string aaSourceName);
        void SyncSetSourceName(uint aaSourceIndex, string aaSourceName);
        void BeginSetSourceName(uint aaSourceIndex, string aaSourceName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceName(IntPtr aAsyncHandle);
        void SyncSourceType(uint aaSourceIndex, out string aaSourceType);
        void BeginSourceType(uint aaSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceType(IntPtr aAsyncHandle, out string aaSourceType);
        void SyncSourceVisible(uint aaSourceIndex, out bool aaSourceVisible);
        void BeginSourceVisible(uint aaSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceVisible(IntPtr aAsyncHandle, out bool aaSourceVisible);
        void SyncSetSourceVisible(uint aaSourceIndex, bool aaSourceVisible);
        void BeginSetSourceVisible(uint aaSourceIndex, bool aaSourceVisible, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceVisible(IntPtr aAsyncHandle);

        void SetPropertyProductTypeChanged(CpProxy.CallbackPropertyChanged aProductTypeChanged);
        void PropertyProductType(out string aProductType);
        void SetPropertyProductModelChanged(CpProxy.CallbackPropertyChanged aProductModelChanged);
        void PropertyProductModel(out string aProductModel);
        void SetPropertyProductNameChanged(CpProxy.CallbackPropertyChanged aProductNameChanged);
        void PropertyProductName(out string aProductName);
        void SetPropertyProductRoomChanged(CpProxy.CallbackPropertyChanged aProductRoomChanged);
        void PropertyProductRoom(out string aProductRoom);
        void SetPropertyProductStandbyChanged(CpProxy.CallbackPropertyChanged aProductStandbyChanged);
        void PropertyProductStandby(out bool aProductStandby);
        void SetPropertyProductSourceIndexChanged(CpProxy.CallbackPropertyChanged aProductSourceIndexChanged);
        void PropertyProductSourceIndex(out uint aProductSourceIndex);
        void SetPropertyProductSourceCountChanged(CpProxy.CallbackPropertyChanged aProductSourceCountChanged);
        void PropertyProductSourceCount(out uint aProductSourceCount);
        void SetPropertyProductSourceXmlChanged(CpProxy.CallbackPropertyChanged aProductSourceXmlChanged);
        void PropertyProductSourceXml(out string aProductSourceXml);
        void SetPropertyStartupSourceIndexChanged(CpProxy.CallbackPropertyChanged aStartupSourceIndexChanged);
        void PropertyStartupSourceIndex(out uint aStartupSourceIndex);
        void SetPropertyStartupSourceEnabledChanged(CpProxy.CallbackPropertyChanged aStartupSourceEnabledChanged);
        void PropertyStartupSourceEnabled(out bool aStartupSourceEnabled);
        void SetPropertyProductAnySourceNameChanged(CpProxy.CallbackPropertyChanged aProductAnySourceNameChanged);
        void PropertyProductAnySourceName(out uint aProductAnySourceName);
        void SetPropertyProductAnySourceVisibleChanged(CpProxy.CallbackPropertyChanged aProductAnySourceVisibleChanged);
        void PropertyProductAnySourceVisible(out uint aProductAnySourceVisible);
        void SetPropertyProductAnySourceTypeChanged(CpProxy.CallbackPropertyChanged aProductAnySourceTypeChanged);
        void PropertyProductAnySourceType(out uint aProductAnySourceType);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Product:3 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkProduct3 : CpProxy, IDisposable, ICpProxyLinnCoUkProduct3
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkProduct3(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkProduct3Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaType"></param>
        public unsafe void SyncType(out string aaType)
        {
            char* aType;
            {
                CpProxyLinnCoUkProduct3SyncType(iHandle, &aType);
            }
            aaType = Marshal.PtrToStringAnsi((IntPtr)aType);
            ZappFree(aType);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndType().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginType(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginType(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaType"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaModel"></param>
        public unsafe void SyncModel(out string aaModel)
        {
            char* aModel;
            {
                CpProxyLinnCoUkProduct3SyncModel(iHandle, &aModel);
            }
            aaModel = Marshal.PtrToStringAnsi((IntPtr)aModel);
            ZappFree(aModel);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndModel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginModel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginModel(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaModel"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public unsafe void SyncName(out string aaName)
        {
            char* aName;
            {
                CpProxyLinnCoUkProduct3SyncName(iHandle, &aName);
            }
            aaName = Marshal.PtrToStringAnsi((IntPtr)aName);
            ZappFree(aName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndName().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginName(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginName(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaName"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public unsafe void SyncSetName(string aaName)
        {
            char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            {
                CpProxyLinnCoUkProduct3SyncSetName(iHandle, aName);
            }
            Marshal.FreeHGlobal((IntPtr)aName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetName().</remarks>
        /// <param name="aaName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetName(string aaName, CallbackAsyncComplete aCallback)
        {
            char* aName = (char*)Marshal.StringToHGlobalAnsi(aaName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetName(iHandle, aName, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aName);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetName(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetName(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRoom"></param>
        public unsafe void SyncRoom(out string aaRoom)
        {
            char* aRoom;
            {
                CpProxyLinnCoUkProduct3SyncRoom(iHandle, &aRoom);
            }
            aaRoom = Marshal.PtrToStringAnsi((IntPtr)aRoom);
            ZappFree(aRoom);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRoom().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginRoom(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginRoom(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaRoom"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRoom"></param>
        public unsafe void SyncSetRoom(string aaRoom)
        {
            char* aRoom = (char*)Marshal.StringToHGlobalAnsi(aaRoom);
            {
                CpProxyLinnCoUkProduct3SyncSetRoom(iHandle, aRoom);
            }
            Marshal.FreeHGlobal((IntPtr)aRoom);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRoom().</remarks>
        /// <param name="aaRoom"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetRoom(string aaRoom, CallbackAsyncComplete aCallback)
        {
            char* aRoom = (char*)Marshal.StringToHGlobalAnsi(aaRoom);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetRoom(iHandle, aRoom, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aRoom);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetRoom(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetRoom(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStandby"></param>
        public unsafe void SyncStandby(out bool aaStandby)
        {
            uint aStandby;
            {
                CpProxyLinnCoUkProduct3SyncStandby(iHandle, &aStandby);
            }
            aaStandby = (aStandby != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStandby().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStandby(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginStandby(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStandby"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStandby"></param>
        public unsafe void SyncSetStandby(bool aaStandby)
        {
            uint aStandby = (aaStandby? 1u : 0u);
            {
                CpProxyLinnCoUkProduct3SyncSetStandby(iHandle, aStandby);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStandby().</remarks>
        /// <param name="aaStandby"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStandby(bool aaStandby, CallbackAsyncComplete aCallback)
        {
            uint aStandby = (aaStandby? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetStandby(iHandle, aStandby, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStandby(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetStandby(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceCount"></param>
        public unsafe void SyncSourceCount(out uint aaSourceCount)
        {
            fixed (uint* aSourceCount = &aaSourceCount)
            {
                CpProxyLinnCoUkProduct3SyncSourceCount(iHandle, aSourceCount);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSourceCount(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceCount(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceCount"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceXml"></param>
        public unsafe void SyncSourceXml(out string aaSourceXml)
        {
            char* aSourceXml;
            {
                CpProxyLinnCoUkProduct3SyncSourceXml(iHandle, &aSourceXml);
            }
            aaSourceXml = Marshal.PtrToStringAnsi((IntPtr)aSourceXml);
            ZappFree(aSourceXml);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceXml().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSourceXml(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceXml(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceXml"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public unsafe void SyncSourceIndex(out uint aaSourceIndex)
        {
            fixed (uint* aSourceIndex = &aaSourceIndex)
            {
                CpProxyLinnCoUkProduct3SyncSourceIndex(iHandle, aSourceIndex);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceIndex().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSourceIndex(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceIndex(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceIndex"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public unsafe void SyncSetSourceIndex(uint aaSourceIndex)
        {
            {
                CpProxyLinnCoUkProduct3SyncSetSourceIndex(iHandle, aaSourceIndex);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceIndex().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetSourceIndex(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetSourceIndex(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetSourceIndex(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetSourceIndex(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceName"></param>
        public unsafe void SyncSetSourceIndexByName(string aaSourceName)
        {
            char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            {
                CpProxyLinnCoUkProduct3SyncSetSourceIndexByName(iHandle, aSourceName);
            }
            Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceIndexByName().</remarks>
        /// <param name="aaSourceName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetSourceIndexByName(string aaSourceName, CallbackAsyncComplete aCallback)
        {
            char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetSourceIndexByName(iHandle, aSourceName, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetSourceIndexByName(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetSourceIndexByName(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceName"></param>
        public unsafe void SyncSetStartupSourceIndexByName(string aaSourceName)
        {
            char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            {
                CpProxyLinnCoUkProduct3SyncSetStartupSourceIndexByName(iHandle, aSourceName);
            }
            Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupSourceIndexByName().</remarks>
        /// <param name="aaSourceName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStartupSourceIndexByName(string aaSourceName, CallbackAsyncComplete aCallback)
        {
            char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetStartupSourceIndexByName(iHandle, aSourceName, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStartupSourceIndexByName(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetStartupSourceIndexByName(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public unsafe void SyncStartupSourceIndex(out uint aaSourceIndex)
        {
            fixed (uint* aSourceIndex = &aaSourceIndex)
            {
                CpProxyLinnCoUkProduct3SyncStartupSourceIndex(iHandle, aSourceIndex);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartupSourceIndex().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStartupSourceIndex(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginStartupSourceIndex(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceIndex"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public unsafe void SyncSetStartupSourceIndex(uint aaSourceIndex)
        {
            {
                CpProxyLinnCoUkProduct3SyncSetStartupSourceIndex(iHandle, aaSourceIndex);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupSourceIndex().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStartupSourceIndex(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetStartupSourceIndex(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStartupSourceIndex(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetStartupSourceIndex(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStartupSourceEnabled"></param>
        public unsafe void SyncStartupSourceEnabled(out bool aaStartupSourceEnabled)
        {
            uint aStartupSourceEnabled;
            {
                CpProxyLinnCoUkProduct3SyncStartupSourceEnabled(iHandle, &aStartupSourceEnabled);
            }
            aaStartupSourceEnabled = (aStartupSourceEnabled != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartupSourceEnabled().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStartupSourceEnabled(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginStartupSourceEnabled(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStartupSourceEnabled"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStartupSourceEnabled"></param>
        public unsafe void SyncSetStartupSourceEnabled(bool aaStartupSourceEnabled)
        {
            uint aStartupSourceEnabled = (aaStartupSourceEnabled? 1u : 0u);
            {
                CpProxyLinnCoUkProduct3SyncSetStartupSourceEnabled(iHandle, aStartupSourceEnabled);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupSourceEnabled().</remarks>
        /// <param name="aaStartupSourceEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetStartupSourceEnabled(bool aaStartupSourceEnabled, CallbackAsyncComplete aCallback)
        {
            uint aStartupSourceEnabled = (aaStartupSourceEnabled? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetStartupSourceEnabled(iHandle, aStartupSourceEnabled, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetStartupSourceEnabled(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetStartupSourceEnabled(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        public unsafe void SyncSourceSystemName(uint aaSourceIndex, out string aaSourceName)
        {
            char* aSourceName;
            {
                CpProxyLinnCoUkProduct3SyncSourceSystemName(iHandle, aaSourceIndex, &aSourceName);
            }
            aaSourceName = Marshal.PtrToStringAnsi((IntPtr)aSourceName);
            ZappFree(aSourceName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceSystemName().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSourceSystemName(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceSystemName(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceName"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        public unsafe void SyncSourceName(uint aaSourceIndex, out string aaSourceName)
        {
            char* aSourceName;
            {
                CpProxyLinnCoUkProduct3SyncSourceName(iHandle, aaSourceIndex, &aSourceName);
            }
            aaSourceName = Marshal.PtrToStringAnsi((IntPtr)aSourceName);
            ZappFree(aSourceName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceName().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSourceName(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceName(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceName"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        public unsafe void SyncSetSourceName(uint aaSourceIndex, string aaSourceName)
        {
            char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            {
                CpProxyLinnCoUkProduct3SyncSetSourceName(iHandle, aaSourceIndex, aSourceName);
            }
            Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceName().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetSourceName(uint aaSourceIndex, string aaSourceName, CallbackAsyncComplete aCallback)
        {
            char* aSourceName = (char*)Marshal.StringToHGlobalAnsi(aaSourceName);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetSourceName(iHandle, aaSourceIndex, aSourceName, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aSourceName);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetSourceName(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetSourceName(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceType"></param>
        public unsafe void SyncSourceType(uint aaSourceIndex, out string aaSourceType)
        {
            char* aSourceType;
            {
                CpProxyLinnCoUkProduct3SyncSourceType(iHandle, aaSourceIndex, &aSourceType);
            }
            aaSourceType = Marshal.PtrToStringAnsi((IntPtr)aSourceType);
            ZappFree(aSourceType);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceType().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSourceType(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceType(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceType"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        public unsafe void SyncSourceVisible(uint aaSourceIndex, out bool aaSourceVisible)
        {
            uint aSourceVisible;
            {
                CpProxyLinnCoUkProduct3SyncSourceVisible(iHandle, aaSourceIndex, &aSourceVisible);
            }
            aaSourceVisible = (aSourceVisible != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceVisible().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSourceVisible(uint aaSourceIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSourceVisible(iHandle, aaSourceIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceVisible"></param>
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

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        public unsafe void SyncSetSourceVisible(uint aaSourceIndex, bool aaSourceVisible)
        {
            uint aSourceVisible = (aaSourceVisible? 1u : 0u);
            {
                CpProxyLinnCoUkProduct3SyncSetSourceVisible(iHandle, aaSourceIndex, aSourceVisible);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceVisible().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetSourceVisible(uint aaSourceIndex, bool aaSourceVisible, CallbackAsyncComplete aCallback)
        {
            uint aSourceVisible = (aaSourceVisible? 1u : 0u);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkProduct3BeginSetSourceVisible(iHandle, aaSourceIndex, aSourceVisible, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetSourceVisible(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkProduct3EndSetSourceVisible(iHandle, aAsyncHandle))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductType state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductTypeChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductModel state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductModelChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductNameChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductRoom state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductRoomChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductStandby state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductStandbyChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductSourceIndex state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductSourceIndexChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductSourceCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductSourceCountChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductSourceXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductSourceXmlChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the StartupSourceIndex state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aStartupSourceIndexChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the StartupSourceEnabled state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aStartupSourceEnabledChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductAnySourceName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductAnySourceNameChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductAnySourceVisible state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductAnySourceVisibleChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Set a delegate to be run when the ProductAnySourceType state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductAnySourceTypeChanged">The delegate to run when the state variable changes</param>
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

        /// <summary>
        /// Query the value of the ProductType property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductType">Will be set to the value of the property</param>
        public unsafe void PropertyProductType(out string aProductType)
        {
            char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductType(iHandle, &ptr);
            aProductType = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the ProductModel property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductModel">Will be set to the value of the property</param>
        public unsafe void PropertyProductModel(out string aProductModel)
        {
            char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductModel(iHandle, &ptr);
            aProductModel = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the ProductName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductName">Will be set to the value of the property</param>
        public unsafe void PropertyProductName(out string aProductName)
        {
            char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductName(iHandle, &ptr);
            aProductName = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the ProductRoom property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductRoom">Will be set to the value of the property</param>
        public unsafe void PropertyProductRoom(out string aProductRoom)
        {
            char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductRoom(iHandle, &ptr);
            aProductRoom = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the ProductStandby property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductStandby">Will be set to the value of the property</param>
        public unsafe void PropertyProductStandby(out bool aProductStandby)
        {
            uint productStandby;
            CpProxyLinnCoUkProduct3PropertyProductStandby(iHandle, &productStandby);
            aProductStandby = (productStandby != 0);
        }

        /// <summary>
        /// Query the value of the ProductSourceIndex property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductSourceIndex">Will be set to the value of the property</param>
        public unsafe void PropertyProductSourceIndex(out uint aProductSourceIndex)
        {
            fixed (uint* productSourceIndex = &aProductSourceIndex)
            {
                CpProxyLinnCoUkProduct3PropertyProductSourceIndex(iHandle, productSourceIndex);
            }
        }

        /// <summary>
        /// Query the value of the ProductSourceCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductSourceCount">Will be set to the value of the property</param>
        public unsafe void PropertyProductSourceCount(out uint aProductSourceCount)
        {
            fixed (uint* productSourceCount = &aProductSourceCount)
            {
                CpProxyLinnCoUkProduct3PropertyProductSourceCount(iHandle, productSourceCount);
            }
        }

        /// <summary>
        /// Query the value of the ProductSourceXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductSourceXml">Will be set to the value of the property</param>
        public unsafe void PropertyProductSourceXml(out string aProductSourceXml)
        {
            char* ptr;
            CpProxyLinnCoUkProduct3PropertyProductSourceXml(iHandle, &ptr);
            aProductSourceXml = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the StartupSourceIndex property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStartupSourceIndex">Will be set to the value of the property</param>
        public unsafe void PropertyStartupSourceIndex(out uint aStartupSourceIndex)
        {
            fixed (uint* startupSourceIndex = &aStartupSourceIndex)
            {
                CpProxyLinnCoUkProduct3PropertyStartupSourceIndex(iHandle, startupSourceIndex);
            }
        }

        /// <summary>
        /// Query the value of the StartupSourceEnabled property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStartupSourceEnabled">Will be set to the value of the property</param>
        public unsafe void PropertyStartupSourceEnabled(out bool aStartupSourceEnabled)
        {
            uint startupSourceEnabled;
            CpProxyLinnCoUkProduct3PropertyStartupSourceEnabled(iHandle, &startupSourceEnabled);
            aStartupSourceEnabled = (startupSourceEnabled != 0);
        }

        /// <summary>
        /// Query the value of the ProductAnySourceName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductAnySourceName">Will be set to the value of the property</param>
        public unsafe void PropertyProductAnySourceName(out uint aProductAnySourceName)
        {
            fixed (uint* productAnySourceName = &aProductAnySourceName)
            {
                CpProxyLinnCoUkProduct3PropertyProductAnySourceName(iHandle, productAnySourceName);
            }
        }

        /// <summary>
        /// Query the value of the ProductAnySourceVisible property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductAnySourceVisible">Will be set to the value of the property</param>
        public unsafe void PropertyProductAnySourceVisible(out uint aProductAnySourceVisible)
        {
            fixed (uint* productAnySourceVisible = &aProductAnySourceVisible)
            {
                CpProxyLinnCoUkProduct3PropertyProductAnySourceVisible(iHandle, productAnySourceVisible);
            }
        }

        /// <summary>
        /// Query the value of the ProductAnySourceType property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductAnySourceType">Will be set to the value of the property</param>
        public unsafe void PropertyProductAnySourceType(out uint aProductAnySourceType)
        {
            fixed (uint* productAnySourceType = &aProductAnySourceType)
            {
                CpProxyLinnCoUkProduct3PropertyProductAnySourceType(iHandle, productAnySourceType);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                CpProxyLinnCoUkProduct3Destroy(iHandle);
                iHandle = IntPtr.Zero;
            }
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

