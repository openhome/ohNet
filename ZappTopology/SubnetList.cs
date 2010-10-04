using System;
using System.Net;
using System.Collections.Generic;
using System.Collections;
using System.Collections.Specialized;
using System.Runtime.InteropServices;
using System.Windows.Threading;
using System.Linq;
using System.Text;

namespace Zapp
{
    public class SubnetList : INotifyCollectionChanged, IEnumerable, IDisposable
    {
        public SubnetList(InitParams aParams, Dispatcher aUiDispatcher, Library aLibrary)
        {
            iLibrary = aLibrary;
            iUiDispatcher = aUiDispatcher;
            aParams.SetSubnetChangedListener(SubnetListChanged);
            CreateSubnetList();
        }

        private void CreateSubnetList()
        {
            iListHandle = iLibrary.SubnetListCreate();
            uint size = iLibrary.SubnetListSize(iListHandle);
            iSubnetList = new List<Subnet>();
            for (uint i = 0; i < size; i++)
            {
                iSubnetList.Add(new Subnet(iLibrary.SubnetAt(iListHandle, i), iLibrary));
            }
        }

        private void SubnetListChanged(IntPtr aPtr)
        {
            lock (iSubnetList)
            {
                iLibrary.SubnetListDestroy(iListHandle);
                iUiDispatcher.Invoke(new Action(delegate()
                {
                    CreateSubnetList();
                    if (CollectionChanged != null)
                    {
                        CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Reset));
                    }
                }), null);
            }
        }

        public IEnumerator GetEnumerator()
        {
            return iSubnetList.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (!this.iDisposed)
            {
                iLibrary.SubnetListDestroy(iListHandle);
                iDisposed = true;
            }
        }

        public int length
        {
            get
            {
                return iSubnetList.Count;
            }
        }

        private uint iListHandle;
        private List<Subnet> iSubnetList;
        private Dispatcher iUiDispatcher;
        private bool iDisposed = false;
        private Library iLibrary;

        public event NotifyCollectionChangedEventHandler CollectionChanged;
    }

    public class Subnet
    {
        public Subnet(uint aNif, Library aLibrary)
        {
            iHandle = aNif;
            iIPAddress = new IPAddress(aLibrary.NetworkInterfaceAddress(iHandle));
            iSubnet = new IPAddress(aLibrary.NetworkInterfaceSubnet(iHandle));
            IntPtr iNamePtr = aLibrary.NetworkInterfaceName(iHandle);
            iName = Marshal.PtrToStringAnsi(iNamePtr);
            //This seems to work, but I don't understand why.
            //However, I decided a likely fix was better than a certain memory leak.
            Marshal.FreeBSTR(iNamePtr); 
        }

        public IPAddress IPAddress
        {
            get
            {
                return IPAddress.Parse(iIPAddress.ToString());
            }
        }

        public IPAddress SubnetAddress
        {
            get
            {
                return IPAddress.Parse(iIPAddress.ToString());
            }
        }

        public string Name
        {
            get
            {
                return iName;
            }
        }

        public uint Handle
        {
            get
            {
                return iHandle;
            }
        }

        public override string ToString()
        {
            return iName + " (" + iIPAddress.ToString() + ")";
        }

        private IPAddress iIPAddress;
        private IPAddress iSubnet;
        private string iName;
        private uint iHandle;
    }
}
