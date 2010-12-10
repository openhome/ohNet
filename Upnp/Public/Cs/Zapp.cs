using System;
using System.Runtime.InteropServices;

namespace Zapp.Core
{
    /// <summary>
    /// Initialisation options
    /// </summary>
    /// <remarks>Most options apply equally to Control Point and Device stacks.
    /// Any functions that are specific to a particular stack include either 'Cp' or 'Dv'</remarks>
    public class InitParams :IDisposable
    {
        [DllImport ("ZappUpnp")]
        static extern IntPtr ZappInitParamsCreate();
        [DllImport ("ZappUpnp")]
        static extern void ZappInitParamsDestroy(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetLogOutput(IntPtr aParams, ZappCallbackMsg aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetFatalErrorHandler(IntPtr aParams, ZappCallbackMsg aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetAsyncBeginHandler(IntPtr aParams, ZappCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetAsyncEndHandler(IntPtr aParams, ZappCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetAsyncErrorHandler(IntPtr aParams, ZappCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetDefaultSubnet(IntPtr aParams, uint aSubnet);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetSubnetChangedListener(IntPtr aParams, ZappCallback aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetTcpConnectTimeout(IntPtr aParams, uint aTimeoutMs);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetMsearchTime(IntPtr aParams, uint aSecs);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetMsearchTtl(IntPtr aParams, uint aTtl);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumEventSessionThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumXmlFetcherThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumActionInvokerThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumInvocations(IntPtr aParams, uint aNumInvocations);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetNumSubscriberThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetPendingSubscriptionTimeout(IntPtr aParams, uint aTimeoutMs);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetDvMaxUpdateTime(IntPtr aParams, uint aSecs);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetDvNumPublisherThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetDvNumWebSocketThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetUseLoopbackNetworkInterface(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsTcpConnectTimeoutMs(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsMsearchTimeSecs(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsMsearchTtl(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumEventSessionThreads(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumXmlFetcherThreads(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumActionInvokerThreads(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumInvocations(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsNumSubscriberThreads(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsPendingSubscriptionTimeoutMs(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsDvMaxUpdateTimeSecs(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsDvNumPublisherThreads(IntPtr aParams);
        [DllImport("ZappUpnp")]
        static extern int ZappInitParamsDvNumWebSocketThreads(IntPtr aParams);

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

        /// <summary>
        /// Set a callback which will be run if the library encounters an error it cannot recover from
        /// </summary>
        /// <remarks>Suggested action if this is called is to exit the process and restart the library and its owning application.
        /// 
        /// The string passed to the callback is an error message so would be useful to log.</remarks>
        /// <param name="aCallback">Callback to run</param>
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

        /// <summary>
        /// Set a timeout for TCP connections
        /// </summary>
        /// <param name="aTimeoutMs">Timeout in milliseconds.  Must be >0</param>
        public void SetTcpConnectTimeout(uint aTimeoutMs)
        {
            ZappInitParamsSetTcpConnectTimeout(iHandle, aTimeoutMs);
        }

        /// <summary>
        /// Set the time that msearch responses should be spread out over
        /// </summary>
        /// <param name="aSecs">Time in seconds.  Should be between 1 and 5 (inclusive).</param>
        public void SetMsearchTime(uint aSecs)
        {
            ZappInitParamsSetMsearchTime(iHandle, aSecs);
        }

        /// <summary>
        /// Set the time-to-live value for msearches
        /// </summary>
        /// <param name="aTtl">Ttl value</param>
        public void SetMsearchTtl(uint aTtl)
        {
            ZappInitParamsSetMsearchTtl(iHandle, aTtl);
        }

        /// <summary>
        /// Set the number of threads which should be dedicated to eventing (handling updates
        /// to subscribed state variables)
        /// </summary>
        /// <param name="aNumThreads">Number of threads.  Must be >0</param>
        public void SetNumEventSessionThreads(uint aNumThreads)
        {
            ZappInitParamsSetNumEventSessionThreads(iHandle, aNumThreads);
        }

        /// <summary>
        /// Set the number of threads which should be dedicated to fetching device/service XML
        /// </summary>
        /// <remarks>A higher number of threads will allow faster population of device lists but
        /// will also require more system resources</remarks>
        /// <param name="aNumThreads">Number of threads.  Must be >0</param>
        public void SetNumXmlFetcherThreads(uint aNumThreads)
        {
            ZappInitParamsSetNumXmlFetcherThreads(iHandle, aNumThreads);
        }

        /// <summary>
        /// Set the number of threads which should be dedicated to invoking actions on devices
        /// </summary>
        /// <remarks>A higher number of threads will allow faster population of device lists
        /// but will also require more system resources</remarks>
        /// <param name="aNumThreads">Number of threads.  Must be >0</param>
        public void SetNumActionInvokerThreads(uint aNumThreads)
        {
            ZappInitParamsSetNumActionInvokerThreads(iHandle, aNumThreads);
        }

        /// <summary>
        /// Set the number of invocations (actions) which should be pre-allocated
        /// </summary>
        /// <remarks>If more that this number are pending, the additional attempted invocations
        /// will block until a pre-allocated slot becomes clear.
        /// 
        /// A higher number of invocations will decrease the likelihood and duration of
        /// any UI-level delays but will also increase the peaks in RAM requirements.</remarks>
        /// <param name="aNumInvocations">Number of invocations.  Must be >0</param>
        public void SetNumInvocations(uint aNumInvocations)
        {
            ZappInitParamsSetNumInvocations(iHandle, aNumInvocations);
        }

        /// <summary>
        /// Set the number of threads which should be dedicated to (un)subscribing
        /// to state variables on a service + device
        /// </summary>
        /// <remarks>A higher number of threads will allow faster population of device lists
        /// but will also require more system resources</remarks>
        /// <param name="aNumThreads">Number of threads.  Must be >0</param>
        public void SetNumSubscriberThreads(uint aNumThreads)
        {
            ZappInitParamsSetNumSubscriberThreads(iHandle, aNumThreads);
        }

        /// <summary>
        /// Set the maximim time to wait before rejecting an event update from an unknown source
        /// </summary>
        /// <remarks>It is possible for initial information on state variables to arrive before
        /// a subscription is noted as complete.  Waiting a short while before rejecting events
        /// from unknown sources decreases the chances of missing the initial event from a subscription</remarks>
        /// <param name="aTimeoutMs">Time in milliseconds to wait before rejecting events</param>
        public void SetPendingSubscriptionTimeout(uint aTimeoutMs)
        {
            ZappInitParamsSetPendingSubscriptionTimeout(iHandle, aTimeoutMs);
        }

        /// <summary>
        /// Set the maximum time between device announcements for the device stack
        /// </summary>
        /// <remarks>This value will appear in the maxage header for UPnP advertisements</remarks>
        /// <param name="aSecs">Time in seconds</param>
        public void SetDvMaxUpdateTime(uint aSecs)
        {
            ZappInitParamsSetDvMaxUpdateTime(iHandle, aSecs);
        }

        /// <summary>
        /// Set the number of threads which should be dedicated to publishing
        /// changes to state variables on a service + device
        /// </summary>
        /// <remarks>A higher number of threads will allow faster publication of changes
        /// but will also require more system resources</remarks>
        /// <param name="aNumThreads"></param>
        public void SetDvNumPublisherThreads(uint aNumThreads)
        {
            ZappInitParamsSetDvNumPublisherThreads(iHandle, aNumThreads);
        }

        /// <summary>
        /// Set the number of threads which will be dedicated to published
        /// changes to state variables via WebSockets
        /// </summary>
        /// <remarks>One thread will be used per active (web browser) connection so a higher
        /// number of threads will allow more concurrent clients but will also
        /// require more system resources.</remarks>
        /// <param name="aNumThreads">Number of threads.  Can be 0 for clients who do not require HTML5 support</param>
        public void SetDvNumWebSocketThreads(uint aNumThreads)
        {
            ZappInitParamsSetDvNumWebSocketThreads(iHandle, aNumThreads);
        }

        /// <summary>
        /// Limit the library to using only the loopback network interface
        /// </summary>
        /// <remarks>Useful for testing but not expected to be used in production code</remarks>
        public void SetUseLoopbackNetworkInterface()
        {
            ZappInitParamsSetUseLoopbackNetworkInterface(iHandle);
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

        public int DvNumWebSocketThreads()
        {
            return ZappInitParamsDvNumWebSocketThreads(iHandle);
        }

        /// <summary>
        /// Destroy the underlying native object.  Must be called before Core.Library.Close().
        /// </summary>
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

        public IntPtr Handle
        {
            get
            {
                return iHandle;
            }
        }

        private IntPtr iHandle;
        protected GCHandle iGch;
        private bool iDisposed = false;

        public delegate void ZappCallback(IntPtr aPtr);
        public delegate void ZappCallbackMsg(IntPtr aPtr, string aMsg);
        public delegate void ZappCallbackAsync(IntPtr aPtr, IntPtr aAsyncHandle);
    }

    public class LibraryException : ApplicationException
    {
    }
    
    /// <summary>
    /// Initialisation and finalisation of this library, plus utility functions
    /// </summary>
    public class Library
    {
        [DllImport ("ZappUpnp")]
        static extern int ZappLibraryInitialise(IntPtr aInitParams);
        [DllImport("ZappUpnp")]
        static extern int ZappLibraryInitialiseMinimal(IntPtr aInitParams);
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
        static extern uint ZappNetworkInterfaceAddress(IntPtr aNif);
        [DllImport("ZappUpnp")]
        static extern uint ZappNetworkInterfaceSubnet(IntPtr aNif);
        [DllImport("ZappUpnp", CallingConvention = CallingConvention.StdCall, EntryPoint = "ZappNetworkInterfaceName", ExactSpelling = false)]
        static extern IntPtr ZappNetworkInterfaceName(IntPtr aNif);
        [DllImport("ZappUpnp")]
        static extern IntPtr ZappSubnetListCreate();
        [DllImport("ZappUpnp")]
        static extern uint ZappSubnetListSize(IntPtr aList);
        [DllImport("ZappUpnp")]
        static extern uint ZappSubnetAt(IntPtr aList, uint aIndex);
        [DllImport("ZappUpnp")]
        static extern void ZappSubnetListDestroy(IntPtr aList);
        [DllImport("ZappUpnp")]
        static extern void ZappSetCurrentSubnet(uint aSubnet);
        [DllImport("ZappUpnp")]
        static extern void ZappSetDefaultSubnet();
        [DllImport("ZappUpnp")]
        static extern void ZappInitParamsSetFreeExternalCallback(IntPtr aParams, CallbackFreeMemory aCallback);

        private delegate void CallbackFreeMemory(IntPtr aPtr);

        private CallbackFreeMemory iCallbackFreeMemory;

        /// <summary>
        /// Initialise the library
        /// </summary>
        /// <remarks>Must be called before any other library function.</remarks>
        /// <param name="aParams">Initialisation options.  Ownership of these passes to the library</param>
        public void Initialise(ref InitParams aParams)
        {
            iCallbackFreeMemory = new CallbackFreeMemory(FreeMemory);
            ZappInitParamsSetFreeExternalCallback(aParams.Handle, iCallbackFreeMemory);
            if (0 != ZappLibraryInitialise(aParams.Handle))
            {
                throw new LibraryException();
            }
        }

        /// <summary>
        /// Lightweight alternative to UpnpLibraryInitialise
        /// </summary>
        /// <remarks>Intended for unit tests which are useful to platform porting only.
        /// 
        /// No class APIs other than Close() can be called if this is used.</remarks>
        /// <param name="aInitParams">Initialisation options.  Ownership of these passes to the library.</param>
        public void InitialiseMinimal(IntPtr aInitParams)
        {
            if (0 != ZappLibraryInitialiseMinimal(aInitParams))
            {
                throw new LibraryException();
            }
        }

        /// <summary>
        /// Start the library as a UPnP control point stack
        /// </summary>
        public void StartCp()
        {
            ZappLibraryStartCp();
        }

        /// <summary>
        /// Start the library as a UPnP device stack
        /// </summary>
        public void StartDv()
        {
            ZappLibraryStartDv();
        }

        /// <summary>
        /// Start the library as both UPnP control point and device stacks
        /// </summary>
        public void StartCombined()
        {
            ZappLibraryStartCombined();
        }

        /// <summary>
        /// Close the UPnP library
        /// </summary>
        /// <remarks>No more library functions should be called after this.</remarks>
        public void Close()
        {
            ZappLibraryClose();
        }

        /// <summary>
        /// Free memory returned by native code
        /// </summary>
        /// <param name="aPtr">IntPtr returned by native code which is documented as requiring explicit destruction</param>
        public void Free(IntPtr aPtr)
        {
            ZappFree(aPtr);
        }

        /// <summary>
        /// Get the ip address for a given network interface
        /// </summary>
        /// <param name="aNif">Handle returned by SubnetAt()</param>
        /// <returns>IPv4 address in network byte order</returns>
        public uint NetworkInterfaceAddress(IntPtr aNif)
        {
            return ZappNetworkInterfaceAddress(aNif);
        }

        /// <summary>
        /// Get the subnet address for a given network interface
        /// </summary>
        /// <param name="aNif">Handle returned by SubnetAt()</param>
        /// <returns>IPv4 address in network byte order</returns>
        public uint NetworkInterfaceSubnet(IntPtr aNif)
        {
            return ZappNetworkInterfaceSubnet(aNif);
        }

        /// <summary>
        /// Get the name for a given network interface
        /// </summary>
        /// <param name="aNif">Handle returned by SubnetAt()</param>
        /// <returns>Pointer to a nul-terminated character array.  Caller is responsible for Free()ing this</returns>
        public IntPtr NetworkInterfaceName(IntPtr aNif)
        {
            return ZappNetworkInterfaceName(aNif);
        }

        /// <summary>
        /// Create a vector of the available subnets
        /// </summary>
        /// <returns>Subnet list handle.  Caller must later call SubnetListDestroy()</returns>
        public IntPtr SubnetListCreate()
        {
            return ZappSubnetListCreate();
        }

        /// <summary>
        /// Query the number of items in a subnet list
        /// </summary>
        /// <param name="aList">Subnet list handle returned by SubnetListCreate()</param>
        /// <returns>The number of items in the subnet</returns>
        public uint SubnetListSize(IntPtr aList)
        {
            return ZappSubnetListSize(aList);
        }

        /// <summary>
        /// Get a handle to a particular subnet from a subnet list
        /// </summary>
        /// <param name="aList">Subnet list handle returned by SubnetListCreate()</param>
        /// <param name="aIndex">Index of the list item to get a handle to (0..SubnetListSize()-1)</param>
        /// <returns>Handle to the subnet</returns>
        public uint SubnetAt(IntPtr aList, uint aIndex)
        {
            return ZappSubnetAt(aList, aIndex);
        }

        /// <summary>
        /// Destroy a subnet list
        /// </summary>
        /// <param name="aList">Subnet list handle returned by SubnetListCreate()</param>
        public void SubnetListDestroy(IntPtr aList)
        {
            ZappSubnetListDestroy(aList);
        }

        /// <summary>
        /// Set which subnet the library should use
        /// </summary>
        /// <remarks>Override any value set via InitialisationParams::SetDefaultSubnet.
        /// 
        /// Device lists and subscriptions will be automatically updated.
        /// 
        /// No other subnet will be selected if aSubnet is not available</remarks>
        /// <param name="aSubnet">Handle returned by SubnetAt()</param>
        public void SetCurrentSubnet(uint aSubnet)
        {
            ZappSetCurrentSubnet(aSubnet);
        }

        /// <summary>
        /// Clear any subnet previously specified using SetCurrentSubnet() or InitialisationParams::SetDefaultSubnet().
        /// OS-specified defaults will be used instead
        /// </summary>
        /// <remarks>Device lists and subscriptions will be automatically updated if necessary</remarks>
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
