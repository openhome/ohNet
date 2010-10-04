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
using System.Threading;


namespace Viewer
{
    /// <summary>
    /// Interaction logic for ProgressBarWindow.xaml
    /// </summary>
    public partial class ProgressBarWindow : Window
    {
        public ProgressBarWindow()
        {
            InitializeComponent();
            this.progressBar.Value = this.progressBar.Minimum;
        }

        public ProgressBarWindow(double aProgressBarMaximum, double aProgressBarMinimum)
        {
            InitializeComponent();
            this.progressBar.Maximum = aProgressBarMaximum;
            this.progressBar.Minimum = aProgressBarMinimum;
            this.progressBar.Value = this.progressBar.Minimum;
        }

        public double Maximum
        {
            get
            {
                return progressBar.Maximum;
            }
            set
            {
                progressBar.Maximum = value;
            }
        }

        public double Minimum
        {
            get
            {
                return progressBar.Minimum;
            }
            set
            {
                progressBar.Minimum = value;
            }
        }

        public double Value
        {
            get
            {
                return progressBar.Value;
            }
            set
            {
                progressBar.Value = value;
            }
        }

        private Mutex iMutex = new Mutex();
    }
}
