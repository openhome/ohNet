using System;
using System.Runtime.InteropServices;
using System.Text;
using Zapp;

namespace Zapp.Device.Providers
{
    public interface IDvProviderLinnCoUkRadio1 : IDisposable
    {

        /// <summary>
        /// Set the value of the ChannelUri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyChannelUri(string aValue);

        /// <summary>
        /// Get a copy of the value of the ChannelUri property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyChannelUri(out string aValue);

        /// <summary>
        /// Set the value of the ChannelMetadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyChannelMetadata(string aValue);

        /// <summary>
        /// Get a copy of the value of the ChannelMetadata property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyChannelMetadata(out string aValue);

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyTransportState(string aValue);

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyTransportState(out string aValue);

        /// <summary>
        /// Set the value of the ProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProtocolInfo(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProtocolInfo property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyProtocolInfo(out string aValue);

        /// <summary>
        /// Set the value of the Id property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyId(uint aValue);

        /// <summary>
        /// Get a copy of the value of the Id property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyId(out uint aValue);

        /// <summary>
        /// Set the value of the IdArray property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyIdArray(string aValue);

        /// <summary>
        /// Get a copy of the value of the IdArray property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyIdArray(out string aValue);

        /// <summary>
        /// Set the value of the IdsMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyIdsMax(uint aValue);

