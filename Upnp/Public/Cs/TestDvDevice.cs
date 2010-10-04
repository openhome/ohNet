using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;

namespace Zapp
{
    class Program
    {
        public static void Main(string[] args)
        {
            InitParams initParams = new InitParams();
            initParams.SetMsearchTime(1);
            Library lib = new Library();
            lib.Initialise(ref initParams);
            lib.StartCombined();
            new Runner();
            lib.Close();
        }
    }

    class ServiceTestBasic : DvServiceZappOrgTestBasic1
    {
        public ServiceTestBasic(DvDevice aDevice)
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
            SetPropertyVarUint(aValueUint);
            SetPropertyVarInt(aValueInt);
            SetPropertyVarBool(aValueBool);
        }
    }
    
    class DeviceBasic : IDisposable
    {
        public static string gDeviceName = "device";
        private DvDevice iDevice;
        private DvServiceZappOrgTestBasic1 iTestBasic;

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
            iTestBasic = new ServiceTestBasic(iDevice);
            iDevice.SetEnabled();
        }
        
        public void Dispose()
        {
            iTestBasic.Dispose();
            iDevice.Dispose();
        }
    }
    
    class Runner
    {
        private List<CpDevice> iDeviceList;
        private Semaphore iUpdatesComplete;
        private Semaphore iSingleChanged;
        private const uint kTestIterations = 10;

        public Runner()
        {
            Console.Write("TestDvDeviceCpp - starting\n");

            iUpdatesComplete = new Semaphore(0, Int32.MaxValue);
            iSingleChanged = new Semaphore(0, Int32.MaxValue);
            DeviceBasic device = new DeviceBasic();
            iDeviceList = new List<CpDevice>();
            CpDeviceList.ChangeHandler added = new CpDeviceList.ChangeHandler(DeviceAdded);
            CpDeviceList.ChangeHandler removed = new CpDeviceList.ChangeHandler(DeviceRemoved);
            CpDeviceListUpnpServiceType list = new CpDeviceListUpnpServiceType("zapp.org", "TestBasic", 1, added, removed);
            Semaphore sem = new Semaphore(0, 1);
            sem.WaitOne(1000);
            TestActions();
	        TestSubscriptions();
            list.Dispose();
            device.Dispose();

            Console.Write("TestDvDeviceCpp - completed\n");
        }

        private void TestActions()
        {
            Console.Write("  Actions\n");
            Debug.Assert(iDeviceList.Count == 1);
            CpProxyZappOrgTestBasic1 proxy = new CpProxyZappOrgTestBasic1(iDeviceList[0]);
            uint i;

            Console.Write("    Unsigned integer arguments...\n");
            uint valUint = 15;
            for (i=0; i<kTestIterations; i++) {
                uint result;
                proxy.SyncIncrement(valUint, out result);
                Debug.Assert(result == valUint+1);
                valUint = result;
            }

            Console.Write("    Integer arguments...\n");
            int valInt = 3;
            for (i=0; i<kTestIterations; i++) {
                int result;
                proxy.SyncDecrement(valInt, out result);
                Debug.Assert(result == valInt-1);
                valInt = result;
            }

            Console.Write("    Boolean arguments...\n");
            bool valBool = true;
            for (i=0; i<kTestIterations; i++) {
                bool result;
                proxy.SyncToggle(valBool, out result);
                Debug.Assert(result == !valBool);
                valBool = result;
            }

            Console.Write("    String arguments...\n");
            string valStr = "<&'tag\">";
            for (i=0; i<kTestIterations; i++) {
                string result;
                proxy.SyncEchoString(valStr, out result);
                Debug.Assert(result == valStr);
            }

            Console.Write("    Binary arguments...\n");
            char[] bin = new char[128];
            for (i=0; i<127; i++) {
                bin[i] = (char)(i+1);
            }
            bin[127] = '\0';
            string valBin = new string(bin);
            for (i=0; i<kTestIterations; i++) {
                string result;
                proxy.SyncEchoBinary(valStr, out result);
                Debug.Assert(result == valStr);
            }

            proxy.Dispose();
        }

        private void TestSubscriptions()
        {
            Console.Write("  Subscriptions\n");
            Debug.Assert(iDeviceList.Count == 1);
            CpProxyZappOrgTestBasic1 proxy = new CpProxyZappOrgTestBasic1(iDeviceList[0]);
            proxy.SetPropertyChanged(UpdatesComplete);
            proxy.Subscribe();
            iUpdatesComplete.WaitOne(); // wait for initial event

            // set callbacks for individual property changes now to avoid all being run by initial event
            proxy.SetPropertyVarUintChanged(SingleChanged);
            proxy.SetPropertyVarIntChanged(SingleChanged);
            proxy.SetPropertyVarBoolChanged(SingleChanged);
            proxy.SetPropertyVarStrChanged(SingleChanged);
            proxy.SetPropertyVarBinChanged(SingleChanged);


            /* For each property,
                 call its setter action
                 wait on a property being updated
                 check that the property matches the value set
                 check that the getter action matches the property
            */

            Console.Write("    Uint...\n");
            proxy.SyncSetUint(1);
            iSingleChanged.WaitOne();
            uint propUint;
            proxy.PropertyVarUint(out propUint);
            Debug.Assert(propUint == 1);
            uint valUint;
            proxy.SyncGetUint(out valUint);
            Debug.Assert(propUint == valUint);

            Console.Write("    Int...\n");
            proxy.SyncSetInt(-99);
            iSingleChanged.WaitOne();
            int propInt;
            proxy.PropertyVarInt(out propInt);
            Debug.Assert(propInt == -99);
            int valInt;
            proxy.SyncGetInt(out valInt);
            Debug.Assert(propInt == valInt);

            Console.Write("    Bool...\n");
            proxy.SyncSetBool(true);
            iSingleChanged.WaitOne();
            bool propBool;
            proxy.PropertyVarBool(out propBool);
            Debug.Assert(propBool);
            bool valBool;
            proxy.SyncGetBool(out valBool);
            Debug.Assert(valBool);

            Console.Write("    String...\n");
            string str = "<&'tag\">";
            proxy.SyncSetString(str);
            iSingleChanged.WaitOne();
            string propStr;
            proxy.PropertyVarStr(out propStr);
            Debug.Assert(propStr == str);
            // test again to check that PropertyVarStr didn't TransferTo the property
            proxy.PropertyVarStr(out propStr);
            Debug.Assert(propStr == str);
            string valStr;
            GC.Collect();
            proxy.SyncGetString(out valStr);
            Debug.Assert(propStr == valStr);

            Console.Write("    Binary...\n");
            char[] bin = new char[128];
            for (int i=0; i<127; i++) {
                bin[i] = (char)(i+1);
            }
            bin[127] = '\0';
            string bufBin = new string(bin);
            proxy.SyncSetBinary(bufBin);
            iSingleChanged.WaitOne();
            string propBin;
            proxy.PropertyVarBin(out propBin);
            Debug.Assert(propBin == bufBin);
            // test again to check that PropertyVarBin didn't TransferTo the property
            proxy.PropertyVarBin(out propBin);
            Debug.Assert(propBin == bufBin);
            string valBin;
            proxy.SyncGetBinary(out valBin);
            Debug.Assert(propBin == valBin);

            Console.Write("    Multiple...\n");
            int waitCount = iUpdatesComplete.Release();
            waitCount++;
            while (waitCount > 0)
            {
                iUpdatesComplete.WaitOne();
                waitCount--;
            }
            proxy.SyncSetMultiple(15, 658, false);
            iUpdatesComplete.WaitOne();
            proxy.PropertyVarUint(out propUint);
            Debug.Assert(propUint == 15);
            proxy.SyncGetUint(out valUint);
            Debug.Assert(propUint == valUint);
            proxy.PropertyVarInt(out propInt);
            Debug.Assert(propInt == 658);
            proxy.SyncGetInt(out valInt);
            Debug.Assert(propInt == valInt);
            proxy.PropertyVarBool(out propBool);
            Debug.Assert(!propBool);
            proxy.SyncGetBool(out valBool);
            Debug.Assert(!valBool);

            proxy.Dispose(); // automatically unsubscribes
        }

        private void UpdatesComplete()
        {
            iUpdatesComplete.Release();
        }

        private void SingleChanged()
        {
            iSingleChanged.Release();
        }
        
        private void DeviceAdded(CpDeviceList aList, CpDevice aDevice)
        {
            lock (this)
            {
                if (aDevice.Udn() == DeviceBasic.gDeviceName)
                {
                    aDevice.AddRef();
                    iDeviceList.Add(aDevice);
                }
            }
        }

        private void DeviceRemoved(CpDeviceList aList, CpDevice aDevice)
        {
            lock (this)
            {
                string udn = aDevice.Udn();
                int count = iDeviceList.Count;
                for (int i = 0; i < count; i++)
                {
                    if (iDeviceList[i].Udn() == udn)
                    {
                        iDeviceList.RemoveAt(i);
                        iDeviceList[i].RemoveRef();
                    }
                }
            }
        }
    }
}
