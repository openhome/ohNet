using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using OpenHome.Net.Device;
using OpenHome.Net.Device.Providers;

namespace OpenHome.Net
{
    class ProviderTestBasic : DvProviderOpenhomeOrgTestBasic1
    {
        public ProviderTestBasic(DvDevice aDevice)
            : base(aDevice)
        {
            EnablePropertyVarUint();
            EnablePropertyVarInt();
            EnablePropertyVarBool();
            EnablePropertyVarStr();
            EnablePropertyVarBin();
            SetPropertyVarUint(0);
            SetPropertyVarInt(0);
            SetPropertyVarBool(false);
            string empty = "";
            byte[] emptyBinary = new byte[0];
            SetPropertyVarStr(empty);
            SetPropertyVarBin(emptyBinary);

            EnableActionIncrement();
            EnableActionDecrement();
            EnableActionToggle();
            EnableActionEchoString();
            EnableActionEchoBinary();
            EnableActionSetUint();
            EnableActionGetUint();
            EnableActionSetInt();
            EnableActionGetInt();
            EnableActionSetBool();
            EnableActionGetBool();
            EnableActionSetString();
            EnableActionGetString();
            EnableActionSetBinary();
            EnableActionGetBinary();
            EnableActionSetMultiple();
        }

        protected override void Increment(IDvInvocation aInvocation, uint aValue, out uint aResult)
        {
            uint version = aInvocation.Version();
            if (version != 1)
                throw new Exception(String.Format("Unexpected result - {0} - from IDvInvocation.Version", version));
            aResult = aValue + 1;
        }

        protected override void Decrement(IDvInvocation aInvocation, int aValue, out int aResult)
        {
            aResult = aValue - 1;
        }

        protected override void Toggle(IDvInvocation aInvocation, bool aValue, out bool aResult)
        {
            aResult = !aValue;
        }

        protected override void EchoString(IDvInvocation aInvocation, string aValue, out string aResult)
        {
            aResult = aValue;
        }

        protected override void EchoBinary(IDvInvocation aInvocation, byte[] aValue, out byte[] aResult)
        {
            aResult = aValue;
        }

        protected override void SetUint(IDvInvocation aInvocation, uint aValueUint)
        {
            SetPropertyVarUint(aValueUint);
        }

        protected override void GetUint(IDvInvocation aInvocation, out uint aValueUint)
        {
            aValueUint = PropertyVarUint();
        }

        protected override void SetInt(IDvInvocation aInvocation, int aValueInt)
        {
            SetPropertyVarInt(aValueInt);
        }

        protected override void GetInt(IDvInvocation aInvocation, out int aValueInt)
        {
            aValueInt = PropertyVarInt();
        }

        protected override void SetBool(IDvInvocation aInvocation, bool aValueBool)
        {
            SetPropertyVarBool(aValueBool);
        }

        protected override void GetBool(IDvInvocation aInvocation, out bool aValueBool)
        {
            aValueBool = PropertyVarBool();
        }

        protected override void SetString(IDvInvocation aInvocation, string aValueStr)
        {
            SetPropertyVarStr(aValueStr);
        }

        protected override void GetString(IDvInvocation aInvocation, out string aValueStr)
        {
            aValueStr = PropertyVarStr();
        }

        protected override void SetBinary(IDvInvocation aInvocation, byte[] aValueBin)
        {
            SetPropertyVarBin(aValueBin);
        }

        protected override void GetBinary(IDvInvocation aInvocation, out byte[] aValueBin)
        {
            aValueBin = PropertyVarBin();
        }

        protected override void SetMultiple(IDvInvocation aInvocation, uint aValueUint, int aValueInt, bool aValueBool)
        {
            PropertiesLock();
            SetPropertyVarUint(aValueUint);
            SetPropertyVarInt(aValueInt);
            SetPropertyVarBool(aValueBool);
            PropertiesUnlock();
        }
    }
    
    class DeviceBasic : IDisposable
    {
        public static string gDeviceName = "device";
        private DvDeviceStandard iDevice;
        private DvProviderOpenhomeOrgTestBasic1 iTestBasic;

        private static void RandomiseUdn(out string aUdn)
        {
            aUdn = gDeviceName;
            aUdn += "-";
            Random rnd = new Random();
            aUdn += rnd.Next();
        }

        public DeviceBasic()
        {
            RandomiseUdn(out gDeviceName);
            iDevice = new DvDeviceStandard(gDeviceName);
            iDevice.SetAttribute("Upnp.Domain", "openhome.org");
            iDevice.SetAttribute("Upnp.Type", "Test");
            iDevice.SetAttribute("Upnp.Version", "1");
            iDevice.SetAttribute("Upnp.FriendlyName", "ohNetTestDevice");
            iDevice.SetAttribute("Upnp.Manufacturer", "None");
            iDevice.SetAttribute("Upnp.ModelName", "ohNet test device");
            iTestBasic = new ProviderTestBasic(iDevice);
            iDevice.SetEnabled();
        }

        public DvDevice Device()
        {
            return iDevice;
        }
        
        public void Dispose()
        {
            iDevice.Dispose();
            iTestBasic.Dispose();
        }
    }
}
