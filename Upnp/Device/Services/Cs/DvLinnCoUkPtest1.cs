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
            : base(aDevice, "linn-co-uk", "Ptest", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action TestComPort is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTestComPort must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTestComPort()
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
        /// DoLedsOn must be overridden if this is called.</remarks>
        protected unsafe void EnableActionLedsOn()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("LedsOn");
            iDelegateLedsOn = new ActionDelegate(DoLedsOn);
            EnableAction(action, iDelegateLedsOn, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action LedsOff is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoLedsOff must be overridden if this is called.</remarks>
        protected unsafe void EnableActionLedsOff()
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

        private static unsafe int DoTestComPort(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aPort = invocation.ReadUint("aPort");
            bool aResult;
            self.TestComPort(aVersion, aPort, out aResult);
            invocation.WriteStart();
            invocation.WriteBool("aResult", aResult);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoLedsOn(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            self.LedsOn(aVersion);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoLedsOff(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkPtest1 self = (DvProviderLinnCoUkPtest1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            self.LedsOff(aVersion);
            invocation.WriteStart();
            invocation.WriteEnd();
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

