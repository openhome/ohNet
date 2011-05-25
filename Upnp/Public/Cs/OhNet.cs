using System;
using System.Runtime.InteropServices;

namespace OpenHome.Net.Core
{
    /// <summary>
    /// Initialisation options
    /// </summary>
    /// <remarks>Most options apply equally to Control Point and Device stacks.
    /// Any functions that are specific to a particular stack include either 'Cp' or 'Dv'</remarks>
    public class InitParams
    {
        public delegate void OhNetCallback(IntPtr aPtr);
        public delegate void OhNetCallbackMsg(IntPtr aPtr, string aMsg);
        public delegate void OhNetCallbackAsync(IntPtr aPtr, IntPtr aAsyncHandle);

        public OhNetCallbackMsg LogOutput { get; set; }
        /// <summary>
        /// A callback which will be run if the library encounters an error it cannot recover from
        /// </summary>
        /// <remarks>Suggested action if this is called is to exit the process and restart the library and its owning application.
        /// 
        /// The string passed to the callback is an error message so would be useful to log.</remarks>
        public OhNetCallbackMsg FatalErrorHandler { private get; set; }
        public OhNetCallbackAsync AsyncBeginHandler { private get; set; }
        public OhNetCallbackAsync AsyncEndHandler { private get; set; }
        public OhNetCallbackAsync AsyncErrorHandler { private get; set; }
        public uint DefaultSubnet { get; set; }
        public OhNetCallback SubnetChangedListener { private get; set; }

        /// <summary>
        /// A timeout for TCP connections in milliseconds. Must be >0
        /// </summary>
        public uint TcpConnectTimeoutMs { get; set; }

        /// <summary>
        /// The time in seconds that msearch responses should be spread out over. Should be between 1 and 5 (inclusive).
        /// </summary>
        public uint MsearchTimeSecs { get; set; }

        /// <summary>
        /// Set the time-to-live value for msearches
        /// </summary>
        public uint MsearchTtl { get; set; }

        /// <summary>
        /// Set the number of threads which should be dedicated to eventing (handling updates
        /// to subscribed state variables).
        /// </summary>
        public uint NumEventSessionThreads { get; set; }

        /// <summary>
        /// Set the number of threads which should be dedicated to fetching device/service XML
        /// </summary>
        /// <remarks>A higher number of threads will allow faster population of device lists but
        /// will also require more system resources</remarks>
        public uint NumXmlFetcherThreads { get; set; }

        /// <summary>
        /// Set the number of threads which should be dedicated to invoking actions on devices
        /// </summary>
        /// <remarks>A higher number of threads will allow faster population of device lists
        /// but will also require more system resources</remarks>
        public uint NumActionInvokerThreads { get; set; }

        /// <summary>
        /// Set the number of invocations (actions) which should be pre-allocated
        /// </summary>
        /// <remarks>If more that this number are pending, the additional attempted invocations
        /// will block until a pre-allocated slot becomes clear.
        /// 
        /// A higher number of invocations will decrease the likelihood and duration of
        /// any UI-level delays but will also increase the peaks in RAM requirements.</remarks>
        public uint NumInvocations { get; set; }

        /// <summary>
        /// Set the number of threads which should be dedicated to (un)subscribing
        /// to state variables on a service + device
        /// </summary>
        /// <remarks>A higher number of threads will allow faster population of device lists
        /// but will also require more system resources</remarks>
        public uint NumSubscriberThreads { get; set; }

        /// <summary>
        /// Set the maximim time in milliseconds to wait before rejecting an event update from
        /// an unknown source
        /// </summary>
        /// <remarks>It is possible for initial information on state variables to arrive before
        /// a subscription is noted as complete.  Waiting a short while before rejecting events
        /// from unknown sources decreases the chances of missing the initial event from a subscription</remarks>
        public uint PendingSubscriptionTimeoutMs { get; set; }

