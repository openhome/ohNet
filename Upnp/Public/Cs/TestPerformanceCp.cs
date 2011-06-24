using System;
using System.Threading;
using System.Collections.Generic;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;
using OpenHome.Net.ControlPoint.Proxies;

namespace OpenHome.Net.Device
{
    class Program
    {
        class ThreadArgs
        {
            public CpDevice Device { get; private set; }
            public int Count
            {
                get { lock (this) { return iCount; } }
            }

            private DateTime iStopTime;
            private int iCount;

            public ThreadArgs(CpDevice aDevice, double aDurationMs)
            {
                Device = aDevice;
                iStopTime = DateTime.Now.AddMilliseconds(aDurationMs);
            }
            public bool IncrementCount()
            {
                lock (this)
                {
                    if (DateTime.Now <= iStopTime)
                    {
                        iCount++;
                        return true;
                    }
                    return false;
                }
            }
        }

        private static readonly int kTestDurationMs = 1000;

        public static void Main(string[] aArgs)
        {
            Console.WriteLine("TestPerformanceCpCs - starting");
            InitParams initParams = new InitParams();
            using (Library lib = Library.Create(initParams))
            {
                IntPtr subnetList = lib.SubnetListCreate();
                IntPtr nif = lib.SubnetAt(subnetList, 0);
                uint subnet = lib.NetworkAdapterSubnet(nif);
                lib.SubnetListDestroy(subnetList);
                var deviceListFactory = new CpUpnpDeviceListFactory(lib.StartCp(subnet));
                CpDevice device = null;
                Semaphore sem = new Semaphore(0, 1);
                var deviceList = deviceListFactory.CreateListServiceType("openhome.org", "TestBasic", 1,
                        (aDeviceList, aDevice) =>
                        {
                            if (device != null)
                            {
                                throw new Exception("Found more than one device.  Giving up as test results will probably be invalid.");
                            }
                            device = aDevice;
                            device.AddRef();
                            sem.Release();
                        },
                        (aDeviceList, aDevice) =>
                        {
                            throw new Exception("ERROR: Device removed while test is running.");
                        });
                sem.WaitOne();

                // actions
                Console.WriteLine("");
                int[] threadCounts = { 1, 2, 4 };
                foreach (int threadCount in threadCounts)
                {
                    List<Thread> threads = new List<Thread>();
                    for (int i = 0; i < threadCount; i++)
                    {
                        threads.Add(new Thread(ActionThread));
                    }
                    ThreadArgs threadArgs = new ThreadArgs(device, kTestDurationMs);
                    for (int i = 0; i < threadCount; i++)
                    {
                        threads[i].Start(threadArgs);
                    }
                    for (int i = 0; i < threadCount; i++)
                    {
                        threads[i].Join();
                    }
                    Console.WriteLine("Invoked {0} actions in {1}ms using {2} threads", threadArgs.Count, kTestDurationMs, threadCount);
                }

                // subscriptions
                Thread thread = new Thread(SubscriptionThread);
                ThreadArgs args = new ThreadArgs(device, kTestDurationMs);
                thread.Start(args);
                thread.Join();
                Console.WriteLine("\nCompleted {0} subscriptions in {1}ms\n", args.Count, kTestDurationMs);

                device.RemoveRef();
                deviceList.Dispose();
                Console.WriteLine("\nTests complete.  Press 'q' to exit.");
                while (Console.ReadKey(true).KeyChar != 'q') ;
            }
        }
        private static void ActionThread(object aArgs)
        {
            ThreadArgs args = (ThreadArgs)aArgs;
            using (CpProxyOpenhomeOrgTestBasic1 proxy = new CpProxyOpenhomeOrgTestBasic1(args.Device))
            {
                uint val;
                do
                {
                    proxy.SyncGetUint(out val);
                } while (args.IncrementCount());
            }
        }
        private static void SubscriptionThread(object aArgs)
        {
            ThreadArgs args = (ThreadArgs)aArgs;
            Semaphore sem = new Semaphore(0, 1);
            do
            {
                CpProxyOpenhomeOrgTestBasic1 proxy = new CpProxyOpenhomeOrgTestBasic1(args.Device);
                proxy.SetPropertyChanged(() => sem.Release());
                proxy.Subscribe();
                sem.WaitOne();
                proxy.Dispose();
            } while (args.IncrementCount());
        }
    }
}
