using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestWidget1 : ICpProxy, IDisposable
    {
        void SyncSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue);
        void BeginSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetReadWriteRegister(IntPtr aAsyncHandle);
        void SyncGetWidgetClass(out uint aWidgetClass);
        void BeginGetWidgetClass(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetWidgetClass(IntPtr aAsyncHandle, out uint aWidgetClass);
        void SetPropertyReadWriteRegister0Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister0Changed);
        uint PropertyReadWriteRegister0();
        void SetPropertyReadWriteRegister1Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister1Changed);
        uint PropertyReadWriteRegister1();
        void SetPropertyReadWriteRegister2Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister2Changed);
        uint PropertyReadWriteRegister2();
        void SetPropertyReadWriteRegister3Changed(CpProxy.CallbackPropertyChanged aReadWriteRegister3Changed);
        uint PropertyReadWriteRegister3();
        void SetPropertyReadOnlyRegister4Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister4Changed);
        uint PropertyReadOnlyRegister4();
        void SetPropertyReadOnlyRegister5Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister5Changed);
        uint PropertyReadOnlyRegister5();
        void SetPropertyReadOnlyRegister6Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister6Changed);
        uint PropertyReadOnlyRegister6();
        void SetPropertyReadOnlyRegister7Changed(CpProxy.CallbackPropertyChanged aReadOnlyRegister7Changed);
        uint PropertyReadOnlyRegister7();
    }

    internal class SyncSetReadWriteRegisterZappOrgTestWidget1 : SyncProxyAction
    {
        private CpProxyZappOrgTestWidget1 iService;

        public SyncSetReadWriteRegisterZappOrgTestWidget1(CpProxyZappOrgTestWidget1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetReadWriteRegister(aAsyncHandle);
        }
    };

    internal class SyncGetWidgetClassZappOrgTestWidget1 : SyncProxyAction
    {
        private CpProxyZappOrgTestWidget1 iService;
        private uint iWidgetClass;

        public SyncGetWidgetClassZappOrgTestWidget1(CpProxyZappOrgTestWidget1 aProxy)
        {
            iService = aProxy;
        }
        public uint WidgetClass()
        {
            return iWidgetClass;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetWidgetClass(aAsyncHandle, out iWidgetClass);
        }
    };

    /// <summary>
    /// Proxy for the zapp.org:TestWidget:1 UPnP service
    /// </summary>
    public class CpProxyZappOrgTestWidget1 : CpProxy, IDisposable, ICpProxyZappOrgTestWidget1
    {
        private Zapp.Core.Action iActionSetReadWriteRegister;
        private Zapp.Core.Action iActionGetWidgetClass;
        private PropertyUint iReadWriteRegister0;
        private PropertyUint iReadWriteRegister1;
        private PropertyUint iReadWriteRegister2;
        private PropertyUint iReadWriteRegister3;
        private PropertyUint iReadOnlyRegister4;
        private PropertyUint iReadOnlyRegister5;
        private PropertyUint iReadOnlyRegister6;
        private PropertyUint iReadOnlyRegister7;
        private CallbackPropertyChanged iReadWriteRegister0Changed;
        private CallbackPropertyChanged iReadWriteRegister1Changed;
        private CallbackPropertyChanged iReadWriteRegister2Changed;
        private CallbackPropertyChanged iReadWriteRegister3Changed;
        private CallbackPropertyChanged iReadOnlyRegister4Changed;
        private CallbackPropertyChanged iReadOnlyRegister5Changed;
        private CallbackPropertyChanged iReadOnlyRegister6Changed;
        private CallbackPropertyChanged iReadOnlyRegister7Changed;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestWidget1(CpDevice aDevice)
            : base("zapp-org", "TestWidget", 1, aDevice)
        {
            Zapp.Core.Parameter param;

            iActionSetReadWriteRegister = new Zapp.Core.Action("SetReadWriteRegister");
            param = new ParameterUint("RegisterIndex");
            iActionSetReadWriteRegister.AddInputParameter(param);
            param = new ParameterUint("RegisterValue");
            iActionSetReadWriteRegister.AddInputParameter(param);

            iActionGetWidgetClass = new Zapp.Core.Action("GetWidgetClass");
            param = new ParameterUint("WidgetClass");
            iActionGetWidgetClass.AddOutputParameter(param);

            iReadWriteRegister0 = new PropertyUint("ReadWriteRegister0", ReadWriteRegister0PropertyChanged);
            AddProperty(iReadWriteRegister0);
            iReadWriteRegister1 = new PropertyUint("ReadWriteRegister1", ReadWriteRegister1PropertyChanged);
            AddProperty(iReadWriteRegister1);
            iReadWriteRegister2 = new PropertyUint("ReadWriteRegister2", ReadWriteRegister2PropertyChanged);
            AddProperty(iReadWriteRegister2);
            iReadWriteRegister3 = new PropertyUint("ReadWriteRegister3", ReadWriteRegister3PropertyChanged);
            AddProperty(iReadWriteRegister3);
            iReadOnlyRegister4 = new PropertyUint("ReadOnlyRegister4", ReadOnlyRegister4PropertyChanged);
            AddProperty(iReadOnlyRegister4);
            iReadOnlyRegister5 = new PropertyUint("ReadOnlyRegister5", ReadOnlyRegister5PropertyChanged);
            AddProperty(iReadOnlyRegister5);
            iReadOnlyRegister6 = new PropertyUint("ReadOnlyRegister6", ReadOnlyRegister6PropertyChanged);
            AddProperty(iReadOnlyRegister6);
            iReadOnlyRegister7 = new PropertyUint("ReadOnlyRegister7", ReadOnlyRegister7PropertyChanged);
            AddProperty(iReadOnlyRegister7);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        public void SyncSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue)
        {
            SyncSetReadWriteRegisterZappOrgTestWidget1 sync = new SyncSetReadWriteRegisterZappOrgTestWidget1(this);
            BeginSetReadWriteRegister(aRegisterIndex, aRegisterValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetReadWriteRegister().</remarks>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetReadWriteRegister(uint aRegisterIndex, uint aRegisterValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetReadWriteRegister, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetReadWriteRegister.InputParameter(inIndex++), aRegisterIndex));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetReadWriteRegister.InputParameter(inIndex++), aRegisterValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetReadWriteRegister(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetClass"></param>
        public void SyncGetWidgetClass(out uint aWidgetClass)
        {
            SyncGetWidgetClassZappOrgTestWidget1 sync = new SyncGetWidgetClassZappOrgTestWidget1(this);
            BeginGetWidgetClass(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aWidgetClass = sync.WidgetClass();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetWidgetClass().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetWidgetClass(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetWidgetClass, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetWidgetClass.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aWidgetClass"></param>
        public void EndGetWidgetClass(IntPtr aAsyncHandle, out uint aWidgetClass)
        {
            uint index = 0;
            aWidgetClass = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the ReadWriteRegister0 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadWriteRegister0Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadWriteRegister0Changed(CallbackPropertyChanged aReadWriteRegister0Changed)
        {
            lock (this)
            {
                iReadWriteRegister0Changed = aReadWriteRegister0Changed;
            }
        }

        private void ReadWriteRegister0PropertyChanged()
        {
            lock (this)
            {
                if (iReadWriteRegister0Changed != null)
                {
                    iReadWriteRegister0Changed();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ReadWriteRegister1 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadWriteRegister1Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadWriteRegister1Changed(CallbackPropertyChanged aReadWriteRegister1Changed)
        {
            lock (this)
            {
                iReadWriteRegister1Changed = aReadWriteRegister1Changed;
            }
        }

        private void ReadWriteRegister1PropertyChanged()
        {
            lock (this)
            {
                if (iReadWriteRegister1Changed != null)
                {
                    iReadWriteRegister1Changed();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ReadWriteRegister2 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadWriteRegister2Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadWriteRegister2Changed(CallbackPropertyChanged aReadWriteRegister2Changed)
        {
            lock (this)
            {
                iReadWriteRegister2Changed = aReadWriteRegister2Changed;
            }
        }

        private void ReadWriteRegister2PropertyChanged()
        {
            lock (this)
            {
                if (iReadWriteRegister2Changed != null)
                {
                    iReadWriteRegister2Changed();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ReadWriteRegister3 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadWriteRegister3Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadWriteRegister3Changed(CallbackPropertyChanged aReadWriteRegister3Changed)
        {
            lock (this)
            {
                iReadWriteRegister3Changed = aReadWriteRegister3Changed;
            }
        }

        private void ReadWriteRegister3PropertyChanged()
        {
            lock (this)
            {
                if (iReadWriteRegister3Changed != null)
                {
                    iReadWriteRegister3Changed();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ReadOnlyRegister4 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadOnlyRegister4Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadOnlyRegister4Changed(CallbackPropertyChanged aReadOnlyRegister4Changed)
        {
            lock (this)
            {
                iReadOnlyRegister4Changed = aReadOnlyRegister4Changed;
            }
        }

        private void ReadOnlyRegister4PropertyChanged()
        {
            lock (this)
            {
                if (iReadOnlyRegister4Changed != null)
                {
                    iReadOnlyRegister4Changed();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ReadOnlyRegister5 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadOnlyRegister5Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadOnlyRegister5Changed(CallbackPropertyChanged aReadOnlyRegister5Changed)
        {
            lock (this)
            {
                iReadOnlyRegister5Changed = aReadOnlyRegister5Changed;
            }
        }

        private void ReadOnlyRegister5PropertyChanged()
        {
            lock (this)
            {
                if (iReadOnlyRegister5Changed != null)
                {
                    iReadOnlyRegister5Changed();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ReadOnlyRegister6 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadOnlyRegister6Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadOnlyRegister6Changed(CallbackPropertyChanged aReadOnlyRegister6Changed)
        {
            lock (this)
            {
                iReadOnlyRegister6Changed = aReadOnlyRegister6Changed;
            }
        }

        private void ReadOnlyRegister6PropertyChanged()
        {
            lock (this)
            {
                if (iReadOnlyRegister6Changed != null)
                {
                    iReadOnlyRegister6Changed();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ReadOnlyRegister7 state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyZappOrgTestWidget1 instance will not overlap.</remarks>
        /// <param name="aReadOnlyRegister7Changed">The delegate to run when the state variable changes</param>
        public void SetPropertyReadOnlyRegister7Changed(CallbackPropertyChanged aReadOnlyRegister7Changed)
        {
            lock (this)
            {
                iReadOnlyRegister7Changed = aReadOnlyRegister7Changed;
            }
        }

        private void ReadOnlyRegister7PropertyChanged()
        {
            lock (this)
            {
                if (iReadOnlyRegister7Changed != null)
                {
                    iReadOnlyRegister7Changed();
                }
            }
        }

        /// <summary>
        /// Query the value of the ReadWriteRegister0 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadWriteRegister0">Will be set to the value of the property</param>
        public uint PropertyReadWriteRegister0()
        {
            return iReadWriteRegister0.Value();
        }

        /// <summary>
        /// Query the value of the ReadWriteRegister1 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadWriteRegister1">Will be set to the value of the property</param>
        public uint PropertyReadWriteRegister1()
        {
            return iReadWriteRegister1.Value();
        }

        /// <summary>
        /// Query the value of the ReadWriteRegister2 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadWriteRegister2">Will be set to the value of the property</param>
        public uint PropertyReadWriteRegister2()
        {
            return iReadWriteRegister2.Value();
        }

        /// <summary>
        /// Query the value of the ReadWriteRegister3 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadWriteRegister3">Will be set to the value of the property</param>
        public uint PropertyReadWriteRegister3()
        {
            return iReadWriteRegister3.Value();
        }

        /// <summary>
        /// Query the value of the ReadOnlyRegister4 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadOnlyRegister4">Will be set to the value of the property</param>
        public uint PropertyReadOnlyRegister4()
        {
            return iReadOnlyRegister4.Value();
        }

        /// <summary>
        /// Query the value of the ReadOnlyRegister5 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadOnlyRegister5">Will be set to the value of the property</param>
        public uint PropertyReadOnlyRegister5()
        {
            return iReadOnlyRegister5.Value();
        }

        /// <summary>
        /// Query the value of the ReadOnlyRegister6 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadOnlyRegister6">Will be set to the value of the property</param>
        public uint PropertyReadOnlyRegister6()
        {
            return iReadOnlyRegister6.Value();
        }

        /// <summary>
        /// Query the value of the ReadOnlyRegister7 property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aReadOnlyRegister7">Will be set to the value of the property</param>
        public uint PropertyReadOnlyRegister7()
        {
            return iReadOnlyRegister7.Value();
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestWidget1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                DisposeProxy();
                iHandle = IntPtr.Zero;
                iActionSetReadWriteRegister.Dispose();
                iActionGetWidgetClass.Dispose();
                iReadWriteRegister0.Dispose();
                iReadWriteRegister1.Dispose();
                iReadWriteRegister2.Dispose();
                iReadWriteRegister3.Dispose();
                iReadOnlyRegister4.Dispose();
                iReadOnlyRegister5.Dispose();
                iReadOnlyRegister6.Dispose();
                iReadOnlyRegister7.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

