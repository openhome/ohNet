using System;
using System.Runtime.InteropServices;

namespace OpenHome.Net.Core
{
    /// <summary>
    /// A subnet list.
    /// </summary>
	public class SubnetList : IDisposable
	{
        [DllImport("ohNet")]
        static extern IntPtr OhNetSubnetListCreate();
        [DllImport("ohNet")]
        static extern uint OhNetSubnetListSize(IntPtr aList);
        [DllImport("ohNet")]
        static extern IntPtr OhNetSubnetAt(IntPtr aList, uint aIndex);
        [DllImport("ohNet")]
        static extern IntPtr OhNetCurrentSubnetAdapter(IntPtr aCookie);
        [DllImport("ohNet")]
        static extern void OhNetSubnetListDestroy(IntPtr aList);

        private IntPtr iHandle;

        /// <summary>
        /// Create a vector of the available subnets
        /// </summary>
        /// <returns>Subnet list handle.  Caller must later call SubnetListDestroy()</returns>
        public SubnetList()
        {
            iHandle = OhNetSubnetListCreate();
        }

        /// <summary>
        /// Query the number of items in the subnet list
        /// </summary>
        /// <returns>The number of items in the subnet</returns>
        public uint Size()
        {
            return OhNetSubnetListSize(iHandle);
        }

        /// <summary>
        /// Get a handle to a particular subnet from the subnet list
        /// </summary>
        /// <param name="aIndex">Index of the list item to get a handle to (0..SubnetListSize()-1)</param>
        /// <returns>Handle to the subnet</returns>
        public NetworkAdapter SubnetAt(uint aIndex)
        {
            return new NetworkAdapter(OhNetSubnetAt(iHandle, aIndex));
        }

        /// <summary>
        /// Query which subnet is in use.
        /// </summary>
        /// <param name="aCookie">Identifier for NetworkAdapter reference.  Must be used in a later call to NetworkAdapter.RemoveRef()</param>
        /// <returns>Network adapter.  Or null if no subnet is selected or we're running the device stack on all subnets.</returns>
        public static NetworkAdapter CurrentAdapter(string aCookie)
        {
            IntPtr cookie = InteropUtils.StringToHGlobalUtf8(aCookie);
            IntPtr nif = OhNetCurrentSubnetAdapter(cookie);
            if (nif == IntPtr.Zero)
                return null;
            NetworkAdapter n = new NetworkAdapter(nif);
            n.AddManagedCookie(aCookie, cookie);
            return n;
        }

        /// <summary>
        /// Destroy the subnet list
        /// </summary>
        public void Dispose()
        {
            OhNetSubnetListDestroy(iHandle);
        }
	}
}
