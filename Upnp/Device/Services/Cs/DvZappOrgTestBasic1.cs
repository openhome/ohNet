using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderZappOrgTestBasic1 : IDisposable
    {

        /// <summary>
        /// Set the value of the VarUint property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVarUint(uint aValue);

        /// <summary>
        /// Get a copy of the value of the VarUint property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyVarUint();

        /// <summary>
        /// Set the value of the VarInt property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVarInt(int aValue);

        /// <summary>
        /// Get a copy of the value of the VarInt property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        int PropertyVarInt();

        /// <summary>
        /// Set the value of the VarBool property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVarBool(bool aValue);

        /// <summary>
        /// Get a copy of the value of the VarBool property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        bool PropertyVarBool();

        /// <summary>
        /// Set the value of the VarStr property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVarStr(string aValue);

        /// <summary>
        /// Get a copy of the value of the VarStr property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        string PropertyVarStr();

        /// <summary>
        /// Set the value of the VarBin property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyVarBin(byte[] aValue);

        /// <summary>
        /// Get a copy of the value of the VarBin property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        byte[] PropertyVarBin();
        
    }
    /// <summary>
    /// Provider for the zapp.org:TestBasic:1 UPnP service
    /// </summary>
    public class DvProviderZappOrgTestBasic1 : DvProvider, IDisposable, IDvProviderZappOrgTestBasic1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateIncrement;
        private ActionDelegate iDelegateDecrement;
        private ActionDelegate iDelegateToggle;
        private ActionDelegate iDelegateEchoString;
        private ActionDelegate iDelegateEchoBinary;
        private ActionDelegate iDelegateSetUint;
        private ActionDelegate iDelegateGetUint;
        private ActionDelegate iDelegateSetInt;
        private ActionDelegate iDelegateGetInt;
        private ActionDelegate iDelegateSetBool;
        private ActionDelegate iDelegateGetBool;
        private ActionDelegate iDelegateSetMultiple;
        private ActionDelegate iDelegateSetString;
        private ActionDelegate iDelegateGetString;
        private ActionDelegate iDelegateSetBinary;
        private ActionDelegate iDelegateGetBinary;
        private ActionDelegate iDelegateToggleBool;
        private ActionDelegate iDelegateWriteFile;
        private ActionDelegate iDelegateShutdown;
        private PropertyUint iPropertyVarUint;
        private PropertyInt iPropertyVarInt;
        private PropertyBool iPropertyVarBool;
        private PropertyString iPropertyVarStr;
        private PropertyBinary iPropertyVarBin;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderZappOrgTestBasic1(DvDevice aDevice)
            : base(aDevice, "zapp-org", "TestBasic", 1)
        {
            iGch = GCHandle.Alloc(this);
            List<String> allowedValues = new List<String>();
            iPropertyVarUint = new PropertyUint(new ParameterUint("VarUint"));
            AddProperty(iPropertyVarUint);
            iPropertyVarInt = new PropertyInt(new ParameterInt("VarInt"));
            AddProperty(iPropertyVarInt);
            iPropertyVarBool = new PropertyBool(new ParameterBool("VarBool"));
            AddProperty(iPropertyVarBool);
            iPropertyVarStr = new PropertyString(new ParameterString("VarStr", allowedValues));
            AddProperty(iPropertyVarStr);
            iPropertyVarBin = new PropertyBinary(new ParameterBinary("VarBin"));
            AddProperty(iPropertyVarBin);
        }

        /// <summary>
        /// Set the value of the VarUint property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarUint(uint aValue)
        {
            return SetPropertyUint(iPropertyVarUint, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarUint property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyVarUint()
        {
            return iPropertyVarUint.Value();
        }

        /// <summary>
        /// Set the value of the VarInt property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarInt(int aValue)
        {
            return SetPropertyInt(iPropertyVarInt, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarInt property
        /// </summary>
        /// <returns>The value of the property</returns>
        public int PropertyVarInt()
        {
            return iPropertyVarInt.Value();
        }

        /// <summary>
        /// Set the value of the VarBool property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarBool(bool aValue)
        {
            return SetPropertyBool(iPropertyVarBool, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarBool property
        /// </summary>
        /// <returns>The value of the property</returns>
        public bool PropertyVarBool()
        {
            return iPropertyVarBool.Value();
        }

        /// <summary>
        /// Set the value of the VarStr property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarStr(string aValue)
        {
            return SetPropertyString(iPropertyVarStr, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarStr property
        /// </summary>
        /// <returns>The value of the property</returns>
        public string PropertyVarStr()
        {
            return iPropertyVarStr.Value();
        }

        /// <summary>
        /// Set the value of the VarBin property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarBin(byte[] aValue)
        {
            return SetPropertyBinary(iPropertyVarBin, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarBin property
        /// </summary>
        /// <returns>The value of the property</returns>
        public byte[] PropertyVarBin()
        {
            return iPropertyVarBin.Value();
        }

        /// <summary>
        /// Signal that the action Increment is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Increment must be overridden if this is called.</remarks>
        protected void EnableActionIncrement()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Increment");
            action.AddInputParameter(new ParameterUint("Value"));
            action.AddOutputParameter(new ParameterUint("Result"));
            iDelegateIncrement = new ActionDelegate(DoIncrement);
            EnableAction(action, iDelegateIncrement, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Decrement is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Decrement must be overridden if this is called.</remarks>
        protected void EnableActionDecrement()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Decrement");
            action.AddInputParameter(new ParameterInt("Value"));
            action.AddOutputParameter(new ParameterInt("Result"));
            iDelegateDecrement = new ActionDelegate(DoDecrement);
            EnableAction(action, iDelegateDecrement, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Toggle is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Toggle must be overridden if this is called.</remarks>
        protected void EnableActionToggle()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Toggle");
            action.AddInputParameter(new ParameterBool("Value"));
            action.AddOutputParameter(new ParameterBool("Result"));
            iDelegateToggle = new ActionDelegate(DoToggle);
            EnableAction(action, iDelegateToggle, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action EchoString is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// EchoString must be overridden if this is called.</remarks>
        protected void EnableActionEchoString()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("EchoString");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("Value", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            iDelegateEchoString = new ActionDelegate(DoEchoString);
            EnableAction(action, iDelegateEchoString, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action EchoBinary is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// EchoBinary must be overridden if this is called.</remarks>
        protected void EnableActionEchoBinary()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("EchoBinary");
            action.AddInputParameter(new ParameterBinary("Value"));
            action.AddOutputParameter(new ParameterBinary("Result"));
            iDelegateEchoBinary = new ActionDelegate(DoEchoBinary);
            EnableAction(action, iDelegateEchoBinary, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetUint is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetUint must be overridden if this is called.</remarks>
        protected void EnableActionSetUint()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetUint");
            action.AddInputParameter(new ParameterRelated("ValueUint", iPropertyVarUint));
            iDelegateSetUint = new ActionDelegate(DoSetUint);
            EnableAction(action, iDelegateSetUint, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetUint is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetUint must be overridden if this is called.</remarks>
        protected void EnableActionGetUint()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetUint");
            action.AddOutputParameter(new ParameterRelated("ValueUint", iPropertyVarUint));
            iDelegateGetUint = new ActionDelegate(DoGetUint);
            EnableAction(action, iDelegateGetUint, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetInt is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetInt must be overridden if this is called.</remarks>
        protected void EnableActionSetInt()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetInt");
            action.AddInputParameter(new ParameterRelated("ValueInt", iPropertyVarInt));
            iDelegateSetInt = new ActionDelegate(DoSetInt);
            EnableAction(action, iDelegateSetInt, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetInt is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetInt must be overridden if this is called.</remarks>
        protected void EnableActionGetInt()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetInt");
            action.AddOutputParameter(new ParameterRelated("ValueInt", iPropertyVarInt));
            iDelegateGetInt = new ActionDelegate(DoGetInt);
            EnableAction(action, iDelegateGetInt, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetBool is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetBool must be overridden if this is called.</remarks>
        protected void EnableActionSetBool()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetBool");
            action.AddInputParameter(new ParameterRelated("ValueBool", iPropertyVarBool));
            iDelegateSetBool = new ActionDelegate(DoSetBool);
            EnableAction(action, iDelegateSetBool, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetBool is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetBool must be overridden if this is called.</remarks>
        protected void EnableActionGetBool()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetBool");
            action.AddOutputParameter(new ParameterRelated("ValueBool", iPropertyVarBool));
            iDelegateGetBool = new ActionDelegate(DoGetBool);
            EnableAction(action, iDelegateGetBool, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetMultiple is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetMultiple must be overridden if this is called.</remarks>
        protected void EnableActionSetMultiple()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetMultiple");
            action.AddInputParameter(new ParameterRelated("ValueUint", iPropertyVarUint));
            action.AddInputParameter(new ParameterRelated("ValueInt", iPropertyVarInt));
            action.AddInputParameter(new ParameterRelated("ValueBool", iPropertyVarBool));
            iDelegateSetMultiple = new ActionDelegate(DoSetMultiple);
            EnableAction(action, iDelegateSetMultiple, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetString is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetString must be overridden if this is called.</remarks>
        protected void EnableActionSetString()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetString");
            action.AddInputParameter(new ParameterRelated("ValueStr", iPropertyVarStr));
            iDelegateSetString = new ActionDelegate(DoSetString);
            EnableAction(action, iDelegateSetString, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetString is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetString must be overridden if this is called.</remarks>
        protected void EnableActionGetString()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetString");
            action.AddOutputParameter(new ParameterRelated("ValueStr", iPropertyVarStr));
            iDelegateGetString = new ActionDelegate(DoGetString);
            EnableAction(action, iDelegateGetString, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetBinary is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetBinary must be overridden if this is called.</remarks>
        protected void EnableActionSetBinary()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetBinary");
            action.AddInputParameter(new ParameterRelated("ValueBin", iPropertyVarBin));
            iDelegateSetBinary = new ActionDelegate(DoSetBinary);
            EnableAction(action, iDelegateSetBinary, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetBinary is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetBinary must be overridden if this is called.</remarks>
        protected void EnableActionGetBinary()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetBinary");
            action.AddOutputParameter(new ParameterRelated("ValueBin", iPropertyVarBin));
            iDelegateGetBinary = new ActionDelegate(DoGetBinary);
            EnableAction(action, iDelegateGetBinary, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ToggleBool is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ToggleBool must be overridden if this is called.</remarks>
        protected void EnableActionToggleBool()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("ToggleBool");
            iDelegateToggleBool = new ActionDelegate(DoToggleBool);
            EnableAction(action, iDelegateToggleBool, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action WriteFile is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// WriteFile must be overridden if this is called.</remarks>
        protected void EnableActionWriteFile()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("WriteFile");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("Data", allowedValues));
            action.AddInputParameter(new ParameterString("FileFullName", allowedValues));
            iDelegateWriteFile = new ActionDelegate(DoWriteFile);
            EnableAction(action, iDelegateWriteFile, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Shutdown is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Shutdown must be overridden if this is called.</remarks>
        protected void EnableActionShutdown()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Shutdown");
            iDelegateShutdown = new ActionDelegate(DoShutdown);
            EnableAction(action, iDelegateShutdown, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Increment action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Increment action for the owning device.
        ///
        /// Must be implemented iff EnableActionIncrement was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Increment(uint aVersion, uint aValue, out uint aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Decrement action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Decrement action for the owning device.
        ///
        /// Must be implemented iff EnableActionDecrement was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Decrement(uint aVersion, int aValue, out int aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Toggle action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Toggle action for the owning device.
        ///
        /// Must be implemented iff EnableActionToggle was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Toggle(uint aVersion, bool aValue, out bool aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EchoString action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EchoString action for the owning device.
        ///
        /// Must be implemented iff EnableActionEchoString was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void EchoString(uint aVersion, string aValue, out string aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EchoBinary action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EchoBinary action for the owning device.
        ///
        /// Must be implemented iff EnableActionEchoBinary was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void EchoBinary(uint aVersion, byte[] aValue, out byte[] aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetUint action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetUint action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetUint was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueUint"></param>
        protected virtual void SetUint(uint aVersion, uint aValueUint)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetUint action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetUint action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetUint was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueUint"></param>
        protected virtual void GetUint(uint aVersion, out uint aValueUint)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetInt action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetInt action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetInt was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueInt"></param>
        protected virtual void SetInt(uint aVersion, int aValueInt)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetInt action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetInt action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetInt was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueInt"></param>
        protected virtual void GetInt(uint aVersion, out int aValueInt)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBool action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBool action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBool was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueBool"></param>
        protected virtual void SetBool(uint aVersion, bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBool action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBool action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBool was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueBool"></param>
        protected virtual void GetBool(uint aVersion, out bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetMultiple action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetMultiple action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetMultiple was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        protected virtual void SetMultiple(uint aVersion, uint aValueUint, int aValueInt, bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetString action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetString action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetString was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueStr"></param>
        protected virtual void SetString(uint aVersion, string aValueStr)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetString action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetString action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetString was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueStr"></param>
        protected virtual void GetString(uint aVersion, out string aValueStr)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetBinary action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetBinary action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetBinary was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueBin"></param>
        protected virtual void SetBinary(uint aVersion, byte[] aValueBin)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetBinary action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetBinary action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetBinary was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aValueBin"></param>
        protected virtual void GetBinary(uint aVersion, out byte[] aValueBin)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ToggleBool action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ToggleBool action for the owning device.
        ///
        /// Must be implemented iff EnableActionToggleBool was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void ToggleBool(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// WriteFile action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// WriteFile action for the owning device.
        ///
        /// Must be implemented iff EnableActionWriteFile was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aData"></param>
        /// <param name="aFileFullName"></param>
        protected virtual void WriteFile(uint aVersion, string aData, string aFileFullName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Shutdown action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Shutdown action for the owning device.
        ///
        /// Must be implemented iff EnableActionShutdown was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Shutdown(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        private static int DoIncrement(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            uint result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadUint("Value");
                invocation.ReadEnd();
                self.Increment(aVersion, value, out result);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Result", result);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoDecrement(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int value;
            int result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadInt("Value");
                invocation.ReadEnd();
                self.Decrement(aVersion, value, out result);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteInt("Result", result);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoToggle(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool value;
            bool result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadBool("Value");
                invocation.ReadEnd();
                self.Toggle(aVersion, value, out result);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("Result", result);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoEchoString(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            string result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadString("Value");
                invocation.ReadEnd();
                self.EchoString(aVersion, value, out result);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Result", result);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoEchoBinary(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            byte[] value;
            byte[] result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadBinary("Value");
                invocation.ReadEnd();
                self.EchoBinary(aVersion, value, out result);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBinary("Result", result);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetUint(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint valueUint;
            try
            {
                invocation.ReadStart();
                valueUint = invocation.ReadUint("ValueUint");
                invocation.ReadEnd();
                self.SetUint(aVersion, valueUint);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        private static int DoGetUint(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint valueUint;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetUint(aVersion, out valueUint);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("ValueUint", valueUint);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetInt(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int valueInt;
            try
            {
                invocation.ReadStart();
                valueInt = invocation.ReadInt("ValueInt");
                invocation.ReadEnd();
                self.SetInt(aVersion, valueInt);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        private static int DoGetInt(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int valueInt;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetInt(aVersion, out valueInt);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteInt("ValueInt", valueInt);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetBool(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool valueBool;
            try
            {
                invocation.ReadStart();
                valueBool = invocation.ReadBool("ValueBool");
                invocation.ReadEnd();
                self.SetBool(aVersion, valueBool);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        private static int DoGetBool(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool valueBool;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetBool(aVersion, out valueBool);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("ValueBool", valueBool);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetMultiple(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint valueUint;
            int valueInt;
            bool valueBool;
            try
            {
                invocation.ReadStart();
                valueUint = invocation.ReadUint("ValueUint");
                valueInt = invocation.ReadInt("ValueInt");
                valueBool = invocation.ReadBool("ValueBool");
                invocation.ReadEnd();
                self.SetMultiple(aVersion, valueUint, valueInt, valueBool);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        private static int DoSetString(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string valueStr;
            try
            {
                invocation.ReadStart();
                valueStr = invocation.ReadString("ValueStr");
                invocation.ReadEnd();
                self.SetString(aVersion, valueStr);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        private static int DoGetString(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string valueStr;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetString(aVersion, out valueStr);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("ValueStr", valueStr);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoSetBinary(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            byte[] valueBin;
            try
            {
                invocation.ReadStart();
                valueBin = invocation.ReadBinary("ValueBin");
                invocation.ReadEnd();
                self.SetBinary(aVersion, valueBin);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        private static int DoGetBinary(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            byte[] valueBin;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetBinary(aVersion, out valueBin);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBinary("ValueBin", valueBin);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoToggleBool(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ToggleBool(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        private static int DoWriteFile(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string data;
            string fileFullName;
            try
            {
                invocation.ReadStart();
                data = invocation.ReadString("Data");
                fileFullName = invocation.ReadString("FileFullName");
                invocation.ReadEnd();
                self.WriteFile(aVersion, data, fileFullName);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        private static int DoShutdown(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderZappOrgTestBasic1 self = (DvProviderZappOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Shutdown(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
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

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderZappOrgTestBasic1()
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

