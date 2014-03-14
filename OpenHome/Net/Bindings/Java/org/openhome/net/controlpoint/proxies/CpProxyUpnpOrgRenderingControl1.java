package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgRenderingControl1.*;
import org.openhome.net.core.*;

    
interface ICpProxyUpnpOrgRenderingControl1 extends ICpProxy
{
    public String syncListPresets(long aInstanceID);
    public void beginListPresets(long aInstanceID, ICpProxyListener aCallback);
    public String endListPresets(long aAsyncHandle);
    public void syncSelectPreset(long aInstanceID, String aPresetName);
    public void beginSelectPreset(long aInstanceID, String aPresetName, ICpProxyListener aCallback);
    public void endSelectPreset(long aAsyncHandle);
    public long syncGetBrightness(long aInstanceID);
    public void beginGetBrightness(long aInstanceID, ICpProxyListener aCallback);
    public long endGetBrightness(long aAsyncHandle);
    public void syncSetBrightness(long aInstanceID, long aDesiredBrightness);
    public void beginSetBrightness(long aInstanceID, long aDesiredBrightness, ICpProxyListener aCallback);
    public void endSetBrightness(long aAsyncHandle);
    public long syncGetContrast(long aInstanceID);
    public void beginGetContrast(long aInstanceID, ICpProxyListener aCallback);
    public long endGetContrast(long aAsyncHandle);
    public void syncSetContrast(long aInstanceID, long aDesiredContrast);
    public void beginSetContrast(long aInstanceID, long aDesiredContrast, ICpProxyListener aCallback);
    public void endSetContrast(long aAsyncHandle);
    public long syncGetSharpness(long aInstanceID);
    public void beginGetSharpness(long aInstanceID, ICpProxyListener aCallback);
    public long endGetSharpness(long aAsyncHandle);
    public void syncSetSharpness(long aInstanceID, long aDesiredSharpness);
    public void beginSetSharpness(long aInstanceID, long aDesiredSharpness, ICpProxyListener aCallback);
    public void endSetSharpness(long aAsyncHandle);
    public long syncGetRedVideoGain(long aInstanceID);
    public void beginGetRedVideoGain(long aInstanceID, ICpProxyListener aCallback);
    public long endGetRedVideoGain(long aAsyncHandle);
    public void syncSetRedVideoGain(long aInstanceID, long aDesiredRedVideoGain);
    public void beginSetRedVideoGain(long aInstanceID, long aDesiredRedVideoGain, ICpProxyListener aCallback);
    public void endSetRedVideoGain(long aAsyncHandle);
    public long syncGetGreenVideoGain(long aInstanceID);
    public void beginGetGreenVideoGain(long aInstanceID, ICpProxyListener aCallback);
    public long endGetGreenVideoGain(long aAsyncHandle);
    public void syncSetGreenVideoGain(long aInstanceID, long aDesiredGreenVideoGain);
    public void beginSetGreenVideoGain(long aInstanceID, long aDesiredGreenVideoGain, ICpProxyListener aCallback);
    public void endSetGreenVideoGain(long aAsyncHandle);
    public long syncGetBlueVideoGain(long aInstanceID);
    public void beginGetBlueVideoGain(long aInstanceID, ICpProxyListener aCallback);
    public long endGetBlueVideoGain(long aAsyncHandle);
    public void syncSetBlueVideoGain(long aInstanceID, long aDesiredBlueVideoGain);
    public void beginSetBlueVideoGain(long aInstanceID, long aDesiredBlueVideoGain, ICpProxyListener aCallback);
    public void endSetBlueVideoGain(long aAsyncHandle);
    public long syncGetRedVideoBlackLevel(long aInstanceID);
    public void beginGetRedVideoBlackLevel(long aInstanceID, ICpProxyListener aCallback);
    public long endGetRedVideoBlackLevel(long aAsyncHandle);
    public void syncSetRedVideoBlackLevel(long aInstanceID, long aDesiredRedVideoBlackLevel);
    public void beginSetRedVideoBlackLevel(long aInstanceID, long aDesiredRedVideoBlackLevel, ICpProxyListener aCallback);
    public void endSetRedVideoBlackLevel(long aAsyncHandle);
    public long syncGetGreenVideoBlackLevel(long aInstanceID);
    public void beginGetGreenVideoBlackLevel(long aInstanceID, ICpProxyListener aCallback);
    public long endGetGreenVideoBlackLevel(long aAsyncHandle);
    public void syncSetGreenVideoBlackLevel(long aInstanceID, long aDesiredGreenVideoBlackLevel);
    public void beginSetGreenVideoBlackLevel(long aInstanceID, long aDesiredGreenVideoBlackLevel, ICpProxyListener aCallback);
    public void endSetGreenVideoBlackLevel(long aAsyncHandle);
    public long syncGetBlueVideoBlackLevel(long aInstanceID);
    public void beginGetBlueVideoBlackLevel(long aInstanceID, ICpProxyListener aCallback);
    public long endGetBlueVideoBlackLevel(long aAsyncHandle);
    public void syncSetBlueVideoBlackLevel(long aInstanceID, long aDesiredBlueVideoBlackLevel);
    public void beginSetBlueVideoBlackLevel(long aInstanceID, long aDesiredBlueVideoBlackLevel, ICpProxyListener aCallback);
    public void endSetBlueVideoBlackLevel(long aAsyncHandle);
    public long syncGetColorTemperature(long aInstanceID);
    public void beginGetColorTemperature(long aInstanceID, ICpProxyListener aCallback);
    public long endGetColorTemperature(long aAsyncHandle);
    public void syncSetColorTemperature(long aInstanceID, long aDesiredColorTemperature);
    public void beginSetColorTemperature(long aInstanceID, long aDesiredColorTemperature, ICpProxyListener aCallback);
    public void endSetColorTemperature(long aAsyncHandle);
    public int syncGetHorizontalKeystone(long aInstanceID);
    public void beginGetHorizontalKeystone(long aInstanceID, ICpProxyListener aCallback);
    public int endGetHorizontalKeystone(long aAsyncHandle);
    public void syncSetHorizontalKeystone(long aInstanceID, int aDesiredHorizontalKeystone);
    public void beginSetHorizontalKeystone(long aInstanceID, int aDesiredHorizontalKeystone, ICpProxyListener aCallback);
    public void endSetHorizontalKeystone(long aAsyncHandle);
    public int syncGetVerticalKeystone(long aInstanceID);
    public void beginGetVerticalKeystone(long aInstanceID, ICpProxyListener aCallback);
    public int endGetVerticalKeystone(long aAsyncHandle);
    public void syncSetVerticalKeystone(long aInstanceID, int aDesiredVerticalKeystone);
    public void beginSetVerticalKeystone(long aInstanceID, int aDesiredVerticalKeystone, ICpProxyListener aCallback);
    public void endSetVerticalKeystone(long aAsyncHandle);
    public boolean syncGetMute(long aInstanceID, String aChannel);
    public void beginGetMute(long aInstanceID, String aChannel, ICpProxyListener aCallback);
    public boolean endGetMute(long aAsyncHandle);
    public void syncSetMute(long aInstanceID, String aChannel, boolean aDesiredMute);
    public void beginSetMute(long aInstanceID, String aChannel, boolean aDesiredMute, ICpProxyListener aCallback);
    public void endSetMute(long aAsyncHandle);
    public long syncGetVolume(long aInstanceID, String aChannel);
    public void beginGetVolume(long aInstanceID, String aChannel, ICpProxyListener aCallback);
    public long endGetVolume(long aAsyncHandle);
    public void syncSetVolume(long aInstanceID, String aChannel, long aDesiredVolume);
    public void beginSetVolume(long aInstanceID, String aChannel, long aDesiredVolume, ICpProxyListener aCallback);
    public void endSetVolume(long aAsyncHandle);
    public int syncGetVolumeDB(long aInstanceID, String aChannel);
    public void beginGetVolumeDB(long aInstanceID, String aChannel, ICpProxyListener aCallback);
    public int endGetVolumeDB(long aAsyncHandle);
    public void syncSetVolumeDB(long aInstanceID, String aChannel, int aDesiredVolume);
    public void beginSetVolumeDB(long aInstanceID, String aChannel, int aDesiredVolume, ICpProxyListener aCallback);
    public void endSetVolumeDB(long aAsyncHandle);
    public GetVolumeDBRange syncGetVolumeDBRange(long aInstanceID, String aChannel);
    public void beginGetVolumeDBRange(long aInstanceID, String aChannel, ICpProxyListener aCallback);
    public GetVolumeDBRange endGetVolumeDBRange(long aAsyncHandle);
    public boolean syncGetLoudness(long aInstanceID, String aChannel);
    public void beginGetLoudness(long aInstanceID, String aChannel, ICpProxyListener aCallback);
    public boolean endGetLoudness(long aAsyncHandle);
    public void syncSetLoudness(long aInstanceID, String aChannel, boolean aDesiredLoudness);
    public void beginSetLoudness(long aInstanceID, String aChannel, boolean aDesiredLoudness, ICpProxyListener aCallback);
    public void endSetLoudness(long aAsyncHandle);
    public void setPropertyLastChangeChanged(IPropertyChangeListener aLastChangeChanged);
    public String getPropertyLastChange();
}

class SyncListPresetsUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private String iCurrentPresetNameList;

    public SyncListPresetsUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public String getCurrentPresetNameList()
    {
        return iCurrentPresetNameList;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endListPresets(aAsyncHandle);
        
        iCurrentPresetNameList = result;
    }
}

class SyncSelectPresetUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSelectPresetUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSelectPreset(aAsyncHandle);
        
    }
}

class SyncGetBrightnessUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentBrightness;

    public SyncGetBrightnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentBrightness()
    {
        return iCurrentBrightness;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetBrightness(aAsyncHandle);
        
        iCurrentBrightness = result;
    }
}

class SyncSetBrightnessUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetBrightnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetBrightness(aAsyncHandle);
        
    }
}

class SyncGetContrastUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentContrast;

    public SyncGetContrastUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentContrast()
    {
        return iCurrentContrast;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetContrast(aAsyncHandle);
        
        iCurrentContrast = result;
    }
}

class SyncSetContrastUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetContrastUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetContrast(aAsyncHandle);
        
    }
}

class SyncGetSharpnessUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentSharpness;

    public SyncGetSharpnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentSharpness()
    {
        return iCurrentSharpness;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetSharpness(aAsyncHandle);
        
        iCurrentSharpness = result;
    }
}

class SyncSetSharpnessUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetSharpnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetSharpness(aAsyncHandle);
        
    }
}

class SyncGetRedVideoGainUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentRedVideoGain;

    public SyncGetRedVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentRedVideoGain()
    {
        return iCurrentRedVideoGain;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetRedVideoGain(aAsyncHandle);
        
        iCurrentRedVideoGain = result;
    }
}

class SyncSetRedVideoGainUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetRedVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetRedVideoGain(aAsyncHandle);
        
    }
}

class SyncGetGreenVideoGainUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentGreenVideoGain;

    public SyncGetGreenVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentGreenVideoGain()
    {
        return iCurrentGreenVideoGain;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetGreenVideoGain(aAsyncHandle);
        
        iCurrentGreenVideoGain = result;
    }
}

class SyncSetGreenVideoGainUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetGreenVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetGreenVideoGain(aAsyncHandle);
        
    }
}

class SyncGetBlueVideoGainUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentBlueVideoGain;

    public SyncGetBlueVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentBlueVideoGain()
    {
        return iCurrentBlueVideoGain;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetBlueVideoGain(aAsyncHandle);
        
        iCurrentBlueVideoGain = result;
    }
}

class SyncSetBlueVideoGainUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetBlueVideoGainUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetBlueVideoGain(aAsyncHandle);
        
    }
}

class SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentRedVideoBlackLevel;

    public SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentRedVideoBlackLevel()
    {
        return iCurrentRedVideoBlackLevel;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetRedVideoBlackLevel(aAsyncHandle);
        
        iCurrentRedVideoBlackLevel = result;
    }
}

class SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetRedVideoBlackLevel(aAsyncHandle);
        
    }
}

class SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentGreenVideoBlackLevel;

    public SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentGreenVideoBlackLevel()
    {
        return iCurrentGreenVideoBlackLevel;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetGreenVideoBlackLevel(aAsyncHandle);
        
        iCurrentGreenVideoBlackLevel = result;
    }
}

class SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetGreenVideoBlackLevel(aAsyncHandle);
        
    }
}

class SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentBlueVideoBlackLevel;

    public SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentBlueVideoBlackLevel()
    {
        return iCurrentBlueVideoBlackLevel;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetBlueVideoBlackLevel(aAsyncHandle);
        
        iCurrentBlueVideoBlackLevel = result;
    }
}

class SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetBlueVideoBlackLevel(aAsyncHandle);
        
    }
}

class SyncGetColorTemperatureUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentColorTemperature;

    public SyncGetColorTemperatureUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentColorTemperature()
    {
        return iCurrentColorTemperature;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetColorTemperature(aAsyncHandle);
        
        iCurrentColorTemperature = result;
    }
}

class SyncSetColorTemperatureUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetColorTemperatureUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetColorTemperature(aAsyncHandle);
        
    }
}

class SyncGetHorizontalKeystoneUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private int iCurrentHorizontalKeystone;

    public SyncGetHorizontalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public int getCurrentHorizontalKeystone()
    {
        return iCurrentHorizontalKeystone;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        int result = iService.endGetHorizontalKeystone(aAsyncHandle);
        
        iCurrentHorizontalKeystone = result;
    }
}

class SyncSetHorizontalKeystoneUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetHorizontalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetHorizontalKeystone(aAsyncHandle);
        
    }
}

class SyncGetVerticalKeystoneUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private int iCurrentVerticalKeystone;

    public SyncGetVerticalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public int getCurrentVerticalKeystone()
    {
        return iCurrentVerticalKeystone;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        int result = iService.endGetVerticalKeystone(aAsyncHandle);
        
        iCurrentVerticalKeystone = result;
    }
}

class SyncSetVerticalKeystoneUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetVerticalKeystoneUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetVerticalKeystone(aAsyncHandle);
        
    }
}

class SyncGetMuteUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private boolean iCurrentMute;

    public SyncGetMuteUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getCurrentMute()
    {
        return iCurrentMute;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endGetMute(aAsyncHandle);
        
        iCurrentMute = result;
    }
}

class SyncSetMuteUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetMuteUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetMute(aAsyncHandle);
        
    }
}

class SyncGetVolumeUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private long iCurrentVolume;

    public SyncGetVolumeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public long getCurrentVolume()
    {
        return iCurrentVolume;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetVolume(aAsyncHandle);
        
        iCurrentVolume = result;
    }
}

class SyncSetVolumeUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetVolumeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetVolume(aAsyncHandle);
        
    }
}

class SyncGetVolumeDBUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private int iCurrentVolume;

    public SyncGetVolumeDBUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public int getCurrentVolume()
    {
        return iCurrentVolume;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        int result = iService.endGetVolumeDB(aAsyncHandle);
        
        iCurrentVolume = result;
    }
}

class SyncSetVolumeDBUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetVolumeDBUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetVolumeDB(aAsyncHandle);
        
    }
}

class SyncGetVolumeDBRangeUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private int iMinValue;
    private int iMaxValue;

    public SyncGetVolumeDBRangeUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public int getMinValue()
    {
        return iMinValue;
    }
    public int getMaxValue()
    {
        return iMaxValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetVolumeDBRange result = iService.endGetVolumeDBRange(aAsyncHandle);
        
        iMinValue = result.getMinValue();
        iMaxValue = result.getMaxValue();
    }
}

class SyncGetLoudnessUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;
    private boolean iCurrentLoudness;

    public SyncGetLoudnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getCurrentLoudness()
    {
        return iCurrentLoudness;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endGetLoudness(aAsyncHandle);
        
        iCurrentLoudness = result;
    }
}

class SyncSetLoudnessUpnpOrgRenderingControl1 extends SyncProxyAction
{
    private CpProxyUpnpOrgRenderingControl1 iService;

    public SyncSetLoudnessUpnpOrgRenderingControl1(CpProxyUpnpOrgRenderingControl1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetLoudness(aAsyncHandle);
        
    }
}

/**
 * Proxy for the upnp.org:RenderingControl:1 UPnP service
 */
public class CpProxyUpnpOrgRenderingControl1 extends CpProxy implements ICpProxyUpnpOrgRenderingControl1
{

    public class GetVolumeDBRange
    {
        private int iMinValue;
        private int iMaxValue;

        public GetVolumeDBRange(
            int aMinValue,
            int aMaxValue
        )
        {
            iMinValue = aMinValue;
            iMaxValue = aMaxValue;
        }
        public int getMinValue()
        {
            return iMinValue;
        }
        public int getMaxValue()
        {
            return iMaxValue;
        }
    }

