using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using System.Linq;
#if __IOS__
using ObjCRuntime;
#endif

namespace OpenHome.Net.Core
{
    /// <summary>
    /// Thrown when Value() is called on a Property whose value has never been set
    /// </summary>
    public class PropertyError : Exception
    {
    }


    /// <summary>
    /// Description of the type plus any bounds of action arguments plus properties.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    /// <remarks>Each action owns 0..n parameters;  each property owns exactly 1.</remarks>
    public class Parameter
    {
        protected IntPtr iHandle;

        public IntPtr Handle()
        {
            return iHandle;
        }

        protected Parameter()
        {
        }
    }

    /// <summary>
    /// Integer type parameter.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class ParameterInt : Parameter
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServiceParameterCreateInt(IntPtr aName, int aMinValue, int aMaxValue, int aStep);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aName">Parameter name</param>
        /// <param name="aMinValue">Minimum allowed value</param>
        /// <param name="aMaxValue">Maximum allowed value</param>
        /// <param name="aStep">Gap between allowed values</param>
        public ParameterInt(String aName, int aMinValue = Int32.MinValue, int aMaxValue = Int32.MaxValue, int aStep = 1)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServiceParameterCreateInt(name, aMinValue, aMaxValue, aStep);
            Marshal.FreeHGlobal(name);
        }
    }

    /// <summary>
    /// Unsigned integer type parameter.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class ParameterUint : Parameter
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServiceParameterCreateUint(IntPtr aName, uint aMinValue, uint aMaxValue, uint aStep);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aName">Parameter name</param>
        /// <param name="aMinValue">Minimum allowed value</param>
        /// <param name="aMaxValue">Maximum allowed value</param>
        /// <param name="aStep">Gap between allowed values</param>
        public ParameterUint(String aName, uint aMinValue = 0, uint aMaxValue = uint.MaxValue, uint aStep = 1)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServiceParameterCreateUint(name, aMinValue, aMaxValue, aStep);
            Marshal.FreeHGlobal(name);
        }
    }

    /// <summary>
    /// Boolean type parameter.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class ParameterBool : Parameter
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServiceParameterCreateBool(IntPtr aName);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aName">Parameter name</param>
        public ParameterBool(String aName)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServiceParameterCreateBool(name);
            Marshal.FreeHGlobal(name);
        }
    }

    /// <summary>
    /// String type parameter.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class ParameterString : Parameter
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServiceParameterCreateString(IntPtr aName, IntPtr[] aAllowedValues, uint aCount);

        /// <summary>
        ///
        /// </summary>
        /// <param name="aName">Parameter name</param>
        /// <param name="aAllowedValues">List of allowed values for the string</param>
        public ParameterString(String aName, List<String> aAllowedValues)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            IntPtr[] allowed = aAllowedValues.Select<string, IntPtr>(InteropUtils.StringToHGlobalUtf8).ToArray();
            iHandle = ServiceParameterCreateString(name, allowed, (uint)aAllowedValues.Count);
            foreach (IntPtr allowedValue in allowed)
            {
                Marshal.FreeHGlobal(allowedValue);
            }
            Marshal.FreeHGlobal(name);
        }
    }

    /// <summary>
    /// String type parameter.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class ParameterBinary : Parameter
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServiceParameterCreateBinary(IntPtr aName);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aName">Parameter name</param>
        public ParameterBinary(String aName)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServiceParameterCreateBinary(name);
            Marshal.FreeHGlobal(name);
        }
    }

    public class ParameterRelated : Parameter
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServiceParameterCreateRelated(IntPtr aName, IntPtr aProperty);

        public ParameterRelated(String aName, OpenHome.Net.Core.Property aProperty)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServiceParameterCreateRelated(name, aProperty.Handle());
            Marshal.FreeHGlobal(name);
        }
    }

    /// <summary>
    /// (Service) Property.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    /// <remarks>One Property will be created per Property (state variable) for the Service</remarks>
    public class Property : IDisposable
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyDestroy(IntPtr aHandle);

        protected delegate void Callback(IntPtr aPtr);

        protected IntPtr iHandle;
        protected GCHandle iGch;
        protected Callback iCallbackValueChanged;
        private System.Action iValueChanged;
        private bool iOwnsNativeProperty;

        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                iGch.Free();
                if (iOwnsNativeProperty)
                    ServicePropertyDestroy(iHandle);
                iHandle = IntPtr.Zero;
            }
        }

        public static void CallPropertyChangedDelegate(System.Action aDelegate)
        {
            try
            {
                aDelegate();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown", new object[] { e });
                System.Diagnostics.Debug.WriteLine("         No exceptions should be thrown by property change delegates");
            }
        }

        internal IntPtr Handle()
        {
            return iHandle;
        }

        protected Property(bool aOwnsNativeProperty)
        {
            iGch = GCHandle.Alloc(this);
            iOwnsNativeProperty = aOwnsNativeProperty;
        }

        protected Property(System.Action aValueChanged)
        {
            iGch = GCHandle.Alloc(this);
            iValueChanged = aValueChanged;
            iCallbackValueChanged = new Callback(ValueChanged);
        }

