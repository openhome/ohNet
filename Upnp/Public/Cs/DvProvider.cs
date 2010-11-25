using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device
{
    /// <summary>
    /// Base class for a service provider.
    /// </summary>
    /// <remarks>Derivations will typically be by service-specific auto-generated code which will
    /// offer 0..n actions and 0..n properties.</remarks>
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
        
        /// <summary>
        /// Lock the provider's properties, blocking publication of updates.
        /// </summary>
        /// <remarks>This is not necessary when updating a single property but is used by providers that
        /// have >1 properties whose values are related.  Without locking, updates to some properties may
        /// be published, leaving related properties in their old (now incompatible) states.
        /// 
        /// Every call to this must be followed by (exactly) one call to PropertiesUnlock().</remarks>
        protected void PropertiesLock()
        {
            DvProviderPropertiesLock(iHandle);
        }

        /// <summary>
        /// Unlock the provider's properties, allowing publication of updates.
        /// </summary>
        /// <remarks>Any pending updates will automatically be scheduled.
        /// 
        /// This must only be called following a call to PropertiesLock().</remarks>
        protected void PropertiesUnlock()
        {
            DvProviderPropertiesUnlock(iHandle);
        }
    }
}
