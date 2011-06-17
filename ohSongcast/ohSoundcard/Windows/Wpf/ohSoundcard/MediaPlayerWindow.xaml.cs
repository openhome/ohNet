using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace OpenHome.Soundcard
{
    public interface IRefreshHandler
    {
        void Refresh();
    }

    /// <summary>
    /// Interaction logic for ReceiversWindow.xaml
    /// </summary>
    public partial class MediaPlayerWindow : Window
    {
        MediaPlayerConfiguration iMediaPlayerConfiguration;

        ReceiverList iReceiverList;

        IRefreshHandler iRefreshHandler;

        public MediaPlayerWindow(bool aEnabled, IRefreshHandler aRefreshHandler)
        {
            InitializeComponent();

            iRefreshHandler = aRefreshHandler;

            buttonRefresh.Click += new RoutedEventHandler(EventButtonRefreshClick);

            iReceiverList = new ReceiverList(this.Dispatcher);

            iReceiverList.CollectionChanged += new System.Collections.Specialized.NotifyCollectionChangedEventHandler(EventReceiverListCollectionChanged);

            iMediaPlayerConfiguration = MediaPlayerConfiguration.Load(aEnabled);

            listBoxReceivers.ItemsSource = iMediaPlayerConfiguration.MediaPlayerList;
        }

        void EventButtonRefreshClick(object sender, RoutedEventArgs e)
        {
            iMediaPlayerConfiguration.Refresh();
            iRefreshHandler.Refresh();
        }


        void EventReceiverListCollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            switch (e.Action)
            {
                case System.Collections.Specialized.NotifyCollectionChangedAction.Add:
                    foreach (object o in e.NewItems)
                    {
                        Receiver receiver = o as Receiver;
                        iMediaPlayerConfiguration.ReceiverAdded(receiver);
                    }
                    break;
                case System.Collections.Specialized.NotifyCollectionChangedAction.Remove:
                    foreach (object o in e.OldItems)
                    {
                        Receiver receiver = o as Receiver;
                        iMediaPlayerConfiguration.ReceiverRemoved(receiver);
                    }
                    break;
                default:
                    break;
            }
        }

        public ReceiverList ReceiverList
        {
            get
            {
                return (iReceiverList);
            }
        }

        private void EventPlayStopClick(object sender, RoutedEventArgs e)
        {
            Button button = sender as Button;
            ListBoxItem parent = button.FindVisualAncestor<ListBoxItem>();
            MediaPlayer player = listBoxReceivers.ItemContainerGenerator.ItemFromContainer(parent) as MediaPlayer;
            player.Click();
        }

        public void SetEnabled(bool aValue)
        {
            iMediaPlayerConfiguration.SetEnabled(aValue);
        }

        public void SubnetChanged()
        {
            iMediaPlayerConfiguration.SubnetChanged();
        }
    }

    public static class DependencyObjectExtensions
    {
        public static ancestorItem FindVisualAncestor<ancestorItem>(this DependencyObject obj) where ancestorItem : DependencyObject
        {
            DependencyObject dep = obj;
            do
            {
                dep = VisualTreeHelper.GetParent(dep);
            } while ((dep != null) && !(dep is ancestorItem));
            return dep as ancestorItem;
        }
    }
}
