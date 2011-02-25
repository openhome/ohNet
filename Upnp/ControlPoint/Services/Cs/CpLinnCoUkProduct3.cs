using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkProduct3 : ICpProxy, IDisposable
    {
        void SyncType(out String aType);
        void BeginType(CpProxy.CallbackAsyncComplete aCallback);
        void EndType(IntPtr aAsyncHandle, out String aType);
        void SyncModel(out String aModel);
        void BeginModel(CpProxy.CallbackAsyncComplete aCallback);
        void EndModel(IntPtr aAsyncHandle, out String aModel);
        void SyncName(out String aName);
        void BeginName(CpProxy.CallbackAsyncComplete aCallback);
        void EndName(IntPtr aAsyncHandle, out String aName);
        void SyncSetName(String aName);
        void BeginSetName(String aName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetName(IntPtr aAsyncHandle);
        void SyncRoom(out String aRoom);
        void BeginRoom(CpProxy.CallbackAsyncComplete aCallback);
        void EndRoom(IntPtr aAsyncHandle, out String aRoom);
        void SyncSetRoom(String aRoom);
        void BeginSetRoom(String aRoom, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRoom(IntPtr aAsyncHandle);
        void SyncStandby(out bool aStandby);
        void BeginStandby(CpProxy.CallbackAsyncComplete aCallback);
        void EndStandby(IntPtr aAsyncHandle, out bool aStandby);
        void SyncSetStandby(bool aStandby);
        void BeginSetStandby(bool aStandby, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStandby(IntPtr aAsyncHandle);
        void SyncSourceCount(out uint aSourceCount);
        void BeginSourceCount(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceCount(IntPtr aAsyncHandle, out uint aSourceCount);
        void SyncSourceXml(out String aSourceXml);
        void BeginSourceXml(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceXml(IntPtr aAsyncHandle, out String aSourceXml);
        void SyncSourceIndex(out uint aSourceIndex);
        void BeginSourceIndex(CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceIndex(IntPtr aAsyncHandle, out uint aSourceIndex);
        void SyncSetSourceIndex(uint aSourceIndex);
        void BeginSetSourceIndex(uint aSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceIndex(IntPtr aAsyncHandle);
        void SyncSetSourceIndexByName(String aSourceName);
        void BeginSetSourceIndexByName(String aSourceName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceIndexByName(IntPtr aAsyncHandle);
        void SyncSetStartupSourceIndexByName(String aSourceName);
        void BeginSetStartupSourceIndexByName(String aSourceName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupSourceIndexByName(IntPtr aAsyncHandle);
        void SyncStartupSourceIndex(out uint aSourceIndex);
        void BeginStartupSourceIndex(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartupSourceIndex(IntPtr aAsyncHandle, out uint aSourceIndex);
        void SyncSetStartupSourceIndex(uint aSourceIndex);
        void BeginSetStartupSourceIndex(uint aSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupSourceIndex(IntPtr aAsyncHandle);
        void SyncStartupSourceEnabled(out bool aStartupSourceEnabled);
        void BeginStartupSourceEnabled(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartupSourceEnabled(IntPtr aAsyncHandle, out bool aStartupSourceEnabled);
        void SyncSetStartupSourceEnabled(bool aStartupSourceEnabled);
        void BeginSetStartupSourceEnabled(bool aStartupSourceEnabled, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStartupSourceEnabled(IntPtr aAsyncHandle);
        void SyncSourceSystemName(uint aSourceIndex, out String aSourceName);
        void BeginSourceSystemName(uint aSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceSystemName(IntPtr aAsyncHandle, out String aSourceName);
        void SyncSourceName(uint aSourceIndex, out String aSourceName);
        void BeginSourceName(uint aSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceName(IntPtr aAsyncHandle, out String aSourceName);
        void SyncSetSourceName(uint aSourceIndex, String aSourceName);
        void BeginSetSourceName(uint aSourceIndex, String aSourceName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceName(IntPtr aAsyncHandle);
        void SyncSourceType(uint aSourceIndex, out String aSourceType);
        void BeginSourceType(uint aSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceType(IntPtr aAsyncHandle, out String aSourceType);
        void SyncSourceVisible(uint aSourceIndex, out bool aSourceVisible);
        void BeginSourceVisible(uint aSourceIndex, CpProxy.CallbackAsyncComplete aCallback);
        void EndSourceVisible(IntPtr aAsyncHandle, out bool aSourceVisible);
        void SyncSetSourceVisible(uint aSourceIndex, bool aSourceVisible);
        void BeginSetSourceVisible(uint aSourceIndex, bool aSourceVisible, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSourceVisible(IntPtr aAsyncHandle);
        void SetPropertyProductTypeChanged(CpProxy.CallbackPropertyChanged aProductTypeChanged);
        String PropertyProductType();
        void SetPropertyProductModelChanged(CpProxy.CallbackPropertyChanged aProductModelChanged);
        String PropertyProductModel();
        void SetPropertyProductNameChanged(CpProxy.CallbackPropertyChanged aProductNameChanged);
        String PropertyProductName();
        void SetPropertyProductRoomChanged(CpProxy.CallbackPropertyChanged aProductRoomChanged);
        String PropertyProductRoom();
        void SetPropertyProductStandbyChanged(CpProxy.CallbackPropertyChanged aProductStandbyChanged);
        bool PropertyProductStandby();
        void SetPropertyProductSourceIndexChanged(CpProxy.CallbackPropertyChanged aProductSourceIndexChanged);
        uint PropertyProductSourceIndex();
        void SetPropertyProductSourceCountChanged(CpProxy.CallbackPropertyChanged aProductSourceCountChanged);
        uint PropertyProductSourceCount();
        void SetPropertyProductSourceXmlChanged(CpProxy.CallbackPropertyChanged aProductSourceXmlChanged);
        String PropertyProductSourceXml();
        void SetPropertyStartupSourceIndexChanged(CpProxy.CallbackPropertyChanged aStartupSourceIndexChanged);
        uint PropertyStartupSourceIndex();
        void SetPropertyStartupSourceEnabledChanged(CpProxy.CallbackPropertyChanged aStartupSourceEnabledChanged);
        bool PropertyStartupSourceEnabled();
        void SetPropertyProductAnySourceNameChanged(CpProxy.CallbackPropertyChanged aProductAnySourceNameChanged);
        uint PropertyProductAnySourceName();
        void SetPropertyProductAnySourceVisibleChanged(CpProxy.CallbackPropertyChanged aProductAnySourceVisibleChanged);
        uint PropertyProductAnySourceVisible();
        void SetPropertyProductAnySourceTypeChanged(CpProxy.CallbackPropertyChanged aProductAnySourceTypeChanged);
        uint PropertyProductAnySourceType();
    }

    internal class SyncTypeLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private String iType;

        public SyncTypeLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public String Type()
        {
            return iType;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndType(aAsyncHandle, out iType);
        }
    };

    internal class SyncModelLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private String iModel;

        public SyncModelLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public String Model()
        {
            return iModel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndModel(aAsyncHandle, out iModel);
        }
    };

    internal class SyncNameLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private String iName;

        public SyncNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public String Name()
        {
            return iName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndName(aAsyncHandle, out iName);
        }
    };

    internal class SyncSetNameLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetName(aAsyncHandle);
        }
    };

    internal class SyncRoomLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private String iRoom;

        public SyncRoomLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public String Room()
        {
            return iRoom;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndRoom(aAsyncHandle, out iRoom);
        }
    };

    internal class SyncSetRoomLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetRoomLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetRoom(aAsyncHandle);
        }
    };

    internal class SyncStandbyLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private bool iStandby;

        public SyncStandbyLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public bool Standby()
        {
            return iStandby;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStandby(aAsyncHandle, out iStandby);
        }
    };

    internal class SyncSetStandbyLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetStandbyLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStandby(aAsyncHandle);
        }
    };

    internal class SyncSourceCountLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private uint iSourceCount;

        public SyncSourceCountLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public uint SourceCount()
        {
            return iSourceCount;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceCount(aAsyncHandle, out iSourceCount);
        }
    };

    internal class SyncSourceXmlLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private String iSourceXml;

        public SyncSourceXmlLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public String SourceXml()
        {
            return iSourceXml;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceXml(aAsyncHandle, out iSourceXml);
        }
    };

    internal class SyncSourceIndexLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private uint iSourceIndex;

        public SyncSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public uint SourceIndex()
        {
            return iSourceIndex;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceIndex(aAsyncHandle, out iSourceIndex);
        }
    };

    internal class SyncSetSourceIndexLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetSourceIndex(aAsyncHandle);
        }
    };

    internal class SyncSetSourceIndexByNameLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetSourceIndexByNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetSourceIndexByName(aAsyncHandle);
        }
    };

    internal class SyncSetStartupSourceIndexByNameLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetStartupSourceIndexByNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStartupSourceIndexByName(aAsyncHandle);
        }
    };

    internal class SyncStartupSourceIndexLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private uint iSourceIndex;

        public SyncStartupSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public uint SourceIndex()
        {
            return iSourceIndex;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartupSourceIndex(aAsyncHandle, out iSourceIndex);
        }
    };

    internal class SyncSetStartupSourceIndexLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetStartupSourceIndexLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStartupSourceIndex(aAsyncHandle);
        }
    };

    internal class SyncStartupSourceEnabledLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private bool iStartupSourceEnabled;

        public SyncStartupSourceEnabledLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public bool StartupSourceEnabled()
        {
            return iStartupSourceEnabled;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartupSourceEnabled(aAsyncHandle, out iStartupSourceEnabled);
        }
    };

    internal class SyncSetStartupSourceEnabledLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetStartupSourceEnabledLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStartupSourceEnabled(aAsyncHandle);
        }
    };

    internal class SyncSourceSystemNameLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private String iSourceName;

        public SyncSourceSystemNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public String SourceName()
        {
            return iSourceName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceSystemName(aAsyncHandle, out iSourceName);
        }
    };

    internal class SyncSourceNameLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private String iSourceName;

        public SyncSourceNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public String SourceName()
        {
            return iSourceName;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceName(aAsyncHandle, out iSourceName);
        }
    };

    internal class SyncSetSourceNameLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetSourceNameLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetSourceName(aAsyncHandle);
        }
    };

    internal class SyncSourceTypeLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private String iSourceType;

        public SyncSourceTypeLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public String SourceType()
        {
            return iSourceType;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceType(aAsyncHandle, out iSourceType);
        }
    };

    internal class SyncSourceVisibleLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;
        private bool iSourceVisible;

        public SyncSourceVisibleLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        public bool SourceVisible()
        {
            return iSourceVisible;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSourceVisible(aAsyncHandle, out iSourceVisible);
        }
    };

    internal class SyncSetSourceVisibleLinnCoUkProduct3 : SyncProxyAction
    {
        private CpProxyLinnCoUkProduct3 iService;

        public SyncSetSourceVisibleLinnCoUkProduct3(CpProxyLinnCoUkProduct3 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetSourceVisible(aAsyncHandle);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Product:3 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkProduct3 : CpProxy, IDisposable, ICpProxyLinnCoUkProduct3
    {
        private Zapp.Core.Action iActionType;
        private Zapp.Core.Action iActionModel;
        private Zapp.Core.Action iActionName;
        private Zapp.Core.Action iActionSetName;
        private Zapp.Core.Action iActionRoom;
        private Zapp.Core.Action iActionSetRoom;
        private Zapp.Core.Action iActionStandby;
        private Zapp.Core.Action iActionSetStandby;
        private Zapp.Core.Action iActionSourceCount;
        private Zapp.Core.Action iActionSourceXml;
        private Zapp.Core.Action iActionSourceIndex;
        private Zapp.Core.Action iActionSetSourceIndex;
        private Zapp.Core.Action iActionSetSourceIndexByName;
        private Zapp.Core.Action iActionSetStartupSourceIndexByName;
        private Zapp.Core.Action iActionStartupSourceIndex;
        private Zapp.Core.Action iActionSetStartupSourceIndex;
        private Zapp.Core.Action iActionStartupSourceEnabled;
        private Zapp.Core.Action iActionSetStartupSourceEnabled;
        private Zapp.Core.Action iActionSourceSystemName;
        private Zapp.Core.Action iActionSourceName;
        private Zapp.Core.Action iActionSetSourceName;
        private Zapp.Core.Action iActionSourceType;
        private Zapp.Core.Action iActionSourceVisible;
        private Zapp.Core.Action iActionSetSourceVisible;
        private PropertyString iProductType;
        private PropertyString iProductModel;
        private PropertyString iProductName;
        private PropertyString iProductRoom;
        private PropertyBool iProductStandby;
        private PropertyUint iProductSourceIndex;
        private PropertyUint iProductSourceCount;
        private PropertyString iProductSourceXml;
        private PropertyUint iStartupSourceIndex;
        private PropertyBool iStartupSourceEnabled;
        private PropertyUint iProductAnySourceName;
        private PropertyUint iProductAnySourceVisible;
        private PropertyUint iProductAnySourceType;
        private CallbackPropertyChanged iProductTypeChanged;
        private CallbackPropertyChanged iProductModelChanged;
        private CallbackPropertyChanged iProductNameChanged;
        private CallbackPropertyChanged iProductRoomChanged;
        private CallbackPropertyChanged iProductStandbyChanged;
        private CallbackPropertyChanged iProductSourceIndexChanged;
        private CallbackPropertyChanged iProductSourceCountChanged;
        private CallbackPropertyChanged iProductSourceXmlChanged;
        private CallbackPropertyChanged iStartupSourceIndexChanged;
        private CallbackPropertyChanged iStartupSourceEnabledChanged;
        private CallbackPropertyChanged iProductAnySourceNameChanged;
        private CallbackPropertyChanged iProductAnySourceVisibleChanged;
        private CallbackPropertyChanged iProductAnySourceTypeChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkProduct3(CpDevice aDevice)
            : base("linn-co-uk", "Product", 3, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionType = new Zapp.Core.Action("Type");
            param = new ParameterString("aType", allowedValues);
            iActionType.AddOutputParameter(param);

            iActionModel = new Zapp.Core.Action("Model");
            param = new ParameterString("aModel", allowedValues);
            iActionModel.AddOutputParameter(param);

            iActionName = new Zapp.Core.Action("Name");
            param = new ParameterString("aName", allowedValues);
            iActionName.AddOutputParameter(param);

            iActionSetName = new Zapp.Core.Action("SetName");
            param = new ParameterString("aName", allowedValues);
            iActionSetName.AddInputParameter(param);

            iActionRoom = new Zapp.Core.Action("Room");
            param = new ParameterString("aRoom", allowedValues);
            iActionRoom.AddOutputParameter(param);

            iActionSetRoom = new Zapp.Core.Action("SetRoom");
            param = new ParameterString("aRoom", allowedValues);
            iActionSetRoom.AddInputParameter(param);

            iActionStandby = new Zapp.Core.Action("Standby");
            param = new ParameterBool("aStandby");
            iActionStandby.AddOutputParameter(param);

            iActionSetStandby = new Zapp.Core.Action("SetStandby");
            param = new ParameterBool("aStandby");
            iActionSetStandby.AddInputParameter(param);

            iActionSourceCount = new Zapp.Core.Action("SourceCount");
            param = new ParameterUint("aSourceCount");
            iActionSourceCount.AddOutputParameter(param);

            iActionSourceXml = new Zapp.Core.Action("SourceXml");
            param = new ParameterString("aSourceXml", allowedValues);
            iActionSourceXml.AddOutputParameter(param);

            iActionSourceIndex = new Zapp.Core.Action("SourceIndex");
            param = new ParameterUint("aSourceIndex");
            iActionSourceIndex.AddOutputParameter(param);

            iActionSetSourceIndex = new Zapp.Core.Action("SetSourceIndex");
            param = new ParameterUint("aSourceIndex");
            iActionSetSourceIndex.AddInputParameter(param);

            iActionSetSourceIndexByName = new Zapp.Core.Action("SetSourceIndexByName");
            param = new ParameterString("aSourceName", allowedValues);
            iActionSetSourceIndexByName.AddInputParameter(param);

            iActionSetStartupSourceIndexByName = new Zapp.Core.Action("SetStartupSourceIndexByName");
            param = new ParameterString("aSourceName", allowedValues);
            iActionSetStartupSourceIndexByName.AddInputParameter(param);

            iActionStartupSourceIndex = new Zapp.Core.Action("StartupSourceIndex");
            param = new ParameterUint("aSourceIndex");
            iActionStartupSourceIndex.AddOutputParameter(param);

            iActionSetStartupSourceIndex = new Zapp.Core.Action("SetStartupSourceIndex");
            param = new ParameterUint("aSourceIndex");
            iActionSetStartupSourceIndex.AddInputParameter(param);

            iActionStartupSourceEnabled = new Zapp.Core.Action("StartupSourceEnabled");
            param = new ParameterBool("aStartupSourceEnabled");
            iActionStartupSourceEnabled.AddOutputParameter(param);

            iActionSetStartupSourceEnabled = new Zapp.Core.Action("SetStartupSourceEnabled");
            param = new ParameterBool("aStartupSourceEnabled");
            iActionSetStartupSourceEnabled.AddInputParameter(param);

            iActionSourceSystemName = new Zapp.Core.Action("SourceSystemName");
            param = new ParameterUint("aSourceIndex");
            iActionSourceSystemName.AddInputParameter(param);
            param = new ParameterString("aSourceName", allowedValues);
            iActionSourceSystemName.AddOutputParameter(param);

            iActionSourceName = new Zapp.Core.Action("SourceName");
            param = new ParameterUint("aSourceIndex");
            iActionSourceName.AddInputParameter(param);
            param = new ParameterString("aSourceName", allowedValues);
            iActionSourceName.AddOutputParameter(param);

            iActionSetSourceName = new Zapp.Core.Action("SetSourceName");
            param = new ParameterUint("aSourceIndex");
            iActionSetSourceName.AddInputParameter(param);
            param = new ParameterString("aSourceName", allowedValues);
            iActionSetSourceName.AddInputParameter(param);

            iActionSourceType = new Zapp.Core.Action("SourceType");
            param = new ParameterUint("aSourceIndex");
            iActionSourceType.AddInputParameter(param);
            param = new ParameterString("aSourceType", allowedValues);
            iActionSourceType.AddOutputParameter(param);

            iActionSourceVisible = new Zapp.Core.Action("SourceVisible");
            param = new ParameterUint("aSourceIndex");
            iActionSourceVisible.AddInputParameter(param);
            param = new ParameterBool("aSourceVisible");
            iActionSourceVisible.AddOutputParameter(param);

            iActionSetSourceVisible = new Zapp.Core.Action("SetSourceVisible");
            param = new ParameterUint("aSourceIndex");
            iActionSetSourceVisible.AddInputParameter(param);
            param = new ParameterBool("aSourceVisible");
            iActionSetSourceVisible.AddInputParameter(param);

            iProductType = new PropertyString("ProductType", ProductTypePropertyChanged);
            AddProperty(iProductType);
            iProductModel = new PropertyString("ProductModel", ProductModelPropertyChanged);
            AddProperty(iProductModel);
            iProductName = new PropertyString("ProductName", ProductNamePropertyChanged);
            AddProperty(iProductName);
            iProductRoom = new PropertyString("ProductRoom", ProductRoomPropertyChanged);
            AddProperty(iProductRoom);
            iProductStandby = new PropertyBool("ProductStandby", ProductStandbyPropertyChanged);
            AddProperty(iProductStandby);
            iProductSourceIndex = new PropertyUint("ProductSourceIndex", ProductSourceIndexPropertyChanged);
            AddProperty(iProductSourceIndex);
            iProductSourceCount = new PropertyUint("ProductSourceCount", ProductSourceCountPropertyChanged);
            AddProperty(iProductSourceCount);
            iProductSourceXml = new PropertyString("ProductSourceXml", ProductSourceXmlPropertyChanged);
            AddProperty(iProductSourceXml);
            iStartupSourceIndex = new PropertyUint("StartupSourceIndex", StartupSourceIndexPropertyChanged);
            AddProperty(iStartupSourceIndex);
            iStartupSourceEnabled = new PropertyBool("StartupSourceEnabled", StartupSourceEnabledPropertyChanged);
            AddProperty(iStartupSourceEnabled);
            iProductAnySourceName = new PropertyUint("ProductAnySourceName", ProductAnySourceNamePropertyChanged);
            AddProperty(iProductAnySourceName);
            iProductAnySourceVisible = new PropertyUint("ProductAnySourceVisible", ProductAnySourceVisiblePropertyChanged);
            AddProperty(iProductAnySourceVisible);
            iProductAnySourceType = new PropertyUint("ProductAnySourceType", ProductAnySourceTypePropertyChanged);
            AddProperty(iProductAnySourceType);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaType"></param>
        public void SyncType(out String aType)
        {
            SyncTypeLinnCoUkProduct3 sync = new SyncTypeLinnCoUkProduct3(this);
            BeginType(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aType = sync.Type();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndType().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginType(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionType, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionType.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaType"></param>
        public void EndType(IntPtr aAsyncHandle, out String aType)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aType = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaModel"></param>
        public void SyncModel(out String aModel)
        {
            SyncModelLinnCoUkProduct3 sync = new SyncModelLinnCoUkProduct3(this);
            BeginModel(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aModel = sync.Model();
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
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaModel"></param>
        public void EndModel(IntPtr aAsyncHandle, out String aModel)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aModel = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public void SyncName(out String aName)
        {
            SyncNameLinnCoUkProduct3 sync = new SyncNameLinnCoUkProduct3(this);
            BeginName(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aName = sync.Name();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndName().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginName(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionName, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionName.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaName"></param>
        public void EndName(IntPtr aAsyncHandle, out String aName)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaName"></param>
        public void SyncSetName(String aName)
        {
            SyncSetNameLinnCoUkProduct3 sync = new SyncSetNameLinnCoUkProduct3(this);
            BeginSetName(aName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetName().</remarks>
        /// <param name="aaName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetName(String aName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetName.InputParameter(inIndex++), aName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetName(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRoom"></param>
        public void SyncRoom(out String aRoom)
        {
            SyncRoomLinnCoUkProduct3 sync = new SyncRoomLinnCoUkProduct3(this);
            BeginRoom(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRoom = sync.Room();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRoom().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginRoom(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionRoom, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionRoom.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaRoom"></param>
        public void EndRoom(IntPtr aAsyncHandle, out String aRoom)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aRoom = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaRoom"></param>
        public void SyncSetRoom(String aRoom)
        {
            SyncSetRoomLinnCoUkProduct3 sync = new SyncSetRoomLinnCoUkProduct3(this);
            BeginSetRoom(aRoom, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRoom().</remarks>
        /// <param name="aaRoom"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetRoom(String aRoom, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetRoom, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetRoom.InputParameter(inIndex++), aRoom));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetRoom(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStandby"></param>
        public void SyncStandby(out bool aStandby)
        {
            SyncStandbyLinnCoUkProduct3 sync = new SyncStandbyLinnCoUkProduct3(this);
            BeginStandby(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aStandby = sync.Standby();
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
        /// <param name="aaStandby"></param>
        public void EndStandby(IntPtr aAsyncHandle, out bool aStandby)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aStandby = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStandby"></param>
        public void SyncSetStandby(bool aStandby)
        {
            SyncSetStandbyLinnCoUkProduct3 sync = new SyncSetStandbyLinnCoUkProduct3(this);
            BeginSetStandby(aStandby, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStandby().</remarks>
        /// <param name="aaStandby"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStandby(bool aStandby, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStandby, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetStandby.InputParameter(inIndex++), aStandby));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStandby(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceCount"></param>
        public void SyncSourceCount(out uint aSourceCount)
        {
            SyncSourceCountLinnCoUkProduct3 sync = new SyncSourceCountLinnCoUkProduct3(this);
            BeginSourceCount(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceCount = sync.SourceCount();
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
        /// <param name="aaSourceCount"></param>
        public void EndSourceCount(IntPtr aAsyncHandle, out uint aSourceCount)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aSourceCount = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceXml"></param>
        public void SyncSourceXml(out String aSourceXml)
        {
            SyncSourceXmlLinnCoUkProduct3 sync = new SyncSourceXmlLinnCoUkProduct3(this);
            BeginSourceXml(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceXml = sync.SourceXml();
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
        /// <param name="aaSourceXml"></param>
        public void EndSourceXml(IntPtr aAsyncHandle, out String aSourceXml)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aSourceXml = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public void SyncSourceIndex(out uint aSourceIndex)
        {
            SyncSourceIndexLinnCoUkProduct3 sync = new SyncSourceIndexLinnCoUkProduct3(this);
            BeginSourceIndex(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceIndex = sync.SourceIndex();
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
        /// <param name="aaSourceIndex"></param>
        public void EndSourceIndex(IntPtr aAsyncHandle, out uint aSourceIndex)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aSourceIndex = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public void SyncSetSourceIndex(uint aSourceIndex)
        {
            SyncSetSourceIndexLinnCoUkProduct3 sync = new SyncSetSourceIndexLinnCoUkProduct3(this);
            BeginSetSourceIndex(aSourceIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceIndex().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetSourceIndex(uint aSourceIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetSourceIndex, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetSourceIndex.InputParameter(inIndex++), aSourceIndex));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetSourceIndex(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceName"></param>
        public void SyncSetSourceIndexByName(String aSourceName)
        {
            SyncSetSourceIndexByNameLinnCoUkProduct3 sync = new SyncSetSourceIndexByNameLinnCoUkProduct3(this);
            BeginSetSourceIndexByName(aSourceName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceIndexByName().</remarks>
        /// <param name="aaSourceName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetSourceIndexByName(String aSourceName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetSourceIndexByName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetSourceIndexByName.InputParameter(inIndex++), aSourceName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetSourceIndexByName(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceName"></param>
        public void SyncSetStartupSourceIndexByName(String aSourceName)
        {
            SyncSetStartupSourceIndexByNameLinnCoUkProduct3 sync = new SyncSetStartupSourceIndexByNameLinnCoUkProduct3(this);
            BeginSetStartupSourceIndexByName(aSourceName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupSourceIndexByName().</remarks>
        /// <param name="aaSourceName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStartupSourceIndexByName(String aSourceName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStartupSourceIndexByName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetStartupSourceIndexByName.InputParameter(inIndex++), aSourceName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStartupSourceIndexByName(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public void SyncStartupSourceIndex(out uint aSourceIndex)
        {
            SyncStartupSourceIndexLinnCoUkProduct3 sync = new SyncStartupSourceIndexLinnCoUkProduct3(this);
            BeginStartupSourceIndex(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceIndex = sync.SourceIndex();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartupSourceIndex().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartupSourceIndex(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartupSourceIndex, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionStartupSourceIndex.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceIndex"></param>
        public void EndStartupSourceIndex(IntPtr aAsyncHandle, out uint aSourceIndex)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aSourceIndex = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        public void SyncSetStartupSourceIndex(uint aSourceIndex)
        {
            SyncSetStartupSourceIndexLinnCoUkProduct3 sync = new SyncSetStartupSourceIndexLinnCoUkProduct3(this);
            BeginSetStartupSourceIndex(aSourceIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupSourceIndex().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStartupSourceIndex(uint aSourceIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStartupSourceIndex, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetStartupSourceIndex.InputParameter(inIndex++), aSourceIndex));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStartupSourceIndex(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStartupSourceEnabled"></param>
        public void SyncStartupSourceEnabled(out bool aStartupSourceEnabled)
        {
            SyncStartupSourceEnabledLinnCoUkProduct3 sync = new SyncStartupSourceEnabledLinnCoUkProduct3(this);
            BeginStartupSourceEnabled(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aStartupSourceEnabled = sync.StartupSourceEnabled();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartupSourceEnabled().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartupSourceEnabled(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartupSourceEnabled, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionStartupSourceEnabled.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaStartupSourceEnabled"></param>
        public void EndStartupSourceEnabled(IntPtr aAsyncHandle, out bool aStartupSourceEnabled)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aStartupSourceEnabled = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaStartupSourceEnabled"></param>
        public void SyncSetStartupSourceEnabled(bool aStartupSourceEnabled)
        {
            SyncSetStartupSourceEnabledLinnCoUkProduct3 sync = new SyncSetStartupSourceEnabledLinnCoUkProduct3(this);
            BeginSetStartupSourceEnabled(aStartupSourceEnabled, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStartupSourceEnabled().</remarks>
        /// <param name="aaStartupSourceEnabled"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStartupSourceEnabled(bool aStartupSourceEnabled, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStartupSourceEnabled, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetStartupSourceEnabled.InputParameter(inIndex++), aStartupSourceEnabled));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStartupSourceEnabled(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        public void SyncSourceSystemName(uint aSourceIndex, out String aSourceName)
        {
            SyncSourceSystemNameLinnCoUkProduct3 sync = new SyncSourceSystemNameLinnCoUkProduct3(this);
            BeginSourceSystemName(aSourceIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceName = sync.SourceName();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceSystemName().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceSystemName(uint aSourceIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceSystemName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSourceSystemName.InputParameter(inIndex++), aSourceIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSourceSystemName.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceName"></param>
        public void EndSourceSystemName(IntPtr aAsyncHandle, out String aSourceName)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aSourceName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        public void SyncSourceName(uint aSourceIndex, out String aSourceName)
        {
            SyncSourceNameLinnCoUkProduct3 sync = new SyncSourceNameLinnCoUkProduct3(this);
            BeginSourceName(aSourceIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceName = sync.SourceName();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceName().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceName(uint aSourceIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSourceName.InputParameter(inIndex++), aSourceIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSourceName.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceName"></param>
        public void EndSourceName(IntPtr aAsyncHandle, out String aSourceName)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aSourceName = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        public void SyncSetSourceName(uint aSourceIndex, String aSourceName)
        {
            SyncSetSourceNameLinnCoUkProduct3 sync = new SyncSetSourceNameLinnCoUkProduct3(this);
            BeginSetSourceName(aSourceIndex, aSourceName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceName().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetSourceName(uint aSourceIndex, String aSourceName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetSourceName, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetSourceName.InputParameter(inIndex++), aSourceIndex));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetSourceName.InputParameter(inIndex++), aSourceName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetSourceName(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceType"></param>
        public void SyncSourceType(uint aSourceIndex, out String aSourceType)
        {
            SyncSourceTypeLinnCoUkProduct3 sync = new SyncSourceTypeLinnCoUkProduct3(this);
            BeginSourceType(aSourceIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceType = sync.SourceType();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceType().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceType(uint aSourceIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceType, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSourceType.InputParameter(inIndex++), aSourceIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSourceType.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceType"></param>
        public void EndSourceType(IntPtr aAsyncHandle, out String aSourceType)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aSourceType = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        public void SyncSourceVisible(uint aSourceIndex, out bool aSourceVisible)
        {
            SyncSourceVisibleLinnCoUkProduct3 sync = new SyncSourceVisibleLinnCoUkProduct3(this);
            BeginSourceVisible(aSourceIndex, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSourceVisible = sync.SourceVisible();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSourceVisible().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSourceVisible(uint aSourceIndex, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSourceVisible, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSourceVisible.InputParameter(inIndex++), aSourceIndex));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionSourceVisible.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaSourceVisible"></param>
        public void EndSourceVisible(IntPtr aAsyncHandle, out bool aSourceVisible)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aSourceVisible = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        public void SyncSetSourceVisible(uint aSourceIndex, bool aSourceVisible)
        {
            SyncSetSourceVisibleLinnCoUkProduct3 sync = new SyncSetSourceVisibleLinnCoUkProduct3(this);
            BeginSetSourceVisible(aSourceIndex, aSourceVisible, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSourceVisible().</remarks>
        /// <param name="aaSourceIndex"></param>
        /// <param name="aaSourceVisible"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetSourceVisible(uint aSourceIndex, bool aSourceVisible, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetSourceVisible, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetSourceVisible.InputParameter(inIndex++), aSourceIndex));
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetSourceVisible.InputParameter(inIndex++), aSourceVisible));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetSourceVisible(IntPtr aAsyncHandle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductType state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductTypeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductTypeChanged(CallbackPropertyChanged aProductTypeChanged)
        {
            lock (iPropertyLock)
            {
                iProductTypeChanged = aProductTypeChanged;
            }
        }

        private void ProductTypePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductTypeChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductModel state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductModelChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductModelChanged(CallbackPropertyChanged aProductModelChanged)
        {
            lock (iPropertyLock)
            {
                iProductModelChanged = aProductModelChanged;
            }
        }

        private void ProductModelPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductModelChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductNameChanged(CallbackPropertyChanged aProductNameChanged)
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
        /// Set a delegate to be run when the ProductRoom state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductRoomChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductRoomChanged(CallbackPropertyChanged aProductRoomChanged)
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
        /// Set a delegate to be run when the ProductStandby state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductStandbyChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductStandbyChanged(CallbackPropertyChanged aProductStandbyChanged)
        {
            lock (iPropertyLock)
            {
                iProductStandbyChanged = aProductStandbyChanged;
            }
        }

        private void ProductStandbyPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductStandbyChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductSourceIndex state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductSourceIndexChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductSourceIndexChanged(CallbackPropertyChanged aProductSourceIndexChanged)
        {
            lock (iPropertyLock)
            {
                iProductSourceIndexChanged = aProductSourceIndexChanged;
            }
        }

        private void ProductSourceIndexPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductSourceIndexChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductSourceCount state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductSourceCountChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductSourceCountChanged(CallbackPropertyChanged aProductSourceCountChanged)
        {
            lock (iPropertyLock)
            {
                iProductSourceCountChanged = aProductSourceCountChanged;
            }
        }

        private void ProductSourceCountPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductSourceCountChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductSourceXml state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductSourceXmlChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductSourceXmlChanged(CallbackPropertyChanged aProductSourceXmlChanged)
        {
            lock (iPropertyLock)
            {
                iProductSourceXmlChanged = aProductSourceXmlChanged;
            }
        }

        private void ProductSourceXmlPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductSourceXmlChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the StartupSourceIndex state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aStartupSourceIndexChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStartupSourceIndexChanged(CallbackPropertyChanged aStartupSourceIndexChanged)
        {
            lock (iPropertyLock)
            {
                iStartupSourceIndexChanged = aStartupSourceIndexChanged;
            }
        }

        private void StartupSourceIndexPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iStartupSourceIndexChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the StartupSourceEnabled state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aStartupSourceEnabledChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStartupSourceEnabledChanged(CallbackPropertyChanged aStartupSourceEnabledChanged)
        {
            lock (iPropertyLock)
            {
                iStartupSourceEnabledChanged = aStartupSourceEnabledChanged;
            }
        }

        private void StartupSourceEnabledPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iStartupSourceEnabledChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductAnySourceName state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductAnySourceNameChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductAnySourceNameChanged(CallbackPropertyChanged aProductAnySourceNameChanged)
        {
            lock (iPropertyLock)
            {
                iProductAnySourceNameChanged = aProductAnySourceNameChanged;
            }
        }

        private void ProductAnySourceNamePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductAnySourceNameChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductAnySourceVisible state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductAnySourceVisibleChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductAnySourceVisibleChanged(CallbackPropertyChanged aProductAnySourceVisibleChanged)
        {
            lock (iPropertyLock)
            {
                iProductAnySourceVisibleChanged = aProductAnySourceVisibleChanged;
            }
        }

        private void ProductAnySourceVisiblePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductAnySourceVisibleChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ProductAnySourceType state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkProduct3 instance will not overlap.</remarks>
        /// <param name="aProductAnySourceTypeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyProductAnySourceTypeChanged(CallbackPropertyChanged aProductAnySourceTypeChanged)
        {
            lock (iPropertyLock)
            {
                iProductAnySourceTypeChanged = aProductAnySourceTypeChanged;
            }
        }

        private void ProductAnySourceTypePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iProductAnySourceTypeChanged);
            }
        }

        /// <summary>
        /// Query the value of the ProductType property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductType">Will be set to the value of the property</param>
        public String PropertyProductType()
        {
            PropertyReadLock();
            String val = iProductType.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductModel property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductModel">Will be set to the value of the property</param>
        public String PropertyProductModel()
        {
            PropertyReadLock();
            String val = iProductModel.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductName">Will be set to the value of the property</param>
        public String PropertyProductName()
        {
            PropertyReadLock();
            String val = iProductName.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductRoom property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductRoom">Will be set to the value of the property</param>
        public String PropertyProductRoom()
        {
            PropertyReadLock();
            String val = iProductRoom.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductStandby property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductStandby">Will be set to the value of the property</param>
        public bool PropertyProductStandby()
        {
            PropertyReadLock();
            bool val = iProductStandby.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductSourceIndex property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductSourceIndex">Will be set to the value of the property</param>
        public uint PropertyProductSourceIndex()
        {
            PropertyReadLock();
            uint val = iProductSourceIndex.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductSourceCount property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductSourceCount">Will be set to the value of the property</param>
        public uint PropertyProductSourceCount()
        {
            PropertyReadLock();
            uint val = iProductSourceCount.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductSourceXml property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductSourceXml">Will be set to the value of the property</param>
        public String PropertyProductSourceXml()
        {
            PropertyReadLock();
            String val = iProductSourceXml.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the StartupSourceIndex property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStartupSourceIndex">Will be set to the value of the property</param>
        public uint PropertyStartupSourceIndex()
        {
            PropertyReadLock();
            uint val = iStartupSourceIndex.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the StartupSourceEnabled property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStartupSourceEnabled">Will be set to the value of the property</param>
        public bool PropertyStartupSourceEnabled()
        {
            PropertyReadLock();
            bool val = iStartupSourceEnabled.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductAnySourceName property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductAnySourceName">Will be set to the value of the property</param>
        public uint PropertyProductAnySourceName()
        {
            PropertyReadLock();
            uint val = iProductAnySourceName.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductAnySourceVisible property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductAnySourceVisible">Will be set to the value of the property</param>
        public uint PropertyProductAnySourceVisible()
        {
            PropertyReadLock();
            uint val = iProductAnySourceVisible.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ProductAnySourceType property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aProductAnySourceType">Will be set to the value of the property</param>
        public uint PropertyProductAnySourceType()
        {
            PropertyReadLock();
            uint val = iProductAnySourceType.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyLinnCoUkProduct3()
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
                iActionType.Dispose();
                iActionModel.Dispose();
                iActionName.Dispose();
                iActionSetName.Dispose();
                iActionRoom.Dispose();
                iActionSetRoom.Dispose();
                iActionStandby.Dispose();
                iActionSetStandby.Dispose();
                iActionSourceCount.Dispose();
                iActionSourceXml.Dispose();
                iActionSourceIndex.Dispose();
                iActionSetSourceIndex.Dispose();
                iActionSetSourceIndexByName.Dispose();
                iActionSetStartupSourceIndexByName.Dispose();
                iActionStartupSourceIndex.Dispose();
                iActionSetStartupSourceIndex.Dispose();
                iActionStartupSourceEnabled.Dispose();
                iActionSetStartupSourceEnabled.Dispose();
                iActionSourceSystemName.Dispose();
                iActionSourceName.Dispose();
                iActionSetSourceName.Dispose();
                iActionSourceType.Dispose();
                iActionSourceVisible.Dispose();
                iActionSetSourceVisible.Dispose();
                iProductType.Dispose();
                iProductModel.Dispose();
                iProductName.Dispose();
                iProductRoom.Dispose();
                iProductStandby.Dispose();
                iProductSourceIndex.Dispose();
                iProductSourceCount.Dispose();
                iProductSourceXml.Dispose();
                iStartupSourceIndex.Dispose();
                iStartupSourceEnabled.Dispose();
                iProductAnySourceName.Dispose();
                iProductAnySourceVisible.Dispose();
                iProductAnySourceType.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

