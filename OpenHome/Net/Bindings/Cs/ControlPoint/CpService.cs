using System;
using System.Runtime.InteropServices;
using System.Text;
using OpenHome.Net.Core;
using System.Collections.Generic;
#if IOS
using ObjCRuntime;
#endif

namespace OpenHome.Net.ControlPoint
{
    /// <summary>
    /// (Action) Argument.  Only intended for use by auto-generated proxies.
    /// </summary>
    /// <remarks>One Argument will be created per [in/out]put Parameter for the Action.
    /// Input parameters should construct arguments using the (Parameter, Val) constructor.
    /// Output parameters should construct arguments using only the parameter and should
    /// read the value when the invocation completes.</remarks>
    public class Argument
    {
        protected IntPtr iHandle;

        internal IntPtr Handle()
        {
            return iHandle;
        }

        protected Argument()
        {
        }
    }

    /// <summary>
    /// Integer type argument.  Only intended for use by auto-generated proxies.
    /// </summary>
    public class ArgumentInt : Argument
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateIntInput(IntPtr aParameter, int aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateIntOutput(IntPtr aParameter);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int ActionArgumentValueInt(IntPtr aHandle);

        /// <summary>
        /// Constructor for integer input argument for an action
        /// </summary>
        /// <remarks>Intended to be write only (its value is written on construction and not be later read)</remarks>
        /// <param name="aParameter">Defines the name plus any bounds to the value for the argument.
        /// Must have been previously added to the action using Action.AddInputParameter</param>
        /// <param name="aValue">Value for the argument</param>
        public ArgumentInt(ParameterInt aParameter, int aValue)
        {
            iHandle = ActionArgumentCreateIntInput(aParameter.Handle(), aValue);
        }

        /// <summary>
        /// Constructor for integer output argument for an action
        /// </summary>
        /// <remarks>Intended to be created without any value.  The value is later set after
        /// CpService.InvokeAction is called but before the invocation's callback is run)</remarks>
        /// <param name="aParameter">Defines the name plus any bounds to the value for the argument.
        /// Must have been previously added to the action using Action.AddOutputParameter</param>
        public ArgumentInt(ParameterInt aParameter)
        {
            iHandle = ActionArgumentCreateIntOutput(aParameter.Handle());
        }

        /// <summary>
        /// Read the value of an integer argument.
        /// </summary>
        /// <remarks>Only intended for use with output arguments inside the invocation completed callback.</remarks>
        /// <returns>Current value of the argument</returns>
        int Value()
        {
            return ActionArgumentValueInt(iHandle);
        }
    }

    /// <summary>
    /// Unsigned integer type argument.  Only intended for use by auto-generated proxies.
    /// </summary>
    public class ArgumentUint : Argument
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateUintInput(IntPtr aParameter, uint aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateUintOutput(IntPtr aParameter);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint ActionArgumentValueUint(IntPtr aHandle);

        /// <summary>
        /// Constructor for unsigned integer input argument for an action
        /// </summary>
        /// <remarks>Intended to be write only (its value is written on construction and not be later read)</remarks>
        /// <param name="aParameter">Defines the name plus any bounds to the value for the argument.
        /// Must have been previously added to the action using Action.AddInputParameter</param>
        /// <param name="aValue">Value for the argument</param>
        public ArgumentUint(ParameterUint aParameter, uint aValue)
        {
            iHandle = ActionArgumentCreateUintInput(aParameter.Handle(), aValue);
        }

        /// <summary>
        /// Constructor for unsigned integer output argument for an action
        /// </summary>
        /// <remarks>Intended to be created without any value.  The value is later set after
        /// CpService.InvokeAction is called but before the invocation's callback is run)</remarks>
        /// <param name="aParameter">Defines the name plus any bounds to the value for the argument.
        /// Must have been previously added to the action using Action.AddOutputParameter</param>
        public ArgumentUint(ParameterUint aParameter)
        {
            iHandle = ActionArgumentCreateUintOutput(aParameter.Handle());
        }

        /// <summary>
        /// Read the value of an unsigned integer argument.
        /// </summary>
        /// <remarks>Only intended for use with output arguments inside the invocation completed callback.</remarks>
        /// <returns>Current value of the argument</returns>
        uint Value()
        {
            return ActionArgumentValueUint(iHandle);
        }
    }

