using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ZapSpyGui
{
    /// <summary>
    /// Creates TreeNodes to represent UPnP devices and their constituent services
    /// in a TreeView.
    /// </summary>
    public class DeviceGrapher
    {
        /// <summary>
        /// This context menu will be attached to each tree node created
        /// by the grapher.
        /// </summary>
        public ContextMenuStrip ContextMenu { get; set; }

        private TreeNode StateVariableInfoToTreeNode(ZappSpy.UpnpServiceStateVariableInfo aStateVariableInfo)
        {
            return new TreeNode(aStateVariableInfo.Name)
                {
                    Tag = aStateVariableInfo,
                    ContextMenuStrip = ContextMenu
                };
        }

        private TreeNode ActionInfoToTreeNode(ZappSpy.UpnpServiceActionInfo aActionInfo)
        {
            return new TreeNode(
                String.Format(
                    "{0}({1})",
                    aActionInfo.Name,
                    string.Join(", ", (from arg in aActionInfo.Arguments select arg.DirectionAsString + " " + arg.Name).ToArray())
                ))
                {
                    Tag = aActionInfo,
                    ContextMenuStrip = ContextMenu
                };
        }

        private TreeNode ServiceInfoToTreeNode(ZappSpy.UpnpServiceInfo aServiceInfo)
        {
            return new TreeNode(
                aServiceInfo.ServiceId, (
                    from action in aServiceInfo.Description.Actions
                    orderby action.Name
                    select ActionInfoToTreeNode(action)
                ).Concat(
                    new[] {
                        new TreeNode(
                            "State variables", (
                                from variable in aServiceInfo.Description.StateVariables
                                orderby variable.Name
                                select StateVariableInfoToTreeNode(variable)
                            ).ToArray())
                    }
                ).ToArray())
                {
                    Tag = aServiceInfo,
                    ContextMenuStrip = ContextMenu
                };
        }

        public TreeNode DeviceInfoToTreeNode(ZappSpy.UpnpDeviceInfo aDeviceInfo)
        {
            return new TreeNode(
                aDeviceInfo.FriendlyName, (
                    from service in aDeviceInfo.Services
                    select ServiceInfoToTreeNode(service)
                ).Concat(
                    from device in aDeviceInfo.EmbeddedDevices
                    select DeviceInfoToTreeNode(device)
                ).ToArray())
                {
                    Name = aDeviceInfo.UDN,
                    Tag = aDeviceInfo,
                    ContextMenuStrip = ContextMenu
                };
        }
    }
}
