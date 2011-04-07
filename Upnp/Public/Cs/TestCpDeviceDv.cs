using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using Zapp.Core;
using Zapp.ControlPoint;
using Zapp.Device;

namespace Zapp
{
    class Program
    {
        public static void Main(string[] args)
        {
            InitParams initParams = new InitParams();
            initParams.SetMsearchTime(1);
            initParams.SetUseLoopbackNetworkInterface();
            Library lib = new Library();
            lib.Initialise(initParams);
            lib.StartCombined();

            Console.Write("TestDvDeviceCs - starting\n");
            DeviceBasic device = new DeviceBasic();
            CpDeviceDv cpDevice = new CpDeviceDv(device.Device());
            TestBasicCp cp = new TestBasicCp(cpDevice);
            cp.TestActions();
            cp.TestSubscriptions();
            cpDevice.RemoveRef();
            device.Dispose();
            Console.Write("TestDvDeviceCpp - completed\n");
            
            lib.Close();
        }
    }
}
