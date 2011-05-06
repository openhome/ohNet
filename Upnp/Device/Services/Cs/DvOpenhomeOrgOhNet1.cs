using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderOpenhomeOrgOhNet1 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the openhome.org:OhNet:1 UPnP service
    /// </summary>
    public class DvProviderOpenhomeOrgOhNet1 : DvProvider, IDisposable, IDvProviderOpenhomeOrgOhNet1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateGetWebSocketPort;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderOpenhomeOrgOhNet1(DvDevice aDevice)
            : base(aDevice, "openhome.org", "OhNet", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action GetWebSocketPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetWebSocketPort must be overridden if this is called.</remarks>
        protected void EnableActionGetWebSocketPort()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetWebSocketPort");
            action.AddOutputParameter(new ParameterUint("Port"));
            iDelegateGetWebSocketPort = new ActionDelegate(DoGetWebSocketPort);
            EnableAction(action, iDelegateGetWebSocketPort, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// GetWebSocketPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetWebSocketPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetWebSocketPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aPort"></param>
        protected virtual void GetWebSocketPort(uint aVersion, out uint aPort)
        {
            throw (new ActionDisabledError());
        }

        private static int DoGetWebSocketPort(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgOhNet1 self = (DvProviderOpenhomeOrgOhNet1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint port;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetWebSocketPort(aVersion, out port);
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
                invocation.WriteUint("Port", port);
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

        ~DvProviderOpenhomeOrgOhNet1()
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

