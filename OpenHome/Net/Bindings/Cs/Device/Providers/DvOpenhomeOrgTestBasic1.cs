using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderOpenhomeOrgTestBasic1 : IDisposable
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
        /// <returns>Value of the VarUint property.</param>
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
        /// <returns>Value of the VarInt property.</param>
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
        /// <returns>Value of the VarBool property.</param>
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
        /// <returns>Value of the VarStr property.</param>
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
        /// <returns>Value of the VarBin property.</param>
        byte[] PropertyVarBin();
    }
    /// <summary>
    /// Provider for the openhome.org:TestBasic:1 UPnP service
    /// </summary>
    public class DvProviderOpenhomeOrgTestBasic1 : DvProvider, IDisposable, IDvProviderOpenhomeOrgTestBasic1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateIncrement;
        private ActionDelegate iDelegateEchoAllowedRangeUint;
        private ActionDelegate iDelegateDecrement;
        private ActionDelegate iDelegateToggle;
        private ActionDelegate iDelegateEchoString;
        private ActionDelegate iDelegateEchoAllowedValueString;
        private ActionDelegate iDelegateEchoBinary;
        private ActionDelegate iDelegateSetUint;
        private ActionDelegate iDelegateGetUint;
        private ActionDelegate iDelegateSetInt;
        private ActionDelegate iDelegateGetInt;
        private ActionDelegate iDelegateSetBool;
        private ActionDelegate iDelegateGetBool;
        private ActionDelegate iDelegateSetMultiple;
        private ActionDelegate iDelegateGetMultiple;
        private ActionDelegate iDelegateSetString;
        private ActionDelegate iDelegateGetString;
        private ActionDelegate iDelegateSetBinary;
        private ActionDelegate iDelegateGetBinary;
        private ActionDelegate iDelegateToggleBool;
        private ActionDelegate iDelegateReportError;
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
        protected DvProviderOpenhomeOrgTestBasic1(DvDevice aDevice)
            : base(aDevice, "openhome.org", "TestBasic", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the VarUint property.
        /// </summary>
        public void EnablePropertyVarUint()
        {
            iPropertyVarUint = new PropertyUint(new ParameterUint("VarUint"));
            AddProperty(iPropertyVarUint);
        }

        /// <summary>
        /// Enable the VarInt property.
        /// </summary>
        public void EnablePropertyVarInt()
        {
            iPropertyVarInt = new PropertyInt(new ParameterInt("VarInt"));
            AddProperty(iPropertyVarInt);
        }

        /// <summary>
        /// Enable the VarBool property.
        /// </summary>
        public void EnablePropertyVarBool()
        {
            iPropertyVarBool = new PropertyBool(new ParameterBool("VarBool"));
            AddProperty(iPropertyVarBool);
        }

        /// <summary>
        /// Enable the VarStr property.
        /// </summary>
        public void EnablePropertyVarStr()
        {
            List<String> allowedValues = new List<String>();
            iPropertyVarStr = new PropertyString(new ParameterString("VarStr", allowedValues));
            AddProperty(iPropertyVarStr);
        }

        /// <summary>
        /// Enable the VarBin property.
        /// </summary>
        public void EnablePropertyVarBin()
        {
            iPropertyVarBin = new PropertyBinary(new ParameterBinary("VarBin"));
            AddProperty(iPropertyVarBin);
        }

        /// <summary>
        /// Set the value of the VarUint property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarUint has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarUint(uint aValue)
        {
            if (iPropertyVarUint == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertyVarUint, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarUint property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarUint has previously been called.</remarks>
        /// <returns>Value of the VarUint property.</returns>
        public uint PropertyVarUint()
        {
            if (iPropertyVarUint == null)
                throw new PropertyDisabledError();
            return iPropertyVarUint.Value();
        }

        /// <summary>
        /// Set the value of the VarInt property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarInt has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarInt(int aValue)
        {
            if (iPropertyVarInt == null)
                throw new PropertyDisabledError();
            return SetPropertyInt(iPropertyVarInt, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarInt property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarInt has previously been called.</remarks>
        /// <returns>Value of the VarInt property.</returns>
        public int PropertyVarInt()
        {
            if (iPropertyVarInt == null)
                throw new PropertyDisabledError();
            return iPropertyVarInt.Value();
        }

        /// <summary>
        /// Set the value of the VarBool property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarBool has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarBool(bool aValue)
        {
            if (iPropertyVarBool == null)
                throw new PropertyDisabledError();
            return SetPropertyBool(iPropertyVarBool, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarBool property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarBool has previously been called.</remarks>
        /// <returns>Value of the VarBool property.</returns>
        public bool PropertyVarBool()
        {
            if (iPropertyVarBool == null)
                throw new PropertyDisabledError();
            return iPropertyVarBool.Value();
        }

        /// <summary>
        /// Set the value of the VarStr property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarStr has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarStr(string aValue)
        {
            if (iPropertyVarStr == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyVarStr, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarStr property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarStr has previously been called.</remarks>
        /// <returns>Value of the VarStr property.</returns>
        public string PropertyVarStr()
        {
            if (iPropertyVarStr == null)
                throw new PropertyDisabledError();
            return iPropertyVarStr.Value();
        }

        /// <summary>
        /// Set the value of the VarBin property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarBin has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyVarBin(byte[] aValue)
        {
            if (iPropertyVarBin == null)
                throw new PropertyDisabledError();
            return SetPropertyBinary(iPropertyVarBin, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the VarBin property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyVarBin has previously been called.</remarks>
        /// <returns>Value of the VarBin property.</returns>
        public byte[] PropertyVarBin()
        {
            if (iPropertyVarBin == null)
                throw new PropertyDisabledError();
            return iPropertyVarBin.Value();
        }

        /// <summary>
        /// Signal that the action Increment is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Increment must be overridden if this is called.</remarks>
        protected void EnableActionIncrement()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Increment");
            action.AddInputParameter(new ParameterUint("Value"));
            action.AddOutputParameter(new ParameterUint("Result"));
            iDelegateIncrement = new ActionDelegate(DoIncrement);
            EnableAction(action, iDelegateIncrement, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action EchoAllowedRangeUint is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// EchoAllowedRangeUint must be overridden if this is called.</remarks>
        protected void EnableActionEchoAllowedRangeUint()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("EchoAllowedRangeUint");
            action.AddInputParameter(new ParameterUint("Value", 10, 20));
            action.AddOutputParameter(new ParameterUint("Result"));
            iDelegateEchoAllowedRangeUint = new ActionDelegate(DoEchoAllowedRangeUint);
            EnableAction(action, iDelegateEchoAllowedRangeUint, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Decrement is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Decrement must be overridden if this is called.</remarks>
        protected void EnableActionDecrement()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Decrement");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Toggle");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("EchoString");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("Value", allowedValues));
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            iDelegateEchoString = new ActionDelegate(DoEchoString);
            EnableAction(action, iDelegateEchoString, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action EchoAllowedValueString is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// EchoAllowedValueString must be overridden if this is called.</remarks>
        protected void EnableActionEchoAllowedValueString()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("EchoAllowedValueString");
            List<String> allowedValues = new List<String>();
            allowedValues.Add("One");
            allowedValues.Add("Two");
            allowedValues.Add("Three");
            allowedValues.Add("Four");
            action.AddInputParameter(new ParameterString("Value", allowedValues));
            allowedValues.Clear();
            action.AddOutputParameter(new ParameterString("Result", allowedValues));
            iDelegateEchoAllowedValueString = new ActionDelegate(DoEchoAllowedValueString);
            EnableAction(action, iDelegateEchoAllowedValueString, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action EchoBinary is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// EchoBinary must be overridden if this is called.</remarks>
        protected void EnableActionEchoBinary()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("EchoBinary");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetUint");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetUint");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetInt");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetInt");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetBool");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetBool");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetMultiple");
            action.AddInputParameter(new ParameterRelated("ValueUint", iPropertyVarUint));
            action.AddInputParameter(new ParameterRelated("ValueInt", iPropertyVarInt));
            action.AddInputParameter(new ParameterRelated("ValueBool", iPropertyVarBool));
            iDelegateSetMultiple = new ActionDelegate(DoSetMultiple);
            EnableAction(action, iDelegateSetMultiple, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetMultiple is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetMultiple must be overridden if this is called.</remarks>
        protected void EnableActionGetMultiple()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetMultiple");
            action.AddOutputParameter(new ParameterRelated("ValueUint", iPropertyVarUint));
            action.AddOutputParameter(new ParameterRelated("ValueInt", iPropertyVarInt));
            action.AddOutputParameter(new ParameterRelated("ValueBool", iPropertyVarBool));
            iDelegateGetMultiple = new ActionDelegate(DoGetMultiple);
            EnableAction(action, iDelegateGetMultiple, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetString is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetString must be overridden if this is called.</remarks>
        protected void EnableActionSetString()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetString");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetString");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetBinary");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("GetBinary");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ToggleBool");
            iDelegateToggleBool = new ActionDelegate(DoToggleBool);
            EnableAction(action, iDelegateToggleBool, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action ReportError is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// ReportError must be overridden if this is called.</remarks>
        protected void EnableActionReportError()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("ReportError");
            iDelegateReportError = new ActionDelegate(DoReportError);
            EnableAction(action, iDelegateReportError, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action WriteFile is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// WriteFile must be overridden if this is called.</remarks>
        protected void EnableActionWriteFile()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("WriteFile");
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
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Shutdown");
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Increment(IDvInvocation aInvocation, uint aValue, out uint aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EchoAllowedRangeUint action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EchoAllowedRangeUint action for the owning device.
        ///
        /// Must be implemented iff EnableActionEchoAllowedRangeUint was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void EchoAllowedRangeUint(IDvInvocation aInvocation, uint aValue, out uint aResult)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Decrement(IDvInvocation aInvocation, int aValue, out int aResult)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void Toggle(IDvInvocation aInvocation, bool aValue, out bool aResult)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void EchoString(IDvInvocation aInvocation, string aValue, out string aResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// EchoAllowedValueString action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// EchoAllowedValueString action for the owning device.
        ///
        /// Must be implemented iff EnableActionEchoAllowedValueString was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void EchoAllowedValueString(IDvInvocation aInvocation, string aValue, out string aResult)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        /// <param name="aResult"></param>
        protected virtual void EchoBinary(IDvInvocation aInvocation, byte[] aValue, out byte[] aResult)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueUint"></param>
        protected virtual void SetUint(IDvInvocation aInvocation, uint aValueUint)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueUint"></param>
        protected virtual void GetUint(IDvInvocation aInvocation, out uint aValueUint)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueInt"></param>
        protected virtual void SetInt(IDvInvocation aInvocation, int aValueInt)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueInt"></param>
        protected virtual void GetInt(IDvInvocation aInvocation, out int aValueInt)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueBool"></param>
        protected virtual void SetBool(IDvInvocation aInvocation, bool aValueBool)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueBool"></param>
        protected virtual void GetBool(IDvInvocation aInvocation, out bool aValueBool)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        protected virtual void SetMultiple(IDvInvocation aInvocation, uint aValueUint, int aValueInt, bool aValueBool)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetMultiple action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetMultiple action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetMultiple was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueUint"></param>
        /// <param name="aValueInt"></param>
        /// <param name="aValueBool"></param>
        protected virtual void GetMultiple(IDvInvocation aInvocation, out uint aValueUint, out int aValueInt, out bool aValueBool)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueStr"></param>
        protected virtual void SetString(IDvInvocation aInvocation, string aValueStr)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueStr"></param>
        protected virtual void GetString(IDvInvocation aInvocation, out string aValueStr)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueBin"></param>
        protected virtual void SetBinary(IDvInvocation aInvocation, byte[] aValueBin)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValueBin"></param>
        protected virtual void GetBinary(IDvInvocation aInvocation, out byte[] aValueBin)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void ToggleBool(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ReportError action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ReportError action for the owning device.
        ///
        /// Must be implemented iff EnableActionReportError was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void ReportError(IDvInvocation aInvocation)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aData"></param>
        /// <param name="aFileFullName"></param>
        protected virtual void WriteFile(IDvInvocation aInvocation, string aData, string aFileFullName)
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
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        protected virtual void Shutdown(IDvInvocation aInvocation)
        {
            throw (new ActionDisabledError());
        }

        private static int DoIncrement(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            uint result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadUint("Value");
                invocation.ReadEnd();
                self.Increment(invocation, value, out result);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Increment");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Increment" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Increment" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Increment" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoEchoAllowedRangeUint(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            uint result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadUint("Value");
                invocation.ReadEnd();
                self.EchoAllowedRangeUint(invocation, value, out result);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "EchoAllowedRangeUint");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "EchoAllowedRangeUint" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "EchoAllowedRangeUint" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "EchoAllowedRangeUint" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoDecrement(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int value;
            int result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadInt("Value");
                invocation.ReadEnd();
                self.Decrement(invocation, value, out result);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Decrement");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Decrement" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Decrement" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Decrement" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoToggle(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool value;
            bool result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadBool("Value");
                invocation.ReadEnd();
                self.Toggle(invocation, value, out result);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Toggle");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Toggle" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Toggle" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Toggle" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoEchoString(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            string result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadString("Value");
                invocation.ReadEnd();
                self.EchoString(invocation, value, out result);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "EchoString");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "EchoString" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "EchoString" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "EchoString" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoEchoAllowedValueString(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            string result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadString("Value");
                invocation.ReadEnd();
                self.EchoAllowedValueString(invocation, value, out result);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "EchoAllowedValueString");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "EchoAllowedValueString" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "EchoAllowedValueString" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "EchoAllowedValueString" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoEchoBinary(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            byte[] value;
            byte[] result;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadBinary("Value");
                invocation.ReadEnd();
                self.EchoBinary(invocation, value, out result);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "EchoBinary");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "EchoBinary" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "EchoBinary" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "EchoBinary" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetUint(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint valueUint;
            try
            {
                invocation.ReadStart();
                valueUint = invocation.ReadUint("ValueUint");
                invocation.ReadEnd();
                self.SetUint(invocation, valueUint);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetUint");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetUint" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetUint" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetUint" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetUint(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint valueUint;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetUint(invocation, out valueUint);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetUint");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "GetUint" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetUint" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetUint" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetInt(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int valueInt;
            try
            {
                invocation.ReadStart();
                valueInt = invocation.ReadInt("ValueInt");
                invocation.ReadEnd();
                self.SetInt(invocation, valueInt);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetInt");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetInt" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetInt" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetInt" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetInt(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            int valueInt;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetInt(invocation, out valueInt);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetInt");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "GetInt" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetInt" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetInt" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetBool(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool valueBool;
            try
            {
                invocation.ReadStart();
                valueBool = invocation.ReadBool("ValueBool");
                invocation.ReadEnd();
                self.SetBool(invocation, valueBool);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetBool");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetBool" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetBool" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetBool" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetBool(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool valueBool;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetBool(invocation, out valueBool);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetBool");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "GetBool" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetBool" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetBool" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetMultiple(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
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
                self.SetMultiple(invocation, valueUint, valueInt, valueBool);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetMultiple");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetMultiple" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetMultiple" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetMultiple" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetMultiple(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint valueUint;
            int valueInt;
            bool valueBool;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetMultiple(invocation, out valueUint, out valueInt, out valueBool);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetMultiple");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "GetMultiple" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetMultiple" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("ValueUint", valueUint);
                invocation.WriteInt("ValueInt", valueInt);
                invocation.WriteBool("ValueBool", valueBool);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetMultiple" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetString(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string valueStr;
            try
            {
                invocation.ReadStart();
                valueStr = invocation.ReadString("ValueStr");
                invocation.ReadEnd();
                self.SetString(invocation, valueStr);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetString");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetString" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetString" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetString" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetString(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string valueStr;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetString(invocation, out valueStr);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetString");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "GetString" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetString" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetString" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetBinary(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            byte[] valueBin;
            try
            {
                invocation.ReadStart();
                valueBin = invocation.ReadBinary("ValueBin");
                invocation.ReadEnd();
                self.SetBinary(invocation, valueBin);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetBinary");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetBinary" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetBinary" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetBinary" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoGetBinary(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            byte[] valueBin;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetBinary(invocation, out valueBin);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "GetBinary");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "GetBinary" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetBinary" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "GetBinary" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoToggleBool(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ToggleBool(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ToggleBool");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "ToggleBool" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "ToggleBool" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "ToggleBool" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoReportError(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.ReportError(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "ReportError");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "ReportError" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "ReportError" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "ReportError" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoWriteFile(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string data;
            string fileFullName;
            try
            {
                invocation.ReadStart();
                data = invocation.ReadString("Data");
                fileFullName = invocation.ReadString("FileFullName");
                invocation.ReadEnd();
                self.WriteFile(invocation, data, fileFullName);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "WriteFile");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "WriteFile" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "WriteFile" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "WriteFile" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoShutdown(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestBasic1 self = (DvProviderOpenhomeOrgTestBasic1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Shutdown(invocation);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Shutdown");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Shutdown" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Shutdown" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
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
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Shutdown" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            if (DisposeProvider())
                iGch.Free();
        }
    }
}

