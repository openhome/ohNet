using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
#if IOS
using ObjCRuntime;
#endif

namespace OpenHome.Net.Core
{
    /// <summary>
    /// Thrown when initialisation fails due to out of memory.
    /// </summary>
    public class ErrorNoMemory : Exception
    {
    }

    /// <summary>
    /// Thrown when initialisation fails due to an attempt to reuse a network address.
    /// </summary>
    /// <remarks>This may imply that another similarly configured instance of ohNet is already running.
    /// On Windows, it could also mean that too many instances of ohNet have been recently launched.</remarks>
    public class ErrorNetworkAddressInUse : Exception
    {
    }

    /// <summary>
    /// Thrown when initialisation fails due to any reason not covered by a more specific error above.
    /// </summary>
    public class ErrorGeneral : Exception
    {
    }

    /// <summary>
    /// A network adapter.
    /// </summary>
    public class NetworkAdapter
    {
        internal class CookieWrapper : IDisposable
        {
            public string AsString { get; private set; }
            public IntPtr AsCString { get; private set; }

            internal CookieWrapper(string aCookie, IntPtr aCString)
            {
                AsString = aCookie;
                AsCString = aCString;
            }
            public void Dispose()
            {
                lock (this)
                {
                    if (AsCString != IntPtr.Zero)
                    {
                        Marshal.FreeHGlobal(AsCString);
                        AsCString = IntPtr.Zero;
                    }
                }
            }
        }

#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetNetworkAdapterAddress(IntPtr aNif);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetNetworkAdapterSubnet(IntPtr aNif);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetNetworkAdapterMask(IntPtr aNif);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr OhNetNetworkAdapterName(IntPtr aNif);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr OhNetNetworkAdapterFullName(IntPtr aNif);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetNetworkAdapterAddRef(IntPtr aNif, IntPtr aCookie);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetNetworkAdapterRemoveRef(IntPtr aNif, IntPtr aCookie);

        private IntPtr iHandle;
        private List<CookieWrapper> iCookies;

        /// <summary>
        /// Constructor. Not intended for external use.
        /// </summary>
        /// <remarks>Network adapters should be constructed via the SubnetList classes.</remarks>
        /// <param name="aHandle">Handle to the underlying native network adapter.</param>
        public NetworkAdapter(IntPtr aHandle)
        {
            iHandle = aHandle;
            iCookies = new List<CookieWrapper>();
        }

        internal IntPtr Handle()
        {
            return iHandle;
        }

        /// <summary>
        /// Get the ip address for the network interface.
        /// </summary>
        /// <returns>IPv4 address in network byte order.</returns>
        public uint Address()
        {
            return OhNetNetworkAdapterAddress(iHandle);
        }

        /// <summary>
        /// Get the subnet address for the network interface.
        /// </summary>
        /// <returns>IPv4 subnet address in network byte order.</returns>
        public uint Subnet()
        {
            return OhNetNetworkAdapterSubnet(iHandle);
        }

        /// <summary>
        /// Get the netmask for the network interface.
        /// </summary>
        /// <returns>IPv4 netmask in network byte order.</returns>
        public uint Mask()
        {
            return OhNetNetworkAdapterMask(iHandle);
        }

        /// <summary>
        /// Get the name for a given network interface.
        /// </summary>
        /// <returns>String containing name of the adapter.</returns>
        public string Name()
        {
            IntPtr cStr = OhNetNetworkAdapterName(iHandle);
            string name = InteropUtils.PtrToStringUtf8(cStr);
            // Library.Free(cStr) not necessary because a copy is not allocated by the underlying NetworkAdapter object
            return name;
        }

        /// <summary>
        /// Get the full name for a given network interface.
        /// </summary>
        /// <returns>String in the form a.b.c.d (name).</returns>
        public string FullName()
        {
            IntPtr cStr = OhNetNetworkAdapterFullName(iHandle);
            string name = InteropUtils.PtrToStringUtf8(cStr);
            Library.Free(cStr);
            return name;
        }

        /// <summary>
        /// Claim a reference to the network adapter.
        /// </summary>
        /// <remarks>Can only be called from code that can guarantee another reference is already held.
        /// Each call to AddRef() must later have exactly one matching call to RemoveRef().</remarks>
        public void AddRef(string aCookie)
        {
            IntPtr cookie = InteropUtils.StringToHGlobalUtf8(aCookie);
            OhNetNetworkAdapterAddRef(iHandle, cookie);
            AddManagedCookie(aCookie, cookie);
        }

