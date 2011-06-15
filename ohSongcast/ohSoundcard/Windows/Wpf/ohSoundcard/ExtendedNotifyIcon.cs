//-----------------------------------------------------------------------------------------
// Based on code published at CodeProject by Murray Foxcroft - April 2009
//-----------------------------------------------------------------------------------------
using System;
using System.Windows.Forms;
using System.Drawing;

namespace OpenHome.Soundcard
{
    /// <summary>
    /// An extension of the notifyIcon Windows Forms class, unfortunately its a 
    //  sealed class so it cannot be inherited. This class adds a timer and additional 
    //  methods and events to allow for monitoring when a mouse enters and leaves the icon area. 
    /// </summary>
    /// 
    public class ExtendedNotifyIcon : IDisposable
    {
        const int kMouseLeaveTimerDelayMilliseconds = 300;

        public Action Hide;
        public Action Show;

        private NotifyIcon iTarget;

        public ExtendedNotifyIcon(Icon aIcon)
        {
            iActive = false;
            iTarget = new NotifyIcon();
            iTarget.Icon = aIcon;
            iTarget.Visible = true;
            iTarget.MouseDown += new MouseEventHandler(EventTargetMouseDown);
        }

        public ContextMenu ContextMenu
        {
            set
            {
                iTarget.ContextMenu = value;
            }
        }

        public void EventTargetMouseDown(object sender, MouseEventArgs e)
        {
            //iActive = true;

            if (e.Button == MouseButtons.Left)
            {
                Show();
            }
        }

        public void EventTargetMouseUp(object sender, MouseEventArgs e)
        {
            iActive = false;
        }

        public void Dispose()
        {
            iTarget.Dispose();
        }

        public bool Active
        {
            get
            {
                return (iActive);
            }
        }

        private bool iActive;
    }
}
