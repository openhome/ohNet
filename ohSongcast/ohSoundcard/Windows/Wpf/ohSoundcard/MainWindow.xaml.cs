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
using System.Collections.ObjectModel;
using System.Collections.Specialized;

using System.Xml;
using System.Xml.Serialization;
using System.IO;

namespace OpenHome.Soundcard
{

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private ExtendedNotifyIcon iExtendedNotifyIcon; // global class scope for the icon as it needs to exist foer the lifetime of the window
        private Storyboard iStoryBoardFadeIn;
        private Storyboard iStoryBoardFadeOut;

        private Soundcard iSoundcard;

        private ConfigurationWindow iConfigurationWindow;
        private MediaPlayerWindow iMediaPlayerWindow;

        public MainWindow()
        {
            InitializeComponent();

            iExtendedNotifyIcon = new ExtendedNotifyIcon(Properties.Resources.Icon);
            iExtendedNotifyIcon.Hide += EventNotifyIconHide;
            iExtendedNotifyIcon.Show += EventNotifyIconShow;

            System.Windows.Forms.ContextMenu menu = new System.Windows.Forms.ContextMenu();

            System.Windows.Forms.MenuItem open = new System.Windows.Forms.MenuItem("Open", new EventHandler(EventContextMenuOpen));
            System.Windows.Forms.MenuItem exit = new System.Windows.Forms.MenuItem("Exit", new EventHandler(EventContextMenuExit));

            menu.MenuItems.Add(open);
            menu.MenuItems.Add(exit);

            iExtendedNotifyIcon.ContextMenu = menu;

            Left = SystemParameters.WorkArea.Width - LayoutRoot.Width - 10;
            Top = SystemParameters.WorkArea.Height - LayoutRoot.Height - 2;

            iConfigurationWindow = new ConfigurationWindow();
            iMediaPlayerWindow = new MediaPlayerWindow(iConfigurationWindow.Enabled);

            iConfigurationWindow.Left = Left;
            iConfigurationWindow.Top = Top - iConfigurationWindow.LayoutRoot.Height + 1;

            iMediaPlayerWindow.Left = Left;
            iMediaPlayerWindow.Top = Top - iMediaPlayerWindow.LayoutRoot.Height + 1;

            // Locate these storyboards and "cache" them - we only ever want to find these once for performance reasons
            iStoryBoardFadeIn = (Storyboard)this.TryFindResource("storyBoardFadeIn");
            iStoryBoardFadeIn.Completed += new EventHandler(EventStoryBoardFadeInCompleted);
            iStoryBoardFadeOut = (Storyboard)TryFindResource("storyBoardFadeOut");
            iStoryBoardFadeOut.Completed += new EventHandler(EventStoryBoardFadeOutCompleted);

            this.Closing += new System.ComponentModel.CancelEventHandler(EventWindowClosing);

            iSoundcard = new Soundcard(IPAddress.Any, iConfigurationWindow.MulticastChannel, iConfigurationWindow.Ttl, iConfigurationWindow.Multicast, iConfigurationWindow.Enabled, iConfigurationWindow.Preset, iMediaPlayerWindow.ReceiverList);

            iConfigurationWindow.NetworkChanged += EventNetworkChanged;
            iConfigurationWindow.MulticastChanged += EventMulticastChanged;
            iConfigurationWindow.MulticastChannelChanged += EventMulticastChannelChanged;
            iConfigurationWindow.TtlChanged += EventTtlChanged;
            iConfigurationWindow.PresetChanged += EventPresetChanged;

            bool value = iConfigurationWindow.Enabled;

            Power.IsChecked = value;

            iMediaPlayerWindow.SetEnabled(value);

            Power.Click += new RoutedEventHandler(EventPowerClick);
            Settings.Click += new RoutedEventHandler(EventSettingsClick);
            Receivers.Click += new RoutedEventHandler(EventReceiversClick);
        }

        void EventNetworkChanged()
        {
        }

        void EventMulticastChanged()
        {
            iSoundcard.SetMulticast(iConfigurationWindow.Multicast);

        }

        void EventMulticastChannelChanged()
        {
            iSoundcard.SetChannel(iConfigurationWindow.MulticastChannel);
        }

        void EventTtlChanged()
        {
            iSoundcard.SetTtl(iConfigurationWindow.Ttl);
        }

        void EventPresetChanged()
        {
            iSoundcard.SetPreset(iConfigurationWindow.Preset);
        }

        void EventContextMenuOpen(object sender, EventArgs e)
        {
            EventNotifyIconShow();
        }

        void EventContextMenuExit(object sender, EventArgs e)
        {
            this.Close();
        }

        void EventPowerClick(object sender, RoutedEventArgs e)
        {
            bool value = Power.IsChecked.Value;
            iConfigurationWindow.Enabled = value;
            iSoundcard.SetEnabled(value);
            iMediaPlayerWindow.SetEnabled(value);
        }

        void EventSettingsClick(object sender, RoutedEventArgs e)
        {
            bool enabled = Settings.IsChecked.Value;

            if (enabled)
            {
                iConfigurationWindow.Visibility = Visibility.Visible;
                iMediaPlayerWindow.Visibility = Visibility.Collapsed;
                Receivers.IsChecked = false;
                iConfigurationWindow.Activate();
            }
            else
            {
                iConfigurationWindow.Visibility = Visibility.Collapsed;
            }
        }

        void EventReceiversClick(object sender, RoutedEventArgs e)
        {
            bool enabled = Receivers.IsChecked.Value;

            if (enabled)
            {
                iMediaPlayerWindow.Visibility = Visibility.Visible;
                iConfigurationWindow.Visibility = Visibility.Collapsed;
                Settings.IsChecked = false;
                iMediaPlayerWindow.Activate();
            }
            else
            {
                iMediaPlayerWindow.Visibility = Visibility.Collapsed;
            }
        }

        void EventWindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            iConfigurationWindow.Close();
            iMediaPlayerWindow.SetEnabled(false);
            iMediaPlayerWindow.Close();
            iExtendedNotifyIcon.Dispose();
            iSoundcard.Dispose();
        }

        void EventStoryBoardFadeInCompleted(object sender, EventArgs e)
        {
        }

        void EventStoryBoardFadeOutCompleted(object sender, EventArgs e)
        {
            this.Visibility = Visibility.Collapsed;
        }

        void EventNotifyIconShow()
        {
            this.Visibility = Visibility.Visible;

            Activate();

            if (Settings.IsChecked.Value)
            {
                iConfigurationWindow.Visibility = Visibility.Visible;
                iConfigurationWindow.Activate();
            }

            if (Receivers.IsChecked.Value)
            {
                iMediaPlayerWindow.Visibility = Visibility.Visible;
                iMediaPlayerWindow.Activate();
            }
        }

        void EventNotifyIconHide()
        {
            /*
            iSettingsWindow.Visibility = Visibility.Collapsed;
            iReceiversWindow.Visibility = Visibility.Collapsed;
            this.Visibility = Visibility.Collapsed;
            */
        }

        protected override void OnDeactivated(EventArgs e)
        {
            base.OnDeactivated(e);

            if (!iExtendedNotifyIcon.Active && !iConfigurationWindow.IsActive && !iMediaPlayerWindow.IsActive)
            {
                EventNotifyIconHide();
            }
        }
    }
}
