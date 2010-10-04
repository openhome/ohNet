using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceUpnpOrgConnectionManager1 : IDisposable
    {
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern uint DvServiceUpnpOrgConnectionManager1Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvServiceUpnpOrgConnectionManager1Destroy(uint aHandle);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe int DvServiceUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe void DvServiceUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe int DvServiceUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe void DvServiceUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe int DvServiceUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern unsafe void DvServiceUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvServiceUpnpOrgConnectionManager1EnableActionGetProtocolInfo(uint aHandle, CallbackGetProtocolInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvServiceUpnpOrgConnectionManager1EnableActionPrepareForConnection(uint aHandle, CallbackPrepareForConnection aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvServiceUpnpOrgConnectionManager1EnableActionConnectionComplete(uint aHandle, CallbackConnectionComplete aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvServiceUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(uint aHandle, CallbackGetCurrentConnectionIDs aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgConnectionManager1")]
        static extern void DvServiceUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(uint aHandle, CallbackGetCurrentConnectionInfo aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetProtocolInfo(IntPtr aPtr, uint aVersion, char** aSource, char** aSink);
        private unsafe delegate int CallbackPrepareForConnection(IntPtr aPtr, uint aVersion, char* aRemoteProtocolInfo, char* aPeerConnectionManager, int aPeerConnectionID, char* aDirection, int* aConnectionID, int* aAVTransportID, int* aRcsID);
        private unsafe delegate int CallbackConnectionComplete(IntPtr aPtr, uint aVersion, int aConnectionID);
        private unsafe delegate int CallbackGetCurrentConnectionIDs(IntPtr aPtr, uint aVersion, char** aConnectionIDs);
        private unsafe delegate int CallbackGetCurrentConnectionInfo(IntPtr aPtr, uint aVersion, int aConnectionID, int* aRcsID, int* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int* aPeerConnectionID, char** aDirection, char** aStatus);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackGetProtocolInfo iCallbackGetProtocolInfo;
        private CallbackPrepareForConnection iCallbackPrepareForConnection;
        private CallbackConnectionComplete iCallbackConnectionComplete;
        private CallbackGetCurrentConnectionIDs iCallbackGetCurrentConnectionIDs;
        private CallbackGetCurrentConnectionInfo iCallbackGetCurrentConnectionInfo;

        public DvServiceUpnpOrgConnectionManager1(DvDevice aDevice)
        {
            iHandle = DvServiceUpnpOrgConnectionManager1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertySourceProtocolInfo(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgConnectionManager1SetPropertySourceProtocolInfo(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertySourceProtocolInfo(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgConnectionManager1GetPropertySourceProtocolInfo(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertySinkProtocolInfo(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgConnectionManager1SetPropertySinkProtocolInfo(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertySinkProtocolInfo(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgConnectionManager1GetPropertySinkProtocolInfo(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyCurrentConnectionIDs(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgConnectionManager1SetPropertyCurrentConnectionIDs(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyCurrentConnectionIDs(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgConnectionManager1GetPropertyCurrentConnectionIDs(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionGetProtocolInfo()
        {
            iCallbackGetProtocolInfo = new CallbackGetProtocolInfo(DoGetProtocolInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgConnectionManager1EnableActionGetProtocolInfo(iHandle, iCallbackGetProtocolInfo, ptr);
        }

        protected unsafe void EnableActionPrepareForConnection()
        {
            iCallbackPrepareForConnection = new CallbackPrepareForConnection(DoPrepareForConnection);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgConnectionManager1EnableActionPrepareForConnection(iHandle, iCallbackPrepareForConnection, ptr);
        }

        protected unsafe void EnableActionConnectionComplete()
        {
            iCallbackConnectionComplete = new CallbackConnectionComplete(DoConnectionComplete);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgConnectionManager1EnableActionConnectionComplete(iHandle, iCallbackConnectionComplete, ptr);
        }

        protected unsafe void EnableActionGetCurrentConnectionIDs()
        {
            iCallbackGetCurrentConnectionIDs = new CallbackGetCurrentConnectionIDs(DoGetCurrentConnectionIDs);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgConnectionManager1EnableActionGetCurrentConnectionIDs(iHandle, iCallbackGetCurrentConnectionIDs, ptr);
        }

        protected unsafe void EnableActionGetCurrentConnectionInfo()
        {
            iCallbackGetCurrentConnectionInfo = new CallbackGetCurrentConnectionInfo(DoGetCurrentConnectionInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgConnectionManager1EnableActionGetCurrentConnectionInfo(iHandle, iCallbackGetCurrentConnectionInfo, ptr);
        }

        protected virtual void GetProtocolInfo(uint aVersion, out string aSource, out string aSink)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void PrepareForConnection(uint aVersion, string aRemoteProtocolInfo, string aPeerConnectionManager, int aPeerConnectionID, string aDirection, out int aConnectionID, out int aAVTransportID, out int aRcsID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void ConnectionComplete(uint aVersion, int aConnectionID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetCurrentConnectionIDs(uint aVersion, out string aConnectionIDs)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetCurrentConnectionInfo(uint aVersion, int aConnectionID, out int aRcsID, out int aAVTransportID, out string aProtocolInfo, out string aPeerConnectionManager, out int aPeerConnectionID, out string aDirection, out string aStatus)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoGetProtocolInfo(IntPtr aPtr, uint aVersion, char** aSource, char** aSink)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgConnectionManager1 self = (DvServiceUpnpOrgConnectionManager1)gch.Target;
            string source;
            string sink;
            self.GetProtocolInfo(aVersion, out source, out sink);
            *aSource = (char*)Marshal.StringToHGlobalAnsi(source).ToPointer();
            *aSink = (char*)Marshal.StringToHGlobalAnsi(sink).ToPointer();
            return 0;
        }

        private static unsafe int DoPrepareForConnection(IntPtr aPtr, uint aVersion, char* aRemoteProtocolInfo, char* aPeerConnectionManager, int aPeerConnectionID, char* aDirection, int* aConnectionID, int* aAVTransportID, int* aRcsID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgConnectionManager1 self = (DvServiceUpnpOrgConnectionManager1)gch.Target;
            string remoteProtocolInfo = Marshal.PtrToStringAnsi((IntPtr)aRemoteProtocolInfo);
            string peerConnectionManager = Marshal.PtrToStringAnsi((IntPtr)aPeerConnectionManager);
            string direction = Marshal.PtrToStringAnsi((IntPtr)aDirection);
            int connectionID;
            int aVTransportID;
            int rcsID;
            self.PrepareForConnection(aVersion, remoteProtocolInfo, peerConnectionManager, aPeerConnectionID, direction, out connectionID, out aVTransportID, out rcsID);
            *aConnectionID = connectionID;
            *aAVTransportID = aVTransportID;
            *aRcsID = rcsID;
            return 0;
        }

        private static unsafe int DoConnectionComplete(IntPtr aPtr, uint aVersion, int aConnectionID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgConnectionManager1 self = (DvServiceUpnpOrgConnectionManager1)gch.Target;
            self.ConnectionComplete(aVersion, aConnectionID);
            return 0;
        }

        private static unsafe int DoGetCurrentConnectionIDs(IntPtr aPtr, uint aVersion, char** aConnectionIDs)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgConnectionManager1 self = (DvServiceUpnpOrgConnectionManager1)gch.Target;
            string connectionIDs;
            self.GetCurrentConnectionIDs(aVersion, out connectionIDs);
            *aConnectionIDs = (char*)Marshal.StringToHGlobalAnsi(connectionIDs).ToPointer();
            return 0;
        }

        private static unsafe int DoGetCurrentConnectionInfo(IntPtr aPtr, uint aVersion, int aConnectionID, int* aRcsID, int* aAVTransportID, char** aProtocolInfo, char** aPeerConnectionManager, int* aPeerConnectionID, char** aDirection, char** aStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgConnectionManager1 self = (DvServiceUpnpOrgConnectionManager1)gch.Target;
            int rcsID;
            int aVTransportID;
            string protocolInfo;
            string peerConnectionManager;
            int peerConnectionID;
            string direction;
            string status;
            self.GetCurrentConnectionInfo(aVersion, aConnectionID, out rcsID, out aVTransportID, out protocolInfo, out peerConnectionManager, out peerConnectionID, out direction, out status);
            *aRcsID = rcsID;
            *aAVTransportID = aVTransportID;
            *aProtocolInfo = (char*)Marshal.StringToHGlobalAnsi(protocolInfo).ToPointer();
            *aPeerConnectionManager = (char*)Marshal.StringToHGlobalAnsi(peerConnectionManager).ToPointer();
            *aPeerConnectionID = peerConnectionID;
            *aDirection = (char*)Marshal.StringToHGlobalAnsi(direction).ToPointer();
            *aStatus = (char*)Marshal.StringToHGlobalAnsi(status).ToPointer();
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceUpnpOrgConnectionManager1()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            uint handle;
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                handle = iHandle;
                iHandle = 0;
            }
            DvServiceUpnpOrgConnectionManager1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

