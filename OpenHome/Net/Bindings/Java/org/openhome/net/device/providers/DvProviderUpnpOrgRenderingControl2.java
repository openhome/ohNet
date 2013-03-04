package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderUpnpOrgRenderingControl2
{

    /**
     * Set the value of the LastChange property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyLastChange(String aValue);

    /**
     * Get a copy of the value of the LastChange property
     *
     * @return value of the LastChange property.
     */
    public String getPropertyLastChange();
        
}

/**
 * Provider for the upnp.org:RenderingControl:2 UPnP service.
 */
public class DvProviderUpnpOrgRenderingControl2 extends DvProvider implements IDvProviderUpnpOrgRenderingControl2
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

    private IDvInvocationListener iDelegateListPresets;
    private IDvInvocationListener iDelegateSelectPreset;
    private IDvInvocationListener iDelegateGetBrightness;
    private IDvInvocationListener iDelegateSetBrightness;
    private IDvInvocationListener iDelegateGetContrast;
    private IDvInvocationListener iDelegateSetContrast;
    private IDvInvocationListener iDelegateGetSharpness;
    private IDvInvocationListener iDelegateSetSharpness;
    private IDvInvocationListener iDelegateGetRedVideoGain;
    private IDvInvocationListener iDelegateSetRedVideoGain;
    private IDvInvocationListener iDelegateGetGreenVideoGain;
    private IDvInvocationListener iDelegateSetGreenVideoGain;
    private IDvInvocationListener iDelegateGetBlueVideoGain;
    private IDvInvocationListener iDelegateSetBlueVideoGain;
    private IDvInvocationListener iDelegateGetRedVideoBlackLevel;
    private IDvInvocationListener iDelegateSetRedVideoBlackLevel;
    private IDvInvocationListener iDelegateGetGreenVideoBlackLevel;
    private IDvInvocationListener iDelegateSetGreenVideoBlackLevel;
    private IDvInvocationListener iDelegateGetBlueVideoBlackLevel;
    private IDvInvocationListener iDelegateSetBlueVideoBlackLevel;
    private IDvInvocationListener iDelegateGetColorTemperature;
    private IDvInvocationListener iDelegateSetColorTemperature;
    private IDvInvocationListener iDelegateGetHorizontalKeystone;
    private IDvInvocationListener iDelegateSetHorizontalKeystone;
    private IDvInvocationListener iDelegateGetVerticalKeystone;
    private IDvInvocationListener iDelegateSetVerticalKeystone;
    private IDvInvocationListener iDelegateGetMute;
    private IDvInvocationListener iDelegateSetMute;
    private IDvInvocationListener iDelegateGetVolume;
    private IDvInvocationListener iDelegateSetVolume;
    private IDvInvocationListener iDelegateGetVolumeDB;
    private IDvInvocationListener iDelegateSetVolumeDB;
    private IDvInvocationListener iDelegateGetVolumeDBRange;
    private IDvInvocationListener iDelegateGetLoudness;
    private IDvInvocationListener iDelegateSetLoudness;
    private IDvInvocationListener iDelegateGetStateVariables;
    private IDvInvocationListener iDelegateSetStateVariables;
    private PropertyString iPropertyLastChange;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderUpnpOrgRenderingControl2(DvDevice aDevice)
    {
        super(aDevice, "upnp.org", "RenderingControl", 2);
    }

    /**
     * Enable the LastChange property.
     */
    public void enablePropertyLastChange()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyLastChange = new PropertyString(new ParameterString("LastChange", allowedValues));
        addProperty(iPropertyLastChange);
    }

    /**
     * Set the value of the LastChange property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyLastChange(String aValue)
    {
        return setPropertyString(iPropertyLastChange, aValue);
    }

    /**
     * Get a copy of the value of the LastChange property
     *
     * @return  value of the LastChange property.
     */
    public String getPropertyLastChange()
    {
        return iPropertyLastChange.getValue();
    }

    /**
     * Signal that the action ListPresets is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ListPresets must be overridden if this is called.
     */      
    protected void enableActionListPresets()
    {
        Action action = new Action("ListPresets");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterString("CurrentPresetNameList", allowedValues));
        iDelegateListPresets = new DoListPresets();
        enableAction(action, iDelegateListPresets);
    }

    /**
     * Signal that the action SelectPreset is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SelectPreset must be overridden if this is called.
     */      
    protected void enableActionSelectPreset()
    {
        Action action = new Action("SelectPreset");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("PresetName", allowedValues));
        iDelegateSelectPreset = new DoSelectPreset();
        enableAction(action, iDelegateSelectPreset);
    }

    /**
     * Signal that the action GetBrightness is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetBrightness must be overridden if this is called.
     */      
    protected void enableActionGetBrightness()
    {
        Action action = new Action("GetBrightness");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentBrightness", 0, 2147483647, 1));
        iDelegateGetBrightness = new DoGetBrightness();
        enableAction(action, iDelegateGetBrightness);
    }

    /**
     * Signal that the action SetBrightness is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetBrightness must be overridden if this is called.
     */      
    protected void enableActionSetBrightness()
    {
        Action action = new Action("SetBrightness");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredBrightness", 0, 2147483647, 1));
        iDelegateSetBrightness = new DoSetBrightness();
        enableAction(action, iDelegateSetBrightness);
    }

    /**
     * Signal that the action GetContrast is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetContrast must be overridden if this is called.
     */      
    protected void enableActionGetContrast()
    {
        Action action = new Action("GetContrast");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentContrast", 0, 2147483647, 1));
        iDelegateGetContrast = new DoGetContrast();
        enableAction(action, iDelegateGetContrast);
    }

    /**
     * Signal that the action SetContrast is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetContrast must be overridden if this is called.
     */      
    protected void enableActionSetContrast()
    {
        Action action = new Action("SetContrast");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredContrast", 0, 2147483647, 1));
        iDelegateSetContrast = new DoSetContrast();
        enableAction(action, iDelegateSetContrast);
    }

    /**
     * Signal that the action GetSharpness is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetSharpness must be overridden if this is called.
     */      
    protected void enableActionGetSharpness()
    {
        Action action = new Action("GetSharpness");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentSharpness", 0, 2147483647, 1));
        iDelegateGetSharpness = new DoGetSharpness();
        enableAction(action, iDelegateGetSharpness);
    }

    /**
     * Signal that the action SetSharpness is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetSharpness must be overridden if this is called.
     */      
    protected void enableActionSetSharpness()
    {
        Action action = new Action("SetSharpness");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredSharpness", 0, 2147483647, 1));
        iDelegateSetSharpness = new DoSetSharpness();
        enableAction(action, iDelegateSetSharpness);
    }

    /**
     * Signal that the action GetRedVideoGain is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRedVideoGain must be overridden if this is called.
     */      
    protected void enableActionGetRedVideoGain()
    {
        Action action = new Action("GetRedVideoGain");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentRedVideoGain", 0, 2147483647, 1));
        iDelegateGetRedVideoGain = new DoGetRedVideoGain();
        enableAction(action, iDelegateGetRedVideoGain);
    }

    /**
     * Signal that the action SetRedVideoGain is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetRedVideoGain must be overridden if this is called.
     */      
    protected void enableActionSetRedVideoGain()
    {
        Action action = new Action("SetRedVideoGain");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredRedVideoGain", 0, 2147483647, 1));
        iDelegateSetRedVideoGain = new DoSetRedVideoGain();
        enableAction(action, iDelegateSetRedVideoGain);
    }

    /**
     * Signal that the action GetGreenVideoGain is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetGreenVideoGain must be overridden if this is called.
     */      
    protected void enableActionGetGreenVideoGain()
    {
        Action action = new Action("GetGreenVideoGain");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentGreenVideoGain", 0, 2147483647, 1));
        iDelegateGetGreenVideoGain = new DoGetGreenVideoGain();
        enableAction(action, iDelegateGetGreenVideoGain);
    }

    /**
     * Signal that the action SetGreenVideoGain is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetGreenVideoGain must be overridden if this is called.
     */      
    protected void enableActionSetGreenVideoGain()
    {
        Action action = new Action("SetGreenVideoGain");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredGreenVideoGain", 0, 2147483647, 1));
        iDelegateSetGreenVideoGain = new DoSetGreenVideoGain();
        enableAction(action, iDelegateSetGreenVideoGain);
    }

    /**
     * Signal that the action GetBlueVideoGain is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetBlueVideoGain must be overridden if this is called.
     */      
    protected void enableActionGetBlueVideoGain()
    {
        Action action = new Action("GetBlueVideoGain");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentBlueVideoGain", 0, 2147483647, 1));
        iDelegateGetBlueVideoGain = new DoGetBlueVideoGain();
        enableAction(action, iDelegateGetBlueVideoGain);
    }

    /**
     * Signal that the action SetBlueVideoGain is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetBlueVideoGain must be overridden if this is called.
     */      
    protected void enableActionSetBlueVideoGain()
    {
        Action action = new Action("SetBlueVideoGain");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredBlueVideoGain", 0, 2147483647, 1));
        iDelegateSetBlueVideoGain = new DoSetBlueVideoGain();
        enableAction(action, iDelegateSetBlueVideoGain);
    }

    /**
     * Signal that the action GetRedVideoBlackLevel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRedVideoBlackLevel must be overridden if this is called.
     */      
    protected void enableActionGetRedVideoBlackLevel()
    {
        Action action = new Action("GetRedVideoBlackLevel");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentRedVideoBlackLevel", 0, 2147483647, 1));
        iDelegateGetRedVideoBlackLevel = new DoGetRedVideoBlackLevel();
        enableAction(action, iDelegateGetRedVideoBlackLevel);
    }

    /**
     * Signal that the action SetRedVideoBlackLevel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetRedVideoBlackLevel must be overridden if this is called.
     */      
    protected void enableActionSetRedVideoBlackLevel()
    {
        Action action = new Action("SetRedVideoBlackLevel");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredRedVideoBlackLevel", 0, 2147483647, 1));
        iDelegateSetRedVideoBlackLevel = new DoSetRedVideoBlackLevel();
        enableAction(action, iDelegateSetRedVideoBlackLevel);
    }

    /**
     * Signal that the action GetGreenVideoBlackLevel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetGreenVideoBlackLevel must be overridden if this is called.
     */      
    protected void enableActionGetGreenVideoBlackLevel()
    {
        Action action = new Action("GetGreenVideoBlackLevel");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentGreenVideoBlackLevel", 0, 2147483647, 1));
        iDelegateGetGreenVideoBlackLevel = new DoGetGreenVideoBlackLevel();
        enableAction(action, iDelegateGetGreenVideoBlackLevel);
    }

    /**
     * Signal that the action SetGreenVideoBlackLevel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetGreenVideoBlackLevel must be overridden if this is called.
     */      
    protected void enableActionSetGreenVideoBlackLevel()
    {
        Action action = new Action("SetGreenVideoBlackLevel");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredGreenVideoBlackLevel", 0, 2147483647, 1));
        iDelegateSetGreenVideoBlackLevel = new DoSetGreenVideoBlackLevel();
        enableAction(action, iDelegateSetGreenVideoBlackLevel);
    }

    /**
     * Signal that the action GetBlueVideoBlackLevel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetBlueVideoBlackLevel must be overridden if this is called.
     */      
    protected void enableActionGetBlueVideoBlackLevel()
    {
        Action action = new Action("GetBlueVideoBlackLevel");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentBlueVideoBlackLevel", 0, 2147483647, 1));
        iDelegateGetBlueVideoBlackLevel = new DoGetBlueVideoBlackLevel();
        enableAction(action, iDelegateGetBlueVideoBlackLevel);
    }

    /**
     * Signal that the action SetBlueVideoBlackLevel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetBlueVideoBlackLevel must be overridden if this is called.
     */      
    protected void enableActionSetBlueVideoBlackLevel()
    {
        Action action = new Action("SetBlueVideoBlackLevel");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredBlueVideoBlackLevel", 0, 2147483647, 1));
        iDelegateSetBlueVideoBlackLevel = new DoSetBlueVideoBlackLevel();
        enableAction(action, iDelegateSetBlueVideoBlackLevel);
    }

    /**
     * Signal that the action GetColorTemperature is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetColorTemperature must be overridden if this is called.
     */      
    protected void enableActionGetColorTemperature()
    {
        Action action = new Action("GetColorTemperature");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterUint("CurrentColorTemperature", 0, 2147483647, 1));
        iDelegateGetColorTemperature = new DoGetColorTemperature();
        enableAction(action, iDelegateGetColorTemperature);
    }

    /**
     * Signal that the action SetColorTemperature is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetColorTemperature must be overridden if this is called.
     */      
    protected void enableActionSetColorTemperature()
    {
        Action action = new Action("SetColorTemperature");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterUint("DesiredColorTemperature", 0, 2147483647, 1));
        iDelegateSetColorTemperature = new DoSetColorTemperature();
        enableAction(action, iDelegateSetColorTemperature);
    }

    /**
     * Signal that the action GetHorizontalKeystone is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetHorizontalKeystone must be overridden if this is called.
     */      
    protected void enableActionGetHorizontalKeystone()
    {
        Action action = new Action("GetHorizontalKeystone");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterInt("CurrentHorizontalKeystone"));
        iDelegateGetHorizontalKeystone = new DoGetHorizontalKeystone();
        enableAction(action, iDelegateGetHorizontalKeystone);
    }

    /**
     * Signal that the action SetHorizontalKeystone is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetHorizontalKeystone must be overridden if this is called.
     */      
    protected void enableActionSetHorizontalKeystone()
    {
        Action action = new Action("SetHorizontalKeystone");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterInt("DesiredHorizontalKeystone"));
        iDelegateSetHorizontalKeystone = new DoSetHorizontalKeystone();
        enableAction(action, iDelegateSetHorizontalKeystone);
    }

    /**
     * Signal that the action GetVerticalKeystone is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetVerticalKeystone must be overridden if this is called.
     */      
    protected void enableActionGetVerticalKeystone()
    {
        Action action = new Action("GetVerticalKeystone");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addOutputParameter(new ParameterInt("CurrentVerticalKeystone"));
        iDelegateGetVerticalKeystone = new DoGetVerticalKeystone();
        enableAction(action, iDelegateGetVerticalKeystone);
    }

    /**
     * Signal that the action SetVerticalKeystone is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetVerticalKeystone must be overridden if this is called.
     */      
    protected void enableActionSetVerticalKeystone()
    {
        Action action = new Action("SetVerticalKeystone");
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterInt("DesiredVerticalKeystone"));
        iDelegateSetVerticalKeystone = new DoSetVerticalKeystone();
        enableAction(action, iDelegateSetVerticalKeystone);
    }

    /**
     * Signal that the action GetMute is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetMute must be overridden if this is called.
     */      
    protected void enableActionGetMute()
    {
        Action action = new Action("GetMute");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addOutputParameter(new ParameterBool("CurrentMute"));
        iDelegateGetMute = new DoGetMute();
        enableAction(action, iDelegateGetMute);
    }

    /**
     * Signal that the action SetMute is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetMute must be overridden if this is called.
     */      
    protected void enableActionSetMute()
    {
        Action action = new Action("SetMute");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addInputParameter(new ParameterBool("DesiredMute"));
        iDelegateSetMute = new DoSetMute();
        enableAction(action, iDelegateSetMute);
    }

    /**
     * Signal that the action GetVolume is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetVolume must be overridden if this is called.
     */      
    protected void enableActionGetVolume()
    {
        Action action = new Action("GetVolume");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addOutputParameter(new ParameterUint("CurrentVolume", 0, 2147483647, 1));
        iDelegateGetVolume = new DoGetVolume();
        enableAction(action, iDelegateGetVolume);
    }

    /**
     * Signal that the action SetVolume is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetVolume must be overridden if this is called.
     */      
    protected void enableActionSetVolume()
    {
        Action action = new Action("SetVolume");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addInputParameter(new ParameterUint("DesiredVolume", 0, 2147483647, 1));
        iDelegateSetVolume = new DoSetVolume();
        enableAction(action, iDelegateSetVolume);
    }

    /**
     * Signal that the action GetVolumeDB is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetVolumeDB must be overridden if this is called.
     */      
    protected void enableActionGetVolumeDB()
    {
        Action action = new Action("GetVolumeDB");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addOutputParameter(new ParameterInt("CurrentVolume"));
        iDelegateGetVolumeDB = new DoGetVolumeDB();
        enableAction(action, iDelegateGetVolumeDB);
    }

    /**
     * Signal that the action SetVolumeDB is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetVolumeDB must be overridden if this is called.
     */      
    protected void enableActionSetVolumeDB()
    {
        Action action = new Action("SetVolumeDB");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addInputParameter(new ParameterInt("DesiredVolume"));
        iDelegateSetVolumeDB = new DoSetVolumeDB();
        enableAction(action, iDelegateSetVolumeDB);
    }

    /**
     * Signal that the action GetVolumeDBRange is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetVolumeDBRange must be overridden if this is called.
     */      
    protected void enableActionGetVolumeDBRange()
    {
        Action action = new Action("GetVolumeDBRange");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addOutputParameter(new ParameterInt("MinValue"));
        action.addOutputParameter(new ParameterInt("MaxValue"));
        iDelegateGetVolumeDBRange = new DoGetVolumeDBRange();
        enableAction(action, iDelegateGetVolumeDBRange);
    }

    /**
     * Signal that the action GetLoudness is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetLoudness must be overridden if this is called.
     */      
    protected void enableActionGetLoudness()
    {
        Action action = new Action("GetLoudness");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addOutputParameter(new ParameterBool("CurrentLoudness"));
        iDelegateGetLoudness = new DoGetLoudness();
        enableAction(action, iDelegateGetLoudness);
    }

    /**
     * Signal that the action SetLoudness is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetLoudness must be overridden if this is called.
     */      
    protected void enableActionSetLoudness()
    {
        Action action = new Action("SetLoudness");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("Channel", allowedValues));
        action.addInputParameter(new ParameterBool("DesiredLoudness"));
        iDelegateSetLoudness = new DoSetLoudness();
        enableAction(action, iDelegateSetLoudness);
    }

    /**
     * Signal that the action GetStateVariables is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetStateVariables must be overridden if this is called.
     */      
    protected void enableActionGetStateVariables()
    {
        Action action = new Action("GetStateVariables");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("StateVariableList", allowedValues));
        action.addOutputParameter(new ParameterString("StateVariableValuePairs", allowedValues));
        iDelegateGetStateVariables = new DoGetStateVariables();
        enableAction(action, iDelegateGetStateVariables);
    }

    /**
     * Signal that the action SetStateVariables is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetStateVariables must be overridden if this is called.
     */      
    protected void enableActionSetStateVariables()
    {
        Action action = new Action("SetStateVariables");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("InstanceID"));
        action.addInputParameter(new ParameterString("RenderingControlUDN", allowedValues));
        action.addInputParameter(new ParameterString("ServiceType", allowedValues));
        action.addInputParameter(new ParameterString("ServiceId", allowedValues));
        action.addInputParameter(new ParameterString("StateVariableValuePairs", allowedValues));
        action.addOutputParameter(new ParameterString("StateVariableList", allowedValues));
        iDelegateSetStateVariables = new DoSetStateVariables();
        enableAction(action, iDelegateSetStateVariables);
    }

    /**
     * ListPresets action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ListPresets action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionListPresets} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected String listPresets(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SelectPreset action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SelectPreset action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSelectPreset} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aPresetName
     */
    protected void selectPreset(IDvInvocation aInvocation, long aInstanceID, String aPresetName)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetBrightness action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetBrightness action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetBrightness} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getBrightness(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetBrightness action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetBrightness action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetBrightness} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredBrightness
     */
    protected void setBrightness(IDvInvocation aInvocation, long aInstanceID, long aDesiredBrightness)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetContrast action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetContrast action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetContrast} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getContrast(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetContrast action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetContrast action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetContrast} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredContrast
     */
    protected void setContrast(IDvInvocation aInvocation, long aInstanceID, long aDesiredContrast)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetSharpness action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetSharpness action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetSharpness} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getSharpness(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetSharpness action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetSharpness action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetSharpness} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredSharpness
     */
    protected void setSharpness(IDvInvocation aInvocation, long aInstanceID, long aDesiredSharpness)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRedVideoGain action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRedVideoGain action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRedVideoGain} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getRedVideoGain(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetRedVideoGain action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetRedVideoGain action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetRedVideoGain} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredRedVideoGain
     */
    protected void setRedVideoGain(IDvInvocation aInvocation, long aInstanceID, long aDesiredRedVideoGain)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetGreenVideoGain action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetGreenVideoGain action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetGreenVideoGain} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getGreenVideoGain(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetGreenVideoGain action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetGreenVideoGain action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetGreenVideoGain} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredGreenVideoGain
     */
    protected void setGreenVideoGain(IDvInvocation aInvocation, long aInstanceID, long aDesiredGreenVideoGain)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetBlueVideoGain action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetBlueVideoGain action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetBlueVideoGain} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getBlueVideoGain(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetBlueVideoGain action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetBlueVideoGain action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetBlueVideoGain} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredBlueVideoGain
     */
    protected void setBlueVideoGain(IDvInvocation aInvocation, long aInstanceID, long aDesiredBlueVideoGain)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRedVideoBlackLevel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRedVideoBlackLevel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRedVideoBlackLevel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getRedVideoBlackLevel(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetRedVideoBlackLevel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetRedVideoBlackLevel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetRedVideoBlackLevel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredRedVideoBlackLevel
     */
    protected void setRedVideoBlackLevel(IDvInvocation aInvocation, long aInstanceID, long aDesiredRedVideoBlackLevel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetGreenVideoBlackLevel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetGreenVideoBlackLevel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetGreenVideoBlackLevel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getGreenVideoBlackLevel(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetGreenVideoBlackLevel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetGreenVideoBlackLevel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetGreenVideoBlackLevel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredGreenVideoBlackLevel
     */
    protected void setGreenVideoBlackLevel(IDvInvocation aInvocation, long aInstanceID, long aDesiredGreenVideoBlackLevel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetBlueVideoBlackLevel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetBlueVideoBlackLevel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetBlueVideoBlackLevel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getBlueVideoBlackLevel(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetBlueVideoBlackLevel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetBlueVideoBlackLevel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetBlueVideoBlackLevel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredBlueVideoBlackLevel
     */
    protected void setBlueVideoBlackLevel(IDvInvocation aInvocation, long aInstanceID, long aDesiredBlueVideoBlackLevel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetColorTemperature action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetColorTemperature action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetColorTemperature} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected long getColorTemperature(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetColorTemperature action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetColorTemperature action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetColorTemperature} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredColorTemperature
     */
    protected void setColorTemperature(IDvInvocation aInvocation, long aInstanceID, long aDesiredColorTemperature)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetHorizontalKeystone action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetHorizontalKeystone action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetHorizontalKeystone} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected int getHorizontalKeystone(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetHorizontalKeystone action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetHorizontalKeystone action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetHorizontalKeystone} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredHorizontalKeystone
     */
    protected void setHorizontalKeystone(IDvInvocation aInvocation, long aInstanceID, int aDesiredHorizontalKeystone)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetVerticalKeystone action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetVerticalKeystone action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetVerticalKeystone} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     */
    protected int getVerticalKeystone(IDvInvocation aInvocation, long aInstanceID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetVerticalKeystone action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetVerticalKeystone action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetVerticalKeystone} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aDesiredVerticalKeystone
     */
    protected void setVerticalKeystone(IDvInvocation aInvocation, long aInstanceID, int aDesiredVerticalKeystone)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetMute action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetMute action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetMute} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     */
    protected boolean getMute(IDvInvocation aInvocation, long aInstanceID, String aChannel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetMute action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetMute action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetMute} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     * @param aDesiredMute
     */
    protected void setMute(IDvInvocation aInvocation, long aInstanceID, String aChannel, boolean aDesiredMute)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetVolume action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetVolume action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetVolume} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     */
    protected long getVolume(IDvInvocation aInvocation, long aInstanceID, String aChannel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetVolume action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetVolume action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetVolume} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     * @param aDesiredVolume
     */
    protected void setVolume(IDvInvocation aInvocation, long aInstanceID, String aChannel, long aDesiredVolume)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetVolumeDB action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetVolumeDB action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetVolumeDB} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     */
    protected int getVolumeDB(IDvInvocation aInvocation, long aInstanceID, String aChannel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetVolumeDB action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetVolumeDB action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetVolumeDB} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     * @param aDesiredVolume
     */
    protected void setVolumeDB(IDvInvocation aInvocation, long aInstanceID, String aChannel, int aDesiredVolume)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetVolumeDBRange action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetVolumeDBRange action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetVolumeDBRange} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     */
    protected GetVolumeDBRange getVolumeDBRange(IDvInvocation aInvocation, long aInstanceID, String aChannel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetLoudness action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetLoudness action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetLoudness} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     */
    protected boolean getLoudness(IDvInvocation aInvocation, long aInstanceID, String aChannel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetLoudness action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetLoudness action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetLoudness} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aChannel
     * @param aDesiredLoudness
     */
    protected void setLoudness(IDvInvocation aInvocation, long aInstanceID, String aChannel, boolean aDesiredLoudness)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetStateVariables action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetStateVariables action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetStateVariables} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aStateVariableList
     */
    protected String getStateVariables(IDvInvocation aInvocation, long aInstanceID, String aStateVariableList)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetStateVariables action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetStateVariables action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetStateVariables} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aInstanceID
     * @param aRenderingControlUDN
     * @param aServiceType
     * @param aServiceId
     * @param aStateVariableValuePairs
     */
    protected String setStateVariables(IDvInvocation aInvocation, long aInstanceID, String aRenderingControlUDN, String aServiceType, String aServiceId, String aStateVariableValuePairs)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Must be called for each class instance.  Must be called before Core.Library.Close().
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            super.dispose();
            iHandle = 0;
        }
    }


    private class DoListPresets implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String currentPresetNameList;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentPresetNameList = listPresets(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ListPresets");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("CurrentPresetNameList", currentPresetNameList);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSelectPreset implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String presetName;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                presetName = invocation.readString("PresetName");
                invocation.readEnd();
                selectPreset(invocation, instanceID, presetName);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SelectPreset");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetBrightness implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentBrightness;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentBrightness = getBrightness(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetBrightness");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentBrightness", currentBrightness);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetBrightness implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredBrightness;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredBrightness = invocation.readUint("DesiredBrightness");
                invocation.readEnd();
                setBrightness(invocation, instanceID, desiredBrightness);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetBrightness");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetContrast implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentContrast;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentContrast = getContrast(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetContrast");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentContrast", currentContrast);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetContrast implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredContrast;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredContrast = invocation.readUint("DesiredContrast");
                invocation.readEnd();
                setContrast(invocation, instanceID, desiredContrast);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetContrast");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetSharpness implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentSharpness;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentSharpness = getSharpness(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetSharpness");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentSharpness", currentSharpness);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetSharpness implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredSharpness;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredSharpness = invocation.readUint("DesiredSharpness");
                invocation.readEnd();
                setSharpness(invocation, instanceID, desiredSharpness);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetSharpness");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetRedVideoGain implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentRedVideoGain;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentRedVideoGain = getRedVideoGain(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRedVideoGain");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentRedVideoGain", currentRedVideoGain);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetRedVideoGain implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredRedVideoGain;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredRedVideoGain = invocation.readUint("DesiredRedVideoGain");
                invocation.readEnd();
                setRedVideoGain(invocation, instanceID, desiredRedVideoGain);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetRedVideoGain");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetGreenVideoGain implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentGreenVideoGain;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentGreenVideoGain = getGreenVideoGain(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetGreenVideoGain");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentGreenVideoGain", currentGreenVideoGain);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetGreenVideoGain implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredGreenVideoGain;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredGreenVideoGain = invocation.readUint("DesiredGreenVideoGain");
                invocation.readEnd();
                setGreenVideoGain(invocation, instanceID, desiredGreenVideoGain);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetGreenVideoGain");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetBlueVideoGain implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentBlueVideoGain;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentBlueVideoGain = getBlueVideoGain(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetBlueVideoGain");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentBlueVideoGain", currentBlueVideoGain);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetBlueVideoGain implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredBlueVideoGain;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredBlueVideoGain = invocation.readUint("DesiredBlueVideoGain");
                invocation.readEnd();
                setBlueVideoGain(invocation, instanceID, desiredBlueVideoGain);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetBlueVideoGain");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetRedVideoBlackLevel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentRedVideoBlackLevel;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentRedVideoBlackLevel = getRedVideoBlackLevel(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRedVideoBlackLevel");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentRedVideoBlackLevel", currentRedVideoBlackLevel);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetRedVideoBlackLevel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredRedVideoBlackLevel;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredRedVideoBlackLevel = invocation.readUint("DesiredRedVideoBlackLevel");
                invocation.readEnd();
                setRedVideoBlackLevel(invocation, instanceID, desiredRedVideoBlackLevel);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetRedVideoBlackLevel");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetGreenVideoBlackLevel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentGreenVideoBlackLevel;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentGreenVideoBlackLevel = getGreenVideoBlackLevel(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetGreenVideoBlackLevel");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentGreenVideoBlackLevel", currentGreenVideoBlackLevel);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetGreenVideoBlackLevel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredGreenVideoBlackLevel;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredGreenVideoBlackLevel = invocation.readUint("DesiredGreenVideoBlackLevel");
                invocation.readEnd();
                setGreenVideoBlackLevel(invocation, instanceID, desiredGreenVideoBlackLevel);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetGreenVideoBlackLevel");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetBlueVideoBlackLevel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentBlueVideoBlackLevel;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentBlueVideoBlackLevel = getBlueVideoBlackLevel(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetBlueVideoBlackLevel");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentBlueVideoBlackLevel", currentBlueVideoBlackLevel);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetBlueVideoBlackLevel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredBlueVideoBlackLevel;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredBlueVideoBlackLevel = invocation.readUint("DesiredBlueVideoBlackLevel");
                invocation.readEnd();
                setBlueVideoBlackLevel(invocation, instanceID, desiredBlueVideoBlackLevel);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetBlueVideoBlackLevel");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetColorTemperature implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long currentColorTemperature;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentColorTemperature = getColorTemperature(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetColorTemperature");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentColorTemperature", currentColorTemperature);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetColorTemperature implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            long desiredColorTemperature;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredColorTemperature = invocation.readUint("DesiredColorTemperature");
                invocation.readEnd();
                setColorTemperature(invocation, instanceID, desiredColorTemperature);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetColorTemperature");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetHorizontalKeystone implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            int currentHorizontalKeystone;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentHorizontalKeystone = getHorizontalKeystone(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetHorizontalKeystone");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeInt("CurrentHorizontalKeystone", currentHorizontalKeystone);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetHorizontalKeystone implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            int desiredHorizontalKeystone;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredHorizontalKeystone = invocation.readInt("DesiredHorizontalKeystone");
                invocation.readEnd();
                setHorizontalKeystone(invocation, instanceID, desiredHorizontalKeystone);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetHorizontalKeystone");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetVerticalKeystone implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            int currentVerticalKeystone;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                invocation.readEnd();
                 currentVerticalKeystone = getVerticalKeystone(invocation, instanceID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetVerticalKeystone");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeInt("CurrentVerticalKeystone", currentVerticalKeystone);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetVerticalKeystone implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            int desiredVerticalKeystone;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                desiredVerticalKeystone = invocation.readInt("DesiredVerticalKeystone");
                invocation.readEnd();
                setVerticalKeystone(invocation, instanceID, desiredVerticalKeystone);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetVerticalKeystone");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetMute implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            boolean currentMute;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                invocation.readEnd();
                 currentMute = getMute(invocation, instanceID, channel);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetMute");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeBool("CurrentMute", currentMute);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetMute implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            boolean desiredMute;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                desiredMute = invocation.readBool("DesiredMute");
                invocation.readEnd();
                setMute(invocation, instanceID, channel, desiredMute);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetMute");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetVolume implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            long currentVolume;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                invocation.readEnd();
                 currentVolume = getVolume(invocation, instanceID, channel);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetVolume");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("CurrentVolume", currentVolume);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetVolume implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            long desiredVolume;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                desiredVolume = invocation.readUint("DesiredVolume");
                invocation.readEnd();
                setVolume(invocation, instanceID, channel, desiredVolume);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetVolume");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetVolumeDB implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            int currentVolume;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                invocation.readEnd();
                 currentVolume = getVolumeDB(invocation, instanceID, channel);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetVolumeDB");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeInt("CurrentVolume", currentVolume);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetVolumeDB implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            int desiredVolume;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                desiredVolume = invocation.readInt("DesiredVolume");
                invocation.readEnd();
                setVolumeDB(invocation, instanceID, channel, desiredVolume);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetVolumeDB");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetVolumeDBRange implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            int minValue;
            int maxValue;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                invocation.readEnd();

            GetVolumeDBRange outArgs = getVolumeDBRange(invocation, instanceID, channel);
            minValue = outArgs.getMinValue();
            maxValue = outArgs.getMaxValue();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetVolumeDBRange");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeInt("MinValue", minValue);
                invocation.writeInt("MaxValue", maxValue);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetLoudness implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            boolean currentLoudness;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                invocation.readEnd();
                 currentLoudness = getLoudness(invocation, instanceID, channel);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetLoudness");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeBool("CurrentLoudness", currentLoudness);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetLoudness implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String channel;
            boolean desiredLoudness;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                channel = invocation.readString("Channel");
                desiredLoudness = invocation.readBool("DesiredLoudness");
                invocation.readEnd();
                setLoudness(invocation, instanceID, channel, desiredLoudness);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetLoudness");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetStateVariables implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String stateVariableList;
            String stateVariableValuePairs;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                stateVariableList = invocation.readString("StateVariableList");
                invocation.readEnd();
                 stateVariableValuePairs = getStateVariables(invocation, instanceID, stateVariableList);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetStateVariables");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("StateVariableValuePairs", stateVariableValuePairs);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetStateVariables implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long instanceID;
            String renderingControlUDN;
            String serviceType;
            String serviceId;
            String stateVariableValuePairs;
            String stateVariableList;
            try
            {
                invocation.readStart();
                instanceID = invocation.readUint("InstanceID");
                renderingControlUDN = invocation.readString("RenderingControlUDN");
                serviceType = invocation.readString("ServiceType");
                serviceId = invocation.readString("ServiceId");
                stateVariableValuePairs = invocation.readString("StateVariableValuePairs");
                invocation.readEnd();
                 stateVariableList = setStateVariables(invocation, instanceID, renderingControlUDN, serviceType, serviceId, stateVariableValuePairs);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetStateVariables");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("StateVariableList", stateVariableList);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }
}

