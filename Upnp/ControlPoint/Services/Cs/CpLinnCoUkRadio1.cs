using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkRadio1 : ICpProxy, IDisposable
    {
        void SyncPlay();
        void BeginPlay(CpProxy.CallbackAsyncComplete aCallback);
        void EndPlay(uint aAsyncHandle);
        void SyncPause();
        void BeginPause(CpProxy.CallbackAsyncComplete aCallback);
        void EndPause(uint aAsyncHandle);
        void SyncStop();
        void BeginStop(CpProxy.CallbackAsyncComplete aCallback);
        void EndStop(uint aAsyncHandle);
        void SyncSeekSecondAbsolute(uint aaSecond);
        void BeginSeekSecondAbsolute(uint aaSecond, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekSecondAbsolute(uint aAsyncHandle);
        void SyncSeekSecondRelative(int aaSecond);
        void BeginSeekSecondRelative(int aaSecond, CpProxy.CallbackAsyncComplete aCallback);
        void EndSeekSecondRelative(uint aAsyncHandle);
        void SyncChannel(out string aaUri, out string aaMetadata);
        void BeginChannel(CpProxy.CallbackAsyncComplete aCallback);
        void EndChannel(uint aAsyncHandle, out string aaUri, out string aaMetadata);
        void SyncSetChannel(string aaUri, string aaMetadata);
        void BeginSetChannel(string aaUri, string aaMetadata, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetChannel(uint aAsyncHandle);
        void SyncProtocolInfo(out string aaInfo);
        void BeginProtocolInfo(CpProxy.CallbackAsyncComplete aCallback);
        void EndProtocolInfo(uint aAsyncHandle, out string aaInfo);
        void SyncTransportState(out string aaState);
        void BeginTransportState(CpProxy.CallbackAsyncComplete aCallback);
        void EndTransportState(uint aAsyncHandle, out string aaState);
        void SyncId(out uint aaId);
        void BeginId(CpProxy.CallbackAsyncComplete aCallback);
        void EndId(uint aAsyncHandle, out uint aaId);
        void SyncSetId(uint aaId, string aaUri);
        void BeginSetId(uint aaId, string aaUri, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetId(uint aAsyncHandle);
        void SyncRead(uint aaId, out string aaMetadata);
        void BeginRead(uint aaId, CpProxy.CallbackAsyncComplete aCallback);
        void EndRead(uint aAsyncHandle, out string aaMetadata);
        void SyncReadList(string aaIdList, out string aaMetadataList);
        void BeginReadList(string aaIdList, CpProxy.CallbackAsyncComplete aCallback);
        void EndReadList(uint aAsyncHandle, out string aaMetadataList);
        void SyncIdArray(out uint aaIdArrayToken, out string aaIdArray);
        void BeginIdArray(CpProxy.CallbackAsyncComplete aCallback);
        void EndIdArray(uint aAsyncHandle, out uint aaIdArrayToken, out string aaIdArray);
        void SyncIdArrayChanged(uint aaIdArrayToken, out bool aaIdArrayChanged);
        void BeginIdArrayChanged(uint aaIdArrayToken, CpProxy.CallbackAsyncComplete aCallback);
        void EndIdArrayChanged(uint aAsyncHandle, out bool aaIdArrayChanged);
        void SyncIdsMax(out uint aaIdsMax);
        void BeginIdsMax(CpProxy.CallbackAsyncComplete aCallback);
        void EndIdsMax(uint aAsyncHandle, out uint aaIdsMax);

        void SetPropertyChannelUriChanged(CpProxy.CallbackPropertyChanged aChannelUriChanged);
        void PropertyChannelUri(out string aChannelUri);
        void SetPropertyChannelMetadataChanged(CpProxy.CallbackPropertyChanged aChannelMetadataChanged);
        void PropertyChannelMetadata(out string aChannelMetadata);
        void SetPropertyTransportStateChanged(CpProxy.CallbackPropertyChanged aTransportStateChanged);
        void PropertyTransportState(out string aTransportState);
        void SetPropertyProtocolInfoChanged(CpProxy.CallbackPropertyChanged aProtocolInfoChanged);
        void PropertyProtocolInfo(out string aProtocolInfo);
        void SetPropertyIdChanged(CpProxy.CallbackPropertyChanged aIdChanged);
        void PropertyId(out uint aId);
        void SetPropertyIdArrayChanged(CpProxy.CallbackPropertyChanged aIdArrayChanged);
        void PropertyIdArray(out string aIdArray);
        void SetPropertyIdsMaxChanged(CpProxy.CallbackPropertyChanged aIdsMaxChanged);
        void PropertyIdsMax(out uint aIdsMax);
    }

    /// <summary>
    /// Proxy for the linn.co.uk:Radio:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkRadio1 : CpProxy, IDisposable, ICpProxyLinnCoUkRadio1
    {
        [DllImport("CpLinnCoUkRadio1")]
        static extern uint CpProxyLinnCoUkRadio1Create(uint aDeviceHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1Destroy(uint aHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncPlay(uint aHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginPlay(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndPlay(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncPause(uint aHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginPause(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndPause(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncStop(uint aHandle);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginStop(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndStop(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncSeekSecondAbsolute(uint aHandle, uint aaSecond);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginSeekSecondAbsolute(uint aHandle, uint aaSecond, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndSeekSecondAbsolute(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncSeekSecondRelative(uint aHandle, int aaSecond);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginSeekSecondRelative(uint aHandle, int aaSecond, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndSeekSecondRelative(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncChannel(uint aHandle, char** aaUri, char** aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginChannel(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndChannel(uint aHandle, uint aAsync, char** aaUri, char** aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncSetChannel(uint aHandle, char* aaUri, char* aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginSetChannel(uint aHandle, char* aaUri, char* aaMetadata, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndSetChannel(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncProtocolInfo(uint aHandle, char** aaInfo);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginProtocolInfo(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndProtocolInfo(uint aHandle, uint aAsync, char** aaInfo);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncTransportState(uint aHandle, char** aaState);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginTransportState(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndTransportState(uint aHandle, uint aAsync, char** aaState);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncId(uint aHandle, uint* aaId);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginId(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndId(uint aHandle, uint aAsync, uint* aaId);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncSetId(uint aHandle, uint aaId, char* aaUri);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginSetId(uint aHandle, uint aaId, char* aaUri, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndSetId(uint aHandle, uint aAsync);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncRead(uint aHandle, uint aaId, char** aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginRead(uint aHandle, uint aaId, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndRead(uint aHandle, uint aAsync, char** aaMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncReadList(uint aHandle, char* aaIdList, char** aaMetadataList);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginReadList(uint aHandle, char* aaIdList, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndReadList(uint aHandle, uint aAsync, char** aaMetadataList);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncIdArray(uint aHandle, uint* aaIdArrayToken, char** aaIdArray, uint* aaIdArrayLen);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginIdArray(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndIdArray(uint aHandle, uint aAsync, uint* aaIdArrayToken, char** aaIdArray, uint* aaIdArrayLen);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncIdArrayChanged(uint aHandle, uint aaIdArrayToken, uint* aaIdArrayChanged);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginIdArrayChanged(uint aHandle, uint aaIdArrayToken, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndIdArrayChanged(uint aHandle, uint aAsync, uint* aaIdArrayChanged);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1SyncIdsMax(uint aHandle, uint* aaIdsMax);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1BeginIdsMax(uint aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe int CpProxyLinnCoUkRadio1EndIdsMax(uint aHandle, uint aAsync, uint* aaIdsMax);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyChannelUriChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyChannelMetadataChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyTransportStateChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyProtocolInfoChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyIdChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyIdArrayChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern void CpProxyLinnCoUkRadio1SetPropertyIdsMaxChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyChannelUri(uint aHandle, char** aChannelUri);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyChannelMetadata(uint aHandle, char** aChannelMetadata);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyTransportState(uint aHandle, char** aTransportState);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyProtocolInfo(uint aHandle, char** aProtocolInfo);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyId(uint aHandle, uint* aId);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyIdArray(uint aHandle, char** aIdArray, uint* aLen);
        [DllImport("CpLinnCoUkRadio1")]
        static extern unsafe void CpProxyLinnCoUkRadio1PropertyIdsMax(uint aHandle, uint* aIdsMax);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iChannelUriChanged;
        private CallbackPropertyChanged iChannelMetadataChanged;
        private CallbackPropertyChanged iTransportStateChanged;
        private CallbackPropertyChanged iProtocolInfoChanged;
        private CallbackPropertyChanged iIdChanged;
        private CallbackPropertyChanged iIdArrayChanged;
        private CallbackPropertyChanged iIdsMaxChanged;
        private Callback iCallbackChannelUriChanged;
        private Callback iCallbackChannelMetadataChanged;
        private Callback iCallbackTransportStateChanged;
        private Callback iCallbackProtocolInfoChanged;
        private Callback iCallbackIdChanged;
        private Callback iCallbackIdArrayChanged;
        private Callback iCallbackIdsMaxChanged;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkRadio1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkRadio1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncPlay()
        {
            {
                CpProxyLinnCoUkRadio1SyncPlay(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPlay().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPlay(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginPlay(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndPlay(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkRadio1EndPlay(iHandle, aAsyncHandle))
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
        public unsafe void SyncPause()
        {
            {
                CpProxyLinnCoUkRadio1SyncPause(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPause().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginPause(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginPause(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndPause(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkRadio1EndPause(iHandle, aAsyncHandle))
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
        public unsafe void SyncStop()
        {
            {
                CpProxyLinnCoUkRadio1SyncStop(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStop().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginStop(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginStop(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndStop(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkRadio1EndStop(iHandle, aAsyncHandle))
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
        /// <param name="aaSecond"></param>
        public unsafe void SyncSeekSecondAbsolute(uint aaSecond)
        {
            {
                CpProxyLinnCoUkRadio1SyncSeekSecondAbsolute(iHandle, aaSecond);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekSecondAbsolute().</remarks>
        /// <param name="aaSecond"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeekSecondAbsolute(uint aaSecond, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginSeekSecondAbsolute(iHandle, aaSecond, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSeekSecondAbsolute(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkRadio1EndSeekSecondAbsolute(iHandle, aAsyncHandle))
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
        /// <param name="aaSecond"></param>
        public unsafe void SyncSeekSecondRelative(int aaSecond)
        {
            {
                CpProxyLinnCoUkRadio1SyncSeekSecondRelative(iHandle, aaSecond);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSeekSecondRelative().</remarks>
        /// <param name="aaSecond"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSeekSecondRelative(int aaSecond, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginSeekSecondRelative(iHandle, aaSecond, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSeekSecondRelative(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkRadio1EndSeekSecondRelative(iHandle, aAsyncHandle))
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
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        public unsafe void SyncChannel(out string aaUri, out string aaMetadata)
        {
            char* aUri;
            char* aMetadata;
            {
                CpProxyLinnCoUkRadio1SyncChannel(iHandle, &aUri, &aMetadata);
            }
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndChannel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginChannel(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginChannel(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        public unsafe void EndChannel(uint aAsyncHandle, out string aaUri, out string aaMetadata)
        {
            char* aUri;
            char* aMetadata;
            {
                if (0 != CpProxyLinnCoUkRadio1EndChannel(iHandle, aAsyncHandle, &aUri, &aMetadata))
                {
                    throw(new ProxyError());
                }
            }
            aaUri = Marshal.PtrToStringAnsi((IntPtr)aUri);
            ZappFree(aUri);
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        public unsafe void SyncSetChannel(string aaUri, string aaMetadata)
        {
            char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
            char* aMetadata = (char*)Marshal.StringToHGlobalAnsi(aaMetadata);
            {
                CpProxyLinnCoUkRadio1SyncSetChannel(iHandle, aUri, aMetadata);
            }
            Marshal.FreeHGlobal((IntPtr)aUri);
            Marshal.FreeHGlobal((IntPtr)aMetadata);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetChannel().</remarks>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetChannel(string aaUri, string aaMetadata, CallbackAsyncComplete aCallback)
        {
            char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
            char* aMetadata = (char*)Marshal.StringToHGlobalAnsi(aaMetadata);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginSetChannel(iHandle, aUri, aMetadata, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aUri);
            Marshal.FreeHGlobal((IntPtr)aMetadata);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetChannel(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkRadio1EndSetChannel(iHandle, aAsyncHandle))
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
        /// <param name="aaInfo"></param>
        public unsafe void SyncProtocolInfo(out string aaInfo)
        {
            char* aInfo;
            {
                CpProxyLinnCoUkRadio1SyncProtocolInfo(iHandle, &aInfo);
            }
            aaInfo = Marshal.PtrToStringAnsi((IntPtr)aInfo);
            ZappFree(aInfo);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndProtocolInfo().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginProtocolInfo(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginProtocolInfo(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaInfo"></param>
        public unsafe void EndProtocolInfo(uint aAsyncHandle, out string aaInfo)
        {
            char* aInfo;
            {
                if (0 != CpProxyLinnCoUkRadio1EndProtocolInfo(iHandle, aAsyncHandle, &aInfo))
                {
                    throw(new ProxyError());
                }
            }
            aaInfo = Marshal.PtrToStringAnsi((IntPtr)aInfo);
            ZappFree(aInfo);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaState"></param>
        public unsafe void SyncTransportState(out string aaState)
        {
            char* aState;
            {
                CpProxyLinnCoUkRadio1SyncTransportState(iHandle, &aState);
            }
            aaState = Marshal.PtrToStringAnsi((IntPtr)aState);
            ZappFree(aState);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTransportState().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginTransportState(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginTransportState(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaState"></param>
        public unsafe void EndTransportState(uint aAsyncHandle, out string aaState)
        {
            char* aState;
            {
                if (0 != CpProxyLinnCoUkRadio1EndTransportState(iHandle, aAsyncHandle, &aState))
                {
                    throw(new ProxyError());
                }
            }
            aaState = Marshal.PtrToStringAnsi((IntPtr)aState);
            ZappFree(aState);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaId"></param>
        public unsafe void SyncId(out uint aaId)
        {
            fixed (uint* aId = &aaId)
            {
                CpProxyLinnCoUkRadio1SyncId(iHandle, aId);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndId().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginId(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginId(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaId"></param>
        public unsafe void EndId(uint aAsyncHandle, out uint aaId)
        {
            fixed (uint* aId = &aaId)
            {
                if (0 != CpProxyLinnCoUkRadio1EndId(iHandle, aAsyncHandle, aId))
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
        /// <param name="aaId"></param>
        /// <param name="aaUri"></param>
        public unsafe void SyncSetId(uint aaId, string aaUri)
        {
            char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
            {
                CpProxyLinnCoUkRadio1SyncSetId(iHandle, aaId, aUri);
            }
            Marshal.FreeHGlobal((IntPtr)aUri);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetId().</remarks>
        /// <param name="aaId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetId(uint aaId, string aaUri, CallbackAsyncComplete aCallback)
        {
            char* aUri = (char*)Marshal.StringToHGlobalAnsi(aaUri);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginSetId(iHandle, aaId, aUri, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aUri);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetId(uint aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkRadio1EndSetId(iHandle, aAsyncHandle))
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
        /// <param name="aaId"></param>
        /// <param name="aaMetadata"></param>
        public unsafe void SyncRead(uint aaId, out string aaMetadata)
        {
            char* aMetadata;
            {
                CpProxyLinnCoUkRadio1SyncRead(iHandle, aaId, &aMetadata);
            }
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRead().</remarks>
        /// <param name="aaId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginRead(uint aaId, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginRead(iHandle, aaId, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetadata"></param>
        public unsafe void EndRead(uint aAsyncHandle, out string aaMetadata)
        {
            char* aMetadata;
            {
                if (0 != CpProxyLinnCoUkRadio1EndRead(iHandle, aAsyncHandle, &aMetadata))
                {
                    throw(new ProxyError());
                }
            }
            aaMetadata = Marshal.PtrToStringAnsi((IntPtr)aMetadata);
            ZappFree(aMetadata);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdList"></param>
        /// <param name="aaMetadataList"></param>
        public unsafe void SyncReadList(string aaIdList, out string aaMetadataList)
        {
            char* aIdList = (char*)Marshal.StringToHGlobalAnsi(aaIdList);
            char* aMetadataList;
            {
                CpProxyLinnCoUkRadio1SyncReadList(iHandle, aIdList, &aMetadataList);
            }
            Marshal.FreeHGlobal((IntPtr)aIdList);
            aaMetadataList = Marshal.PtrToStringAnsi((IntPtr)aMetadataList);
            ZappFree(aMetadataList);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndReadList().</remarks>
        /// <param name="aaIdList"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginReadList(string aaIdList, CallbackAsyncComplete aCallback)
        {
            char* aIdList = (char*)Marshal.StringToHGlobalAnsi(aaIdList);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginReadList(iHandle, aIdList, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aIdList);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetadataList"></param>
        public unsafe void EndReadList(uint aAsyncHandle, out string aaMetadataList)
        {
            char* aMetadataList;
            {
                if (0 != CpProxyLinnCoUkRadio1EndReadList(iHandle, aAsyncHandle, &aMetadataList))
                {
                    throw(new ProxyError());
                }
            }
            aaMetadataList = Marshal.PtrToStringAnsi((IntPtr)aMetadataList);
            ZappFree(aMetadataList);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        public unsafe void SyncIdArray(out uint aaIdArrayToken, out string aaIdArray)
        {
            char* aIdArray;
            uint aIdArrayLen;
            fixed (uint* aIdArrayToken = &aaIdArrayToken)
            {
                CpProxyLinnCoUkRadio1SyncIdArray(iHandle, aIdArrayToken, &aIdArray, &aIdArrayLen);
            }
            aaIdArray = Marshal.PtrToStringAnsi((IntPtr)aIdArray, (int)aIdArrayLen);
            ZappFree(aIdArray);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdArray().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginIdArray(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginIdArray(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        public unsafe void EndIdArray(uint aAsyncHandle, out uint aaIdArrayToken, out string aaIdArray)
        {
            char* aIdArray;
            uint aIdArrayLen;
            fixed (uint* aIdArrayToken = &aaIdArrayToken)
            {
                if (0 != CpProxyLinnCoUkRadio1EndIdArray(iHandle, aAsyncHandle, aIdArrayToken, &aIdArray, &aIdArrayLen))
                {
                    throw(new ProxyError());
                }
            }
            aaIdArray = Marshal.PtrToStringAnsi((IntPtr)aIdArray, (int)aIdArrayLen);
            ZappFree(aIdArray);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArrayChanged"></param>
        public unsafe void SyncIdArrayChanged(uint aaIdArrayToken, out bool aaIdArrayChanged)
        {
            uint aIdArrayChanged;
            {
                CpProxyLinnCoUkRadio1SyncIdArrayChanged(iHandle, aaIdArrayToken, &aIdArrayChanged);
            }
            aaIdArrayChanged = (aIdArrayChanged != 0);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdArrayChanged().</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginIdArrayChanged(uint aaIdArrayToken, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginIdArrayChanged(iHandle, aaIdArrayToken, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdArrayChanged"></param>
        public unsafe void EndIdArrayChanged(uint aAsyncHandle, out bool aaIdArrayChanged)
        {
            uint aIdArrayChanged;
            {
                if (0 != CpProxyLinnCoUkRadio1EndIdArrayChanged(iHandle, aAsyncHandle, &aIdArrayChanged))
                {
                    throw(new ProxyError());
                }
            }
            aaIdArrayChanged = (aIdArrayChanged != 0);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdsMax"></param>
        public unsafe void SyncIdsMax(out uint aaIdsMax)
        {
            fixed (uint* aIdsMax = &aaIdsMax)
            {
                CpProxyLinnCoUkRadio1SyncIdsMax(iHandle, aIdsMax);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdsMax().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginIdsMax(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkRadio1BeginIdsMax(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdsMax"></param>
        public unsafe void EndIdsMax(uint aAsyncHandle, out uint aaIdsMax)
        {
            fixed (uint* aIdsMax = &aaIdsMax)
            {
                if (0 != CpProxyLinnCoUkRadio1EndIdsMax(iHandle, aAsyncHandle, aIdsMax))
                {
                    throw(new ProxyError());
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ChannelUri state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aChannelUriChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyChannelUriChanged(CallbackPropertyChanged aChannelUriChanged)
        {
            iChannelUriChanged = aChannelUriChanged;
            iCallbackChannelUriChanged = new Callback(PropertyChannelUriChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyChannelUriChanged(iHandle, iCallbackChannelUriChanged, ptr);
        }

        private void PropertyChannelUriChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iChannelUriChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the ChannelMetadata state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aChannelMetadataChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyChannelMetadataChanged(CallbackPropertyChanged aChannelMetadataChanged)
        {
            iChannelMetadataChanged = aChannelMetadataChanged;
            iCallbackChannelMetadataChanged = new Callback(PropertyChannelMetadataChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyChannelMetadataChanged(iHandle, iCallbackChannelMetadataChanged, ptr);
        }

        private void PropertyChannelMetadataChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iChannelMetadataChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the TransportState state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aTransportStateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTransportStateChanged(CallbackPropertyChanged aTransportStateChanged)
        {
            iTransportStateChanged = aTransportStateChanged;
            iCallbackTransportStateChanged = new Callback(PropertyTransportStateChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyTransportStateChanged(iHandle, iCallbackTransportStateChanged, ptr);
        }

        private void PropertyTransportStateChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iTransportStateChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the ProtocolInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aProtocolInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProtocolInfoChanged(CallbackPropertyChanged aProtocolInfoChanged)
        {
            iProtocolInfoChanged = aProtocolInfoChanged;
            iCallbackProtocolInfoChanged = new Callback(PropertyProtocolInfoChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyProtocolInfoChanged(iHandle, iCallbackProtocolInfoChanged, ptr);
        }

        private void PropertyProtocolInfoChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iProtocolInfoChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the Id state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aIdChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIdChanged(CallbackPropertyChanged aIdChanged)
        {
            iIdChanged = aIdChanged;
            iCallbackIdChanged = new Callback(PropertyIdChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyIdChanged(iHandle, iCallbackIdChanged, ptr);
        }

        private void PropertyIdChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iIdChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the IdArray state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aIdArrayChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIdArrayChanged(CallbackPropertyChanged aIdArrayChanged)
        {
            iIdArrayChanged = aIdArrayChanged;
            iCallbackIdArrayChanged = new Callback(PropertyIdArrayChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyIdArrayChanged(iHandle, iCallbackIdArrayChanged, ptr);
        }

        private void PropertyIdArrayChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iIdArrayChanged();
        }

        /// <summary>
        /// Set a delegate to be run when the IdsMax state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkRadio1 instance will not overlap.</remarks>
        /// <param name="aIdsMaxChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIdsMaxChanged(CallbackPropertyChanged aIdsMaxChanged)
        {
            iIdsMaxChanged = aIdsMaxChanged;
            iCallbackIdsMaxChanged = new Callback(PropertyIdsMaxChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyLinnCoUkRadio1SetPropertyIdsMaxChanged(iHandle, iCallbackIdsMaxChanged, ptr);
        }

        private void PropertyIdsMaxChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyLinnCoUkRadio1 self = (CpProxyLinnCoUkRadio1)gch.Target;
            self.iIdsMaxChanged();
        }

        /// <summary>
        /// Query the value of the ChannelUri property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aChannelUri">Will be set to the value of the property</param>
        public unsafe void PropertyChannelUri(out string aChannelUri)
        {
            char* ptr;
            CpProxyLinnCoUkRadio1PropertyChannelUri(iHandle, &ptr);
            aChannelUri = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the ChannelMetadata property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aChannelMetadata">Will be set to the value of the property</param>
        public unsafe void PropertyChannelMetadata(out string aChannelMetadata)
        {
            char* ptr;
            CpProxyLinnCoUkRadio1PropertyChannelMetadata(iHandle, &ptr);
            aChannelMetadata = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the TransportState property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTransportState">Will be set to the value of the property</param>
        public unsafe void PropertyTransportState(out string aTransportState)
        {
            char* ptr;
            CpProxyLinnCoUkRadio1PropertyTransportState(iHandle, &ptr);
            aTransportState = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the ProtocolInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProtocolInfo">Will be set to the value of the property</param>
        public unsafe void PropertyProtocolInfo(out string aProtocolInfo)
        {
            char* ptr;
            CpProxyLinnCoUkRadio1PropertyProtocolInfo(iHandle, &ptr);
            aProtocolInfo = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the Id property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aId">Will be set to the value of the property</param>
        public unsafe void PropertyId(out uint aId)
        {
            fixed (uint* id = &aId)
            {
                CpProxyLinnCoUkRadio1PropertyId(iHandle, id);
            }
        }

        /// <summary>
        /// Query the value of the IdArray property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aIdArray">Will be set to the value of the property</param>
        public unsafe void PropertyIdArray(out string aIdArray)
        {
            char* ptr;
            uint len;
            CpProxyLinnCoUkRadio1PropertyIdArray(iHandle, &ptr, &len);
            aIdArray = Marshal.PtrToStringAnsi((IntPtr)ptr, (int)len);
            ZappFree(ptr);
        }

        /// <summary>
        /// Query the value of the IdsMax property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aIdsMax">Will be set to the value of the property</param>
        public unsafe void PropertyIdsMax(out uint aIdsMax)
        {
            fixed (uint* idsMax = &aIdsMax)
            {
                CpProxyLinnCoUkRadio1PropertyIdsMax(iHandle, idsMax);
            }
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkRadio1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                CpProxyLinnCoUkRadio1Destroy(iHandle);
                iHandle = 0;
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

