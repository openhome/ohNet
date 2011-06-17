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
    /// <summary>
    /// Interaction logic for SettingsWindow.xaml
    /// </summary>
    public partial class ConfigurationWindow : Window
    {
        private Configuration iConfiguration;
        private SubnetList iSubnetList;

        public ConfigurationWindow()
        {
            InitializeComponent();

            iConfiguration = Configuration.Load();

            iSubnetList = new SubnetList(this.Dispatcher);

            iSubnetList.CollectionChanged += new System.Collections.Specialized.NotifyCollectionChangedEventHandler(EventSubnetListCollectionChanged);

            comboBoxNetwork.ItemsSource = iSubnetList;

            textBlockInfo.Text = "V" + System.Windows.Forms.Application.ProductVersion;

            radioButtonUnicast.IsChecked = !iConfiguration.Multicast;
            radioButtonMulticast.IsChecked = iConfiguration.Multicast;
            textBoxChannel.Text = iConfiguration.MulticastChannel.ToString();
            sliderTtl.Value = iConfiguration.Ttl;
            textBoxPreset.Text = iConfiguration.Preset.ToString();

            buttonChannelNew.Click += EventButtonChannelNewClick;
            sliderTtl.ValueChanged += EventSliderTtlValueChanged;
            textBoxPreset.TextChanged += EventTextBoxPresetTextChanged;
            radioButtonUnicast.Checked += EventRadioButtonUnicastChecked;
            radioButtonMulticast.Checked += EventRadioButtonMulticastChecked;
            comboBoxNetwork.SelectionChanged += EventComboBoxNetworkSelectionChanged;
        }

        void EventSubnetListCollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            int index = 0;

            foreach (Subnet subnet in iSubnetList)
            {
                if (subnet.Address == iConfiguration.Subnet)
                {
                    comboBoxNetwork.SelectedIndex = index;
                    return;
                }

                index++;
            }

            comboBoxNetwork.SelectedIndex = -1;
        }

        public SubnetList SubnetList
        {
            get
            {
                return (iSubnetList);
            }
        }

        private void InformListeners(Action aAction)
        {
            if (aAction != null)
            {
                aAction();
            }
        }

        private void EventButtonChannelNewClick(object sender, RoutedEventArgs e)
        {
            uint value = (uint)(new Random().Next(65535) + 1);
            textBoxChannel.Text = value.ToString();
            iConfiguration.MulticastChannel = value;
            iConfiguration.Save();
            InformListeners(MulticastChannelChanged);
        }

        private void EventSliderTtlValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            iConfiguration.Ttl = (uint)sliderTtl.Value;
            iConfiguration.Save();
            InformListeners(TtlChanged);
        }

        private void EventTextBoxPresetTextChanged(object sender, TextChangedEventArgs e)
        {
            uint value;

            if (uint.TryParse(textBoxPreset.Text, out value))
            {
                if (value != iConfiguration.Preset)
                {
                    iConfiguration.Preset = value;
                    iConfiguration.Save();
                    InformListeners(PresetChanged);
                }
            }

            string svalue = iConfiguration.Preset.ToString();

            if (textBoxPreset.Text != svalue)
            {
                textBoxPreset.Text = svalue;
            }
        }

        private void EventRadioButtonUnicastChecked(object sender, RoutedEventArgs e)
        {
            if (iConfiguration.Multicast)
            {
                iConfiguration.Multicast = false;
                iConfiguration.Save();
                InformListeners(MulticastChanged);
            }
        }

        private void EventRadioButtonMulticastChecked(object sender, RoutedEventArgs e)
        {
            if (!iConfiguration.Multicast)
            {
                iConfiguration.Multicast = true;
                iConfiguration.Save();
                InformListeners(MulticastChanged);
            }
        }

        private void EventComboBoxNetworkSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int index = comboBoxNetwork.SelectedIndex;

            if (index >= 0)
            {
                Subnet subnet = iSubnetList.SubnetAt(index);
                
                uint address = subnet.Address;

                if (iConfiguration.Subnet != address)
                {
                    iConfiguration.Subnet = address;
                    iConfiguration.Save();
                    InformListeners(SubnetChanged);
                }
            }

        }

        public Action DefaultAutoplayChanged;
        public Action SubnetChanged;
        public Action MulticastChanged;
        public Action MulticastChannelChanged;
        public Action TtlChanged;
        public Action PresetChanged;

        public uint Subnet
        {
            get
            {
                return (iConfiguration.Subnet);
            }
        }

        public bool Multicast
        {
            get
            {
                return (iConfiguration.Multicast);
            }
        }

        public uint MulticastChannel
        {
            get
            {
                return (iConfiguration.MulticastChannel);
            }
        }

        public uint Ttl
        {
            get
            {
                return (iConfiguration.Ttl);
            }
        }

        public uint Preset
        {
            get
            {
                return (iConfiguration.Preset);
            }
        }

        public bool Enabled
        {
            get
            {
                return (iConfiguration.Enabled);
            }
            set
            {
                if (iConfiguration.Enabled != value)
                {
                    iConfiguration.Enabled = value;
                    iConfiguration.Save();
                }
            }
        }
    }
}
