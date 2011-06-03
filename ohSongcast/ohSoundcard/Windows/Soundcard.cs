using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Net;
using System.Collections.Generic;

namespace OpenHome.Soundcard
{
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
        string Room { get; }
        string Group { get; }
        string Name { get; }
        EReceiverStatus Status { get; }
    }

    internal class Receiver : IReceiver, IDisposable
    {
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
        static extern void ReceiverAddRef(IntPtr aHandle);
        [DllImport("ohSoundcard.dll")]
        static extern void ReceiverRemoveRef(IntPtr aHandle);

        internal Receiver(IntPtr aReceiver)
        {
            iReceiver = aReceiver;
            ReceiverAddRef(iReceiver);
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
        string iRoom;
        string iGroup;
        string iName;
    }

    public class Soundcard : IDisposable
    {
        private enum EReceiverCallbackType
        {
            eAdded,
            eChanged,
            eRemoved
        }

        private delegate void DelegateReceiverCallback(IntPtr aPtr, EReceiverCallbackType aType, IntPtr aReceiver);

        [DllImport("ohSoundcard.dll")]
        static extern unsafe IntPtr SoundcardCreate(uint aSubnet, uint aChannel, uint aTtl, bool aMulticast, bool aEnabled, uint aPreset, DelegateReceiverCallback aCallback, IntPtr aPtr);
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
        static extern void SoundcardDestroy(IntPtr aHandle);

        public unsafe Soundcard(IPAddress aSubnet, uint aChannel, uint aTtl, bool aMulticast, bool aEnabled, uint aPreset, IReceiverHandler aHandler)
        {
            iHandler = aHandler;
            iReceiverList = new List<Receiver>();
            byte[] subnetBytes = aSubnet.GetAddressBytes();
            uint subnetAddress = BitConverter.ToUInt32(subnetBytes, 0);
            iHandle = SoundcardCreate(subnetAddress, aChannel, aTtl, aMulticast, aEnabled, aPreset, ReceiverCallback, IntPtr.Zero);
        }

        private void ReceiverCallback(IntPtr aPtr, EReceiverCallbackType aType, IntPtr aReceiver)
        {
            switch (aType)
            {
                case EReceiverCallbackType.eAdded:
                    ReceiverAdded(aReceiver);
                    break;
                case EReceiverCallbackType.eChanged:
                    ReceiverChanged(aReceiver);
                    break;
                case EReceiverCallbackType.eRemoved:
                    ReceiverRemoved(aReceiver);
                    break;
            }
        }

        private void ReceiverAdded(IntPtr aReceiver)
        {
            Receiver receiver = new Receiver(aReceiver);
            iReceiverList.Add(receiver);
            iHandler.ReceiverAdded(receiver);
        }

        private void ReceiverChanged(IntPtr aReceiver)
        {
            foreach (Receiver receiver in iReceiverList)
            {
                if (receiver.Owns(aReceiver))
                {
                    iHandler.ReceiverChanged(receiver);
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
                    iHandler.ReceiverRemoved(receiver);
                    receiver.Dispose();
                    iReceiverList.Remove(receiver);
                    return;
                }
            }
        }

        public void SetSubnet(IPAddress aValue)
        {
            byte[] subnetBytes = aValue.GetAddressBytes();
            uint subnetAddress = BitConverter.ToUInt32(subnetBytes, 0);
            SoundcardSetSubnet(iHandle, subnetAddress);
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
            Console.WriteLine("Handle: {0}", iHandle);
            SoundcardSetEnabled(iHandle, aValue);
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

        public void Dispose()
        {
            SoundcardDestroy(iHandle);
        }

        private IReceiverHandler iHandler;
        private IntPtr iHandle;
        private List<Receiver> iReceiverList;
    }
} // namespace OpenHome.Soundcard