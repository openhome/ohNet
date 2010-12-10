using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkVolkano1 : ICpProxy, IDisposable
    {
        void SyncReboot();
        void BeginReboot(CpProxy.CallbackAsyncComplete aCallback);
        void EndReboot(IntPtr aAsyncHandle);
        void SyncBootMode(out string aaMode);
        void BeginBootMode(CpProxy.CallbackAsyncComplete aCallback);
        void EndBootMode(IntPtr aAsyncHandle, out string aaMode);
        void SyncSetBootMode(string aaMode);
        void BeginSetBootMode(string aaMode, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBootMode(IntPtr aAsyncHandle);
        void SyncBspType(out string aaBspType);
        void BeginBspType(CpProxy.CallbackAsyncComplete aCallback);
        void EndBspType(IntPtr aAsyncHandle, out string aaBspType);
        void SyncUglyName(out string aaUglyName);
        void BeginUglyName(CpProxy.CallbackAsyncComplete aCallback);
        void EndUglyName(IntPtr aAsyncHandle, out string aaUglyName);
        void SyncMacAddress(out string aaMacAddress);
        void BeginMacAddress(CpProxy.CallbackAsyncComplete aCallback);
        void EndMacAddress(IntPtr aAsyncHandle, out string aaMacAddress);
        void SyncProductId(out string aaProductNumber);
        void BeginProductId(CpProxy.CallbackAsyncComplete aCallback);
        void EndProductId(IntPtr aAsyncHandle, out string aaProductNumber);
        void SyncBoardId(uint aaIndex, out string aaBoardNumber);
        void BeginBoardId(uint aaIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndBoardId(IntPtr aAsyncHandle, out string aaBoardNumber);
        void SyncBoardType(uint aaIndex, out string aaBoardNumber);
        void BeginBoardType(uint aaIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndBoardType(IntPtr aAsyncHandle, out string aaBoardNumber);
        void SyncMaxBoards(out uint aaMaxBoards);
        void BeginMaxBoards(CpProxy.CallbackAsyncComplete aCallback);
        void EndMaxBoards(IntPtr aAsyncHandle, out uint aaMaxBoards);
        void SyncSoftwareVersion(out string aaSoftwareVersion);
        void BeginSoftwareVersion(CpProxy.CallbackAsyncComplete aCallback);
        void EndSoftwareVersion(IntPtr aAsyncHandle, out string aaSoftwareVersion);

    }

    /// <summary>
    /// Proxy for the linn.co.uk:Volkano:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkVolkano1 : CpProxy, IDisposable, ICpProxyLinnCoUkVolkano1
    {
        [DllImport("CpLinnCoUkVolkano1")]
        static extern IntPtr CpProxyLinnCoUkVolkano1Create(IntPtr aDeviceHandle);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern void CpProxyLinnCoUkVolkano1Destroy(IntPtr aHandle);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncReboot(IntPtr aHandle);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginReboot(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndReboot(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncBootMode(IntPtr aHandle, char** aaMode);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginBootMode(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndBootMode(IntPtr aHandle, IntPtr aAsync, char** aaMode);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncSetBootMode(IntPtr aHandle, char* aaMode);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginSetBootMode(IntPtr aHandle, char* aaMode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndSetBootMode(IntPtr aHandle, IntPtr aAsync);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncBspType(IntPtr aHandle, char** aaBspType);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginBspType(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndBspType(IntPtr aHandle, IntPtr aAsync, char** aaBspType);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncUglyName(IntPtr aHandle, char** aaUglyName);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginUglyName(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndUglyName(IntPtr aHandle, IntPtr aAsync, char** aaUglyName);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncMacAddress(IntPtr aHandle, char** aaMacAddress);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginMacAddress(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndMacAddress(IntPtr aHandle, IntPtr aAsync, char** aaMacAddress);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncProductId(IntPtr aHandle, char** aaProductNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginProductId(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndProductId(IntPtr aHandle, IntPtr aAsync, char** aaProductNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncBoardId(IntPtr aHandle, uint aaIndex, char** aaBoardNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginBoardId(IntPtr aHandle, uint aaIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndBoardId(IntPtr aHandle, IntPtr aAsync, char** aaBoardNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncBoardType(IntPtr aHandle, uint aaIndex, char** aaBoardNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginBoardType(IntPtr aHandle, uint aaIndex, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndBoardType(IntPtr aHandle, IntPtr aAsync, char** aaBoardNumber);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncMaxBoards(IntPtr aHandle, uint* aaMaxBoards);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginMaxBoards(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndMaxBoards(IntPtr aHandle, IntPtr aAsync, uint* aaMaxBoards);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1SyncSoftwareVersion(IntPtr aHandle, char** aaSoftwareVersion);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe void CpProxyLinnCoUkVolkano1BeginSoftwareVersion(IntPtr aHandle, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpLinnCoUkVolkano1")]
        static extern unsafe int CpProxyLinnCoUkVolkano1EndSoftwareVersion(IntPtr aHandle, IntPtr aAsync, char** aaSoftwareVersion);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkVolkano1(CpDevice aDevice)
        {
            iHandle = CpProxyLinnCoUkVolkano1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public unsafe void SyncReboot()
        {
            {
                CpProxyLinnCoUkVolkano1SyncReboot(iHandle);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndReboot().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginReboot(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginReboot(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndReboot(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkVolkano1EndReboot(iHandle, aAsyncHandle))
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
        /// <param name="aaMode"></param>
        public unsafe void SyncBootMode(out string aaMode)
        {
            char* aMode;
            {
                CpProxyLinnCoUkVolkano1SyncBootMode(iHandle, &aMode);
            }
            aaMode = Marshal.PtrToStringAnsi((IntPtr)aMode);
            ZappFree(aMode);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBootMode().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginBootMode(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginBootMode(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMode"></param>
        public unsafe void EndBootMode(IntPtr aAsyncHandle, out string aaMode)
        {
            char* aMode;
            {
                if (0 != CpProxyLinnCoUkVolkano1EndBootMode(iHandle, aAsyncHandle, &aMode))
                {
                    throw(new ProxyError());
                }
            }
            aaMode = Marshal.PtrToStringAnsi((IntPtr)aMode);
            ZappFree(aMode);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaMode"></param>
        public unsafe void SyncSetBootMode(string aaMode)
        {
            char* aMode = (char*)Marshal.StringToHGlobalAnsi(aaMode);
            {
                CpProxyLinnCoUkVolkano1SyncSetBootMode(iHandle, aMode);
            }
            Marshal.FreeHGlobal((IntPtr)aMode);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBootMode().</remarks>
        /// <param name="aaMode"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSetBootMode(string aaMode, CallbackAsyncComplete aCallback)
        {
            char* aMode = (char*)Marshal.StringToHGlobalAnsi(aaMode);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginSetBootMode(iHandle, aMode, iActionComplete, ptr);
            Marshal.FreeHGlobal((IntPtr)aMode);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public unsafe void EndSetBootMode(IntPtr aAsyncHandle)
        {
            {
                if (0 != CpProxyLinnCoUkVolkano1EndSetBootMode(iHandle, aAsyncHandle))
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
        /// <param name="aaBspType"></param>
        public unsafe void SyncBspType(out string aaBspType)
        {
            char* aBspType;
            {
                CpProxyLinnCoUkVolkano1SyncBspType(iHandle, &aBspType);
            }
            aaBspType = Marshal.PtrToStringAnsi((IntPtr)aBspType);
            ZappFree(aBspType);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBspType().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginBspType(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginBspType(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBspType"></param>
        public unsafe void EndBspType(IntPtr aAsyncHandle, out string aaBspType)
        {
            char* aBspType;
            {
                if (0 != CpProxyLinnCoUkVolkano1EndBspType(iHandle, aAsyncHandle, &aBspType))
                {
                    throw(new ProxyError());
                }
            }
            aaBspType = Marshal.PtrToStringAnsi((IntPtr)aBspType);
            ZappFree(aBspType);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaUglyName"></param>
        public unsafe void SyncUglyName(out string aaUglyName)
        {
            char* aUglyName;
            {
                CpProxyLinnCoUkVolkano1SyncUglyName(iHandle, &aUglyName);
            }
            aaUglyName = Marshal.PtrToStringAnsi((IntPtr)aUglyName);
            ZappFree(aUglyName);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndUglyName().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginUglyName(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginUglyName(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUglyName"></param>
        public unsafe void EndUglyName(IntPtr aAsyncHandle, out string aaUglyName)
        {
            char* aUglyName;
            {
                if (0 != CpProxyLinnCoUkVolkano1EndUglyName(iHandle, aAsyncHandle, &aUglyName))
                {
                    throw(new ProxyError());
                }
            }
            aaUglyName = Marshal.PtrToStringAnsi((IntPtr)aUglyName);
            ZappFree(aUglyName);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaMacAddress"></param>
        public unsafe void SyncMacAddress(out string aaMacAddress)
        {
            char* aMacAddress;
            {
                CpProxyLinnCoUkVolkano1SyncMacAddress(iHandle, &aMacAddress);
            }
            aaMacAddress = Marshal.PtrToStringAnsi((IntPtr)aMacAddress);
            ZappFree(aMacAddress);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMacAddress().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginMacAddress(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginMacAddress(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMacAddress"></param>
        public unsafe void EndMacAddress(IntPtr aAsyncHandle, out string aaMacAddress)
        {
            char* aMacAddress;
            {
                if (0 != CpProxyLinnCoUkVolkano1EndMacAddress(iHandle, aAsyncHandle, &aMacAddress))
                {
                    throw(new ProxyError());
                }
            }
            aaMacAddress = Marshal.PtrToStringAnsi((IntPtr)aMacAddress);
            ZappFree(aMacAddress);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaProductNumber"></param>
        public unsafe void SyncProductId(out string aaProductNumber)
        {
            char* aProductNumber;
            {
                CpProxyLinnCoUkVolkano1SyncProductId(iHandle, &aProductNumber);
            }
            aaProductNumber = Marshal.PtrToStringAnsi((IntPtr)aProductNumber);
            ZappFree(aProductNumber);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndProductId().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginProductId(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginProductId(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaProductNumber"></param>
        public unsafe void EndProductId(IntPtr aAsyncHandle, out string aaProductNumber)
        {
            char* aProductNumber;
            {
                if (0 != CpProxyLinnCoUkVolkano1EndProductId(iHandle, aAsyncHandle, &aProductNumber))
                {
                    throw(new ProxyError());
                }
            }
            aaProductNumber = Marshal.PtrToStringAnsi((IntPtr)aProductNumber);
            ZappFree(aProductNumber);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaBoardNumber"></param>
        public unsafe void SyncBoardId(uint aaIndex, out string aaBoardNumber)
        {
            char* aBoardNumber;
            {
                CpProxyLinnCoUkVolkano1SyncBoardId(iHandle, aaIndex, &aBoardNumber);
            }
            aaBoardNumber = Marshal.PtrToStringAnsi((IntPtr)aBoardNumber);
            ZappFree(aBoardNumber);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBoardId().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginBoardId(uint aaIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginBoardId(iHandle, aaIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBoardNumber"></param>
        public unsafe void EndBoardId(IntPtr aAsyncHandle, out string aaBoardNumber)
        {
            char* aBoardNumber;
            {
                if (0 != CpProxyLinnCoUkVolkano1EndBoardId(iHandle, aAsyncHandle, &aBoardNumber))
                {
                    throw(new ProxyError());
                }
            }
            aaBoardNumber = Marshal.PtrToStringAnsi((IntPtr)aBoardNumber);
            ZappFree(aBoardNumber);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aaBoardNumber"></param>
        public unsafe void SyncBoardType(uint aaIndex, out string aaBoardNumber)
        {
            char* aBoardNumber;
            {
                CpProxyLinnCoUkVolkano1SyncBoardType(iHandle, aaIndex, &aBoardNumber);
            }
            aaBoardNumber = Marshal.PtrToStringAnsi((IntPtr)aBoardNumber);
            ZappFree(aBoardNumber);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBoardType().</remarks>
        /// <param name="aaIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginBoardType(uint aaIndex, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginBoardType(iHandle, aaIndex, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaBoardNumber"></param>
        public unsafe void EndBoardType(IntPtr aAsyncHandle, out string aaBoardNumber)
        {
            char* aBoardNumber;
            {
                if (0 != CpProxyLinnCoUkVolkano1EndBoardType(iHandle, aAsyncHandle, &aBoardNumber))
                {
                    throw(new ProxyError());
                }
            }
            aaBoardNumber = Marshal.PtrToStringAnsi((IntPtr)aBoardNumber);
            ZappFree(aBoardNumber);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaMaxBoards"></param>
        public unsafe void SyncMaxBoards(out uint aaMaxBoards)
        {
            fixed (uint* aMaxBoards = &aaMaxBoards)
            {
                CpProxyLinnCoUkVolkano1SyncMaxBoards(iHandle, aMaxBoards);
            }
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMaxBoards().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginMaxBoards(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginMaxBoards(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMaxBoards"></param>
        public unsafe void EndMaxBoards(IntPtr aAsyncHandle, out uint aaMaxBoards)
        {
            fixed (uint* aMaxBoards = &aaMaxBoards)
            {
                if (0 != CpProxyLinnCoUkVolkano1EndMaxBoards(iHandle, aAsyncHandle, aMaxBoards))
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
        /// <param name="aaSoftwareVersion"></param>
        public unsafe void SyncSoftwareVersion(out string aaSoftwareVersion)
        {
            char* aSoftwareVersion;
            {
                CpProxyLinnCoUkVolkano1SyncSoftwareVersion(iHandle, &aSoftwareVersion);
            }
            aaSoftwareVersion = Marshal.PtrToStringAnsi((IntPtr)aSoftwareVersion);
            ZappFree(aSoftwareVersion);
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSoftwareVersion().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public unsafe void BeginSoftwareVersion(CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyLinnCoUkVolkano1BeginSoftwareVersion(iHandle, iActionComplete, ptr);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSoftwareVersion"></param>
        public unsafe void EndSoftwareVersion(IntPtr aAsyncHandle, out string aaSoftwareVersion)
        {
            char* aSoftwareVersion;
            {
                if (0 != CpProxyLinnCoUkVolkano1EndSoftwareVersion(iHandle, aAsyncHandle, &aSoftwareVersion))
                {
                    throw(new ProxyError());
                }
            }
            aaSoftwareVersion = Marshal.PtrToStringAnsi((IntPtr)aSoftwareVersion);
            ZappFree(aSoftwareVersion);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkVolkano1()
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
                CpProxyLinnCoUkVolkano1Destroy(iHandle);
                iHandle = IntPtr.Zero;
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

