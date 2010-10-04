using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;

namespace Zapp
{
    class Program
    {
        public static void Main(string[] args)
        {
            // !!!! add OptionParser class rather than relying on the user guessing that the first arg
            // is an int 1..3 and the second is the path of a folder that'll serve a test UI
            InitParams initParams = new InitParams();
            Library lib = new Library();
            lib.Initialise(ref initParams);
            lib.StartDv();
            Console.Write("TestDvLights - starting\n");
            DeviceLights device = new DeviceLights(Convert.ToInt32(args[0]), args[1]);
            Semaphore blocker = new Semaphore(0, 1);
            blocker.WaitOne(60 * 60 * 1000); // make the device available for 1 hour then assume we've been forgotten about and exit
            device.Dispose();
            Console.Write("TestDvLights - exiting\n");
            lib.Close();
        }
    }

    class Light
    {
        private string iRoom;
        private string iName;
        private uint iPosX;
        private uint iPosY;
        private uint iPosZ;
        private uint iColor;

        public Light(string aRoom, string aName, uint aPosX, uint aPosY, uint aPosZ, uint aColor)
        {
            iRoom = aRoom;
            iName = aName;
            iPosX = aPosX;
            iPosY = aPosY;
            iPosZ = aPosZ;
            iColor = aColor;
        }
        public string Room
        {
            get { return iRoom; }
        }
        public string Name
        {
            get { return iName; }
        }
        public uint PosX
        {
            get { return iPosX; }
        }
        public uint PosY
        {
            get { return iPosY; }
        }
        public uint PosZ
        {
            get { return iPosZ; }
        }
        public uint Color
        {
            get { return iColor; }
            set { iColor = value; }
        }
    }

    class ServiceLights : DvServiceZappOrgTestLights1
    {
        public List<Light> iLights;

        public ServiceLights(DvDevice aDevice, int aMode)
            : base(aDevice)
        {
            EnableActionGetCount();
            EnableActionGetRoom();
            EnableActionGetName();
            EnableActionGetPosition();
            EnableActionSetColor();
            EnableActionGetColor();
            EnableActionGetColorComponents();

            iLights = new List<Light>();

            switch (aMode)
            {
                case 1:
                    InitMode1();
                    break;
                case 2:
                    InitMode2();
                    break;
                case 3:
                    InitMode3();
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
        }

        protected override void GetCount(uint aVersion, out uint aCount)
        {
            aCount = (uint)iLights.Count;
        }

        protected override void GetRoom(uint aVersion, uint aIndex, out string aRoomName)
        {
            aRoomName = Light(aIndex).Room;
        }

        protected override void GetName(uint aVersion, uint aIndex, out string aFriendlyName)
        {
            aFriendlyName = Light(aIndex).Name;
        }

        protected override void GetPosition(uint aVersion, uint aIndex, out uint aX, out uint aY, out uint aZ)
        {
            Light light = Light(aIndex);
            aX = light.PosX;
            aY = light.PosY;
            aZ = light.PosZ;
        }

        protected override void SetColor(uint aVersion, uint aIndex, uint aColor)
        {
            Light(aIndex).Color = aColor;
        }

        protected override void GetColor(uint aVersion, uint aIndex, out uint aColor)
        {
            aColor = Light(aIndex).Color;
        }

        protected override void GetColorComponents(uint aVersion, uint aColor, out uint aBrightness, out uint aRed, out uint aGreen, out uint aBlue)
        {
            aBrightness = aColor>>24;
            aRed = aColor>>16;
            aGreen = aColor>>8;
            aBlue = aColor&0xff;
        }

        private Light Light(uint aIndex)
        {
            return iLights[(int)(aIndex)];
        }

        private void InitMode1()
        {
            iLights.Add(new Light("Lounge", "Ceiling1", 150, 180, 200, MakeColor(255, 255, 255, 255)));
            iLights.Add(new Light("Lounge", "Ceiling2", 650, 180, 200, MakeColor(128, 255, 255, 255)));
            iLights.Add(new Light("Lounge", "Reading", 400, 30, 135, MakeColor(0, 255, 255, 255)));
        }

        private void InitMode2()
        {
            iLights.Add(new Light("Lounge", "Ceiling1", 150, 180, 200, MakeColor(255, 255, 255, 255)));
            iLights.Add(new Light("Lounge", "Ceiling2", 650, 180, 200, MakeColor(128, 255, 255, 255)));
            iLights.Add(new Light("Lounge", "Reading", 400, 30, 135, MakeColor(0, 255, 255, 255)));
            iLights.Add(new Light("Kitchen", "Kitchen", 160, 120, 200, MakeColor(0, 255, 255, 255)));
            iLights.Add(new Light("Hall", "Hall", 120, 60, 200, MakeColor(0, 255, 255, 255)));
        }

        private void InitMode3()
        {
            iLights.Add(new Light("Lounge", "Ceiling1", 150, 180, 200, MakeColor(255, 255, 255, 255)));
            iLights.Add(new Light("Lounge", "Ceiling2", 650, 180, 200, MakeColor(128, 255, 255, 255)));
            iLights.Add(new Light("Lounge", "Reading", 400, 30, 135, MakeColor(0, 255, 255, 255)));
            iLights.Add(new Light("Kitchen", "Kitchen", 160, 120, 200, MakeColor(0, 255, 255, 255)));
            iLights.Add(new Light("Hall", "Hall", 120, 60, 200, MakeColor(0, 255, 255, 255)));
            iLights.Add(new Light("Bedroom1", "Ceiling", 225, 150, 200, MakeColor(64, 32, 32, 255)));
            iLights.Add(new Light("Bedroom1", "Bedside1", 90, 15, 100, MakeColor(0, 255, 255, 255)));
            iLights.Add(new Light("Bedroom1", "Bedside2", 360, 15, 100, MakeColor(0, 255, 255, 255)));
            iLights.Add(new Light("Bedroom2", "Ceiling", 150, 150, 200, MakeColor(0, 255, 255, 255)));
        }

        private uint MakeColor(byte aBrightness, byte aRed, byte aGreen, byte aBlue)
        {
            return (uint)(aBrightness << 24 | aRed << 16 | aGreen << 8 | aBlue);
        }
    }

