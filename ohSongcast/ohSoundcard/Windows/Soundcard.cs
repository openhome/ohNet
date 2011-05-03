using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Net;

namespace ohSoundcard
{
    public class Soundcard : IDisposable
    {
        [DllImport("ohSoundcard.dll")]
        static extern unsafe IntPtr SoundcardCreate(char* aName, uint aChannel, uint aInterface, uint aTtl, bool aMulticast, bool aEnabled);
        [DllImport("ohSoundcard.dll")]
        static extern unsafe void SoundcardSetName(IntPtr aHandle, char* aName);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetChannel(IntPtr aHandle, uint aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetTtl(IntPtr aHandle, uint aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetMulticast(IntPtr aHandle, bool aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardSetEnabled(IntPtr aHandle, bool aValue);
        [DllImport("ohSoundcard.dll")]
        static extern unsafe void SoundcardSetTrack(IntPtr aHandle, char* aMetadata, long aSamplesTotal, long aSampleStart);
        [DllImport("ohSoundcard.dll")]
        static extern unsafe void SoundcardSetMetatext(IntPtr aHandle, char* aValue);
        [DllImport("ohSoundcard.dll")]
        static extern void SoundcardDestroy(IntPtr aHandle);

        public unsafe Soundcard(string aName, uint aChannel, IPAddress aInterface, uint aTtl, bool aMulticast, bool aEnabled)
        {
            IntPtr name = Marshal.StringToHGlobalAnsi(aName);
            byte[] interfaceBytes = aInterface.GetAddressBytes();
            uint interfaceAddress = BitConverter.ToUInt32(interfaceBytes, 0);
            iHandle = SoundcardCreate((char*)name, aChannel, interfaceAddress, aTtl, aMulticast, aEnabled);
            Console.WriteLine("Handle: {0}", iHandle);
            Marshal.FreeHGlobal(name);
        }

        public unsafe void SetName(string aName)
        {
            IntPtr name = Marshal.StringToHGlobalAnsi(aName);
            SoundcardSetName(iHandle, (char*)name);
            Marshal.FreeHGlobal(name);
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

        public unsafe void SetTrack(IntPtr aHandle, string aMetadata, long aSamplesTotal, long aSampleStart)
        {
            IntPtr metadata = Marshal.StringToHGlobalAnsi(aMetadata);
            SoundcardSetTrack(iHandle, (char*)metadata, aSamplesTotal, aSampleStart);
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

        protected IntPtr iHandle;
    }
} // namespace ohSoundcard