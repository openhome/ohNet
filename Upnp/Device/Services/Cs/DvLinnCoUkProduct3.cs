using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkProduct3 : IDisposable
    {

        /// <summary>
        /// Set the value of the ProductType property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductType(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductType property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyProductType();

        /// <summary>
        /// Set the value of the ProductModel property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductModel(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductModel property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyProductModel();

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

        /// <summary>
        /// Set the value of the ProductSourceCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductSourceCount(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductSourceCount property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyProductSourceCount();

        /// <summary>
        /// Set the value of the ProductSourceXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductSourceXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductSourceXml property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyProductSourceXml();

        /// <summary>
        /// Set the value of the StartupSourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStartupSourceIndex(uint aValue);

        /// <summary>
        /// Get a copy of the value of the StartupSourceIndex property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyStartupSourceIndex();

        /// <summary>
        /// Set the value of the StartupSourceEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStartupSourceEnabled(bool aValue);

        /// <summary>
        /// Get a copy of the value of the StartupSourceEnabled property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyStartupSourceEnabled();

        /// <summary>
        /// Set the value of the ProductAnySourceName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductAnySourceName(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceName property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyProductAnySourceName();

        /// <summary>
        /// Set the value of the ProductAnySourceVisible property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductAnySourceVisible(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceVisible property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyProductAnySourceVisible();

        /// <summary>
        /// Set the value of the ProductAnySourceType property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductAnySourceType(uint aValue);

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceType property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyProductAnySourceType();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Product:3 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkProduct3 : DvProvider, IDisposable, IDvProviderLinnCoUkProduct3
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
        private ActionDelegate iDelegateSourceXml;
        private ActionDelegate iDelegateSourceIndex;
        private ActionDelegate iDelegateSetSourceIndex;
        private ActionDelegate iDelegateSetSourceIndexByName;
        private ActionDelegate iDelegateSetStartupSourceIndexByName;
        private ActionDelegate iDelegateStartupSourceIndex;
        private ActionDelegate iDelegateSetStartupSourceIndex;
        private ActionDelegate iDelegateStartupSourceEnabled;
        private ActionDelegate iDelegateSetStartupSourceEnabled;
        private ActionDelegate iDelegateSourceSystemName;
        private ActionDelegate iDelegateSourceName;
        private ActionDelegate iDelegateSetSourceName;
        private ActionDelegate iDelegateSourceType;
        private ActionDelegate iDelegateSourceVisible;
        private ActionDelegate iDelegateSetSourceVisible;
        private PropertyString iPropertyProductType;
        private PropertyString iPropertyProductModel;
        private PropertyString iPropertyProductName;
        private PropertyString iPropertyProductRoom;
        private PropertyBool iPropertyProductStandby;
        private PropertyUint iPropertyProductSourceIndex;
        private PropertyUint iPropertyProductSourceCount;
        private PropertyString iPropertyProductSourceXml;
        private PropertyUint iPropertyStartupSourceIndex;
        private PropertyBool iPropertyStartupSourceEnabled;
        private PropertyUint iPropertyProductAnySourceName;
        private PropertyUint iPropertyProductAnySourceVisible;
        private PropertyUint iPropertyProductAnySourceType;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkProduct3(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Product", 3)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyProductType = new PropertyString(new ParameterString("ProductType", allowedValues));
            AddProperty(iPropertyProductType);
            iPropertyProductModel = new PropertyString(new ParameterString("ProductModel", allowedValues));
            AddProperty(iPropertyProductModel);
            iPropertyProductName = new PropertyString(new ParameterString("ProductName", allowedValues));
            AddProperty(iPropertyProductName);
            iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom", allowedValues));
            AddProperty(iPropertyProductRoom);
            iPropertyProductStandby = new PropertyBool(new ParameterBool("ProductStandby"));
            AddProperty(iPropertyProductStandby);
            iPropertyProductSourceIndex = new PropertyUint(new ParameterUint("ProductSourceIndex"));
            AddProperty(iPropertyProductSourceIndex);
            iPropertyProductSourceCount = new PropertyUint(new ParameterUint("ProductSourceCount"));
            AddProperty(iPropertyProductSourceCount);
            iPropertyProductSourceXml = new PropertyString(new ParameterString("ProductSourceXml", allowedValues));
            AddProperty(iPropertyProductSourceXml);
            iPropertyStartupSourceIndex = new PropertyUint(new ParameterUint("StartupSourceIndex"));
            AddProperty(iPropertyStartupSourceIndex);
            iPropertyStartupSourceEnabled = new PropertyBool(new ParameterBool("StartupSourceEnabled"));
            AddProperty(iPropertyStartupSourceEnabled);
            iPropertyProductAnySourceName = new PropertyUint(new ParameterUint("ProductAnySourceName"));
            AddProperty(iPropertyProductAnySourceName);
            iPropertyProductAnySourceVisible = new PropertyUint(new ParameterUint("ProductAnySourceVisible"));
            AddProperty(iPropertyProductAnySourceVisible);
            iPropertyProductAnySourceType = new PropertyUint(new ParameterUint("ProductAnySourceType"));
            AddProperty(iPropertyProductAnySourceType);
        }

        /// <summary>
        /// Set the value of the ProductType property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductType(string aValue)
        {
            return SetPropertyString(iPropertyProductType, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductType property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyProductType()
        {
            return iPropertyProductType.Value();
        }

        /// <summary>
        /// Set the value of the ProductModel property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductModel(string aValue)
        {
            return SetPropertyString(iPropertyProductModel, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductModel property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyProductModel()
        {
            return iPropertyProductModel.Value();
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
        /// Set the value of the ProductSourceCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductSourceCount(uint aValue)
        {
            return SetPropertyUint(iPropertyProductSourceCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductSourceCount property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyProductSourceCount()
        {
            return iPropertyProductSourceCount.Value();
        }

        /// <summary>
        /// Set the value of the ProductSourceXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductSourceXml(string aValue)
        {
            return SetPropertyString(iPropertyProductSourceXml, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductSourceXml property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyProductSourceXml()
        {
            return iPropertyProductSourceXml.Value();
        }

        /// <summary>
        /// Set the value of the StartupSourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStartupSourceIndex(uint aValue)
        {
            return SetPropertyUint(iPropertyStartupSourceIndex, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the StartupSourceIndex property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyStartupSourceIndex()
        {
            return iPropertyStartupSourceIndex.Value();
        }

        /// <summary>
        /// Set the value of the StartupSourceEnabled property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStartupSourceEnabled(bool aValue)
        {
            return SetPropertyBool(iPropertyStartupSourceEnabled, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the StartupSourceEnabled property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyStartupSourceEnabled()
        {
            return iPropertyStartupSourceEnabled.Value();
        }

        /// <summary>
        /// Set the value of the ProductAnySourceName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductAnySourceName(uint aValue)
        {
            return SetPropertyUint(iPropertyProductAnySourceName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceName property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyProductAnySourceName()
        {
            return iPropertyProductAnySourceName.Value();
        }

        /// <summary>
        /// Set the value of the ProductAnySourceVisible property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductAnySourceVisible(uint aValue)
        {
            return SetPropertyUint(iPropertyProductAnySourceVisible, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceVisible property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyProductAnySourceVisible()
        {
            return iPropertyProductAnySourceVisible.Value();
        }

        /// <summary>
        /// Set the value of the ProductAnySourceType property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductAnySourceType(uint aValue)
        {
            return SetPropertyUint(iPropertyProductAnySourceType, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductAnySourceType property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyProductAnySourceType()
        {
            return iPropertyProductAnySourceType.Value();
        }

        /// <summary>
        /// Signal that the action Type is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoType must be overridden if this is called.</remarks>
        protected unsafe void EnableActionType()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Type");
            action.AddOutputParameter(new ParameterRelated("aType", iPropertyProductType));
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
            action.AddOutputParameter(new ParameterRelated("aModel", iPropertyProductModel));
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
            action.AddOutputParameter(new ParameterRelated("aSourceCount", iPropertyProductSourceCount));
            iDelegateSourceCount = new ActionDelegate(DoSourceCount);
            EnableAction(action, iDelegateSourceCount, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceXml must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceXml()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SourceXml");
            action.AddOutputParameter(new ParameterRelated("aSourceXml", iPropertyProductSourceXml));
            iDelegateSourceXml = new ActionDelegate(DoSourceXml);
            EnableAction(action, iDelegateSourceXml, GCHandle.ToIntPtr(iGch));
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
        /// Signal that the action SetSourceIndexByName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSourceIndexByName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSourceIndexByName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetSourceIndexByName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("aSourceName", allowedValues));
            iDelegateSetSourceIndexByName = new ActionDelegate(DoSetSourceIndexByName);
            EnableAction(action, iDelegateSetSourceIndexByName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStartupSourceIndexByName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStartupSourceIndexByName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStartupSourceIndexByName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStartupSourceIndexByName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("aSourceName", allowedValues));
            iDelegateSetStartupSourceIndexByName = new ActionDelegate(DoSetStartupSourceIndexByName);
            EnableAction(action, iDelegateSetStartupSourceIndexByName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StartupSourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartupSourceIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartupSourceIndex()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("StartupSourceIndex");
            action.AddOutputParameter(new ParameterRelated("aSourceIndex", iPropertyStartupSourceIndex));
            iDelegateStartupSourceIndex = new ActionDelegate(DoStartupSourceIndex);
            EnableAction(action, iDelegateStartupSourceIndex, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStartupSourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStartupSourceIndex must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStartupSourceIndex()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStartupSourceIndex");
            action.AddInputParameter(new ParameterRelated("aSourceIndex", iPropertyStartupSourceIndex));
            iDelegateSetStartupSourceIndex = new ActionDelegate(DoSetStartupSourceIndex);
            EnableAction(action, iDelegateSetStartupSourceIndex, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action StartupSourceEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStartupSourceEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStartupSourceEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("StartupSourceEnabled");
            action.AddOutputParameter(new ParameterRelated("aStartupSourceEnabled", iPropertyStartupSourceEnabled));
            iDelegateStartupSourceEnabled = new ActionDelegate(DoStartupSourceEnabled);
            EnableAction(action, iDelegateStartupSourceEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStartupSourceEnabled is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetStartupSourceEnabled must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetStartupSourceEnabled()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetStartupSourceEnabled");
            action.AddInputParameter(new ParameterRelated("aStartupSourceEnabled", iPropertyStartupSourceEnabled));
            iDelegateSetStartupSourceEnabled = new ActionDelegate(DoSetStartupSourceEnabled);
            EnableAction(action, iDelegateSetStartupSourceEnabled, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceSystemName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceSystemName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceSystemName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SourceSystemName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aSourceIndex", iPropertyProductSourceIndex));
            action.AddOutputParameter(new ParameterString("aSourceName", allowedValues));
            iDelegateSourceSystemName = new ActionDelegate(DoSourceSystemName);
            EnableAction(action, iDelegateSourceSystemName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SourceName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aSourceIndex", iPropertyProductSourceIndex));
            action.AddOutputParameter(new ParameterString("aSourceName", allowedValues));
            iDelegateSourceName = new ActionDelegate(DoSourceName);
            EnableAction(action, iDelegateSourceName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetSourceName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSourceName must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSourceName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetSourceName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("aSourceIndex", iPropertyProductSourceIndex));
            action.AddInputParameter(new ParameterString("aSourceName", allowedValues));
            iDelegateSetSourceName = new ActionDelegate(DoSetSourceName);
            EnableAction(action, iDelegateSetSourceName, GCHandle.ToIntPtr(iGch));
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
        /// Signal that the action SourceVisible is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSourceVisible must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSourceVisible()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SourceVisible");
            action.AddInputParameter(new ParameterRelated("aSourceIndex", iPropertyProductSourceIndex));
            action.AddOutputParameter(new ParameterBool("aSourceVisible"));
            iDelegateSourceVisible = new ActionDelegate(DoSourceVisible);
            EnableAction(action, iDelegateSourceVisible, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetSourceVisible is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetSourceVisible must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetSourceVisible()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetSourceVisible");
            action.AddInputParameter(new ParameterRelated("aSourceIndex", iPropertyProductSourceIndex));
            action.AddInputParameter(new ParameterBool("aSourceVisible"));
            iDelegateSetSourceVisible = new ActionDelegate(DoSetSourceVisible);
            EnableAction(action, iDelegateSetSourceVisible, GCHandle.ToIntPtr(iGch));
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
        /// SourceXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceXml was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceXml"></param>
        protected virtual void SourceXml(uint aVersion, out string aaSourceXml)
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
        /// SetSourceIndexByName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceIndexByName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceIndexByName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceName"></param>
        protected virtual void SetSourceIndexByName(uint aVersion, string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupSourceIndexByName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupSourceIndexByName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupSourceIndexByName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceName"></param>
        protected virtual void SetStartupSourceIndexByName(uint aVersion, string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartupSourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartupSourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartupSourceIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        protected virtual void StartupSourceIndex(uint aVersion, out uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupSourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupSourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupSourceIndex was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        protected virtual void SetStartupSourceIndex(uint aVersion, uint aaSourceIndex)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// StartupSourceEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// StartupSourceEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionStartupSourceEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupSourceEnabled"></param>
        protected virtual void StartupSourceEnabled(uint aVersion, out bool aaStartupSourceEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStartupSourceEnabled action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStartupSourceEnabled action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStartupSourceEnabled was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaStartupSourceEnabled"></param>
        protected virtual void SetStartupSourceEnabled(uint aVersion, bool aaStartupSourceEnabled)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceSystemName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceSystemName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceSystemName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        protected virtual void SourceSystemName(uint aVersion, uint aaSourceIndex, out string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        protected virtual void SourceName(uint aVersion, uint aaSourceIndex, out string aaSourceName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        protected virtual void SetSourceName(uint aVersion, uint aaSourceIndex, string aaSourceName)
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

        /// <summary>
        /// SourceVisible action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceVisible action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceVisible was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        protected virtual void SourceVisible(uint aVersion, uint aaSourceIndex, out bool aaSourceVisible)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceVisible action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceVisible action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceVisible was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        protected virtual void SetSourceVisible(uint aVersion, uint aaSourceIndex, bool aaSourceVisible)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoType(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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

        private static unsafe int DoSourceXml(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                string aSourceXml;
                self.SourceXml(aVersion, out aSourceXml);
                invocation.WriteStart();
                invocation.WriteString("aSourceXml", aSourceXml);
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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

        private static unsafe int DoSetSourceIndexByName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string aSourceName = invocation.ReadString("aSourceName");
                invocation.ReadEnd();
                self.SetSourceIndexByName(aVersion, aSourceName);
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

        private static unsafe int DoSetStartupSourceIndexByName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                string aSourceName = invocation.ReadString("aSourceName");
                invocation.ReadEnd();
                self.SetStartupSourceIndexByName(aVersion, aSourceName);
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

        private static unsafe int DoStartupSourceIndex(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                uint aSourceIndex;
                self.StartupSourceIndex(aVersion, out aSourceIndex);
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

        private static unsafe int DoSetStartupSourceIndex(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint aSourceIndex = invocation.ReadUint("aSourceIndex");
                invocation.ReadEnd();
                self.SetStartupSourceIndex(aVersion, aSourceIndex);
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

        private static unsafe int DoStartupSourceEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                invocation.ReadEnd();
                bool aStartupSourceEnabled;
                self.StartupSourceEnabled(aVersion, out aStartupSourceEnabled);
                invocation.WriteStart();
                invocation.WriteBool("aStartupSourceEnabled", aStartupSourceEnabled);
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

        private static unsafe int DoSetStartupSourceEnabled(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                bool aStartupSourceEnabled = invocation.ReadBool("aStartupSourceEnabled");
                invocation.ReadEnd();
                self.SetStartupSourceEnabled(aVersion, aStartupSourceEnabled);
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

        private static unsafe int DoSourceSystemName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint aSourceIndex = invocation.ReadUint("aSourceIndex");
                invocation.ReadEnd();
                string aSourceName;
                self.SourceSystemName(aVersion, aSourceIndex, out aSourceName);
                invocation.WriteStart();
                invocation.WriteString("aSourceName", aSourceName);
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

        private static unsafe int DoSourceName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint aSourceIndex = invocation.ReadUint("aSourceIndex");
                invocation.ReadEnd();
                string aSourceName;
                self.SourceName(aVersion, aSourceIndex, out aSourceName);
                invocation.WriteStart();
                invocation.WriteString("aSourceName", aSourceName);
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

        private static unsafe int DoSetSourceName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint aSourceIndex = invocation.ReadUint("aSourceIndex");
                string aSourceName = invocation.ReadString("aSourceName");
                invocation.ReadEnd();
                self.SetSourceName(aVersion, aSourceIndex, aSourceName);
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
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
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

        private static unsafe int DoSourceVisible(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint aSourceIndex = invocation.ReadUint("aSourceIndex");
                invocation.ReadEnd();
                bool aSourceVisible;
                self.SourceVisible(aVersion, aSourceIndex, out aSourceVisible);
                invocation.WriteStart();
                invocation.WriteBool("aSourceVisible", aSourceVisible);
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

        private static unsafe int DoSetSourceVisible(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkProduct3 self = (DvProviderLinnCoUkProduct3)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try {
                invocation.ReadStart();
                uint aSourceIndex = invocation.ReadUint("aSourceIndex");
                bool aSourceVisible = invocation.ReadBool("aSourceVisible");
                invocation.ReadEnd();
                self.SetSourceVisible(aVersion, aSourceIndex, aSourceVisible);
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

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkProduct3()
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

