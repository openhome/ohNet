using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;

namespace Zapp
{
    class ProviderTestBasic : DvProviderZappOrgTestBasic1
    {
        public ProviderTestBasic(DvDevice aDevice)
            : base(aDevice)
        {
            SetPropertyVarUint(0);
            SetPropertyVarInt(0);
            SetPropertyVarBool(false);
            string empty = "";
            SetPropertyVarStr(empty);
            SetPropertyVarBin(empty);

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

        protected override void EchoBinary(uint aVersion, string aValue, out string aResult)
        {
            aResult = aValue;
        }

        protected override void SetUint(uint aVersion, uint aValueUint)
        {
            SetPropertyVarUint(aValueUint);
        }

        protected override void GetUint(uint aVersion, out uint aValueUint)
        {
            GetPropertyVarUint(out aValueUint);
        }

        protected override void SetInt(uint aVersion, int aValueInt)
        {
            SetPropertyVarInt(aValueInt);
        }

        protected override void GetInt(uint aVersion, out int aValueInt)
        {
            GetPropertyVarInt(out aValueInt);
        }

        protected override void SetBool(uint aVersion, bool aValueBool)
        {
            SetPropertyVarBool(aValueBool);
        }

        protected override void GetBool(uint aVersion, out bool aValueBool)
        {
            GetPropertyVarBool(out aValueBool);
        }

        protected override void SetString(uint aVersion, string aValueStr)
        {
            SetPropertyVarStr(aValueStr);
        }

        protected override void GetString(uint aVersion, out string aValueStr)
        {
            GetPropertyVarStr(out aValueStr);
        }

        protected override void SetBinary(uint aVersion, string aValueBin)
        {
            SetPropertyVarBin(aValueBin);
        }

        protected override void GetBinary(uint aVersion, out string aValueBin)
        {
            GetPropertyVarBin(out aValueBin);
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
        private DvDevice iDevice;
        private DvProviderZappOrgTestBasic1 iTestBasic;

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
            iDevice = new DvDevice(gDeviceName);
            iDevice.SetAttribute("Upnp.Domain", "zapp.org");
            iDevice.SetAttribute("Upnp.Type", "Test");
            iDevice.SetAttribute("Upnp.Version", "1");
            iDevice.SetAttribute("Upnp.FriendlyName", "ZappTestDevice");
            iDevice.SetAttribute("Upnp.Manufacturer", "None");
            iDevice.SetAttribute("Upnp.ManufacturerUrl", "http://www.linn.co.uk");
            iDevice.SetAttribute("Upnp.ModelDescription", "Test service");
            iDevice.SetAttribute("Upnp.ModelName", "Zapp test device");
            iDevice.SetAttribute("Upnp.ModelNumber", "1");
            iDevice.SetAttribute("Upnp.ModelUrl", "http://www.linn.co.uk");
            iDevice.SetAttribute("Upnp.SerialNumber", "123456");
            iDevice.SetAttribute("Upnp.Upc", "123456654321");
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
