using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyAvOpenhomeOrgMediaServer1 : ICpProxy, IDisposable
    {
        void SyncManufacturer(out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void BeginManufacturer(CpProxy.CallbackAsyncComplete aCallback);
        void EndManufacturer(IntPtr aAsyncHandle, out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void SyncModel(out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void BeginModel(CpProxy.CallbackAsyncComplete aCallback);
        void EndModel(IntPtr aAsyncHandle, out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void SyncProduct(out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void BeginProduct(CpProxy.CallbackAsyncComplete aCallback);
        void EndProduct(IntPtr aAsyncHandle, out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void SyncAttributes(out String aValue);
        void BeginAttributes(CpProxy.CallbackAsyncComplete aCallback);
        void EndAttributes(IntPtr aAsyncHandle, out String aValue);
        void SyncQueryPort(out uint aValue);
        void BeginQueryPort(CpProxy.CallbackAsyncComplete aCallback);
        void EndQueryPort(IntPtr aAsyncHandle, out uint aValue);
        void SyncBrowsePort(out uint aValue);
        void BeginBrowsePort(CpProxy.CallbackAsyncComplete aCallback);
        void EndBrowsePort(IntPtr aAsyncHandle, out uint aValue);
        void SyncUpdateCount(out uint aValue);
        void BeginUpdateCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndUpdateCount(IntPtr aAsyncHandle, out uint aValue);
        void SetPropertyManufacturerNameChanged(System.Action aManufacturerNameChanged);
        String PropertyManufacturerName();
        void SetPropertyManufacturerInfoChanged(System.Action aManufacturerInfoChanged);
        String PropertyManufacturerInfo();
        void SetPropertyManufacturerUrlChanged(System.Action aManufacturerUrlChanged);
        String PropertyManufacturerUrl();
        void SetPropertyManufacturerImageUriChanged(System.Action aManufacturerImageUriChanged);
        String PropertyManufacturerImageUri();
        void SetPropertyModelNameChanged(System.Action aModelNameChanged);
        String PropertyModelName();
        void SetPropertyModelInfoChanged(System.Action aModelInfoChanged);
        String PropertyModelInfo();
        void SetPropertyModelUrlChanged(System.Action aModelUrlChanged);
        String PropertyModelUrl();
        void SetPropertyModelImageUriChanged(System.Action aModelImageUriChanged);
        String PropertyModelImageUri();
        void SetPropertyProductNameChanged(System.Action aProductNameChanged);
        String PropertyProductName();
        void SetPropertyProductInfoChanged(System.Action aProductInfoChanged);
        String PropertyProductInfo();
        void SetPropertyProductUrlChanged(System.Action aProductUrlChanged);
        String PropertyProductUrl();
        void SetPropertyProductImageUriChanged(System.Action aProductImageUriChanged);
        String PropertyProductImageUri();
        void SetPropertyAttributesChanged(System.Action aAttributesChanged);
        String PropertyAttributes();
        void SetPropertyQueryPortChanged(System.Action aQueryPortChanged);
        uint PropertyQueryPort();
        void SetPropertyBrowsePortChanged(System.Action aBrowsePortChanged);
        uint PropertyBrowsePort();
        void SetPropertyUpdateCountChanged(System.Action aUpdateCountChanged);
        uint PropertyUpdateCount();
    }

    internal class SyncManufacturerAvOpenhomeOrgMediaServer1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgMediaServer1 iService;
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public SyncManufacturerAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
        {
            iService = aProxy;
        }
        public String Name()
        {
            return iName;
        }
        public String Info()
        {
            return iInfo;
        }
        public String Url()
        {
            return iUrl;
        }
        public String ImageUri()
        {
            return iImageUri;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndManufacturer(aAsyncHandle, out iName, out iInfo, out iUrl, out iImageUri);
        }
    };

    internal class SyncModelAvOpenhomeOrgMediaServer1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgMediaServer1 iService;
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public SyncModelAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
        {
            iService = aProxy;
        }
        public String Name()
        {
            return iName;
        }
        public String Info()
        {
            return iInfo;
        }
        public String Url()
        {
            return iUrl;
        }
        public String ImageUri()
        {
            return iImageUri;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndModel(aAsyncHandle, out iName, out iInfo, out iUrl, out iImageUri);
        }
    };

    internal class SyncProductAvOpenhomeOrgMediaServer1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgMediaServer1 iService;
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public SyncProductAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
        {
            iService = aProxy;
        }
        public String Name()
        {
            return iName;
        }
        public String Info()
        {
            return iInfo;
        }
        public String Url()
        {
            return iUrl;
        }
        public String ImageUri()
        {
            return iImageUri;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndProduct(aAsyncHandle, out iName, out iInfo, out iUrl, out iImageUri);
        }
    };

    internal class SyncAttributesAvOpenhomeOrgMediaServer1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgMediaServer1 iService;
        private String iValue;

        public SyncAttributesAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
        {
            iService = aProxy;
        }
        public String Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndAttributes(aAsyncHandle, out iValue);
        }
    };

    internal class SyncQueryPortAvOpenhomeOrgMediaServer1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgMediaServer1 iService;
        private uint iValue;

        public SyncQueryPortAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
        {
            iService = aProxy;
        }
        public uint Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndQueryPort(aAsyncHandle, out iValue);
        }
    };

    internal class SyncBrowsePortAvOpenhomeOrgMediaServer1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgMediaServer1 iService;
        private uint iValue;

        public SyncBrowsePortAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
        {
            iService = aProxy;
        }
        public uint Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndBrowsePort(aAsyncHandle, out iValue);
        }
    };

    internal class SyncUpdateCountAvOpenhomeOrgMediaServer1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgMediaServer1 iService;
        private uint iValue;

        public SyncUpdateCountAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
        {
            iService = aProxy;
        }
        public uint Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndUpdateCount(aAsyncHandle, out iValue);
        }
    };

    /// <summary>
    /// Proxy for the av.openhome.org:MediaServer:1 UPnP service
    /// </summary>
    public class CpProxyAvOpenhomeOrgMediaServer1 : CpProxy, IDisposable, ICpProxyAvOpenhomeOrgMediaServer1
    {
        private OpenHome.Net.Core.Action iActionManufacturer;
        private OpenHome.Net.Core.Action iActionModel;
        private OpenHome.Net.Core.Action iActionProduct;
        private OpenHome.Net.Core.Action iActionAttributes;
        private OpenHome.Net.Core.Action iActionQueryPort;
        private OpenHome.Net.Core.Action iActionBrowsePort;
        private OpenHome.Net.Core.Action iActionUpdateCount;
        private PropertyString iManufacturerName;
        private PropertyString iManufacturerInfo;
        private PropertyString iManufacturerUrl;
        private PropertyString iManufacturerImageUri;
        private PropertyString iModelName;
        private PropertyString iModelInfo;
        private PropertyString iModelUrl;
        private PropertyString iModelImageUri;
        private PropertyString iProductName;
        private PropertyString iProductInfo;
        private PropertyString iProductUrl;
        private PropertyString iProductImageUri;
        private PropertyString iAttributes;
        private PropertyUint iQueryPort;
        private PropertyUint iBrowsePort;
        private PropertyUint iUpdateCount;
        private System.Action iManufacturerNameChanged;
        private System.Action iManufacturerInfoChanged;
        private System.Action iManufacturerUrlChanged;
        private System.Action iManufacturerImageUriChanged;
        private System.Action iModelNameChanged;
        private System.Action iModelInfoChanged;
        private System.Action iModelUrlChanged;
        private System.Action iModelImageUriChanged;
        private System.Action iProductNameChanged;
        private System.Action iProductInfoChanged;
        private System.Action iProductUrlChanged;
        private System.Action iProductImageUriChanged;
        private System.Action iAttributesChanged;
        private System.Action iQueryPortChanged;
        private System.Action iBrowsePortChanged;
        private System.Action iUpdateCountChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyAvOpenhomeOrgMediaServer1(CpDevice aDevice)
            : base("av-openhome-org", "MediaServer", 1, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionManufacturer = new OpenHome.Net.Core.Action("Manufacturer");
            param = new ParameterString("Name", allowedValues);
            iActionManufacturer.AddOutputParameter(param);
            param = new ParameterString("Info", allowedValues);
            iActionManufacturer.AddOutputParameter(param);
            param = new ParameterString("Url", allowedValues);
            iActionManufacturer.AddOutputParameter(param);
            param = new ParameterString("ImageUri", allowedValues);
            iActionManufacturer.AddOutputParameter(param);

            iActionModel = new OpenHome.Net.Core.Action("Model");
            param = new ParameterString("Name", allowedValues);
            iActionModel.AddOutputParameter(param);
            param = new ParameterString("Info", allowedValues);
            iActionModel.AddOutputParameter(param);
            param = new ParameterString("Url", allowedValues);
            iActionModel.AddOutputParameter(param);
            param = new ParameterString("ImageUri", allowedValues);
            iActionModel.AddOutputParameter(param);

            iActionProduct = new OpenHome.Net.Core.Action("Product");
            param = new ParameterString("Name", allowedValues);
            iActionProduct.AddOutputParameter(param);
            param = new ParameterString("Info", allowedValues);
            iActionProduct.AddOutputParameter(param);
            param = new ParameterString("Url", allowedValues);
            iActionProduct.AddOutputParameter(param);
            param = new ParameterString("ImageUri", allowedValues);
            iActionProduct.AddOutputParameter(param);

            iActionAttributes = new OpenHome.Net.Core.Action("Attributes");
            param = new ParameterString("Value", allowedValues);
            iActionAttributes.AddOutputParameter(param);

            iActionQueryPort = new OpenHome.Net.Core.Action("QueryPort");
            param = new ParameterUint("Value");
            iActionQueryPort.AddOutputParameter(param);

            iActionBrowsePort = new OpenHome.Net.Core.Action("BrowsePort");
            param = new ParameterUint("Value");
            iActionBrowsePort.AddOutputParameter(param);

            iActionUpdateCount = new OpenHome.Net.Core.Action("UpdateCount");
            param = new ParameterUint("Value");
            iActionUpdateCount.AddOutputParameter(param);

            iManufacturerName = new PropertyString("ManufacturerName", ManufacturerNamePropertyChanged);
            AddProperty(iManufacturerName);
            iManufacturerInfo = new PropertyString("ManufacturerInfo", ManufacturerInfoPropertyChanged);
            AddProperty(iManufacturerInfo);
            iManufacturerUrl = new PropertyString("ManufacturerUrl", ManufacturerUrlPropertyChanged);
            AddProperty(iManufacturerUrl);
            iManufacturerImageUri = new PropertyString("ManufacturerImageUri", ManufacturerImageUriPropertyChanged);
            AddProperty(iManufacturerImageUri);
            iModelName = new PropertyString("ModelName", ModelNamePropertyChanged);
            AddProperty(iModelName);
            iModelInfo = new PropertyString("ModelInfo", ModelInfoPropertyChanged);
            AddProperty(iModelInfo);
            iModelUrl = new PropertyString("ModelUrl", ModelUrlPropertyChanged);
            AddProperty(iModelUrl);
            iModelImageUri = new PropertyString("ModelImageUri", ModelImageUriPropertyChanged);
            AddProperty(iModelImageUri);
            iProductName = new PropertyString("ProductName", ProductNamePropertyChanged);
            AddProperty(iProductName);
            iProductInfo = new PropertyString("ProductInfo", ProductInfoPropertyChanged);
            AddProperty(iProductInfo);
            iProductUrl = new PropertyString("ProductUrl", ProductUrlPropertyChanged);
            AddProperty(iProductUrl);
            iProductImageUri = new PropertyString("ProductImageUri", ProductImageUriPropertyChanged);
            AddProperty(iProductImageUri);
            iAttributes = new PropertyString("Attributes", AttributesPropertyChanged);
            AddProperty(iAttributes);
            iQueryPort = new PropertyUint("QueryPort", QueryPortPropertyChanged);
            AddProperty(iQueryPort);
            iBrowsePort = new PropertyUint("BrowsePort", BrowsePortPropertyChanged);
            AddProperty(iBrowsePort);
            iUpdateCount = new PropertyUint("UpdateCount", UpdateCountPropertyChanged);
            AddProperty(iUpdateCount);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        public void SyncManufacturer(out String aName, out String aInfo, out String aUrl, out String aImageUri)
        {
            SyncManufacturerAvOpenhomeOrgMediaServer1 sync = new SyncManufacturerAvOpenhomeOrgMediaServer1(this);
            BeginManufacturer(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aName = sync.Name();
            aInfo = sync.Info();
            aUrl = sync.Url();
            aImageUri = sync.ImageUri();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndManufacturer().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginManufacturer(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionManufacturer, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionManufacturer.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionManufacturer.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionManufacturer.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionManufacturer.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        public void EndManufacturer(IntPtr aAsyncHandle, out String aName, out String aInfo, out String aUrl, out String aImageUri)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aName = Invocation.OutputString(aAsyncHandle, index++);
            aInfo = Invocation.OutputString(aAsyncHandle, index++);
            aUrl = Invocation.OutputString(aAsyncHandle, index++);
            aImageUri = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        public void SyncModel(out String aName, out String aInfo, out String aUrl, out String aImageUri)
        {
            SyncModelAvOpenhomeOrgMediaServer1 sync = new SyncModelAvOpenhomeOrgMediaServer1(this);
            BeginModel(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aName = sync.Name();
            aInfo = sync.Info();
            aUrl = sync.Url();
            aImageUri = sync.ImageUri();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndModel().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginModel(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionModel, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionModel.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionModel.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionModel.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionModel.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        public void EndModel(IntPtr aAsyncHandle, out String aName, out String aInfo, out String aUrl, out String aImageUri)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aName = Invocation.OutputString(aAsyncHandle, index++);
            aInfo = Invocation.OutputString(aAsyncHandle, index++);
            aUrl = Invocation.OutputString(aAsyncHandle, index++);
            aImageUri = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        public void SyncProduct(out String aName, out String aInfo, out String aUrl, out String aImageUri)
        {
            SyncProductAvOpenhomeOrgMediaServer1 sync = new SyncProductAvOpenhomeOrgMediaServer1(this);
            BeginProduct(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aName = sync.Name();
            aInfo = sync.Info();
            aUrl = sync.Url();
            aImageUri = sync.ImageUri();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndProduct().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginProduct(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionProduct, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionProduct.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionProduct.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionProduct.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionProduct.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        public void EndProduct(IntPtr aAsyncHandle, out String aName, out String aInfo, out String aUrl, out String aImageUri)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aName = Invocation.OutputString(aAsyncHandle, index++);
            aInfo = Invocation.OutputString(aAsyncHandle, index++);
            aUrl = Invocation.OutputString(aAsyncHandle, index++);
            aImageUri = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncAttributes(out String aValue)
        {
            SyncAttributesAvOpenhomeOrgMediaServer1 sync = new SyncAttributesAvOpenhomeOrgMediaServer1(this);
            BeginAttributes(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndAttributes().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginAttributes(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionAttributes, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionAttributes.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndAttributes(IntPtr aAsyncHandle, out String aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncQueryPort(out uint aValue)
        {
            SyncQueryPortAvOpenhomeOrgMediaServer1 sync = new SyncQueryPortAvOpenhomeOrgMediaServer1(this);
            BeginQueryPort(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndQueryPort().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginQueryPort(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionQueryPort, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionQueryPort.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndQueryPort(IntPtr aAsyncHandle, out uint aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncBrowsePort(out uint aValue)
        {
            SyncBrowsePortAvOpenhomeOrgMediaServer1 sync = new SyncBrowsePortAvOpenhomeOrgMediaServer1(this);
            BeginBrowsePort(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBrowsePort().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginBrowsePort(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionBrowsePort, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowsePort.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndBrowsePort(IntPtr aAsyncHandle, out uint aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncUpdateCount(out uint aValue)
        {
            SyncUpdateCountAvOpenhomeOrgMediaServer1 sync = new SyncUpdateCountAvOpenhomeOrgMediaServer1(this);
            BeginUpdateCount(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndUpdateCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginUpdateCount(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionUpdateCount, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionUpdateCount.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndUpdateCount(IntPtr aAsyncHandle, out uint aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the ManufacturerName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aManufacturerNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyManufacturerNameChanged(System.Action aManufacturerNameChanged)
        {
            lock (iPropertyLock)
            {
                iManufacturerNameChanged = aManufacturerNameChanged;
            }
        }

        private void ManufacturerNamePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iManufacturerNameChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ManufacturerInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aManufacturerInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyManufacturerInfoChanged(System.Action aManufacturerInfoChanged)
        {
            lock (iPropertyLock)
            {
                iManufacturerInfoChanged = aManufacturerInfoChanged;
            }
        }

        private void ManufacturerInfoPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iManufacturerInfoChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ManufacturerUrl state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aManufacturerUrlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyManufacturerUrlChanged(System.Action aManufacturerUrlChanged)
        {
            lock (iPropertyLock)
            {
                iManufacturerUrlChanged = aManufacturerUrlChanged;
            }
        }

        private void ManufacturerUrlPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iManufacturerUrlChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ManufacturerImageUri state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aManufacturerImageUriChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyManufacturerImageUriChanged(System.Action aManufacturerImageUriChanged)
        {
            lock (iPropertyLock)
            {
                iManufacturerImageUriChanged = aManufacturerImageUriChanged;
            }
        }

        private void ManufacturerImageUriPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iManufacturerImageUriChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ModelName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aModelNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyModelNameChanged(System.Action aModelNameChanged)
        {
            lock (iPropertyLock)
            {
                iModelNameChanged = aModelNameChanged;
            }
        }

        private void ModelNamePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iModelNameChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ModelInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aModelInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyModelInfoChanged(System.Action aModelInfoChanged)
        {
            lock (iPropertyLock)
            {
                iModelInfoChanged = aModelInfoChanged;
            }
        }

        private void ModelInfoPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iModelInfoChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ModelUrl state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aModelUrlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyModelUrlChanged(System.Action aModelUrlChanged)
        {
            lock (iPropertyLock)
            {
                iModelUrlChanged = aModelUrlChanged;
            }
        }

        private void ModelUrlPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iModelUrlChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ModelImageUri state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aModelImageUriChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyModelImageUriChanged(System.Action aModelImageUriChanged)
        {
            lock (iPropertyLock)
            {
                iModelImageUriChanged = aModelImageUriChanged;
            }
        }

        private void ModelImageUriPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iModelImageUriChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aProductNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductNameChanged(System.Action aProductNameChanged)
        {
            lock (iPropertyLock)
            {
                iProductNameChanged = aProductNameChanged;
            }
        }

        private void ProductNamePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductNameChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductInfo state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aProductInfoChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductInfoChanged(System.Action aProductInfoChanged)
        {
            lock (iPropertyLock)
            {
                iProductInfoChanged = aProductInfoChanged;
            }
        }

        private void ProductInfoPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductInfoChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductUrl state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aProductUrlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductUrlChanged(System.Action aProductUrlChanged)
        {
            lock (iPropertyLock)
            {
                iProductUrlChanged = aProductUrlChanged;
            }
        }

        private void ProductUrlPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductUrlChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductImageUri state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aProductImageUriChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductImageUriChanged(System.Action aProductImageUriChanged)
        {
            lock (iPropertyLock)
            {
                iProductImageUriChanged = aProductImageUriChanged;
            }
        }

        private void ProductImageUriPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductImageUriChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Attributes state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aAttributesChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyAttributesChanged(System.Action aAttributesChanged)
        {
            lock (iPropertyLock)
            {
                iAttributesChanged = aAttributesChanged;
            }
        }

        private void AttributesPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iAttributesChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the QueryPort state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aQueryPortChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyQueryPortChanged(System.Action aQueryPortChanged)
        {
            lock (iPropertyLock)
            {
                iQueryPortChanged = aQueryPortChanged;
            }
        }

        private void QueryPortPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iQueryPortChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the BrowsePort state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aBrowsePortChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyBrowsePortChanged(System.Action aBrowsePortChanged)
        {
            lock (iPropertyLock)
            {
                iBrowsePortChanged = aBrowsePortChanged;
            }
        }

        private void BrowsePortPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iBrowsePortChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the UpdateCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.</remarks>
        /// <param name="aUpdateCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyUpdateCountChanged(System.Action aUpdateCountChanged)
        {
            lock (iPropertyLock)
            {
                iUpdateCountChanged = aUpdateCountChanged;
            }
        }

        private void UpdateCountPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iUpdateCountChanged);
            }
        }

        /// <summary>
        /// Query the value of the ManufacturerName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ManufacturerName property</returns>
        public String PropertyManufacturerName()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iManufacturerName.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ManufacturerInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ManufacturerInfo property</returns>
        public String PropertyManufacturerInfo()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iManufacturerInfo.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ManufacturerUrl property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ManufacturerUrl property</returns>
        public String PropertyManufacturerUrl()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iManufacturerUrl.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ManufacturerImageUri property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ManufacturerImageUri property</returns>
        public String PropertyManufacturerImageUri()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iManufacturerImageUri.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ModelName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ModelName property</returns>
        public String PropertyModelName()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iModelName.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ModelInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ModelInfo property</returns>
        public String PropertyModelInfo()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iModelInfo.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ModelUrl property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ModelUrl property</returns>
        public String PropertyModelUrl()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iModelUrl.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ModelImageUri property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ModelImageUri property</returns>
        public String PropertyModelImageUri()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iModelImageUri.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ProductName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ProductName property</returns>
        public String PropertyProductName()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iProductName.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ProductInfo property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ProductInfo property</returns>
        public String PropertyProductInfo()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iProductInfo.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ProductUrl property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ProductUrl property</returns>
        public String PropertyProductUrl()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iProductUrl.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the ProductImageUri property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ProductImageUri property</returns>
        public String PropertyProductImageUri()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iProductImageUri.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the Attributes property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Attributes property</returns>
        public String PropertyAttributes()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iAttributes.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the QueryPort property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the QueryPort property</returns>
        public uint PropertyQueryPort()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iQueryPort.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the BrowsePort property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the BrowsePort property</returns>
        public uint PropertyBrowsePort()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iBrowsePort.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the UpdateCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the UpdateCount property</returns>
        public uint PropertyUpdateCount()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iUpdateCount.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DisposeProxy();
                iHandle = IntPtr.Zero;
            }
            iActionManufacturer.Dispose();
            iActionModel.Dispose();
            iActionProduct.Dispose();
            iActionAttributes.Dispose();
            iActionQueryPort.Dispose();
            iActionBrowsePort.Dispose();
            iActionUpdateCount.Dispose();
            iManufacturerName.Dispose();
            iManufacturerInfo.Dispose();
            iManufacturerUrl.Dispose();
            iManufacturerImageUri.Dispose();
            iModelName.Dispose();
            iModelInfo.Dispose();
            iModelUrl.Dispose();
            iModelImageUri.Dispose();
            iProductName.Dispose();
            iProductInfo.Dispose();
            iProductUrl.Dispose();
            iProductImageUri.Dispose();
            iAttributes.Dispose();
            iQueryPort.Dispose();
            iBrowsePort.Dispose();
            iUpdateCount.Dispose();
        }
    }
}