    /// <summary>
    /// Boolean type argument.  Only intended for use by auto-generated proxies.
    /// </summary>
    public class ArgumentBool : Argument
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateBoolInput(IntPtr aParameter, uint aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateBoolOutput(IntPtr aParameter);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint ActionArgumentValueBool(IntPtr aHandle);

        /// <summary>
        /// Constructor for boolean input argument for an action
        /// </summary>
        /// <remarks>Intended to be write only (its value is written on construction and not be later read)</remarks>
        /// <param name="aParameter">Defines the name for the argument.
        /// Must have been previously added to the action using Action.AddInputParameter</param>
        /// <param name="aValue">Value for the argument</param>
        public ArgumentBool(ParameterBool aParameter, bool aValue)
        {
            iHandle = ActionArgumentCreateBoolInput(aParameter.Handle(), (aValue? 1u : 0u));
        }

        /// <summary>
        /// Constructor for boolean output argument for an action
        /// </summary>
        /// <remarks>Intended to be created without any value.  The value is later set after
        /// CpService.InvokeAction is called but before the invocation's callback is run)</remarks>
        /// <param name="aParameter">Defines the name for the argument.
        /// Must have been previously added to the action using Action.AddOutputParameter</param>
        public ArgumentBool(ParameterBool aParameter)
        {
            iHandle = ActionArgumentCreateBoolOutput(aParameter.Handle());
        }

        /// <summary>
        /// Read the value of a boolean argument.
        /// </summary>
        /// <remarks>Only intended for use with output arguments inside the invocation completed callback.</remarks>
        /// <returns>Current value of the argument</returns>
        bool Value()
        {
            uint val = ActionArgumentValueBool(iHandle);
            return (val != 0);
        }
    }