        /// <summary>
        /// Get a copy of the value of the IdsMax property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        void GetPropertyIdsMax(out uint aValue);
        
    }
    /// <summary>
    /// Provider for the linn.co.uk:Radio:1 UPnP service
    /// </summary>
    public class DvProviderLinnCoUkRadio1 : DvProvider, IDisposable, IDvProviderLinnCoUkRadio1
    {
        [DllImport("DvLinnCoUkRadio1")]
        static extern IntPtr DvProviderLinnCoUkRadio1Create(IntPtr aDeviceHandle);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1Destroy(IntPtr aHandle);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe int DvProviderLinnCoUkRadio1SetPropertyChannelUri(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe void DvProviderLinnCoUkRadio1GetPropertyChannelUri(IntPtr aHandle, char** aValue);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe int DvProviderLinnCoUkRadio1SetPropertyChannelMetadata(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe void DvProviderLinnCoUkRadio1GetPropertyChannelMetadata(IntPtr aHandle, char** aValue);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe int DvProviderLinnCoUkRadio1SetPropertyTransportState(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe void DvProviderLinnCoUkRadio1GetPropertyTransportState(IntPtr aHandle, char** aValue);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe int DvProviderLinnCoUkRadio1SetPropertyProtocolInfo(IntPtr aHandle, char* aValue, uint* aChanged);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe void DvProviderLinnCoUkRadio1GetPropertyProtocolInfo(IntPtr aHandle, char** aValue);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe int DvProviderLinnCoUkRadio1SetPropertyId(IntPtr aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe void DvProviderLinnCoUkRadio1GetPropertyId(IntPtr aHandle, uint* aValue);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe int DvProviderLinnCoUkRadio1SetPropertyIdArray(IntPtr aHandle, char* aValue, int aValueLen, uint* aChanged);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe void DvProviderLinnCoUkRadio1GetPropertyIdArray(IntPtr aHandle, char** aValue, int* aValueLen);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe int DvProviderLinnCoUkRadio1SetPropertyIdsMax(IntPtr aHandle, uint aValue, uint* aChanged);
        [DllImport("DvLinnCoUkRadio1")]
        static extern unsafe void DvProviderLinnCoUkRadio1GetPropertyIdsMax(IntPtr aHandle, uint* aValue);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionPlay(IntPtr aHandle, CallbackPlay aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionPause(IntPtr aHandle, CallbackPause aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionStop(IntPtr aHandle, CallbackStop aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionSeekSecondAbsolute(IntPtr aHandle, CallbackSeekSecondAbsolute aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionSeekSecondRelative(IntPtr aHandle, CallbackSeekSecondRelative aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionChannel(IntPtr aHandle, CallbackChannel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionSetChannel(IntPtr aHandle, CallbackSetChannel aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionProtocolInfo(IntPtr aHandle, CallbackProtocolInfo aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionTransportState(IntPtr aHandle, CallbackTransportState aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionId(IntPtr aHandle, CallbackId aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionSetId(IntPtr aHandle, CallbackSetId aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionRead(IntPtr aHandle, CallbackRead aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionReadList(IntPtr aHandle, CallbackReadList aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionIdArray(IntPtr aHandle, CallbackIdArray aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionIdArrayChanged(IntPtr aHandle, CallbackIdArrayChanged aCallback, IntPtr aPtr);
        [DllImport("DvLinnCoUkRadio1")]
        static extern void DvProviderLinnCoUkRadio1EnableActionIdsMax(IntPtr aHandle, CallbackIdsMax aCallback, IntPtr aPtr);
        [DllImport("ZappUpnp")]
        static extern unsafe void ZappFree(void* aPtr);

        private unsafe delegate int CallbackPlay(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackPause(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackStop(IntPtr aPtr, uint aVersion);
        private unsafe delegate int CallbackSeekSecondAbsolute(IntPtr aPtr, uint aVersion, uint aaSecond);
        private unsafe delegate int CallbackSeekSecondRelative(IntPtr aPtr, uint aVersion, int aaSecond);
        private unsafe delegate int CallbackChannel(IntPtr aPtr, uint aVersion, char** aaUri, char** aaMetadata);
        private unsafe delegate int CallbackSetChannel(IntPtr aPtr, uint aVersion, char* aaUri, char* aaMetadata);
        private unsafe delegate int CallbackProtocolInfo(IntPtr aPtr, uint aVersion, char** aaInfo);
        private unsafe delegate int CallbackTransportState(IntPtr aPtr, uint aVersion, char** aaState);
        private unsafe delegate int CallbackId(IntPtr aPtr, uint aVersion, uint* aaId);
        private unsafe delegate int CallbackSetId(IntPtr aPtr, uint aVersion, uint aaId, char* aaUri);
        private unsafe delegate int CallbackRead(IntPtr aPtr, uint aVersion, uint aaId, char** aaMetadata);
        private unsafe delegate int CallbackReadList(IntPtr aPtr, uint aVersion, char* aaIdList, char** aaMetadataList);
        private unsafe delegate int CallbackIdArray(IntPtr aPtr, uint aVersion, uint* aaIdArrayToken, char** aaIdArray, int* aaIdArrayLen);
        private unsafe delegate int CallbackIdArrayChanged(IntPtr aPtr, uint aVersion, uint aaIdArrayToken, int* aaIdArrayChanged);
        private unsafe delegate int CallbackIdsMax(IntPtr aPtr, uint aVersion, uint* aaIdsMax);

        private GCHandle iGch;
        private CallbackPlay iCallbackPlay;
        private CallbackPause iCallbackPause;
        private CallbackStop iCallbackStop;
        private CallbackSeekSecondAbsolute iCallbackSeekSecondAbsolute;
        private CallbackSeekSecondRelative iCallbackSeekSecondRelative;
        private CallbackChannel iCallbackChannel;
        private CallbackSetChannel iCallbackSetChannel;
        private CallbackProtocolInfo iCallbackProtocolInfo;
        private CallbackTransportState iCallbackTransportState;
        private CallbackId iCallbackId;
        private CallbackSetId iCallbackSetId;
        private CallbackRead iCallbackRead;
        private CallbackReadList iCallbackReadList;
        private CallbackIdArray iCallbackIdArray;
        private CallbackIdArrayChanged iCallbackIdArrayChanged;
        private CallbackIdsMax iCallbackIdsMax;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderLinnCoUkRadio1(DvDevice aDevice)
        {
            iHandle = DvProviderLinnCoUkRadio1Create(aDevice.Handle()); 
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Set the value of the ChannelUri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyChannelUri(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkRadio1SetPropertyChannelUri(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ChannelUri property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyChannelUri(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkRadio1GetPropertyChannelUri(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the ChannelMetadata property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyChannelMetadata(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkRadio1SetPropertyChannelMetadata(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ChannelMetadata property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyChannelMetadata(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkRadio1GetPropertyChannelMetadata(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the TransportState property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyTransportState(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkRadio1SetPropertyTransportState(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the TransportState property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyTransportState(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkRadio1GetPropertyTransportState(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the ProtocolInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyProtocolInfo(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int err = DvProviderLinnCoUkRadio1SetPropertyProtocolInfo(iHandle, value, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the ProtocolInfo property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyProtocolInfo(out string aValue)
        {
            char* value;
            DvProviderLinnCoUkRadio1GetPropertyProtocolInfo(iHandle, &value);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the Id property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyId(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkRadio1SetPropertyId(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the Id property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyId(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkRadio1GetPropertyId(iHandle, value);
            }
        }

        /// <summary>
        /// Set the value of the IdArray property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyIdArray(string aValue)
        {
            uint changed;
            char* value = (char*)Marshal.StringToHGlobalAnsi(aValue).ToPointer();
            int valueLen = aValue.Length;
            int err = DvProviderLinnCoUkRadio1SetPropertyIdArray(iHandle, value, valueLen, &changed);
            Marshal.FreeHGlobal((IntPtr)value);
            if (err != 0)
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the IdArray property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyIdArray(out string aValue)
        {
            char* value;
            int valueLen;
             DvProviderLinnCoUkRadio1GetPropertyIdArray(iHandle, &value, &valueLen);
            aValue = Marshal.PtrToStringAnsi((IntPtr)value, valueLen);
            ZappFree(value);
        }

        /// <summary>
        /// Set the value of the IdsMax property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public unsafe bool SetPropertyIdsMax(uint aValue)
        {
            uint changed;
            if (0 != DvProviderLinnCoUkRadio1SetPropertyIdsMax(iHandle, aValue, &changed))
            {
                throw(new PropertyUpdateError());
            }
            return (changed != 0);
        }

        /// <summary>
        /// Get a copy of the value of the IdsMax property
        /// </summary>
        /// <param name="aValue">Property's value will be copied here</param>
        public unsafe void GetPropertyIdsMax(out uint aValue)
        {
            fixed (uint* value = &aValue)
            {
                DvProviderLinnCoUkRadio1GetPropertyIdsMax(iHandle, value);
            }
        }

        /// <summary>
        /// Signal that the action Play is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPlay must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPlay()
        {
            iCallbackPlay = new CallbackPlay(DoPlay);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionPlay(iHandle, iCallbackPlay, ptr);
        }

        /// <summary>
        /// Signal that the action Pause is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoPause must be overridden if this is called.</remarks>
        protected unsafe void EnableActionPause()
        {
            iCallbackPause = new CallbackPause(DoPause);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionPause(iHandle, iCallbackPause, ptr);
        }

        /// <summary>
        /// Signal that the action Stop is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoStop must be overridden if this is called.</remarks>
        protected unsafe void EnableActionStop()
        {
            iCallbackStop = new CallbackStop(DoStop);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionStop(iHandle, iCallbackStop, ptr);
        }

        /// <summary>
        /// Signal that the action SeekSecondAbsolute is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekSecondAbsolute must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekSecondAbsolute()
        {
            iCallbackSeekSecondAbsolute = new CallbackSeekSecondAbsolute(DoSeekSecondAbsolute);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionSeekSecondAbsolute(iHandle, iCallbackSeekSecondAbsolute, ptr);
        }

        /// <summary>
        /// Signal that the action SeekSecondRelative is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSeekSecondRelative must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSeekSecondRelative()
        {
            iCallbackSeekSecondRelative = new CallbackSeekSecondRelative(DoSeekSecondRelative);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionSeekSecondRelative(iHandle, iCallbackSeekSecondRelative, ptr);
        }

        /// <summary>
        /// Signal that the action Channel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoChannel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionChannel()
        {
            iCallbackChannel = new CallbackChannel(DoChannel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionChannel(iHandle, iCallbackChannel, ptr);
        }

        /// <summary>
        /// Signal that the action SetChannel is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetChannel must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetChannel()
        {
            iCallbackSetChannel = new CallbackSetChannel(DoSetChannel);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionSetChannel(iHandle, iCallbackSetChannel, ptr);
        }

        /// <summary>
        /// Signal that the action ProtocolInfo is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoProtocolInfo must be overridden if this is called.</remarks>
        protected unsafe void EnableActionProtocolInfo()
        {
            iCallbackProtocolInfo = new CallbackProtocolInfo(DoProtocolInfo);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionProtocolInfo(iHandle, iCallbackProtocolInfo, ptr);
        }

        /// <summary>
        /// Signal that the action TransportState is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoTransportState must be overridden if this is called.</remarks>
        protected unsafe void EnableActionTransportState()
        {
            iCallbackTransportState = new CallbackTransportState(DoTransportState);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionTransportState(iHandle, iCallbackTransportState, ptr);
        }

        /// <summary>
        /// Signal that the action Id is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoId must be overridden if this is called.</remarks>
        protected unsafe void EnableActionId()
        {
            iCallbackId = new CallbackId(DoId);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionId(iHandle, iCallbackId, ptr);
        }

        /// <summary>
        /// Signal that the action SetId is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoSetId must be overridden if this is called.</remarks>
        protected unsafe void EnableActionSetId()
        {
            iCallbackSetId = new CallbackSetId(DoSetId);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionSetId(iHandle, iCallbackSetId, ptr);
        }

        /// <summary>
        /// Signal that the action Read is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoRead must be overridden if this is called.</remarks>
        protected unsafe void EnableActionRead()
        {
            iCallbackRead = new CallbackRead(DoRead);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionRead(iHandle, iCallbackRead, ptr);
        }

        /// <summary>
        /// Signal that the action ReadList is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoReadList must be overridden if this is called.</remarks>
        protected unsafe void EnableActionReadList()
        {
            iCallbackReadList = new CallbackReadList(DoReadList);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionReadList(iHandle, iCallbackReadList, ptr);
        }

        /// <summary>
        /// Signal that the action IdArray is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIdArray must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIdArray()
        {
            iCallbackIdArray = new CallbackIdArray(DoIdArray);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionIdArray(iHandle, iCallbackIdArray, ptr);
        }

        /// <summary>
        /// Signal that the action IdArrayChanged is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIdArrayChanged must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIdArrayChanged()
        {
            iCallbackIdArrayChanged = new CallbackIdArrayChanged(DoIdArrayChanged);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionIdArrayChanged(iHandle, iCallbackIdArrayChanged, ptr);
        }

        /// <summary>
        /// Signal that the action IdsMax is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// DoIdsMax must be overridden if this is called.</remarks>
        protected unsafe void EnableActionIdsMax()
        {
            iCallbackIdsMax = new CallbackIdsMax(DoIdsMax);
            IntPtr ptr = GCHandle.ToIntPtr(iGch);
            DvProviderLinnCoUkRadio1EnableActionIdsMax(iHandle, iCallbackIdsMax, ptr);
        }

        /// <summary>
        /// Play action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Play action for the owning device.
        ///
        /// Must be implemented iff EnableActionPlay was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Play(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Pause action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Pause action for the owning device.
        ///
        /// Must be implemented iff EnableActionPause was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Pause(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Stop action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Stop action for the owning device.
        ///
        /// Must be implemented iff EnableActionStop was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        protected virtual void Stop(uint aVersion)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekSecondAbsolute action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekSecondAbsolute action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekSecondAbsolute was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSecond"></param>
        protected virtual void SeekSecondAbsolute(uint aVersion, uint aaSecond)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SeekSecondRelative action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SeekSecondRelative action for the owning device.
        ///
        /// Must be implemented iff EnableActionSeekSecondRelative was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaSecond"></param>
        protected virtual void SeekSecondRelative(uint aVersion, int aaSecond)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Channel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Channel action for the owning device.
        ///
        /// Must be implemented iff EnableActionChannel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        protected virtual void Channel(uint aVersion, out string aaUri, out string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetChannel action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetChannel action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetChannel was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaUri"></param>
        /// <param name="aaMetadata"></param>
        protected virtual void SetChannel(uint aVersion, string aaUri, string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ProtocolInfo action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ProtocolInfo action for the owning device.
        ///
        /// Must be implemented iff EnableActionProtocolInfo was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaInfo"></param>
        protected virtual void ProtocolInfo(uint aVersion, out string aaInfo)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// TransportState action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// TransportState action for the owning device.
        ///
        /// Must be implemented iff EnableActionTransportState was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaState"></param>
        protected virtual void TransportState(uint aVersion, out string aaState)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Id action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Id action for the owning device.
        ///
        /// Must be implemented iff EnableActionId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaId"></param>
        protected virtual void Id(uint aVersion, out uint aaId)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetId action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetId action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetId was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaId"></param>
        /// <param name="aaUri"></param>
        protected virtual void SetId(uint aVersion, uint aaId, string aaUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Read action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Read action for the owning device.
        ///
        /// Must be implemented iff EnableActionRead was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaId"></param>
        /// <param name="aaMetadata"></param>
        protected virtual void Read(uint aVersion, uint aaId, out string aaMetadata)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// ReadList action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// ReadList action for the owning device.
        ///
        /// Must be implemented iff EnableActionReadList was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIdList"></param>
        /// <param name="aaMetadataList"></param>
        protected virtual void ReadList(uint aVersion, string aaIdList, out string aaMetadataList)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// IdArray action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// IdArray action for the owning device.
        ///
        /// Must be implemented iff EnableActionIdArray was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArray"></param>
        protected virtual void IdArray(uint aVersion, out uint aaIdArrayToken, out string aaIdArray)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// IdArrayChanged action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// IdArrayChanged action for the owning device.
        ///
        /// Must be implemented iff EnableActionIdArrayChanged was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIdArrayToken"></param>
        /// <param name="aaIdArrayChanged"></param>
        protected virtual void IdArrayChanged(uint aVersion, uint aaIdArrayToken, out bool aaIdArrayChanged)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// IdsMax action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// IdsMax action for the owning device.
        ///
        /// Must be implemented iff EnableActionIdsMax was called.</remarks>
        /// <param name="aVersion">Version of the service being requested (will be <= the version advertised)</param>
        /// <param name="aaIdsMax"></param>
        protected virtual void IdsMax(uint aVersion, out uint aaIdsMax)
        {
            throw (new ActionDisabledError());
        }

        private static unsafe int DoPlay(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            self.Play(aVersion);
            return 0;
        }

        private static unsafe int DoPause(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            self.Pause(aVersion);
            return 0;
        }

        private static unsafe int DoStop(IntPtr aPtr, uint aVersion)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            self.Stop(aVersion);
            return 0;
        }

        private static unsafe int DoSeekSecondAbsolute(IntPtr aPtr, uint aVersion, uint aaSecond)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            self.SeekSecondAbsolute(aVersion, aaSecond);
            return 0;
        }

        private static unsafe int DoSeekSecondRelative(IntPtr aPtr, uint aVersion, int aaSecond)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            self.SeekSecondRelative(aVersion, aaSecond);
            return 0;
        }

        private static unsafe int DoChannel(IntPtr aPtr, uint aVersion, char** aaUri, char** aaMetadata)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            string aUri;
            string aMetadata;
            self.Channel(aVersion, out aUri, out aMetadata);
            *aaUri = (char*)Marshal.StringToHGlobalAnsi(aUri).ToPointer();
            *aaMetadata = (char*)Marshal.StringToHGlobalAnsi(aMetadata).ToPointer();
            return 0;
        }

        private static unsafe int DoSetChannel(IntPtr aPtr, uint aVersion, char* aaUri, char* aaMetadata)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            string aUri = Marshal.PtrToStringAnsi((IntPtr)aaUri);
            string aMetadata = Marshal.PtrToStringAnsi((IntPtr)aaMetadata);
            self.SetChannel(aVersion, aUri, aMetadata);
            return 0;
        }

        private static unsafe int DoProtocolInfo(IntPtr aPtr, uint aVersion, char** aaInfo)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            string aInfo;
            self.ProtocolInfo(aVersion, out aInfo);
            *aaInfo = (char*)Marshal.StringToHGlobalAnsi(aInfo).ToPointer();
            return 0;
        }

        private static unsafe int DoTransportState(IntPtr aPtr, uint aVersion, char** aaState)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            string aState;
            self.TransportState(aVersion, out aState);
            *aaState = (char*)Marshal.StringToHGlobalAnsi(aState).ToPointer();
            return 0;
        }

        private static unsafe int DoId(IntPtr aPtr, uint aVersion, uint* aaId)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            uint aId;
            self.Id(aVersion, out aId);
            *aaId = aId;
            return 0;
        }

        private static unsafe int DoSetId(IntPtr aPtr, uint aVersion, uint aaId, char* aaUri)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            string aUri = Marshal.PtrToStringAnsi((IntPtr)aaUri);
            self.SetId(aVersion, aaId, aUri);
            return 0;
        }

        private static unsafe int DoRead(IntPtr aPtr, uint aVersion, uint aaId, char** aaMetadata)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            string aMetadata;
            self.Read(aVersion, aaId, out aMetadata);
            *aaMetadata = (char*)Marshal.StringToHGlobalAnsi(aMetadata).ToPointer();
            return 0;
        }

        private static unsafe int DoReadList(IntPtr aPtr, uint aVersion, char* aaIdList, char** aaMetadataList)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            string aIdList = Marshal.PtrToStringAnsi((IntPtr)aaIdList);
            string aMetadataList;
            self.ReadList(aVersion, aIdList, out aMetadataList);
            *aaMetadataList = (char*)Marshal.StringToHGlobalAnsi(aMetadataList).ToPointer();
            return 0;
        }

        private static unsafe int DoIdArray(IntPtr aPtr, uint aVersion, uint* aaIdArrayToken, char** aaIdArray, int* aaIdArrayLen)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            uint aIdArrayToken;
            string aIdArray;
            self.IdArray(aVersion, out aIdArrayToken, out aIdArray);
            *aaIdArrayToken = aIdArrayToken;
            *aaIdArray = (char*)Marshal.StringToHGlobalAnsi(aIdArray).ToPointer();
            *aaIdArrayLen = aIdArray.Length;
            return 0;
        }

        private static unsafe int DoIdArrayChanged(IntPtr aPtr, uint aVersion, uint aaIdArrayToken, int* aaIdArrayChanged)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            bool aIdArrayChanged;
            self.IdArrayChanged(aVersion, aaIdArrayToken, out aIdArrayChanged);
            *aaIdArrayChanged = (aIdArrayChanged ? 1 : 0);
            return 0;
        }

        private static unsafe int DoIdsMax(IntPtr aPtr, uint aVersion, uint* aaIdsMax)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderLinnCoUkRadio1 self = (DvProviderLinnCoUkRadio1)gch.Target;
            uint aIdsMax;
            self.IdsMax(aVersion, out aIdsMax);
            *aaIdsMax = aIdsMax;
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            DoDispose();
            GC.SuppressFinalize(this);
        }

        ~DvProviderLinnCoUkRadio1()
        {
            DoDispose();
        }

        private void DoDispose()
        {
            IntPtr handle;
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                {
                    return;
                }
                handle = iHandle;
                iHandle = IntPtr.Zero;
            }
            DvProviderLinnCoUkRadio1Destroy(handle);
            if (iGch.IsAllocated)
            {
                iGch.Free();
            }
        }
    }
}

