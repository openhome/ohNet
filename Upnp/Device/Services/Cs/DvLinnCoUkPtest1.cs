using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkPtest1 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Ptest:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkPtest1 : DvProvider, IDisposable, IDvProviderLinnCoUkPtest1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateTestComPort;
        private ActionDelegate iDelegateLedsOn;
        private ActionDelegate iDelegateLedsOff;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkPtest1(DvDevice aDevice)
            : base(aDevice, "linn.co.uk", "Ptest", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action TestComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// TestComPort must be overridden if this is called.</remarks>
        protected void EnableActionTestComPort()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("TestComPort");
            action.AddInputParameter(new ParameterUint("aPort"));
            action.AddOutputParameter(new ParameterBool("aResult"));
            iDelegateTestComPort = new ActionDelegate(DoTestComPort);
            EnableAction(action, iDelegateTestComPort, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action LedsOn is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// LedsOn must be overridden if this is called.</remarks>
        protected void EnableActionLedsOn()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("LedsOn");
            iDelegateLedsOn = new ActionDelegate(DoLedsOn);
            EnableAction(action, iDelegateLedsOn, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action LedsOff is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// LedsOff must be overridden if this is called.</remarks>
        protected void EnableActionLedsOff()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("LedsOff");
            iDelegateLedsOff = new ActionDelegate(DoLedsOff);
            EnableAction(action, iDelegateLedsOff, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// TestComPort action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TestComPort action for the owning device.
        ///
        /// Must be implemented iff EnableActionTestComPort was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaPort"></param>
        /// <param name="aaResult"></param>
        protected virtual void TestComPort(uint aVersion, uint aaPort, out bool aaResult)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// LedsOn action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// LedsOn action for the owning device.
        ///
        /// Must be implemented iff EnableActionLedsOn was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void LedsOn(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// LedsOff action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// LedsOff action for the owning device.
        ///
        /// Must be implemented iff EnableActionLedsOff was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void LedsOff(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        private static int DoTestComPort(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aPort;
            bool aResult;
            try
            {
                invocation.ReadStart();
                aPort = invocation.ReadUint("aPort");
                invocation.ReadEnd();
                self.TestComPort(aVersion, aPort, out aResult);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("aResult", aResult);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            return 0;
        }

        private static int DoLedsOn(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.LedsOn(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        private static int DoLedsOff(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.LedsOff(aVersion);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML");
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML");
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
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkPtest1()
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