        /// <summary>
        /// Set the maximum time in seconds between device announcements for the device stack
        /// </summary>
        /// <remarks>This value will appear in the maxage header for UPnP advertisements</remarks>
        public uint DvMaxUpdateTimeSecs { get; set; }

        /// <summary>
        /// Set the number of threads which should be dedicated to processing
        /// control/eventing/presentation requests.
        /// </summary>
        /// <remarks>A higher number of threads may allow faster response to multiple clients
        /// making concurrent requests but will also require more system resources.</remarks>
        public uint DvNumServerThreads { get; set; }

        /// <summary>
        /// Set the number of threads which should be dedicated to publishing
        /// changes to state variables on a service + device
        /// </summary>
        /// <remarks>A higher number of threads will allow faster publication of changes
        /// but will also require more system resources</remarks>
        public uint DvNumPublisherThreads { get; set; }

        /// <summary>
        /// Set the number of threads which will be dedicated to published
        /// changes to state variables via WebSockets
        /// </summary>
        /// <remarks>One thread will be used per active (web browser) connection so a higher
        /// number of threads will allow more concurrent clients but will also
        /// require more system resources. Can be 0 for clients who do not require HTML5
        /// support</remarks>
        public uint DvNumWebSocketThreads { get; set; }

        /// <summary>Get/set the tcp port number the WebSocket server will run on.</summary>
        /// <remarks>The default value is 0 (meaning that the OS will assign a port).
        ///  You should question your design if you need to use this.</remarks>
        public uint DvWebSocketPort { get; set; }

        /// <summary>
        /// Limit the library to using only the loopback network interface
        /// </summary>
        /// <remarks>Useful for testing but not expected to be used in production code</remarks>
        public bool UseLoopbackNetworkInterface { get; set; }

        /// <summary>
        /// Enable use of Bonjour.
        /// </summary>
        /// <remarks>All DvDevice instances with an IResourceManager will be published using Bonjour.
        /// If a device sets the "Upnp.MdnsHostName" attribute, its presentation will be available via http://[hostname].local.
        /// Behaviour when more than one DvDevice sets the "MdnsHostName" attribute is undefined.
        /// Note that enabling Bonjour will cause the device stack to run a http server on port 80, requiring root privileges on linux.</remarks>
        public bool DvEnableBonjour { get; set; }

