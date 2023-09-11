using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device
{
    public class ResourceWriterError : Exception
    {
    }
    
    /// <summary>
    /// Interface passed to implementors of DvDevice allowing them to serve UI files to Control Points
    /// </summary>
    public interface IResourceWriter
    {
        /// <summary>
        /// Must be called before writing any file data
        /// </summary>
        /// <param name="aTotalBytes">Size in bytes of the file.  Can be 0 if size is unknown.</param>
        /// <param name="aMimeType">MIME type of the file.  May be NULL if this is unknown.</param>
        void WriteResourceBegin(int aTotalBytes, string aMimeType);
        /// <summary>
        /// Called to write a block of file data
        /// </summary>
        /// <remarks>Will be called 0..n times after WriteResourceBegin and before WriteResourceEnd</remarks>
        /// <param name="aData">File data to write</param>
        /// <param name="aBytes">Size in bytes of aData</param>
        void WriteResource(byte[] aData, int aBytes);
        /// <summary>
        /// Called when serving of a file is complete
        /// </summary>
        /// <remarks>Must only be called after a call to WriteResourceBegin.
        /// 
        /// An error writing the file can be inferred if WriteResource has not been called or
        /// if aTotalBytes was non-zero in the WriteResourceBegin callback and the sum of aBytes
        /// values in the WriteResource callbacks does not match aTotalBytes.</remarks>
        void WriteResourceEnd();
    }

    /// <summary>
    /// Interface used by devices to publish data (typically files)
    /// </summary>
    public interface IResourceManager
    {
        void WriteResource(string aUriTail, uint aIpAddress, List<string> aLanguageList, IResourceWriter aWriter);
    }

    /// <summary>
    /// Helper class for writing resources (files) to native code
    /// </summary>
    /// @internal
    class ResourceWriter : IResourceWriter
    {
        private IntPtr iWriterData;
        private DvDeviceStandard.CallbackWriteResourceBegin iWriteBegin;
        private DvDeviceStandard.CallbackWriteResource iWriteResource;
        private DvDeviceStandard.CallbackWriteResourceEnd iWriteEnd;

        public ResourceWriter(IntPtr aWriterData,
                              DvDeviceStandard.CallbackWriteResourceBegin aWriteBegin,
                              DvDeviceStandard.CallbackWriteResource aWriteResource,
                              DvDeviceStandard.CallbackWriteResourceEnd aWriteEnd)
        {
            iWriterData = aWriterData;
            iWriteBegin = aWriteBegin;
            iWriteResource = aWriteResource;
            iWriteEnd = aWriteEnd;
        }

        public void Write(IResourceManager aManager, string aUriTail, uint aInterface, List<string> aLanguageList)
        {
            aManager.WriteResource(aUriTail, aInterface, aLanguageList, this);
        }                              
        
        public void WriteResourceBegin(int aTotalBytes, string aMimeType)
        {
            IntPtr mimeType = InteropUtils.StringToHGlobalUtf8(aMimeType);
            int err = iWriteBegin(iWriterData, aTotalBytes, mimeType);
            Marshal.FreeHGlobal(mimeType);
            if (err != 0)
                throw new ResourceWriterError();
        }

        public void WriteResource(byte[] aData, int aBytes)
        {
            int err = iWriteResource(iWriterData, aData, aBytes);
            if (err != 0)
                throw new ResourceWriterError();
        }

        public void WriteResourceEnd()
        {
            int err = iWriteEnd(iWriterData);
            if (err != 0)
                throw new ResourceWriterError();
        }
    }

    /// <summary>
    /// A factory to create DvDevices.
    /// </summary>
    public interface IDvDeviceFactory
    {
        /// <summary>
        /// Constructor.  Creates a device without support for any protocol but capable of adding services or attributes.
        /// This should only be used with CpDeviceDv.
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        OpenHome.Net.Device.IDvDevice CreateDevice(string aUdn);

        /// <summary>
        /// Constructor.  Creates a device capable of operating on any of the protocols the device
        /// stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        OpenHome.Net.Device.IDvDevice CreateDeviceStandard(string aUdn);

        /// <summary>
        /// Constructor.  Creates a device capable of serving UI files and of operating on any of the
        /// protocols the device stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        /// <param name="aResourceManager">Allows the owner of a device to serve UI files.</param>
        OpenHome.Net.Device.IDvDevice CreateDeviceStandard(string aUdn, IResourceManager aResourceManager);
    }

    /// <summary>
    /// The default factory for DvDevices. Creates devices normally.
    /// </summary>
    public class DvDeviceFactory : IDvDeviceFactory
    {
        private OpenHome.Net.Core.DeviceStack iDeviceStack;

        /// <summary>
        /// Create a new device factory. Requires a running device stack.
        /// </summary>
        public DvDeviceFactory(OpenHome.Net.Core.DeviceStack aDeviceStack)
        {
            iDeviceStack = aDeviceStack;
            if (iDeviceStack == null)
            {
                throw new ArgumentNullException("aDeviceStack");
            }
        }

        /// <summary>
        /// Constructor.  Creates a device without support for any protocol but capable of adding services or attributes.
        /// This should only be used with CpDeviceDv.
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        public OpenHome.Net.Device.DvDevice CreateDevice(string aUdn)
        {
            return new DvDevice(aUdn);
        }


        /// <summary>
        /// Constructor.  Creates a device capable of operating on any of the protocols the device
        /// stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        public OpenHome.Net.Device.DvDevice CreateDeviceStandard(string aUdn)
        {
            return new DvDeviceStandard(aUdn);
        }

        /// <summary>
        /// Constructor.  Creates a device capable of serving UI files and of operating on any of the
        /// protocols the device stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        /// <param name="aResourceManager">Allows the owner of a device to serve UI files</param>
        public OpenHome.Net.Device.DvDevice CreateDeviceStandard(string aUdn, IResourceManager aResourceManager)
        {
            return new DvDeviceStandard(aUdn, aResourceManager);
        }

        // Explicit interface implementations. These forward to the regular methods.

        /// <summary>
        /// Constructor.  Creates a device without support for any protocol but capable of adding services or attributes.
        /// This should only be used with CpDeviceDv.
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        OpenHome.Net.Device.IDvDevice IDvDeviceFactory.CreateDevice(string aUdn)
        {
            return CreateDevice(aUdn);
        }

        /// <summary>
        /// Constructor.  Creates a device capable of operating on any of the protocols the device
        /// stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        OpenHome.Net.Device.IDvDevice IDvDeviceFactory.CreateDeviceStandard(string aUdn)
        {
            return CreateDeviceStandard(aUdn);
        }

        /// <summary>
        /// Constructor.  Creates a device capable of serving UI files and of operating on any of the
        /// protocols the device stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.</param>
        /// <param name="aResourceManager">Allows the owner of a device to serve UI files</param>
        OpenHome.Net.Device.IDvDevice IDvDeviceFactory.CreateDeviceStandard(string aUdn, IResourceManager aResourceManager)
        {
            return CreateDeviceStandard(aUdn, aResourceManager);
        }
    }

    /// <summary>
    /// Interface to allow unit-testing of code that uses DvDevices.
    /// </summary>
    public interface IDvDevice : IDisposable
    {
        /// <summary>
        /// Constructing providers cannot be done with just the interface.
        /// A genuine instance of DvDevice is required. This provides access
        /// to it.
        /// </summary>
        DvDevice RawDevice { get; }
        string Udn();
        bool Enabled();
        void SetEnabled();
        void SetDisabled(System.Action aCompleted);
        void GetAttribute(string aKey, out string aValue);
        void SetAttribute(string aKey, string aValue);
        IntPtr Handle();
    }

    public class DvDevice : IDvDevice
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr DvDeviceCreate(IntPtr aUdn);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvDeviceDestroy(IntPtr aDevice);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvDeviceGetUdn(IntPtr aDevice, out IntPtr aUdn, out uint aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern int DvDeviceEnabled(IntPtr aDevice);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvDeviceSetEnabled(IntPtr aDevice);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvDeviceSetDisabled(IntPtr aDevice, DisabledCallback aCompleted, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvDeviceGetAttribute(IntPtr aDevice, IntPtr aKey, out IntPtr aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvDeviceSetAttribute(IntPtr aDevice, IntPtr aKey, IntPtr aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetFree(IntPtr aPtr);

        protected IntPtr iHandle;
        protected GCHandle iGch;
        private delegate void DisabledCallback(IntPtr aPtr);
        private DisabledCallback iCallbackDisabled;

        /// <summary>
        /// Constructor.  Creates a device without support for any protocol but capable of adding services or attributes.
        /// This should only be used with CpDeviceDv.
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.  The caller is responsible for calculating/assigning this</param>
        public DvDevice(string aUdn)
        {
            IntPtr udn = InteropUtils.StringToHGlobalUtf8(aUdn);
            iHandle = DvDeviceCreate(udn);
            Marshal.FreeHGlobal(udn);
            iCallbackDisabled = new DisabledCallback(Disabled);
        }

        DvDevice IDvDevice.RawDevice { get { return this; } }

        protected DvDevice()
        {
            iCallbackDisabled = new DisabledCallback(Disabled);
        }

        /// <summary>
        /// Query the (client-specified) unique device name
        /// </summary>
        /// <returns>The name passed to the c'tor</returns>
        public String Udn()
        {
            IntPtr ptr;
            uint len;
            DvDeviceGetUdn(iHandle, out ptr, out len);
            String udn = InteropUtils.PtrToStringUtf8(ptr, len);
            return udn;
        }
        
        /// <summary>
        /// Query whether a device is enabled
        /// </summary>
        /// <returns>true if the device is enabled; false otherwise</returns>
        public bool Enabled()
        {
            int enabled = DvDeviceEnabled(iHandle);
            if (enabled != 0)
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// Set the device ready for external use
        /// </summary>
        /// <remarks>When this returns, the device will be available for use using any of the protocols
        /// the device stack supports.  Services must not be added (DvProvider-derived classes
        /// created using this device) and attributes must not be set while a device is enabled.
        /// If these need to change in future, the device must first be disabled.</remarks>
        public void SetEnabled()
        {
            DvDeviceSetEnabled(iHandle);
        }

        /// <summary>
        /// Disable the device, withdrawing its availability for external use
        /// </summary>
        /// <remarks>Services can be added and attributes can be set once a device is disabled.  The device
        /// will not be available for use again until SetEnabled() is called again.
        /// 
        /// This call is asynchronous so returns before the device is fully disabled.  Wait for the
        /// aCompleted callback before adding services or setting attributes.</remarks>
        /// <param name="aCompleted">Callback which runs when the device is fully disabled.
        /// Until this runs, the device should be considered to still be enabled.</param>
        public void SetDisabled(System.Action aCompleted)
        {
            GCHandle gch = GCHandle.Alloc(aCompleted);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            DvDeviceSetDisabled(iHandle, iCallbackDisabled, ptr);
        }

        private static void Disabled(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            System.Action cb = (System.Action)gch.Target;
            gch.Free();
            cb();
        }
        
        /// <summary>
        /// Query the value of an atrribute
        /// </summary>
        /// <param name="aKey">string of the form protocol_name.protocol_specific_key.
        /// Commonly used keys are published ... (!!!! where?)</param>
        /// <param name="aValue">string containing the attribute or null if the attribute has not been set.</param>
        public void GetAttribute(string aKey, out string aValue)
        {
            IntPtr key = InteropUtils.StringToHGlobalUtf8(aKey);
            IntPtr value;
            DvDeviceGetAttribute(iHandle, key, out value);
            Marshal.FreeHGlobal(key);
            aValue = InteropUtils.PtrToStringUtf8(value);
        }
        
        /// <summary>
        /// Set the value of an attribute
        /// </summary>
        /// <param name="aKey">string of the form protocol_name.protocol_specific_key</param>
        /// <param name="aValue">attribute will be set to a copy of this string</param>
        public void SetAttribute(string aKey, string aValue)
        {
            IntPtr key = InteropUtils.StringToHGlobalUtf8(aKey);
            IntPtr value = InteropUtils.StringToHGlobalUtf8(aValue);
            DvDeviceSetAttribute(iHandle, key, value);
            Marshal.FreeHGlobal(key);
            Marshal.FreeHGlobal(value);
        }

        /// <summary>
        /// Get the handle to the underlying native device
        /// </summary>
        /// <returns>Handle to the underlying native device</returns>
        public IntPtr Handle()
        {
            return iHandle;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DvDeviceDestroy(iHandle);
                iHandle = IntPtr.Zero;
                if (iGch.IsAllocated)
                    iGch.Free();
            }
        }
    }

    public class DvDeviceStandard : DvDevice
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr DvDeviceStandardCreateNoResources(IntPtr aUdn);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr DvDeviceStandardCreate(IntPtr aUdn, CallbackResourceManager aResourceManager, IntPtr aPtr);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void DvDeviceStandardGetResourceManagerUri(IntPtr aDevice, IntPtr aAdapter, out IntPtr aUri, out uint aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern uint DvResourceWriterLanguageCount(IntPtr aHandle);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr DvResourceWriterLanguage(IntPtr aHandle, uint aIndex);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void OhNetFree(IntPtr aPtr);

        public delegate int CallbackWriteResourceBegin(IntPtr aPtr, int aTotalBytes, IntPtr aMimeType);
        public delegate int CallbackWriteResource(IntPtr aPtr, byte[] aData, int aBytes);
        public delegate int CallbackWriteResourceEnd(IntPtr aPtr);
        private delegate int CallbackResourceManager(IntPtr aUserData, IntPtr aUriTail, uint aInterface, IntPtr aLanguageList, IntPtr aWriterData,
                                                     CallbackWriteResourceBegin aWriteBegin,
                                                     CallbackWriteResource aWriteResource,
                                                     CallbackWriteResourceEnd aWriteEnd);

        private IResourceManager iResourceManager;
        private CallbackResourceManager iCallbackResourceManager;

        /// <summary>
        /// Constructor.  Creates a device capable of operating on any of the protocols the device
        /// stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.  The caller is responsible for calculating/assigning this</param>
        public DvDeviceStandard(string aUdn)
        {
            IntPtr udn = InteropUtils.StringToHGlobalUtf8(aUdn);
            iHandle = DvDeviceStandardCreateNoResources(udn);
            Marshal.FreeHGlobal(udn);
        }

        /// <summary>
        /// Constructor.  Creates a device capable of serving UI files and of operating on any of the
        /// protocols the device stack supports as standard but with no services or attributes as yet
        /// </summary>
        /// <param name="aUdn">Universally unique identifier.  The caller is responsible for calculating/assigning this</param>
        /// <param name="aResourceManager">Allows the owner of a device to serve UI files</param>
        public DvDeviceStandard(string aUdn, IResourceManager aResourceManager)
        {
            iResourceManager = aResourceManager;
            iGch = GCHandle.Alloc(this);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            IntPtr udn = InteropUtils.StringToHGlobalUtf8(aUdn);
            iCallbackResourceManager = new CallbackResourceManager(WriteResource);
            iHandle = DvDeviceStandardCreate(udn, iCallbackResourceManager, ptr);
            Marshal.FreeHGlobal(udn);
        }

        /// <summary>
        /// Query the base uri for the resource manager.
        /// </summary>
        /// <param name="aAdapter">The network adapter to return a uri for.</param>
        /// <returns>The base uri.  May be empty if there is no resource manager.</returns>
        public string ResourceManagerUri(Core.NetworkAdapter aAdapter)
        {
            if (aAdapter == null)
                return "";
            IntPtr ptr;
            uint len;
            DvDeviceStandardGetResourceManagerUri(iHandle, aAdapter.Handle(), out ptr, out len);
            string uri = InteropUtils.PtrToStringUtf8(ptr, len);
            OhNetFree(ptr);
            return uri;
        }

        private static int WriteResource(IntPtr aUserData, IntPtr aUriTail, uint aInterface, IntPtr aLanguageList, IntPtr aWriterData,
                                         CallbackWriteResourceBegin aWriteBegin,
                                         CallbackWriteResource aWriteResource,
                                         CallbackWriteResourceEnd aWriteEnd)
        {
            GCHandle gch = GCHandle.FromIntPtr(aUserData);
            DvDeviceStandard self = (DvDeviceStandard)gch.Target;
            string uriTail = InteropUtils.PtrToStringUtf8(aUriTail);
            List<string> languageList = new List<string>();
            uint count = DvResourceWriterLanguageCount(aLanguageList);
            for (uint i = 0; i < count; i++)
            {
                languageList.Add(InteropUtils.PtrToStringUtf8(DvResourceWriterLanguage(aLanguageList, i)));
            }
            ResourceWriter writer = new ResourceWriter(aWriterData, aWriteBegin, aWriteResource, aWriteEnd);
            try
            {
                writer.Write(self.iResourceManager, uriTail, aInterface, languageList);

            }
            catch
            {
                return -1;
            }
            return 0;
        }
    }
}
