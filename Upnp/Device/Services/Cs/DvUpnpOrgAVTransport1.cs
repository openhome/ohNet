using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class DvServiceUpnpOrgAVTransport1 : IDisposable
    {
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern uint DvServiceUpnpOrgAVTransport1Create(uint aDeviceHandle);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1Destroy(uint aHandle);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern unsafe int DvServiceUpnpOrgAVTransport1SetPropertyLastChange(uint aHandle, char* aValue);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern unsafe void DvServiceUpnpOrgAVTransport1GetPropertyLastChange(uint aHandle, char** aValue);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionSetAVTransportURI(uint aHandle, CallbackSetAVTransportURI aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionSetNextAVTransportURI(uint aHandle, CallbackSetNextAVTransportURI aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionGetMediaInfo(uint aHandle, CallbackGetMediaInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionGetTransportInfo(uint aHandle, CallbackGetTransportInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionGetPositionInfo(uint aHandle, CallbackGetPositionInfo aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionGetDeviceCapabilities(uint aHandle, CallbackGetDeviceCapabilities aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionGetTransportSettings(uint aHandle, CallbackGetTransportSettings aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionStop(uint aHandle, CallbackStop aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionPlay(uint aHandle, CallbackPlay aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionPause(uint aHandle, CallbackPause aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionRecord(uint aHandle, CallbackRecord aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionSeek(uint aHandle, CallbackSeek aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionNext(uint aHandle, CallbackNext aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionPrevious(uint aHandle, CallbackPrevious aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionSetPlayMode(uint aHandle, CallbackSetPlayMode aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionSetRecordQualityMode(uint aHandle, CallbackSetRecordQualityMode aCallback, IntPtr aPtr);
        [DllImport("DvUpnpOrgAVTransport1")]
        static extern void DvServiceUpnpOrgAVTransport1EnableActionGetCurrentTransportActions(uint aHandle, CallbackGetCurrentTransportActions aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackSetAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData);
        private unsafe delegate int CallbackSetNextAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNextURI, char* aNextURIMetaData);
        private unsafe delegate int CallbackGetMediaInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
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

        private uint iHandle;
        private GCHandle iGch;
        private CallbackSetAVTransportURI iCallbackSetAVTransportURI;
        private CallbackSetNextAVTransportURI iCallbackSetNextAVTransportURI;
        private CallbackGetMediaInfo iCallbackGetMediaInfo;
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

        public DvServiceUpnpOrgAVTransport1(DvDevice aDevice)
        {
            iHandle = DvServiceUpnpOrgAVTransport1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SetPropertyLastChange(string aValue)
        {
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvServiceUpnpOrgAVTransport1SetPropertyLastChange(iHandle, value);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
        }

        public unsafe void GetPropertyLastChange(out string aValue)
        {
            char* value;
            DvServiceUpnpOrgAVTransport1GetPropertyLastChange(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        protected unsafe void EnableActionSetAVTransportURI()
        {
            iCallbackSetAVTransportURI = new CallbackSetAVTransportURI(DoSetAVTransportURI);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionSetAVTransportURI(iHandle, iCallbackSetAVTransportURI, ptr);
        }

        protected unsafe void EnableActionSetNextAVTransportURI()
        {
            iCallbackSetNextAVTransportURI = new CallbackSetNextAVTransportURI(DoSetNextAVTransportURI);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionSetNextAVTransportURI(iHandle, iCallbackSetNextAVTransportURI, ptr);
        }

        protected unsafe void EnableActionGetMediaInfo()
        {
            iCallbackGetMediaInfo = new CallbackGetMediaInfo(DoGetMediaInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionGetMediaInfo(iHandle, iCallbackGetMediaInfo, ptr);
        }

        protected unsafe void EnableActionGetTransportInfo()
        {
            iCallbackGetTransportInfo = new CallbackGetTransportInfo(DoGetTransportInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionGetTransportInfo(iHandle, iCallbackGetTransportInfo, ptr);
        }

        protected unsafe void EnableActionGetPositionInfo()
        {
            iCallbackGetPositionInfo = new CallbackGetPositionInfo(DoGetPositionInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionGetPositionInfo(iHandle, iCallbackGetPositionInfo, ptr);
        }

        protected unsafe void EnableActionGetDeviceCapabilities()
        {
            iCallbackGetDeviceCapabilities = new CallbackGetDeviceCapabilities(DoGetDeviceCapabilities);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionGetDeviceCapabilities(iHandle, iCallbackGetDeviceCapabilities, ptr);
        }

        protected unsafe void EnableActionGetTransportSettings()
        {
            iCallbackGetTransportSettings = new CallbackGetTransportSettings(DoGetTransportSettings);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionGetTransportSettings(iHandle, iCallbackGetTransportSettings, ptr);
        }

        protected unsafe void EnableActionStop()
        {
            iCallbackStop = new CallbackStop(DoStop);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionStop(iHandle, iCallbackStop, ptr);
        }

        protected unsafe void EnableActionPlay()
        {
            iCallbackPlay = new CallbackPlay(DoPlay);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionPlay(iHandle, iCallbackPlay, ptr);
        }

        protected unsafe void EnableActionPause()
        {
            iCallbackPause = new CallbackPause(DoPause);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionPause(iHandle, iCallbackPause, ptr);
        }

        protected unsafe void EnableActionRecord()
        {
            iCallbackRecord = new CallbackRecord(DoRecord);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionRecord(iHandle, iCallbackRecord, ptr);
        }

        protected unsafe void EnableActionSeek()
        {
            iCallbackSeek = new CallbackSeek(DoSeek);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionSeek(iHandle, iCallbackSeek, ptr);
        }

        protected unsafe void EnableActionNext()
        {
            iCallbackNext = new CallbackNext(DoNext);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionNext(iHandle, iCallbackNext, ptr);
        }

        protected unsafe void EnableActionPrevious()
        {
            iCallbackPrevious = new CallbackPrevious(DoPrevious);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionPrevious(iHandle, iCallbackPrevious, ptr);
        }

        protected unsafe void EnableActionSetPlayMode()
        {
            iCallbackSetPlayMode = new CallbackSetPlayMode(DoSetPlayMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionSetPlayMode(iHandle, iCallbackSetPlayMode, ptr);
        }

        protected unsafe void EnableActionSetRecordQualityMode()
        {
            iCallbackSetRecordQualityMode = new CallbackSetRecordQualityMode(DoSetRecordQualityMode);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionSetRecordQualityMode(iHandle, iCallbackSetRecordQualityMode, ptr);
        }

        protected unsafe void EnableActionGetCurrentTransportActions()
        {
            iCallbackGetCurrentTransportActions = new CallbackGetCurrentTransportActions(DoGetCurrentTransportActions);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvServiceUpnpOrgAVTransport1EnableActionGetCurrentTransportActions(iHandle, iCallbackGetCurrentTransportActions, ptr);
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

        private static unsafe int DoSetAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            string currentURI = Marshal.PtrToStringAnsi((IntPtr)aCurrentURI);
            string currentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)aCurrentURIMetaData);
            self.SetAVTransportURI(aVersion, aInstanceID, currentURI, currentURIMetaData);
            return 0;
        }

        private static unsafe int DoSetNextAVTransportURI(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNextURI, char* aNextURIMetaData)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            string nextURI = Marshal.PtrToStringAnsi((IntPtr)aNextURI);
            string nextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)aNextURIMetaData);
            self.SetNextAVTransportURI(aVersion, aInstanceID, nextURI, nextURIMetaData);
            return 0;
        }

        private static unsafe int DoGetMediaInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
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

        private static unsafe int DoGetTransportInfo(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
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
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
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
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
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
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
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
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            self.Stop(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoPlay(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aSpeed)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            string speed = Marshal.PtrToStringAnsi((IntPtr)aSpeed);
            self.Play(aVersion, aInstanceID, speed);
            return 0;
        }

        private static unsafe int DoPause(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            self.Pause(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoRecord(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            self.Record(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoSeek(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aUnit, char* aTarget)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            string unit = Marshal.PtrToStringAnsi((IntPtr)aUnit);
            string target = Marshal.PtrToStringAnsi((IntPtr)aTarget);
            self.Seek(aVersion, aInstanceID, unit, target);
            return 0;
        }

        private static unsafe int DoNext(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            self.Next(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoPrevious(IntPtr aPtr, uint aVersion, uint aInstanceID)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            self.Previous(aVersion, aInstanceID);
            return 0;
        }

        private static unsafe int DoSetPlayMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewPlayMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            string newPlayMode = Marshal.PtrToStringAnsi((IntPtr)aNewPlayMode);
            self.SetPlayMode(aVersion, aInstanceID, newPlayMode);
            return 0;
        }

        private static unsafe int DoSetRecordQualityMode(IntPtr aPtr, uint aVersion, uint aInstanceID, char* aNewRecordQualityMode)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            string newRecordQualityMode = Marshal.PtrToStringAnsi((IntPtr)aNewRecordQualityMode);
            self.SetRecordQualityMode(aVersion, aInstanceID, newRecordQualityMode);
            return 0;
        }

        private static unsafe int DoGetCurrentTransportActions(IntPtr aPtr, uint aVersion, uint aInstanceID, char** aActions)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvServiceUpnpOrgAVTransport1 self = (DvServiceUpnpOrgAVTransport1)gch.Target;
            string actions;
            self.GetCurrentTransportActions(aVersion, aInstanceID, out actions);
            *aActions = (char*)Marshal.StringToHGlobalAnsi(actions).ToPointer();
            return 0;
        }


        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvServiceUpnpOrgAVTransport1()
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
            DvServiceUpnpOrgAVTransport1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

