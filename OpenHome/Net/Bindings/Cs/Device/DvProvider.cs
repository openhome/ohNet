using System;
using System.Runtime.InteropServices;
using System.Text;
using OpenHome.Net.Core;
using System.Collections.Generic;

namespace OpenHome.Net.Device
{
    /// <summary>
    /// Base class for a service provider.
    /// </summary>
    /// <remarks>Derivations will typically be by service-specific auto-generated code which will
    /// offer 0..n actions and 0..n properties.</remarks>
    public class DvProvider
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe IntPtr DvProviderCreate(IntPtr aDevice, IntPtr aDomain, IntPtr aType, uint aVersion);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvProviderDestroy(IntPtr aProvider);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvProviderAddAction(IntPtr aProvider, IntPtr aAction, ActionDelegate aCallback, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvProviderPropertiesLock(IntPtr aHandle);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvProviderPropertiesUnlock(IntPtr aHandle);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvProviderAddProperty(IntPtr aProvider, IntPtr aProperty);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvProviderSetPropertyInt(IntPtr aProvider, IntPtr aProperty, int aValue, uint* aChanged);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvProviderSetPropertyUint(IntPtr aProvider, IntPtr aProperty, uint aValue, uint* aChanged);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvProviderSetPropertyBool(IntPtr aProvider, IntPtr aProperty, uint aValue, uint* aChanged);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvProviderSetPropertyString(IntPtr aProvider, IntPtr aProperty, IntPtr aValue, uint* aChanged);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvProviderSetPropertyBinary(IntPtr aProvider, IntPtr aProperty, byte* aData, uint aLen, uint* aChanged);

        protected delegate int ActionDelegate(IntPtr aPtr, IntPtr aInvocation);

        protected IntPtr iHandle;
        private List<OpenHome.Net.Core.Action> iActions;
        private List<OpenHome.Net.Core.Property> iProperties;

        /// <summary>
        /// Lock the provider's properties, blocking publication of updates.
        /// </summary>
        /// <remarks>This is not necessary when updating a single property but is used by providers that
        /// have >1 properties whose values are related.  Without locking, updates to some properties may
        /// be published, leaving related properties in their old (now incompatible) states.
        /// 
        /// Every call to this must be followed by (exactly) one call to PropertiesUnlock().</remarks>
        public void PropertiesLock()
        {
            DvProviderPropertiesLock(iHandle);
        }

        /// <summary>
        /// Unlock the provider's properties, allowing publication of updates.
        /// </summary>
        /// <remarks>Any pending updates will automatically be scheduled.
        /// 
        /// This must only be called following a call to PropertiesLock().</remarks>
        public void PropertiesUnlock()
        {
            DvProviderPropertiesUnlock(iHandle);
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device the service is being added to and will be offered by</param>
        /// <param name="aDomain">Domain of the vendor who defined the service</param>
        /// <param name="aType">Name of the service</param>
        /// <param name="aVersion">Version number of the service</param>
        protected unsafe DvProvider(DvDevice aDevice, String aDomain, String aType, uint aVersion)
        {
            IntPtr domain = InteropUtils.StringToHGlobalUtf8(aDomain);
            IntPtr type = InteropUtils.StringToHGlobalUtf8(aType);
            iHandle = DvProviderCreate(aDevice.Handle(), domain, type, aVersion);
            Marshal.FreeHGlobal(type);
            Marshal.FreeHGlobal(domain);
            iActions = new List<OpenHome.Net.Core.Action>();
            iProperties = new List<OpenHome.Net.Core.Property>();
        }

        /// <summary>
        /// Register an action as available.  The action will be published as part of the owning device's service xml
        /// </summary>
        /// <param name="aAction">Action being registered as availabke</param>
        /// <param name="aDelegate">Delegate to call when the action is invoked</param>
        /// <param name="aPtr">Data to pass to the delegate</param>
        protected void EnableAction(OpenHome.Net.Core.Action aAction, ActionDelegate aDelegate, IntPtr aPtr)
        {
            iActions.Add(aAction);
            DvProviderAddAction(iHandle, aAction.Handle(), aDelegate, aPtr);
        }
        
        /// <summary>
        /// Add a property to this provider
        /// </summary>
        /// <remarks>Any later updates to the value of the property will be automatically published to
        /// any subscribers</remarks>
        /// <param name="aProperty">Property being added</param>
        protected void AddProperty(OpenHome.Net.Core.Property aProperty)
        {
            iProperties.Add(aProperty);
            DvProviderAddProperty(iHandle, aProperty.Handle());
        }
        
        /// <summary>
        /// Utility function which updates the value of a PropertyInt. (Not intended for external use)
        /// </summary>
        /// <remarks>If the property value has changed and the properties are not locked (PropertiesLock()
        /// called more recently than PropertiesUnlock()), publication of an update is scheduled.
        ///
        /// Throws ParameterValidationError if the property has a range of allowed values and
        /// the new value is not in this range</remarks>
        /// <param name="aProperty">Property to be updated</param>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the property's value has changed (aValue was different to the previous value)</returns>
        protected unsafe bool SetPropertyInt(PropertyInt aProperty, int aValue)
        {
            uint changed;
            int err = DvProviderSetPropertyInt(iHandle, aProperty.Handle(), aValue, &changed);
            if (err != 0)
            {
                throw new PropertyUpdateError();
            }
            return (changed != 0);
        }

        /// <summary>
        /// Utility function which updates the value of a PropertyUint. (Not intended for external use)
        /// </summary>
        /// <remarks>If the property value has changed and the properties are not locked (PropertiesLock()
        /// called more recently than PropertiesUnlock()), publication of an update is scheduled.
        ///
        /// Throws ParameterValidationError if the property has a range of allowed values and
        /// the new value is not in this range</remarks>
        /// <param name="aProperty">Property to be updated</param>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the property's value has changed (aValue was different to the previous value)</returns>
        protected unsafe bool SetPropertyUint(PropertyUint aProperty, uint aValue)
        {
            uint changed;
            int err = DvProviderSetPropertyUint(iHandle, aProperty.Handle(), aValue, &changed);
            if (err != 0)
            {
                throw new PropertyUpdateError();
            }
            return (changed != 0);
        }

        /// <summary>
        /// Utility function which updates the value of a PropertyBool. (Not intended for external use)
        /// </summary>
        /// <remarks>If the property value has changed and the properties are not locked (PropertiesLock()
        /// called more recently than PropertiesUnlock()), publication of an update is scheduled</remarks>
        /// <param name="aProperty">Property to be updated</param>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the property's value has changed (aValue was different to the previous value)</returns>
        protected unsafe bool SetPropertyBool(PropertyBool aProperty, bool aValue)
        {
            uint changed;
            uint val = (aValue ? 1u : 0u);
            int err = DvProviderSetPropertyBool(iHandle, aProperty.Handle(), val, &changed);
            if (err != 0)
            {
                throw new PropertyUpdateError();
            }
            return (changed != 0);
        }

        /// <summary>
        /// Utility function which updates the value of a PropertyString. (Not intended for external use)
        /// </summary>
        /// <remarks>If the property value has changed and the properties are not locked (PropertiesLock()
        /// called more recently than PropertiesUnlock()), publication of an update is scheduled.
        ///
        /// Throws ParameterValidationError if the property has a range of allowed values and
        /// the new value is not in this range</remarks>
        /// <param name="aProperty">Property to be updated</param>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the property's value has changed (aValue was different to the previous value)</returns>
        protected unsafe bool SetPropertyString(PropertyString aProperty, String aValue)
        {
            uint changed;
            IntPtr value = InteropUtils.StringToHGlobalUtf8(aValue);
            int err = DvProviderSetPropertyString(iHandle, aProperty.Handle(), value, &changed);
            Marshal.FreeHGlobal(value);
            if (err != 0)
            {
                throw new PropertyUpdateError();
            }
            return (changed != 0);
        }

        /// <summary>
        /// Utility function which updates the value of a PropertyBinary. (Not intended for external use)
        /// </summary>
        /// <remarks>If the property value has changed and the properties are not locked (PropertiesLock()
        /// called more recently than PropertiesUnlock()), publication of an update is scheduled</remarks>
        /// <param name="aProperty">Property to be updated</param>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the property's value has changed (aValue was different to the previous value)</returns>
        protected unsafe bool SetPropertyBinary(PropertyBinary aProperty, byte[] aValue)
        {
            uint changed;
            int err;
            fixed (byte* pValue = aValue)
            {
                err = DvProviderSetPropertyBinary(iHandle, aProperty.Handle(), pValue, (uint)aValue.Length, &changed);
            }
            if (err != 0)
            {
                throw new PropertyUpdateError();
            }
            return (changed != 0);
        }

        /// <summary>
        /// Must be called by each sub-class, preferably from their Dispose() method
        /// </summary>
        protected bool DisposeProvider()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return false;
                DvProviderDestroy(iHandle);
                iHandle = IntPtr.Zero;
            }
            // don't Dispose contents of iActions - the underlying native provider handles this
            for (int i = 0; i < iProperties.Count; i++)
                iProperties[i].Dispose();
            return true;
        }
    }

    public interface IDvInvocation
    {
        /// <summary>
        /// Get the version number of the service requested by the caller.
        /// </summary>
        /// <returns>The version number of the service the caller expects.</returns>
        uint Version();
        /// <summary>
        /// Get the network adapter an action was invoked using.
        /// </summary>
        /// <returns>The network adapter used to invoke this action.</returns>
        uint Adapter();
        /// <summary>
        /// Get the prefix to use on any uris to resources offered by the provider.
        /// </summary>
        /// <returns>The prefix to resource uris.</returns>
        string ResourceUriPrefix();
        /// <summary>
        /// Get the endpoint of the client.
        /// </summary>
        /// <param name="aAddress">IPv4 address in network byte order</param>
        /// <param name="aPort">Client's port [1..65535]</param>
        void GetClientEndpoint(out uint aAddress, out uint aPort);
    }

    /// <summary>
    /// Utility class used by providers to read input and write output arguments
    /// </summary>
    /// <remarks>Only intended for use by auto-generated providers</remarks>
    public class DvInvocation : IDvInvocation
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe void DvInvocationGetVersion(IntPtr aInvocation, uint* aVersion);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe void DvInvocationGetAdapter(IntPtr aInvocation, uint* aAdapter);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe void DvInvocationGetResourceUriPrefix(IntPtr aInvocation, IntPtr* aPrefix, uint* aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe void DvInvocationGetClientEndpoint(IntPtr aInvocation, uint* aAddress, uint* aPort);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int DvInvocationReadStart(IntPtr aInvocation);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationReadInt(IntPtr aInvocation, IntPtr aName, int* aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationReadUint(IntPtr aInvocation, IntPtr aName, uint* aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationReadBool(IntPtr aInvocation, IntPtr aName, uint* aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationReadStringAsBuffer(IntPtr aInvocation, IntPtr aName, IntPtr* aValue, uint* aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationReadBinary(IntPtr aInvocation, IntPtr aName, IntPtr* aData, uint* aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int DvInvocationReadEnd(IntPtr aInvocation);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationReportError(IntPtr aInvocation, uint aCode, IntPtr aDescription);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int DvInvocationWriteStart(IntPtr aInvocation);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteInt(IntPtr aInvocation, IntPtr aName, int aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteUint(IntPtr aInvocation, IntPtr aName, uint aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteBool(IntPtr aInvocation, IntPtr aName, uint aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteStringStart(IntPtr aInvocation, IntPtr aName);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteString(IntPtr aInvocation, IntPtr aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteStringEnd(IntPtr aInvocation, IntPtr aName);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteBinaryStart(IntPtr aInvocation, IntPtr aName);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteBinary(IntPtr aInvocation, byte* aData, uint aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int DvInvocationWriteBinaryEnd(IntPtr aInvocation, IntPtr aName);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int DvInvocationWriteEnd(IntPtr aInvocation);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe void OhNetFree(IntPtr aPtr);

        protected IntPtr iHandle;
        
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aHandle">'aInvocation' argument to ActionDelegate</param>
        public DvInvocation(IntPtr aHandle)
        {
            iHandle = aHandle;
        }
        /// <summary>
        /// Get the version number of the service requested by the caller.
        /// </summary>
        /// <returns>The version number of the service the caller expects.</returns>
        public unsafe uint Version()
        {
            uint version;
            DvInvocationGetVersion(iHandle, &version);
            return version;
        }
        /// <summary>
        /// Get the network adapter an action was invoked using.
        /// </summary>
        /// <returns>The network adapter used to invoke this action.</returns>
        public unsafe uint Adapter()
        {
            uint adapter;
            DvInvocationGetAdapter(iHandle, &adapter);
            return adapter;
        }
        /// <summary>
        /// Get the prefix to use on any uris to resources offered by the provider.
        /// </summary>
        /// <returns>The prefix to resource uris.</returns>
        public unsafe string ResourceUriPrefix()
        {
            IntPtr cPrefix;
            uint len;
            DvInvocationGetResourceUriPrefix(iHandle, &cPrefix, &len);
            String prefix = InteropUtils.PtrToStringUtf8(cPrefix, len);
            return prefix;
        }
        /// <summary>
        /// Get the endpoint of the client.
        /// </summary>
        /// <param name="aAddress">IPv4 address in network byte order</param>
        /// <param name="aPort">Client's port [1..65535]</param>
        public unsafe void GetClientEndpoint(out uint aAddress, out uint aPort)
        {
            uint address, port;
            DvInvocationGetClientEndpoint(iHandle, &address, &port);
            aAddress = address;
            aPort = port;
        }
        /// <summary>
        /// Begin reading (input arguments for) an invocation
        /// </summary>
        /// <remarks>Must be called before the values of any input arguments are read.
        /// Must be called for invocations with no input arguments.</remarks>
        public void ReadStart()
        {
            CheckError(DvInvocationReadStart(iHandle));
        }
        /// <summary>
        /// Read the value of an integer input argument for an invocation
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this input argument</param>
        /// <returns>Value of the input argument</returns>
        public unsafe int ReadInt(String aName)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            int val;
            int err = DvInvocationReadInt(iHandle, name, &val);
            Marshal.FreeHGlobal(name);
            CheckError(err);
            return val;
        }
        /// <summary>
        /// Read the value of an unsigned integer input argument for an invocation
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this input argument</param>
        /// <returns>Value of the input argument</returns>
        public unsafe uint ReadUint(String aName)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            uint val;
            int err = DvInvocationReadUint(iHandle, name, &val);
            Marshal.FreeHGlobal(name);
            CheckError(err);
            return val;
        }
        /// <summary>
        /// Read the value of a boolean input argument for an invocation
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this input argument</param>
        /// <returns>Value of the input argument</returns>
        public unsafe bool ReadBool(String aName)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            uint val;
            int err = DvInvocationReadBool(iHandle, name, &val);
            Marshal.FreeHGlobal(name);
            CheckError(err);
            return (val != 0);
        }
        /// <summary>
        /// Read the value of a string input argument for an invocation
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this input argument</param>
        /// <returns>Value of the input argument</returns>
        public unsafe String ReadString(String aName)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            IntPtr ptr;
            uint len;
            int err = DvInvocationReadStringAsBuffer(iHandle, name, &ptr, &len);
            Marshal.FreeHGlobal(name);
            String str = InteropUtils.PtrToStringUtf8(ptr, len);
            OhNetFree(ptr);
            CheckError(err);
            return str;
        }
        /// <summary>
        /// Read the value of a binary input argument for an invocation
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this input argument</param>
        /// <returns>Value of the input argument</returns>
        public unsafe byte[] ReadBinary(String aName)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            IntPtr data;
            uint len;
            int err = DvInvocationReadBinary(iHandle, name, &data, &len);
            Marshal.FreeHGlobal(name);

            byte[] bin = new byte[len];
            if (len > 0)
            {
                Marshal.Copy(data, bin, 0, (int)len);
            }
            OhNetFree((IntPtr)data);
            CheckError(err);
            return bin;
        }
        /// <summary>
        /// Complete reading (input arguments for) an invocation
        /// </summary>
        /// <remarks>Must be called after the values of all input arguments are read.
        /// Must be called for invocations with no input arguments.</remarks>
        public void ReadEnd()
        {
            int err = DvInvocationReadEnd(iHandle);
            CheckError(err);
        }
        /// <summary>
        /// Report an error reading or writing an invocation
        /// </summary>
        /// <remarks>Must be called if ReadEnd() isn't reached.
        /// May be called if WriteStart() or later have been called.</remarks>
        /// <param name="aCode">Error code</param>
        /// <param name="aDescription">Error description</param>
        public unsafe void ReportError(uint aCode, String aDescription)
        {
            IntPtr desc = InteropUtils.StringToHGlobalUtf8(aDescription);
            // no point in propogating any error - client code can't cope with error reporting failing
            DvInvocationReportError(iHandle, aCode, desc);
            Marshal.FreeHGlobal(desc);
        }
        /// <summary>
        /// Begin reading (output arguments for) an invocation
        /// </summary>
        /// <remarks>Must be called before the values of any output arguments are written.
        /// Must be called for invocations with no output arguments.</remarks>
        public void WriteStart()
        {
            CheckError(DvInvocationWriteStart(iHandle));
        }
        /// <summary>
        /// Set the value of an integer output argument for an invocation.
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this output argument</param>
        /// <param name="aValue">Value of the output argument</param>
        public unsafe void WriteInt(String aName, int aValue)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            int err = DvInvocationWriteInt(iHandle, name, aValue);
            Marshal.FreeHGlobal(name);
            CheckError(err);
        }
        /// <summary>
        /// Set the value of an unsigned integer output argument for an invocation.
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this output argument</param>
        /// <param name="aValue">Value of the output argument</param>
        public unsafe void WriteUint(String aName, uint aValue)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            int err = DvInvocationWriteUint(iHandle, name, aValue);
            Marshal.FreeHGlobal(name);
            CheckError(err);
        }
        /// <summary>
        /// Set the value of a boolean output argument for an invocation.
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this output argument</param>
        /// <param name="aValue">Value of the output argument</param>
        public unsafe void WriteBool(String aName, bool aValue)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            uint val = (aValue? 1u : 0u);
            int err = DvInvocationWriteBool(iHandle, name, val);
            Marshal.FreeHGlobal(name);
            CheckError(err);
        }
        /// <summary>
        /// Set the value of a string output argument for an invocation.
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this output argument</param>
        /// <param name="aValue">Value of the output argument</param>
        public unsafe void WriteString(String aName, String aValue)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            IntPtr value = InteropUtils.StringToHGlobalUtf8(aValue);
            int err = DvInvocationWriteStringStart(iHandle, name);
            if (err == 0)
                err = DvInvocationWriteString(iHandle, value);
            Marshal.FreeHGlobal(value);
            if (err == 0)
                err = DvInvocationWriteStringEnd(iHandle, name);
            Marshal.FreeHGlobal(name);
            CheckError(err);
        }
        /// <summary>
        /// Set the value of a binary output argument for an invocation.
        /// </summary>
        /// <param name="aName">Name of the parameter associated with this output argument</param>
        /// <param name="aData">Value of the output argument</param>
        public unsafe void WriteBinary(String aName, byte[] aData)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            int err = DvInvocationWriteBinaryStart(iHandle, name);
            if (err == 0)
            {
                fixed (byte* data = aData)
                {
                    err = DvInvocationWriteBinary(iHandle, data, (uint)aData.Length);
                }
            }
            if (err == 0)
            {
                err = DvInvocationWriteBinaryEnd(iHandle, name);
            }
            Marshal.FreeHGlobal(name);
            CheckError(err);
        }
        /// <summary>
        /// Complete writing (output arguments for) an invocation
        /// </summary>
        /// <remarks>Must be called after the values of all output arguments are written.
        /// Must be called for invocations with no output arguments.</remarks>
        public void WriteEnd()
        {
            CheckError(DvInvocationWriteEnd(iHandle));
        }
        public void ReportActionError(ActionError aException, string aActionName)
        {
            uint errCode = aException.Code;
            if (errCode == 0)
                errCode = 501;

            String msg = aException.Message;
            if (msg == null || msg.Length == 0)
                msg = String.Format("Action {0} failed", aActionName);

            ReportError(errCode, msg);
        }
        private void CheckError(int aError)
        {
            if (aError != 0)
            {
                throw (new ActionError());
            }
        }
    }
}
