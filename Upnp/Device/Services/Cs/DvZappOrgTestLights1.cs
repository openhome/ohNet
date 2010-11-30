using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderZappOrgTestLights1 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the zapp.org:TestLights:1 UPnP service
    /// </summary>
    public class DvProviderZappOrgTestLights1 : DvProvider, IDisposable, IDvProviderZappOrgTestLights1
    {
        [DllImport("DvZappOrgTestLights1")]
        static extern uint DvProviderZappOrgTestLights1Create(uint aDeviceHandle);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvProviderZappOrgTestLights1Destroy(uint aHandle);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvProviderZappOrgTestLights1EnableActionGetCount(uint aHandle, CallbackGetCount aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvProviderZappOrgTestLights1EnableActionGetRoom(uint aHandle, CallbackGetRoom aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvProviderZappOrgTestLights1EnableActionGetName(uint aHandle, CallbackGetName aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvProviderZappOrgTestLights1EnableActionGetPosition(uint aHandle, CallbackGetPosition aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvProviderZappOrgTestLights1EnableActionSetColor(uint aHandle, CallbackSetColor aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvProviderZappOrgTestLights1EnableActionGetColor(uint aHandle, CallbackGetColor aCallback, IntPtr aPtr);
        [DllImport("DvZappOrgTestLights1")]
        static extern void DvProviderZappOrgTestLights1EnableActionGetColorComponents(uint aHandle, CallbackGetColorComponents aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackGetCount(IntPtr aPtr, uint aVersion, uint* aCount);
        private unsafe delegate int CallbackGetRoom(IntPtr aPtr, uint aVersion, uint aIndex, char** aRoomName);
        private unsafe delegate int CallbackGetName(IntPtr aPtr, uint aVersion, uint aIndex, char** aFriendlyName);
        private unsafe delegate int CallbackGetPosition(IntPtr aPtr, uint aVersion, uint aIndex, uint* aX, uint* aY, uint* aZ);
        private unsafe delegate int CallbackSetColor(IntPtr aPtr, uint aVersion, uint aIndex, uint aColor);
        private unsafe delegate int CallbackGetColor(IntPtr aPtr, uint aVersion, uint aIndex, uint* aColor);
        private unsafe delegate int CallbackGetColorComponents(IntPtr aPtr, uint aVersion, uint aColor, uint* aBrightness, uint* aRed, uint* aGreen, uint* aBlue);

        private GCHandle iGch;
        private CallbackGetCount iCallbackGetCount;
        private CallbackGetRoom iCallbackGetRoom;
        private CallbackGetName iCallbackGetName;
        private CallbackGetPosition iCallbackGetPosition;
        private CallbackSetColor iCallbackSetColor;
        private CallbackGetColor iCallbackGetColor;
        private CallbackGetColorComponents iCallbackGetColorComponents;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderZappOrgTestLights1(DvDevice aDevice)
        {
            iHandle = DvProviderZappOrgTestLights1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action GetCount is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetCount must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetCount()
        {
            iCallbackGetCount = new CallbackGetCount(DoGetCount);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestLights1EnableActionGetCount(iHandle, iCallbackGetCount, ptr);
        }

        /// <summary>
        /// Signal that the action GetRoom is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetRoom must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetRoom()
        {
            iCallbackGetRoom = new CallbackGetRoom(DoGetRoom);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestLights1EnableActionGetRoom(iHandle, iCallbackGetRoom, ptr);
        }

        /// <summary>
        /// Signal that the action GetName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetName()
        {
            iCallbackGetName = new CallbackGetName(DoGetName);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestLights1EnableActionGetName(iHandle, iCallbackGetName, ptr);
        }

        /// <summary>
        /// Signal that the action GetPosition is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetPosition must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetPosition()
        {
            iCallbackGetPosition = new CallbackGetPosition(DoGetPosition);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestLights1EnableActionGetPosition(iHandle, iCallbackGetPosition, ptr);
        }

        /// <summary>
        /// Signal that the action SetColor is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetColor must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetColor()
        {
            iCallbackSetColor = new CallbackSetColor(DoSetColor);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestLights1EnableActionSetColor(iHandle, iCallbackSetColor, ptr);
        }

        /// <summary>
        /// Signal that the action GetColor is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetColor must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetColor()
        {
            iCallbackGetColor = new CallbackGetColor(DoGetColor);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestLights1EnableActionGetColor(iHandle, iCallbackGetColor, ptr);
        }

        /// <summary>
        /// Signal that the action GetColorComponents is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoGetColorComponents must be overridden if this is called.</remarks>
        protected unsafe void EnableActionGetColorComponents()
        {
            iCallbackGetColorComponents = new CallbackGetColorComponents(DoGetColorComponents);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderZappOrgTestLights1EnableActionGetColorComponents(iHandle, iCallbackGetColorComponents, ptr);
        }

        /// <summary>
        /// GetCount action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetCount action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetCount was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aCount"></param>
        protected virtual void GetCount(uint aVersion, out uint aCount)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetRoom action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetRoom action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetRoom was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aIndex"></param>
        /// <param name="aRoomName"></param>
        protected virtual void GetRoom(uint aVersion, uint aIndex, out string aRoomName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetName action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aIndex"></param>
        /// <param name="aFriendlyName"></param>
        protected virtual void GetName(uint aVersion, uint aIndex, out string aFriendlyName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetPosition action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetPosition action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetPosition was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aIndex"></param>
        /// <param name="aX"></param>
        /// <param name="aY"></param>
        /// <param name="aZ"></param>
        protected virtual void GetPosition(uint aVersion, uint aIndex, out uint aX, out uint aY, out uint aZ)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetColor action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetColor action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetColor was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aIndex"></param>
        /// <param name="aColor"></param>
        protected virtual void SetColor(uint aVersion, uint aIndex, uint aColor)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetColor action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetColor action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetColor was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aIndex"></param>
        /// <param name="aColor"></param>
        protected virtual void GetColor(uint aVersion, uint aIndex, out uint aColor)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetColorComponents action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetColorComponents action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetColorComponents was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aColor"></param>
        /// <param name="aBrightness"></param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        protected virtual void GetColorComponents(uint aVersion, uint aColor, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoGetCount(IntPtr aPtr, uint aVersion, uint* aCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            uint count;
            self.GetCount(aVersion, out count);
            *aCount = count;
            return 0;
        }

        private static unsafe int DoGetRoom(IntPtr aPtr, uint aVersion, uint aIndex, char** aRoomName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            string roomName;
            self.GetRoom(aVersion, aIndex, out roomName);
            *aRoomName = (char*)Marshal.StringToHGlobalAnsi(roomName).ToPointer();
            return 0;
        }

        private static unsafe int DoGetName(IntPtr aPtr, uint aVersion, uint aIndex, char** aFriendlyName)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            string friendlyName;
            self.GetName(aVersion, aIndex, out friendlyName);
            *aFriendlyName = (char*)Marshal.StringToHGlobalAnsi(friendlyName).ToPointer();
            return 0;
        }

        private static unsafe int DoGetPosition(IntPtr aPtr, uint aVersion, uint aIndex, uint* aX, uint* aY, uint* aZ)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
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
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            self.SetColor(aVersion, aIndex, aColor);
            return 0;
        }

        private static unsafe int DoGetColor(IntPtr aPtr, uint aVersion, uint aIndex, uint* aColor)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            uint color;
            self.GetColor(aVersion, aIndex, out color);
            *aColor = color;
            return 0;
        }

        private static unsafe int DoGetColorComponents(IntPtr aPtr, uint aVersion, uint aColor, uint* aBrightness, uint* aRed, uint* aGreen, uint* aBlue)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
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

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderZappOrgTestLights1()
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
            DvProviderZappOrgTestLights1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