        internal CookieWrapper AddManagedCookie(string aCookie, IntPtr aCString)
        {
            CookieWrapper cookie = new CookieWrapper(aCookie, aCString);
            lock (this)
            {
                iCookies.Add(cookie);
            }
            return cookie;
        }

        /// <summary>
        /// Remove a reference to the network adapter.
        /// </summary>
        /// <remarks>Removing the final reference causes the network adapter to be deleted.</remarks>
        public void RemoveRef(string aCookie)
        {
            CookieWrapper cookie = null;
            lock (this)
            {
                for (int i = 0; i < iCookies.Count; i++)
                {
                    if (iCookies[i].AsString == aCookie)
                    {
                        cookie = iCookies[i];
                        iCookies.RemoveAt(i);
                        break;
                    }
                }
            }
            if (cookie == null)
                throw new ArgumentException();
            OhNetNetworkAdapterRemoveRef(iHandle, cookie.AsCString);
            cookie.Dispose();
        }
    }

    public class Listener : IDisposable
    {
        protected Listener()
        {
            iGch = GCHandle.Alloc(this);
        }

        public void Dispose()
        {
            if(iGch.IsAllocated)
            {
                iGch.Free();
            }
        }

        public IntPtr Handle()
        {
            return GCHandle.ToIntPtr(iGch);
        }

        private GCHandle iGch;
    }

    public class ChangedListener : Listener
    {
        public ChangedListener(InitParams.ChangeHandler aHandler)
        {
            iHandler = aHandler;
            Callback = new InitParams.OhNetCallback(Changed);
        }

        public InitParams.OhNetCallback Callback { get; private set; }

#if IOS
        [MonoPInvokeCallback (typeof (InitParams.OhNetCallback))]
#endif
        public static void Changed(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            ChangedListener listener = (ChangedListener)gch.Target;
            if(listener.iHandler != null)
            {
                listener.iHandler();
            }
        }

        private InitParams.ChangeHandler iHandler;
    }

    public class MessageListener : Listener
    {
        public MessageListener(InitParams.MessageHandler aHandler)
        {
            iHandler = aHandler;
            Callback = new InitParams.OhNetCallbackMsg(Message);
        }

        public InitParams.OhNetCallbackMsg Callback { get; private set; }

#if IOS
        [MonoPInvokeCallback (typeof (InitParams.OhNetCallbackMsg))]
#endif
        public static void Message(IntPtr aPtr, string aMessage)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            MessageListener listener = (MessageListener)gch.Target;
            if(listener.iHandler != null)
            {
                listener.iHandler(aMessage);
            }
        }

