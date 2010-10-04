using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceZappOrgTestLights1 : IDisposable
    {
        [DllImport("DvZappOrgTestLights1")]
        static extern uint DvServiceZappOrgTestLights1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvServiceZappOrgTestLights1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvServiceZappOrgTestLights1EnableActionGetCount(uint aHandle, CallbackGetCount aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvServiceZappOrgTestLights1EnableActionGetRoom(uint aHandle, CallbackGetRoom aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvServiceZappOrgTestLights1EnableActionGetName(uint aHandle, CallbackGetName aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvServiceZappOrgTestLights1EnableActionGetPosition(uint aHandle, CallbackGetPosition aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvServiceZappOrgTestLights1EnableActionSetColor(uint aHandle, CallbackSetColor aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvServiceZappOrgTestLights1EnableActionGetColor(uint aHandle, CallbackGetColor aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvServiceZappOrgTestLights1EnableActionGetColorComponents(uint aHandle, CallbackGetColorComponents aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetCount(IntPtr aPtr, uint aVersion, uint* aCount);
        private unsafe delegate int CallbackGetRoom(IntPtr aPtr, uint aVersion, uint aIndex, char** aRoomName);
        private unsafe delegate int CallbackGetName(IntPtr aPtr, uint aVersion, uint aIndex, char** aFriendlyName);
        private unsafe delegate int CallbackGetPosition(IntPtr aPtr, uint aVersion, uint aIndex, uint* aX, uint* aY, uint* aZ);
        private unsafe delegate int CallbackSetColor(IntPtr aPtr, uint aVersion, uint aIndex, uint aColor);
        private unsafe delegate int CallbackGetColor(IntPtr aPtr, uint aVersion, uint aIndex, uint* aColor);
        private unsafe delegate int CallbackGetColorComponents(IntPtr aPtr, uint aVersion, uint aColor, uint* aBrightness, uint* aRed, uint* aGreen, uint* aBlue);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackGetCount iCallbackGetCount;
        private CallbackGetRoom iCallbackGetRoom;
        private CallbackGetName iCallbackGetName;
        private CallbackGetPosition iCallbackGetPosition;
        private CallbackSetColor iCallbackSetColor;
        private CallbackGetColor iCallbackGetColor;
        private CallbackGetColorComponents iCallbackGetColorComponents;

        public DvServiceZappOrgTestLights1(DvDevice aDevice)
        {
            iHandle = DvServiceZappOrgTestLights1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        protected unsafe void EnableActionGetCount()
        {
            iCallbackGetCount = new CallbackGetCount(DoGetCount);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestLights1EnableActionGetCount(iHandle, iCallbackGetCount, ptr);
        }

        protected unsafe void EnableActionGetRoom()
        {
            iCallbackGetRoom = new CallbackGetRoom(DoGetRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestLights1EnableActionGetRoom(iHandle, iCallbackGetRoom, ptr);
        }

        protected unsafe void EnableActionGetName()
        {
            iCallbackGetName = new CallbackGetName(DoGetName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestLights1EnableActionGetName(iHandle, iCallbackGetName, ptr);
        }

        protected unsafe void EnableActionGetPosition()
        {
            iCallbackGetPosition = new CallbackGetPosition(DoGetPosition);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestLights1EnableActionGetPosition(iHandle, iCallbackGetPosition, ptr);
        }

        protected unsafe void EnableActionSetColor()
        {
            iCallbackSetColor = new CallbackSetColor(DoSetColor);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestLights1EnableActionSetColor(iHandle, iCallbackSetColor, ptr);
        }

        protected unsafe void EnableActionGetColor()
        {
            iCallbackGetColor = new CallbackGetColor(DoGetColor);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestLights1EnableActionGetColor(iHandle, iCallbackGetColor, ptr);
        }

        protected unsafe void EnableActionGetColorComponents()
        {
            iCallbackGetColorComponents = new CallbackGetColorComponents(DoGetColorComponents);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceZappOrgTestLights1EnableActionGetColorComponents(iHandle, iCallbackGetColorComponents, ptr);
        }

        protected virtual void GetCount(uint aVersion, out uint aCount)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetRoom(uint aVersion, uint aIndex, out string aRoomName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetName(uint aVersion, uint aIndex, out string aFriendlyName)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetPosition(uint aVersion, uint aIndex, out uint aX, out uint aY, out uint aZ)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetColor(uint aVersion, uint aIndex, uint aColor)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetColor(uint aVersion, uint aIndex, out uint aColor)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetColorComponents(uint aVersion, uint aColor, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoGetCount(IntPtr aPtr, uint aVersion, uint* aCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestLights1 self = (DvServiceZappOrgTestLights1)gch.Target;
            uint count;
            self.GetCount(aVersion, out count);
            *aCount = count;
            return 0;
        }

        private static unsafe int DoGetRoom(IntPtr aPtr, uint aVersion, uint aIndex, char** aRoomName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestLights1 self = (DvServiceZappOrgTestLights1)gch.Target;
            string roomName;
            self.GetRoom(aVersion, aIndex, out roomName);
            *aRoomName = (char*)Marshal.StringToHGlobalAnsi(roomName).ToPointer();
            return 0;
        }

        private static unsafe int DoGetName(IntPtr aPtr, uint aVersion, uint aIndex, char** aFriendlyName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestLights1 self = (DvServiceZappOrgTestLights1)gch.Target;
            string friendlyName;
            self.GetName(aVersion, aIndex, out friendlyName);
            *aFriendlyName = (char*)Marshal.StringToHGlobalAnsi(friendlyName).ToPointer();
            return 0;
        }

        private static unsafe int DoGetPosition(IntPtr aPtr, uint aVersion, uint aIndex, uint* aX, uint* aY, uint* aZ)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestLights1 self = (DvServiceZappOrgTestLights1)gch.Target;
            uint x;
            uint y;
            uint z;
            self.GetPosition(aVersion, aIndex, out x, out y, out z);
            *aX = x;
            *aY = y;
            *aZ = z;
            return 0;
        }

        private static unsafe int DoSetColor(IntPtr aPtr, uint aVersion, uint aIndex, uint aColor)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestLights1 self = (DvServiceZappOrgTestLights1)gch.Target;
            self.SetColor(aVersion, aIndex, aColor);
            return 0;
        }

        private static unsafe int DoGetColor(IntPtr aPtr, uint aVersion, uint aIndex, uint* aColor)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestLights1 self = (DvServiceZappOrgTestLights1)gch.Target;
            uint color;
            self.GetColor(aVersion, aIndex, out color);
            *aColor = color;
            return 0;
        }

        private static unsafe int DoGetColorComponents(IntPtr aPtr, uint aVersion, uint aColor, uint* aBrightness, uint* aRed, uint* aGreen, uint* aBlue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceZappOrgTestLights1 self = (DvServiceZappOrgTestLights1)gch.Target;
            uint brightness;
            uint red;
            uint green;
            uint blue;
            self.GetColorComponents(aVersion, aColor, out brightness, out red, out green, out blue);
            *aBrightness = brightness;
            *aRed = red;
            *aGreen = green;
            *aBlue = blue;
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceZappOrgTestLights1()
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
            DvServiceZappOrgTestLights1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

