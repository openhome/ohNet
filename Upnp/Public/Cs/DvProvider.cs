using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvProvider
    {
        [DllImport("ZappUpnp")]
        static extern void DvProviderPropertiesLock(uint aHandle);
        [DllImport("ZappUpnp")]
        static extern void DvProviderPropertiesUnlock(uint aHandle);
        
        protected uint iHandle;

        protected DvProvider()
        {
        }
        
        protected void PropertiesLock()
        {
            DvProviderPropertiesLock(iHandle);
        }

        protected void PropertiesUnlock()
        {
            DvProviderPropertiesUnlock(iHandle);
        }
    }
}
