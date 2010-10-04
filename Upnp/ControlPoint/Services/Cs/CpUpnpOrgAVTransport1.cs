using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp
{
    public class CpProxyUpnpOrgAVTransport1 : CpProxy, IDisposable
    {
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern uint CpProxyUpnpOrgAVTransport1Create(uint aDeviceHandle);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern void CpProxyUpnpOrgAVTransport1Destroy(uint aHandle);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncSetAVTransportURI(uint aHandle, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginSetAVTransportURI(uint aHandle, uint aInstanceID, char* aCurrentURI, char* aCurrentURIMetaData, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndSetAVTransportURI(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncSetNextAVTransportURI(uint aHandle, uint aInstanceID, char* aNextURI, char* aNextURIMetaData);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginSetNextAVTransportURI(uint aHandle, uint aInstanceID, char* aNextURI, char* aNextURIMetaData, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndSetNextAVTransportURI(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncGetMediaInfo(uint aHandle, uint aInstanceID, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginGetMediaInfo(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndGetMediaInfo(uint aHandle, uint aAsync, uint* aNrTracks, char** aMediaDuration, char** aCurrentURI, char** aCurrentURIMetaData, char** aNextURI, char** aNextURIMetaData, char** aPlayMedium, char** aRecordMedium, char** aWriteStatus);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncGetTransportInfo(uint aHandle, uint aInstanceID, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginGetTransportInfo(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndGetTransportInfo(uint aHandle, uint aAsync, char** aCurrentTransportState, char** aCurrentTransportStatus, char** aCurrentSpeed);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncGetPositionInfo(uint aHandle, uint aInstanceID, uint* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int* aRelCount, int* aAbsCount);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginGetPositionInfo(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndGetPositionInfo(uint aHandle, uint aAsync, uint* aTrack, char** aTrackDuration, char** aTrackMetaData, char** aTrackURI, char** aRelTime, char** aAbsTime, int* aRelCount, int* aAbsCount);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncGetDeviceCapabilities(uint aHandle, uint aInstanceID, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginGetDeviceCapabilities(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndGetDeviceCapabilities(uint aHandle, uint aAsync, char** aPlayMedia, char** aRecMedia, char** aRecQualityModes);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncGetTransportSettings(uint aHandle, uint aInstanceID, char** aPlayMode, char** aRecQualityMode);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginGetTransportSettings(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndGetTransportSettings(uint aHandle, uint aAsync, char** aPlayMode, char** aRecQualityMode);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncStop(uint aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginStop(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndStop(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncPlay(uint aHandle, uint aInstanceID, char* aSpeed);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginPlay(uint aHandle, uint aInstanceID, char* aSpeed, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndPlay(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncPause(uint aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginPause(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndPause(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncRecord(uint aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginRecord(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndRecord(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncSeek(uint aHandle, uint aInstanceID, char* aUnit, char* aTarget);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginSeek(uint aHandle, uint aInstanceID, char* aUnit, char* aTarget, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndSeek(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncNext(uint aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginNext(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndNext(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncPrevious(uint aHandle, uint aInstanceID);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginPrevious(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndPrevious(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncSetPlayMode(uint aHandle, uint aInstanceID, char* aNewPlayMode);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginSetPlayMode(uint aHandle, uint aInstanceID, char* aNewPlayMode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndSetPlayMode(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncSetRecordQualityMode(uint aHandle, uint aInstanceID, char* aNewRecordQualityMode);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginSetRecordQualityMode(uint aHandle, uint aInstanceID, char* aNewRecordQualityMode, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndSetRecordQualityMode(uint aHandle, uint aAsync);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1SyncGetCurrentTransportActions(uint aHandle, uint aInstanceID, char** aActions);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1BeginGetCurrentTransportActions(uint aHandle, uint aInstanceID, CallbackActionComplete aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe int CpProxyUpnpOrgAVTransport1EndGetCurrentTransportActions(uint aHandle, uint aAsync, char** aActions);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern void CpProxyUpnpOrgAVTransport1SetPropertyLastChangeChanged(uint aHandle, Callback aCallback, IntPtr aPtr);
        [DllImport("CpUpnpOrgAVTransport1")]
        static extern unsafe void CpProxyUpnpOrgAVTransport1PropertyLastChange(uint aHandle, char** aLastChange);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private GCHandle iGch;
        private CallbackPropertyChanged iLastChangeChanged;
        private Callback iCallbackLastChangeChanged;

        public CpProxyUpnpOrgAVTransport1(CpDevice aDevice)
        {
            iHandle = CpProxyUpnpOrgAVTransport1Create(aDevice.Handle());
            iGch = GCHandle.Alloc(this);
        }

        public unsafe void SyncSetAVTransportURI(uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData)
        {
			char* currentURI = (char*)Marshal.StringToHGlobalAnsi(aCurrentURI);
			char* currentURIMetaData = (char*)Marshal.StringToHGlobalAnsi(aCurrentURIMetaData);
			{
				CpProxyUpnpOrgAVTransport1SyncSetAVTransportURI(iHandle, aInstanceID, currentURI, currentURIMetaData);
			}
			Marshal.FreeHGlobal((IntPtr)currentURI);
			Marshal.FreeHGlobal((IntPtr)currentURIMetaData);
        }

        public unsafe void BeginSetAVTransportURI(uint aInstanceID, string aCurrentURI, string aCurrentURIMetaData, CallbackAsyncComplete aCallback)
        {
			char* currentURI = (char*)Marshal.StringToHGlobalAnsi(aCurrentURI);
			char* currentURIMetaData = (char*)Marshal.StringToHGlobalAnsi(aCurrentURIMetaData);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginSetAVTransportURI(iHandle, aInstanceID, currentURI, currentURIMetaData, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)currentURI);
			Marshal.FreeHGlobal((IntPtr)currentURIMetaData);
        }

        public unsafe void EndSetAVTransportURI(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndSetAVTransportURI(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetNextAVTransportURI(uint aInstanceID, string aNextURI, string aNextURIMetaData)
        {
			char* nextURI = (char*)Marshal.StringToHGlobalAnsi(aNextURI);
			char* nextURIMetaData = (char*)Marshal.StringToHGlobalAnsi(aNextURIMetaData);
			{
				CpProxyUpnpOrgAVTransport1SyncSetNextAVTransportURI(iHandle, aInstanceID, nextURI, nextURIMetaData);
			}
			Marshal.FreeHGlobal((IntPtr)nextURI);
			Marshal.FreeHGlobal((IntPtr)nextURIMetaData);
        }

        public unsafe void BeginSetNextAVTransportURI(uint aInstanceID, string aNextURI, string aNextURIMetaData, CallbackAsyncComplete aCallback)
        {
			char* nextURI = (char*)Marshal.StringToHGlobalAnsi(aNextURI);
			char* nextURIMetaData = (char*)Marshal.StringToHGlobalAnsi(aNextURIMetaData);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginSetNextAVTransportURI(iHandle, aInstanceID, nextURI, nextURIMetaData, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)nextURI);
			Marshal.FreeHGlobal((IntPtr)nextURIMetaData);
        }

        public unsafe void EndSetNextAVTransportURI(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndSetNextAVTransportURI(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetMediaInfo(uint aInstanceID, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
			char* mediaDuration;
			char* currentURI;
			char* currentURIMetaData;
			char* nextURI;
			char* nextURIMetaData;
			char* playMedium;
			char* recordMedium;
			char* writeStatus;
			fixed (uint* nrTracks = &aNrTracks)
			{
				CpProxyUpnpOrgAVTransport1SyncGetMediaInfo(iHandle, aInstanceID, nrTracks, &mediaDuration, &currentURI, &currentURIMetaData, &nextURI, &nextURIMetaData, &playMedium, &recordMedium, &writeStatus);
			}
            aMediaDuration = Marshal.PtrToStringAnsi((IntPtr)mediaDuration);
            ZappFree(mediaDuration);
            aCurrentURI = Marshal.PtrToStringAnsi((IntPtr)currentURI);
            ZappFree(currentURI);
            aCurrentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)currentURIMetaData);
            ZappFree(currentURIMetaData);
            aNextURI = Marshal.PtrToStringAnsi((IntPtr)nextURI);
            ZappFree(nextURI);
            aNextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)nextURIMetaData);
            ZappFree(nextURIMetaData);
            aPlayMedium = Marshal.PtrToStringAnsi((IntPtr)playMedium);
            ZappFree(playMedium);
            aRecordMedium = Marshal.PtrToStringAnsi((IntPtr)recordMedium);
            ZappFree(recordMedium);
            aWriteStatus = Marshal.PtrToStringAnsi((IntPtr)writeStatus);
            ZappFree(writeStatus);
        }

        public unsafe void BeginGetMediaInfo(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginGetMediaInfo(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetMediaInfo(uint aAsyncHandle, out uint aNrTracks, out string aMediaDuration, out string aCurrentURI, out string aCurrentURIMetaData, out string aNextURI, out string aNextURIMetaData, out string aPlayMedium, out string aRecordMedium, out string aWriteStatus)
        {
			char* mediaDuration;
			char* currentURI;
			char* currentURIMetaData;
			char* nextURI;
			char* nextURIMetaData;
			char* playMedium;
			char* recordMedium;
			char* writeStatus;
			fixed (uint* nrTracks = &aNrTracks)
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndGetMediaInfo(iHandle, aAsyncHandle, nrTracks, &mediaDuration, &currentURI, &currentURIMetaData, &nextURI, &nextURIMetaData, &playMedium, &recordMedium, &writeStatus))
				{
					throw(new ProxyError());
				}
			}
            aMediaDuration = Marshal.PtrToStringAnsi((IntPtr)mediaDuration);
            ZappFree(mediaDuration);
            aCurrentURI = Marshal.PtrToStringAnsi((IntPtr)currentURI);
            ZappFree(currentURI);
            aCurrentURIMetaData = Marshal.PtrToStringAnsi((IntPtr)currentURIMetaData);
            ZappFree(currentURIMetaData);
            aNextURI = Marshal.PtrToStringAnsi((IntPtr)nextURI);
            ZappFree(nextURI);
            aNextURIMetaData = Marshal.PtrToStringAnsi((IntPtr)nextURIMetaData);
            ZappFree(nextURIMetaData);
            aPlayMedium = Marshal.PtrToStringAnsi((IntPtr)playMedium);
            ZappFree(playMedium);
            aRecordMedium = Marshal.PtrToStringAnsi((IntPtr)recordMedium);
            ZappFree(recordMedium);
            aWriteStatus = Marshal.PtrToStringAnsi((IntPtr)writeStatus);
            ZappFree(writeStatus);
        }

        public unsafe void SyncGetTransportInfo(uint aInstanceID, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed)
        {
			char* currentTransportState;
			char* currentTransportStatus;
			char* currentSpeed;
			{
				CpProxyUpnpOrgAVTransport1SyncGetTransportInfo(iHandle, aInstanceID, &currentTransportState, &currentTransportStatus, &currentSpeed);
			}
            aCurrentTransportState = Marshal.PtrToStringAnsi((IntPtr)currentTransportState);
            ZappFree(currentTransportState);
            aCurrentTransportStatus = Marshal.PtrToStringAnsi((IntPtr)currentTransportStatus);
            ZappFree(currentTransportStatus);
            aCurrentSpeed = Marshal.PtrToStringAnsi((IntPtr)currentSpeed);
            ZappFree(currentSpeed);
        }

        public unsafe void BeginGetTransportInfo(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginGetTransportInfo(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetTransportInfo(uint aAsyncHandle, out string aCurrentTransportState, out string aCurrentTransportStatus, out string aCurrentSpeed)
        {
			char* currentTransportState;
			char* currentTransportStatus;
			char* currentSpeed;
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndGetTransportInfo(iHandle, aAsyncHandle, &currentTransportState, &currentTransportStatus, &currentSpeed))
				{
					throw(new ProxyError());
				}
			}
            aCurrentTransportState = Marshal.PtrToStringAnsi((IntPtr)currentTransportState);
            ZappFree(currentTransportState);
            aCurrentTransportStatus = Marshal.PtrToStringAnsi((IntPtr)currentTransportStatus);
            ZappFree(currentTransportStatus);
            aCurrentSpeed = Marshal.PtrToStringAnsi((IntPtr)currentSpeed);
            ZappFree(currentSpeed);
        }

        public unsafe void SyncGetPositionInfo(uint aInstanceID, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount)
        {
			char* trackDuration;
			char* trackMetaData;
			char* trackURI;
			char* relTime;
			char* absTime;
			fixed (uint* track = &aTrack)
			fixed (int* relCount = &aRelCount)
			fixed (int* absCount = &aAbsCount)
			{
				CpProxyUpnpOrgAVTransport1SyncGetPositionInfo(iHandle, aInstanceID, track, &trackDuration, &trackMetaData, &trackURI, &relTime, &absTime, relCount, absCount);
			}
            aTrackDuration = Marshal.PtrToStringAnsi((IntPtr)trackDuration);
            ZappFree(trackDuration);
            aTrackMetaData = Marshal.PtrToStringAnsi((IntPtr)trackMetaData);
            ZappFree(trackMetaData);
            aTrackURI = Marshal.PtrToStringAnsi((IntPtr)trackURI);
            ZappFree(trackURI);
            aRelTime = Marshal.PtrToStringAnsi((IntPtr)relTime);
            ZappFree(relTime);
            aAbsTime = Marshal.PtrToStringAnsi((IntPtr)absTime);
            ZappFree(absTime);
        }

        public unsafe void BeginGetPositionInfo(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginGetPositionInfo(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetPositionInfo(uint aAsyncHandle, out uint aTrack, out string aTrackDuration, out string aTrackMetaData, out string aTrackURI, out string aRelTime, out string aAbsTime, out int aRelCount, out int aAbsCount)
        {
			char* trackDuration;
			char* trackMetaData;
			char* trackURI;
			char* relTime;
			char* absTime;
			fixed (uint* track = &aTrack)
			fixed (int* relCount = &aRelCount)
			fixed (int* absCount = &aAbsCount)
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndGetPositionInfo(iHandle, aAsyncHandle, track, &trackDuration, &trackMetaData, &trackURI, &relTime, &absTime, relCount, absCount))
				{
					throw(new ProxyError());
				}
			}
            aTrackDuration = Marshal.PtrToStringAnsi((IntPtr)trackDuration);
            ZappFree(trackDuration);
            aTrackMetaData = Marshal.PtrToStringAnsi((IntPtr)trackMetaData);
            ZappFree(trackMetaData);
            aTrackURI = Marshal.PtrToStringAnsi((IntPtr)trackURI);
            ZappFree(trackURI);
            aRelTime = Marshal.PtrToStringAnsi((IntPtr)relTime);
            ZappFree(relTime);
            aAbsTime = Marshal.PtrToStringAnsi((IntPtr)absTime);
            ZappFree(absTime);
        }

        public unsafe void SyncGetDeviceCapabilities(uint aInstanceID, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes)
        {
			char* playMedia;
			char* recMedia;
			char* recQualityModes;
			{
				CpProxyUpnpOrgAVTransport1SyncGetDeviceCapabilities(iHandle, aInstanceID, &playMedia, &recMedia, &recQualityModes);
			}
            aPlayMedia = Marshal.PtrToStringAnsi((IntPtr)playMedia);
            ZappFree(playMedia);
            aRecMedia = Marshal.PtrToStringAnsi((IntPtr)recMedia);
            ZappFree(recMedia);
            aRecQualityModes = Marshal.PtrToStringAnsi((IntPtr)recQualityModes);
            ZappFree(recQualityModes);
        }

        public unsafe void BeginGetDeviceCapabilities(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginGetDeviceCapabilities(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetDeviceCapabilities(uint aAsyncHandle, out string aPlayMedia, out string aRecMedia, out string aRecQualityModes)
        {
			char* playMedia;
			char* recMedia;
			char* recQualityModes;
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndGetDeviceCapabilities(iHandle, aAsyncHandle, &playMedia, &recMedia, &recQualityModes))
				{
					throw(new ProxyError());
				}
			}
            aPlayMedia = Marshal.PtrToStringAnsi((IntPtr)playMedia);
            ZappFree(playMedia);
            aRecMedia = Marshal.PtrToStringAnsi((IntPtr)recMedia);
            ZappFree(recMedia);
            aRecQualityModes = Marshal.PtrToStringAnsi((IntPtr)recQualityModes);
            ZappFree(recQualityModes);
        }

        public unsafe void SyncGetTransportSettings(uint aInstanceID, out string aPlayMode, out string aRecQualityMode)
        {
			char* playMode;
			char* recQualityMode;
			{
				CpProxyUpnpOrgAVTransport1SyncGetTransportSettings(iHandle, aInstanceID, &playMode, &recQualityMode);
			}
            aPlayMode = Marshal.PtrToStringAnsi((IntPtr)playMode);
            ZappFree(playMode);
            aRecQualityMode = Marshal.PtrToStringAnsi((IntPtr)recQualityMode);
            ZappFree(recQualityMode);
        }

        public unsafe void BeginGetTransportSettings(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginGetTransportSettings(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetTransportSettings(uint aAsyncHandle, out string aPlayMode, out string aRecQualityMode)
        {
			char* playMode;
			char* recQualityMode;
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndGetTransportSettings(iHandle, aAsyncHandle, &playMode, &recQualityMode))
				{
					throw(new ProxyError());
				}
			}
            aPlayMode = Marshal.PtrToStringAnsi((IntPtr)playMode);
            ZappFree(playMode);
            aRecQualityMode = Marshal.PtrToStringAnsi((IntPtr)recQualityMode);
            ZappFree(recQualityMode);
        }

        public unsafe void SyncStop(uint aInstanceID)
        {
			{
				CpProxyUpnpOrgAVTransport1SyncStop(iHandle, aInstanceID);
			}
        }

        public unsafe void BeginStop(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginStop(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndStop(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndStop(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncPlay(uint aInstanceID, string aSpeed)
        {
			char* speed = (char*)Marshal.StringToHGlobalAnsi(aSpeed);
			{
				CpProxyUpnpOrgAVTransport1SyncPlay(iHandle, aInstanceID, speed);
			}
			Marshal.FreeHGlobal((IntPtr)speed);
        }

        public unsafe void BeginPlay(uint aInstanceID, string aSpeed, CallbackAsyncComplete aCallback)
        {
			char* speed = (char*)Marshal.StringToHGlobalAnsi(aSpeed);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginPlay(iHandle, aInstanceID, speed, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)speed);
        }

        public unsafe void EndPlay(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndPlay(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncPause(uint aInstanceID)
        {
			{
				CpProxyUpnpOrgAVTransport1SyncPause(iHandle, aInstanceID);
			}
        }

        public unsafe void BeginPause(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginPause(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndPause(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndPause(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncRecord(uint aInstanceID)
        {
			{
				CpProxyUpnpOrgAVTransport1SyncRecord(iHandle, aInstanceID);
			}
        }

        public unsafe void BeginRecord(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginRecord(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndRecord(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndRecord(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSeek(uint aInstanceID, string aUnit, string aTarget)
        {
			char* unit = (char*)Marshal.StringToHGlobalAnsi(aUnit);
			char* target = (char*)Marshal.StringToHGlobalAnsi(aTarget);
			{
				CpProxyUpnpOrgAVTransport1SyncSeek(iHandle, aInstanceID, unit, target);
			}
			Marshal.FreeHGlobal((IntPtr)unit);
			Marshal.FreeHGlobal((IntPtr)target);
        }

        public unsafe void BeginSeek(uint aInstanceID, string aUnit, string aTarget, CallbackAsyncComplete aCallback)
        {
			char* unit = (char*)Marshal.StringToHGlobalAnsi(aUnit);
			char* target = (char*)Marshal.StringToHGlobalAnsi(aTarget);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginSeek(iHandle, aInstanceID, unit, target, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)unit);
			Marshal.FreeHGlobal((IntPtr)target);
        }

        public unsafe void EndSeek(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndSeek(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncNext(uint aInstanceID)
        {
			{
				CpProxyUpnpOrgAVTransport1SyncNext(iHandle, aInstanceID);
			}
        }

        public unsafe void BeginNext(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginNext(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndNext(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndNext(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncPrevious(uint aInstanceID)
        {
			{
				CpProxyUpnpOrgAVTransport1SyncPrevious(iHandle, aInstanceID);
			}
        }

        public unsafe void BeginPrevious(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginPrevious(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndPrevious(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndPrevious(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetPlayMode(uint aInstanceID, string aNewPlayMode)
        {
			char* newPlayMode = (char*)Marshal.StringToHGlobalAnsi(aNewPlayMode);
			{
				CpProxyUpnpOrgAVTransport1SyncSetPlayMode(iHandle, aInstanceID, newPlayMode);
			}
			Marshal.FreeHGlobal((IntPtr)newPlayMode);
        }

        public unsafe void BeginSetPlayMode(uint aInstanceID, string aNewPlayMode, CallbackAsyncComplete aCallback)
        {
			char* newPlayMode = (char*)Marshal.StringToHGlobalAnsi(aNewPlayMode);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginSetPlayMode(iHandle, aInstanceID, newPlayMode, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)newPlayMode);
        }

        public unsafe void EndSetPlayMode(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndSetPlayMode(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncSetRecordQualityMode(uint aInstanceID, string aNewRecordQualityMode)
        {
			char* newRecordQualityMode = (char*)Marshal.StringToHGlobalAnsi(aNewRecordQualityMode);
			{
				CpProxyUpnpOrgAVTransport1SyncSetRecordQualityMode(iHandle, aInstanceID, newRecordQualityMode);
			}
			Marshal.FreeHGlobal((IntPtr)newRecordQualityMode);
        }

        public unsafe void BeginSetRecordQualityMode(uint aInstanceID, string aNewRecordQualityMode, CallbackAsyncComplete aCallback)
        {
			char* newRecordQualityMode = (char*)Marshal.StringToHGlobalAnsi(aNewRecordQualityMode);
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginSetRecordQualityMode(iHandle, aInstanceID, newRecordQualityMode, iActionComplete, ptr);
			Marshal.FreeHGlobal((IntPtr)newRecordQualityMode);
        }

        public unsafe void EndSetRecordQualityMode(uint aAsyncHandle)
        {
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndSetRecordQualityMode(iHandle, aAsyncHandle))
				{
					throw(new ProxyError());
				}
			}
        }

        public unsafe void SyncGetCurrentTransportActions(uint aInstanceID, out string aActions)
        {
			char* actions;
			{
				CpProxyUpnpOrgAVTransport1SyncGetCurrentTransportActions(iHandle, aInstanceID, &actions);
			}
            aActions = Marshal.PtrToStringAnsi((IntPtr)actions);
            ZappFree(actions);
        }

        public unsafe void BeginGetCurrentTransportActions(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            GCHandle gch = GCHandle.Alloc(aCallback);
            IntPtr ptr = GCHandle.ToIntPtr(gch);
            CpProxyUpnpOrgAVTransport1BeginGetCurrentTransportActions(iHandle, aInstanceID, iActionComplete, ptr);
        }

        public unsafe void EndGetCurrentTransportActions(uint aAsyncHandle, out string aActions)
        {
			char* actions;
			{
				if (0 != CpProxyUpnpOrgAVTransport1EndGetCurrentTransportActions(iHandle, aAsyncHandle, &actions))
				{
					throw(new ProxyError());
				}
			}
            aActions = Marshal.PtrToStringAnsi((IntPtr)actions);
            ZappFree(actions);
        }

        public void SetPropertyLastChangeChanged(CallbackPropertyChanged aLastChangeChanged)
        {
            iLastChangeChanged = aLastChangeChanged;
            iCallbackLastChangeChanged = new Callback(PropertyLastChangeChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            CpProxyUpnpOrgAVTransport1SetPropertyLastChangeChanged(iHandle, iCallbackLastChangeChanged, ptr);
        }

        private void PropertyLastChangeChanged(IntPtr aPtr)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpProxyUpnpOrgAVTransport1 self = (CpProxyUpnpOrgAVTransport1)gch.Target;
            self.iLastChangeChanged();
        }

        public unsafe void PropertyLastChange(out string aLastChange)
        {
			char* ptr;
            CpProxyUpnpOrgAVTransport1PropertyLastChange(iHandle, &ptr);
            aLastChange = Marshal.PtrToStringAnsi((IntPtr)ptr);
            ZappFree(ptr);
        }

        public void Dispose()
        {
            DoDispose(true);
        }

        ~CpProxyUpnpOrgAVTransport1()
        {
            DoDispose(false);
        }

        private void DoDispose(bool aDisposing)
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
            CpProxyUpnpOrgAVTransport1Destroy(handle);
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

