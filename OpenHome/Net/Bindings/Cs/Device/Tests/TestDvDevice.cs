using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;
using OpenHome.Net.Device;

namespace OpenHome.Net.Device
{
    class Program
    {
        public static void Main(string[] args)
        {
            InitParams initParams = new InitParams
            {
                MsearchTimeSecs = 1,
                UseLoopbackNetworkAdapter = true,
                DvUpnpWebServerPort = 0
            };
            using (Library lib = Library.Create(initParams))
            {
                SubnetList subnetList = new SubnetList();
                NetworkAdapter nif = subnetList.SubnetAt(0);
                uint subnet = nif.Subnet();
                subnetList.Dispose();
                lib.StartCombined(subnet);
                new Runner();
            }
        }
    }

    class Runner
    {
        private List<ICpDevice> iDeviceList;

        public Runner()
        {
            Console.Write("TestDvDeviceCs - starting\n");

            DeviceBasic device = new DeviceBasic();
            iDeviceList = new List<ICpDevice>();
            CpDeviceList.ChangeHandler added = new CpDeviceList.ChangeHandler(DeviceAdded);
            CpDeviceList.ChangeHandler removed = new CpDeviceList.ChangeHandler(DeviceRemoved);
            CpDeviceListUpnpServiceType list = new CpDeviceListUpnpServiceType("openhome.org", "TestBasic", 1, added, removed);
            Semaphore sem = new Semaphore(0, 1);
            sem.WaitOne(1000);
            Debug.Assert(iDeviceList.Count == 1);
            TestBasicCp cp = new TestBasicCp(iDeviceList[0]);
            cp.TestActions();
            cp.TestSubscriptions();
            list.Dispose();
            lock (this)
            {
                for (int i = 0; i < iDeviceList.Count; i++)
                {
                    iDeviceList[i].RemoveRef();
                }
            }
            device.Dispose();

            Console.Write("TestDvDeviceCs - completed\n");
        }

        private void DeviceAdded(CpDeviceList aList, ICpDevice aDevice)
        {
            lock (this)
            {
                if (iDeviceList.Count == 0 && aDevice.Udn() == DeviceBasic.gDeviceName)
                {
                    aDevice.AddRef();
                    iDeviceList.Add(aDevice);
                }
            }
        }

        private void DeviceRemoved(CpDeviceList aList, ICpDevice aDevice)
        {
            /* The device stack sends byebyes then alives for each newly enabled device.
               These can be interleaved with responses to a msearch and can cause tests to misbehave,
               thinking a device has been removed.  The simplest way to work around this is to say
               our test guarantees that a device remains available as long as its needed then take
               advantage of this by ignoring device removed callbacks. */
            /*lock (this)
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
            }*/
        }
    }
}
