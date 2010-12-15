using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using Zapp.Core;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkDebug2 : IDisposable
    {
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Debug:2 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkDebug2 : DvProvider, IDisposable, IDvProviderLinnCoUkDebug2
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateSetDebugLevel;
        private ActionDelegate iDelegateDebugLevel;
        private ActionDelegate iDelegateMemWrite;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkDebug2(DvDevice aDevice)
            : base(aDevice, "linn-co-uk", "Debug", 2)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Signal that the action SetDebugLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetDebugLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetDebugLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("SetDebugLevel");
            action.AddInputParameter(new ParameterUint("aDebugLevel"));
            iDelegateSetDebugLevel = new ActionDelegate(DoSetDebugLevel);
            EnableAction(action, iDelegateSetDebugLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action DebugLevel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoDebugLevel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionDebugLevel()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("DebugLevel");
            action.AddOutputParameter(new ParameterUint("aDebugLevel"));
            iDelegateDebugLevel = new ActionDelegate(DoDebugLevel);
            EnableAction(action, iDelegateDebugLevel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action MemWrite is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoMemWrite must be overridden if this is called.</remarks>
        protected unsafe void EnableActionMemWrite()
        {
            Zapp.Core.Action action = new Zapp.Core.Action("MemWrite");
            action.AddInputParameter(new ParameterUint("aMemAddress"));
            action.AddInputParameter(new ParameterBinary("aMemData"));
            iDelegateMemWrite = new ActionDelegate(DoMemWrite);
            EnableAction(action, iDelegateMemWrite, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// SetDebugLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetDebugLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetDebugLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDebugLevel"></param>
        protected virtual void SetDebugLevel(uint aVersion, uint aaDebugLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// DebugLevel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// DebugLevel action for the owning device.
        ///
        /// Must be implemented iff EnableActionDebugLevel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaDebugLevel"></param>
        protected virtual void DebugLevel(uint aVersion, out uint aaDebugLevel)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// MemWrite action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// MemWrite action for the owning device.
        ///
        /// Must be implemented iff EnableActionMemWrite was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaMemAddress"></param>
        /// <param name="aaMemData"></param>
        protected virtual void MemWrite(uint aVersion, uint aaMemAddress, string aaMemData)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetDebugLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDebug2 self = (DvProviderLinnCoUkDebug2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aDebugLevel = invocation.ReadUint("aDebugLevel");
            self.SetDebugLevel(aVersion, aDebugLevel);
            invocation.WriteStart();
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoDebugLevel(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDebug2 self = (DvProviderLinnCoUkDebug2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aDebugLevel;
            self.DebugLevel(aVersion, out aDebugLevel);
            invocation.WriteStart();
            invocation.WriteUint("aDebugLevel", aDebugLevel);
            invocation.WriteEnd();
            return 0;
        }

        private static unsafe int DoMemWrite(IntPtr aPtr, IntPtr aInvocation, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkDebug2 self = (DvProviderLinnCoUkDebug2)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint aMemAddress = invocation.ReadUint("aMemAddress");
            string aMemData = invocation.ReadBinary("aMemData");
            self.MemWrite(aVersion, aMemAddress, aMemData);
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

        ~DvProviderLinnCoUkDebug2()
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

