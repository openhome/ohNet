using System;
using System.Runtime.InteropServices;
using OpenHome.Net.Core;

namespace OpenHome.Net.ControlPoint
{
    /// <summary>
    /// Factory interface for creating any sort of Upnp device list.
    /// </summary>
    public interface ICpUpnpDeviceListFactory
    {
        /// <summary>
        /// Create a device list that detects all UPnP devices.
        /// </summary>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        ICpDeviceList CreateListAll(
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved);

        /// <summary>
        /// Create a device list that detects all UPnP root devices.
        /// </summary>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        ICpDeviceList CreateListRoot(
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved);

        /// <summary>
        /// Create a device list that detects a UPnP devices with a specific Udn.
        /// </summary>
        /// <param name="aUuid">Unique identifier for the target device.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        ICpDeviceList CreateListUuid(
            string aUuid,
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved);

        /// <summary>
        /// Create a device list that detects UPnP devices of a specific type.
        /// </summary>
        /// <param name="aDomain">Vendor domain for the target device.</param>
        /// <param name="aDeviceType">Name of the target device.</param>
        /// <param name="aVersion">Version number for the target device.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        ICpDeviceList CreateListDeviceType(
            string aDomain,
            string aDeviceType,
            uint aVersion,
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved);

        /// <summary>
        /// Create a device list that detects UPnP devices bearing a specific type of service.
        /// </summary>
        /// <param name="aDomain">Vendor domain for the target service (e.g. upnp.org).</param>
        /// <param name="aServiceType">Name of the target service.</param>
        /// <param name="aVersion">Version number for the target service.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        ICpDeviceList CreateListServiceType(
            string aDomain,
            string aServiceType,
            uint aVersion,
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved);
    }

    /// <summary>
    /// Default implementation of device list factory interface.
    /// </summary>
    public class CpUpnpDeviceListFactory : ICpUpnpDeviceListFactory
    {
        private ControlPointStack iControlPointStack;

        public CpUpnpDeviceListFactory(
            ControlPointStack aControlPointStack)
        {
            iControlPointStack = aControlPointStack;
            if (iControlPointStack == null)
            {
                throw new ArgumentNullException("aControlPointStack");
            }
        }

        /// <summary>
        /// Create a device list that detects all UPnP devices.
        /// </summary>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public ICpDeviceList CreateListAll(
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved)
        {
            return new CpDeviceListUpnpAll(aAdded, aRemoved);
        }

        /// <summary>
        /// Create a device list that detects all UPnP root devices.
        /// </summary>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public ICpDeviceList CreateListRoot(
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved)
        {
            return new CpDeviceListUpnpRoot(aAdded, aRemoved);
        }

        /// <summary>
        /// Create a device list that detects a UPnP devices with a specific Udn.
        /// </summary>
        /// <param name="aUuid">Unique identifier for the target device.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public ICpDeviceList CreateListUuid(
            string aUuid,
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved)
        {
            return new CpDeviceListUpnpUuid(aUuid, aAdded, aRemoved);
        }

        /// <summary>
        /// Create a device list that detects UPnP devices of a specific type.
        /// </summary>
        /// <param name="aDomain">Vendor domain for the target device.</param>
        /// <param name="aDeviceType">Name of the target device.</param>
        /// <param name="aVersion">Version number for the target device.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public ICpDeviceList CreateListDeviceType(
            string aDomain,
            string aDeviceType,
            uint aVersion,
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved)
        {
            return new CpDeviceListUpnpDeviceType(aDomain, aDeviceType, aVersion, aAdded, aRemoved);
        }

        /// <summary>
        /// Create a device list that detects UPnP devices bearing a specific type of service.
        /// </summary>
        /// <param name="aDomain">Vendor domain for the target service (e.g. upnp.org).</param>
        /// <param name="aServiceType">Name of the target service.</param>
        /// <param name="aVersion">Version number for the target service.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public ICpDeviceList CreateListServiceType(
            string aDomain,
            string aServiceType,
            uint aVersion,
            CpDeviceList.ChangeHandler aAdded,
            CpDeviceList.ChangeHandler aRemoved)
        {
            return new CpDeviceListUpnpServiceType(aDomain, aServiceType, aVersion, aAdded, aRemoved);
        }
    }

    public class CpDeviceListUpnp : CpDeviceList
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpDeviceListUpnpTryAdd(IntPtr aListHandlem, IntPtr aLocation);

        public void TryAdd(string aLocation)
       {
            IntPtr location = InteropUtils.StringToHGlobalUtf8(aLocation);
            CpDeviceListUpnpTryAdd(iHandle, location);
            Marshal.FreeHGlobal(location);
        }

        protected CpDeviceListUpnp(ChangeHandler aAdded, ChangeHandler aRemoved)
            : base(aAdded, aRemoved)
        {
        }
    }


    /// <summary>
    /// List of all UPnP devices on the current subnet
    /// </summary>
    public class CpDeviceListUpnpAll : CpDeviceListUpnp
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr CpDeviceListCreateUpnpAll(CallbackDevice aAdded, IntPtr aPtrAdded,
                                                       CallbackDevice aRemoved, IntPtr aPtrRemoved);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public CpDeviceListUpnpAll(ChangeHandler aAdded, ChangeHandler aRemoved)
            : base(aAdded, aRemoved)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpAll(iFnAdded, ptr, iFnRemoved, ptr);
        }
    }

    /// <summary>
    /// List of all root UPnP devices on the current subnet
    /// </summary>
    public class CpDeviceListUpnpRoot : CpDeviceListUpnp
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr CpDeviceListCreateUpnpRoot(CallbackDevice aAdded, IntPtr aPtrAdded,
                                                        CallbackDevice aRemoved, IntPtr aPtrRemoved);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public CpDeviceListUpnpRoot(ChangeHandler aAdded, ChangeHandler aRemoved)
            : base(aAdded, aRemoved)
        {
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpRoot(iFnAdded, ptr, iFnRemoved, ptr);
        }
    }

    /// <summary>
    /// List of all UPnP devices with a given uuid (udn) on the current subnet
    /// </summary>
    public class CpDeviceListUpnpUuid : CpDeviceListUpnp
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr CpDeviceListCreateUpnpUuid(IntPtr aUuid,
                                                        CallbackDevice aAdded, IntPtr aPtrAdded,
                                                        CallbackDevice aRemoved, IntPtr aPtrRemoved);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aUuid">Unique identifier for the target device.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public CpDeviceListUpnpUuid(String aUuid, ChangeHandler aAdded, ChangeHandler aRemoved)
            : base(aAdded, aRemoved)
        {
            IntPtr uuid = InteropUtils.StringToHGlobalUtf8(aUuid);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpUuid(uuid, iFnAdded, ptr, iFnRemoved, ptr);
            Marshal.FreeHGlobal(uuid);
        }
    }

    /// <summary>
    /// List of all UPnP devices of a given device type on the current subnet
    /// </summary>
    public class CpDeviceListUpnpDeviceType : CpDeviceListUpnp
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr CpDeviceListCreateUpnpDeviceType(IntPtr aDomainName, IntPtr aDeviceType, uint aVersion,
                                                              CallbackDevice aAdded, IntPtr aPtrAdded,
                                                              CallbackDevice aRemoved, IntPtr aPtrRemoved);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDomainName">Vendor domain for the target device.</param>
        /// <param name="aDeviceType">Name of the target device.</param>
        /// <param name="aVersion">Version number for the target device.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public CpDeviceListUpnpDeviceType(String aDomainName, String aDeviceType, uint aVersion,
                                          ChangeHandler aAdded, ChangeHandler aRemoved)
            : base(aAdded, aRemoved)
        {
            IntPtr domain = InteropUtils.StringToHGlobalUtf8(aDomainName);
            IntPtr type = InteropUtils.StringToHGlobalUtf8(aDeviceType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpDeviceType(domain, type, aVersion, iFnAdded, ptr, iFnRemoved, ptr);
            Marshal.FreeHGlobal(domain);
            Marshal.FreeHGlobal(type);
        }
    }

    /// <summary>
    /// List of all UPnP devices of a given service type on the current subnet
    /// </summary>
    public class CpDeviceListUpnpServiceType : CpDeviceListUpnp
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern IntPtr CpDeviceListCreateUpnpServiceType(IntPtr aDomainName, IntPtr aServiceType, uint aVersion,
                                                               CallbackDevice aAdded, IntPtr aPtrAdded,
                                                               CallbackDevice aRemoved, IntPtr aPtrRemoved);

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDomainName">Vendor domain for the target service (e.g. upnp.org).</param>
        /// <param name="aServiceType">Name of the target service.</param>
        /// <param name="aVersion">Version number for the target service.</param>
        /// <param name="aAdded">Delegate which will be run when a new device is detected.
        /// Clients who are interested this new device should call AddRef() on it and add it to some local collection.
        /// This callback will never be run for a device that is already in the list.</param>
        /// <param name="aRemoved">Delegatewhich will be run when a device is removed from the network.
        /// Clients who had previously stored a reference to the device in their aAdded callback should call RemoveRef()
        /// and remove the device from their local collection.
        /// Clients who had not previously claimed a reference to a device must not call ReleaseRef().</param>
        public CpDeviceListUpnpServiceType(String aDomainName, String aServiceType, uint aVersion,
                                           ChangeHandler aAdded, ChangeHandler aRemoved)
            : base(aAdded, aRemoved)
        {
            IntPtr domain = InteropUtils.StringToHGlobalUtf8(aDomainName);
            IntPtr type = InteropUtils.StringToHGlobalUtf8(aServiceType);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpServiceType(domain, type, aVersion, iFnAdded, ptr, iFnRemoved, ptr);
            Marshal.FreeHGlobal(domain);
            Marshal.FreeHGlobal(type);
        }
    }
}
