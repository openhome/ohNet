using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ZappSpy
{
    /// <summary>
    /// Finds and tracks UPnP devices on the network.
    /// </summary>
    public class UpnpDeviceFinder : IDisposable
    {
        private class UpnpDeviceCollection : IEnumerable<UpnpDeviceInfo>
        {
            private Dictionary<string, UpnpDeviceInfo> iDevices = new Dictionary<string,UpnpDeviceInfo>();
            private object iLock = new object();
            public void AddDevice(UpnpDeviceInfo aDevice)
            {
                lock (iLock)
                {
                    iDevices[aDevice.UDN] = aDevice;
                }
            }
            public bool TryGetDevice(string aDeviceUdn, out UpnpDeviceInfo aDeviceInfo)
            {
                lock (iLock)
                {
                    return iDevices.TryGetValue(aDeviceUdn, out aDeviceInfo);
                }
            }
            public void DropDevice(string aDeviceUdn)
            {
                lock (iLock)
                {
                    // Warning!: There's a race condition here. We can't be sure
                    // that we've handled the add event before the remove event
                    // comes along. In theory the adding thread could still be
                    // waiting to acquire the lock. If we get them out of order
                    // we'll end up with an orphaned device in the collection.
                    if (iDevices.ContainsKey(aDeviceUdn))
                    {
                        iDevices.Remove(aDeviceUdn);
                    }
                }
            }

            public IEnumerator<UpnpDeviceInfo> GetEnumerator()
            {
                List<UpnpDeviceInfo> deviceListCopy;
                lock (iLock)
                {
                    deviceListCopy = iDevices.Values.ToList();
                }
                return deviceListCopy.GetEnumerator();
            }

            System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
        }

        public UpnpDeviceFinder(ZappLibraryWrapper aZappLibrary)
        {
            iZappLibrary = aZappLibrary;
            iDeviceList = new Zapp.CpDeviceListUpnpRoot(
                HandleDeviceAdded,
                HandleDeviceRemoved);
            iDeviceList.Refresh();
        }

        /// <summary>
        /// Create a device finder that scans for a specific device, specified
        /// by its UUID.
        /// </summary>
        /// <param name="aUuid">UUID of the device to find.</param>
        public UpnpDeviceFinder(ZappLibraryWrapper aZappLibrary, string aUuid)
        {
            iZappLibrary = aZappLibrary;
            iDeviceList = new Zapp.CpDeviceListUpnpUuid(
                aUuid,
                HandleDeviceAdded,
                HandleDeviceRemoved);
        }

        public void Dispose()
        {
            iDeviceList.Dispose();
        }

        /// <summary>
        /// Rescan for devices.
        /// </summary>
        public void Refresh()
        {
            // It might be a good idea either to flush the list, or even better
            // to note which devices respond and after some time remove the rest
            // from the list.
            iDeviceList.Refresh();
        }

        public class UpnpDeviceEventArgs : EventArgs
        {
            public UpnpDeviceInfo DeviceInfo { get; set; }
        }

        /// <summary>
        /// Fired whenever a device is added to the network.
        /// </summary>
        /// <remarks>
        /// There's no guarantee which thread this will arrive on. We don't
        /// do anything to protect users from problems with message races.
        /// </remarks>
        public event Action<object, UpnpDeviceEventArgs> DeviceAdded;

        /// <summary>
        /// Fired whenever a device is removed from the network.
        /// </summary>
        /// <remarks>
        /// There's no guarantee which thread this will arrive on. We don't
        /// do anything to protect users from problems with message races.
        /// </remarks>
        public event Action<object, UpnpDeviceEventArgs> DeviceRemoved;

        /// <summary>
        /// The visible devices at some instant in time. Thread-safe for
        /// iterating - upon starting to iterate a copy is made, so you
        /// will not see changes that occur during the iteration.
        /// </summary>
        public IEnumerable<UpnpDeviceInfo> Devices
        {
            get
            {
                return iDevices;
            }
        }

        private ZappLibraryWrapper iZappLibrary;
        private UpnpDeviceCollection iDevices = new UpnpDeviceCollection();
        private Zapp.CpDeviceList iDeviceList;

        private void HandleDeviceAdded(Zapp.CpDeviceList aList, Zapp.CpDevice aDevice)
        {
            string xml;
            if (!aDevice.GetAttribute("Upnp.DeviceXml", out xml))
            {
                Console.WriteLine("Device has no DeviceXml.");
                return;
            }
            string uri;
            if (!aDevice.GetAttribute("Upnp.Location", out uri))
            {
                Console.WriteLine("Device has no Location???");
                return;
            }

            var info = UpnpDeviceInfo.FromXmlString(
                xml,
                new Uri(uri),
                new HttpFetcher());
            iDevices.AddDevice(info);

            var deviceAddedDelegate = DeviceAdded;
            if (deviceAddedDelegate != null)
            {
                deviceAddedDelegate.Invoke(this, new UpnpDeviceEventArgs { DeviceInfo = info });
            }
        }

        private void HandleDeviceRemoved(Zapp.CpDeviceList aList, Zapp.CpDevice aDevice)
        {
            UpnpDeviceInfo info;
            if (iDevices.TryGetDevice(aDevice.Udn(), out info))
            {
                iDevices.DropDevice(aDevice.Udn());
                var deviceRemovedDelegate = DeviceRemoved;
                if (deviceRemovedDelegate != null)
                {
                    deviceRemovedDelegate.Invoke(this, new UpnpDeviceEventArgs { DeviceInfo = info });
                }
            }
        }
    }
}