    private Action iActionListPresets;
    private Action iActionSelectPreset;
    private Action iActionGetBrightness;
    private Action iActionSetBrightness;
    private Action iActionGetContrast;
    private Action iActionSetContrast;
    private Action iActionGetSharpness;
    private Action iActionSetSharpness;
    private Action iActionGetRedVideoGain;
    private Action iActionSetRedVideoGain;
    private Action iActionGetGreenVideoGain;
    private Action iActionSetGreenVideoGain;
    private Action iActionGetBlueVideoGain;
    private Action iActionSetBlueVideoGain;
    private Action iActionGetRedVideoBlackLevel;
    private Action iActionSetRedVideoBlackLevel;
    private Action iActionGetGreenVideoBlackLevel;
    private Action iActionSetGreenVideoBlackLevel;
    private Action iActionGetBlueVideoBlackLevel;
    private Action iActionSetBlueVideoBlackLevel;
    private Action iActionGetColorTemperature;
    private Action iActionSetColorTemperature;
    private Action iActionGetHorizontalKeystone;
    private Action iActionSetHorizontalKeystone;
    private Action iActionGetVerticalKeystone;
    private Action iActionSetVerticalKeystone;
    private Action iActionGetMute;
    private Action iActionSetMute;
    private Action iActionGetVolume;
    private Action iActionSetVolume;
    private Action iActionGetVolumeDB;
    private Action iActionSetVolumeDB;
    private Action iActionGetVolumeDBRange;
    private Action iActionGetLoudness;
    private Action iActionSetLoudness;
    private PropertyString iLastChange;
    private IPropertyChangeListener iLastChangeChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyUpnpOrgRenderingControl1(CpDevice aDevice)
    {
        super("schemas-upnp-org", "RenderingControl", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionListPresets = new Action("ListPresets");
        param = new ParameterUint("InstanceID");
        iActionListPresets.addInputParameter(param);
        param = new ParameterString("CurrentPresetNameList", allowedValues);
        iActionListPresets.addOutputParameter(param);

        iActionSelectPreset = new Action("SelectPreset");
        param = new ParameterUint("InstanceID");
        iActionSelectPreset.addInputParameter(param);
        param = new ParameterString("PresetName", allowedValues);
        iActionSelectPreset.addInputParameter(param);

        iActionGetBrightness = new Action("GetBrightness");
        param = new ParameterUint("InstanceID");
        iActionGetBrightness.addInputParameter(param);
        param = new ParameterUint("CurrentBrightness", 0, 2147483647, 1);
        iActionGetBrightness.addOutputParameter(param);

        iActionSetBrightness = new Action("SetBrightness");
        param = new ParameterUint("InstanceID");
        iActionSetBrightness.addInputParameter(param);
        param = new ParameterUint("DesiredBrightness", 0, 2147483647, 1);
        iActionSetBrightness.addInputParameter(param);

        iActionGetContrast = new Action("GetContrast");
        param = new ParameterUint("InstanceID");
        iActionGetContrast.addInputParameter(param);
        param = new ParameterUint("CurrentContrast", 0, 2147483647, 1);
        iActionGetContrast.addOutputParameter(param);

        iActionSetContrast = new Action("SetContrast");
        param = new ParameterUint("InstanceID");
        iActionSetContrast.addInputParameter(param);
        param = new ParameterUint("DesiredContrast", 0, 2147483647, 1);
        iActionSetContrast.addInputParameter(param);

        iActionGetSharpness = new Action("GetSharpness");
        param = new ParameterUint("InstanceID");
        iActionGetSharpness.addInputParameter(param);
        param = new ParameterUint("CurrentSharpness", 0, 2147483647, 1);
        iActionGetSharpness.addOutputParameter(param);

        iActionSetSharpness = new Action("SetSharpness");
        param = new ParameterUint("InstanceID");
        iActionSetSharpness.addInputParameter(param);
        param = new ParameterUint("DesiredSharpness", 0, 2147483647, 1);
        iActionSetSharpness.addInputParameter(param);

        iActionGetRedVideoGain = new Action("GetRedVideoGain");
        param = new ParameterUint("InstanceID");
        iActionGetRedVideoGain.addInputParameter(param);
        param = new ParameterUint("CurrentRedVideoGain", 0, 2147483647, 1);
        iActionGetRedVideoGain.addOutputParameter(param);

        iActionSetRedVideoGain = new Action("SetRedVideoGain");
        param = new ParameterUint("InstanceID");
        iActionSetRedVideoGain.addInputParameter(param);
        param = new ParameterUint("DesiredRedVideoGain", 0, 2147483647, 1);
        iActionSetRedVideoGain.addInputParameter(param);

        iActionGetGreenVideoGain = new Action("GetGreenVideoGain");
        param = new ParameterUint("InstanceID");
        iActionGetGreenVideoGain.addInputParameter(param);
        param = new ParameterUint("CurrentGreenVideoGain", 0, 2147483647, 1);
        iActionGetGreenVideoGain.addOutputParameter(param);

        iActionSetGreenVideoGain = new Action("SetGreenVideoGain");
        param = new ParameterUint("InstanceID");
        iActionSetGreenVideoGain.addInputParameter(param);
        param = new ParameterUint("DesiredGreenVideoGain", 0, 2147483647, 1);
        iActionSetGreenVideoGain.addInputParameter(param);

        iActionGetBlueVideoGain = new Action("GetBlueVideoGain");
        param = new ParameterUint("InstanceID");
        iActionGetBlueVideoGain.addInputParameter(param);
        param = new ParameterUint("CurrentBlueVideoGain", 0, 2147483647, 1);
        iActionGetBlueVideoGain.addOutputParameter(param);

        iActionSetBlueVideoGain = new Action("SetBlueVideoGain");
        param = new ParameterUint("InstanceID");
        iActionSetBlueVideoGain.addInputParameter(param);
        param = new ParameterUint("DesiredBlueVideoGain", 0, 2147483647, 1);
        iActionSetBlueVideoGain.addInputParameter(param);

        iActionGetRedVideoBlackLevel = new Action("GetRedVideoBlackLevel");
        param = new ParameterUint("InstanceID");
        iActionGetRedVideoBlackLevel.addInputParameter(param);
        param = new ParameterUint("CurrentRedVideoBlackLevel", 0, 2147483647, 1);
        iActionGetRedVideoBlackLevel.addOutputParameter(param);

        iActionSetRedVideoBlackLevel = new Action("SetRedVideoBlackLevel");
        param = new ParameterUint("InstanceID");
        iActionSetRedVideoBlackLevel.addInputParameter(param);
        param = new ParameterUint("DesiredRedVideoBlackLevel", 0, 2147483647, 1);
        iActionSetRedVideoBlackLevel.addInputParameter(param);

        iActionGetGreenVideoBlackLevel = new Action("GetGreenVideoBlackLevel");
        param = new ParameterUint("InstanceID");
        iActionGetGreenVideoBlackLevel.addInputParameter(param);
        param = new ParameterUint("CurrentGreenVideoBlackLevel", 0, 2147483647, 1);
        iActionGetGreenVideoBlackLevel.addOutputParameter(param);

        iActionSetGreenVideoBlackLevel = new Action("SetGreenVideoBlackLevel");
        param = new ParameterUint("InstanceID");
        iActionSetGreenVideoBlackLevel.addInputParameter(param);
        param = new ParameterUint("DesiredGreenVideoBlackLevel", 0, 2147483647, 1);
        iActionSetGreenVideoBlackLevel.addInputParameter(param);

        iActionGetBlueVideoBlackLevel = new Action("GetBlueVideoBlackLevel");
        param = new ParameterUint("InstanceID");
        iActionGetBlueVideoBlackLevel.addInputParameter(param);
        param = new ParameterUint("CurrentBlueVideoBlackLevel", 0, 2147483647, 1);
        iActionGetBlueVideoBlackLevel.addOutputParameter(param);

        iActionSetBlueVideoBlackLevel = new Action("SetBlueVideoBlackLevel");
        param = new ParameterUint("InstanceID");
        iActionSetBlueVideoBlackLevel.addInputParameter(param);
        param = new ParameterUint("DesiredBlueVideoBlackLevel", 0, 2147483647, 1);
        iActionSetBlueVideoBlackLevel.addInputParameter(param);

        iActionGetColorTemperature = new Action("GetColorTemperature");
        param = new ParameterUint("InstanceID");
        iActionGetColorTemperature.addInputParameter(param);
        param = new ParameterUint("CurrentColorTemperature", 0, 2147483647, 1);
        iActionGetColorTemperature.addOutputParameter(param);

        iActionSetColorTemperature = new Action("SetColorTemperature");
        param = new ParameterUint("InstanceID");
        iActionSetColorTemperature.addInputParameter(param);
        param = new ParameterUint("DesiredColorTemperature", 0, 2147483647, 1);
        iActionSetColorTemperature.addInputParameter(param);

        iActionGetHorizontalKeystone = new Action("GetHorizontalKeystone");
        param = new ParameterUint("InstanceID");
        iActionGetHorizontalKeystone.addInputParameter(param);
        param = new ParameterInt("CurrentHorizontalKeystone");
        iActionGetHorizontalKeystone.addOutputParameter(param);

        iActionSetHorizontalKeystone = new Action("SetHorizontalKeystone");
        param = new ParameterUint("InstanceID");
        iActionSetHorizontalKeystone.addInputParameter(param);
        param = new ParameterInt("DesiredHorizontalKeystone");
        iActionSetHorizontalKeystone.addInputParameter(param);

        iActionGetVerticalKeystone = new Action("GetVerticalKeystone");
        param = new ParameterUint("InstanceID");
        iActionGetVerticalKeystone.addInputParameter(param);
        param = new ParameterInt("CurrentVerticalKeystone");
        iActionGetVerticalKeystone.addOutputParameter(param);

        iActionSetVerticalKeystone = new Action("SetVerticalKeystone");
        param = new ParameterUint("InstanceID");
        iActionSetVerticalKeystone.addInputParameter(param);
        param = new ParameterInt("DesiredVerticalKeystone");
        iActionSetVerticalKeystone.addInputParameter(param);

        iActionGetMute = new Action("GetMute");
        param = new ParameterUint("InstanceID");
        iActionGetMute.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionGetMute.addInputParameter(param);
        param = new ParameterBool("CurrentMute");
        iActionGetMute.addOutputParameter(param);

        iActionSetMute = new Action("SetMute");
        param = new ParameterUint("InstanceID");
        iActionSetMute.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionSetMute.addInputParameter(param);
        param = new ParameterBool("DesiredMute");
        iActionSetMute.addInputParameter(param);

        iActionGetVolume = new Action("GetVolume");
        param = new ParameterUint("InstanceID");
        iActionGetVolume.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionGetVolume.addInputParameter(param);
        param = new ParameterUint("CurrentVolume", 0, 2147483647, 1);
        iActionGetVolume.addOutputParameter(param);

        iActionSetVolume = new Action("SetVolume");
        param = new ParameterUint("InstanceID");
        iActionSetVolume.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionSetVolume.addInputParameter(param);
        param = new ParameterUint("DesiredVolume", 0, 2147483647, 1);
        iActionSetVolume.addInputParameter(param);

        iActionGetVolumeDB = new Action("GetVolumeDB");
        param = new ParameterUint("InstanceID");
        iActionGetVolumeDB.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionGetVolumeDB.addInputParameter(param);
        param = new ParameterInt("CurrentVolume");
        iActionGetVolumeDB.addOutputParameter(param);

        iActionSetVolumeDB = new Action("SetVolumeDB");
        param = new ParameterUint("InstanceID");
        iActionSetVolumeDB.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionSetVolumeDB.addInputParameter(param);
        param = new ParameterInt("DesiredVolume");
        iActionSetVolumeDB.addInputParameter(param);

        iActionGetVolumeDBRange = new Action("GetVolumeDBRange");
        param = new ParameterUint("InstanceID");
        iActionGetVolumeDBRange.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionGetVolumeDBRange.addInputParameter(param);
        param = new ParameterInt("MinValue");
        iActionGetVolumeDBRange.addOutputParameter(param);
        param = new ParameterInt("MaxValue");
        iActionGetVolumeDBRange.addOutputParameter(param);

        iActionGetLoudness = new Action("GetLoudness");
        param = new ParameterUint("InstanceID");
        iActionGetLoudness.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionGetLoudness.addInputParameter(param);
        param = new ParameterBool("CurrentLoudness");
        iActionGetLoudness.addOutputParameter(param);

        iActionSetLoudness = new Action("SetLoudness");
        param = new ParameterUint("InstanceID");
        iActionSetLoudness.addInputParameter(param);
        param = new ParameterString("Channel", allowedValues);
        iActionSetLoudness.addInputParameter(param);
        param = new ParameterBool("DesiredLoudness");
        iActionSetLoudness.addInputParameter(param);

        iLastChangeChanged = new PropertyChangeListener();
        iLastChange = new PropertyString("LastChange",
            new PropertyChangeListener() {
                public void notifyChange() {
                    lastChangePropertyChanged();
                }
            }
        );
        addProperty(iLastChange);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncListPresets(long aInstanceID)
    {
        SyncListPresetsUpnpOrgRenderingControl1 sync = new SyncListPresetsUpnpOrgRenderingControl1(this);
        beginListPresets(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentPresetNameList();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endListPresets}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginListPresets(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionListPresets, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionListPresets.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionListPresets.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginListPresets} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginListPresets} method.
     * @return the result of the previously invoked action.
     */
    public String endListPresets(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String currentPresetNameList = Invocation.getOutputString(aAsyncHandle, index++);
        return currentPresetNameList;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSelectPreset(long aInstanceID, String aPresetName)
    {
        SyncSelectPresetUpnpOrgRenderingControl1 sync = new SyncSelectPresetUpnpOrgRenderingControl1(this);
        beginSelectPreset(aInstanceID, aPresetName, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSelectPreset}.
     * 
     * @param aInstanceID
     * @param aPresetName
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSelectPreset(long aInstanceID, String aPresetName, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSelectPreset, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSelectPreset.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSelectPreset.getInputParameter(inIndex++), aPresetName));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSelectPreset} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSelectPreset} method.
     */
    public void endSelectPreset(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetBrightness(long aInstanceID)
    {
        SyncGetBrightnessUpnpOrgRenderingControl1 sync = new SyncGetBrightnessUpnpOrgRenderingControl1(this);
        beginGetBrightness(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentBrightness();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetBrightness}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetBrightness(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetBrightness, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetBrightness.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetBrightness.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetBrightness} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetBrightness} method.
     * @return the result of the previously invoked action.
     */
    public long endGetBrightness(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentBrightness = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentBrightness;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetBrightness(long aInstanceID, long aDesiredBrightness)
    {
        SyncSetBrightnessUpnpOrgRenderingControl1 sync = new SyncSetBrightnessUpnpOrgRenderingControl1(this);
        beginSetBrightness(aInstanceID, aDesiredBrightness, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetBrightness}.
     * 
     * @param aInstanceID
     * @param aDesiredBrightness
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetBrightness(long aInstanceID, long aDesiredBrightness, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetBrightness, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetBrightness.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetBrightness.getInputParameter(inIndex++), aDesiredBrightness));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetBrightness} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetBrightness} method.
     */
    public void endSetBrightness(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetContrast(long aInstanceID)
    {
        SyncGetContrastUpnpOrgRenderingControl1 sync = new SyncGetContrastUpnpOrgRenderingControl1(this);
        beginGetContrast(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentContrast();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetContrast}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetContrast(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetContrast, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetContrast.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetContrast.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetContrast} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetContrast} method.
     * @return the result of the previously invoked action.
     */
    public long endGetContrast(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentContrast = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentContrast;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetContrast(long aInstanceID, long aDesiredContrast)
    {
        SyncSetContrastUpnpOrgRenderingControl1 sync = new SyncSetContrastUpnpOrgRenderingControl1(this);
        beginSetContrast(aInstanceID, aDesiredContrast, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetContrast}.
     * 
     * @param aInstanceID
     * @param aDesiredContrast
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetContrast(long aInstanceID, long aDesiredContrast, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetContrast, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetContrast.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetContrast.getInputParameter(inIndex++), aDesiredContrast));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetContrast} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetContrast} method.
     */
    public void endSetContrast(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetSharpness(long aInstanceID)
    {
        SyncGetSharpnessUpnpOrgRenderingControl1 sync = new SyncGetSharpnessUpnpOrgRenderingControl1(this);
        beginGetSharpness(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentSharpness();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetSharpness}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetSharpness(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetSharpness, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetSharpness.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetSharpness.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetSharpness} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetSharpness} method.
     * @return the result of the previously invoked action.
     */
    public long endGetSharpness(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentSharpness = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentSharpness;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetSharpness(long aInstanceID, long aDesiredSharpness)
    {
        SyncSetSharpnessUpnpOrgRenderingControl1 sync = new SyncSetSharpnessUpnpOrgRenderingControl1(this);
        beginSetSharpness(aInstanceID, aDesiredSharpness, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetSharpness}.
     * 
     * @param aInstanceID
     * @param aDesiredSharpness
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetSharpness(long aInstanceID, long aDesiredSharpness, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetSharpness, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetSharpness.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetSharpness.getInputParameter(inIndex++), aDesiredSharpness));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetSharpness} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetSharpness} method.
     */
    public void endSetSharpness(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetRedVideoGain(long aInstanceID)
    {
        SyncGetRedVideoGainUpnpOrgRenderingControl1 sync = new SyncGetRedVideoGainUpnpOrgRenderingControl1(this);
        beginGetRedVideoGain(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentRedVideoGain();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRedVideoGain}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRedVideoGain(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRedVideoGain, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetRedVideoGain.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetRedVideoGain.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRedVideoGain} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRedVideoGain} method.
     * @return the result of the previously invoked action.
     */
    public long endGetRedVideoGain(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentRedVideoGain = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentRedVideoGain;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetRedVideoGain(long aInstanceID, long aDesiredRedVideoGain)
    {
        SyncSetRedVideoGainUpnpOrgRenderingControl1 sync = new SyncSetRedVideoGainUpnpOrgRenderingControl1(this);
        beginSetRedVideoGain(aInstanceID, aDesiredRedVideoGain, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetRedVideoGain}.
     * 
     * @param aInstanceID
     * @param aDesiredRedVideoGain
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetRedVideoGain(long aInstanceID, long aDesiredRedVideoGain, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetRedVideoGain, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetRedVideoGain.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetRedVideoGain.getInputParameter(inIndex++), aDesiredRedVideoGain));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetRedVideoGain} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetRedVideoGain} method.
     */
    public void endSetRedVideoGain(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetGreenVideoGain(long aInstanceID)
    {
        SyncGetGreenVideoGainUpnpOrgRenderingControl1 sync = new SyncGetGreenVideoGainUpnpOrgRenderingControl1(this);
        beginGetGreenVideoGain(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentGreenVideoGain();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetGreenVideoGain}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetGreenVideoGain(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetGreenVideoGain, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetGreenVideoGain.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetGreenVideoGain.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetGreenVideoGain} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetGreenVideoGain} method.
     * @return the result of the previously invoked action.
     */
    public long endGetGreenVideoGain(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentGreenVideoGain = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentGreenVideoGain;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetGreenVideoGain(long aInstanceID, long aDesiredGreenVideoGain)
    {
        SyncSetGreenVideoGainUpnpOrgRenderingControl1 sync = new SyncSetGreenVideoGainUpnpOrgRenderingControl1(this);
        beginSetGreenVideoGain(aInstanceID, aDesiredGreenVideoGain, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetGreenVideoGain}.
     * 
     * @param aInstanceID
     * @param aDesiredGreenVideoGain
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetGreenVideoGain(long aInstanceID, long aDesiredGreenVideoGain, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetGreenVideoGain, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetGreenVideoGain.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetGreenVideoGain.getInputParameter(inIndex++), aDesiredGreenVideoGain));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetGreenVideoGain} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetGreenVideoGain} method.
     */
    public void endSetGreenVideoGain(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetBlueVideoGain(long aInstanceID)
    {
        SyncGetBlueVideoGainUpnpOrgRenderingControl1 sync = new SyncGetBlueVideoGainUpnpOrgRenderingControl1(this);
        beginGetBlueVideoGain(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentBlueVideoGain();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetBlueVideoGain}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetBlueVideoGain(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetBlueVideoGain, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetBlueVideoGain.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetBlueVideoGain.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetBlueVideoGain} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetBlueVideoGain} method.
     * @return the result of the previously invoked action.
     */
    public long endGetBlueVideoGain(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentBlueVideoGain = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentBlueVideoGain;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetBlueVideoGain(long aInstanceID, long aDesiredBlueVideoGain)
    {
        SyncSetBlueVideoGainUpnpOrgRenderingControl1 sync = new SyncSetBlueVideoGainUpnpOrgRenderingControl1(this);
        beginSetBlueVideoGain(aInstanceID, aDesiredBlueVideoGain, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetBlueVideoGain}.
     * 
     * @param aInstanceID
     * @param aDesiredBlueVideoGain
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetBlueVideoGain(long aInstanceID, long aDesiredBlueVideoGain, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetBlueVideoGain, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetBlueVideoGain.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetBlueVideoGain.getInputParameter(inIndex++), aDesiredBlueVideoGain));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetBlueVideoGain} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetBlueVideoGain} method.
     */
    public void endSetBlueVideoGain(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetRedVideoBlackLevel(long aInstanceID)
    {
        SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1 sync = new SyncGetRedVideoBlackLevelUpnpOrgRenderingControl1(this);
        beginGetRedVideoBlackLevel(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentRedVideoBlackLevel();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRedVideoBlackLevel}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRedVideoBlackLevel(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRedVideoBlackLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetRedVideoBlackLevel.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetRedVideoBlackLevel.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRedVideoBlackLevel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRedVideoBlackLevel} method.
     * @return the result of the previously invoked action.
     */
    public long endGetRedVideoBlackLevel(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentRedVideoBlackLevel = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentRedVideoBlackLevel;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetRedVideoBlackLevel(long aInstanceID, long aDesiredRedVideoBlackLevel)
    {
        SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1 sync = new SyncSetRedVideoBlackLevelUpnpOrgRenderingControl1(this);
        beginSetRedVideoBlackLevel(aInstanceID, aDesiredRedVideoBlackLevel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetRedVideoBlackLevel}.
     * 
     * @param aInstanceID
     * @param aDesiredRedVideoBlackLevel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetRedVideoBlackLevel(long aInstanceID, long aDesiredRedVideoBlackLevel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetRedVideoBlackLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetRedVideoBlackLevel.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetRedVideoBlackLevel.getInputParameter(inIndex++), aDesiredRedVideoBlackLevel));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetRedVideoBlackLevel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetRedVideoBlackLevel} method.
     */
    public void endSetRedVideoBlackLevel(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetGreenVideoBlackLevel(long aInstanceID)
    {
        SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1 sync = new SyncGetGreenVideoBlackLevelUpnpOrgRenderingControl1(this);
        beginGetGreenVideoBlackLevel(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentGreenVideoBlackLevel();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetGreenVideoBlackLevel}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetGreenVideoBlackLevel(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetGreenVideoBlackLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetGreenVideoBlackLevel.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetGreenVideoBlackLevel.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetGreenVideoBlackLevel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetGreenVideoBlackLevel} method.
     * @return the result of the previously invoked action.
     */
    public long endGetGreenVideoBlackLevel(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentGreenVideoBlackLevel = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentGreenVideoBlackLevel;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetGreenVideoBlackLevel(long aInstanceID, long aDesiredGreenVideoBlackLevel)
    {
        SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1 sync = new SyncSetGreenVideoBlackLevelUpnpOrgRenderingControl1(this);
        beginSetGreenVideoBlackLevel(aInstanceID, aDesiredGreenVideoBlackLevel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetGreenVideoBlackLevel}.
     * 
     * @param aInstanceID
     * @param aDesiredGreenVideoBlackLevel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetGreenVideoBlackLevel(long aInstanceID, long aDesiredGreenVideoBlackLevel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetGreenVideoBlackLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetGreenVideoBlackLevel.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetGreenVideoBlackLevel.getInputParameter(inIndex++), aDesiredGreenVideoBlackLevel));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetGreenVideoBlackLevel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetGreenVideoBlackLevel} method.
     */
    public void endSetGreenVideoBlackLevel(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetBlueVideoBlackLevel(long aInstanceID)
    {
        SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1 sync = new SyncGetBlueVideoBlackLevelUpnpOrgRenderingControl1(this);
        beginGetBlueVideoBlackLevel(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentBlueVideoBlackLevel();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetBlueVideoBlackLevel}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetBlueVideoBlackLevel(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetBlueVideoBlackLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetBlueVideoBlackLevel.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetBlueVideoBlackLevel.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetBlueVideoBlackLevel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetBlueVideoBlackLevel} method.
     * @return the result of the previously invoked action.
     */
    public long endGetBlueVideoBlackLevel(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentBlueVideoBlackLevel = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentBlueVideoBlackLevel;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetBlueVideoBlackLevel(long aInstanceID, long aDesiredBlueVideoBlackLevel)
    {
        SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1 sync = new SyncSetBlueVideoBlackLevelUpnpOrgRenderingControl1(this);
        beginSetBlueVideoBlackLevel(aInstanceID, aDesiredBlueVideoBlackLevel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetBlueVideoBlackLevel}.
     * 
     * @param aInstanceID
     * @param aDesiredBlueVideoBlackLevel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetBlueVideoBlackLevel(long aInstanceID, long aDesiredBlueVideoBlackLevel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetBlueVideoBlackLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetBlueVideoBlackLevel.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetBlueVideoBlackLevel.getInputParameter(inIndex++), aDesiredBlueVideoBlackLevel));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetBlueVideoBlackLevel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetBlueVideoBlackLevel} method.
     */
    public void endSetBlueVideoBlackLevel(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetColorTemperature(long aInstanceID)
    {
        SyncGetColorTemperatureUpnpOrgRenderingControl1 sync = new SyncGetColorTemperatureUpnpOrgRenderingControl1(this);
        beginGetColorTemperature(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentColorTemperature();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetColorTemperature}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetColorTemperature(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetColorTemperature, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetColorTemperature.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetColorTemperature.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetColorTemperature} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetColorTemperature} method.
     * @return the result of the previously invoked action.
     */
    public long endGetColorTemperature(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentColorTemperature = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentColorTemperature;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetColorTemperature(long aInstanceID, long aDesiredColorTemperature)
    {
        SyncSetColorTemperatureUpnpOrgRenderingControl1 sync = new SyncSetColorTemperatureUpnpOrgRenderingControl1(this);
        beginSetColorTemperature(aInstanceID, aDesiredColorTemperature, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetColorTemperature}.
     * 
     * @param aInstanceID
     * @param aDesiredColorTemperature
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetColorTemperature(long aInstanceID, long aDesiredColorTemperature, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetColorTemperature, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetColorTemperature.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetColorTemperature.getInputParameter(inIndex++), aDesiredColorTemperature));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetColorTemperature} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetColorTemperature} method.
     */
    public void endSetColorTemperature(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public int syncGetHorizontalKeystone(long aInstanceID)
    {
        SyncGetHorizontalKeystoneUpnpOrgRenderingControl1 sync = new SyncGetHorizontalKeystoneUpnpOrgRenderingControl1(this);
        beginGetHorizontalKeystone(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentHorizontalKeystone();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetHorizontalKeystone}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetHorizontalKeystone(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetHorizontalKeystone, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetHorizontalKeystone.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetHorizontalKeystone.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetHorizontalKeystone} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetHorizontalKeystone} method.
     * @return the result of the previously invoked action.
     */
    public int endGetHorizontalKeystone(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        int currentHorizontalKeystone = Invocation.getOutputInt(aAsyncHandle, index++);
        return currentHorizontalKeystone;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetHorizontalKeystone(long aInstanceID, int aDesiredHorizontalKeystone)
    {
        SyncSetHorizontalKeystoneUpnpOrgRenderingControl1 sync = new SyncSetHorizontalKeystoneUpnpOrgRenderingControl1(this);
        beginSetHorizontalKeystone(aInstanceID, aDesiredHorizontalKeystone, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetHorizontalKeystone}.
     * 
     * @param aInstanceID
     * @param aDesiredHorizontalKeystone
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetHorizontalKeystone(long aInstanceID, int aDesiredHorizontalKeystone, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetHorizontalKeystone, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetHorizontalKeystone.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentInt((ParameterInt)iActionSetHorizontalKeystone.getInputParameter(inIndex++), aDesiredHorizontalKeystone));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetHorizontalKeystone} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetHorizontalKeystone} method.
     */
    public void endSetHorizontalKeystone(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public int syncGetVerticalKeystone(long aInstanceID)
    {
        SyncGetVerticalKeystoneUpnpOrgRenderingControl1 sync = new SyncGetVerticalKeystoneUpnpOrgRenderingControl1(this);
        beginGetVerticalKeystone(aInstanceID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentVerticalKeystone();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetVerticalKeystone}.
     * 
     * @param aInstanceID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetVerticalKeystone(long aInstanceID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetVerticalKeystone, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetVerticalKeystone.getInputParameter(inIndex++), aInstanceID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetVerticalKeystone.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetVerticalKeystone} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetVerticalKeystone} method.
     * @return the result of the previously invoked action.
     */
    public int endGetVerticalKeystone(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        int currentVerticalKeystone = Invocation.getOutputInt(aAsyncHandle, index++);
        return currentVerticalKeystone;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetVerticalKeystone(long aInstanceID, int aDesiredVerticalKeystone)
    {
        SyncSetVerticalKeystoneUpnpOrgRenderingControl1 sync = new SyncSetVerticalKeystoneUpnpOrgRenderingControl1(this);
        beginSetVerticalKeystone(aInstanceID, aDesiredVerticalKeystone, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetVerticalKeystone}.
     * 
     * @param aInstanceID
     * @param aDesiredVerticalKeystone
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetVerticalKeystone(long aInstanceID, int aDesiredVerticalKeystone, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetVerticalKeystone, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetVerticalKeystone.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentInt((ParameterInt)iActionSetVerticalKeystone.getInputParameter(inIndex++), aDesiredVerticalKeystone));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetVerticalKeystone} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetVerticalKeystone} method.
     */
    public void endSetVerticalKeystone(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public boolean syncGetMute(long aInstanceID, String aChannel)
    {
        SyncGetMuteUpnpOrgRenderingControl1 sync = new SyncGetMuteUpnpOrgRenderingControl1(this);
        beginGetMute(aInstanceID, aChannel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentMute();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetMute}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetMute(long aInstanceID, String aChannel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetMute, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetMute.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionGetMute.getInputParameter(inIndex++), aChannel));
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionGetMute.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetMute} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetMute} method.
     * @return the result of the previously invoked action.
     */
    public boolean endGetMute(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        boolean currentMute = Invocation.getOutputBool(aAsyncHandle, index++);
        return currentMute;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetMute(long aInstanceID, String aChannel, boolean aDesiredMute)
    {
        SyncSetMuteUpnpOrgRenderingControl1 sync = new SyncSetMuteUpnpOrgRenderingControl1(this);
        beginSetMute(aInstanceID, aChannel, aDesiredMute, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetMute}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aDesiredMute
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetMute(long aInstanceID, String aChannel, boolean aDesiredMute, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetMute, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetMute.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetMute.getInputParameter(inIndex++), aChannel));
        invocation.addInput(new ArgumentBool((ParameterBool)iActionSetMute.getInputParameter(inIndex++), aDesiredMute));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetMute} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetMute} method.
     */
    public void endSetMute(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetVolume(long aInstanceID, String aChannel)
    {
        SyncGetVolumeUpnpOrgRenderingControl1 sync = new SyncGetVolumeUpnpOrgRenderingControl1(this);
        beginGetVolume(aInstanceID, aChannel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentVolume();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetVolume}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetVolume(long aInstanceID, String aChannel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetVolume, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetVolume.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionGetVolume.getInputParameter(inIndex++), aChannel));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetVolume.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetVolume} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetVolume} method.
     * @return the result of the previously invoked action.
     */
    public long endGetVolume(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long currentVolume = Invocation.getOutputUint(aAsyncHandle, index++);
        return currentVolume;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetVolume(long aInstanceID, String aChannel, long aDesiredVolume)
    {
        SyncSetVolumeUpnpOrgRenderingControl1 sync = new SyncSetVolumeUpnpOrgRenderingControl1(this);
        beginSetVolume(aInstanceID, aChannel, aDesiredVolume, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetVolume}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aDesiredVolume
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetVolume(long aInstanceID, String aChannel, long aDesiredVolume, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetVolume, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetVolume.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetVolume.getInputParameter(inIndex++), aChannel));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetVolume.getInputParameter(inIndex++), aDesiredVolume));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetVolume} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetVolume} method.
     */
    public void endSetVolume(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public int syncGetVolumeDB(long aInstanceID, String aChannel)
    {
        SyncGetVolumeDBUpnpOrgRenderingControl1 sync = new SyncGetVolumeDBUpnpOrgRenderingControl1(this);
        beginGetVolumeDB(aInstanceID, aChannel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentVolume();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetVolumeDB}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetVolumeDB(long aInstanceID, String aChannel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetVolumeDB, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetVolumeDB.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionGetVolumeDB.getInputParameter(inIndex++), aChannel));
        int outIndex = 0;
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetVolumeDB.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetVolumeDB} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetVolumeDB} method.
     * @return the result of the previously invoked action.
     */
    public int endGetVolumeDB(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        int currentVolume = Invocation.getOutputInt(aAsyncHandle, index++);
        return currentVolume;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetVolumeDB(long aInstanceID, String aChannel, int aDesiredVolume)
    {
        SyncSetVolumeDBUpnpOrgRenderingControl1 sync = new SyncSetVolumeDBUpnpOrgRenderingControl1(this);
        beginSetVolumeDB(aInstanceID, aChannel, aDesiredVolume, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetVolumeDB}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aDesiredVolume
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetVolumeDB(long aInstanceID, String aChannel, int aDesiredVolume, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetVolumeDB, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetVolumeDB.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetVolumeDB.getInputParameter(inIndex++), aChannel));
        invocation.addInput(new ArgumentInt((ParameterInt)iActionSetVolumeDB.getInputParameter(inIndex++), aDesiredVolume));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetVolumeDB} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetVolumeDB} method.
     */
    public void endSetVolumeDB(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetVolumeDBRange syncGetVolumeDBRange(long aInstanceID, String aChannel)
    {
        SyncGetVolumeDBRangeUpnpOrgRenderingControl1 sync = new SyncGetVolumeDBRangeUpnpOrgRenderingControl1(this);
        beginGetVolumeDBRange(aInstanceID, aChannel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetVolumeDBRange(
            sync.getMinValue(),
            sync.getMaxValue()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetVolumeDBRange}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetVolumeDBRange(long aInstanceID, String aChannel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetVolumeDBRange, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetVolumeDBRange.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionGetVolumeDBRange.getInputParameter(inIndex++), aChannel));
        int outIndex = 0;
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetVolumeDBRange.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetVolumeDBRange.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetVolumeDBRange} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetVolumeDBRange} method.
     * @return the result of the previously invoked action.
     */
    public GetVolumeDBRange endGetVolumeDBRange(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        int minValue = Invocation.getOutputInt(aAsyncHandle, index++);
        int maxValue = Invocation.getOutputInt(aAsyncHandle, index++);
        return new GetVolumeDBRange(
            minValue,
            maxValue
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public boolean syncGetLoudness(long aInstanceID, String aChannel)
    {
        SyncGetLoudnessUpnpOrgRenderingControl1 sync = new SyncGetLoudnessUpnpOrgRenderingControl1(this);
        beginGetLoudness(aInstanceID, aChannel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCurrentLoudness();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetLoudness}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetLoudness(long aInstanceID, String aChannel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetLoudness, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetLoudness.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionGetLoudness.getInputParameter(inIndex++), aChannel));
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionGetLoudness.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetLoudness} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetLoudness} method.
     * @return the result of the previously invoked action.
     */
    public boolean endGetLoudness(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        boolean currentLoudness = Invocation.getOutputBool(aAsyncHandle, index++);
        return currentLoudness;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetLoudness(long aInstanceID, String aChannel, boolean aDesiredLoudness)
    {
        SyncSetLoudnessUpnpOrgRenderingControl1 sync = new SyncSetLoudnessUpnpOrgRenderingControl1(this);
        beginSetLoudness(aInstanceID, aChannel, aDesiredLoudness, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetLoudness}.
     * 
     * @param aInstanceID
     * @param aChannel
     * @param aDesiredLoudness
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetLoudness(long aInstanceID, String aChannel, boolean aDesiredLoudness, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetLoudness, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetLoudness.getInputParameter(inIndex++), aInstanceID));
        invocation.addInput(new ArgumentString((ParameterString)iActionSetLoudness.getInputParameter(inIndex++), aChannel));
        invocation.addInput(new ArgumentBool((ParameterBool)iActionSetLoudness.getInputParameter(inIndex++), aDesiredLoudness));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetLoudness} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetLoudness} method.
     */
    public void endSetLoudness(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Set a delegate to be run when the LastChange state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgRenderingControl1 instance will not overlap.
     *
     * @param aLastChangeChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyLastChangeChanged(IPropertyChangeListener aLastChangeChanged)
    {
        synchronized (iPropertyLock)
        {
            iLastChangeChanged = aLastChangeChanged;
        }
    }

    private void lastChangePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iLastChangeChanged);
        }
    }

    /**
     * Query the value of the LastChange property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the LastChange property.
     */
    public String getPropertyLastChange()
    {
        propertyReadLock();
        String val = iLastChange.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Dispose of this control point proxy.
     * Must be called for each class instance.
     * Must be called before <tt>Library.close()</tt>.
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            disposeProxy();
            iHandle = 0;
            iActionListPresets.destroy();
            iActionSelectPreset.destroy();
            iActionGetBrightness.destroy();
            iActionSetBrightness.destroy();
            iActionGetContrast.destroy();
            iActionSetContrast.destroy();
            iActionGetSharpness.destroy();
            iActionSetSharpness.destroy();
            iActionGetRedVideoGain.destroy();
            iActionSetRedVideoGain.destroy();
            iActionGetGreenVideoGain.destroy();
            iActionSetGreenVideoGain.destroy();
            iActionGetBlueVideoGain.destroy();
            iActionSetBlueVideoGain.destroy();
            iActionGetRedVideoBlackLevel.destroy();
            iActionSetRedVideoBlackLevel.destroy();
            iActionGetGreenVideoBlackLevel.destroy();
            iActionSetGreenVideoBlackLevel.destroy();
            iActionGetBlueVideoBlackLevel.destroy();
            iActionSetBlueVideoBlackLevel.destroy();
            iActionGetColorTemperature.destroy();
            iActionSetColorTemperature.destroy();
            iActionGetHorizontalKeystone.destroy();
            iActionSetHorizontalKeystone.destroy();
            iActionGetVerticalKeystone.destroy();
            iActionSetVerticalKeystone.destroy();
            iActionGetMute.destroy();
            iActionSetMute.destroy();
            iActionGetVolume.destroy();
            iActionSetVolume.destroy();
            iActionGetVolumeDB.destroy();
            iActionSetVolumeDB.destroy();
            iActionGetVolumeDBRange.destroy();
            iActionGetLoudness.destroy();
            iActionSetLoudness.destroy();
            iLastChange.destroy();
        }
    }
}