        private InitParams.MessageHandler iHandler;
    }

    public class NetworkAdapterListener : Listener
    {
        public NetworkAdapterListener(InitParams.NetworkAdapterHandler aHandler)
        {
            iHandler = aHandler;
            Callback = new InitParams.OhNetCallbackNetworkAdapter(NetworkAdapter);
        }

        public InitParams.OhNetCallbackNetworkAdapter Callback { get; private set; }

#if IOS
        [MonoPInvokeCallback (typeof (InitParams.OhNetCallbackNetworkAdapter))]
#endif
        public static void NetworkAdapter(IntPtr aPtr, IntPtr aAdapter)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            NetworkAdapterListener listener = (NetworkAdapterListener)gch.Target;
            NetworkAdapter adapter = new NetworkAdapter(aAdapter);
            if(listener.iHandler != null)
            {
                listener.iHandler(adapter);
            }
        }

        private InitParams.NetworkAdapterHandler iHandler;
    }

    public class AsyncListener : Listener
    {
        public AsyncListener(InitParams.AsyncHandler aHandler)
        {
            iHandler = aHandler;
            Callback = new InitParams.OhNetCallbackAsync(AsyncListenerCallback);
        }

        public InitParams.OhNetCallbackAsync Callback { get; private set; }

#if IOS
        [MonoPInvokeCallback (typeof (InitParams.OhNetCallbackAsync))]
#endif
        public static void AsyncListenerCallback(IntPtr aPtr, IntPtr aAsyncHandle)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            AsyncListener listener = (AsyncListener)gch.Target;
            if(listener.iHandler != null)
            {
                listener.iHandler(aAsyncHandle);
            }
        }

        private InitParams.AsyncHandler iHandler;
    }

    /// <summary>
    /// Initialisation options
    /// </summary>
    /// <remarks>Most options apply equally to Control Point and Device stacks.
    /// Any functions that are specific to a particular stack include either 'Cp' or 'Dv'</remarks>
    public class InitParams
    {
        public delegate void ChangeHandler();
        public delegate void MessageHandler(string aMessage);
        public delegate void NetworkAdapterHandler(NetworkAdapter aAdapter);
        public delegate void AsyncHandler(IntPtr aAsyncHandle);

        public delegate void OhNetCallback(IntPtr aPtr);
        public delegate void OhNetCallbackNetworkAdapter(IntPtr aPtr, IntPtr aAdapter);
        public delegate void OhNetCallbackMsg(IntPtr aPtr, string aMsg);
        public delegate void OhNetCallbackAsync(IntPtr aPtr, IntPtr aAsyncHandle);

        public MessageListener LogOutput { get; set; }
        /// <summary>
        /// A callback which will be run if the library encounters an error it cannot recover from
        /// </summary>
        /// <remarks>Suggested action if this is called is to exit the process and restart the library and its owning application.
        ///
        /// The string passed to the callback is an error message so would be useful to log.</remarks>
        public MessageListener FatalErrorHandler { internal get; set; }
        public AsyncListener AsyncBeginHandler { internal get; set; }
        public AsyncListener AsyncEndHandler { internal get; set; }
        public AsyncListener AsyncErrorHandler { internal get; set; }
        public ChangedListener SubnetListChangedListener { internal get; set; }
        public NetworkAdapterListener SubnetAddedListener { internal get; set; }
        public NetworkAdapterListener SubnetRemovedListener { internal get; set; }
        public NetworkAdapterListener NetworkAdapterChangedListener { internal get; set; }

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
        /// Set the duration control point subscriptions will request.
        /// </summary>
        public uint SubscriptionDurationSecs { get; set; }

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

        /// <summary>Set the tcp port number the control point stack's UPnP event server will run on.</summary>
        /// <remarks>The default value is 0 (meaning that the OS will assign a port).
        /// You should only set this if you know the full set of services (plus their port
        /// requirements) running on a device.</remarks>
        public uint CpUpnpEventPort { get; set; }

        /// <summary>Set the tcp port number the device stack's UPnP web server will run on.</summary>
        /// <remarks>The default value is 0 (OS-assigned).
        public uint DvUpnpWebServerPort
        {
            get
            {
                if (DvEnableBonjour)
                    return 80;
                return iDvUpnpWebServerPort;
            }
            set { iDvUpnpWebServerPort = value; }
        }

        /// <summary>Get/set the tcp port number the WebSocket server will run on.</summary>
        /// <remarks>The default value is 0 (meaning that the OS will assign a port).
        /// You should only set this if you know the full set of services (plus their port
        /// requirements) running on a device.</remarks>
        public uint DvWebSocketPort { get; set; }

        /// <summary>
        /// Limit the library to using only the loopback network interface
        /// </summary>
        /// <remarks>Useful for testing but not expected to be used in production code</remarks>
        public bool UseLoopbackNetworkAdapter { get; set; }

        /// <summary>
        /// Include the loopback network interface in the list of available adapters.
        /// </summary>
        /// <remarks>Useful for testing but not expected to be used in production code</remarks>
        public bool IncludeLoopbackNetworkAdapter { get; set; }

        /// <summary>
        /// Enable use of Bonjour.
        /// </summary>
        /// <remarks>All DvDevice instances with an IResourceManager will be published using Bonjour.
        /// If a device sets the "Upnp.MdnsHostName" attribute, its presentation will be available via http://[hostname].local.
        /// Behaviour when more than one DvDevice sets the "MdnsHostName" attribute is undefined.
        /// Note that enabling Bonjour will cause the device stack to run a http server on port 80, requiring root privileges on linux.</remarks>
        public bool DvEnableBonjour { get; set; }
        /// <summary>
        /// Set a MDNS hostname.
        /// </summary>
        /// <remarks>Only used if DvEnableBonjour is true.</remarks>
        public string DvMdnsHostName { private get; set; }
        /// <summary>
        /// Set User-Agent reported by HTTP clients
        /// </summary>
        /// <remarks></remarks>
        public string HttpUserAgent { private get; set; }
        /// <summary>
        /// Set true to disable inferred BYEBYEs from device lists
        /// </summary>
        /// <remarks></remarks>
        public bool HostUdpIsLowQuality { get; set; }

        private uint iDvUpnpWebServerPort;

#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr OhNetInitParamsCreate();
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsDestroy(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetLogOutput(IntPtr aParams, OhNetCallbackMsg aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetFatalErrorHandler(IntPtr aParams, OhNetCallbackMsg aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetAsyncBeginHandler(IntPtr aParams, OhNetCallbackAsync aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetAsyncEndHandler(IntPtr aParams, OhNetCallbackAsync aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetAsyncErrorHandler(IntPtr aParams, OhNetCallbackAsync aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetSubnetListChangedListener(IntPtr aParams, OhNetCallback aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetSubnetAddedListener(IntPtr aParams, OhNetCallbackNetworkAdapter aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetSubnetRemovedListener(IntPtr aParams, OhNetCallbackNetworkAdapter aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetNetworkAdapterChangedListener(IntPtr aParams, OhNetCallbackNetworkAdapter aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetTcpConnectTimeout(IntPtr aParams, uint aTimeoutMs);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetMsearchTime(IntPtr aParams, uint aSecs);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetMsearchTtl(IntPtr aParams, uint aTtl);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetNumEventSessionThreads(IntPtr aParams, uint aNumThreads);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetNumXmlFetcherThreads(IntPtr aParams, uint aNumThreads);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetNumActionInvokerThreads(IntPtr aParams, uint aNumThreads);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetNumInvocations(IntPtr aParams, uint aNumInvocations);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetNumSubscriberThreads(IntPtr aParams, uint aNumThreads);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetSubscriptionDuration(IntPtr aParams, uint aDurationSecs);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetPendingSubscriptionTimeout(IntPtr aParams, uint aTimeoutMs);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetDvMaxUpdateTime(IntPtr aParams, uint aSecs);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetDvNumServerThreads(IntPtr aParams, uint aNumThreads);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetDvNumPublisherThreads(IntPtr aParams, uint aNumThreads);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetDvNumWebSocketThreads(IntPtr aParams, uint aNumThreads);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetCpUpnpEventServerPort(IntPtr aParams, uint aPort);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetDvUpnpServerPort(IntPtr aParams, uint aPort);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetDvWebSocketPort(IntPtr aParams, uint aPort);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetDvEnableBonjour(IntPtr aParams, IntPtr aHostName);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetUseLoopbackNetworkAdapter(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetIncludeLoopbackNetworkAdapter(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetHttpUserAgent(IntPtr aParams, IntPtr aHostName);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetHostUdpIsLowQuality(IntPtr aParams, int aHostName);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsTcpConnectTimeoutMs(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsMsearchTimeSecs(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsMsearchTtl(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsNumEventSessionThreads(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsNumXmlFetcherThreads(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsNumActionInvokerThreads(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsNumInvocations(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsNumSubscriberThreads(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsSubscriptionDurationSecs(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsPendingSubscriptionTimeoutMs(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsDvMaxUpdateTimeSecs(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsDvNumServerThreads(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsDvNumPublisherThreads(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsDvNumWebSocketThreads(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsCpUpnpEventServerPort(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsDvUpnpServerPort(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsDvWebSocketPort(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetInitParamsDvIsBonjourEnabled(IntPtr aParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int OhNetInitParamsIsHostUdpLowQuality(IntPtr aParams);

        public InitParams()
        {
            IntPtr defaultParams = OhNetInitParamsCreate();

            LogOutput = null;
            FatalErrorHandler = null;
            AsyncBeginHandler = null;
            AsyncEndHandler = null;
            AsyncErrorHandler = null;
            SubnetListChangedListener = null;
            SubnetAddedListener = null;
            SubnetRemovedListener = null;
            NetworkAdapterChangedListener = null;
            TcpConnectTimeoutMs = OhNetInitParamsTcpConnectTimeoutMs(defaultParams);
            MsearchTimeSecs = OhNetInitParamsMsearchTimeSecs(defaultParams);
            MsearchTtl = OhNetInitParamsMsearchTtl(defaultParams);
            NumEventSessionThreads = OhNetInitParamsNumEventSessionThreads(defaultParams);
            NumXmlFetcherThreads = OhNetInitParamsNumXmlFetcherThreads(defaultParams);
            NumActionInvokerThreads = OhNetInitParamsNumActionInvokerThreads(defaultParams);
            NumInvocations = OhNetInitParamsNumInvocations(defaultParams);
            NumSubscriberThreads = OhNetInitParamsNumSubscriberThreads(defaultParams);
            SubscriptionDurationSecs = OhNetInitParamsSubscriptionDurationSecs(defaultParams);
            PendingSubscriptionTimeoutMs = OhNetInitParamsPendingSubscriptionTimeoutMs(defaultParams);
            DvMaxUpdateTimeSecs = OhNetInitParamsDvMaxUpdateTimeSecs(defaultParams);
            DvNumServerThreads = OhNetInitParamsDvNumServerThreads(defaultParams);
            DvNumPublisherThreads = OhNetInitParamsDvNumPublisherThreads(defaultParams);
            DvNumWebSocketThreads = OhNetInitParamsDvNumWebSocketThreads(defaultParams);
            CpUpnpEventPort = OhNetInitParamsCpUpnpEventServerPort(defaultParams);
            DvUpnpWebServerPort = OhNetInitParamsDvUpnpServerPort(defaultParams);
            DvWebSocketPort = OhNetInitParamsDvWebSocketPort(defaultParams);
            UseLoopbackNetworkAdapter = false; // FIXME: No getter?
            IncludeLoopbackNetworkAdapter = false;
            DvEnableBonjour = OhNetInitParamsDvIsBonjourEnabled(defaultParams) != 0;
            HostUdpIsLowQuality = OhNetInitParamsIsHostUdpLowQuality(defaultParams) != 0;

            OhNetInitParamsDestroy(defaultParams);
        }
        internal IntPtr AllocNativeInitParams(IntPtr aCallbackPtr)
        {
            IntPtr nativeParams = OhNetInitParamsCreate();

            if (LogOutput != null)
            {
                OhNetInitParamsSetLogOutput(nativeParams, LogOutput.Callback, LogOutput.Handle());
            }
            if (FatalErrorHandler != null)
            {
                OhNetInitParamsSetFatalErrorHandler(nativeParams, FatalErrorHandler.Callback, FatalErrorHandler.Handle());
            }
            if (AsyncBeginHandler != null)
            {
                OhNetInitParamsSetAsyncBeginHandler(nativeParams, AsyncBeginHandler.Callback, AsyncBeginHandler.Handle());
            }
            if (AsyncEndHandler != null)
            {
                OhNetInitParamsSetAsyncEndHandler(nativeParams, AsyncEndHandler.Callback, AsyncEndHandler.Handle());
            }
            if (AsyncErrorHandler != null)
            {
                OhNetInitParamsSetAsyncErrorHandler(nativeParams, AsyncErrorHandler.Callback, AsyncErrorHandler.Handle());
            }
            if (SubnetListChangedListener != null)
            {
                OhNetInitParamsSetSubnetListChangedListener(nativeParams, SubnetListChangedListener.Callback, SubnetListChangedListener.Handle());
            }
            if (SubnetAddedListener != null)
            {
                OhNetInitParamsSetSubnetAddedListener(nativeParams, SubnetAddedListener.Callback, SubnetAddedListener.Handle());
            }
            if (SubnetRemovedListener != null)
            {
                OhNetInitParamsSetSubnetRemovedListener(nativeParams, SubnetRemovedListener.Callback, SubnetRemovedListener.Handle());
            }
            if (NetworkAdapterChangedListener != null)
            {
                OhNetInitParamsSetNetworkAdapterChangedListener(nativeParams, NetworkAdapterChangedListener.Callback, NetworkAdapterChangedListener.Handle());
            }
            OhNetInitParamsSetTcpConnectTimeout(nativeParams, TcpConnectTimeoutMs);
            OhNetInitParamsSetMsearchTime(nativeParams, MsearchTimeSecs);
            OhNetInitParamsSetMsearchTtl(nativeParams, MsearchTtl);
            OhNetInitParamsSetNumEventSessionThreads(nativeParams, NumEventSessionThreads);
            OhNetInitParamsSetNumXmlFetcherThreads(nativeParams, NumXmlFetcherThreads);
            OhNetInitParamsSetNumActionInvokerThreads(nativeParams, NumActionInvokerThreads);
            OhNetInitParamsSetNumInvocations(nativeParams, NumInvocations);
            OhNetInitParamsSetNumSubscriberThreads(nativeParams, NumSubscriberThreads);
            OhNetInitParamsSetSubscriptionDuration(nativeParams, SubscriptionDurationSecs);
            OhNetInitParamsSetPendingSubscriptionTimeout(nativeParams, PendingSubscriptionTimeoutMs);
            OhNetInitParamsSetDvMaxUpdateTime(nativeParams, DvMaxUpdateTimeSecs);
            OhNetInitParamsSetDvNumServerThreads(nativeParams, DvNumServerThreads);
            OhNetInitParamsSetDvNumPublisherThreads(nativeParams, DvNumPublisherThreads);
            OhNetInitParamsSetDvNumWebSocketThreads(nativeParams, DvNumWebSocketThreads);
            OhNetInitParamsSetCpUpnpEventServerPort(nativeParams, CpUpnpEventPort);
            OhNetInitParamsSetDvUpnpServerPort(nativeParams, DvUpnpWebServerPort);
            OhNetInitParamsSetDvWebSocketPort(nativeParams, DvWebSocketPort);
            if (DvEnableBonjour)
            {
                IntPtr hostName = InteropUtils.StringToHGlobalUtf8(DvMdnsHostName);
                OhNetInitParamsSetDvEnableBonjour(nativeParams, hostName);
                Marshal.FreeHGlobal(hostName);
            }
            if (!String.IsNullOrEmpty(HttpUserAgent))
            {
                IntPtr userAgent = InteropUtils.StringToHGlobalUtf8(HttpUserAgent);
                OhNetInitParamsSetHttpUserAgent(nativeParams, userAgent);
                Marshal.FreeHGlobal(userAgent);
            }
            OhNetInitParamsSetHostUdpIsLowQuality(nativeParams, HostUdpIsLowQuality ? 1 : 0);
            if (UseLoopbackNetworkAdapter)
            {
                OhNetInitParamsSetUseLoopbackNetworkAdapter(nativeParams);
            }
            if (IncludeLoopbackNetworkAdapter)
            {
                if (UseLoopbackNetworkAdapter)
                {
                    System.Diagnostics.Debug.WriteLine("WARNING: IncludeLoopbackNetworkAdapter is incompatible with UseLoopbackNetworkAdapter. Ignoring UseLoopbackNetworkAdapter.");
                }
                OhNetInitParamsSetIncludeLoopbackNetworkAdapter(nativeParams);
            }
            return nativeParams;
        }
        internal static void FreeNativeInitParams(IntPtr aNativeInitParams)
        {
            OhNetInitParamsDestroy(aNativeInitParams);
        }
    }

    public class LibraryException : Exception
    {
        public LibraryException() { }
        public LibraryException(string message) : base(message) { }
        public LibraryException(string message, Exception inner) : base(message, inner) { }
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
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int OhNetLibraryInitialise(IntPtr aInitParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int OhNetLibraryInitialiseMinimal(IntPtr aInitParams);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetLibraryStartCp(uint aSubnet);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetLibraryStartDv();
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint OhNetLibraryStartCombined(uint aSubnet);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetLibraryClose();
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetLibraryNotifySuspended();
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetLibraryNotifyResumed();
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetLibrarySetHttpUserAgent(IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetFree(IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetSetCurrentSubnet(uint aSubnet);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetRefreshNetworkAdapterList();
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetDebugSetLevel(uint aLevel);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetAbortProcess();
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetInitParamsSetFreeExternalCallback(IntPtr aParams, CallbackFreeMemory aCallback);

        private bool iIsDisposed;

#pragma warning disable 414
        private InitParams iInitParams;
#pragma warning restore 414
        private IDisposable iLogOutput;
        private IDisposable iFatalErrorHandler;
        private IDisposable iAsyncBeginHandler;
        private IDisposable iAsyncEndHandler;
        private IDisposable iAsyncErrorHandler;
        private IDisposable iSubnetListChangedListener;
        private IDisposable iSubnetAddedListener;
        private IDisposable iSubnetRemovedListener;
        private IDisposable iNetworkAdapterChangedListener;

        private delegate void CallbackFreeMemory(IntPtr aPtr);

        private void Initialise(InitParams aParams)
        {
            iLogOutput = aParams.LogOutput;
            iFatalErrorHandler = aParams.FatalErrorHandler;
            iAsyncBeginHandler = aParams.AsyncBeginHandler;
            iAsyncEndHandler = aParams.AsyncEndHandler;
            iAsyncErrorHandler = aParams.AsyncErrorHandler;
            iSubnetListChangedListener = aParams.SubnetListChangedListener;
            iSubnetAddedListener = aParams.SubnetAddedListener;
            iSubnetRemovedListener = aParams.SubnetRemovedListener;
            iNetworkAdapterChangedListener = aParams.NetworkAdapterChangedListener;
            IntPtr nativeInitParams = aParams.AllocNativeInitParams(IntPtr.Zero);
            OhNetInitParamsSetFreeExternalCallback(nativeInitParams, FreeMemory);
            if (0 != OhNetLibraryInitialise(nativeInitParams))
            {
                InitParams.FreeNativeInitParams(nativeInitParams);
                throw new LibraryException();
            }
        }

        /// <summary>
        /// Create the library instance.
        /// </summary>
        /// <remarks>Only one instance per process is allowed.
        /// This must be called before any other library function.</remarks>
        public static Library Create(InitParams aParams)
        {
            Library instance = new Library(aParams);
            instance.Initialise(aParams);
            return instance;
        }

        private Library(InitParams aParams)
        {
            iInitParams = aParams;
        }

        /// <summary>
        /// Start the library as a UPnP control point stack
        /// </summary>
        /// <returns>
        /// A control-point stack. Can be used to create device list factories.
        /// </returns>
        public ControlPointStack StartCp(uint aSubnet)
        {
            uint err = OhNetLibraryStartCp(aSubnet);
            CheckStartupError(err);
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
            uint err = OhNetLibraryStartDv();
            CheckStartupError(err);
            return new DeviceStack();
        }

        /// <summary>
        /// Start the library as both UPnP control point and device stacks
        /// </summary>
        public CombinedStack StartCombined(uint aSubnet)
        {
            uint err = OhNetLibraryStartCombined(aSubnet);
            CheckStartupError(err);
            return new CombinedStack();
        }

        private void CheckStartupError(uint aError)
        {
            switch (aError)
            {
                case 0:
                default:
                    break;
                case 1:
                    throw new ErrorNoMemory();
                case 2:
                    throw new ErrorGeneral();
                case 3:
                    throw new ErrorNetworkAddressInUse();
            }
        }

        /// <summary>
        /// Free memory returned by native code
        /// </summary>
        /// <param name="aPtr">IntPtr returned by native code which is documented as requiring explicit destruction</param>
        public static void Free(IntPtr aPtr)
        {
            OhNetFree(aPtr);
        }

        /// <summary>
        /// Set which subnet the library should use
        /// </summary>
        /// <remarks>Device lists and subscriptions will be automatically updated.
        ///
        /// No other subnet will be selected if aSubnet is not available</remarks>
        /// <param name="aSubnet">Handle returned by SubnetAt()</param>
        public void SetCurrentSubnet(NetworkAdapter aSubnet)
        {
            OhNetSetCurrentSubnet(aSubnet.Subnet());
        }

        /// <summary>
        /// Force a refresh of the library's list of available network adapters
        /// </summary>
        /// <remarks>This should only be required on platforms that are not capable of
        /// automatically detecting adapter changes.</remarks>
        public void RefreshNetworkAdapterList()
        {
            OhNetRefreshNetworkAdapterList();
        }

        /// <summary>
        /// Inform the library that the application has been suspended.
        /// </summary>
        /// <remarks>This is necessary if the application may be paused while other processes on
        /// a device continued to be executed (e.g. when an app moves to background on iOS).
        /// It is typically not necessary to call this when the host device hibernates.</remarks>
        public void NotifySuspended()
        {
            OhNetLibraryNotifySuspended();
        }

        /// <summary>
        /// Inform the library that the application has been resumed
        /// </summary>
        /// <remarks>This is necessary if the application may have been paused while other processes on
        /// a device continued to be executed (e.g. when an app moves to background on iOS).
        /// It is typically not necessary to call this when the host device resumes from hibernation.</remarks>
        public void NotifyResumed()
        {
            OhNetLibraryNotifyResumed();
        }

        public void SetHttpUserAgent(string aUserAgent)
        {
            IntPtr userAgent = InteropUtils.StringToHGlobalUtf8(aUserAgent);
            OhNetLibrarySetHttpUserAgent(userAgent);
            Marshal.FreeHGlobal(userAgent);
        }

        public enum DebugLevel: uint
        {
            None           = 0,
            Trace          = 1<<1,
            Thread         = 1<<2,
            Network        = 1<<3,
            Timer          = 1<<4,
            SsdpMulticast  = 1<<5,
            SsdpUnicast    = 1<<6,
            Http           = 1<<7,
            Device         = 1<<8,
            XmlFetch       = 1<<9,
            Service        = 1<<10,
            Event          = 1<<11,
            SsdpNotifier   = 1<<12,
            DvInvocation   = 1<<13,
            DvEvent        = 1<<14,
            DvWebSocket    = 1<<15,
            Bonjour        = 1<<17,
            DvDevice       = 1<<18,
            App0           = 1<<20,
            App1           = 1<<21,
            App2           = 1<<22,
            App3           = 1<<23,
            App4           = 1<<24,
            App5           = 1<<25,
            App6           = 1<<26,
            App7           = 1<<27,
            App8           = 1<<28,
            App9           = 1<<29,
            Error          = 1<<30,
            All            = 0x7FFFFFFF,
            Verbose        = 0x80000000
        }

        /// <summary>
        /// Set the level (if any) of debug logging.
        /// </summary>
        /// <remarks>Log messages will be passed to the callback registered in InitParams.LogOutput.</remarks>
        /// <param name="aLevel">Bit(s) specifying which debug levels to enable</param>
        public static void SetDebugLevel(DebugLevel aLevel)
        {
            OhNetDebugSetLevel((uint)aLevel);
        }

        /// <summary>
        /// Terminate the process after a fatal error.
        /// </summary>
        public static void AbortProcess()
        {
            OhNetAbortProcess();
        }

#if IOS
        [MonoPInvokeCallback (typeof (CallbackFreeMemory))]
#endif
        private static void FreeMemory(IntPtr aPtr)
        {
            Marshal.FreeHGlobal(aPtr);
        }

        public void Dispose()
        {
            if (!iIsDisposed)
            {
                iIsDisposed = true;

                OhNetLibraryClose(); // need to call this before disposing callbacks (below)
                                     // which may be called during stack destruction

                if(iLogOutput != null)
                {
                    iLogOutput.Dispose();
                }
                if(iFatalErrorHandler != null)
                {
                    iFatalErrorHandler.Dispose();
                }
                if(iAsyncBeginHandler != null)
                {
                    iAsyncBeginHandler.Dispose();
                }
                if(iAsyncEndHandler != null)
                {
                    iAsyncEndHandler.Dispose();
                }
                if(iAsyncErrorHandler != null)
                {
                    iAsyncErrorHandler.Dispose();
                }
                if(iSubnetListChangedListener != null)
                {
                    iSubnetListChangedListener.Dispose();
                }
                if(iSubnetAddedListener != null)
                {
                    iSubnetAddedListener.Dispose();
                }
                if(iSubnetRemovedListener != null)
                {
                    iSubnetRemovedListener.Dispose();
                }
                if(iNetworkAdapterChangedListener != null)
                {
                    iNetworkAdapterChangedListener.Dispose();
                }
            }
        }
    }

    public class InteropUtils
    {
        public static IntPtr StringToHGlobalUtf8(string aStr)
        {
            if (aStr == null)
                return IntPtr.Zero;
            byte[] bytes = System.Text.Encoding.UTF8.GetBytes(aStr);
            IntPtr ptr = Marshal.AllocHGlobal(bytes.Length + 1);
            Marshal.Copy(bytes, 0, ptr, bytes.Length);
            Marshal.WriteByte(ptr, bytes.Length, (byte)0);
            return ptr;
        }

        public static string PtrToStringUtf8(IntPtr aPtr, uint aLen) // aPtr is not nul-terminated
        {
            String str = "";
            if (aLen > 0)
            {
                byte[] array = new byte[aLen];
                Marshal.Copy(aPtr, array, 0, (int)aLen);
                str = System.Text.Encoding.UTF8.GetString(array, 0, array.Length);
            }
            return str;
        }

        public static string PtrToStringUtf8(IntPtr aPtr) // aPtr is nul-terminated
        {
            if (aPtr == IntPtr.Zero)
                return "";
            int len = 0;
            while (Marshal.ReadByte(aPtr, len) != 0)
                len++;
            if (len == 0)
                return "";
            byte[] array = new byte[len];
            Marshal.Copy(aPtr, array, 0, len);
            return System.Text.Encoding.UTF8.GetString(array, 0, array.Length);
        }
    }
}
