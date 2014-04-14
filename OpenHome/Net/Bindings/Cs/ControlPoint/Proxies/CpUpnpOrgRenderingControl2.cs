using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgRenderingControl2 : ICpProxy, IDisposable
    {
        void SyncListPresets(uint aInstanceID, out String aCurrentPresetNameList);
        void BeginListPresets(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndListPresets(IntPtr aAsyncHandle, out String aCurrentPresetNameList);
        void SyncSelectPreset(uint aInstanceID, String aPresetName);
        void BeginSelectPreset(uint aInstanceID, String aPresetName, CpProxy.CallbackAsyncComplete aCallback);
        void EndSelectPreset(IntPtr aAsyncHandle);
        void SyncGetBrightness(uint aInstanceID, out uint aCurrentBrightness);
        void BeginGetBrightness(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetBrightness(IntPtr aAsyncHandle, out uint aCurrentBrightness);
        void SyncSetBrightness(uint aInstanceID, uint aDesiredBrightness);
        void BeginSetBrightness(uint aInstanceID, uint aDesiredBrightness, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBrightness(IntPtr aAsyncHandle);
        void SyncGetContrast(uint aInstanceID, out uint aCurrentContrast);
        void BeginGetContrast(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetContrast(IntPtr aAsyncHandle, out uint aCurrentContrast);
        void SyncSetContrast(uint aInstanceID, uint aDesiredContrast);
        void BeginSetContrast(uint aInstanceID, uint aDesiredContrast, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetContrast(IntPtr aAsyncHandle);
        void SyncGetSharpness(uint aInstanceID, out uint aCurrentSharpness);
        void BeginGetSharpness(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetSharpness(IntPtr aAsyncHandle, out uint aCurrentSharpness);
        void SyncSetSharpness(uint aInstanceID, uint aDesiredSharpness);
        void BeginSetSharpness(uint aInstanceID, uint aDesiredSharpness, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetSharpness(IntPtr aAsyncHandle);
        void SyncGetRedVideoGain(uint aInstanceID, out uint aCurrentRedVideoGain);
        void BeginGetRedVideoGain(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRedVideoGain(IntPtr aAsyncHandle, out uint aCurrentRedVideoGain);
        void SyncSetRedVideoGain(uint aInstanceID, uint aDesiredRedVideoGain);
        void BeginSetRedVideoGain(uint aInstanceID, uint aDesiredRedVideoGain, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRedVideoGain(IntPtr aAsyncHandle);
        void SyncGetGreenVideoGain(uint aInstanceID, out uint aCurrentGreenVideoGain);
        void BeginGetGreenVideoGain(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetGreenVideoGain(IntPtr aAsyncHandle, out uint aCurrentGreenVideoGain);
        void SyncSetGreenVideoGain(uint aInstanceID, uint aDesiredGreenVideoGain);
        void BeginSetGreenVideoGain(uint aInstanceID, uint aDesiredGreenVideoGain, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetGreenVideoGain(IntPtr aAsyncHandle);
        void SyncGetBlueVideoGain(uint aInstanceID, out uint aCurrentBlueVideoGain);
        void BeginGetBlueVideoGain(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetBlueVideoGain(IntPtr aAsyncHandle, out uint aCurrentBlueVideoGain);
        void SyncSetBlueVideoGain(uint aInstanceID, uint aDesiredBlueVideoGain);
        void BeginSetBlueVideoGain(uint aInstanceID, uint aDesiredBlueVideoGain, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBlueVideoGain(IntPtr aAsyncHandle);
        void SyncGetRedVideoBlackLevel(uint aInstanceID, out uint aCurrentRedVideoBlackLevel);
        void BeginGetRedVideoBlackLevel(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRedVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentRedVideoBlackLevel);
        void SyncSetRedVideoBlackLevel(uint aInstanceID, uint aDesiredRedVideoBlackLevel);
        void BeginSetRedVideoBlackLevel(uint aInstanceID, uint aDesiredRedVideoBlackLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRedVideoBlackLevel(IntPtr aAsyncHandle);
        void SyncGetGreenVideoBlackLevel(uint aInstanceID, out uint aCurrentGreenVideoBlackLevel);
        void BeginGetGreenVideoBlackLevel(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetGreenVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentGreenVideoBlackLevel);
        void SyncSetGreenVideoBlackLevel(uint aInstanceID, uint aDesiredGreenVideoBlackLevel);
        void BeginSetGreenVideoBlackLevel(uint aInstanceID, uint aDesiredGreenVideoBlackLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetGreenVideoBlackLevel(IntPtr aAsyncHandle);
        void SyncGetBlueVideoBlackLevel(uint aInstanceID, out uint aCurrentBlueVideoBlackLevel);
        void BeginGetBlueVideoBlackLevel(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetBlueVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentBlueVideoBlackLevel);
        void SyncSetBlueVideoBlackLevel(uint aInstanceID, uint aDesiredBlueVideoBlackLevel);
        void BeginSetBlueVideoBlackLevel(uint aInstanceID, uint aDesiredBlueVideoBlackLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetBlueVideoBlackLevel(IntPtr aAsyncHandle);
        void SyncGetColorTemperature(uint aInstanceID, out uint aCurrentColorTemperature);
        void BeginGetColorTemperature(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetColorTemperature(IntPtr aAsyncHandle, out uint aCurrentColorTemperature);
        void SyncSetColorTemperature(uint aInstanceID, uint aDesiredColorTemperature);
        void BeginSetColorTemperature(uint aInstanceID, uint aDesiredColorTemperature, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetColorTemperature(IntPtr aAsyncHandle);
        void SyncGetHorizontalKeystone(uint aInstanceID, out int aCurrentHorizontalKeystone);
        void BeginGetHorizontalKeystone(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetHorizontalKeystone(IntPtr aAsyncHandle, out int aCurrentHorizontalKeystone);
        void SyncSetHorizontalKeystone(uint aInstanceID, int aDesiredHorizontalKeystone);
        void BeginSetHorizontalKeystone(uint aInstanceID, int aDesiredHorizontalKeystone, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetHorizontalKeystone(IntPtr aAsyncHandle);
        void SyncGetVerticalKeystone(uint aInstanceID, out int aCurrentVerticalKeystone);
        void BeginGetVerticalKeystone(uint aInstanceID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetVerticalKeystone(IntPtr aAsyncHandle, out int aCurrentVerticalKeystone);
        void SyncSetVerticalKeystone(uint aInstanceID, int aDesiredVerticalKeystone);
        void BeginSetVerticalKeystone(uint aInstanceID, int aDesiredVerticalKeystone, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVerticalKeystone(IntPtr aAsyncHandle);
        void SyncGetMute(uint aInstanceID, String aChannel, out bool aCurrentMute);
        void BeginGetMute(uint aInstanceID, String aChannel, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetMute(IntPtr aAsyncHandle, out bool aCurrentMute);
        void SyncSetMute(uint aInstanceID, String aChannel, bool aDesiredMute);
        void BeginSetMute(uint aInstanceID, String aChannel, bool aDesiredMute, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetMute(IntPtr aAsyncHandle);
        void SyncGetVolume(uint aInstanceID, String aChannel, out uint aCurrentVolume);
        void BeginGetVolume(uint aInstanceID, String aChannel, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetVolume(IntPtr aAsyncHandle, out uint aCurrentVolume);
        void SyncSetVolume(uint aInstanceID, String aChannel, uint aDesiredVolume);
        void BeginSetVolume(uint aInstanceID, String aChannel, uint aDesiredVolume, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolume(IntPtr aAsyncHandle);
        void SyncGetVolumeDB(uint aInstanceID, String aChannel, out int aCurrentVolume);
        void BeginGetVolumeDB(uint aInstanceID, String aChannel, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetVolumeDB(IntPtr aAsyncHandle, out int aCurrentVolume);
        void SyncSetVolumeDB(uint aInstanceID, String aChannel, int aDesiredVolume);
        void BeginSetVolumeDB(uint aInstanceID, String aChannel, int aDesiredVolume, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetVolumeDB(IntPtr aAsyncHandle);
        void SyncGetVolumeDBRange(uint aInstanceID, String aChannel, out int aMinValue, out int aMaxValue);
        void BeginGetVolumeDBRange(uint aInstanceID, String aChannel, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetVolumeDBRange(IntPtr aAsyncHandle, out int aMinValue, out int aMaxValue);
        void SyncGetLoudness(uint aInstanceID, String aChannel, out bool aCurrentLoudness);
        void BeginGetLoudness(uint aInstanceID, String aChannel, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoudness(IntPtr aAsyncHandle, out bool aCurrentLoudness);
        void SyncSetLoudness(uint aInstanceID, String aChannel, bool aDesiredLoudness);
        void BeginSetLoudness(uint aInstanceID, String aChannel, bool aDesiredLoudness, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetLoudness(IntPtr aAsyncHandle);
        void SyncGetStateVariables(uint aInstanceID, String aStateVariableList, out String aStateVariableValuePairs);
        void BeginGetStateVariables(uint aInstanceID, String aStateVariableList, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStateVariables(IntPtr aAsyncHandle, out String aStateVariableValuePairs);
        void SyncSetStateVariables(uint aInstanceID, String aRenderingControlUDN, String aServiceType, String aServiceId, String aStateVariableValuePairs, out String aStateVariableList);
        void BeginSetStateVariables(uint aInstanceID, String aRenderingControlUDN, String aServiceType, String aServiceId, String aStateVariableValuePairs, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStateVariables(IntPtr aAsyncHandle, out String aStateVariableList);
        void SetPropertyLastChangeChanged(System.Action aLastChangeChanged);
        String PropertyLastChange();
    }

    internal class SyncListPresetsUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private String iCurrentPresetNameList;

        public SyncListPresetsUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public String CurrentPresetNameList()
        {
            return iCurrentPresetNameList;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndListPresets(aAsyncHandle, out iCurrentPresetNameList);
        }
    };

    internal class SyncSelectPresetUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSelectPresetUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSelectPreset(aAsyncHandle);
        }
    };

    internal class SyncGetBrightnessUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentBrightness;

        public SyncGetBrightnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentBrightness()
        {
            return iCurrentBrightness;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetBrightness(aAsyncHandle, out iCurrentBrightness);
        }
    };

    internal class SyncSetBrightnessUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetBrightnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBrightness(aAsyncHandle);
        }
    };

    internal class SyncGetContrastUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentContrast;

        public SyncGetContrastUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentContrast()
        {
            return iCurrentContrast;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetContrast(aAsyncHandle, out iCurrentContrast);
        }
    };

    internal class SyncSetContrastUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetContrastUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetContrast(aAsyncHandle);
        }
    };

    internal class SyncGetSharpnessUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentSharpness;

        public SyncGetSharpnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentSharpness()
        {
            return iCurrentSharpness;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetSharpness(aAsyncHandle, out iCurrentSharpness);
        }
    };

    internal class SyncSetSharpnessUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetSharpnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetSharpness(aAsyncHandle);
        }
    };

    internal class SyncGetRedVideoGainUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentRedVideoGain;

        public SyncGetRedVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentRedVideoGain()
        {
            return iCurrentRedVideoGain;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRedVideoGain(aAsyncHandle, out iCurrentRedVideoGain);
        }
    };

    internal class SyncSetRedVideoGainUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetRedVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetRedVideoGain(aAsyncHandle);
        }
    };

    internal class SyncGetGreenVideoGainUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentGreenVideoGain;

        public SyncGetGreenVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentGreenVideoGain()
        {
            return iCurrentGreenVideoGain;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetGreenVideoGain(aAsyncHandle, out iCurrentGreenVideoGain);
        }
    };

    internal class SyncSetGreenVideoGainUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetGreenVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetGreenVideoGain(aAsyncHandle);
        }
    };

    internal class SyncGetBlueVideoGainUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentBlueVideoGain;

        public SyncGetBlueVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentBlueVideoGain()
        {
            return iCurrentBlueVideoGain;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetBlueVideoGain(aAsyncHandle, out iCurrentBlueVideoGain);
        }
    };

    internal class SyncSetBlueVideoGainUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetBlueVideoGainUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBlueVideoGain(aAsyncHandle);
        }
    };

    internal class SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentRedVideoBlackLevel;

        public SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentRedVideoBlackLevel()
        {
            return iCurrentRedVideoBlackLevel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRedVideoBlackLevel(aAsyncHandle, out iCurrentRedVideoBlackLevel);
        }
    };

    internal class SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetRedVideoBlackLevel(aAsyncHandle);
        }
    };

    internal class SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentGreenVideoBlackLevel;

        public SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentGreenVideoBlackLevel()
        {
            return iCurrentGreenVideoBlackLevel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetGreenVideoBlackLevel(aAsyncHandle, out iCurrentGreenVideoBlackLevel);
        }
    };

    internal class SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetGreenVideoBlackLevel(aAsyncHandle);
        }
    };

    internal class SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentBlueVideoBlackLevel;

        public SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentBlueVideoBlackLevel()
        {
            return iCurrentBlueVideoBlackLevel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetBlueVideoBlackLevel(aAsyncHandle, out iCurrentBlueVideoBlackLevel);
        }
    };

    internal class SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetBlueVideoBlackLevel(aAsyncHandle);
        }
    };

    internal class SyncGetColorTemperatureUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentColorTemperature;

        public SyncGetColorTemperatureUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentColorTemperature()
        {
            return iCurrentColorTemperature;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetColorTemperature(aAsyncHandle, out iCurrentColorTemperature);
        }
    };

    internal class SyncSetColorTemperatureUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetColorTemperatureUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetColorTemperature(aAsyncHandle);
        }
    };

    internal class SyncGetHorizontalKeystoneUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private int iCurrentHorizontalKeystone;

        public SyncGetHorizontalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public int CurrentHorizontalKeystone()
        {
            return iCurrentHorizontalKeystone;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetHorizontalKeystone(aAsyncHandle, out iCurrentHorizontalKeystone);
        }
    };

    internal class SyncSetHorizontalKeystoneUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetHorizontalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetHorizontalKeystone(aAsyncHandle);
        }
    };

    internal class SyncGetVerticalKeystoneUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private int iCurrentVerticalKeystone;

        public SyncGetVerticalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public int CurrentVerticalKeystone()
        {
            return iCurrentVerticalKeystone;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetVerticalKeystone(aAsyncHandle, out iCurrentVerticalKeystone);
        }
    };

    internal class SyncSetVerticalKeystoneUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetVerticalKeystoneUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetVerticalKeystone(aAsyncHandle);
        }
    };

    internal class SyncGetMuteUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private bool iCurrentMute;

        public SyncGetMuteUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public bool CurrentMute()
        {
            return iCurrentMute;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetMute(aAsyncHandle, out iCurrentMute);
        }
    };

    internal class SyncSetMuteUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetMuteUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetMute(aAsyncHandle);
        }
    };

    internal class SyncGetVolumeUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private uint iCurrentVolume;

        public SyncGetVolumeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public uint CurrentVolume()
        {
            return iCurrentVolume;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetVolume(aAsyncHandle, out iCurrentVolume);
        }
    };

    internal class SyncSetVolumeUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetVolumeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetVolume(aAsyncHandle);
        }
    };

    internal class SyncGetVolumeDBUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private int iCurrentVolume;

        public SyncGetVolumeDBUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public int CurrentVolume()
        {
            return iCurrentVolume;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetVolumeDB(aAsyncHandle, out iCurrentVolume);
        }
    };

    internal class SyncSetVolumeDBUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetVolumeDBUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetVolumeDB(aAsyncHandle);
        }
    };

    internal class SyncGetVolumeDBRangeUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private int iMinValue;
        private int iMaxValue;

        public SyncGetVolumeDBRangeUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public int MinValue()
        {
            return iMinValue;
        }
        public int MaxValue()
        {
            return iMaxValue;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetVolumeDBRange(aAsyncHandle, out iMinValue, out iMaxValue);
        }
    };

    internal class SyncGetLoudnessUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private bool iCurrentLoudness;

        public SyncGetLoudnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public bool CurrentLoudness()
        {
            return iCurrentLoudness;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetLoudness(aAsyncHandle, out iCurrentLoudness);
        }
    };

    internal class SyncSetLoudnessUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;

        public SyncSetLoudnessUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetLoudness(aAsyncHandle);
        }
    };

    internal class SyncGetStateVariablesUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private String iStateVariableValuePairs;

        public SyncGetStateVariablesUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public String StateVariableValuePairs()
        {
            return iStateVariableValuePairs;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetStateVariables(aAsyncHandle, out iStateVariableValuePairs);
        }
    };

    internal class SyncSetStateVariablesUpnpOrgRenderingControl2 : SyncProxyAction
    {
        private CpProxyUpnpOrgRenderingControl2 iService;
        private String iStateVariableList;

        public SyncSetStateVariablesUpnpOrgRenderingControl2(CpProxyUpnpOrgRenderingControl2 aProxy)
        {
            iService = aProxy;
        }
        public String StateVariableList()
        {
            return iStateVariableList;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStateVariables(aAsyncHandle, out iStateVariableList);
        }
    };

    /// <summary>
    /// Proxy for the upnp.org:RenderingControl:2 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgRenderingControl2 : CpProxy, IDisposable, ICpProxyUpnpOrgRenderingControl2
    {
        private OpenHome.Net.Core.Action iActionListPresets;
        private OpenHome.Net.Core.Action iActionSelectPreset;
        private OpenHome.Net.Core.Action iActionGetBrightness;
        private OpenHome.Net.Core.Action iActionSetBrightness;
        private OpenHome.Net.Core.Action iActionGetContrast;
        private OpenHome.Net.Core.Action iActionSetContrast;
        private OpenHome.Net.Core.Action iActionGetSharpness;
        private OpenHome.Net.Core.Action iActionSetSharpness;
        private OpenHome.Net.Core.Action iActionGetRedVideoGain;
        private OpenHome.Net.Core.Action iActionSetRedVideoGain;
        private OpenHome.Net.Core.Action iActionGetGreenVideoGain;
        private OpenHome.Net.Core.Action iActionSetGreenVideoGain;
        private OpenHome.Net.Core.Action iActionGetBlueVideoGain;
        private OpenHome.Net.Core.Action iActionSetBlueVideoGain;
        private OpenHome.Net.Core.Action iActionGetRedVideoBlackLevel;
        private OpenHome.Net.Core.Action iActionSetRedVideoBlackLevel;
        private OpenHome.Net.Core.Action iActionGetGreenVideoBlackLevel;
        private OpenHome.Net.Core.Action iActionSetGreenVideoBlackLevel;
        private OpenHome.Net.Core.Action iActionGetBlueVideoBlackLevel;
        private OpenHome.Net.Core.Action iActionSetBlueVideoBlackLevel;
        private OpenHome.Net.Core.Action iActionGetColorTemperature;
        private OpenHome.Net.Core.Action iActionSetColorTemperature;
        private OpenHome.Net.Core.Action iActionGetHorizontalKeystone;
        private OpenHome.Net.Core.Action iActionSetHorizontalKeystone;
        private OpenHome.Net.Core.Action iActionGetVerticalKeystone;
        private OpenHome.Net.Core.Action iActionSetVerticalKeystone;
        private OpenHome.Net.Core.Action iActionGetMute;
        private OpenHome.Net.Core.Action iActionSetMute;
        private OpenHome.Net.Core.Action iActionGetVolume;
        private OpenHome.Net.Core.Action iActionSetVolume;
        private OpenHome.Net.Core.Action iActionGetVolumeDB;
        private OpenHome.Net.Core.Action iActionSetVolumeDB;
        private OpenHome.Net.Core.Action iActionGetVolumeDBRange;
        private OpenHome.Net.Core.Action iActionGetLoudness;
        private OpenHome.Net.Core.Action iActionSetLoudness;
        private OpenHome.Net.Core.Action iActionGetStateVariables;
        private OpenHome.Net.Core.Action iActionSetStateVariables;
        private PropertyString iLastChange;
        private System.Action iLastChangeChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgRenderingControl2(CpDevice aDevice)
            : base("schemas-upnp-org", "RenderingControl", 2, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionListPresets = new OpenHome.Net.Core.Action("ListPresets");
            param = new ParameterUint("InstanceID");
            iActionListPresets.AddInputParameter(param);
            param = new ParameterString("CurrentPresetNameList", allowedValues);
            iActionListPresets.AddOutputParameter(param);

            iActionSelectPreset = new OpenHome.Net.Core.Action("SelectPreset");
            param = new ParameterUint("InstanceID");
            iActionSelectPreset.AddInputParameter(param);
            param = new ParameterString("PresetName", allowedValues);
            iActionSelectPreset.AddInputParameter(param);

            iActionGetBrightness = new OpenHome.Net.Core.Action("GetBrightness");
            param = new ParameterUint("InstanceID");
            iActionGetBrightness.AddInputParameter(param);
            param = new ParameterUint("CurrentBrightness", 0, 2147483647, 1);
            iActionGetBrightness.AddOutputParameter(param);

            iActionSetBrightness = new OpenHome.Net.Core.Action("SetBrightness");
            param = new ParameterUint("InstanceID");
            iActionSetBrightness.AddInputParameter(param);
            param = new ParameterUint("DesiredBrightness", 0, 2147483647, 1);
            iActionSetBrightness.AddInputParameter(param);

            iActionGetContrast = new OpenHome.Net.Core.Action("GetContrast");
            param = new ParameterUint("InstanceID");
            iActionGetContrast.AddInputParameter(param);
            param = new ParameterUint("CurrentContrast", 0, 2147483647, 1);
            iActionGetContrast.AddOutputParameter(param);

            iActionSetContrast = new OpenHome.Net.Core.Action("SetContrast");
            param = new ParameterUint("InstanceID");
            iActionSetContrast.AddInputParameter(param);
            param = new ParameterUint("DesiredContrast", 0, 2147483647, 1);
            iActionSetContrast.AddInputParameter(param);

            iActionGetSharpness = new OpenHome.Net.Core.Action("GetSharpness");
            param = new ParameterUint("InstanceID");
            iActionGetSharpness.AddInputParameter(param);
            param = new ParameterUint("CurrentSharpness", 0, 2147483647, 1);
            iActionGetSharpness.AddOutputParameter(param);

            iActionSetSharpness = new OpenHome.Net.Core.Action("SetSharpness");
            param = new ParameterUint("InstanceID");
            iActionSetSharpness.AddInputParameter(param);
            param = new ParameterUint("DesiredSharpness", 0, 2147483647, 1);
            iActionSetSharpness.AddInputParameter(param);

            iActionGetRedVideoGain = new OpenHome.Net.Core.Action("GetRedVideoGain");
            param = new ParameterUint("InstanceID");
            iActionGetRedVideoGain.AddInputParameter(param);
            param = new ParameterUint("CurrentRedVideoGain", 0, 2147483647, 1);
            iActionGetRedVideoGain.AddOutputParameter(param);

            iActionSetRedVideoGain = new OpenHome.Net.Core.Action("SetRedVideoGain");
            param = new ParameterUint("InstanceID");
            iActionSetRedVideoGain.AddInputParameter(param);
            param = new ParameterUint("DesiredRedVideoGain", 0, 2147483647, 1);
            iActionSetRedVideoGain.AddInputParameter(param);

            iActionGetGreenVideoGain = new OpenHome.Net.Core.Action("GetGreenVideoGain");
            param = new ParameterUint("InstanceID");
            iActionGetGreenVideoGain.AddInputParameter(param);
            param = new ParameterUint("CurrentGreenVideoGain", 0, 2147483647, 1);
            iActionGetGreenVideoGain.AddOutputParameter(param);

            iActionSetGreenVideoGain = new OpenHome.Net.Core.Action("SetGreenVideoGain");
            param = new ParameterUint("InstanceID");
            iActionSetGreenVideoGain.AddInputParameter(param);
            param = new ParameterUint("DesiredGreenVideoGain", 0, 2147483647, 1);
            iActionSetGreenVideoGain.AddInputParameter(param);

            iActionGetBlueVideoGain = new OpenHome.Net.Core.Action("GetBlueVideoGain");
            param = new ParameterUint("InstanceID");
            iActionGetBlueVideoGain.AddInputParameter(param);
            param = new ParameterUint("CurrentBlueVideoGain", 0, 2147483647, 1);
            iActionGetBlueVideoGain.AddOutputParameter(param);

            iActionSetBlueVideoGain = new OpenHome.Net.Core.Action("SetBlueVideoGain");
            param = new ParameterUint("InstanceID");
            iActionSetBlueVideoGain.AddInputParameter(param);
            param = new ParameterUint("DesiredBlueVideoGain", 0, 2147483647, 1);
            iActionSetBlueVideoGain.AddInputParameter(param);

            iActionGetRedVideoBlackLevel = new OpenHome.Net.Core.Action("GetRedVideoBlackLevel");
            param = new ParameterUint("InstanceID");
            iActionGetRedVideoBlackLevel.AddInputParameter(param);
            param = new ParameterUint("CurrentRedVideoBlackLevel", 0, 2147483647, 1);
            iActionGetRedVideoBlackLevel.AddOutputParameter(param);

            iActionSetRedVideoBlackLevel = new OpenHome.Net.Core.Action("SetRedVideoBlackLevel");
            param = new ParameterUint("InstanceID");
            iActionSetRedVideoBlackLevel.AddInputParameter(param);
            param = new ParameterUint("DesiredRedVideoBlackLevel", 0, 2147483647, 1);
            iActionSetRedVideoBlackLevel.AddInputParameter(param);

            iActionGetGreenVideoBlackLevel = new OpenHome.Net.Core.Action("GetGreenVideoBlackLevel");
            param = new ParameterUint("InstanceID");
            iActionGetGreenVideoBlackLevel.AddInputParameter(param);
            param = new ParameterUint("CurrentGreenVideoBlackLevel", 0, 2147483647, 1);
            iActionGetGreenVideoBlackLevel.AddOutputParameter(param);

            iActionSetGreenVideoBlackLevel = new OpenHome.Net.Core.Action("SetGreenVideoBlackLevel");
            param = new ParameterUint("InstanceID");
            iActionSetGreenVideoBlackLevel.AddInputParameter(param);
            param = new ParameterUint("DesiredGreenVideoBlackLevel", 0, 2147483647, 1);
            iActionSetGreenVideoBlackLevel.AddInputParameter(param);

            iActionGetBlueVideoBlackLevel = new OpenHome.Net.Core.Action("GetBlueVideoBlackLevel");
            param = new ParameterUint("InstanceID");
            iActionGetBlueVideoBlackLevel.AddInputParameter(param);
            param = new ParameterUint("CurrentBlueVideoBlackLevel", 0, 2147483647, 1);
            iActionGetBlueVideoBlackLevel.AddOutputParameter(param);

            iActionSetBlueVideoBlackLevel = new OpenHome.Net.Core.Action("SetBlueVideoBlackLevel");
            param = new ParameterUint("InstanceID");
            iActionSetBlueVideoBlackLevel.AddInputParameter(param);
            param = new ParameterUint("DesiredBlueVideoBlackLevel", 0, 2147483647, 1);
            iActionSetBlueVideoBlackLevel.AddInputParameter(param);

            iActionGetColorTemperature = new OpenHome.Net.Core.Action("GetColorTemperature");
            param = new ParameterUint("InstanceID");
            iActionGetColorTemperature.AddInputParameter(param);
            param = new ParameterUint("CurrentColorTemperature", 0, 2147483647, 1);
            iActionGetColorTemperature.AddOutputParameter(param);

            iActionSetColorTemperature = new OpenHome.Net.Core.Action("SetColorTemperature");
            param = new ParameterUint("InstanceID");
            iActionSetColorTemperature.AddInputParameter(param);
            param = new ParameterUint("DesiredColorTemperature", 0, 2147483647, 1);
            iActionSetColorTemperature.AddInputParameter(param);

            iActionGetHorizontalKeystone = new OpenHome.Net.Core.Action("GetHorizontalKeystone");
            param = new ParameterUint("InstanceID");
            iActionGetHorizontalKeystone.AddInputParameter(param);
            param = new ParameterInt("CurrentHorizontalKeystone");
            iActionGetHorizontalKeystone.AddOutputParameter(param);

            iActionSetHorizontalKeystone = new OpenHome.Net.Core.Action("SetHorizontalKeystone");
            param = new ParameterUint("InstanceID");
            iActionSetHorizontalKeystone.AddInputParameter(param);
            param = new ParameterInt("DesiredHorizontalKeystone");
            iActionSetHorizontalKeystone.AddInputParameter(param);

            iActionGetVerticalKeystone = new OpenHome.Net.Core.Action("GetVerticalKeystone");
            param = new ParameterUint("InstanceID");
            iActionGetVerticalKeystone.AddInputParameter(param);
            param = new ParameterInt("CurrentVerticalKeystone");
            iActionGetVerticalKeystone.AddOutputParameter(param);

            iActionSetVerticalKeystone = new OpenHome.Net.Core.Action("SetVerticalKeystone");
            param = new ParameterUint("InstanceID");
            iActionSetVerticalKeystone.AddInputParameter(param);
            param = new ParameterInt("DesiredVerticalKeystone");
            iActionSetVerticalKeystone.AddInputParameter(param);

            iActionGetMute = new OpenHome.Net.Core.Action("GetMute");
            param = new ParameterUint("InstanceID");
            iActionGetMute.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionGetMute.AddInputParameter(param);
            param = new ParameterBool("CurrentMute");
            iActionGetMute.AddOutputParameter(param);

            iActionSetMute = new OpenHome.Net.Core.Action("SetMute");
            param = new ParameterUint("InstanceID");
            iActionSetMute.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionSetMute.AddInputParameter(param);
            param = new ParameterBool("DesiredMute");
            iActionSetMute.AddInputParameter(param);

            iActionGetVolume = new OpenHome.Net.Core.Action("GetVolume");
            param = new ParameterUint("InstanceID");
            iActionGetVolume.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionGetVolume.AddInputParameter(param);
            param = new ParameterUint("CurrentVolume", 0, 2147483647, 1);
            iActionGetVolume.AddOutputParameter(param);

            iActionSetVolume = new OpenHome.Net.Core.Action("SetVolume");
            param = new ParameterUint("InstanceID");
            iActionSetVolume.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionSetVolume.AddInputParameter(param);
            param = new ParameterUint("DesiredVolume", 0, 2147483647, 1);
            iActionSetVolume.AddInputParameter(param);

            iActionGetVolumeDB = new OpenHome.Net.Core.Action("GetVolumeDB");
            param = new ParameterUint("InstanceID");
            iActionGetVolumeDB.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionGetVolumeDB.AddInputParameter(param);
            param = new ParameterInt("CurrentVolume");
            iActionGetVolumeDB.AddOutputParameter(param);

            iActionSetVolumeDB = new OpenHome.Net.Core.Action("SetVolumeDB");
            param = new ParameterUint("InstanceID");
            iActionSetVolumeDB.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionSetVolumeDB.AddInputParameter(param);
            param = new ParameterInt("DesiredVolume");
            iActionSetVolumeDB.AddInputParameter(param);

            iActionGetVolumeDBRange = new OpenHome.Net.Core.Action("GetVolumeDBRange");
            param = new ParameterUint("InstanceID");
            iActionGetVolumeDBRange.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionGetVolumeDBRange.AddInputParameter(param);
            param = new ParameterInt("MinValue");
            iActionGetVolumeDBRange.AddOutputParameter(param);
            param = new ParameterInt("MaxValue");
            iActionGetVolumeDBRange.AddOutputParameter(param);

            iActionGetLoudness = new OpenHome.Net.Core.Action("GetLoudness");
            param = new ParameterUint("InstanceID");
            iActionGetLoudness.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionGetLoudness.AddInputParameter(param);
            param = new ParameterBool("CurrentLoudness");
            iActionGetLoudness.AddOutputParameter(param);

            iActionSetLoudness = new OpenHome.Net.Core.Action("SetLoudness");
            param = new ParameterUint("InstanceID");
            iActionSetLoudness.AddInputParameter(param);
            param = new ParameterString("Channel", allowedValues);
            iActionSetLoudness.AddInputParameter(param);
            param = new ParameterBool("DesiredLoudness");
            iActionSetLoudness.AddInputParameter(param);

            iActionGetStateVariables = new OpenHome.Net.Core.Action("GetStateVariables");
            param = new ParameterUint("InstanceID");
            iActionGetStateVariables.AddInputParameter(param);
            param = new ParameterString("StateVariableList", allowedValues);
            iActionGetStateVariables.AddInputParameter(param);
            param = new ParameterString("StateVariableValuePairs", allowedValues);
            iActionGetStateVariables.AddOutputParameter(param);

            iActionSetStateVariables = new OpenHome.Net.Core.Action("SetStateVariables");
            param = new ParameterUint("InstanceID");
            iActionSetStateVariables.AddInputParameter(param);
            param = new ParameterString("RenderingControlUDN", allowedValues);
            iActionSetStateVariables.AddInputParameter(param);
            param = new ParameterString("ServiceType", allowedValues);
            iActionSetStateVariables.AddInputParameter(param);
            param = new ParameterString("ServiceId", allowedValues);
            iActionSetStateVariables.AddInputParameter(param);
            param = new ParameterString("StateVariableValuePairs", allowedValues);
            iActionSetStateVariables.AddInputParameter(param);
            param = new ParameterString("StateVariableList", allowedValues);
            iActionSetStateVariables.AddOutputParameter(param);

            iLastChange = new PropertyString("LastChange", LastChangePropertyChanged);
            AddProperty(iLastChange);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentPresetNameList"></param>
        public void SyncListPresets(uint aInstanceID, out String aCurrentPresetNameList)
        {
            SyncListPresetsUpnpOrgRenderingControl2 sync = new SyncListPresetsUpnpOrgRenderingControl2(this);
            BeginListPresets(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentPresetNameList = sync.CurrentPresetNameList();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndListPresets().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginListPresets(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionListPresets, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionListPresets.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionListPresets.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentPresetNameList"></param>
        public void EndListPresets(IntPtr aAsyncHandle, out String aCurrentPresetNameList)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentPresetNameList = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aPresetName"></param>
        public void SyncSelectPreset(uint aInstanceID, String aPresetName)
        {
            SyncSelectPresetUpnpOrgRenderingControl2 sync = new SyncSelectPresetUpnpOrgRenderingControl2(this);
            BeginSelectPreset(aInstanceID, aPresetName, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSelectPreset().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aPresetName"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSelectPreset(uint aInstanceID, String aPresetName, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSelectPreset, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSelectPreset.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSelectPreset.InputParameter(inIndex++), aPresetName));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSelectPreset(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBrightness"></param>
        public void SyncGetBrightness(uint aInstanceID, out uint aCurrentBrightness)
        {
            SyncGetBrightnessUpnpOrgRenderingControl2 sync = new SyncGetBrightnessUpnpOrgRenderingControl2(this);
            BeginGetBrightness(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentBrightness = sync.CurrentBrightness();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetBrightness().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetBrightness(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetBrightness, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetBrightness.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetBrightness.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentBrightness"></param>
        public void EndGetBrightness(IntPtr aAsyncHandle, out uint aCurrentBrightness)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentBrightness = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBrightness"></param>
        public void SyncSetBrightness(uint aInstanceID, uint aDesiredBrightness)
        {
            SyncSetBrightnessUpnpOrgRenderingControl2 sync = new SyncSetBrightnessUpnpOrgRenderingControl2(this);
            BeginSetBrightness(aInstanceID, aDesiredBrightness, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBrightness().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBrightness"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetBrightness(uint aInstanceID, uint aDesiredBrightness, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetBrightness, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetBrightness.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetBrightness.InputParameter(inIndex++), aDesiredBrightness));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetBrightness(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentContrast"></param>
        public void SyncGetContrast(uint aInstanceID, out uint aCurrentContrast)
        {
            SyncGetContrastUpnpOrgRenderingControl2 sync = new SyncGetContrastUpnpOrgRenderingControl2(this);
            BeginGetContrast(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentContrast = sync.CurrentContrast();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetContrast().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetContrast(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetContrast, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetContrast.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetContrast.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentContrast"></param>
        public void EndGetContrast(IntPtr aAsyncHandle, out uint aCurrentContrast)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentContrast = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredContrast"></param>
        public void SyncSetContrast(uint aInstanceID, uint aDesiredContrast)
        {
            SyncSetContrastUpnpOrgRenderingControl2 sync = new SyncSetContrastUpnpOrgRenderingControl2(this);
            BeginSetContrast(aInstanceID, aDesiredContrast, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetContrast().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredContrast"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetContrast(uint aInstanceID, uint aDesiredContrast, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetContrast, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetContrast.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetContrast.InputParameter(inIndex++), aDesiredContrast));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetContrast(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentSharpness"></param>
        public void SyncGetSharpness(uint aInstanceID, out uint aCurrentSharpness)
        {
            SyncGetSharpnessUpnpOrgRenderingControl2 sync = new SyncGetSharpnessUpnpOrgRenderingControl2(this);
            BeginGetSharpness(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentSharpness = sync.CurrentSharpness();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetSharpness().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetSharpness(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetSharpness, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetSharpness.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetSharpness.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentSharpness"></param>
        public void EndGetSharpness(IntPtr aAsyncHandle, out uint aCurrentSharpness)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentSharpness = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredSharpness"></param>
        public void SyncSetSharpness(uint aInstanceID, uint aDesiredSharpness)
        {
            SyncSetSharpnessUpnpOrgRenderingControl2 sync = new SyncSetSharpnessUpnpOrgRenderingControl2(this);
            BeginSetSharpness(aInstanceID, aDesiredSharpness, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetSharpness().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredSharpness"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetSharpness(uint aInstanceID, uint aDesiredSharpness, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetSharpness, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetSharpness.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetSharpness.InputParameter(inIndex++), aDesiredSharpness));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetSharpness(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentRedVideoGain"></param>
        public void SyncGetRedVideoGain(uint aInstanceID, out uint aCurrentRedVideoGain)
        {
            SyncGetRedVideoGainUpnpOrgRenderingControl2 sync = new SyncGetRedVideoGainUpnpOrgRenderingControl2(this);
            BeginGetRedVideoGain(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentRedVideoGain = sync.CurrentRedVideoGain();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRedVideoGain().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRedVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRedVideoGain, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetRedVideoGain.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRedVideoGain.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentRedVideoGain"></param>
        public void EndGetRedVideoGain(IntPtr aAsyncHandle, out uint aCurrentRedVideoGain)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentRedVideoGain = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredRedVideoGain"></param>
        public void SyncSetRedVideoGain(uint aInstanceID, uint aDesiredRedVideoGain)
        {
            SyncSetRedVideoGainUpnpOrgRenderingControl2 sync = new SyncSetRedVideoGainUpnpOrgRenderingControl2(this);
            BeginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRedVideoGain().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredRedVideoGain"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetRedVideoGain(uint aInstanceID, uint aDesiredRedVideoGain, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetRedVideoGain, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetRedVideoGain.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetRedVideoGain.InputParameter(inIndex++), aDesiredRedVideoGain));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetRedVideoGain(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentGreenVideoGain"></param>
        public void SyncGetGreenVideoGain(uint aInstanceID, out uint aCurrentGreenVideoGain)
        {
            SyncGetGreenVideoGainUpnpOrgRenderingControl2 sync = new SyncGetGreenVideoGainUpnpOrgRenderingControl2(this);
            BeginGetGreenVideoGain(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentGreenVideoGain = sync.CurrentGreenVideoGain();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetGreenVideoGain().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetGreenVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetGreenVideoGain, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetGreenVideoGain.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetGreenVideoGain.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentGreenVideoGain"></param>
        public void EndGetGreenVideoGain(IntPtr aAsyncHandle, out uint aCurrentGreenVideoGain)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentGreenVideoGain = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredGreenVideoGain"></param>
        public void SyncSetGreenVideoGain(uint aInstanceID, uint aDesiredGreenVideoGain)
        {
            SyncSetGreenVideoGainUpnpOrgRenderingControl2 sync = new SyncSetGreenVideoGainUpnpOrgRenderingControl2(this);
            BeginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetGreenVideoGain().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredGreenVideoGain"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetGreenVideoGain(uint aInstanceID, uint aDesiredGreenVideoGain, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetGreenVideoGain, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetGreenVideoGain.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetGreenVideoGain.InputParameter(inIndex++), aDesiredGreenVideoGain));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetGreenVideoGain(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBlueVideoGain"></param>
        public void SyncGetBlueVideoGain(uint aInstanceID, out uint aCurrentBlueVideoGain)
        {
            SyncGetBlueVideoGainUpnpOrgRenderingControl2 sync = new SyncGetBlueVideoGainUpnpOrgRenderingControl2(this);
            BeginGetBlueVideoGain(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentBlueVideoGain = sync.CurrentBlueVideoGain();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetBlueVideoGain().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetBlueVideoGain(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetBlueVideoGain, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetBlueVideoGain.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetBlueVideoGain.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentBlueVideoGain"></param>
        public void EndGetBlueVideoGain(IntPtr aAsyncHandle, out uint aCurrentBlueVideoGain)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentBlueVideoGain = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBlueVideoGain"></param>
        public void SyncSetBlueVideoGain(uint aInstanceID, uint aDesiredBlueVideoGain)
        {
            SyncSetBlueVideoGainUpnpOrgRenderingControl2 sync = new SyncSetBlueVideoGainUpnpOrgRenderingControl2(this);
            BeginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBlueVideoGain().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBlueVideoGain"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetBlueVideoGain(uint aInstanceID, uint aDesiredBlueVideoGain, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetBlueVideoGain, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetBlueVideoGain.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetBlueVideoGain.InputParameter(inIndex++), aDesiredBlueVideoGain));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetBlueVideoGain(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentRedVideoBlackLevel"></param>
        public void SyncGetRedVideoBlackLevel(uint aInstanceID, out uint aCurrentRedVideoBlackLevel)
        {
            SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2 sync = new SyncGetRedVideoBlackLevelUpnpOrgRenderingControl2(this);
            BeginGetRedVideoBlackLevel(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentRedVideoBlackLevel = sync.CurrentRedVideoBlackLevel();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRedVideoBlackLevel().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRedVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRedVideoBlackLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetRedVideoBlackLevel.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRedVideoBlackLevel.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentRedVideoBlackLevel"></param>
        public void EndGetRedVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentRedVideoBlackLevel)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentRedVideoBlackLevel = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredRedVideoBlackLevel"></param>
        public void SyncSetRedVideoBlackLevel(uint aInstanceID, uint aDesiredRedVideoBlackLevel)
        {
            SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2 sync = new SyncSetRedVideoBlackLevelUpnpOrgRenderingControl2(this);
            BeginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRedVideoBlackLevel().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredRedVideoBlackLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetRedVideoBlackLevel(uint aInstanceID, uint aDesiredRedVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetRedVideoBlackLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetRedVideoBlackLevel.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetRedVideoBlackLevel.InputParameter(inIndex++), aDesiredRedVideoBlackLevel));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetRedVideoBlackLevel(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentGreenVideoBlackLevel"></param>
        public void SyncGetGreenVideoBlackLevel(uint aInstanceID, out uint aCurrentGreenVideoBlackLevel)
        {
            SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2 sync = new SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl2(this);
            BeginGetGreenVideoBlackLevel(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentGreenVideoBlackLevel = sync.CurrentGreenVideoBlackLevel();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetGreenVideoBlackLevel().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetGreenVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetGreenVideoBlackLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetGreenVideoBlackLevel.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetGreenVideoBlackLevel.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentGreenVideoBlackLevel"></param>
        public void EndGetGreenVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentGreenVideoBlackLevel)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentGreenVideoBlackLevel = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredGreenVideoBlackLevel"></param>
        public void SyncSetGreenVideoBlackLevel(uint aInstanceID, uint aDesiredGreenVideoBlackLevel)
        {
            SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2 sync = new SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl2(this);
            BeginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetGreenVideoBlackLevel().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredGreenVideoBlackLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetGreenVideoBlackLevel(uint aInstanceID, uint aDesiredGreenVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetGreenVideoBlackLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetGreenVideoBlackLevel.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetGreenVideoBlackLevel.InputParameter(inIndex++), aDesiredGreenVideoBlackLevel));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetGreenVideoBlackLevel(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentBlueVideoBlackLevel"></param>
        public void SyncGetBlueVideoBlackLevel(uint aInstanceID, out uint aCurrentBlueVideoBlackLevel)
        {
            SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2 sync = new SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl2(this);
            BeginGetBlueVideoBlackLevel(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentBlueVideoBlackLevel = sync.CurrentBlueVideoBlackLevel();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetBlueVideoBlackLevel().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetBlueVideoBlackLevel(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetBlueVideoBlackLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetBlueVideoBlackLevel.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetBlueVideoBlackLevel.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentBlueVideoBlackLevel"></param>
        public void EndGetBlueVideoBlackLevel(IntPtr aAsyncHandle, out uint aCurrentBlueVideoBlackLevel)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentBlueVideoBlackLevel = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBlueVideoBlackLevel"></param>
        public void SyncSetBlueVideoBlackLevel(uint aInstanceID, uint aDesiredBlueVideoBlackLevel)
        {
            SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2 sync = new SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl2(this);
            BeginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetBlueVideoBlackLevel().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredBlueVideoBlackLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetBlueVideoBlackLevel(uint aInstanceID, uint aDesiredBlueVideoBlackLevel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetBlueVideoBlackLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetBlueVideoBlackLevel.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetBlueVideoBlackLevel.InputParameter(inIndex++), aDesiredBlueVideoBlackLevel));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetBlueVideoBlackLevel(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentColorTemperature"></param>
        public void SyncGetColorTemperature(uint aInstanceID, out uint aCurrentColorTemperature)
        {
            SyncGetColorTemperatureUpnpOrgRenderingControl2 sync = new SyncGetColorTemperatureUpnpOrgRenderingControl2(this);
            BeginGetColorTemperature(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentColorTemperature = sync.CurrentColorTemperature();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetColorTemperature().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetColorTemperature(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetColorTemperature, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetColorTemperature.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetColorTemperature.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentColorTemperature"></param>
        public void EndGetColorTemperature(IntPtr aAsyncHandle, out uint aCurrentColorTemperature)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentColorTemperature = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredColorTemperature"></param>
        public void SyncSetColorTemperature(uint aInstanceID, uint aDesiredColorTemperature)
        {
            SyncSetColorTemperatureUpnpOrgRenderingControl2 sync = new SyncSetColorTemperatureUpnpOrgRenderingControl2(this);
            BeginSetColorTemperature(aInstanceID, aDesiredColorTemperature, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetColorTemperature().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredColorTemperature"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetColorTemperature(uint aInstanceID, uint aDesiredColorTemperature, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetColorTemperature, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetColorTemperature.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetColorTemperature.InputParameter(inIndex++), aDesiredColorTemperature));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetColorTemperature(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentHorizontalKeystone"></param>
        public void SyncGetHorizontalKeystone(uint aInstanceID, out int aCurrentHorizontalKeystone)
        {
            SyncGetHorizontalKeystoneUpnpOrgRenderingControl2 sync = new SyncGetHorizontalKeystoneUpnpOrgRenderingControl2(this);
            BeginGetHorizontalKeystone(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentHorizontalKeystone = sync.CurrentHorizontalKeystone();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetHorizontalKeystone().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetHorizontalKeystone(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetHorizontalKeystone, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetHorizontalKeystone.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetHorizontalKeystone.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentHorizontalKeystone"></param>
        public void EndGetHorizontalKeystone(IntPtr aAsyncHandle, out int aCurrentHorizontalKeystone)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentHorizontalKeystone = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredHorizontalKeystone"></param>
        public void SyncSetHorizontalKeystone(uint aInstanceID, int aDesiredHorizontalKeystone)
        {
            SyncSetHorizontalKeystoneUpnpOrgRenderingControl2 sync = new SyncSetHorizontalKeystoneUpnpOrgRenderingControl2(this);
            BeginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetHorizontalKeystone().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredHorizontalKeystone"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetHorizontalKeystone(uint aInstanceID, int aDesiredHorizontalKeystone, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetHorizontalKeystone, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetHorizontalKeystone.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSetHorizontalKeystone.InputParameter(inIndex++), aDesiredHorizontalKeystone));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetHorizontalKeystone(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aCurrentVerticalKeystone"></param>
        public void SyncGetVerticalKeystone(uint aInstanceID, out int aCurrentVerticalKeystone)
        {
            SyncGetVerticalKeystoneUpnpOrgRenderingControl2 sync = new SyncGetVerticalKeystoneUpnpOrgRenderingControl2(this);
            BeginGetVerticalKeystone(aInstanceID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentVerticalKeystone = sync.CurrentVerticalKeystone();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetVerticalKeystone().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetVerticalKeystone(uint aInstanceID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetVerticalKeystone, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetVerticalKeystone.InputParameter(inIndex++), aInstanceID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetVerticalKeystone.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentVerticalKeystone"></param>
        public void EndGetVerticalKeystone(IntPtr aAsyncHandle, out int aCurrentVerticalKeystone)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentVerticalKeystone = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredVerticalKeystone"></param>
        public void SyncSetVerticalKeystone(uint aInstanceID, int aDesiredVerticalKeystone)
        {
            SyncSetVerticalKeystoneUpnpOrgRenderingControl2 sync = new SyncSetVerticalKeystoneUpnpOrgRenderingControl2(this);
            BeginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVerticalKeystone().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aDesiredVerticalKeystone"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetVerticalKeystone(uint aInstanceID, int aDesiredVerticalKeystone, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetVerticalKeystone, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetVerticalKeystone.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSetVerticalKeystone.InputParameter(inIndex++), aDesiredVerticalKeystone));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetVerticalKeystone(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentMute"></param>
        public void SyncGetMute(uint aInstanceID, String aChannel, out bool aCurrentMute)
        {
            SyncGetMuteUpnpOrgRenderingControl2 sync = new SyncGetMuteUpnpOrgRenderingControl2(this);
            BeginGetMute(aInstanceID, aChannel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentMute = sync.CurrentMute();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetMute().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetMute(uint aInstanceID, String aChannel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetMute, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetMute.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetMute.InputParameter(inIndex++), aChannel));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetMute.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentMute"></param>
        public void EndGetMute(IntPtr aAsyncHandle, out bool aCurrentMute)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentMute = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredMute"></param>
        public void SyncSetMute(uint aInstanceID, String aChannel, bool aDesiredMute)
        {
            SyncSetMuteUpnpOrgRenderingControl2 sync = new SyncSetMuteUpnpOrgRenderingControl2(this);
            BeginSetMute(aInstanceID, aChannel, aDesiredMute, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetMute().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredMute"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetMute(uint aInstanceID, String aChannel, bool aDesiredMute, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetMute, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetMute.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetMute.InputParameter(inIndex++), aChannel));
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetMute.InputParameter(inIndex++), aDesiredMute));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetMute(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentVolume"></param>
        public void SyncGetVolume(uint aInstanceID, String aChannel, out uint aCurrentVolume)
        {
            SyncGetVolumeUpnpOrgRenderingControl2 sync = new SyncGetVolumeUpnpOrgRenderingControl2(this);
            BeginGetVolume(aInstanceID, aChannel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentVolume = sync.CurrentVolume();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetVolume().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetVolume(uint aInstanceID, String aChannel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetVolume, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetVolume.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetVolume.InputParameter(inIndex++), aChannel));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetVolume.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentVolume"></param>
        public void EndGetVolume(IntPtr aAsyncHandle, out uint aCurrentVolume)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentVolume = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredVolume"></param>
        public void SyncSetVolume(uint aInstanceID, String aChannel, uint aDesiredVolume)
        {
            SyncSetVolumeUpnpOrgRenderingControl2 sync = new SyncSetVolumeUpnpOrgRenderingControl2(this);
            BeginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolume().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredVolume"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetVolume(uint aInstanceID, String aChannel, uint aDesiredVolume, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetVolume, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetVolume.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetVolume.InputParameter(inIndex++), aChannel));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetVolume.InputParameter(inIndex++), aDesiredVolume));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetVolume(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentVolume"></param>
        public void SyncGetVolumeDB(uint aInstanceID, String aChannel, out int aCurrentVolume)
        {
            SyncGetVolumeDBUpnpOrgRenderingControl2 sync = new SyncGetVolumeDBUpnpOrgRenderingControl2(this);
            BeginGetVolumeDB(aInstanceID, aChannel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentVolume = sync.CurrentVolume();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetVolumeDB().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetVolumeDB(uint aInstanceID, String aChannel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetVolumeDB, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetVolumeDB.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetVolumeDB.InputParameter(inIndex++), aChannel));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetVolumeDB.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentVolume"></param>
        public void EndGetVolumeDB(IntPtr aAsyncHandle, out int aCurrentVolume)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentVolume = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredVolume"></param>
        public void SyncSetVolumeDB(uint aInstanceID, String aChannel, int aDesiredVolume)
        {
            SyncSetVolumeDBUpnpOrgRenderingControl2 sync = new SyncSetVolumeDBUpnpOrgRenderingControl2(this);
            BeginSetVolumeDB(aInstanceID, aChannel, aDesiredVolume, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetVolumeDB().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredVolume"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetVolumeDB(uint aInstanceID, String aChannel, int aDesiredVolume, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetVolumeDB, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetVolumeDB.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetVolumeDB.InputParameter(inIndex++), aChannel));
            invocation.AddInput(new ArgumentInt((ParameterInt)iActionSetVolumeDB.InputParameter(inIndex++), aDesiredVolume));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetVolumeDB(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aMinValue"></param>
        /// <param name="aMaxValue"></param>
        public void SyncGetVolumeDBRange(uint aInstanceID, String aChannel, out int aMinValue, out int aMaxValue)
        {
            SyncGetVolumeDBRangeUpnpOrgRenderingControl2 sync = new SyncGetVolumeDBRangeUpnpOrgRenderingControl2(this);
            BeginGetVolumeDBRange(aInstanceID, aChannel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aMinValue = sync.MinValue();
            aMaxValue = sync.MaxValue();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetVolumeDBRange().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetVolumeDBRange(uint aInstanceID, String aChannel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetVolumeDBRange, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetVolumeDBRange.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetVolumeDBRange.InputParameter(inIndex++), aChannel));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetVolumeDBRange.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentInt((ParameterInt)iActionGetVolumeDBRange.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aMinValue"></param>
        /// <param name="aMaxValue"></param>
        public void EndGetVolumeDBRange(IntPtr aAsyncHandle, out int aMinValue, out int aMaxValue)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aMinValue = Invocation.OutputInt(aAsyncHandle, index++);
            aMaxValue = Invocation.OutputInt(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCurrentLoudness"></param>
        public void SyncGetLoudness(uint aInstanceID, String aChannel, out bool aCurrentLoudness)
        {
            SyncGetLoudnessUpnpOrgRenderingControl2 sync = new SyncGetLoudnessUpnpOrgRenderingControl2(this);
            BeginGetLoudness(aInstanceID, aChannel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aCurrentLoudness = sync.CurrentLoudness();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLoudness().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetLoudness(uint aInstanceID, String aChannel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetLoudness, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetLoudness.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetLoudness.InputParameter(inIndex++), aChannel));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetLoudness.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aCurrentLoudness"></param>
        public void EndGetLoudness(IntPtr aAsyncHandle, out bool aCurrentLoudness)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aCurrentLoudness = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredLoudness"></param>
        public void SyncSetLoudness(uint aInstanceID, String aChannel, bool aDesiredLoudness)
        {
            SyncSetLoudnessUpnpOrgRenderingControl2 sync = new SyncSetLoudnessUpnpOrgRenderingControl2(this);
            BeginSetLoudness(aInstanceID, aChannel, aDesiredLoudness, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetLoudness().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aChannel"></param>
        /// <param name="aDesiredLoudness"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetLoudness(uint aInstanceID, String aChannel, bool aDesiredLoudness, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetLoudness, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetLoudness.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetLoudness.InputParameter(inIndex++), aChannel));
            invocation.AddInput(new ArgumentBool((ParameterBool)iActionSetLoudness.InputParameter(inIndex++), aDesiredLoudness));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetLoudness(IntPtr aAsyncHandle)
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
        /// <param name="aInstanceID"></param>
        /// <param name="aStateVariableList"></param>
        /// <param name="aStateVariableValuePairs"></param>
        public void SyncGetStateVariables(uint aInstanceID, String aStateVariableList, out String aStateVariableValuePairs)
        {
            SyncGetStateVariablesUpnpOrgRenderingControl2 sync = new SyncGetStateVariablesUpnpOrgRenderingControl2(this);
            BeginGetStateVariables(aInstanceID, aStateVariableList, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aStateVariableValuePairs = sync.StateVariableValuePairs();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetStateVariables().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aStateVariableList"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetStateVariables(uint aInstanceID, String aStateVariableList, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetStateVariables, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetStateVariables.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionGetStateVariables.InputParameter(inIndex++), aStateVariableList));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetStateVariables.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aStateVariableValuePairs"></param>
        public void EndGetStateVariables(IntPtr aAsyncHandle, out String aStateVariableValuePairs)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aStateVariableValuePairs = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aRenderingControlUDN"></param>
        /// <param name="aServiceType"></param>
        /// <param name="aServiceId"></param>
        /// <param name="aStateVariableValuePairs"></param>
        /// <param name="aStateVariableList"></param>
        public void SyncSetStateVariables(uint aInstanceID, String aRenderingControlUDN, String aServiceType, String aServiceId, String aStateVariableValuePairs, out String aStateVariableList)
        {
            SyncSetStateVariablesUpnpOrgRenderingControl2 sync = new SyncSetStateVariablesUpnpOrgRenderingControl2(this);
            BeginSetStateVariables(aInstanceID, aRenderingControlUDN, aServiceType, aServiceId, aStateVariableValuePairs, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aStateVariableList = sync.StateVariableList();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStateVariables().</remarks>
        /// <param name="aInstanceID"></param>
        /// <param name="aRenderingControlUDN"></param>
        /// <param name="aServiceType"></param>
        /// <param name="aServiceId"></param>
        /// <param name="aStateVariableValuePairs"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStateVariables(uint aInstanceID, String aRenderingControlUDN, String aServiceType, String aServiceId, String aStateVariableValuePairs, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStateVariables, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetStateVariables.InputParameter(inIndex++), aInstanceID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetStateVariables.InputParameter(inIndex++), aRenderingControlUDN));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetStateVariables.InputParameter(inIndex++), aServiceType));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetStateVariables.InputParameter(inIndex++), aServiceId));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetStateVariables.InputParameter(inIndex++), aStateVariableValuePairs));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSetStateVariables.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aStateVariableList"></param>
        public void EndSetStateVariables(IntPtr aAsyncHandle, out String aStateVariableList)
        {
            uint code;
            string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aStateVariableList = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the LastChange state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgRenderingControl2 instance will not overlap.</remarks>
        /// <param name="aLastChangeChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyLastChangeChanged(System.Action aLastChangeChanged)
        {
            lock (iPropertyLock)
            {
                iLastChangeChanged = aLastChangeChanged;
            }
        }

        private void LastChangePropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iLastChangeChanged);
            }
        }

        /// <summary>
        /// Query the value of the LastChange property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the LastChange property</returns>
        public String PropertyLastChange()
        {
            PropertyReadLock();
            String val;
            try
            {
                val = iLastChange.Value();
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
            iActionListPresets.Dispose();
            iActionSelectPreset.Dispose();
            iActionGetBrightness.Dispose();
            iActionSetBrightness.Dispose();
            iActionGetContrast.Dispose();
            iActionSetContrast.Dispose();
            iActionGetSharpness.Dispose();
            iActionSetSharpness.Dispose();
            iActionGetRedVideoGain.Dispose();
            iActionSetRedVideoGain.Dispose();
            iActionGetGreenVideoGain.Dispose();
            iActionSetGreenVideoGain.Dispose();
            iActionGetBlueVideoGain.Dispose();
            iActionSetBlueVideoGain.Dispose();
            iActionGetRedVideoBlackLevel.Dispose();
            iActionSetRedVideoBlackLevel.Dispose();
            iActionGetGreenVideoBlackLevel.Dispose();
            iActionSetGreenVideoBlackLevel.Dispose();
            iActionGetBlueVideoBlackLevel.Dispose();
            iActionSetBlueVideoBlackLevel.Dispose();
            iActionGetColorTemperature.Dispose();
            iActionSetColorTemperature.Dispose();
            iActionGetHorizontalKeystone.Dispose();
            iActionSetHorizontalKeystone.Dispose();
            iActionGetVerticalKeystone.Dispose();
            iActionSetVerticalKeystone.Dispose();
            iActionGetMute.Dispose();
            iActionSetMute.Dispose();
            iActionGetVolume.Dispose();
            iActionSetVolume.Dispose();
            iActionGetVolumeDB.Dispose();
            iActionSetVolumeDB.Dispose();
            iActionGetVolumeDBRange.Dispose();
            iActionGetLoudness.Dispose();
            iActionSetLoudness.Dispose();
            iActionGetStateVariables.Dispose();
            iActionSetStateVariables.Dispose();
            iLastChange.Dispose();
        }
    }
}

