using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyAvOpenhomeOrgProduct1 : ICpProxy, IDisposable
    {
        void SyncManufacturer(out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void BeginManufacturer(CpProxy.CallbackAsyncComplete aCallback);
        void EndManufacturer(IntPtr aAsyncHandle, out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void SyncModel(out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void BeginModel(CpProxy.CallbackAsyncComplete aCallback);
        void EndModel(IntPtr aAsyncHandle, out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void SyncProduct(out String aRoom, out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void BeginProduct(CpProxy.CallbackAsyncComplete aCallback);
        void EndProduct(IntPtr aAsyncHandle, out String aRoom, out String aName, out String aInfo, out String aUrl, out String aImageUri);
        void SyncStandby(out bool aValue);
        void BeginStandby(CpProxy.CallbackAsyncComplete aCallback);
        void EndStandby(IntPtr aAsyncHandle, out bool aValue);
        void SyncSetStandby(bool aValue);
        void BeginSetStandby(bool aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStandby(IntPtr aAsyncHandle);
        void SyncSourceCount(out uint aValue);
        void BeginSourceCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceCount(IntPtr aAsyncHandle, out uint aValue);
        void SyncSourceXml(out String aValue);
        void BeginSourceXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceXml(IntPtr aAsyncHandle, out String aValue);
        void SyncSourceIndex(out uint aValue);
        void BeginSourceIndex(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceIndex(IntPtr aAsyncHandle, out uint aValue);
        void SyncSetSourceIndex(uint aValue);
        void BeginSetSourceIndex(uint aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceIndex(IntPtr aAsyncHandle);
        void SyncSetSourceIndexByName(String aValue);
        void BeginSetSourceIndexByName(String aValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceIndexByName(IntPtr aAsyncHandle);
        void SyncSource(uint aIndex, out String aSystemName, out String aType, out String aName, out bool aVisible);
        void BeginSource(uint aIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSource(IntPtr aAsyncHandle, out String aSystemName, out String aType, out String aName, out bool aVisible);
        void SyncAttributes(out String aValue);
        void BeginAttributes(CpProxy.CallbackAsyncComplete aCallback);
        void EndAttributes(IntPtr aAsyncHandle, out String aValue);
        void SyncSourceXmlChangeCount(out uint aValue);
        void BeginSourceXmlChangeCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceXmlChangeCount(IntPtr aAsyncHandle, out uint aValue);
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
        void SetPropertyProductRoomChanged(System.Action aProductRoomChanged);
        String PropertyProductRoom();
        void SetPropertyProductNameChanged(System.Action aProductNameChanged);
        String PropertyProductName();
        void SetPropertyProductInfoChanged(System.Action aProductInfoChanged);
        String PropertyProductInfo();
        void SetPropertyProductUrlChanged(System.Action aProductUrlChanged);
        String PropertyProductUrl();
        void SetPropertyProductImageUriChanged(System.Action aProductImageUriChanged);
        String PropertyProductImageUri();
        void SetPropertyStandbyChanged(System.Action aStandbyChanged);
        bool PropertyStandby();
        void SetPropertySourceIndexChanged(System.Action aSourceIndexChanged);
        uint PropertySourceIndex();
        void SetPropertySourceCountChanged(System.Action aSourceCountChanged);
        uint PropertySourceCount();
        void SetPropertySourceXmlChanged(System.Action aSourceXmlChanged);
        String PropertySourceXml();
        void SetPropertyAttributesChanged(System.Action aAttributesChanged);
        String PropertyAttributes();
    }

    internal class SyncManufacturerAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public SyncManufacturerAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
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

    internal class SyncModelAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public SyncModelAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
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

    internal class SyncProductAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private String iRoom;
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public SyncProductAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        public String Room()
        {
            return iRoom;
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
            iService.EndProduct(aAsyncHandle, out iRoom, out iName, out iInfo, out iUrl, out iImageUri);
        }
    };

    internal class SyncStandbyAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private bool iValue;

        public SyncStandbyAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        public bool Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStandby(aAsyncHandle, out iValue);
        }
    };

    internal class SyncSetStandbyAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;

        public SyncSetStandbyAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStandby(aAsyncHandle);
        }
    };

    internal class SyncSourceCountAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private uint iValue;

        public SyncSourceCountAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        public uint Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceCount(aAsyncHandle, out iValue);
        }
    };

    internal class SyncSourceXmlAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private String iValue;

        public SyncSourceXmlAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        public String Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceXml(aAsyncHandle, out iValue);
        }
    };

    internal class SyncSourceIndexAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private uint iValue;

        public SyncSourceIndexAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        public uint Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceIndex(aAsyncHandle, out iValue);
        }
    };

    internal class SyncSetSourceIndexAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;

        public SyncSetSourceIndexAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetSourceIndex(aAsyncHandle);
        }
    };

    internal class SyncSetSourceIndexByNameAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;

        public SyncSetSourceIndexByNameAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetSourceIndexByName(aAsyncHandle);
        }
    };

    internal class SyncSourceAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private String iSystemName;
        private String iType;
        private String iName;
        private bool iVisible;

        public SyncSourceAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        public String SystemName()
        {
            return iSystemName;
        }
        public String Type()
        {
            return iType;
        }
        public String Name()
        {
            return iName;
        }
        public bool Visible()
        {
            return iVisible;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSource(aAsyncHandle, out iSystemName, out iType, out iName, out iVisible);
        }
    };

    internal class SyncAttributesAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private String iValue;

        public SyncAttributesAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
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

    internal class SyncSourceXmlChangeCountAvOpenhomeOrgProduct1 : SyncProxyAction
    {
        private CpProxyAvOpenhomeOrgProduct1 iService;
        private uint iValue;

        public SyncSourceXmlChangeCountAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
        {
            iService = aProxy;
        }
        public uint Value()
        {
            return iValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceXmlChangeCount(aAsyncHandle, out iValue);
        }
    };

    /// <summary>
    /// Proxy for the av.openhome.org:Product:1 UPnP service
    /// </summary>
    public class CpProxyAvOpenhomeOrgProduct1 : CpProxy, IDisposable, ICpProxyAvOpenhomeOrgProduct1
    {
        private OpenHome.Net.Core.Action iActionManufacturer;
        private OpenHome.Net.Core.Action iActionModel;
        private OpenHome.Net.Core.Action iActionProduct;
        private OpenHome.Net.Core.Action iActionStandby;
        private OpenHome.Net.Core.Action iActionSetStandby;
        private OpenHome.Net.Core.Action iActionSourceCount;
        private OpenHome.Net.Core.Action iActionSourceXml;
        private OpenHome.Net.Core.Action iActionSourceIndex;
        private OpenHome.Net.Core.Action iActionSetSourceIndex;
        private OpenHome.Net.Core.Action iActionSetSourceIndexByName;
        private OpenHome.Net.Core.Action iActionSource;
        private OpenHome.Net.Core.Action iActionAttributes;
        private OpenHome.Net.Core.Action iActionSourceXmlChangeCount;
        private PropertyString iManufacturerName;
        private PropertyString iManufacturerInfo;
        private PropertyString iManufacturerUrl;
        private PropertyString iManufacturerImageUri;
        private PropertyString iModelName;
        private PropertyString iModelInfo;
        private PropertyString iModelUrl;
        private PropertyString iModelImageUri;
        private PropertyString iProductRoom;
        private PropertyString iProductName;
        private PropertyString iProductInfo;
        private PropertyString iProductUrl;
        private PropertyString iProductImageUri;
        private PropertyBool iStandby;
        private PropertyUint iSourceIndex;
        private PropertyUint iSourceCount;
        private PropertyString iSourceXml;
        private PropertyString iAttributes;
        private System.Action iManufacturerNameChanged;
        private System.Action iManufacturerInfoChanged;
        private System.Action iManufacturerUrlChanged;
        private System.Action iManufacturerImageUriChanged;
        private System.Action iModelNameChanged;
        private System.Action iModelInfoChanged;
        private System.Action iModelUrlChanged;
        private System.Action iModelImageUriChanged;
        private System.Action iProductRoomChanged;
        private System.Action iProductNameChanged;
        private System.Action iProductInfoChanged;
        private System.Action iProductUrlChanged;
        private System.Action iProductImageUriChanged;
        private System.Action iStandbyChanged;
        private System.Action iSourceIndexChanged;
        private System.Action iSourceCountChanged;
        private System.Action iSourceXmlChanged;
        private System.Action iAttributesChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyAvOpenhomeOrgProduct1(ICpDevice aDevice)
            : base("av-openhome-org", "Product", 1, aDevice)
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
            param = new ParameterString("Room", allowedValues);
            iActionProduct.AddOutputParameter(param);
            param = new ParameterString("Name", allowedValues);
            iActionProduct.AddOutputParameter(param);
            param = new ParameterString("Info", allowedValues);
            iActionProduct.AddOutputParameter(param);
            param = new ParameterString("Url", allowedValues);
            iActionProduct.AddOutputParameter(param);
            param = new ParameterString("ImageUri", allowedValues);
            iActionProduct.AddOutputParameter(param);

            iActionStandby = new OpenHome.Net.Core.Action("Standby");
            param = new ParameterBool("Value");
            iActionStandby.AddOutputParameter(param);

            iActionSetStandby = new OpenHome.Net.Core.Action("SetStandby");
            param = new ParameterBool("Value");
            iActionSetStandby.AddInputParameter(param);

            iActionSourceCount = new OpenHome.Net.Core.Action("SourceCount");
            param = new ParameterUint("Value");
            iActionSourceCount.AddOutputParameter(param);

            iActionSourceXml = new OpenHome.Net.Core.Action("SourceXml");
            param = new ParameterString("Value", allowedValues);
            iActionSourceXml.AddOutputParameter(param);

            iActionSourceIndex = new OpenHome.Net.Core.Action("SourceIndex");
            param = new ParameterUint("Value");
            iActionSourceIndex.AddOutputParameter(param);

            iActionSetSourceIndex = new OpenHome.Net.Core.Action("SetSourceIndex");
            param = new ParameterUint("Value");
            iActionSetSourceIndex.AddInputParameter(param);

            iActionSetSourceIndexByName = new OpenHome.Net.Core.Action("SetSourceIndexByName");
            param = new ParameterString("Value", allowedValues);
            iActionSetSourceIndexByName.AddInputParameter(param);

            iActionSource = new OpenHome.Net.Core.Action("Source");
            param = new ParameterUint("Index");
            iActionSource.AddInputParameter(param);
            param = new ParameterString("SystemName", allowedValues);
            iActionSource.AddOutputParameter(param);
            param = new ParameterString("Type", allowedValues);
            iActionSource.AddOutputParameter(param);
            param = new ParameterString("Name", allowedValues);
            iActionSource.AddOutputParameter(param);
            param = new ParameterBool("Visible");
            iActionSource.AddOutputParameter(param);

            iActionAttributes = new OpenHome.Net.Core.Action("Attributes");
            param = new ParameterString("Value", allowedValues);
            iActionAttributes.AddOutputParameter(param);

            iActionSourceXmlChangeCount = new OpenHome.Net.Core.Action("SourceXmlChangeCount");
            param = new ParameterUint("Value");
            iActionSourceXmlChangeCount.AddOutputParameter(param);

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
            iProductRoom = new PropertyString("ProductRoom", ProductRoomPropertyChanged);
            AddProperty(iProductRoom);
            iProductName = new PropertyString("ProductName", ProductNamePropertyChanged);
            AddProperty(iProductName);
            iProductInfo = new PropertyString("ProductInfo", ProductInfoPropertyChanged);
            AddProperty(iProductInfo);
            iProductUrl = new PropertyString("ProductUrl", ProductUrlPropertyChanged);
            AddProperty(iProductUrl);
            iProductImageUri = new PropertyString("ProductImageUri", ProductImageUriPropertyChanged);
            AddProperty(iProductImageUri);
            iStandby = new PropertyBool("Standby", StandbyPropertyChanged);
            AddProperty(iStandby);
            iSourceIndex = new PropertyUint("SourceIndex", SourceIndexPropertyChanged);
            AddProperty(iSourceIndex);
            iSourceCount = new PropertyUint("SourceCount", SourceCountPropertyChanged);
            AddProperty(iSourceCount);
            iSourceXml = new PropertyString("SourceXml", SourceXmlPropertyChanged);
            AddProperty(iSourceXml);
            iAttributes = new PropertyString("Attributes", AttributesPropertyChanged);
            AddProperty(iAttributes);
            
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
            SyncManufacturerAvOpenhomeOrgProduct1 sync = new SyncManufacturerAvOpenhomeOrgProduct1(this);
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
            SyncModelAvOpenhomeOrgProduct1 sync = new SyncModelAvOpenhomeOrgProduct1(this);
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
        /// <param name="aRoom"></param>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        public void SyncProduct(out String aRoom, out String aName, out String aInfo, out String aUrl, out String aImageUri)
        {
            SyncProductAvOpenhomeOrgProduct1 sync = new SyncProductAvOpenhomeOrgProduct1(this);
            BeginProduct(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRoom = sync.Room();
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
            invocation.AddOutput(new ArgumentString((ParameterString)iActionProduct.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aRoom"></param>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        public void EndProduct(IntPtr aAsyncHandle, out String aRoom, out String aName, out String aInfo, out String aUrl, out String aImageUri)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aRoom = Invocation.OutputString(aAsyncHandle, index++);
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
        public void SyncStandby(out bool aValue)
        {
            SyncStandbyAvOpenhomeOrgProduct1 sync = new SyncStandbyAvOpenhomeOrgProduct1(this);
            BeginStandby(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStandby().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStandby(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStandby, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionStandby.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndStandby(IntPtr aAsyncHandle, out bool aValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aValue = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncSetStandby(bool aValue)
        {
            SyncSetStandbyAvOpenhomeOrgProduct1 sync = new SyncSetStandbyAvOpenhomeOrgProduct1(this);
            BeginSetStandby(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStandby().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStandby(bool aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStandby, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetStandby.InputParameter(inIndex++), aValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStandby(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncSourceCount(out uint aValue)
        {
            SyncSourceCountAvOpenhomeOrgProduct1 sync = new SyncSourceCountAvOpenhomeOrgProduct1(this);
            BeginSourceCount(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceCount(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceCount, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSourceCount.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndSourceCount(IntPtr aAsyncHandle, out uint aValue)
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
        public void SyncSourceXml(out String aValue)
        {
            SyncSourceXmlAvOpenhomeOrgProduct1 sync = new SyncSourceXmlAvOpenhomeOrgProduct1(this);
            BeginSourceXml(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceXml().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceXml(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceXml, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSourceXml.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndSourceXml(IntPtr aAsyncHandle, out String aValue)
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
        public void SyncSourceIndex(out uint aValue)
        {
            SyncSourceIndexAvOpenhomeOrgProduct1 sync = new SyncSourceIndexAvOpenhomeOrgProduct1(this);
            BeginSourceIndex(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceIndex().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceIndex(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceIndex, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSourceIndex.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndSourceIndex(IntPtr aAsyncHandle, out uint aValue)
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
        public void SyncSetSourceIndex(uint aValue)
        {
            SyncSetSourceIndexAvOpenhomeOrgProduct1 sync = new SyncSetSourceIndexAvOpenhomeOrgProduct1(this);
            BeginSetSourceIndex(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceIndex().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetSourceIndex(uint aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetSourceIndex, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetSourceIndex.InputParameter(inIndex++), aValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetSourceIndex(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncSetSourceIndexByName(String aValue)
        {
            SyncSetSourceIndexByNameAvOpenhomeOrgProduct1 sync = new SyncSetSourceIndexByNameAvOpenhomeOrgProduct1(this);
            BeginSetSourceIndexByName(aValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceIndexByName().</remarks>
        /// <param name="aValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetSourceIndexByName(String aValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetSourceIndexByName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetSourceIndexByName.InputParameter(inIndex++), aValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetSourceIndexByName(IntPtr aAsyncHandle)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aSystemName"></param>
        /// <param name="aType"></param>
        /// <param name="aName"></param>
        /// <param name="aVisible"></param>
        public void SyncSource(uint aIndex, out String aSystemName, out String aType, out String aName, out bool aVisible)
        {
            SyncSourceAvOpenhomeOrgProduct1 sync = new SyncSourceAvOpenhomeOrgProduct1(this);
            BeginSource(aIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSystemName = sync.SystemName();
            aType = sync.Type();
            aName = sync.Name();
            aVisible = sync.Visible();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSource().</remarks>
        /// <param name="aIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSource(uint aIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSource, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSource.InputParameter(inIndex++), aIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSource.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSource.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSource.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionSource.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSystemName"></param>
        /// <param name="aType"></param>
        /// <param name="aName"></param>
        /// <param name="aVisible"></param>
        public void EndSource(IntPtr aAsyncHandle, out String aSystemName, out String aType, out String aName, out bool aVisible)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aSystemName = Invocation.OutputString(aAsyncHandle, index++);
            aType = Invocation.OutputString(aAsyncHandle, index++);
            aName = Invocation.OutputString(aAsyncHandle, index++);
            aVisible = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aValue"></param>
        public void SyncAttributes(out String aValue)
        {
            SyncAttributesAvOpenhomeOrgProduct1 sync = new SyncAttributesAvOpenhomeOrgProduct1(this);
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
        public void SyncSourceXmlChangeCount(out uint aValue)
        {
            SyncSourceXmlChangeCountAvOpenhomeOrgProduct1 sync = new SyncSourceXmlChangeCountAvOpenhomeOrgProduct1(this);
            BeginSourceXmlChangeCount(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aValue = sync.Value();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceXmlChangeCount().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceXmlChangeCount(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceXmlChangeCount, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSourceXmlChangeCount.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aValue"></param>
        public void EndSourceXmlChangeCount(IntPtr aAsyncHandle, out uint aValue)
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// Set a delegate to be run when the ProductRoom state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
        /// <param name="aProductRoomChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductRoomChanged(System.Action aProductRoomChanged)
        {
            lock (iPropertyLock)
            {
                iProductRoomChanged = aProductRoomChanged;
            }
        }

        private void ProductRoomPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductRoomChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// Set a delegate to be run when the Standby state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
        /// <param name="aStandbyChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStandbyChanged(System.Action aStandbyChanged)
        {
            lock (iPropertyLock)
            {
                iStandbyChanged = aStandbyChanged;
            }
        }

        private void StandbyPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iStandbyChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the SourceIndex state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
        /// <param name="aSourceIndexChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySourceIndexChanged(System.Action aSourceIndexChanged)
        {
            lock (iPropertyLock)
            {
                iSourceIndexChanged = aSourceIndexChanged;
            }
        }

        private void SourceIndexPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSourceIndexChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the SourceCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
        /// <param name="aSourceCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySourceCountChanged(System.Action aSourceCountChanged)
        {
            lock (iPropertyLock)
            {
                iSourceCountChanged = aSourceCountChanged;
            }
        }

        private void SourceCountPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSourceCountChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the SourceXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
        /// <param name="aSourceXmlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySourceXmlChanged(System.Action aSourceXmlChanged)
        {
            lock (iPropertyLock)
            {
                iSourceXmlChanged = aSourceXmlChanged;
            }
        }

        private void SourceXmlPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSourceXmlChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Attributes state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyAvOpenhomeOrgProduct1 instance will not overlap.</remarks>
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
        /// Query the value of the ProductRoom property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ProductRoom property</returns>
        public String PropertyProductRoom()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iProductRoom.Value();
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
        /// Query the value of the Standby property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the Standby property</returns>
        public bool PropertyStandby()
        {
            PropertyReadLock();
            bool val;
            try
            {
                val = iStandby.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the SourceIndex property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the SourceIndex property</returns>
        public uint PropertySourceIndex()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iSourceIndex.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the SourceCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the SourceCount property</returns>
        public uint PropertySourceCount()
        {
            PropertyReadLock();
            uint val;
            try
            {
                val = iSourceCount.Value();
            }
            finally
            {
                PropertyReadUnlock();
            }
            return val;
        }

        /// <summary>
        /// Query the value of the SourceXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the SourceXml property</returns>
        public String PropertySourceXml()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iSourceXml.Value();
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
            iActionStandby.Dispose();
            iActionSetStandby.Dispose();
            iActionSourceCount.Dispose();
            iActionSourceXml.Dispose();
            iActionSourceIndex.Dispose();
            iActionSetSourceIndex.Dispose();
            iActionSetSourceIndexByName.Dispose();
            iActionSource.Dispose();
            iActionAttributes.Dispose();
            iActionSourceXmlChangeCount.Dispose();
            iManufacturerName.Dispose();
            iManufacturerInfo.Dispose();
            iManufacturerUrl.Dispose();
            iManufacturerImageUri.Dispose();
            iModelName.Dispose();
            iModelInfo.Dispose();
            iModelUrl.Dispose();
            iModelImageUri.Dispose();
            iProductRoom.Dispose();
            iProductName.Dispose();
            iProductInfo.Dispose();
            iProductUrl.Dispose();
            iProductImageUri.Dispose();
            iStandby.Dispose();
            iSourceIndex.Dispose();
            iSourceCount.Dispose();
            iSourceXml.Dispose();
            iAttributes.Dispose();
        }
    }
}

