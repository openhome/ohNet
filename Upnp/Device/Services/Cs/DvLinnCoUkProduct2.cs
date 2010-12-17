using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkProduct2 : IDisposable
    {

        /// <summary>
        /// Set the value of the ProductName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductName(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyProductName();

        /// <summary>
        /// Set the value of the ProductRoom property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductRoom(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductRoom property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyProductRoom();

        /// <summary>
        /// Set the value of the ProductStandby property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductStandby(bool aValue);

        /// <summary>
        /// Get a copy of the value of the ProductStandby property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyProductStandby();

        /// <summary>
        /// Set the value of the ProductSourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductSourceIndex(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductSourceIndex property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyProductSourceIndex();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Product:2 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkProduct2 : DvProvider, IDisposable, IDvProviderLinnCoUkProduct2
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateType;
        private ActionDelegate iDelegateModel;
        private ActionDelegate iDelegateName;
        private ActionDelegate iDelegateSetName;
        private ActionDelegate iDelegateRoom;
        private ActionDelegate iDelegateSetRoom;
        private ActionDelegate iDelegateStandby;
        private ActionDelegate iDelegateSetStandby;
        private ActionDelegate iDelegateSourceCount;
        private ActionDelegate iDelegateSourceIndex;
        private ActionDelegate iDelegateSetSourceIndex;
        private ActionDelegate iDelegateSourceType;
        private PropertyString iPropertyProductName;
        private PropertyString iPropertyProductRoom;
        private PropertyBool iPropertyProductStandby;
        private PropertyUint iPropertyProductSourceIndex;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkProduct2(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Product", 2)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyProductName = new PropertyString(new ParameterString("ProductName", allowedValues));
            AddProperty(iPropertyProductName);
            iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom", allowedValues));
            AddProperty(iPropertyProductRoom);
            iPropertyProductStandby = new PropertyBool(new ParameterBool("ProductStandby"));
            AddProperty(iPropertyProductStandby);
            iPropertyProductSourceIndex = new PropertyUint(new ParameterUint("ProductSourceIndex"));
            AddProperty(iPropertyProductSourceIndex);
        }

        /// <summary>
        /// Set the value of the ProductName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductName(string aValue)
        {
            return SetPropertyString(iPropertyProductName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductName property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyProductName()
        {
            return iPropertyProductName.Value();
        }

        /// <summary>
        /// Set the value of the ProductRoom property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductRoom(string aValue)
        {
            return SetPropertyString(iPropertyProductRoom, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductRoom property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyProductRoom()
        {
            return iPropertyProductRoom.Value();
        }

        /// <summary>
        /// Set the value of the ProductStandby property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductStandby(bool aValue)
        {
            return SetPropertyBool(iPropertyProductStandby, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductStandby property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyProductStandby()
        {
            return iPropertyProductStandby.Value();
        }

        /// <summary>
        /// Set the value of the ProductSourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductSourceIndex(uint aValue)
        {
            return SetPropertyUint(iPropertyProductSourceIndex, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductSourceIndex property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyProductSourceIndex()
        {
            return iPropertyProductSourceIndex.Value();
        }

        /// <summary>
        /// Signal that the action Type is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoType must be overridden if this is called.</remarks>
        protected unsafe void EnableActionType()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Type");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aType", allowedValues));
            iDelegateType = new ActionDelegate(DoType);
            EnableAction(action, iDelegateType, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Model is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoModel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionModel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Model");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("aModel", allowedValues));
            iDelegateModel = new ActionDelegate(DoModel);
            EnableAction(action, iDelegateModel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Name is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Name");
            action.AddOutputParameter(new ParameterRelated("aName", iPropertyProductName));
            iDelegateName = new ActionDelegate(DoName);
            EnableAction(action, iDelegateName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetName");
            action.AddInputParameter(new ParameterRelated("aName", iPropertyProductName));
            iDelegateSetName = new ActionDelegate(DoSetName);
            EnableAction(action, iDelegateSetName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Room is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRoom must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRoom()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Room");
            action.AddOutputParameter(new ParameterRelated("aRoom", iPropertyProductRoom));
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
            action.AddInputParameter(new ParameterRelated("aRoom", iPropertyProductRoom));
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
            action.AddOutputParameter(new ParameterRelated("aStandby", iPropertyProductStandby));
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
            action.AddInputParameter(new ParameterRelated("aStandby", iPropertyProductStandby));
            iDelegateSetStandby = new ActionDelegate(DoSetStandby);
            EnableAction(action, iDelegateSetStandby, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceCount is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceCount must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceCount()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SourceCount");
            action.AddOutputParameter(new ParameterRelated("aSourceCount", iPropertyProductSourceIndex));
            iDelegateSourceCount = new ActionDelegate(DoSourceCount);
            EnableAction(action, iDelegateSourceCount, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceIndex()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SourceIndex");
            action.AddOutputParameter(new ParameterRelated("aSourceIndex", iPropertyProductSourceIndex));
            iDelegateSourceIndex = new ActionDelegate(DoSourceIndex);
            EnableAction(action, iDelegateSourceIndex, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetSourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSourceIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSourceIndex()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetSourceIndex");
            action.AddInputParameter(new ParameterRelated("aSourceIndex", iPropertyProductSourceIndex));
            iDelegateSetSourceIndex = new ActionDelegate(DoSetSourceIndex);
            EnableAction(action, iDelegateSetSourceIndex, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceType is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceType must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceType()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SourceType");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aSourceIndex", iPropertyProductSourceIndex));
            action.AddOutputParameter(new ParameterString("aSourceType", allowedValues));
            iDelegateSourceType = new ActionDelegate(DoSourceType);
            EnableAction(action, iDelegateSourceType, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Type action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Type action for the owning device.
        ///
        /// Must be implemented iff EnableActionType was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaType"></param>
        protected virtual void Type(uint aVersion, out string aaType)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Model action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Model action for the owning device.
        ///
        /// Must be implemented iff EnableActionModel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaModel"></param>
        protected virtual void Model(uint aVersion, out string aaModel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Name action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Name action for the owning device.
        ///
        /// Must be implemented iff EnableActionName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaName"></param>
        protected virtual void Name(uint aVersion, out string aaName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaName"></param>
        protected virtual void SetName(uint aVersion, string aaName)
        {
            throw (new ActionDisabledError());
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

        /// <summary>
        /// SourceCount action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceCount action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceCount was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceCount"></param>
        protected virtual void SourceCount(uint aVersion, out uint aaSourceCount)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        protected virtual void SourceIndex(uint aVersion, out uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        protected virtual void SetSourceIndex(uint aVersion, uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceType action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceType action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceType was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceType"></param>
        protected virtual void SourceType(uint aVersion, uint aaSourceIndex, out string aaSourceType)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoType(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                string aType;
                self.Type(aVersion, out aType);
                invocation.WriteStart();
                invocation.WriteString("aType", aType);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoModel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                string aModel;
                self.Model(aVersion, out aModel);
                invocation.WriteStart();
                invocation.WriteString("aModel", aModel);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                string aName;
                self.Name(aVersion, out aName);
                invocation.WriteStart();
                invocation.WriteString("aName", aName);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string aName = invocation.ReadString("aName");
                invocation.ReadEnd();
                self.SetName(aVersion, aName);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoRoom(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                string aRoom;
                self.Room(aVersion, out aRoom);
                invocation.WriteStart();
                invocation.WriteString("aRoom", aRoom);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetRoom(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string aRoom = invocation.ReadString("aRoom");
                invocation.ReadEnd();
                self.SetRoom(aVersion, aRoom);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoStandby(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                bool aStandby;
                self.Standby(aVersion, out aStandby);
                invocation.WriteStart();
                invocation.WriteBool("aStandby", aStandby);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetStandby(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                bool aStandby = invocation.ReadBool("aStandby");
                invocation.ReadEnd();
                self.SetStandby(aVersion, aStandby);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSourceCount(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                uint aSourceCount;
                self.SourceCount(aVersion, out aSourceCount);
                invocation.WriteStart();
                invocation.WriteUint("aSourceCount", aSourceCount);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSourceIndex(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                uint aSourceIndex;
                self.SourceIndex(aVersion, out aSourceIndex);
                invocation.WriteStart();
                invocation.WriteUint("aSourceIndex", aSourceIndex);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSetSourceIndex(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint aSourceIndex = invocation.ReadUint("aSourceIndex");
                invocation.ReadEnd();
                self.SetSourceIndex(aVersion, aSourceIndex);
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
            {
                return -1;
            }
            return 0;
        }

        private static unsafe int DoSourceType(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct2 self = (DvProviderLinnCoUkProduct2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint aSourceIndex = invocation.ReadUint("aSourceIndex");
                invocation.ReadEnd();
                string aSourceType;
                self.SourceType(aVersion, aSourceIndex, out aSourceType);
                invocation.WriteStart();
                invocation.WriteString("aSourceType", aSourceType);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (PropertyUpdateError)
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

        ~DvProviderLinnCoUkProduct2()
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

