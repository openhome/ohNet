using System;
using System.Runtime.InteropServices;

namespace Zapp
{
    public class CpDeviceListUpnpAll : CpDeviceList
    {
        [DllImport ("ZappUpnp")]
        static extern unsafe uint CpDeviceListCreateUpnpAll(CallbackDevice aAdded, IntPtr aPtrAdded,
                                                            CallbackDevice aRemoved, IntPtr aPtrRemoved);

        public unsafe CpDeviceListUpnpAll(ChangeHandler aAdded, ChangeHandler aRemoved)
        {
            iAdded = aAdded;
            iRemoved = aRemoved;
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpAll(iFnAdded, ptr, iFnRemoved, ptr);
        }
    }

    public class CpDeviceListUpnpRoot : CpDeviceList
    {
        [DllImport ("ZappUpnp")]
        static extern unsafe uint CpDeviceListCreateUpnpRoot(CallbackDevice aAdded, IntPtr aPtrAdded,
                                                             CallbackDevice aRemoved, IntPtr aPtrRemoved);

        public unsafe CpDeviceListUpnpRoot(ChangeHandler aAdded, ChangeHandler aRemoved)
        {
            iAdded = aAdded;
            iRemoved = aRemoved;
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            iHandle = CpDeviceListCreateUpnpRoot(iFnAdded, ptr, iFnRemoved, ptr);
        }
    }

    public class CpDeviceListUpnpUuid : CpDeviceList
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern unsafe uint CpDeviceListCreateUpnpUuid(char* aUuid,
                                                             CallbackDevice aAdded, IntPtr aPtrAdded,
                                                             CallbackDevice aRemoved, IntPtr aPtrRemoved);

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

    public class CpDeviceListUpnpDeviceType : CpDeviceList
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern unsafe uint CpDeviceListCreateUpnpDeviceType(char* aDomainName, char* aDeviceType, uint aVersion,
                                                                   CallbackDevice aAdded, IntPtr aPtrAdded,
                                                                   CallbackDevice aRemoved, IntPtr aPtrRemoved);

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

    public class CpDeviceListUpnpServiceType : CpDeviceList
    {
        [DllImport ("ZappUpnp", CharSet = CharSet.Ansi)]
        static extern unsafe uint CpDeviceListCreateUpnpServiceType(char* aDomainName, char* aServiceType, uint aVersion,
                                                                    CallbackDevice aAdded, IntPtr aPtrAdded,
                                                                    CallbackDevice aRemoved, IntPtr aPtrRemoved);

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