    class DeviceLights : IResourceManager, IDisposable
    {
        private DvDevice iDevice;
        private ServiceLights iLights;
        private string iConfigDir;
        public string iDeviceName;

        public DeviceLights(int aMode, string aConfigDir)
        {
            iConfigDir = aConfigDir;
            RandomiseUdn(out iDeviceName);
            iDevice = new DvDevice(iDeviceName, this);
            iDevice.SetAttribute("Upnp.Domain", "zapp.org");
            iDevice.SetAttribute("Upnp.Type", "TestLights");
            iDevice.SetAttribute("Upnp.Version", "1");
            iDevice.SetAttribute("Upnp.FriendlyName", "Zapp Lights");
            iDevice.SetAttribute("Upnp.Manufacturer", "None");
            iDevice.SetAttribute("Upnp.ManufacturerUrl", "http://www.linn.co.uk");
            iDevice.SetAttribute("Upnp.ModelDescription", "Demo lighting service, enabling simple UI development");
            iDevice.SetAttribute("Upnp.ModelName", "Zapp Lights v1");
            iDevice.SetAttribute("Upnp.ModelNumber", "1");
            iDevice.SetAttribute("Upnp.ModelUrl", "http://www.linn.co.uk");
            iDevice.SetAttribute("Upnp.SerialNumber", "123456");
            iDevice.SetAttribute("Upnp.Upc", "123456654321");
            iLights = new ServiceLights(iDevice, aMode);
            iDevice.SetEnabled();
        }

        public void Dispose()
        {
            iLights.Dispose();
            iDevice.Dispose();
        }

        public override void WriteResource(string aUriTail, uint aIpAddress, IResourceWriter aWriter)
        {
            string path = iConfigDir;
            if (aUriTail.Length == 0)
            {
                path += "index.html";
            }
            else
            {
                path += aUriTail;
            }
            byte[] data = System.IO.File.ReadAllBytes(path);
            aWriter.WriteResourceBegin(data.Length, "");
            aWriter.WriteResource(data, data.Length);
            aWriter.WriteResourceEnd();
        }

        private static void RandomiseUdn(out string aUdn)
        {
            aUdn = "device";
            aUdn += "-";
            /*Random rnd = new Random();
            aUdn += rnd.Next();*/
            aUdn += "ZappLights";
        }

    }
}
