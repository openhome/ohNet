using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

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
        private GCHandle iGch;
        private ActionDelegate iDelegateGetCount;
        private ActionDelegate iDelegateGetRoom;
        private ActionDelegate iDelegateGetName;
        private ActionDelegate iDelegateGetPosition;
        private ActionDelegate iDelegateSetColor;
        private ActionDelegate iDelegateGetColor;
        private ActionDelegate iDelegateGetColorComponents;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderZappOrgTestLights1(DvDevice aDevice)
            : base(aDevice, "zapp.org", "TestLights", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action GetCount is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetCount must be overridden if this is called.</remarks>
        protected void EnableActionGetCount()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetCount");
            action.AddOutputParameter(new ParameterUint("Count"));
            iDelegateGetCount = new ActionDelegate(DoGetCount);
            EnableAction(action, iDelegateGetCount, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetRoom is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetRoom must be overridden if this is called.</remarks>
        protected void EnableActionGetRoom()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetRoom");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("Index"));
            action.AddOutputParameter(new ParameterString("RoomName", allowedValues));
            iDelegateGetRoom = new ActionDelegate(DoGetRoom);
            EnableAction(action, iDelegateGetRoom, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetName must be overridden if this is called.</remarks>
        protected void EnableActionGetName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterUint("Index"));
            action.AddOutputParameter(new ParameterString("FriendlyName", allowedValues));
            iDelegateGetName = new ActionDelegate(DoGetName);
            EnableAction(action, iDelegateGetName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetPosition is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetPosition must be overridden if this is called.</remarks>
        protected void EnableActionGetPosition()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetPosition");
            action.AddInputParameter(new ParameterUint("Index"));
            action.AddOutputParameter(new ParameterUint("X"));
            action.AddOutputParameter(new ParameterUint("Y"));
            action.AddOutputParameter(new ParameterUint("Z"));
            iDelegateGetPosition = new ActionDelegate(DoGetPosition);
            EnableAction(action, iDelegateGetPosition, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetColor is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetColor must be overridden if this is called.</remarks>
        protected void EnableActionSetColor()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetColor");
            action.AddInputParameter(new ParameterUint("Index"));
            action.AddInputParameter(new ParameterUint("Color"));
            iDelegateSetColor = new ActionDelegate(DoSetColor);
            EnableAction(action, iDelegateSetColor, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetColor is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetColor must be overridden if this is called.</remarks>
        protected void EnableActionGetColor()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetColor");
            action.AddInputParameter(new ParameterUint("Index"));
            action.AddOutputParameter(new ParameterUint("Color"));
            iDelegateGetColor = new ActionDelegate(DoGetColor);
            EnableAction(action, iDelegateGetColor, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetColorComponents is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetColorComponents must be overridden if this is called.</remarks>
        protected void EnableActionGetColorComponents()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetColorComponents");
            action.AddInputParameter(new ParameterUint("Color"));
            action.AddOutputParameter(new ParameterUint("Brightness"));
            action.AddOutputParameter(new ParameterUint("Red"));
            action.AddOutputParameter(new ParameterUint("Green"));
            action.AddOutputParameter(new ParameterUint("Blue"));
            iDelegateGetColorComponents = new ActionDelegate(DoGetColorComponents);
            EnableAction(action, iDelegateGetColorComponents, GCHandle.ToIntPtr(iGch));
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

        private static int DoGetCount(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint count;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetCount(aVersion, out count);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Count", count);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetRoom(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint index;
            string roomName;
            try
            {
                invocation.ReadStart();
                index = invocation.ReadUint("Index");
                invocation.ReadEnd();
                self.GetRoom(aVersion, index, out roomName);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("RoomName", roomName);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint index;
            string friendlyName;
            try
            {
                invocation.ReadStart();
                index = invocation.ReadUint("Index");
                invocation.ReadEnd();
                self.GetName(aVersion, index, out friendlyName);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("FriendlyName", friendlyName);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetPosition(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint index;
            uint x;
            uint y;
            uint z;
            try
            {
                invocation.ReadStart();
                index = invocation.ReadUint("Index");
                invocation.ReadEnd();
                self.GetPosition(aVersion, index, out x, out y, out z);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("X", x);
                invocation.WriteUint("Y", y);
                invocation.WriteUint("Z", z);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetColor(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint index;
            uint color;
            try
            {
                invocation.ReadStart();
                index = invocation.ReadUint("Index");
                color = invocation.ReadUint("Color");
                invocation.ReadEnd();
                self.SetColor(aVersion, index, color);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetColor(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint index;
            uint color;
            try
            {
                invocation.ReadStart();
                index = invocation.ReadUint("Index");
                invocation.ReadEnd();
                self.GetColor(aVersion, index, out color);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Color", color);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoGetColorComponents(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestLights1 self = (DvProviderZappOrgTestLights1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint color;
            uint brightness;
            uint red;
            uint green;
            uint blue;
            try
            {
                invocation.ReadStart();
                color = invocation.ReadUint("Color");
                invocation.ReadEnd();
                self.GetColorComponents(aVersion, color, out brightness, out red, out green, out blue);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Brightness", brightness);
                invocation.WriteUint("Red", red);
                invocation.WriteUint("Green", green);
                invocation.WriteUint("Blue", blue);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
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
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProvider();
                iHandle = IntPtr.Zero;
            }
            iGch.Free();
        }
    }
}

