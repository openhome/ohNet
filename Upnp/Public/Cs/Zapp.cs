using System;
using System.Runtime.InteropServices;

namespace Zapp
{
    public class InitParams :IDisposable
    {
        [DllImport ("ZappUpnp")]
        static extern uint ZappInitParamsCreate();
        [DllImport ("ZappUpnp")]
        static extern void ZappInitParamsDestroy(uint aParams);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetLogOutput(uint aParams, ZappCallbackMsg aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetFatalErrorHandler(uint aParams, ZappCallbackMsg aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetAsyncBeginHandler(uint aParams, ZappCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetAsyncEndHandler(uint aParams, ZappCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetAsyncErrorHandler(uint aParams, ZappCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetDefaultSubnet(uint aParams, uint aSubnet);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetSubnetChangedListener(uint aParams, ZappCallback aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetTcpConnectTimeout(uint aParams, uint aTimeoutMs);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetMsearchTime(uint aParams, uint aSecs);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetMsearchTtl(uint aParams, uint aTtl);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumEventSessionThreads(uint aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumXmlFetcherThreads(uint aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumActionInvokerThreads(uint aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumInvocations(uint aParams, uint aNumInvocations);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumSubscriberThreads(uint aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetPendingSubscriptionTimeout(uint aParams, uint aTimeoutMs);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetDvMaxUpdateTime(uint aParams, uint aSecs);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetDvNumPublisherThreads(uint aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsTcpConnectTimeoutMs(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsMsearchTimeSecs(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsMsearchTtl(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumEventSessionThreads(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumXmlFetcherThreads(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumActionInvokerThreads(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumInvocations(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumSubscriberThreads(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsPendingSubscriptionTimeoutMs(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsDvMaxUpdateTimeSecs(uint aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsDvNumPublisherThreads(uint aParams);

        public InitParams()
        {
            iHandle = ZappInitParamsCreate();
            iGch = GCHandle.Alloc(this);
        }

        public void SetLogOutput(ZappCallbackMsg aCallback)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            ZappInitParamsSetLogOutput(iHandle, aCallback, ptr);
        }

        public void SetFatalErrorHandler(ZappCallbackMsg aCallback)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            ZappInitParamsSetFatalErrorHandler(iHandle, aCallback, ptr);
        }

        public void SetAsyncBeginHandler(ZappCallbackAsync aCallback)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            ZappInitParamsSetAsyncBeginHandler(iHandle, aCallback, ptr);
        }

        public void SetAsyncEndHandler(ZappCallbackAsync aCallback)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            ZappInitParamsSetAsyncEndHandler(iHandle, aCallback, ptr); 
        }
        
        public void SetAsyncErrorHandler(ZappCallbackAsync aCallback)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            ZappInitParamsSetAsyncErrorHandler(iHandle, aCallback, ptr);
        }

        public void SetDefaultSubnet(uint aSubnet)
        {
            ZappInitParamsSetDefaultSubnet(iHandle, aSubnet);
        }

        public void SetSubnetChangedListener(ZappCallback aCallback)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            ZappInitParamsSetSubnetChangedListener(iHandle, aCallback, ptr);
        }

        public void SetTcpConnectTimeout(uint aTimeoutMs)
        {
            ZappInitParamsSetTcpConnectTimeout(iHandle, aTimeoutMs);
        }

        public void SetMsearchTime(uint aSecs)
        {
            ZappInitParamsSetMsearchTime(iHandle, aSecs);
        }

        public void SetMsearchTtl(uint aTtl)
        {
            ZappInitParamsSetMsearchTtl(iHandle, aTtl);
        }

        public void SetNumEventSessionThreads(uint aNumThreads)
        {
            ZappInitParamsSetNumEventSessionThreads(iHandle, aNumThreads);
        }

        public void SetNumXmlFetcherThreads(uint aNumThreads)
        {
            ZappInitParamsSetNumXmlFetcherThreads(iHandle, aNumThreads);
        }

        public void SetNumActionInvokerThreads(uint aNumThreads)
        {
            ZappInitParamsSetNumActionInvokerThreads(iHandle, aNumThreads);
        }

        public void SetNumInvocations(uint aNumInvocations)
        {
            ZappInitParamsSetNumInvocations(iHandle, aNumInvocations);
        }

        public void SetNumSubscriberThreads(uint aNumThreads)
        {
            ZappInitParamsSetNumSubscriberThreads(iHandle, aNumThreads);
        }

        public void SetPendingSubscriptionTimeout(uint aTimeoutMs)
        {
            ZappInitParamsSetPendingSubscriptionTimeout(iHandle, aTimeoutMs);
        }

        public void SetDvMaxUpdateTime(uint aSecs)
        {
            ZappInitParamsSetDvMaxUpdateTime(iHandle, aSecs);
        }

        public void SetDvNumPublisherThreads(uint aNumThreads)
        {
            ZappInitParamsSetDvNumPublisherThreads(iHandle, aNumThreads);
        }

        public int TcpConnectTimeoutMs()
        {
            return ZappInitParamsTcpConnectTimeoutMs(iHandle);
        }

        public int MsearchTimeSecs()
        {
            return ZappInitParamsMsearchTimeSecs(iHandle);
        }

        public int MsearchTtl()
        {
            return ZappInitParamsMsearchTtl(iHandle);
        }

        public int NumEventSessionThreads()
        {
            return ZappInitParamsNumEventSessionThreads(iHandle);
        }

        public int NumXmlFetcherThreads()
        {
            return ZappInitParamsNumXmlFetcherThreads(iHandle);
        }

        public int NumActionInvokerThreads()
        {
            return ZappInitParamsNumActionInvokerThreads(iHandle);
        }

        public int NumInvocations()
        {
            return ZappInitParamsNumInvocations(iHandle);
        }

        public int NumSubscriberThreads()
        {
            return ZappInitParamsNumSubscriberThreads(iHandle);
        }

        public int PendingSubscriptionTimeoutMs()
        {
            return ZappInitParamsPendingSubscriptionTimeoutMs(iHandle);
        }

        public int DvMaxUpdateTimeSecs()
        {
            return ZappInitParamsDvMaxUpdateTimeSecs(iHandle);
        }

        public int DvNumPublisherThreads()
        {
            return ZappInitParamsDvNumPublisherThreads(iHandle);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (!this.iDisposed)
            {
                iGch.Free();
            }
        }

        public uint Handle
        {
            get
            {
                return iHandle;
            }
        }

        private uint iHandle;
        protected GCHandle iGch;
        private bool iDisposed = false;

        public delegate void ZappCallback(IntPtr aPtr);
        public delegate void ZappCallbackMsg(IntPtr aPtr, string aMsg);
        public delegate void ZappCallbackAsync(IntPtr aPtr, uint aAsyncHandle);
    }

    public class Library
    {
        [DllImport ("ZappUpnp")]
        static extern int ZappLibraryInitialise(uint aInitParams);
        [DllImport("ZappUpnp")]
        static extern int ZappLibraryInitialiseMinimal(uint aInitParams);
        [DllImport ("ZappUpnp")]
        static extern void ZappLibraryStartCp();
        [DllImport ("ZappUpnp")]
        static extern void ZappLibraryStartDv();
        [DllImport ("ZappUpnp")]
        static extern void ZappLibraryStartCombined();
        [DllImport ("ZappUpnp")]
        static extern void ZappLibraryClose();
        [DllImport("ZappUpnp")]
        static extern void ZappFree(IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern uint ZappNetworkInterfaceAddress(uint aNif);
        [DllImport("ZappUpnp")]
        static extern uint ZappNetworkInterfaceSubnet(uint aNif);
        [DllImport("ZappUpnp", CallingConvention = CallingConvention.StdCall, EntryPoint = "ZappNetworkInterfaceName", ExactSpelling = false)]
        static extern IntPtr ZappNetworkInterfaceName(uint aNif);
        [DllImport("ZappUpnp")]
        static extern uint ZappSubnetListCreate();
        [DllImport("ZappUpnp")]
        static extern uint ZappSubnetListSize(uint aList);
        [DllImport("ZappUpnp")]
        static extern uint ZappSubnetAt(uint aList, uint aIndex);
        [DllImport("ZappUpnp")]
        static extern void ZappSubnetListDestroy(uint aList);
        [DllImport("ZappUpnp")]
        static extern void ZappSetCurrentSubnet(uint aSubnet);
        [DllImport("ZappUpnp")]
        static extern void ZappSetDefaultSubnet();
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetFreeExternalCallback(uint aParams, CallbackFreeMemory aCallback);

        private delegate void CallbackFreeMemory(IntPtr aPtr);

        private CallbackFreeMemory iCallbackFreeMemory;

        public void Initialise(ref InitParams aParams)
        {
            iCallbackFreeMemory = new CallbackFreeMemory(FreeMemory);
            ZappInitParamsSetFreeExternalCallback(aParams.Handle, iCallbackFreeMemory);
            ZappLibraryInitialise(aParams.Handle);
        }

        public int InitialiseMinimal(uint aInitParams)
        {
            return ZappLibraryInitialiseMinimal(aInitParams);
        }

        public void StartCp()
        {
            ZappLibraryStartCp();
        }

        public void StartDv()
        {
            ZappLibraryStartDv();
        }

        public void StartCombined()
        {
            ZappLibraryStartCombined();
        }

        public void Close()
        {
            ZappLibraryClose();
        }

        public void Free(IntPtr aPtr)
        {
            ZappFree(aPtr);
        }

        public uint NetworkInterfaceAddress(uint aNif)
        {
            return ZappNetworkInterfaceAddress(aNif);
        }

        public uint NetworkInterfaceSubnet(uint aNif)
        {
            return ZappNetworkInterfaceSubnet(aNif);
        }

        public IntPtr NetworkInterfaceName(uint aNif)
        {
            return ZappNetworkInterfaceName(aNif);
        }

        public uint SubnetListCreate()
        {
            return ZappSubnetListCreate();
        }

        public uint SubnetListSize(uint aList)
        {
            return ZappSubnetListSize(aList);
        }

        public uint SubnetAt(uint aList, uint aIndex)
        {
            return ZappSubnetAt(aList, aIndex);
        }

        public void SubnetListDestroy(uint aList)
        {
            ZappSubnetListDestroy(aList);
        }

        public void SetCurrentSubnet(uint aSubnet)
        {
            ZappSetCurrentSubnet(aSubnet);
        }

        public void SetDefaultSubnet()
        {
            ZappSetDefaultSubnet();
        }

        private void FreeMemory(IntPtr aPtr)
        {
            Marshal.FreeHGlobal(aPtr);
        }
    }
}