#if __IOS__
        [MonoPInvokeCallback (typeof (Callback))]
#endif
        private static void ValueChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            Property self = (Property)gch.Target;
            CallPropertyChangedDelegate(self.iValueChanged);
        }
    }

    /// <summary>
    /// Integer type property.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class PropertyInt : Property
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateIntCp(IntPtr aName, Callback aCallback, IntPtr aPtr);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateIntDv(IntPtr aParameterHandle);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int ServicePropertyValueInt(IntPtr aHandle, out int aValue);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint ServicePropertySetValueInt(IntPtr aHandle, int aValue);

        /// <summary>
        /// Constructor suitable for use by clients of the control point stack
        /// </summary>
        /// <param name="aName">Property name</param>
        /// <param name="aValueChanged">Action to run when the property's value changes</param>
        public PropertyInt(String aName, System.Action aValueChanged)
            : base(aValueChanged)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServicePropertyCreateIntCp(name, iCallbackValueChanged, ptr);
            Marshal.FreeHGlobal(name);
        }

        /// <summary>
        /// Constructor suitable for use by clients of the device stack
        /// </summary>
        /// <param name="aParameter">Parameter defining the name and any value bounds for the property.</param>
        /// <param name="aOwnsNativeProperty">Whether the managed property owns the underlying native property.</param>
        public PropertyInt(ParameterInt aParameter, bool aOwnsNativeProperty = false)
            : base(aOwnsNativeProperty)
        {
            iHandle = ServicePropertyCreateIntDv(aParameter.Handle());
        }

        /// <summary>
        /// Query the value of the property
        /// </summary>
        /// <returns>Integer property value</returns>
        public int Value()
        {
            int val;
            if (ServicePropertyValueInt(iHandle, out val) == -1)
                throw new PropertyError();
            return val;
        }

        /// <summary>
        /// Set the value of the property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>True if the property's value was changed; false otherwise</returns>
        public bool SetValue(int aValue)
        {
            uint changed = ServicePropertySetValueInt(iHandle, aValue);
            return (changed != 0);
        }
    }

    /// <summary>
    /// Unsigned integer type property.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class PropertyUint : Property
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateUintCp(IntPtr aName, Callback aCallback, IntPtr aPtr);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateUintDv(IntPtr aParameterHandle);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int ServicePropertyValueUint(IntPtr aHandle, out uint aValue);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint ServicePropertySetValueUint(IntPtr aHandle, uint aValue);

        /// <summary>
        /// Constructor suitable for use by clients of the control point stack
        /// </summary>
        /// <param name="aName">Property name</param>
        /// <param name="aValueChanged">Action to run when the property's value changes</param>
        public PropertyUint(String aName, System.Action aValueChanged)
            : base(aValueChanged)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServicePropertyCreateUintCp(name, iCallbackValueChanged, ptr);
            Marshal.FreeHGlobal(name);
        }

        /// <summary>
        /// Constructor suitable for use by clients of the device stack
        /// </summary>
        /// <param name="aParameter">Parameter defining the name and any value bounds for the property.</param>
        /// <param name="aOwnsNativeProperty">Whether the managed property owns the underlying native property.</param>
        public PropertyUint(ParameterUint aParameter, bool aOwnsNativeProperty = false)
            : base(aOwnsNativeProperty)
        {
            iHandle = ServicePropertyCreateUintDv(aParameter.Handle());
        }

        /// <summary>
        /// Query the value of the property
        /// </summary>
        /// <returns>Unsigned integer property value</returns>
        public uint Value()
        {
            uint val;
            if (ServicePropertyValueUint(iHandle, out val) == -1)
                throw new PropertyError();
            return val;
        }

        /// <summary>
        /// Set the value of the property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>True if the property's value was changed; false otherwise</returns>
        public bool SetValue(uint aValue)
        {
            uint changed = ServicePropertySetValueUint(iHandle, aValue);
            return (changed != 0);
        }
    }

    /// <summary>
    /// Boolean type property.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class PropertyBool : Property
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateBoolCp(IntPtr aName, Callback aCallback, IntPtr aPtr);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateBoolDv(IntPtr aParameterHandle);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int ServicePropertyValueBool(IntPtr aHandle, out uint aValue);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint ServicePropertySetValueBool(IntPtr aHandle, uint aValue);

        /// <summary>
        /// Constructor suitable for use by clients of the control point stack
        /// </summary>
        /// <param name="aName">Property name</param>
        /// <param name="aValueChanged">Action to run when the property's value changes</param>
        public PropertyBool(String aName, System.Action aValueChanged)
            : base(aValueChanged)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServicePropertyCreateBoolCp(name, iCallbackValueChanged, ptr);
            Marshal.FreeHGlobal(name);
        }

        /// <summary>
        /// Constructor suitable for use by clients of the device stack
        /// </summary>
        /// <param name="aParameter">Parameter defining the name for the property.</param>
        /// <param name="aOwnsNativeProperty">Whether the managed property owns the underlying native property.</param>
        public PropertyBool(ParameterBool aParameter, bool aOwnsNativeProperty = false)
            : base(aOwnsNativeProperty)
        {
            iHandle = ServicePropertyCreateBoolDv(aParameter.Handle());
        }

        /// <summary>
        /// Query the value of the property
        /// </summary>
        /// <returns>Boolean property value</returns>
        public bool Value()
        {
            uint val;
            if (ServicePropertyValueBool(iHandle, out val) == -1)
                throw new PropertyError();
            return (val != 0);
        }

        /// <summary>
        /// Set the value of the property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>True if the property's value was changed; false otherwise</returns>
        public bool SetValue(bool aValue)
        {
            uint val = (aValue ? 1u : 0u);
            uint changed = ServicePropertySetValueBool(iHandle, val);
            return (changed != 0);
        }
    }

    /// <summary>
    /// String type property.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class PropertyString : Property
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateStringCp(IntPtr aName, Callback aCallback, IntPtr aPtr);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateStringDv(IntPtr aParameterHandle);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int ServicePropertyGetValueString(IntPtr aHandle, out IntPtr aData, out uint aLen);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetFree(IntPtr aPtr);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint ServicePropertySetValueString(IntPtr aHandle, IntPtr aValue);

        /// <summary>
        /// Constructor suitable for use by clients of the control point stack
        /// </summary>
        /// <param name="aName">Property name</param>
        /// <param name="aValueChanged">Action to run when the property's value changes</param>
        public PropertyString(String aName, System.Action aValueChanged)
            : base(aValueChanged)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServicePropertyCreateStringCp(name, iCallbackValueChanged, ptr);
            Marshal.FreeHGlobal(name);
        }

        /// <summary>
        /// Constructor suitable for use by clients of the device stack
        /// </summary>
        /// <param name="aParameter">Parameter defining the name and any set of allowed values for the property.</param>
        /// <param name="aOwnsNativeProperty">Whether the managed property owns the underlying native property.</param>
        public PropertyString(ParameterString aParameter, bool aOwnsNativeProperty = false)
            : base(aOwnsNativeProperty)
        {
            iHandle = ServicePropertyCreateStringDv(aParameter.Handle());
        }

        /// <summary>
        /// Query the value of the property
        /// </summary>
        /// <returns>String property value</returns>
        public String Value()
        {
            IntPtr ptr;
            uint len;
            if (ServicePropertyGetValueString(iHandle, out ptr, out len) == -1)
                throw new PropertyError();
            String str = InteropUtils.PtrToStringUtf8(ptr, len);
            OhNetFree(ptr);
            return str;
        }

        /// <summary>
        /// Set the value of the property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>True if the property's value was changed; false otherwise</returns>
        public bool SetValue(string aValue)
        {
            IntPtr val = InteropUtils.StringToHGlobalUtf8(aValue);
            uint changed = ServicePropertySetValueString(iHandle, val);
            Marshal.FreeHGlobal(val);
            return (changed != 0);
        }
    }

    /// <summary>
    /// Binary type property.  Only intended for use by auto-generated proxies and providers.
    /// </summary>
    public class PropertyBinary : Property
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateBinaryCp(IntPtr aName, Callback aCallback, IntPtr aPtr);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServicePropertyCreateBinaryDv(IntPtr aParameterHandle);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int ServicePropertyGetValueBinary(IntPtr aHandle, out IntPtr aData, out uint aLen);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint ServicePropertySetValueBinary(IntPtr aHandle, IntPtr aData, uint aLen);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetFree(IntPtr aPtr);

        /// <summary>
        /// Constructor suitable for use by clients of the control point stack
        /// </summary>
        /// <param name="aName">Property name</param>
        /// <param name="aValueChanged">Action to run when the property's value changes</param>
        public PropertyBinary(String aName, System.Action aValueChanged)
            : base(aValueChanged)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServicePropertyCreateBinaryCp(name, iCallbackValueChanged, ptr);
            Marshal.FreeHGlobal(name);
        }

        /// <summary>
        /// Constructor suitable for use by clients of the device stack
        /// </summary>
        /// <param name="aParameter">Parameter defining the name for the property.</param>
        /// <param name="aOwnsNativeProperty">Whether the managed property owns the underlying native property.</param>
        public PropertyBinary(ParameterBinary aParameter, bool aOwnsNativeProperty = false)
            : base(aOwnsNativeProperty)
        {
            iHandle = ServicePropertyCreateBinaryDv(aParameter.Handle());
        }

        /// <summary>
        /// Query the value of the property
        /// </summary>
        /// <returns>Binary property value</returns>
        public byte[] Value()
        {
            IntPtr pData;
            uint len;
            if (ServicePropertyGetValueBinary(iHandle, out pData, out len) == -1)
                throw new PropertyError();
            byte[] data = new byte[len];
            Marshal.Copy(pData, data, 0, (int)len);
            OhNetFree(pData);
            return data;
        }

        /// <summary>
        /// Set the value of the property
        /// </summary>
        /// <param name="aData">New value for the property</param>
        /// <returns>True if the property's value was changed; false otherwise</returns>
        public bool SetValue(byte[] aData)
        {
            uint changed;
            GCHandle h = GCHandle.Alloc(aData, GCHandleType.Pinned);
            changed = ServicePropertySetValueBinary(iHandle, h.AddrOfPinnedObject(), (uint)aData.Length);
            h.Free();
            return (changed != 0);
        }
    }

    /// <summary>
    /// (Service) Action
    /// </summary>
    /// <remarks>Each service has 0..n of these.  Each action has 0..n input parameters and
    /// 0..m output parameters.  Each parameter must be either input or output.</remarks>
    public class Action : IDisposable
    {
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr ServiceActionCreate(IntPtr aName);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void ServiceActionDestroy(IntPtr aAction);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void ServiceActionAddInputParameter(IntPtr aAction, IntPtr aParameter);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void ServiceActionAddOutputParameter(IntPtr aAction, IntPtr aParameter);
#if __IOS__
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void ServiceActionGetName(IntPtr aAction, out IntPtr aName, out uint aLen);

        private IntPtr iHandle;
        private List<Parameter> iInputParameters;
        private List<Parameter> iOutputParameters;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aName">Action name</param>
        public Action(String aName)
        {
            IntPtr name = InteropUtils.StringToHGlobalUtf8(aName);
            iHandle = ServiceActionCreate(name);
            Marshal.FreeHGlobal(name);
            iInputParameters = new List<Parameter>();
            iOutputParameters = new List<Parameter>();
        }

        /// <summary>
        /// Add an input parameter
        /// </summary>
        /// <param name="aParameter">Input parameter.  Ownership is passed to the action</param>
        public void AddInputParameter(Parameter aParameter)
        {
            iInputParameters.Add(aParameter);
            ServiceActionAddInputParameter(iHandle, aParameter.Handle());
        }

        /// <summary>
        /// Add an output parameter
        /// </summary>
        /// <param name="aParameter">Output parameter.  Ownership is passed to the action</param>
        public void AddOutputParameter(Parameter aParameter)
        {
            iOutputParameters.Add(aParameter);
            ServiceActionAddOutputParameter(iHandle, aParameter.Handle());
        }

        /// <summary>
        /// Retrieve an input parameter
        /// </summary>
        /// <param name="aIndex">(Zero-based) Index of the parameter</param>
        /// <returns>The relevant input parameter</returns>
        public Parameter InputParameter(int aIndex)
        {
            return iInputParameters[aIndex];
        }

        /// <summary>
        /// Retrieve an output parameter
        /// </summary>
        /// <param name="aIndex">(Zero-based) Index of the parameter</param>
        /// <returns>The relevant output parameter</returns>
        public Parameter OutputParameter(int aIndex)
        {
            return iOutputParameters[aIndex];
        }

        /// <summary>
        /// Query the name of the action
        /// </summary>
        /// <returns>Action name</returns>
        public String Name()
        {
            IntPtr str;
            uint len;
            ServiceActionGetName(iHandle, out str, out len);
            return InteropUtils.PtrToStringUtf8(str, len);
        }

        internal IntPtr Handle()
        {
            return iHandle;
        }

        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                ServiceActionDestroy(iHandle);
                iHandle = IntPtr.Zero;
            }
        }
    }
}
