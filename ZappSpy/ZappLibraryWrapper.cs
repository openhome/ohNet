using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ZappSpy
{
    public class OhNetLibraryWrapper : IDisposable
    {
        private OpenHome.Net.Core.Library iLibrary;
        public OhNetLibraryWrapper()
        {
            OpenHome.Net.Core.InitParams initialisationParams = new OpenHome.Net.Core.InitParams
            {
                // Nothing to set, yet!
            };
            iLibrary = new OpenHome.Net.Core.Library();
            iLibrary.Initialise(initialisationParams);
            iLibrary.StartCp();
        }

        public OpenHome.Net.ControlPoint.CpDeviceList GetUpnpRootDeviceList(
            OpenHome.Net.ControlPoint.CpDeviceList.ChangeHandler aAdded,
            OpenHome.Net.ControlPoint.CpDeviceList.ChangeHandler aRemoved)
        {
            return new OpenHome.Net.ControlPoint.CpDeviceListUpnpRoot(aAdded, aRemoved);
        }

        public void Dispose()
        {
            iLibrary.Close();
        }
    }
}
