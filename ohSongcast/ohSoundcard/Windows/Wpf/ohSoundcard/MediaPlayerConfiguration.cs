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

        public bool Active
        {
            get
            {
                return (iReceiver != null);
            }
        }

        public void SetEnabled(bool aValue)
        {
            iEnabled = aValue;

            UpdateStatus();

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
            else
            {
                if (iStatus == "Playing")
                {
                    Stop();
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
            if (iReceiver != null && iEnabled)
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

        public void Detach()
        {
            iReceiver = null;

            UpdateStatus();
        }

        void Play()
        {
            iReceiver.Play();
        }

        void Stop()
        {
            iReceiver.Stop();
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

                    if (iReceiver != null)
                    {
                        if (iAttached && iEnabled)
                        {
                            Play();
                        }

                        if (!iAttached && !iEnabled)
                        {
                            Standby();
                        }
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

            return (1);
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

        public void SubnetChanged()
        {
            iMediaPlayerList.DetachAll();
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
            if (e.PropertyName == "Attached")
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

        public void Refresh()
        {
            iMediaPlayerList.Purge();

            Save();
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

            Save();
        }

        public void ReceiverRemoved(Receiver aReceiver)
        {
            foreach (MediaPlayer player in iMediaPlayerList)
            {
                if (player.Udn == aReceiver.Udn)
                {
                    player.Detach();
                    return;
                }
            }
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

        public void DetachAll()
        {
            foreach (MediaPlayer player in iList)
            {
                player.Detach();
            }
        }

        public void Add(Object aObject)
        {
            MediaPlayer add = aObject as MediaPlayer;

            int index = 0;

            foreach (MediaPlayer player in iList)
            {
                if (add.CompareTo(player) < 0)
                {
                    iList.Insert(index, add);

                    if (CollectionChanged != null)
                    {
                        CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, aObject, index));
                    }

                    return;
                }

                index++;
            }

            iList.Add(add);

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

        internal void Purge()
        {
            List<int> list = new List<int>();

            int index = 0;

            foreach (MediaPlayer player in iList)
            {
                if (!player.Active)
                {
                    list.Add(index);
                }

                index++;
            }

            int adjustment = 0;

            foreach (int i in list)
            {
                MediaPlayer player = iList[i + adjustment];

                if (CollectionChanged != null)
                {
                    CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, player, i + adjustment));
                }

                iList.Remove(player);

                adjustment--;
            }
        }

        public System.Collections.IEnumerator GetEnumerator()
        {
            return (iList.GetEnumerator());
        }

        private List<MediaPlayer> iList;
    }
}
