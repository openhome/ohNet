using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using Zapp.ControlPoint;
using Zapp.ControlPoint.Proxies;

namespace Zapp
{
    class TestBasicCp
    {
        private Semaphore iUpdatesComplete;
        private CpDevice iDevice;
        private const uint kTestIterations = 10;

        public TestBasicCp(CpDevice aDevice)
        {
            iDevice = aDevice;
            iUpdatesComplete = new Semaphore(0, Int32.MaxValue);
        }

        public void TestActions()
        {
            Console.Write("  Actions\n");
            CpProxyZappOrgTestBasic1 proxy = new CpProxyZappOrgTestBasic1(iDevice);
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
                proxy.SyncEchoBinary(valBin, out result);
                Debug.Assert(result == valBin);
            }

            proxy.Dispose();
        }

        public void TestSubscriptions()
        {
            Console.Write("  Subscriptions\n");
            CpProxyZappOrgTestBasic1 proxy = new CpProxyZappOrgTestBasic1(iDevice);
            proxy.SetPropertyChanged(UpdatesComplete);
            proxy.Subscribe();
            iUpdatesComplete.WaitOne(); // wait for initial event

            /* For each property,
                 call its setter action
                 wait on a property being updated
                 check that the property matches the value set
                 check that the getter action matches the property
            */

            Console.Write("    Uint...\n");
            proxy.SyncSetUint(1);
            iUpdatesComplete.WaitOne();
            uint propUint;
            proxy.PropertyVarUint(out propUint);
            Debug.Assert(propUint == 1);
            uint valUint;
            proxy.SyncGetUint(out valUint);
            Debug.Assert(propUint == valUint);

            Console.Write("    Int...\n");
            proxy.SyncSetInt(-99);
            iUpdatesComplete.WaitOne();
            int propInt;
            proxy.PropertyVarInt(out propInt);
            Debug.Assert(propInt == -99);
            int valInt;
            proxy.SyncGetInt(out valInt);
            Debug.Assert(propInt == valInt);

            Console.Write("    Bool...\n");
            proxy.SyncSetBool(true);
            iUpdatesComplete.WaitOne();
            bool propBool;
            proxy.PropertyVarBool(out propBool);
            Debug.Assert(propBool);
            bool valBool;
            proxy.SyncGetBool(out valBool);
            Debug.Assert(valBool);

            Console.Write("    String...\n");
            string str = "<&'tag\">";
            proxy.SyncSetString(str);
            iUpdatesComplete.WaitOne();
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
            iUpdatesComplete.WaitOne();
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
    }
}
