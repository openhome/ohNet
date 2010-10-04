using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Zapp
{
    class Program
    {
        public static void Main(string[] args)
        {
            InitParams initParams = new InitParams();
            Library lib = new Library();
            lib.Initialise(ref initParams);
            lib.StartCp();
            new Runner();
            lib.Close();
        }
    }

    class Runner
    {
        private List<CpDevice> iDeviceList;
        private uint iActionCount;
        private uint iSubscriptionCount;
        private CpProxyUpnpOrgConnectionManager1 iConnMgr;
        private string iExpectedSink;
        private DateTime iActionPollStopTime;
        private Semaphore iActionPollStop;
        private Semaphore iSubscriptionSem;
        private const uint kDevicePollMs = 1000;
        private const uint kDevicePollSecs = 1;

        public Runner()
        {
            iDeviceList = new List<CpDevice>();
            CpDeviceList.ChangeHandler added = new CpDeviceList.ChangeHandler(DeviceAdded);
            CpDeviceList.ChangeHandler removed = new CpDeviceList.ChangeHandler(DeviceRemoved);
            CpDeviceListUpnpServiceType list = new CpDeviceListUpnpServiceType("upnp.org", "ConnectionManager", 1, added, removed);
            //CpDeviceListUpnpUuid list = new CpDeviceListUpnpUuid("896659847466-a4badbeaacbc-737837", added, removed);
            Semaphore sem = new Semaphore(0, 1);
            sem.WaitOne(6000);
            
            InvokeSync();
            // Note that following tests handle the device list changing (i.e. devices being switched on/off) badly

            Console.Write("\n\n");
            int count = iDeviceList.Count;
            DateTime startTime = DateTime.Now;
            PollInvoke();
            DateTime endTime = DateTime.Now;
            uint avgActions = 0;
            if (count > 0)
            {
                avgActions = (uint)(iActionCount / count);
            }
            double secs = endTime.Subtract(startTime).TotalSeconds;
            Console.Write("\n" + iActionCount + " actions invoked on " + count + " devices (avg " + avgActions + ") in " + secs + " seconds\n\n");

            Console.Write("\n\n");
            startTime = DateTime.Now;
            PollSubscribe();
            endTime = DateTime.Now;
            uint avgSubscriptions = 0;
            if (count > 0)
            {
                avgSubscriptions = (uint)(iSubscriptionCount / count);
            }
            secs = endTime.Subtract(startTime).TotalSeconds;
            Console.Write("\n" + iSubscriptionCount + " subscriptions on " + count + " devices (avg " + avgSubscriptions + ") in " + secs + " seconds\n\n");

            list.Dispose();
            Console.Write("Tests completed\n");
        }

        private void InvokeSync()
        {
            // trivial validation of the sync wrappers to all APIs
            // single sync call to whichever device happens to be first in our list
            if (iDeviceList.Count == 0)
            {
                Console.Write("No devices found, so nothing to test\n");
                return;
            }
            CpDevice device = iDeviceList[0];
            Console.Write("\n\nSync call to device " + device.Udn() + "\n");
            CpProxyUpnpOrgConnectionManager1 connMgr = new CpProxyUpnpOrgConnectionManager1(device);
            string source;
            string sink;
            connMgr.SyncGetProtocolInfo(out source, out sink);
            Console.Write("source is " + source + "\nsink is " + sink + "\n");
            connMgr.Dispose();
        }
        
        private void PollInvoke()
        {
            iActionPollStop = new Semaphore(0, 1);
            System.Timers.Timer timer = new System.Timers.Timer();
            timer.Elapsed += TimerElapsed;
            timer.AutoReset = false;
            for (int i=0; i<iDeviceList.Count; i++)
            {
                CpDevice device = iDeviceList[i];
                uint countBefore = iActionCount;
                Console.Write("Device " + device.Udn());
                iConnMgr = new CpProxyUpnpOrgConnectionManager1(device);
                iActionPollStopTime = DateTime.Now.AddMilliseconds(kDevicePollMs);
                timer.Interval = kDevicePollMs;
                timer.Enabled = false;
                timer.Enabled = true;
                for (int j=0; j<4; j++)
                {
                    iConnMgr.BeginGetProtocolInfo(GetProtocolInfoComplete);
                }
                iActionPollStop.WaitOne();
                Console.Write("    " + (iActionCount - countBefore) + "\n");
                iConnMgr.Dispose();
                iExpectedSink = null;
            }
        }

        private void PollSubscribe()
        {
            iSubscriptionSem = new Semaphore(0, 1);
            for (int i=0; i<iDeviceList.Count; i++)
            {
                CpDevice device = iDeviceList[i];
                string udn = device.Udn();
                if (udn == "896659847466-a4badbeaacbc-737837" ||
                    udn == "541d0cb5-3b34-4264-8ff0-d8653acf6425")
                    continue;
                uint countBefore = iSubscriptionCount;
                Console.Write("Device " + device.Udn());
                CpProxyUpnpOrgConnectionManager1 connMgr = new CpProxyUpnpOrgConnectionManager1(device);
                connMgr.SetPropertyChanged(PropertyChanged);
                DateTime startTime = DateTime.Now;
                while(true)
                {
                    connMgr.Subscribe();
                    iSubscriptionSem.WaitOne((int)(2 * kDevicePollMs));
                    connMgr.Unsubscribe();
                    DateTime now = DateTime.Now;
                    if (now.Subtract(startTime).TotalSeconds > kDevicePollSecs)
                    {
                        break;
                    }
                    iSubscriptionCount++;
                }
                Console.Write("    " + (iSubscriptionCount - countBefore) + "\n");
                connMgr.Dispose();
            }
        }

        private void TimerElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            iActionPollStop.Release();
        }

        private void GetProtocolInfoComplete(uint aAsyncHandle)
        {
            if (DateTime.Now >= iActionPollStopTime)
            {
                return;
            }
            iConnMgr.BeginGetProtocolInfo(GetProtocolInfoComplete);

            try
            {
                string source;
                string sink;
                iConnMgr.EndGetProtocolInfo(aAsyncHandle, out source, out sink);
                iActionCount++;
                if (sink == null && iExpectedSink != null)
                {
                    throw (new Exception());
                }
                else
                {
                    if (iExpectedSink == null)
                    {
                        iExpectedSink = sink;
                    }
                    else if (sink != iExpectedSink)
                    {
                        Console.Write("Expected " + iExpectedSink + "\n...got " + sink + "\n");
                    }
                }
            }
            catch (ProxyError) { }
        }

        private void PropertyChanged()
        {
            iSubscriptionSem.Release();
        }

        private void DeviceAdded(CpDeviceList aList, CpDevice aDevice)
        {
            lock (this)
            {
                PrintDeviceInfo("Added", aDevice);
                aDevice.AddRef();
                iDeviceList.Add(aDevice);
            }
        }

        private void DeviceRemoved(CpDeviceList aList, CpDevice aDevice)
        {
            lock (this)
            {
                PrintDeviceInfo("Removed", aDevice);
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

        private void PrintDeviceInfo(string aPrologue, CpDevice aDevice)
        {
            string location;
            aDevice.GetAttribute("Upnp.Location", out location);
            string friendlyName;
            aDevice.GetAttribute("Upnp.FriendlyName", out friendlyName);
            Console.Write(aPrologue +
                          "\n    udn = " + aDevice.Udn() + 
                          "\n    location = " + location +
                          "\n    name = " + friendlyName + "\n");
        }
    }
}
