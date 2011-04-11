using System;
using System.Runtime.InteropServices;
using Zapp.Core;

namespace Zapp.ControlPoint
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
            if (aControlPointStack == null)
            {
                throw new ArgumentNullException("aControlPointStack");
            }
            iControlPointStack = aControlPointStack;
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


    /// <summary>
    /// List of all UPnP devices on the current subnet
    /// </summary>
    public class CpDeviceListUpnpAll : CpDeviceList
    {
        [DllImport ("ZappUpnp")]
        static extern unsafe IntPtr CpDeviceListCreateUpnpAll(CallbackDevice aAdded, IntPtr aPtrAdded,
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
        public unsafe CpDeviceListUpnpAll(ChangeHandler aAdded, ChangeHandler aRemoved)
        {
            iAdded = aAdded;
            iRemoved = aRemoved;
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpAll(iFnAdded, ptr, iFnRemoved, ptr);
        }
    }

    /// <summary>
    /// List of all root UPnP devices on the current subnet
    /// </summary>
    public class CpDeviceListUpnpRoot : CpDeviceList
    {
        [DllImport ("ZappUpnp")]
        static extern unsafe IntPtr CpDeviceListCreateUpnpRoot(CallbackDevice aAdded, IntPtr aPtrAdded,
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
        public unsafe CpDeviceListUpnpRoot(ChangeHandler aAdded, ChangeHandler aRemoved)
        {
            iAdded = aAdded;
            iRemoved = aRemoved;
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpRoot(iFnAdded, ptr, iFnRemoved, ptr);
        }
    }

    /// <summary>
    /// List of all UPnP devices with a given uuid (udn) on the current subnet
    /// </summary>
    public class CpDeviceListUpnpUuid : CpDeviceList
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern unsafe IntPtr CpDeviceListCreateUpnpUuid(char* aUuid,
                                                             CallbackDevice aAdded, IntPtr aPtrAdded,
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
        public unsafe CpDeviceListUpnpUuid(String aUuid, ChangeHandler aAdded, ChangeHandler aRemoved)
        {
            iAdded = aAdded;
            iRemoved = aRemoved;
            char* uuid = (char*)Marshal.StringToHGlobalAnsi(aUuid).ToPointer();
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpUuid(uuid, iFnAdded, ptr, iFnRemoved, ptr);
            Marshal.FreeHGlobal((IntPtr)uuid);
        }
    }

    /// <summary>
    /// List of all UPnP devices of a given device type on the current subnet
    /// </summary>
    public class CpDeviceListUpnpDeviceType : CpDeviceList
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern unsafe IntPtr CpDeviceListCreateUpnpDeviceType(char* aDomainName, char* aDeviceType, uint aVersion,
                                                                   CallbackDevice aAdded, IntPtr aPtrAdded,
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
        public unsafe CpDeviceListUpnpDeviceType(String aDomainName, String aDeviceType, uint aVersion,
                                                 ChangeHandler aAdded, ChangeHandler aRemoved)
        {
            iAdded = aAdded;
            iRemoved = aRemoved;
            char* domain = (char*)Marshal.StringToHGlobalAnsi(aDomainName).ToPointer();
            char* type = (char*)Marshal.StringToHGlobalAnsi(aDeviceType).ToPointer();
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpDeviceType(domain, type, aVersion, iFnAdded, ptr, iFnRemoved, ptr);
            Marshal.FreeHGlobal((IntPtr)domain);
            Marshal.FreeHGlobal((IntPtr)type);
        }
    }

    /// <summary>
    /// List of all UPnP devices of a given service type on the current subnet
    /// </summary>
    public class CpDeviceListUpnpServiceType : CpDeviceList
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern unsafe IntPtr CpDeviceListCreateUpnpServiceType(char* aDomainName, char* aServiceType, uint aVersion,
                                                                    CallbackDevice aAdded, IntPtr aPtrAdded,
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
        public unsafe CpDeviceListUpnpServiceType(String aDomainName, String aServiceType, uint aVersion,
                                                  ChangeHandler aAdded, ChangeHandler aRemoved)
        {
            iAdded = aAdded;
            iRemoved = aRemoved;
            char* domain = (char*)Marshal.StringToHGlobalAnsi(aDomainName).ToPointer();
            char* type = (char*)Marshal.StringToHGlobalAnsi(aServiceType).ToPointer();
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpServiceType(domain, type, aVersion, iFnAdded, ptr, iFnRemoved, ptr);
            Marshal.FreeHGlobal((IntPtr)domain);
            Marshal.FreeHGlobal((IntPtr)type);
        }
    }
}
