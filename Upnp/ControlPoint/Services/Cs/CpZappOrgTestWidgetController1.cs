using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyZappOrgTestWidgetController1 : ICpProxy, IDisposable
    {
        void SyncCreateWidget(string aWidgetUdn, uint aWidgetClass);
        void BeginCreateWidget(string aWidgetUdn, uint aWidgetClass, CpProxy.CallbackAsyncComplete aCallback);
        void EndCreateWidget(uint aAsyncHandle);
        void SyncRemoveWidget(string aWidgetUdn);
        void BeginRemoveWidget(string aWidgetUdn, CpProxy.CallbackAsyncComplete aCallback);
        void EndRemoveWidget(uint aAsyncHandle);
        void SyncSetWidgetRegister(string aWidgetUdn, uint aRegisterIndex, uint aRegisterValue);
        void BeginSetWidgetRegister(string aWidgetUdn, uint aRegisterIndex, uint aRegisterValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetWidgetRegister(uint aAsyncHandle);
        void SyncGetWidgetRegister(string aWidgetUdn, uint aRegisterIndex, out uint aRegisterValue);
        void BeginGetWidgetRegister(string aWidgetUdn, uint aRegisterIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetWidgetRegister(uint aAsyncHandle, out uint aRegisterValue);

    }

    public class CpProxyZappOrgTestWidgetController1 : CpProxy, IDisposable, ICpProxyZappOrgTestWidgetController1
    {
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern uint CpProxyZappOrgTestWidgetController1Create(uint aDeviceHandle);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern void CpProxyZappOrgTestWidgetController1Destroy(uint aHandle);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe void CpProxyZappOrgTestWidgetController1SyncCreateWidget(uint aHandle, char* aWidgetUdn, uint aWidgetClass);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe void CpProxyZappOrgTestWidgetController1BeginCreateWidget(uint aHandle, char* aWidgetUdn, uint aWidgetClass, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe int CpProxyZappOrgTestWidgetController1EndCreateWidget(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe void CpProxyZappOrgTestWidgetController1SyncRemoveWidget(uint aHandle, char* aWidgetUdn);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe void CpProxyZappOrgTestWidgetController1BeginRemoveWidget(uint aHandle, char* aWidgetUdn, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe int CpProxyZappOrgTestWidgetController1EndRemoveWidget(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe void CpProxyZappOrgTestWidgetController1SyncSetWidgetRegister(uint aHandle, char* aWidgetUdn, uint aRegisterIndex, uint aRegisterValue);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe void CpProxyZappOrgTestWidgetController1BeginSetWidgetRegister(uint aHandle, char* aWidgetUdn, uint aRegisterIndex, uint aRegisterValue, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe int CpProxyZappOrgTestWidgetController1EndSetWidgetRegister(uint aHandle, uint aAsync);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe void CpProxyZappOrgTestWidgetController1SyncGetWidgetRegister(uint aHandle, char* aWidgetUdn, uint aRegisterIndex, uint* aRegisterValue);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe void CpProxyZappOrgTestWidgetController1BeginGetWidgetRegister(uint aHandle, char* aWidgetUdn, uint aRegisterIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpZappOrgTestWidgetController1")]
        static extern unsafe int CpProxyZappOrgTestWidgetController1EndGetWidgetRegister(uint aHandle, uint aAsync, uint* aRegisterValue);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyZappOrgTestWidgetController1(CpDevice aDevice)
        {
            iHandle = CpProxyZappOrgTestWidgetController1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aWidgetClass"></param>
        public unsafe void SyncCreateWidget(string aWidgetUdn, uint aWidgetClass)
        {
			char* widgetUdn = (char*)Marshal.StringToHGlobalAnsi(aWidgetUdn);
			{
				CpProxyZappOrgTestWidgetController1SyncCreateWidget(iHandle, widgetUdn, aWidgetClass);
			}
			Marshal.FreeHGlobal((IntPtr)widgetUdn);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCreateWidget().</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aWidgetClass"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginCreateWidget(string aWidgetUdn, uint aWidgetClass, CallbackAsyncComplete aCallback)
        {
			char* widgetUdn = (char*)Marshal.StringToHGlobalAnsi(aWidgetUdn);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestWidgetController1BeginCreateWidget(iHandle, widgetUdn, aWidgetClass, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)widgetUdn);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndCreateWidget(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestWidgetController1EndCreateWidget(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetUdn"></param>
        public unsafe void SyncRemoveWidget(string aWidgetUdn)
        {
			char* widgetUdn = (char*)Marshal.StringToHGlobalAnsi(aWidgetUdn);
			{
				CpProxyZappOrgTestWidgetController1SyncRemoveWidget(iHandle, widgetUdn);
			}
			Marshal.FreeHGlobal((IntPtr)widgetUdn);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRemoveWidget().</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginRemoveWidget(string aWidgetUdn, CallbackAsyncComplete aCallback)
        {
			char* widgetUdn = (char*)Marshal.StringToHGlobalAnsi(aWidgetUdn);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestWidgetController1BeginRemoveWidget(iHandle, widgetUdn, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)widgetUdn);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndRemoveWidget(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestWidgetController1EndRemoveWidget(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        public unsafe void SyncSetWidgetRegister(string aWidgetUdn, uint aRegisterIndex, uint aRegisterValue)
        {
			char* widgetUdn = (char*)Marshal.StringToHGlobalAnsi(aWidgetUdn);
			{
				CpProxyZappOrgTestWidgetController1SyncSetWidgetRegister(iHandle, widgetUdn, aRegisterIndex, aRegisterValue);
			}
			Marshal.FreeHGlobal((IntPtr)widgetUdn);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetWidgetRegister().</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetWidgetRegister(string aWidgetUdn, uint aRegisterIndex, uint aRegisterValue, CallbackAsyncComplete aCallback)
        {
			char* widgetUdn = (char*)Marshal.StringToHGlobalAnsi(aWidgetUdn);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestWidgetController1BeginSetWidgetRegister(iHandle, widgetUdn, aRegisterIndex, aRegisterValue, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)widgetUdn);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetWidgetRegister(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyZappOrgTestWidgetController1EndSetWidgetRegister(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aRegisterValue"></param>
        public unsafe void SyncGetWidgetRegister(string aWidgetUdn, uint aRegisterIndex, out uint aRegisterValue)
        {
			char* widgetUdn = (char*)Marshal.StringToHGlobalAnsi(aWidgetUdn);
			fixed (uint* registerValue = &aRegisterValue)
			{
				CpProxyZappOrgTestWidgetController1SyncGetWidgetRegister(iHandle, widgetUdn, aRegisterIndex, registerValue);
			}
			Marshal.FreeHGlobal((IntPtr)widgetUdn);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetWidgetRegister().</remarks>
        /// <param name="aWidgetUdn"></param>
        /// <param name="aRegisterIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginGetWidgetRegister(string aWidgetUdn, uint aRegisterIndex, CallbackAsyncComplete aCallback)
        {
			char* widgetUdn = (char*)Marshal.StringToHGlobalAnsi(aWidgetUdn);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyZappOrgTestWidgetController1BeginGetWidgetRegister(iHandle, widgetUdn, aRegisterIndex, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)widgetUdn);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRegisterValue"></param>
        public unsafe void EndGetWidgetRegister(uint aAsyncHandle, out uint aRegisterValue)
        {
			fixed (uint* registerValue = &aRegisterValue)
			{
				if (0 != CpProxyZappOrgTestWidgetController1EndGetWidgetRegister(iHandle, aAsyncHandle, registerValue))
				{
					throw(new ProxyError());
				}
			}
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyZappOrgTestWidgetController1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
        {
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                CpProxyZappOrgTestWidgetController1Destroy(iHandle);
                iHandle = 0;
            }
            iGch.Free();
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
            else
            {
                DisposeProxy();
            }
        }
    }
}

