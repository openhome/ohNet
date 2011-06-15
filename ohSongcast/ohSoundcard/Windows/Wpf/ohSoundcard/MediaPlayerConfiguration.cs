using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Xml;
using System.Xml.Serialization;
using System.IO;

using System.ComponentModel;
using System.Collections;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace OpenHome.Soundcard
{
    public class MediaPlayer : INotifyPropertyChanged, IComparable
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public MediaPlayer()
        {
            iEnabled = false;
        }

        public void Click()
        {
            if (iStatus != "Off")
            {
                if (iStatus == "Stopped")
                {
                    iReceiver.Play();
                }
                else
                {
                    iReceiver.Stop();
                }
            }
        }

        public void SetEnabled(bool aValue)
        {
            iEnabled = aValue;

            if (iReceiver != null)
            {   
                EnactAttached();
            }
        }

        private void EnactAttached()
        {
            if (iAttached)
            {
                if (iEnabled)
                {
                    Play();
                }
                else
                {
                    Standby();
                }
            }
        }

        public void Initialise(bool aEnabled)
        {
            iEnabled = aEnabled;
            UpdateDescription();
            UpdateStatus();
        }

        public MediaPlayer(Receiver aReceiver, bool aEnabled)
        {
            iReceiver = aReceiver;

            iReceiver.PropertyChanged += new PropertyChangedEventHandler(EventReceiverPropertyChanged);

            iAttached = false;
            iUdn = aReceiver.Udn;
            iRoom = aReceiver.Room;
            iName = aReceiver.Name;
            iGroup = aReceiver.Group;

            Initialise(aEnabled);
        }

        private void UpdateStatus()
        {
            if (iReceiver != null)
            {
                switch (iReceiver.Status)
                {
                    case EReceiverStatus.eConnected:
                        Status = "Playing";
                        break;
                    case EReceiverStatus.eConnecting:
                        Status = "Buffering";
                        break;
                    case EReceiverStatus.eDisconnected:
                        Status = "Stopped";
                        break;
                }
            }
            else
            {
                Status = "Off";
            }
        }

        public bool Attach(Receiver aReceiver)
        {
            iReceiver = aReceiver;

            iReceiver.PropertyChanged += new PropertyChangedEventHandler(EventReceiverPropertyChanged);

            bool changed = false;

            if (iRoom != aReceiver.Room)
            {
                Room = aReceiver.Room;
                changed = true;
            }

            if (iName != aReceiver.Name)
            {
                Name = aReceiver.Name;
                changed = true;
            }

            if (Group != aReceiver.Group)
            {
                Group = aReceiver.Group;
                changed = true;
            }

            UpdateStatus();

            EnactAttached();

            return (changed);
        }

        void Play()
        {
            iReceiver.Play();
        }

        void Standby()
        {
            iReceiver.Standby();
        }

        void EventReceiverPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "Status")
            {
                UpdateStatus();
            }
        }

        [XmlElement("Attached")]

        public bool Attached
        {
            get
            {
                return (iAttached);
            }
            set
            {
                if (iAttached != value)
                {
                    iAttached = value;

                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Attached"));
                    }
                }
            }
        }

        [XmlElement("Udn")]

        public string Udn
        {
            get
            {
                return (iUdn);
            }
            set
            {
                iUdn = value;
            }
        }


        [XmlElement("Room")]

        public string Room
        {
            get
            {
                return (iRoom);
            }
            set
            {
                if (iRoom != value)
                {
                    iRoom = value;

                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Room"));

                        UpdateDescription();
                    }
                }
            }
        }

        [XmlElement("Name")]

        public string Name
        {
            get
            {
                return (iName);
            }
            set
            {
                if (iName != value)
                {
                    iName = value;

                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Name"));
                    }
                }
            }
        }

        [XmlElement("Group")]

        public string Group
        {
            get
            {
                return (iGroup);
            }
            set
            {
                if (iGroup != value)
                {
                    iGroup = value;

                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Group"));

                        UpdateDescription();
                    }
                }
            }
        }

        [XmlIgnore]

        public string Status
        {
            get
            {
                return (iStatus);
            }
            set
            {
                if (iStatus != value)
                {
                    iStatus = value;

                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Status"));
                    }
                }
            }
        }

        [XmlIgnore]

        public string Description
        {
            get
            {
                return (iDescription);
            }
        }

        private void UpdateDescription()
        {
            string description = iRoom + ":" + iGroup;

            if (iDescription != description)
            {
                iDescription = description;

                if (PropertyChanged != null)
                {
                    PropertyChanged(this, new PropertyChangedEventArgs("Description"));
                }
            }
        }

        public int CompareTo(object obj)
        {
            MediaPlayer player = obj as MediaPlayer;

            if (iDescription != null && player.iDescription != null)
            {
                return (iDescription.CompareTo(player.iDescription));
            }

            return (-1);
        }


        private Receiver iReceiver;
        private bool iAttached;
        private string iRoom;
        private string iName;
        private string iGroup;
        private string iStatus;
        private string iUdn;
        private string iDescription;
        private bool iEnabled;
    }

    [XmlRoot("MediaPlayerConfiguration")]
    [XmlInclude(typeof(MediaPlayer))]

    public class MediaPlayerConfiguration
    {
        public static MediaPlayerConfiguration Load(bool aEnabled)
        {
            MediaPlayerConfiguration configuration;

            XmlSerializer xml = new XmlSerializer(typeof(MediaPlayerConfiguration));

            string common = Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData);
            string folder = Path.Combine(common, "ohSoundcard");

            if (!Directory.Exists(folder))
            {
                Directory.CreateDirectory(folder);
            }

            string path = Path.Combine(folder, "MediaPlayerConfiguration.xml");

            if (!File.Exists(path))
            {
                configuration = new MediaPlayerConfiguration();
                configuration.SetPath(path);
                configuration.Save();
            }
            else
            {
                TextReader reader = new StreamReader(path);
                configuration = (MediaPlayerConfiguration)xml.Deserialize(reader);
                configuration.SetPath(path);
                reader.Close();
            }

            configuration.Initialise(aEnabled);

            return (configuration);
        }

        private void SetPath(string aPath)
        {
            iPath = aPath;
        }

        private string iPath;

        private void Initialise(bool aEnabled)
        {
            iEnabled = aEnabled;

            foreach (MediaPlayer player in iMediaPlayerList)
            {
                player.Initialise(iEnabled);
                player.PropertyChanged += new PropertyChangedEventHandler(EventMediaPlayerPropertyChanged);
            }

            iMediaPlayerList.CollectionChanged += new NotifyCollectionChangedEventHandler(EventMediaPlayerListCollectionChanged);
        }

        void EventMediaPlayerListCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            switch (e.Action)
            {
                case System.Collections.Specialized.NotifyCollectionChangedAction.Add:
                    foreach (object o in e.NewItems)
                    {
                        MediaPlayer player = o as MediaPlayer;
                        player.PropertyChanged += new PropertyChangedEventHandler(EventMediaPlayerPropertyChanged);
                    }
                    break;
                default:
                    break;
            }
        }

        void EventMediaPlayerPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "Autoplay")
            {
                Save();
            }
        }

        public void Save()
        {
            XmlSerializer xml = new XmlSerializer(typeof(MediaPlayerConfiguration));

            TextWriter writer = new StreamWriter(iPath);

            xml.Serialize(writer, this);

            writer.Close();
        }

        public MediaPlayerConfiguration()
        {
            iMediaPlayerList = new MediaPlayerList();
        }

        [XmlElement("MediaPlayerList")]

        public MediaPlayerList MediaPlayerList
        {
            get
            {
                return (iMediaPlayerList);
            }
            set
            {
                iMediaPlayerList = value;
            }
        }

        public void ReceiverAdded(Receiver aReceiver)
        {
            foreach (MediaPlayer player in iMediaPlayerList)
            {
                if (player.Udn == aReceiver.Udn)
                {
                    if (player.Attach(aReceiver))
                    {
                        Save();
                    }

                    return;
                }
            }

            MediaPlayer newplayer = new MediaPlayer(aReceiver, iEnabled);

            iMediaPlayerList.Add(newplayer);

            iMediaPlayerList.Sort();

            Save();
        }

        public void SetEnabled(bool aEnabled)
        {
            iEnabled = aEnabled;
            iMediaPlayerList.SetEnabled(iEnabled);
        }

        bool iEnabled;

        MediaPlayerList iMediaPlayerList;
    }

    public class MediaPlayerList : IEnumerable, INotifyCollectionChanged
    {
        public event NotifyCollectionChangedEventHandler CollectionChanged;

        public MediaPlayerList()
        {
            iList = new List<MediaPlayer>();
        }

        public void Add(Object aObject)
        {
            iList.Add(aObject as MediaPlayer);

            if (CollectionChanged != null)
            {
                CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, aObject));
            }
        }

        public void Sort()
        {
            iList.Sort();
        }

        internal void SetEnabled(bool aValue)
        {
            foreach (MediaPlayer player in iList)
            {
                player.SetEnabled(aValue);
            }
        }

        public System.Collections.IEnumerator GetEnumerator()
        {
            return (iList.GetEnumerator());
        }

        private List<MediaPlayer> iList;
    }
}
