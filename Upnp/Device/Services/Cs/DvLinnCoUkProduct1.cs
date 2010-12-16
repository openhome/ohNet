using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkProduct1 : IDisposable
    {

        /// <summary>
        /// Set the value of the Room property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyRoom(string aValue);

        /// <summary>
        /// Get a copy of the value of the Room property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyRoom();

        /// <summary>
        /// Set the value of the Standby property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStandby(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Standby property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyStandby();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Product:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkProduct1 : DvProvider, IDisposable, IDvProviderLinnCoUkProduct1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateRoom;
        private ActionDelegate iDelegateSetRoom;
        private ActionDelegate iDelegateStandby;
        private ActionDelegate iDelegateSetStandby;
        private PropertyString iPropertyRoom;
        private PropertyBool iPropertyStandby;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkProduct1(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Product", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyRoom = new PropertyString(new ParameterString("Room", allowedValues));
            AddProperty(iPropertyRoom);
            iPropertyStandby = new PropertyBool(new ParameterBool("Standby"));
            AddProperty(iPropertyStandby);
        }

        /// <summary>
        /// Set the value of the Room property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyRoom(string aValue)
        {
            return SetPropertyString(iPropertyRoom, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Room property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyRoom()
        {
            return iPropertyRoom.Value();
        }

        /// <summary>
        /// Set the value of the Standby property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStandby(bool aValue)
        {
            return SetPropertyBool(iPropertyStandby, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Standby property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyStandby()
        {
            return iPropertyStandby.Value();
        }

        /// <summary>
        /// Signal that the action Room is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRoom must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRoom()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Room");
            action.AddOutputParameter(new ParameterRelated("aRoom", iPropertyRoom));
            iDelegateRoom = new ActionDelegate(DoRoom);
            EnableAction(action, iDelegateRoom, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetRoom is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetRoom must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetRoom()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetRoom");
            action.AddInputParameter(new ParameterRelated("aRoom", iPropertyRoom));
            iDelegateSetRoom = new ActionDelegate(DoSetRoom);
            EnableAction(action, iDelegateSetRoom, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Standby is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStandby must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStandby()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Standby");
            action.AddOutputParameter(new ParameterRelated("aStandby", iPropertyStandby));
            iDelegateStandby = new ActionDelegate(DoStandby);
            EnableAction(action, iDelegateStandby, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStandby is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStandby must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStandby()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStandby");
            action.AddInputParameter(new ParameterRelated("aStandby", iPropertyStandby));
            iDelegateSetStandby = new ActionDelegate(DoSetStandby);
            EnableAction(action, iDelegateSetStandby, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Room action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Room action for the owning device.
        ///
        /// Must be implemented iff EnableActionRoom was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRoom"></param>
        protected virtual void Room(uint aVersion, out string aaRoom)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetRoom action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetRoom action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetRoom was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaRoom"></param>
        protected virtual void SetRoom(uint aVersion, string aaRoom)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Standby action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Standby action for the owning device.
        ///
        /// Must be implemented iff EnableActionStandby was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStandby"></param>
        protected virtual void Standby(uint aVersion, out bool aaStandby)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStandby action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStandby action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStandby was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStandby"></param>
        protected virtual void SetStandby(uint aVersion, bool aaStandby)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoRoom(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct1 self = (DvProviderLinnCoUkProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            string aRoom;
            self.Room(aVersion, out aRoom);
            invocation.WriteStart();
            invocation.WriteString("aRoom", aRoom);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetRoom(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct1 self = (DvProviderLinnCoUkProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            string aRoom = invocation.ReadString("aRoom");
            invocation.ReadEnd();
            self.SetRoom(aVersion, aRoom);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoStandby(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct1 self = (DvProviderLinnCoUkProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            invocation.ReadEnd();
            bool aStandby;
            self.Standby(aVersion, out aStandby);
            invocation.WriteStart();
            invocation.WriteBool("aStandby", aStandby);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoSetStandby(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct1 self = (DvProviderLinnCoUkProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            invocation.ReadStart();
            bool aStandby = invocation.ReadBool("aStandby");
            invocation.ReadEnd();
            self.SetStandby(aVersion, aStandby);
            invocation.WriteStart();
            invocation.WriteEnd();
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

        ~DvProviderLinnCoUkProduct1()
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

