using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceUpnpOrgAVTransport2 : IDisposable
    {
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern uint DvServiceUpnpOrgAVTransport2Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2Destroy(uint aHandle);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern unsafe int DvServiceUpnpOrgAVTransport2SetPropertyLastChange(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern unsafe void DvServiceUpnpOrgAVTransport2GetPropertyLastChange(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern unsafe int DvServiceUpnpOrgAVTransport2SetPropertyDRMState(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern unsafe void DvServiceUpnpOrgAVTransport2GetPropertyDRMState(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionSetAVTransportURI(uint aHandle, CallbackSetAVTransportURI aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(uint aHandle, CallbackSetNextAVTransportURI aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetMediaInfo(uint aHandle, CallbackGetMediaInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(uint aHandle, CallbackGetMediaInfo_Ext aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetTransportInfo(uint aHandle, CallbackGetTransportInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetPositionInfo(uint aHandle, CallbackGetPositionInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(uint aHandle, CallbackGetDeviceCapabilities aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetTransportSettings(uint aHandle, CallbackGetTransportSettings aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionStop(uint aHandle, CallbackStop aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionPlay(uint aHandle, CallbackPlay aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionPause(uint aHandle, CallbackPause aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionRecord(uint aHandle, CallbackRecord aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionSeek(uint aHandle, CallbackSeek aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionNext(uint aHandle, CallbackNext aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionPrevious(uint aHandle, CallbackPrevious aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionSetPlayMode(uint aHandle, CallbackSetPlayMode aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionSetRecordQualityMode(uint aHandle, CallbackSetRecordQualityMode aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(uint aHandle, CallbackGetCurrentTransportActions aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetDRMState(uint aHandle, CallbackGetDRMState aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionGetStateVariables(uint aHandle, CallbackGetStateVariables aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport2")]
        static extern void DvServiceUpnpOrgAVTransport2EnableActionSetStateVariables(uint aHandle, CallbackSetStateVariables aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData);
        private unsafe delegate int CallbackSetNextAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNextURI, char* aNextURIMetaData);
        private unsafe delegate int CallbackGetMediaInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        private unsafe delegate int CallbackGetMediaInfo_Ext(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentType, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        private unsafe delegate int CallbackGetTransportInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
        private unsafe delegate int CallbackGetPositionInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int* aRelCount, int* aAbsCount);
        private unsafe delegate int CallbackGetDeviceCapabilities(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
        private unsafe delegate int CallbackGetTransportSettings(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aPlayMode, char** aRecQualityMode);
        private unsafe delegate int CallbackStop(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackPlay(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aSpeed);
        private unsafe delegate int CallbackPause(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackRecord(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackSeek(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aUnit, char* aTarget);
        private unsafe delegate int CallbackNext(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackPrevious(IntPtr aPtr, uint aVersion, uint aInstanceID);
        private unsafe delegate int CallbackSetPlayMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewPlayMode);
        private unsafe delegate int CallbackSetRecordQualityMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewRecordQualityMode);
        private unsafe delegate int CallbackGetCurrentTransportActions(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aActions);
        private unsafe delegate int CallbackGetDRMState(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentDRMState);
        private unsafe delegate int CallbackGetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs);
        private unsafe delegate int CallbackSetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aAVTransportUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList);

        private uint iHandle;
        private GCHandle iGch;
        private CallbackSetAVTransportURI iCallbackSetAVTransportURI;
        private CallbackSetNextAVTransportURI iCallbackSetNextAVTransportURI;
        private CallbackGetMediaInfo iCallbackGetMediaInfo;
        private CallbackGetMediaInfo_Ext iCallbackGetMediaInfo_Ext;
        private CallbackGetTransportInfo iCallbackGetTransportInfo;
        private CallbackGetPositionInfo iCallbackGetPositionInfo;
        private CallbackGetDeviceCapabilities iCallbackGetDeviceCapabilities;
        private CallbackGetTransportSettings iCallbackGetTransportSettings;
        private CallbackStop iCallbackStop;
        private CallbackPlay iCallbackPlay;
        private CallbackPause iCallbackPause;
        private CallbackRecord iCallbackRecord;
        private CallbackSeek iCallbackSeek;
        private CallbackNext iCallbackNext;
        private CallbackPrevious iCallbackPrevious;
        private CallbackSetPlayMode iCallbackSetPlayMode;
        private CallbackSetRecordQualityMode iCallbackSetRecordQualityMode;
        private CallbackGetCurrentTransportActions iCallbackGetCurrentTransportActions;
        private CallbackGetDRMState iCallbackGetDRMState;
        private CallbackGetStateVariables iCallbackGetStateVariables;
        private CallbackSetStateVariables iCallbackSetStateVariables;

        public DvServiceUpnpOrgAVTransport2(DvDevice aDevice)
        {
            iHandle = DvServiceUpnpOrgAVTransport2Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyLastChange(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgAVTransport2SetPropertyLastChange(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyLastChange(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgAVTransport2GetPropertyLastChange(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        public unsafe void SetPropertyDRMState(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgAVTransport2SetPropertyDRMState(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyDRMState(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgAVTransport2GetPropertyDRMState(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionSetAVTransportURI()
        {
            iCallbackSetAVTransportURI = new CallbackSetAVTransportURI(DoSetAVTransportURI);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionSetAVTransportURI(iHandle, iCallbackSetAVTransportURI, ptr);
        }

        protected unsafe void EnableActionSetNextAVTransportURI()
        {
            iCallbackSetNextAVTransportURI = new CallbackSetNextAVTransportURI(DoSetNextAVTransportURI);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionSetNextAVTransportURI(iHandle, iCallbackSetNextAVTransportURI, ptr);
        }

        protected unsafe void EnableActionGetMediaInfo()
        {
            iCallbackGetMediaInfo = new CallbackGetMediaInfo(DoGetMediaInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetMediaInfo(iHandle, iCallbackGetMediaInfo, ptr);
        }

        protected unsafe void EnableActionGetMediaInfo_Ext()
        {
            iCallbackGetMediaInfo_Ext = new CallbackGetMediaInfo_Ext(DoGetMediaInfo_Ext);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetMediaInfo_Ext(iHandle, iCallbackGetMediaInfo_Ext, ptr);
        }

        protected unsafe void EnableActionGetTransportInfo()
        {
            iCallbackGetTransportInfo = new CallbackGetTransportInfo(DoGetTransportInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetTransportInfo(iHandle, iCallbackGetTransportInfo, ptr);
        }

        protected unsafe void EnableActionGetPositionInfo()
        {
            iCallbackGetPositionInfo = new CallbackGetPositionInfo(DoGetPositionInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetPositionInfo(iHandle, iCallbackGetPositionInfo, ptr);
        }

        protected unsafe void EnableActionGetDeviceCapabilities()
        {
            iCallbackGetDeviceCapabilities = new CallbackGetDeviceCapabilities(DoGetDeviceCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetDeviceCapabilities(iHandle, iCallbackGetDeviceCapabilities, ptr);
        }

        protected unsafe void EnableActionGetTransportSettings()
        {
            iCallbackGetTransportSettings = new CallbackGetTransportSettings(DoGetTransportSettings);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetTransportSettings(iHandle, iCallbackGetTransportSettings, ptr);
        }

        protected unsafe void EnableActionStop()
        {
            iCallbackStop = new CallbackStop(DoStop);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionStop(iHandle, iCallbackStop, ptr);
        }

        protected unsafe void EnableActionPlay()
        {
            iCallbackPlay = new CallbackPlay(DoPlay);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionPlay(iHandle, iCallbackPlay, ptr);
        }

        protected unsafe void EnableActionPause()
        {
            iCallbackPause = new CallbackPause(DoPause);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionPause(iHandle, iCallbackPause, ptr);
        }

        protected unsafe void EnableActionRecord()
        {
            iCallbackRecord = new CallbackRecord(DoRecord);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionRecord(iHandle, iCallbackRecord, ptr);
        }

        protected unsafe void EnableActionSeek()
        {
            iCallbackSeek = new CallbackSeek(DoSeek);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionSeek(iHandle, iCallbackSeek, ptr);
        }

        protected unsafe void EnableActionNext()
        {
            iCallbackNext = new CallbackNext(DoNext);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionNext(iHandle, iCallbackNext, ptr);
        }

        protected unsafe void EnableActionPrevious()
        {
            iCallbackPrevious = new CallbackPrevious(DoPrevious);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionPrevious(iHandle, iCallbackPrevious, ptr);
        }

        protected unsafe void EnableActionSetPlayMode()
        {
            iCallbackSetPlayMode = new CallbackSetPlayMode(DoSetPlayMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionSetPlayMode(iHandle, iCallbackSetPlayMode, ptr);
        }

        protected unsafe void EnableActionSetRecordQualityMode()
        {
            iCallbackSetRecordQualityMode = new CallbackSetRecordQualityMode(DoSetRecordQualityMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionSetRecordQualityMode(iHandle, iCallbackSetRecordQualityMode, ptr);
        }

        protected unsafe void EnableActionGetCurrentTransportActions()
        {
            iCallbackGetCurrentTransportActions = new CallbackGetCurrentTransportActions(DoGetCurrentTransportActions);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetCurrentTransportActions(iHandle, iCallbackGetCurrentTransportActions, ptr);
        }

        protected unsafe void EnableActionGetDRMState()
        {
            iCallbackGetDRMState = new CallbackGetDRMState(DoGetDRMState);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetDRMState(iHandle, iCallbackGetDRMState, ptr);
        }

        protected unsafe void EnableActionGetStateVariables()
        {
            iCallbackGetStateVariables = new CallbackGetStateVariables(DoGetStateVariables);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionGetStateVariables(iHandle, iCallbackGetStateVariables, ptr);
        }

        protected unsafe void EnableActionSetStateVariables()
        {
            iCallbackSetStateVariables = new CallbackSetStateVariables(DoSetStateVariables);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport2EnableActionSetStateVariables(iHandle, iCallbackSetStateVariables, ptr);
        }

        protected virtual void SetAVTransportURI(uint aVersion, uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetNextAVTransportURI(uint aVersion, uint aInstanceID, string aNextURI, string aNextURIMetaData)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetMediaInfo(uint aVersion, uint aInstanceID, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetMediaInfo_Ext(uint aVersion, uint aInstanceID, out string aCurrentType, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetTransportInfo(uint aVersion, uint aInstanceID, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetPositionInfo(uint aVersion, uint aInstanceID, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetDeviceCapabilities(uint aVersion, uint aInstanceID, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetTransportSettings(uint aVersion, uint aInstanceID, out string aPlayMode, out string aRecQualityMode)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Stop(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Play(uint aVersion, uint aInstanceID, string aSpeed)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Pause(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Record(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Seek(uint aVersion, uint aInstanceID, string aUnit, string aTarget)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Next(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void Previous(uint aVersion, uint aInstanceID)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetPlayMode(uint aVersion, uint aInstanceID, string aNewPlayMode)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetRecordQualityMode(uint aVersion, uint aInstanceID, string aNewRecordQualityMode)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetCurrentTransportActions(uint aVersion, uint aInstanceID, out string aActions)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetDRMState(uint aVersion, uint aInstanceID, out string aCurrentDRMState)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void GetStateVariables(uint aVersion, uint aInstanceID, string aStateVariableList, out string aStateVariableValuePairs)
        {
            throw (new ActionDisabledError());
        }

        protected virtual void SetStateVariables(uint aVersion, uint aInstanceID, string aAVTransportUDN, string aServiceType, string aServiceId, string aStateVariableValuePairs, out string aStateVariableList)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoSetAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string currentURI = Marshal.PtrToStringAnsi((IntPtr)aCurrentURI);
            string currentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)aCurrentURIMetaData);
            self.SetAVTransportURI(aVersion, aInstanceID, currentURI, currentURIMetaData);
            return 0;
        }

        private static unsafe int DoSetNextAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNextURI, char* aNextURIMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string nextURI = Marshal.PtrToStringAnsi((IntPtr)aNextURI);
            string nextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)aNextURIMetaData);
            self.SetNextAVTransportURI(aVersion, aInstanceID, nextURI, nextURIMetaData);
            return 0;
        }

        private static unsafe int DoGetMediaInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            uint nrTracks;
            string mediaDuration;
            string currentURI;
            string currentURIMetaData;
            string nextURI;
            string nextURIMetaData;
            string playMedium;
            string recordMedium;
            string writeStatus;
            self.GetMediaInfo(aVersion, aInstanceID, out nrTracks, out mediaDuration, out currentURI, out currentURIMetaData, out nextURI, out nextURIMetaData, out playMedium, out recordMedium, out writeStatus);
            *aNrTracks = nrTracks;
            *aMediaDuration = (char*)Marshal.StringToHGlobalAnsi(mediaDuration).ToPointer();
            *aCurrentURI = (char*)Marshal.StringToHGlobalAnsi(currentURI).ToPointer();
            *aCurrentURIMetaData = (char*)Marshal.StringToHGlobalAnsi(currentURIMetaData).ToPointer();
            *aNextURI = (char*)Marshal.StringToHGlobalAnsi(nextURI).ToPointer();
            *aNextURIMetaData = (char*)Marshal.StringToHGlobalAnsi(nextURIMetaData).ToPointer();
            *aPlayMedium = (char*)Marshal.StringToHGlobalAnsi(playMedium).ToPointer();
            *aRecordMedium = (char*)Marshal.StringToHGlobalAnsi(recordMedium).ToPointer();
            *aWriteStatus = (char*)Marshal.StringToHGlobalAnsi(writeStatus).ToPointer();
            return 0;
        }

        private static unsafe int DoGetMediaInfo_Ext(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentType, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string currentType;
            uint nrTracks;
            string mediaDuration;
            string currentURI;
            string currentURIMetaData;
            string nextURI;
            string nextURIMetaData;
            string playMedium;
            string recordMedium;
            string writeStatus;
            self.GetMediaInfo_Ext(aVersion, aInstanceID, out currentType, out nrTracks, out mediaDuration, out currentURI, out currentURIMetaData, out nextURI, out nextURIMetaData, out playMedium, out recordMedium, out writeStatus);
            *aCurrentType = (char*)Marshal.StringToHGlobalAnsi(currentType).ToPointer();
            *aNrTracks = nrTracks;
            *aMediaDuration = (char*)Marshal.StringToHGlobalAnsi(mediaDuration).ToPointer();
            *aCurrentURI = (char*)Marshal.StringToHGlobalAnsi(currentURI).ToPointer();
            *aCurrentURIMetaData = (char*)Marshal.StringToHGlobalAnsi(currentURIMetaData).ToPointer();
            *aNextURI = (char*)Marshal.StringToHGlobalAnsi(nextURI).ToPointer();
            *aNextURIMetaData = (char*)Marshal.StringToHGlobalAnsi(nextURIMetaData).ToPointer();
            *aPlayMedium = (char*)Marshal.StringToHGlobalAnsi(playMedium).ToPointer();
            *aRecordMedium = (char*)Marshal.StringToHGlobalAnsi(recordMedium).ToPointer();
            *aWriteStatus = (char*)Marshal.StringToHGlobalAnsi(writeStatus).ToPointer();
            return 0;
        }

        private static unsafe int DoGetTransportInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string currentTransportState;
            string currentTransportStatus;
            string currentSpeed;
            self.GetTransportInfo(aVersion, aInstanceID, out currentTransportState, out currentTransportStatus, out currentSpeed);
            *aCurrentTransportState = (char*)Marshal.StringToHGlobalAnsi(currentTransportState).ToPointer();
            *aCurrentTransportStatus = (char*)Marshal.StringToHGlobalAnsi(currentTransportStatus).ToPointer();
            *aCurrentSpeed = (char*)Marshal.StringToHGlobalAnsi(currentSpeed).ToPointer();
            return 0;
        }

        private static unsafe int DoGetPositionInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int* aRelCount, int* aAbsCount)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            uint track;
            string trackDuration;
            string trackMetaData;
            string trackURI;
            string relTime;
            string absTime;
            int relCount;
            int absCount;
            self.GetPositionInfo(aVersion, aInstanceID, out track, out trackDuration, out trackMetaData, out trackURI, out relTime, out absTime, out relCount, out absCount);
            *aTrack = track;
            *aTrackDuration = (char*)Marshal.StringToHGlobalAnsi(trackDuration).ToPointer();
            *aTrackMetaData = (char*)Marshal.StringToHGlobalAnsi(trackMetaData).ToPointer();
            *aTrackURI = (char*)Marshal.StringToHGlobalAnsi(trackURI).ToPointer();
            *aRelTime = (char*)Marshal.StringToHGlobalAnsi(relTime).ToPointer();
            *aAbsTime = (char*)Marshal.StringToHGlobalAnsi(absTime).ToPointer();
            *aRelCount = relCount;
            *aAbsCount = absCount;
            return 0;
        }

        private static unsafe int DoGetDeviceCapabilities(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string playMedia;
            string recMedia;
            string recQualityModes;
            self.GetDeviceCapabilities(aVersion, aInstanceID, out playMedia, out recMedia, out recQualityModes);
            *aPlayMedia = (char*)Marshal.StringToHGlobalAnsi(playMedia).ToPointer();
            *aRecMedia = (char*)Marshal.StringToHGlobalAnsi(recMedia).ToPointer();
            *aRecQualityModes = (char*)Marshal.StringToHGlobalAnsi(recQualityModes).ToPointer();
            return 0;
        }

        private static unsafe int DoGetTransportSettings(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aPlayMode, char** aRecQualityMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string playMode;
            string recQualityMode;
            self.GetTransportSettings(aVersion, aInstanceID, out playMode, out recQualityMode);
            *aPlayMode = (char*)Marshal.StringToHGlobalAnsi(playMode).ToPointer();
            *aRecQualityMode = (char*)Marshal.StringToHGlobalAnsi(recQualityMode).ToPointer();
            return 0;
        }

        private static unsafe int DoStop(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            self.Stop(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoPlay(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aSpeed)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string speed = Marshal.PtrToStringAnsi((IntPtr)aSpeed);
            self.Play(aVersion, aInstanceID, speed);
            return 0;
        }

        private static unsafe int DoPause(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            self.Pause(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoRecord(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            self.Record(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoSeek(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aUnit, char* aTarget)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string unit = Marshal.PtrToStringAnsi((IntPtr)aUnit);
            string target = Marshal.PtrToStringAnsi((IntPtr)aTarget);
            self.Seek(aVersion, aInstanceID, unit, target);
            return 0;
        }

        private static unsafe int DoNext(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            self.Next(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoPrevious(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            self.Previous(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoSetPlayMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewPlayMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string newPlayMode = Marshal.PtrToStringAnsi((IntPtr)aNewPlayMode);
            self.SetPlayMode(aVersion, aInstanceID, newPlayMode);
            return 0;
        }

        private static unsafe int DoSetRecordQualityMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewRecordQualityMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string newRecordQualityMode = Marshal.PtrToStringAnsi((IntPtr)aNewRecordQualityMode);
            self.SetRecordQualityMode(aVersion, aInstanceID, newRecordQualityMode);
            return 0;
        }

        private static unsafe int DoGetCurrentTransportActions(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aActions)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string actions;
            self.GetCurrentTransportActions(aVersion, aInstanceID, out actions);
            *aActions = (char*)Marshal.StringToHGlobalAnsi(actions).ToPointer();
            return 0;
        }

        private static unsafe int DoGetDRMState(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentDRMState)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string currentDRMState;
            self.GetDRMState(aVersion, aInstanceID, out currentDRMState);
            *aCurrentDRMState = (char*)Marshal.StringToHGlobalAnsi(currentDRMState).ToPointer();
            return 0;
        }

        private static unsafe int DoGetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aStateVariableList, char** aStateVariableValuePairs)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string stateVariableList = Marshal.PtrToStringAnsi((IntPtr)aStateVariableList);
            string stateVariableValuePairs;
            self.GetStateVariables(aVersion, aInstanceID, stateVariableList, out stateVariableValuePairs);
            *aStateVariableValuePairs = (char*)Marshal.StringToHGlobalAnsi(stateVariableValuePairs).ToPointer();
            return 0;
        }

        private static unsafe int DoSetStateVariables(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aAVTransportUDN, char* aServiceType, char* aServiceId, char* aStateVariableValuePairs, char** aStateVariableList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport2 self = (DvServiceUpnpOrgAVTransport2)gch.Target;
            string aVTransportUDN = Marshal.PtrToStringAnsi((IntPtr)aAVTransportUDN);
            string serviceType = Marshal.PtrToStringAnsi((IntPtr)aServiceType);
            string serviceId = Marshal.PtrToStringAnsi((IntPtr)aServiceId);
            string stateVariableValuePairs = Marshal.PtrToStringAnsi((IntPtr)aStateVariableValuePairs);
            string stateVariableList;
            self.SetStateVariables(aVersion, aInstanceID, aVTransportUDN, serviceType, serviceId, stateVariableValuePairs, out stateVariableList);
            *aStateVariableList = (char*)Marshal.StringToHGlobalAnsi(stateVariableList).ToPointer();
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceUpnpOrgAVTransport2()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            uint handle;
            lock (this)
            {
                if (iHandle == 0)
                {
                    return;
                }
                handle = iHandle;
                iHandle = 0;
            }
            DvServiceUpnpOrgAVTransport2Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

