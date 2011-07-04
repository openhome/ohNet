using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Net;
using System.Collections.Generic;

namespace OpenHome.Soundcard
{
    public class SoundcardError : Exception
    {
        internal SoundcardError()
            : base("ohSoundcard audio driver not installed")
        {
        }
    }

    public interface IReceiverHandler
    {
        void ReceiverAdded(IReceiver aReceiver);
        void ReceiverChanged(IReceiver aReceiver);
        void ReceiverRemoved(IReceiver aReceiver);
    }

    public enum EReceiverStatus
    {
        eDisconnected,
        eConnecting,
        eConnected
    }

    public interface IReceiver
    {
        void Play();
        void Stop();
        void Standby();
        string Udn { get; }
        string Room { get; }
        string Group { get; }
        string Name { get; }
        EReceiverStatus Status { get; }
    }

    internal class Receiver : IReceiver, IDisposable
    {
        [DllImport("ohSoundcard.dll")]
        static extern IntPtr ReceiverUdn(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern IntPtr ReceiverRoom(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern IntPtr ReceiverGroup(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern IntPtr ReceiverName(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern uint ReceiverStatus(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void ReceiverPlay(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void ReceiverStop(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void ReceiverStandby(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void ReceiverAddRef(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void ReceiverRemoveRef(IntPtr aHandle);

        internal Receiver(IntPtr aReceiver)
        {
            iReceiver = aReceiver;
            ReceiverAddRef(iReceiver);
            iUdn = Marshal.PtrToStringAnsi(ReceiverUdn(iReceiver));
            iRoom = Marshal.PtrToStringAnsi(ReceiverRoom(iReceiver));
            iGroup = Marshal.PtrToStringAnsi(ReceiverGroup(iReceiver));
            iName = Marshal.PtrToStringAnsi(ReceiverName(iReceiver));
        }

        internal bool Owns(IntPtr aReceiver)
        {
            return (iReceiver == aReceiver);
        }

        public void Dispose()
        {
            ReceiverRemoveRef(iReceiver);
        }

        public void Play()
        {
            ReceiverPlay(iReceiver);
        }

        public void Stop()
        {
            ReceiverStop(iReceiver);
        }

        public void Standby()
        {
            ReceiverStandby(iReceiver);
        }

        public string Udn
        {
            get
            {
                return (iUdn);
            }
        }

        public string Room
        {
            get
            {
                return (iRoom);
            }
        }

        public string Group
        {
            get
            {
                return (iGroup);
            }
        }

        public string Name
        {
            get
            {
                return (iName);
            }
        }

        public EReceiverStatus Status
        {
            get
            {
                return ((EReceiverStatus)ReceiverStatus(iReceiver));
            }
        }

        IntPtr iReceiver;
        string iUdn;
        string iRoom;
        string iGroup;
        string iName;
    }

    public interface ISubnetHandler
    {
        void SubnetAdded(ISubnet aSubnet);
        void SubnetChanged(ISubnet aSubnet);
        void SubnetRemoved(ISubnet aSubnet);
    }

    public interface ISubnet
    {
        uint Address { get; }
        string AdapterName { get; }
    }

    internal class Subnet : ISubnet, IDisposable
    {
        [DllImport("ohSoundcard.dll")]
        static extern IntPtr SubnetAddress(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern IntPtr SubnetAdapterName(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void SubnetAddRef(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void SubnetRemoveRef(IntPtr aHandle);

        public Subnet(IntPtr aSubnet)
        {
            iSubnet = aSubnet;
            iAddress = (uint)SubnetAddress(iSubnet);
            iAdapterName = Marshal.PtrToStringAnsi(SubnetAdapterName(iSubnet));
        }

        internal bool Owns(IntPtr aSubnet)
        {
            return (iSubnet == aSubnet);
        }

        public uint Address
        {
            get
            {
                return (iAddress);
            }
        }

        public string AdapterName
        {
            get
            {
                return (iAdapterName);
            }
        }

        public void Dispose()
        {
            SubnetRemoveRef(iSubnet);
        }

        IntPtr iSubnet;
        uint iAddress;
        string iAdapterName;
    }

    public class Soundcard : IDisposable
    {
        private enum ECallbackType
        {
            eAdded,
            eChanged,
            eRemoved
        }

        private delegate void DelegateReceiverCallback(IntPtr aPtr, ECallbackType aType, IntPtr aReceiver);
        private delegate void DelegateSubnetCallback(IntPtr aPtr, ECallbackType aType, IntPtr aSubnet);

        [DllImport("ohSoundcard.dll")]
        static extern unsafe IntPtr SoundcardCreate(uint aSubnet, uint aChannel, uint aTtl, bool aMulticast, bool aEnabled, uint aPreset, DelegateReceiverCallback aReceiverCallback, IntPtr aReceiverPtr, DelegateSubnetCallback aSubnetCallback, IntPtr aSubnetPtr);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetSubnet(IntPtr aHandle, uint aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetChannel(IntPtr aHandle, uint aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetTtl(IntPtr aHandle, uint aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetMulticast(IntPtr aHandle, bool aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetEnabled(IntPtr aHandle, bool aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetPreset(IntPtr aHandle, uint aValue);
        [DllImport("ohSoundcard.dll")]
        static extern unsafe void SoundcardSetTrack(IntPtr aHandle, char* aUri, char* aMetadata, long aSamplesTotal, long aSampleStart);
        [DllImport("ohSoundcard.dll")]
        static extern unsafe void SoundcardSetMetatext(IntPtr aHandle, char* aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardRefreshReceivers(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardDestroy(IntPtr aHandle);

        public unsafe Soundcard(uint aSubnet, uint aChannel, uint aTtl, bool aMulticast, bool aEnabled, uint aPreset, IReceiverHandler aReceiverHandler, ISubnetHandler aSubnetHandler)
        {
            iReceiverHandler = aReceiverHandler;
            iSubnetHandler = aSubnetHandler;
            iReceiverCallback = new DelegateReceiverCallback(ReceiverCallback);
            iSubnetCallback = new DelegateSubnetCallback(SubnetCallback);
            iReceiverList = new List<Receiver>();
            iSubnetList = new List<Subnet>();
            iHandle = SoundcardCreate(aSubnet, aChannel, aTtl, aMulticast, aEnabled, aPreset, iReceiverCallback, IntPtr.Zero, iSubnetCallback, IntPtr.Zero);

            if (iHandle == IntPtr.Zero)
            {
                throw (new SoundcardError());
            }
        }

        private void ReceiverCallback(IntPtr aPtr, ECallbackType aType, IntPtr aReceiver)
        {
            switch (aType)
            {
                case ECallbackType.eAdded:
                    ReceiverAdded(aReceiver);
                    break;
                case ECallbackType.eChanged:
                    ReceiverChanged(aReceiver);
                    break;
                case ECallbackType.eRemoved:
                    ReceiverRemoved(aReceiver);
                    break;
            }
        }

        private void ReceiverAdded(IntPtr aReceiver)
        {
            Receiver receiver = new Receiver(aReceiver);
            iReceiverList.Add(receiver);
            iReceiverHandler.ReceiverAdded(receiver);
        }

        private void ReceiverChanged(IntPtr aReceiver)
        {
            foreach (Receiver receiver in iReceiverList)
            {
                if (receiver.Owns(aReceiver))
                {
                    iReceiverHandler.ReceiverChanged(receiver);
                    return;
                }
            }
        }

        private void ReceiverRemoved(IntPtr aReceiver)
        {
            foreach (Receiver receiver in iReceiverList)
            {
                if (receiver.Owns(aReceiver))
                {
                    iReceiverHandler.ReceiverRemoved(receiver);
                    receiver.Dispose();
                    iReceiverList.Remove(receiver);
                    return;
                }
            }
        }

        private void SubnetCallback(IntPtr aPtr, ECallbackType aType, IntPtr aSubnet)
        {
            switch (aType)
            {
                case ECallbackType.eAdded:
                    SubnetAdded(aSubnet);
                    break;
                case ECallbackType.eChanged:
                    SubnetChanged(aSubnet);
                    break;
                case ECallbackType.eRemoved:
                    SubnetRemoved(aSubnet);
                    break;
            }
        }

        private void SubnetAdded(IntPtr aSubnet)
        {
            Subnet subnet = new Subnet(aSubnet);
            iSubnetList.Add(subnet);
            iSubnetHandler.SubnetAdded(subnet);
        }

        private void SubnetChanged(IntPtr aSubnet)
        {
            foreach (Subnet subnet in iSubnetList)
            {
                if (subnet.Owns(aSubnet))
                {
                    iSubnetHandler.SubnetChanged(subnet);
                    return;
                }
            }
        }

        private void SubnetRemoved(IntPtr aSubnet)
        {
            foreach (Subnet subnet in iSubnetList)
            {
                if (subnet.Owns(aSubnet))
                {
                    iSubnetHandler.SubnetRemoved(subnet);
                    subnet.Dispose();
                    iSubnetList.Remove(subnet);
                    return;
                }
            }
        }

        public void SetSubnet(uint aValue)
        {
            SoundcardSetSubnet(iHandle, aValue);
        }

        public void SetChannel(uint aValue)
        {
            SoundcardSetChannel(iHandle, aValue);
        }

        public void SetTtl(uint aValue)
        {
            SoundcardSetTtl(iHandle, aValue);
        }

        public void SetMulticast(bool aValue)
        {
            SoundcardSetMulticast(iHandle, aValue);
        }

        public void SetEnabled(bool aValue)
        {
            SoundcardSetEnabled(iHandle, aValue);
        }

        public void SetPreset(uint aValue)
        {
            SoundcardSetPreset(iHandle, aValue);
        }

        public unsafe void SetTrack(IntPtr aHandle, string aUri, string aMetadata, long aSamplesTotal, long aSampleStart)
        {
            IntPtr uri = Marshal.StringToHGlobalAnsi(aUri);
            IntPtr metadata = Marshal.StringToHGlobalAnsi(aMetadata);
            SoundcardSetTrack(iHandle, (char*)uri, (char*)metadata, aSamplesTotal, aSampleStart);
            Marshal.FreeHGlobal(uri);
            Marshal.FreeHGlobal(metadata);
        }

        public unsafe void SetMetatext(IntPtr aHandle, string aValue)
        {
            IntPtr value = Marshal.StringToHGlobalAnsi(aValue);
            SoundcardSetMetatext(iHandle, (char*)value);
            Marshal.FreeHGlobal(value);
        }

        public void RefreshReceivers()
        {
            SoundcardRefreshReceivers(iHandle);
        }

        public void Dispose()
        {
            SoundcardDestroy(iHandle);
        }

        private IReceiverHandler iReceiverHandler;
        private ISubnetHandler iSubnetHandler;
        private IntPtr iHandle;
        private List<Receiver> iReceiverList;
        private List<Subnet> iSubnetList;
        private DelegateReceiverCallback iReceiverCallback;
        private DelegateSubnetCallback iSubnetCallback;
    }
} // namespace OpenHome.Soundcard