    /// <summary>
    /// String type argument.  Only intended for use by auto-generated proxies.
    /// </summary>
    public class ArgumentString : Argument
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateStringInput(IntPtr aParameter, IntPtr aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateStringOutput(IntPtr aParameter);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void ActionArgumentGetValueString(IntPtr aHandle, out IntPtr aData, out uint aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetFree(IntPtr aPtr);

        /// <summary>
        /// Constructor for string input argument for an action
        /// </summary>
        /// <remarks>Intended to be write only (its value is written on construction and not be later read)</remarks>
        /// <param name="aParameter">Defines the name plus any bounds to the value for the argument.
        /// Must have been previously added to the action using Action.AddInputParameter</param>
        /// <param name="aValue">Value for the argument</param>
        public ArgumentString(ParameterString aParameter, String aValue)
        {
            IntPtr value = InteropUtils.StringToHGlobalUtf8(aValue);
            iHandle = ActionArgumentCreateStringInput(aParameter.Handle(), value);
            Marshal.FreeHGlobal(value);
        }

        /// <summary>
        /// Constructor for string output argument for an action
        /// </summary>
        /// <remarks>Intended to be created without any value.  The value is later set after
        /// CpService.InvokeAction is called but before the invocation's callback is run)</remarks>
        /// <param name="aParameter">Defines the name plus any bounds to the value for the argument.
        /// Must have been previously added to the action using Action.AddOutputParameter</param>
        public ArgumentString(ParameterString aParameter)
        {
            iHandle = ActionArgumentCreateStringOutput(aParameter.Handle());
        }

        /// <summary>
        /// Read the value of a binary argument.
        /// </summary>
        /// <remarks>Only intended for use with output arguments inside the invocation completed callback.
        /// Can only be called once as the first call extracts the string data from the underlying native object</remarks>
        /// <returns>Current value of the argument</returns>
        String Value()
        {
            IntPtr ptr;
            uint len;
            ActionArgumentGetValueString(iHandle, out ptr, out len);
            String ret = InteropUtils.PtrToStringUtf8(ptr, len);
            OhNetFree(ptr);
            return ret;
        }
    }

    /// <summary>
    /// Binary type argument.  Only intended for use by auto-generated proxies.
    /// </summary>
    public class ArgumentBinary : Argument
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateBinaryInput(IntPtr aParameter, IntPtr aData, int aLength);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ActionArgumentCreateBinaryOutput(IntPtr aParameter);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void ActionArgumentGetValueBinary(IntPtr aHandle, out IntPtr aData, out uint aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetFree(IntPtr aPtr);

        /// <summary>
        /// Constructor for binary input argument for an action
        /// </summary>
        /// <remarks>Intended to be write only (its value is written on construction and not be later read)</remarks>
        /// <param name="aParameter">Defines the name for the argument.
        /// Must have been previously added to the action using Action.AddInputParameter</param>
        /// <param name="aData">Value for the argument</param>
        public ArgumentBinary(ParameterBinary aParameter, byte[] aData)
        {
            GCHandle h = GCHandle.Alloc(aData, GCHandleType.Pinned);
            iHandle = ActionArgumentCreateBinaryInput(aParameter.Handle(), h.AddrOfPinnedObject(), aData.Length);
            h.Free();
        }

        /// <summary>
        /// Constructor for binary output argument for an action
        /// </summary>
        /// <remarks>Intended to be created without any value.  The value is later set after
        /// CpService.InvokeAction is called but before the invocation's callback is run)</remarks>
        /// <param name="aParameter">Defines the name plus any bounds to the value for the argument.
        /// Must have been previously added to the action using Action.AddOutputParameter</param>
        public ArgumentBinary(ParameterBinary aParameter)
        {
            iHandle = ActionArgumentCreateBinaryOutput(aParameter.Handle());
        }

        /// <summary>
        /// Read the value of a binary argument.
        /// </summary>
        /// <remarks>Only intended for use with output arguments inside the invocation completed callback.
        /// Can only be called once as the first call extracts the string data from the underlying native object</remarks>
        /// <returns>Current value of the argument</returns>
        byte[] Value()
        {
            IntPtr data;
            uint len;
            ActionArgumentGetValueBinary(iHandle, out data, out len);
            byte[] ret = new byte[len];
            Marshal.Copy(data, ret, 0, (int)len);
            OhNetFree(data);
            return ret;
        }
    }

    /// <summary>
    /// Utility class used to execute a single action.  Only intended for use by auto-generated proxies.
    /// </summary>
    public class Invocation
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr CpServiceInvocation(IntPtr aService, IntPtr aAction, CpProxy.CallbackActionComplete aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpInvocationAddInput(IntPtr aInvocation, IntPtr aArgument);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpInvocationAddOutput(IntPtr aInvocation, IntPtr aArgument);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint CpInvocationError(IntPtr aInvocation, out uint aErrorCode, out IntPtr aErrorDesc);
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
        static extern int CpInvocationOutputInt(IntPtr aInvocation, uint aIndex);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint CpInvocationOutputUint(IntPtr aInvocation, uint aIndex);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint CpInvocationOutputBool(IntPtr aInvocation, uint aIndex);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpInvocationGetOutputString(IntPtr aInvocation, uint aIndex, out IntPtr aData, out uint aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpInvocationGetOutputBinary(IntPtr aInvocation, uint aIndex, out IntPtr aData, out uint aLen);

        private CpProxy.CallbackAsyncComplete iAsyncComplete;
        private CpProxy.CallbackActionComplete iCallbackAsyncComplete;
        private IntPtr iHandle;
        private CpService iService;
        private List<Argument> iInputArgs;
        private List<Argument> iOutputArgs;

        /// <summary>
        /// Constructor.  Not intended for external use (use CpService.Invocation instead)
        /// </summary>
        /// <param name="aService">Service the action is being invoked on</param>
        /// <param name="aAction">Handle to the action being invoked</param>
        /// <param name="aCallback">Callback to run when the action completes</param>
        internal Invocation(CpService aService, IntPtr aAction, CpProxy.CallbackAsyncComplete aCallback)
        {
            iService = aService;
            iInputArgs = new List<Argument>();
            iOutputArgs = new List<Argument>();
            GCHandle gch = GCHandle.Alloc(this); /* no need to store gch as a member as AsyncComplete is guaranteed
                                                    to be called, even in error cases */
            iAsyncComplete = aCallback;
            iCallbackAsyncComplete = new CpProxy.CallbackActionComplete(AsyncComplete);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            iHandle = CpServiceInvocation(aService.Handle(), aAction, iCallbackAsyncComplete, ptr);
        }

        /// <summary>
        /// Add an input argument to an invocation
        /// </summary>
        /// <param name="aArgument">Input argument being added.  Ownership passes to the invocation</param>
        public void AddInput(Argument aArgument)
        {
            iInputArgs.Add(aArgument);
            CpInvocationAddInput(iHandle, aArgument.Handle());
        }

        /// <summary>
        /// Add an output argument to an invocation
        /// </summary>
        /// <param name="aArgument">Output argument being added.  Ownership passes to the invocation</param>
        public void AddOutput(Argument aArgument)
        {
            iOutputArgs.Add(aArgument);
            CpInvocationAddOutput(iHandle, aArgument.Handle());
        }

        /// <summary>
        /// Check whether the invocation failed
        /// </summary>
        /// <remarks>Only intended for use in the invocation complete callback</remarks>
        /// <returns>true if the invocation failed; false if it succeeded</returns>
        public static bool Error(IntPtr aHandle, out uint aErrorCode, out string aErrorDesc)
        {
            uint code;
            IntPtr desc;
            uint err = CpInvocationError(aHandle, out code, out desc);
            aErrorCode = code;
            aErrorDesc = InteropUtils.PtrToStringUtf8(desc);
            return (err != 0);
        }

        /// <summary>
        /// Utility to retrieve the value of an integer type output argument
        /// </summary>
        /// <param name="aHandle">Invocation handle</param>
        /// <param name="aIndex">Zero-based index into array of output arguments.
        /// Must refer to an ArgumentInt.</param>
        /// <returns>Value of the integer output argument</returns>
        public static int OutputInt(IntPtr aHandle, uint aIndex)
        {
            return CpInvocationOutputInt(aHandle, aIndex);
        }

        /// <summary>
        /// Utility to retrieve the value of an unsigned integer type output argument
        /// </summary>
        /// <param name="aHandle">Invocation handle</param>
        /// <param name="aIndex">Zero-based index into array of output arguments.
        /// Must refer to an ArgumentUint.</param>
        /// <returns>Value of the unsigned integer output argument</returns>
        public static uint OutputUint(IntPtr aHandle, uint aIndex)
        {
            return CpInvocationOutputUint(aHandle, aIndex);
        }

        /// <summary>
        /// Utility to retrieve the value of a boolean type output argument
        /// </summary>
        /// <param name="aHandle">Invocation handle</param>
        /// <param name="aIndex">Zero-based index into array of output arguments.
        /// Must refer to an ArgumentBool.</param>
        /// <returns>Value of the boolean output argument</returns>
        public static bool OutputBool(IntPtr aHandle, uint aIndex)
        {
            uint val = CpInvocationOutputBool(aHandle, aIndex);
            return (val != 0);
        }

        /// <summary>
        /// Utility to retrieve the value of a string type output argument
        /// </summary>
        /// <remarks>Must only be called once per output argument.  (The first call extracts
        /// the string data from the underlying native object so later calls would return an
        /// empty string.)</remarks>
        /// <param name="aHandle">Invocation handle</param>
        /// <param name="aIndex">Zero-based index into array of output arguments.
        /// Must refer to an ArgumentString.</param>
        /// <returns>Value of the string output argument</returns>
        public static String OutputString(IntPtr aHandle, uint aIndex)
        {
            IntPtr ptr;
            uint len;
            CpInvocationGetOutputString(aHandle, aIndex, out ptr, out len);
            String str = InteropUtils.PtrToStringUtf8(ptr, len);
            OhNetFree(ptr);
            return str;
        }

        /// <summary>
        /// Utility to retrieve the value of a binary type output argument
        /// </summary>
        /// <remarks>Must only be called once per output argument.  (The first call extracts
        /// the binary data from the underlying native object so later calls would return an
        /// empty string.)</remarks>
        /// <param name="aHandle">Invocation handle</param>
        /// <param name="aIndex">Zero-based index into array of output arguments.
        /// Must refer to an ArgumentString.</param>
        /// <returns>Value of the string output argument</returns>
        public static byte[] OutputBinary(IntPtr aHandle, uint aIndex)
        {
            IntPtr data;
            uint len;
            CpInvocationGetOutputBinary(aHandle, aIndex, out data, out len);
            if (data == IntPtr.Zero)
            {
                return null;
            }
            byte[] bin = new byte[len];
            Marshal.Copy(data, bin, 0, (int)len);
            OhNetFree(data);
            return bin;
        }

        internal IntPtr Handle()
        {
            return iHandle;
        }

#if IOS
        [MonoPInvokeCallback (typeof (CpProxy.CallbackActionComplete))]
#endif
        private static void AsyncComplete(IntPtr aPtr, IntPtr aAsyncHandle)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            Invocation self = (Invocation)gch.Target;
            try
            {
                self.iAsyncComplete(aAsyncHandle);
            }
            catch (ProxyError)
            {
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown", new object[] { e });
                System.Diagnostics.Debug.WriteLine("         Only ProxyError can be thrown by action complete delegates");
            }
            gch.Free();
            self.iService.InvocationComplete(self);
        }
    }

    /// <summary>
    /// Used by CpProxy to represent a service offered by a remote device.  Only intended for use by auto-generated proxies.
    /// </summary>
    public class CpService
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr CpServiceCreate(IntPtr aDomain, IntPtr aName, uint aVersion, IntPtr aDevice);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpServiceDestroy(IntPtr aService);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpServiceInvokeAction(IntPtr aService, IntPtr aInvocation);

        private IntPtr iHandle;
        private List<Invocation> iActiveInvocations;

        /// <summary>
        /// Constructor.  Only intended for use by CpProxy.
        /// </summary>
        /// <param name="aHandle"></param>
        internal CpService(IntPtr aHandle)
        {
            iHandle = aHandle;
            iActiveInvocations = new List<Invocation>();
        }

        /// <summary>
        /// Request an invocation object prior to setting input/output arguments
        /// </summary>
        /// <param name="aAction">Action which will be invoked</param>
        /// <param name="aCallback">Delegate to run when the action completes</param>
        /// <returns>Invocation object, ready to receive input and output arguments</returns>
        public Invocation Invocation(OpenHome.Net.Core.Action aAction, CpProxy.CallbackAsyncComplete aCallback)
        {
            Invocation invocation = new Invocation(this, aAction.Handle(), aCallback);
            lock (this)
            {
                iActiveInvocations.Add(invocation);
            }
            return invocation;
        }

        /// <summary>
        /// Invoke an action
        /// </summary>
        /// <param name="aInvocation">Invocation object, with all input and output arguments added</param>
        public void InvokeAction(Invocation aInvocation)
        {
            CpServiceInvokeAction(iHandle, aInvocation.Handle());
        }

        internal void InvocationComplete(Invocation aInvocation)
        {
            IntPtr handle = aInvocation.Handle();
            lock (this)
            {
                for (int i=0; i<iActiveInvocations.Count; i++)
                {
                    if (iActiveInvocations[i].Handle() == handle)
                    {
                        iActiveInvocations.RemoveAt(i);
                        break;
                    }
                }
            }
        }

        internal IntPtr Handle()
        {
            return iHandle;
        }
    }
}
