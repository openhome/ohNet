using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkMediaTime1 : IDisposable
    {

        /// <summary>
        /// Set the value of the Seconds property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySeconds(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Seconds property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        uint PropertySeconds();
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:MediaTime:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkMediaTime1 : DvProvider, IDisposable, IDvProviderLinnCoUkMediaTime1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSeconds;
        private PropertyUint iPropertySeconds;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkMediaTime1(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "MediaTime", 1)
        {
            iGch = GCHandle.Alloc(this);
            iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"));
            AddProperty(iPropertySeconds);
        }

        /// <summary>
        /// Set the value of the Seconds property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySeconds(uint aValue)
        {
            return SetPropertyUint(iPropertySeconds, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Seconds property
        /// </summary>
        /// <returns>The value of the property</returns>
        public uint PropertySeconds()
        {
            return iPropertySeconds.Value();
        }

        /// <summary>
        /// Signal that the action Seconds is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Seconds must be overridden if this is called.</remarks>
        protected void EnableActionSeconds()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("Seconds");
            action.AddOutputParameter(new ParameterRelated("aSeconds", iPropertySeconds));
            iDelegateSeconds = new ActionDelegate(DoSeconds);
            EnableAction(action, iDelegateSeconds, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Seconds action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Seconds action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeconds was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSeconds"></param>
        protected virtual void Seconds(uint aVersion, out uint aaSeconds)
        {
            throw (new ActionDisabledError());
        }

        private static int DoSeconds(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkMediaTime1 self = (DvProviderLinnCoUkMediaTime1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aSeconds;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Seconds(aVersion, out aSeconds);
            }
            catch (ActionError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            catch (ActionDisabledError)
            {
                invocation.ReportError(501, "Action not implemented"); ;
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, "Invalid XML"); ;
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("aSeconds", aSeconds);
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

        ~DvProviderLinnCoUkMediaTime1()
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

