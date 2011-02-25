using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyLinnCoUkPlaylist1 : ICpProxy, IDisposable
    {
        void SyncRead(uint aId, out String aUri, out String aMetaData);
        void BeginRead(uint aId, CpProxy.CallbackAsyncComplete aCallback);
        void EndRead(IntPtr aAsyncHandle, out String aUri, out String aMetaData);
        void SyncReadList(String aIdList, out String aMetaDataList);
        void BeginReadList(String aIdList, CpProxy.CallbackAsyncComplete aCallback);
        void EndReadList(IntPtr aAsyncHandle, out String aMetaDataList);
        void SyncInsert(uint aAfterId, String aUri, String aMetaData, out uint aNewId);
        void BeginInsert(uint aAfterId, String aUri, String aMetaData, CpProxy.CallbackAsyncComplete aCallback);
        void EndInsert(IntPtr aAsyncHandle, out uint aNewId);
        void SyncDelete(uint aId);
        void BeginDelete(uint aId, CpProxy.CallbackAsyncComplete aCallback);
        void EndDelete(IntPtr aAsyncHandle);
        void SyncDeleteAll();
        void BeginDeleteAll(CpProxy.CallbackAsyncComplete aCallback);
        void EndDeleteAll(IntPtr aAsyncHandle);
        void SyncSetRepeat(bool aRepeat);
        void BeginSetRepeat(bool aRepeat, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRepeat(IntPtr aAsyncHandle);
        void SyncRepeat(out bool aRepeat);
        void BeginRepeat(CpProxy.CallbackAsyncComplete aCallback);
        void EndRepeat(IntPtr aAsyncHandle, out bool aRepeat);
        void SyncSetShuffle(bool aShuffle);
        void BeginSetShuffle(bool aShuffle, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetShuffle(IntPtr aAsyncHandle);
        void SyncShuffle(out bool aShuffle);
        void BeginShuffle(CpProxy.CallbackAsyncComplete aCallback);
        void EndShuffle(IntPtr aAsyncHandle, out bool aShuffle);
        void SyncTracksMax(out uint aTracksMax);
        void BeginTracksMax(CpProxy.CallbackAsyncComplete aCallback);
        void EndTracksMax(IntPtr aAsyncHandle, out uint aTracksMax);
        void SyncIdArray(out uint aIdArrayToken, out byte[] aIdArray);
        void BeginIdArray(CpProxy.CallbackAsyncComplete aCallback);
        void EndIdArray(IntPtr aAsyncHandle, out uint aIdArrayToken, out byte[] aIdArray);
        void SyncIdArrayChanged(uint aIdArrayToken, out bool aIdArrayChanged);
        void BeginIdArrayChanged(uint aIdArrayToken, CpProxy.CallbackAsyncComplete aCallback);
        void EndIdArrayChanged(IntPtr aAsyncHandle, out bool aIdArrayChanged);
        void SetPropertyIdArrayChanged(CpProxy.CallbackPropertyChanged aIdArrayChanged);
        byte[] PropertyIdArray();
        void SetPropertyRepeatChanged(CpProxy.CallbackPropertyChanged aRepeatChanged);
        bool PropertyRepeat();
        void SetPropertyShuffleChanged(CpProxy.CallbackPropertyChanged aShuffleChanged);
        bool PropertyShuffle();
        void SetPropertyTracksMaxChanged(CpProxy.CallbackPropertyChanged aTracksMaxChanged);
        uint PropertyTracksMax();
    }

    internal class SyncReadLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;
        private String iUri;
        private String iMetaData;

        public SyncReadLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        public String Uri()
        {
            return iUri;
        }
        public String MetaData()
        {
            return iMetaData;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndRead(aAsyncHandle, out iUri, out iMetaData);
        }
    };

    internal class SyncReadListLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;
        private String iMetaDataList;

        public SyncReadListLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        public String MetaDataList()
        {
            return iMetaDataList;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndReadList(aAsyncHandle, out iMetaDataList);
        }
    };

    internal class SyncInsertLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;
        private uint iNewId;

        public SyncInsertLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        public uint NewId()
        {
            return iNewId;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndInsert(aAsyncHandle, out iNewId);
        }
    };

    internal class SyncDeleteLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;

        public SyncDeleteLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDelete(aAsyncHandle);
        }
    };

    internal class SyncDeleteAllLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;

        public SyncDeleteAllLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDeleteAll(aAsyncHandle);
        }
    };

    internal class SyncSetRepeatLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;

        public SyncSetRepeatLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetRepeat(aAsyncHandle);
        }
    };

    internal class SyncRepeatLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;
        private bool iRepeat;

        public SyncRepeatLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        public bool Repeat()
        {
            return iRepeat;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndRepeat(aAsyncHandle, out iRepeat);
        }
    };

    internal class SyncSetShuffleLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;

        public SyncSetShuffleLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetShuffle(aAsyncHandle);
        }
    };

    internal class SyncShuffleLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;
        private bool iShuffle;

        public SyncShuffleLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        public bool Shuffle()
        {
            return iShuffle;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndShuffle(aAsyncHandle, out iShuffle);
        }
    };

    internal class SyncTracksMaxLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;
        private uint iTracksMax;

        public SyncTracksMaxLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        public uint TracksMax()
        {
            return iTracksMax;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndTracksMax(aAsyncHandle, out iTracksMax);
        }
    };

    internal class SyncIdArrayLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;
        private uint iIdArrayToken;
        private byte[] iIdArray;

        public SyncIdArrayLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        public uint IdArrayToken()
        {
            return iIdArrayToken;
        }
        public byte[] IdArray()
        {
            return iIdArray;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndIdArray(aAsyncHandle, out iIdArrayToken, out iIdArray);
        }
    };

    internal class SyncIdArrayChangedLinnCoUkPlaylist1 : SyncProxyAction
    {
        private CpProxyLinnCoUkPlaylist1 iService;
        private bool iIdArrayChanged;

        public SyncIdArrayChangedLinnCoUkPlaylist1(CpProxyLinnCoUkPlaylist1 aProxy)
        {
            iService = aProxy;
        }
        public bool IdArrayChanged()
        {
            return iIdArrayChanged;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndIdArrayChanged(aAsyncHandle, out iIdArrayChanged);
        }
    };

    /// <summary>
    /// Proxy for the linn.co.uk:Playlist:1 UPnP service
    /// </summary>
    public class CpProxyLinnCoUkPlaylist1 : CpProxy, IDisposable, ICpProxyLinnCoUkPlaylist1
    {
        private Zapp.Core.Action iActionRead;
        private Zapp.Core.Action iActionReadList;
        private Zapp.Core.Action iActionInsert;
        private Zapp.Core.Action iActionDelete;
        private Zapp.Core.Action iActionDeleteAll;
        private Zapp.Core.Action iActionSetRepeat;
        private Zapp.Core.Action iActionRepeat;
        private Zapp.Core.Action iActionSetShuffle;
        private Zapp.Core.Action iActionShuffle;
        private Zapp.Core.Action iActionTracksMax;
        private Zapp.Core.Action iActionIdArray;
        private Zapp.Core.Action iActionIdArrayChanged;
        private PropertyBinary iIdArray;
        private PropertyBool iRepeat;
        private PropertyBool iShuffle;
        private PropertyUint iTracksMax;
        private CallbackPropertyChanged iIdArrayChanged;
        private CallbackPropertyChanged iRepeatChanged;
        private CallbackPropertyChanged iShuffleChanged;
        private CallbackPropertyChanged iTracksMaxChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyLinnCoUkPlaylist1(CpDevice aDevice)
            : base("linn-co-uk", "Playlist", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionRead = new Zapp.Core.Action("Read");
            param = new ParameterUint("aId");
            iActionRead.AddInputParameter(param);
            param = new ParameterString("aUri", allowedValues);
            iActionRead.AddOutputParameter(param);
            param = new ParameterString("aMetaData", allowedValues);
            iActionRead.AddOutputParameter(param);

            iActionReadList = new Zapp.Core.Action("ReadList");
            param = new ParameterString("aIdList", allowedValues);
            iActionReadList.AddInputParameter(param);
            param = new ParameterString("aMetaDataList", allowedValues);
            iActionReadList.AddOutputParameter(param);

            iActionInsert = new Zapp.Core.Action("Insert");
            param = new ParameterUint("aAfterId");
            iActionInsert.AddInputParameter(param);
            param = new ParameterString("aUri", allowedValues);
            iActionInsert.AddInputParameter(param);
            param = new ParameterString("aMetaData", allowedValues);
            iActionInsert.AddInputParameter(param);
            param = new ParameterUint("aNewId");
            iActionInsert.AddOutputParameter(param);

            iActionDelete = new Zapp.Core.Action("Delete");
            param = new ParameterUint("aId");
            iActionDelete.AddInputParameter(param);

            iActionDeleteAll = new Zapp.Core.Action("DeleteAll");

            iActionSetRepeat = new Zapp.Core.Action("SetRepeat");
            param = new ParameterBool("aRepeat");
            iActionSetRepeat.AddInputParameter(param);

            iActionRepeat = new Zapp.Core.Action("Repeat");
            param = new ParameterBool("aRepeat");
            iActionRepeat.AddOutputParameter(param);

            iActionSetShuffle = new Zapp.Core.Action("SetShuffle");
            param = new ParameterBool("aShuffle");
            iActionSetShuffle.AddInputParameter(param);

            iActionShuffle = new Zapp.Core.Action("Shuffle");
            param = new ParameterBool("aShuffle");
            iActionShuffle.AddOutputParameter(param);

            iActionTracksMax = new Zapp.Core.Action("TracksMax");
            param = new ParameterUint("aTracksMax");
            iActionTracksMax.AddOutputParameter(param);

            iActionIdArray = new Zapp.Core.Action("IdArray");
            param = new ParameterUint("aIdArrayToken");
            iActionIdArray.AddOutputParameter(param);
            param = new ParameterBinary("aIdArray");
            iActionIdArray.AddOutputParameter(param);

            iActionIdArrayChanged = new Zapp.Core.Action("IdArrayChanged");
            param = new ParameterUint("aIdArrayToken");
            iActionIdArrayChanged.AddInputParameter(param);
            param = new ParameterBool("aIdArrayChanged");
            iActionIdArrayChanged.AddOutputParameter(param);

            iIdArray = new PropertyBinary("IdArray", IdArrayPropertyChanged);
            AddProperty(iIdArray);
            iRepeat = new PropertyBool("Repeat", RepeatPropertyChanged);
            AddProperty(iRepeat);
            iShuffle = new PropertyBool("Shuffle", ShufflePropertyChanged);
            AddProperty(iShuffle);
            iTracksMax = new PropertyUint("TracksMax", TracksMaxPropertyChanged);
            AddProperty(iTracksMax);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        public void SyncRead(uint aId, out String aUri, out String aMetaData)
        {
            SyncReadLinnCoUkPlaylist1 sync = new SyncReadLinnCoUkPlaylist1(this);
            BeginRead(aId, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aUri = sync.Uri();
            aMetaData = sync.MetaData();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRead().</remarks>
        /// <param name="aaId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginRead(uint aId, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionRead, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionRead.InputParameter(inIndex++), aId));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionRead.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionRead.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        public void EndRead(IntPtr aAsyncHandle, out String aUri, out String aMetaData)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aUri = Invocation.OutputString(aAsyncHandle, index++);
            aMetaData = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdList"></param>
        /// <param name="aaMetaDataList"></param>
        public void SyncReadList(String aIdList, out String aMetaDataList)
        {
            SyncReadListLinnCoUkPlaylist1 sync = new SyncReadListLinnCoUkPlaylist1(this);
            BeginReadList(aIdList, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aMetaDataList = sync.MetaDataList();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndReadList().</remarks>
        /// <param name="aaIdList"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginReadList(String aIdList, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionReadList, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionReadList.InputParameter(inIndex++), aIdList));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionReadList.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaMetaDataList"></param>
        public void EndReadList(IntPtr aAsyncHandle, out String aMetaDataList)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aMetaDataList = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaAfterId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        /// <param name="aaNewId"></param>
        public void SyncInsert(uint aAfterId, String aUri, String aMetaData, out uint aNewId)
        {
            SyncInsertLinnCoUkPlaylist1 sync = new SyncInsertLinnCoUkPlaylist1(this);
            BeginInsert(aAfterId, aUri, aMetaData, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aNewId = sync.NewId();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndInsert().</remarks>
        /// <param name="aaAfterId"></param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetaData"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginInsert(uint aAfterId, String aUri, String aMetaData, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionInsert, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionInsert.InputParameter(inIndex++), aAfterId));
            invocation.AddInput(new ArgumentString((ParameterString)iActionInsert.InputParameter(inIndex++), aUri));
            invocation.AddInput(new ArgumentString((ParameterString)iActionInsert.InputParameter(inIndex++), aMetaData));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionInsert.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaNewId"></param>
        public void EndInsert(IntPtr aAsyncHandle, out uint aNewId)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aNewId = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaId"></param>
        public void SyncDelete(uint aId)
        {
            SyncDeleteLinnCoUkPlaylist1 sync = new SyncDeleteLinnCoUkPlaylist1(this);
            BeginDelete(aId, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDelete().</remarks>
        /// <param name="aaId"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDelete(uint aId, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDelete, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionDelete.InputParameter(inIndex++), aId));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDelete(IntPtr aAsyncHandle)
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
        public void SyncDeleteAll()
        {
            SyncDeleteAllLinnCoUkPlaylist1 sync = new SyncDeleteAllLinnCoUkPlaylist1(this);
            BeginDeleteAll(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDeleteAll().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDeleteAll(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDeleteAll, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDeleteAll(IntPtr aAsyncHandle)
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
        /// <param name="aaRepeat"></param>
        public void SyncSetRepeat(bool aRepeat)
        {
            SyncSetRepeatLinnCoUkPlaylist1 sync = new SyncSetRepeatLinnCoUkPlaylist1(this);
            BeginSetRepeat(aRepeat, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRepeat().</remarks>
        /// <param name="aaRepeat"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetRepeat(bool aRepeat, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetRepeat, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetRepeat.InputParameter(inIndex++), aRepeat));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetRepeat(IntPtr aAsyncHandle)
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
        /// <param name="aaRepeat"></param>
        public void SyncRepeat(out bool aRepeat)
        {
            SyncRepeatLinnCoUkPlaylist1 sync = new SyncRepeatLinnCoUkPlaylist1(this);
            BeginRepeat(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRepeat = sync.Repeat();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndRepeat().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginRepeat(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionRepeat, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionRepeat.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaRepeat"></param>
        public void EndRepeat(IntPtr aAsyncHandle, out bool aRepeat)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aRepeat = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaShuffle"></param>
        public void SyncSetShuffle(bool aShuffle)
        {
            SyncSetShuffleLinnCoUkPlaylist1 sync = new SyncSetShuffleLinnCoUkPlaylist1(this);
            BeginSetShuffle(aShuffle, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetShuffle().</remarks>
        /// <param name="aaShuffle"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetShuffle(bool aShuffle, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetShuffle, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetShuffle.InputParameter(inIndex++), aShuffle));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetShuffle(IntPtr aAsyncHandle)
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
        /// <param name="aaShuffle"></param>
        public void SyncShuffle(out bool aShuffle)
        {
            SyncShuffleLinnCoUkPlaylist1 sync = new SyncShuffleLinnCoUkPlaylist1(this);
            BeginShuffle(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aShuffle = sync.Shuffle();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndShuffle().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginShuffle(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionShuffle, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionShuffle.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaShuffle"></param>
        public void EndShuffle(IntPtr aAsyncHandle, out bool aShuffle)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aShuffle = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaTracksMax"></param>
        public void SyncTracksMax(out uint aTracksMax)
        {
            SyncTracksMaxLinnCoUkPlaylist1 sync = new SyncTracksMaxLinnCoUkPlaylist1(this);
            BeginTracksMax(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aTracksMax = sync.TracksMax();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndTracksMax().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginTracksMax(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionTracksMax, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionTracksMax.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaTracksMax"></param>
        public void EndTracksMax(IntPtr aAsyncHandle, out uint aTracksMax)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aTracksMax = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        public void SyncIdArray(out uint aIdArrayToken, out byte[] aIdArray)
        {
            SyncIdArrayLinnCoUkPlaylist1 sync = new SyncIdArrayLinnCoUkPlaylist1(this);
            BeginIdArray(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aIdArrayToken = sync.IdArrayToken();
            aIdArray = sync.IdArray();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdArray().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginIdArray(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionIdArray, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionIdArray.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentBinary((ParameterBinary)iActionIdArray.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        public void EndIdArray(IntPtr aAsyncHandle, out uint aIdArrayToken, out byte[] aIdArray)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aIdArrayToken = Invocation.OutputUint(aAsyncHandle, index++);
            aIdArray = Invocation.OutputBinary(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArrayChanged"></param>
        public void SyncIdArrayChanged(uint aIdArrayToken, out bool aIdArrayChanged)
        {
            SyncIdArrayChangedLinnCoUkPlaylist1 sync = new SyncIdArrayChangedLinnCoUkPlaylist1(this);
            BeginIdArrayChanged(aIdArrayToken, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aIdArrayChanged = sync.IdArrayChanged();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndIdArrayChanged().</remarks>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginIdArrayChanged(uint aIdArrayToken, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionIdArrayChanged, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionIdArrayChanged.InputParameter(inIndex++), aIdArrayToken));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionIdArrayChanged.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aaIdArrayChanged"></param>
        public void EndIdArrayChanged(IntPtr aAsyncHandle, out bool aIdArrayChanged)
        {
            if (Invocation.Error(aAsyncHandle))
            {
                throw new ProxyError();
            }
            uint index = 0;
            aIdArrayChanged = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the IdArray state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPlaylist1 instance will not overlap.</remarks>
        /// <param name="aIdArrayChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIdArrayChanged(CallbackPropertyChanged aIdArrayChanged)
        {
            lock (iPropertyLock)
            {
                iIdArrayChanged = aIdArrayChanged;
            }
        }

        private void IdArrayPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iIdArrayChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Repeat state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPlaylist1 instance will not overlap.</remarks>
        /// <param name="aRepeatChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyRepeatChanged(CallbackPropertyChanged aRepeatChanged)
        {
            lock (iPropertyLock)
            {
                iRepeatChanged = aRepeatChanged;
            }
        }

        private void RepeatPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iRepeatChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the Shuffle state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPlaylist1 instance will not overlap.</remarks>
        /// <param name="aShuffleChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyShuffleChanged(CallbackPropertyChanged aShuffleChanged)
        {
            lock (iPropertyLock)
            {
                iShuffleChanged = aShuffleChanged;
            }
        }

        private void ShufflePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iShuffleChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TracksMax state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyLinnCoUkPlaylist1 instance will not overlap.</remarks>
        /// <param name="aTracksMaxChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTracksMaxChanged(CallbackPropertyChanged aTracksMaxChanged)
        {
            lock (iPropertyLock)
            {
                iTracksMaxChanged = aTracksMaxChanged;
            }
        }

        private void TracksMaxPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iTracksMaxChanged);
            }
        }

        /// <summary>
        /// Query the value of the IdArray property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aIdArray">Will be set to the value of the property</param>
        public byte[] PropertyIdArray()
        {
            PropertyReadLock();
            byte[] val = iIdArray.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the Repeat property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aRepeat">Will be set to the value of the property</param>
        public bool PropertyRepeat()
        {
            PropertyReadLock();
            bool val = iRepeat.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the Shuffle property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aShuffle">Will be set to the value of the property</param>
        public bool PropertyShuffle()
        {
            PropertyReadLock();
            bool val = iShuffle.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the TracksMax property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aTracksMax">Will be set to the value of the property</param>
        public uint PropertyTracksMax()
        {
            PropertyReadLock();
            uint val = iTracksMax.Value();
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

        ~CpProxyLinnCoUkPlaylist1()
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
                iActionRead.Dispose();
                iActionReadList.Dispose();
                iActionInsert.Dispose();
                iActionDelete.Dispose();
                iActionDeleteAll.Dispose();
                iActionSetRepeat.Dispose();
                iActionRepeat.Dispose();
                iActionSetShuffle.Dispose();
                iActionShuffle.Dispose();
                iActionTracksMax.Dispose();
                iActionIdArray.Dispose();
                iActionIdArrayChanged.Dispose();
                iIdArray.Dispose();
                iRepeat.Dispose();
                iShuffle.Dispose();
                iTracksMax.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

