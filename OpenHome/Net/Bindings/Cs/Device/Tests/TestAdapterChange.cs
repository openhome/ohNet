using System;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;
using OpenHome.Net.Device;

namespace OpenHome.Net.Device
{
    class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Starting...");
            Runner runner = new Runner();
            while (true)
            {
                if (Console.ReadLine() == "quit")
                    break;
            }
            runner.Dispose();
            Console.WriteLine("Finished...");
        }
    }

    class Runner : IDisposable
    {
        private InitParams iInitParams;
        private Library iLibrary;

        public Runner()
        {
            iInitParams = new InitParams();
            iInitParams.DvUpnpWebServerPort = 0;
            iInitParams.LogOutput = new MessageListener(Log);
            iInitParams.SubnetListChangedListener = new ChangedListener(SubnetListChanged);
            iInitParams.SubnetAddedListener = new NetworkAdapterListener(SubnetAdded);
            iInitParams.SubnetRemovedListener = new NetworkAdapterListener(SubnetRemoved);
            iInitParams.NetworkAdapterChangedListener = new NetworkAdapterListener(NetworkAdapterChanged);
            iLibrary = Library.Create(iInitParams);
            Library.SetDebugLevel(Library.DebugLevel.Trace);
            SubnetList subnetList = new SubnetList();
            NetworkAdapter nif = subnetList.SubnetAt(0);
            uint subnet = nif.Subnet();
            subnetList.Dispose();
            iLibrary.StartCombined(subnet);
        }

        public void Dispose()
        {
            iLibrary.Dispose();
        }

        private void Log(string aMsg)
        {
            Console.WriteLine(aMsg);
        }

        private void SubnetListChanged()
        {
            Console.WriteLine("SubnetListChanged");
        }

        private void SubnetAdded(NetworkAdapter aAdapter)
        {
            Console.WriteLine(String.Format("SubnetAdded: {0}", aAdapter.Name()));
        }

        private void SubnetRemoved(NetworkAdapter aAdapter)
        {
            Console.WriteLine(String.Format("SubnetRemoved: {0}", aAdapter.Name()));
        }

        private void NetworkAdapterChanged(NetworkAdapter aAdapter)
        {
            Console.WriteLine(String.Format("NetworkAdapterChanged: {0}", aAdapter.Name()));
        }
    }
}
