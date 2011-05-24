using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderOpenhomeOrgTestDimmableLight1 : IDisposable
    {

        /// <summary>
        /// Set the value of the A_ARG_Level property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyA_ARG_Level(uint aValue);

        /// <summary>
        /// Get a copy of the value of the A_ARG_Level property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertyA_ARG_Level();
        
    }
    /// <summary>
    /// Provider for the openhome.org:TestDimmableLight:1 UPnP service
    /// </summary>
    public class DvProviderOpenhomeOrgTestDimmableLight1 : DvProvider, IDisposable, IDvProviderOpenhomeOrgTestDimmableLight1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateGetLevel;
        private ActionDelegate iDelegateSetLevel;
        private PropertyUint iPropertyA_ARG_Level;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderOpenhomeOrgTestDimmableLight1(DvDevice aDevice)
            : base(aDevice, "openhome.org", "TestDimmableLight", 1)
        {
            iGch = GCHandle.Alloc(this);
            iPropertyA_ARG_Level = new PropertyUint(new ParameterUint("A_ARG_Level"));
            AddProperty(iPropertyA_ARG_Level);
        }

        /// <summary>
        /// Set the value of the A_ARG_Level property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyA_ARG_Level(uint aValue)
        {
            return SetPropertyUint(iPropertyA_ARG_Level, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the A_ARG_Level property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertyA_ARG_Level()
        {
            return iPropertyA_ARG_Level.Value();
        }

        /// <summary>
        /// Signal that the action GetLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// GetLevel must be overridden if this is called.</remarks>
        protected void EnableActionGetLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("GetLevel");
            action.AddOutputParameter(new ParameterRelated("Level", iPropertyA_ARG_Level));
            iDelegateGetLevel = new ActionDelegate(DoGetLevel);
            EnableAction(action, iDelegateGetLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetLevel must be overridden if this is called.</remarks>
        protected void EnableActionSetLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetLevel");
            action.AddInputParameter(new ParameterRelated("Level", iPropertyA_ARG_Level));
            iDelegateSetLevel = new ActionDelegate(DoSetLevel);
            EnableAction(action, iDelegateSetLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// GetLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// GetLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionGetLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aLevel"></param>
        protected virtual void GetLevel(uint aVersion, out uint aLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aLevel"></param>
        protected virtual void SetLevel(uint aVersion, uint aLevel)
        {
            throw (new ActionDisabledError());
        }

        private static int DoGetLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestDimmableLight1 self = (DvProviderOpenhomeOrgTestDimmableLight1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint level;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.GetLevel(aVersion, out level);
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
                invocation.WriteUint("Level", level);
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

        private static int DoSetLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderOpenhomeOrgTestDimmableLight1 self = (DvProviderOpenhomeOrgTestDimmableLight1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint level;
            try
            {
                invocation.ReadStart();
                level = invocation.ReadUint("Level");
                invocation.ReadEnd();
                self.SetLevel(aVersion, level);
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

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderOpenhomeOrgTestDimmableLight1()
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

