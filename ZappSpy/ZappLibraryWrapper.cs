using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ZappSpy
{
    public class ZappLibraryWrapper : IDisposable
    {
        private Zapp.Core.Library iLibrary;
        public ZappLibraryWrapper()
        {
            Zapp.Core.InitParams initialisationParams = new Zapp.Core.InitParams
            {
                // Nothing to set, yet!
            };
            iLibrary = new Zapp.Core.Library();
            iLibrary.Initialise(ref initialisationParams);
            iLibrary.StartCp();
        }

        public Zapp.ControlPoint.CpDeviceList GetUpnpRootDeviceList(
            Zapp.ControlPoint.CpDeviceList.ChangeHandler aAdded,
            Zapp.ControlPoint.CpDeviceList.ChangeHandler aRemoved)
        {
            return new Zapp.ControlPoint.CpDeviceListUpnpRoot(aAdded, aRemoved);
        }

        public void Dispose()
        {
            iLibrary.Close();
        }
    }
}
