using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using System.Linq;
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
            byte[] bin = new byte[128];
            for (i=0; i<127; i++) {
                bin[i] = (byte)(i+1);
            }
            bin[127] = 0;
            for (i=0; i<kTestIterations; i++) {
                byte[] result;
                proxy.SyncEchoBinary(bin, out result);
                Debug.Assert(SequencesEqual(bin, result));
            }

            proxy.Dispose();
        }
        
        private static bool SequencesEqual<T>(IEnumerable<T> xs, IEnumerable<T> ys)
        {
            return Enumerable.Zip(xs, ys, EqualityComparer<T>.Default.Equals).All(b=>b);
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
            uint propUint = proxy.PropertyVarUint();
            Debug.Assert(propUint == 1);
            uint valUint;
            proxy.SyncGetUint(out valUint);
            Debug.Assert(propUint == valUint);

            Console.Write("    Int...\n");
            proxy.SyncSetInt(-99);
            iUpdatesComplete.WaitOne();
            int propInt = proxy.PropertyVarInt();
            Debug.Assert(propInt == -99);
            int valInt;
            proxy.SyncGetInt(out valInt);
            Debug.Assert(propInt == valInt);

            Console.Write("    Bool...\n");
            proxy.SyncSetBool(true);
            iUpdatesComplete.WaitOne();
            bool propBool = proxy.PropertyVarBool();
            Debug.Assert(propBool);
            bool valBool;
            proxy.SyncGetBool(out valBool);
            Debug.Assert(valBool);

            Console.Write("    String...\n");
            string str = "<&'tag\">";
            proxy.SyncSetString(str);
            iUpdatesComplete.WaitOne();
            string propStr = proxy.PropertyVarStr();
            Debug.Assert(propStr == str);
            // test again to check that PropertyVarStr didn't TransferTo the property
            propStr = proxy.PropertyVarStr();
            Debug.Assert(propStr == str);
            string valStr;
            GC.Collect();
            proxy.SyncGetString(out valStr);
            Debug.Assert(propStr == valStr);

            Console.Write("    Binary...\n");
            byte[] bin = new byte[128];
            for (int i=0; i<127; i++) {
                bin[i] = (byte)(i+1);
            }
            bin[127] = 0;
            proxy.SyncSetBinary(bin);
            iUpdatesComplete.WaitOne();
            byte[] propBin = proxy.PropertyVarBin();
            Debug.Assert(SequencesEqual(propBin, bin));
            // test again to check that PropertyVarBin didn't TransferTo the property
            propBin = proxy.PropertyVarBin();
            Debug.Assert(SequencesEqual(propBin, bin));
            byte[] valBin;
            proxy.SyncGetBinary(out valBin);
            Debug.Assert(SequencesEqual(propBin, valBin));

            Console.Write("    Multiple...\n");
            proxy.SyncSetMultiple(15, 658, false);
            iUpdatesComplete.WaitOne();
            propUint = proxy.PropertyVarUint();
            Debug.Assert(propUint == 15);
            proxy.SyncGetUint(out valUint);
            Debug.Assert(propUint == valUint);
            propInt = proxy.PropertyVarInt();
            Debug.Assert(propInt == 658);
            proxy.SyncGetInt(out valInt);
            Debug.Assert(propInt == valInt);
            propBool = proxy.PropertyVarBool();
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
