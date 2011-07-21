using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net;
using System.ComponentModel;
using System.Collections;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Windows.Threading;

namespace OpenHome.Soundcard
{
    public class Receiver : INotifyPropertyChanged
    {
        internal Receiver(IReceiver aReceiver)
        {
            iReceiver = aReceiver;
            iDescription = iReceiver.Room + " (" + iReceiver.Group + ")";
        }

        public void Play()
        {
            iReceiver.Play();
        }

        public void Stop()
        {
            iReceiver.Stop();
        }

        public void Standby()
        {
            iReceiver.Stop();
        }

        public string Udn
        {
            get
            {
                return (iReceiver.Udn);
            }
        }

        public string Room
        {
            get
            {
                return (iReceiver.Room);
            }
        }

        public string Group
        {
            get
            {
                return (iReceiver.Group);
            }
        }

        public string Name
        {
            get
            {
                return (iReceiver.Name);
            }
        }

        public EReceiverStatus Status
        {
            get
            {
                return (iReceiver.Status);
            }
        }

        public override string ToString()
        {
            return (iDescription);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        internal bool MapsTo(IReceiver aReceiver)
        {
            return (aReceiver == iReceiver);
        }

        internal void Changed()
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs("Status"));
            }
        }

        private IReceiver iReceiver;
        private string iDescription;
    }

    internal delegate void DelegateReceiverList(IReceiver aReceiver);

    public class ReceiverList : IReceiverHandler, IEnumerable, INotifyCollectionChanged
    {
        public ReceiverList(Dispatcher aDispatcher)
        {
            iDispatcher = aDispatcher;
            iList = new List<Receiver>();
        }

        public void ReceiverAdded(IReceiver aReceiver)
        {
            iDispatcher.BeginInvoke(new DelegateReceiverList(Added), new object[] { aReceiver });
        }

        internal void Added(IReceiver aReceiver)
        {
            Receiver receiver = new Receiver(aReceiver);
            iList.Add(receiver);

            if (CollectionChanged != null)
            {
                CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, receiver));
            }
        }

        public void ReceiverChanged(IReceiver aReceiver)
        {
            iDispatcher.BeginInvoke(new DelegateReceiverList(Changed), new object[] { aReceiver });
        }

        internal void Changed(IReceiver aReceiver)
        {
            foreach (Receiver receiver in iList)
            {
                if (receiver.MapsTo(aReceiver))
                {
                    receiver.Changed();
                    return;
                }
            }
        }

        public void ReceiverRemoved(IReceiver aReceiver)
        {
            iDispatcher.BeginInvoke(new DelegateReceiverList(Removed), new object[] { aReceiver });
        }

        internal void Removed(IReceiver aReceiver)
        {
            int index = 0;

            foreach (Receiver receiver in iList)
            {
                if (receiver.MapsTo(aReceiver))
                {
                    iList.Remove(receiver);

                    if (CollectionChanged != null)
                    {
                        CollectionChanged(this, new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, receiver, index));
                    }

                    return;
                }

                index++;
            }
        }

        public System.Collections.IEnumerator GetEnumerator()
        {
            return (iList.GetEnumerator());
        }
        

        public event NotifyCollectionChangedEventHandler CollectionChanged;

        Dispatcher iDispatcher;
        List<Receiver> iList;
    }

}