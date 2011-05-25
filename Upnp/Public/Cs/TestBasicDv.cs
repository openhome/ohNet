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

        protected override void Increment(uint aVersion, uint aValue, out uint aResult)
        {
            aResult = aValue + 1;
        }

        protected override void Decrement(uint aVersion, int aValue, out int aResult)
        {
            aResult = aValue - 1;
        }

        protected override void Toggle(uint aVersion, bool aValue, out bool aResult)
        {
            aResult = !aValue;
        }

        protected override void EchoString(uint aVersion, string aValue, out string aResult)
        {
            aResult = aValue;
        }

        protected override void EchoBinary(uint aVersion, byte[] aValue, out byte[] aResult)
        {
            aResult = aValue;
        }

        protected override void SetUint(uint aVersion, uint aValueUint)
        {
            SetPropertyVarUint(aValueUint);
        }

        protected override void GetUint(uint aVersion, out uint aValueUint)
        {
            aValueUint = PropertyVarUint();
        }

        protected override void SetInt(uint aVersion, int aValueInt)
        {
            SetPropertyVarInt(aValueInt);
        }

        protected override void GetInt(uint aVersion, out int aValueInt)
        {
            aValueInt = PropertyVarInt();
        }

        protected override void SetBool(uint aVersion, bool aValueBool)
        {
            SetPropertyVarBool(aValueBool);
        }

        protected override void GetBool(uint aVersion, out bool aValueBool)
        {
            aValueBool = PropertyVarBool();
        }

        protected override void SetString(uint aVersion, string aValueStr)
        {
            SetPropertyVarStr(aValueStr);
        }

        protected override void GetString(uint aVersion, out string aValueStr)
        {
            aValueStr = PropertyVarStr();
        }

        protected override void SetBinary(uint aVersion, byte[] aValueBin)
        {
            SetPropertyVarBin(aValueBin);
        }

        protected override void GetBinary(uint aVersion, out byte[] aValueBin)
        {
            aValueBin = PropertyVarBin();
        }

        protected override void SetMultiple(uint aVersion, uint aValueUint, int aValueInt, bool aValueBool)
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
            iTestBasic.Dispose();
            iDevice.Dispose();
        }
    }
}
