using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Zapp
{
    public abstract class IResourceWriter
    {
        public abstract void WriteResourceBegin(int aTotalBytes, string aMimeType);
        public abstract void WriteResource(byte[] aData, int aBytes);
        public abstract void WriteResourceEnd();
    }

    public abstract class IResourceManager
    {
        public abstract void WriteResource(string aUriTail, uint aIpAddress, IResourceWriter aWriter);
    }

    class ResourceWriter : IResourceWriter
    {
        private IntPtr iWriterData;
        private DvDevice.CallbackWriteResourceBegin iWriteBegin;
        private DvDevice.CallbackWriteResource iWriteResource;
        private DvDevice.CallbackWriteResourceEnd iWriteEnd;

        public ResourceWriter(IResourceManager aManager, string aUriTail, uint aInterface, IntPtr aWriterData,
                              DvDevice.CallbackWriteResourceBegin aWriteBegin,
                              DvDevice.CallbackWriteResource aWriteResource,
                              DvDevice.CallbackWriteResourceEnd aWriteEnd)
        {
            iWriterData = aWriterData;
            iWriteBegin = aWriteBegin;
            iWriteResource = aWriteResource;
            iWriteEnd = aWriteEnd;
            aManager.WriteResource(aUriTail, aInterface, this);
        }

        public unsafe override void WriteResourceBegin(int aTotalBytes, string aMimeType)
        {
            char* mimeType = (char*)Marshal.StringToHGlobalAnsi(aMimeType).ToPointer();
            iWriteBegin(iWriterData, aTotalBytes, mimeType);
            Marshal.FreeHGlobal((IntPtr)mimeType);
        }

        public override void WriteResource(byte[] aData, int aBytes)
        {
            iWriteResource(iWriterData, aData, aBytes);
        }

        public override void WriteResourceEnd()
        {
            iWriteEnd(iWriterData);
        }
    }
    
    public class DvDevice : IDisposable
    {
        [DllImport("ZappUpnp")]
        static extern unsafe IntPtr DvDeviceCreateNoResources(char* aUdn);
        [DllImport("ZappUpnp")]
        static extern unsafe IntPtr DvDeviceCreate(char* aUdn, CallbackResourceManager aResourceManager, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern void DvDeviceDestroy(IntPtr aDevice);
        [DllImport("ZappUpnp")]
        static extern unsafe char* DvDeviceUdn(IntPtr aDevice);
        [DllImport("ZappUpnp")]
        static extern int DvDeviceEnabled(IntPtr aDevice);
        [DllImport("ZappUpnp")]
        static extern void DvDeviceSetEnabled(IntPtr aDevice);
        [DllImport("ZappUpnp")]
        static extern unsafe void DvDeviceSetDisabled(IntPtr aDevice, DisableCompleted aCompleted, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void DvDeviceGetAttribute(IntPtr aDevice, char* aKey, char** aValue);
        [DllImport("ZappUpnp")]
        static extern unsafe void DvDeviceSetAttribute(IntPtr aDevice, char* aKey, char* aValue);
        [DllImport("ZappUpnp")]
        static extern unsafe void DvDeviceSetXmlExtension(IntPtr aDevice, char* aXml);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        public delegate void Callback();
        private delegate void DisableCompleted(IntPtr aPtr);
        public unsafe delegate void CallbackWriteResourceBegin(IntPtr aPtr, int aTotalBytes, char* aMimeType);
        public delegate void CallbackWriteResource(IntPtr aPtr, byte[] aData, int aBytes);
        public delegate void CallbackWriteResourceEnd(IntPtr aPtr);
        private unsafe delegate void CallbackResourceManager(IntPtr aUserData, char* aUriTail, uint aInterface, IntPtr aWriterData,
                                                             CallbackWriteResourceBegin aWriteBegin,
                                                             CallbackWriteResource aWriteResource,
                                                             CallbackWriteResourceEnd aWriteEnd);

        private IntPtr iHandle;
        private GCHandle iGch;
        private IResourceManager iResourceManager;

        public unsafe DvDevice(string aUdn)
        {
            char* udn = (char*)Marshal.StringToHGlobalAnsi(aUdn).ToPointer();
            iHandle = DvDeviceCreateNoResources(udn);
            Marshal.FreeHGlobal((IntPtr)udn);
        }

        public unsafe DvDevice(string aUdn, IResourceManager aResourceManager)
        {
            iResourceManager = aResourceManager;
            iGch = GCHandle.Alloc(this);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            char* udn = (char*)Marshal.StringToHGlobalAnsi(aUdn).ToPointer();
            iHandle = DvDeviceCreate(udn, WriteResource, ptr);
            Marshal.FreeHGlobal((IntPtr)udn);
        }

        private static unsafe void WriteResource(IntPtr aUserData, char* aUriTail, uint aInterface, IntPtr aWriterData,
                                                 CallbackWriteResourceBegin aWriteBegin,
                                                 CallbackWriteResource aWriteResource,
                                                 CallbackWriteResourceEnd aWriteEnd)
        {
            GCHandle gch = GCHandle.FromIntPtr(aUserData);
            DvDevice self = (DvDevice)gch.Target;
            string uriTail = Marshal.PtrToStringAnsi((IntPtr)aUriTail);
            ResourceWriter writer = new ResourceWriter(self.iResourceManager, uriTail, aInterface, aWriterData, aWriteBegin, aWriteResource, aWriteEnd);
        }

        public unsafe String Udn()
        {
            IntPtr ip = (IntPtr)DvDeviceUdn(iHandle);
            String udn = Marshal.PtrToStringAnsi(ip);
            return udn;
        }
        
        public bool Enabled()
        {
            int enabled = DvDeviceEnabled(iHandle);
            if (enabled != 0)
            {
                return true;
            }
            return false;
        }

        public void SetEnabled()
        {
            DvDeviceSetEnabled(iHandle);
        }

        public void SetDisabled(Callback aCompleted)
        {
            GCHandle gch = GCHandle.Alloc(aCompleted);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            DvDeviceSetDisabled(iHandle, Disabled, ptr);
        }

        private static void Disabled(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            Callback cb = (Callback)gch.Target;
            gch.Free();
            cb();
        }
        
        public unsafe void GetAttribute(string aKey, out string aValue)
        {
            char* key = (char*)Marshal.StringToHGlobalAnsi(aKey).ToPointer();
            char* value;
            DvDeviceGetAttribute(iHandle, key, &value);
            Marshal.FreeHGlobal((IntPtr)key);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }
        
        public unsafe void SetAttribute(string aKey, string aValue)
        {
            char* key = (char*)Marshal.StringToHGlobalAnsi(aKey).ToPointer();
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            DvDeviceSetAttribute(iHandle, key, value);
            Marshal.FreeHGlobal((IntPtr)key);
            Marshal.FreeHGlobal((IntPtr)value);
        }

        public unsafe void SetXmlExtension(string aXml)
        {
            char* xml = (char*)Marshal.StringToHGlobalAnsi(aXml).ToPointer();
            DvDeviceSetXmlExtension(iHandle, xml);
            Marshal.FreeHGlobal((IntPtr)xml);
        }

        public IntPtr Handle()
        {
            return iHandle;
        }
        
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvDevice()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            DvDeviceDestroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}
