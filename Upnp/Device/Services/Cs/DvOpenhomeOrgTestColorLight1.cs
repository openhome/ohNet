using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderOpenhomeOrgTestColorLight1 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the openhome.org:TestColorLight:1 UPnP service
    /// </summary>
    public class DvProviderOpenhomeOrgTestColorLight1 : DvProvider, IDisposable, IDvProviderOpenhomeOrgTestColorLight1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateGetName;
        private ActionDelegate iDelegateSetColor;
        private ActionDelegate iDelegateGetColor;
        private ActionDelegate iDelegateGetMaxColors;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderOpenhomeOrgTestColorLight1(DvDevice aDevice)
            : base(aDevice, "openhome.org", "TestColorLight", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action GetName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetName must be overridden if this is called.</remarks>
        protected void EnableActionGetName()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetName");
            List<String> allowedValues = new List<String>();
            action.AddOutputParameter(new ParameterString("FriendlyName", allowedValues));
            iDelegateGetName = new ActionDelegate(DoGetName);
            EnableAction(action, iDelegateGetName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetColor is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetColor must be overridden if this is called.</remarks>
        protected void EnableActionSetColor()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetColor");
            action.AddInputParameter(new ParameterUint("Red"));
            action.AddInputParameter(new ParameterUint("Green"));
            action.AddInputParameter(new ParameterUint("Blue"));
            iDelegateSetColor = new ActionDelegate(DoSetColor);
            EnableAction(action, iDelegateSetColor, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetColor is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetColor must be overridden if this is called.</remarks>
        protected void EnableActionGetColor()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetColor");
            action.AddOutputParameter(new ParameterUint("Red"));
            action.AddOutputParameter(new ParameterUint("Green"));
            action.AddOutputParameter(new ParameterUint("Blue"));
            iDelegateGetColor = new ActionDelegate(DoGetColor);
            EnableAction(action, iDelegateGetColor, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action GetMaxColors is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetMaxColors must be overridden if this is called.</remarks>
        protected void EnableActionGetMaxColors()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetMaxColors");
            action.AddOutputParameter(new ParameterUint("Red"));
            action.AddOutputParameter(new ParameterUint("Green"));
            action.AddOutputParameter(new ParameterUint("Blue"));
            iDelegateGetMaxColors = new ActionDelegate(DoGetMaxColors);
            EnableAction(action, iDelegateGetMaxColors, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// GetName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetName action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetName was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aFriendlyName"></param>
        protected virtual void GetName(uint aVersion, out string aFriendlyName)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetColor action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetColor action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetColor was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        protected virtual void SetColor(uint aVersion, uint aRed, uint aGreen, uint aBlue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetColor action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetColor action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetColor was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        protected virtual void GetColor(uint aVersion, out uint aRed, out uint aGreen, out uint aBlue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// GetMaxColors action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetMaxColors action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetMaxColors was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aRed"></param>
        /// <param name="aGreen"></param>
        /// <param name="aBlue"></param>
        protected virtual void GetMaxColors(uint aVersion, out uint aRed, out uint aGreen, out uint aBlue)
        {
            throw (new ActionDisabledError());
        }

        private static int DoGetName(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestColorLight1 self = (DvProviderOpenhomeOrgTestColorLight1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string friendlyName;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetName(aVersion, out friendlyName);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("FriendlyName", friendlyName);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoSetColor(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestColorLight1 self = (DvProviderOpenhomeOrgTestColorLight1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint red;
            uint green;
            uint blue;
            try
            {
                invocation.ReadStart();
                red = invocation.ReadUint("Red");
                green = invocation.ReadUint("Green");
                blue = invocation.ReadUint("Blue");
                invocation.ReadEnd();
                self.SetColor(aVersion, red, green, blue);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetColor(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestColorLight1 self = (DvProviderOpenhomeOrgTestColorLight1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint red;
            uint green;
            uint blue;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetColor(aVersion, out red, out green, out blue);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Red", red);
                invocation.WriteUint("Green", green);
                invocation.WriteUint("Blue", blue);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        private static int DoGetMaxColors(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestColorLight1 self = (DvProviderOpenhomeOrgTestColorLight1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint red;
            uint green;
            uint blue;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetMaxColors(aVersion, out red, out green, out blue);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("WARNING: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("         Only ActionError or PropertyUpdateError can be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Red", red);
                invocation.WriteUint("Green", green);
                invocation.WriteUint("Blue", blue);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ERROR: unexpected exception {0}(\"{1}\") thrown by {2}", e.GetType(), e.Message, e.TargetSite.Name);
                Console.WriteLine("       Only ActionError can be thrown by action response writer");
                System.Diagnostics.Process.GetCurrentProcess().Kill();
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderOpenhomeOrgTestColorLight1()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProvider();
                iHandle = IntPtr.Zero;
            }
            iGch.Free();
        }
    }
}