        [DllImport ("ohNet")]
        static extern IntPtr OhNetInitParamsCreate();
        [DllImport ("ohNet")]
        static extern void OhNetInitParamsDestroy(IntPtr aParams);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetLogOutput(IntPtr aParams, OhNetCallbackMsg aCallback, IntPtr aPtr);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetFatalErrorHandler(IntPtr aParams, OhNetCallbackMsg aCallback, IntPtr aPtr);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetAsyncBeginHandler(IntPtr aParams, OhNetCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetAsyncEndHandler(IntPtr aParams, OhNetCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetAsyncErrorHandler(IntPtr aParams, OhNetCallbackAsync aCallback, IntPtr aPtr);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetDefaultSubnet(IntPtr aParams, uint aSubnet);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetSubnetChangedListener(IntPtr aParams, OhNetCallback aCallback, IntPtr aPtr);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetTcpConnectTimeout(IntPtr aParams, uint aTimeoutMs);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetMsearchTime(IntPtr aParams, uint aSecs);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetMsearchTtl(IntPtr aParams, uint aTtl);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetNumEventSessionThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetNumXmlFetcherThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetNumActionInvokerThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetNumInvocations(IntPtr aParams, uint aNumInvocations);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetNumSubscriberThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetPendingSubscriptionTimeout(IntPtr aParams, uint aTimeoutMs);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetDvMaxUpdateTime(IntPtr aParams, uint aSecs);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetDvNumServerThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetDvNumPublisherThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetDvNumWebSocketThreads(IntPtr aParams, uint aNumThreads);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetDvWebSocketPort(IntPtr aParams, uint aPort);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetDvEnableBonjour(IntPtr aParams);
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetUseLoopbackNetworkInterface(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsTcpConnectTimeoutMs(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsMsearchTimeSecs(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsMsearchTtl(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsNumEventSessionThreads(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsNumXmlFetcherThreads(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsNumActionInvokerThreads(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsNumInvocations(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsNumSubscriberThreads(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsPendingSubscriptionTimeoutMs(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsDvMaxUpdateTimeSecs(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsDvNumServerThreads(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsDvNumPublisherThreads(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsDvNumWebSocketThreads(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsDvWebSocketPort(IntPtr aParams);
        [DllImport("ohNet")]
        static extern uint OhNetInitParamsDvIsBonjourEnabled(IntPtr aParams);

        private static void DefaultActionFunction()
        {
            throw new InvalidOperationException("This is a sentinel value and shouldn't actually be invoked.");
        }
        // These delegates are stored in the callback properties. If they are still there
        // when we come to generate the native InitParams, we don't write anything into it
        // and keep whatever value it has. Using this as a sentinel instead of null is
        // useful because it allows the user to write null to the property and have it
        // properly passed through to the library.
        private static readonly OhNetCallback DefaultCallback = aPtr => DefaultActionFunction();
        private static readonly OhNetCallbackMsg DefaultCallbackMsg = (aPtr, aMsg) => DefaultActionFunction();
        private static readonly OhNetCallbackAsync DefaultCallbackAsync = (aPtr, aAsyncHandle) => DefaultActionFunction();

        public InitParams()
        {
            IntPtr defaultParams = OhNetInitParamsCreate();
            
            LogOutput = DefaultCallbackMsg;
            FatalErrorHandler = DefaultCallbackMsg;
            AsyncBeginHandler = DefaultCallbackAsync;
            AsyncEndHandler = DefaultCallbackAsync;
            AsyncErrorHandler = DefaultCallbackAsync;
            DefaultSubnet = 0; // FIXME: No getter?
            SubnetChangedListener = DefaultCallback;
            TcpConnectTimeoutMs = OhNetInitParamsTcpConnectTimeoutMs(defaultParams); 
            MsearchTimeSecs = OhNetInitParamsMsearchTimeSecs(defaultParams); 
            MsearchTtl = OhNetInitParamsMsearchTtl(defaultParams); 
            NumEventSessionThreads = OhNetInitParamsNumEventSessionThreads(defaultParams); 
            NumXmlFetcherThreads = OhNetInitParamsNumXmlFetcherThreads(defaultParams); 
            NumActionInvokerThreads = OhNetInitParamsNumActionInvokerThreads(defaultParams); 
            NumInvocations = OhNetInitParamsNumInvocations(defaultParams); 
            NumSubscriberThreads = OhNetInitParamsNumSubscriberThreads(defaultParams); 
            PendingSubscriptionTimeoutMs = OhNetInitParamsPendingSubscriptionTimeoutMs(defaultParams); 
            DvMaxUpdateTimeSecs = OhNetInitParamsDvMaxUpdateTimeSecs(defaultParams); 
            DvNumServerThreads = OhNetInitParamsDvNumServerThreads(defaultParams); 
            DvNumPublisherThreads = OhNetInitParamsDvNumPublisherThreads(defaultParams);
            DvNumWebSocketThreads = OhNetInitParamsDvNumWebSocketThreads(defaultParams);
            DvWebSocketPort = OhNetInitParamsDvWebSocketPort(defaultParams); 
            UseLoopbackNetworkInterface = false; // FIXME: No getter?
            DvEnableBonjour = OhNetInitParamsDvIsBonjourEnabled(defaultParams) != 0; 

            OhNetInitParamsDestroy(defaultParams);
        }
        internal IntPtr AllocNativeInitParams(IntPtr aCallbackPtr)
        {
            IntPtr nativeParams = OhNetInitParamsCreate();

            if (LogOutput != DefaultCallbackMsg)
            {
                OhNetInitParamsSetLogOutput(nativeParams, LogOutput, aCallbackPtr);
            }
            if (FatalErrorHandler != DefaultCallbackMsg)
            {
                OhNetInitParamsSetFatalErrorHandler(nativeParams, FatalErrorHandler, aCallbackPtr);
            }
            if (AsyncBeginHandler != DefaultCallbackAsync)
            {
                OhNetInitParamsSetAsyncBeginHandler(nativeParams, AsyncBeginHandler, aCallbackPtr);
            }
            if (AsyncEndHandler != DefaultCallbackAsync)
            {
                OhNetInitParamsSetAsyncEndHandler(nativeParams, AsyncEndHandler, aCallbackPtr);
            }
            if (AsyncErrorHandler != DefaultCallbackAsync)
            {
                OhNetInitParamsSetAsyncErrorHandler(nativeParams, AsyncErrorHandler, aCallbackPtr);
            }
            OhNetInitParamsSetDefaultSubnet(nativeParams, DefaultSubnet);
            if (SubnetChangedListener != DefaultCallback)
            {
                OhNetInitParamsSetSubnetChangedListener(nativeParams, SubnetChangedListener, aCallbackPtr);
            }
            OhNetInitParamsSetTcpConnectTimeout(nativeParams, TcpConnectTimeoutMs);
            OhNetInitParamsSetMsearchTime(nativeParams, MsearchTimeSecs);
            OhNetInitParamsSetMsearchTtl(nativeParams, MsearchTtl);
            OhNetInitParamsSetNumEventSessionThreads(nativeParams, NumEventSessionThreads);
            OhNetInitParamsSetNumXmlFetcherThreads(nativeParams, NumXmlFetcherThreads);
            OhNetInitParamsSetNumActionInvokerThreads(nativeParams, NumActionInvokerThreads);
            OhNetInitParamsSetNumInvocations(nativeParams, NumInvocations);
            OhNetInitParamsSetNumSubscriberThreads(nativeParams, NumSubscriberThreads);
            OhNetInitParamsSetPendingSubscriptionTimeout(nativeParams, PendingSubscriptionTimeoutMs);
            OhNetInitParamsSetDvMaxUpdateTime(nativeParams, DvMaxUpdateTimeSecs);
            OhNetInitParamsSetDvNumServerThreads(nativeParams, DvNumServerThreads);
            OhNetInitParamsSetDvNumPublisherThreads(nativeParams, DvNumPublisherThreads);
            OhNetInitParamsSetDvNumWebSocketThreads(nativeParams, DvNumWebSocketThreads);
            OhNetInitParamsSetDvWebSocketPort(nativeParams, DvWebSocketPort);
            if (DvEnableBonjour)
            {
                OhNetInitParamsSetDvEnableBonjour(nativeParams);
            }
            if (UseLoopbackNetworkInterface)
            {
                OhNetInitParamsSetUseLoopbackNetworkInterface(nativeParams);
            }
            return nativeParams;
        }
        internal static void FreeNativeInitParams(IntPtr aNativeInitParams)
        {
            OhNetInitParamsDestroy(aNativeInitParams);
        }
    }

    [Serializable]
    public class LibraryException : Exception
    {
        public LibraryException() { }
        public LibraryException(string message) : base(message) { }
        public LibraryException(string message, Exception inner) : base(message, inner) { }
        protected LibraryException(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context)
            : base(info, context) { }
    }



    /// <summary>
    /// A control-point stack. Pre-requisite for creating a device-list
    /// factory.
    /// </summary>
    public class ControlPointStack
    {
        // Constructor is not public - obtain an instance from Library.
        internal ControlPointStack()
        {
        }
    }

    /// <summary>
    /// A device stack. Pre-requisite for creating a device factory.
    /// </summary>
    public class DeviceStack
    {
        // Constructor is not public - obtain an instance from Library.
        internal DeviceStack()
        {
        }
    }

    /// <summary>
    /// Combined control-point and device stacks.
    /// </summary>
    public class CombinedStack
    {
        /// <summary>
        /// Provides access to the ControlPointStack to create a device-list
        /// factory.
        /// </summary>
        public ControlPointStack ControlPointStack { get; private set; }

        /// <summary>
        /// Provides access to the DeviceStack to create a device factory.
        /// </summary>
        public DeviceStack DeviceStack { get; private set; }

        // Constructor is not public - obtain an instance from Library.
        internal CombinedStack()
        {
            ControlPointStack = new ControlPointStack();
            DeviceStack = new DeviceStack();
        }
    }

    /// <summary>
    /// Initialisation and finalisation of this library, plus utility functions
    /// </summary>
    public class Library : IDisposable
    {
        [DllImport ("ohNet")]
        static extern int OhNetLibraryInitialise(IntPtr aInitParams);
        [DllImport("ohNet")]
        static extern int OhNetLibraryInitialiseMinimal(IntPtr aInitParams);
        [DllImport ("ohNet")]
        static extern void OhNetLibraryStartCp();
        [DllImport ("ohNet")]
        static extern void OhNetLibraryStartDv();
        [DllImport ("ohNet")]
        static extern void OhNetLibraryStartCombined();
        [DllImport ("ohNet")]
        static extern void OhNetLibraryClose();
        [DllImport("ohNet")]
        static extern void OhNetFree(IntPtr aPtr);
        [DllImport("ohNet")]
        static extern uint OhNetNetworkInterfaceAddress(IntPtr aNif);
        [DllImport("ohNet")]
        static extern uint OhNetNetworkInterfaceSubnet(IntPtr aNif);
        [DllImport("ohNet", CallingConvention = CallingConvention.StdCall, EntryPoint = "OhNetNetworkInterfaceName", ExactSpelling = false)]
        static extern IntPtr OhNetNetworkInterfaceName(IntPtr aNif);
        [DllImport("ohNet")]
        static extern IntPtr OhNetSubnetListCreate();
        [DllImport("ohNet")]
        static extern uint OhNetSubnetListSize(IntPtr aList);
        [DllImport("ohNet")]
        static extern uint OhNetSubnetAt(IntPtr aList, uint aIndex);
        [DllImport("ohNet")]
        static extern void OhNetSubnetListDestroy(IntPtr aList);
        [DllImport("ohNet")]
        static extern void OhNetSetCurrentSubnet(uint aSubnet);
        [DllImport("ohNet")]
        static extern void OhNetSetDefaultSubnet();
        [DllImport("ohNet")]
        static extern void OhNetInitParamsSetFreeExternalCallback(IntPtr aParams, CallbackFreeMemory aCallback);

        private bool iIsDisposed;

        private delegate void CallbackFreeMemory(IntPtr aPtr);

        private CallbackFreeMemory iCallbackFreeMemory;

        /// <summary>
        /// Initialise the library
        /// </summary>
        /// <remarks>Must be called before any other library function.</remarks>
        public void Initialise(InitParams aParams)
        {
            IntPtr nativeInitParams = aParams.AllocNativeInitParams(IntPtr.Zero);
            iCallbackFreeMemory = new CallbackFreeMemory(FreeMemory);
            OhNetInitParamsSetFreeExternalCallback(nativeInitParams, iCallbackFreeMemory);
            if (0 != OhNetLibraryInitialise(nativeInitParams))
            {
                InitParams.FreeNativeInitParams(nativeInitParams);
                throw new LibraryException();
            }
        }

        public static Library Create(InitParams aParams)
        {
            Library instance = new Library();
            instance.Initialise(aParams);
            return instance;
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
            if (0 != OhNetLibraryInitialiseMinimal(aInitParams))
            {
                throw new LibraryException();
            }
        }

        /// <summary>
        /// Start the library as a UPnP control point stack
        /// </summary>
        /// <returns>
        /// A control-point stack. Can be used to create device list factories.
        /// </returns>
        public ControlPointStack StartCp()
        {
            OhNetLibraryStartCp();
            return new ControlPointStack();
        }

        /// <summary>
        /// Start the library as a UPnP device stack
        /// </summary>
        /// <returns>
        /// A device stack. Can be used to create device factories.
        /// </returns>
        public DeviceStack StartDv()
        {
            OhNetLibraryStartDv();
            return new DeviceStack();
        }

        /// <summary>
        /// Start the library as both UPnP control point and device stacks
        /// </summary>
        public CombinedStack StartCombined()
        {
            OhNetLibraryStartCombined();
            return new CombinedStack();
        }

        /// <summary>
        /// Close the UPnP library
        /// </summary>
        /// <remarks>No more library functions should be called after this.</remarks>
        public void Close()
        {
            OhNetLibraryClose();
        }

        /// <summary>
        /// Free memory returned by native code
        /// </summary>
        /// <param name="aPtr">IntPtr returned by native code which is documented as requiring explicit destruction</param>
        public void Free(IntPtr aPtr)
        {
            OhNetFree(aPtr);
        }

        /// <summary>
        /// Get the ip address for a given network interface
        /// </summary>
        /// <param name="aNif">Handle returned by SubnetAt()</param>
        /// <returns>IPv4 address in network byte order</returns>
        public uint NetworkInterfaceAddress(IntPtr aNif)
        {
            return OhNetNetworkInterfaceAddress(aNif);
        }

        /// <summary>
        /// Get the subnet address for a given network interface
        /// </summary>
        /// <param name="aNif">Handle returned by SubnetAt()</param>
        /// <returns>IPv4 address in network byte order</returns>
        public uint NetworkInterfaceSubnet(IntPtr aNif)
        {
            return OhNetNetworkInterfaceSubnet(aNif);
        }

        /// <summary>
        /// Get the name for a given network interface
        /// </summary>
        /// <param name="aNif">Handle returned by SubnetAt()</param>
        /// <returns>Pointer to a nul-terminated character array.  Caller is responsible for Free()ing this</returns>
        public IntPtr NetworkInterfaceName(IntPtr aNif)
        {
            return OhNetNetworkInterfaceName(aNif);
        }

        /// <summary>
        /// Create a vector of the available subnets
        /// </summary>
        /// <returns>Subnet list handle.  Caller must later call SubnetListDestroy()</returns>
        public IntPtr SubnetListCreate()
        {
            return OhNetSubnetListCreate();
        }

        /// <summary>
        /// Query the number of items in a subnet list
        /// </summary>
        /// <param name="aList">Subnet list handle returned by SubnetListCreate()</param>
        /// <returns>The number of items in the subnet</returns>
        public uint SubnetListSize(IntPtr aList)
        {
            return OhNetSubnetListSize(aList);
        }

        /// <summary>
        /// Get a handle to a particular subnet from a subnet list
        /// </summary>
        /// <param name="aList">Subnet list handle returned by SubnetListCreate()</param>
        /// <param name="aIndex">Index of the list item to get a handle to (0..SubnetListSize()-1)</param>
        /// <returns>Handle to the subnet</returns>
        public uint SubnetAt(IntPtr aList, uint aIndex)
        {
            return OhNetSubnetAt(aList, aIndex);
        }

        /// <summary>
        /// Destroy a subnet list
        /// </summary>
        /// <param name="aList">Subnet list handle returned by SubnetListCreate()</param>
        public void SubnetListDestroy(IntPtr aList)
        {
            OhNetSubnetListDestroy(aList);
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
            OhNetSetCurrentSubnet(aSubnet);
        }

        /// <summary>
        /// Clear any subnet previously specified using SetCurrentSubnet() or InitialisationParams::SetDefaultSubnet().
        /// OS-specified defaults will be used instead
        /// </summary>
        /// <remarks>Device lists and subscriptions will be automatically updated if necessary</remarks>
        public void SetDefaultSubnet()
        {
            OhNetSetDefaultSubnet();
        }

        private void FreeMemory(IntPtr aPtr)
        {
            Marshal.FreeHGlobal(aPtr);
        }

        public void Dispose()
        {
            if (!iIsDisposed)
            {
                iIsDisposed = true;
                Close();
            }
        }
    }
}
