using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Xml;
using System.Xml.Serialization;
using System.IO;

namespace OpenHome.Soundcard
{
    [XmlRoot("Configuration")]

    public class Configuration
    {
        public static Configuration Load()
        {
            XmlSerializer xml = new XmlSerializer(typeof(Configuration));

            string common = Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData);
            string folder = Path.Combine(common, "ohSoundcard");

            if (!Directory.Exists(folder))
            {
                Directory.CreateDirectory(folder);
            }

            string path = Path.Combine(folder, "Configuration.xml");

            if (!File.Exists(path))
            {
                return (New(path));
            }

            FileInfo info = new FileInfo(path);

            if (info.Length == 0)
            {
                return (New(path));
            }

            try
            {
                TextReader reader = new StreamReader(path);
                Configuration configuration = (Configuration)xml.Deserialize(reader);
                configuration.SetPath(path);
                reader.Close();
                return (configuration);
            }
            catch (Exception)
            {
                return (New(path));
            }
        }

        private static Configuration New(string aPath)
        {
            Configuration configuration = new Configuration();
            configuration.Subnet = 0;
            configuration.Multicast = false;
            configuration.MulticastChannel = (uint)(new Random().Next(65535) + 1);
            configuration.Ttl = 1;
            configuration.Preset = 0;
            configuration.SetPath(aPath);
            configuration.Save();
            return (configuration);
        }

        public void Save()
        {
            XmlSerializer xml = new XmlSerializer(typeof(Configuration));

            TextWriter writer = new StreamWriter(iPath);

            xml.Serialize(writer, this);

            writer.Close();
        }

        private void SetPath(string aPath)
        {
            iPath = aPath;
        }

        private string iPath;

        [XmlElement("Network")]

        public uint Subnet
        {
            get
            {
                return (iSubnet);
            }
            set
            {
                iSubnet = value;
            }
        }

        [XmlElement("Multicast")]

        public bool Multicast
        {
            get
            {
                return (iMulticast);
            }
            set
            {
                iMulticast = value;
            }
        }

        [XmlElement("MulticastChannel")]

        public uint MulticastChannel
        {
            get
            {
                return (iMulticastChannel);
            }
            set
            {
                iMulticastChannel = value;
            }
        }

        [XmlElement("Ttl")]

        public uint Ttl
        {
            get
            {
                return (iTtl);
            }
            set
            {
                iTtl = value;
            }
        }

        [XmlElement("Preset")]

        public uint Preset
        {
            get
            {
                return (iPreset);
            }
            set
            {
                iPreset = value;
            }
        }

        [XmlElement("Enabled")]

        public bool Enabled
        {
            get
            {
                return (iEnabled);
            }
            set
            {
                iEnabled = value;
            }
        }


        private uint iSubnet;
        private bool iMulticast;
        private uint iMulticastChannel;
        private uint iTtl;
        private uint iPreset;
        private bool iEnabled;
    }


}