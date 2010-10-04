using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ZapSpyGui
{
    public partial class MainForm : Form
    {
        private ZappSpy.ZappLibraryWrapper iZappLibrary;
        private ZappSpy.UpnpDeviceFinder iDeviceFinder;
        private DeviceGrapher iDeviceGrapher;
        private ContextMenuStrip iContextMenu;

        public MainForm(DeviceGrapher aDeviceGrapher)
        {
            iDeviceGrapher = aDeviceGrapher;
            iContextMenu = new ContextMenuStrip();
            iDeviceGrapher.ContextMenu = iContextMenu;
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            iZappLibrary = new ZappSpy.ZappLibraryWrapper();
            iDeviceFinder = new ZappSpy.UpnpDeviceFinder(iZappLibrary);
            iDeviceFinder.DeviceAdded += HandleDeviceAdded;
            iDeviceFinder.DeviceRemoved += HandleDeviceRemoved;
            iContextMenu.Opening += iContextMenu_Opening;
            iDeviceTreeView.NodeMouseClick += iDeviceTreeView_NodeMouseClick;
            iDeviceTreeView.AfterSelect += iDeviceTreeView_AfterSelect;
            iDeviceTreeView.Sorted = true;
            this.FormClosing += new FormClosingEventHandler(MainForm_FormClosing);
            // TODO: Fix API to prevent race conditions between initialisation and event registration.
            iDeviceFinder.Refresh();
        }

        void MainForm_FormClosing(object aSender, FormClosingEventArgs aE)
        {
            iDeviceFinder.DeviceAdded -= HandleDeviceAdded;
            iDeviceFinder.DeviceRemoved -= HandleDeviceRemoved;
            iContextMenu.Opening -= iContextMenu_Opening;
            iDeviceTreeView.NodeMouseClick -= iDeviceTreeView_NodeMouseClick;
            iDeviceTreeView.AfterSelect -= iDeviceTreeView_AfterSelect;
            iDeviceFinder.Dispose();
            iDeviceFinder = null;
            iZappLibrary.Dispose();
            iZappLibrary = null;
        }

        void iDeviceTreeView_AfterSelect(object aSender, TreeViewEventArgs aE)
        {
            object nodeTag = iDeviceTreeView.SelectedNode.Tag;
            ZappSpy.IPropertyBag propertyBag = nodeTag as ZappSpy.IPropertyBag;
            iDetailsListView.Items.Clear();
            if (propertyBag != null)
            {

                iDetailsListView.Items.AddRange((
                    from kvp in propertyBag.Properties
                    select new ListViewItem(new string[] { kvp.Key, kvp.Value })).ToArray());
            }
        }

        void iDeviceTreeView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            // By default, right-clicking doesn't select the node.
            // Since the context menu's Opening event doesn't know what
            // node it was triggered for (only the control) we have to
            // make sure that the selected node is set during the click.
            // A nicer solution would be appreciated. Note that any
            // solution should not interfere with using the context
            // menu key on the keyboard.
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                iDeviceTreeView.SelectedNode = e.Node;
            }
        }

        void iContextMenu_Opening(object sender, CancelEventArgs e)
        {
            // Populate the context menu appropriate to whatever was
            // clicked on, or cancel it if the node doesn't have any
            // actions.
            iContextMenu.Items.Clear();
            e.Cancel = false;
            object nodeTag = iDeviceTreeView.SelectedNode.Tag;
            ZappSpy.UpnpServiceInfo serviceInfo = nodeTag as ZappSpy.UpnpServiceInfo;
            if (serviceInfo != null)
            {
                iContextMenu.Items.Add(
                    new ToolStripMenuItem(
                        "Show Service XML",
                        null,
                        (aSender, aE) =>
                        {
                            var form = new ShowXmlForm();
                            form.XmlContent = serviceInfo.DescriptionXml;
                            form.Text = serviceInfo.ServiceId + " - Service XML";
                            form.Show();
                        }));       
                return;
            }
            ZappSpy.UpnpDeviceInfo deviceInfo = nodeTag as ZappSpy.UpnpDeviceInfo;
            if (deviceInfo != null)
            {
                iContextMenu.Items.Add(
                    new ToolStripMenuItem(
                        "Show Device XML",
                        null,
                        (aSender, aE) =>
                        {
                            var form = new ShowXmlForm();
                            form.XmlContent = deviceInfo.DeviceXml;
                            form.Text = deviceInfo.FriendlyName + " - Device XML";
                            form.Show();
                        }));
                return;
            }
            e.Cancel = true;
            return;
        }

        private void HandleDeviceAdded(object aSender, ZappSpy.UpnpDeviceFinder.UpnpDeviceEventArgs aEventArgs)
        {
            Invoke((Action)(()=>
                {
                    TreeNode treeNode = iDeviceGrapher.DeviceInfoToTreeNode(aEventArgs.DeviceInfo);
                    iDeviceTreeView.Nodes.Add(treeNode);
                }));
        }

        private void HandleDeviceRemoved(object aSender, ZappSpy.UpnpDeviceFinder.UpnpDeviceEventArgs aEventArgs)
        {
            Invoke((Action)(()=>
                {
                    iDeviceTreeView.Nodes.RemoveByKey(aEventArgs.DeviceInfo.UDN);
                }));
        }
    }
}