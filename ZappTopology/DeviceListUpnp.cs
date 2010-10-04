using System;
using System.Collections;
using System.Windows.Threading;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Threading;

namespace Zapp
{
    public class DeviceListUpnp : INotifyCollectionChanged, IEnumerable, IDisposable
    {
        public DeviceListUpnp(String aDomainName, String aServiceType, uint aVersion, Dispatcher aUiDispatcher)
        {
            iList = new SortedList();
            iUiDispatcher = aUiDispatcher;
            iDisposeLock = new Object();
            iRefMutex = new Mutex();
            iCpDeviceListUpnpServiceType = new CpDeviceListUpnpServiceType(aDomainName, aServiceType, aVersion, Added, Removed);
        }

        ~DeviceListUpnp()
        {
            Dispose();
        }

        private void Added(CpDeviceList aCpDeviceList, CpDevice aCpDevice)
        {
            DeviceUpnp addedDevice = new DeviceUpnp(aCpDevice);
            //Use BeginInvoke here to prevent the thread hanging if Invoke is called
            //whilst the Dispatcher's owner is being disposed.
            iUiDispatcher.BeginInvoke(new Action(delegate()
            {
                //Lock(this) so external objects can lock this object and prevent the list being
                //updated when they are enumerating over it.
                lock (this)
                {
                    //refMutex is used here to prevent this method from adding references to devices
                    //after the devicelist has been disposed. In rare cases this can throw unhandled exceptions.
                    iRefMutex.WaitOne();
                    if (iDisposed)
                    {
                        iRefMutex.ReleaseMutex();
                        return;
                    }
                    aCpDevice.AddRef();
                    iRefMutex.ReleaseMutex();

                    try
                    {
                        iList.Add(addedDevice.ToString(), addedDevice);
                    }
                    catch (ArgumentException e)
                    {
                        //If a device is added twice to our list, just ignore it.
                        if (e.Message.StartsWith("Item has already been added"))
                            return;
                        else
                            throw;
                    }
                    int index = iList.IndexOfValue(addedDevice);
                    if (CollectionChanged != null)
                    {
                        CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, addedDevice, index));
                    }
                }
            }), null);
        }

        private void Removed(CpDeviceList aList, CpDevice aCpDevice)
        {
            DeviceUpnp removedDevice = new DeviceUpnp(aCpDevice);
            //Use BeginInvoke here to prevent the thread hanging if Invoke is called
            //whilst the Dispatcher's owner is being disposed.
            iUiDispatcher.BeginInvoke(new Action(delegate()
            {
                //Lock(this) so external objects can lock this object and prevent the list being
                //updated when they are enumerating over it.
                lock (this)
                {
                    aCpDevice.RemoveRef();
                    int index = iList.IndexOfValue(removedDevice);
                    iList.Remove(removedDevice.ToString());
                    if (CollectionChanged != null)
                    {
                        CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, removedDevice, index));
                    }
                }
            }), null);
        }

        /// <summary>
        /// Returns an enumerator for foreach loops. Ensure you lock this object
        /// to prevent the list being updated whilst you are enumerating.
        /// </summary>
        /// <returns>Returns an Enumerator.</returns>
        public IEnumerator GetEnumerator()
        {
            return iList.GetValueList().GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
            lock (iDisposeLock)
            {
                if (!this.iDisposed)
                {
                    iRefMutex.WaitOne();
                    iDisposed = true;
                    iRefMutex.ReleaseMutex();
                    iCpDeviceListUpnpServiceType.Dispose();
                    foreach (DeviceUpnp t in iList.GetValueList())
                        t.BaseDevice.RemoveRef();
                    iList = null;
                }
            }
        }

        public int Count
        {
            get
            {
                return iList.Count;
            }
        }

        private SortedList iList;
        private Dispatcher iUiDispatcher;
        private CpDeviceListUpnpServiceType iCpDeviceListUpnpServiceType;
        public event NotifyCollectionChangedEventHandler CollectionChanged;
        private bool iDisposed = false;
        private Object iDisposeLock;
        private Mutex iRefMutex;
    }

    public class DeviceUpnp
    {
        public DeviceUpnp(CpDevice aDevice)
        {
            iDevice = aDevice;
            iUdn = aDevice.Udn();
        }

        public bool GetAttribute(string aKey, out string aValue)
        {
            return iDevice.GetAttribute(aKey, out aValue);
        }

        public CpDevice BaseDevice
        {
            get { return iDevice; }
        }

        public string Udn
        {
            get
            {
                return iUdn;
            }
        }

        public override string ToString()
        {
            string aValue;
            bool result = iDevice.GetAttribute("Upnp.FriendlyName", out aValue);
            if (!result)
                aValue = "Non-Upnp Device";
            return aValue;
        }

        public override bool Equals(object obj)
        {
            return obj is DeviceUpnp && this.iUdn.Equals(((DeviceUpnp)obj).Udn, StringComparison.OrdinalIgnoreCase);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        private CpDevice iDevice;
        private string iUdn;
    }
}
