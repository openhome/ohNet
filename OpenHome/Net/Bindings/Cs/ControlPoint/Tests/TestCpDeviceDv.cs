using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;
using OpenHome.Net.Device;

namespace OpenHome.Net
{
    class Program
    {
        public static void Main(string[] args)
        {
            InitParams initParams = new InitParams
            {
                MsearchTimeSecs = 1,
                UseLoopbackNetworkAdapter = true
            };
            using (Library lib = Library.Create(initParams))
            {
                SubnetList subnetList = new SubnetList();
                NetworkAdapter nif = subnetList.SubnetAt(0);
                uint subnet = nif.Subnet();
                subnetList.Dispose();
                lib.StartCombined(subnet);

                Console.Write("TestCpDeviceDvCs - starting\n");
                DeviceBasic device = new DeviceBasic();
                CpDeviceDv cpDevice = new CpDeviceDv(device.Device());
                TestBasicCp cp = new TestBasicCp(cpDevice);
                cp.TestActions();
                cp.TestSubscriptions();
                cpDevice.RemoveRef();
                device.Dispose();
                Console.Write("TestCpDeviceDvCs - completed\n");
            }
        }
    }
}
