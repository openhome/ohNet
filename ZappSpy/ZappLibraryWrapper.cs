using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ZappSpy
{
    public class ZappLibraryWrapper : IDisposable
    {
        private Zapp.Library iLibrary;
        public ZappLibraryWrapper()
        {
            Zapp.InitParams initialisationParams = new Zapp.InitParams
            {
                // Nothing to set, yet!
            };
            iLibrary = new Zapp.Library();
            iLibrary.Initialise(ref initialisationParams);
            iLibrary.StartCp();
        }

        public Zapp.CpDeviceList GetUpnpRootDeviceList(
            Zapp.CpDeviceList.ChangeHandler aAdded,
            Zapp.CpDeviceList.ChangeHandler aRemoved)
        {
            return new Zapp.CpDeviceListUpnpRoot(aAdded, aRemoved);
        }

        public void Dispose()
        {
            iLibrary.Close();
        }
    }
}
